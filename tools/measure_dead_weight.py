# -*- coding: utf-8 -*-
"""measure_dead_weight.py — 度量内核的「死残留」（精简度体检，**只报告不拦截**）

================ 为什么需要它 ================
「继续压缩精简」这类要求如果没有度量，就只能靠感觉 —— 感觉会让人反复去删那些
**看起来像垃圾、实际是契约**的东西（例如上轮：物品脚本里 328 个空桩函数，看着像
冗余，实则是原版 `has_method()` 动态派发的落点；删了就会让回调静默失效）。

本工具给出两个可复现的数字，回答「还有多少可压」：

  死桩函数 —— 函数体只有 `pass`/空，且**全工程**（gd_core + gd_core_items）
              除定义处外零引用，且不在动态派发敏感名单里。
  死字段   —— `var x` 声明后全工程零引用（典型来源：`onready var X = $Particles`
              被剥成 `var X` 后的残留）。

================ 判据为什么必须保守 ================
1. **动态派发名单**（DYNAMIC_SAFE）里的名字一律不算死 —— 原版大量使用
   `has_method("onCombatStart")` / tscn 的 `timeout → buffEnded` 连接 / 信号回调，
   全都不产生源码级引用。
2. **同一名字在别处的定义也算引用**：若 `playAttackAnimation` 在 CoreHooks 有定义，
   那它在物品脚本里的空覆写就不是「零引用」，本工具会跳过（宁可少报）。
3. 本工具**不做任何删除**。按项目既定原则「宁可少删」，删除必须逐条人工判断。

================ 当前基线（2026-09-23 实测）================
    gd_core          26 行 / 9046 行 = 0.3%   ← 手写内核，已到地板
    gd_core_items   332 行 / 20242 行 = 1.6%  ← 自动生成，其中 128 行集中在
                                                 gd_core_items/Item.gd（适配层）
结论：**继续压缩的空间已极小**，且剩余部分多为有意保留的契约。

用法：
    python tools/measure_dead_weight.py            # 汇总 + 明细 top 25
    python tools/measure_dead_weight.py --detail   # 逐名字列出全部（不截断）
"""
import os
import re
import sys
from collections import Counter, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DIRS = ["gd_core", "gd_core_items"]

# ── 动态派发敏感名单 ──
# 这些名字即使当前无人按名引用也必须保留：原版靠 has_method() / tscn 连接 /
# 信号回调到达它们，源码级引用为零是**正常状态**而非冗余。
DYNAMIC_SAFE = {
    # Godot 生命周期
    "_ready", "_readyInit", "_physics_process", "_process", "_input",
    "_notification", "_init", "setup",
    # 内核接缝与物品回调（见 CoreItem.SELF_BEHAVIOR_METHODS 与 Item.gd 的动态派发）
    "onPrepare", "onCombatStart", "onCombatEnd", "doCooldownEffect", "canAffect",
    "getTriggerPriority", "reactToItemTypeChange", "ready_deferred",
    "onDealtDamage", "onChargeReceived", "onChargeLeft",
    "onPreDealDamage_early", "onPreDealDamage_late",
    "getGatedDescriptor", "getReplaceDescriptor",
    "getAffectedCellsAfterRotate_primary", "getAffectedCellsAfterRotate_secondary",
    "isAffectingDistinct", "affectsEmpty", "canCombine",
    # 商店钩子（tscn / Game 信号连接）
    "onGateItemRoll", "onShopEntered", "onItemRoll", "onSaleRoll",
}

FUNC_RE = re.compile(r"^func\s+([A-Za-z_]\w*)\s*\(")
VAR_RE = re.compile(r"^var\s+([A-Za-z_]\w*)\s*(?::|=|$)")
TOKEN_RE = re.compile(r"[A-Za-z_]\w*")


def load_sources():
    src = {}
    for d in DIRS:
        base = os.path.join(ROOT, d)
        if not os.path.isdir(base):
            continue
        for root, _, fs in os.walk(base):
            for f in fs:
                if f.endswith(".gd"):
                    p = os.path.join(root, f)
                    rel = os.path.relpath(p, ROOT).replace(os.sep, "/")
                    src[rel] = open(p, encoding="utf-8", errors="replace").read().splitlines()
    return src


def scan(src):
    """返回 (tokens, empty_funcs, declared_vars)。"""
    tokens = Counter()
    empty_funcs = defaultdict(list)
    declared_vars = defaultdict(list)
    for p, lines in src.items():
        for i, ln in enumerate(lines):
            code = re.sub(r"#[^\n]*", "", ln)
            for t in TOKEN_RE.findall(code):
                tokens[t] += 1
            m = FUNC_RE.match(ln)
            if m:
                j = i + 1
                body = []
                while j < len(lines) and (lines[j].strip() == "" or lines[j][:1] in " \t"):
                    body.append(lines[j].strip())
                    j += 1
                nb = [x for x in body if x]
                if not nb or nb == ["pass"]:
                    empty_funcs[m.group(1)].append("%s:%d" % (p, i + 1))
            m2 = VAR_RE.match(ln)
            if m2:
                declared_vars[m2.group(1)].append("%s:%d" % (p, i + 1))
    return tokens, empty_funcs, declared_vars


def main():
    show_all = "--detail" in sys.argv
    src = load_sources()
    tokens, empty_funcs, declared_vars = scan(src)

    # 零引用判据：token 数 <= 定义处数（定义行自身会贡献 1 个 token）
    dead_f = {n: ps for n, ps in empty_funcs.items()
              if tokens.get(n, 0) <= len(ps) and n not in DYNAMIC_SAFE}
    dead_v = {n: ps for n, ps in declared_vars.items() if tokens.get(n, 0) <= len(ps)}

    print("死残留体检（只报告，不删除）")
    print("=" * 70)
    print("扫描 %d 个 .gd 文件" % len(src))
    print("")
    print("空桩函数：%d 个名字 / %d 处定义"
          % (len(empty_funcs), sum(len(v) for v in empty_funcs.values())))
    print("  → 其中全工程零引用且不在动态派发名单：%d 个名字 / %d 处"
          % (len(dead_f), sum(len(v) for v in dead_f.values())))
    if dead_f:
        lim = None if show_all else 25
        for n, _ in sorted(dead_f.items(), key=lambda x: -len(x[1]))[:lim]:
            print("       %-32s %2d 处  %s" % (n, len(dead_f[n]), dead_f[n][0]))
    print("")
    print("字段声明：%d 个名字 / %d 处声明"
          % (len(declared_vars), sum(len(v) for v in declared_vars.values())))
    print("  → 其中全工程零引用：%d 个名字 / %d 处"
          % (len(dead_v), sum(len(v) for v in dead_v.values())))
    if dead_v:
        lim = None if show_all else 25
        for n, _ in sorted(dead_v.items(), key=lambda x: -len(x[1]))[:lim]:
            print("       %-32s %2d 处  %s" % (n, len(dead_v[n]), dead_v[n][0]))

    # 按目录汇总「死残留行数 / 总行数」。★ 逐**路径**计数，不能按名字 ——
    # 同一个名字可能同时在两个目录里有定义（如 CoreHooks 与物品脚本各一份）。
    print("")
    print("按目录（死残留行数 = 死桩定义处 + 死字段声明处）")
    print("-" * 70)
    per_path = Counter()
    for ps in list(dead_f.values()) + list(dead_v.values()):
        for p in ps:
            per_path[p.split(":")[0]] += 1
    grand = 0
    grand_tot = 0
    for d in DIRS:
        hits = sum(c for p, c in per_path.items() if p.startswith(d + "/"))
        tot = sum(len(v) for p, v in src.items() if p.startswith(d + "/"))
        grand += hits
        grand_tot += tot
        pct = (100.0 * hits / tot) if tot else 0.0
        print("  %-16s %5d 行 / %6d 行 = %4.1f%%" % (d, hits, tot, pct))
    print("  %-16s %5d 行 / %6d 行 = %4.1f%%"
          % ("合计", grand, grand_tot, (100.0 * grand / grand_tot) if grand_tot else 0.0))
    print("")
    print("★ 判据是保守的（动态派发名单 + 同名字跨文件互认），故真实可删量只会更小。")
    print("★ 按项目原则「宁可少删」，本工具不执行任何删除。")
    return 0


if __name__ == "__main__":
    sys.exit(main())
