# -*- coding: utf-8 -*-
"""audit_effects.py — 逐物品核对行为是否从源码正确提取。
输出：
  1) 无脚本物品
  2) 仍落在 methods_raw(编译失败) 的方法，并标注是否为战斗相关方法
  3) 战斗相关方法缺失统计（源码有、DB无）
"""
import json, os, sys, re
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import simulator.extract_items as E

DB = os.path.join(os.path.dirname(__file__), "..", "assets", "battle_items.json")
DECOMP = os.path.join(os.path.dirname(__file__), "..", "decompiled_full", "Items")

# 战斗相关方法（引擎在战斗中会调用）
COMBAT_METHODS = {
    "doCooldownEffect", "onCombatStart", "combatStart", "onTriggerPotion",
    "onCombatEnd", "onWeaponAttacked", "onDealtDamage", "preHit",
    "onPreDealDamage_early", "onPreDealDamage_late", "afterBlock",
    "onHit", "onDamaged", "onAttacked", "onPotionTriggered", "onConsume",
    "onPrepare", "prepare", "onReady", "canAffect", "canAffect_secondary",
    "canAffect_global", "onItemActivated", "onAnyItemActivated",
    "onCharacterDamaged", "onCharacterHealed", "onRoundStart", "onBattleStart",
    "onDealtDamage", "onTrigger", "onActivate", "onStartOfBattle",
    "onHit", "onAttacked", "onDamaged", "onMeleeAttacked", "onRangedAttacked",
}


def combat_methods_in_source(path):
    """从源码提取所有 func 名（不解析体，只看签名）"""
    if not os.path.exists(path):
        return set()
    txt = open(path, encoding="utf-8", errors="replace").read()
    return set(re.findall(r'func\s+([A-Za-z_]\w*)\s*\(', txt))


def main():
    db = json.load(open(DB, encoding="utf-8"))
    items = db.get("items", db)
    idx = E.scan_scripts()

    no_script = []
    raw_combat_broken = []   # (item, [combat methods in raw])
    raw_noncombat = []       # (item, [noncombat methods in raw])
    missing_combat = []      # (item, [combat methods in source but not in DB methods])

    for key, v in items.items():
        beh = v.get("behavior")
        scr = v.get("script")
        sp = None
        if scr:
            norm = scr[:-3].lower().replace(" ", "") if scr.endswith(".gd") else scr.lower().replace(" ", "")
            sp = idx.get(norm)
        if sp is None:
            sp = E.match_script_key(key, idx)
        if sp is None:
            no_script.append(key)
            continue
        src_methods = combat_methods_in_source(sp)
        if not beh:
            # 有脚本但无 behavior（理论上不会发生）
            missing_combat.append((key, sorted(src_methods & COMBAT_METHODS)))
            continue
        db_methods = set(beh.get("methods", {}).keys())
        raw_methods = set(beh.get("methods_raw", {}).keys())
        broken_combat = sorted((raw_methods) & COMBAT_METHODS)
        broken_non = sorted(raw_methods - COMBAT_METHODS)
        if broken_combat:
            raw_combat_broken.append((key, broken_combat))
        if broken_non:
            raw_noncombat.append((key, broken_non))
        # 源码有战斗方法但 DB 完全没有（既不在 methods 也不在 raw）
        absent = sorted((src_methods & COMBAT_METHODS) - db_methods - raw_methods)
        if absent:
            missing_combat.append((key, absent))

    print("=" * 70)
    print(f"一、无脚本物品 ({len(no_script)}):")
    for k in no_script:
        print("   ", k, "| cat=", items[k].get("category"), "| can_activate=", items[k].get("can_activate"))
    print("=" * 70)
    print(f"二、战斗相关方法编译失败(落入 raw, 即‘无效果/错误’)({len(raw_combat_broken)}):")
    for k, m in raw_combat_broken:
        print("   ", k, "->", m)
    print("=" * 70)
    print(f"三、源码有战斗方法但 DB 完全缺失({len(missing_combat)}):")
    for k, m in missing_combat:
        print("   ", k, "->", m)
    print("=" * 70)
    print(f"四、非战斗方法(商店/视觉)编译失败，不影响战斗({len(raw_noncombat)}):")
    for k, m in raw_noncombat:
        print("   ", k, "->", m)
    print("=" * 70)
    print("汇总: 无脚本=%d, 战斗方法损坏=%d, 战斗方法缺失=%d, 非战斗损坏=%d" % (
        len(no_script), len(raw_combat_broken), len(missing_combat), len(raw_noncombat)))


if __name__ == "__main__":
    main()
