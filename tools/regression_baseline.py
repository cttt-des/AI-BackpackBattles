# -*- coding: utf-8 -*-
"""regression_baseline.py — 模拟器回归基线（固定种子，防精度回退）

用途：在改动模拟器/物品库之前采集一份「战斗结果快照」，改动之后重跑比对，
用来证明改动是否引入了非预期的行为变化。

采集内容（每对阵容一场固定种子战斗）：
  * 胜负、结束原因、战斗时长、双方剩余 HP / 伤害 / 治疗 / 暴击 / 激活次数
  * 事件流指纹（events_hash）与人类可读日志指纹（log_hash）
    —— 指纹比数值摘要更敏感，任何过程级改动都能被发现

用法：
    python tools/regression_baseline.py --save          # 采集并覆盖 latest
    python tools/regression_baseline.py --check         # 与 latest 比对
    python tools/regression_baseline.py --save --tag before_linkage
    python tools/regression_baseline.py --check --tag before_linkage
    python tools/regression_baseline.py --list          # 列出已有基线
"""
from __future__ import annotations

import argparse
import glob
import hashlib
import json
import os
import sys
import time
from datetime import datetime
from typing import Any, Dict, List, Optional

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

# Windows 控制台默认 GBK，输出含符号会 UnicodeEncodeError -> 统一 UTF-8
for _stream in (sys.stdout, sys.stderr):
    try:
        if hasattr(_stream, "reconfigure"):
            _stream.reconfigure(encoding="utf-8", errors="replace")
    except Exception:  # noqa: BLE001
        pass

ENGINES = ("simulator", "engine")   # simulator=旧内核（回归基线）, engine=新内核
DEFAULT_ENGINE = "simulator"


def _load_engine(name: str):
    """按名加载战斗内核（延迟导入，避免单进程双引擎常驻）"""
    if name == "engine":
        from engine.combat import CombatEngine      # noqa: E402
        from engine.data import load_items, load_characters   # noqa: E402
    else:
        from simulator.combat import CombatEngine   # noqa: E402
        from simulator.data import load_items, load_characters  # noqa: E402
    from simulator.lineup import load_lineup        # noqa: E402（阵容格式两引擎共用）
    return CombatEngine, load_items, load_characters, load_lineup


LINEUPS_DIR = os.path.join(ROOT, "lineups")
OUT_DIR = os.path.join(ROOT, "output", "baseline")
SEED = 42
BASE_VERSION = 1


def list_lineups() -> List[str]:
    return sorted(glob.glob(os.path.join(LINEUPS_DIR, "*.json")))


def _events_list(log, engine: str) -> List[Dict[str, Any]]:
    """统一两内核的事件视图（新内核为惰性 record 列表，无 to_dict）"""
    if engine == "engine":
        return [{"t": ev.t, "type": ev.type, "actor": ev.actor,
                 "target": ev.target} for ev in log.events]
    events = log.to_dict()
    return events if isinstance(events, list) else events.get("events", [])


def run_pair(a: str, b: str, item_db, char_db, seed: int,
             engine: str = DEFAULT_ENGINE) -> Dict[str, Any]:
    """跑一场固定种子战斗，返回可比对的结果摘要。"""
    CombatEngine, _, _, load_lineup = _load_engine(engine)
    la = load_lineup(a)
    lb = load_lineup(b)
    eng = CombatEngine(la, lb, item_db, char_db, seed=seed)
    eng.run()

    s = eng.summary()
    events = _events_list(eng.log, engine)
    # 旧内核指纹字段为 origin（保持历史基线兼容）；新内核用 target（Event.origin
    # 是物品对象引用，不进指纹）
    fld = "origin" if engine == DEFAULT_ENGINE else "target"
    events_sig = "|".join(
        f"{e.get('t')},{e.get('type')},{e.get('actor')},{e.get(fld)}"
        for e in events
    )
    if engine == "engine":
        # 新内核惰性日志：无文本渲染，文本指纹以警告流代替（进程级改动同样敏感）
        txt = "|".join(getattr(eng.log, "warnings", []))
    else:
        txt = eng.log.to_text("en")
    return {
        "player": os.path.basename(a),
        "opponent": os.path.basename(b),
        "seed": seed,
        "engine": engine,
        "winner": "player" if eng.player_wins() else "opponent",
        "reason": s.get("reason"),
        "time": round(float(s.get("time", 0.0)), 3),
        "fatigue_counter": s.get("fatigue_counter"),
        "player_hp": s["player"]["hp"],
        "opponent_hp": s["opponent"]["hp"],
        "player_damage": s["player"]["stats"]["damage_dealt"],
        "opponent_damage": s["opponent"]["stats"]["damage_dealt"],
        "player_healing": s["player"]["stats"]["healing_done"],
        "opponent_healing": s["opponent"]["stats"]["healing_done"],
        "player_crits": s["player"]["stats"]["crits"],
        "player_activations": s["player"]["stats"]["activations"],
        "num_events": len(events) if isinstance(events, list)
        else len(events.get("events", [])),
        "events_hash": hashlib.md5(events_sig.encode("utf-8")).hexdigest()[:16],
        "log_hash": hashlib.md5(txt.encode("utf-8")).hexdigest()[:16],
    }


def collect(seed: int = SEED, verbose: bool = True,
            engine: str = DEFAULT_ENGINE) -> Dict[str, Any]:
    _, load_items, load_characters, _ = _load_engine(engine)
    item_db = load_items()
    char_db = load_characters()
    files = list_lineups()
    if len(files) < 2:
        raise SystemExit(f"阵容不足：{LINEUPS_DIR} 下至少需要 2 个 JSON")

    results = []
    t0 = time.time()
    n = 0
    for i in range(len(files)):
        for j in range(len(files)):
            if i == j:
                continue
            a, b = files[i], files[j]
            try:
                r = run_pair(a, b, item_db, char_db, seed, engine=engine)
            except Exception as e:  # noqa: BLE001
                r = {"player": os.path.basename(a), "opponent": os.path.basename(b),
                     "seed": seed, "error": f"{type(e).__name__}: {e}"}
            results.append(r)
            n += 1
            if verbose and n % 10 == 0:
                print(f"  {n}/{len(files) * (len(files) - 1)} ...", flush=True)

    return {
        "version": BASE_VERSION,
        "engine": engine,
        "generated_at": datetime.now().isoformat(timespec="seconds"),
        "seed": seed,
        "lineups": [os.path.basename(f) for f in files],
        "elapsed_sec": round(time.time() - t0, 1),
        "results": results,
    }


def baseline_path(tag: str, engine: str = DEFAULT_ENGINE) -> str:
    if engine == DEFAULT_ENGINE:
        legacy = os.path.join(OUT_DIR, f"baseline_{tag}.json")
        if os.path.exists(legacy):
            return legacy          # 兼容历史旧内核基线文件名
    return os.path.join(OUT_DIR, f"baseline_{tag}__{engine}.json")


def save(tag: str, seed: int, engine: str = DEFAULT_ENGINE) -> int:
    os.makedirs(OUT_DIR, exist_ok=True)
    print(f"采集基线（seed={seed}, engine={engine}）...")
    data = collect(seed=seed, engine=engine)
    path = baseline_path(tag, engine)
    json.dump(data, open(path, "w", encoding="utf-8"),
              ensure_ascii=False, indent=1)
    ok = sum(1 for r in data["results"] if "error" not in r)
    bad = len(data["results"]) - ok
    print(f"已保存: {path}")
    print(f"  {len(data['results'])} 场（异常 {bad}）  用时 {data['elapsed_sec']}s")
    return 0


def check(tag: str, seed: int, engine: str = DEFAULT_ENGINE) -> int:
    path = baseline_path(tag, engine)
    if not os.path.exists(path):
        print(f"基线不存在: {path}")
        return 2
    base = json.load(open(path, encoding="utf-8"))
    print(f"比对基线: {path}（生成于 {base.get('generated_at')}）")
    cur = collect(seed=seed, verbose=False, engine=engine)

    def key(r):
        return (r["player"], r["opponent"])

    old = {key(r): r for r in base["results"]}
    new = {key(r): r for r in cur["results"]}

    diffs: List[Dict[str, Any]] = []
    for k, o in old.items():
        n = new.get(k)
        if n is None:
            diffs.append({"pair": k, "issue": "missing"})
            continue
        if o.get("error") or n.get("error"):
            if o.get("error") != n.get("error"):
                diffs.append({"pair": k, "issue": "error-changed",
                              "old": o.get("error"), "new": n.get("error")})
            continue
        changed = {f: (o.get(f), n.get(f)) for f in (
            "winner", "reason", "time", "player_hp", "opponent_hp",
            "player_damage", "opponent_damage", "player_healing",
            "opponent_healing", "player_crits", "player_activations",
            "num_events", "events_hash", "log_hash")
            if o.get(f) != n.get(f)}
        if changed:
            diffs.append({"pair": k, "changes": changed})

    if not diffs:
        print(f"[OK] 无差异（{len(old)} 场全部一致）")
        return 0
    print(f"[DIFF] 发现 {len(diffs)} 场存在差异：")
    for d in diffs[:40]:
        if "changes" in d:
            ch = d["changes"]
            brief = ", ".join(
                f"{f}: {v[0]}->{v[1]}" for f, v in list(ch.items())[:6])
            print(f"  {d['pair'][0]} vs {d['pair'][1]}: {brief}")
        else:
            print(f"  {d['pair'][0]} vs {d['pair'][1]}: {d['issue']}")
    # 完整差异落盘，便于逐条分析
    diff_path = os.path.join(OUT_DIR, f"diff_{tag}_{datetime.now().strftime('%Y%m%d_%H%M%S')}.json")
    json.dump(diffs, open(diff_path, "w", encoding="utf-8"),
              ensure_ascii=False, indent=1)
    print(f"完整差异: {diff_path}")
    return 1


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description="模拟器回归基线")
    ap.add_argument("--save", action="store_true", help="采集并保存基线")
    ap.add_argument("--check", action="store_true", help="与基线比对")
    ap.add_argument("--list", action="store_true", help="列出已有基线")
    ap.add_argument("--tag", default="latest", help="基线标签（默认 latest）")
    ap.add_argument("--seed", type=int, default=SEED, help=f"随机种子（默认 {SEED}）")
    ap.add_argument("--engine", choices=ENGINES, default=DEFAULT_ENGINE,
                    help="战斗内核：simulator=旧（默认/回归基线），engine=新")
    args = ap.parse_args(argv)

    if args.list:
        if not os.path.isdir(OUT_DIR):
            print("（无基线）")
            return 0
        for f in sorted(os.listdir(OUT_DIR)):
            if f.startswith("baseline_"):
                p = os.path.join(OUT_DIR, f)
                try:
                    d = json.load(open(p, encoding="utf-8"))
                    print(f"  {f}  {d.get('generated_at')}  "
                          f"{len(d.get('results', []))} 场")
                except Exception:  # noqa: BLE001
                    print(f"  {f}  (损坏)")
        return 0

    if args.check:
        return check(args.tag, args.seed, args.engine)
    if args.save:
        return save(args.tag, args.seed, args.engine)

    ap.print_help()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
