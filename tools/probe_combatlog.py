# -*- coding: utf-8 -*-
"""probe_combatlog.py — 在活体游戏进程上标定 CombatLog / CombatEvent 内存布局。

只读探针（不改游戏进程）：
  1. 找到游戏窗口 → PID → MemoryReader → GodotReader（RVA 取 config，无效则自动发现）
  2. 全树 BFS 枚举所有 res://Core/CombatLog.gd 节点
  3. 成员逐个 dump，用语义锚点锁定（OBJECT→节点名/脚本路径，ARRAY→元素类型/脚本）
  4. 锚定 events 数组后解析 CombatEvent（id/timestamp/type/params/origin）验证布局

用法：
  python tools/probe_combatlog.py            # 完整标定报告
  python tools/probe_combatlog.py --tail 20  # 只看最近 20 条事件
"""
from __future__ import annotations

import sys
from collections import deque
from pathlib import Path
from typing import Any, List, Optional, Tuple

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))

from core.godot_probe import discover_os_singleton_rva  # noqa: E402
from core.godot_reader import GodotReader  # noqa: E402
from core.memory_reader import MemoryReader  # noqa: E402
from core.window_manager import WindowManager  # noqa: E402

COMBATLOG_SCRIPT = "res://Core/CombatLog.gd"
COMBATEVENT_SCRIPT = "res://Core/CombatEvent.gd"

# CombatLog 成员名表：基类 ResizableControl(10) + 自身按文件声明顺序。
# 用于把成员下标翻译成名字（与探针实测互相印证）。
COMBATLOG_MEMBERS = [
    # ResizableControl.gd
    "vResizeButton", "hResizeButton", "draggable", "dragPosition",
    "verticalResizing", "horizontalResizing", "resizeOffset", "dragging",
    "movedDuringDrag", "globalDragStartPosition",
    # CombatLog.gd（文件声明顺序）
    "fadedStyleboxes",
    "scrollContainer", "container", "lineArrow", "hoverHint", "dragHint",
    "buttonHint", "tutorialAni", "buttonTutorialAni", "playerDmgMeter",
    "opponentDmgMeter", "playerButton", "opponentButton", "filterPanel",
    "searchBar", "tooltipNode", "scrollTimer", "closeButton",
    "arrowTween", "scrollWithArrow", "tooltip", "warpPointNodes",
    "events", "eventNum", "timestamps", "logLines", "activeLine",
    "loggingFinished", "statLoggers", "globalStatHistories",
    "activeItemState", "activeCharacterStats", "itemsWithCooldown",
    "electricalCharges", "emitterEventToChargeInstance", "numPlayerCharges",
    "showPlayerEvents", "showOpponentEvents", "activationsState",
    "searchTerm", "scrolledToBottom", "delayedLogList", "delayListDone",
    "eventsLogged", "highlightedItem", "replayingCombat", "replayTime",
    "replaySpeed", "activeLineYBeforeFilterChange",
]

# Godot 3.x Variant::Type
VT_NAMES = {
    0: "NIL", 1: "BOOL", 2: "INT", 3: "REAL", 4: "STRING", 5: "VEC2",
    6: "RECT2", 7: "VEC3", 8: "TF2D", 9: "PLANE", 10: "QUAT", 11: "AABB",
    12: "BASIS", 13: "TRANSFORM", 14: "COLOR", 15: "NODEPATH", 16: "RID",
    17: "OBJECT", 18: "DICT", 19: "ARRAY", 20: "POOLByteArray",
    21: "POOLIntArray", 22: "POOLRealArray", 23: "POOLStringArray",
    24: "POOLVector2Array", 25: "POOLVector3Array", 26: "POOLColorArray",
}

EventTypeNames = {
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


class VariantReader:
    """带布局探测的 Variant 读取器。OBJECT/ARRAY/DICTIONARY 的内部布局
    在候选偏移间探测，用语义校验（节点名/脚本路径/元素类型）锁定后缓存。"""

    def __init__(self, gr: GodotReader):
        self.gr = gr
        self.obj_off: Optional[int] = None        # OBJECT: 对象指针在 union+off
        self.arr_vec_off: Optional[int] = None    # ARRAY: Array 对象内 Vector 偏移
        self.dict_vec_off: Optional[int] = None   # DICT: buckets Vector 在 HashMap+off
        self.elem_key_off: Optional[int] = None   # ListElement: key Variant 偏移
        self.elem_next_off: Optional[int] = None  # ListElement: next 指针偏移

    # ---- 基础 ----
    def vtype(self, addr: int) -> Optional[int]:
        return self.gr._read_int(addr, 4)

    def vname(self, addr: int) -> str:
        t = self.vtype(addr)
        return VT_NAMES.get(t, f"T{t}")

    def read_scalar(self, addr: int) -> Any:
        t = self.vtype(addr)
        if t == 2:
            return self.gr._read_int(addr + 8, 8)
        if t == 3:
            return self.gr._read_double(addr + 8)
        if t == 1:
            d = self.gr.reader.read(addr + 8, 1)
            return bool(d[0]) if d else None
        if t == 4:
            return self.gr._read_godot_string(self.gr._ptr(addr + 8))
        return None

    # ---- OBJECT ----
    def read_object(self, addr: int, want_script: Optional[str] = None) -> Optional[int]:
        """返回 Object*。探测 union 里 {id,obj}(obj 在 +8) / {obj,id}(在 +0)。"""
        order = ((8, 0) if self.obj_off is None
                 else ((self.obj_off, ) if self.obj_off == 8 else (0, 8)))
        for off in order:
            p = self.gr._ptr(addr + 8 + off)
            if not p or p < 0x10000 or p > 0x7FFFFFFFFFFF:
                continue
            if want_script is None:
                # 无目标脚本时用「能读出节点名」作为语义校验来锁定偏移
                if self.gr.node_name(p) is not None or \
                        self.gr.node_script_path(p) is not None:
                    self.obj_off = off
                    return p
                if self.obj_off is not None:
                    return p
                continue
            sp = self.gr.node_script_path(p)
            if sp == want_script:
                self.obj_off = off
                return p
        # 已锁定时按锁定偏移兜底返回（origin 可能是任意对象）
        if want_script is None and self.obj_off is not None:
            p = self.gr._ptr(addr + 8 + self.obj_off)
            if p and 0x10000 < p <= 0x7FFFFFFFFFFF:
                return p
        return None

    # ---- ARRAY ----
    def array_cow(self, var_addr: int) -> Optional[int]:
        """Variant(ARRAY) → CowData<Variant> 元素区指针。"""
        arr_obj = self.gr._ptr(var_addr + 8)
        if not arr_obj or arr_obj < 0x10000:
            return None
        for vec_off in (0, 8):
            cow = self.gr._ptr(arr_obj + vec_off)
            if not cow or cow < 0x10000:
                continue
            n = self.gr._cow_count(cow)
            if n is None or n < 0 or n > 1000000:
                continue
            if n > 0:
                t = self.vtype(cow)
                if t is None or t > 26:
                    continue
            self.arr_vec_off = vec_off
            return cow
        return None

    def array_len(self, cow: Optional[int]) -> int:
        if not cow:
            return 0
        return self.gr._cow_count(cow) or 0

    # ---- DICTIONARY ----
    def dict_items(self, var_addr: int, max_items: int = 256) -> List[Tuple[Any, Any]]:
        """Variant(DICT) → [(key, value)]。HashMap ListElement 链遍历，
        key 偏移用「key 是可读 STRING」锚定。"""
        d_obj = self.gr._ptr(var_addr + 8)
        map_obj = self.gr._ptr(d_obj) if d_obj and d_obj > 0x10000 else None
        if not map_obj or map_obj < 0x10000:
            return []
        buckets_cow = None
        for vec_off in (0, 8):
            cow = self.gr._ptr(map_obj + vec_off)
            if not cow or cow < 0x10000:
                continue
            nb = self.gr._cow_count(cow)
            if nb is None or nb <= 0 or nb > 1 << 22:
                continue
            buckets_cow = cow
            self.dict_vec_off = vec_off
            break
        if not buckets_cow:
            return []
        nb = self.gr._cow_count(buckets_cow) or 0
        out: List[Tuple[Any, Any]] = []
        for i in range(min(nb, 8192)):
            el = self.gr._ptr(buckets_cow + i * 8)
            hops = 0
            while el and el > 0x10000 and hops < 64:
                hops += 1
                kv = self._read_element(el)
                if kv is None:
                    break
                out.append(kv)
                if len(out) >= max_items:
                    return out
                el = self._element_next(el)
        return out

    def _locate_key_off(self, el: int) -> Optional[int]:
        for koff in (24, 16, 32, 40, 8, 48):
            if self.vtype(el + koff) == 4:
                s = self.gr._read_godot_string(self.gr._ptr(el + koff + 8))
                if s:
                    return koff
        return None

    def _read_element(self, el: int) -> Optional[Tuple[Any, Any]]:
        koff = self.elem_key_off
        if koff is None:
            koff = self._locate_key_off(el)
            if koff is None:
                return None
            self.elem_key_off = koff
        return (self.read_scalar(el + koff), self.read_value(el + koff + 24, 2))

    def _element_next(self, el: int) -> Optional[int]:
        if self.elem_next_off is not None:
            p = self.gr._ptr(el + self.elem_next_off)
            return p if p and p > 0x10000 else None
        for noff in (0, 8, 16):
            nxt = self.gr._ptr(el + noff)
            if nxt and nxt > 0x10000 and self._locate_key_off(nxt) is not None:
                self.elem_next_off = noff
                return nxt
        return None

    # ---- 通用 ----
    def describe(self, addr: int) -> str:
        """单 Variant 的诊断描述（类型 + 语义预览）。"""
        t = self.vtype(addr)
        name = VT_NAMES.get(t, f"T{t}")
        if t == 2:
            return f"INT={self.gr._read_int(addr + 8, 8)}"
        if t == 3:
            return f"REAL={self.gr._read_double(addr + 8)}"
        if t == 1:
            return f"BOOL={self.read_scalar(addr)}"
        if t == 4:
            return f"STR={self.read_scalar(addr)!r}"
        if t == 17:
            p = self.read_object(addr)
            if not p:
                return f"OBJ=<unreadable raw={hex(self.gr._ptr(addr + 8) or 0)}>"
            sp = self.gr.node_script_path(p) or ""
            nm = self.gr.node_name(p)
            return f"OBJ={hex(p)} name={nm} script={sp.rsplit('/', 1)[-1] or '-'}"
        if t == 19:
            cow = self.array_cow(addr)
            n = self.array_len(cow)
            first = "?"
            if cow and n > 0:
                ft = self.vname(cow)
                if ft == "OBJECT":
                    for script in (COMBATEVENT_SCRIPT,):
                        op = self.read_object(cow, script)
                        if op:
                            first = "CombatEvent"
                            break
                    else:
                        op = self.read_object(cow)
                        sp = self.gr.node_script_path(op) if op else None
                        first = sp.rsplit("/", 1)[-1] if sp else "Object"
                else:
                    first = ft
            return f"ARRAY len={n} first={first}"
        if t == 18:
            items = self.dict_items(addr, max_items=6)
            return f"DICT n≈{len(items)} {items[:3]}"
        return name


def connect() -> Tuple[GodotReader, MemoryReader]:
    wm = WindowManager()
    w = wm.find_game_window()
    if not w:
        print("!! 未找到游戏窗口（Backpack Battles）")
        sys.exit(1)
    print(f"* 游戏窗口: PID={w.pid}")
    reader = MemoryReader(w.pid)
    gr = GodotReader(reader)
    rva = gr.off.get("os_singleton_rva", 0)
    if not rva or not gr.get_root():
        print("* RVA 不可用，自动发现 OS::singleton ...")
        rva = discover_os_singleton_rva(reader, gr.off)
        if not rva:
            print("!! OS::singleton 定位失败")
            sys.exit(1)
        gr.off["os_singleton_rva"] = rva
        print(f"* 自动发现 RVA = {hex(rva)}")
    else:
        print(f"* 使用 config RVA = {hex(rva)}")
    print(f"* root = {hex(gr.get_root())}")
    return gr, reader


def find_all_by_script(gr: GodotReader, script_path: str) -> List[int]:
    root = gr.get_root()
    out: List[int] = []
    if not root:
        return out
    dq = deque([root])
    seen = {root}
    scanned = 0
    while dq:
        n = dq.popleft()
        scanned += 1
        if gr.node_script_path(n) == script_path:
            out.append(n)
        for c in gr.get_children(n):
            if c not in seen:
                seen.add(c)
                dq.append(c)
    print(f"* BFS 扫描 {scanned} 个节点，命中 {len(out)} 个 {script_path}")
    return out


def main() -> None:
    tail = 20
    if "--tail" in sys.argv:
        tail = int(sys.argv[sys.argv.index("--tail") + 1])

    gr, _reader = connect()
    vr = VariantReader(gr)

    nodes = find_all_by_script(gr, COMBATLOG_SCRIPT)
    if not nodes:
        print("!! 找不到 CombatLog 节点（可能不在对局中，战斗场景未实例化）")
        sys.exit(2)

    for node in nodes:
        print(f"\n===== CombatLog 节点 @ {hex(node)} =====")
        si = gr._script_instance(node)
        members_addr = gr._ptr(si + gr.off["gdscript_members_off"])
        count = gr._cow_count(members_addr) or 0
        print(f"成员数: {count}（名字表 {len(COMBATLOG_MEMBERS)} 条）")

        events_cow = None
        events_idx = None
        for i in range(count):
            va = members_addr + i * gr.off["variant_size"]
            name = COMBATLOG_MEMBERS[i] if i < len(COMBATLOG_MEMBERS) else f"?{i}"
            desc = vr.describe(va)
            print(f"  [{i:2d}] {name:32s} {desc}")
            if name == "events" and desc.startswith("ARRAY"):
                cow = vr.array_cow(va)
                if cow and vr.array_len(cow) > 0:
                    first = vr.read_object(cow, COMBATEVENT_SCRIPT)
                    if first:
                        events_cow, events_idx = cow, i

        if events_cow is None:
            print("\n  * events 数组为空或不含 CombatEvent —— 当前没有可导出的日志。")
            print("    eventNum 上次的值见上方（>0 表示上次战斗的事件数）。")
            continue

        n = vr.array_len(events_cow)
        print(f"\n  == events @ [{events_idx}]，共 {n} 条；布局: "
              f"OBJ.obj@union+{vr.obj_off} ARR.vec@Array+{vr.arr_vec_off} "
              f"DICT.buckets@Map+{vr.dict_vec_off} "
              f"ELEM.key@+{vr.elem_key_off} next@+{vr.elem_next_off}")

        lo = max(0, n - tail)
        for ei in range(lo, n):
            ea = events_cow + ei * gr.off["variant_size"]
            ev = vr.read_object(ea, COMBATEVENT_SCRIPT)
            if not ev:
                print(f"  #{ei}: <不可读>")
                continue
            m = gr._ptr(gr._script_instance(ev) + gr.off["gdscript_members_off"])
            mv = lambda k: m + k * gr.off["variant_size"]  # noqa: E731
            eid = gr._read_int(mv(0) + 8, 8)
            ts = gr._read_double(mv(1) + 8)
            etype = gr._read_int(mv(4) + 8, 8)
            target = vr.read_scalar(mv(6))
            odesc = vr.describe(mv(3))
            params = vr.read_value(mv(7), 2) if vr.vtype(mv(7)) == 18 else \
                vr.dict_items(mv(7))
            print(f"  #{eid} t={ts:.2f} {EventTypeNames.get(etype, etype):20s} "
                  f"target={target} origin={odesc} params={params}")

    print("\n* 标定结束。")


if __name__ == "__main__":
    main()
