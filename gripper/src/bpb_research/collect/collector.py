"""采集器骨架：批次目录 + manifest 指纹 + 冷却状态机 + JSON 日志。

不依赖 Steam：数据源可插拔（steam / web / local）。
只写工作区 database/，绝不写游戏目录。
"""
from __future__ import annotations

import hashlib
import json
import os
import time
from dataclasses import dataclass, field
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Callable

SUCCESS_DELAY = 1200
FAILURE_DELAY = 300
SCHEMA = 1


def fingerprint(path: Path) -> dict[str, Any]:
    data = path.read_bytes()
    return {"sha256": hashlib.sha256(data).hexdigest(), "size": len(data)}


def utc_now() -> str:
    return datetime.now(timezone.utc).isoformat()


@dataclass
class Batch:
    root: Path
    batch_id: str
    state: dict = field(default_factory=dict)

    @property
    def dir(self) -> Path:
        return self.root / self.batch_id

    @property
    def manifest_path(self) -> Path:
        return self.dir / "manifest.json"

    def write_manifest(self) -> None:
        self.manifest_path.write_text(
            json.dumps(self.state, ensure_ascii=False, indent=2), encoding="utf-8"
        )

    def add(self, name: str, data: bytes) -> None:
        target = self.dir / name
        target.write_bytes(data)
        self.state.setdefault("files", {})[name] = fingerprint(target)


class Collector:
    """一轮采集：取源 → 落盘 → 校验 → 冷却记账。"""

    def __init__(self, database_dir: Path, source: Callable[[], bytes], source_name: str = "source"):
        self.database_dir = Path(database_dir)
        self.source = source
        self.source_name = source_name
        self.root = self.database_dir / "downloads"
        self.state_path = self.root / "state.json"
        self.log_path = self.root / "collect.log"

    def cooldown_remaining(self) -> int:
        if not self.state_path.exists():
            return 0
        state = json.loads(self.state_path.read_text(encoding="utf-8"))
        return max(0, int(state.get("next_allowed_at", 0) - time.time()))

    def log(self, event: str, **fields: Any) -> None:
        self.root.mkdir(parents=True, exist_ok=True)
        line = json.dumps({"at": utc_now(), "event": event, **fields}, ensure_ascii=False)
        with self.log_path.open("a", encoding="utf-8") as f:
            f.write(line + "\n")

    def run_once(self, *, force: bool = False) -> dict[str, Any]:
        wait = 0 if force else self.cooldown_remaining()
        if wait > 0:
            self.log("cooldown", remaining=wait)
            return {"status": "cooldown", "remaining": wait}

        started = time.time()
        state = {}
        if self.state_path.exists():
            try:
                state = json.loads(self.state_path.read_text(encoding="utf-8"))
            except Exception:
                state = {}

        # 先取数据算指纹：内容未变就不建新批次，避免缓存不变时堆垃圾
        try:
            payload = self.source()
        except Exception as error:
            batch_id = datetime.now(timezone.utc).strftime("%Y%m%d_%H%M%S_%fZ")
            batch = Batch(self.root, batch_id)
            batch.dir.mkdir(parents=True, exist_ok=True)
            batch.state = {
                "schema_version": SCHEMA,
                "status": "failed",
                "created_at": utc_now(),
                "source": self.source_name,
                "error": str(error)[:500],
                "failed_at": utc_now(),
            }
            batch.write_manifest()
            next_at = time.time() + FAILURE_DELAY
            self.log("failed", batch=batch_id, error=str(error)[:200])
            self._save_state(started, next_at, state.get("last_sha"))
            return {"status": "failed", "batch": batch_id, "next_in": int(next_at - time.time())}

        sha = hashlib.sha256(payload).hexdigest()
        unchanged = (not force) and state.get("last_sha") == sha and state.get("status") == "complete"
        if unchanged:
            next_at = time.time() + SUCCESS_DELAY
            self.log("unchanged", sha=sha[:12])
            self._save_state(started, next_at, sha, status="complete")
            return {"status": "unchanged", "sha": sha[:12], "next_in": int(next_at - time.time())}

        batch_id = datetime.now(timezone.utc).strftime("%Y%m%d_%H%M%S_%fZ")
        batch = Batch(self.root, batch_id)
        batch.dir.mkdir(parents=True, exist_ok=True)
        batch.state = {
            "schema_version": SCHEMA,
            "status": "running",
            "created_at": utc_now(),
            "source": self.source_name,
            "sha256": sha,
        }
        batch.write_manifest()
        try:
            batch.add("payload.json", payload)
            parsed = json.loads(payload)
            if isinstance(parsed, list):
                records = len(parsed)
            elif isinstance(parsed, dict) and "runs" in parsed:
                records = len(parsed["runs"])
            else:
                records = 1
            batch.state.update(status="complete", completed_at=utc_now(),
                               counts={"records": records},
                               elapsed=round(time.time() - started, 3))
            batch.write_manifest()
            next_at = time.time() + SUCCESS_DELAY
            self.log("complete", batch=batch_id, elapsed=batch.state["elapsed"], sha=sha[:12])
            status = "complete"
        except Exception as error:
            batch.state.update(status="failed", error=str(error)[:500], failed_at=utc_now())
            batch.write_manifest()
            next_at = time.time() + FAILURE_DELAY
            self.log("failed", batch=batch_id, error=str(error)[:200])
            status = "failed"
        self._save_state(started, next_at, sha, status=status)
        return {"status": status, "batch": batch_id, "next_in": int(next_at - time.time())}

    def _save_state(self, started: float, next_at: float, sha: str | None,
                    status: str | None = None) -> None:
        self.root.mkdir(parents=True, exist_ok=True)
        state = {
            "last_attempt_at": started,
            "next_allowed_at": next_at,
            "last_sha": sha,
            "status": status,
        }
        self.state_path.write_text(json.dumps(state, indent=2), encoding="utf-8")


def compress_old_batches(root: Path, keep_latest: int = 1) -> list[str]:
    """把较旧批次的 payload.json 压成 .gz，保留 manifest 与校验信息。"""
    import gzip
    complete = []
    for manifest in sorted((root / "downloads").glob("*/manifest.json")):
        try:
            data = json.loads(manifest.read_text(encoding="utf-8"))
        except Exception:
            continue
        if data.get("status") == "complete":
            complete.append(manifest.parent)
    compressed = []
    for old in complete[:-keep_latest] if keep_latest >= 0 else []:
        payload = old / "payload.json"
        if not payload.exists():
            continue
        with payload.open("rb") as src, gzip.open(str(payload) + ".gz", "wb") as dst:
            dst.write(src.read())
        payload.unlink()
        compressed.append(old.name)
    return compressed


def prune_batches(root: Path, keep: int = 3) -> list[str]:
    """只保留最近 keep 个已完成批次，避免长期运行堆积。返回被删除的批次名。"""
    complete = []
    for manifest in sorted((root / "downloads").glob("*/manifest.json")):
        try:
            data = json.loads(manifest.read_text(encoding="utf-8"))
        except Exception:
            continue
        if data.get("status") == "complete":
            complete.append(manifest.parent)
    removed = []
    for old in complete[:-keep] if keep > 0 else []:
        for child in old.glob("*"):
            try:
                child.unlink()
            except OSError:
                pass
        try:
            old.rmdir()
            removed.append(old.name)
        except OSError:
            pass
    return removed


def verified_batches(root: Path) -> list[Path]:
    out = []
    for manifest in sorted((root / "downloads").glob("*/manifest.json")):
        try:
            data = json.loads(manifest.read_text(encoding="utf-8"))
        except Exception:
            continue
        if data.get("status") != "complete":
            continue
        ok = True
        for name, meta in (data.get("files") or {}).items():
            target = manifest.parent / name
            compressed = manifest.parent / (name + ".gz")
            if target.exists():
                if fingerprint(target) != meta:
                    ok = False
                    break
            elif compressed.exists():
                # 旧批次 payload 已压缩：解压后按原 sha 校验
                import gzip
                with gzip.open(compressed, "rb") as f:
                    raw = f.read()
                if {"sha256": hashlib.sha256(raw).hexdigest(), "size": len(raw)} != meta:
                    ok = False
                    break
            else:
                ok = False
                break
        if ok:
            out.append(manifest.parent)
    return out