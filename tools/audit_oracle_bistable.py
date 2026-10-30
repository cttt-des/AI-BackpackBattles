#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
audit_oracle_bistable.py — oracle 复放双稳批量审计（alignment_fix_log r23 卡⑥/r24 卡⑨）

背景：r23 仪器级定谳——oracle 探针复放自身双稳（run702 同进程 run1=语料轨迹、
run2=gd 轨迹；run688 语料-vs-探针仅 222/939）。此类场神谕自身不可复现，属
**不可对齐子集**：任何 gd_core 修复都无法把一个双稳基准对齐，混进 Top 簇会
污染聚类与通道分派。本工具把 r23 的单场人工复跑扩成批量：

  对每场调用一次 oracle harness（oracle_fight.gd），harness 自带「紧邻同种子
  复跑」闸（oracle_fight.gd:337-341 / determinism_check:1068-1108）：cases[0]
  跑完后立即同种子复跑一遍，run1 留档 events_first.json、run2 覆写 events.json，
  逐字节比对。即 1 次进程 = 2 跑/场（≈40s，r23 实测口径）。

判定（每场两条独立信号，JSON 全保留）：
  rerun        run1(events_first.json) vs run2(events.json) 逐字节+逐事件比对
               fail → **双稳**（神谕同进程同种子两跑不一致）→ 不可对齐子集
  corpus_vs_r1 冻结语料 events.json vs run1 —— 识别「语料是抖动实现之一」
               （r23 run688：语料≠当前进程轨迹）

产物：
  output/oracle/oracle_bistable_audit.json  逐场结论（含首分歧事件 idx/预览）
  output/oracle/oracle_bistable_ids.txt     rerun=fail 的 caseId 清单（每行一个）
  （--ids-out/--out 可改；后者供 tools/alignment_digest.py --bistable 消费，
    把双稳场从 Top 簇/首分歧统计中剔除，防不可对齐场污染修复分派）

用法：
  python -X utf8 tools/audit_oracle_bistable.py --dry-run        # 只列出将审计的场
  python -X utf8 tools/audit_oracle_bistable.py --limit 20       # 前 20 场
  python -X utf8 tools/audit_oracle_bistable.py --cases run702_r18,run688_r10
  python -X utf8 tools/audit_oracle_bistable.py                  # 默认=alignment.json 全部未对齐场
  python -X utf8 tools/audit_oracle_bistable.py --all            # 全部 914 场
  python -X utf8 tools/audit_oracle_bistable.py --resume         # 跳过已有结论的场续跑
  python -X utf8 tools/audit_oracle_bistable.py --from-probe <dir> [--corpus]
                 # 不跑 Godot：只对已有探针产物目录做 run1-vs-run2（可加 --corpus 比语料）

注意：本工具**只写探针重定向目录**（ORACLE_FIGHTS_ROOT），冻结语料
output/oracle/fights/ 只读、从不触碰（oracle_fight.gd:373-379 同约定）。
"""
from __future__ import annotations

import argparse
import io
import json
import os
import subprocess
import sys
from typing import Any, Dict, List, Optional

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FIGHTS_DIR = os.path.join(ROOT, "output", "oracle", "fights")
ALIGNMENT_JSON = os.path.join(ROOT, "output", "oracle", "alignment.json")
DEFAULT_PROBE_ROOT = os.path.join(ROOT, "output", "oracle", "probe", "bist_audit")
DEFAULT_OUT = os.path.join(ROOT, "output", "oracle", "oracle_bistable_audit.json")
DEFAULT_IDS = os.path.join(ROOT, "output", "oracle", "oracle_bistable_ids.txt")
GODOT = os.path.join(ROOT, "output", "godot36", "Godot_v3.6-stable_win64.exe")
ORACLE_PROJECT = os.path.join(ROOT, "oracle")

# harness 判定行（oracle_fight.gd determinism_check 的 say() 文案）
VERDICT_PASS = "同种子复跑事件流逐字节一致"
VERDICT_FAIL = "[FAIL] 同种子复跑不一致"


def cases_from_alignment(all_cases: bool) -> List[str]:
    """默认=alignment.json 未对齐场（match != 三方一致）；--all=全部场。"""
    data = json.load(io.open(ALIGNMENT_JSON, encoding="utf-8"))
    out = []
    for r in data.get("perCase") or []:
        if "match" not in r:
            continue
        if all_cases or r.get("match") != "三方一致":
            out.append(r["caseId"])
    return out


def corpus_exists(case_id: str) -> bool:
    return os.path.getsize(os.path.join(FIGHTS_DIR, case_id, "events.json")) > 0 \
        if os.path.exists(os.path.join(FIGHTS_DIR, case_id, "events.json")) else False


def _events_of(path: str) -> Optional[List[Dict[str, Any]]]:
    try:
        data = json.load(io.open(path, encoding="utf-8"))
    except Exception:  # noqa: BLE001 —— 探针产物残缺如实返回 None
        return None
    ev = data.get("events")
    return ev if isinstance(ev, list) else None


def _first_diff(a: List[Any], b: List[Any]) -> Dict[str, Any]:
    n = min(len(a), len(b))
    for i in range(n):
        if a[i] != b[i]:
            return {"kind": "event", "index": i,
                    "r1": json.dumps(a[i], ensure_ascii=False)[:220],
                    "r2": json.dumps(b[i], ensure_ascii=False)[:220]}
    if len(a) != len(b):
        return {"kind": "length", "index": None,
                "detail": "r1=%d r2=%d" % (len(a), len(b))}
    return {"kind": None, "index": None}


def run_harness_once(case_id: str, probe_root: str, timeout: float) -> Dict[str, Any]:
    """一次 harness 进程：ORACLE_ONLY_CASES 单场 + ORACLE_FIGHTS_ROOT 重定向。
    harness 对 cases[0] 自动做紧邻同种子复跑（1 进程=2 跑）。"""
    case_probe_dir = os.path.join(probe_root, case_id)
    os.makedirs(case_probe_dir, exist_ok=True)
    # ★ 2026-10-30：改走 tools/godot_headless（--no-window 而非 --headless）。
    #   Godot 3.6 没有 --headless，写了会走窗口路径出真窗口、还招搜狗 IME
    #   弹 "OpenMem failed" 模态框；同时本沙箱禁匿名管道，capture_output 会
    #   CreatePipe 失败（WinError 5），故输出重定向到文件再读回。
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import godot_headless as gh
    cmd = gh.cmd(project="oracle", script="oracle_fight.gd")
    p, _lp, _fh = gh.spawn(cmd, label="bistable_%s" % case_id, tag="bistable",
                           env_extra={"ORACLE_FIGHTS_ROOT": probe_root,
                                      "ORACLE_ONLY_CASES": case_id})
    try:
        rc = p.wait(timeout=timeout)
    except subprocess.TimeoutExpired:
        p.kill()
        p.wait()
        _fh.close()
        raise
    finally:
        try:
            _fh.close()
        except OSError:
            pass
    stdout = gh.read_log(_lp)
    # 判定行可能带全角✓/场 id，宽松匹配
    verdict = "pass" if (VERDICT_PASS in stdout) else \
        ("fail" if VERDICT_FAIL in stdout else "no-verdict")
    log_path = os.path.join(case_probe_dir, "_harness_stdout.log")
    with io.open(log_path, "w", encoding="utf-8", newline="\n") as fh:
        fh.write(stdout)  # 已含 stderr（重定向合并），无需再追加
    return {"verdict_line": verdict, "exit": rc, "log": log_path}


def audit_case(case_id: str, probe_root: str) -> Dict[str, Any]:
    """单场审计：harness 2 跑 + 语料比对。绝不写冻结语料目录。"""
    res: Dict[str, Any] = {"caseId": case_id}
    d = os.path.join(probe_root, case_id)
    r1p = os.path.join(d, "events_first.json")
    r2p = os.path.join(d, "events.json")
    corp = os.path.join(FIGHTS_DIR, case_id, "events.json")
    had = os.path.exists(r1p) and os.path.exists(r2p)
    try:
        run = run_harness_once(case_id, probe_root, timeout=600.0)
    except subprocess.TimeoutExpired:
        res.update(rerun="timeout", note="harness 600s 超时（见 %s）" % d)
        return res
    res["harness"] = {"exit": run["exit"], "verdict_line": run["verdict_line"]}
    # run1-vs-run2：以文件字节序为主判（verdict_line 仅旁证；两者不一致时如实记）
    r1, r2 = _events_of(r1p), _events_of(r2p)
    if r1 is None or r2 is None:
        res.update(rerun="no-verdict", note="探针产物缺 events_first/events.json（%s）" % d)
        return res
    if run["verdict_line"] == "fail" or json.dumps(r1) != json.dumps(r2):
        res["rerun"] = "fail"
        res["first_diverge"] = _first_diff(r1, r2)
    else:
        res["rerun"] = "pass"
    # corpus vs run1（run2 旁证一并记录）
    if corpus_exists(case_id):
        c = _events_of(corp)
        res["corpus_vs_r1"] = "match" if c == r1 else "mismatch"
        res["corpus_vs_r2"] = "match" if c == r2 else "mismatch"
        if res["corpus_vs_r1"] == "mismatch" and c is not None:
            res["corpus_diverge"] = _first_diff(c, r1)
        res["corpus_events"] = len(c) if c is not None else None
    res["r1_events"], res["r2_events"] = len(r1), len(r2)
    if not had:
        res["note"] = "首次审计（此前无探针产物）"
    return res


def audit_from_probe(case_id: str, probe_root: str, with_corpus: bool) -> Dict[str, Any]:
    """--from-probe：不跑 Godot，只比对既有探针产物。"""
    res: Dict[str, Any] = {"caseId": case_id, "mode": "from-probe"}
    d = os.path.join(probe_root, case_id)
    r1, r2 = _events_of(os.path.join(d, "events_first.json")), \
        _events_of(os.path.join(d, "events.json"))
    if r1 is None or r2 is None:
        res.update(rerun="no-verdict", note="缺探针产物（%s 下需 events_first.json+events.json）" % d)
        return res
    if json.dumps(r1) != json.dumps(r2):
        res.update(rerun="fail")
        res["first_diverge"] = _first_diff(r1, r2)
    else:
        res.update(rerun="pass")
    res["r1_events"], res["r2_events"] = len(r1), len(r2)
    if with_corpus and corpus_exists(case_id):
        c = _events_of(os.path.join(FIGHTS_DIR, case_id, "events.json"))
        res["corpus_vs_r1"] = "match" if c == r1 else "mismatch"
        res["corpus_vs_r2"] = "match" if c == r2 else "mismatch"
    return res


def main() -> int:
    ap = argparse.ArgumentParser(description="oracle 复放双稳批量审计（2 跑/场，筛不可对齐子集）")
    ap.add_argument("--cases", default="", help="逗号分隔 case_id（默认=alignment.json 未对齐场）")
    ap.add_argument("--all", action="store_true", help="审计全部场（默认只审未对齐场）")
    ap.add_argument("--limit", type=int, default=0, help="只跑前 N 场（0=不限）")
    ap.add_argument("--probe-root", default=DEFAULT_PROBE_ROOT,
                    help="探针重定向目录（冻结语料只读，绝不写入）")
    ap.add_argument("--out", default=DEFAULT_OUT, help="审计 JSON 输出")
    ap.add_argument("--ids-out", default=DEFAULT_IDS, help="双稳场 caseId 清单输出")
    ap.add_argument("--resume", action="store_true", help="跳过 --out 里已有 rerun 结论的场")
    ap.add_argument("--dry-run", action="store_true", help="只列出将审计的场，不跑 Godot")
    ap.add_argument("--from-probe", dest="from_probe", default="",
                    help="不跑 Godot：对指定探针根目录下的既有产物做审计")
    ap.add_argument("--corpus", action="store_true", help="--from-probe 时附加语料比对")
    args = ap.parse_args()

    if args.cases:
        ids = [c.strip() for c in args.cases.split(",") if c.strip()]
    else:
        if not os.path.exists(ALIGNMENT_JSON):
            print("找不到 %s（先跑 tools/verify_oracle.py）" % ALIGNMENT_JSON, file=sys.stderr)
            return 2
        ids = cases_from_alignment(args.all)
    if args.limit > 0:
        ids = ids[:args.limit]
    if not args.from_probe:
        # 只有真跑 harness 才要求冻结语料在场（--from-probe 只比既有探针产物，
        # 语料可有可无——_selftest 等合成场名也需要能过）
        missing = [c for c in ids if not corpus_exists(c)]
        if missing:
            print("缺冻结语料 events.json（跳过）：%s" % ",".join(missing), file=sys.stderr)
            ids = [c for c in ids if c not in set(missing)]
    if not ids:
        print("无场可审计", file=sys.stderr)
        return 2

    prev: Dict[str, Any] = {}
    if args.resume and os.path.exists(args.out):
        try:
            prev = json.load(io.open(args.out, encoding="utf-8")).get("perCase") or {}
        except Exception:  # noqa: BLE001 —— 损坏则从零开始
            prev = {}
    todo = [c for c in ids if not (args.resume and isinstance(prev.get(c), dict)
                                   and prev[c].get("rerun") in ("pass", "fail"))]
    if args.dry_run:
        print("[dry-run] 将审计 %d 场（探针根 %s）：%s" % (
            len(todo), args.probe_root, ",".join(todo[:20]) + ("…" if len(todo) > 20 else "")))
        return 0
    if args.from_probe:
        per = {c: audit_from_probe(c, args.from_probe, args.corpus) for c in todo}
    else:
        if not os.path.exists(GODOT):
            print("找不到 Godot：%s" % GODOT, file=sys.stderr)
            return 2
        os.makedirs(args.probe_root, exist_ok=True)  # 探针重定向目录（可写）
        per = dict(prev)
        for i, c in enumerate(todo, 1):
            r = audit_case(c, args.probe_root)
            per[c] = r
            print("  [%d/%d] %s rerun=%s%s" % (
                i, len(todo), c, r.get("rerun"),
                (" corpus_vs_r1=%s" % r["corpus_vs_r1"]) if "corpus_vs_r1" in r else ""))
            if i % 10 == 0:
                _flush(args.out, args.ids_out, per, ids)
    _flush(args.out, args.ids_out, per, ids)
    fails = sorted(c for c, r in per.items() if isinstance(r, dict) and r.get("rerun") == "fail")
    print("=== 双稳审计：%d 场有结论，rerun=fail（不可对齐子集）%d 场%s" % (
        sum(1 for r in per.values() if isinstance(r, dict) and r.get("rerun") in ("pass", "fail")),
        len(fails), "：%s" % ",".join(fails[:15]) + ("…" if len(fails) > 15 else "") if fails else ""))
    print("audit JSON → %s\n双稳清单 → %s（供 alignment_digest.py --bistable 消费）" % (
        args.out, args.ids_out))
    return 0


def _flush(out_path: str, ids_path: str, per: Dict[str, Any], order: List[str]) -> None:
    os.makedirs(os.path.dirname(os.path.abspath(out_path)), exist_ok=True)
    fails = sorted(c for c, r in per.items() if isinstance(r, dict) and r.get("rerun") == "fail")
    payload = {
        "tool": "audit_oracle_bistable.py",
        "judgement": "rerun=fail → 神谕同种子两跑不一致（双稳）→ 不可对齐子集；"
                     "corpus_vs_r1=mismatch → 语料是抖动实现之一（r23 run688 口径）",
        "audited": sum(1 for r in per.values() if isinstance(r, dict)
                       and r.get("rerun") in ("pass", "fail")),
        "bistable_count": len(fails),
        "bistable": fails,
        "perCase": per,
    }
    with io.open(out_path, "w", encoding="utf-8", newline="\n") as fh:
        json.dump(payload, fh, ensure_ascii=False, indent=1)
        fh.write("\n")
    with io.open(ids_path, "w", encoding="utf-8", newline="\n") as fh:
        for c in sorted(order):
            if c in set(fails):
                fh.write(c + "\n")


if __name__ == "__main__":
    raise SystemExit(main())
