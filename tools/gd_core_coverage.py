#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""gd_core_coverage.py — gd_core 相对解包源码的方法覆盖度核算

回答一个问题：gd_core 到底照搬了原版的哪些方法、漏掉了哪些、漏掉的属不属于
战斗判定路径？

做法：把 gd_core/CoreXxx.gd 的 `func` 名集合，与对应解包源码
decompiled_full/.../Xxx.gd 的 `func` 名集合做差集，再按**名字启发式**给缺失项
分类。分类只用于人眼筛查，不作为「无影响」的证明 —— 证明仍靠源码逐行核对。

用法：
    python tools/gd_core_coverage.py            # 汇总表
    python tools/gd_core_coverage.py --list     # 附带每个文件的缺失明细
    python tools/gd_core_coverage.py --unknown  # 只列「启发式无法归类」的缺失项
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# gd_core 文件 → 解包源码文件
MAP = {
    "CoreItem.gd":         "Items/Item.gd",
    "CoreCharacter.gd":    "Core/Character.gd",
    "CoreBuff.gd":         "Core/Buff.gd",
    "CoreCombatLog.gd":    "Core/CombatLog.gd",
    "CoreDamageSource.gd": "Utility/DamageSource.gd",
    "CoreDamageResult.gd": "Utility/DamageResult.gd",
    "CoreEvent.gd":        "Core/CombatEvent.gd",
}

FUNC_RE = re.compile(r"^func\s+([A-Za-z_]\w*)", re.M)

# ★ 战斗判定路径关键词：未收录即视为**缺口**（下一里程碑待补），
#   因为物品行为（Items/*.gd）会直接调这些函数。
BATTLE_KEYS = (
    # 伤害 / 治疗 / 生命
    "heal", "steal", "damage", "purge", "lifesteal", "vampirism", "healthto",
    "gethp", "curhealth", "maxhealth", "missinghealth", "relativehealth",
    # 计时 / 触发 / 激活
    "trigger", "activate", "cooldown", "effect", "charge", "sendcharge",
    "reactsto", "chance", "crit", "accuracy",
    # Buff / 栈 / 状态
    "buff", "stack", "empower", "lucky", "blind", "spikes", "heat", "cold",
    "poison", "mana", "regen", "cleanse", "inflict", "stun", "vamp",
    "battlerage", "resistance", "reduction", "protection", "vulnerable",
    # 体力
    "stamina",
    # 类型 / 判定辅助
    "hastype", "gettype", "gettypes", "isstate", "counttype", "gainsbuff",
    "usebuff", "isbaseitem",
    # 命中 / 格挡
    "block", "hit", "miss", "reflect", "resist",
    # 网格邻接 / 宝石 / 联动（阶段2）
    "affected", "neighbor", "collision", "gem", "socket", "canaffect",
    "extension", "cell", "rotate", "orientation",
    # 朝向（SpintoWin.doCooldownEffect / LongSpear / RainbowPotion 按 faceDirection 分流效果）
    "facedirection",
)

# 非判定路径关键词：不收录属「解耦剥离」，是本次精简的目的
OUT_KEYS = (
    "anim", "tween", "shader", "particle", "sprite", "texture", "color",
    "modulate", "z_", "pulse", "flash", "blink", "label", "shadow", "bright",
    "spotlight", "popin", "reveal", "clip", "float_label",
    "sound", "audio", "stream", "music", "sfx", "pitch", "volume",
    "button", "cursor", "drag", "hover", "click", "scroll", "arrow", "_input",
    "focus", "menu", "tooltip", "highlight", "select", "toggle", "rect",
    "resize", "visible", "filter", "search", "unhighlight", "warp",
    "_ready", "_enter_tree", "_exit_tree", "_notification", "reparent",
    "replay", "history", "statlogger", "catchup", "astext", "export",
    "meter", "idle",
    "save", "load", "achievement", "unlock", "steam", "network", "rpc",
    "settings", "profile", "levelup",
    "inventory", "storage", "shop", "craft", "recipe", "fuse", "fusion",
    "catalyst", "ingredient", "bond", "price", "gold", "sell", "buy",
    "library", "preview", "buildviewer", "infopanel", "gridstorageicon",
    "pickup", "drop", "lock", "picking", "grabbable", "rigidbody", "physics_material",
    "preset", "discard", "disappear", "setstate", "onstatechanged", "getdata",
    "setdata", "combattoshop", "shoptotitle", "titletoshop", "combattotitle",
    "gettranslated", "getflavortext", "getdescription", "getrarity", "gettext",
    "gettable", "getnumtooltip", "getmode", "getnumtiers",
)


# 已按设计改走 CoreHooks 钩子的原版方法（名字是表现/UI，但落在判定路径关键词上被
# 启发式误抓）。这些**不是缺口**：调用点仍在，只是副作用被换成可注入的空实现。
HOOK_ROUTED = {
    "showCooldown", "showCooldownSmooth", "logCooldown",
    "playActivateAnimation", "playStunAnimation", "playBattleRageAnimation",
    "playInvulnerableAnimation", "playAffectedPlacedAnimation", "playActivateAnimation",
    "activateDragParticles", "deactivateDragParticles", "deactivateParticles",
    "clearCanAffectVisuals", "randBuffLabelPos", "randHealNumberPos",
    "hideSockets", "showSockets",
    "getCombatDisplayAccuracy", "getDisplayCritChance", "getTextEffect",
    "getTypeDescription", "rollShopChance", "getShopChance",
    "activateScrollWithArrow", "replayElectricalCharges", "logElectricalCharge",
    "updateDisplayCooldowns", "snapshotDamageDealt", "updateDamageMeter",
}


def classify(name):
    low = name.lower()
    if name in HOOK_ROUTED:
        return "钩子剥离"
    # ★ 判定路径优先判定：避免 "getAffectedCells" 被 "cell"/"get" 类关键词误伤
    if any(k in low for k in BATTLE_KEYS):
        return "★战斗缺口"
    if any(k in low for k in OUT_KEYS):
        return "解耦剥离"
    return "待目视"


def funcs_of(path):
    try:
        with open(path, encoding="utf-8") as fh:
            return set(NAME_ONLY.findall(fh.read()))
    except OSError:
        return None


NAME_ONLY = re.compile(r"^func\s+([A-Za-z_]\w*)", re.M)


def main():
    show_list = "--list" in sys.argv
    only_unknown = "--unknown" in sys.argv

    print("gd_core 覆盖度核算（方法名集合差）")
    print("=" * 78)
    print("  ★战斗缺口 = 名字落在判定路径关键词上，未收录即为下一里程碑待补")
    print("  解耦剥离   = UI/视觉/音频/回放/背包/商店/合成/存档，本次精简有意剥离")
    print("  待目视     = 启发式无法判断，需逐个看源码确认归属")
    print()
    print(f"{'gd_core 文件':<20}{'源文件':<24}{'原版':>5}{'收录':>5}{'★缺口':>7}{'剥离':>6}{'待目视':>7}")
    print("-" * 78)

    all_unknown = {}
    all_gap = {}
    grand = [0, 0]
    for core, src in MAP.items():
        cp = os.path.join(ROOT, "gd_core", core)
        sp = os.path.join(ROOT, "decompiled_full", *src.split("/"))
        if not os.path.exists(cp) or not os.path.exists(sp):
            continue
        cf, sf = funcs_of(cp), funcs_of(sp)
        missing = sf - cf
        gap = sorted(m for m in missing if classify(m) == "★战斗缺口")
        out = sum(1 for m in missing if classify(m) == "解耦剥离")
        unk = sorted(m for m in missing if classify(m) == "待目视")
        all_gap[core] = gap
        all_unknown[core] = unk
        grand[0] += len(sf)
        grand[1] += len(cf)
        print(f"{core:<20}{src:<24}{len(sf):>5}{len(cf):>5}{len(gap):>7}{out:>6}{len(unk):>7}")
        if show_list:
            if gap:
                print(f"    ★战斗缺口（{len(gap)}）: " + ", ".join(gap))
            if unk:
                print(f"    待目视（{len(unk)}）: " + ", ".join(unk))
            print()

    print("-" * 78)
    print(f"方法名覆盖率：原版 {grand[0]} → gd_core 收录 {grand[1]}"
          f"（{grand[1] * 100.0 / max(grand[0], 1):.1f}%）")

    total_gap = sum(len(v) for v in all_gap.values())
    print(f"\n★ 判定路径缺口合计：{total_gap} 项")
    for core, names in all_gap.items():
        if names:
            print(f"  {core}（{len(names)}）: " + ", ".join(names))

    total_unk = sum(len(v) for v in all_unknown.values())
    print(f"\n待目视合计：{total_unk} 项（需逐个看源码确认归属）")
    return 0


if __name__ == "__main__":
    sys.exit(main())
