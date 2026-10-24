# -*- coding: utf-8 -*-
"""C5TRIO 取证 v2：GP 影响格几何 + 两侧 classes 数据对拍（只读）。"""
import io, json, csv

ROOT = r"D:/文件资料/学习/自动背包AI"
bi = json.load(io.open(ROOT + "/assets/battle_items.json", encoding="utf-8"))
items = bi.get("items", bi)

# oracle CSV classes 列（Girl Power 行: col6="Neutral 1,2"；col1=name）
csv_classes = {}
with io.open(ROOT + "/oracle/Sheets/CSV/ItemData.csv", encoding="utf-8") as fh:
    for row in csv.reader(fh):
        if len(row) > 6:
            csv_classes[row[0]] = row[6]

def occupied(key, pos):
    d = items.get(key)
    if not d or "grid" not in d:
        return None
    return [(pos[0] + c[0], pos[1] + c[1]) for c in d["grid"]["collision_cells"]]

def affected(key, pos):
    d = items.get(key)
    g = d["grid"].get("affected_cells") or []
    return [(pos[0] + c[0], pos[1] + c[1]) for c in g]

for case in ["run608_r18", "run613_r18", "run729_r14"]:
    lu = json.load(io.open(ROOT + "/output/oracle/fights/%s/lineups.json" % case, encoding="utf-8"))
    side = lu["player"]
    its = side["items"]
    gp = next(it for it in its if it["name"] == "Girl Power")
    gpos = (gp["top_left"]["x"], gp["top_left"]["y"])
    acells = set(affected("Girl Power", gpos))
    print("=" * 90)
    print(case, "GP@%s" % (gpos,))
    hit, miss = [], []
    for it in its:
        if it["name"] == "Girl Power":
            continue
        oc = occupied(it["name"], (it["top_left"]["x"], it["top_left"]["y"]))
        if oc is None:
            miss.append(it["name"])
            continue
        if set(oc) & acells:
            hit.append(it["name"])
    if miss:
        print("  [miss in battle_items.json]:", sorted(set(miss)))
    distinct = sorted(set(hit))
    n_cls = 0
    for nm in distinct:
        cls = items[nm].get("classes")
        is_cls = cls not in (0, None)
        if is_cls:
            n_cls += 1
        print("   %-28s json_classes=%-4s csv_classes=%-12r -> %s" %
              (nm, cls, csv_classes.get(nm), "CLASS" if is_cls else "-"))
    print("  N(distinct class keys, json 面就位者) = %d" % n_cls)
