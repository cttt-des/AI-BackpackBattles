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
import time
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

# ★ 扩样对齐（2026-11-07，docs/expand_fix_kickoff.md §6.3 Step 2）：新增
#   --fights-root / --align-root / --cases-json / --alignment-out 四参数，全局
#   在 main() 里重绑；不传参时一切取上述默认（914 基线口径，行为零回归）。
#   worker 子进程经 _root_cli_args() 收到同一组参数后走同一重绑逻辑。
_DEFAULT_FIGHTS_DIR = FIGHTS_DIR
_DEFAULT_ALIGN_DIR = ALIGN_DIR
_DEFAULT_CASES_JSON = CASES_JSON
_DEFAULT_ALIGNMENT_JSON = ALIGNMENT_JSON
#: gd 腿（Godot）的夹具/语料根覆盖（扩样模式由 main() 填充；基线模式恒空 =
#: OracleAlignBattle.gd 走自己的默认路径，逐字节同旧行为）
_GD_ENV_EXTRA: Dict[str, str] = {}


def _is_default(path: str, default: str) -> bool:
    return os.path.normcase(os.path.abspath(path)) == \
        os.path.normcase(os.path.abspath(default))
GODOT = os.path.join(ROOT, "output", "godot36", "Godot_v3.6-stable_win64.exe")

# ── ★ np21-① 宿主补偿键控表（py 腿镜像；真源 = gd_core_test/OracleAlignBattle.gd
#    文件头三表 + :481-514 注入段，逐点同步；机理与 canonical 推导证据见该处注释
#    与 output/oracle/wf_notes/np18_fix.md §3、np20 台账 round2）──
#    隔离开关：环境变量 ORACLE_ALIGN_NO_PERM_HARVEST / ORACLE_ALIGN_NO_WARM_LATCH
#    置任意非空值即关对应补偿（与 gd 宿主同名同义，单笔隔离用）。
# ★ np46 净化重录后清空（2026-11-06，与 gd 宿主 PERM_STACK_HARVEST 同步）：
#    语料=逐案隔离 harness 全量重录的干净形状（台账 §6m82），执行链收割键控面
#    退役；run702/1022 旧键已随旧语料退役。
PY_PERM_STACK_HARVEST = {}
# ★ np22（与 gd 宿主 PERM_STACK_HARVEST/OVERRIDE np22 增行镜像；值=gd 收割
#   管线全长对拍定谳的净真值向量，np21-①「py 只灌净真值表、不复刻收割管线」
#   体例）：1371=gd 暖场自然终局收割原值；1444=收割之上 Cold(110) 覆写 1
#   （exec2 终局残差 ≥1，见 gd 侧表注）。
# ★ np30（2026-11-05）：run702 blind 残差真值 1→4（与 gd 宿主 PERM_STACK_OVERRIDE
#   np30 重定谳同步；R=4 全中语料 31 笔玩家侧到期、R=3 @24.867 失配、R=1 正是
#   FD@1118 LG Blind TO -7 v -6 的直接根因）。推导与证据见 gd 宿主表注。
# ★ np37（2026-11-05）：run1022 blind 残差真值 6→1（np20 同批过期推导批量复验；
#   与 gd 宿主 PERM_STACK_OVERRIDE np37 重定谳同步——离线标定模拟器
#   sim1022v4 48/48 语料 TO 全中唯一 R=1；R=6 → ct898 Shelly -6 被 perm 全吸
#   → BB(to=ct1118) 存活 → ct1118 武装火=FD@2456）。推导与证据见 gd 宿主表注。
# ★ np46 净化重录后清空（2026-11-06，与 gd 宿主 PERM_STACK_OVERRIDE 同步）：
#    canonical 推导残留覆盖全面退役；run986/702/1022/977/1371/1444 旧键已随
#    旧语料退役（§6m84 986 已实测零键控三方一致）。
PY_PERM_STACK_OVERRIDE = {}
# ★ np43（2026-11-05）绝对钟 T0 预载键控表（py 腿镜像，真源 = gd 宿主
#   WARMUP_TIME_TICKS 同步）：机理与 run1120_r18 推导见 gd 宿主表注——语料录制
#   批 Util.time 跨场不清零，跨 dur 同刻对撞双池的 earliest 重扫严格 `<` 序由
#   录制进程 f64 累加尘埃决定（不可复现的录制工件）。K=暖场整场 tick 数
#   （[M7] chunk=1 假说：暖场=自身同 seed 整场，2553 ticks）。gd 腿 3466/3466
#   实证（T0=0 时 Banner 先=原 FD@868；K=2553 时 LG 先=语料）。引擎侧
#   simulator/gd_core_engine.py warmup_time_ticks 参数（run() 开战前逐次
#   += PHYSICS_DELTA 共 K 次，与神谕 Util.time 累加链逐位同构）。
PY_WARMUP_TIME_TICKS = {
    # ★ np46 净化重录后清空（2026-11-06，与 gd 宿主 WARMUP_TIME_TICKS 同步）：
    #    新语料每场 Util.time 归零=gd_core fresh，T0 预载键控面退役；run1120
    #    旧键 2553 已随旧语料退役。
}
# ★ np43（2026-11-05）Buff 清空 stop seen 清除键控表（py 腿镜像，真源 = gd 宿主
#   BUFF_STOP_CLEARS_SEEN 同步）：机理与 run986_r12 推导见 gd_core/CoreContext.gd
#   keyed_stop_clears_seen 注——语料 6.4833 清空 stop 后同 dur(5) start 须重同步
#   （H 池满 5s=语料 idx494@11.5333），不得走 np26W1 碰撞支（当拍 fire=FD@271）。
#   录制批注册表态不可复原，键控补偿。引擎侧 simulator/gd_core_engine.py
#   keyed_stop_clears_seen 参数（构造后置 ctx 字段）。
PY_BUFF_STOP_CLEARS_SEEN = {
    # ★ np46 净化重录后清空（2026-11-06，与 gd 宿主同步）：run986_r12 已以净化
    #    harness 重录收割（台账 §6m84，零键控三方一致）。
}
# ★ np44 清洗落池序键控表（py 腿镜像，真源 = gd 宿主 CLEANSE_BIGGEST_FIRST）：
#   机理与双场模拟器定谳见 gd_core/CoreBuff.gd loseStacks np44 注。
PY_CLEANSE_BIGGEST_FIRST = {
    # ★ np46 净化重录后清空（2026-11-06，与 gd 宿主同步）：986 残留态已随重录
    #    收割退役。
}
# ★ np22 重录后摘除 696/1371 两键（新语料=ORACLE_NOLIMIT 全长重录干净形状，
#   无闩残留；真源=gd 宿主 WARM_LATCH_PLAYERS 同步）。906/1125/1409 保留。
PY_WARM_LATCH_PLAYERS = {
    # ★ np46 净化重录后清空（2026-11-06，与 gd 宿主 WARM_LATCH_PLAYERS 同步）：
    #    gd 侧 np23 已清空、py 侧 906/1125/1409 三键系旧镜像未同步残留——本轮
    #    语料=逐案隔离 harness 全量重录（每场开战前 attackMovingForward=false），
    #    暖场闩面彻底退役。
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
PY_R5_DUAL_EXEC = {
    # ★ np46 净化重录后清空（2026-11-06）：「清空全部录制工件键控表」范围
    #    （超出 ask 点名的六表清单，依据=gd 孪生表 R5_DUAL_EXEC 自 np23 起已空、
    #    本表三键系未同步的镜像残留）。新语料=逐案隔离 harness 全量重录的干净
    #    形状（每场开战前 EventBus.disconnectAll+permanentStacks=0+闩复位，台账
    #    §6m82），双执行拓扑在录制面已不存在，嫁接只会污染 py 腿。
}
# ★ np22 重录场正式腿事件闸对位抬闸（真源 = gd_core_test/OracleAlignBattle.gd
#   NP22_REC_EV_GATE 表）：三场新语料以 ORACLE_NOLIMIT=1（事件闸 200000）
#   全长录制，py 正式腿同闸对位（引擎 formal_ev_gate 参数），否则 M12=25000
#   截断 → 伪长度分歧。其余场缺省 25000 零变化。
# ★ np24 补全（2026-10-27）：2026-10-25 全量重录时抬闸面是 **20 场**（语料
#   event_count>25000 的全集，np24 矿点实证：最大 run1362=79595），np22 期
#   只登记了当时新录的 3 场——其余 17 场 gd/py 两腿恒在 25000 截断，对
#   全长语料必伪红（20 场全在 RED 清单）。按「语料 >25000 = 录制抬闸」的
#   操作定义全量补齐（run1444 语料事件数≤25000 走标准闸，不在集中；
#   语料删除的是 run1445，勿混淆）。
PY_NP22_REC_EV_GATE = {
    # ★ np47（2026-11-07）：np46 净化重录后按 914 全量语料 event_count 再生（含 54 长场）
    "run1082_r18": 200000, "run1124_r18": 200000, "run1125_r18": 200000, "run1174_r18": 200000, "run1194_r18": 200000, "run1219_r18": 200000, "run1302_r18": 200000, "run1342_r18": 200000, "run1348_r18": 200000, "run1362_r18": 200000, "run1371_r18": 200000, "run1374_r18": 200000, "run1408_r18": 200000, "run1409_r18": 200000, "run685_r18": 200000, "run696_r18": 200000, "run845_r18": 200000, "run894_r18": 200000, "run905_r18": 200000, "run906_r18": 200000
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

def _fights_case_table() -> str:
    """用例表来源（随 --fights-root 走）：基线 root 沿用 oracle/fights.json
    （914 场用例序）；非默认 root（扩样语料）用其旁的 cases.json
    （expand_select_cases 产物，含 case_id/seed/round_id）。旁表缺失时报错退出
    ——绝不静默落回基线表（扩样 case_id 与 914 全不同，落回只会得到 0 场）。"""
    if not _is_default(FIGHTS_DIR, _DEFAULT_FIGHTS_DIR):
        sibling = os.path.join(os.path.dirname(os.path.abspath(FIGHTS_DIR)),
                               "cases.json")
        if not os.path.exists(sibling):
            raise SystemExit("[cases] 语料根 %s 旁无 cases.json 用例表"
                             "（expand_select_cases 产物）" % FIGHTS_DIR)
        return sibling
    return os.path.join(ROOT, "oracle", "fights.json")


def select_cases(limit: int) -> List[Dict[str, Any]]:
    """用例表 ∩ 神谕语料（events.json 存在且非空），保序。"""
    fights = json.load(io.open(_fights_case_table(), encoding="utf-8"))
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
        # ★ 2026-10-30 统一走 tools/godot_headless：--no-window（3.6 无 --headless，
        #   写了会走窗口路径）、**独立隐藏桌面**（否则窗口与搜狗 IME 的
        #   "OpenMem failed" 弹窗都会出现在用户屏幕上）、输出重定向到文件
        #   （沙箱禁匿名管道，capture_output 会 WinError 5）。
        import godot_headless as _gh
        cmd = _gh.cmd(project="gd_core_test", script="OracleAlignBattle.gd")
        # ★★★ 2026-11-01 修的**严重 bug**：这里过去从不下发 ORACLE_ALIGN_CASES，
        #   于是 GDScript 侧（OracleAlignBattle.gd:1149-1161）看不到定向清单，
        #   每个 gd 分片进程都按 res://oracle_align_cases.json 跑**全量**。
        #   后果实测（860 场全量刷账）：
        #     · 5 个分片各跑 860 场 = 5 倍工作量，还互相争同一批 events.json；
        #     · 墙钟 29 分钟 ≈ 单进程全量的 22.6 分钟 —— **并行度 5，收益 0**；
        #     · 多个进程并发写同一 events.json，产物有竞争风险。
        #   修法：只要本轮的 ids 是**真子集**（分片 worker 就是这种情况），就显式下发；
        #   全量单进程时不下发（省掉 ~10KB 环境变量，且保留调用方经 os.environ
        #   自行设置的能力，例如 tools/_np21_gate.py 就是这么用的）。
        extra = {"APPDATA": env["APPDATA"], "ORACLE_ALIGN_OUT": GD_OUT}
        if chunk > 0:
            extra["ORACLE_ALIGN_CHUNK"] = str(chunk)
        # ★ 扩样对齐（2026-11-07）：夹具/语料根覆盖下发给 Godot（基线模式
        #   _GD_ENV_EXTRA 恒空 = GDScript 走自身默认路径，零变化）
        extra.update(_GD_ENV_EXTRA)
        all_fixture = fixture_case_ids()
        if case_ids is not None and len(ids) < len(all_fixture):
            extra["ORACLE_ALIGN_CASES"] = ",".join(ids)
            expect = len(ids)
        else:
            expect = None
        p, log_path, _fh = _gh.spawn(cmd, label="gd_r%d" % round_i, env_extra=extra)
        _fh.close()
        last_rc = p.wait()
        # ★ 自证「分片清单真的生效了」：GDScript 侧收到定向清单会打印
        #   「★ 定向：ORACLE_ALIGN_CASES → N 场」。N 与本片场数不符 → 说明它又跑了
        #   全量（即上面的 env 下发失效），此时如实报错，绝不静默当成跑完。
        if expect is not None:
            _txt = _gh.read_log(log_path)
            _m = re.search(r"ORACLE_ALIGN_CASES\s*→\s*(\d+)\s*场", _txt)
            if _m is None or int(_m.group(1)) != expect:
                print("[godot][BUG] 本片 %d 场的定向清单没生效（日志里 %s）"
                      "——它会跑全量，已中止以免 5 倍重复劳动"
                      % (expect, "无定向行" if _m is None else "定向 %s 场" % _m.group(1)),
                      file=sys.stderr)
                return -1
        done_after = sum(1 for cid in ids
                         if _event_count(os.path.join(GD_OUT, cid, "events.json")) > 0)
        print("[godot] 第 %d 轮：退出码 %d，完成 %d/%d" % (round_i + 1, last_rc,
                                                          done_after, total))
        tail_txt = _gh.read_log(log_path)[-2000:]
        if tail_txt:
            sys.stdout.write(tail_txt)
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
    # ★ np51㉟：case 级门控表镜像（gd 宿主 gd_core_test/oracle_align_case_overrides.json
    #   同表同语义）：表内条目经 os.environ 注入（转写内核 _os_environ_get 直读），
    #   逐场 set/restore——与 OracleAlignBattle.gd run_case 开头的门控应用对位。
    case_overrides = {}
    _ovp = os.path.join(ROOT, "gd_core_test", "oracle_align_case_overrides.json")
    if os.path.exists(_ovp):
        try:
            case_overrides = json.load(io.open(_ovp, encoding="utf-8"))
        except Exception:
            case_overrides = {}
    _OV_KEYS = ("ORACLE_NO_FLKFIRE", "ORACLE_INJ_ITEM", "ORACLE_INJ_TRIGGER_N",
                "ORACLE_FLK_DELAY", "ORACLE_FLK_OFF", "ORACLE_TIMER_NO_PHASE_COMP")
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
        # 2026-11-14 修：_ov_saved 原在 try 内部定义，而 except 分支会引用它；
        # 若 load_lineup / 夹具读取在它之前抛异常，except 会变成
        # UnboundLocalError（掩盖真异常，实测卡在这里排查了两轮）。
        _ov_saved = {}          # 兜底：未走到门控快照时也能安全还原
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
            # ★ np43 T0 预载（镜像 gd 宿主 ORACLE_ALIGN_NO_T0 隔离开关）
            _no_t0 = os.environ.get("ORACLE_ALIGN_NO_T0", "") != ""
            warmup_ticks = 0
            if not _no_t0 and case_id in PY_WARMUP_TIME_TICKS:
                warmup_ticks = int(PY_WARMUP_TIME_TICKS[case_id])
            # ★ np43 Buff 清空 stop seen 清除键控（镜像 gd 宿主，共用 NO_T0 开关）
            stop_clears_seen = (not _no_t0 and case_id in PY_BUFF_STOP_CLEARS_SEEN)
            # ★ np51㉟：应用 case 门控（先清残留 → 按表设 → finally 恢复）
            _ov_saved = {k: os.environ.get(k) for k in _OV_KEYS}
            for k in _OV_KEYS:
                os.environ.pop(k, None)
            _ov = case_overrides.get(case_id) or {}
            if _ov.get("no_flkfire"):
                os.environ["ORACLE_NO_FLKFIRE"] = "1"
            if str(_ov.get("inj_item", "")) != "":
                os.environ["ORACLE_INJ_ITEM"] = str(_ov["inj_item"])
                os.environ["ORACLE_INJ_TRIGGER_N"] = str(int(_ov.get("inj_trigger_n", 1)))
            if _ov.get("flk_off"):
                os.environ["ORACLE_FLK_OFF"] = ",".join(_ov["flk_off"])
            if _ov.get("no_phase_comp"):
                os.environ["ORACLE_TIMER_NO_PHASE_COMP"] = "1"
            if _ov.get("flk_delay"):
                _pairs = []
                for k in sorted(_ov["flk_delay"]):
                    for v in str(_ov["flk_delay"][k]).split(","):
                        _pairs.append("%s=%s" % (k, v))
                os.environ["ORACLE_FLK_DELAY"] = ",".join(_pairs)
            # ★ np44 清洗落池序键控（镜像 gd 宿主，共用 NO_T0 开关）
            cleanse_biggest_first = (not _no_t0 and case_id in PY_CLEANSE_BIGGEST_FIRST)
            # ★ np51㊳：库实例发火对位（lib_fires=[t,lo,hi,…] per case）
            _lf_path = os.path.join(ROOT, "gd_core_test", "lib_fires_overrides.json")
            if os.path.exists(_lf_path):
                try:
                    _lf_all = json.load(io.open(_lf_path, encoding="utf-8"))
                    eng_kwargs_lib = _lf_all.get(case_id) or []
                except Exception:
                    eng_kwargs_lib = []
            else:
                eng_kwargs_lib = []
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
                               warmup_time_ticks=warmup_ticks,
                               keyed_stop_clears_seen=stop_clears_seen,
                               keyed_cleanse_biggest_first=cleanse_biggest_first,
                               formal_ev_gate=int(PY_NP22_REC_EV_GATE.get(case_id, 25000)),
                               # ★ 2026-11-09：体力上限直通夹具真值——gd 宿主
                               #   new_character 读 side["stamina"]/["base_max_stamina"]，
                               #   扩样夹具 stamina 取 history.db roundData（含宝物/袋
                               #   加成），而引擎 character_stats 只取 class_modifiers
                               #   base。不同源 ⇒ py 体力池偏低，长局先 OutofStamina。
                               p_stats={"stamina": fixture[case_id]["player"].get("stamina"),
                                        "health": fixture[case_id]["player"].get("health"),
                                        "regen": fixture[case_id]["player"].get("regen")},
                               o_stats={"stamina": fixture[case_id]["opponent"].get("stamina"),
                                        "health": fixture[case_id]["opponent"].get("health"),
                                        "regen": fixture[case_id]["opponent"].get("regen")},
                               # ★ np51：存档自定义规则健康倍率（镜像 gd 宿主的
                               #   ctx.custom_health_multiplier 注入；夹具层解析）
                               custom_health_multiplier=float(
                                   c.get("custom_health_multiplier", 100.0)))
            # ★ np51㊳：库实例发火对位（transpiled ctx.lib_fires）
            eng.ctx.lib_fires = [list(map(float, e)) for e in eng_kwargs_lib]
            eng.run()
        except Exception as exc:  # noqa: BLE001 —— 单场失败不拖垮批量，如实记档
            for k, v in _ov_saved.items():
                if v is None:
                    os.environ.pop(k, None)
                else:
                    os.environ[k] = v
            os.makedirs(out_dir, exist_ok=True)
            with io.open(out_path, "w", encoding="utf-8", newline="\n") as fh:
                json.dump({"case_id": case_id, "seed": c["seed"],
                           "status": "error", "error": "%s: %s" % (type(exc).__name__, exc),
                           "event_count": 0, "events": []}, fh,
                          ensure_ascii=False, indent=1)
            print("  [py][FAIL] %s：%s: %s" % (case_id, type(exc).__name__, exc))
            # ★ 2026-11-13:py 腿崩溃保留全栈——本次 §11.4 闭环排查若非此处
            #   print_exc,62 场崩因(super cell)将无从定位;一行式信息不足。
            import traceback as _tb
            _tb.print_exc()
            continue
        for k, v in _ov_saved.items():
            if v is None:
                os.environ.pop(k, None)
            else:
                os.environ[k] = v
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
            # ★ gem origin 转录（round8，2026-10-31 修订，与
            #   gd_core_test/OracleAlignBattle.gd::_j 同口径）：host.str="GemSocket2"
            #   是**占位字面**，不是真值——录制工程 socket 节点自动名分布为
            #   {GemSocket2/GemSocket/GemSocket1/GemSocket3}（2026-10-31 新语料
            #   抽样 80 场 3073 例），socket_index 恒 -1；旧「21164/21164 全为
            #   GemSocket2」系旧语料批内残留态化石，勿回信。py 内核侧真值
            #   （宿主 identifier+槽位）在 _OriginRef(ident, host_key, slot) 已
            #   动态保留，但**不可**写入 host.identifier——canonical
            #   （_origin_canon）会取 host_identifier 入元组，而语料无此字段，
            #   写入即破坏三方元组等价（("gem", None, -1)）。消费面实证：
            #   canonical 与 render_lines 双层都不消费 host.str，本字面纯属
            #   dump 层形状兼容。
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
    from simulator.log_text import render_log
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


# ── 并行比对（2026-10-29）─────────────────────────────────────────────
# 比对是**纯 CPU 的逐场独立计算**（读三份 events.json → canonical_stream →
# render_lines → first_divergence），无共享状态，故可按 case 分片并行。
# 实测 914 场：串行约 10 分钟 → 5 路 279s（LPT 分桶后各片 173MB 均衡）；
# 结果与串行**逐场一致**（perCase 顺序、match、首分歧 index 全等，
# 对照产物 output/_recovery/align_par_lpt.json）。
#
# 实现约束（照抄别改）：
#   * 沙箱禁止命名管道（ProcessPoolExecutor 建 Pipe 报 WinError 5），
#     故用**独立子进程 + 真实文件交换**，分片结果写 cmp_shards/shard_N.out.json；
#   * 分桶用 LPT（按语料 events.json 体积降序装箱），避免轮转分片把长战堆一起；
#   * 结果必须按 cases 原顺序还原——alignment.json 的 perCase 顺序是可比基线；
#   * 任一子进程失败即抛错（由 main 决定是否回退串行），绝不静默缺场。
#
# ── 并行度：默认"按当时机器资源实时决定"（2026-10-29）───────────────────
# 规则（三条同时满足才加路数，取最小）：
#   1. CPU：jobs <= max(1, cpu_count - 1)   —— 留一核给系统与主进程
#   2. 内存：jobs <= 可用内存 // PER_JOB_MEM_GB  —— 每个 worker 的峰值预算
#   3. 硬上限 PARALLEL_MAX_JOBS = 5        —— 与 gd/py 腿分片对齐，收益递减
# 任何一条探测失败都退回保守值（1），绝不因为探测异常把机器压垮。
PARALLEL_MAX_JOBS = 5
PER_JOB_MEM_GB = 1.2      # 单 worker 峰值预算：长战单场 events 解析 + 内核装载


def _avail_mem_gb() -> float:
    """当前可用物理内存（GB）。Windows 用 GlobalMemoryStatusEx，其它平台退回 8。"""
    try:
        import ctypes

        class _MEMSTATUSEX(ctypes.Structure):
            _fields_ = [("dwLength", ctypes.c_ulong),
                        ("dwMemoryLoad", ctypes.c_ulong),
                        ("ullTotalPhys", ctypes.c_ulonglong),
                        ("ullAvailPhys", ctypes.c_ulonglong),
                        ("ullTotalPageFile", ctypes.c_ulonglong),
                        ("ullAvailPageFile", ctypes.c_ulonglong),
                        ("ullTotalVirtual", ctypes.c_ulonglong),
                        ("ullAvailVirtual", ctypes.c_ulonglong),
                        ("ullAvailExtendedVirtual", ctypes.c_ulonglong)]

        st = _MEMSTATUSEX()
        st.dwLength = ctypes.sizeof(_MEMSTATUSEX)
        if not ctypes.windll.kernel32.GlobalMemoryStatusEx(ctypes.byref(st)):
            return 8.0
        return float(st.ullAvailPhys) / (1024.0 ** 3)
    except Exception:  # noqa: BLE001 —— 探测失败不影响正确性
        return 8.0


def auto_jobs(n_cases: int, requested: int = 0) -> int:
    """并行度决策：requested>0 时按请求（仍受上限约束），0=按机器资源自动。"""
    if n_cases <= 0:
        return 1
    cap = PARALLEL_MAX_JOBS
    if requested and requested > 0:
        return max(1, min(int(requested), cap, n_cases))
    cpu = os.cpu_count() or 1
    by_cpu = max(1, cpu - 1)
    mem = _avail_mem_gb()
    by_mem = max(1, int(mem // PER_JOB_MEM_GB))
    return max(1, min(cap, by_cpu, by_mem, n_cases))


def _shard_by_weight(case_ids: List[str], jobs: int) -> Tuple[List[List[str]], List[int]]:
    """LPT 分桶：按语料 events.json 体积降序投放给当前最轻的桶。

    长战（run906_r18 25026 事件 / 8MB）若与别的场挤在同一片，该片决定总时长；
    LPT 让各片负载近似相等（实测 914 场 5 片各 173MB，同时收尾）。
    """
    weight = {}
    for cid in case_ids:
        try:
            weight[cid] = os.path.getsize(os.path.join(FIGHTS_DIR, cid, "events.json"))
        except OSError:
            weight[cid] = 1
    buckets: List[List[str]] = [[] for _ in range(jobs)]
    load = [0] * jobs
    for cid in sorted(case_ids, key=lambda c: -weight[c]):
        k = load.index(min(load))
        buckets[k].append(cid)
        load[k] += weight[cid]
    return buckets, load


def _worker_env(idx: int) -> Dict[str, str]:
    """并行 worker 的环境：按分片号隔离 APPDATA。

    每个 worker 是独立 python 进程（自身 PID 不同），但 run_godot 内部按
    os.getpid() 再派生一层，仍有重叠风险；这里显式给 ORACLE_ALIGN_APPDATA，
    run_godot 会优先采用它，保证同一时刻多个 Godot 不共 user://。
    """
    env = dict(os.environ)
    env["ORACLE_ALIGN_APPDATA"] = os.path.join(
        ROOT, "output", "_recovery", "appdata_p", "shard_%d_%d" % (os.getpid(), idx))
    os.makedirs(env["ORACLE_ALIGN_APPDATA"], exist_ok=True)
    return env


def _root_cli_args() -> List[str]:
    """把当前（可能被四参数重绑过的）root 全局下发给 worker 子进程。

    worker 走同一 argparse 入口，收到参数后在 main() 里走同一重绑逻辑——
    分片 worker 与主进程的语料/夹具/产物口径强一致。只在与默认值不同时下发，
    基线路径的子进程命令行保持原样。"""
    args: List[str] = []
    if not _is_default(FIGHTS_DIR, _DEFAULT_FIGHTS_DIR):
        args += ["--fights-root", FIGHTS_DIR]
    if not _is_default(ALIGN_DIR, _DEFAULT_ALIGN_DIR):
        args += ["--align-root", ALIGN_DIR]
    if not _is_default(CASES_JSON, _DEFAULT_CASES_JSON):
        args += ["--cases-json", CASES_JSON]
    if not _is_default(ALIGNMENT_JSON, _DEFAULT_ALIGNMENT_JSON):
        args += ["--alignment-out", ALIGNMENT_JSON]
    return args


def _spawn_workers(subcmd: str, buckets: List[List[str]], tmpdir: str,
                   log_prefix: str) -> List[Tuple[int, int, Any]]:
    """起若干子进程（一桶一进程），返回 [(序号, 场数, Popen)]。

    subcmd: 传给本文件的子命令（--gd-worker/--py-worker），每桶一个清单文件。
    """
    os.makedirs(tmpdir, exist_ok=True)
    procs = []
    for i, shard in enumerate(buckets):
        if not shard:
            continue
        lst = os.path.join(tmpdir, "%s_%d.in.json" % (log_prefix, i))
        with io.open(lst, "w", encoding="utf-8") as fh:
            json.dump(shard, fh)
        log = open(os.path.join(tmpdir, "%s_%d.log" % (log_prefix, i)), "wb")
        # ★ 走 gh.py_popen 而非裸 Popen：worker 自己也要落在**隐藏桌面**上。
        #   否则搜狗 IME 注入 worker 后，它弹的框就出现在用户屏幕上（2026-11-02 定位）。
        import godot_headless as _gh2
        procs.append((i, len(shard), _gh2.py_popen(
            [sys.executable, "-X", "utf8", os.path.abspath(__file__), subcmd, lst]
            + _root_cli_args(),
            cwd=ROOT, stdout=log, stderr=subprocess.STDOUT, env=_worker_env(i))))
    return procs


def gd_worker_main(list_path: str) -> int:
    """gd 腿子进程：跑一个分片（chunk=0，避免每 120 场再重启 Godot）。"""
    with io.open(list_path, encoding="utf-8") as fh:
        case_ids = json.load(fh)
    return run_godot(case_ids=case_ids, chunk=0)


def py_worker_main(list_path: str) -> int:
    """py 腿子进程：跑一个分片（run_py 自身幂等跳过已有产物）。"""
    with io.open(list_path, encoding="utf-8") as fh:
        want = json.load(fh)
    fixture = {c["case_id"]: c for c in
               json.load(io.open(CASES_JSON, encoding="utf-8"))["cases"]}
    cases = [fixture[c] for c in want if c in fixture]
    return run_py(cases)


def run_godot_parallel(case_ids: List[str], jobs: int) -> int:
    """gd 腿并行：按 LPT 分片、每片一个子进程；返回首个非零 rc（0=全成功）。"""
    jobs = auto_jobs(len(case_ids), jobs)
    if jobs <= 1:
        print("[godot] 串行（jobs=1）")
        return run_godot(case_ids=case_ids, chunk=0)
    buckets, load = _shard_by_weight(case_ids, jobs)
    print("[godot] 并行 %d 路，分桶负载（MB）：%s" % (
        jobs, ", ".join("%.1f" % (x / 1048576.0) for x in load)))
    tmpdir = os.path.join(ALIGN_DIR, "_gd_shards")
    t0 = time.time()
    procs = _spawn_workers("--gd-worker", buckets, tmpdir, "gd")
    rc_all = 0
    for i, n, proc in procs:
        rc = proc.wait()
        print("[godot] 分片 %d 完成：%d 场 rc=%s（累计 %.0fs）" % (i, n, rc, time.time() - t0))
        if rc and not rc_all:
            rc_all = rc
    return rc_all


def run_py_parallel(cases: List[Dict[str, Any]], jobs: int) -> int:
    """py 腿并行：按 LPT 分片、每片一个子进程。"""
    case_ids = [c["case_id"] for c in cases]
    jobs = auto_jobs(len(case_ids), jobs)
    if jobs <= 1:
        print("[py] 串行（jobs=1）")
        return run_py(cases)
    buckets, load = _shard_by_weight(case_ids, jobs)
    print("[py] 并行 %d 路，分桶负载（MB）：%s" % (
        jobs, ", ".join("%.1f" % (x / 1048576.0) for x in load)))
    tmpdir = os.path.join(ALIGN_DIR, "_py_shards")
    t0 = time.time()
    procs = _spawn_workers("--py-worker", buckets, tmpdir, "py")
    rc_all = 0
    for i, n, proc in procs:
        rc = proc.wait()
        print("[py] 分片 %d 完成：%d 场 rc=%s（累计 %.0fs）" % (i, n, rc, time.time() - t0))
        if rc and not rc_all:
            rc_all = rc
    return rc_all


def _split_leg_budget(n_cases: int, gd_jobs: int, py_jobs: int) -> Tuple[int, int]:
    """把**总**并行预算分给 gd / py 两条腿（2026-11-01 修）。

    ★ 修的是什么 bug：过去两腿各叫一次 auto_jobs()，各自都能拿到 5，于是
      **同时在跑的 worker 上限是 5+5=10**，而不是文档说的 PARALLEL_MAX_JOBS=5。
      实测（30 场样本）峰值 **27 个 python + 5 个 Godot**，机器明显卡顿。
      更糟的是 py 那一侧还是**只起不收**（见下面的滚动池修复），最多堆到 25 个。

    ★ 现在的口径：
      · 用户**显式**给了 --gd-jobs / --py-jobs → 按用户给的值（不截断、不改写），
        但另一条腿若没给，就从"总预算 - 已给"里分，避免叠加超限；
      · 都没给（自动）→ 总预算 = auto_jobs(n)，按 6:4 分给 gd / py
        （gd 腿跑真 Godot 更重，给它多一点），两项都至少 1。
    """
    total = auto_jobs(n_cases, 0)
    gd_req = int(gd_jobs or 0)
    py_req = int(py_jobs or 0)
    if gd_req > 0 and py_req > 0:
        # 两个都显式：尊重用户，只提示可能的过载
        if gd_req + py_req > total:
            print("[legs][提示] 显式要求 gd %d 路 + py %d 路 = %d 路，超出自适应预算 %d；"
                  "按显式值执行，机器可能吃紧" % (gd_req, py_req, gd_req + py_req, total),
                  file=sys.stderr)
        return min(gd_req, PARALLEL_MAX_JOBS), min(py_req, PARALLEL_MAX_JOBS)
    if gd_req > 0:
        gd_n = min(gd_req, PARALLEL_MAX_JOBS)
        return gd_n, max(1, min(total - gd_n, PARALLEL_MAX_JOBS))
    if py_req > 0:
        py_n = min(py_req, PARALLEL_MAX_JOBS)
        return max(1, min(total - py_n, PARALLEL_MAX_JOBS)), py_n
    gd_n = max(1, min(PARALLEL_MAX_JOBS, int(round(total * 0.6))))
    py_n = max(1, min(PARALLEL_MAX_JOBS, total - gd_n))
    return gd_n, py_n


def _run_both_legs(cases: List[Dict[str, Any]], gd_jobs: int, py_jobs: int,
                   skip_godot: bool = False, skip_py: bool = False) -> None:
    """gd 腿（Godot 子进程）与 py 腿（纯 Python）**重叠执行**（2026-10-30）。

    为什么能重叠：两腿读同一份 case 清单，但产物写各自目录（GD_OUT / PY_OUT），
    中间不交换任何数据；唯一的交汇点是之后的 compare，它必须等两腿都完。
    串行时总耗时 = gd + py，重叠后 = max(gd, py)。

    并行度预算：两腿同时跑会争 CPU，故默认把总预算 PARALLEL_MAX_JOBS 平分成
    两半（各至少 1）；用户显式 --gd-jobs/--py-jobs 时按显式值，不被截断。

    失败语义不变：某腿非零不中断另一腿，只打警告（比对阶段会用已有产物给出
    "缺产物"结论，绝不静默当作一致）。
    """
    if skip_godot and skip_py:
        return
    if skip_godot or skip_py:
        # 只有一腿 → 没什么可重叠的，按原样串行
        if not skip_godot:
            rc = run_godot_parallel([c["case_id"] for c in cases], gd_jobs)
            if rc != 0:
                print("gd_core(Godot) 批量未全 PASS（退出码 %d）——继续比对已有产物" % rc,
                      file=sys.stderr)
        if not skip_py:
            run_py_parallel(cases, py_jobs)
        return

    case_ids = [c["case_id"] for c in cases]
    gd_n, py_n = _split_leg_budget(len(case_ids), gd_jobs, py_jobs)
    if gd_n <= 1 and py_n <= 1:
        _run_legs_serial(case_ids, cases, gd_jobs, py_jobs)
        return

    # ── 流水线重叠 ─────────────────────────────────────────────────────
    # gd 腿必须**先**产出：py 腿读 gd 的 events.json 取 activation_order
    # （verify_oracle.py:318-322，激活顺序来源），没产物就 skip。所以两腿
    # 不能整段重叠，只能**按分片流水**：gd 的第 N 片一完成，立刻让 py 接手这
    # 一片，gd 后面的片继续跑。实测总耗时 = 首批 py 等待 + 后续交错。
    gd_buckets, gd_load = _shard_by_weight(case_ids, gd_n)
    print("[legs] 流水线：gd %d 路交错，py 分片批跟随（py 最多 %d 路/批）"
          % (gd_n, py_n))
    print("[legs] gd 分桶负载（MB）：%s"
          % ", ".join("%.1f" % (x / 1048576.0) for x in gd_load))
    t0 = time.time()
    tmpdir = os.path.join(ALIGN_DIR, "_gd_shards")
    gd_procs = _spawn_workers("--gd-worker", gd_buckets, tmpdir, "gdpipe")
    lstdir = os.path.join(ALIGN_DIR, "_py_shards")
    os.makedirs(lstdir, exist_ok=True)

    # ★ 滚动池（2026-11-01 修）：过去 py 进程是「只起不收」——每个 gd 分片完成就把
    #   min(py_n, 片场数) 个 py 进程 append 进列表，直到最后才统一 wait()。
    #   gd 5 片 × py 5 路 = 最多 25 个 py 进程同时活着，实测峰值 27 python + 5 godot。
    #   现在改成真正的池：在途数恒 <= py_n，完成一个立刻补下一个。
    pending_py: List[Tuple[str, List[str]]] = []   # [(tag, 该片的 case 清单)]
    pid = 0
    rc_all = 0
    py_done = 0
    py_fail = 0

    def _py_launch(tag, part):
        lst = os.path.join(lstdir, "pypipe_%s.in.json" % tag)
        with io.open(lst, "w", encoding="utf-8") as fh:
            json.dump(part, fh)
        log = open(os.path.join(lstdir, "pypipe_%s.log" % tag), "wb")
        import godot_headless as _gh2
        proc = _gh2.py_popen(
            [sys.executable, "-X", "utf8", os.path.abspath(__file__),
             "--py-worker", lst] + _root_cli_args(),
            cwd=ROOT, stdout=log, stderr=subprocess.STDOUT,
            env=_worker_env(100 + int(tag.split("_")[-1])))
        return (tag, len(part), proc, log)

    running_py = []

    def _py_reap(block=False):
        nonlocal py_done, py_fail
        while running_py:
            tag, n, proc, log = running_py[0]
            if not block and proc.poll() is None:
                return
            prc = proc.wait()
            try:
                log.close()
            except OSError:
                pass
            running_py.pop(0)
            py_done += 1
            if prc:
                py_fail += 1
            print("[legs] py 片 %s 完成（%d 场 rc=%s，累计 %.0fs）"
                  % (tag, n, prc, time.time() - t0))
            if not block:
                return

    for i, n, proc in gd_procs:
        rc = proc.wait()
        if rc and not rc_all:
            rc_all = rc
        print("[legs] gd 片 %d 完成（%d 场 rc=%s，累计 %.0fs）——py 接手该片"
              % (i, n, rc, time.time() - t0))
        shard = gd_buckets[i]
        # 该片的 py 按 py_n 再切一刀，避免单进程串跑长尾
        sub = max(1, min(py_n, len(shard)))
        for k, part in enumerate(shard[j::sub] for j in range(sub)):
            if not part:
                continue
            pending_py.append(("%d_%d" % (i, k), part))
        # 立刻尽量把池填满；满了就先回收一个再补
        while pending_py:
            while pending_py and len(running_py) < py_n:
                tag, part = pending_py.pop(0)
                running_py.append(_py_launch(tag, part))
                pid += 1
            if pending_py:
                _py_reap(block=True)
    # gd 全部完成后，把剩余 py 跑完
    while running_py:
        _py_reap(block=True)
    print("[legs] py 共 %d 片完成（失败 %d）" % (py_done, py_fail))
    print("[legs] 流水线完成，总墙钟 %.0fs" % (time.time() - t0))
    if rc_all:
        print("gd_core(Godot) 批量未全 PASS（退出码 %s）——继续比对已有产物" % (rc_all,),
              file=sys.stderr)


def _run_legs_serial(case_ids: List[str], cases: List[Dict[str, Any]],
                     gd_jobs: int, py_jobs: int) -> None:
    """一腿一路时的退化路径：gd 跑完再 py。"""
    rc = run_godot_parallel(case_ids, gd_jobs)
    if rc != 0:
        print("gd_core(Godot) 批量未全 PASS（退出码 %d）——继续比对已有产物" % rc,
              file=sys.stderr)
    run_py_parallel(cases, py_jobs)


COMPARE_MAX_JOBS = 5


def _compare_worker_main(list_path: str, out_path: str) -> int:
    """子进程入口：读 case 清单 → 逐场比对 → 写 {case_id: result}。"""
    with io.open(list_path, encoding="utf-8") as fh:
        case_ids = json.load(fh)
    et = _et_names()
    out: Dict[str, Any] = {}
    for cid in case_ids:
        try:
            out[cid] = compare_case(cid, et)
        except Exception as exc:  # noqa: BLE001 —— 与串行口径完全一致
            out[cid] = {"caseId": cid, "match": "比对异常",
                        "error": "%s: %s" % (type(exc).__name__, exc),
                        "firstDivergence": None}
    tmp = out_path + ".tmp"
    with io.open(tmp, "w", encoding="utf-8") as fh:
        json.dump(out, fh, ensure_ascii=False)
    os.replace(tmp, out_path)
    return 0


def compare_cases(cases: List[Dict[str, Any]], et_names: Dict[int, str],
                  jobs: int = COMPARE_MAX_JOBS) -> List[Dict[str, Any]]:
    """逐场比对；jobs>1 时用子进程分片并行（保序），否则单进程。"""
    order = [c["case_id"] for c in cases]
    jobs = auto_jobs(len(order), jobs)
    if jobs <= 1:
        per_case = []
        for i, cid in enumerate(order, 1):
            try:
                result = compare_case(cid, et_names)
            except Exception as exc:  # noqa: BLE001
                result = {"caseId": cid, "match": "比对异常",
                          "error": "%s: %s" % (type(exc).__name__, exc),
                          "firstDivergence": None}
            per_case.append(result)
            if i % 20 == 0 or i == len(order):
                aligned = sum(1 for r in per_case if r.get("match") == "三方一致")
                print("  [compare] %d/%d（三方一致 %d）" % (i, len(order), aligned))
        return per_case

    t0 = time.time()
    buckets, load = _shard_by_weight(order, jobs)
    print("  [compare] 并行 %d 路，分桶负载（MB）：%s" % (
        jobs, ", ".join("%.1f" % (x / 1048576.0) for x in load)))

    tmpdir = os.path.join(ALIGN_DIR, "_cmp_shards")
    os.makedirs(tmpdir, exist_ok=True)
    procs = []
    for i, shard in enumerate(buckets):
        if not shard:
            continue
        lst = os.path.join(tmpdir, "shard_%d.in.json" % i)
        out = os.path.join(tmpdir, "shard_%d.out.json" % i)
        with io.open(lst, "w", encoding="utf-8") as fh:
            json.dump(shard, fh)
        if os.path.exists(out):
            os.remove(out)
        import godot_headless as _gh2
        procs.append((i, len(shard), out, _gh2.py_popen(
            [sys.executable, "-X", "utf8", os.path.abspath(__file__),
             "--compare-worker", lst, out] + _root_cli_args(),
            cwd=ROOT, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)))

    out_by_id: Dict[str, Dict[str, Any]] = {}
    for i, n, out, proc in procs:
        rc = proc.wait()
        if rc != 0 or not os.path.exists(out):
            raise RuntimeError("compare 分片 %d 失败（rc=%s，%d 场）" % (i, rc, n))
        with io.open(out, encoding="utf-8") as fh:
            out_by_id.update(json.load(fh))
        print("  [compare] 分片 %d 完成（%d 场，累计 %.1fs）" % (i, n, time.time() - t0))
    missing = [c for c in order if c not in out_by_id]
    if missing:
        raise RuntimeError("并行比对缺 %d 场（首例 %s）" % (len(missing), missing[0]))
    aligned = sum(1 for c in order if out_by_id[c].get("match") == "三方一致")
    print("  [compare] %d/%d（三方一致 %d，%.1fs）" % (
        len(order), len(order), aligned, time.time() - t0))
    return [out_by_id[cid] for cid in order]


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
    ap.add_argument("--gd-jobs", type=int, default=0,
                    help="gd_core(Godot) 重放并发数（0=按机器资源自动，上限 %d）"
                         % PARALLEL_MAX_JOBS)
    ap.add_argument("--py-jobs", type=int, default=0,
                    help="gd_core_py 重放并发数（0=按机器资源自动，上限 %d）"
                         % PARALLEL_MAX_JOBS)
    ap.add_argument("--compare-jobs", type=int, default=0,
                    help="比对并发数（0=按机器资源自动，上限 %d；1=串行）"
                         % PARALLEL_MAX_JOBS)
    ap.add_argument("--alignment-out", default="",
                    help="对齐账本输出（默认 output/oracle/alignment.json；"
                         "扩样传 output/oracle/expand/alignment_expand.json）")
    # ★ 扩样对齐（2026-11-07，kickoff §6.3 Step 2）：四个 root 参数，默认值 =
    #   模块常量（914 基线口径），不传参零回归。重绑逻辑见下方"四参数重绑"。
    ap.add_argument("--fights-root", default="",
                    help="神谕语料根（默认 output/oracle/fights；扩样传 "
                         "output/oracle/expand/fights）")
    ap.add_argument("--align-root", default="",
                    help="三方重放产物根（默认 output/oracle/align；扩样传 "
                         "output/oracle/align_expand）")
    ap.add_argument("--cases-json", default="",
                    help="用例夹具（默认 gd_core_test/oracle_align_cases.json；"
                         "扩样传 gd_core_test/expand_align_cases.json）")
    # 内部子进程入口（并行分片 worker），不要手工调用
    ap.add_argument("--compare-worker", nargs=2, default=None,
                    metavar=("LIST_JSON", "OUT_JSON"), help=argparse.SUPPRESS)
    ap.add_argument("--gd-worker", default=None, metavar="LIST_JSON",
                    help=argparse.SUPPRESS)
    ap.add_argument("--py-worker", default=None, metavar="LIST_JSON",
                    help=argparse.SUPPRESS)
    args = ap.parse_args()

    # ── ★ 四参数重绑全局（必须在 worker 分发之前：worker 子进程同样经此处
    #    重绑后才有正确口径；基线模式四值全空 ⇒ 全局不动 ⇒ 逐字节旧行为）──
    global FIGHTS_DIR, ALIGN_DIR, GD_OUT, PY_OUT, RENDER_DIR, LINEUP_OUT, \
        CASES_JSON, ALIGNMENT_JSON
    if args.fights_root:
        FIGHTS_DIR = os.path.abspath(args.fights_root)
    if args.align_root:
        ALIGN_DIR = os.path.abspath(args.align_root)
    elif args.fights_root:
        # 只给 --fights-root 时防污染基线：产物根自动落到语料旁 align_expand
        ALIGN_DIR = os.path.join(os.path.dirname(FIGHTS_DIR), "align_expand")
        print("[align-root] 未指定，自动落 %s（防写入 914 基线 align/）" % ALIGN_DIR)
    if args.fights_root or args.align_root:
        GD_OUT = os.path.join(ALIGN_DIR, "gdcore")
        PY_OUT = os.path.join(ALIGN_DIR, "py")
        RENDER_DIR = os.path.join(ALIGN_DIR, "render")
        LINEUP_OUT = os.path.join(ALIGN_DIR, "lineups")
        # ★ np51㊳终⑰（2026-11-09）：账本路径与产物根同规则重定向——此前只有
        #   产物根自动落 align_expand，账本仍写全局默认 output/oracle/alignment.json，
        #   扩样跑批会把基线账本整本覆盖成扩样结果（1690 覆盖 914 账），而
        #   alignment_expand.json 停在旧状态——读账人看到「严重回退/红场复现」。
        #   现规则：扩样模式（给了 --fights-root/--cases-json 且未显式给
        #   --alignment-out）⇒ 账本自动落 <ALIGN_DIR>/alignment_expand.json；
        #   显式 --alignment-out 永远优先；基线模式四值全空 ⇒ 逐字节旧行为。
        if args.alignment_out:
            print("[alignment-out] 显式指定 %s" % ALIGNMENT_JSON)
        else:
            ALIGNMENT_JSON = os.path.join(ALIGN_DIR, "alignment_expand.json")
            print("[alignment-out] 未指定，随产物根自动落 %s（防覆盖基线账本）"
                  % ALIGNMENT_JSON)
    if args.cases_json:
        CASES_JSON = os.path.abspath(args.cases_json)
    if args.alignment_out:
        ALIGNMENT_JSON = os.path.abspath(args.alignment_out)
    if not _is_default(FIGHTS_DIR, _DEFAULT_FIGHTS_DIR) or \
            not _is_default(CASES_JSON, _DEFAULT_CASES_JSON):
        _GD_ENV_EXTRA["ORACLE_ALIGN_FIGHTS_ROOT"] = FIGHTS_DIR.replace("\\", "/")
        _GD_ENV_EXTRA["ORACLE_ALIGN_CASES_JSON"] = CASES_JSON.replace("\\", "/")

    if args.compare_worker:
        return _compare_worker_main(*args.compare_worker)
    if args.gd_worker:
        return gd_worker_main(args.gd_worker)
    if args.py_worker:
        return py_worker_main(args.py_worker)

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
        _run_both_legs(cases, args.gd_jobs, args.py_jobs,
                       skip_godot=args.skip_godot, skip_py=args.skip_py)
    else:
        # ★ 口径修正（2026-11-01）：--compare-only 过去**不做夹具过滤**，于是全量
        #   比对报的是语料场数（914），而主流程报的是夹具场数（860）——同一个
        #   alignment.json 在两条路径下 total 不一样，读报告的人会以为基线漂了。
        #   这里补上过滤（夹具文件缺失时退回全集，且如实提示）。
        try:
            fixture_ids = set(fixture_case_ids())
        except Exception:  # noqa: BLE001 —— 夹具不在就别硬套口径
            fixture_ids = set()
        if fixture_ids:
            before = len(cases)
            cases = [c for c in cases if c["case_id"] in fixture_ids]
            print("[cases] --compare-only：按夹具口径 %d/%d 场（与主流程一致）"
                  % (len(cases), before))
            if not cases:
                print("夹具为空（全部用例生成期被剔除）", file=sys.stderr)
                return 2

    et_names = _et_names()
    per_case = compare_cases(cases, et_names, args.compare_jobs)

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
    out_path = ALIGNMENT_JSON  # 四参数重绑后的全局（默认值或 --alignment-out）
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
