# -*- coding: utf-8 -*-
"""corpus_fold.py — 把原始记录折叠成训练语料（decisions / lineups）

原始层（raw/）如实记录每一次摆放、每一次锁定切换。本工具负责**压缩**：

1. **决策点切分**：`round_start / buy / sell / reroll / combine / combat_start`
   是决策点；摆盘与锁定切换不是——它们只更新"当前状态"；
2. **净零丢弃**：相邻决策点之间的连续操作段，若"段首状态"与"段尾状态"
   等价（背包多重集、储物箱、每槽 reserved 完全相同），整段丢弃。
   反复摆盘、反复切换锁定都因此归零；
3. **锁定归并**：段内有净锁定变化时，每槽只保留一条 `set_reserved(slot, final)`；
4. **摆盘不产生动作**：最终背包体现在 `next_state.backpack`，不产 move/rotate。

输出（写进 <run>/corpus/）::

    decisions.jsonl   每行 = 一个决策点（state + actions + next_state + label）
    lineups.jsonl     每行 = 一个回合的开战摆盘（摆盘 AI 的主数据）

用法::

    python -X utf8 tools/corpus_fold.py output/records/<run_id> [更多目录...]
    python -X utf8 tools/corpus_fold.py --all output/records
"""
from __future__ import annotations

import argparse
import json
import os
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Dict, Iterable, List, Optional, Tuple

_REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _REPO not in sys.path:
    sys.path.insert(0, _REPO)

from core.store import iter_run_events, load_meta, load_snapshot  # noqa: E402

# 决策点事件（切段）
DECISION_TYPES = {"round_start", "buy", "sell", "reroll", "combine", "combat_start"}
# 过程事件（只更新状态，不切段）
PROCESS_TYPES = {"place", "move", "rotate", "gems_change", "storage_in",
                 "storage_put", "lock", "unlock"}
# 忽略事件（不影响状态等价性）
IGNORE_TYPES = {"frame", "gap", "run_start", "run_end", "carry_over",
                "combat_end", "recorder_stopped"}


@dataclass
class FoldStats:
    runs: int = 0
    decisions: int = 0
    lineups: int = 0
    dropped_zero_segments: int = 0
    folded_lock_toggles: int = 0
    folded_placement_ops: int = 0
    placement_only_segments: int = 0   # 只有摆盘净变化、不产样本的段
    skipped_events: int = 0
    unknown_changes: int = 0

    def merge(self, other: "FoldStats") -> None:
        for f in self.__dataclass_fields__:
            setattr(self, f, getattr(self, f) + getattr(other, f))

    def as_dict(self) -> dict:
        return {f: getattr(self, f) for f in self.__dataclass_fields__}


# ---------------------------------------------------------------------------
# 状态（折叠期维护的"当前世界"）
# ---------------------------------------------------------------------------
@dataclass
class WorldState:
    """折叠器维护的当前状态。等价性只比对这些字段。"""

    round: Optional[int] = None
    gold: Optional[int] = None
    hp: Optional[int] = None
    backpack: Dict[Tuple, int] = field(default_factory=dict)   # 规范元组 → 数量
    storage: Dict[Tuple, int] = field(default_factory=dict)
    reserved: Dict[int, Tuple[str, bool]] = field(default_factory=dict)  # slot → (id, 锁定)
    shop: Dict[int, Tuple] = field(default_factory=dict)

    def key(self) -> Tuple:
        """等价性键：背包/储物箱多重集 + 每槽锁定状态。"""
        return (_multiset_key(self.backpack), _multiset_key(self.storage),
                tuple(sorted((s, v[1]) for s, v in self.reserved.items())))

    def copy(self) -> "WorldState":
        return WorldState(round=self.round, gold=self.gold, hp=self.hp,
                          backpack=dict(self.backpack), storage=dict(self.storage),
                          reserved=dict(self.reserved), shop=dict(self.shop))

    def to_json(self) -> dict:
        return {
            "round": self.round, "gold": self.gold, "hp": self.hp,
            "backpack": _multiset_items(self.backpack),
            "storage": _multiset_items(self.storage),
            "shop": [{"slot": s, "id": v[0], "price": v[1],
                      "normal_price": v[2], "on_sale": v[3], "free": v[4],
                      "bought": v[5], "reserved": v[7] if len(v) > 7 else False}
                     for s, v in sorted(self.shop.items())],
        }


def _multiset_key(d: Dict[Tuple, int]) -> Tuple:
    return tuple(sorted((k, v) for k, v in d.items() if v > 0))


def _multiset_items(d: Dict[Tuple, int]) -> List[dict]:
    out = []
    for sig, n in sorted(d.items()):
        if n <= 0:
            continue
        item = {"id": sig[0], "at": [sig[1], sig[2]], "r": sig[3],
                "gems": list(sig[4])}
        if len(sig) > 5 and sig[5] is not None and int(sig[5]) >= 0:
            item["in"] = int(sig[5])
        for _ in range(n):
            out.append(dict(item))
    return out


def _sig_to_tuple(raw: Iterable) -> Tuple:
    t = tuple(raw)
    # (id, row, col, r, gems, in)：gems 需可哈希
    if len(t) >= 5:
        gems = tuple(sorted(t[4] or ()))
        parent = t[5] if len(t) > 5 else -1
        return (t[0], int(t[1]), int(t[2]), int(t[3]), gems,
                -1 if parent is None else int(parent))
    return t


# ---------------------------------------------------------------------------
# 事件 → 状态更新
# ---------------------------------------------------------------------------
def apply_event(state: WorldState, ev: dict) -> WorldState:
    """把一条原始事件应用到折叠状态（返回新对象，不改入参）。"""
    st = state.copy()
    t = ev.get("type")
    a = ev.get("action") or {}
    d = ev.get("delta") or {}

    if st.round is None and ev.get("round") is not None:
        st.round = ev.get("round")

    if t == "round_start":
        st.round = a.get("to_round", st.round)
        if d.get("gold") is not None:
            st.gold = d.get("gold")
        if d.get("hp") is not None:
            st.hp = d.get("hp")
        return st

    if t == "combat_end":
        if a.get("hp_after") is not None:
            st.hp = a.get("hp_after")
        return st

    if t in ("buy", "sell", "reroll"):
        gd = (d.get("gold") if d.get("gold") is not None
              else -(a.get("price") or a.get("cost") or 0))
        if t == "buy" and d.get("gold") is None and a.get("price") is not None:
            gd = -int(a["price"])
        if t == "sell" and d.get("gold") is None and a.get("price") is not None:
            gd = int(a["price"])
        if gd is not None and st.gold is not None:
            st.gold = st.gold + int(gd)

    if t in ("lock", "unlock"):
        slot = a.get("slot")
        if slot is not None:
            cur = st.reserved.get(int(slot))
            item_id = a.get("id") or (cur[0] if cur else None)
            st.reserved[int(slot)] = (item_id, t == "lock")
        return st

    if t == "place":
        sig = _sig_to_tuple((a.get("id"), (a.get("at") or [0, 0])[0],
                             (a.get("at") or [0, 0])[1], a.get("r", 0),
                             _gems_placeholder(a), -1))
        _add(st.backpack, sig)
        if a.get("from") == "storage":
            _remove_any(st.storage, a.get("id"))
        return st

    if t in ("storage_in", "storage_put"):
        sig = _sig_to_tuple((a.get("id"), (a.get("at") or [0, 0])[0],
                             (a.get("at") or [0, 0])[1], a.get("r", 0),
                             (), -1))
        if t == "storage_in":
            _remove_any(st.backpack, a.get("id"))
        _add(st.storage, (sig[0], sig[1], sig[2], sig[3], ()))
        return st

    if t in ("move", "rotate", "gems_change"):
        _apply_transform(st, t, a)
        return st

    if t == "sell":
        if a.get("from") == "storage":
            _remove_any(st.storage, a.get("id"))
        else:
            _remove_any(st.backpack, a.get("id"))
        return st

    if t == "combine":
        for inp in (a.get("inputs") or []):
            _remove_any(st.backpack, inp.get("id"))
        out = a.get("output") or {}
        if out:
            at = out.get("at") or [0, 0]
            _add(st.backpack, (out.get("id"), int(at[0]), int(at[1]),
                               int(out.get("r", 0)), (), -1))
        return st

    if t == "combat_start":
        if a.get("hp") is not None:
            st.hp = a.get("hp")
        return st

    return st


def _gems_placeholder(a: dict) -> Tuple:
    return tuple(sorted(a.get("gems") or ()))


def _add(d: Dict[Tuple, int], sig: Tuple) -> None:
    d[sig] = d.get(sig, 0) + 1


def _remove_any(d: Dict[Tuple, int], item_id: Optional[str]) -> None:
    """删掉 id 匹配的一件（优先数量最多的规范元组）。"""
    if item_id is None:
        return
    for sig in sorted(d.keys()):
        if sig[0] == item_id and d.get(sig, 0) > 0:
            d[sig] -= 1
            if d[sig] <= 0:
                d.pop(sig, None)
            return


def _apply_transform(st: WorldState, t: str, a: dict) -> None:
    """move/rotate/gems_change：把匹配的物品替换成新签名。"""
    item_id = a.get("id")
    if item_id is None:
        return
    from_at = a.get("from")
    to_at = a.get("to") or a.get("at")
    for sig in sorted(st.backpack.keys()):
        if sig[0] != item_id:
            continue
        st.backpack[sig] -= 1
        if st.backpack[sig] <= 0:
            st.backpack.pop(sig, None)
        if t == "move" and isinstance(to_at, (list, tuple)) and len(to_at) == 2:
            new_sig = (sig[0], int(to_at[0]), int(to_at[1]),
                       int(a.get("r", sig[3])), sig[4], sig[5])
        elif t == "rotate":
            new_sig = (sig[0], sig[1], sig[2], int(a.get("to_r", sig[3])), sig[4], sig[5])
        else:  # gems_change
            new_sig = (sig[0], sig[1], sig[2], sig[3],
                       tuple(sorted(a.get("to") or sig[4])), sig[5])
        _add(st.backpack, new_sig)
        return


# ---------------------------------------------------------------------------
# 折叠主逻辑
# ---------------------------------------------------------------------------
@dataclass
class Segment:
    """相邻决策点之间的过程事件累积。"""

    events: List[dict] = field(default_factory=list)
    state_start: Optional[WorldState] = None
    state_end: Optional[WorldState] = None

    def net_zero(self) -> bool:
        if self.state_start is None or self.state_end is None:
            return False
        return self.state_start.key() == self.state_end.key()


@dataclass
class FoldOptions:
    """折叠参数（与 config.yaml 的 recorder.fold 对应）。"""

    drop_zero_net: bool = True     # 净零过程段丢弃（反复摆盘/反复锁定的过滤器）
    export_traces: bool = False    # 额外导出摆盘搜索轨迹（RL 热启动用）
    merge_qty: bool = False        # 预留：连续同名同价买入合并为 qty（当前未实现）

    @classmethod
    def from_dict(cls, d: Optional[dict]) -> "FoldOptions":
        o = cls()
        for f in ("drop_zero_net", "export_traces", "merge_qty"):
            if d and d.get(f) is not None:
                setattr(o, f, bool(d[f]))
        return o


def fold_run(run_dir: Path, options: Optional[FoldOptions] = None
             ) -> Tuple[List[dict], List[dict], FoldStats, List[dict]]:
    """把一个对局目录折叠成 (decisions, lineups, stats, traces)。

    `traces` 仅在 `options.export_traces` 为真时非空（摆盘搜索轨迹，RL 热启动用）。
    """
    run_dir = Path(run_dir)
    opts = options or FoldOptions()
    meta = load_meta(run_dir)
    stats = FoldStats(runs=1)
    traces: List[dict] = []

    state = _initial_state(run_dir, meta)
    decisions: List[dict] = []
    lineups: List[dict] = []

    # 按决策点切段
    pending: List[dict] = []      # 当前决策点之后的过程事件
    pending_state_start = state.copy()
    last_decision: Optional[Tuple[dict, WorldState]] = None  # (样本, 决策前状态)
    last_round: Optional[int] = None

    def flush_segment(cur: WorldState) -> WorldState:
        """结算当前过程段，返回"下一个决策的 state 基准"。

        规则（docs/recorder_design.md §4.2）：
        * 段内净零 → 整段丢弃；
        * 净锁定变化非空 → 产出一条只含 set_reserved 的决策样本
          （锁定是真实决策：零花费、影响下回合可购买集合）；
        * 只有摆盘净变化 → 不产样本（摆盘交给 RL），状态继续累积。
        """
        nonlocal pending, pending_state_start, last_decision
        if not pending:
            pending_state_start = cur.copy()
            return cur
        seg = Segment(events=pending, state_start=pending_state_start,
                      state_end=cur)
        if opts.export_traces:
            traces.append(_trace_record(meta, last_round, seg))
        net_locks = ([] if seg.net_zero()
                     else _net_locks(seg.state_start, seg.state_end))
        if net_locks:
            # 段内第一个锁定之前的状态 = 上一个决策的 next_state（摆盘先于锁定）
            before_lock = _state_before_first_lock(seg.state_start, seg.events)
            if last_decision is not None:
                _finish_decision(last_decision, before_lock, stats, decisions)
            rec = _lock_decision(meta, seg.events, last_round, before_lock,
                                 seg.state_end, net_locks)
            decisions.append(rec)
            stats.decisions += 1
            stats.folded_lock_toggles += max(0, len(pending) - len(net_locks))
            stats.folded_placement_ops += max(0, len(pending) - len(net_locks))
            last_decision = None
        elif seg.net_zero():
            if opts.drop_zero_net:
                stats.dropped_zero_segments += 1
                stats.folded_placement_ops += len(pending)
            else:
                # 关闭净零丢弃：净零段也记成一条空动作样本（研究"反复尝试"用）
                rec = _lock_decision(meta, seg.events, last_round,
                                     seg.state_start, seg.state_end, [])
                rec["provenance"]["event"] = "zero_net_segment"
                decisions.append(rec)
                stats.decisions += 1
        else:
            # 只有摆盘净变化：不产样本、也不打断上一个决策——摆盘结果
            # 会体现在下一个决策的 state 里（这是"摆放不计入决策"的落点）。
            stats.folded_placement_ops += len(pending)
            stats.placement_only_segments += 1
        pending = []
        pending_state_start = cur.copy()
        return cur

    for rnd, ev in iter_run_events(run_dir):
        t = ev.get("type")
        if t in IGNORE_TYPES:
            if t == "combat_end":
                state = apply_event(state, ev)
            continue
        if t == "unknown_change":
            stats.unknown_changes += 1
            continue

        if t in DECISION_TYPES:
            state = flush_segment(state)
            before = state.copy()
            state = apply_event(state, ev)

            if t == "round_start":
                # 回合边界：只结算上一段并重置，本身不产样本
                if last_decision is not None:
                    _finish_decision(last_decision, before, stats, decisions)
                    last_decision = None
                last_round = rnd
                continue

            if t == "combat_start":
                if last_decision is not None:
                    _finish_decision(last_decision, before, stats, decisions)
                    last_decision = None
                snap_ref = (ev.get("action") or {}).get("anchor")
                snap = load_snapshot(run_dir, snap_ref) if snap_ref else None
                lineups.append(_lineup_record(meta, rnd, before, snap, ev))
                stats.lineups += 1
                continue

            if last_decision is not None:
                _finish_decision(last_decision, before, stats, decisions)
            last_decision = (_new_decision(meta, ev, rnd, before), before)
            continue

        if t in PROCESS_TYPES:
            if not pending:
                pending_state_start = state.copy()
            pending.append(ev)
            state = apply_event(state, ev)
            continue

        # 其它未知类型：计数但不影响折叠
        stats.skipped_events += 1

    # 收尾：最后一段过程 + 最后一个决策
    final_state = flush_segment(state)
    if last_decision is not None:
        _finish_decision(last_decision, final_state, stats, decisions)
    return decisions, lineups, stats, traces


def _initial_state(run_dir: Path, meta: dict) -> WorldState:
    """用第一回合的商店快照作为折叠起点（没有快照就从空状态开始）。"""
    st = WorldState(round=1, gold=None, hp=None)
    snaps = sorted((run_dir / "snapshots").glob("R*_shop_open.json"))
    if not snaps:
        return st
    snap = json.loads(snaps[0].read_text(encoding="utf-8"))
    st.round = snap.get("round")
    st.gold = snap.get("gold")
    st.hp = snap.get("hp")
    for item in (snap.get("backpack") or {}).get("items", []):
        at = item.get("at") or [0, 0]
        sig = (item.get("id"), int(at[0]), int(at[1]), int(item.get("r", 0)),
               tuple(sorted(item.get("gems") or [])),
               int(item["in"]) if item.get("in") is not None else -1)
        _add(st.backpack, sig)
    for item in (snap.get("storage") or []):
        at = item.get("at") or [0, 0]
        _add(st.storage, (item.get("id"), int(at[0]), int(at[1]),
                          int(item.get("r", 0)), tuple(sorted(item.get("gems") or []))))
    for slot in (snap.get("shop") or []):
        st.shop[int(slot.get("slot", -1))] = (
            slot.get("id"), slot.get("price"), slot.get("normal_price"),
            bool(slot.get("on_sale")), bool(slot.get("free")),
            bool(slot.get("bought")), None, bool(slot.get("reserved")))
        st.reserved[int(slot.get("slot", -1))] = (slot.get("id"),
                                                  bool(slot.get("reserved")))
    return st


def _net_locks(start: Optional[WorldState], end: Optional[WorldState]) -> List[dict]:
    """段内净锁定变化 → 每槽一条 set_reserved。"""
    if start is None or end is None:
        return []
    out = []
    for slot, (item_id, locked) in sorted(end.reserved.items()):
        prev = start.reserved.get(slot)
        prev_locked = bool(prev[1]) if prev else False
        if prev_locked != locked:
            out.append({"kind": "set_reserved", "slot": slot, "value": bool(locked),
                        "id": item_id})
    return out


def _new_decision(meta: dict, ev: dict, rnd: Optional[int],
                  before: WorldState) -> dict:
    a = ev.get("action") or {}
    kind = ev.get("type")
    acts: List[dict] = []
    if kind in ("buy", "sell", "reroll", "combine"):
        act: dict = {"kind": kind}
        act.update({k: v for k, v in a.items() if k in (
            "slot", "id", "price", "price_source", "normal_price", "on_sale",
            "free", "cost", "from", "inputs", "output")})
        acts.append(act)
    rec = {
        "run_id": meta.get("run_id"),
        "seq": ev.get("seq"),
        "round": rnd if rnd is not None else ev.get("round"),
        "character": meta.get("character"),
        "source": meta.get("source", "human"),
        "confidence": ev.get("confidence"),
        "state": before.to_json(),
        "actions": acts,
        "next_state": None,
        "outcome": {},
        "provenance": {"anchor": ev.get("anchor"), "event": kind},
    }
    return rec


def _trace_record(meta: dict, rnd: Optional[int],
                  seg: "Segment") -> dict:
    """摆盘搜索轨迹（仅 trace 导出时生成）：段内每一次过程操作。

    与决策样本严格分开：轨迹**不是**决策数据，只给 RL 做行为预训练/预热。
    """
    return {
        "run_id": meta.get("run_id"),
        "round": rnd,
        "ops": [{"type": ev.get("type"), "action": ev.get("action")}
                for ev in seg.events],
        "state_start": (seg.state_start.to_json() if seg.state_start else None),
        "state_end": (seg.state_end.to_json() if seg.state_end else None),
        "noisy": True,      # 人类试摆的原始轨迹，含大量无效尝试
    }


def _state_before_first_lock(start: WorldState,
                             events: List[dict]) -> WorldState:
    """重放段内事件直到第一处 lock/unlock，返回那一刻的状态。"""
    st = start.copy()
    for ev in events:
        if ev.get("type") in ("lock", "unlock"):
            return st
        st = apply_event(st, ev)
    return st


def _lock_decision(meta: dict, seg_events: List[dict], rnd: Optional[int],
                   before: WorldState, after: WorldState,
                   net_locks: List[dict]) -> dict:
    """只含锁定净变化的决策样本（摆盘变化不进来）。"""
    first = seg_events[0] if seg_events else {}
    return {
        "run_id": meta.get("run_id"),
        "seq": first.get("seq"),
        "round": rnd if rnd is not None else first.get("round"),
        "character": meta.get("character"),
        "source": meta.get("source", "human"),
        "confidence": 0.95,
        "state": before.to_json(),
        "actions": net_locks,
        "next_state": after.to_json(),
        "outcome": {},
        "provenance": {"anchor": first.get("anchor"), "event": "reservation"},
    }


def _finish_decision(decision: Tuple[dict, WorldState], after: WorldState,
                     stats: FoldStats, out: List[dict]) -> None:
    rec, _before = decision
    rec["next_state"] = after.to_json()
    out.append(rec)
    stats.decisions += 1


def _lineup_record(meta: dict, rnd: Optional[int], before: WorldState,
                   snap: Optional[dict], ev: dict) -> dict:
    lineup = (snap or {}).get("backpack_combat") or (snap or {}).get("backpack") or {}
    return {
        "run_id": meta.get("run_id"),
        "round": rnd if rnd is not None else ev.get("round"),
        "character": meta.get("character"),
        "lineup": lineup,
        "pool": {
            "gold_at_start": (snap or {}).get("gold"),
            "shop_at_start": (snap or {}).get("shop"),
            "storage_at_start": (snap or {}).get("storage"),
        },
        "context": {"hp": before.hp, "round": rnd,
                    "wins": (snap or {}).get("wins"),
                    "losses": (snap or {}).get("losses")},
        "label": {"round_result": None,
                  "final_rank": (meta.get("final") or {}).get("rank"),
                  "engine_winrate": None},
    }


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------
def fold_dir(run_dir: Path, out_dir: Optional[Path] = None,
             write: bool = True,
             options: Optional[FoldOptions] = None) -> FoldStats:
    options = options or _options_from_meta(run_dir)
    decisions, lineups, stats, traces = fold_run(run_dir, options)
    if write:
        out = Path(out_dir) if out_dir else (Path(run_dir) / "corpus")
        out.mkdir(parents=True, exist_ok=True)
        _dump_jsonl(out / "decisions.jsonl", decisions)
        _dump_jsonl(out / "lineups.jsonl", lineups)
        tpath = out / "traces.jsonl"
        if options.export_traces:
            _dump_jsonl(tpath, traces)
        elif tpath.exists():
            tpath.unlink()      # 关了开关就清掉旧产物，避免误用陈旧轨迹
    return stats


def _options_from_meta(run_dir: Path) -> FoldOptions:
    """从 meta.recorder.config.fold 读取折叠参数（记录时的生效配置）。"""
    try:
        cfg = (load_meta(run_dir).get("recorder") or {}).get("config") or {}
        return FoldOptions.from_dict(cfg.get("fold"))
    except Exception:  # noqa: BLE001
        return FoldOptions()


def _dump_jsonl(path: Path, rows: List[dict]) -> None:
    tmp = path.with_suffix(path.suffix + ".tmp")
    with open(tmp, "w", encoding="utf-8", newline="\n") as f:
        for row in rows:
            f.write(json.dumps(row, ensure_ascii=False) + "\n")
    os.replace(tmp, path)


def main(argv: Optional[List[str]] = None) -> int:
    ap = argparse.ArgumentParser(description="把原始对局记录折叠成训练语料")
    ap.add_argument("runs", nargs="*", help="对局目录（可多个）")
    ap.add_argument("--all", metavar="ROOT", help="递归折叠 ROOT 下所有对局目录")
    ap.add_argument("--out", help="输出目录（默认写到 <run>/corpus）")
    ap.add_argument("--dry-run", action="store_true", help="只统计，不写文件")
    ap.add_argument("--traces", action="store_true",
                    help="额外导出 traces.jsonl（摆盘搜索轨迹，RL 热启动用）")
    ap.add_argument("--keep-zero-net", action="store_true",
                    help="不丢弃净零过程段（保留反复尝试的痕迹，样本会变多）")
    ap.add_argument("--json", action="store_true", help="以 JSON 输出统计")
    args = ap.parse_args(argv)

    runs: List[Path] = [Path(p) for p in args.runs]
    if args.all:
        root = Path(args.all)
        runs.extend(sorted(p for p in root.iterdir()
                           if p.is_dir() and (p / "raw").exists()))
    if not runs:
        ap.print_help()
        return 2

    total = FoldStats()
    for run in runs:
        if not (run / "raw").exists():
            print(f"[跳过] {run}（没有 raw/ 目录）")
            continue
        opts = FoldOptions.from_dict({"export_traces": args.traces,
                                      "drop_zero_net": not args.keep_zero_net})
        stats = fold_dir(run, Path(args.out) if args.out else None,
                         write=not args.dry_run, options=opts)
        total.merge(stats)
        print(f"[完成] {run.name}: decisions={stats.decisions} "
              f"lineups={stats.lineups} 丢弃净零段={stats.dropped_zero_segments} "
              f"折叠锁定切换={stats.folded_lock_toggles} "
              f"折叠摆盘操作={stats.folded_placement_ops} "
              f"未归类={stats.unknown_changes}")
    if args.json:
        print(json.dumps(total.as_dict(), ensure_ascii=False, indent=2))
    return 0


if __name__ == "__main__":
    sys.exit(main())
