# -*- coding: utf-8 -*-
"""ast_diff.py — 生成器机械变换的 AST 等价差分（docs/性能优化执行路径.md S0-H2/H3 骨架）

用途：gd_to_py.py 生成策略变更（S3 的 C1/C4/C5 等机械变换）后，把**新旧产物**
逐模块做 AST 直方图差分，产出「每模块每个 AST 节点类型的数量变化」机器可读清单；
再按 H3 白名单（--expect）判定：出现的节点类型变化是否全部属于该变换的预期面。
「不改语义」从人手核对降级为「生成后自动验证」——全量过闸只需兜底异常。

用法：
    # 1) 变换前先留底当前产物
    python tools/ast_diff.py snapshot --out output/perf/ast_snapshot_c4.json

    # 2) 生成器改动并重转写后对拍
    python tools/ast_diff.py diff --snapshot output/perf/ast_snapshot_c4.json \
        --expect output/perf/expect_c4.json [--out report.json]

    # 或直接对拍两棵产物树：
    python tools/ast_diff.py diff --old gd_core_py_bak --new gd_core_py \
        --expect output/perf/expect_c4.json

退出码：0=全部模块的 AST 变化落在白名单内；1=有越界变化（列出模块与节点类型）；
2=参数/路径错误。

白名单（--expect）格式（JSON）：
    {"_rule": "C4 _R.C 静态绑定",
     "allowed": {"Call": [1, 1],        # [旧最少次数, 新最多次数] 形式的区间断言过重，
                 "Attribute": null},     # 骨架版先只支持「允许出现的节点类型集合」，
     "allow_any": ["Name", "Constant"]}  # null=该类型变化量不限
骨架版语义：模块差分中出现的每个节点类型，要么在 `allowed`（变化量不限），
要么在 `allow_any`（同上，别名用法）；不在其内 → RED。区间断言留给后续按需加。

★ 原则：本工具只**报告**与**闸门判定**，不修任何文件；差分基准永远取
  「生成器变更前的真实产物快照」，不取记忆。
"""
from __future__ import annotations

import argparse
import ast
import json
import os
import sys
from collections import Counter

PY_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def _histogram(src: str) -> Counter:
    tree = ast.parse(src)
    c: Counter = Counter()
    for node in ast.walk(tree):
        c[type(node).__name__] += 1
    return c


def _collect(root: str) -> dict:
    """root 下全部 .py → {相对路径: 直方图}。"""
    out = {}
    for dirpath, _dirnames, filenames in os.walk(root):
        if "__pycache__" in dirpath:
            continue
        for fn in filenames:
            if not fn.endswith(".py"):
                continue
            full = os.path.join(dirpath, fn)
            rel = os.path.relpath(full, root).replace("\\", "/")
            with open(full, encoding="utf-8") as f:
                try:
                    out[rel] = _histogram(f.read())
                except SyntaxError as e:
                    out[rel] = {"<SYNTAX_ERROR>": 1}
                    print(f"WARN: {rel} 解析失败: {e}", file=sys.stderr)
    return out


def cmd_snapshot(args):
    old = os.path.join(PY_ROOT, args.root)
    data = {rel: dict(h) for rel, h in _collect(old).items()}
    payload = {"root": args.root, "modules": len(data), "histograms": data}
    with open(args.out, "w", encoding="utf-8") as f:
        json.dump(payload, f, ensure_ascii=False)
        f.write("\n")
    print(f"snapshot: {len(data)} 模块 → {args.out}")
    return 0


def cmd_diff(args):
    if args.snapshot:
        with open(args.snapshot, encoding="utf-8") as f:
            snap = json.load(f)
        old_map = {k: Counter(v) for k, v in snap["histograms"].items()}
        # ★ 新树默认 = 快照时的 root（不是仓库根！否则 gui/tools 全被卷进来）
        snap_root = snap.get("root") or "gd_core_py"
    elif args.old:
        old_map = _collect(os.path.join(PY_ROOT, args.old) if not os.path.isabs(args.old) else args.old)
        snap_root = args.old
    else:
        print("需要 --snapshot 或 --old", file=sys.stderr)
        return 2
    new_tree = args.new if args.new is not None else snap_root
    new_root = new_tree if os.path.isabs(new_tree) else os.path.join(PY_ROOT, new_tree)

    new_map = _collect(new_root)
    expect = None
    if args.expect:
        with open(args.expect, encoding="utf-8") as f:
            expect = json.load(f)
        allowed = set(expect.get("allowed") or {}) | set(expect.get("allow_any") or [])

    changes = {}
    red = []
    for rel in sorted(set(old_map) | set(new_map)):
        oh, nh = old_map.get(rel, Counter()), new_map.get(rel, Counter())
        delta = {}
        for k in set(oh) | set(nh):
            d = nh.get(k, 0) - oh.get(k, 0)
            if d:
                delta[k] = d
        if not delta:
            continue
        changes[rel] = delta
        if expect is not None:
            bad = [k for k in delta if k not in allowed]
            if bad or "<SYNTAX_ERROR>" in delta:
                red.append({"module": rel, "unexpected_node_types": bad,
                            "delta": delta})
    report = {
        "changed_modules": len(changes),
        "total_modules": len(new_map),
        "rule": (expect or {}).get("_rule"),
        "red": red,
        "pass": (not red) if expect is not None else None,
        "changes": changes,
    }
    if args.out:
        with open(args.out, "w", encoding="utf-8") as f:
            json.dump(report, f, ensure_ascii=False, indent=1)
            f.write("\n")
    top = sorted(changes.items(), key=lambda kv: -sum(abs(v) for v in kv[1].values()))[:8]
    for rel, delta in top:
        kinds = ", ".join(f"{k}{v:+d}" for k, v in
                          sorted(delta.items(), key=lambda kv: -abs(kv[1]))[:5])
        print(f"  {rel}: {kinds}")
    if expect is None:
        print(f"diff: {len(changes)}/{len(new_map)} 模块有 AST 变化（未带 --expect，仅报告不判定）")
        return 0
    if red:
        print(f"AST-DIFF RED：{len(red)} 模块出现白名单外节点类型："
              + ", ".join(r["module"] for r in red[:5]))
        return 1
    print(f"AST-DIFF PASS：{len(changes)} 模块变化全部落在白名单内"
          f"（规则：{expect.get('_rule')}）")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description="产物 AST 等价差分（H2/H3）")
    sub = ap.add_subparsers(dest="cmd", required=True)

    p1 = sub.add_parser("snapshot", help="留底当前产物 AST 直方图")
    p1.add_argument("--root", default="gd_core_py", help="产物树（默认 gd_core_py）")
    p1.add_argument("--out", required=True)

    p2 = sub.add_parser("diff", help="对拍快照/旧树 vs 当前树，按白名单判定")
    p2.add_argument("--snapshot", help="ast_diff.py snapshot 的产物")
    p2.add_argument("--old", help="或直接指定旧树目录")
    p2.add_argument("--new", default=None, help="新树（默认当前 gd_core_py）")
    p2.add_argument("--expect", help="H3 白名单 JSON")
    p2.add_argument("--out", help="差分报告 JSON")

    args = ap.parse_args()
    if args.cmd == "snapshot":
        return cmd_snapshot(args)
    return cmd_diff(args)


if __name__ == "__main__":
    raise SystemExit(main())
