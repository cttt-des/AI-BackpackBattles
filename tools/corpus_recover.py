# -*- coding: utf-8 -*-
"""corpus_recover.py — 补收尾被强杀中断的对局记录

进程被 os._exit / 任务管理器 / 断电中断时，raw/ 里最后一回合还是明文、
meta.end_reason 是 null。数据本身没丢，只是缺"封印"。本工具做三件事：

1. 归档残留明文分片（lzma，压缩后校验字节数）；
2. 写 meta：end_reason="crash"、incomplete=true、sealed_after_crash=true；
3. 打印该局能折叠出多少样本，确认数据可用。

用法::

    python -X utf8 tools/corpus_recover.py output/records
    python -X utf8 tools/corpus_recover.py output/records/<run_id> --dry-run
"""
from __future__ import annotations

import argparse
import json
import os
import sys
from pathlib import Path
from typing import List, Optional

_REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _REPO not in sys.path:
    sys.path.insert(0, _REPO)

from core.store import load_meta, seal_run  # noqa: E402
from tools.corpus_fold import fold_run  # noqa: E402


def _inspect(run_dir: Path) -> dict:
    meta = load_meta(run_dir)
    plain = sorted(p.name for p in (run_dir / "raw").glob("R*.jsonl"))
    packed = sorted(p.name for p in (run_dir / "raw").glob("R*.jsonl.xz"))
    try:
        decisions, lineups, stats, _t = fold_run(run_dir)
        fold = {"decisions": len(decisions), "lineups": len(lineups),
                "dropped_zero_net": stats.dropped_zero_segments,
                "unknown": stats.unknown_changes}
    except Exception as e:  # noqa: BLE001
        fold = {"error": str(e)}
    return {
        "run_id": meta.get("run_id") or run_dir.name,
        "end_reason": meta.get("end_reason"),
        "incomplete": meta.get("incomplete"),
        "plain_shards": plain,
        "packed_shards": packed,
        "fold": fold,
    }


def main(argv: Optional[List[str]] = None) -> int:
    ap = argparse.ArgumentParser(description="补收尾被中断的对局记录")
    ap.add_argument("path", help="对局目录，或包含多个对局目录的父目录")
    ap.add_argument("--dry-run", action="store_true", help="只报告，不修改")
    args = ap.parse_args(argv)

    root = Path(args.path)
    if not root.exists():
        print(f"路径不存在: {root}")
        return 2
    runs = ([root] if (root / "raw").exists()
            else sorted(p for p in root.iterdir()
                        if p.is_dir() and (p / "raw").exists()))
    if not runs:
        print(f"未找到对局目录: {root}")
        return 2

    failed = 0
    for run in runs:
        before = _inspect(run)
        print(f"== {before['run_id']} ==")
        print(f"  end_reason={before['end_reason']}  incomplete={before['incomplete']}")
        print(f"  明文分片 {len(before['plain_shards'])} 个，已归档 "
              f"{len(before['packed_shards'])} 个")
        if before["plain_shards"]:
            print(f"  待归档: {', '.join(before['plain_shards'])}")

        if before["end_reason"] is None and not args.dry_run:
            meta = seal_run(run, reason="crash")
            if meta is None:
                print("  [FAIL] 补收尾失败")
                failed += 1
            else:
                print("  [OK] 已补收尾（归档明文 + 写 end_reason=crash）")
        elif before["end_reason"] is None:
            print("  [DRY] 将补收尾")

        after = _inspect(run)
        fold = after["fold"]
        if "error" in fold:
            print(f"  折叠: 失败（{fold['error']}）")
            failed += 1
        else:
            print(f"  可折叠出: 决策 {fold['decisions']} 条 / 摆盘 "
                  f"{fold['lineups']} 条（丢弃净零段 {fold['dropped_zero_net']}，"
                  f"未归类 {fold['unknown']}）")
        print(json.dumps(after, ensure_ascii=False))

    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
