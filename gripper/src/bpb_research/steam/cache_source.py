"""Steam run 缓存数据源（经 Godot 导出，带 rating）。

为什么不直接解析二进制：runs_steam.cache 是 Godot store_var 格式，
手工解析容易错位（试过，rating 位置猜错过）。改用 Godot 自己的
get_var() 导出 JSON，再由 Python 入库，稳定可靠。
"""
from __future__ import annotations

import hashlib
import json
import os
import subprocess
import sys
from pathlib import Path
from typing import Any, Callable

ROOT = Path(__file__).resolve().parents[4]
GODOT = ROOT / "output" / "godot36" / "Godot_v3.6-stable_win64.exe"
PROJECT = ROOT / "gd_core_test"
DUMP_SCRIPT = "dump_run_cache.gd"
EXPORT_DIR = ROOT / "output" / "cache_export"


def cache_path() -> Path | None:
    appdata = os.environ.get("APPDATA")
    if not appdata:
        return None
    p = Path(appdata) / "Godot" / "app_userdata" / "Backpack Battles" / "runs_steam.cache"
    return p if p.exists() else None


def cache_sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def export_cache(cache: Path | None = None, timeout: int = 300) -> dict[str, Any]:
    """用 Godot 把缓存导出成结构化 JSON，返回 {"cache_sha", "runs": [...]}。"""
    cache = cache or cache_path()
    if cache is None or not Path(cache).exists():
        raise FileNotFoundError("找不到 runs_steam.cache")
    if not GODOT.exists():
        raise FileNotFoundError(f"找不到 Godot：{GODOT}")

    EXPORT_DIR.mkdir(parents=True, exist_ok=True)
    out_json = EXPORT_DIR / "runs_full.json"
    if out_json.exists():
        out_json.unlink()

    sys.path.insert(0, str(ROOT / "tools"))
    import godot_headless as gh

    env = gh.env()
    env["BPB_CACHE"] = str(cache)
    env["BPB_OUT"] = str(out_json)

    log_path = EXPORT_DIR / "godot_dump.log"
    with log_path.open("wb") as fh:
        proc = subprocess.run(
            [str(GODOT), "--no-window", "--audio-driver", "Dummy",
             "--path", str(PROJECT), "--script", DUMP_SCRIPT],
            cwd=str(PROJECT), env=env, stdout=fh, stderr=subprocess.STDOUT,
            timeout=timeout,
        )
    if proc.returncode != 0 or not out_json.exists():
        tail = ""
        try:
            tail = log_path.read_text(encoding="utf-8", errors="replace")[-800:]
        except OSError:
            pass
        raise RuntimeError(f"Godot 导出失败 rc={proc.returncode}：{tail}")

    payload = json.loads(out_json.read_text(encoding="utf-8"))
    payload["cache_sha"] = cache_sha(cache)
    payload["cache_path"] = str(cache)
    return payload


def steam_run_cache() -> Callable[[], bytes]:
    """采集器数据源：导出缓存并返回 JSON 字节（含 rating）。"""

    def fetch() -> bytes:
        payload = export_cache()
        records = payload.get("runs") or []
        return json.dumps(
            {"cache_sha": payload["cache_sha"], "runs": records},
            ensure_ascii=False,
        ).encode("utf-8")

    return fetch
