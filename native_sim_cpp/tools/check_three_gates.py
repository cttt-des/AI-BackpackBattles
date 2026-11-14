# -*- coding: utf-8 -*-
"""native_sim（C++20 转写内核）确定性三闸检验——借用主仓模拟器优化的三闸方法学，
但**独立成账**（台账见 native_sim_cpp/确定性检验台账.md，不写主仓 docs/性能优化下一步规划.md）。

三闸（口径同主仓）：
  闸1 seed 双态   : lineups/truth_20261001_220653_R19 × seeds {20260923, 42}
                    判据 = 主仓 tools/check_seed_dual.py 的基线
                    （907/opponent/1548、1042/opponent/1991；events_bytes 无法比对——
                    native 侧不导出事件流，只比 ticks/winner/event_count）
  闸2 REG 九场    : gd_core_test/oracle_align_cases.json 全部 9 场
                    判据 = 绿色 REG9 账本（output/perf/_fin_reg9.json）的
                    winner.oracle + oracleEvents（Godot 神谕真值）
  闸3 60 场快闸   : output/perf/core_cases.txt（取自 gd_core_test/expand_align_cases.json）
                    判据 = output/oracle/expand/alignment_expand.json 的
                    winner.oracle + oracleEvents

每闸额外做两个确定性检验：
  A. 同 case 独立跑两遍 → BattleResult 全字段逐位相等（自洽确定性）
  B. run_batch(n_threads=8) 结果 == 串行 run_one（线程/批位不变性）

旗标映射（对照主仓引擎语义推得）：
  闸1 = GDCoreEngine 默认路径（seed_gate.py 口径）：
        startBattle(preordered=False)（内核 ctx.rng.shuffle+排序）
        ⇒ native_activation_order=False, reseed_after_player_character=False, max_time=180
  闸2/3 = 神谕对齐路径（verify_oracle / test_parity 口径）：
        CoreContext(seed) 注入 + 真链 seed(S)→shuffle×2→sort_TriggerPriority 直通
        ⇒ native_activation_order=True, reseed_after_player_character=True,
          formal_ev_gate=25000（M12 常数，同神谕）, max_time=90（同 verify_oracle）,
          below_master=False（账本 convention：录制时 isBelowLeague(Master)=假）

用法:
    python -X utf8 native_sim_cpp/tools/check_three_gates.py [--gates 123] [--json OUT]
退出码 0 = 所跑闸全绿。
"""
from __future__ import annotations

import argparse
import json
import os
import sys
import time
from pathlib import Path

_TOOLS = Path(__file__).resolve().parent
BUNDLE_ROOT = _TOOLS.parent            # native_sim_cpp/
REPO_ROOT = BUNDLE_ROOT.parent         # 主仓根 D:\文件资料\学习\自动背包AI
if str(BUNDLE_ROOT) not in sys.path:
    sys.path.insert(0, str(BUNDLE_ROOT))

from native_sim.sim import get_simulator  # noqa: E402


def res_to_dict(res) -> dict:
    out = {}
    for name, *_ in type(res)._fields_:
        v = getattr(res, name)
        if hasattr(type(v), "_length_"):  # ctypes 数组（item_activations）→ list
            v = list(v)
        out[name] = v
    return out


def res_diff(a: dict, b: dict) -> list:
    diffs = []
    for k in a:
        va, vb = a[k], b[k]
        eq = (va == vb)
        if not eq:
            if isinstance(va, float) and isinstance(vb, float):
                diffs.append(f"{k} {va!r}!={vb!r}")
            else:
                diffs.append(f"{k} {va}!={vb}")
    return diffs


def load_json(p: Path):
    with open(p, encoding="utf-8") as f:
        return json.load(f)


def find_green_reg9_ledger() -> tuple[dict, Path]:
    """取最近一份 9/9 全绿的 REG9 账本作为神谕真值载体。"""
    cands = sorted((REPO_ROOT / "output" / "perf").glob("*reg9*.json"),
                   key=lambda p: p.stat().st_mtime, reverse=True)
    for p in cands:
        try:
            d = load_json(p)
        except Exception:
            continue
        pc = d.get("perCase") or []
        if d.get("aligned") == 9 and d.get("total") == 9 and len(pc) == 9 \
                and all(c.get("match") == "三方一致" for c in pc):
            return {c["caseId"]: c for c in pc}, p
    raise RuntimeError("找不到 9/9 全绿的 REG9 账本（output/perf/*reg9*.json）")


# ────────────────────────────── 闸 1：seed 双态 ──────────────────────────────

def gate1(sim) -> tuple[dict, bool]:
    base = load_json(REPO_ROOT / "output" / "perf" / "_seed_gate_baseline.json")
    pl = load_json(REPO_ROOT / "lineups" / "truth_20261001_220653_R19_player.json")
    op = load_json(REPO_ROOT / "lineups" / "truth_20261001_220653_R19_opponent.json")
    out = {"baseline": base, "cases": []}
    all_ok = True
    t0 = time.perf_counter()
    for seed_s, quad in sorted(base.items()):
        seed = int(seed_s)
        r1 = sim.run_one(pl, op, seed=seed,
                         round_id=int(pl.get("round", 1)),
                         native_activation_order=False,
                         reseed_after_player_character=False,
                         label_rng_enabled=True,
                         max_time=180.0)
        r2 = sim.run_one(pl, op, seed=seed,
                         round_id=int(pl.get("round", 1)),
                         native_activation_order=False,
                         reseed_after_player_character=False,
                         label_rng_enabled=True,
                         max_time=180.0)
        d1, d2 = res_to_dict(r1), res_to_dict(r2)
        rerun_diffs = res_diff(d1, d2)
        got = (d1["ticks"], "opponent" if d1["player_wins"] == 0 else "player", d1["event_count"])
        # 事件计数口径：py 基线 = eng.log.event_count 在 run() 之后取值，含
        # emit_combat_end 合成行（+1，simulator/gd_core_engine.py:1515→624）；
        # native 钩子只数内核 logEvent。故 native 期望 = n_events - 1。
        exp = (quad["ticks"], quad["winner"], quad["n_events"] - 1)
        ok = (got == exp) and not rerun_diffs
        all_ok &= ok
        out["cases"].append({
            "seed": seed, "expected_ticks/winner/events": exp,
            "got": got, "rerun_bitexact": not rerun_diffs,
            "rerun_diffs": rerun_diffs[:10], "ok": ok,
            "full_result_run1": d1,
        })
        print(f"  seed={seed}: ticks {got[0]}/{exp[0]} winner {got[1]}/{exp[1]} "
              f"events {got[2]}/{exp[2]} rerun_bitexact={not rerun_diffs} "
              f"-> {'OK' if ok else 'FAIL'}")
    out["native_ms_per_fight"] = (time.perf_counter() - t0) * 1000 / (2 * len(base))
    print(f"  [gate1] native mean {out['native_ms_per_fight']:.1f} ms/fight")
    return out, all_ok


# ────────────────────────────── 闸 2/3 公共跑法 ──────────────────────────────

def run_case_set(sim, cases: list[dict], *, tag: str, below_master: bool = False) -> tuple[dict[int, dict], float]:
    """串行跑每个 case 两遍；返回 {index: run1_dict}、每场均耗时。

    below_master 语料约定（np24 终谳）：
      旧语料（oracle_align / REG9）= True（录制时 isBelowLeague(Master)=真，
        对手冷却掷 (0.975,1.05)）；新语料（expand / 60 场）= False（(0.95,1.05)）。
    """
    res = {}
    t0 = time.perf_counter()
    for i, c in enumerate(cases):
        kw = dict(seed=int(c["seed"]),
                  round_id=int(c.get("round_id", 1)),
                  label_rng_enabled=bool(c.get("label_rng", True)),
                  custom_health_multiplier=float(c.get("custom_health_multiplier", 100.0)),
                  native_activation_order=True,
                  reseed_after_player_character=True,
                  below_master=below_master,
                  formal_ev_gate=25000,
                  max_time=90.0)
        r1 = sim.run_one(c["player"], c["opponent"], **kw)
        r2 = sim.run_one(c["player"], c["opponent"], **kw)
        d1, d2 = res_to_dict(r1), res_to_dict(r2)
        diffs = res_diff(d1, d2)
        if diffs:
            print(f"  !! [{tag}] {c['case_id']} 双跑不一致(确定性破): {diffs[:6]}")
        res[i] = {"case": c, "d1": d1, "rerun_diffs": diffs}
    dt = (time.perf_counter() - t0) * 1000 / max(1, len(cases))
    return res, dt


def run_batch_once(sim, cases: list[dict], n_threads: int, below_master: bool = False) -> dict[int, dict]:
    pairs = []
    for c in cases:
        opt = sim.make_options(seed=int(c["seed"]),
                               round_id=int(c.get("round_id", 1)),
                               label_rng_enabled=bool(c.get("label_rng", True)),
                               custom_health_multiplier=float(c.get("custom_health_multiplier", 100.0)),
                               native_activation_order=True,
                               reseed_after_player_character=True,
                               below_master=below_master,
                               formal_ev_gate=25000,
                               max_time=90.0)
        pairs.append((c["player"], c["opponent"], opt))
    batch = sim.run_batch(pairs, n_threads=n_threads)
    return {i: res_to_dict(r) for i, r in enumerate(batch)}


def judge_vs_ledger(res: dict, ledger_by_id: dict, tag: str) -> tuple[list[dict], bool]:
    rows = []
    all_ok = True
    for i, r in res.items():
        c = r["case"]
        d1 = r["d1"]
        led = ledger_by_id.get(c["case_id"])
        if led is None:
            rows.append({"case_id": c["case_id"], "ok": False, "note": "账本缺该 case"})
            all_ok = False
            continue
        got_winner = "player" if d1["player_wins"] else "opponent"
        # 事件计数口径：账本 oracleEvents/gdcoreEvents 含 py/神谕导出侧的合成
        # combat_end 行（+1，见 run570 实证 548=547 内核行+1）；native 只数内核行。
        exp_events = led["oracleEvents"] - 1
        ok = (got_winner == led["winner"]["oracle"]
              and d1["event_count"] == exp_events
              and not r["rerun_diffs"])
        all_ok &= ok
        rows.append({
            "case_id": c["case_id"], "seed": c["seed"],
            "expected": {"winner": led["winner"]["oracle"], "events": led["oracleEvents"] - 1},
            "got": {"winner": got_winner, "events": d1["event_count"],
                    "ticks": d1["ticks"], "combat_time": d1["combat_time"],
                    "player_hp": d1["player_hp"], "opponent_hp": d1["opponent_hp"]},
            "rerun_bitexact": not r["rerun_diffs"], "ok": ok,
        })
        if not ok:
            print(f"  !! [{tag}] {c['case_id']}: got win={got_winner} ev={d1['event_count']} "
                  f"ticks={d1['ticks']} | oracle win={led['winner']['oracle']} ev={led['oracleEvents']}")
    return rows, all_ok


def batch_invariance(sim, cases: list[dict], serial: dict[int, dict], below_master: bool = False) -> tuple[bool, list]:
    """run_batch(8T) 必须与串行 run_one 逐位一致。"""
    bad = []
    bt = run_batch_once(sim, cases, n_threads=8, below_master=below_master)
    for i, c in enumerate(cases):
        diffs = res_diff(serial[i]["d1"], bt[i])
        if diffs:
            bad.append({"case_id": c["case_id"], "diffs": diffs[:8]})
            print(f"  !! 批跑(8T)与串行不一致: {c['case_id']} {diffs[:6]}")
    return (not bad), bad


# ────────────────────────────── 主流程 ──────────────────────────────

def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--gates", default="123", help="跑哪些闸，如 123 / 13")
    ap.add_argument("--json", default=str(BUNDLE_ROOT / "output" / "three_gates_result.json"))
    args = ap.parse_args()
    gates = set(args.gates)

    sim = get_simulator()
    report: dict = {"bundle": str(BUNDLE_ROOT), "results": {}}
    exit_ok = True

    # ── 闸 1 ──
    if "1" in gates:
        print("== 闸1 seed 双态 ==")
        out, ok = gate1(sim)
        report["results"]["gate1_seed_dual"] = {**out, "ok": ok}
        exit_ok &= ok
        print(f"  闸1 {'GREEN' if ok else 'RED'}")

    # ── 闸 2 ──
    if "2" in gates:
        print("== 闸2 REG 九场 ==")
        led, led_path = find_green_reg9_ledger()
        print(f"  真值载体: {led_path.name}")
        cases = load_json(REPO_ROOT / "gd_core_test" / "oracle_align_cases.json")["cases"]
        cases = sorted(cases, key=lambda c: int(c["seed"]))
        res, dt = run_case_set(sim, cases, tag="REG9", below_master=True)
        rows, ok = judge_vs_ledger(res, led, "REG9")
        b_ok, b_bad = batch_invariance(sim, cases, res, below_master=True)
        ok &= b_ok
        n_green = sum(1 for r in rows if r["ok"])
        print(f"  REG9: {n_green}/{len(rows)} 对齐神谕; 批不变性 {'OK' if b_ok else 'RED'}; "
              f"native mean {dt:.1f} ms/fight")
        print(f"  闸2 {'GREEN' if ok else 'RED'}")
        report["results"]["gate2_reg9"] = {"ledger": led_path.name, "perCase": rows,
                                           "batch_invariant": b_ok, "batch_bad": b_bad,
                                           "native_ms_per_fight": dt, "ok": ok}
        exit_ok &= ok

    # ── 闸 3 ──
    if "3" in gates:
        print("== 闸3 60 场 ==")
        led_raw = load_json(REPO_ROOT / "output" / "oracle" / "expand" / "alignment_expand.json")
        led = {c["caseId"]: c for c in led_raw["perCase"]}
        core60 = (REPO_ROOT / "output" / "perf" / "core_cases.txt").read_text(encoding="utf-8").strip().split(",")
        all_cases = {c["case_id"]: c for c in load_json(REPO_ROOT / "gd_core_test" / "expand_align_cases.json")["cases"]}
        cases = [all_cases[cid] for cid in core60]
        # ★ 60 场（expand 新语料）与 REG9 同：verify_oracle 的 py 腿对两个语料
        #   都硬编码 below_master=True（tools/verify_oracle.py:518）。
        #   账本 convention 文本写的「below_master: false」是陈旧记载——
        #   归因实验（tools/_attrib_expand.py 四臂）实证 bl=True 复现账本、
        #   bl=False 的 py 结果与 native 逐场同局（ticks 全同，事件差 1 合成行）。
        res, dt = run_case_set(sim, cases, tag="60场", below_master=True)
        rows, ok = judge_vs_ledger(res, led, "60场")
        b_ok, b_bad = batch_invariance(sim, cases, res, below_master=True)
        ok &= b_ok
        n_green = sum(1 for r in rows if r["ok"])
        print(f"  60 场: {n_green}/{len(rows)} 对齐神谕; 批不变性 {'OK' if b_ok else 'RED'}; "
              f"native mean {dt:.1f} ms/fight")
        print(f"  闸3 {'GREEN' if ok else 'RED'}")
        report["results"]["gate3_60"] = {"perCase": rows, "batch_invariant": b_ok,
                                         "batch_bad": b_bad, "native_ms_per_fight": dt, "ok": ok}
        exit_ok &= ok

    os.makedirs(os.path.dirname(args.json), exist_ok=True)
    with open(args.json, "w", encoding="utf-8") as f:
        json.dump(report, f, ensure_ascii=False, indent=1)
    print(f"结果已写 {args.json}")
    print("THREE GATES", "ALL GREEN" if exit_ok else "RED")
    return 0 if exit_ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
