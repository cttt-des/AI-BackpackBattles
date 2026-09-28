# -*- coding: utf-8 -*-
"""verify_linkage_subs.py — 联动物品信号订阅批量验证（2026-09-28 定型）。

源自本轮联动排查（详见 docs/gd_core_truth.md §6.21）。扫描器两处曾犯的错已修正：
  1. 邻居直接放在 L 的 affected 格上（几何精确匹配），而不是随便围一圈
  2. 断言 = 「canAffect 通过 且 落在 affected 格」的邻居必须存在连接
静态抽取放宽：emitter 参数不是 character()/opponent()/gem 相关的一律收集。
"""
import os
import re
import sys
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

from simulator.gd_core_engine import GDCoreEngine, runtime_data  # noqa: E402

NEIGHBORS = ["Hero Sword", "Banana", "Health Potion", "Stone",
             "Garlic", "Magic Ring", "Mana Orb", "Amulet of Darkness"]


def onprepare_signals(kern_gd_path):
    txt = open(kern_gd_path, encoding="utf-8").read()
    want = set()
    for fname in ("onPrepare", "onCombatStart"):
        m = re.search(r"^func\s+%s\s*\([^)]*\)[^:]*:(.+?)(?=^func\s|\Z)"
                      % fname, txt, re.M | re.S)
        if not m:
            continue
        for mm in re.finditer(
                r"connectForCombat\(\s*([A-Za-z_]\w*)\s*,\s*\"([^\"]+)\"", m.group(1)):
            em, sig = mm.group(1), mm.group(2)
            if em in ("character", "opponent", "socket", "gem",
                      "ctx", "board", "inventory"):
                continue
            want.add(sig)
    return want


def main():
    data = runtime_data()
    targets = []
    for key, ent in data["items"].items():
        r0 = ent["rot"].get("0") or next(iter(ent["rot"].values()))
        if any(c for c in (r0.get("affected") or {}).values()):
            targets.append(key)

    results = {"OK": [], "FAIL": [], "SKIP": [], "NOCONN": []}
    for key in sorted(targets):
        ent = data["items"][key]
        gd_path = os.path.join(
            ROOT, ent["script"].split("res://", 1)[1].replace("/", os.sep))
        if not os.path.exists(gd_path):
            continue
        want = onprepare_signals(gd_path)
        if not want:
            results["NOCONN"].append(key)
            continue

        # L 放 (4,5)；邻居放 affected 平移格
        r0 = ent["rot"].get("0") or next(iter(ent["rot"].values()))
        aff_cells = []
        for cells in (r0.get("affected") or {}).values():
            aff_cells += [(c[1], c[0]) for c in cells]   # (row,col) = (y,x)
        aff_cells = sorted(set(aff_cells))
        items = [{"id": key, "row": 4, "col": 5, "rotation": 0, "gems": []}]
        ni = 0
        for (r, c) in aff_cells[:24]:
            rr, cc = 4 + r, 5 + c
            if not (0 <= rr < 7 and 0 <= cc < 10):
                continue
            if (rr, cc) == (4, 5):
                continue
            items.append({"id": NEIGHBORS[ni % len(NEIGHBORS)],
                          "row": rr, "col": cc, "rotation": 0, "gems": []})
            ni += 1
        lineup = {
            "version": 3, "meta": {"name": "mass_link2", "source": "diag"},
            "character": "Ranger", "round": 5,
            "class_modifiers": {"health": 80, "stamina": 5, "stamina_regen": 1.0},
            "health_override": None,
            "backpack": {"grid": {"rows": 7, "cols": 10}, "items": items},
            "storage": [],
        }
        oppo = {
            "version": 3, "meta": {"name": "dummy", "source": "diag"},
            "character": "Adventurer", "round": 5,
            "class_modifiers": {"health": 40, "stamina": 5, "stamina_regen": 1.0},
            "health_override": None,
            "backpack": {"grid": {"rows": 7, "cols": 10}, "items": []},
            "storage": [],
        }
        try:
            eng = GDCoreEngine(lineup, oppo, seed=42)
        except Exception as e:  # noqa: BLE001
            results["SKIP"].append((key, "装配失败: %s" % str(e)[:70]))
            continue

        L = next(i for i in eng._p_items if i.descriptor.identifier == key)
        bus = eng.ctx.bus
        inv_sid = {v: k for k, v in bus.signalIDs.items()}
        # 按 emitter 实例记录：connections 的键 emissionID 低 32 位 = emitter id
        id2item = {it.get_instance_id(): it for it in eng._p_items}
        conns = set()
        for eid, fs in bus.connections.items():
            emitter = id2item.get(eid & 0xFFFFFFFF)
            if emitter is None:
                continue
            for _f in fs:
                conns.add((emitter, inv_sid.get(eid >> 32)))

        # 判定集合：canAffect 通过 且 与 L 的 affected 格有交集的邻居
        must = []
        for other in eng._p_items:
            if other is L:
                continue
            oc = set((c.x, c.y) for c in other.occupiedCells)
            hit = False
            for color, cells in L.affectedTileCells.items():
                ac = set((c.x, c.y) for c in cells)
                if not (oc & ac):
                    continue
                try:
                    if L.canAffect_color(other, int(color)):
                        hit = True
                        break
                except Exception:  # noqa: BLE001
                    pass
            if hit:
                must.append(other)

        if not must:
            results["SKIP"].append((key, "邻居不匹配 %s" % sorted(want)))
            continue

        missing = []
        for other in must:
            for sig in want:
                if (other, sig) not in conns:
                    missing.append((other.descriptor.identifier, sig))
        if missing:
            results["FAIL"].append((key, sorted(want), missing[:5]))
        else:
            results["OK"].append((key, len(must), sorted(want)))

    print("== 统计 ==")
    for k, v in results.items():
        print("%-8s %d" % (k, len(v)))
    print("\n== FAIL 明细 ==")
    for key, want, missing in results["FAIL"]:
        print("[%s] 期望 %s" % (key, want))
        for em, sig in missing:
            print("    缺: %s --%s--> %s" % (em, sig, key))
    print("\n== SKIP 明细 ==")
    for key, why in results["SKIP"]:
        print("  %-28s %s" % (key, why))


if __name__ == "__main__":
    main()
