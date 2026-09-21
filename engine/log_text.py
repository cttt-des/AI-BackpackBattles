# -*- coding: utf-8 -*-
"""log_text.py — 战斗日志文本渲染（复刻游戏 CombatLog 格式）

真值源：decompiled_full/Core/CombatLog.gd + CombatEvent.gd asText()
  * 深度 0 行：``x.xx:  ``（时间戳 %2.2f + ":  "）
  * 子事件行：``  ``×depth + ``> ``
  * 文本 = LOG 模板.format({origin/damage/amount/buff/debuff/duration/stamina/...})
  * 物品名经官方中文翻译（battle_items.json zh 字段）
  * dual=True 时带 [玩家]/[对手] 侧标，子事件继承父事件侧标
"""
from __future__ import annotations

from typing import Any, Dict, List, Optional

from .i18n import zh_name

# buff 类型 -> 原版显示名（对齐 Game.EventType；中文为内置翻译）
BUFF_DISPLAY = {
    100: ("Block", "护盾"),
    101: ("Lucky", "幸运"),
    102: ("Regeneration", "恢复"),
    103: ("Vampirism", "吸血"),
    104: ("Spikes", "尖刺"),
    105: ("Mana", "魔法"),
    106: ("Empower", "充能"),
    107: ("Heat", "狂热"),
    108: ("Poison", "中毒"),
    109: ("Blind", "致盲"),
    110: ("Cold", "冰冷"),
}


def _is_buff(t: int) -> bool:
    """原版 isBuff：Game.EventType.Block(100)..Heat(107)"""
    return 100 <= t <= 107


def _is_debuff(t: int) -> bool:
    """原版 isDebuff：Poison(108)..Cold(110)"""
    return 108 <= t <= 110


# 原版 LOG 模板（en / zh），键 = CombatEvent.asText() 的 LOG 变体族
TEMPLATES = {
    "Activation":        ("{origin} activated.", "{origin} 激活。"),
    "DealDamage":        ("Dealt {damage} damage ({origin}).", "造成{damage}点伤害（{origin}）。"),
    "CriticalDamage":    ("Dealt {damage} critical damage ({origin}).", "造成{damage}点暴击伤害（{origin}）。"),
    "MissedAttack":      ("Missed an attack ({origin}).", "攻击落空（{origin}）。"),
    "Health":            ("Regenerated {amount} health ({origin}).", "恢复{amount}点生命值（{origin}）。"),
    "LoseHealth":        ("Lost {amount} health ({origin}).", "失去{amount}点生命值（{origin}）。"),
    "Stamina":           ("Regenerated {stamina} stamina ({origin}).", "恢复{stamina}点耐力（{origin}）。"),
    "DrainStamina":      ("Removed {stamina} stamina ({origin}).", "消耗{stamina}点耐力（{origin}）。"),
    "OutofStamina":      ("Out of stamina ({origin}).", "耐力耗尽（{origin}）。"),
    "Stun":              ("Stunned for {duration}s ({origin}).", "被眩晕{duration}秒（{origin}）。"),
    "StunResisted":      ("Stun resisted ({origin}).", "眩晕被抵挡（{origin}）。"),
    "InvulnerableStart": ("Gained invulnerability for {duration}s ({origin}).", "获得了{duration}s内无敌（{origin}）。"),
    "InvulnerableEnd":   ("Invulnerability ended ({origin}).", "无敌结束（{origin}）。"),
    "DamageBuff":        ("{item} gained +{damage} damage ({origin}).", "{item}获得了+{damage}点伤害（{origin}）。"),
    "Reincarnate":       ("Reincarnated with {health} health ({origin}).", "以{health}生命值复活（{origin}）。"),
    "BattleRageStart":   ("Entered Battle Rage for {duration}s ({origin}).", "进入狂战士之怒 {duration}s（{origin}）。"),
    "BattleRageEnd":     ("Battle Rage ended.", "狂战士之怒结束。"),
    "FatigueStart":      ("Fatigue sets in...", "开始感觉疲惫……"),
    "FatigueDamage":     ("Fatigue Damage: {counter}", "疲惫伤害：{counter}"),
    "Win":               ("Round won!", "回合胜利！"),
    "Loss":              ("Round lost.", "回合失败。"),
    "CritResisted":      ("Crit Resisted", "暴击抵挡"),
    # —— 增减益变体（buff 用 {buff}，debuff 用 {debuff}）——
    "GAIN_BUFF": ("Gained {amount} {buff} ({origin}).", "获得{amount}层 {buff}（{origin}）。"),
    "GAIN_BUFF_TEMP": ("Gained {amount} {buff} for {duration}s ({origin}).", "获得了{amount} {buff}，持续{duration}秒 ({origin})。"),
    "GAIN_DEBUFF": ("Inflicted {amount} {debuff} ({origin}).", "施加{amount}层 {debuff}（{origin}）。"),
    "GAIN_DEBUFF_SELF": ("Self-inflicted {amount} {debuff} ({origin}).", "对自身施加{amount}层 {debuff}（{origin}）。"),
    "GAIN_DEBUFF_TEMP": ("Inflicted {amount} {debuff} for {duration}s ({origin}).", "施加了{amount} {debuff}，持续{duration}秒 ({origin})。"),
    "GAIN_DEBUFF_SELF_TEMP": ("Self-inflicted {amount} {debuff} for {duration}s ({origin}).", "对自己施加了{amount} {debuff}，持续{duration}秒 ({origin})。"),
    "LOSE_BUFF": ("Lost {amount} {buff} ({origin}).", "失去{amount}层 {buff}（{origin}）。"),
    "LOSE_DEBUFF": ("Cleansed {amount} {debuff} ({origin}).", "净化{amount}层 {debuff}（{origin}）。"),
    "USE_BUFF": ("Used {amount} {buff} ({origin}).", "消耗{amount} {buff} （{origin}）。"),
    "BUFF_TIMEOUT": ("{amount} {buff} timed out ({origin}).", "{amount} {buff}持续时间结束({origin})。"),
    "NULLIFY_BUFF": ("{amount} {buff} nullified ({origin}).", "{amount} {buff}被无效化（{origin}）。"),
    "RESIST_DEBUFF": ("{amount} {debuff} resisted ({origin}).", "{amount} {debuff}被抵挡（{origin}）。"),
    "REFLECT_RESIST": ("{amount} reflected {debuff} resisted ({origin}).", "反弹的{amount} {debuff}被抵挡（{origin}）。"),
    "REFLECT_DEBUFF": ("{amount} {debuff} reflected ({origin}).", "{amount} {debuff}被反弹（{origin}）。"),
    "REFLECT_DEBUFF_TEMP": ("{amount} {debuff} reflected for {duration}s ({origin}).", "{amount} {debuff}在{duration}s内被反弹（{origin}）。"),
    "PROTECT_BUFF": ("{amount} {buff} protected from removal ({origin}).", "对{amount} {buff}的移除被保护（{origin}）。"),
    "PROTECT_DEBUFF": ("{amount} {debuff} protected from cleansing ({origin}).", "对{amount} {debuff}的净化被保护（{origin}）。"),
}

# 原版无对应日志行的事件（保留在 JSON，文本抑制）
_SUPPRESSED = {"combat_start", "stun_end", "death", "tick", "spikes", "vampirism", "block_break"}


def _fmt_duration(d) -> str:
    if d is None:
        return ""
    if isinstance(d, float) and d.is_integer():
        return str(int(d))
    return f"{d:.2f}".rstrip("0").rstrip(".")


def _stack_variant(p: Dict[str, Any], is_buff: bool, is_loss: bool) -> str:
    """对齐 CombatEvent.asText() 的 LOG 变体构造"""
    if p.get("timeout"):
        return "BUFF_TIMEOUT"
    if p.get("used"):
        return "USE_BUFF"
    if p.get("resisted"):
        if is_buff:
            return "NULLIFY_BUFF"
        return "REFLECT_RESIST" if p.get("reflected") else "RESIST_DEBUFF"
    if p.get("protected"):
        return "PROTECT_BUFF" if is_buff else "PROTECT_DEBUFF"
    if p.get("reflected"):
        if is_buff:
            return "REFLECT_BUFF"
        return "REFLECT_DEBUFF_TEMP" if "duration" in p else "REFLECT_DEBUFF"
    if is_loss:
        return "LOSE_BUFF" if is_buff else "LOSE_DEBUFF"
    if is_buff:
        return "GAIN_BUFF_TEMP" if "duration" in p else "GAIN_BUFF"
    variant = "GAIN_DEBUFF"
    if p.get("actor_is_target"):
        variant += "_SELF"
    if "duration" in p:
        variant += "_TEMP"
    return variant


def _t(key: str, fp: Dict[str, Any], lang: str) -> str:
    en, zh = TEMPLATES.get(key, ("{%s}" % key, "{%s}" % key))
    tmpl = zh if lang == "zh" else en
    try:
        text = tmpl.format(**fp)
    except (KeyError, IndexError):
        text = tmpl
    # 占位符为空产生的括号残留
    text = text.replace("( )", "").replace("()", "")
    text = text.replace("（ ）", "").replace("（）", "").replace(" .", ".")
    return text


def _side_of(actor) -> Optional[str]:
    a = str(actor) if actor is not None else ""
    if a in ("player", "0"):
        return "P"
    if a in ("opponent", "1"):
        return "O"
    return None


def render_log(events: List[Any], lang: str = "zh",
               dual: bool = True) -> str:
    """把引擎事件流渲染为游戏格式文本。"""
    if lang == "zh":
        side_tag = {"P": "[玩家] ", "O": "[对手] "}
    else:
        side_tag = {"P": "[P] ", "O": "[O] "}
    lines = []
    sides: Dict[int, Optional[str]] = {}
    for e in events:
        # 侧标：事件 actor 优先；子事件继承父事件
        side = _side_of(getattr(e, "actor", None))
        if side is None and getattr(e, "parent", None) is not None:
            side = sides.get(e.parent)
        eid = getattr(e, "id", None)
        if eid is not None:
            sides[eid] = side
        text = _render_event(e, lang)
        if not text:
            continue
        tag = side_tag[side] if (dual and side) else ""
        depth = getattr(e, "depth", 0) or 0
        if depth == 0:
            line = f"{e.t:.2f}" + ":  " + tag + text
        else:
            line = "  " * depth + "> " + tag + text
        lines.append(line)
    return "\n".join(lines)


def _render_event(e, lang: str) -> Optional[str]:
    etype = getattr(e, "type", "")
    p = getattr(e, "params", {}) or {}
    origin = getattr(e, "origin", None) or ""
    if not isinstance(origin, str):
        origin = getattr(origin, "key", "")
    # 物品名国际化：优先游戏官方中文名
    if lang == "zh" and origin:
        origin = zh_name(origin)
    if lang == "zh" and p.get("buff"):
        p = dict(p)
        for k in ("buff", "debuff", "item_name"):
            if p.get(k):
                p[k] = zh_name(p[k])

    if etype in _SUPPRESSED:
        return None

    if etype == "combat_end":
        return _t("Win" if p.get("winner") == "player" else "Loss", {}, lang)

    if etype == "item_activate":
        return _t("Activation", {"origin": origin}, lang)

    if etype in ("attack", "critical"):
        if etype == "critical" or p.get("crit") or p.get("critical"):
            return _t("CriticalDamage", {"damage": p.get("damage", 0), "origin": origin}, lang)
        if p.get("missed") or not p.get("hit", True):
            return _t("MissedAttack", {"origin": origin}, lang)
        return _t("DealDamage", {"damage": p.get("damage", 0), "origin": origin}, lang)

    if etype == "missed":
        return _t("MissedAttack", {"origin": origin}, lang)

    if etype == "heal":
        return _t("Health", {"amount": p.get("amount", 0), "origin": origin}, lang)

    if etype == "lose_health":
        return _t("LoseHealth", {"amount": p.get("amount", 0), "origin": origin}, lang)

    if etype == "unhealing":
        return _t("LoseHealth", {"amount": p.get("amount", 0), "origin": origin}, lang)

    if etype == "spike_damage":
        return _t("DealDamage", {"damage": p.get("amount", 0), "origin": origin or "spikes"}, lang)

    if etype == "fatigue_damage":
        return _t("FatigueDamage", {"counter": p.get("amount", p.get("counter", 0))}, lang)

    if etype == "fatigue_start":
        return _t("FatigueStart", {}, lang)

    if etype == "stamina_gain":
        return _t("Stamina", {"stamina": p.get("amount", 0), "origin": origin}, lang)

    if etype in ("stamina_drain", "stamina_use"):
        return _t("DrainStamina", {"stamina": p.get("amount", 0), "origin": origin}, lang)

    if etype == "out_of_stamina":
        return _t("OutofStamina", {"origin": origin}, lang)

    if etype == "stun":
        return _t("Stun", {"duration": _fmt_duration(p.get("duration")),
                           "origin": origin}, lang)

    if etype == "stun_resisted":
        return _t("StunResisted", {"origin": origin}, lang)

    if etype == "crit_resisted":
        return _t("CritResisted", {}, lang)

    if etype == "invulnerable_start":
        return _t("InvulnerableStart", {"duration": _fmt_duration(p.get("duration")),
                                        "origin": origin}, lang)

    if etype == "invulnerable_end":
        return _t("InvulnerableEnd", {"origin": origin}, lang)

    if etype == "reincarnate":
        return _t("Reincarnate", {"health": p.get("amount", 0), "origin": origin}, lang)

    if etype in ("stack_gain", "stack_lose", "stack_timeout"):
        bt = getattr(e, "buff_type", None)
        disp_en, disp_zh = BUFF_DISPLAY.get(
            bt, (p.get("buff", "?"), p.get("buff", "?")))
        is_buff = _is_buff(bt) if bt is not None else True
        is_loss = (etype == "stack_lose")
        variant = _stack_variant(p, is_buff, is_loss)
        amt = p.get("amount", 0)
        fp = {"amount": abs(amt) if isinstance(amt, (int, float)) else 0,
              "buff": disp_en, "debuff": disp_en,
              "duration": _fmt_duration(p.get("duration")),
              "origin": origin}
        if lang == "zh":
            fp["buff"], fp["debuff"] = disp_zh, disp_zh
        return _t(variant, fp, lang)

    # 兜底：未知类型按伤害行渲染（理论上不命中）
    return _t("DealDamage", {"damage": p.get("damage", p.get("amount", 0)),
                             "origin": origin}, lang)
