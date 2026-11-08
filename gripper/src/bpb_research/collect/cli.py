"""定时采集入口：采集 → 解码 → 入库。

数据源：
  steam-cache   Steam 排行榜缓存（只读 AppData，需游戏曾拉取过排行榜）
  bpb2-matches  公开站逐场对局（HTTP）
  bpb2-builds   公开站社区摆盘（HTTP）

用法：
  python -m bpb_research.collect.cli --source steam-cache --once
  python -m bpb_research.collect.cli --source bpb2-matches --interval 20
  python -m bpb_research.collect.cli --status
"""
from __future__ import annotations

import argparse
import json
import sys
import time
from pathlib import Path

from bpb_research.collect import store
from bpb_research.collect.collector import (
    Collector,
    compress_old_batches,
    prune_batches,
    verified_batches,
)
from bpb_research.collect.sources import bpb2_builds, bpb2_matches, local_file
from bpb_research.steam.cache_source import steam_run_cache  # Godot 导出（含 rating）
from bpb_research.steam.leaderboard import steam_batch_available
from bpb_research.steam.run_cache import cache_signature

SOURCES = {
    "steam-cache": lambda a: steam_run_cache(),
    "bpb2-builds": lambda a: bpb2_builds(page_size=a.page_size, max_pages=a.max_pages),
    "bpb2-matches": lambda a: bpb2_matches(page_size=a.page_size, max_pages=a.max_pages),
}


def _default_database_dir() -> Path:
    """默认落在仓库根 database/，不受调用时工作目录影响。"""
    root = Path(__file__).resolve().parents[4]
    return root / "database"


def _ingest_batches(database_dir: Path, conn) -> dict[str, int]:
    totals = {"records": 0, "runs_new": 0, "runs_skipped": 0, "rounds": 0, "items": 0, "errors": 0}
    for batch in verified_batches(database_dir):
        payload_path = batch / "payload.json"
        if not payload_path.exists():
            gz = batch / "payload.json.gz"
            if not gz.exists():
                continue
            import gzip
            payload = json.loads(gzip.decompress(gz.read_bytes()).decode("utf-8"))
        else:
            payload = json.loads(payload_path.read_text(encoding="utf-8"))
        meta = json.loads((batch / "manifest.json").read_text(encoding="utf-8"))
        source = str(meta.get("source") or "unknown")
        if source == "steam-cache" and isinstance(payload, dict) and "runs" in payload:
            # 新格式：Godot 导出的结构化记录（含 rating / arr6 逐轮串）
            sha = payload.get("cache_sha", "")
            result = store.ingest_export(conn, payload["runs"], source=source, cache_sha=sha)
            for key in totals:
                totals[key] += result.get(key, 0)
            continue
        records = payload if isinstance(payload, list) else [payload]
        result = store.ingest_records(conn, records, source=source)
        for key in totals:
            totals[key] += result.get(key, 0)
    return totals


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="按冷却定时采集对手/对局数据并入库")
    parser.add_argument("--database-dir", type=Path, default=_default_database_dir())
    parser.add_argument("--source", choices=sorted(SOURCES) + ["file"], default="steam-cache")
    parser.add_argument("--file", type=Path)
    parser.add_argument("--interval", type=int, default=20, help="分钟")
    parser.add_argument("--once", action="store_true")
    parser.add_argument("--force", action="store_true")
    parser.add_argument("--no-ingest", action="store_true")
    parser.add_argument("--min-rounds", type=int, default=6, help="（已废弃，保留兼容）")
    parser.add_argument("--keep-batches", type=int, default=3, help="保留最近几个已完成批次")
    parser.add_argument("--page-size", type=int, default=20)
    parser.add_argument("--max-pages", type=int)
    parser.add_argument("--log-format", choices=("summary", "json"), default="summary")
    parser.add_argument("--status", action="store_true")
    args = parser.parse_args(argv)

    if args.status:
        conn = store.connect(args.database_dir / "staging.sqlite")
        print(json.dumps({
            "steam": steam_batch_available(),
            "cache": cache_signature(),
            "db": store.summary(conn),
        }, ensure_ascii=False, indent=2, default=str))
        return 0

    source = local_file(args.file) if args.source == "file" else SOURCES[args.source](args)
    from bpb_research.collect import collector as collector_module

    collector_module.SUCCESS_DELAY = max(args.interval * 60, 300)
    collector_module.FAILURE_DELAY = min(collector_module.SUCCESS_DELAY, 600)
    collector = Collector(args.database_dir, source, source_name=args.source)
    conn = store.connect(args.database_dir / "staging.sqlite")

    round_no = 0
    while True:
        round_no += 1
        result = collector.run_once(force=args.force and round_no == 1)
        payload: dict = {"round": round_no, **result}
        if not args.no_ingest and result["status"] == "complete":
            payload["ingest"] = _ingest_batches(args.database_dir, conn)
            payload["db"] = store.summary(conn)
            payload["pruned"] = prune_batches(args.database_dir, keep=args.keep_batches)
            payload["compressed"] = compress_old_batches(args.database_dir, keep_latest=1)
        if args.log_format == "json":
            print(json.dumps(payload, ensure_ascii=False), flush=True)
        else:
            ing = payload.get("ingest") or {}
            print(f"第 {round_no} 轮 | {result['status']} | 新增 {ing.get('runs_new', 0)} 场 | "
                  f"库内 {(payload.get('db') or {}).get('runs', '?')} 场", flush=True)
        if args.once:
            break
        wait = max(0, collector.cooldown_remaining())
        if wait > 0:
            time.sleep(wait)
    return 0


if __name__ == "__main__":
    sys.exit(main())
