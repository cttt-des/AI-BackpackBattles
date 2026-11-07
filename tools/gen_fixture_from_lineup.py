#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
gen_fixture_from_lineup.py — 真值实录阵容 → lineups/*.json 夹具
（docs/consistency_workflow.md §3 Phase 1 / M2 的交付件）

用途：三角定位 DK（黏黏龙骑士）正反馈问题。把一组真值实录的双方阵容
（dist/output/combat_logs/<组>/<组>.Player.json / .Opponent.json，v4 平铺格式）
转成 tools/gen_lineup_fixture.py 消费的内部 v3 形状，落到 lineups/ 下，
再由 gen_lineup_fixture.py 编译进 gd_core_test/LineupFixture.gd，
供 gd_core_test/TruthBattle.gd 在 Godot 无头内核里复现这一场。

转换规则（与 simulator/lineup.py::_normalize_v4 / ai/encoding.py 口径一致）：
  * v4 `at=[row,col]`、`r` 旋转、`gems` 逐条直转；真值平铺导出允许根物品
    坐标压叠（袋内物品与袋同格），引擎装配照单全收（gd_core_py CoreGrid.addItem）。
  * 宝石若不在 assets/battle_items.json（如 GoldCounter——不可装配的内部件），
    **剔除并告警**：两条引擎路线（Godot 夹具 / gd_core_engine）都会对无转译
    脚本的物品抛错，仓库既有口径是剔除（ai/encoding.py unknown_ids）。
    剔除清单会打出来，保证双方阵容变换完全一致。

用法：
    python tools/gen_fixture_from_lineup.py <combat_log组目录>
    python tools/gen_fixture_from_lineup.py dist/output/combat_logs/CombatLog_20261001_220653_R19_Win

受控神谕模式（docs/oracle_workflow.md Phase 3，verify_oracle 管线第一步）：
    python tools/gen_fixture_from_lineup.py --oracle <神谕用例目录>... \
        --lineup-out output/oracle/align/lineups --batch-out gd_core_test/oracle_align_cases.json

扩样语料（docs/expand_fix_kickoff.md §6.2，玩家开局 stamina 必须取合并库）：
    python tools/gen_fixture_from_lineup.py --oracle <扩样用例目录>... \
        --history-db output/oracle/expand/data/history.db \
        --lineup-out output/oracle/align_expand/lineups --batch-out gd_core_test/expand_align_cases.json
    （等价环境变量 EXPAND_HISTORY_DB=<合并库>；缺省仍取 oracle/data/history.db，零回归）

  <神谕用例目录> = output/oracle/fights/<case_id>/（含 lineups.json）。
  产出两类夹具，双方模拟器消费**同一份装配序**（lineups.json items 数组顺序，
  即原版 sort_BagOrder 后的装配顺序，oracle_fight.gd::dump_lineups 原样 dump）：
    1. --lineup-out：v3 内部阵容 JSON（oracle_<case_id>_{player,opponent}.json），
       供 gd_core_py 侧（simulator.simulate / GDCoreEngine）直接加载；
       之所以不落 lineups/ 是因为 tools/gen_lineup_fixture.py 会 glob 该目录
       把所有阵容编译进 LineupFixture.gd，批量夹具不能污染它。
    2. --batch-out：Godot 批量脚本（gd_core_test/OracleAlignBattle.gd）消费的
       用例夹具（几何按 gen_lineup_fixture.placement_of 同一实现展开成绝对格；
       描述符/脚本路径不复制——GDScript 侧运行时读 item_battle_fixture.json）。

  战斗起始体力约定（对齐原版装配路径，证据见各字段注释）：
    * 玩家：setMaxStamina(roundData.stamina)（oracle_fight.gd:608，setMaxStamina
      同设 cur，Character.gd:951-956）→ battle-start = 语料史真值
      oracle/data/history.db roundData.stamina（明文列，实测分布 5..10；
      r33 定谳——「恒 base」与「恒 base+袋」均被 813/910 同画像异值证伪），
      baseMaxStamina 保持角色默认 5。
    * 对手：initHistoryOpponent 显式 baseMaxStamina=5 + recalculateMaxStamina
      （=5 + Stamina Sack 件数）→ battle-start stamina = 5 + 袋数，base=5。
"""
from __future__ import annotations

import io
import json
import math
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")
OUT_DIR = os.path.join(ROOT, "lineups")

# 神谕模式公用：几何展开复用 gen_lineup_fixture 的同一实现（旋转/占格/受影响格
# 数学与 gd_core_runtime.json / simulator 侧同源，见其文件头坐标约定）。
_TOOLS_DIR = os.path.dirname(os.path.abspath(__file__))
if _TOOLS_DIR not in sys.path:
    sys.path.insert(0, _TOOLS_DIR)


def convert(side_json_path: str, out_name: str) -> (str, list):
    db = json.load(io.open(DB_PATH, encoding="utf-8"))["items"]
    d = json.load(io.open(side_json_path, encoding="utf-8"))

    dropped = []
    items = []
    for it in d["items"]:
        gems = []
        for g in (it.get("gems") or []):
            if g in db:
                gems.append({"id": g})
            else:
                dropped.append("%s:%s" % (it["id"], g))
        items.append({
            "id": it["id"],
            "row": int(it["at"][0]),
            "col": int(it["at"][1]),
            "rotation": int(it.get("r", 0) or 0) % 360,
            "quantity": 1,
            "container": False,
            "contents": [],
            "gems": gems,
        })

    out = {
        "version": 3,
        "meta": {"name": out_name, "source": "combatlog:" +
                 os.path.basename(side_json_path)},
        "character": d["character"],
        "round": int(d["round"]),
        # 真值 v4 无 class_modifiers → 用默认表 + 回合成长（gen_lineup_fixture
        # ::character_stats 与模拟器 engine/combat.py 同口径）
        "class_modifiers": {},
        "health_override": None,
        "backpack": {"grid": {"rows": int(d["grid"][0]),
                              "cols": int(d["grid"][1])}, "items": items},
        "storage": [],
    }
    path = os.path.join(OUT_DIR, out_name + ".json")
    with io.open(path, "w", encoding="utf-8", newline="\n") as fh:
        json.dump(out, fh, ensure_ascii=False, indent=1)
        fh.write("\n")
    return path, dropped


def main_legacy() -> int:
    if len(sys.argv) != 2:
        print(__doc__)
        return 2
    grp = sys.argv[1].rstrip("/\\")
    base = os.path.basename(grp)
    total_dropped = []
    for side, tag in (("Player", "player"), ("Opponent", "opponent")):
        src = os.path.join(grp, base + "." + side + ".json")
        if not os.path.exists(src):
            print("缺文件：%s" % src)
            return 1
        out_name = "truth_" + base.split("_", 1)[1].rsplit("_", 1)[0] + "_" + tag
        path, dropped = convert(src, out_name)
        print("已生成 %s（%d 件）" % (os.path.relpath(path, ROOT),
                                     len(json.load(io.open(path, encoding="utf-8"))
                                         ["backpack"]["items"])))
        if dropped:
            print("  剔除不可装配宝石：%s" % ", ".join(dropped))
            total_dropped += dropped
    if not total_dropped:
        print("  无剔除物品")
    return 0


# ═══════════════════ 受控神谕模式（oracle_workflow Phase 3） ═══════════════════

# 战斗起始体力基准（见文件头「战斗起始体力约定」）
OPP_BASE_STAMINA = 5.0
STAMINA_SACK_ID = "Stamina Sack"


def _oracle_side_entries(lu_side: dict, db: dict, warnings: list) -> list:
    """lineups.json 单侧 items → 装配序条目（保序，含宝石过滤/几何展开）。

    条目形状：{key, row, col, rotation, gems:[key|None,...], dropped}
    * gems 不可装配（不在 battle_items.json，如 GoldCounter 内部件）→ 剔除并告警
      （沿用本工具 v4→v3 的既有口径：两侧阵容变换完全一致）。
    * null 插座保留占位（setGem 的槽位下标语义）。
    """
    entries = []
    for it in lu_side["items"]:
        key = it["identifier"]
        if key not in db:
            warnings.append("物品不在 battle_items.json（不可装配）：%s" % key)
            continue
        gems = []
        for g in (it.get("gems") or []):
            if g is None:
                gems.append(None)
            elif g in db:
                gems.append(g)
            else:
                gems.append(None)
                warnings.append("剔除不可装配宝石：%s:%s" % (key, g))
        entries.append({
            "key": key,
            "row": int(it["top_left"]["y"]),
            "col": int(it["top_left"]["x"]),
            "rotation": (int(it.get("face_direction", 0) or 0) * 90) % 360,
            "gems": gems,
            # r34 crafted 效果真值（lineups.json snapshot 3）：MagicRing 族实例
            # 的 effects（[{triggerType,stackType},...]）。重放里实例先 roll 后被
            # 史真值覆写——模拟器侧必须同序：先照常 roll（链位一致），再用本值
            # 覆写（零 rng 消耗）。无效果字段→None（不注入）。
            "effects": ([
                {"triggerType": int(e["triggerType"]), "stackType": int(e["stackType"])}
                for e in (it.get("effects") or [])
            ] if it.get("effects") else None),
            # ★ np24：crafted 实例真值透传（run871 定谳：实例≠配方图）
            "crafted": bool(it.get("crafted")),
        })
    return entries


# ★ 扩样语料（docs/expand_fix_kickoff.md §6.2）：合并库 runID 带 +100000×库序号
#   偏移，只存在于 output/oracle/expand/data/history.db——硬编码基线库会查不到行
#   ⇒ stamina 静默退回 base ⇒ gd 腿与神谕从开战不同源（假分歧）。覆盖入口：
#   ① 环境变量 EXPAND_HISTORY_DB（模块加载时生效）；② --history-db 参数；
#   ③ 驱动进程内调 set_history_db()。三者都缺省 = 基线库，行为零回归。
_HISTORY_DB = os.environ.get("EXPAND_HISTORY_DB") or os.path.join(
    ROOT, "oracle", "data", "history.db")
_round_stamina_cache = {}


def set_history_db(path: str) -> None:
    """覆盖战斗起始 stamina 的取数库（扩样=合并库；缺行仍按 None 退回 base）。"""
    global _HISTORY_DB
    _HISTORY_DB = path
    _round_stamina_cache.clear()


def _history_round_stamina(run_id: int, round_id: int):
    """语料 run 史的玩家回合开局 stamina 真值（oracle/data/history.db 明文列）。

    oracle_fight.gd:608 G.PLAYER.setMaxStamina(p_round.stamina)——玩家战斗
    开局 max=cur=史记录值，实测分布 5..10（run910_r5=6、run813_r12=5，
    两者阵容画像同含 1 袋：证伪「恒 base」与「恒 base+袋」两个模型）。
    缺库/缺行返回 None（调用方退回 base）。"""
    key = (run_id, round_id)
    if key not in _round_stamina_cache:
        val = None
        try:
            import sqlite3
            con = sqlite3.connect("file:%s?mode=ro" % _HISTORY_DB.replace("\\", "/"), uri=True)
            try:
                row = con.execute(
                    "SELECT stamina FROM roundData WHERE runID=? AND roundID=?",
                    (run_id, round_id)).fetchone()
                if row is not None:
                    val = float(row[0])
            finally:
                con.close()
        except Exception:
            val = None
        _round_stamina_cache[key] = val
    return _round_stamina_cache[key]


def _history_run_custom(run_id):
    """player_run 的存档自定义规则串（runData.custom 列，BitStream 形态原样）。

    ★ np51：oracle harness 逐场 fromString(player_run.customRules)（oracle_fight.gd:591），
    prepare() 按其中的 HealthMultiplier 给双方加静默临时体上限（item=null 无事件）。
    gd/py 腿经 ctx 复原该语义。缺库/缺行返回 ""（=100 零回归）。
    与 _history_round_stamina 同库（--history-db / EXPAND_HISTORY_DB 可换）。"""
    if run_id is None:
        return ""
    key = ("custom", run_id)
    if key not in _round_stamina_cache:
        val = ""
        try:
            import sqlite3
            con = sqlite3.connect("file:%s?mode=ro" % _HISTORY_DB.replace("\\", "/"), uri=True)
            try:
                row = con.execute(
                    "SELECT custom FROM runData WHERE runID=?", (run_id,)).fetchone()
                if row is not None and row[0] is not None:
                    val = str(row[0])
            finally:
                con.close()
        except Exception:
            val = ""
        _round_stamina_cache[key] = val
    return _round_stamina_cache[key]


def custom_health_multiplier_of(serialized: str) -> float:
    """BitStream 串 → CustomRules.Rules.HealthMultiplier（缺省/空串=100）。

    对齐 CustomRules.fromString + BitStream（BASE64OFFSET=62，每字符 6bit
    MSB-first，pull(n)=ceil(log2(n)) 位）：league pull(9)=4 位、BonusGold
    pull(21)=5、BonusTreasures pull(21)=5、HealthMultiplier pull(37)=6，
    值 = pulled×STEP(5) + MIN(20)，范围 20..200。后续规则战斗面不消费。
    python 侧 full-fidelity 实现（内核只吃数值，规避 py String 位操作垫片）。"""
    if not serialized:
        return 100.0
    bits = []
    for ch in serialized:
        v = ord(ch) - 62
        if v < 0 or v > 63:
            return 100.0
        for d in range(5, -1, -1):
            bits.append((v >> d) & 1)
    pos = 0

    def pull(range_max):
        nonlocal pos
        n = int(math.ceil(math.log2(range_max)))
        if pos + n > len(bits):
            return None
        v = 0
        for _ in range(n):
            v = (v << 1) | bits[pos]
            pos += 1
        return v

    pull(9)
    pull(21)
    pull(21)
    hp = pull(37)
    if hp is None or hp < 0:
        return 100.0
    return float(hp * 5 + 20)


def _battle_start_stamina(lu_side: dict, entries: list, is_player: bool,
                          run_id: int = None, round_id: int = None):
    """→ (battle_start_stamina, base_stamina)。依据见文件头「战斗起始体力约定」。"""
    base = float(lu_side.get("base_max_stamina", 5.0))
    if is_player:
        # r33 真值注入：battle-start = 语料史 roundData.stamina（setMaxStamina
        # 同设 cur，Character.gd:951-956）。缺真值退回 base（旧口径）。
        if run_id is not None and round_id is not None:
            v = _history_round_stamina(run_id, round_id)
            if v is not None:
                return v, base
        return base, base
    # r32 最终模型（RECALC-O-TAIL 双场+run862 OPP 战斗实测）：oracle
    # OPPONENT 战斗 max=base+袋（initHistoryOpponent 尾部显式 recalc 数
    # INVENTORY 袋，run592 OPP max=7 sacks=2 / run813 OPP max=7 sacks=2 /
    # run862 OPP 8.6167 完整攻击链=max≥7）。
    sacks = sum(1 for e in entries if e["key"] == STAMINA_SACK_ID)
    return OPP_BASE_STAMINA + sacks, OPP_BASE_STAMINA


def _v3_lineup(case_id: str, side: str, lu_side: dict, entries: list,
               stamina: float, base_stamina: float, round_id: int) -> dict:
    """装配序条目 → v3 内部阵容（gd_core_py 侧 load_lineup 直接消费）。"""
    return {
        "version": 3,
        "meta": {"name": "oracle_%s_%s" % (case_id, side),
                 "source": "oracle:" + case_id},
        "character": lu_side["class_name"],
        "round": int(round_id),
        # health_override = 神谕 max_health（开局满血；snapshot 里的 current_health
        # 是战斗中值，不用）
        "health_override": lu_side["max_health"],
        "class_modifiers": {"stamina": stamina},
        # 战斗起始 stamina 与 baseMaxStamina 分离（引擎加法键，见 gd_core_engine
        # ::_make_character；对手侧 5 + Stamina Sack 件数 ≠ base）
        "base_max_stamina": base_stamina,
        "backpack": {"grid": {"rows": 7, "cols": 10},
                     "items": [{"id": e["key"], "row": e["row"], "col": e["col"],
                                "rotation": e["rotation"], "quantity": 1,
                                "container": False, "contents": [],
                                # r34：crafted 效果真值（None 时不落键，py 侧同判）
                                "effects": e["effects"],
                                # ★ np24：crafted 实例真值（py 侧同注入）
                                "crafted": e["crafted"],
                                "gems": [{"id": g} for g in e["gems"] if g]}
                               for e in entries]},
        "storage": [],
    }


def oracle_mode(case_dirs: list, lineup_out: str, batch_out: str) -> int:
    from gen_lineup_fixture import placement_of, script_path  # noqa: E402

    # r40 OSError[Errno 22] 修复：外部运行器传参可能带尾随 \r/空格（CRLF 切分
    # 或转义被吃），Windows io.open 对含控制字符的路径恰抛
    # [Errno 22] Invalid argument（np10_data 实证复现）。入口剥不可见尾字符，
    # clean 路径行为不变。
    lineup_out = lineup_out.strip()
    if batch_out:
        batch_out = batch_out.strip()

    db = json.load(io.open(DB_PATH, encoding="utf-8"))["items"]
    # Godot 侧描述符表（item_battle_fixture.json，517 件可装配物品）——用例引用的
    # 每件物品/宝石都必须在表内，否则批量脚本运行期才爆（GDScript 无 try/catch，
    # 单场脚本错误会中止整个批量进程），必须在夹具生成期剔除并如实报告。
    fixture_table_path = os.path.join(ROOT, "gd_core_test", "item_battle_fixture.json")
    table_items = json.load(io.open(fixture_table_path, encoding="utf-8"))["items"]
    os.makedirs(lineup_out, exist_ok=True)

    cases = []
    failed = []
    for case_dir in case_dirs:
        case_dir = case_dir.rstrip("/\\")
        case_id = os.path.basename(case_dir)
        lu_path = os.path.join(case_dir, "lineups.json")
        if not os.path.exists(lu_path):
            failed.append((case_id, "缺 lineups.json"))
            continue
        lu = json.load(io.open(lu_path, encoding="utf-8"))
        round_id = int(lu["round_id"])
        warnings = []
        sides = {}
        batch_sides = {}
        bad = False
        for side, is_player in (("player", True), ("opponent", False)):
            entries = _oracle_side_entries(lu[side], db, warnings)
            missing = [e["key"] for e in entries if e["key"] not in table_items]
            missing += [g for e in entries for g in e["gems"]
                        if g is not None and g not in table_items]
            if missing:
                failed.append((case_id, "物品不在 gd_core 描述符表：%s" % sorted(set(missing))))
                bad = True
                break
            try:
                for e in entries:
                    e["script"] = script_path(e["key"], db[e["key"]])
            except SystemExit as exc:
                failed.append((case_id, str(exc)))
                bad = True
                break
            run_id = None
            # ★ 扩样 case_id 形如 run<玩家>_r<回合>_o<对手>_r<对手回合>（带 _o…
            #   后缀）；旧正则 r"run(\d+)_r\d+$" 尾锚必不匹配 ⇒ run_id=None ⇒
            #   stamina 静默退回 base（kickoff §6.2 同型假分歧）。放宽为可选
            #   _o… 尾段；基线 run<run>_r<round> 仍走第一支，零回归。
            m = re.match(r"run(\d+)_r\d+(?:_o\d+_r\d+)?$", case_id)
            if m:
                run_id = int(m.group(1))
            stamina, base_stamina = _battle_start_stamina(
                lu[side], entries, is_player, run_id, round_id)
            sides[side] = _v3_lineup(case_id, side, lu[side], entries,
                                     stamina, base_stamina, round_id)
            # Godot 侧条目：几何展开成绝对格（Vector2(x=col,y=row) 约定 →
            # occupied/collision/affected 均为 [col,row] 对，与 LineupFixture 一致）
            items_gd = []
            for e in entries:
                ent = db[e["key"]]
                pl = placement_of(e["key"], ent, e["row"], e["col"], e["rotation"])
                sockets = int(table_items[e["key"]]["sockets"])
                gems = e["gems"]
                if len(gems) > sockets:
                    # 原版 socket 数与内核 tscn 扫描数不一致——夹具按内核口径截断
                    # （setGem 越位只会静默 print），截断必须两侧一致并留痕。
                    warnings.append("宝石数 %d > 内核插座数 %d（截断）：%s"
                                    % (len(gems), sockets, e["key"]))
                    gems = gems[:sockets]
                gems_gd = []
                for g in gems:
                    if g is None:
                        gems_gd.append(None)
                    else:
                        gems_gd.append({"key": g, "script": script_path(g, db[g])})
                items_gd.append({
                    "key": e["key"], "script": e["script"],
                    "occupied": pl["occupied"], "collision": pl["collision"],
                    "affected": {str(c): v for c, v in pl["affected"].items()},
                    # 朝向（度数，= 神谕 face_direction×90）：chargeCells 等**本地格**
                    # 常量需按节点旋转映射进背包（ElectricalCharge.start 的
                    # getGlobalPointsForCells），内核装配层用它换算 faceDirection
                    "rotation": e["rotation"],
                    "gems": gems_gd,
                    # r34：crafted 效果真值（None=不注入，键仍保留便于宿主判空）
                    "effects": e["effects"],
                    # ★ np24：crafted 实例真值（Anvil 计数根因）
                    "crafted": e["crafted"],
                })
            batch_sides[side] = {
                "class": int(lu[side]["class"]),
                "health": lu[side]["max_health"],
                "stamina": stamina,
                "base_max_stamina": base_stamina,
                "regen": 1.0,
                "items": items_gd,
            }
            # v3 阵容的 gems 也要走同一截断口径（两侧阵容变换一致）
            if sides[side]["backpack"]["items"]:
                v3i = sides[side]["backpack"]["items"]
                gi = 0
                for e in entries:
                    gems = e["gems"]
                    if len(gems) > int(table_items[e["key"]]["sockets"]):
                        gems = gems[:int(table_items[e["key"]]["sockets"])]
                    v3i[gi]["gems"] = [{"id": g} for g in gems if g]
                    gi += 1
        if bad:
            continue
        for w in warnings:
            print("  [%s] 告警：%s" % (case_id, w))

        for side in ("player", "opponent"):
            path = os.path.join(lineup_out, "oracle_%s_%s.json" % (case_id, side))
            with io.open(path, "w", encoding="utf-8", newline="\n") as fh:
                json.dump(sides[side], fh, ensure_ascii=False, indent=1)
                fh.write("\n")

        # ★ np51：player_run 自定义规则 → 夹具 case 级 custom_health_multiplier
        #   （位流在夹具层解析为数值）→ gd/py 腿 ctx 复原 prepare() 健康倍率。
        m_case = re.match(r"run(\d+)_r\d+(?:_o\d+_r\d+)?$", case_id)
        cases.append({
            "case_id": case_id,
            "seed": int(lu["seed"]),
            "round_id": round_id,
            "custom_health_multiplier": custom_health_multiplier_of(
                _history_run_custom(int(m_case.group(1)) if m_case else None)),
            "player": batch_sides["player"],
            "opponent": batch_sides["opponent"],
        })

    if batch_out:
        os.makedirs(os.path.dirname(os.path.abspath(batch_out)), exist_ok=True)
        with io.open(batch_out, "w", encoding="utf-8", newline="\n") as fh:
            json.dump({"format": "oracle-align-cases/1",
                       "generated_by": "tools/gen_fixture_from_lineup.py --oracle",
                       "note": "items 数组即装配顺序（原版 sort_BagOrder 后）；"
                               "激活顺序由 OracleAlignBattle.gd 用真 Godot 全局链 "
                               "seed(S)+shuffle+sort_TriggerPriority 现场复刻",
                       "cases": cases}, fh, ensure_ascii=False, separators=(",", ":"))
            fh.write("\n")

    print("神谕夹具：%d 场生成 / %d 场失败"
          % (len(cases), len(failed)))
    for case_id, why in failed:
        print("  [FAIL] %s：%s" % (case_id, why))
    if batch_out:
        print("批量夹具：%s（%d 场）" % (batch_out, len(cases)))
    return 0 if not failed else 1


def main() -> int:
    argv = sys.argv[1:]
    if argv and argv[0] == "--oracle":
        case_dirs, lineup_out, batch_out, history_db = [], None, None, None
        i = 1
        while i < len(argv):
            if argv[i] == "--lineup-out":
                lineup_out = argv[i + 1]
                i += 2
            elif argv[i] == "--batch-out":
                batch_out = argv[i + 1]
                i += 2
            elif argv[i] == "--history-db":
                history_db = argv[i + 1]
                i += 2
            else:
                case_dirs.append(argv[i])
                i += 1
        if not case_dirs:
            print("用法：--oracle <用例目录>... [--lineup-out 目录] [--batch-out 文件]"
                  " [--history-db 库文件]")
            return 2
        if history_db:
            set_history_db(history_db)
            print("stamina 取数库（--history-db）：%s" % history_db)
        elif os.environ.get("EXPAND_HISTORY_DB"):
            print("stamina 取数库（EXPAND_HISTORY_DB）：%s" % _HISTORY_DB)
        if lineup_out is None:
            lineup_out = os.path.join(ROOT, "output", "oracle", "align", "lineups")
        return oracle_mode(case_dirs, lineup_out, batch_out)
    return main_legacy()


if __name__ == "__main__":
    raise SystemExit(main())
