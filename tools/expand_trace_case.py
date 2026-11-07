#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
expand_trace_case.py — 扩样单场双链 trace 采集器（np24 双链 trace 锚定对齐法的前置）

在**隔离工程副本**（output/_expand/oracle_proj/，expand_run_oracle.py 的授权工作面）
上重放指定扩样场，两侧各产出逐抽链日志，**输出全部重定向到 scratch 目录**，
语料盘（output/oracle/expand/fights/）与 gd 产物（align_expand/）零触碰：

  oracle 侧  ORACLE_RNG_TRACE=1（np29fC 独立门控）→ <scratch>/oracle/<case>/rng_log.txt
  gd 侧      ORACLE_ALIGN_TRACE=1 → <scratch>/gdcore/<case>/rng_trace.txt

用法：
    python -X utf8 tools/expand_trace_case.py run101582_r9_o704990_r9
    python -X utf8 tools/expand_trace_case.py <case_id> --skip-gd      # 只采 oracle 侧
之后：
    python -X utf8 tools/diff_draw_trace.py <case_id> <scratch>/oracle/<case>/rng_log.txt \\
        <scratch>/gdcore/<case>/rng_trace.txt
"""
from __future__ import annotations

import argparse
import io
import json
import os
import shutil
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))

COPY = os.path.join(ROOT, "output", "_expand", "oracle_proj")
SCRATCH = os.path.join(ROOT, "output", "_expand", "trace_root")
CASES_JSON = os.path.join(ROOT, "gd_core_test", "expand_align_cases.json")
FIGHTS_DIR = os.path.join(ROOT, "output", "oracle", "expand", "fights")


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("case_id")
    ap.add_argument("--skip-gd", action="store_true")
    ap.add_argument("--skip-oracle", action="store_true")
    args = ap.parse_args()
    cid = args.case_id

    cases = json.load(io.open(CASES_JSON, encoding="utf-8"))
    entry = next((c for c in cases["cases"] if c["case_id"] == cid), None)
    if entry is None:
        print("用例不在 expand_align_cases.json：%s" % cid, file=sys.stderr)
        return 2

    # 1) 副本 fights.json ← 全量 1,690 用例表（oracle_fight.gd 读 res://fights.json，
    #    ORACLE_ONLY_CASES 选场；副本可写=授权工作面）
    fj = os.path.join(COPY, "fights.json")
    bak = fj + ".bak"
    if not os.path.exists(bak):
        shutil.copy2(fj, bak)
    with io.open(fj, "w", encoding="utf-8", newline="\n") as fh:
        json.dump({"format": "oracle-fights/1",
                   "generated_by": "tools/expand_trace_case.py（trace 用）",
                   "cases": cases["cases"]}, fh, ensure_ascii=False,
                  separators=(",", ":"))
        fh.write("\n")
    print("[copy] fights.json ← %d 场（原文件备份 .bak）" % len(cases["cases"]))

    import godot_headless as gh

    ora_root = os.path.join(SCRATCH, "oracle").replace("\\", "/")
    gd_root = os.path.join(SCRATCH, "gdcore").replace("\\", "/")
    os.makedirs(ora_root, exist_ok=True)
    os.makedirs(gd_root, exist_ok=True)

    # 2) oracle 探针重放（输出→scratch；rng_log 由 ORACLE_RNG_TRACE 落 case 目录）
    if not args.skip_oracle:
        cmd = gh.cmd(project=COPY, script="oracle_fight.gd")
        env = {"ORACLE_ONLY_CASES": cid,
               "ORACLE_FIGHTS_ROOT": ora_root,
               "ORACLE_RNG_TRACE": "1",
               "ORACLE_FIGHT_CHUNK": "0"}
        rc, out, log = gh.run(cmd, label="trace_oracle", env_extra=env, timeout=2400)
        print("[oracle] rc=%d log=%s" % (rc, log))
        rng_log = os.path.join(ora_root, cid, "rng_log.txt")
        print("[oracle] rng_log: %s（%s）" % (
            rng_log, "OK %d 行" % sum(1 for _ in io.open(rng_log, errors="replace"))
            if os.path.exists(rng_log) else "缺失！"))
        ev = os.path.join(ora_root, cid, "events.json")
        if os.path.exists(ev):
            d = json.load(io.open(ev, encoding="utf-8"))
            print("[oracle] 重放 event_count=%d（语料 %d）" % (
                d.get("event_count", -1),
                json.load(io.open(os.path.join(FIGHTS_DIR, cid, "events.json"),
                                  encoding="utf-8")).get("event_count", -1)))

    # 3) gd trace 重放（输出→scratch）
    if not args.skip_gd:
        cmd = gh.cmd(project=os.path.join(ROOT, "gd_core_test"),
                     script="OracleAlignBattle.gd")
        env = {"ORACLE_ALIGN_CASES_JSON": CASES_JSON.replace("\\", "/"),
               "ORACLE_ALIGN_FIGHTS_ROOT": FIGHTS_DIR.replace("\\", "/"),
               "ORACLE_ALIGN_OUT": gd_root,
               "ORACLE_ALIGN_CASES": cid,
               "ORACLE_ALIGN_TRACE": "1",
               "ORACLE_ALIGN_CHUNK": "0"}
        rc, out, log = gh.run(cmd, label="trace_gd", env_extra=env, timeout=600)
        print("[gd] rc=%d log=%s" % (rc, log))
        rng_trace = os.path.join(gd_root, cid, "rng_trace.txt")
        print("[gd] rng_trace: %s（%s）" % (
            rng_trace, "OK %d 行" % sum(1 for _ in io.open(rng_trace, errors="replace"))
            if os.path.exists(rng_trace) else "缺失！"))

    print("[done] 对位：python -X utf8 tools/diff_draw_trace.py %s %s %s"
          % (cid,
             os.path.join(ora_root, cid, "rng_log.txt"),
             os.path.join(gd_root, cid, "rng_trace.txt")))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
