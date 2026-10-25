# -*- coding: utf-8 -*-
"""build_history.py — 从游戏历史记录数据库导出阵容

真值源（decompiled_full/）：
  * history.db（SQLite）：Utility/BuildHistoryDB.gd
    - runData (runID, class, loadout, rank, version, time, subclass, skill1, skill2, custom)
    - roundData (runID, roundID, result, tries, health, stamina, buildInfo)
    - db 路径 user://{steam_id}{build}history → %APPDATA%/Godot/app_userdata/
      Backpack Battles/{steam_id}/full/history.db
  * buildInfo 位流：Core/RunDatabase.gd serializeRound + Utility/RunData.gd
    deserializeStream（解码端逐位对齐）
    - 字符编码：BitStream.toGodotString —— 6bit 分组 + 62 偏移
    - pull(rangeMax) = ceil(log2(rangeMax)) 位；pullBitsize(n) = 固定 n 位
    - 顺序：health(999) stamina(999) → 每物品
      [index(totalNumItems) col(10) row(10) face(4) (hasGems(2→1bit) gems×sockets
      (totalNumGems=64→6bit)) (MagicRing 持久段 12bit)]
  * faceDirection → 旋转：UP/RIGHT/DOWN/LEFT → 0/90/180/270（correction 表顺序）
  * 物品索引映射：assets/item_index_map.json（tools/gen_item_index_map.py 生成）
"""
from __future__ import annotations

import glob
import json
import math
import os
import sqlite3
from typing import Any, Dict, List, Optional

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MAP_PATH = os.path.join(ROOT, "assets", "item_index_map.json")

CLASSES = {0: "Ranger", 1: "Reaper", 2: "Berserker", 3: "Pyromancer"}
FACE_TO_ROT = {0: 0, 1: 90, 2: 180, 3: 270}
MAX_HEALTH = 999
MAX_STAMINA = 999
INV_MAX = 10
MAGIC_RING = "Magic Ring"
MAGIC_RING_PD_BITS = 12        # numEffects=2 × (2+4)（MagicRing.gd:291）


def _find_map() -> Dict[str, Any]:
    # 优先活体刷新表（运行版游戏 ItemBook 实测映射），回退静态表
    live = os.path.join(ROOT, "assets", "item_index_map_live.json")
    if os.path.exists(live):
        try:
            with open(live, encoding="utf-8") as f:
                d = json.load(f)
            if d.get("index_to_name"):
                return d
        except Exception:
            pass
    with open(MAP_PATH, encoding="utf-8") as f:
        return json.load(f)


def live_item_index_map(gr, mem_reader) -> Optional[Dict[str, Any]]:
    """从运行中的游戏读取 ItemBook.descriptorList / numSockets / gemList。

    descriptorList 的数组下标即 itemIndex（ItemBook.gd:948 按 itemIndex 槽
    写入）；元素为 ItemDescriptor 对象，name 成员下标 6（与 combatlog_reader
    的 DESC_NAME 一致，实战校准）。返回与 tools/gen_item_index_map.py 同构
    的映射表；写入 assets/item_index_map_live.json 供离线解码复用。
    """
    vs = gr.off["variant_size"]
    root = gr.get_root()
    if not root:
        return None
    node = None
    for c in gr.get_children(root):
        if gr.node_name(c) == "ItemBook":
            node = c
            break
    if not node:
        return None
    si = gr._script_instance(node)
    if not si:
        return None
    mptr = gr._ptr(si + gr.off["gdscript_members_off"])
    msize = gr._cow_count(mptr)
    if not mptr or not msize or msize <= 0:
        return None

    def vtype(addr):
        return gr._read_int(addr, 4)

    def array_at(var_addr):
        priv = gr._ptr(var_addr + 8)
        if not priv or priv < 0x10000:
            return None, 0
        elems = gr._ptr(priv + 16)
        if not elems or elems < 0x10000:
            return None, 0
        n = gr._read_int(elems - 4, 4)
        if n is None or n < 0 or n > 1_000_000:
            return None, 0
        return elems, n

    def obj_at(var_addr):
        if vtype(var_addr) != 17:
            return None
        # 该构建 OBJECT Variant 布局：type(4) id(4) 预留(8) obj*(8)
        # —— 实测指针在 +16（+8 为 ObjectID，非地址）
        return gr._ptr(var_addr + 16)

    def desc_name(obj):
        si2 = gr._ptr(obj + gr.off["object_script_instance_off"])
        if not si2:
            return None
        dma = gr._ptr(si2 + gr.off["gdscript_members_off"])
        if not dma:
            return None
        va = dma + 6 * vs
        if vtype(va) != 4:
            return None
        return gr._read_godot_string(gr._ptr(va + 8))

    # 扫描 members 里的 ARRAY 候选（descriptorList：400~600 个 OBJECT 元素）
    desc = None
    for i in range(msize):
        va = mptr + i * vs
        if vtype(va) != 19:
            continue
        elems, n = array_at(va)
        if elems and 400 <= n <= 700:
            if all(vtype(elems + k * vs) == 17 for k in range(min(5, n))):
                desc = (elems, n)
                break
    if not desc:
        return None
    desc_elems, desc_n = desc

    # numSockets：与 descriptorList 等长的 INT 数组
    num_sockets_arr = None
    for i in range(msize):
        va = mptr + i * vs
        if vtype(va) != 19:
            continue
        elems, n = array_at(va)
        if elems and n == desc_n:
            if all(vtype(elems + k * vs) == 2 for k in range(min(20, n))):
                num_sockets_arr = (elems, n)
                break

    # gemList：元素 OBJECT、计数 10..100，且元素名与已知宝石名单交集最大
    # （1.1.7 CSV type==Gem 共 34 个；1.1.8 大概率沿用同批宝石）
    gem_names_known = {"Chipped Ruby", "Flawless Ruby", "Chipped Sapphire",
                       "Flawless Sapphire", "Chipped Emerald", "Flawless Emerald",
                       "Chipped Topaz", "Flawless Topaz", "Chipped Amethyst",
                       "Flawless Amethyst", "Ruby", "Sapphire", "Emerald",
                       "Topaz", "Amethyst", "Pearl of Restoring", "Pearl of Wisdom",
                       "Pearl of Power", "Pearl of Luck", "Pearl of Nimbleness",
                       "Chipped Pearl", "Flawless Pearl"}
    gem_candidates = []
    for i in range(msize):
        va = mptr + i * vs
        if vtype(va) != 19:
            continue
        elems, n = array_at(va)
        if not elems or not (10 <= n < 100):
            continue
        names = []
        for k in range(min(n, 12)):
            o = obj_at(elems + k * vs)
            if o:
                nm = desc_name(o)
                if nm:
                    names.append(nm)
        if not names:
            continue
        hit = sum(1 for x in names if x in gem_names_known)
        gem_candidates.append((hit, i, elems, n, names))
    gem_candidates.sort(reverse=True)
    gem_arr = None
    gem_order = []
    if gem_candidates and gem_candidates[0][0] >= 3:
        _, gi, gelems, gn, _ = gem_candidates[0]
        gem_arr = (gelems, gn)
        for k in range(gn):
            o = obj_at(gelems + k * vs)
            if o:
                nm = desc_name(o)
                gem_order.append(nm if nm else f"#{k}")

    index_to_name = {}
    for k in range(desc_n):
        o = obj_at(desc_elems + k * vs)
        if not o:
            continue
        name = desc_name(o)
        if name:
            index_to_name[k] = name

    num_sockets = {}
    if num_sockets_arr:
        elems, n = num_sockets_arr
        for k in range(n):
            v = gr._read_int(elems + k * vs + 8, 8)
            num_sockets[index_to_name.get(k, f"#{k}")] = int(v or 0)

    gem_order = []
    if gem_arr:
        elems, n = gem_arr
        for k in range(n):
            o = obj_at(elems + k * vs)
            if o:
                nm = desc_name(o)
                gem_order.append(nm if nm else f"#{k}")

    total_gems = 2 ** math.ceil(math.log2(len(gem_order) + 1)) if gem_order else 64
    out = {
        "version": "live",
        "total_items": max(index_to_name) + 1 if index_to_name else 518,
        "index_to_name": {str(k): v for k, v in sorted(index_to_name.items())},
        "gem_order": gem_order,
        "total_num_gems_ceil": total_gems,
        "empty_socket_id": total_gems - 1,
        "num_sockets": num_sockets,
    }
    try:
        with open(os.path.join(ROOT, "assets", "item_index_map_live.json"),
                  "w", encoding="utf-8") as f:
            json.dump(out, f, ensure_ascii=False, indent=1)
    except Exception:
        pass
    return out


def find_history_db() -> Optional[str]:
    """定位最新的 history.db（多个 SteamID 目录取 mtime 新的）。"""
    base = os.path.join(os.environ.get("APPDATA", ""), "Godot", "app_userdata",
                        "Backpack Battles")
    if not os.path.isdir(base):
        return None
    cands = glob.glob(os.path.join(base, "*", "full", "history.db")) + \
        glob.glob(os.path.join(base, "*", "history.db"))
    if not cands:
        return None
    return max(cands, key=os.path.getmtime)


class _BitReader:
    """BitStream.fromGodotString/pull 的 Python 对齐实现。"""

    def __init__(self, s: str):
        self.bits: List[int] = []
        for ch in s:
            v = ord(ch) - 62
            if v < 0 or v > 63:
                raise ValueError("buildInfo 字符超出 base62 变体范围")
            for d in range(5, -1, -1):
                self.bits.append((v >> d) & 1)
        self.pos = 0

    def bits_left(self) -> int:
        return len(self.bits) - self.pos

    def pull_bitsize(self, n: int) -> int:
        v = 0
        for _ in range(n):
            if self.pos >= len(self.bits):
                return -1
            v = (v << 1) | self.bits[self.pos]
            self.pos += 1
        return v

    def pull(self, range_max: int) -> int:
        if range_max <= 1:
            return 0
        n = math.ceil(math.log2(range_max))
        return self.pull_bitsize(n)


def decode_build_info(s: str, imap: Dict[str, Any]) -> Optional[Dict[str, Any]]:
    """解码 buildInfo 位流 → {health, stamina, items: [{id, row, col, rot, gems}]}。

    对齐 RunData.deserializeStream；任一字段非法返回 None（与游戏端一致）。
    """
    index_to_name = {int(k): v for k, v in imap["index_to_name"].items()}
    gem_order = imap["gem_order"]
    num_sockets = imap["num_sockets"]
    total_items = int(imap["total_items"])
    total_gems = int(imap["total_num_gems_ceil"])
    empty_id = int(imap["empty_socket_id"])
    gem_bits = int(math.log2(total_gems)) if total_gems > 1 else 1
    ring_index = next((int(k) for k, v in index_to_name.items()
                       if v == MAGIC_RING), -1)

    br = _BitReader(s)
    health = br.pull(MAX_HEALTH)
    stamina = br.pull(MAX_STAMINA)
    if health < 0 or stamina < 0:
        return None
    items = []
    while br.bits_left() >= 8:
        idx = br.pull(total_items)
        if idx < 0 or idx >= total_items:
            return None
        col = br.pull(INV_MAX)
        row = br.pull(INV_MAX)
        # serializeRound 用 push(face, 4)——rangeMax 语义 = ceil(log2(4)) = 2 位
        face = br.pull(4)
        if col < 0 or row < 0 or face < 0:
            return None
        name = index_to_name.get(idx)
        if name is None:
            return None
        gems: List[str] = []
        ns = int(num_sockets.get(name, 0))
        if ns > 0:
            has_gems = br.pull(2)
            if has_gems == 1:
                for _ in range(ns):
                    g = br.pull_bitsize(gem_bits)
                    if g < 0:
                        return None
                    if g != empty_id and g < len(gem_order):
                        gems.append(gem_order[g])
        if idx == ring_index:
            br.pull_bitsize(MAGIC_RING_PD_BITS)
        items.append({
            "id": name,
            "at": [int(row), int(col)],
            "r": FACE_TO_ROT.get(face, 0) % 360,
            "gems": gems,
        })
    return {"health": health, "stamina": stamina, "items": items}


def list_runs(db_path: Optional[str] = None) -> List[Dict[str, Any]]:
    """列出历史 runs（新→旧）：run_id / character / num_rounds / time。"""
    db = db_path or find_history_db()
    if not db or not os.path.exists(db):
        return []
    con = sqlite3.connect(db)
    try:
        cur = con.cursor()
        rows = cur.execute(
            "select r.runID, r.class, r.time, count(q.roundID) "
            "from runData r left join roundData q on q.runID = r.runID "
            "group by r.runID order by r.runID desc").fetchall()
        return [{"run_id": r[0], "character": CLASSES.get(r[1], f"cls{r[1]}"),
                 "time": r[2], "num_rounds": r[3]} for r in rows]
    finally:
        con.close()


def list_rounds(db_path: Optional[str] = None, run_id: int = 0) -> List[Dict[str, Any]]:
    """列出某 run 的全部回合（roundID 升序 + 胜负/血量）。"""
    db = db_path or find_history_db()
    if not db or not os.path.exists(db):
        return []
    con = sqlite3.connect(db)
    try:
        cur = con.cursor()
        rows = cur.execute(
            "select roundID, result, health, stamina, buildInfo "
            "from roundData where runID = ? order by roundID", (run_id,)).fetchall()
        return [{"round_id": r[0], "result": r[1], "health": r[2],
                 "stamina": r[3], "build_info": r[4]} for r in rows]
    finally:
        con.close()


def export_round(run_id: int, round_id: int, out_path: str,
                 db_path: Optional[str] = None) -> Dict[str, Any]:
    """导出指定 run 的指定回合为 v4 阵容 JSON；返回写入的数据。"""
    db = db_path or find_history_db()
    if not db or not os.path.exists(db):
        raise FileNotFoundError("未找到 history.db（需至少游玩过一次游戏）")
    imap = _find_map()
    con = sqlite3.connect(db)
    try:
        cur = con.cursor()
        run = cur.execute(
            "select class, loadout, time from runData where runID = ?",
            (run_id,)).fetchone()
        row = cur.execute(
            "select result, health, stamina, buildInfo from roundData "
            "where runID = ? and roundID = ?", (run_id, round_id)).fetchone()
    finally:
        con.close()
    if run is None or row is None:
        raise ValueError(f"runID={run_id} roundID={round_id} 不存在")

    decoded = decode_build_info(row[3], imap)
    if decoded is None:
        raise ValueError("buildInfo 解码失败（版本不兼容或数据损坏）")

    character = CLASSES.get(run[0], "Adventurer")
    data: Dict[str, Any] = {
        "version": 4,
        "name": f"历史 Run{run_id} 第{round_id}回合",
        "character": character,
        "round": int(round_id) + 1,
        "class_modifiers": {
            "health": row[1],
            "stamina": row[2],
        },
        "grid": [INV_MAX, INV_MAX],
        "items": decoded["items"],
        "storage": [],
        "meta": {
            "name": f"历史 Run{run_id} 第{round_id}回合",
            "source": "game_history",
            "run_id": run_id,
            "round_id": round_id,
            "result": row[0],
        },
    }
    os.makedirs(os.path.dirname(os.path.abspath(out_path)), exist_ok=True)
    with open(out_path, "w", encoding="utf-8") as f:
        json.dump(data, f, ensure_ascii=False, indent=2)
    return data
