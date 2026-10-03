# -*- coding: utf-8 -*-
"""
一致性差分 v1：真值机 JSONL ↔ engine/ JSONL（docs/consistency_interface.md）。

v1 比对范围：配置对齐检查（ALIGNMENT）+ 结局（胜负/血量/时长）+ DealDamage 序列。
用法：
  python tools/consistency_diff.py <truth.jsonl> <engine.jsonl> [-o 报告前缀]
输出：<前缀>.diff.json 与 <前缀>.diff.md（默认打印到 stdout）。
"""
import argparse
import json
import re
import sys
from pathlib import Path

# 真值 EventType（Game.gd:443）→ 语义名（仅 v1 用到的子集）
EV = {0: "Activation", 1: "DealDamage", 2: "CriticalDamage", 3: "MissedAttack",
      4: "TakeDamage", 5: "LoseHealth", 12: "Health", 13: "Stamina",
      15: "OutOfStamina", 99: "Fatigue", 100: "Block", 101: "Lucky"}


def parse_truth(path):
    lines = Path(path).read_text(encoding="utf-8").splitlines()
    meta = json.loads(lines[0])
    events, result = [], {}
    for l in lines[1:]:
        d = json.loads(l)
        if "_result" in d:
            result = d["_result"]
            continue
        t = int(d.get("type", -1))
        params = d.get("params", "")
        m = re.search(r"damage:(\d+)", str(params))
        damage = int(m.group(1)) if m else None
        events.append({
            "t": float(d.get("timestamp", 0)),
            "type": EV.get(t, str(t)),
            "origin": re.sub(r":\[[^]]+\]", "", str(d.get("origin", ""))),
            "damage": damage,
        })
    meta["_result"] = result
    return meta, events


def parse_engine(path):
    lines = Path(path).read_text(encoding="utf-8").splitlines()
    meta = json.loads(lines[0])
    events = [json.loads(l) for l in lines[1:]]
    return meta, events


def alignment(truth_meta, eng_meta):
    """对齐检查：返回问题列表（空=对齐）。"""
    issues = []
    for k in ("fight_seed", "round"):
        if truth_meta.get(k) != eng_meta.get(k):
            issues.append(f"{k}: 真值={truth_meta.get(k)} 引擎={eng_meta.get(k)}")
    for side in ("p_items", "o_items"):
        a, b = truth_meta.get(side, []), eng_meta.get(side, [])
        if len(a) != len(b):
            issues.append(f"{side} 数量: {len(a)} vs {len(b)}")
            continue
        for x, y in zip(a, b):
            for f in ("name", "row", "col"):
                if x.get(f) != y.get(f):
                    issues.append(f"{side} {x.get('name')}: {f} {x.get(f)} vs {y.get(f)}")
    ch_t = truth_meta.get("character")
    ch_e = eng_meta.get("character")
    if ch_t and ch_e and ch_t != ch_e:
        issues.append(f"character: {ch_t} vs {ch_e}")
    return issues


def damage_sequence(events, side_suffix=None):
    """提取 (t, source, damage) 序列；side_suffix 过滤 '_PLAYER'/'_OPPONENT'。"""
    out = []
    for e in events:
        if e["type"] in ("DealDamage", "CriticalDamage"):
            src = e["origin"]
            if side_suffix and not src.endswith(side_suffix):
                continue
            out.append((round(e["t"], 2), src, e["damage"]))
        elif e.get("type") == "attack" and not e.get("params", {}).get("missed"):
            out.append((round(e["t"], 2), e.get("actor"), e.get("params", {}).get("damage")))
    return out


def seq_diff(a, b, tol=0.06):
    """两段序列对齐比较：值不同或时间超差记一条。返回差异列表。"""
    diffs = []
    for i, (x, y) in enumerate(zip(a, b)):
        if x[2] != y[2] or abs(x[0] - y[0]) > tol:
            diffs.append({"i": i, "truth": x, "engine": y})
    if len(a) != len(b):
        diffs.append({"len": (len(a), len(b))})
    return diffs


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("truth")
    ap.add_argument("engine")
    ap.add_argument("-o", "--out", default=None)
    args = ap.parse_args()

    tm, te = parse_truth(args.truth)
    em, ee = parse_engine(args.engine)

    report = {"alignment": alignment(tm, em), "outcome": {}, "damage_seq": {}}
    report["outcome"] = {
        "truth": tm.get("_result", {}),
        "engine": em.get("result", {}),
    }
    report["damage_seq"]["all"] = seq_diff(damage_sequence(te), damage_sequence(ee))

    ok = not report["alignment"] and not report["damage_seq"]["all"]
    md = ["# 一致性差分报告 v1", "",
          f"- 真值: {args.truth}", f"- 引擎: {args.engine}", "",
          f"**结论: {'PASS' if ok else 'FAIL'}**", "",
          "## 对齐检查"]
    md += [f"- ❌ {x}" for x in report["alignment"]] or ["- ✅ 对齐"]
    md += ["", "## 结局",
           f"- 真值: {json.dumps(report['outcome']['truth'], ensure_ascii=False)}",
           f"- 引擎: {json.dumps(report['outcome']['engine'], ensure_ascii=False)}"]
    md += ["", "## 伤害序列差异"]
    if report["damage_seq"]["all"]:
        md += [f"- {json.dumps(d, ensure_ascii=False)}" for d in report["damage_seq"]["all"][:20]]
    else:
        md.append("- ✅ DealDamage 序列一致")

    text = "\n".join(md)
    if args.out:
        Path(args.out + ".diff.md").write_text(text, encoding="utf-8")
        Path(args.out + ".diff.json").write_text(
            json.dumps(report, ensure_ascii=False, indent=1), encoding="utf-8")
        print(f"报告已写出: {args.out}.diff.md / .json")
    else:
        print(text)
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
