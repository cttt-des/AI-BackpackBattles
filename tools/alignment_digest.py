#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
alignment_digest.py — alignment.json 紧凑摘要（修复循环的每轮输入）

背景：output/oracle/alignment.json 含 914 场 perCase 明细（约 6.9MB），修复
代理直接读它是最大的配额黑洞（docs/alignment_fix_workflow.md 的循环设计要求
"缺口分析→修复→重验"，缺口分析应靠脚本不靠大模型啃原始 JSON）。

本脚本把 alignment.json 压成 <20KB 的 Markdown 摘要：
  * 总量与分布（aligned / match_distribution / localization 族计数）
  * 首分歧事件类型 Top15、首分歧 origin 物品 Top15（把数字型 type 翻译成名字）
  * 首分歧 index 统计（median/p25/p75/max、idx<=2 边界场计数——开战边界 2 抽族）
  * 按签名聚类：每族取 (pair, kind, index<=2, 首分歧 type+origin) 为签名，
    计数排序，输出代表案例 ID（每簇至多 5 个，总量截断）与 first_line_diff 样例
  * 已对齐场清单、fixPlan 的 goal（不含 steps 全文——步骤在 verify_oracle.py 里有）

  用法：
  python -X utf8 tools/alignment_digest.py            # 打印 + 写 output/oracle/alignment_digest.md
  python -X utf8 tools/alignment_digest.py --top 10   # 聚类/直方图取前 10
  python -X utf8 tools/alignment_digest.py --bistable output/oracle/oracle_bistable_audit.json
      # （r23 卡⑥/r24 卡⑨）oracle 复放双稳批量审计（tools/audit_oracle_bistable.py 产物）
      # 里 rerun=fail 的场=神谕自身不可复现 → 不可对齐子集：从首分歧统计/签名聚类
      # 剔除并单独计数，防不可修复场污染 Top 簇与通道分派。不给本参数=行为不变。
退出码：0 正常；1 alignment.json 缺失或损坏。
"""
from __future__ import annotations

import argparse
import io
import json
import os
import sys
from collections import Counter
from typing import Any, Dict, List, Optional, Tuple

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ALIGNMENT_JSON = os.path.join(ROOT, "output", "oracle", "alignment.json")
DIGEST_MD = os.path.join(ROOT, "output", "oracle", "alignment_digest.md")

# canonical 数字 type → 人读名（与 verify_oracle.ETYPE_TO_NUM 同源；100-110 为 buff 栈）
_TYPE_NAMES = {
    0: "Activation", 1: "DealDamage", 2: "critical", 3: "MissedAttack",
    5: "lose_health", 7: "invulnerable_start", 8: "invulnerable_end",
    9: "stun", 10: "stun_resisted", 11: "crit_resisted", 12: "Health",
    13: "stamina_gain", 14: "stamina_drain", 15: "out_of_stamina",
    16: "damage_buff", 17: "dam_reduction", 18: "dam_increase",
    19: "TemporaryMaxHealth", 20: "temporary_max_stamina",
    21: "battle_rage_start", 22: "battle_rage_end", 23: "reincarnate",
    98: "unhealing", 99: "fatigue_damage",
    100: "Block", 101: "Lucky", 102: "Regeneration", 103: "Vampirism",
    104: "Spikes", 105: "Mana", 107: "Heat", 108: "Poison", 109: "Blind",
    110: "Cold", 111: "logWin", 112: "logLoss",
}


def _tname(num: Any) -> str:
    try:
        n = int(num)
    except (TypeError, ValueError):
        return str(num)
    if n in _TYPE_NAMES:
        return "%s(%d)" % (_TYPE_NAMES[n], n)
    if 100 <= n <= 110:
        return "stack(%d)" % n
    return "type%d" % n


def _origin_name(origin: Any) -> str:
    if origin is None:
        return "-"
    if isinstance(origin, (list, tuple)):
        if origin and origin[0] == "item":
            return str(origin[1]) if len(origin) > 1 else "item"
        if origin and origin[0] == "gem":
            return "gem@%s#%s" % (origin[1] if len(origin) > 1 else "?",
                                  origin[2] if len(origin) > 2 else "?")
        if origin and origin[0] == "src":
            return "src:%s" % (origin[1] if len(origin) > 1 else "?")
        return "/".join(str(x) for x in origin)
    return str(origin)


def _fd_entry(pc: Dict[str, Any]) -> Optional[Dict[str, Any]]:
    """取 oracle_vs_gdcore 的首分歧条目（定位主轴；gdcore_vs_py 仅在纯转写场用）。

    verify_oracle.py 的 firstDivergence 有两种形状：单 pair 时是条目本身
    （含 "pair" 键），双 pair 时是 {"oracle_vs_gdcore": 条目, "gdcore_vs_py": 条目}。
    """
    fd = pc.get("firstDivergence")
    if not isinstance(fd, dict):
        return None
    if "oracle_vs_gdcore" in fd:
        return fd["oracle_vs_gdcore"]
    if "pair" in fd:
        return fd
    return None


def _fd_summary(pc: Dict[str, Any]) -> Dict[str, Any]:
    """单场首分歧摘要：pair/kind/index、oracle 侧首分歧事件 type+origin、渲染行差。"""
    out: Dict[str, Any] = {"pair": None, "kind": None, "index": None,
                           "o_type": None, "o_origin": None, "g_type": None,
                           "line_diff": None}
    entry = _fd_entry(pc)
    if entry:
        out["pair"] = entry.get("pair")
        out["kind"] = entry.get("kind")
        out["index"] = entry.get("index")
        o = (entry.get("oracle") or {}).get("at_idx") or {}
        g = (entry.get("gdcore") or {}).get("at_idx") or {}
        out["o_type"] = o.get("type")
        out["o_origin"] = _origin_name(o.get("origin"))
        out["g_type"] = g.get("type")
        fld = entry.get("first_line_diff")
        if isinstance(fld, dict):
            ol = fld.get("oracle_line")
            gl = fld.get("gdcore_line")
            if ol or gl:
                out["line_diff"] = "O:%s | G:%s" % (
                    (ol or "")[:90], (gl or "")[:90])
    elif isinstance(pc.get("firstDivergence"), dict):
        entry = pc["firstDivergence"].get("gdcore_vs_py")
        if entry:
            out["pair"] = entry.get("pair")
            out["kind"] = entry.get("kind")
            out["index"] = entry.get("index")
            g = (entry.get("gdcore") or {}).get("at_idx") or {}
            out["g_type"] = g.get("type")
            out["o_origin"] = _origin_name(g.get("origin"))
    return out


def _pct(vals: List[float], q: float) -> float:
    if not vals:
        return 0.0
    s = sorted(vals)
    i = min(len(s) - 1, max(0, int(round(q * (len(s) - 1)))))
    return s[i]


def build_digest(report: Dict[str, Any], top: int,
                 bistable_ids: Optional[frozenset] = None) -> str:
    bistable_ids = bistable_ids or frozenset()
    per_case = [r for r in report.get("perCase") or [] if "match" in r]
    aligned_ids = [r["caseId"] for r in per_case if r.get("match") == "三方一致"]
    lines: List[str] = []
    lines.append("# alignment.json 摘要（%s）" % _mtime(ALIGNMENT_JSON))
    lines.append("")
    lines.append("- aligned：**%s / %s**" % (report.get("aligned"), report.get("total")))
    lines.append("- match_distribution：%s" % json.dumps(
        report.get("match_distribution") or {}, ensure_ascii=False))
    loc_counter = Counter()
    for r in per_case:
        loc_counter[r.get("localization") or "?"] += 1
    lines.append("- localization 族计数：%s" % json.dumps(
        dict(loc_counter.most_common()), ensure_ascii=False))
    lines.append("- 已对齐场：%s" % (",".join(aligned_ids) or "（无）"))
    lines.append("")

    # ── 首分歧统计（只统计 oracle≠gdcore 的场；双稳场剔除并单独计数）──
    div_all = [(r, _fd_summary(r)) for r in per_case if r.get("match") != "三方一致"
               and (r.get("judgement") or {}).get("event_tuples", {}).get("oracle_gd") is False]
    bist_hit = sorted(r["caseId"] for r, _ in div_all if r["caseId"] in bistable_ids)
    div = [(r, f) for r, f in div_all if r["caseId"] not in bistable_ids]
    idxs = [f["index"] for _, f in div if f["index"] is not None]
    lines.append("## 首分歧统计（oracle≠gdcore 共 %d 场%s）" % (
        len(div_all), ("，其中双稳剔除 %d 场后 %d 场" % (len(bist_hit), len(div)))
        if bist_hit else ""))
    if idxs:
        idxs_sorted = sorted(idxs)
        lines.append("- 首分歧 index：median=%d p25=%d p75=%d max=%d；idx<=2（开战边界）%d 场、"
                     "idx<=9 %d 场、idx<=19 %d 场" % (
                         int(_pct([float(i) for i in idxs], 0.5)),
                         int(_pct([float(i) for i in idxs], 0.25)),
                         int(_pct([float(i) for i in idxs], 0.75)),
                         idxs_sorted[-1],
                         sum(1 for i in idxs if i <= 2),
                         sum(1 for i in idxs if i <= 9),
                         sum(1 for i in idxs if i <= 19)))
    type_hist = Counter(_tname(f["o_type"]) for _, f in div if f["o_type"] is not None)
    origin_hist = Counter(f["o_origin"] for _, f in div if f["o_origin"])
    lines.append("- 首分歧事件类型 Top%d：%s" % (top, ", ".join(
        "%s×%d" % (k, v) for k, v in type_hist.most_common(top))))
    lines.append("- 首分歧 origin Top%d：%s" % (top, ", ".join(
        "%s×%d" % (k, v) for k, v in origin_hist.most_common(top))))
    if bist_hit:
        lines.append("- **oracle 复放双稳（rerun=fail，不可对齐，已剔除）%d 场**：%s"
                     % (len(bist_hit), ",".join(bist_hit[:20]) +
                        ("…" if len(bist_hit) > 20 else "")))
    lines.append("")

    # ── 签名聚类：同签名场归一簇，给出代表案例与渲染行差样例 ──
    clusters: Dict[Tuple, List[Tuple[str, Dict[str, Any]]]] = {}
    for r, f in div:
        sig = (f["pair"], f["kind"], f["index"] is not None and f["index"] <= 2,
               _tname(f["o_type"]), f["o_origin"])
        clusters.setdefault(sig, []).append((r["caseId"], f))
    lines.append("## 签名聚类（按 (pair, kind, idx<=2, type, origin)；每簇代表 ≤5 场）")
    for sig, members in sorted(clusters.items(), key=lambda kv: -len(kv[1]))[:top]:
        rep = [cid for cid, _ in members[:5]]
        line_diff = next((f["line_diff"] for _, f in members if f["line_diff"]), None)
        lines.append("- **%d 场** pair=%s kind=%s idx<=2=%s type=%s origin=%s"
                     % (len(members), sig[0], sig[1], sig[2], sig[3], sig[4]))
        lines.append("  - 代表：%s" % ",".join(rep))
        if line_diff:
            lines.append("  - 行差样例：%s" % line_diff)
    lines.append("")

    # ── 纯转写场（gdcore≡oracle 但 py 分歧）单独列 ──
    trans = [r for r in per_case if r.get("localization") == "gd_core_py-transpiler"]
    if trans:
        lines.append("## 纯转写场（gdcore≡oracle、py 分歧）%d 场：%s" % (
            len(trans), ",".join(r["caseId"] for r in trans[:20])))
        lines.append("")

    # ── fixPlan 目标行 ──
    lines.append("## fixPlan 目标")
    for p in report.get("fixPlan") or []:
        lines.append("- [%s] %d 场：%s" % (p.get("category"), p.get("case_count"),
                                          p.get("goal")))
    lines.append("")
    return "\n".join(lines) + "\n"


def _mtime(path: str) -> str:
    try:
        import datetime
        t = os.path.getmtime(path)
        return datetime.datetime.fromtimestamp(t).strftime("%Y-%m-%d %H:%M")
    except OSError:
        return "时间未知"


def main() -> int:
    ap = argparse.ArgumentParser(description="alignment.json → 紧凑 Markdown 摘要")
    ap.add_argument("--top", type=int, default=15, help="直方图/聚类取前 N（默认 15）")
    ap.add_argument("--out", default=DIGEST_MD, help="摘要输出路径（空串=只打印）")
    ap.add_argument("--bistable", default="",
                    help="oracle 双稳审计 JSON（tools/audit_oracle_bistable.py 产物）："
                         "rerun=fail 场从统计/聚类剔除并单独计数")
    args = ap.parse_args()

    bistable_ids: frozenset = frozenset()
    if args.bistable:
        try:
            audit = json.load(io.open(args.bistable, encoding="utf-8"))
            bistable_ids = frozenset(audit.get("bistable") or [])
        except Exception as exc:  # noqa: BLE001 —— 审计文件损坏如实报错退出
            print("--bistable 解析失败：%s: %s" % (type(exc).__name__, exc),
                  file=sys.stderr)
            return 1

    if not os.path.exists(ALIGNMENT_JSON):
        print("找不到 %s（先跑 tools/verify_oracle.py）" % ALIGNMENT_JSON, file=sys.stderr)
        return 1
    try:
        report = json.load(io.open(ALIGNMENT_JSON, encoding="utf-8"))
    except Exception as exc:  # noqa: BLE001 —— 损坏如实报错退出
        print("alignment.json 解析失败：%s: %s" % (type(exc).__name__, exc),
              file=sys.stderr)
        return 1

    digest = build_digest(report, args.top, bistable_ids)
    sys.stdout.write(digest)
    if args.out:
        os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)
        with io.open(args.out, "w", encoding="utf-8", newline="\n") as fh:
            fh.write(digest)
        size_kb = os.path.getsize(args.out) / 1024.0
        print("[digest] %s（%.1f KB）" % (args.out, size_kb), file=sys.stderr)
        if size_kb > 40:
            print("[digest] 警告：摘要超 40KB，考虑减小 --top", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())