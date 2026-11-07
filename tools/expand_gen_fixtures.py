#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
expand_gen_fixtures.py — 扩样语料 → 三方对齐夹具（分批驱动 gen_fixture_from_lineup）

docs/expand_fix_kickoff.md §6.3 Step 1 / §10 队列 3：1,194 个用例目录塞不进单条
命令行（Windows ~32K 限制），本驱动按 --batch（默认 200）场一批**进程内**调用
gen_fixture_from_lineup.oracle_mode，逐批落 tmp 夹具文件，最后按 cases.json 原序
合并成 gd_core_test/expand_align_cases.json（绝不动 oracle_align_cases.json）。

要点：
  * stamina 取数库固定 = output/oracle/expand/data/history.db（合并库，runID 带
    +100000×库序号偏移）——经 set_history_db 注入；oracle/data/history.db 不触碰；
  * 玩家 run_id 解析沿用 oracle_mode 内的扩样兼容正则（run<r>_r<n>_o<r>_r<n> 取玩家段）；
  * v3 阵容落 output/oracle/align_expand/lineups/（独立 root，不混 914 的 align/lineups）；
  * label_rng=True 注入（与 verify_oracle.gen_fixtures 同口径，round20 定谳恒 ON）；
  * 不可装配场（物品不在 gd_core 描述符表等）如实记档
    output/oracle/align_expand/fixture_failures.json，不为其改内核（kickoff 红线）；
  * 收尾自检（防 §6.2 假分歧复发）：逐场比对「夹具玩家 stamina」vs「合并库直查
    roundData.stamina」——不一致 = 夹具取数链有洞，硬失败退出；
  * 断点续跑：某批 tmp 已存在且合法则跳过（--force 重算）。

用法：
    python -X utf8 tools/expand_gen_fixtures.py                 # 全量分批生成+合并
    python -X utf8 tools/expand_gen_fixtures.py --batch 200 --limit 6   # 冒烟
"""
from __future__ import annotations

import argparse
import io
import json
import os
import re
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
_TOOLS = os.path.join(ROOT, "tools")
if _TOOLS not in sys.path:
    sys.path.insert(0, _TOOLS)

CASES_JSON = os.path.join(ROOT, "output", "oracle", "expand", "cases.json")
FIGHTS_DIR = os.path.join(ROOT, "output", "oracle", "expand", "fights")
HISTORY_DB = os.path.join(ROOT, "output", "oracle", "expand", "data", "history.db")
LINEUP_OUT = os.path.join(ROOT, "output", "oracle", "align_expand", "lineups")
TMP_DIR = os.path.join(ROOT, "output", "oracle", "align_expand", "_fixture_batches")
FINAL_OUT = os.path.join(ROOT, "gd_core_test", "expand_align_cases.json")
FAILURES_OUT = os.path.join(ROOT, "output", "oracle", "align_expand",
                            "fixture_failures.json")
BATCH_LOG_DIR = os.path.join(TMP_DIR, "logs")

RUN_RE = re.compile(r"run(\d+)_r\d+(?:_o\d+_r\d+)?$")


def main() -> int:
    ap = argparse.ArgumentParser(description="扩样夹具分批生成（kickoff §6.3 Step 1）")
    ap.add_argument("--batch", type=int, default=200)
    ap.add_argument("--limit", type=int, default=0, help="只跑前 N 场（冒烟）")
    ap.add_argument("--force", action="store_true", help="忽略已存在批 tmp，全部重算")
    args = ap.parse_args()

    import gen_fixture_from_lineup as gfl
    gfl.set_history_db(HISTORY_DB)
    print("[db] stamina 取数库 = %s" % HISTORY_DB)

    table = json.load(io.open(CASES_JSON, encoding="utf-8"))
    case_ids = [c["case_id"] for c in table["cases"]]
    if args.limit > 0:
        case_ids = case_ids[:args.limit]
    case_dirs = [os.path.join(FIGHTS_DIR, cid) for cid in case_ids]
    n_batches = (len(case_dirs) + args.batch - 1) // args.batch
    print("[plan] %d 场 → %d 批（每批 %d）" % (len(case_dirs), n_batches, args.batch))

    os.makedirs(LINEUP_OUT, exist_ok=True)
    os.makedirs(BATCH_LOG_DIR, exist_ok=True)

    t0 = time.time()
    for bi in range(0, len(case_dirs), args.batch):
        k = bi // args.batch + 1
        tmp = os.path.join(TMP_DIR, "batch_%03d.json" % k)
        if os.path.exists(tmp) and not args.force:
            try:
                json.load(io.open(tmp, encoding="utf-8"))
                print("[batch %03d] 已存在，跳过（--force 重算）" % k)
                continue
            except Exception:  # noqa: BLE001 —— 损坏 tmp 重算
                pass
        batch_dirs = case_dirs[bi:bi + args.batch]
        # 批内 stdout 落批日志（告警/FAIL 全量留痕，控制台只看汇总）
        log_path = os.path.join(BATCH_LOG_DIR, "batch_%03d.log" % k)
        buf = io.open(log_path, "w", encoding="utf-8")
        old_stdout = sys.stdout
        rc = -1
        try:
            sys.stdout = buf
            rc = gfl.oracle_mode(batch_dirs, LINEUP_OUT, tmp)
        finally:
            sys.stdout = old_stdout
            buf.close()
        print("[batch %03d] %d 场 rc=%d（累计 %.0fs）→ %s"
              % (k, len(batch_dirs), rc, time.time() - t0, log_path))

    # ── 合并（按 cases.json 原序）────────────────────────────────────
    merged = []
    seen = set()
    header = None
    for k in range(1, n_batches + 1):
        tmp = os.path.join(TMP_DIR, "batch_%03d.json" % k)
        data = json.load(io.open(tmp, encoding="utf-8"))
        if header is None:
            header = {kk: data[kk] for kk in data if kk != "cases"}
        for c in data["cases"]:
            if c["case_id"] in seen:
                continue
            seen.add(c["case_id"])
            merged.append(c)
    # ★ 与 verify_oracle.gen_fixtures 同口径：label_rng 恒 ON（round20 定谳）
    for c in merged:
        c["label_rng"] = True

    os.makedirs(os.path.dirname(FINAL_OUT), exist_ok=True)
    with io.open(FINAL_OUT, "w", encoding="utf-8", newline="\n") as fh:
        out = dict(header or {"format": "oracle-align-cases/1",
                              "generated_by": "tools/expand_gen_fixtures.py"})
        out["note"] = ("items 数组即装配顺序（原版 sort_BagOrder 后）；"
                       "扩样夹具=分批驱动 gen_fixture_from_lineup --oracle 生成，"
                       "stamina 取 output/oracle/expand/data/history.db 合并库")
        out["cases"] = merged
        json.dump(out, fh, ensure_ascii=False, separators=(",", ":"))
        fh.write("\n")

    # ── 失败清单（批日志 [FAIL] 行 + 差集兜底）──────────────────────
    failures = {}
    for k in range(1, n_batches + 1):
        log_path = os.path.join(BATCH_LOG_DIR, "batch_%03d.log" % k)
        if not os.path.exists(log_path):
            continue
        for ln in io.open(log_path, encoding="utf-8", errors="replace"):
            if ln.startswith("  [FAIL] "):
                body = ln[len("  [FAIL] "):].rstrip("\n")
                cid, _, why = body.partition("：")
                failures[cid.strip()] = why.strip()
    missing = [c for c in case_ids if c not in seen]
    for cid in missing:
        failures.setdefault(cid, "未出现在任何批产物（无 [FAIL] 行，需人工查批日志）")

    # ── 收尾自检：夹具玩家 stamina vs 合并库直查（防 kickoff §6.2 假分歧）──
    fixture = {c["case_id"]: c for c in merged}
    db_hit = db_miss = stamina_bad = 0
    bad_samples = []
    for cid in case_ids:
        if cid not in fixture:
            continue
        m = RUN_RE.match(cid)
        run_id = int(m.group(1)) if m else None
        rid = int(fixture[cid]["round_id"])
        v = gfl._history_round_stamina(run_id, rid) if run_id else None
        got = float(fixture[cid]["player"]["stamina"])
        if v is None:
            db_miss += 1
            if got != float(fixture[cid]["player"]["base_max_stamina"]):
                stamina_bad += 1
                bad_samples.append((cid, "db 缺行但 stamina≠base：%r" % got))
        else:
            db_hit += 1
            if abs(got - float(v)) > 1e-9:
                stamina_bad += 1
                bad_samples.append((cid, "stamina %r ≠ 库值 %r" % (got, v)))

    with io.open(FAILURES_OUT, "w", encoding="utf-8", newline="\n") as fh:
        json.dump({"total_cases": len(case_ids), "generated": len(merged),
                   "failed": failures, "stamina_db_hit": db_hit,
                   "stamina_db_miss_fallback_base": db_miss,
                   "stamina_mismatch": stamina_bad}, fh,
                  ensure_ascii=False, indent=1)

    print("")
    print("=== 扩样夹具：%d/%d 场生成 → %s" % (len(merged), len(case_ids), FINAL_OUT))
    print("    失败 %d 场（清单+原因 → %s）" % (len(failures), FAILURES_OUT))
    print("    stamina 自检：库命中 %d / 缺行退 base %d / 数值不符 %d"
          % (db_hit, db_miss, stamina_bad))
    for cid, why in bad_samples[:10]:
        print("    [STAMINA-BAD] %s：%s" % (cid, why))
    if stamina_bad:
        print("stamina 取数链有洞（kickoff §6.2 假分歧风险）——先修再继续", file=sys.stderr)
        return 1
    return 0 if not failures else 1


if __name__ == "__main__":
    raise SystemExit(main())
