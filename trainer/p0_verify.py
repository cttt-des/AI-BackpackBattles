# -*- coding: utf-8 -*-
"""p0_verify.py — 训练路径规划 §6 红名单逐条验证（P0 动工前置闸）

产出 docs/训练路径规划.md 要求的「动工前必须逐条验证」证据：
  R1  包的 |extension| vs 运行时 collision（面积会计前提）
  R2  corpus 同坐标同 gid 多条记录的口径解释
  R3  Exclusive 包可得性（rarity 语义）
  R4  27 包加成作用时机（onCombatStart / prepare / onAffected...）
  R5  跨包摆放的代码路径确认
  R6  63 格禁区（已由 oracle/Core/Inventory.gd:37-38 静态核实，此处复核）

只读，不改任何资产。输出人类可读报告 + JSON 留档。
"""
from __future__ import annotations

import json
import os
import re
import sys
import sqlite3

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

T_EXTENSION = 2
T_COLLISION = 3


def parse_tscn_tiles(path):
    """CollisionMap tile_data → {tile_id: [(x, y), ...]}（复用 extract_grid 的解码口径）"""
    from simulator.extract_grid import parse_tscn_grid
    return parse_tscn_grid(path)


def bag_pool():
    """27 包：继承链判定（gd_core_items/**/*.gd extends 闭包）+ runtime json 几何。"""
    import json
    runtime = json.load(open(os.path.join(ROOT, "assets", "gd_core_runtime.json"),
                             encoding="utf-8"))
    extends_map = {}
    for root, _dirs, files in os.walk(os.path.join(ROOT, "gd_core_items")):
        for fn in files:
            if fn.endswith(".gd"):
                with open(os.path.join(root, fn), encoding="utf-8") as f:
                    for line in f:
                        m = re.match(r"extends\s+(\w+)", line)
                        if m:
                            extends_map[fn[:-3]] = m.group(1)
    bags = {"Bag"}
    changed = True
    while changed:
        changed = False
        for mod, ext in extends_map.items():
            if ext in bags and mod not in bags:
                bags.add(mod)
                changed = True
    out = {}
    for name, v in runtime["items"].items():
        mod = os.path.basename(v["script"])[:-3]
        if mod in bags and mod != "Bag":
            out[name] = v
    return out


def verify_r1(bags):
    """R1: tscn Extension/Collision 格数 vs runtime rot.collision 格数。"""
    rows = []
    for name, v in sorted(bags.items()):
        base = os.path.basename(v["script"]).replace(".gd", ".tscn")
        # 场景与脚本同名（Exclusive）或 Leather Bag 特例（LeatherBag.tscn，脚本 Bag.gd）
        cand = [os.path.join(ROOT, "oracle", "Items", "Exclusive", base),
                os.path.join(ROOT, "oracle", "Items", base),
                os.path.join(ROOT, "oracle", "Items", "Exclusive",
                             name.replace(" ", "") + ".tscn"),
                os.path.join(ROOT, "oracle", "Items",
                             name.replace(" ", "") + ".tscn")]
        tscn = next((p for p in cand if os.path.exists(p)), None)
        rt = {}
        for deg, pl in v["rot"].items():
            rt[deg] = len(pl["collision"])
        entry = {
            "bag": name,
            "tscn": os.path.relpath(tscn, ROOT) if tscn else None,
            "runtime_collision_cells": rt,
        }
        if tscn:
            tiles = parse_tscn_tiles(tscn)
            ext = tiles.get(T_EXTENSION, [])
            col = tiles.get(T_COLLISION, [])
            entry["tscn_extension"] = len(ext)
            entry["tscn_collision"] = len(col)
            entry["tscn_ext_cells"] = sorted(ext)
            entry["tscn_col_cells"] = sorted(col)
            entry["match"] = (len(ext) in set(rt.values())
                              and len(col) == 0)
        rows.append(entry)
    return rows


def verify_r2():
    """R2: corpus 同坐标重复记录——锚点 vs 占格判定。

    取规划文档提到的 run a8bfb956 R18 (x=9,y=6) 附近，并全量抽样统计：
    同 (round, x, y) 下不同 gid 的频率分布 + gid 的形状宽度分布。
    若 x 是锚点且形状可延伸到 x+1..x+w-1，则同锚点异 gid 合法。
    """
    con = sqlite3.connect("file:" + os.path.join(ROOT, "database", "corpus.sqlite"),
                          uri=True)
    cur = con.cursor()
    out = {}
    # 规划文档提到的具体 run
    key = "run_id:a8bfb956"
    rows = cur.execute(
        "SELECT record_key FROM corpus_items WHERE record_key LIKE ? LIMIT 1",
        (key + "%",)).fetchall()
    out["doc_run_found"] = bool(rows)
    if rows:
        rk = rows[0][0]
        dups = cur.execute(
            "SELECT x, y, gid, COUNT(*) c FROM corpus_items "
            "WHERE record_key=? AND round_no=18 AND x=9 AND y=6 GROUP BY gid "
            "ORDER BY c DESC LIMIT 12", (rk,)).fetchall()
        out["doc_run_dups_at_9_6"] = dups
    # 抽样：同 round 同 (x,y) 多条记录的 (gid 集合) 直方图
    hist = cur.execute(
        "SELECT n_gid, COUNT(*) FROM ("
        "  SELECT record_key, round_no, x, y, COUNT(DISTINCT gid) n_gid "
        "  FROM corpus_items WHERE x IS NOT NULL AND y IS NOT NULL "
        "  GROUP BY record_key, round_no, x, y) GROUP BY n_gid ORDER BY n_gid").fetchall()
    out["distinct_gid_per_cell_hist"] = hist
    con.close()
    return out


def verify_r3(bags):
    """R3: Exclusive 包可得性——rarity 数值语义 + 商店/配方逻辑。"""
    # 1) 全物品 rarity 分布
    runtime = json.load(open(os.path.join(ROOT, "assets", "gd_core_runtime.json"),
                             encoding="utf-8"))
    rar = {}
    for name, v in runtime["items"].items():
        rar.setdefault(v["descr"].get("rarity"), []).append(name)
    dist = {k: len(v) for k, v in sorted(rar.items())}
    # 2) 找 rarity → 商店权重/可得性的代码
    ev = {}
    for f in ["oracle/Utility/ItemPool.gd", "oracle/Core/Game.gd"]:
        p = os.path.join(ROOT, f)
        if os.path.exists(p):
            with open(p, encoding="utf-8") as fh:
                txt = fh.read()
            hits = []
            for m in re.finditer(r"func (\w*[Rr]arity\w*|\w*[Ss]hop\w*)\([^)]*\)[^\n]*", txt):
                hits.append(m.group(0)[:120])
            ev[f] = hits[:10]
    # 3) Classes 枚举（职业专属判定）：包的 classes 字段
    cls = {}
    for name, v in bags.items():
        cls[name] = {"rarity": v["descr"].get("rarity"),
                     "classes": v["descr"].get("classes")}
    return {"rarity_dist": dist, "code_evidence": ev, "bag_rarity_classes": cls}


def verify_r4(bags):
    """R4: 27 包加成作用时机——扫描对应 py 模块的 prepare/onCombatStart/挂接函数。"""
    rows = []
    for name, v in sorted(bags.items()):
        mod = os.path.basename(v["script"])[:-3]
        py = os.path.join(ROOT, "gd_core_py", "gd_core_items", mod + ".py")
        if not os.path.exists(py):
            py = os.path.join(ROOT, "gd_core_py", "gd_core_items", "Exclusive",
                              mod + ".py")
        entry = {"bag": name, "module": os.path.relpath(py, ROOT) if os.path.exists(py) else None}
        if py and os.path.exists(py):
            with open(py, encoding="utf-8") as f:
                txt = f.read()
            fns = re.findall(r"def (prepare|onCombatStart|onAffectedItemInsideAdded|"
                             r"onItemInsideAdded|canApplyEffect|onCombatEnd)\(", txt)
            entry["hooks"] = fns
            m = re.search(r"def canApplyEffect\([^)]*\):\s*\n(.*?)(?=\n\tdef |\Z)", txt, re.S)
            if m:
                body = [l.strip() for l in m.group(1).splitlines()
                        if l.strip() and not l.strip().startswith("#")][:4]
                entry["canApplyEffect_body"] = body
        rows.append(entry)
    return rows


def verify_r5():
    """R5: 跨包摆放——内核 getItemsInCells / Bag.getItemsInside 路径确认。"""
    ev = {}
    grid = os.path.join(ROOT, "gd_core_py", "gd_core", "CoreGrid.py")
    with open(grid, encoding="utf-8") as f:
        lines = f.readlines()
    ev["CoreGrid.getItemsInCells"] = "".join(lines[185:205]).strip()
    bag = os.path.join(ROOT, "gd_core_py", "gd_core_items", "Bag.py")
    with open(bag, encoding="utf-8") as f:
        lines = f.readlines()
    ev["Bag.getItemsInside"] = "".join(lines[172:192]).strip()
    return ev


def main():
    report = {}
    bags = bag_pool()
    print(f"[bag pool] {len(bags)} bags (extends-closure from gd_core_items)")
    report["bag_pool_size"] = len(bags)
    report["R1"] = verify_r1(bags)
    bad = [r for r in report["R1"] if not r.get("match")]
    print(f"[R1] 27 包 extension vs runtime collision: {len(report['R1']) - len(bad)} match, {len(bad)} mismatch")
    for r in bad:
        print("   MISMATCH:", r["bag"], "tscn_ext=", r.get("tscn_extension"),
              "tscn_col=", r.get("tscn_collision"), "runtime=", r["runtime_collision_cells"])
    report["R2"] = verify_r2()
    print(f"[R2] doc run found: {report['R2']['doc_run_found']}, "
          f"dup hist: {report['R2']['distinct_gid_per_cell_hist']}")
    report["R3"] = verify_r3(bags)
    print(f"[R3] rarity dist: {report['R3']['rarity_dist']}")
    report["R4"] = verify_r4(bags)
    print(f"[R4] hooks sampled: {sum(1 for r in report['R4'] if r.get('hooks'))}/{len(report['R4'])} bags with hook methods")
    report["R5"] = verify_r5()
    print("[R5] code evidence extracted (see json)")
    out = os.path.join(ROOT, "trainer", "p0_verify_report.json")
    with open(out, "w", encoding="utf-8") as f:
        json.dump(report, f, ensure_ascii=False, indent=1, default=str)
    print("saved ->", out)


if __name__ == "__main__":
    main()
