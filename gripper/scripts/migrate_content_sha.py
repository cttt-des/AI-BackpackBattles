"""迁移：为 runs 表补 content_sha 并清理重复内容（幂等）。

用法：python gripper/scripts/migrate_content_sha.py [--database PATH] [--dry-run]
"""
from __future__ import annotations

import argparse
import json
import sqlite3
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "gripper" / "src"))

from bpb_research.collect.store import _content_sha  # noqa: E402


def migrate(db: Path, *, dry_run: bool = False) -> dict:
    conn = sqlite3.connect(db)
    cols = [r[1] for r in conn.execute("PRAGMA table_info(runs)")]
    added = "content_sha" not in cols
    if added and not dry_run:
        with conn:
            conn.execute("ALTER TABLE runs ADD COLUMN content_sha TEXT")

    runs = conn.execute("SELECT run_id FROM runs").fetchall()
    filled = 0
    with conn if not dry_run else _nullctx():
        for (run_id,) in runs:
            rows = conn.execute(
                "SELECT health, stamina, items_json FROM rounds WHERE run_id=? ORDER BY round_no",
                (run_id,),
            ).fetchall()
            rounds = [{"health": h, "stamina": s, "items": json.loads(it)} for h, s, it in rows]
            sha = _content_sha(rounds) if rounds else None
            if sha:
                conn.execute("UPDATE runs SET content_sha=? WHERE run_id=?", (sha, run_id))
                filled += 1

    dupes = conn.execute(
        "SELECT COUNT(*) FROM runs WHERE rowid NOT IN (SELECT MIN(rowid) FROM runs GROUP BY content_sha)"
    ).fetchone()[0]
    if not dry_run and dupes:
        with conn:
            conn.execute("DELETE FROM runs WHERE rowid NOT IN (SELECT MIN(rowid) FROM runs GROUP BY content_sha)")
            conn.execute("DELETE FROM rounds WHERE run_id NOT IN (SELECT run_id FROM runs)")
            conn.execute("DELETE FROM items WHERE run_id NOT IN (SELECT run_id FROM runs)")

    result = {
        "database": str(db),
        "column_added": added,
        "runs_total": len(runs),
        "filled": filled,
        "duplicates_found": dupes,
        "dry_run": dry_run,
        "remaining_runs": conn.execute("SELECT COUNT(*) FROM runs").fetchone()[0],
    }
    return result


class _nullctx:
    def __enter__(self):
        return None

    def __exit__(self, *exc):
        return False


def main() -> int:
    parser = argparse.ArgumentParser(description="给 runs 补 content_sha 并去重")
    parser.add_argument("--database", type=Path, default=ROOT / "database" / "staging.sqlite")
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args()
    print(json.dumps(migrate(args.database, dry_run=args.dry_run), ensure_ascii=False))
    return 0


if __name__ == "__main__":
    sys.exit(main())
