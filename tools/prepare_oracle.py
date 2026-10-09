# -*- coding: utf-8 -*-
"""prepare_oracle.py — 受控神谕工作流 Phase 1：冻结现场与拷贝（幂等，可重复运行）。

设计依据 docs/oracle_workflow.md §2 Phase 1：
  1) Steam 完整性基线：对 "Backpack Battles/" 下全部文件（递归）计算 MD5，
     写 output/oracle/steam_baseline.json（相对路径 -> md5）。
     history.db 可能被运行中的游戏写入——基线只记录运行当时的状态；
     本工作流全程不写这些文件，Phase 5 用同一脚本复核基线以证明零修改。
  2) 拷贝 extracted_running/decomp/ -> oracle/（工作副本，随意改），
     跳过 .godot 缓存与 .autoconverted。
  3) 拷贝 history.db 最新快照 -> oracle/data/history.db。
     实际路径： %APPDATA%/Godot/app_userdata/Backpack Battles/*/full/history.db
     按 mtime 取最新；优先走 SQLite 只读 backup API（对运行中的库取一致快照），
     失败则回退为原始字节拷贝。
  4) 幂等：oracle/ 已存在且非空时，逐文件跳过（size + mtime_ns 一致视为已完成），
     只重新校验基线并更新 db 快照。

红线（docs/oracle_workflow.md §4）：
  - 只读 Steam 目录 "Backpack Battles/"，绝不写入/修改其中任何文件；
  - 全程无头后台，不启动任何窗口/游戏进程，不进入排名/休闲/在线模式。
"""

import hashlib
import json
import os
import shutil
import sqlite3
import sys
import time
from pathlib import Path

# ---------------------------------------------------------------- 常量与路径

ROOT = Path(__file__).resolve().parent.parent
STEAM_GAME_DIR = ROOT / "Backpack Battles"          # Steam 版游戏目录（只读！）
DECOMP_SRC = ROOT / "extracted_running" / "decomp"  # 1.1.8 运行版反编译全量源码
ORACLE_DIR = ROOT / "oracle"                        # 神谕工作副本
ORACLE_DATA_DIR = ORACLE_DIR / "data"
BASELINE_JSON = ROOT / "output" / "oracle" / "steam_baseline.json"
DB_SNAPSHOT = ORACLE_DATA_DIR / "history.db"
DB_SNAPSHOT_META = ORACLE_DATA_DIR / "history_snapshot.json"

# 跳过的目录名：.godot=Godot 编辑器/导入缓存；.autoconverted=gdre 反编译工具的转换产物
SKIP_DIR_NAMES = {".godot", ".autoconverted"}

# history.db 快照的候选 glob（相对 %APPDATA%）
APPDATA = Path(os.environ["APPDATA"])
DB_GLOB_ROOT = APPDATA / "Godot" / "app_userdata" / "Backpack Battles"
DB_GLOB = "*/full/history.db"

MD5_CHUNK = 1 << 20  # 1 MiB


def fail(msg: str) -> None:
    """fail-fast：现场冻结失败必须中止，绝不带病继续。"""
    raise SystemExit(f"[prepare_oracle][FATAL] {msg}")


def md5_of_file(path: Path) -> str:
    """流式计算文件 MD5（大文件友好）。"""
    h = hashlib.md5()
    with path.open("rb") as f:
        while True:
            chunk = f.read(MD5_CHUNK)
            if not chunk:
                break
            h.update(chunk)
    return h.hexdigest()


# ---------------------------------------------------- 步骤 1：Steam 完整性基线

def build_steam_baseline() -> dict:
    """对 Steam 游戏目录递归计算全部文件的 MD5，写 output/oracle/steam_baseline.json。

    只读操作：os.walk + open("rb")，不打开任何写句柄。
    """
    if not STEAM_GAME_DIR.is_dir():
        fail(f"Steam 游戏目录不存在: {STEAM_GAME_DIR}")
    baseline: dict[str, str] = {}
    total_bytes = 0
    for dirpath, dirnames, filenames in os.walk(STEAM_GAME_DIR):
        dirnames.sort()
        for name in sorted(filenames):
            full = Path(dirpath) / name
            rel = full.relative_to(STEAM_GAME_DIR).as_posix()  # JSON 键统一 posix 分隔符
            if not full.is_file():
                fail(f"基线遍历遇到非普通文件: {full}")
            baseline[rel] = md5_of_file(full)
            total_bytes += full.stat().st_size
    BASELINE_JSON.parent.mkdir(parents=True, exist_ok=True)
    BASELINE_JSON.write_text(
        json.dumps(baseline, ensure_ascii=False, indent=2, sort_keys=True) + "\n",
        encoding="utf-8",
    )
    return baseline, total_bytes


# ---------------------------------------------- 步骤 2：decomp -> oracle/ 拷贝

def sync_decomp_to_oracle() -> dict:
    """把 extracted_running/decomp/ 拷到 oracle/（跳过 .godot/.autoconverted）。

    幂等策略：目标文件已存在且 size 与 mtime_ns 一致（±2ms，NTFS 精度余量）
    即跳过；否则重新拷贝。copy2 保留 mtime，使下一轮比较成立。
    """
    if not DECOMP_SRC.is_dir():
        fail(f"反编译源码目录不存在: {DECOMP_SRC}")
    stats = {"copied": 0, "skipped": 0, "bytes": 0, "dirs_created": 0}
    for dirpath, dirnames, filenames in os.walk(DECOMP_SRC):
        # 就地过滤：让 os.walk 不进入被跳过的目录（.godot 缓存 / .autoconverted）
        dirnames[:] = sorted(d for d in dirnames if d not in SKIP_DIR_NAMES)
        src_dir = Path(dirpath)
        rel_dir = src_dir.relative_to(DECOMP_SRC)
        dst_dir = ORACLE_DIR / rel_dir if str(rel_dir) != "." else ORACLE_DIR
        if not dst_dir.exists():
            dst_dir.mkdir(parents=True, exist_ok=True)
            stats["dirs_created"] += 1
        for name in sorted(filenames):
            src = src_dir / name
            dst = dst_dir / name
            if not src.is_file():
                fail(f"decomp 遍历遇到非普通文件: {src}")
            s_stat = src.stat()
            if dst.is_file():
                d_stat = dst.stat()
                if d_stat.st_size == s_stat.st_size and \
                        abs(d_stat.st_mtime_ns - s_stat.st_mtime_ns) <= 2_000_000:
                    stats["skipped"] += 1
                    continue
            shutil.copy2(src, dst)
            stats["copied"] += 1
            stats["bytes"] += s_stat.st_size
    return stats


# ------------------------------------------ 步骤 3：history.db 最新快照拷贝

def snapshot_history_db() -> dict:
    """取 %APPDATA%/.../Backpack Battles/*/full/history.db 中 mtime 最新的一个，
    快照到 oracle/data/history.db。

    优先用 SQLite 只读 backup API：对可能正被运行中的游戏写入的库取得
    事务一致的快照，且以 mode=ro 打开源库（绝不写源文件）。
    回退：原始字节拷贝（记录在 meta 中）。
    """
    if not DB_GLOB_ROOT.is_dir():
        fail(f"Godot 用户数据目录不存在: {DB_GLOB_ROOT}")
    candidates = sorted(DB_GLOB_ROOT.glob(DB_GLOB))
    if not candidates:
        fail(f"未找到任何 history.db 快照候选（glob={DB_GLOB_ROOT / DB_GLOB}）")
    # 按 mtime 取最新；mtime 相同再按 size 取大者
    newest = max(candidates, key=lambda p: (p.stat().st_mtime_ns, p.stat().st_size))
    src_stat = newest.stat()

    ORACLE_DATA_DIR.mkdir(parents=True, exist_ok=True)
    method = "sqlite_backup"
    try:
        src_uri = newest.as_uri() + "?mode=ro"  # 只读打开，保证不写源库
        with sqlite3.connect(src_uri, uri=True, timeout=5.0) as src_conn:
            with sqlite3.connect(DB_SNAPSHOT) as dst_conn:
                src_conn.backup(dst_conn)  # 页级一致快照
    except sqlite3.Error as exc:
        # 回退为原始拷贝（例如库损坏/被独占锁）
        print(f"[prepare_oracle][WARN] SQLite backup 失败（{exc}），回退原始字节拷贝")
        shutil.copy2(newest, DB_SNAPSHOT)
        method = "raw_copy"

    snap_size = DB_SNAPSHOT.stat().st_size
    if snap_size == 0:
        fail(f"快照拷贝得到 0 字节文件: {DB_SNAPSHOT}")
    snap_md5 = md5_of_file(DB_SNAPSHOT)

    # 一致性自检：目标端 quick_check（只读快照，不影响源）
    integrity = "not_checked"
    try:
        with sqlite3.connect(f"file:{DB_SNAPSHOT.as_uri()[8:]}?mode=ro", uri=True) as conn:
            integrity = conn.execute("PRAGMA quick_check").fetchone()[0]
    except sqlite3.Error:
        pass  # 原始拷贝时源库可能正在写，quick_check 失败不致命，如实记录

    meta = {
        "source_path": str(newest),
        "source_mtime_ns": src_stat.st_mtime_ns,
        "source_size": src_stat.st_size,
        "candidates": [
            {"path": str(p), "mtime_ns": p.stat().st_mtime_ns, "size": p.stat().st_size}
            for p in candidates
        ],
        "snapshot_path": str(DB_SNAPSHOT),
        "snapshot_size": snap_size,
        "snapshot_md5": snap_md5,
        "method": method,
        "quick_check": integrity,
        "taken_at": time.strftime("%Y-%m-%dT%H:%M:%S"),
    }
    DB_SNAPSHOT_META.write_text(
        json.dumps(meta, ensure_ascii=False, indent=2) + "\n", encoding="utf-8"
    )
    return meta


# ------------------------------------------------------------------ 主流程

def main() -> int:
    try:
        sys.stdout.reconfigure(encoding="utf-8", errors="replace")  # -X utf8 之外的兜底
    except Exception:
        pass
    t0 = time.time()
    print("[prepare_oracle] Phase 1 冻结现场开始（只读 Steam 目录，无头后台）")

    # 1) Steam 完整性基线（每次运行重算 = 对当前状态的校验/复核）
    baseline, baseline_bytes = build_steam_baseline()
    print(f"[prepare_oracle][1] Steam 基线: {len(baseline)} 个文件, "
          f"{baseline_bytes} 字节 -> {BASELINE_JSON.relative_to(ROOT)}")
    for rel, digest in sorted(baseline.items()):
        print(f"    {digest}  {rel}")

    # 2) decomp -> oracle/（幂等：已一致的文件跳过）
    oracle_existed = ORACLE_DIR.is_dir() and any(ORACLE_DIR.iterdir())
    sync = sync_decomp_to_oracle()
    mode = "增量更新" if oracle_existed else "首次拷贝"
    print(f"[prepare_oracle][2] decomp -> oracle/ ({mode}): "
          f"新拷 {sync['copied']} 个文件 / {sync['bytes']} 字节, "
          f"跳过已一致 {sync['skipped']} 个, 建目录 {sync['dirs_created']} 个")

    # 3) history.db 最新快照（每次运行都刷新 = db 快照更新）
    meta = snapshot_history_db()
    print(f"[prepare_oracle][3] history.db 快照: 源={meta['source_path']} "
          f"({meta['source_size']} 字节, 候选 {len(meta['candidates'])} 个)")
    print(f"    -> {DB_SNAPSHOT.relative_to(ROOT)} ({meta['snapshot_size']} 字节, "
          f"md5={meta['snapshot_md5']}, 方式={meta['method']}, quick_check={meta['quick_check']})")

    print(f"[prepare_oracle] 完成，耗时 {time.time() - t0:.1f}s，exit 0")
    return 0


if __name__ == "__main__":
    sys.exit(main())
