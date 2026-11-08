"""一键自检：验证解码器、缓存、库、去重、状态机是否都在正常状态。

用法：python -m bpb_research.collect.selftest
"""
from __future__ import annotations

import json
import sqlite3
import sys
from pathlib import Path

from bpb_research.collect import store
from bpb_research.steam.run_cache import cache_signature, parse_runs


def main() -> int:
    root = Path(__file__).resolve().parents[4]
    checks: list[dict] = []

    def check(name: str, ok: bool, detail: object = None) -> None:
        checks.append({"name": name, "ok": bool(ok), "detail": detail})

    sig = cache_signature()
    check("Steam 缓存存在", sig.get("available") is True, sig.get("bytes"))

    runs = []
    try:
        runs = parse_runs()
        check("缓存可切分为 run", len(runs) > 0, {"runs": len(runs),
              "full18": sum(1 for r in runs if r.round_count >= 18)})
    except Exception as error:
        check("缓存可切分为 run", False, str(error))

    db = root / "database" / "staging.sqlite"
    if db.exists():
        conn = sqlite3.connect(db)
        summary = store.summary(conn)
        check("库内数据非空", summary["runs"] > 0, summary)
        # 去重校验：content_sha 不应有重复
        dup = conn.execute("""
            SELECT COUNT(*) FROM (SELECT content_sha FROM runs
            WHERE content_sha IS NOT NULL GROUP BY content_sha HAVING COUNT(*) > 1)
        """).fetchone()[0]
        check("内容指纹无重复", dup == 0, {"duplicate_groups": dup})
        # 血量单调性
        bad = conn.execute("""
            SELECT COUNT(*) FROM (
              SELECT health, LAG(health) OVER (PARTITION BY run_id ORDER BY round_no) prev
              FROM rounds
            ) WHERE prev IS NOT NULL AND health < prev
        """).fetchone()[0]
        check("轮次血量单调", bad == 0, {"violations": bad})
        # 物品覆盖
        distinct = summary["distinct_items"]
        check("物品覆盖完整", distinct >= 500, {"distinct": distinct})
    else:
        check("库存在", False, str(db))

    dataset = root / "database" / "dataset"
    check("数据集已导出", (dataset / "runs.jsonl").exists() and (dataset / "items.jsonl").exists(),
          {f.name: f.stat().st_size for f in dataset.glob("*.jsonl")} if dataset.exists() else None)

    failed = [c for c in checks if not c["ok"]]
    report = {"ok": not failed, "checks": checks}
    print(json.dumps(report, ensure_ascii=False, indent=2))
    return 0 if not failed else 1


if __name__ == "__main__":
    sys.exit(main())
