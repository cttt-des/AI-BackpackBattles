# -*- coding: utf-8 -*-
"""events.py — 战斗事件日志（严格复刻 Core/CombatEvent.gd + Core/CombatLog.gd）

复刻要点（来自 decompiled_full）：
  * 时间戳格式：深度 0 行 = ``"%2.2f" % t + ":  "``（如 ``12.34:  ``）；
    深度 > 0 的子事件行 = ``"  " * depth + "> "``（如 ``   > ``），**无时间戳**。
  * 文本模板全部取自原版 Interface.csv 的 LOG_* 翻译串（此处 GDRE 把 key 丢了，
    但英文/中文文本完整），用词条 + {origin}/{damage}/{amount}/{buff}/{debuff}/
    {duration}/{stamina}/{health}/{counter} 占位符还原。
  * 父/子事件：原版中一次物品激活(activation)是父事件，它触发的攻击/治疗/增减益
    都是其 ``triggerEvent`` 子事件，渲染时缩进一级并加 ``> `` 前缀。

事件类型常量尽量对齐 Game.EventType；渲染时再映射到原版的 LOG 模板。
"""
from __future__ import annotations

from typing import Any, Dict, List, Optional

from .i18n import zh_name as i18n_zh_name

# ---------------------------------------------------------------------------
# 事件类型（对齐 Game.EventType 中有日志语义的部分）
# ---------------------------------------------------------------------------
class Ev:
    COMBAT_START = "combat_start"
    COMBAT_END = "combat_end"
    STACK_GAIN = "stack_gain"
    STACK_LOSE = "stack_lose"
    STACK_TIMEOUT = "stack_timeout"
    ATTACK = "attack"
    CRITICAL = "critical"
    MISSED = "missed"
    SPIKES = "spikes"
    VAMPIRISM = "vampirism"
    HEAL = "heal"
    UNHEALING = "unhealing"
    STAMINA_GAIN = "stamina_gain"
    STAMINA_USE = "stamina_use"
    STAMINA_DRAIN = "stamina_drain"
    OUT_OF_STAMINA = "out_of_stamina"
    STUN = "stun"
    STUN_END = "stun_end"
    STUN_RESISTED = "stun_resisted"
    INVULNERABLE_START = "invulnerable_start"
    INVULNERABLE_END = "invulnerable_end"
    BLOCK_BREAK = "block_break"
    CRIT_RESISTED = "crit_resisted"
    TICK = "tick"
    FATIGUE_START = "fatigue_start"
    FATIGUE_DAMAGE = "fatigue_damage"
    ITEM_ACTIVATE = "item_activate"
    DEATH = "death"
    REINCARNATE = "reincarnate"
    DODGE = "dodge"
    LOSE_HEALTH = "lose_health"


# buff 类型 -> 原版显示名（对齐 Game.EventType 名称；中文为翻译）
BUFF_DISPLAY = {
    100: ("Block", "格挡"),
    101: ("Lucky", "幸运"),
    102: ("Regeneration", "再生"),
    103: ("Vampirism", "吸血"),
    104: ("Spikes", "反伤"),
    105: ("Mana", "法力"),
    106: ("Empower", "充能"),
    107: ("Heat", "热量"),
    108: ("Poison", "中毒"),
    109: ("Blind", "致盲"),
    110: ("Cold", "寒冷"),
}

# 原版 isBuff / isDebuff（Game.EventType.Block..Heat 为 buff；Poison..Cold 为 debuff）
def _is_buff(t: int) -> bool:
    return 100 <= t <= 107

def _is_debuff(t: int) -> bool:
    return 108 <= t <= 110


# ---------------------------------------------------------------------------
# 原版 LOG 模板（en / zh）。占位符：{origin} {damage} {amount} {buff} {debuff}
# {duration} {stamina} {health} {counter} {item}
# 键为渲染时计算出的「变体族」，buffs 用 {buff}、debuffs 用 {debuff} 占位。
# ---------------------------------------------------------------------------
TEMPLATES = {
    # —— 激活 / 攻击 / 命中 ——
    "Activation":        ("{origin} activated.", "{origin} 激活。"),
    "DealDamage":        ("Dealt {damage} damage ({origin}).", "造成{damage}点伤害（{origin}）。"),
    "CriticalDamage":    ("Dealt {damage} critical damage ({origin}).", "造成{damage}点暴击伤害（{origin}）。"),
    "MissedAttack":      ("Missed an attack ({origin}).", "攻击落空（{origin}）。"),
    # —— 治疗 / 受伤 ——
    "Health":            ("Regenerated {amount} health ({origin}).", "恢复{amount}点生命值（{origin}）。"),
    "LoseHealth":        ("Lost {amount} health ({origin}).", "失去{amount}点生命值（{origin}）。"),
    # —— 体力 ——
    "Stamina":           ("Regenerated {stamina} stamina ({origin}).", "恢复{stamina}点耐力（{origin}）。"),
    "DrainStamina":      ("Removed {stamina} stamina ({origin}).", "消耗{stamina}点耐力（{origin}）。"),
    "OutofStamina":      ("Out of stamina ({origin}).", "耐力耗尽（{origin}）。"),
    # —— 眩晕 / 无敌 ——
    "Stun":              ("Stunned for {duration}s ({origin}).", "被眩晕{duration}秒（{origin}）。"),
    "StunResisted":      ("Stun resisted ({origin}).", "眩晕被抵挡（{origin}）。"),
    "InvulnerableStart": ("Gained invulnerability for {duration}s ({origin}).", "获得了{duration}s内无敌（{origin}）。"),
    "InvulnerableEnd":   ("Invulnerability ended ({origin}).", "无敌结束（{origin}）。"),
    # —— 伤害增益 / 复活 / 狂怒 / 疲劳 / 胜负 ——
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
    "GAIN_BUFF":         ("Gained {amount} {buff} ({origin}).", "获得{amount}层 {buff}（{origin}）。"),
    "GAIN_BUFF_TEMP":    ("Gained {amount} {buff} for {duration}s ({origin}).", "获得了{amount} {buff}，持续{duration}秒（{origin}）。"),
    "GAIN_DEBUFF":       ("Inflicted {amount} {debuff} ({origin}).", "施加{amount}层 {debuff}（{origin}）。"),
    "GAIN_DEBUFF_SELF":  ("Self-inflicted {amount} {debuff} ({origin}).", "对自身施加{amount}层 {debuff}（{origin}）。"),
    "GAIN_DEBUFF_TEMP":  ("Inflicted {amount} {debuff} for {duration}s ({origin}).", "施加了{amount} {debuff}，持续{duration}秒（{origin}）。"),
    "GAIN_DEBUFF_SELF_TEMP": ("Self-inflicted {amount} {debuff} for {duration}s ({origin}).", "对自己施加了{amount} {debuff}，持续{duration}秒（{origin}）。"),
    "LOSE_BUFF":         ("Lost {amount} {buff} ({origin}).", "失去{amount}层 {buff}（{origin}）。"),
    "LOSE_DEBUFF":       ("Cleansed {amount} {debuff} ({origin}).", "净化{amount}层 {debuff}（{origin}）。"),
    "USE_BUFF":          ("Used {amount} {buff} ({origin}).", "消耗{amount}层 {buff}（{origin}）。"),
    "BUFF_TIMEOUT":      ("{amount} {buff} timed out ({origin}).", "{amount} {buff}持续时间结束（{origin}）。"),
    "NULLIFY_BUFF":      ("{amount} {buff} nullified ({origin}).", "{amount} {buff}被无效化（{origin}）。"),
    "NULLIFY_DEBUFF":    ("Nullified {amount}{debuff}", "{amount}{debuff}无效"),
    "RESIST_DEBUFF":     ("{amount} {debuff} resisted ({origin}).", "{amount} {debuff}被抵挡（{origin}）。"),
    "REFLECT_RESIST":    ("{amount} reflected {debuff} resisted ({origin}).", "反弹的{amount} {debuff}被抵挡（{origin}）。"),
    "REFLECT_BUFF":      ("Reflected {amount}{buff}", "反弹{amount} {buff}"),
    "REFLECT_DEBUFF":    ("{amount} {debuff} reflected ({origin}).", "{amount} {debuff}被反弹（{origin}）。"),
    "REFLECT_DEBUFF_TEMP": ("{amount} {debuff} reflected for {duration}s ({origin}).", "{amount} {debuff}在{duration}s内被反弹（{origin}）。"),
    "PROTECT_BUFF":      ("{amount} {buff} protected from removal ({origin}).", "对{amount} {buff}的移除被保护（{origin}）。"),
    "PROTECT_DEBUFF":    ("{amount} {debuff} protected from cleansing ({origin}).", "对{amount} {debuff}的净化被保护（{origin}）。"),
}


class CombatEvent:
    """对齐 CombatEvent.gd：id / timestamp / parentEvent / origin / type / target / params"""

    __slots__ = ("id", "t", "type", "actor", "target", "origin", "params",
                 "parent", "depth", "buff_type")

    def __init__(self, eid: int, t: float, etype: str,
                 actor: Optional[str] = None, target: Optional[str] = None,
                 origin: Optional[str] = None, params: Optional[Dict] = None,
                 parent: Optional[int] = None, depth: int = 0, buff_type=None):
        self.id = eid
        self.t = round(t, 3)
        self.type = etype
        self.actor = actor
        self.target = target
        self.origin = origin
        self.params = params or {}
        self.parent = parent
        self.depth = depth
        self.buff_type = buff_type

    def get_origin(self):
        """getOrigin — 行为脚本事件来源访问（对齐 GDScript）"""
        return self.origin

    def to_dict(self) -> Dict[str, Any]:
        d = {"id": self.id, "t": round(self.t, 3), "type": self.type,
             "depth": self.depth}
        if self.actor is not None:
            d["actor"] = self.actor
        if self.target is not None:
            d["target"] = self.target
        if self.origin is not None:
            d["origin"] = self.origin
        if self.buff_type is not None:
            d["buff_type"] = self.buff_type
        if self.params:
            d["params"] = self.params
        if self.parent is not None:
            d["parent"] = self.parent
        return d


class CombatLog:
    """对齐 CombatLog.gd：事件收集 + 文本渲染（复刻原版格式）"""

    def __init__(self, combat_delay: float = 2.5, tick_rate: int = 60, lang: str = "en"):
        self.combat_delay = combat_delay
        self.tick_rate = tick_rate
        self.current_time: float = 0.0
        self.lang = lang
        self.events: List[CombatEvent] = []
        self._next_id = 0
        self._by_id: Dict[int, CombatEvent] = {}
        self._parent_stack: List[int] = []   # 当前激活链（嵌套触发时还原父节点）
        self.warnings: List[str] = []        # 行为/引擎告警（不阻断战斗）

    def warn(self, msg: str):
        self.warnings.append(msg)
        try:
            import sys
            print(f"[warn] {msg}", file=sys.stderr)
        except Exception:
            pass

    # ---------------- 父/子事件链接 ----------------
    def begin_activation(self, event_id: Optional[int]):
        self._parent_stack.append(event_id)

    def end_activation(self):
        if self._parent_stack:
            self._parent_stack.pop()

    # ---------------- 事件创建 ----------------
    def _emit(self, t: float, etype: str, actor=None, target=None,
              origin=None, params=None, parent=None, depth=None,
              buff_type=None) -> CombatEvent:
        if parent is None and self._parent_stack:
            parent = self._parent_stack[-1]
        if depth is None:
            if parent is None:
                depth = 0
            else:
                depth = self._by_id[parent].depth + 1
        ev = CombatEvent(self._next_id, t, etype, actor, target, origin,
                         params, parent, depth, buff_type)
        self._next_id += 1
        self._by_id[ev.id] = ev
        self.events.append(ev)
        return ev

    def combat_start(self, t: float):
        return self._emit(t, Ev.COMBAT_START)

    def combat_end(self, t: float, winner: str, reason: str):
        return self._emit(t, Ev.COMBAT_END, params={"winner": winner, "reason": reason})

    def stack_gain(self, t, actor, target, origin, buff, amount,
                   permanent=True, duration=None, parent=None, resisted=False,
                   reflected=False, protected=False, buff_type=None):
        p = {"buff": buff, "amount": amount, "permanent": permanent}
        if duration is not None:
            p["duration"] = round(duration, 3)
        if resisted:
            p["resisted"] = True
        if reflected:
            p["reflected"] = True
        if protected:
            p["protected"] = True
        return self._emit(t, Ev.STACK_GAIN, actor, target, origin, p, parent, buff_type=buff_type)

    def stack_lose(self, t, actor, target, origin, buff, amount, used=False,
                   buff_type=None, parent=None):
        p = {"buff": buff, "amount": amount, "used": used}
        return self._emit(t, Ev.STACK_LOSE, actor, target, origin, p, parent, buff_type=buff_type)

    def stack_timeout(self, t, actor, target, origin, buff, amount, buff_type=None):
        return self._emit(t, Ev.STACK_TIMEOUT, actor, target, origin,
                          {"buff": buff, "amount": amount}, buff_type=buff_type)

    def attack(self, t, actor, target, origin, damage, health_damage,
               hit=True, critical=False, block_absorbed=0, parent=None):
        return self._emit(t, Ev.CRITICAL if critical else Ev.ATTACK, actor, target, origin,
                          {"damage": int(round(damage)),
                           "health_damage": int(round(health_damage)),
                           "block_absorbed": int(round(block_absorbed))},
                          parent)

    # spikes 反伤：作为一次「DealDamage」，origin 记为 Spikes（子事件挂到当前激活上）
    def spike_damage(self, t, actor, target, damage, parent=None):
        return self._emit(t, Ev.ATTACK, actor, target, "Spikes",
                          {"damage": int(round(damage))}, parent)

    def missed(self, t, actor, target, origin, parent=None):
        return self._emit(t, Ev.MISSED, actor, target, origin, {}, parent)

    def dodge(self, t, actor, target, origin, parent=None):
        # 原版没有独立的 dodge 行，归并到 MissedAttack
        return self._emit(t, Ev.MISSED, actor, target, origin, {}, parent)

    def heal(self, t, actor, amount, overheal=0, origin=None, parent=None):
        return self._emit(t, Ev.HEAL, actor, None, origin,
                          {"amount": int(round(amount)), "overheal": int(round(overheal))}, parent)

    def lose_health(self, t, actor, amount, origin=None, parent=None):
        return self._emit(t, Ev.LOSE_HEALTH, actor, None, origin,
                          {"amount": int(round(amount))}, parent)

    def unhealing(self, t, actor, target, damage, parent=None):
        return self._emit(t, Ev.UNHEALING, actor, target, "Unhealing",
                          {"damage": int(round(damage))}, parent)

    def stamina_gain(self, t, actor, amount, origin=None):
        return self._emit(t, Ev.STAMINA_GAIN, actor, None, origin,
                          {"stamina": round(amount, 2)})

    def stamina_use(self, t, actor, amount, origin=None):
        return self._emit(t, Ev.STAMINA_USE, actor, None, origin,
                          {"stamina": round(amount, 2)})

    def stamina_drain(self, t, actor, target, amount, origin=None):
        return self._emit(t, Ev.STAMINA_DRAIN, actor, target, origin,
                          {"stamina": round(amount, 2)})

    def out_of_stamina(self, t, actor, origin):
        return self._emit(t, Ev.OUT_OF_STAMINA, actor, None, origin, {})

    def stun(self, t, actor, target, duration, origin=None, parent=None):
        return self._emit(t, Ev.STUN, actor, target, origin,
                          {"duration": round(duration, 2)}, parent)

    def stun_end(self, t, actor):
        return self._emit(t, Ev.STUN_END, actor, None, None, {})

    def stun_resisted(self, t, actor, target, origin=None):
        return self._emit(t, Ev.STUN_RESISTED, actor, target, origin, {})

    def crit_resisted(self, t, actor, target):
        return self._emit(t, Ev.CRIT_RESISTED, actor, target, None, {})

    def invulnerable_start(self, t, actor, duration, origin=None):
        return self._emit(t, Ev.INVULNERABLE_START, actor, None, origin,
                          {"duration": round(duration, 2)})

    def invulnerable_end(self, t, actor, origin=None):
        return self._emit(t, Ev.INVULNERABLE_END, actor, None, origin, {})

    def fatigue_start(self, t):
        return self._emit(t, Ev.FATIGUE_START)

    def fatigue_damage(self, t, counter, player_damage, opponent_damage):
        return self._emit(t, Ev.FATIGUE_DAMAGE, params={
            "counter": counter, "player_damage": player_damage,
            "opponent_damage": opponent_damage})

    def item_activate(self, t, actor, origin):
        return self._emit(t, Ev.ITEM_ACTIVATE, actor, None, origin, {})

    def death(self, t, actor):
        return self._emit(t, Ev.DEATH, actor, None, None, {})

    def reincarnate(self, t, actor, amount, origin=None):
        return self._emit(t, Ev.REINCARNATE, actor, None, origin, {"amount": amount})

    # ---------------- 渲染 ----------------
    def to_dict(self) -> List[Dict[str, Any]]:
        return [e.to_dict() for e in self.events]

    def _stack_variant(self, p: Dict[str, Any], is_buff: bool, is_loss: bool = False) -> str:
        """复刻 CombatEvent.asText 的 buff/debuff 后缀逻辑。

        原版用单个带符号 amount 的事件区分增减：amount<0 即 LOSE。
        本模拟器把增减拆成 STACK_GAIN / STACK_LOSE，因此由调用方通过
        is_loss 显式告知「这是一次失去」（原版的 amount<0 情形）。
        """
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
        # gain
        if is_buff:
            return "GAIN_BUFF_TEMP" if "duration" in p else "GAIN_BUFF"
        # debuff
        variant = "GAIN_DEBUFF"
        if p.get("actor_is_target"):
            variant += "_SELF"
        if "duration" in p:
            variant += "_TEMP"
        return variant

    def _fmt_duration(self, d) -> str:
        # 原版伤害/时间多为整数显示
        if d is None:
            return ""
        if isinstance(d, float) and d.is_integer():
            return str(int(d))
        return f"{d:.2f}".rstrip("0").rstrip(".")

    def _render_event(self, e: CombatEvent, lang: str) -> Optional[str]:
        p = e.params
        origin = e.origin or ""
        # 物品名国际化：优先游戏官方中文名（i18n），无则英文
        if lang == "zh" and origin:
            origin = i18n_zh_name(origin)
        # 事件内嵌的 buff/debuff/物品名参数翻译
        if lang == "zh" and p.get("buff"):
            p = dict(p)
            from .i18n import zh_name as _zn
            for k in ("buff", "debuff", "item_name"):
                if p.get(k):
                    p[k] = _zn(p[k])

        # 原版无对应日志行的事件，抑制文本（仍保留在 JSON）
        if e.type in (Ev.COMBAT_START, Ev.STUN_END, Ev.DEATH, Ev.TICK,
                      Ev.SPIKES, Ev.VAMPIRISM, Ev.BLOCK_BREAK):
            return None

        if e.type == Ev.COMBAT_END:
            return self._t("Win" if p.get("winner") == "player" else "Loss", {}, lang)

        if e.type == Ev.ITEM_ACTIVATE:
            return self._t("Activation", {"origin": origin}, lang)

        if e.type in (Ev.ATTACK, Ev.CRITICAL):
            if e.type == Ev.CRITICAL:
                return self._t("CriticalDamage", {"damage": p["damage"], "origin": origin}, lang)
            return self._t("DealDamage", {"damage": p["damage"], "origin": origin}, lang)

        if e.type == Ev.MISSED:
            return self._t("MissedAttack", {"origin": origin}, lang)

        if e.type == Ev.HEAL:
            return self._t("Health", {"amount": p["amount"], "origin": origin}, lang)

        if e.type == Ev.LOSE_HEALTH:
            return self._t("LoseHealth", {"amount": p["amount"], "origin": origin}, lang)

        if e.type == Ev.UNHEALING:
            return self._t("LoseHealth", {"amount": p["damage"], "origin": origin}, lang)

        if e.type == Ev.STAMINA_GAIN:
            return self._t("Stamina", {"stamina": p["stamina"], "origin": origin}, lang)

        if e.type in (Ev.STAMINA_USE, Ev.STAMINA_DRAIN):
            return self._t("DrainStamina", {"stamina": p["stamina"], "origin": origin}, lang)

        if e.type == Ev.OUT_OF_STAMINA:
            return self._t("OutofStamina", {"origin": origin}, lang)

        if e.type == Ev.STUN:
            return self._t("Stun", {"duration": self._fmt_duration(p["duration"]),
                                    "origin": origin}, lang)

        if e.type == Ev.STUN_RESISTED:
            return self._t("StunResisted", {"origin": origin}, lang)

        if e.type == Ev.CRIT_RESISTED:
            return self._t("CritResisted", {}, lang)

        if e.type == Ev.INVULNERABLE_START:
            return self._t("InvulnerableStart", {"duration": self._fmt_duration(p["duration"]),
                                                "origin": origin}, lang)

        if e.type == Ev.INVULNERABLE_END:
            return self._t("InvulnerableEnd", {"origin": origin}, lang)

        if e.type == Ev.REINCARNATE:
            return self._t("Reincarnate", {"health": p["amount"], "origin": origin}, lang)

        if e.type == Ev.FATIGUE_START:
            return self._t("FatigueStart", {}, lang)

        if e.type == Ev.FATIGUE_DAMAGE:
            return self._t("FatigueDamage", {"counter": p["counter"]}, lang)

        # 增减益栈事件
        if e.type in (Ev.STACK_GAIN, Ev.STACK_LOSE, Ev.STACK_TIMEOUT):
            bt = e.buff_type
            disp_en, disp_zh = BUFF_DISPLAY.get(bt, (e.params.get("buff", "?"), e.params.get("buff", "?")))
            is_buff = _is_buff(bt) if bt is not None else True
            is_loss = (e.type == Ev.STACK_LOSE)
            variant = self._stack_variant(p, is_buff, is_loss)
            fp = {"amount": abs(p.get("amount", 0)),
                  "buff": disp_en, "debuff": disp_en,
                  "duration": self._fmt_duration(p.get("duration")),
                  "origin": origin}
            if lang == "zh":
                fp["buff"], fp["debuff"] = disp_zh, disp_zh
            return self._t(variant, fp, lang)

        # 兜底（理论上不会命中）
        return self._t("Activation" if False else "DealDamage", {}, lang)

    def _t(self, key: str, fp: Dict[str, Any], lang: str) -> str:
        en, zh = TEMPLATES.get(key, ("{%s}" % key, "{%s}" % key))
        tmpl = zh if lang == "zh" else en
        try:
            text = tmpl.format(**fp)
        except (KeyError, IndexError):
            text = tmpl
        # 去掉因占位符为空产生的 () / ( ) / （）/（） 残留；以及由此留下的 " ." 尾随空格
        text = text.replace("( )", "").replace("()", "")
        text = text.replace("（ ）", "").replace("（）", "").replace(" .", ".")
        return text

    def to_text(self, lang: Optional[str] = None, show_buffs: bool = True,
                dual: bool = True) -> str:
        """复刻原版文本：深度0 = ``x.xx:  ``，子事件 = ``   > `` 缩进。

        dual=True 时同时显示双方数据：每行带 [玩家]/[对手]（zh）或 [P]/[O]（en）侧标，
        子事件继承父事件的侧标；全局事件（胜负/疲劳）无侧标。
        """
        lang = lang or self.lang
        if lang == "zh":
            side_tag = {"P": "[玩家] ", "O": "[对手] "}
        else:
            side_tag = {"P": "[P] ", "O": "[O] "}
        lines = []
        sides: Dict[int, Optional[str]] = {}
        for e in self.events:
            # 侧标：事件 actor 优先；子事件继承父事件
            if e.actor == "player":
                side = "P"
            elif e.actor == "opponent":
                side = "O"
            elif e.parent is not None:
                side = sides.get(e.parent)
            else:
                side = None
            sides[e.id] = side
            text = self._render_event(e, lang)
            if not text:
                continue
            tag = side_tag[side] if (dual and side) else ""
            if e.depth == 0:
                line = f"{e.t:.2f}" + ":  " + tag + text
            else:
                line = "  " * e.depth + "> " + tag + text
            lines.append(line)
        return "\n".join(lines)
