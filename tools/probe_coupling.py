# -*- coding: utf-8 -*-
"""临时探针：量化解包 GDScript 战斗路径与 UI/物理/音频/日志的耦合度。"""
import re, os, collections

BASE = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "decompiled_full")

COMBAT_FUNCS_ITEM = {
 "_physics_process","prepare","onPrepare","preCombatStart","onPreCombatStart",
 "combatStart","postCombatStart","onPostCombatStart","repeatCombatStart","combatEnd","onCombatEnd",
 "cacheAffectedItemsForCombat","trigger","doCooldownEffect","activate","activateFromEvent",
 "adjustCooldown","updateBaseCooldown","setBaseCooldown","resetBaseCooldown",
 "getCooldown","getBaseCooldown","advanceCooldownPercent","advanceCooldownSeconds",
 "checkTriggerCount","canActivate","randDamage","getMinDamage","getMaxDamage",
 "getSpeed","disconnectCombat","connectForCombat","getGemsNoNull",
}

CAT = [
 ("visual",  re.compile(r"\b(animation|sprite|shadow|Shadow|particles|Particles|tween|Tween|modulate|z_index|global_scale|showCooldown|playActivation|playAnimation|resetSprite|spawnRotationSparks|updateShadow|updateShaderRotation)\b")),
 ("audio",   re.compile(r"\b(Sound|playDropSound|playActivationSound|playSound|volume_db)\b")),
 ("log",     re.compile(r"\b(combatLog|snapshotItemTooltipStat|snapshotGlobalStat|createEvent|addMetric|spawnLabel|addItemMetric)\b")),
 ("ui",      re.compile(r"\b(clickArea|tooltip|Tooltip|hover|Hover|mouse|Mouse|dragged|picking|Picking|focus|Focus|preview)\b")),
 ("physics", re.compile(r"\b(apply_impulse|get_linear_velocity|Physics2D|spaceState|collide_shape|makeRigidBody|makeNonRigidBody|physics_material_override|RigidBody2D|collisionShape|findFreeSpace|sleeping|mode)\b")),
 ("persist", re.compile(r"\b(persistData|getData|setData|RunDatabase)\b")),
 ("singleton", re.compile(r"\b(Game|Util|Settings|EventBus|ItemBook|CraftingManager|Sound|ObjectPool)\.")),
]


def split_funcs(path):
    src = open(path, encoding="utf-8", errors="replace").read().splitlines()
    funcs, cur, name, start = [], [], None, 0
    for i, line in enumerate(src):
        m = re.match(r"^func\s+([A-Za-z_]\w*)", line)
        if m:
            if name:
                funcs.append((name, start, cur))
            name, cur, start = m.group(1), [line], i + 1
        elif name is not None:
            cur.append(line)
    if name:
        funcs.append((name, start, cur))
    return funcs


def report(rel, wanted=None):
    path = os.path.join(BASE, rel)
    total = len(open(path, encoding="utf-8", errors="replace").read().splitlines())
    funcs = split_funcs(path)
    sel = [f for f in funcs if (wanted is None or f[0] in wanted)]
    n = sum(len(f[2]) for f in sel)
    cnt = collections.Counter()
    for name, start, lines in sel:
        for line in lines:
            for cname, rx in CAT:
                if rx.search(line):
                    cnt[cname] += 1
    print("== %s ==  文件 %d 行 / 所选函数 %d 个 %d 行" % (rel, total, len(sel), n))
    for cname, _ in CAT:
        print("     %-10s %4d 行  %5.1f%%" % (cname, cnt[cname], 100.0 * cnt[cname] / max(1, n)))
    print()


report("Items/Item.gd", COMBAT_FUNCS_ITEM)
report("Core/Character.gd")
report("Core/Buff.gd")
report("Core/Game.gd")
