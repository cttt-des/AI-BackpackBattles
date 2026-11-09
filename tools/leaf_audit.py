# -*- coding: utf-8 -*-
"""leaf_audit.py — S2-B2 分层导入的设计数据：extends 图 → core/leaf 拆分审计。

gd_core_py/_bootstrap.py 是生成物（勿手改），B2 的 load_core()/load_for() 必须
由 tools/gd_to_py.py 的 emit_bootstrap 产出（下个 session 带闸落地）。本工具先行
产出那份改动需要的**机械判据**：

  1. 扫全部生成模块的 `class X(_R.C("基类"))` 与 `class X(基类)`（含多基），
     建 extends 图（名 → 注册别名按 stem 约定）；
  2. core 集 = `gd_core/` 全部模块 ∪ 「被任何模块继承」的 gd_core_items 模块
     的传递闭包；leaf 集 = 其余 gd_core_items 模块；
  3. 判据 A（分层可行性）：leaf 模块的直接基类必须全部落在 core 集——
     否则 `load_for()` 只导入该 leaf 会拿到占位基类（静默错，见 _registry 注）；
  4. 判据 B（名称唯一性）：注册别名（res_path/class_name/stem）与模块一一对应，
     无跨树同名冲突需要仲裁者在场（reg() 的 np24-P3-7 仲裁依赖 gd_core 树先注册）。

用法：
    python -X utf8 tools/leaf_audit.py [--json output/perf/leaf_audit.json]

退出码：0=判据 A/B 全过（B2 可安全分层）；1=有违例（列出，B2 不可盲上）。
"""
from __future__ import annotations

import argparse
import ast
import json
import os
import re
import sys
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PKG = os.path.join(ROOT, "gd_core_py")

# class X(_R.C("Y")) / class X(Y, _R.C("Z")) —— 生成器改写后的基类引用
_RE_R_C = re.compile(r"_R\.C\(\s*[\"']([^\"']+)[\"']\s*\)")


def _mod_of(rel):
    return rel[:-3].replace("\\", "/")


def _stem(name):
    s = str(name).rsplit("/", 1)[-1]
    if s.endswith(".gd"):
        s = s[:-3]
    elif s.endswith(".py"):
        s = s[:-3]
    return s


def main() -> int:
    ap = argparse.ArgumentParser(description="extends 图审计（S2-B2 设计数据）")
    ap.add_argument("--json", default=os.path.join(ROOT, "output", "perf",
                                                   "leaf_audit.json"))
    args = ap.parse_args()

    mods = {}          # module_path(rel) -> [基类名...]
    tree = {}          # module_path -> 'core' | 'items'
    rels = []
    for dirpath, dirnames, filenames in os.walk(PKG):
        dirnames[:] = [d for d in dirnames if d != "__pycache__"]
        for fn in filenames:
            if not fn.endswith(".py"):
                continue
            full = os.path.join(dirpath, fn)
            rel = os.path.relpath(full, PKG).replace("\\", "/")
            if rel.startswith("_"):
                continue                      # _rt/_registry/_bootstrap/_colors
            rels.append(rel)
            tree[rel] = "core" if rel.startswith("gd_core/") else "items"

    # 名 → 定义模块（stem 约定）；先建好，裸名基类过滤依赖它
    by_stem = defaultdict(list)
    for rel in rels:
        by_stem[_stem(rel)].append(rel)

    for rel in rels:
        full = os.path.join(PKG, rel)
        with open(full, encoding="utf-8") as f:
            src = f.read()
            bases = []
            for node in ast.walk(ast.parse(src)):
                if isinstance(node, ast.ClassDef):
                    for kw in node.bases:
                        src_code = ast.unparse(kw)
                        bases += _RE_R_C.findall(src_code)
                        # 裸名基类（如 class CoreItem(GodotObject)）非跨文件；
                        # 仅计入「确实是某模块 stem」的裸名（其余为字符串字面量
                        # 内的词或本文件助手类，过滤之——审计宁缺勿滥）
                        for m in re.findall(r"\b[A-Z][A-Za-z0-9_]*\b", src_code):
                            if m in by_stem:
                                bases.append(m)
            mods[rel] = bases

    # extends 闭包：凡被继承者并入 core

    core = {rel for rel in mods if tree[rel] == "core"}
    closure = set(core)
    changed = True
    while changed:
        changed = False
        for rel, bases in mods.items():
            if rel in closure:
                continue
            for b in bases:
                for cand in by_stem.get(_stem(b), []):
                    if cand in closure:
                        closure.add(rel)
                        changed = True
                        break
                if rel in closure:
                    break
    leaves = sorted(rel for rel in mods if rel not in closure)

    # 判据 A：每个 leaf 的直接基类都能在 core 闭包里找到定义模块
    viol_a = []
    for rel in leaves:
        for b in mods[rel]:
            defs = by_stem.get(_stem(b), [])
            if not defs:
                viol_a.append({"leaf": rel, "base": str(b),
                               "problem": "no module defines this name"})
            elif not any(d in closure for d in defs):
                viol_a.append({"leaf": rel, "base": str(b),
                               "problem": f"base only in leaves: {defs}"})
            elif len(defs) > 1:
                viol_a.append({"leaf": rel, "base": str(b),
                               "problem": f"ambiguous stem in {defs} (判据 B WARN)"})

    dup = {s: v for s, v in by_stem.items() if len(v) > 1}

    # B2 真实口径：load_for(lineup) = gd_core/* + 阵容物品的祖先闭包
    # （不必是「全部被继承者」——那只对最坏情况成立）。
    core_fixed = sorted(r for r in mods if tree[r] == "core")
    gd_core_n = len(core_fixed)

    def ancestors_closure(leaf_rels):
        need = set()
        stack = list(leaf_rels)
        while stack:
            rel = stack.pop()
            if rel in need:
                continue
            need.add(rel)
            for b in mods.get(rel, []):
                for cand in by_stem.get(_stem(b), []):
                    if tree.get(cand) == "items" and cand not in need:
                        stack.append(cand)
                    elif tree.get(cand) == "core":
                        need.add(cand)          # gd_core 树恒在 core 档
        return need

    sample = [r for r in mods if tree[r] == "items"][:40]   # 稀薄物品抽样 40 件
    per_item = sorted(ancestors_closure([r]) - set(core_fixed) for r in sample)
    avg_items = sum(len(s) for s in per_item) / max(1, len(per_item))

    report = {
        "modules_total": len(mods),
        "gd_core_tree": gd_core_n,
        "items_tree": len(mods) - gd_core_n,
        "items_inherited_by_anyone": len(closure - set(core_fixed)),
        "load_for_sample_lineup_avg_imports": round(gd_core_n + avg_items, 1),
        "load_all_imports": len(mods),
        "startup_saving_pct": round(100 * (1 - (gd_core_n + avg_items) / len(mods)), 1),
        "duplicate_stems": {s: v for s, v in dup.items()},
        "criteria_A_violations": viol_a,
        "leaves_sample": leaves[:15],
        "pass": not viol_a,
    }
    os.makedirs(os.path.dirname(args.json), exist_ok=True)
    with open(args.json, "w", encoding="utf-8") as f:
        json.dump(report, f, ensure_ascii=False, indent=1)
        f.write("\n")
    print(f"modules={report['modules_total']} gd_core树={report['gd_core_tree']} "
          f"items树={report['items_tree']}（被继承者 {report['items_inherited_by_anyone']}）")
    print(f"load_for 抽样阵容(40 件) 平均导入 {report['load_for_sample_lineup_avg_imports']} "
          f"vs load_all {report['load_all_imports']} → 可省 ≈{report['startup_saving_pct']}%")
    print(f"duplicate stems={len(dup)} 判据A违例={len(viol_a)}")
    for v in viol_a[:8]:
        print(f"  VIOL {v['leaf']}: base {v['base']} → {v['problem']}")
    print(f"→ {args.json}")
    return 0 if report["pass"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
