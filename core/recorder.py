# -*- coding: utf-8 -*-
"""recorder.py — 对局操作语料记录器（纯外置只读）

设计见 docs/recorder_design.md。本模块只做三件事：

1. **采样**：后台线程周期读取玩家状态（金币/血量/回合/职业/背包/储物箱/商店）
   与战斗状态，归一化成 `Frame`；
2. **差分**：`diff_frames(prev, cur)` 是纯函数，把两帧的差异翻译成事件
   （buy/sell/place/move/rotate/storage_*/reroll/lock/unlock/combine/...），
   无法归类时如实产出 `unknown_change` 而不是猜；
3. **落盘**：经 `core.store.RunStore` 按回合分片追加、写快照、归档压缩。

原始层（raw）保持"什么变化都记"，反复摆盘与反复切换锁定都会如实出现；
把它们折成训练样本是 `tools/corpus_fold.py` 的职责（净零段丢弃），
两层彻底解耦——这里不做任何"训练友好"的删改。

只读约束：全程 ReadProcessMemory，不写游戏内存、不注入、不按键鼠。
"""
from __future__ import annotations

import logging
import threading
import time
from dataclasses import dataclass
from datetime import datetime
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

from .lineup import anchor_cell, gems_of, rotation_deg, to_v4
from .store import RunStore, StoreError, new_run_id

logger = logging.getLogger(__name__)

SCHEMA_VERSION = 4
PHASE_SHOP = "shop"
PHASE_COMBAT = "combat"
PHASE_TITLE = "title"
PHASE_UNKNOWN = "unknown"

# CombatLog 事件类型：111=Win 112=Loss（见 core/combatlog_reader.py EVENT_TYPES）
COMBAT_EVENT_WIN = 111
COMBAT_EVENT_LOSS = 112


# ===========================================================================
# 帧（归一化后的采样）
# ===========================================================================
@dataclass
class Frame:
    """一帧规范化状态。所有列表都是**排序后的规范元组**，便于多重集比对。"""

    t: float = 0.0
    round: Optional[int] = None
    phase: str = PHASE_UNKNOWN
    gold: Optional[int] = None
    hp: Optional[int] = None
    wins: Optional[int] = None
    losses: Optional[int] = None
    character: Optional[str] = None
    # (id, row, col, r, gems, in)
    backpack: Tuple[Tuple, ...] = ()
    # (id, row, col, r, gems)
    storage: Tuple[Tuple, ...] = ()
    # (slot, id, price, normal_price, on_sale, free, bought, reserved)
    shop: Tuple[Tuple, ...] = ()
    combat_count: Optional[int] = None
    combat_finished: Optional[bool] = None
    combat_last_type: Optional[int] = None
    game_state: Optional[int] = None      # Game.state（0=Title/1=Shop/2=Combat）
    ok: bool = True

    # ---- 便捷派生 ----
    def signature(self) -> Tuple:
        """阶段签名：不变则整帧丢弃（不产生事件）。"""
        return (self.phase, self.round, self.gold, self.hp, self.character,
                self.backpack, self.storage, self.shop)

    def gold_of(self) -> Optional[int]:
        return self.gold

    def to_snapshot_state(self) -> Dict[str, Any]:
        """快照用的状态块（v4 阵容 + 商店 + 资源）。"""
        return {
            "gold": self.gold,
            "hp": self.hp,
            "wins": self.wins,
            "losses": self.losses,
            "character": self.character,
            "backpack": _backpack_to_v4(self.backpack, self.character, self.round),
            "storage": [{"id": i, "at": [r, c], "r": rot, "gems": list(g)}
                        for (i, r, c, rot, g) in self.storage],
            "shop": [{"slot": s, "id": i, "price": pr, "normal_price": np_,
                      "on_sale": bool(osale), "free": bool(fr),
                      "bought": bool(bt), "reserved": bool(rv)}
                     for (s, i, pr, np_, osale, fr, bt, rv) in self.shop],
        }


def _backpack_to_v4(backpack: Tuple[Tuple, ...], character: Optional[str],
                    round_num: Optional[int]) -> dict:
    if not backpack:
        base = to_v4([], character or "Adventurer", round_num)
        return base
    flat = sorted(backpack)
    items = []
    for (i, row, col, rot, gems, parent) in flat:
        e: Dict[str, Any] = {"id": i, "at": [int(row), int(col)], "r": int(rot)}
        if parent is not None and int(parent) >= 0:
            e["in"] = int(parent)
        if gems:
            e["gems"] = list(gems)
        items.append(e)
    return {
        "version": 4,
        "name": "对局实录",
        "character": character or "Adventurer",
        "round": int(round_num) if round_num is not None else 1,
        "grid": [7, 9],
        "items": items,
    }


# ===========================================================================
# 采样结果 → Frame
# ===========================================================================
def normalize(bot_state: Optional[dict], combat: Optional[dict] = None,
              now: Optional[float] = None) -> Frame:
    """把 `BackpackBot.get_state()` 的返回（+ CombatLog poll）归一化成 Frame。

    `bot_state` 为空表示本次读取失败：返回 `ok=False` 的帧，由调用方记 gap。
    """
    t = now if now is not None else time.time()
    if not bot_state:
        return Frame(t=t, ok=False)

    live = bot_state.get("live_items") or {}
    round_num = _as_int(bot_state.get("round"))
    gold = _as_int(bot_state.get("gold"))
    hp = _as_int(bot_state.get("hp"))
    character = bot_state.get("character") or None

    backpack = tuple(sorted(_sig_backpack(live.get("backpack") or [])))
    storage = tuple(sorted(_sig_storage(live.get("storage") or [])))
    shop = tuple(sorted(_sig_shop(live.get("shop") or [])))

    combat_count = None
    combat_finished = None
    combat_last = None
    if combat:
        combat_count = _as_int(combat.get("event_count"))
        fin = combat.get("finished")
        combat_finished = bool(fin) if fin is not None else None
        combat_last = _as_int(combat.get("last_type"))

    phase = _infer_phase(round_num, live, combat, bot_state)
    return Frame(
        t=t, round=round_num, phase=phase, gold=gold, hp=hp,
        wins=_as_int(bot_state.get("wins")),
        losses=_as_int(bot_state.get("losses")),
        character=character, backpack=backpack, storage=storage, shop=shop,
        combat_count=combat_count, combat_finished=combat_finished,
        combat_last_type=combat_last,
        game_state=_as_int(bot_state.get("game_state")), ok=True,
    )


def _as_int(v) -> Optional[int]:
    try:
        return int(v) if v is not None else None
    except (TypeError, ValueError):
        return None


def _sig_backpack(items: List[dict]) -> List[Tuple]:
    """ItemInfo 列表 → 背包规范元组（含袋内物品，`in` 指向父下标）。"""
    out: List[Tuple] = []

    def walk(it: dict, parent: Optional[int]) -> None:
        row, col = anchor_cell(it)
        sig = (str(it.get("name", "")), int(row), int(col),
               int(rotation_deg(it)), tuple(sorted(gems_of(it))),
               -1 if parent is None else parent)
        out.append(sig)
        idx = len(out) - 1
        for child in (it.get("contents") or []):
            if isinstance(child, dict):
                walk(child, idx)

    for it in items:
        if isinstance(it, dict):
            walk(it, None)
    return out


def _sig_storage(items: List[dict]) -> List[Tuple]:
    out = []
    for it in items:
        if not isinstance(it, dict):
            continue
        row, col = anchor_cell(it)
        out.append((str(it.get("name", "")), int(row), int(col),
                    int(rotation_deg(it)), tuple(sorted(gems_of(it)))))
    return out


def _sig_shop(items: List[dict]) -> List[Tuple]:
    """商店物品 ItemInfo（已并上 offer 字段）→ 规范元组。"""
    out = []
    for it in items:
        if not isinstance(it, dict):
            continue
        slot = _as_int(it.get("slot"))
        if slot is None:
            # 没有槽位号时用名字占位，仍可参与比对
            slot = -1
        out.append((
            int(slot), str(it.get("name", "")), _as_int(it.get("price")),
            _as_int(it.get("normal_price")), bool(it.get("on_sale")),
            bool(it.get("free")), bool(it.get("bought")),
            bool(it.get("reserved")),
        ))
    return out


def _infer_phase(round_num: Optional[int], live: dict, combat: Optional[dict],
                 bot_state: dict) -> str:
    """阶段判定（强→弱）。

    1. CombatLog：有事件且未结束 → combat；刚结束且回到商店 → shop；
    2. 场景：能读到对手阵容（Opponent 在场景中）→ combat；
       有商店槽/储物箱 → shop；
    3. 什么都没有 → unknown（不回退成 shop，避免把标题界面当成商店）。
    """
    if combat and combat.get("connected"):
        count = combat.get("event_count") or 0
        finished = combat.get("finished")
        if count > 0 and not finished:
            return PHASE_COMBAT
        if count > 0 and finished:
            return PHASE_SHOP
    # Game.state（标定 member_state 后可用）：Title/Shop/Combat 是游戏内权威值
    gs = bot_state.get("game_state")
    if isinstance(gs, int):
        if gs == 0:
            return PHASE_TITLE
        if gs == 2:
            return PHASE_COMBAT
        if gs == 1:
            return PHASE_SHOP
    if round_num is None:
        return PHASE_UNKNOWN
    if live.get("shop") or live.get("storage"):
        return PHASE_SHOP
    if live.get("backpack"):
        # 有背包但无商店/储物箱：可能是战斗场景（商店界面被隐藏）
        return PHASE_COMBAT
    return PHASE_UNKNOWN


# ===========================================================================
# 差分（纯函数）
# ===========================================================================
def diff_frames(prev: Frame, cur: Frame, ctx: dict) -> List[dict]:
    """两帧差异 → 事件列表（不含 seq/t，由调用方补齐）。

    `ctx` 提供：`round`、`anchor`（当前快照引用）、`prev_anchor`、
    `candidate_shops`（上一帧商店，用于 buy 的价格核对）。

    判定顺序（避免同一变化报两次）：回合 → 买 → 刷新 → 卖 → 背包多重集
    → 锁/解锁 → 合成 → 未归类。
    """
    events: List[dict] = []
    base = {
        "phase": cur.phase,
        "round": cur.round,
        "source": "diff",
        "confidence": 1.0,
        "anchor": ctx.get("anchor"),
    }

    # --- 0. 回合推进 ---
    if prev.round is not None and cur.round is not None and cur.round > prev.round:
        events.append({
            **base, "type": "round_start", "confidence": 1.0,
            "action": {"from_round": prev.round, "to_round": cur.round},
            "evidence": {"gold": cur.gold, "hp": cur.hp},
        })

    # --- 1. 金币与商店 ---
    gold_delta = None
    if prev.gold is not None and cur.gold is not None:
        gold_delta = cur.gold - prev.gold

    consumed_slots: set = set()
    buy_events = _detect_buys(prev, cur, gold_delta, base)
    for ev in buy_events:
        events.append(ev)
        slot = ev["action"].get("slot")
        if slot is not None:
            consumed_slots.add(slot)

    buyer_item_ids = {ev["action"].get("id") for ev in buy_events
                      if ev["action"].get("id")}
    spent_on_buys = sum((ev["action"].get("price") or 0) for ev in buy_events)

    if (not buy_events and gold_delta is not None and gold_delta < 0
            and _shop_changed(prev, cur)):
        events.append({
            **base, "type": "reroll", "confidence": 0.9,
            "action": {"cost": -gold_delta},
            "delta": {"gold": gold_delta, "shop": _shop_diff(prev, cur)},
            "evidence": {"kept_slots": _kept_slots(prev, cur)},
        })
    elif buy_events and gold_delta is not None and gold_delta < -spent_on_buys:
        # 买完还花了钱：可能同帧内也刷新了
        events.append({
            **base, "type": "unknown_change", "confidence": 0.0,
            "action": {},
            "delta": {"gold": gold_delta - (-spent_on_buys)},
            "evidence": {"reason": "买入之外的金币减少，无法归类"},
        })

    # --- 2. 背包内部 / 储物箱 ---
    inventory_events = _detect_inventory(prev, cur, gold_delta, buyer_item_ids,
                                         base)
    events.extend(inventory_events)

    # --- 3. 锁定 / 解锁 ---
    events.extend(_detect_reserved(prev, cur, consumed_slots, base))

    # --- 4. 未归类兜底 ---
    covered = {e["type"] for e in events}
    if not events and prev.signature() != cur.signature():
        events.append({
            **base, "type": "unknown_change", "confidence": 0.0,
            "action": {},
            "delta": {"gold": gold_delta, "shop": _shop_diff(prev, cur)},
            "evidence": {"covered": sorted(covered), "reason": "未匹配任何判定规则"},
        })
    return events


def _slot_map(frame: Frame) -> Dict[int, Tuple]:
    return {s[0]: s for s in frame.shop}


def _shop_changed(prev: Frame, cur: Frame) -> bool:
    a = {s[0]: s[1] for s in prev.shop}
    b = {s[0]: s[1] for s in cur.shop}
    if set(a) != set(b):
        return True
    return any(a[k] != b[k] for k in a)


def _shop_diff(prev: Frame, cur: Frame) -> List[dict]:
    """商店槽位变化（记账用，不参与判定）。"""
    a, b = _slot_map(prev), _slot_map(cur)
    out = []
    for slot in sorted(set(a) | set(b)):
        pa, pb = a.get(slot), b.get(slot)
        if pa == pb:
            continue
        if pa and pb:
            if pa[1] != pb[1]:
                out.append({"slot": slot, "op": "replace", "from": pa[1], "to": pb[1]})
            elif pa[6] != pb[6]:
                out.append({"slot": slot, "op": "bought", "id": pb[1]})
            elif pa[7] != pb[7]:
                out.append({"slot": slot, "op": "reserve", "value": pb[7]})
        elif pa and not pb:
            out.append({"slot": slot, "op": "gone", "id": pa[1]})
        else:
            out.append({"slot": slot, "op": "new", "id": pb[1]})
    return out


def _kept_slots(prev: Frame, cur: Frame) -> List[int]:
    """reroll 时被保留（锁定）而未刷掉的槽位。"""
    a, b = _slot_map(prev), _slot_map(cur)
    kept = []
    for slot, pb in b.items():
        pa = a.get(slot)
        if pa and pb[7] and pa[1] == pb[1]:
            kept.append(slot)
    return sorted(kept)


def _detect_buys(prev: Frame, cur: Frame, gold_delta: Optional[int],
                 base: dict) -> List[dict]:
    """买 → 事件。两个信号：

    ① 槽位 `bought` false→true（游戏内最直接）；
    ② 槽位物品消失 + 背包/储物箱新增同 id + 金币减少（bought 标志已被重置时）。
    """
    out: List[dict] = []
    a = _slot_map(prev)
    b = _slot_map(cur)
    gold_down = gold_delta is not None and gold_delta < 0

    # ① bought 翻转
    for slot, pb in b.items():
        pa = a.get(slot)
        if pa and not pa[6] and pb[6]:
            out.append({
                **base, "type": "buy", "confidence": 0.95,
                "action": {
                    "slot": slot, "id": pb[1], "price": pb[2],
                    "price_source": "decoded" if pb[2] is not None else "unknown",
                    "normal_price": pb[3], "on_sale": pb[4], "free": pb[5],
                },
                "evidence": {"signal": "bought_flag", "gold_delta": gold_delta},
            })

    if out or not gold_down:
        return out

    # ② 槽位物品消失 + 同 id 出现在背包/储物箱
    new_ids = {s[0] for s in cur.storage} | {s[0] for s in cur.backpack}
    prev_ids = {s[0] for s in prev.storage} | {s[0] for s in prev.backpack}
    gained = new_ids - prev_ids
    for slot, pa in a.items():
        if pa[1] in gained and (slot not in b or b[slot][1] != pa[1]):
            out.append({
                **base, "type": "buy", "confidence": 0.8,
                "action": {
                    "slot": slot, "id": pa[1], "price": pa[2],
                    "price_source": ("decoded" if pa[2] is not None
                                     else ("gold_delta" if len(a) == 1 else "unknown")),
                    "normal_price": pa[3], "on_sale": pa[4], "free": pa[5],
                },
                "evidence": {"signal": "shop_item_left", "gold_delta": gold_delta},
            })
            gained.discard(pa[1])
    return out


def _detect_inventory(prev: Frame, cur: Frame, gold_delta: Optional[int],
                      buyer_ids: set, base: dict) -> List[dict]:
    """背包/储物箱变化 → place/move/rotate/gems_change/storage_in/sell/combine。"""
    out: List[dict] = []
    gold_up = gold_delta is not None and gold_delta > 0

    prev_bp = list(prev.backpack)
    cur_bp = list(cur.backpack)
    prev_st = list(prev.storage)
    cur_st = list(cur.storage)

    # 背包多重集差
    gone_bp, new_bp = _multiset_delta(prev_bp, cur_bp)
    gone_st, new_st = _multiset_delta(prev_st, cur_st)

    # --- 合成：多件消失 + 一件新增，且金币没变 ---
    if len(gone_bp) >= 2 and len(new_bp) == 1 and not gold_up:
        ev = {
            **base, "type": "combine", "confidence": 0.6,
            "action": {
                "inputs": [{"id": f[0], "at": [f[1], f[2]]} for f in gone_bp],
                "output": {"id": new_bp[0][0], "at": [new_bp[0][1], new_bp[0][2]]},
            },
            "evidence": {"reason": "背包多件消失且一件新增，金币未变"},
        }
        out.append(ev)
        return out

    # --- 背包内位移/旋转/宝石 ---
    for sig in list(gone_bp):
        match = _find_pair(sig, new_bp)
        if match is None:
            continue
        gone_bp.remove(sig)
        new_bp.remove(match)
        _emit_transform(out, sig, match, base)

    # --- 储物箱消失 → 回到背包（storage_out 语义并入 place.from=storage）---
    moved_from_storage: set = set()
    for sig in list(gone_st):
        target = next((c for c in new_bp if c[0] == sig[0]), None)
        if target is None:
            continue
        gone_st.remove(sig)
        new_bp.remove(target)
        moved_from_storage.add(sig[0])
        out.append({
            **base, "type": "place", "confidence": 0.85,
            "action": {"id": target[0], "at": [target[1], target[2]],
                       "r": target[3], "gems": list(target[4]),
                       "from": "storage"},
            "evidence": {"signal": "storage_decreased"},
        })

    # --- 背包消失 → 进储物箱 ---
    for sig in list(gone_bp):
        target = next((c for c in new_st if c[0] == sig[0]), None)
        if target is None:
            continue
        gone_bp.remove(sig)
        new_st.remove(target)
        out.append({
            **base, "type": "storage_in", "confidence": 0.8,
            "action": {"id": sig[0], "at": [sig[1], sig[2]], "r": sig[3],
                       "gems": list(sig[4])},
            "evidence": {"signal": "storage_increased"},
        })

    # --- 背包消失且金币增加 → 卖出 ---
    sold_rows = []
    for sig in list(gone_bp):
        if gold_up:
            gone_bp.remove(sig)
            sold_rows.append({
                **base, "type": "sell", "confidence": 0.9,
                "action": {"id": sig[0], "at": [sig[1], sig[2]], "from": "backpack",
                           "price": gold_delta if len(gone_bp) == 0 else None},
                "evidence": {"gold_delta": gold_delta},
            })
    out.extend(sold_rows)
    for sig in list(gone_st):
        if gold_up:
            gone_st.remove(sig)
            out.append({
                **base, "type": "sell", "confidence": 0.85,
                "action": {"id": sig[0], "from": "storage",
                           "price": gold_delta if len(gone_st) == 0 else None},
                "evidence": {"gold_delta": gold_delta},
            })

    # --- 背包新增 → 放置（来源：买入 / 未知）---
    for sig in list(new_bp):
        new_bp.remove(sig)
        from_ = "shop" if sig[0] in buyer_ids else "unknown"
        out.append({
            **base, "type": "place", "confidence": 0.8 if from_ != "unknown" else 0.6,
            "action": {"id": sig[0], "at": [sig[1], sig[2]], "r": sig[3],
                       "gems": list(sig[4]), "from": from_},
            "evidence": {},
        })

    # --- 储物箱新增（非背包移入）---
    for sig in list(new_st):
        new_st.remove(sig)
        out.append({
            **base, "type": "storage_put", "confidence": 0.6,
            "action": {"id": sig[0], "at": [sig[1], sig[2]], "r": sig[3],
                       "gems": list(sig[4])},
            "evidence": {"reason": "储物箱新增且非背包移入"},
        })

    # --- 完全无法归类的残留 ---
    if gone_bp or gone_st or new_bp or new_st:
        out.append({
            **base, "type": "unknown_change", "confidence": 0.0,
            "action": {},
            "delta": {"gone_backpack": [list(x) for x in gone_bp],
                      "gone_storage": [list(x) for x in gone_st],
                      "new_backpack": [list(x) for x in new_bp],
                      "new_storage": [list(x) for x in new_st]},
            "evidence": {"reason": "多重集差异无法配对"},
        })
    return out


def _emit_transform(out: List[dict], sig: Tuple, match: Tuple, base: dict) -> None:
    """同一物品的位移/旋转/宝石变化 → move / rotate / gems_change。"""
    rot_changed = sig[3] != match[3]
    pos_changed = sig[1:3] != match[1:3] or sig[5] != match[5]
    gems_changed = sig[4] != match[4]
    if pos_changed:
        out.append({
            **base, "type": "move", "confidence": 0.9,
            "action": {"id": sig[0], "from": [sig[1], sig[2]],
                       "to": [match[1], match[2]], "r": match[3]},
            "evidence": {},
        })
        if rot_changed:
            out.append({
                **base, "type": "rotate", "confidence": 0.85,
                "action": {"id": sig[0], "at": [match[1], match[2]],
                           "from_r": sig[3], "to_r": match[3]},
                "evidence": {"also_moved": True},
            })
    elif rot_changed:
        out.append({
            **base, "type": "rotate", "confidence": 0.9,
            "action": {"id": sig[0], "at": [match[1], match[2]],
                       "from_r": sig[3], "to_r": match[3]},
            "evidence": {},
        })
    if gems_changed:
        out.append({
            **base, "type": "gems_change", "confidence": 0.85,
            "action": {"id": sig[0], "at": [match[1], match[2]],
                       "from": list(sig[4]), "to": list(match[4])},
            "evidence": {},
        })
    if not (rot_changed or pos_changed or gems_changed):
        out.append({
            **base, "type": "unknown_change", "confidence": 0.0,
            "action": {"id": sig[0]},
            "evidence": {"reason": "签名相同却配了对（不应发生）"},
        })


def _detect_reserved(prev: Frame, cur: Frame, consumed_slots: set,
                     base: dict) -> List[dict]:
    """锁定/解锁。买走导致的复位不记（并入 buy）。"""
    out: List[dict] = []
    a, b = _slot_map(prev), _slot_map(cur)
    for slot, pb in b.items():
        pa = a.get(slot)
        if not pa:
            continue
        if pa[7] == pb[7]:
            continue
        if slot in consumed_slots:
            continue
        out.append({
            **base, "type": "lock" if pb[7] else "unlock",
            "confidence": 0.95,
            "action": {"slot": slot, "id": pb[1], "price": pb[2]},
            "evidence": {},
        })
    return out


def _multiset_delta(prev: List[Tuple], cur: List[Tuple]) -> Tuple[List[Tuple], List[Tuple]]:
    """多重集差：(prev 中多出的, cur 中多出的)。"""
    remaining = list(cur)
    gone: List[Tuple] = []
    for sig in prev:
        if sig in remaining:
            remaining.remove(sig)
        else:
            gone.append(sig)
    return gone, remaining


def _find_pair(gone: Tuple, candidates: List[Tuple]) -> Optional[Tuple]:
    """在候选里为消失的物品找一个"同一件"（同 id 且最像）。"""
    same_id = [c for c in candidates if c[0] == gone[0]]
    if not same_id:
        return None
    # 优先：位置相同（旋转/宝石变化）；其次：旋转相同（纯位移）；否则取第一个
    same_pos = [c for c in same_id
                if c[1] == gone[1] and c[2] == gone[2] and c[5] == gone[5]]
    if same_pos:
        return same_pos[0]
    same_rot = [c for c in same_id if c[3] == gone[3] and c[5] == gone[5]]
    if same_rot:
        return same_rot[0]
    return same_id[0]


# ===========================================================================
# 记录器
# ===========================================================================
@dataclass
class RecorderConfig:
    enabled: bool = False
    out_dir: str = "output/records"
    interval_ms: int = 400
    adaptive_interval: bool = True
    combat_interval_ms: int = 800
    capture_bot: bool = False
    confirm_frames: int = 2
    compress: str = "lzma"
    auto_stop_on_title: bool = True
    max_events_per_run: int = 20000
    gap_threshold_ms: int = 5000
    save_frames: bool = False

    @classmethod
    def from_dict(cls, d: Optional[dict]) -> "RecorderConfig":
        d = d or {}
        cfg = cls()
        for f in ("enabled", "out_dir", "interval_ms", "adaptive_interval",
                  "combat_interval_ms", "capture_bot", "confirm_frames",
                  "compress", "auto_stop_on_title", "max_events_per_run",
                  "gap_threshold_ms", "save_frames"):
            if f in d and d[f] is not None:
                cur = getattr(cfg, f)
                try:
                    setattr(cfg, f, type(cur)(d[f]))
                except (TypeError, ValueError):
                    pass
        return cfg

    def to_dict(self) -> dict:
        return {f: getattr(self, f) for f in self.__dataclass_fields__}


class Recorder:
    """对局记录器。

    用法::

        rec = Recorder(bot, config=cfg, on_event=cb)
        rec.start()          # 起后台采样线程
        ...
        rec.stop("user_stop")

    `bot` 需提供 `get_state()`（返回 gold/hp/round/live_items）、
    `read_character()`，以及可选 `memory_reader`/`godot_reader`
    （用于战斗起止判定；缺失时退化为场景启发式）。
    """

    def __init__(self, bot, config: Optional[RecorderConfig] = None,
                 on_event=None, on_error=None):
        self.bot = bot
        self.cfg = config or RecorderConfig()
        self.on_event = on_event
        self.on_error = on_error

        self._thread: Optional[threading.Thread] = None
        self._stop = threading.Event()
        self._lock = threading.Lock()

        self.store: Optional[RunStore] = None
        self.run_id: Optional[str] = None
        self._prev: Optional[Frame] = None        # 最近一次 diff 的基准（已提交）
        self._committed: Optional[Frame] = None   # 最后一个已提交的世界状态
        self._last_seen: Optional[Frame] = None   # 最近一次采样到的帧（去抖用）
        self._seq = 0
        self._event_count = 0
        self._rounds_started = 0
        self._dropped = 0
        self._gaps = 0
        self._last_ok_t: Optional[float] = None
        self._combat_reader = None
        self._read_cost_ms = 0.0
        self._last_error: Optional[str] = None
        self._combat_open = False
        self._combat_snapshot_ref: Optional[str] = None
        self._hp_before_combat: Optional[int] = None
        self._shop_snapshot_ref: Optional[str] = None
        self._gap_open = False
        self._stop_reason: Optional[str] = None
        self._finished = False
        self._t0 = time.time()

    # ---------------- 对外状态 ----------------
    @property
    def running(self) -> bool:
        return self._thread is not None and self._thread.is_alive()

    def stats(self) -> dict:
        return {
            "running": self.running,
            "run_id": self.run_id,
            "events": self._event_count,
            "rounds": self._rounds_started,
            "dropped_frames": self._dropped,
            "gaps": self._gaps,
            "read_cost_ms": round(self._read_cost_ms, 1),
            "last_error": self._last_error,
        }

    # ---------------- 启停 ----------------
    def start(self) -> bool:
        if self.running:
            return True
        if self.bot is None:
            self._err("未初始化机器人，无法开始记录")
            return False
        self._stop.clear()
        self._thread = threading.Thread(target=self._loop, name="recorder",
                                        daemon=True)
        self._thread.start()
        return True

    def stop(self, reason: str = "user_stop", timeout: float = 3.0) -> None:
        """停止记录并收尾。

        可从任意线程调用；**在采样线程内部调用时**只置停止标志（否则会
        自己 join 自己而卡死），收尾由 `_loop` 退出后完成。
        """
        self._stop_reason = reason
        self._stop.set()
        th = self._thread
        if th is threading.current_thread():
            return
        if th is not None and th.is_alive():
            th.join(timeout=timeout)
        self._thread = None
        self._finish(reason)

    # ---------------- 采样循环 ----------------
    def _loop(self) -> None:
        while not self._stop.is_set():
            t0 = time.time()
            try:
                self._tick()
            except Exception as e:  # noqa: BLE001
                self._err(f"采样异常: {e}")
            interval = self._interval_s()
            elapsed = time.time() - t0
            time.sleep(max(0.05, interval - elapsed))
        # 采样线程自发停止（回标题 / 超限）时在此收尾；外部 stop() 已收过则跳过
        self._thread = None
        self._finish(self._stop_reason or "stopped")

    def _interval_s(self) -> float:
        base = max(0.05, self.cfg.interval_ms / 1000.0)
        if self.cfg.adaptive_interval:
            base = max(base, 2.0 * self._read_cost_ms / 1000.0, 0.2)
        if self._prev is not None and self._prev.phase == PHASE_COMBAT:
            base = max(base, self.cfg.combat_interval_ms / 1000.0)
        return base

    def _tick(self) -> None:
        t0 = time.time()
        combat = self._poll_combat()
        state = None
        try:
            state = self.bot.get_state()
        except Exception as e:  # noqa: BLE001
            self._last_error = f"读取状态失败: {e}"
        self._read_cost_ms = (time.time() - t0) * 1000.0

        frame = normalize(state, combat, now=time.time())
        if not frame.ok:
            self._on_bad_frame()
            return

        with self._lock:
            self._handle_frame(frame)

    def _on_bad_frame(self) -> None:
        """读失败：记 gap（连续失败超阈值只记一次）。"""
        prev_ok = self._last_ok_t
        if prev_ok is not None and (time.time() - prev_ok) * 1000.0 >= self.cfg.gap_threshold_ms:
            if not getattr(self, "_gap_open", False):
                self._gap_open = True
                self._gaps += 1
                self._emit({
                    "type": "gap", "round": self._prev.round if self._prev else None,
                    "phase": self._prev.phase if self._prev else PHASE_UNKNOWN,
                    "source": "recorder", "confidence": 1.0,
                    "action": {"gap_ms": int((time.time() - prev_ok) * 1000)},
                    "evidence": {"reason": "连续读取失败"},
                })

    def _handle_frame(self, frame: Frame) -> None:
        """去抖提交（debounce）。

        单次采样内部由多次 ReadProcessMemory 组成，可能读到"跨帧混合态"。
        规则：一次状态变化必须**在下一帧仍然成立**才提交为事件；只出现一帧
        就回退的抖动被丢弃。`confirm_frames=1` 关闭该保护（逐帧提交）。

        `_committed` 始终是"最后一个已提交的世界状态"，diff 一律用它做基准，
        因此去抖不会丢动作（延迟最多一个采样周期）。
        """
        self._last_ok_t = time.time()
        if getattr(self, "_gap_open", False):
            self._gap_open = False

        # 首帧：开新局
        if self._committed is None:
            self._open_run(frame)
            self._committed = frame
            self._last_seen = frame
            return

        if frame.signature() == self._committed.signature():
            self._last_seen = frame
            self._dropped += 1
            return

        if self.cfg.confirm_frames >= 2 and self._last_seen is not None and \
                frame.signature() != self._last_seen.signature():
            # 变化尚未稳定：等下一帧确认（不做任何提交）
            self._last_seen = frame
            return

        prev = self._committed
        self._committed = frame
        self._last_seen = frame
        self._prev = prev
        self._commit(prev, frame)

    def _commit(self, prev: Frame, cur: Frame) -> None:
        # 阶段切换：战斗开始/结束
        self._maybe_combat_transition(prev, cur)

        if prev.signature() == cur.signature():
            self._dropped += 1
            return

        ctx = {"anchor": self._cur_anchor_ref()}
        events = diff_frames(prev, cur, ctx)
        for ev in events:
            self._emit(ev)

        if self.cfg.save_frames:
            self._emit_frame_record(cur)

        # 回合推进：写新回合快照 + 归档上一回合
        if prev.round is not None and cur.round is not None and cur.round != prev.round:
            self._archive_round(prev.round)
            if cur.phase == PHASE_SHOP:
                self._rounds_started += 1
                self._write_shop_snapshot(cur)

        # 回到标题 = 本局结束
        if cur.phase == PHASE_TITLE and prev.phase != PHASE_TITLE:
            self._emit({
                "type": "run_end", "round": prev.round, "phase": PHASE_TITLE,
                "source": "recorder", "confidence": 1.0,
                "action": {"reason": "back_to_title", "last_round": prev.round},
                "evidence": {"hp": prev.hp},
            })
            if self.cfg.auto_stop_on_title:
                self.stop("run_end")

    def _maybe_combat_transition(self, prev: Frame, cur: Frame) -> None:
        started = (prev.phase != PHASE_COMBAT and cur.phase == PHASE_COMBAT)
        ended = (prev.phase == PHASE_COMBAT and cur.phase != PHASE_COMBAT)
        if started:
            self._combat_open = True
            self._hp_before_combat = prev.hp
            snap = self._write_combat_snapshot(prev, cur)
            self._combat_snapshot_ref = snap
            self._emit({
                "type": "combat_start", "round": cur.round, "phase": cur.phase,
                "source": "recorder", "confidence": 0.95,
                "action": {"anchor": snap},
                "evidence": {"combat_count": cur.combat_count, "hp": prev.hp},
            })
        elif ended and self._combat_open:
            self._combat_open = False
            result = None
            if cur.combat_last_type == COMBAT_EVENT_WIN:
                result = "Win"
            elif cur.combat_last_type == COMBAT_EVENT_LOSS:
                result = "Loss"
            self._emit({
                "type": "combat_end", "round": prev.round, "phase": cur.phase,
                "source": "recorder", "confidence": 0.9,
                "action": {"result": result,
                           "hp_before": self._hp_before_combat,
                           "hp_after": cur.hp},
                "evidence": {"combat_last_type": cur.combat_last_type},
            })

    # ---------------- 局 ----------------
    def _open_run(self, frame: Frame) -> None:
        now = datetime.now()
        root = Path(self.cfg.out_dir)
        # 同一秒内多次开录（人为反复点按钮）不能覆盖已有对局目录
        run_id = new_run_id(now, 1)
        ordinal = 1
        while (root / run_id).exists() and ordinal < 100:
            ordinal += 1
            run_id = new_run_id(now, ordinal)
        self.run_id = run_id
        self.store = RunStore(root, run_id, compress=self.cfg.compress)
        meta = {
            "schema": SCHEMA_VERSION,
            "run_id": run_id,
            "started_at": now.isoformat(timespec="seconds"),
            "ended_at": None,
            "end_reason": None,
            "incomplete": False,
            "joined_mid_run": bool(frame.round and frame.round > 1),
            "game": {"pid": getattr(getattr(self.bot, "memory_reader", None), "pid", None)},
            "character": frame.character,
            "mode": "unknown",
            "source": "human",
            "grid": [7, 9],
            "sampler": {"interval_ms": self.cfg.interval_ms},
            "recorder": {"version": "4.0.0", "config": self.cfg.to_dict()},
            "notes": "hp 取 Game.tries 语义成员（配置 member_hp），见 docs/recorder_design.md §10",
        }
        try:
            self.store.open(meta)
        except StoreError as e:
            self._err(str(e))
            self.store = None
            return
        self._t0 = time.time()
        self._rounds_started = 1 if frame.round else 0
        self._write_shop_snapshot(frame)
        self._emit({
            "type": "run_start", "round": frame.round, "phase": frame.phase,
            "source": "recorder", "confidence": 1.0,
            "action": {"joined_mid_run": meta["joined_mid_run"]},
            "evidence": {"gold": frame.gold, "hp": frame.hp},
        })

    def _cur_anchor_ref(self) -> Optional[str]:
        return self._shop_snapshot_ref

    def _write_shop_snapshot(self, frame: Frame) -> None:
        if not self.store:
            return
        name = f"R{int(frame.round or 0):02d}_shop_open"
        data = frame.to_snapshot_state()
        data["round"] = frame.round
        data["shop_meta"] = {"reroll_cost": None,
                             "note": "reroll 成本取 gold_delta，见 docs §10"}
        try:
            self._shop_snapshot_ref = self.store.write_snapshot(name, data)
        except StoreError as e:
            self._err(str(e))

    def _write_combat_snapshot(self, prev: Frame, cur: Frame) -> Optional[str]:
        """开战瞬时快照：玩家摆盘（战斗帧读到）+ 对手摆盘 + 开战前商店。

        背包取 `cur`（战斗场景里才完整可读），商店/血量取 `prev`（开战前的
        商店阶段状态）——两者拼起来才是"带着什么商店资源、摆成什么样去开战"。
        """
        if not self.store:
            return None
        data = cur.to_snapshot_state()
        data["round"] = prev.round
        data["shop"] = [{"slot": s, "id": i, "price": pr, "normal_price": np_,
                         "on_sale": bool(osale), "free": bool(fr),
                         "bought": bool(bt), "reserved": bool(rv)}
                        for (s, i, pr, np_, osale, fr, bt, rv) in prev.shop]
        data["combat"] = {"count": cur.combat_count, "hp": prev.hp,
                          "hp_before": prev.hp}
        try:
            lineups = self.bot.item_reader.read_fight_lineups()
        except Exception:  # noqa: BLE001
            lineups = None
        if lineups:
            data["opponent"] = to_v4(lineups.get("opponent") or [],
                                     self._read_opponent_class(), prev.round)
            character = prev.character or getattr(cur, "character", None)
            player = to_v4(lineups.get("player") or [], character, prev.round)
            if player.get("items"):
                data["backpack_combat"] = player
        name = f"R{int(prev.round or 0):02d}_combat_start"
        try:
            return self.store.write_snapshot(name, data)
        except StoreError as e:
            self._err(str(e))
            return None

    def _read_opponent_class(self) -> Optional[str]:
        try:
            if self._combat_reader is not None:
                return self._combat_reader.read_opponent_class()
        except Exception:  # noqa: BLE001
            pass
        return None

    def _archive_round(self, rnd: Optional[int]) -> None:
        if self.store is None or rnd is None:
            return
        self.store.archive_round(int(rnd))

    def _finish(self, reason: str) -> None:
        if self._finished:
            return
        self._finished = True
        if self.store is None:
            return
        stats = self.stats()
        try:
            self.store.finish(end_reason=reason,
                              incomplete=bool(self._gaps),
                              sampler={"interval_ms": self.cfg.interval_ms,
                                       "read_cost_ms_avg": round(self._read_cost_ms, 1),
                                       "dropped_frames": self._dropped,
                                       "gaps": self._gaps},
                              stats={"events": self._event_count,
                                     "rounds": self._rounds_started})
        except Exception as e:  # noqa: BLE001
            self._err(f"收尾失败: {e}")
        if self.on_event:
            try:
                self.on_event({"type": "recorder_stopped", "reason": reason,
                               "stats": stats})
            except Exception:  # noqa: BLE001
                pass
        self.store = None

    # ---------------- 写事件 ----------------
    def _emit(self, event: dict) -> None:
        if self.store is None:
            return
        if self._event_count >= self.cfg.max_events_per_run:
            self._err(f"事件数超过上限 {self.cfg.max_events_per_run}，自动停止记录")
            self.stop("limit")
            return
        self._seq += 1
        self._event_count += 1
        ev = {"seq": self._seq,
              "t": round(time.time() - self._t0, 3),
              "wall": datetime.now().isoformat(timespec="milliseconds")}
        ev.update(event)
        try:
            self.store.append_event(ev)
        except StoreError as e:
            self._err(str(e))
            return
        if self.on_event:
            try:
                self.on_event(ev)
            except Exception:  # noqa: BLE001
                pass

    def emit_action(self, kind: str, params: Optional[dict] = None,
                    ok: bool = True) -> None:
        """AI 主动上报一个动作（source=bot，confidence=1.0）。不记录时是空操作。"""
        if not self.cfg.capture_bot or self.store is None or self._prev is None:
            return
        with self._lock:
            self._emit({
                "type": kind, "round": self._prev.round, "phase": self._prev.phase,
                "source": "bot", "confidence": 1.0,
                "action": dict(params or {}),
                "evidence": {"ok": bool(ok)},
            })

    def _emit_frame_record(self, frame: Frame) -> None:
        self._emit({
            "type": "frame", "round": frame.round, "phase": frame.phase,
            "source": "recorder", "confidence": 1.0,
            "action": {},
            "delta": {"gold": frame.gold, "hp": frame.hp,
                      "shop": _shop_diff(self._prev or frame, frame),
                      "items": [list(x) for x in frame.backpack]},
            "evidence": {},
        })

    def _poll_combat(self) -> Optional[dict]:
        """CombatLog 轮询（用于战斗起止与胜负）。不可用时返回 None。"""
        if self._combat_reader is None:
            self._combat_reader = self._make_combat_reader()
        if self._combat_reader is None:
            return None
        try:
            return self._combat_reader.poll()
        except Exception as e:  # noqa: BLE001
            self._last_error = f"CombatLog 轮询失败: {e}"
            return None

    def _make_combat_reader(self):
        """复用 bot 已打开的进程句柄，避免重复开进程/重复标定。"""
        try:
            from .combatlog_reader import CombatLogReader
            gr = getattr(self.bot, "godot_reader", None)
            mr = getattr(self.bot, "memory_reader", None)
            if gr is None or mr is None:
                return None
            cr = CombatLogReader(item_db=getattr(getattr(self.bot, "item_reader", None), "db", None))
            cr.reader = mr
            cr.gr = gr
            cr.pid = getattr(mr, "pid", None)
            try:
                cr._game_node = gr.get_game_node()
            except Exception:  # noqa: BLE001
                cr._game_node = None
            try:
                cr.log_node = cr._find_combatlog()
            except Exception:  # noqa: BLE001
                cr.log_node = None
            if cr.log_node is None:
                logger.info("CombatLog 未找到（不在对局中），阶段判定退化为场景启发式")
                return None
            return cr
        except Exception as e:  # noqa: BLE001
            logger.info("CombatLog 读取器初始化失败（退化为场景启发式）: %s", e)
            return None

    def _err(self, msg: str) -> None:
        self._last_error = msg
        logger.warning("[记录器] %s", msg)
        if self.on_error:
            try:
                self.on_error(msg)
            except Exception:  # noqa: BLE001
                pass

