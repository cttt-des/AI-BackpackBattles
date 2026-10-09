# -*- coding: utf-8 -*-
"""canonical_events.py — 事件规范化 + HP 账本（docs/consistency_workflow.md §3 Phase 0 / M1）。

三种事件流 → 统一规范事件 (t, type, side, origin_key, params) + 双方 HP 曲线/终值。

来源与格式（均已逐一核对）：
  truth  dist/output/combat_logs/<组>/<组名>.json
         字段 t/type/type_name/target/side/origin/params；origin 可为 null
         （导出逻辑：core/combatlog_reader.py:549-637）
  trace  gd_core_test/event_trace.txt
         每行 `id|type|depth|origin|target|params`（gd_core_test/LineupBattle.gd:153-161），
         `## <A>|<B>|<seed>` 起头新开一局。注意：首字段是**事件号**不是时间——
         轨迹不含时间戳，本工具以事件号充当 t，曲线按事件粒度输出。
  sim    模拟器 log.to_dict() 的 JSON（simulator/events.py:162-179）
         字段 t/type/actor/target/origin/params（可包 {events:[...]} 或裸数组）；
         actor 名 'player'/'opponent' 在此归一为 'P'/'O'。

事件语义真值（HP 账本归一决策的依据）：
  · Game.EventType 枚举：decompiled_full/Core/Game.gd:441-478。
  · HP 只在四处变动（decompiled_full/Core/Character.gd）：
      takeDamage（:587-599，curHealth -= healthDamage）、heal（:578-585）、
      loseHealth（:644-648）、changeMaxHealthTemporary（:892-896，curHealth += amount）。
  · DealDamage/CriticalDamage 的 params.damage 是**格挡前**口径：实扣 healthDamage
    在 Character.gd:587-596 才扣除 Block。HP 账本统一按 params.damage 记借
    （真值流没有 healthDamage；Block 吸收重建属 Phase 3 不变量 I4 的范畴）。
  · 疲劳/中毒/尖刺/不治的跳伤落账位置**按来源不同**：
      真值/轨迹 → DealDamage/CriticalDamage（伤害源 origin：Unhealing=98 /
        Fatigue=99 / Spikes=104 / Poison=108，CoreDamageSource.Type 枚举
        gd_core/CoreDamageSource.gd:18-26），走 createEvent_Damage
        （target=**非受害方**，gd_core/CoreCombatLog.gd:88-97）；
      模拟流 → 中毒 lose_health（simulator/character.py:374-376）、不治
        unhealing（character.py:647）、疲劳 fatigue_damage（combat.py:370，
        双方各记一跳）、尖刺 attack origin="Spikes"（events.py:266-268）。
  · Fatigue/Unhealing/Poison/Spikes/Regeneration/Vampirism **类型**的事件是层数
    施加/消耗（createEvent_Stack，不动 HP）——按字面把层数当 HP 变动会双计，
    故层数事件不入账；设计文档「Poison/Spikes 记借、Regeneration 记贷」的意图
    由上述跳伤/跳血事件满足。吸血/恢复跳血落为 Health（origin=Vampirism/Regeneration）。
  · 受害方推导：
      truth  物品 origin → side=攻击方；伤害源 origin → side 按 target 兜底
             （combatlog_reader.py:635-636，getMainActor 语义）= 非受害方。
             两路统一：受害方 = 1 - side。
      trace  物品 origin 走 createEvent_Attack：target=受害方
             （gd_core/CoreCombatLog.gd:66-72），side=origin 物品 ownerType；
             伤害源 origin 走 createEvent_Damage：target=非受害方 →
             受害方 = 1 - target。
             ★ SelfDamage 特例（CoreCombatLog.gd:67-68
               attackedCharacter = character）：target=攻击者自己——
               受害方推导不受影响（受害仍=target），但 side 必须取
               ownerType 而非 1-受害方，否则记成对方。v1.1.7 语料内无
               物品实际施加 SelfDamage（全库仅 CombatLog.gd 分支与
               DamageSource 枚举两处出现），此为防御性处理。
      sim    attack/critical：actor=攻击方 → 受害方 = 1 - actor；
             unhealing：target=受害方（simulator/events.py:285-287）。
  · TemporaryMaxHealth 记贷（Character.gd:894-895 curHealth += amount），
    方 = origin 物品所属方（ownerType：PlayerInventory=1→P、Opponent=3→O，
    decompiled_full/Items/Item.gd:17-31）。
    ★ 已知缺口（仅纯 Python simulator 路径）：simulator/character.py:1167-1172
      的 change_max_health_temporary **不发事件** → 纯 Python 流重建的 HP 会
      漏掉临时上限加血。gd_core 引擎产出的模拟日志**含** temporary_max_health
      事件（如 output/sim_run/*_seed1_log.json 有 12 条），不受此缺口影响。
      账本如实暴露该偏差，不在本工具内圆谎。
  · Reincarnate 不入账（_hp_delta 返回 None）：语料内 0 条、模拟器无发射点，
    但**一旦出现即账本失效**——HP 停在 0 会被误判 hp_zero 终止。
  · LoseHealth：真值/轨迹 amount 为负（createEvent_LoseHealth(-amount)，
    gd_core/CoreCombatLog.gd:116-121），模拟 amount 为正
    （simulator/character.py:376）→ 统一记 -|amount|。
  · 回血量 = params.amount，不扣过量治疗（真值 Health 无 overheal 参数，
    三来源统一口径，均按满值记贷）。
  · 初始 HP：--truth 从组目录阵容 JSON（character+round）按
    simulator/combat.py:117-130 同一成长公式推；--sim 优先 setup.max_health；
    --trace 优先从 gd_core_test/LineupFixture.gd 的 LINEUPS 按局头阵容名推导
    （fixture 阵容 health=25.0，LineupBattle.gd:258 setMaxHealth(lu["health"])）；
    推导不出时回退 --initial-hp（默认 100,100）。终值超过初始 HP 时 CLI 告警。
  · 截断与终止：HP 夹在 ≥0；一方归 0 → 终止（reason=hp_zero）；否则末事件
    t > time_limit → timeout；否则 completed。
  · ★ 验收口径（Phase 0 退出标准的边界）：账本按格挡前 params.damage 记借
    （真值流无 healthDamage 参数），**重建终值 ≠ 结算 result 的实际 HP**
    （实测 seed1：账本 P=236 vs result 675；归因于 Block 吸收未重建）。
    「同一实录三种来源解析出一致的 HP 终值」只在**各流内部同口径自洽**上
    成立，不与结算 HP 对齐；与结算 HP 对齐需 Block 重建（Phase 3 / I4）。
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path
from typing import Any, Dict, List, Optional

REPO_ROOT = Path(__file__).resolve().parents[1]

# ── Game.EventType（decompiled_full/Core/Game.gd:441-478；与
#    core/combatlog_reader.py EVENT_TYPES 同表） ─────────────────────────────
EVENT_TYPES: Dict[int, str] = {
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

# 伤害源 origin（DamageSource.Type 整数）在轨迹里记作 i<N>；这些 N 即判定
# 「物品 origin（受害方=target）vs 伤害源 origin（受害方=1-target）」的依据。
_ITEM_ORIGIN_PREFIXES = ("it:", "gem(")
_OWNER_TYPE_TO_SIDE = {1: "P", 3: "O"}  # decompiled_full/Items/Item.gd:17-31

SIM_ACTOR_TO_SIDE = {"player": "P", "opponent": "O"}

# 模拟器 Ev 常量（simulator/events.py:26-56）→ 规范类型名（真值 type_name 口径）
SIM_TYPE_MAP: Dict[str, str] = {
    "attack": "DealDamage",
    "critical": "CriticalDamage",
    "missed": "MissedAttack",
    "heal": "Health",
    "lose_health": "LoseHealth",
    "unhealing": "Unhealing",
    "fatigue_damage": "Fatigue",   # 双方各记一跳：params.player_damage / opponent_damage
    "item_activate": "Activation",
    "reincarnate": "Reincarnate",
    "temporary_max_health": "TemporaryMaxHealth",
}

# params.buff 名（simulator/buff.py:34-41 BuffType.NAMES）→ EventType 数字。
# 仅纯 Python simulator 的层数事件带该名；gd_core 引擎的层数事件两样皆无
# （无 buff_type 也无 params.buff，实测 output/sim_run/* 335+ 条），落通用 Stack。
_SIM_BUFF_NAMES: Dict[str, int] = {
    "block": 100, "lucky": 101, "regen": 102, "regeneration": 102,
    "vampirism": 103, "spikes": 104, "mana": 105, "empower": 106,
    "heat": 107, "poison": 108, "blind": 109, "cold": 110,
}

HP_LOSS_TYPES = ("DealDamage", "CriticalDamage")
HEAL_TYPES = ("Health",)


def _opp(side: Optional[str]) -> Optional[str]:
    if side not in ("P", "O"):
        raise ValueError(f"受害方推导需要 P/O，得到 {side!r}")
    return "O" if side == "P" else "P"


def _tick(t: float) -> float:
    """时间戳对齐：游戏 tick 60Hz 取整（docs/consistency_workflow.md §3 Phase 0）。"""
    return round(t * 60) / 60.0


def _side_from_owner_type(owner_type: int) -> Optional[str]:
    if owner_type not in _OWNER_TYPE_TO_SIDE:
        raise ValueError(f"未知 ownerType {owner_type!r}（应为 1=PlayerInventory / 3=Opponent）")
    return _OWNER_TYPE_TO_SIDE[owner_type]


def _origin_owner_side(origin_key: Optional[str]) -> Optional[str]:
    """轨迹 origin 串 → 所属方。`it:<名>~<ownerType>~<格>` / `gem(<宿主>~<槽>)`
    （gd_core_test/LineupBattle.gd:144-145）；宝石宿主递归复用同一编码。"""
    if not origin_key:
        return None
    if origin_key.startswith("it:"):
        parts = origin_key.split("~")
        if len(parts) < 2 or not parts[1].lstrip("-").isdigit():
            raise ValueError(f"轨迹 origin 缺 ownerType：{origin_key!r}")
        return _side_from_owner_type(int(parts[1]))
    if origin_key.startswith("gem(") and origin_key.endswith(")"):
        return _origin_owner_side(origin_key[4:-1])
    return None


# ═══════════════════════════ 来源 a：真值实录 ═══════════════════════════

def parse_truth_events(events: List[Dict[str, Any]]) -> List[Dict[str, Any]]:
    """真值 JSON 的 events 数组 → 规范事件流。fail-fast：缺字段/未知 target 即抛。"""
    out: List[Dict[str, Any]] = []
    for seq, e in enumerate(events):
        try:
            t = _tick(float(e["t"]))
        except (KeyError, TypeError, ValueError) as exc:
            raise ValueError(f"真值事件#{seq} 时间戳异常: {e.get('t')!r}") from exc
        type_name = e.get("type_name")
        if not type_name:
            raise ValueError(f"真值事件#{seq} 缺 type_name: {e!r}")
        tgt = e.get("target")
        if tgt is None:
            target_side = None
        elif isinstance(tgt, int) and tgt in (0, 1):
            target_side = "P" if tgt == 0 else "O"
        else:
            raise ValueError(f"真值事件#{seq} target 异常: {tgt!r}（应为 0/1/null）")
        origin = e.get("origin")
        origin_key = origin.get("name") if isinstance(origin, dict) else None
        side = e.get("side")
        if side not in ("P", "O", None):
            raise ValueError(f"真值事件#{seq} side 异常: {side!r}")
        out.append({
            "t": t, "seq": seq, "type": type_name, "side": side,
            "origin_key": origin_key, "target": target_side,
            "params": dict(e.get("params") or {}), "src": "truth",
        })
    return out


def parse_truth_group(group_dir: str | Path) -> Dict[str, Any]:
    """解析一组真值实录目录：主 JSON + 双方阵容（推初始 HP 用）。"""
    group_dir = Path(group_dir)
    main_path = group_dir / f"{group_dir.name}.json"
    if not main_path.is_file():
        raise FileNotFoundError(f"主日志不存在：{main_path}")
    data = json.loads(main_path.read_text(encoding="utf-8"))
    lineups: Dict[str, Optional[Dict[str, Any]]] = {}
    for side, tag in (("P", "Player"), ("O", "Opponent")):
        p = group_dir / f"{group_dir.name}.{tag}.json"
        lineups[side] = json.loads(p.read_text(encoding="utf-8")) if p.is_file() else None
    return {
        "path": str(main_path),
        "meta": data.get("meta", {}),
        "events": parse_truth_events(data.get("events") or []),
        "lineups": lineups,
    }


# ═══════════════════════════ 来源 b：gd_core 轨迹 ═══════════════════════════

def _decode_trace_value(tok: str) -> Any:
    """轨迹值解码（_ekey 编码，LineupBattle.gd:125-151）：
    i<N>→int、%.6f→float、T/F→bool、'-'→None，其余原样字符串。"""
    if tok == "-":
        return None
    if tok.startswith("i") and tok[1:].lstrip("-").isdigit():
        return int(tok[1:])
    if tok in ("T", "F"):
        return tok == "T"
    try:
        return float(tok)
    except ValueError:
        return tok


def _parse_trace_params(params_s: str, lineno: int) -> Dict[str, Any]:
    params: Dict[str, Any] = {}
    if params_s in ("", "-"):
        return params
    for tok in params_s.split(","):
        if "=" not in tok:
            raise ValueError(f"event_trace.txt 行{lineno} 参数段无法解析：{tok!r}")
        k, v = tok.split("=", 1)
        params[k] = _decode_trace_value(v)
    return params


def parse_trace(path: str | Path) -> List[Dict[str, Any]]:
    """gd_core_test/event_trace.txt → [{header, events:[规范事件]}]（每局一项）。

    行格式 `id|type|depth|origin|target|params`（LineupBattle.gd:160-161）；
    首字段为事件号，规范事件的 t 即取该号（轨迹无时间戳）。
    """
    fights: List[Dict[str, Any]] = []
    cur: Optional[Dict[str, Any]] = None
    text = Path(path).read_text(encoding="utf-8")
    for lineno, raw in enumerate(text.splitlines(), 1):
        line = raw.strip()
        if not line:
            continue
        if line.startswith("##"):
            cur = {"header": line[2:].strip(), "events": []}
            fights.append(cur)
            continue
        if cur is None:
            raise ValueError(f"event_trace.txt 行{lineno} 先于 ## 局头：{line!r}")
        parts = line.split("|")
        if len(parts) != 6:
            raise ValueError(f"event_trace.txt 行{lineno} 字段数 != 6：{line!r}")
        eid_s, etype_s, _depth_s, origin_s, target_s, params_s = parts
        if not eid_s.isdigit() or not etype_s.lstrip("-").isdigit():
            raise ValueError(f"event_trace.txt 行{lineno} id/type 非整数：{line!r}")
        etype = int(etype_s)
        type_name = EVENT_TYPES.get(etype, f"Type{etype}")
        origin_key: Optional[str] = None if origin_s == "-" else origin_s
        target_val = _decode_trace_value(target_s) if target_s != "-" else None
        target_side: Optional[str] = None
        if isinstance(target_val, int) and target_val in (0, 1):
            target_side = "P" if target_val == 0 else "O"
        elif target_val is not None:
            raise ValueError(f"event_trace.txt 行{lineno} target 异常：{target_s!r}（应为 i0/i1/-）")

        # side 归一（与真值 side=行为方 同语义）：
        #   伤害事件：target=受害方（物品 origin）或非受害方（伤害源 origin）
        #   其余有 target 的事件：target=受验方=行为方
        #   无 target 的事件（TemporaryMaxHealth 等）：origin ownerType 兜底
        if type_name in HP_LOSS_TYPES:
            if origin_key is None or target_side is None:
                raise ValueError(f"event_trace.txt 行{lineno} 伤害事件缺 origin/target：{line!r}")
            if origin_key.startswith(_ITEM_ORIGIN_PREFIXES):
                # createEvent_Attack：target=受害方；side=origin 物品 ownerType。
                # SelfDamage 特例（CoreCombatLog.gd:67-68）target=攻击者自己，
                # side 不能按 1-受害方 推——ownerType 是唯一可靠来源。
                victim = target_side
                side = _origin_owner_side(origin_key) or _opp(victim)
            else:
                # createEvent_Damage：target=非受害方（CoreCombatLog.gd:88-97）
                side = target_side
        elif target_side is not None:
            side = target_side
        else:
            side = _origin_owner_side(origin_key)

        cur["events"].append({
            "t": float(eid_s), "seq": int(eid_s), "type": type_name, "side": side,
            "origin_key": origin_key, "target": target_side,
            "params": _parse_trace_params(params_s, lineno), "src": "trace",
        })
    return fights


# ═══════════════════════════ 来源 c：Python 模拟事件流 ═══════════════════════════

def parse_sim_events(events: List[Dict[str, Any]]) -> List[Dict[str, Any]]:
    """模拟器 log.to_dict() JSON（数组或 {events:[...]}）→ 规范事件流。

    actor/target 名 'player'/'opponent' → 'P'/'O'；Ev 字符串类型 → 真值
    type_name 口径（stack_gain/stack_lose 按 buff_type 映射到 Block..Cold，
    与真值层数事件的 type_name 对齐）。
    """
    if isinstance(events, dict):
        events = events.get("events") or []
    out: List[Dict[str, Any]] = []
    for seq, e in enumerate(events):
        try:
            t = _tick(float(e["t"]))
        except (KeyError, TypeError, ValueError) as exc:
            raise ValueError(f"模拟事件#{seq} 时间戳异常: {e.get('t')!r}") from exc
        etype = e.get("type")
        if not isinstance(etype, str):
            raise ValueError(f"模拟事件#{seq} type 异常: {etype!r}")
        if etype in ("stack_gain", "stack_lose", "stack_timeout"):
            # 层数事件不入 HP 账本（_hp_delta 对 Block..Cold 均返回 None），
            # 故降级容错而非 fail-fast：buff_type（纯 Python 路径）→ params.buff
            # 名（simulator/buff.py:34-41）→ 通用 "Stack"（gd_core 引擎路径，
            # 实测 6/6 份 output/sim_run/*_log.json 两样皆无，335+ 条）。
            bt = e.get("buff_type")
            type_name = EVENT_TYPES.get(bt) if isinstance(bt, int) else None
            if type_name is None:
                buff = (e.get("params") or {}).get("buff")
                bt2 = _SIM_BUFF_NAMES.get(buff) if isinstance(buff, str) else None
                type_name = EVENT_TYPES.get(bt2, "Stack")
        else:
            type_name = SIM_TYPE_MAP.get(etype, etype)
        actor = e.get("actor")
        side = SIM_ACTOR_TO_SIDE.get(actor) if actor is not None else None
        if actor is not None and side is None:
            raise ValueError(f"模拟事件#{seq} actor 异常: {actor!r}（应为 player/opponent）")
        tgt = e.get("target")
        if tgt is None:
            target_side = None
        elif isinstance(tgt, str):
            target_side = SIM_ACTOR_TO_SIDE.get(tgt)
            if target_side is None:
                raise ValueError(f"模拟事件#{seq} target 异常: {tgt!r}（应为 player/opponent）")
        elif isinstance(tgt, int) and tgt in (0, 1):
            target_side = "P" if tgt == 0 else "O"
        else:
            raise ValueError(f"模拟事件#{seq} target 异常: {tgt!r}")
        origin = e.get("origin")
        origin_key = str(origin) if origin is not None else None
        out.append({
            "t": t, "seq": seq, "type": type_name, "side": side,
            "origin_key": origin_key, "target": target_side,
            "params": dict(e.get("params") or {}), "src": "sim",
        })
    return out


def load_sim_file(path: str | Path) -> Dict[str, Any]:
    """读模拟事件 JSON 文件；返回 {events(规范流), setup, meta}。"""
    data = json.loads(Path(path).read_text(encoding="utf-8"))
    if isinstance(data, list):
        return {"events": parse_sim_events(data), "setup": {}, "meta": {}}
    if isinstance(data, dict) and "events" in data:
        return {
            "events": parse_sim_events(data["events"]),
            "setup": data.get("setup") or {},
            "meta": data.get("meta") or {},
        }
    raise ValueError(f"模拟事件文件结构异常（应为数组或含 events 的对象）：{path}")


# ═══════════════════════════ 初始 HP ═══════════════════════════

def _load_characters_db() -> Dict[str, Dict[str, Any]]:
    path = REPO_ROOT / "assets" / "characters.json"
    data = json.loads(path.read_text(encoding="utf-8"))
    return data.get("characters", data)


def initial_hp_from_lineup(lineup: Dict[str, Any],
                           characters_db: Optional[Dict[str, Dict[str, Any]]] = None) -> float:
    """阵容 JSON（v4）→ 战斗初始 HP。

    对齐 simulator/combat.py:117-130：class_modifiers.health > characters.json >
    默认 25；health_override 直取；回合成长 i>=15:+30 / i>=10:+20 / i>=5:+15 /
    其余:+10（自第 2 回合起累计）。
    """
    if characters_db is None:
        characters_db = _load_characters_db()
    override = lineup.get("health_override")
    if override is not None:
        return float(override)
    mods = lineup.get("class_modifiers") or {}
    char = characters_db.get(lineup.get("character", "Adventurer"), {})
    base = mods.get("health", char.get("health", 25.0))
    rnd = int(lineup.get("round") or 1)
    hp = float(base)
    for i in range(2, rnd + 1):
        if i >= 15:
            hp += 30
        elif i >= 10:
            hp += 20
        elif i >= 5:
            hp += 15
        else:
            hp += 10
    return hp


def load_fixture_health(path: str | Path | None = None) -> Optional[Dict[str, float]]:
    """gd_core_test/LineupFixture.gd 的 LINEUPS → {阵容名: health}。

    fixture 阵容 health=25.0（LineupFixture.gd LINEUPS 常量），战斗入口
    setMaxHealth(int(lu["health"]))（LineupBattle.gd:258-259）——轨迹局的初始
    HP 必须按此推导，--initial-hp 的 100 默认值与该语料不符。
    解析失败（缺文件/结构不符）返回 None，由调用方回退 --initial-hp。
    """
    path = Path(path) if path else REPO_ROOT / "gd_core_test" / "LineupFixture.gd"
    if not path.is_file():
        return None
    text = path.read_text(encoding="utf-8")
    m0 = re.search(r"const LINEUPS\s*:?\s*=\s*\{", text)
    if not m0:
        return None
    start = m0.end() - 1  # 指向 "{"
    depth, end = 0, None
    for i in range(start, len(text)):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                end = i
                break
    if end is None:
        return None
    block = text[start + 1:end]
    starts = list(re.finditer(r'"(lineup_\w+)"\s*:\s*\{', block))
    out: Dict[str, float] = {}
    for i, m1 in enumerate(starts):
        seg_end = starts[i + 1].start() if i + 1 < len(starts) else len(block)
        m2 = re.search(r'"health"\s*:\s*([0-9.]+)', block[m1.end():seg_end])
        if m2:
            out[m1.group(1)] = float(m2.group(1))
    return out or None


# ═══════════════════════════ HP 账本 ═══════════════════════════

def _num(value: Any, what: str) -> float:
    if isinstance(value, bool) or not isinstance(value, (int, float)):
        raise ValueError(f"HP 账本需要数值参数：{what}={value!r}")
    return float(value)


def _damage_victim(ev: Dict[str, Any]) -> str:
    """DealDamage/CriticalDamage 的受害方（推导规则见模块 docstring）。"""
    src = ev["src"]
    if src in ("truth", "sim"):
        return _opp(ev["side"])          # side=攻击方/非受害方
    # trace：物品 origin → target 即受害方；伤害源 origin → target 是非受害方
    if ev["origin_key"] and ev["origin_key"].startswith(_ITEM_ORIGIN_PREFIXES):
        return ev["target"]
    return _opp(ev["target"])


def _hp_delta(ev: Dict[str, Any]) -> Optional[Dict[str, float]]:
    """单事件 → {side: HP 增量}；与 HP 无关的事件返回 None。"""
    t = ev["type"]
    p = ev["params"]
    if t in HP_LOSS_TYPES:
        dmg = _num(p.get("damage"), "damage")
        return {_damage_victim(ev): -dmg}
    if t == "Fatigue":
        # 模拟流的 fatigue_damage 一条事件双方各记一跳；轨迹/真值不产生该类型
        if "player_damage" in p and "opponent_damage" in p:
            return {"P": -_num(p["player_damage"], "player_damage"),
                    "O": -_num(p["opponent_damage"], "opponent_damage")}
        raise ValueError(f"Fatigue 事件缺 player_damage/opponent_damage（疲劳跳伤"
                         f"在真值/轨迹中应为 DealDamage(origin=Fatigue)）：{ev!r}")
    if t == "Unhealing":
        # 模拟流：actor=触发治疗的一方，target=受害方（simulator/events.py:285-287）
        if ev["src"] == "sim":
            if ev["target"] is None:
                raise ValueError(f"模拟 Unhealing 事件缺 target：{ev!r}")
            return {ev["target"]: -_num(p.get("damage"), "damage")}
        raise ValueError(f"Unhealing 类型事件不出现在真值/轨迹（不治反伤落为"
                         f"DealDamage origin=Unhealing=98）：{ev!r}")
    if t == "LoseHealth":
        amt = _num(p.get("amount"), "amount")
        victim = ev["target"] or ev["side"]  # truth/trace: target=受害方；sim: actor=受害方
        if victim not in ("P", "O"):
            raise ValueError(f"LoseHealth 事件无法定位受害方：{ev!r}")
        return {victim: -abs(amt)}
    if t in HEAL_TYPES:
        receiver = ev["target"] or ev["side"]  # truth/trace: target=受方；sim: actor=受方
        if receiver not in ("P", "O"):
            raise ValueError(f"Health 事件无法定位受方：{ev!r}")
        return {receiver: _num(p.get("amount"), "amount")}
    if t == "TemporaryMaxHealth":
        amt = _num(p.get("amount"), "amount")
        if ev["side"] not in ("P", "O"):
            raise ValueError(f"TemporaryMaxHealth 事件无法定位所属方：{ev!r}")
        return {ev["side"]: amt}  # Character.gd:894-895 curHealth += amount
    if t == "Reincarnate":
        # 复活把 HP 设为 amount（Character.gd:616-620；真值语料未出现，模拟器未发）
        return None
    return None


def build_hp_ledger(events: List[Dict[str, Any]], hp_p0: float, hp_o0: float,
                    time_limit: float = 180.0) -> Dict[str, Any]:
    """规范事件流 → 双方 HP 曲线与终值。

    返回 {
      initial: {"P","O"}, terminal: {"P","O"},
      reason: "hp_zero"|"timeout"|"completed", ended_t: float|None,
      curve_per_event: 每事件后的 [{t, hp_p, hp_o, event}...],
      curve_per_second: 逐秒曲线（仅当 t 为秒，即 truth/sim；trace 为 None）
    }
    """
    hp = {"P": float(hp_p0), "O": float(hp_o0)}
    curve_per_event: List[Dict[str, Any]] = []
    reason = "completed"
    ended_t: Optional[float] = None

    ordered = sorted(events, key=lambda e: (e["t"], e["seq"]))
    for ev in ordered:
        delta = _hp_delta(ev)
        if delta:
            for s, d in delta.items():
                if d:
                    hp[s] = max(0.0, hp[s] + d)  # 扣血截断在 0
        curve_per_event.append(
            {"t": ev["t"], "hp_p": hp["P"], "hp_o": hp["O"], "event": ev["type"]})
        if hp["P"] <= 0.0 or hp["O"] <= 0.0:
            reason, ended_t = "hp_zero", ev["t"]
            break

    if reason == "completed":
        last_t = curve_per_event[-1]["t"] if curve_per_event else 0.0
        if last_t > time_limit:
            reason, ended_t = "timeout", last_t

    curve_per_second: Optional[List[Dict[str, Any]]] = None
    if curve_per_event and any(e["src"] in ("truth", "sim") for e in events):
        curve_per_second = []
        last_t = curve_per_event[-1]["t"]
        idx = 0
        for sec in range(0, int(last_t) + 1):
            while (idx < len(curve_per_event)
                   and curve_per_event[idx]["t"] <= sec):
                idx += 1
            snap = curve_per_event[idx - 1] if idx > 0 else {
                "t": 0.0, "hp_p": hp_p0, "hp_o": hp_o0, "event": None}
            curve_per_second.append(
                {"t": sec, "hp_p": snap["hp_p"], "hp_o": snap["hp_o"]})
        # 末位补一行精确终值（末事件时刻）
        curve_per_second.append(
            {"t": last_t, "hp_p": curve_per_event[-1]["hp_p"],
             "hp_o": curve_per_event[-1]["hp_o"]})

    return {
        "initial": {"P": float(hp_p0), "O": float(hp_o0)},
        "terminal": {"P": hp["P"], "O": hp["O"]},
        "reason": reason, "ended_t": ended_t,
        "curve_per_event": curve_per_event,
        "curve_per_second": curve_per_second,
    }


# ═══════════════════════════ CLI ═══════════════════════════

def _print_curve(rows: List[Dict[str, Any]], label: str, show: bool, max_rows: int) -> None:
    tail = rows[-max_rows:]
    print(f"  {label}：{len(rows)} 点" + ("" if show else "（--curve 显示全部）"))
    for r in tail:
        ev = f"  [{r['event']}]" if r.get("event") else ""
        print(f"    t={r['t']:<8g} P={r['hp_p']:<10g} O={r['hp_o']:<10g}{ev}")


def _summary(ledger: Dict[str, Any], n_events: int, src: str) -> None:
    print(f"[{src}] 事件数：{n_events}")
    print(f"  初始 HP：P={ledger['initial']['P']:g}  O={ledger['initial']['O']:g}")
    print(f"  终值 HP：P={ledger['terminal']['P']:g}  O={ledger['terminal']['O']:g}")
    if (ledger["terminal"]["P"] > ledger["initial"]["P"] + 1e-9
            or ledger["terminal"]["O"] > ledger["initial"]["O"] + 1e-9):
        print("  ⚠ 终值超过初始 HP：初始 HP 可能与来源不符（--initial-hp / "
              "LineupFixture 推导），或过量治疗/临时上限被全额计入（见 docstring 口径说明）")
    ended = f"（t={ledger['ended_t']:g}）" if ledger['ended_t'] is not None else ""
    print(f"  终止原因：{ledger['reason']}{ended}")


def _parse_initial_hp(text: str) -> tuple:
    parts = text.split(",")
    if len(parts) != 2:
        raise ValueError(f"--initial-hp 需 <P,O> 两数：{text!r}")
    return float(parts[0]), float(parts[1])


def main(argv: Optional[List[str]] = None) -> int:
    if hasattr(sys.stdout, "reconfigure"):
        sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    ap = argparse.ArgumentParser(
        description="三种事件流 → 规范事件 + HP 账本（consistency_workflow Phase 0 / M1）")
    ap.add_argument("--selftest", action="store_true", help="内置最小样例自测")
    ap.add_argument("--truth", metavar="组目录", help="解析真值实录组并打印双方 HP 终值")
    ap.add_argument("--sim", metavar="events.json", help="解析模拟事件流并打印双方 HP 终值")
    ap.add_argument("--trace", metavar="event_trace.txt", help="解析 gd_core 轨迹并打印各局 HP 终值")
    ap.add_argument("--initial-hp", default="100,100", metavar="P,O",
                    help="sim/trace 的初始 HP（truth 自动从阵容推；默认 100,100）")
    ap.add_argument("--time-limit", type=float, default=180.0,
                    help="超时判定秒数（默认 180，对齐 CoreCombat.max_time 口径）")
    ap.add_argument("--curve", action="store_true", help="打印完整逐秒曲线（默认只打尾部）")
    ap.add_argument("--max-rows", type=int, default=12, help="曲线尾部最多打印行数（默认 12）")
    args = ap.parse_args(argv)

    if args.selftest:
        return _selftest()

    did_work = False
    if args.truth:
        did_work = True
        grp = parse_truth_group(args.truth)
        lineups = grp["lineups"]
        if lineups["P"] is None or lineups["O"] is None:
            raise FileNotFoundError(
                f"组目录缺阵容 JSON（{{.Player|.Opponent}}.json），无法推初始 HP：{args.truth}")
        p0 = initial_hp_from_lineup(lineups["P"])
        o0 = initial_hp_from_lineup(lineups["O"])
        ledger = build_hp_ledger(grp["events"], p0, o0, args.time_limit)
        print(f"真值：{grp['path']}  round={grp['meta'].get('round')} "
              f"result={grp['meta'].get('result')}")
        _summary(ledger, len(grp["events"]), "truth")
        if ledger["curve_per_second"]:
            _print_curve(ledger["curve_per_second"], "逐秒曲线", args.curve, args.max_rows)
    if args.sim:
        did_work = True
        sim = load_sim_file(args.sim)
        setup = sim["setup"]
        p_def, o_def = _parse_initial_hp(args.initial_hp)
        p0 = float(setup.get("player", {}).get("max_health", p_def))
        o0 = float(setup.get("opponent", {}).get("max_health", o_def))
        time_limit = float(sim["meta"].get("max_time", args.time_limit))
        ledger = build_hp_ledger(sim["events"], p0, o0, time_limit)
        print(f"模拟：{args.sim}")
        _summary(ledger, len(sim["events"]), "sim")
        if ledger["curve_per_second"]:
            _print_curve(ledger["curve_per_second"], "逐秒曲线", args.curve, args.max_rows)
    if args.trace:
        did_work = True
        fights = parse_trace(args.trace)
        p_def, o_def = _parse_initial_hp(args.initial_hp)
        fixture_health = load_fixture_health()
        if fixture_health is None:
            print("⚠ 未能从 gd_core_test/LineupFixture.gd 推导阵容 HP，回退 --initial-hp")
        print(f"轨迹：{args.trace}（{len(fights)} 局）")
        for i, fight in enumerate(fights, 1):
            names = fight["header"].split("|")
            p0 = o0 = None
            if fixture_health:
                p0 = fixture_health.get(names[0]) if len(names) > 0 else None
                o0 = fixture_health.get(names[1]) if len(names) > 1 else None
            if p0 is None:
                p0 = p_def
            if o0 is None:
                o0 = o_def
            ledger = build_hp_ledger(fight["events"], p0, o0, args.time_limit)
            print(f"—— 局 {i}: {fight['header']}")
            _summary(ledger, len(fight["events"]), "trace")
            _print_curve(ledger["curve_per_event"], "事件粒度曲线（轨迹无时间戳）",
                         args.curve, args.max_rows)
    if not did_work:
        ap.print_help()
        return 2
    return 0


# ═══════════════════════════ 自测 ═══════════════════════════

def _selftest() -> int:
    """内置最小样例：断言三种来源的解析结果与 HP 终值（初始均 10/10）。"""
    # ── 真值样例 ──
    truth_events = [
        {"t": 0.0, "type": 0, "type_name": "Activation", "target": None, "side": "P",
         "origin": {"name": "Falcon Blade", "zh": "猎鹰战刃"}, "params": {}},
        # O 攻 P 3（物品 origin，side=攻击方，target=null）→ P 7
        {"t": 0.4, "type": 1, "type_name": "DealDamage", "target": None, "side": "O",
         "origin": {"name": "Dragon Knight", "zh": "黏黏龙骑士"}, "params": {"damage": 3}},
        # P 得尖刺 2 层 —— 层数施加，不动 HP（反证：入账会双计）
        {"t": 0.6, "type": 104, "type_name": "Spikes", "target": 0, "side": "P",
         "origin": {"name": "Djinn Lamp", "zh": "阿拉丁神灯"}, "params": {"amount": 2}},
        # 中毒跳伤 P 2（伤害源 origin，side=target 兜底=非受害方）→ P 5
        {"t": 1.2, "type": 1, "type_name": "DealDamage", "target": 1, "side": "O",
         "origin": {"name": "Poison", "zh": "中毒", "source": "damage_type"},
         "params": {"damage": 2}},
        # P 回血 2 → 7
        {"t": 1.5, "type": 12, "type_name": "Health", "target": 0, "side": "P",
         "origin": {"name": "Cheese Goobert", "zh": "奶酪黏黏"}, "params": {"amount": 2}},
        # P 临时上限 +3（同时加当前血，Character.gd:894-895）→ 10
        {"t": 2.0, "type": 19, "type_name": "TemporaryMaxHealth", "target": None, "side": "P",
         "origin": {"name": "Twine", "zh": "细绳"}, "params": {"amount": 3}},
        # O 直接失去 4（amount 为负）→ 6
        {"t": 2.4, "type": 5, "type_name": "LoseHealth", "target": 1, "side": "O",
         "origin": {"name": "Djinn Lamp", "zh": "阿拉丁神灯"}, "params": {"amount": -4}},
    ]
    ce = parse_truth_events(truth_events)
    assert [(e["type"], e["side"], e["target"]) for e in ce[:2]] == \
        [("Activation", "P", None), ("DealDamage", "O", None)]
    assert ce[1]["t"] == 0.4 and ce[1]["origin_key"] == "Dragon Knight"
    lt = build_hp_ledger(ce, 10.0, 10.0)
    assert (lt["terminal"]["P"], lt["terminal"]["O"]) == (10.0, 6.0), lt["terminal"]
    assert lt["reason"] == "completed"
    # 逐秒曲线：t<=1 的扣血生效、t in (1,2] 的回血+临时上限生效
    assert lt["curve_per_second"][1] == {"t": 1, "hp_p": 7.0, "hp_o": 10.0}
    assert lt["curve_per_second"][2] == {"t": 2, "hp_p": 10.0, "hp_o": 10.0}

    # ── 轨迹样例（行格式 id|type|depth|origin|target|params） ──
    trace_text = "\n".join([
        "## lineup_armor_wall|lineup_cursed_reaper|20260924",
        "1|1|0|it:Dragon Knight~3~1,0;1,1|i0|damage=i3",        # O 攻 P：target=受害方 → P 7
        "2|104|0|it:Djinn Lamp~1~2,0|i0|amount=i2,reflected=F,used=F",  # P 层数，不动 HP
        "3|1|0|i108|i1|damage=i2",                               # 中毒跳伤 P：伤害源 origin → 受害=1-target=0 → P 5
        "4|12|0|i102|i0|amount=i2",                              # 恢复跳血 P：target=受方 → P 7
        "5|19|0|it:Twine~1~2,0|-|amount=5.000000",               # 临时上限 ownerType=1 → P +5 → 12
        "6|5|0|it:Djinn Lamp~3~1,0;i1,0|i1|amount=i-4",          # LoseHealth target=受害方 → O 10-4=6
    ]) + "\n"
    import tempfile
    with tempfile.NamedTemporaryFile("w", suffix=".txt", delete=False, encoding="utf-8") as fh:
        fh.write(trace_text)
        trace_path = fh.name
    fights = parse_trace(trace_path)
    assert len(fights) == 1 and fights[0]["header"] == \
        "lineup_armor_wall|lineup_cursed_reaper|20260924"
    te = fights[0]["events"]
    assert [(e["type"], e["side"], e["target"]) for e in te] == [
        ("DealDamage", "O", "P"), ("Spikes", "P", "P"), ("DealDamage", "O", "O"),
        ("Health", "P", "P"), ("TemporaryMaxHealth", "P", None),
        ("LoseHealth", "O", "O")]
    assert te[4]["params"]["amount"] == 5.0 and te[5]["params"]["amount"] == -4
    ltr = build_hp_ledger(te, 10.0, 10.0)
    assert (ltr["terminal"]["P"], ltr["terminal"]["O"]) == (12.0, 6.0), ltr["terminal"]
    assert ltr["reason"] == "completed" and ltr["curve_per_second"] is None

    # ── 模拟样例（含真实结构层数事件：gd_core 引擎无 buff_type/params.buff，
    #     纯 Python 路径带 params.buff 名——两条路都不入 HP 账本） ──
    sim_events = [
        {"id": 0, "t": 0.0, "type": "combat_start", "depth": 0},
        # gd_core 引擎实产结构（output/sim_run/*_log.json）：无 buff_type、无 params.buff
        {"id": 1, "t": 0.1, "type": "stack_gain", "depth": 0, "actor": "player",
         "target": "player",
         "params": {"amount": 30, "used": False, "reflected": False,
                    "actor_is_target": True}},
        # 纯 Python simulator 结构（simulator/events.py:237 params.buff）
        {"id": 2, "t": 0.2, "type": "stack_lose", "depth": 0, "actor": "opponent",
         "target": "opponent", "origin": "Falcon Blade",
         "params": {"buff": "block", "amount": 4, "permanent": True}},
        {"id": 3, "t": 0.4, "type": "attack", "depth": 1, "actor": "opponent",
         "target": "player", "origin": "Dragon Knight",
         "params": {"damage": 3, "health_damage": 3, "block_absorbed": 0}},   # P 7
        {"id": 4, "t": 1.2, "type": "lose_health", "depth": 1, "actor": "player",
         "origin": "Poison", "params": {"amount": 2}},                        # P 5
        {"id": 5, "t": 1.5, "type": "heal", "depth": 1, "actor": "player",
         "origin": "Regeneration", "params": {"amount": 2, "overheal": 0}},   # P 7
        {"id": 6, "t": 2.4, "type": "unhealing", "depth": 1, "actor": "player",
         "target": "opponent", "origin": "Unhealing", "params": {"damage": 4}},  # O 6
        {"id": 7, "t": 3.0, "type": "fatigue_damage", "depth": 0,
         "params": {"counter": 1, "player_damage": 1, "opponent_damage": 2}},  # P 6, O 4
    ]
    se = parse_sim_events(sim_events)
    assert se[1]["type"] == "Stack" and se[1]["side"] == "P"      # 降级容错
    assert se[2]["type"] == "Block" and se[2]["side"] == "O"      # params.buff 名映射
    assert [(e["type"], e["side"], e["target"]) for e in se[3:]] == [
        ("DealDamage", "O", "P"), ("LoseHealth", "P", None), ("Health", "P", None),
        ("Unhealing", "P", "O"), ("Fatigue", None, None)]
    ls = build_hp_ledger(se, 10.0, 10.0)
    assert (ls["terminal"]["P"], ls["terminal"]["O"]) == (6.0, 4.0), ls["terminal"]
    assert ls["reason"] == "completed"   # 层数事件未动 HP（否则 4+30 会穿帮）

    # ── 轨迹初始 HP 推导：fixture 阵容 health=25.0 ──
    fh = load_fixture_health()
    assert fh is not None and fh.get("lineup_armor_wall") == 25.0, fh

    # ── 扣血截断在 0 + hp_zero 终止：后续事件不再入账 ──
    kill = parse_sim_events([
        {"id": 0, "t": 1.0, "type": "attack", "depth": 0, "actor": "opponent",
         "target": "player", "origin": "Greatsword",
         "params": {"damage": 50, "health_damage": 50, "block_absorbed": 0}},
        {"id": 1, "t": 2.0, "type": "heal", "depth": 0, "actor": "player",
         "origin": "Potion", "params": {"amount": 20, "overheal": 0}},
    ])
    lk = build_hp_ledger(kill, 10.0, 10.0)
    assert lk["reason"] == "hp_zero" and lk["ended_t"] == 1.0
    assert lk["terminal"]["P"] == 0.0 and lk["terminal"]["O"] == 10.0
    assert len(lk["curve_per_event"]) == 1  # 致死事件后停止

    # ── 超时判定 ──
    lto = build_hp_ledger(parse_truth_events([
        {"t": 181.0, "type": 1, "type_name": "DealDamage", "target": None, "side": "O",
         "origin": {"name": "X"}, "params": {"damage": 1}},
    ]), 10.0, 10.0, time_limit=180.0)
    assert lto["reason"] == "timeout" and lto["terminal"]["P"] == 9.0

    print("SELFTEST PASS：三种来源解析 + HP 终值/曲线/截断/终止原因 全部断言通过")
    return 0


if __name__ == "__main__":
    sys.exit(main())
