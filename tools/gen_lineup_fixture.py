#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
gen_lineup_fixture.py — 把真实阵容（lineups/*.json）编译成 GDScript 常量夹具

为什么需要它：
  `gd_core_test/LineupBattle.gd`（闸门 8）要在无头内核里跑**真实阵容**，验证
  469 个转译物品行为装上之后「到底跑不跑得起来、跑出来是否确定」。GDScript 侧
  没有 CSV/JSON 数据管线，故由本工具把数据编译成 `const` 字面量，闸门只做装配。

产出的三类数据：
  1. ITEMS[<key>]      —— 描述符字段（枚举已转成 CoreConst 的 int）
  2. PLACEMENT[<key>]  —— 该物品**各朝向无关**的锚点系网格数据（collision/affected）
  3. LINEUPS[<name>]   —— 每个阵容：职业/生命/体力 + 每件的绝对占格与绝对受影响格

另产出一份 **全物品** 夹具（供闸门 9「全物品逐一上场」用）：
  gd_core_test/item_battle_fixture.json
    {"anchor": [row, col], "items": {<key>: {script, sockets, descr, occupied,
                                            collision, affected}, …}}
  ★ 为什么单独走 JSON 而不是再塞一个 GDScript `const`：502 件物品的网格数据写成
    GDScript 字面量约 670 KB，单文件解析既慢又容易踩到脚本体积上限；JSON 由
    GDScript 的 parse_json 读入，量级降到 ~60 KB。
  ★ 代价是**数字全变 float**，故 GDScript 侧对 `tags` / `types` 显式 int() 化
    （见 ItemBattle.gd 的 _descr_of）；`params` 本就是 float 数组，不受影响。

坐标约定（与 simulator/item.py `_init_grid_metadata` / `_affected_cells_abs` 逐行对齐，
那是经 47 套真实阵容零冲突验证过的实现）：
  tscn 格 (x, y)：x = 横向 = 背包 col，y = 纵向 = 背包 row
    rotated   = [rotate_cell(c, rot) for c in collision_cells]      # 锚点系旋转
    min       = (min x, min y) of rotated
    occupied  = sorted((y + row, x + col) for (x, y) in normalized(rotated))
    rotatedCells（传给脚本的入参）= [(col + x - minx, row + y - miny) for (x, y) in rotated]
                                    ★ 保持 rotated 的原序（不排序）——原版
                                    getCollisionPoints() 的次序即脚本 `rotatedCells[i]` 的语义
    affected  = {(row + y - miny, col + x - minx) for (x, y) in rotate(rel, rot)}
  GDScript 侧向量统一为 Vector2(x=col, y=row)。

用法：
    python tools/gen_lineup_fixture.py            # 就地重写 gd_core_test/LineupFixture.gd
    python tools/gen_lineup_fixture.py --check    # 只校验是否同步（闸门用）
"""
from __future__ import annotations

import glob
import io
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")
LINEUP_DIR = os.path.join(ROOT, "lineups")
CORE_CONST = os.path.join(ROOT, "gd_core", "CoreConst.gd")
OUT_PATH = os.path.join(ROOT, "gd_core_test", "LineupFixture.gd")
# 全物品夹具（闸门 9 用）。见文件头「另产出一份全物品夹具」。
OUT_ITEMS_JSON = os.path.join(ROOT, "gd_core_test", "item_battle_fixture.json")
# 背包尺寸（原版 7 行 × 10 列，与 simulator 的边界校验一致）
GRID_ROWS, GRID_COLS = 7, 10
# 对齐 ItemBook.gd:8 `const NUM_PARAMS = 10` —— params 数组的定长（见 compile_descriptor）
NUM_PARAMS = 10
# 全物品夹具的锚点：全部物品都摆在 (0,0)。因为占格已归一化到 min=(0,0)，
# 只要物品本身放得进 7×10（游戏前提），就绝不会越界 —— 故无需逐件挑锚点。
ANCHOR = (0, 0)
ITEMS_DIR = os.path.join(ROOT, "gd_core_items")
EXTRACTED_ITEMS = os.path.join(ROOT, "extracted", "Items")

sys.path.insert(0, ROOT)
from simulator.grid import rotate_cell  # noqa: E402  （已验证的旋转实现，避免二次实现）


# ───────────────────────── CoreConst 枚举读取 ─────────────────────────

def parse_enums(path: str) -> dict:
    """从 CoreConst.gd 抓 `enum X{...}` 的成员名→值，作为唯一的枚举真值源。

    这样内核改枚举时夹具自动跟随，不会出现「夹具里硬编码 4=Weapon」的漂移。
    """
    src = io.open(path, encoding="utf-8", errors="replace").read()
    out = {}
    for m in re.finditer(r"enum\s+([A-Za-z_]\w*)\s*\{([^}]*)\}", src):
        name, body = m.group(1), m.group(2)
        members = {}
        nxt = 0
        for raw in body.split(","):
            item = raw.strip()
            if not item:
                continue
            if "=" in item:
                k, v = item.split("=", 1)
                k = k.strip()
                v = v.strip().replace(" ", "")
                try:
                    nxt = int(v, 0)
                except ValueError:
                    continue
                members[k] = nxt
                nxt += 1
            else:
                members[item] = nxt
                nxt += 1
        out[name] = members
    return out


ENUMS = parse_enums(CORE_CONST)


def enum_lookup(enum_name: str, member: str):
    """大小写不敏感查枚举；查不到返回 None（调用方负责报错）。"""
    table = ENUMS.get(enum_name) or {}
    for k, v in table.items():
        if k.lower() == str(member).lower():
            return v
    return None


# ───────────────────────── socket 数（从 tscn 数 GemSocket 实例） ─────────────────────────

def scan_socket_counts() -> dict:
    """{规范名(小写无空格无下划线): socket 数}

    原版 `Item.sockets = $Icon/Sockets.get_children()`（Item.gd:309），故 socket 数
    = 场景里 GemSocket 实例的个数。内核 `gems[]` 即 sockets[] 的替身，必须先按
    socket 数建等长数组，`setGem(i, gem)` 的下标检查才有意义。
    """
    out = {}
    for sub in ("", "Exclusive", "Gems"):
        for p in glob.glob(os.path.join(EXTRACTED_ITEMS, sub, "*.tscn")):
            txt = io.open(p, encoding="utf-8", errors="replace").read()
            n = len(re.findall(r'\[node name="[^"]*Socket[^"]*"', txt))
            if not n:
                continue
            key = os.path.splitext(os.path.basename(p))[0].lower().replace(" ", "").replace("_", "")
            out[key] = n
    return out


SOCKETS = scan_socket_counts()


def socket_count_for(key: str, script_file: str) -> int:
    for cand in (key, os.path.splitext(os.path.basename(script_file or ""))[0]):
        v = SOCKETS.get(cand.lower().replace(" ", "").replace("_", ""))
        if v is not None:
            return v
    return 0


# ───────────────────────── 脚本路径 ─────────────────────────

def build_script_index() -> dict:
    """{小写basename: gd_core_items 内的相对路径}

    ★ 为什么需要索引：battle_items.json 的 `behavior.script_file` 只给**裸文件名**
      （"StoneArmor.gd"），而实际文件在 `Items/Exclusive/` 下（"Exclusive/StoneArmor.gd"）。
      直接拼 `res://gd_core_items/<script_file>` 会让 Exclusive 系物品全部 load 失败
      （闸门 8 首轮：16 个物品里 5 个路径拼错，报
      "Cannot load source code from file ..."）。
    """
    idx = {}
    for dirpath, _dirs, files in os.walk(ITEMS_DIR):
        for fn in files:
            if not fn.endswith(".gd"):
                continue
            rel = os.path.relpath(os.path.join(dirpath, fn), ITEMS_DIR).replace(os.sep, "/")
            idx[fn[:-3].lower()] = rel
    return idx


SCRIPT_INDEX = build_script_index()


def script_path(key: str, entry: dict) -> str:
    rel = (entry.get("behavior") or {}).get("script_file") or ""
    if not rel:
        return ""
    base = os.path.splitext(os.path.basename(rel))[0].lower()
    if base not in SCRIPT_INDEX:
        raise SystemExit("转译产物里找不到脚本 %s（物品 %s）" % (rel, key))
    return "res://gd_core_items/" + SCRIPT_INDEX[base]


def script_path_opt(key: str, entry: dict):
    """`script_path` 的非抛出版本：查不到返回 None（全物品扫描时正好跳过）。

    为什么必须有：`battle_items.json` 有 518 项，而转译产物是 502 个 —— 差的那些是
    无脚本物品（Leather Bag / Coins 等基类物品），它们本就不该进闸门 9。
    """
    rel = (entry.get("behavior") or {}).get("script_file") or ""
    if not rel:
        return None
    base = os.path.splitext(os.path.basename(rel))[0].lower()
    if base not in SCRIPT_INDEX:
        return None
    return "res://gd_core_items/" + SCRIPT_INDEX[base]


# ───────────────────────── 描述符字段编译 ─────────────────────────

def parse_chance(raw) -> float:
    """对齐 engine/item.py:1709 `_parse_chance`：取前导数字（`5:crit` → 5.0）。"""
    m = re.match(r"[-+]?\d*\.?\d+", str(raw or "").strip())
    return float(m.group(0)) if m else 0.0


def compile_descriptor(key: str, entry: dict) -> dict:
    # ★ `params` 必须**按列对齐**（定长 NUM_PARAMS，下标 = 列号-1）。
    #   原版 ItemBook.gd:855-875 对 p1..p10 每一列都 push_back（空列 push 0），
    #   故 `getP1() = params[0]` … `getP10() = params[9]`。若这里是紧凑数组，
    #   含空列的物品（Carrot / Dark Lantern / Brass Knuckles …）`getP1..getP10`
    #   会整体错位，且 `getP_check` 越界报错 —— 静默偏值比报错更危险。
    #   不变量在此处断言（消费点），修正入口是 tools/align_item_params.py。
    params = entry.get("params") or []
    if len(params) != NUM_PARAMS:
        raise SystemExit(
            "物品 %s 的 params 长度 %d ≠ %d（未按列对齐）："
            "请先跑 `python tools/align_item_params.py`"
            % (key, len(params), NUM_PARAMS))

    types, bad_types = [], []
    for t in entry.get("types") or []:
        v = enum_lookup("Type", t)
        if v is None:
            bad_types.append(t)
        else:
            types.append(v)
    if bad_types:
        raise SystemExit("未知类型名 %s（物品 %s）：请检查 CoreConst.Type" % (bad_types, key))

    tags, bad_tags = 0, []
    for t in entry.get("tags") or []:
        v = enum_lookup("Tag", t)
        if v is None:
            bad_tags.append(t)
        else:
            tags |= v
    if bad_tags:
        raise SystemExit("未知标签名 %s（物品 %s）：请检查 CoreConst.Tag" % (bad_tags, key))

    rarity = enum_lookup("Rarity", entry.get("rarity") or "Common")
    if rarity is None:
        raise SystemExit("未知稀有度 %s（物品 %s）" % (entry.get("rarity"), key))

    return {
        "name": key,
        "identifier": key,
        "minDam": int(entry.get("min_dam") or 0),
        "maxDam": int(entry.get("max_dam") or 0),
        "cd": float(entry.get("cd") or 0.0),
        "extraCds": entry.get("extra_cds") or [],
        "accuracy": float(entry.get("accuracy") or 0.0),
        "staminaCost": float(entry.get("stamina_cost") or 0.0),
        "block": int(entry.get("block") or 0),
        "price": int(entry.get("price") or 0),
        "rarity": rarity,
        "classes": int(entry.get("classes") or 0),
        "canActivate": bool(entry.get("can_activate", True)),
        "chance": parse_chance(entry.get("csv_chance")),
        "chance2": parse_chance(entry.get("csv_chance2")),
        "types": sorted(set(types)),
        "tags": tags,
        "params": params,
        "namedParams": entry.get("named_params") or {},
        "sockets": socket_count_for(key, (entry.get("behavior") or {}).get("script_file")),
    }


# ───────────────────────── 网格几何 ─────────────────────────

AFFECTED_KEYS = {
    0: "affected_cells",
    1: "affected_secondary",
    2: "affected_tertiary",
    3: "affected_lightning",
}


def placement_of(key: str, entry: dict, row: int, col: int, rot: int) -> dict:
    """算一件物品的绝对占格 / 绝对受影响格（见文件头坐标约定）。"""
    grid = entry.get("grid") or {}
    base = [tuple(c) for c in (grid.get("collision_cells") or [])]
    if not base:
        # 对齐 simulator/item.py:1712 —— 无网格数据（宝石/符文/棋子…）在游戏中均为 1×1；
        # 不兜底会让它们不占格、邻接联动全部失效。
        base = [(0, 0)]
    rotated = [rotate_cell(c, rot) for c in base]
    minx = min(c[0] for c in rotated)
    miny = min(c[1] for c in rotated)

    # ★ occupied 与 collision/affected 必须同一坐标系（Vector2(x=col, y=row)）。
    #   此前 (c[1]..row, c[0]..col) 行列互换 → filledCells 键与 affected 查询格
    #   错位，1×1 物品邻接联动（getAffectedItems）恒空且零报错（两侧同源偏差，
    #   双引擎逐事件对照抓不到——两侧用同一套装配）。
    occupied = sorted({(c[0] - minx + col, c[1] - miny + row) for c in rotated})
    collision = [(c[0] - minx + col, c[1] - miny + row) for c in rotated]

    affected = {}
    for color, gkey in AFFECTED_KEYS.items():
        cells = set()
        for c in (grid.get(gkey) or []):
            rc = rotate_cell(tuple(c), rot)
            cells.add((rc[0] - minx + col, rc[1] - miny + row))
        if cells:
            affected[color] = sorted(cells)

    return {
        "row": row, "col": col, "rot": rot,
        "occupied": occupied,
        "collision": collision,
        "affected": affected,
    }


# ───────────────────────── 阵容读取 ─────────────────────────

def key_of(x):
    return (x.get("id") or x.get("key")) if isinstance(x, dict) else x


def collect_keys(lineups: dict) -> set:
    keys = set()
    for d in lineups.values():
        for sec in ("backpack", "storage"):
            s = d.get(sec) or {}
            for it in (s.get("items") or []):
                keys.add(it["id"])
                for g in it.get("gems") or []:
                    keys.add(key_of(g))
                for c in it.get("contents") or []:
                    keys.add(key_of(c))
    return keys


def character_stats(d: dict, char_db: dict) -> dict:
    """对齐 engine/combat.py:113-138 `_character_stats`（class_modifiers > 表 > 默认 + 回合成长）。"""
    character = d.get("character") or "Adventurer"
    mods = d.get("class_modifiers") or {}
    db_char = char_db.get(character, {})
    base_health = float(mods.get("health", db_char.get("health", 25.0)))
    stamina = float(mods.get("stamina", db_char.get("stamina", 5.0)))
    regen = float(mods.get("stamina_regen", db_char.get("regen", 1.0)))

    override = d.get("health_override")
    if override is not None:
        health = float(override)
    else:
        health = base_health
        for i in range(2, int(d.get("round") or 1) + 1):
            if i >= 15:
                health += 30
            elif i >= 10:
                health += 20
            elif i >= 5:
                health += 15
            else:
                health += 10
    # 职业枚举有两张表（CoreConst 对齐 Game.gd:131-146）：
    #   Classes（Ranger/Reaper/Berserker/Pyromancer，排位赛可选）
    #   Classes_Full（多出 Mage/Adventurer/Engineer，标题界面可选）
    # 两张表在 0..3 上取值一致；阵容里出现 Adventurer 之类只在 Full 表里的名字，
    # 故 Full 作回落。
    cls = enum_lookup("Classes", character)
    if cls is None:
        cls = enum_lookup("Classes_Full", character)
    if cls is None:
        raise SystemExit("未知职业 %s（请检查 CoreConst.Classes / Classes_Full）" % character)
    return {"class": cls, "health": health, "stamina": stamina, "regen": regen,
            "round": int(d.get("round") or 1)}


# ───────────────────────── GDScript 渲染 ─────────────────────────

def gd_value(v, indent: int = 0):
    pad = "\t" * indent
    if isinstance(v, bool):
        return "true" if v else "false"
    if isinstance(v, (int, float)):
        if isinstance(v, float) and v == int(v) and abs(v) < 1e15:
            return "%.1f" % v
        return repr(v) if isinstance(v, int) else "%.6g" % v
    if isinstance(v, str):
        return '"%s"' % v.replace("\\", "\\\\").replace('"', '\\"')
    if isinstance(v, (list, tuple)):
        return "[" + ", ".join(gd_value(x, indent) for x in v) + "]"
    if isinstance(v, dict):
        if not v:
            return "{}"
        parts = []
        for k, val in v.items():
            kk = gd_value(k) if isinstance(k, str) else str(k)
            parts.append("%s\t%s: %s" % (pad, kk, gd_value(val, indent + 1)))
        return "{\n" + ",\n".join(parts) + "\n" + pad + "}"
    raise TypeError("无法渲染 %r" % (v,))


def render_body(items: dict, lineups: dict) -> str:
    out = []
    out.append("const ITEMS := {")
    for k in sorted(items):
        out.append("\t%s: %s," % (gd_value(k), gd_value(items[k], 1)))
    out.append("}")
    out.append("")
    out.append("const LINEUPS := {")
    for k in sorted(lineups):
        lu = lineups[k]
        out.append("\t%s: {" % gd_value(k))
        out.append("\t\t\"name\": %s," % gd_value(lu["name"]))
        out.append("\t\t\"class\": %d," % lu["class"])
        out.append("\t\t\"round\": %d," % lu["round"])
        out.append("\t\t\"health\": %s," % gd_value(lu["health"]))
        out.append("\t\t\"stamina\": %s," % gd_value(lu["stamina"]))
        out.append("\t\t\"regen\": %s," % gd_value(lu["regen"]))
        out.append("\t\t\"items\": [")
        for it in lu["items"]:
            out.append("\t\t\t%s," % gd_value(it, 3).replace("\n", "\n\t\t"))
        out.append("\t\t],")
        out.append("\t},")
    out.append("}")
    return "\n".join(out)


HEADER = """# =============================================================================
# LineupFixture.gd — 真实阵容夹具（由 tools/gen_lineup_fixture.py 生成，勿手改）
# =============================================================================
# 数据来源：assets/battle_items.json（物品静态数据 + tscn 网格）
#           lineups/*.json（真实阵容摆盘）
#           gd_core/CoreConst.gd（Type/Tag/Rarity/Classes 枚举，唯一真值源）
#           extracted/Items/*.tscn（socket 数 = GemSocket 实例个数）
#
# 几何约定与推导过程见 tools/gen_lineup_fixture.py 文件头；GDScript 侧
# 向量一律 Vector2(x=col, y=row)，与 CoreItem/CoreGrid 一致。
#
# 覆盖 %d 个物品、%d 个阵容。
# =============================================================================
extends Reference
class_name LineupFixture


"""


def build():
    db = json.load(io.open(DB_PATH, encoding="utf-8"))["items"]
    char_db_path = os.path.join(ROOT, "assets", "characters.json")
    char_db = {}
    if os.path.exists(char_db_path):
        char_db = json.load(io.open(char_db_path, encoding="utf-8"))
        if isinstance(char_db, dict) and "characters" in char_db:
            char_db = char_db["characters"]

    lineups_raw = {}
    for p in sorted(glob.glob(os.path.join(LINEUP_DIR, "*.json"))):
        name = os.path.splitext(os.path.basename(p))[0]
        lineups_raw[name] = json.load(io.open(p, encoding="utf-8"))

    keys = collect_keys(lineups_raw)
    missing = sorted(k for k in keys if k not in db)
    if missing:
        raise SystemExit("阵容引用了未知物品：%s" % missing)

    items = {k: compile_descriptor(k, db[k]) for k in sorted(keys)}

    lineups = {}
    for name, d in lineups_raw.items():
        stats = character_stats(d, char_db)
        entries = []
        for sec in ("backpack", "storage"):
            s = d.get(sec) or {}
            for it in (s.get("items") or []):
                pl = placement_of(it["id"], db[it["id"]],
                                  int(it.get("row") or 0), int(it.get("col") or 0),
                                  int(it.get("rotation") or 0) % 360)
                pl["key"] = it["id"]
                pl["script"] = script_path(it["id"], db[it["id"]])
                pl["bagslot"] = bool(it.get("container"))
                pl["storage"] = (sec == "storage")
                pl["gems"] = [key_of(g) for g in (it.get("gems") or [])]
                if pl["gems"]:
                    pl["gemScripts"] = [script_path(gk, db[gk]) for gk in pl["gems"]]
                entries.append(pl)
        lineups[name] = {"name": (d.get("meta") or {}).get("name", name), **stats,
                         "items": entries}
    return items, lineups


def build_item_table() -> dict:
    """全物品夹具：每件可转译物品 → 描述符 + 网格 + 脚本路径。

    ★ 用途是闸门 9「全物品逐一上场」，它存在的理由是**覆盖面**：
      闸门 8 只跑 8 套真实阵容（16 件物品），而转译产物有 502 件。
      「某件物品的行为脚本装上之后跑不跑得起来」这种问题，静态解析（闸门 6）
      看不出来、真实阵容（闸门 8）覆盖不到 —— 只有逐件真的打一场才暴露。
      实测价值：本轮 `has_node_modal` 误判修正后保留面扩大，正是这道闸门把
      「保留语句引用了视觉变量」这类潜在运行期错误全量扫了一遍。
    """
    db = json.load(io.open(DB_PATH, encoding="utf-8"))["items"]
    items = {}
    skipped = []
    for key in sorted(db):
        entry = db[key]
        path = script_path_opt(key, entry)
        if not path:
            skipped.append(key)
            continue
        pl = placement_of(key, entry, ANCHOR[0], ANCHOR[1], 0)
        h = max(c[0] for c in pl["occupied"]) + 1
        w = max(c[1] for c in pl["occupied"]) + 1
        if h > GRID_ROWS or w > GRID_COLS:
            raise SystemExit("物品 %s 占格 %d×%d 超出背包 %d×%d"
                             % (key, h, w, GRID_ROWS, GRID_COLS))
        items[key] = {
            "script": path,
            "sockets": socket_count_for(key, (entry.get("behavior") or {}).get("script_file")),
            "descr": compile_descriptor(key, entry),
            "occupied": pl["occupied"],
            "collision": pl["collision"],
            "affected": pl["affected"],
        }
    return {"anchor": list(ANCHOR), "items": items, "skipped": skipped}


def main() -> int:
    items, lineups = build()
    text = HEADER % (len(items), len(lineups)) + render_body(items, lineups) + "\n"
    table = build_item_table()
    jtext = json.dumps(table, ensure_ascii=False, sort_keys=True,
                       separators=(",", ":")) + "\n"

    if "--check" in sys.argv:
        bad = []
        for path, want in ((OUT_PATH, text), (OUT_ITEMS_JSON, jtext)):
            old = ""
            if os.path.exists(path):
                old = io.open(path, encoding="utf-8", errors="replace").read()
            if old != want:
                bad.append(os.path.relpath(path, ROOT))
        if bad:
            print("夹具已过期（数据/源码变动后需重跑 gen_lineup_fixture.py）：%s" % bad)
            return 1
        print("夹具与数据源同步（阵容物品 %d、全物品 %d、阵容 %d）"
              % (len(items), len(table["items"]), len(lineups)))
        return 0

    with io.open(OUT_PATH, "w", encoding="utf-8", newline="\n") as fh:
        fh.write(text)
    with io.open(OUT_ITEMS_JSON, "w", encoding="utf-8", newline="\n") as fh:
        fh.write(jtext)

    n_sock = sum(1 for v in items.values() if v["sockets"])
    n_gem = sum(len(e["gems"]) for lu in lineups.values() for e in lu["items"])
    print("已生成 %s" % os.path.relpath(OUT_PATH, ROOT))
    print("  物品 %d（其中 %d 个带 socket）、阵容 %d、嵌宝石 %d 颗"
          % (len(items), n_sock, len(lineups), n_gem))
    print("已生成 %s" % os.path.relpath(OUT_ITEMS_JSON, ROOT))
    print("  可上场物品 %d、无转译脚本跳过 %d、体积 %.0f KB"
          % (len(table["items"]), len(table["skipped"]),
             len(jtext.encode("utf-8")) / 1024.0))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
