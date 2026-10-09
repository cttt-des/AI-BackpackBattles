#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
verify_oracle_s2.py — 阶段2：装配期（物品实例创建期）rng 消耗对齐后的
**同 seed 无 state 注入**三方逐行对齐（docs/alignment_fix_workflow.md §2 阶段2）

与 verify_oracle_s1.py（阶段1 注入）的本质差异：
  阶段1 用神谕导出的 Util.rng.state（rng_state.txt）在 startBattle 前 set_state
  直灌，绕开装配期消耗差异以隔离战斗期。阶段2 的判定本体是**不再注入**：
  两侧 gd_core 从 seed(S) 起跑完整链——装配期消耗面（物品/宝石场景双绑定
  2×BalancedRng=4 步/实例、FlickerAnimation 入树 +2 步、对手 Character 4×
  BalancedRng=8 步）已逻辑一致还原进内核（gd_core/CoreItem.gd setup/_readyInit；
  数据层 tools/enrich_flicker_animation.py；实证 oracle/oracle_stage_probe.gd +
  output/_probe_assembly_steps.py，917 场装配步数模型零残差）——
  同 seed 下不注入 state 也逐行一致 = 装配顺序/初始化次数/消耗位置全面一致。

抽样：从阶段1 语料可用场（events 非空 ∩ 夹具内）**随机抽 20 场**
（--sample-seed 固定抽样种子，默认 20261007，样本清单随报告落档可复现）。

判据（与 verify_oracle_s1.py 同口径）：
  主：engine/log_text.py 渲染战报逐行比对；
  辅：事件 canonical（t 按 1/60s tick 取整、type/side/origin/params/parent-depth 全等）。

用法：
  python -X utf8 tools/verify_oracle_s2.py                       # 抽 20 场全流程
  python -X utf8 tools/verify_oracle_s2.py --sample-seed 42      # 换样本
  python -X utf8 tools/verify_oracle_s2.py --cases a,b,c         # 定向
  python -X utf8 tools/verify_oracle_s2.py --compare-only        # 只重跑比对
输出：
  output/oracle/alignment_s2.json {threeWayAligned, total, perCase, sample…}
  output/oracle/align/render_s2/<case>.{oracle,gdcore,py}.logtext（留档）
"""
from __future__ import annotations

import argparse
import io
import json
import os
import random
import sys
from typing import Any, Dict, List

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)
sys.path.insert(0, os.path.join(ROOT, "tools"))

import verify_oracle as vo  # noqa: E402  — 复用 canonical/渲染/首分歧/Godot 批量机器

ALIGN_DIR = vo.ALIGN_DIR
GD_OUT = os.path.join(ALIGN_DIR, "gdcore_s2")
PY_OUT = os.path.join(ALIGN_DIR, "py_s2")
RENDER_DIR = os.path.join(ALIGN_DIR, "render_s2")
LINEUP_OUT = vo.LINEUP_OUT
CASES_JSON = vo.CASES_JSON
ALIGNMENT_JSON = os.path.join(ROOT, "output", "oracle", "alignment_s2.json")


def select_cases_s2(sample_seed: int, sample_size: int,
                    only: List[str]) -> List[Dict[str, Any]]:
    """阶段1 语料可用场（events 非空 ∩ 夹具内）→ 随机样本（可复现）。"""
    fights = json.load(io.open(os.path.join(ROOT, "oracle", "fights.json"),
                               encoding="utf-8"))
    fixture = set(vo.fixture_case_ids())
    eligible = []
    for c in fights["cases"]:
        cid = c["case_id"]
        if cid not in fixture:
            continue
        if vo._event_count(os.path.join(vo.FIGHTS_DIR, cid, "events.json")) <= 0:
            continue
        eligible.append({"case_id": cid, "seed": int(c["seed"]),
                         "round_id": int(c["round_id"])})
    if only:
        keep = [c for c in eligible if c["case_id"] in only]
        return keep
    rng = random.Random(sample_seed)
    return rng.sample(eligible, min(sample_size, len(eligible)))


# ═══════════════════════════ gd_core(Godot) 侧 ═══════════════════════════

def run_godot_s2(cases: List[Dict[str, Any]], chunk: int = 40,
                 max_rounds: int = 40) -> int:
    """分块跑**无注入**版 gd_core(Godot) 批量（ORACLE_ALIGN_NO_INJECT=1）。"""
    if not os.path.exists(vo.GODOT):
        print("找不到 Godot：%s" % vo.GODOT, file=sys.stderr)
        return 2
    vo.GD_OUT = GD_OUT
    os.environ["ORACLE_ALIGN_OUT"] = GD_OUT
    os.environ["ORACLE_ALIGN_NO_INJECT"] = "1"
    if cases:
        os.environ["ORACLE_ALIGN_CASES"] = ",".join(c["case_id"] for c in cases)
    else:
        os.environ.pop("ORACLE_ALIGN_CASES", None)
    total = len(cases)
    last_rc = 0
    for round_i in range(max_rounds):
        done_before = sum(1 for c in cases
                          if vo._event_count(os.path.join(GD_OUT, c["case_id"],
                                                          "events.json")) > 0)
        if done_before >= total:
            print("[godot-s2] 全部 %d 场已完成" % total)
            return 0
        cmd = [vo.GODOT, "--headless", "--path",
               os.path.join(ROOT, "gd_core_test"),
               "--script", "OracleAlignBattle.gd"]
        import subprocess
        proc = subprocess.run(cmd, capture_output=True, text=True,
                              encoding="utf-8", errors="replace", cwd=ROOT)
        last_rc = proc.returncode
        done_after = sum(1 for c in cases
                         if vo._event_count(os.path.join(GD_OUT, c["case_id"],
                                                         "events.json")) > 0)
        print("[godot-s2] 第 %d 轮：退出码 %d，完成 %d/%d" % (round_i + 1, last_rc,
                                                            done_after, total))
        if proc.stdout:
            sys.stdout.write(proc.stdout[-1200:])
        if proc.stderr:
            sys.stderr.write(proc.stderr[-800:])
        if done_after >= total:
            return 0
        if done_after <= done_before:
            print("[godot-s2] 本轮无进展（%d/%d）——确定性卡死，停止重试"
                  % (done_after, total), file=sys.stderr)
            return last_rc or 1
    return last_rc or 1


# ═══════════════════════════ gd_core_py(Python) 侧 ═══════════════════════════

def run_py_s2(cases: List[Dict[str, Any]]) -> int:
    """批量驱动：与阶段1 同一装配 kwargs，但**不传 rng_state**，且
    reseed_after_player_character=True（神谕约定：PLAYER 构造消耗在播种前被
    seed 抹除）、post_seed_draws=0（旧校准常数已删，装配期消耗已进内核逻辑）。"""
    from simulator.data import load_items, load_characters
    from simulator.lineup import load_lineup
    from simulator.gd_core_engine import GDCoreEngine, kernel

    item_db = load_items()
    character_db = load_characters()
    et_names = {int(v): k for k, v in kernel()["CoreConst"].EventType.items()}

    fixture = {c["case_id"]: c for c in
               json.load(io.open(CASES_JSON, encoding="utf-8"))["cases"]}
    os.makedirs(PY_OUT, exist_ok=True)

    ok = 0
    for i, c in enumerate(cases, 1):
        case_id = c["case_id"]
        out_dir = os.path.join(PY_OUT, case_id)
        out_path = os.path.join(out_dir, "events.json")
        if os.path.exists(out_path) and vo._event_count(out_path) > 0:
            ok += 1
            continue
        if case_id not in fixture:
            print("  [py][skip] %s 不在夹具内" % case_id)
            continue
        gd_path = os.path.join(GD_OUT, case_id, "events.json")
        if not os.path.exists(gd_path) or vo._event_count(gd_path) <= 0:
            print("  [py][skip] %s 缺 gd_core_s2 侧产物（激活顺序来源）" % case_id)
            continue
        order = json.load(io.open(gd_path, encoding="utf-8"))["activation_order"]
        try:
            player = load_lineup(os.path.join(LINEUP_OUT,
                                              "oracle_%s_player.json" % case_id))
            opponent = load_lineup(os.path.join(LINEUP_OUT,
                                                "oracle_%s_opponent.json" % case_id))
            eng = GDCoreEngine(player, opponent, item_db, character_db,
                               seed=c["seed"], max_time=90.0,
                               probe_bases=(vo._FightEndGate,),
                               below_master=True,
                               p_activation_order=[int(x) for x in order["player"]],
                               o_activation_order=[int(x) for x in order["opponent"]],
                               reseed_after_player_character=True,
                               post_seed_draws=0)
            eng.run()
        except Exception as exc:  # noqa: BLE001 —— 单场失败不拖垮批量，如实记档
            os.makedirs(out_dir, exist_ok=True)
            with io.open(out_path, "w", encoding="utf-8", newline="\n") as fh:
                json.dump({"case_id": case_id, "seed": c["seed"],
                           "status": "error",
                           "error": "%s: %s" % (type(exc).__name__, exc),
                           "event_count": 0, "events": []}, fh,
                          ensure_ascii=False, indent=1)
            print("  [py][FAIL] %s：%s: %s" % (case_id, type(exc).__name__, exc))
            continue
        payload = vo._py_payload(case_id, c["seed"], eng, et_names)
        payload["rng_state_injected"] = None
        payload["reseeded_after_player_character"] = True
        payload["post_seed_draws"] = 0
        os.makedirs(out_dir, exist_ok=True)
        with io.open(out_path, "w", encoding="utf-8", newline="\n") as fh:
            json.dump(payload, fh, ensure_ascii=False, indent=1)
        ok += 1
        if i % 10 == 0:
            import gc
            gc.collect()
            print("  [py] %d/%d" % (i, len(cases)))
    print("[py-s2] 完成 %d/%d 场" % (ok, len(cases)))
    return 0 if ok == len(cases) else 1


# ═══════════════════════════ 逐行比对 ═══════════════════════════

def compare_case_s2(case_id: str, et_names: Dict[int, str]) -> Dict[str, Any]:
    paths = {
        "oracle": os.path.join(vo.FIGHTS_DIR, case_id, "events.json"),
        "gdcore": os.path.join(GD_OUT, case_id, "events.json"),
        "py": os.path.join(PY_OUT, case_id, "events.json"),
    }
    for tag, p in paths.items():
        if not os.path.exists(p) or vo._event_count(p) <= 0:
            return {"caseId": case_id, "match": "%s 缺产物" % tag,
                    "firstDivergence": None}
    streams = {tag: vo.canonical_stream(p, et_names) for tag, p in paths.items()}
    lines = {tag: vo.render_lines(streams[tag]) for tag in streams}

    ev_og = vo.first_divergence([vo._tuple_of(e) for e in streams["oracle"]],
                                [vo._tuple_of(e) for e in streams["gdcore"]],
                                "oracle", "gdcore")
    ev_gp = vo.first_divergence([vo._tuple_of(e) for e in streams["gdcore"]],
                                [vo._tuple_of(e) for e in streams["py"]],
                                "gdcore", "py")
    ln_og = vo.first_divergence(lines["oracle"], lines["gdcore"], "oracle", "gdcore")
    ln_gp = vo.first_divergence(lines["gdcore"], lines["py"], "gdcore", "py")

    og = ev_og["kind"] is None and ln_og["kind"] is None   # 内核对齐
    gp = ev_gp["kind"] is None and ln_gp["kind"] is None   # 转写孪生对齐
    if og and gp:
        match = "三方一致"
    elif og and not gp:
        match = "gdcore≡oracle 但 py 分歧"
    elif gp and not og:
        match = "oracle≠gdcore"
    else:
        match = "oracle≠gdcore 且 py 分歧"

    first_div: Dict[str, Any] = {}
    for pair, ev, ln, la, lb in (
            ("oracle_vs_gdcore", ev_og, ln_og, "oracle", "gdcore"),
            ("gdcore_vs_py", ev_gp, ln_gp, "gdcore", "py")):
        if ev.get("kind") is not None or ln.get("kind") is not None:
            idx = ev.get("index")
            first_div[pair] = {
                "event_divergence": ev, "line_divergence": ln,
                "counts": {la: len(streams[la]), lb: len(streams[lb])},
                "context": None if idx is None else {
                    la: json.dumps(vo._tuple_of(streams[la][idx]),
                                   ensure_ascii=False, default=str)[:300],
                    lb: json.dumps(vo._tuple_of(streams[lb][idx]),
                                   ensure_ascii=False, default=str)[:300],
                },
            }

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
        "oracleEvents": len(streams["oracle"]),
        "gdcoreEvents": len(streams["gdcore"]),
        "pyEvents": len(streams["py"]),
        "winner": {"oracle": oracle_meta.get("winner"),
                   "gdcore": gd_meta.get("winner"), "py": py_meta.get("winner")},
        "match": match,
        "kernelAligned": og,
        "pyAligned": gp,
        "firstDivergence": first_div if first_div else None,
        "judgement": {"event_tuples": {"oracle_gd": ev_og["kind"] is None,
                                       "gd_py": ev_gp["kind"] is None},
                      "rendered_lines": {"oracle_gd": ln_og["kind"] is None,
                                         "gd_py": ln_gp["kind"] is None}},
    }


# ═══════════════════════════ 主流程 ═══════════════════════════

def main() -> int:
    ap = argparse.ArgumentParser(description="阶段2：同 seed 无注入三方逐行对齐")
    ap.add_argument("--sample-size", type=int, default=20)
    ap.add_argument("--sample-seed", type=int, default=20261007)
    ap.add_argument("--cases", default="", help="逗号分隔 case_id 定向（优先于抽样）")
    ap.add_argument("--skip-godot", action="store_true")
    ap.add_argument("--skip-py", action="store_true")
    ap.add_argument("--compare-only", action="store_true")
    ap.add_argument("--alignment-out", default=ALIGNMENT_JSON)
    args = ap.parse_args()

    only = [x for x in args.cases.split(",") if x]
    cases = select_cases_s2(args.sample_seed, args.sample_size, only)
    print("[cases] 可用语料抽样 %d 场（sample_seed=%d，cases=%s）"
          % (len(cases), args.sample_seed, args.cases or "-"))
    if not cases:
        print("无可用用例", file=sys.stderr)
        return 2

    if not args.compare_only:
        if not args.skip_godot:
            rc = run_godot_s2(cases)
            if rc != 0:
                print("gd_core(Godot) 批量未全 PASS（退出码 %d）——继续比对已有产物"
                      % rc, file=sys.stderr)
        if not args.skip_py:
            run_py_s2(cases)

    et_names = vo._et_names()
    per_case = []
    for i, c in enumerate(cases, 1):
        try:
            result = compare_case_s2(c["case_id"], et_names)
        except Exception as exc:  # noqa: BLE001
            result = {"caseId": c["case_id"], "match": "比对异常",
                      "error": "%s: %s" % (type(exc).__name__, exc),
                      "firstDivergence": None}
        per_case.append(result)
        print("  [%d/%d] %-16s %s（oracle=%d gdcore=%d py=%d）"
              % (i, len(cases), c["case_id"], result.get("match"),
                 result.get("oracleEvents", -1), result.get("gdcoreEvents", -1),
                 result.get("pyEvents", -1)))

    kernel_aligned = sum(1 for r in per_case if r.get("kernelAligned"))
    three_way = sum(1 for r in per_case if r.get("match") == "三方一致")
    match_dist: Dict[str, int] = {}
    for r in per_case:
        match_dist[r.get("match", "?")] = match_dist.get(r.get("match", "?"), 0) + 1

    report = {
        "stage": "2（装配期消耗对齐，同 seed 无 state 注入）",
        "kernelAligned": kernel_aligned,
        "threeWayAligned": three_way,
        "total": len(per_case),
        "match_distribution": match_dist,
        "sample": {"sample_seed": args.sample_seed,
                   "sample_size": args.sample_size,
                   "case_ids": [c["case_id"] for c in cases]},
        "convention": {
            "injection": "无——两侧 gd_core 从 seed(S) 起跑完整链（阶段2 判定本体）",
            "assembly_model": "物品/宝石实例 2×BalancedRng=4 步（场景双绑定）+ "
                              "FlickerAnimation 入树 2 步 + 对手 Character 8 步；"
                              "对手角色在播种后实例化（oracle_fight.gd:576）",
            "activation_order": "真 Godot seed(S)+shuffle×2+sort_TriggerPriority 终序直通",
            "judgement": "主判据=engine/log_text.py 渲染战报逐行比对；辅判据=事件 canonical",
        },
        "perCase": per_case,
    }
    out_path = args.alignment_out
    os.makedirs(os.path.dirname(os.path.abspath(out_path)), exist_ok=True)
    with io.open(out_path, "w", encoding="utf-8", newline="\n") as fh:
        json.dump(report, fh, ensure_ascii=False, indent=1)
        fh.write("\n")

    print("")
    print("=== 阶段2 结果（无注入）：内核对齐（oracle≡gdcore）%d/%d；三方一致 %d/%d ==="
          % (kernel_aligned, len(per_case), three_way, len(per_case)))
    for m, n in sorted(match_dist.items(), key=lambda kv: -kv[1]):
        print("  %-28s %d" % (m, n))
    print("alignment_s2.json → %s" % out_path)
    return 0 if three_way == len(per_case) else 1


if __name__ == "__main__":
    raise SystemExit(main())
