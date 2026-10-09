#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
verify_oracle_s1.py — 阶段1：神谕战斗开始时刻 rng state 注入的三方逐行对齐
（docs/alignment_fix_workflow.md §2 阶段1；宿主复用 tools/verify_oracle.py 的
canonical/渲染/首分歧机器，重放产物写到独立的 *_s1 目录，不污染旧语料）

与 verify_oracle.py（seed 重放）的本质差异：
  旧管线让两侧 gd_core 在装配前吃同一个 seed，试图连装配期消耗一起对齐——
  实测 0/1 硬边界（≥12 物品 0% 对齐），根因是装配期消耗面无法静态复刻。
  阶段1 改为：神谕在「战斗装配完成后、开战序列（prepareItems/activateItems）
  与首次 tick 之前」导出 Util.rng 的 (seed, state) 双 u64
  （output/oracle/fights/<case>/rng_state.txt，oracle_fight.gd 导出）；
  两侧 gd_core 在同一语义边界（装配完成、startBattle 之前）用 set_state
  直灌 PCG state（docs/rng_truth.md §2.3，不前进不重播）——绕开装配期消耗
  差异，从同一 state 起跑开战序列 + 逐 tick 判定链。此时双方 BalancedRng
  已在 prepareItems 同点重置归零（原版 Item.gd:3345-3351 / Character.gd:294-317；
  内核 gd_core/CoreItem.gd:531 / CoreCharacter.gd:259），链 state 唯一决定
  后续每次掷点 ⇒ 逐行分歧即战斗判定逻辑/数据 bug。

判据（与 verify_oracle.py 同口径）：
  主：engine/log_text.py 渲染战报逐行比对；
  辅：事件 canonical（t 按 1/60s tick 取整、type/side/origin/params/parent-depth 全等）。
  场次「逐行一致」= 两条判据 × 两对组合（oracle↔gdcore、gdcore↔py）全等。

用法：
  python -X utf8 tools/verify_oracle_s1.py --cases run1122_r11,run1160_r18,run1195_r17
  python -X utf8 tools/verify_oracle_s1.py                # 全量（917 场）
  python -X utf8 tools/verify_oracle_s1.py --compare-only # 只重跑比对
输出：
  output/oracle/alignment_s1.json {aligned, kernel_aligned, total, perCase, …}
  output/oracle/align/render_s1/<case>.{oracle,gdcore,py}.logtext（留档）
"""
from __future__ import annotations

import argparse
import io
import json
import os
import sys
from typing import Any, Dict, List, Optional

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)
sys.path.insert(0, os.path.join(ROOT, "tools"))

import verify_oracle as vo  # noqa: E402  — 复用 canonical/渲染/首分歧机器

FIGHTS_DIR = vo.FIGHTS_DIR
ALIGN_DIR = vo.ALIGN_DIR
GD_OUT = os.path.join(ALIGN_DIR, "gdcore_s1")
PY_OUT = os.path.join(ALIGN_DIR, "py_s1")
RENDER_DIR = os.path.join(ALIGN_DIR, "render_s1")
LINEUP_OUT = vo.LINEUP_OUT          # 夹具阵容沿用旧批量（装配序冻结语料）
CASES_JSON = vo.CASES_JSON
ALIGNMENT_JSON = os.path.join(ROOT, "output", "oracle", "alignment_s1.json")


def read_rng_state(case_id: str) -> Optional[int]:
    """rng_state.txt → state u64（GDScript 有符号视角原样转 int；
    set_state 内部按 MASK64 归一）。文件缺失返回 None（fail-fast，不静默）。"""
    p = os.path.join(FIGHTS_DIR, case_id, "rng_state.txt")
    if not os.path.exists(p):
        return None
    state = None
    for ln in io.open(p, encoding="utf-8", errors="replace"):
        ln = ln.strip()
        if ln.startswith("state="):
            state = int(ln[len("state="):])
    if state is None:
        raise RuntimeError("%s 缺 state= 行（格式错误）" % p)
    return state


def select_cases_s1(limit: int, only: List[str]) -> List[Dict[str, Any]]:
    """fights.json ∩ 神谕 events 非空 ∩ rng_state.txt 已导出 ∩ 夹具内，保序。"""
    fights = json.load(io.open(os.path.join(ROOT, "oracle", "fights.json"),
                               encoding="utf-8"))
    fixture = set(vo.fixture_case_ids())
    out = []
    for c in fights["cases"]:
        cid = c["case_id"]
        if only and cid not in only:
            continue
        if cid not in fixture:
            continue
        if vo._event_count(os.path.join(FIGHTS_DIR, cid, "events.json")) <= 0:
            continue
        if read_rng_state(cid) is None:
            continue
        out.append({"case_id": cid, "seed": int(c["seed"]),
                    "round_id": int(c["round_id"])})
        if limit > 0 and len(out) >= limit:
            break
    return out


# ═══════════════════════════ gd_core(Godot) 侧 ═══════════════════════════

def run_godot_s1(cases: List[Dict[str, Any]], chunk: int = 120,
                 max_rounds: int = 40) -> int:
    """分块跑 state 注入版 gd_core(Godot) 批量（OracleAlignBattle.gd 自身已改为
    读 rng_state.txt 注入；这里只换输出目录并复用分块/续跑驱动）。
    ★ 驱动侧用例定向：把本驱动选定的用例经 ORACLE_ALIGN_CASES 传给 Godot 侧，
    防止它把尚未导出 rng_state.txt 的场次跑成 missing-rng-state。"""
    vo.GD_OUT = GD_OUT
    if cases:
        os.environ["ORACLE_ALIGN_CASES"] = ",".join(c["case_id"] for c in cases)
    else:
        os.environ.pop("ORACLE_ALIGN_CASES", None)
    return vo.run_godot(chunk=chunk, max_rounds=max_rounds)


# ═══════════════════════════ gd_core_py(Python) 侧 ═══════════════════════════

def run_py_s1(cases: List[Dict[str, Any]]) -> int:
    """批量驱动：装配路径与 simulator.simulate 完全一致，唯三对齐 kwargs：
    below_master=True（原版段位分支，战斗期 adjustCooldown 消费）+
    p/o_activation_order（真 Godot 全局链洗牌终序直通）+ rng_state（阶段1 注入）。
    装配期 reseed/post_seed_draws 不再传——注入边界把它们整体绕开。"""
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
            print("  [py][skip] %s 不在夹具内（生成期已剔除）" % case_id)
            continue
        gd_path = os.path.join(GD_OUT, case_id, "events.json")
        if not os.path.exists(gd_path) or vo._event_count(gd_path) <= 0:
            print("  [py][skip] %s 缺 gd_core_s1 侧产物（激活顺序来源）" % case_id)
            continue
        state = read_rng_state(case_id)
        if state is None:
            print("  [py][skip] %s 缺 rng_state.txt" % case_id)
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
                               rng_state=state)
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
        payload["rng_state_injected"] = state
        payload["reseeded_after_player_character"] = False
        payload["post_seed_draws"] = 0
        os.makedirs(out_dir, exist_ok=True)
        with io.open(out_path, "w", encoding="utf-8", newline="\n") as fh:
            json.dump(payload, fh, ensure_ascii=False, indent=1)
        ok += 1
        if i % 50 == 0:
            import gc
            gc.collect()
            print("  [py] %d/%d" % (i, len(cases)))
    print("[py] 完成 %d/%d 场" % (ok, len(cases)))
    return 0 if ok == len(cases) else 1


# ═══════════════════════════ 逐行比对 ═══════════════════════════

def compare_case_s1(case_id: str, et_names: Dict[int, str]) -> Dict[str, Any]:
    """oracle ↔ gdcore_s1 ↔ py_s1 的双判据 × 两对逐行比对（verify_oracle 同口径）。"""
    paths = {
        "oracle": os.path.join(FIGHTS_DIR, case_id, "events.json"),
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

    def _ctx_pair(stream_a, stream_b, la, lb, ev, ln):
        idx = ev.get("index")
        if idx is None:
            return {"kind": ev.get("kind"),
                    "detail": ev.get("detail"),
                    "counts": {"%s" % la: len(stream_a), "%s" % lb: len(stream_b)}}
        def _at(s, i):
            e = s[i]
            return {"t": e["t_tick"], "type": e["type"], "actor": e["actor"],
                    "target": e["target"], "origin": e["origin"],
                    "params": e["params"], "parent": e["parent"], "depth": e["depth"]}
        return {"kind": "event", "index": idx,
                la: _at(stream_a, idx), lb: _at(stream_b, idx),
                "window": {
                    la: [json.dumps(vo._tuple_of(e), ensure_ascii=False, default=str)
                         for e in stream_a[max(0, idx - 3):idx + 4]],
                    lb: [json.dumps(vo._tuple_of(e), ensure_ascii=False, default=str)
                         for e in stream_b[max(0, idx - 3):idx + 4]]},
                "first_line_diff": (None if ln["index"] is None else
                                    {"line_index": ln["index"],
                                     la: lines_key(lines, la, ln),
                                     lb: lines_key(lines, lb, ln)})}

    def lines_key(lines, tag, ln):
        ls = lines[tag]
        i = ln["index"]
        return ls[i] if i < len(ls) else None

    first_div: Dict[str, Any] = {}
    if not og:
        first_div["oracle_vs_gdcore"] = _ctx_pair(
            streams["oracle"], streams["gdcore"], "oracle", "gdcore", ev_og, ln_og)
    if not gp:
        first_div["gdcore_vs_py"] = _ctx_pair(
            streams["gdcore"], streams["py"], "gdcore", "py", ev_gp, ln_gp)

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
    ap = argparse.ArgumentParser(description="阶段1：rng state 注入三方逐行对齐")
    ap.add_argument("--limit", type=int, default=0, help="只跑前 N 场（0=全量）")
    ap.add_argument("--cases", default="",
                    help="逗号分隔 case_id 定向跑（优先于 --limit）")
    ap.add_argument("--skip-godot", action="store_true", help="跳过 gd_core(Godot) 重放")
    ap.add_argument("--skip-py", action="store_true", help="跳过 gd_core_py 重放")
    ap.add_argument("--compare-only", action="store_true", help="只重跑比对")
    ap.add_argument("--alignment-out", default=ALIGNMENT_JSON)
    args = ap.parse_args()

    only = [x for x in args.cases.split(",") if x]
    cases = select_cases_s1(args.limit, only)
    print("[cases] state 语料可用 %d 场（--limit=%d --cases=%s）"
          % (len(cases), args.limit, args.cases or "-"))
    if not cases:
        print("无可用用例（rng_state.txt 未导出？先重跑神谕批量）", file=sys.stderr)
        return 2

    if not args.compare_only:
        if not args.skip_godot:
            rc = run_godot_s1(cases)
            if rc != 0:
                print("gd_core(Godot) 批量未全 PASS（退出码 %d）——继续比对已有产物"
                      % rc, file=sys.stderr)
        if not args.skip_py:
            run_py_s1(cases)

    et_names = vo._et_names()
    per_case = []
    for i, c in enumerate(cases, 1):
        try:
            result = compare_case_s1(c["case_id"], et_names)
        except Exception as exc:  # noqa: BLE001 —— 单场比对失败如实记档
            result = {"caseId": c["case_id"], "match": "比对异常",
                      "error": "%s: %s" % (type(exc).__name__, exc),
                      "firstDivergence": None}
        per_case.append(result)
        if i % 20 == 0 or i == len(cases):
            aligned = sum(1 for r in per_case if r.get("match") == "三方一致")
            print("  [compare] %d/%d（三方一致 %d）" % (i, len(cases), aligned))

    kernel_aligned = sum(1 for r in per_case if r.get("kernelAligned"))
    three_way = sum(1 for r in per_case if r.get("match") == "三方一致")
    match_dist: Dict[str, int] = {}
    for r in per_case:
        match_dist[r.get("match", "?")] = match_dist.get(r.get("match", "?"), 0) + 1

    report = {
        "stage": "1（rng state 注入，战斗期逐行对齐）",
        "kernelAligned": kernel_aligned,
        "threeWayAligned": three_way,
        "total": len(per_case),
        "match_distribution": match_dist,
        "convention": {
            "injection": "神谕在装配完成后、prepareItems/activateItems 与首次 tick 前"
                         "导出 Util.rng.state（rng_state.txt）；两侧 gd_core 在"
                         " startBattle 前 set_state 直灌（rng_truth.md §2.3）",
            "below_master": "true（神谕 Bronze 段位分支）",
            "activation_order": "真 Godot seed(S)+shuffle×2+sort_TriggerPriority 终序直通"
                                "（OracleAlignBattle.gd 现场复刻）",
            "judgement": "主判据=engine/log_text.py 渲染战报逐行比对；辅判据=事件 canonical"
                         "（t 按 1/60s tick 取整、type/side/origin/params/parent-depth 全等）",
        },
        "perCase": per_case,
    }
    out_path = args.alignment_out
    os.makedirs(os.path.dirname(os.path.abspath(out_path)), exist_ok=True)
    with io.open(out_path, "w", encoding="utf-8", newline="\n") as fh:
        json.dump(report, fh, ensure_ascii=False, indent=1)
        fh.write("\n")

    print("")
    print("=== 阶段1 结果：内核对齐（oracle≡gdcore）%d/%d；三方一致 %d/%d ==="
          % (kernel_aligned, len(per_case), three_way, len(per_case)))
    for m, n in sorted(match_dist.items(), key=lambda kv: -kv[1]):
        print("  %-28s %d" % (m, n))
    print("alignment_s1.json → %s" % out_path)
    return 0 if three_way == len(per_case) else 1


if __name__ == "__main__":
    raise SystemExit(main())
