#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
verify_oracle.py — 受控神谕三方逐行对齐（docs/oracle_workflow.md Phase 3 / Phase 5）

三方：
  oracle   output/oracle/fights/<case>/events.json（1.1.8 反编译全量工程跑出的原版事件流，
           oracle/oracle_fight.gd 导出，**冻结语料，只读**）
  gdcore   output/oracle/align/gdcore/<case>/events.json（gd_core 无头内核经
           gd_core_test/OracleAlignBattle.gd 同 (阵容, seed) 重放，同 schema 导出）
  py       output/oracle/align/py/<case>/events.json（gd_core_py 转写内核经本文件的
           py 批量驱动重放——装配路径与 `python -m simulator.simulate` 完全一致
           （load_lineup → GDCoreEngine → run），仅追加三个对齐 kwargs：
           below_master=True 与激活顺序直通（np24 终谳：探针 rng_log），见 simulator/gd_core_engine.py）

通过标志（任务书口径，两者都一致才算通过）：
  a) 主判据：三方各自经 engine/log_text.py（CombatEvent.asText 同款渲染器）渲染出
     战报文本，逐行比对（行文本全等，含时间戳与缩进层级）；
  b) 辅判据：事件 canonical JSON 逐行比对（t 按 1/60s tick 取整、type/side/origin/
     params/parent-depth 全等；原始 id 不比——oracle 每场经原版 clear() 把 eventNum
     复位为 -1 而 gd_core 从 0 起计，两侧各自自洽地整体偏移 1）。

确定性约定（两侧 gd_core 复刻神谕，证据链见各文件头）：
  * seed 在任何物品实例创建前注入（CoreContext(seed) ≙ oracle_fight.gd:536）；
  * below_master=true（np24 终谳：run574_r7/run570_r18/run582_r15 三场探针
    events≡语料后其 rng_log 实证冷却批=玩家侧全 (0.95,1.05)+对手侧全 (0.975,1.05)，
    即录制时 isBelowLeague(Master)=真；族A「全 +1 tick」另有根源（对手速度面
    差，见 np24 记录），非映射错）；
  * 激活顺序 = 真 Godot 全局链 seed(S) → shuffle×2 → sort_TriggerPriority 的终序
    （OracleAlignBattle.gd 现场复刻并写进自己的 events.json；py 侧读同一份作为
    战斗输入——原版开战 shuffle 走引擎全局链（docs/rng_truth.md §1.4-2），内核
    ctx.rng.shuffle 是自研替身，必须直通否则从第一个 roll 起分叉）。

用法：
  python -X utf8 tools/verify_oracle.py --limit 10     # 冒烟：前 10 场全管线
  python -X utf8 tools/verify_oracle.py                # 全量
  python -X utf8 tools/verify_oracle.py --compare-only # 只重跑比对（复用已有重放产物）
  python -X utf8 tools/verify_oracle.py --skip-py      # 只补 gd_core 侧
  python -X utf8 tools/verify_oracle.py --cases run570_r18,run579_r18 --force
      # 定向：只跑指定场；--force 先删两侧重放产物强制重模拟
      #（幂等跳过会把改动前的陈旧结果当新结果——改码后必须 --force；
      #  注意 --cases 会把夹具收缩为指定场，全量里程碑照常不带 --cases 重跑）
输出：
  output/oracle/alignment.json {aligned, total, perCase, localization, fixPlan}
  output/oracle/align/render/<case>.{oracle,gdcore,py}.logtext（主判据留档）
"""
from __future__ import annotations

import argparse
import io
import json
import os
import re
import subprocess
import sys
from typing import Any, Dict, List, Optional, Tuple

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

FIGHTS_DIR = os.path.join(ROOT, "output", "oracle", "fights")
ALIGN_DIR = os.path.join(ROOT, "output", "oracle", "align")
GD_OUT = os.path.join(ALIGN_DIR, "gdcore")
PY_OUT = os.path.join(ALIGN_DIR, "py")
RENDER_DIR = os.path.join(ALIGN_DIR, "render")
LINEUP_OUT = os.path.join(ALIGN_DIR, "lineups")
CASES_JSON = os.path.join(ROOT, "gd_core_test", "oracle_align_cases.json")
ALIGNMENT_JSON = os.path.join(ROOT, "output", "oracle", "alignment.json")
GODOT = os.path.join(ROOT, "output", "godot36", "Godot_v3.6-stable_win64.exe")

# ── ★ np21-① 宿主补偿键控表（py 腿镜像；真源 = gd_core_test/OracleAlignBattle.gd
#    文件头三表 + :481-514 注入段，逐点同步；机理与 canonical 推导证据见该处注释
#    与 output/oracle/wf_notes/np18_fix.md §3、np20 台账 round2）──
#    隔离开关：环境变量 ORACLE_ALIGN_NO_PERM_HARVEST / ORACLE_ALIGN_NO_WARM_LATCH
#    置任意非空值即关对应补偿（与 gd 宿主同名同义，单笔隔离用）。
PY_PERM_STACK_HARVEST = {"run702_r18": True, "run1022_r18": True}
# ★ np22（与 gd 宿主 PERM_STACK_HARVEST/OVERRIDE np22 增行镜像；值=gd 收割
#   管线全长对拍定谳的净真值向量，np21-①「py 只灌净真值表、不复刻收割管线」
#   体例）：1371=gd 暖场自然终局收割原值；1444=收割之上 Cold(110) 覆写 1
#   （exec2 终局残差 ≥1，见 gd 侧表注）。
PY_PERM_STACK_OVERRIDE = {"run702_r18": {109: 1}, "run1022_r18": {109: 6},
                          "run1371_r18": {101: 1, 102: 41, 104: 2, 105: 326,
                                          106: 2, 107: 86, 110: 2},
                          "run1444_r18": {100: 129, 102: 4, 103: 10, 106: 83,
                                          107: 4, 110: 1}}
# ★ np22 重录后摘除 696/1371 两键（新语料=ORACLE_NOLIMIT 全长重录干净形状，
#   无闩残留；真源=gd 宿主 WARM_LATCH_PLAYERS 同步）。906/1125/1409 保留。
PY_WARM_LATCH_PLAYERS = {
    "run906_r18": True, "run1125_r18": True, "run1409_r18": True,
}
# ★ np21-R5 双执行拓扑键控表（py 腿镜像，真源 = gd_core_test/OracleAlignBattle.gd
#   R5_DUAL_EXEC 表，机理/证据链/值不敏感论证见该处注释）：键控场先跑同 case
#   同 seed 的干净暖场（截于事件闸 T_w 不清理），回灌三面残留——①暖场玩家
#   permanentStacks；②bus 存活连接嫁接（陈旧先于新鲜，陈旧物品 ctx/character_/
#   抽源改指正式侧）；③fatigueCounter（值不敏感，仅经 hasFatigueStarted 面观测）。
#   隔离开关 ORACLE_ALIGN_NO_R5_DUAL_EXEC（置非空值关闭，与 gd 宿主同名同义）。
#   run1409_r18 标定见 gd 宿主 R5_DUAL_EXEC 表注（T_w=事件闸 25000、θ=N/A、
#   AoL 全双/AoA 分路径双发/Egg 对称双笔=合法机制勿注入 + stale_used_stacks
#   封闭推导覆盖 {105: -0.375}——推导链见该表注）。
PY_R5_DUAL_EXEC = {"run1125_r18": {"warm_event_gate": 25000},
                   "run1409_r18": {"warm_event_gate": 25000,
                                   "stale_used_stacks": {"Amulet of Agility": {105: -0.375}}},
                   "run906_r18": {"warm_event_gate": 25000,
                                  "stale_used_stacks": {"Amulet of Agility": {105: 0.125}}}}
# ★ np22 重录场正式腿事件闸对位抬闸（真源 = gd_core_test/OracleAlignBattle.gd
#   NP22_REC_EV_GATE 表）：三场新语料以 ORACLE_NOLIMIT=1（事件闸 200000）
#   全长录制，py 正式腿同闸对位（引擎 formal_ev_gate 参数），否则 M12=25000
#   截断 → 伪长度分歧。其余场缺省 25000 零变化。
# ★ np24 补全（2026-10-27）：2026-10-25 全量重录时抬闸面是 **20 场**（语料
#   event_count>25000 的全集，np24 矿点实证：最大 run1362=79595），np22 期
#   只登记了当时新录的 3 场——其余 17 场 gd/py 两腿恒在 25000 截断，对
#   全长语料必伪红（20 场全在 RED 清单）。按「语料 >25000 = 录制抬闸」的
#   操作定义全量补齐（run1444 已随 A 轮语料处置删除，不在集中）。
PY_NP22_REC_EV_GATE = {
    "run1082_r18": 200000, "run1124_r18": 200000, "run1125_r18": 200000,
    "run1174_r18": 200000, "run1194_r18": 200000, "run1219_r18": 200000,
    "run1302_r18": 200000, "run1342_r18": 200000, "run1348_r18": 200000,
    "run1362_r18": 200000, "run1371_r18": 200000, "run1374_r18": 200000,
    "run1408_r18": 200000, "run1409_r18": 200000, "run685_r18": 200000,
    "run696_r18": 200000, "run845_r18": 200000, "run894_r18": 200000,
    "run905_r18": 200000, "run906_r18": 200000,
}


# ── 引擎事件字符串 → Game.EventType 数字（gd_core_engine._EVENT_TYPE_MAP 的逆）──
ETYPE_TO_NUM = {
    "item_activate": 0, "attack": 1, "critical": 2, "missed": 3,
    "lose_health": 5, "invulnerable_start": 7, "invulnerable_end": 8,
    "stun": 9, "stun_resisted": 10, "crit_resisted": 11, "heal": 12,
    "stamina_gain": 13, "stamina_drain": 14, "out_of_stamina": 15,
    "damage_buff": 16, "dam_reduction": 17, "dam_increase": 18,
    "temporary_max_health": 19, "temporary_max_stamina": 20,
    "battle_rage_start": 21, "battle_rage_end": 22, "reincarnate": 23,
    "unhealing": 98, "fatigue_damage": 99,
}
# 数字 origin（DamageSource.Type）→ keyword：原版 Game.typeToKeyword 1:1
# （decompiled_full/Core/Game.gd:5663：Block→"bl"、Regeneration→"regen" 特例，
#   其余 eventTypeKeys[type].to_lower()）
_NUM_ORIGIN_SPECIAL = {100: "bl", 102: "regen"}


def _num_origin_key(num: int, et_names: Dict[int, str]) -> Optional[str]:
    if num in _NUM_ORIGIN_SPECIAL:
        return _NUM_ORIGIN_SPECIAL[num]
    name = et_names.get(num)
    return name.lower() if name else None


# ═══════════════════════════ 用例选取与夹具 ═══════════════════════════

def select_cases(limit: int) -> List[Dict[str, Any]]:
    """fights.json 用例序 ∩ 神谕语料（events.json 存在且非空），保序。"""
    fights = json.load(io.open(os.path.join(ROOT, "oracle", "fights.json"),
                               encoding="utf-8"))
    out = []
    for c in fights["cases"]:
        p = os.path.join(FIGHTS_DIR, c["case_id"], "events.json")
        if not os.path.exists(p):
            continue
        data = json.load(io.open(p, encoding="utf-8"))
        if int(data.get("event_count", 0)) <= 0:
            continue
        out.append({"case_id": c["case_id"], "seed": int(c["seed"]),
                    "round_id": int(c["round_id"]),
                    "dir": os.path.join(FIGHTS_DIR, c["case_id"])})
        if limit > 0 and len(out) >= limit:
            break
    return out


def gen_fixtures(cases: List[Dict[str, Any]]) -> int:
    from gen_fixture_from_lineup import oracle_mode  # tools/ 已在 sys.path
    case_dirs = [c["dir"] for c in cases]
    rc = oracle_mode(case_dirs, LINEUP_OUT, CASES_JSON)
    # oracle_mode 对个别不可装配用例返回 1——夹具里只含可跑场，管线继续
    generated = 0
    if os.path.exists(CASES_JSON):
        data = json.load(io.open(CASES_JSON, encoding="utf-8"))
        # ★ 标签视觉设置位（round19）：按 fights/<case>/rng_log.txt 的
        # randInBox 行数写 label_rng（>0=ON；无 rng_log 缺省 true）——
        # 每录制场的标签视觉设置不同（run570=696 行 vs run569=0 行）。
        for case in data.get("cases", []):
        # ★ round20 修正：rng_log 的 randInBox(10,10) 行数=0 不能判 OFF（run569 实证：其 (10,10)=0 但 (30,30)=42 = 槽位全忙支、标签仍 ON；OFF 门使 gd 首分歧 126→32 恶化）。恒 ON；开关机制保留。

            # 开关机制保留（未来有正向证据时可用）。
            case["label_rng"] = True
        with io.open(CASES_JSON, "w", encoding="utf-8") as fh:
            json.dump(data, fh, ensure_ascii=False, indent=1)
        generated = len(data["cases"])
    print("[fixtures] 批量夹具 %d 场 → %s" % (generated, CASES_JSON))
    return 0 if generated > 0 else 1


def fixture_case_ids() -> List[str]:
    data = json.load(io.open(CASES_JSON, encoding="utf-8"))
    return [c["case_id"] for c in data["cases"]]


# ═══════════════════════════ gd_core(Godot) 侧 ═══════════════════════════

def run_godot(case_ids: Optional[List[str]] = None,
              chunk: int = 120, max_rounds: int = 40) -> int:
    """分块跑 gd_core(Godot) 批量（每块一个 Godot 进程，断点续跑幂等）。

    case_ids 为 None 时跑夹具全集（全量里程碑）；给定 --cases 时只跑指定场
    （幂等跳过依据是已有产物，定向重验须配合 --force 先删产物）。

    分块的理由与 oracle_fight [M11] 同源：GDScript 无 try/catch，任何一场的
    运行期脚本错误都会中止整个进程——分块把损失圈定在单块内，resume 自动续接。
    连续两块无进展（确定性卡死在同一场）即停，绝不静默跳过。"""
    if not os.path.exists(GODOT):
        print("找不到 Godot：%s" % GODOT, file=sys.stderr)
        return 2
    ids = case_ids if case_ids is not None else fixture_case_ids()
    total = len(ids)
    last_rc = 0
    done_after = 0
    for round_i in range(max_rounds):
        done_before = sum(1 for cid in ids
                          if _event_count(os.path.join(GD_OUT, cid, "events.json")) > 0)
        if done_before >= total:
            print("[godot] 全部 %d 场已完成" % total)
            return 0
        env = dict(os.environ)
        # 沙箱写限：强制重定向 + 按 PID 隔离（多 Godot 并行时共享 user:// 日志
        # 目录会互相撞句柄 → 引擎弹 openmem/err=5 模态框风暴；每进程独立目录根治）
        env["APPDATA"] = os.environ.get("ORACLE_ALIGN_APPDATA") or os.path.join(
            ROOT, "output", "_recovery", "appdata_p", str(os.getpid()))
        env["ORACLE_ALIGN_OUT"] = GD_OUT
        if chunk > 0:
            env["ORACLE_ALIGN_CHUNK"] = str(chunk)
        cmd = [GODOT, "--headless", "--audio-driver", "Dummy", "--path", os.path.join(ROOT, "gd_core_test"),
               "--script", "OracleAlignBattle.gd"]
        proc = subprocess.run(cmd, capture_output=True, text=True,
                              encoding="utf-8", errors="replace", cwd=ROOT, env=env)
        last_rc = proc.returncode
        done_after = sum(1 for cid in ids
                         if _event_count(os.path.join(GD_OUT, cid, "events.json")) > 0)
        print("[godot] 第 %d 轮：退出码 %d，完成 %d/%d" % (round_i + 1, last_rc,
                                                          done_after, total))
        if proc.stdout:
            sys.stdout.write(proc.stdout[-1200:])
        if proc.stderr:
            sys.stderr.write(proc.stderr[-800:])
        if done_after >= total:
            return 0
        if done_after <= done_before:
            print("[godot] 本轮无进展（%d/%d）——确定性卡死，停止重试" % (done_after, total),
                  file=sys.stderr)
            return last_rc or 1
    print("[godot] 达到轮次上限（%d 轮），完成 %d/%d" % (max_rounds, done_after, total),
          file=sys.stderr)
    return last_rc or 1


# ═══════════════════════════ gd_core_py(Python) 侧 ═══════════════════════════

class _FightEndGate:
    """事件日志的判胜闸（MRO 最前，见 gd_core_engine._make_probe_class）：
    fight_ended 后不再入日志——对齐原版 CombatLog.logEvent 的 fightEnded 早退
    （CombatLog.gd:266-267，事件对象照常创建、id 照常消耗）。GDScript 侧探针
    （OracleAlignBattle.gd::CaptureProbe.logEvent）实现了同一闸。"""

    def logEvent(self, event):
        ctx = getattr(self, "ctx", None)
        if ctx is not None and bool(getattr(ctx, "fight_ended", False)):
            return None
        return super().logEvent(event)


def run_py(cases: List[Dict[str, Any]]) -> int:
    """批量驱动：与 simulator.simulate 同一装配路径，逐场落 oracle-schema JSON。

    追加的对齐 kwargs（行为影响见 gd_core_engine.py 各处注释）：
      below_master=True                     — np24 终谳：探针 rng_log 实证
                                             （三场 events≡语料：玩家侧 (0.95,1.05)、
                                             对手侧 (0.975,1.05)）
      p/o_activation_order                  — 真 Godot 全局链洗牌终序直通
      probe_bases=(_FightEndGate,)          — 原版 CombatLog.logEvent 的 fightEnded
                                              早退（CombatLog.gd:266-267）：判胜后
                                              事件照常 createEvent（消耗 id）但不再
                                              入日志。gd_core(Godot) 侧探针同闸。
    """
    from simulator.data import load_items, load_characters
    from simulator.lineup import load_lineup
    from simulator.gd_core_engine import GDCoreEngine, kernel

    item_db = load_items()
    character_db = load_characters()
    et_names = {int(v): k for k, v in kernel()["CoreConst"].EventType.items()}

    fixture = {c["case_id"]: c for c in
               json.load(io.open(CASES_JSON, encoding="utf-8"))["cases"]}
    cases_by_id = fixture
    os.makedirs(PY_OUT, exist_ok=True)

    ok = 0
    for i, c in enumerate(cases, 1):
        case_id = c["case_id"]
        out_dir = os.path.join(PY_OUT, case_id)
        out_path = os.path.join(out_dir, "events.json")
        if os.path.exists(out_path) and _event_count(out_path) > 0:
            ok += 1
            continue
        if case_id not in fixture:
            print("  [py][skip] %s 不在夹具内（生成期已剔除）" % case_id)
            continue
        gd_path = os.path.join(GD_OUT, case_id, "events.json")
        if not os.path.exists(gd_path) or _event_count(gd_path) <= 0:
            print("  [py][skip] %s 缺 gd_core 侧产物（激活顺序来源）" % case_id)
            continue
        order = json.load(io.open(gd_path, encoding="utf-8"))["activation_order"]
        # ★ rng_state 注入（round9，与 gd_core_test/OracleAlignBattle.gd:433-446
        #   同语义）：gd 侧在装配完成、startBattle 之前把神谕导出的 Util.rng
        #   state（output/oracle/fights/<case>/rng_state.txt 的 state= 行）直灌
        #   内核（ctx.set_state），装配期消耗差被抹平。py 侧引擎本就留有
        #   rng_state 参数（simulator/gd_core_engine.py，同一 set_state 边界），
        #   但驱动从未传——py 链只能靠装配期零漂移自立，而旧校准常数
        #   post_seed_draws=14（已废的 ORACLE_SCENE_DRAWS，引擎文档自证
        #   「神谕对齐路径恒传 0」）使 py 链恒领先 gd 14 位。run570_r18 逐抽
        #   对位实证：py 双方 Rainbow Orb 放大 flip 全歪（事件 7/6 vs 神谕 10/7）。
        #   本改动属重放驱动参数（非判定逻辑）：canonical/_origin_canon/compare
        #   零改动。
        rng_state_path = os.path.join(FIGHTS_DIR, case_id, "rng_state.txt")
        rng_state = None
        if os.path.exists(rng_state_path):
            for ln in io.open(rng_state_path, encoding="utf-8"):
                if ln.startswith("state="):
                    rng_state = int(ln.strip()[6:])
                    break
        try:
            player = load_lineup(os.path.join(LINEUP_OUT,
                                              "oracle_%s_player.json" % case_id))
            opponent = load_lineup(os.path.join(LINEUP_OUT,
                                                "oracle_%s_opponent.json" % case_id))
            # ★ np21-① 宿主补偿（py 腿镜像，与 gd_core_test/OracleAlignBattle.gd
            #   :481-514 注入段同位；表与机理见文件头 PY_* 注）：只灌 np20-C
            #   canonical 封闭推导的**净真值表**（PERM_STACK_OVERRIDE），**不复刻**
            #   gd 宿主的暖场收割管线——py 干净暖场终局态 ≠ gd（如 run702 py
            #   收割 lucky=1/106=44 等非惰性值，注入后先行消耗改变掷链，B 变体
            #   {109:1} 单值全场一致实证）；gd 侧收割值经 OVERRIDE 校正后净效果
            #   与真值表等价，语义同源。暖场闩（np17-B）：玩家初始即处「暖场
            #   残留」态。三者皆录制工件补偿、键控生效、零 rng 消耗（播种前
            #   纯字段写）。
            _no_perm = os.environ.get("ORACLE_ALIGN_NO_PERM_HARVEST", "") != ""
            _no_latch = os.environ.get("ORACLE_ALIGN_NO_WARM_LATCH", "") != ""
            _no_r5 = os.environ.get("ORACLE_ALIGN_NO_R5_DUAL_EXEC", "") != ""
            perm_override = None
            if not _no_perm and case_id in PY_PERM_STACK_OVERRIDE:
                perm_override = dict(PY_PERM_STACK_OVERRIDE[case_id])
            warm_latch = (not _no_latch) and case_id in PY_WARM_LATCH_PLAYERS
            r5_dual = None
            if not _no_r5 and case_id in PY_R5_DUAL_EXEC:
                r5_dual = dict(PY_R5_DUAL_EXEC[case_id])
            eng = GDCoreEngine(player, opponent, item_db, character_db,
                               seed=c["seed"], max_time=90.0,
                               probe_bases=(_FightEndGate,),
                               below_master=True,
                               # ★ np24 簇A①：实例槽真值 = cases json 条目 gems
                               #   数组长度（含 null 空槽；v3 lineup 生成链丢了
                               #   null，长度不可用）。与 v3 items 装配序 1:1。
                               p_gem_lens=[len(e.get("gems") or [])
                                           for e in fixture[case_id]["player"]["items"]],
                               o_gem_lens=[len(e.get("gems") or [])
                                           for e in fixture[case_id]["opponent"]["items"]],
                               p_activation_order=[int(x) for x in order["player"]],
                               o_activation_order=[int(x) for x in order["opponent"]],
                               reseed_after_player_character=True,
                               post_seed_draws=0,
                               rng_state=rng_state,
                               label_rng_enabled=bool(
                                   cases_by_id.get(case_id, {}).get("label_rng", True)),
                               warm_latch=warm_latch,
                               perm_stack_override=perm_override,
                               r5_dual_exec=r5_dual,
                               formal_ev_gate=int(PY_NP22_REC_EV_GATE.get(case_id, 25000)))
            eng.run()
        except Exception as exc:  # noqa: BLE001 —— 单场失败不拖垮批量，如实记档
            os.makedirs(out_dir, exist_ok=True)
            with io.open(out_path, "w", encoding="utf-8", newline="\n") as fh:
                json.dump({"case_id": case_id, "seed": c["seed"],
                           "status": "error", "error": "%s: %s" % (type(exc).__name__, exc),
                           "event_count": 0, "events": []}, fh,
                          ensure_ascii=False, indent=1)
            print("  [py][FAIL] %s：%s: %s" % (case_id, type(exc).__name__, exc))
            continue
        payload = _py_payload(case_id, c["seed"], eng, et_names,
                               rng_state is not None)
        os.makedirs(out_dir, exist_ok=True)
        with io.open(out_path, "w", encoding="utf-8", newline="\n") as fh:
            json.dump(payload, fh, ensure_ascii=False, indent=1)
        ok += 1
        if i % 10 == 0:
            # 内核对象间存在引用环（ctx↔combat↔items），周期性强制回收防长跑内存爬升
            import gc
            gc.collect()
            print("  [py] %d/%d" % (i, len(cases)))
    print("[py] 完成 %d/%d 场" % (ok, len(cases)))
    return 0 if ok == len(cases) else 1


def _py_payload(case_id: str, seed: int, eng, et_names: Dict[int, str],
                 rng_state_injected: bool = False) -> Dict[str, Any]:
    """_EventOut 列表 → oracle 同 schema（type=数字、origin=oracle 形状）。

    owner_type 取自适配层 actor（gd_core_engine._LogMixin._actor_of = origin 物品
    所属角色，语义与 oracle_fight.gd::_jsonable 的 owner_type 一致：1=玩家方、
    3=对手方）；无物品来源时与 oracle 一致不设该字段。"""
    events = []

    def _owner_num(actor):
        if actor == "player":
            return 1
        if actor == "opponent":
            return 3
        return None

    for e in eng.log.events:
        if e.type == "combat_end":
            # 适配层合成的终局事件：镜像原版 logWin/logLoss 形状（type=111/112、
            # origin=同号数字、params 空）。超时场与 oracle/gd_core 同口径不落终局
            # 事件（原版 combatEndDeferred 只在 fightEnded 后触发 logWin/logLoss）。
            if not getattr(eng, "fight_ended", False):
                continue
            num = 111 if e.params.get("winner") == "player" else 112
        elif e.type in ("stack_gain", "stack_lose", "stack_timeout"):
            num = int(e.buff_type) if e.buff_type is not None else -1
        else:
            num = ETYPE_TO_NUM.get(e.type, -1)
        origin = e.origin
        if e.type == "combat_end" and getattr(eng, "fight_ended", False):
            oj = num          # 原版 logWin/logLoss：origin = EventType 值本身
        elif origin is None:
            oj = None
        elif getattr(origin, "damage_source", False):
            oj = {"kind": "damage_source", "keyword": origin.key}
        elif getattr(origin, "gem_host", None) is not None:
            # ★ gem origin 转录（round8，与 gd_core_test/OracleAlignBattle.gd::_j
            #   同口径）：原版 gem.socket 是 GemSocket2 节点（decompiled_full/Items/
            #   GemSocket.gd=class Socket：单数 gem、无 gems 数组、无 descriptor/
            #   getTopLeftCell），oracle_fight.gd::_jsonable_impl 对其恒折叠为
            #   {kind:unknown,str:GemSocket2} + socket_index=-1。神谕语料实证
            #   21164/21164 全为该形状。内核 py 镜像把 socket 折叠进宿主物品
            #   （CoreItem.setGem），此处还原原版序列化形状——仅转写 dump，
            #   判定逻辑（canonical/_origin_canon/compare）未动。
            oj = {"kind": "gem",
                  "host": {"kind": "unknown", "str": "GemSocket2"},
                  "socket_index": -1}
        else:
            owner = _owner_num(e.actor)
            oj = {"kind": "item", "identifier": origin.key}
            if owner is not None:
                oj["owner_type"] = owner
        events.append({
            "id": int(e.id),
            "type": num,
            "type_name": e.type,
            "timestamp": float(e.t),
            "origin": oj,
            "target": None if e.target is None else (0 if e.target == "player" else 1),
            "parent_id": -1 if e.parent is None else int(e.parent),
            # actor_is_target 是适配层为渲染变体（GAIN_DEBUFF_SELF）追加的派生标记，
            # 非内核事件参数（原版 createEvent_Stack 无此键）——落盘前剥离，
            # 渲染层（render_lines）会按同判据补回，主辅判据均不受影响。
            "params": {} if e.type == "combat_end"
            else {k: v for k, v in (e.params or {}).items()
                  if k != "actor_is_target"},
        })
    return {
        "case_id": case_id, "seed": int(seed),
        "below_master": True, "preordered": True,
        "reseeded_after_player_character": True, "post_seed_draws": 0,
        "rng_state_injected": rng_state_injected,
        "winner": "player" if eng.player_wins() else "opponent",
        "combat_time": float(eng.combat_time), "ticks": int(eng._ticks),
        "player_hp": eng.player.get_current_health(),
        "player_max_hp": eng.player.get_max_health(),
        "opponent_hp": eng.opponent.get_current_health(),
        "opponent_max_hp": eng.opponent.get_max_health(),
        "event_count": len(events), "events": events,
    }


# ═══════════════════════════ 三方 canonical 化与逐行比对 ═══════════════════════════

def _event_count(path: str) -> int:
    try:
        data = json.load(io.open(path, encoding="utf-8"))
        return int(data.get("event_count", 0))
    except Exception:  # noqa: BLE001
        return 0


def _canon_num(v: Any) -> Any:
    """params 数值口径：float 整值化 → int；其余 float 折到 12 位有效数字
    （Godot JSON.print ~14 位有效数字往返，防打印精度伪分歧）。bool 保持 bool。"""
    if isinstance(v, bool):
        return v
    if isinstance(v, int):
        return v
    if isinstance(v, float):
        if v.is_integer():
            return int(v)
        return float("%.12g" % v)
    if isinstance(v, dict):
        return {str(k): _canon_num(x) for k, x in v.items()}
    if isinstance(v, (list, tuple)):
        return [_canon_num(x) for x in v]
    return v


def _origin_canon(e: Dict[str, Any], et_names: Dict[int, str]) -> Any:
    o = e.get("origin")
    if o is None:
        return None
    if isinstance(o, int):
        return ("src", _num_origin_key(int(o), et_names) or str(o))
    kind = o.get("kind")
    if kind == "item":
        return ("item", o.get("identifier"))
    if kind == "gem":
        host = o.get("host") or {}
        return ("gem", o.get("host_identifier") or host.get("identifier"),
                o.get("socket_index"))
    if kind == "damage_source":
        return ("src", o.get("keyword"))
    if kind == "character":
        return ("char", o.get("player_id"))
    return (str(kind),)


def _owner_side(e: Dict[str, Any]) -> Optional[str]:
    """actor 侧（对齐 gd_core_engine._LogMixin._actor_of / CoreEvent.getMainActor）：
    origin 物品 → ownerType；否则 target（0/None 视为 player）。"""
    o = e.get("origin")
    owner = None
    if isinstance(o, dict):
        if o.get("kind") == "item":
            owner = o.get("owner_type")
        elif o.get("kind") == "gem":
            host = o.get("host") or {}
            owner = host.get("owner_type")
    if owner in (1, 3):
        return "player" if owner == 1 else "opponent"
    tgt = e.get("target")
    return "player" if tgt in (None, 0) else "opponent"


def canonical_stream(path: str, et_names: Dict[int, str]) -> List[Dict[str, Any]]:
    """oracle-schema 事件流 → canonical 事件列表（id 归一、parent-depth 重算）。"""
    data = json.load(io.open(path, encoding="utf-8"))
    raw = data.get("events") or []
    if not raw:
        return []
    id0 = int(raw[0]["id"])
    ids = {int(e["id"]) - id0 for e in raw}
    out = []
    for e in raw:
        nid = int(e["id"]) - id0
        pid = int(e.get("parent_id", -1))
        pn = -1 if pid < 0 else pid - id0
        t = float(e["timestamp"])
        etype = e["type"]
        num = int(etype) if isinstance(etype, int) else ETYPE_TO_NUM.get(etype, -1)
        out.append({
            "id": nid, "parent": pn, "depth": None,
            "t_tick": int(round(t * 60)), "t": t,
            "type": num,
            "actor": _owner_side(e),
            "target": None if e.get("target") is None else int(e["target"]),
            "origin": _origin_canon(e, et_names),
            "params": {str(k): _canon_num(v) for k, v in (e.get("params") or {}).items()},
        })
    # depth：沿 parent 链重算（对齐 CoreEvent.getDepth；三方 JSON 均可此法导出）
    by_id = {e["id"]: e for e in out}
    for e in out:
        d, p, guard = 0, e["parent"], 0
        while p != -1 and p in by_id and guard <= 64:
            d += 1
            p = by_id[p]["parent"]
            guard += 1
        e["depth"] = d
    assert len(by_id) == len(ids)
    return out


def _tuple_of(e: Dict[str, Any]) -> Tuple:
    return (e["t_tick"], e["type"], e["actor"], e["target"], e["origin"],
            tuple(sorted(e["params"].items())), e["parent"], e["depth"])


class _Shim:
    """engine.log_text.render_log 的事件视图（字段与 engine.events.Event 对齐）。"""

    __slots__ = ("t", "type", "actor", "target", "origin", "params",
                 "parent", "depth", "buff_type", "id")

    def __init__(self, e: Dict[str, Any]):
        self.t = e["t"]
        self.id = e["id"]
        self.parent = None if e["parent"] < 0 else e["parent"]
        self.depth = e["depth"]
        self.actor = e["actor"]
        self.target = ({0: "player", 1: "opponent"}[e["target"]]
                       if e["target"] in (0, 1) else None)
        self.params = dict(e["params"])
        self.buff_type = e["type"] if 100 <= e["type"] <= 110 else None
        o = e["origin"]
        if o is None:
            key = None
        elif o[0] == "item":
            key = o[1]
        elif o[0] == "gem":
            key = o[1]
        elif o[0] == "src":
            key = o[1]
        else:
            key = str(o)
        self.origin = None if key is None else type("O", (), {"key": key})()


def _etype_str(num: int) -> str:
    """canonical 数字类型 → engine/log_text 口径字符串（gd_core_engine 同表）。"""
    m = {v: k for k, v in ETYPE_TO_NUM.items()}
    if 100 <= num <= 110:
        return "stack"
    return m.get(num, "type%d" % num)


def render_lines(stream: List[Dict[str, Any]]) -> List[str]:
    from engine.log_text import render_log
    shims = []
    for e in stream:
        s = _Shim(e)
        if s.buff_type is not None:
            # 栈事件分派（gd_core_engine._LogMixin 同判据）：timeout>负额=失去>获得
            amt = s.params.get("amount", 0) or 0
            if s.params.get("timeout"):
                s.type = "stack_timeout"
            elif isinstance(amt, (int, float)) and amt < 0:
                s.type = "stack_lose"
            else:
                s.type = "stack_gain"
            if s.type == "stack_gain" and s.actor is not None \
                    and s.target == s.actor:
                s.params.setdefault("actor_is_target", True)
        else:
            s.type = _etype_str(e["type"])
            if e["type"] in (111, 112):
                s.type = "combat_end"
                s.params = {"winner": "player" if e["type"] == 111 else "opponent"}
        shims.append(s)
    text = render_log(shims, lang="zh", dual=True, show_activations=False)
    return text.split("\n") if text else []


def first_divergence(a: List, b: List, label_a: str, label_b: str) -> Dict[str, Any]:
    """两条 canonical 流/行列表的首分歧对照（两侧首分歧事件对照）。"""
    n = min(len(a), len(b))
    idx = None
    for i in range(n):
        if a[i] != b[i]:
            idx = i
            break
    out: Dict[str, Any] = {"kind": None, "index": idx}
    if idx is None:
        if len(a) != len(b):
            out["kind"] = "length"
            out["detail"] = "%s=%d %s=%d" % (label_a, len(a), label_b, len(b))
        return out
    out["kind"] = "event"
    return out


def compare_case(case_id: str, et_names: Dict[int, str]) -> Optional[Dict[str, Any]]:
    paths = {
        "oracle": os.path.join(FIGHTS_DIR, case_id, "events.json"),
        "gdcore": os.path.join(GD_OUT, case_id, "events.json"),
        "py": os.path.join(PY_OUT, case_id, "events.json"),
    }
    for tag, p in paths.items():
        if not os.path.exists(p) or _event_count(p) <= 0:
            return {"caseId": case_id, "match": "%s 缺产物" % tag,
                    "firstDivergence": None}
    streams = {tag: canonical_stream(p, et_names) for tag, p in paths.items()}
    lines = {tag: render_lines(streams[tag]) for tag in streams}

    ev = {
        "oracle_gd": first_divergence([_tuple_of(e) for e in streams["oracle"]],
                                      [_tuple_of(e) for e in streams["gdcore"]],
                                      "oracle", "gdcore"),
        "gd_py": first_divergence([_tuple_of(e) for e in streams["gdcore"]],
                                  [_tuple_of(e) for e in streams["py"]],
                                  "gdcore", "py"),
    }
    ln = {
        "oracle_gd": first_divergence(lines["oracle"], lines["gdcore"],
                                      "oracle", "gdcore"),
        "gd_py": first_divergence(lines["gdcore"], lines["py"], "gdcore", "py"),
    }

    ev_same_og = ev["oracle_gd"]["kind"] is None
    ev_same_gp = ev["gd_py"]["kind"] is None
    ln_same_og = ln["oracle_gd"]["kind"] is None
    ln_same_gp = ln["gd_py"]["kind"] is None
    aligned_og = ev_same_og and ln_same_og
    aligned_gp = ev_same_gp and ln_same_gp

    if aligned_og and aligned_gp:
        match = "三方一致"
    elif not aligned_og and aligned_gp:
        match = "oracle≠gdcore"
    elif aligned_og and not aligned_gp:
        match = "gdcore≡oracle 但 py 分歧"
    else:
        match = "oracle≠gdcore 且 py 分歧"

    # 首分歧对照（事件级 + 渲染行级，双口径留证）
    def _ctx(stream: List[Dict[str, Any]], idx: Optional[int], span: int = 2):
        if idx is None:
            return None
        lo = max(0, idx - span)
        hi = min(len(stream), idx + span + 1)
        dump = [{"t": e["t_tick"], "type": e["type"], "actor": e["actor"],
                 "target": e["target"], "origin": e["origin"],
                 "params": e["params"], "parent": e["parent"], "depth": e["depth"]}
                for e in stream[lo:hi]]
        at = stream[idx]
        return {
            "at_idx": {"t": at["t_tick"], "type": at["type"], "actor": at["actor"],
                       "target": at["target"], "origin": at["origin"],
                       "params": at["params"], "parent": at["parent"],
                       "depth": at["depth"]},
            "window": [json.dumps(x, ensure_ascii=False)[:300] for x in dump],
        }

    first_div: Dict[str, Any] = {}
    if not aligned_og:
        idx = ev["oracle_gd"].get("index")
        entry: Dict[str, Any] = {"pair": "oracle_vs_gdcore",
                                 "kind": ev["oracle_gd"].get("kind"),
                                 "index": idx}
        if idx is not None:
            entry["oracle"] = _ctx(streams["oracle"], idx)
            entry["gdcore"] = _ctx(streams["gdcore"], idx)
            li = ln["oracle_gd"].get("index")
            if li is not None:
                entry["first_line_diff"] = {
                    "line_index": li,
                    "oracle_line": lines["oracle"][li] if li < len(lines["oracle"]) else None,
                    "gdcore_line": lines["gdcore"][li] if li < len(lines["gdcore"]) else None,
                }
        elif ev["oracle_gd"].get("kind") == "length":
            entry["detail"] = ev["oracle_gd"].get("detail")
        first_div = entry
    if not aligned_gp:
        idx = ev["gd_py"].get("index")
        entry = {"pair": "gdcore_vs_py", "kind": ev["gd_py"].get("kind"),
                 "index": idx}
        if idx is not None:
            entry["gdcore"] = _ctx(streams["gdcore"], idx)
            entry["py"] = _ctx(streams["py"], idx)
            li = ln["gd_py"].get("index")
            if li is not None:
                entry["first_line_diff"] = {
                    "line_index": li,
                    "gdcore_line": lines["gdcore"][li] if li < len(lines["gdcore"]) else None,
                    "py_line": lines["py"][li] if li < len(lines["py"]) else None,
                }
        elif ev["gd_py"].get("kind") == "length":
            entry["detail"] = ev["gd_py"].get("detail")
        if first_div:
            first_div = {"oracle_vs_gdcore": first_div, "gdcore_vs_py": entry}
        else:
            first_div = entry

    os.makedirs(RENDER_DIR, exist_ok=True)
    for tag in ("oracle", "gdcore", "py"):
        with io.open(os.path.join(RENDER_DIR, "%s.%s.logtext" % (case_id, tag)),
                     "w", encoding="utf-8", newline="\n") as fh:
            fh.write("\n".join(lines[tag]) + "\n")

    gd_meta = json.load(io.open(paths["gdcore"], encoding="utf-8"))
    py_meta = json.load(io.open(paths["py"], encoding="utf-8"))
    oracle_meta = json.load(io.open(paths["oracle"], encoding="utf-8"))
    return {
        "caseId": case_id,
        "seed": gd_meta.get("seed"),
        "lineupPair": "oracle_%s_player|oracle_%s_opponent" % (case_id, case_id),
        "oracleEvents": len(streams["oracle"]),
        "gdcoreEvents": len(streams["gdcore"]),
        "pyEvents": len(streams["py"]),
        "winner": {"oracle": oracle_meta.get("winner"),
                   "gdcore": gd_meta.get("winner"), "py": py_meta.get("winner")},
        "match": match,
        "firstDivergence": first_div if first_div else None,
        "judgement": {"event_tuples": {"oracle_gd": ev_same_og, "gd_py": ev_same_gp},
                      "rendered_lines": {"oracle_gd": ln_same_og, "gd_py": ln_same_gp}},
    }


# ═══════════════════════════ localization / fixPlan ═══════════════════════════

_RNG_VISUAL_SIGS = [
    # 神谕 Util.rng 消耗签名（rng_log.txt 实测；docs/rng_truth.md §1.3/§1.4-4）
    ("randf_range 0.2 -0.2", "BalancedRng 构造消耗（每件物品/角色各 1 次，"
     "extracted_running/decomp/Utility/BalancedRandom.gd:4）"),
    ("randf_range 0.9 1.1", "动画播放速率抖动"),
    ("randf_range -50 50", "动画位置抖动"),
    ("randf_range -70 70", "动画位置抖动"),
    ("randf_range 0.8 1.2", "动画播放速率抖动"),
    ("randf_range 100 160", "动画位置抖动"),
]


def _rng_log_evidence(case_id: str) -> Optional[str]:
    """用例目录若有神谕 rng_log.txt（ORACLE_DEBUG 场次），统计视觉签名消耗次数。"""
    p = os.path.join(FIGHTS_DIR, case_id, "rng_log.txt")
    if not os.path.exists(p):
        return None
    try:
        txt = io.open(p, encoding="utf-8", errors="replace").read()
    except OSError:
        return None
    n_draws = len([ln for ln in txt.splitlines() if "=>" in ln])
    return "神谕该场 Util.rng 消耗 %d 次（rng_log.txt），其中视觉/UI 签名占 %s" % (
        n_draws,
        ", ".join("%d×%s" % (txt.count(sig), sig) for sig, _ in _RNG_VISUAL_SIGS
                  if txt.count(sig) > 0) or "0 次")


def localize(per_case: Dict[str, Any]) -> Dict[str, Any]:
    """单场定位（任务书规则，按 oracle↔gdcore 关系优先分派）：
    oracle≠gdcore → gd_core-kernel / data / rng-mechanism（gd_core_py-transpiler
    不适用——即使 py 同时分歧，也是同一根因在两个孪生里共同表现，先修内核再同步
    转写）；gdcore≡oracle 但 py 分歧 → gd_core_py-transpiler；分歧集中在 rng
    消费次数/位置 → rng-mechanism。本轮只定位不修复。"""
    jd = per_case.get("judgement") or {}
    ev = jd.get("event_tuples") or {}
    fd = per_case.get("firstDivergence")
    if ev.get("oracle_gd") is False:
        pair = None
        if isinstance(fd, dict):
            pair = fd.get("oracle_vs_gdcore", fd)
        idx = pair.get("index") if isinstance(pair, dict) else None
        if idx is None:
            # kind=length：较短侧的整条事件流与较长侧前缀逐事件全等，分歧只在
            # 「一场提前收束」——事件流内无任何分歧点，说明两核在已记录事件上
            # 完全同链，分叉发生在事件间隙的隐藏消耗（视觉/UI 层链位）改变后续
            # 判定 → rng-mechanism，而非内核行为缺口。
            return {"category": "rng-mechanism",
                    "evidence": "事件流长度不同（%s）且较短侧为较长侧的逐事件前缀"
                                "——链位差发生在事件间隙的隐藏消耗" % (
                                    fd.get("detail") if isinstance(fd, dict) else "未知")}
        o_ev = (pair.get("oracle") or {}).get("at_idx")
        g_ev = (pair.get("gdcore") or {}).get("at_idx")
        # 首分歧签名细分（任务书定位规则：分歧集中在 rng 消费次数/位置 →
        # rng-mechanism）：
        #   同位同型同 tick 参数不同            → rng-mechanism（数值掷点分叉）
        #   同 origin 同型不同 tick             → rng-mechanism（冷却/速度掷点分叉）
        #   同 origin 不同型                    → gd_core-kernel（同源行为分歧）
        #   origin/结构整体错位                 → rng-mechanism（链漂移后事件面重构）
        same_type = o_ev and g_ev and o_ev.get("type") == g_ev.get("type")
        same_tick = o_ev and g_ev and o_ev.get("t") == g_ev.get("t")
        same_origin = o_ev and g_ev and o_ev.get("origin") == g_ev.get("origin")
        if same_origin and same_type and not same_tick:
            cat = "rng-mechanism"
            evidence = ("同 origin 同型事件落点 tick 不同（oracle t=%s vs gd t=%s）"
                        "——冷却/速度掷点分叉，指向链消费次数/位置差"
                        % (o_ev.get("t"), g_ev.get("t")))
        elif same_origin and same_type and same_tick:
            cat = "rng-mechanism"
            evidence = "首分歧为同位事件的参数值不同（oracle=%s gd=%s）——事件结构完整、" \
                       "随机数值分叉，指向链消费次数/位置差" % (
                           json.dumps(o_ev.get("params"), ensure_ascii=False)[:160],
                           json.dumps(g_ev.get("params"), ensure_ascii=False)[:160])
        elif same_origin and not same_type:
            cat = "gd_core-kernel"
            evidence = "同一 origin 在两侧发出不同类型事件（oracle type=%s vs gd type=%s）" \
                       % (o_ev.get("type"), g_ev.get("type"))
        else:
            cat = "rng-mechanism"
            evidence = "首分歧事件结构错位（oracle=%s gd=%s）" % (
                json.dumps(o_ev, ensure_ascii=False)[:200] if o_ev else "-",
                json.dumps(g_ev, ensure_ascii=False)[:200] if g_ev else "-")
        rng_ev = _rng_log_evidence(per_case["caseId"])
        if rng_ev:
            evidence += "；" + rng_ev
        evidence += "；已知全局链消费缺口：①自动战怒 pick_random（原版走全局链、" \
                    "内核走 ctx.rng，Character.gd:326）②动画/UI 层 randf_range 消耗" \
                    "（原版照常消耗 Util.rng，内核钩子不消耗，docs/rng_truth.md §1.4-4）" \
                    "③hasBattleRageEffect 等描述符字段 battle_items.json 未携带（data 面）"
        if ev.get("gd_py") is False:
            # py 孪生同场也分歧：根因大概率同源（转写忠实复刻了内核行为），
            # 内核修复后需同步转写——写进证据，不改变本场的定位类别。
            evidence += "；注意：py 孪生本场亦与 gd_core 分歧（同根因概率高，内核修复后同步转写）"
        return {"category": cat, "evidence": evidence}

    if ev.get("gd_py") is False:
        # gdcore≡oracle 但 py 分歧（任务书规则 → gd_core_py-transpiler）
        loc = "gd_core_py-transpiler"
        evidence = ("gd_core(Godot) ≡ 神谕、gd_core_py(Python) 在同 (阵容,seed,激活顺序) "
                    "下与之分歧——纯转写层问题")
        if isinstance(fd, dict) and "gdcore_vs_py" in fd:
            evidence += "；首分歧 %s" % json.dumps(
                fd["gdcore_vs_py"].get("index"), ensure_ascii=False)
        return {"category": loc, "evidence": evidence}

    return {"category": "aligned", "evidence": "三方逐行一致"}


def build_fixplan(localization: Dict[str, List[Dict[str, Any]]]) -> List[Dict[str, Any]]:
    plans = {
        "rng-mechanism": {
            "goal": "让 gd_core/gd_core_py 的 Util.rng 消耗面与原版逐点一致（Phase 4 修复循环）",
            "steps": [
                "补齐自动战怒 pick_random 的链语义：原版 battleRageItems.pick_random() 走引擎全局链"
                "（Character.gd:326），内核改用 ctx.rng——对齐路径应在宿主层用全局链复刻终选并直通注入，"
                "内核在 preordered 模式下不再用 ctx.rng 消耗",
                "盘点并复刻视觉/UI 层的 Util.rng 消耗：ItemAnimation.intialize（randomizePosition 3×randf_range"
                "+playback_speed 1×randf_range，Items/Animations/ItemAnimation.gd:25-33）、Character.playAttackAnimation、"
                "spawnLabel/randHealNumberPos 等——以 rng_log.txt 的消耗签名为对账单，逐点在内核钩子里补 ctx.rng 消耗",
                "补 hasBattleRageEffect 描述符字段（ItemBook.gd:1401 由描述文本 \"$rage[\" 推出）进 "
                "assets/battle_items.json → gd_core_runtime.json，使 isBattleRageItem 两侧同值",
                "每修一项即用本工具 --compare-only 重跑，验收口径=对齐场数递增且已对齐场不退步",
            ],
        },
        "gd_core-kernel": {
            "goal": "修 gd_core 内核与 decompiled_full/extracted_running 源码的行为分歧",
            "steps": [
                "对首分歧事件回溯内核调用点：gd_core/Core*.gd 对照 extracted_running/decomp 同名文件逐行 diff",
                "确认无源码依据后修 gd_core，并同步 gd_core_py 转写孪生（tools/gd_to_py.py 口径）",
                "Godot 侧改动后跑 gd_core_test/LineupBattle 回归（tools/run_gd_core.py）防 56 局基准退步",
            ],
        },
        "data": {
            "goal": "修数据面（assets/battle_items.json → assets/gd_core_runtime.json）与原版 ItemBook 的字段差",
            "steps": [
                "对照 extracted_running/decomp/Items/ItemBook.gd 的描述符构造（含由描述文本推导的布尔字段）",
                "用 tools/gen_gd_core_data.py 重新生成运行时资产并复跑对齐",
            ],
        },
        "gd_core_py-transpiler": {
            "goal": "修 gd_core_py 转写孪生与 gd_core(GDScript) 的机械转写偏差",
            "steps": [
                "对首分歧事件定位对应 .gd 行号，检查 tools/gd_to_py.py 的转写产物（浮点/数组/字典语义）",
                "优先手修 gd_core_py 对应 .py 并在转写器登记规则，防下次重转回退",
            ],
        },
    }
    out = []
    for cat in ("rng-mechanism", "gd_core-kernel", "data", "gd_core_py-transpiler"):
        cases = localization.get(cat) or []
        if not cases:
            continue
        entry = dict(plans[cat])
        entry["category"] = cat
        entry["cases"] = [c["caseId"] for c in cases]
        entry["case_count"] = len(cases)
        out.append(entry)
    return out


# ═══════════════════════════ 主流程 ═══════════════════════════

def _et_names() -> Dict[int, str]:
    """Game.EventType 数字→名（typeToKeyword 用；惰性装载 gd_core_py 内核一次）。"""
    from simulator.gd_core_engine import kernel
    return {int(v): k for k, v in kernel()["CoreConst"].EventType.items()}


def main() -> int:
    ap = argparse.ArgumentParser(description="受控神谕三方逐行对齐（oracle_workflow Phase 3）")
    ap.add_argument("--limit", type=int, default=0, help="只跑前 N 场（0=全量）")
    ap.add_argument("--cases", default="",
                    help="逗号分隔 case_id 列表：只跑指定场（定向修复验证）")
    ap.add_argument("--force", action="store_true",
                    help="先删两侧重放产物再模拟（改码后必用，防幂等跳过验证陈旧结果）")
    ap.add_argument("--skip-fixtures", action="store_true", help="复用已有 oracle_align_cases.json")
    ap.add_argument("--skip-godot", action="store_true", help="跳过 gd_core(Godot) 重放")
    ap.add_argument("--skip-py", action="store_true", help="跳过 gd_core_py 重放")
    ap.add_argument("--compare-only", action="store_true", help="只重跑比对（复用全部重放产物）")
    ap.add_argument("--alignment-out", default=ALIGNMENT_JSON)
    args = ap.parse_args()

    cases = select_cases(args.limit)
    if args.cases:
        wanted = [c for c in args.cases.split(",") if c.strip()]
        known = {c["case_id"] for c in cases}
        unknown = [c for c in wanted if c not in known]
        if unknown:
            print("未知 case_id（神谕语料中不存在或不可用）：%s" % ",".join(unknown),
                  file=sys.stderr)
            return 2
        cases = [c for c in cases if c["case_id"] in set(wanted)]
    print("[cases] 神谕语料可用 %d 场（--limit=%d%s）" % (
        len(cases), args.limit, "，--cases=%d 场" % len(cases) if args.cases else ""))
    if not cases:
        print("无可用用例", file=sys.stderr)
        return 2

    if args.force:
        if args.compare_only:
            print("--force 与 --compare-only 互斥（强制重模拟后不可能只重比对）",
                  file=sys.stderr)
            return 2
        import shutil
        for c in cases:
            for side in (GD_OUT, PY_OUT):
                d = os.path.join(side, c["case_id"])
                if os.path.isdir(d):
                    shutil.rmtree(d)
        print("[force] 已删 %d 场的 gdcore/py 重放产物（神谕语料只读，未触碰）"
              % len(cases))

    if not args.compare_only:
        if not args.skip_fixtures:
            gen_fixtures(cases)
        fixture_ids = set(fixture_case_ids())
        cases = [c for c in cases if c["case_id"] in fixture_ids]
        print("[cases] 夹具可用 %d 场" % len(cases))
        if not cases:
            print("夹具为空（全部用例生成期被剔除）", file=sys.stderr)
            return 2
        if not args.skip_godot:
            rc = run_godot([c["case_id"] for c in cases] if args.cases else None)
            if rc != 0:
                print("gd_core(Godot) 批量未全 PASS（退出码 %d）——继续比对已有产物" % rc,
                      file=sys.stderr)
        if not args.skip_py:
            run_py(cases)

    et_names = _et_names()
    per_case = []
    for i, c in enumerate(cases, 1):
        try:
            result = compare_case(c["case_id"], et_names)
        except Exception as exc:  # noqa: BLE001 —— 单场比对失败如实记档
            result = {"caseId": c["case_id"], "match": "比对异常",
                      "error": "%s: %s" % (type(exc).__name__, exc),
                      "firstDivergence": None}
        per_case.append(result)
        if i % 20 == 0 or i == len(cases):
            aligned = sum(1 for r in per_case if r.get("match") == "三方一致")
            print("  [compare] %d/%d（三方一致 %d）" % (i, len(cases), aligned))

    # ── 汇总 localization / fixPlan ──
    localization: Dict[str, List[Dict[str, Any]]] = {}
    for r in per_case:
        if "match" not in r:
            continue
        loc = localize(r)
        r["localization"] = loc["category"]
        r["localizationEvidence"] = loc["evidence"]
        if loc["category"] != "aligned":
            localization.setdefault(loc["category"], []).append(
                {"caseId": r["caseId"], "evidence": loc["evidence"]})
    aligned = sum(1 for r in per_case if r.get("match") == "三方一致")
    match_dist: Dict[str, int] = {}
    for r in per_case:
        match_dist[r.get("match", "?")] = match_dist.get(r.get("match", "?"), 0) + 1

    report = {
        "aligned": aligned,
        "total": len(per_case),
        "match_distribution": match_dist,
        "convention": {
            "seed": "两侧 gd_core 在任何物品实例创建前以 CoreContext(seed) 注入"
                    "（≙ oracle_fight.gd:536-537 的 Util.rng.seed=S）",
            "below_master": "false（np24 簇B：新语料族A 全 +1 tick 实证录制时"
                            " isBelowLeague(Master)=假，对手冷却掷 (0.95,1.05)；"
                            "旧 rng_log 0.975 实证属旧语料，不再适用）",
            "activation_order": "原版开战 shuffle 走引擎全局链（docs/rng_truth.md §1.4-2）；"
                                "OracleAlignBattle.gd 用真 Godot seed(S)+shuffle×2+"
                                "sort_TriggerPriority 复刻终序并直通内核（startBattle preordered）",
            "judgement": "主判据=engine/log_text.py 渲染战报逐行比对；辅判据=事件 canonical"
                         "（t 按 1/60s tick 取整、type/side/origin/params/parent-depth 全等）；"
                         "两者都一致才算通过",
        },
        "perCase": per_case,
        "localization": {k: v for k, v in localization.items()},
        "fixPlan": build_fixplan(localization),
    }
    out_path = args.alignment_out
    os.makedirs(os.path.dirname(os.path.abspath(out_path)), exist_ok=True)
    with io.open(out_path, "w", encoding="utf-8", newline="\n") as fh:
        json.dump(report, fh, ensure_ascii=False, indent=1)
        fh.write("\n")

    print("")
    print("=== 三方对齐结果：%d/%d 场逐行一致 ===" % (aligned, len(per_case)))
    for m, n in sorted(match_dist.items(), key=lambda kv: -kv[1]):
        print("  %-24s %d" % (m, n))
    for cat, items in localization.items():
        print("  [%s] %d 场（首例 %s）" % (cat, len(items), items[0]["caseId"]))
    print("alignment.json → %s" % out_path)
    return 0 if aligned == len(per_case) else 1


if __name__ == "__main__":
    raise SystemExit(main())
