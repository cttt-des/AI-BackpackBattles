# -*- coding: utf-8 -*-
"""`load_for` 等价性校验：改 `tools/gd_to_py.py` 的档二导入逻辑后必跑。

用法：
    python -X utf8 tools/check_loadfor.py
    python -X utf8 tools/check_loadfor.py --lineup lineups/xxx_player.json

为什么需要它：`load_for` 决定「哪些 items 模块被真正导入」。漏导不会报错——
`_R.C(name)` 会静默回落到占位类，确定性闸门才在很久之后红。所以每次改它都必须
证明「want 集合与改前逐项相等」，而不是等闸门兜。

做法：在进程内用 `_ITEM_PARENTS` + `_ITEM_ORDER` 重新实现一份「参考实现」
（= 索引化之前的线性扫描语义），与现行 `_ITEM_STEM` 查表结果对拍：
  1) 全部 505 个 stem × 3 种写法（裸 stem / 带 .gd / 带路径）
  2) 真实阵容（默认 R19 双方）
  3) 边界输入：[] / None / 非物品名 / gd_core 侧名字

判据：TOTAL FAILS = 0，且报告每类覆盖数量。
"""
import argparse
import json
import os
import sys

_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

from gd_core_py import _bootstrap as B  # noqa: E402

PARENTS = B._ITEM_PARENTS
ORDER = B._ITEM_ORDER
STEM = B._ITEM_STEM


def reference_want(scripts):
    """索引化之前的语义：对每个脚本线性扫 ORDER 全表，命中即展开父闭包。"""
    want = set()
    for s in scripts or ():
        stem = str(s).rsplit("/", 1)[-1]
        if stem.endswith(".gd"):
            stem = stem[:-3]
        for rel in ORDER:
            if rel.rsplit("/", 1)[-1][:-3] == stem:
                stack = [rel]
                while stack:
                    r0 = stack.pop()
                    if r0 not in want:
                        want.add(r0)
                        stack.extend(PARENTS.get(r0, ()))
                break
    return want


def current_want(scripts):
    """现行实现（与生成器发射的 load_for 同逻辑）。"""
    want = set()
    for s in scripts or ():
        stem = str(s).rsplit("/", 1)[-1]
        if stem.endswith(".gd"):
            stem = stem[:-3]
        rel = STEM.get(stem)
        if rel is None:
            continue
        stack = [rel]
        while stack:
            r0 = stack.pop()
            if r0 not in want:
                want.add(r0)
                stack.extend(PARENTS.get(r0, ()))
    return want


def _lineup_scripts(path):
    d = json.load(open(path, encoding="utf-8"))
    out = []
    for it in (d.get("backpack") or {}).get("items", []) or []:
        out.append(it.get("id", ""))
        for g in it.get("gems", []) or []:
            out.append(g.get("id", ""))
    return [s.replace(" ", "") for s in out]


def main() -> int:
    ap = argparse.ArgumentParser(description="load_for 等价性校验")
    ap.add_argument("--lineup", action="append", default=[],
                    help="额外阵容 JSON，可多次给")
    args = ap.parse_args()

    fails = 0
    checked = 0

    stems = 0
    for rel in ORDER:
        stem = rel.rsplit("/", 1)[-1][:-3]
        for variant in (stem, stem + ".gd", "scripts/" + stem + ".gd"):
            checked += 1
            if reference_want([variant]) != current_want([variant]):
                fails += 1
                print("MISMATCH stem", variant)
        stems += 1

    lineups = args.lineup or [
        os.path.join(_ROOT, "lineups", "truth_20261001_220653_R19_player.json"),
        os.path.join(_ROOT, "lineups", "truth_20261001_220653_R19_opponent.json"),
    ]
    for p in lineups:
        if not os.path.exists(p):
            print("SKIP 缺失阵容", p)
            continue
        scripts = _lineup_scripts(p)
        a, b = reference_want(scripts), current_want(scripts)
        checked += 1
        ok = a == b
        fails += 0 if ok else 1
        print("lineup %-52s scripts=%3d want=%2d %s"
              % (os.path.basename(p), len(scripts), len(a), "OK" if ok else "MISMATCH"))

    tricky = [[], None, ["NotARealItem"], ["CoreItem"], ["Item.gd"], ["Ghost"]]
    for t in tricky:
        checked += 1
        if reference_want(t) != current_want(t):
            fails += 1
            print("MISMATCH tricky", t)

    print()
    print("覆盖：%d 个 items stem，%d 项检查" % (stems, checked))
    print("TOTAL FAILS = %d" % fails)
    return 1 if fails else 0


if __name__ == "__main__":
    raise SystemExit(main())
