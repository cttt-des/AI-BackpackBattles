#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
expand_isolated_check.py — 扩样红场「录制批泄漏」分类器（np51⑤）

背景：oracle_fight.gd:591 逐场 CustomRules.fromString(player_run.customRules)，
但 fromString 对空串**早退不复位**（CustomRules 单例跨场残留）⇒ 录制批内某场带
custom 规则（如 HealthMultiplier 120/220/60）后，同进程后续场的 prepare() 静默
临时体上限加成（item=null，无事件）被污染。gd/py 腿恒干净（mult=100）⇒ 凡污染
场必红。np49 §6m112 语料池化残留同族。

本工具对指定场做**单场隔离重放**（全新 oracle 进程=无泄漏，输出→scratch，语料
盘零触碰），按 events.json 三方对照分类：
  CLEAN-POLLUTED  隔离重放 == gd 腿产物   ⇒ 语料被泄漏污染，重录即绿
  KERNEL-DIVERGE  隔离重放 == 语料        ⇒ 非泄漏，gd_core 内核真分歧
  MESSY           隔离重放两者都不等      ⇒ 需人工深查
用法：
    python -X utf8 tools/expand_isolated_check.py case_id1,case_id2,...
    python -X utf8 tools/expand_isolated_check.py --all-red
结果落 output/_expand/isolated_check/<case_id>/（events.json + verdict）。
"""
from __future__ import annotations

import io
import json
import os
import shutil
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))

COPY = os.path.join(ROOT, "output", "_expand", "oracle_proj")
SCRATCH = os.path.join(ROOT, "output", "_expand", "isolated_check")
CASES_JSON = os.path.join(ROOT, "gd_core_test", "expand_align_cases.json")
FIGHTS_DIR = os.path.join(ROOT, "output", "oracle", "expand", "fights")
GD_OUT = os.path.join(ROOT, "output", "oracle", "align_expand", "gdcore")


def events_sig(p):
    try:
        d = json.load(io.open(p, encoding="utf-8"))
    except Exception:  # noqa: BLE001
        return None
    return json.dumps(d.get("events", []), sort_keys=True)


def main() -> int:
    args = sys.argv[1:]
    cases = json.load(io.open(CASES_JSON, encoding="utf-8"))["cases"]
    by_id = {c["case_id"]: c for c in cases}
    if args and args[0] == "--all-red":
        al = json.load(io.open(os.path.join(ROOT, "output", "oracle", "expand",
                                            "alignment_expand.json"), encoding="utf-8"))
        want = [r["caseId"] for r in al["perCase"] if r.get("match") != "三方一致"]
    else:
        want = [c.strip() for a in args for c in a.split(",") if c.strip()]

    import godot_headless as gh
    summary = {}
    for n, cid in enumerate(want, 1):
        if cid not in by_id:
            print("[%d/%d] %s 不在夹具" % (n, len(want), cid))
            continue
        out_dir = os.path.join(SCRATCH, cid)
        os.makedirs(out_dir, exist_ok=True)
        env = {"ORACLE_ONLY_CASES": cid,
               "ORACLE_FIGHTS_ROOT": SCRATCH.replace("\\", "/"),
               "ORACLE_FIGHT_CHUNK": "0"}
        rc, out, log = gh.run(gh.cmd(project=COPY, script="oracle_fight.gd"),
                              label="iso_oracle", env_extra=env, timeout=1500)
        iso = os.path.join(SCRATCH, cid, "events.json")
        sig_iso = events_sig(iso) if rc == 0 else None
        sig_corpus = events_sig(os.path.join(FIGHTS_DIR, cid, "events.json"))
        sig_gd = events_sig(os.path.join(GD_OUT, cid, "events.json"))
        if sig_iso is None:
            verdict = "ORACLE-FAIL(rc=%s)" % rc
        elif sig_iso == sig_gd and sig_iso == sig_corpus:
            verdict = "ALL-SAME(本场红因不在事件面?)"
        elif sig_iso == sig_gd:
            verdict = "CLEAN-POLLUTED"
        elif sig_iso == sig_corpus:
            verdict = "KERNEL-DIVERGE"
        else:
            verdict = "MESSY"
        summary[cid] = verdict
        print("[%d/%d] %-34s rc=%d → %s" % (n, len(want), cid, rc, verdict))

    with io.open(os.path.join(SCRATCH, "verdicts.json"), "w",
                 encoding="utf-8", newline="\n") as fh:
        json.dump(summary, fh, ensure_ascii=False, indent=1)
        fh.write("\n")
    from collections import Counter
    print("\n=== 分类汇总 ===")
    for v, c in Counter(summary.values()).most_common():
        print("  %-18s %d" % (v, c))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
