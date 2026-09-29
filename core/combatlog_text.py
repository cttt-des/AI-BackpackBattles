# -*- coding: utf-8 -*-
"""combatlog_text.py — 把内存读出的战斗事件渲染成游戏同格式日志文本

真值源：decompiled_full/Core/CombatEvent.gd 的 asText()（LOG 键推导逻辑
逐分支复刻），模板文本取自官方翻译表 Interface.csv（en/zh 列）。
  * 深度 0 行：``x.xx:  ``（时间戳 %2.2f + ":  "）
  * 子事件行：``  ``×depth + `` > ``
  * 物品名：origin 为物品节点时用官方中文名（ItemDB）
事件输入格式见 core/combatlog_reader.read_events()。
"""
from __future__ import annotations

import re
from typing import Any, Dict, List, Optional, Tuple

# Game.EventType → 枚举名（与 reader 保持一致）
EVENT_TYPES = {
    0: "Activation", 1: "DealDamage", 2: "CriticalDamage", 3: "MissedAttack",
    4: "TakeDamage", 5: "LoseHealth", 6: "AttackSpeed", 7: "InvulnerableStart",
    8: "InvulnerableEnd", 9: "Stun", 10: "StunResisted", 11: "CriticalResisted",
    12: "Health", 13: "Stamina", 14: "DrainStamina", 15: "OutofStamina",
    16: "DamageBuff", 17: "DamReduction", 18: "DamIncrease",
    19: "TemporaryMaxHealth", 20: "TemporaryMaxStamina",
    21: "BattleRageStart", 22: "BattleRageEnd", 23: "Reincarnate",
    24: "CooldownAdvance", 98: "Unhealing", 99: "Fatigue", 100: "Block",
    101: "Lucky", 102: "Regeneration", 103: "Vampirism", 104: "Spikes",
    105: "Mana", 106: "Empower", 107: "Heat", 108: "Poison", 109: "Blind",
    110: "Cold", 111: "Win", 112: "Loss",
}

# buff/debuff 类型 → (英文名, 中文名)。游戏内渲染为图标，文本导出用名称。
BUFF_NAMES = {
    100: ("Block", "护盾"), 101: ("Lucky", "幸运"), 102: ("Regeneration", "恢复"),
    103: ("Vampirism", "吸血"), 104: ("Spikes", "尖刺"), 105: ("Mana", "魔法"),
    106: ("Empower", "充能"), 107: ("Heat", "狂热"), 108: ("Poison", "中毒"),
    109: ("Blind", "致盲"), 110: ("Cold", "冰冷"),
}

# 官方 LOG 模板（en / zh），键 = asText() 推导出的 LOG 变体族
TEMPLATES: Dict[str, Tuple[str, str]] = {
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
    "TemporaryMaxHealth": ("Gained {amount} maximum health ({origin}).", "获得{amount}最大生命值({origin})。"),
    "TemporaryMaxStamina": ("Gained {stamina} maximum stamina ({origin}).", "获得{stamina}点最大耐力（{origin}）。"),
    "Reincarnate":       ("Reincarnated with {health} health ({origin}).", "以{health}生命值复活({origin})。"),
    "BattleRageStart":   ("Entered Battle Rage for {duration}s ({origin}).", "进入狂战士之怒 {duration}s ({origin})。"),
    "BattleRageEnd":     ("Battle Rage ended.", "狂战士之怒结束。"),
    "FatigueStart":      ("Fatigue sets in...", "开始感觉疲惫……"),
    "FatigueDamage":     ("Fatigue Damage: {counter}", "疲惫伤害：{counter}"),
    "Win":               ("Round won!", "回合胜利！"),
    "Loss":              ("Round lost.", "回合失败。"),
    # —— 增减益变体（buff 用 {buff}，debuff 用 {debuff}）——
    "GAIN_BUFF": ("Gained {amount} {buff} ({origin}).", "获得{amount}层 {buff}（{origin}）。"),
    "GAIN_BUFF_TEMP": ("Gained {amount} {buff} for {duration}s ({origin}).", "获得了{amount} {buff}，持续{duration}秒 ({origin})。"),
    "GAIN_DEBUFF": ("Inflicted {amount} {debuff} ({origin}).", "施加{amount}层 {debuff}（{origin}）。"),
    "GAIN_DEBUFF_SELF": ("Self-inflicted {amount} {debuff} ({origin}).", "对自身施加{amount}层 {debuff}（{origin}）。"),
    "GAIN_DEBUFF_TEMP": ("Inflicted {amount} {debuff} for {duration}s ({origin}).", "施加了{amount} {debuff}，持续{duration}秒 ({origin})。"),
    "GAIN_DEBUFF_SELF_TEMP": ("Self-inflicted {amount} {debuff} for {duration}s ({origin}).", "对自己施加了{amount} {debuff}，持续{duration}秒 ({origin})。"),
    "LOSE_BUFF": ("Removed {amount} {buff} ({origin}).", "移除{amount}层 {buff}（{origin}）。"),
    "LOSE_BUFF_SELF": ("Lost {amount} {buff} ({origin}).", "失去{amount}层 {buff}（{origin}）。"),
    "LOSE_DEBUFF": ("Cleansed {amount} {debuff} ({origin}).", "净化{amount}层 {debuff}（{origin}）。"),
    "GAIN_BUFF_OPPONENT": ("Gave opponent {amount} {buff} ({origin}).", "给对手{amount} {buff} （{origin}）。"),
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


def _num(v: Any) -> str:
    """GDScript str() 语义：整数值浮点不带小数点；一般浮点取 6 位小数
    并去尾零（游戏内 float 运算的 4.800000000001 在原版显示为 4.8）。"""
    if isinstance(v, float):
        if v.is_integer():
            return str(int(v))
        s = f"{v:.6f}".rstrip("0").rstrip(".")
        return s if s not in ("", "-") else "0"
    return str(v)


def _is_buff(t: int) -> bool:
    return 100 <= t <= 107


def _is_debuff(t: int) -> bool:
    return 108 <= t <= 110


def _log_key(etype: int, p: Dict[str, Any], actor: int,
             target: Optional[int]) -> Optional[str]:
    """复刻 CombatEvent.asText() 的 LOG 键推导。"""
    type_str = EVENT_TYPES.get(etype)
    if not type_str:
        return None
    if "amount" in p:
        amount = p["amount"]
        if etype in (18, 17):  # DamIncrease / DamReduction（含 _TYPED/_TEMP 变体，
            return "LOG_" + type_str  # 游戏中极罕见，按基础键渲染）
        if "timeout" in p:
            return "LOG_BuffTimeout"
        if _is_buff(etype) or _is_debuff(etype):
            if p.get("used"):
                return "LOG_USE_BUFF"
            if p.get("resisted"):
                if _is_buff(etype):
                    return "LOG_NULLIFY_BUFF"
                return "LOG_REFLECT_RESIST" if p.get("reflected") else "LOG_RESIST_DEBUFF"
            if p.get("protected"):
                return "LOG_PROTECT_BUFF" if _is_buff(etype) else "LOG_PROTECT_DEBUFF"
            key = "LOG_"
            reflected = bool(p.get("reflected"))
            if reflected:
                key += "REFLECT_"
            elif amount < 0:
                key += "LOSE_"
            else:
                key += "GAIN_"
            if _is_buff(etype):
                key += "BUFF"
                if amount < 0:
                    if actor == target:
                        key += "_SELF"
                else:
                    if "duration" in p:
                        key += "_TEMP"
                    if actor != target:
                        key += "_OPPONENT"
            else:
                key += "DEBUFF"
                if not reflected and amount > 0 and actor == target:
                    key += "_SELF"
                if "duration" in p:
                    key += "_TEMP"
            return key
        return "LOG_" + type_str
    return "LOG_" + type_str


def _fmt_params(e: Dict[str, Any], lang: str) -> Dict[str, Any]:
    p = e["params"]
    etype = e["type"]
    fp: Dict[str, Any] = {}
    for k, v in p.items():
        fp[k] = _num(v) if isinstance(v, (int, float)) else v
    if "amount" in p:
        fp["amount"] = _num(abs(p["amount"]))
    if "damage" in p:
        fp["damage"] = _num(p["damage"])
    if "stamina" in p:
        fp["stamina"] = _num(p["stamina"])
    if etype in BUFF_NAMES or etype in (17, 18):
        name = BUFF_NAMES.get(etype)
        disp = (name[1] if lang == "zh" else name[0]) if name else "?"
        fp["buff"] = disp
        fp["debuff"] = disp
    if "target" in fp or e.get("target") is not None:
        fp["target"] = ("你" if lang == "zh" else "You") \
            if e.get("target") == 0 else ("对手" if lang == "zh" else "Opponent")
    origin = e.get("origin")
    if origin:
        fp["origin"] = origin["zh"] if lang == "zh" else origin["name"]
    else:
        fp["origin"] = ""
    item = p.get("item")
    if item:
        fp["item"] = item
    return fp


def render_event(e: Dict[str, Any], lang: str = "zh") -> Optional[str]:
    """单事件 → 日志行文本（不含时间戳/缩进/侧标前缀）；
    无模板的事件返回 None（与游戏一致不显示）。"""
    etype = e["type"]
    p = e["params"]
    target = e.get("target")
    if etype == 0:  # Activation：原版默认隐藏激活行（activationsState=Hide），
        return None  # 只有物品发挥的效果才成行
    # actor（行为方）：优先用事件的真实归属 side；
    # 缺失时启发——buff 视为目标自身获得，debuff 视为对手施加
    side = e.get("side")
    if side in ("P", "O"):
        actor = 0 if side == "P" else 1
    elif _is_buff(etype):
        actor = target if target is not None else 0
    else:
        actor = 1 - target if target is not None else 0
    key = _log_key(etype, p, actor, target)
    if not key:
        return None
    variant = key[4:]
    tpl = TEMPLATES.get(variant)
    # 游戏翻译表缺部分变体（如 GAIN_BUFF_OPPONENT——给对手上 buff），
    # 剥后缀回退到基础模板，并用 target 称谓（你/对手）前缀补足语义
    target_prefix = ""
    v = variant
    while tpl is None:
        stripped = False
        for suf in ("_OPPONENT", "_SELF"):
            if v.endswith(suf):
                v = v[:-len(suf)]
                target_prefix = True
                stripped = True
                break
        if not stripped:
            break
        tpl = TEMPLATES.get(v)
    if not tpl and (_is_buff(etype) or _is_debuff(etype)):
        # 兜底：按语义选增益/减益家族的基础模板，保证 buff 行不丢
        if p.get("used"):
            variant = "USE_BUFF"
        elif p.get("timeout"):
            variant = "BUFF_TIMEOUT"
        elif p.get("resisted"):
            variant = "NULLIFY_BUFF" if _is_buff(etype) else "RESIST_DEBUFF"
        elif p.get("protected"):
            variant = "PROTECT_BUFF" if _is_buff(etype) else "PROTECT_DEBUFF"
        else:
            neg = isinstance(p.get("amount"), (int, float)) and p["amount"] < 0
            fam = "BUFF" if _is_buff(etype) else "DEBUFF"
            variant = ("LOSE_" if neg else "GAIN_") + fam
            if not neg and "duration" in p:
                variant += "_TEMP"
        tpl = TEMPLATES.get(variant)
    if not tpl:
        return None
    fp = _fmt_params(e, lang)
    try:
        text = (tpl[1] if lang == "zh" else tpl[0]).format(**fp)
    except (KeyError, IndexError):
        # 缺占位符时按空串兜底，避免整行丢失
        text = (tpl[1] if lang == "zh" else tpl[0])
        import string
        for _, field, _, _ in string.Formatter().parse(text):
            if field and field.split('.')[0].split('[')[0] not in fp:
                fp[field] = ""
        try:
            text = text.format(**fp)
        except Exception:  # noqa: BLE001
            text = text
    text = text.replace("( )", "").replace("()", "")
    text = text.replace("（ ）", "").replace("（）", "")
    if target_prefix and fp.get("target") and text:
        # 「对手获得…」/「Opponent gained…」
        if lang == "en":
            text = fp["target"] + " " + text[0].lower() + text[1:]
        else:
            text = fp["target"] + text
    return text


def render_log(events: List[Dict[str, Any]], lang: str = "zh",
               dual: bool = True) -> str:
    """事件流 → 完整日志文本（模板渲染，对照 CombatEvent.asText()）。

    * 深度由 parentEvent 触发链还原：深度 0 行带 ``x.xx:  `` 时间戳前缀，
      子事件按原版缩进（``  ``×depth + ``> ``）；
    * dual=True 时每行带 ``[玩家] ``/``[对手] `` 侧标（游戏中靠行底色
      区分，文本导出显式标出），子事件继承父事件侧标。
    """
    parent_of = {e["id"]: e.get("parent") for e in events
                 if isinstance(e.get("id"), int)}
    side_of = {e["id"]: e.get("side") for e in events
               if isinstance(e.get("id"), int)}

    def depth_of(e: Dict[str, Any]) -> int:
        d, pid, seen = 0, e.get("parent"), set()
        while pid is not None and pid in parent_of and pid not in seen:
            seen.add(pid)
            d += 1
            pid = parent_of[pid]
        return d

    def side_of_line(e: Dict[str, Any]) -> Optional[str]:
        sid = e.get("side")
        if sid:
            return sid
        pid, seen = e.get("parent"), set()
        while pid is not None and pid in side_of and pid not in seen:
            seen.add(pid)
            sid = side_of[pid]
            if sid:
                return sid
            pid = parent_of.get(pid)
        return None

    tag = {"P": ("[玩家] ", "[P] "), "O": ("[对手] ", "[O] ")}
    lines = []
    for e in events:
        text = render_event(e, lang)
        if not text:
            continue
        depth = depth_of(e)
        sid = side_of_line(e)
        prefix = tag[sid][0 if lang == "zh" else 1] if (dual and sid) else ""
        if depth == 0:
            lines.append(f"{e['t']:.2f}" + ":  " + prefix + text)
        else:
            lines.append("  " * depth + "> " + prefix + text)
    return "\n".join(lines)
