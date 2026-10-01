# -*- coding: utf-8 -*-
"""combatlog_reader.py — 战斗日志(CombatLog)结构性内存读取器

游戏不落盘战斗日志：CombatLog.gd 把整场战斗的事件存在内存数组
`events: Array[CombatEvent]` 里（CombatEvent.asText() 渲染成 UI 行）。
本读取器从活体进程把它原样读出，供导出工具使用。只读，不修改游戏。

内存布局全部在活体进程（Backpack Battles v1.1.7, 魔改 Godot 3.6 构建）
上标定，与原版 Godot 3.x 不同，勿按原版布局改回去：

* Variant: 24B = {type:i32 @+0, pad, union@+8}
  - INT/REAL/BOOL/STRING: 值在 union@+8（STRING 为 CowData<char> 指针）
  - OBJECT(17): union0 = 「槽地址」，真对象 = *(union0)；
    union0 为空时（RefCounted）直接用 union8。注意不是原版的 obj 直存。
* Array: priv 指针@union0；长度 u32 @priv+12；元素区指针 @priv+16
* Dictionary: priv 指针@union0；桶数组 @priv+16，桶数 u32 @桶-8；
  桶元素 = {hash@0, next@+8, key变体内联@+16(24B), 值盒指针@+40}
  值盒 = {back_ptr@0, 变体@+8}：type@+8, len@+12, INT/REAL 值@+16,
  字符串 len>0 时 UTF-16 内联@+24，len==0 时 +16 为 String 指针
* CombatLog 成员（基类 ResizableControl 10 个 + 自身按声明顺序）:
  events=32, eventNum=33, loggingFinished=37
* CombatEvent 成员: id=0, timestamp=1, parentEvent=2（**CombatEvent 对象
  引用**，读取时解引用取其 id）, origin=3（Item 节点引用或伤害源对象）,
  type=4, target=6, params=7
* 事件归属方：origin 节点沿父链找 Player/Opponent 根节点
  （战斗场景中物品直接挂在一方根下，宝石经 GemSocket 中转）

定位：Game 单例的 OBJECT 成员中按脚本路径 res://Core/CombatLog.gd 锚定
（BFS 场景树会撞上已释放的陈旧实例，不可靠）。
"""
from __future__ import annotations

import logging
import re
import struct
from collections import deque
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

from .godot_probe import discover_os_singleton_rva
from .godot_reader import GodotReader
from .item_db import ItemDB, clean_name
from .memory_reader import MemoryReader
from .window_manager import WindowManager

logger = logging.getLogger(__name__)

COMBATLOG_SCRIPT = "res://Core/CombatLog.gd"
COMBATEVENT_SCRIPT = "res://Core/CombatEvent.gd"

# CombatLog 成员下标（活体标定）
MEM_EVENTS = 32
MEM_EVENT_NUM = 33
MEM_FINISHED = 37
MEM_DELAYED = 51  # delayedLogList：日志面板关闭期间的事件都堆在这里
# 物品节点成员: descriptor=20（ItemDescriptor 对象，getTranslatedName 的真值源）
ITEM_DESCRIPTOR = 20
DESC_NAME = 6
# CombatEvent 成员下标
EV_ID, EV_TS, EV_PARENT, EV_ORIGIN, EV_TYPE, EV_TARGET, EV_PARAMS = 0, 1, 2, 3, 4, 6, 7
# Game 单例成员下标（活体标定）
GAME_MEMBER_ROUND = 65
GAME_MEMBER_CURCLASS = 83        # Game.Classes: Ranger0/Reaper1/Berserker2/Pyromancer3
GAME_MEMBER_CUR_OPPONENT = 145   # curOpponentData 字典（含对手 classI 等）
CLASSES = {0: "Ranger", 1: "Reaper", 2: "Berserker", 3: "Pyromancer"}

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

# DamageSource.Type（createEvent_Damage/Heal 的 origin）→ 关键词
# （0/1/2 实际不会出现——普攻走 createEvent_Attack 用物品作 origin）
DS_KEYWORDS = {
    0: "melee", 1: "ranged", 2: "effect", 98: "unhealing", 99: "fatigue",
    102: "regeneration", 103: "vampirism", 104: "spikes", 108: "poison",
}
DS_FALLBACK_ZH = {
    "melee": "近战", "ranged": "远程", "effect": "效果", "unhealing": "不治",
    "fatigue": "疲劳", "regeneration": "恢复", "vampirism": "吸血",
    "spikes": "尖刺", "poison": "中毒",
}


def _valid_type(t: Optional[int]) -> bool:
    return t is not None and (0 <= t <= 24 or 98 <= t <= 112)


class CombatLogReader:
    """从活体游戏进程读取战斗日志事件。"""

    def __init__(self, item_db: Optional[ItemDB] = None):
        self.item_db = item_db or ItemDB()
        self.reader: Optional[MemoryReader] = None
        self.gr: Optional[GodotReader] = None
        self.pid: Optional[int] = None
        self.log_node: Optional[int] = None
        self._game_node: Optional[int] = None
        self._desc_cache: Dict[int, Optional[str]] = {}
        self._rt_names: Optional[Dict[str, str]] = None

    # ---------------- 连接 ----------------
    def connect(self) -> bool:
        wm = WindowManager()
        w = wm.find_game_window()
        if not w:
            logger.info("未找到游戏窗口（Backpack Battles）")
            return False
        self.pid = w.pid
        self.reader = MemoryReader(w.pid)
        self.gr = GodotReader(self.reader)
        rva = self.gr.off.get("os_singleton_rva", 0)
        if not rva or not self.gr.get_root():
            rva = discover_os_singleton_rva(self.reader, self.gr.off)
            if not rva:
                logger.warning("OS::singleton 定位失败")
                return False
            self.gr.off["os_singleton_rva"] = rva
            self.gr._root_cache = None
        if not self.gr.get_root():
            return False
        self._game_node = self.gr.get_game_node()
        self.log_node = self._find_combatlog()
        if not self.log_node:
            logger.info("Game 单例中未找到 CombatLog（可能不在对局中）")
        return True

    def ensure_connected(self) -> bool:
        """断线/失效时重连；已连接且能读到日志节点则直接返回。"""
        if self.reader and self.gr and self.gr.get_root() and self._game_node:
            if self.log_node and self._members_addr(self.log_node):
                return True
            self.log_node = self._find_combatlog()
            if self.log_node:
                return True
        try:
            if self.reader:
                self.reader.close()
        except Exception:  # noqa: BLE001
            pass
        return self.connect()

    def _find_combatlog(self) -> Optional[int]:
        """在 Game 单例的 OBJECT 成员里按脚本路径锚定 CombatLog 节点。"""
        game = self._game_node or (self.gr.get_game_node() if self.gr else None)
        if not game:
            return None
        ma = self._members_addr(game)
        if not ma:
            return None
        n = self.gr._cow_count(ma) or 0
        for i in range(n):
            va = ma + i * self.gr.off["variant_size"]
            if self._vtype(va) != 17:
                continue
            obj = self._obj_at(va)
            if obj and self.gr.node_script_path(obj) == COMBATLOG_SCRIPT:
                return obj
        return None

    def _descriptor_name(self, node: int) -> Optional[str]:
        """物品节点 → descriptor 的 name 成员（getTranslatedName 的键）。
        descriptor 下标随物品子类脚本而异，按脚本路径扫描。"""
        cached = self._desc_cache.get(node, "?")
        if cached != "?":
            return cached
        name = None
        ima = self._members_addr(node)
        cnt = self.gr._cow_count(ima) if ima else 0
        vs = self.gr.off["variant_size"]
        for i in range(min(cnt or 0, 400)):
            va = ima + i * vs
            if self._vtype(va) != 17:
                continue
            o = self._obj_at(va)
            if o and self.gr.node_script_path(o) == "res://Items/ItemDescriptor.gd":
                dma = self._members_addr(o)
                if dma:
                    name = self._read_scalar(dma + DESC_NAME * vs)
                break
        self._desc_cache[node] = name
        return name

    def _runtime_name_map(self) -> Dict[str, str]:
        """Util.translationCache 的 `<identifier>_NAME → 官方中文名`。

        物品跨版本改名后 identifier（旧名）与翻译键（新名）不一致，但游戏
        运行时实际解析过名字并缓存在此——这是官方译名的权威来源。
        """
        if self._rt_names is not None:
            return self._rt_names
        out: Dict[str, str] = {}
        try:
            root = self.gr.get_root()
            util = next((c for c in self.gr.get_children(root)
                         if self.gr.node_name(c) == "Util"), None)
            if util:
                uma = self._members_addr(util)
                vs = self.gr.off["variant_size"]
                if uma and self._vtype(uma + 5 * vs) == 18:
                    for k, v in self._dict_items(uma + 5 * vs,
                                                 max_items=100000):
                        if isinstance(k, str) and k.endswith("_NAME") \
                                and isinstance(v, str) and v \
                                and self._good_text(v):
                            out[k[:-5]] = v
        except Exception:  # noqa: BLE001
            pass
        self._rt_names = out
        if out:
            # 同步进 ItemDB 补充表，其他路径（JSON/兜底渲染）也用得上
            self.item_db.zh_supplement.update(out)
        return out

    def _resolve_item_name(self, node: int, raw: str) -> str:
        """物品显示键：优先取游戏运行时已解析的官方名（含改名物品），
        其次 descriptor 名（未鉴定护符鉴定后随之变成真名），
        两名都查不到中文时回退节点名。"""
        base = clean_name(raw)
        dn = self._descriptor_name(node)
        rt = self._runtime_name_map()
        for cand in (dn, base):
            if cand and cand in rt:
                return cand
        for cand in (dn, base):
            if cand and self.item_db.zh(cand) != cand:
                return cand
        if self._rt_names is not None:
            # 缓存可能早于本次战斗的名字解析，补一次刷新再试
            self._rt_names = None
            rt = self._runtime_name_map()
            for cand in (dn, base):
                if cand and cand in rt:
                    return cand
        return dn or base

    def _origin_side(self, obj: int) -> Optional[str]:
        """origin 物品节点 → 所属方 'P'/'O'（沿父链找 Player/Opponent 根）。
        实测战斗场景中物品直接挂在 Player/Opponent 节点下，宝石经
        GemSocket → 宿主物品 → 一方根，最多数层。"""
        cur = obj
        for _ in range(12):
            p = self.gr._ptr(cur + self.gr.off["node_parent_off"])
            if not p or p < 0x10000:
                return None
            nm = self.gr.node_name(p)
            if nm == "Player":
                return "P"
            if nm == "Opponent":
                return "O"
            cur = p
        return None

    # ---------------- 底层读取 ----------------
    def _members_addr(self, node: int) -> Optional[int]:
        si = self.gr._script_instance(node)
        if not si:
            return None
        return self.gr._ptr(si + self.gr.off["gdscript_members_off"])

    def _vtype(self, addr: int) -> Optional[int]:
        return self.gr._read_int(addr, 4)

    def _obj_at(self, var_addr: int) -> Optional[int]:
        """Variant(OBJECT) → 对象指针（槽间接布局，见模块注释）。"""
        slot = self.gr._ptr(var_addr + 8)
        if slot and slot > 0x10000:
            obj = self.gr._ptr(slot)
            if obj and obj > 0x10000:
                return obj
        return self.gr._ptr(var_addr + 16) or None

    def _read_scalar(self, addr: int) -> Any:
        t = self._vtype(addr)
        if t == 2:
            return self.gr._read_int(addr + 8, 8)
        if t == 3:
            return self.gr._read_double(addr + 8)
        if t == 1:
            d = self.reader.read(addr + 8, 1)
            return bool(d[0]) if d else None
        if t == 4:
            return self.gr._read_godot_string(self.gr._ptr(addr + 8))
        return None

    def _array(self, var_addr: int) -> Tuple[Optional[int], int]:
        """Variant(ARRAY) → (元素区指针, 长度)。

        实测：元素个数在 elems-4（标准 CowData 头），priv+12 不是长度
        （在该构建里是别的字段，Util[11] 上与长度巧合相同曾造成误判）。
        """
        priv = self.gr._ptr(var_addr + 8)
        if not priv or priv < 0x10000:
            return None, 0
        elems = self.gr._ptr(priv + 16)
        if not elems or elems < 0x10000:
            return None, 0
        n = self.gr._read_int(elems - 4, 4)
        if n is None or n < 0 or n > 1_000_000:
            return None, 0
        return elems, n

    def _boxed_value(self, box: int) -> Any:
        """字典值盒 → 值（变体在 box+8，见模块注释）。"""
        t = self._vtype(box + 8)
        if t == 2:
            return self.gr._read_int(box + 16, 8)
        if t == 3:
            return self.gr._read_double(box + 16)
        if t == 1:
            d = self.reader.read(box + 16, 1)
            return bool(d[0]) if d else None
        if t == 4:
            return self._read_boxed_string(box)
        if t == 17:
            return self._obj_at(box + 8)
        return None

    @staticmethod
    def _good_text(s: str) -> bool:
        """文本是否只含正常字符（ASCII 可打印 / CJK / 全角标点）。
        排除值盒解码错位时混入的韩文、拉丁扩展等噪音。"""
        if not s:
            return False
        for ch in s:
            o = ord(ch)
            if not (0x20 <= o <= 0x7E or 0x4E00 <= o <= 0x9FFF
                    or 0x3000 <= o <= 0x303F or 0xFF00 <= o <= 0xFFEF
                    or ch in "·—…"):
                return False
        return True

    def _read_boxed_string(self, box: int) -> Optional[str]:
        """值盒字符串。两类字典的盒内布局有差异（内联数据在 +24 或 +16、
        或 +16 为堆 String 指针），生成全部候选（含不依赖 len 的噪音截断
        读法），按字符类别评分选优；key='item'（DamageBuff 的武器名）
        时再用物品名库校验。"""
        cands: List[str] = []
        n = self.gr._read_int(box + 12, 4)
        if n is not None and 0 < n <= 4096:
            for off in (24, 16):
                raw = self.reader.read(box + off, n * 2)
                if raw and len(raw) >= n * 2:
                    try:
                        cands.append(raw.decode("utf-16-le").split("\x00")[0])
                    except Exception:  # noqa: BLE001
                        pass
        for poff in (16, 24):
            p = self.gr._ptr(box + poff)
            if p and p > 0x10000:
                s = self.gr._read_godot_string(p)
                if s:
                    cands.append(s)
        # 不依赖 len 的读法：定长读取后在 NUL/噪音处截断（len 字段本身
        # 也可能随布局错位）
        for off in (24, 16):
            raw = self.reader.read(box + off, 64)
            if not raw:
                continue
            try:
                txt = raw.decode("utf-16-le").split("\x00")[0]
            except Exception:  # noqa: BLE001
                continue
            txt = txt.split("\ufffd")[0] if "\ufffd" in txt else txt
            if txt:
                cands.append(txt)
        if not cands:
            return None
        for c in cands:
            if self._good_text(c) and self._is_known_item_name(c):
                return c
        for c in cands:
            if self._good_text(c):
                return c
        return cands[0]

    _known_names: Optional[set] = None

    def _is_known_item_name(self, s: str) -> bool:
        if self._known_names is None:
            names = set(self.item_db.db.keys())
            names |= {v.get("zh") for v in self.item_db.db.values() if v.get("zh")}
            names |= set(self.item_db.zh_supplement.keys())
            names |= set(self.item_db.zh_supplement.values())
            self._known_names = {n for n in names if n}
        return s in self._known_names

    def _dict_items(self, var_addr: int, max_items: int = 512) -> List[Tuple[Any, Any]]:
        """Variant(DICT) → [(key, value)]。"""
        priv = self.gr._ptr(var_addr + 8)
        if not priv or priv < 0x10000:
            return []
        buckets = self.gr._ptr(priv + 16)
        if not buckets or buckets < 0x10000:
            return []
        nb = self.gr._read_int(buckets - 8, 4)
        if not nb or nb <= 0 or nb > 1 << 22:
            return []
        out: List[Tuple[Any, Any]] = []
        for i in range(min(nb, 8192)):
            el = self.gr._ptr(buckets + i * 8)
            hops = 0
            while el and el > 0x10000 and hops < 64:
                hops += 1
                kt = self._vtype(el + 16)
                if kt in (1, 2, 3, 4):
                    key = self._read_scalar(el + 16)
                elif kt == 17:
                    ko = self._obj_at(el + 16)
                    key = self.gr.node_name(ko) if ko else None
                else:
                    key = None
                box = self.gr._ptr(el + 40)
                val = self._boxed_value(box) if box and box > 0x10000 else None
                if box and box > 0x10000 and self._vtype(box + 8) == 17 \
                        and isinstance(val, int) and val > 0x10000:
                    sp = self.gr.node_script_path(val)
                    val = sp or self.gr.node_name(val) or hex(val)
                out.append((key, val))
                if len(out) >= max_items:
                    return out
                el = self.gr._ptr(el + 8)
        return out

    # ---------------- 高层读取 ----------------
    def poll(self) -> Dict[str, Any]:
        """轻量轮询：只读事件数 / eventNum / loggingFinished / 回合。"""
        state: Dict[str, Any] = {
            "connected": False, "pid": self.pid, "round": None,
            "event_count": 0, "event_num": None, "finished": None,
            "error": None,
        }
        if not self.ensure_connected():
            state["error"] = "未连接（游戏未运行或不在对局）"
            return state
        try:
            ma = self._members_addr(self.log_node)
            if not ma:
                self.log_node = None
                state["error"] = "CombatLog 读取失效"
                return state
            vs = self.gr.off["variant_size"]
            last_type = None
            last_ts = None
            last_id = -1
            total = 0
            for arr_idx in (MEM_EVENTS, MEM_DELAYED):
                va = ma + arr_idx * vs
                if self._vtype(va) != 19:
                    continue
                elems, n = self._array(va)
                total += n or 0
                if not elems or n <= 0:
                    continue
                ev = self._obj_at(elems + (n - 1) * vs)
                if not ev:
                    continue
                ema = self._members_addr(ev)
                if not ema:
                    continue
                eid = self._read_scalar(ema + EV_ID * vs)
                if not isinstance(eid, int) or eid <= last_id:
                    continue
                last_id = eid
                lt = self._read_scalar(ema + EV_TYPE * vs)
                ts = self._read_scalar(ema + EV_TS * vs)
                last_type = lt if _valid_type(lt) else None
                last_ts = round(float(ts), 3) if isinstance(ts, (int, float)) else None
            en_va = ma + MEM_EVENT_NUM * self.gr.off["variant_size"]
            fin_va = ma + MEM_FINISHED * self.gr.off["variant_size"]
            state.update({
                "connected": True,
                "event_count": total,
                "event_num": self._read_scalar(en_va),
                "finished": self._read_scalar(fin_va),
                "last_type": last_type,
                "last_ts": last_ts,
                "round": self.read_round(),
            })
        except Exception as e:  # noqa: BLE001
            state["error"] = f"轮询异常: {e}"
        return state

    def read_round(self) -> Optional[int]:
        if not self._game_node:
            return None
        try:
            return self.gr.read_member(self._game_node, GAME_MEMBER_ROUND)
        except Exception:  # noqa: BLE001
            return None

    def read_class(self) -> Optional[str]:
        """玩家职业名（Game.curClass）。"""
        if not self._game_node:
            return None
        try:
            v = self.gr.read_member(self._game_node, GAME_MEMBER_CURCLASS)
            return CLASSES.get(v, "Adventurer")
        except Exception:  # noqa: BLE001
            return None

    def read_opponent_class(self) -> Optional[str]:
        """对手职业名（curOpponentData["classI"]）。"""
        if not self._game_node:
            return None
        try:
            ma = self._members_addr(self._game_node)
            if not ma:
                return None
            vs = self.gr.off["variant_size"]
            va = ma + GAME_MEMBER_CUR_OPPONENT * vs
            if self._vtype(va) != 18:
                return None
            for k, v in self._dict_items(va, max_items=64):
                if k == "classI" and isinstance(v, int):
                    return CLASSES.get(v, "Adventurer")
            return None
        except Exception:  # noqa: BLE001
            return None

    _kw_zh: Optional[Dict[str, str]] = None

    @classmethod
    def _keyword_zh(cls) -> Dict[str, str]:
        """官方关键词中文名（assets/keywords_zh_official.json，懒加载）。"""
        if cls._kw_zh is None:
            import json
            try:
                p = Path(__file__).resolve().parent.parent / "assets" / \
                    "keywords_zh_official.json"
                cls._kw_zh = json.loads(p.read_text(encoding="utf-8"))
            except Exception:  # noqa: BLE001
                cls._kw_zh = {}
        return cls._kw_zh

    def read_events(self, tail: Optional[int] = None) -> List[Dict[str, Any]]:
        """完整解析事件（含 params、归属方）。

        事件分流入 `events`（面板可见期）与 `delayedLogList`（面板关闭期），
        两数组按 id 合并去重即全量。归属方：origin 物品的所属方
        （父链找 Player/Opponent 根）；非物品 origin（尖刺/吸血等伤害源）
        按 getMainActor 语义回退到 target 字段。origin 为整数
        （DamageSource.Type）时以官方关键词命名。物品显示名走
        descriptor（getTranslatedName 真值源），未鉴定护符鉴定后即真名。

        单条解析失败抛 ValueError（战斗进行中读到半态属正常，重试即可）。
        """
        if not self.ensure_connected():
            return []
        ma = self._members_addr(self.log_node)
        if not ma:
            return []
        vs = self.gr.off["variant_size"]
        by_id: Dict[int, Dict[str, Any]] = {}
        self._desc_cache = {}
        self._rt_names = None  # 每次完整读取都刷新运行时译名缓存
        for arr_idx in (MEM_EVENTS, MEM_DELAYED):
            va = ma + arr_idx * vs
            if self._vtype(va) != 19:
                continue
            elems, n = self._array(va)
            if not elems or n <= 0:
                continue
            for i in range(n):
                ev = self._obj_at(elems + i * vs)
                if not ev:
                    raise ValueError(f"array[{arr_idx}][{i}] 对象不可读")
                ema = self._members_addr(ev)
                if not ema:
                    raise ValueError(f"array[{arr_idx}][{i}] 成员不可读")
                mv = lambda k: ema + k * vs  # noqa: E731
                eid = self._read_scalar(mv(EV_ID))
                ts = self._read_scalar(mv(EV_TS))
                etype = self._read_scalar(mv(EV_TYPE))
                if not isinstance(eid, int) or not isinstance(ts, (int, float)) \
                        or not _valid_type(etype) or not (0 <= ts <= 600):
                    raise ValueError(
                        f"array[{arr_idx}][{i}] 字段异常 id={eid} ts={ts} type={etype}")
                if eid in by_id:
                    continue  # 同一事件同时进两数组（面板可见期）时去重
                # parentEvent 是 CombatEvent 对象引用（非 id），解出其 id 供缩进用
                parent_id = None
                if self._vtype(mv(EV_PARENT)) == 17:
                    pobj = self._obj_at(mv(EV_PARENT))
                    if pobj:
                        pma = self._members_addr(pobj)
                        if pma:
                            pid = self._read_scalar(pma + EV_ID * vs)
                            if isinstance(pid, int):
                                parent_id = pid
                target = self._read_scalar(mv(EV_TARGET))
                origin_obj = None
                ot = self._vtype(mv(EV_ORIGIN))
                if ot == 17:
                    origin_obj = self._obj_at(mv(EV_ORIGIN))
                pma = self._ptr_params(mv(EV_PARAMS))
                params = self._dict_items(pma) if pma else []
                origin: Optional[Dict[str, Any]] = None
                side: Optional[str] = None
                if origin_obj:
                    raw = self.gr.node_name(origin_obj)
                    if raw:
                        name = self._resolve_item_name(origin_obj, raw)
                        origin = {"name": name, "zh": self.item_db.zh(name)}
                        # 仅对真正的节点（有名字）做归属判定；
                        # DamageSource 等非节点对象走 target 兜底
                        side = self._origin_side(origin_obj)
                elif ot in (2, 3):
                    ov = self._read_scalar(mv(EV_ORIGIN))
                    kw = DS_KEYWORDS.get(ov) if isinstance(ov, int) else None
                    if kw:
                        zh = self._keyword_zh().get(kw) or DS_FALLBACK_ZH.get(kw, kw)
                        origin = {"name": kw.capitalize(), "zh": zh,
                                  "source": "damage_type"}
                by_id[eid] = {
                    "id": eid, "t": float(ts),
                    "type": int(etype), "type_name": EVENT_TYPES.get(etype, str(etype)),
                    "parent": parent_id,
                    "target": target if isinstance(target, int) else None,
                    "side": side,
                    "origin": origin,
                    "params": {k: v for k, v in params if isinstance(k, str)},
                }
        # 行缺失时的归属兜底：target（getMainActor 对非物品 origin 的语义）
        for e in by_id.values():
            if e["side"] is None and e["target"] is not None:
                e["side"] = "P" if e["target"] == 0 else "O"
        events = [by_id[k] for k in sorted(by_id)]
        if tail:
            events = events[-tail:]
        return events

    def _ptr_params(self, var_addr: int) -> Optional[int]:
        """params 成员必须是 DICT；返回其 Variant 地址。"""
        if self._vtype(var_addr) != 18:
            return None
        return var_addr

    def close(self):
        if self.reader:
            try:
                self.reader.close()
            except Exception:  # noqa: BLE001
                pass
            self.reader = None
        self.gr = None
        self.log_node = None
        self._game_node = None
