"""从 staging.sqlite 导出训练用数据集。

产物：
- runs.jsonl     每场一行：{run_id, source, rounds:[{round, health, stamina, items:[...]}]}
- items.jsonl    每条物品一行：{run_id, round, name, x, y, face, gems}
- stats.json     物品流行度（按轮次）与覆盖度
"""
from __future__ import annotations

import argparse
import json
import sqlite3
from collections import Counter, defaultdict
from pathlib import Path


def export(conn: sqlite3.Connection, out_dir: Path, *, min_rounds: int = 6) -> dict:
    out_dir.mkdir(parents=True, exist_ok=True)
    runs_path = out_dir / "runs.jsonl"
    items_path = out_dir / "items.jsonl"
    rounds_by_run: dict[str, list[dict]] = defaultdict(list)
    run_meta: dict[str, dict] = {}

    for run_id, source, captured, rounds, meta in conn.execute(
        "SELECT run_id, source, captured_at, rounds, meta_json FROM runs"
    ):
        if rounds < min_rounds:
            continue
        run_meta[run_id] = {"run_id": run_id, "source": source, "captured_at": captured,
                            "rounds": rounds, "meta": json.loads(meta or "{}")}

    for run_id, round_no, health, stamina, items_json in conn.execute(
        "SELECT run_id, round_no, health, stamina, items_json FROM rounds ORDER BY run_id, round_no"
    ):
        if run_id not in run_meta:
            continue
        rounds_by_run[run_id].append({
            "round": round_no, "health": health, "stamina": stamina,
            "items": json.loads(items_json),
        })

    item_counts: dict[int, Counter] = defaultdict(Counter)
    distinct = set()
    n_runs = 0
    with runs_path.open("w", encoding="utf-8") as f:
        for run_id, rounds in rounds_by_run.items():
            record = {**run_meta[run_id], "rounds": rounds}
            f.write(json.dumps(record, ensure_ascii=False) + "\n")
            n_runs += 1
            for r in rounds:
                for item in r["items"]:
                    item_counts[r["round"]][item["id"]] += 1
                    distinct.add(item["id"])

    n_items = 0
    with items_path.open("w", encoding="utf-8") as f:
        for run_id, round_no, slot, name, x, y, face, gid, gems in conn.execute(
            "SELECT run_id, round_no, slot, name, x, y, face, gid, gems_json FROM items ORDER BY run_id, round_no, slot"
        ):
            if run_id not in run_meta:
                continue
            f.write(json.dumps({"run_id": run_id, "round": round_no, "slot": slot, "name": name,
                                "x": x, "y": y, "face": face, "gid": gid,
                                "gems": json.loads(gems or "[]")}, ensure_ascii=False) + "\n")
            n_items += 1

    stats = {
        "runs": n_runs,
        "item_rows": n_items,
        "distinct_items": len(distinct),
        "top_items_by_round": {
            str(round_no): [{"name": n, "count": c} for n, c in counter.most_common(10)]
            for round_no, counter in sorted(item_counts.items())
        },
    }
    (out_dir / "stats.json").write_text(json.dumps(stats, ensure_ascii=False, indent=2), encoding="utf-8")
    return {"runs": n_runs, "item_rows": n_items, "distinct_items": len(distinct), "out": str(out_dir)}


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="导出训练数据集")
    root = Path(__file__).resolve().parents[4]
    parser.add_argument("--database", type=Path, default=root / "database" / "staging.sqlite")
    parser.add_argument("--out", type=Path, default=root / "database" / "dataset")
    parser.add_argument("--min-rounds", type=int, default=6)
    args = parser.parse_args(argv)
    conn = sqlite3.connect(args.database)
    result = export(conn, args.out, min_rounds=args.min_rounds)
    print(json.dumps(result, ensure_ascii=False))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
