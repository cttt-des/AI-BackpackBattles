#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
aligned_set.py — 已对齐场集合快照与退步检测

修复循环的单调性闸门（docs/alignment_fix_workflow.md：验收口径=对齐场数递增且
已对齐场不退步）。旧循环只看 aligned 总数、退步无人发现——本工具把"已对齐场
集合"落盘，修复后比对：

  python -X utf8 tools/aligned_set.py snapshot -o output/oracle/aligned_sets/round3.txt
      # 从 output/oracle/alignment.json 取 match=="三方一致" 的 caseId 写快照
  python -X utf8 tools/aligned_set.py check -b output/oracle/aligned_sets/round3.txt
      # 当前 alignment.json 与基线比对：新增=+，退步=-
      # 退出码：0 无退步（或有新增）；1 存在退步（列出明细）；2 用法/文件错误

注意：check 不改写基线——回滚与否由调用方（修复循环）决定。
"""
from __future__ import annotations

import argparse
import io
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ALIGNMENT_JSON = os.path.join(ROOT, "output", "oracle", "alignment.json")


def current_aligned(path: str = ALIGNMENT_JSON) -> frozenset:
    data = json.load(io.open(path, encoding="utf-8"))
    return frozenset(r["caseId"] for r in data.get("perCase") or []
                     if r.get("match") == "三方一致")


def main() -> int:
    ap = argparse.ArgumentParser(description="aligned 场集合快照/退步检测")
    sub = ap.add_subparsers(dest="cmd", required=True)
    snap = sub.add_parser("snapshot", help="把当前已对齐场写入快照文件")
    snap.add_argument("-o", "--out", required=True, help="快照输出路径")
    chk = sub.add_parser("check", help="当前集合与基线快照比对")
    chk.add_argument("-b", "--baseline", required=True, help="基线快照路径")

    args = ap.parse_args()
    if not os.path.exists(ALIGNMENT_JSON):
        print("找不到 %s（先跑 tools/verify_oracle.py）" % ALIGNMENT_JSON,
              file=sys.stderr)
        return 2
    try:
        cur = current_aligned()
    except Exception as exc:  # noqa: BLE001 —— 解析失败如实报错
        print("alignment.json 解析失败：%s: %s" % (type(exc).__name__, exc),
              file=sys.stderr)
        return 2

    if args.cmd == "snapshot":
        os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)
        with io.open(args.out, "w", encoding="utf-8", newline="\n") as fh:
            fh.write("\n".join(sorted(cur)) + ("\n" if cur else ""))
        print("[snapshot] %d 场 → %s" % (len(cur), args.out))
        return 0

    if not os.path.exists(args.baseline):
        print("基线快照不存在：%s" % args.baseline, file=sys.stderr)
        return 2
    base = frozenset(ln.strip() for ln in
                     io.open(args.baseline, encoding="utf-8").read().splitlines()
                     if ln.strip())
    added = sorted(cur - base)
    removed = sorted(base - cur)
    print("[check] 基线 %d 场 → 当前 %d 场：新增 %d，退步 %d"
          % (len(base), len(cur), len(added), len(removed)))
    if added:
        print("  新增：%s" % ",".join(added))
    if removed:
        print("  退步：%s" % ",".join(removed))
    if removed:
        print("存在退步场——按不变式须回滚本轮改动（git apply -R output/_round_patches/roundN.patch）",
              file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
