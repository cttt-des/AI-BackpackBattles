# -*- coding: utf-8 -*-
"""store.py — 对局记录写盘：局目录、回合分片、快照、归档

职责边界
--------
* 只管"怎么安全地把字节写到正确位置"，不关心事件语义（那是 recorder）；
* 写入策略面向**崩溃安全**：每个事件一次 `write + flush`，绝不拼接多行；
  归档走「压缩到临时文件 → 校验可解 → os.replace → 删明文」，任一步失败都
  保留明文并回报，**绝不丢数据**。

目录结构（docs/recorder_design.md §2）::

    <out_dir>/<run_id>/
    ├── meta.json
    ├── raw/R01.jsonl          (R01.jsonl.xz 为归档态)
    └── snapshots/R07_shop_open.json

stdout/日志都用简体中文；异常一律抛出 `StoreError`，由 recorder 决定是否收尾。
"""
from __future__ import annotations

import json
import logging
import lzma
import os
import shutil
import tempfile
from datetime import datetime
from pathlib import Path
from typing import Any, Dict, Optional

logger = logging.getLogger(__name__)

SCHEMA_VERSION = 4
COMPRESS_SUFFIXES = {"lzma": ".xz", "gzip": ".gz", "none": ""}


class StoreError(RuntimeError):
    """写盘不可恢复失败（磁盘满、权限、目录被删）。"""


def _json_dumps(obj: Any, indent: Optional[int] = None) -> str:
    return json.dumps(obj, ensure_ascii=False, indent=indent,
                      sort_keys=False, default=str)


class RunStore:
    """单个对局目录的写入器。

    线程模型：**只允许单线程调用**（recorder 采样线程）。不加锁以免在 GUI
    退出路径上死等。
    """

    def __init__(self, root: Path, run_id: str, compress: str = "lzma"):
        self.root = Path(root) / run_id
        self.run_id = run_id
        self.compress = compress if compress in COMPRESS_SUFFIXES else "lzma"
        self.raw_dir = self.root / "raw"
        self.snap_dir = self.root / "snapshots"
        self.meta_path = self.root / "meta.json"
        self._handle = None
        self._cur_round: Optional[int] = None
        self._archived: set = set()
        self._meta: Dict[str, Any] = {}
        self._archive_failed: list = []

    # ---------------- 生命周期 ----------------
    def open(self, meta: Dict[str, Any]) -> None:
        """创建目录并写 meta（覆盖写，幂等）。"""
        try:
            self.raw_dir.mkdir(parents=True, exist_ok=True)
            self.snap_dir.mkdir(parents=True, exist_ok=True)
        except OSError as e:
            raise StoreError(f"无法创建记录目录 {self.root}: {e}") from e
        self._meta = dict(meta)
        self._meta.setdefault("schema", SCHEMA_VERSION)
        self._meta.setdefault("run_id", self.run_id)
        self.write_meta()

    def write_meta(self) -> None:
        try:
            _atomic_write_text(self.meta_path, _json_dumps(self._meta, indent=2))
        except OSError as e:
            raise StoreError(f"写 meta.json 失败: {e}") from e

    def set_meta(self, **kw) -> None:
        """更新 meta 并立即落盘（结束信息、采样统计等）。"""
        self._meta.update(kw)
        self.write_meta()

    def meta(self) -> Dict[str, Any]:
        return dict(self._meta)

    # ---------------- 事件流 ----------------
    def append_event(self, event: Dict[str, Any]) -> None:
        """追加一条事件到当前回合分片；回合变化时自动切换分片。

        调用方负责 `round` 字段正确（recorder 保证）。
        """
        rnd = event.get("round")
        try:
            rnd_i = int(rnd) if rnd is not None else 0
        except (TypeError, ValueError):
            rnd_i = 0
        if rnd_i != self._cur_round:
            self._switch_round(rnd_i)
        line = _json_dumps(event)
        if "\n" in line:
            # 事件对象里出现裸换行说明有字段被序列化成了多行字符串；
            # JSONL 一行一条是硬约束，直接拒绝而不是写入坏行。
            raise StoreError("事件序列化后包含换行，违反 JSONL 约束")
        try:
            self._handle.write(line + "\n")
            self._handle.flush()
        except OSError as e:
            raise StoreError(f"写事件失败: {e}") from e

    def _switch_round(self, rnd: int) -> None:
        self.close_round()
        if self._archive_failed:
            self._archive_failed.clear()
        path = self.raw_dir / f"R{rnd:02d}.jsonl"
        try:
            self._handle = open(path, "a", encoding="utf-8", newline="\n")
        except OSError as e:
            raise StoreError(f"打开回合分片失败 {path}: {e}") from e
        self._cur_round = rnd

    def current_round(self) -> Optional[int]:
        return self._cur_round

    def close_round(self) -> None:
        if self._handle is not None:
            try:
                self._handle.flush()
                self._handle.close()
            except OSError:
                pass
            self._handle = None

    def archive_round(self, rnd: int) -> bool:
        """把 R{nn}.jsonl 压缩归档并删除明文。返回是否成功。

        失败时保留明文并记 `archive_failed`（meta 可查），**绝不丢数据**。
        """
        if self.compress == "none":
            return True
        if rnd in self._archived:
            return True
        if self._cur_round == rnd:
            self.close_round()
        src = self.raw_dir / f"R{rnd:02d}.jsonl"
        if not src.exists():
            return True
        dst = src.with_suffix(src.suffix + COMPRESS_SUFFIXES[self.compress])
        try:
            tmp = dst.with_suffix(dst.suffix + ".tmp")
            if self.compress == "lzma":
                with open(src, "rb") as fi, lzma.open(tmp, "wb",
                                                     preset=6) as fo:
                    shutil.copyfileobj(fi, fo)
                # 校验可解：解压后字节数必须与原文一致
                with lzma.open(tmp, "rb") as f:
                    got = len(f.read())
                want = src.stat().st_size
                if got != want:
                    raise OSError(f"压缩校验失败({got}!={want})")
            else:  # gzip 分支保留给将来；当前只用 lzma
                import gzip
                with open(src, "rb") as fi, gzip.open(tmp, "wb", 6) as fo:
                    shutil.copyfileobj(fi, fo)
            os.replace(tmp, dst)
            src.unlink()
            self._archived.add(rnd)
            return True
        except OSError as e:
            logger.warning("回合 %s 归档失败（保留明文）: %s", rnd, e)
            self._archive_failed.append({"round": rnd, "error": str(e)})
            try:
                tmp = dst.with_suffix(dst.suffix + ".tmp")
                if tmp.exists():
                    tmp.unlink()
            except OSError:
                pass
            return False

    def archive_all(self) -> None:
        self.close_round()
        for p in sorted(self.raw_dir.glob("R*.jsonl")):
            try:
                rnd = int(p.stem[1:])
            except ValueError:
                continue
            self.archive_round(rnd)

    # ---------------- 快照 ----------------
    def write_snapshot(self, name: str, data: Dict[str, Any]) -> str:
        """写快照到 snapshots/<name>.json，返回相对运行根的引用名。"""
        safe = "".join(c if (c.isalnum() or c in "_-") else "_" for c in name)
        path = self.snap_dir / f"{safe}.json"
        try:
            _atomic_write_text(path, _json_dumps(data, indent=2))
        except OSError as e:
            raise StoreError(f"写快照失败 {path}: {e}") from e
        return f"snapshots/{safe}.json"

    # ---------------- 收尾 ----------------
    def finish(self, **meta_updates) -> None:
        """归档全部回合 + 更新 meta。异常不抛出，最终由 recorder 记 end_reason。"""
        self.close_round()
        if self._archive_failed:
            meta_updates["archive_failed"] = list(self._archive_failed)
        self.archive_all()
        try:
            self._meta.update(meta_updates)
            self._meta.setdefault("ended_at", datetime.now().isoformat(timespec="seconds"))
            self.write_meta()
        except StoreError as e:  # 收尾阶段不再升级为崩溃
            logger.warning("收尾写 meta 失败: %s", e)


def _atomic_write_text(path: Path, text: str) -> None:
    """同目录临时文件 + os.replace，避免半截 JSON。"""
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, tmp = tempfile.mkstemp(prefix=".tmp_", dir=str(path.parent))
    try:
        with os.fdopen(fd, "w", encoding="utf-8", newline="\n") as f:
            f.write(text)
            f.flush()
            os.fsync(f.fileno())
        os.replace(tmp, path)
    except BaseException:
        try:
            Path(tmp).unlink()
        except OSError:
            pass
        raise


def new_run_id(now: Optional[datetime] = None, ordinal: int = 1) -> str:
    now = now or datetime.now()
    return now.strftime("%Y%m%d_%H%M%S") + f"_r{ordinal:02d}"


# ---------------- 读取侧（校验/折叠工具共用） ----------------
def iter_run_events(run_dir: Path):
    """按回合顺序产出 (round, event)。兼容明文与 lzma 归档两种状态。"""
    run_dir = Path(run_dir)
    raw = run_dir / "raw"
    if not raw.exists():
        return
    files = {}
    for p in raw.glob("R*.jsonl"):
        try:
            files[int(p.stem[1:])] = p
        except ValueError:
            continue
    for p in raw.glob("R*.jsonl.xz"):
        try:
            files[int(p.name[1:3])] = p
        except ValueError:
            continue
    for rnd in sorted(files):
        p = files[rnd]
        opener = lzma.open(p, "rt", encoding="utf-8") if p.suffix == ".xz" \
            else open(p, "r", encoding="utf-8")
        with opener as f:
            for line in f:
                line = line.strip()
                if not line:
                    continue
                try:
                    ev = json.loads(line)
                except json.JSONDecodeError:
                    logger.warning("%s 存在损坏行（已跳过）", p.name)
                    continue
                yield rnd, ev


def load_meta(run_dir: Path) -> Dict[str, Any]:
    p = Path(run_dir) / "meta.json"
    if not p.exists():
        return {}
    return json.loads(p.read_text(encoding="utf-8"))


def load_snapshot(run_dir: Path, ref: str) -> Optional[Dict[str, Any]]:
    p = Path(run_dir) / ref
    if not p.exists():
        return None
    return json.loads(p.read_text(encoding="utf-8"))
