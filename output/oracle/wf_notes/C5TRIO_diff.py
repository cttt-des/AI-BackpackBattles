# -*- coding: utf-8 -*-
"""C5TRIO 泳道取证：语料 vs py 全流对拍（只读）。
复用 tools/verify_oracle.py 的 canonical_stream/_tuple_of（import 纯函数，不跑主流程）。
目标：GirlPower / ArmoredPowerPuppy / Crown 三物品在七场的全部事件侧写。
"""
import io, json, sys, importlib.util

ROOT = r"D:/文件资料/学习/自动背包AI"
spec = importlib.util.spec_from_file_location("vo", ROOT + "/tools/verify_oracle.py")
vo = importlib.util.module_from_spec(spec)
sys.argv = ["verify_oracle.py", "--nothing"]  # 防 main 误跑
spec.loader.exec_module(vo)

ET = vo._et_names()
CASES = ["run608_r18", "run613_r18", "run729_r14",
         "run805_r18", "run879_r11", "run1172_r18", "run1176_r11"]
ITEMS = ("girl power", "armored power puppy", "crown")

def stream(path):
    return vo.canonical_stream(path, ET)

def origin_item(e):
    o = e["origin"]
    if o and o[0] == "item":
        return o[1].lower()
    return None

def tup(e):
    return vo._tuple_of(e)

for case in CASES:
    a = stream(ROOT + "/output/oracle/fights/%s/events.json" % case)   # 语料(oracle)
    b = stream(ROOT + "/output/oracle/align/py/%s/events.json" % case)  # py 全流
    ta = [tup(e) for e in a]
    tb = [tup(e) for e in b]
    print("=" * 90)
    print(case, "oracle=%d py=%d" % (len(a), len(b)))
    # 首分歧
    fd = None
    for i in range(min(len(ta), len(tb))):
        if ta[i] != tb[i]:
            fd = i
            break
    if fd is None and len(ta) != len(tb):
        fd = min(len(ta), len(tb))
    print("first_divergence(tuples) =", fd)
    if fd is not None:
        print("  O[%s] %s" % (fd, json.dumps(ta[fd], ensure_ascii=False, default=str)[:220]) if fd < len(ta) else "  O: <none>")
        print("  P[%s] %s" % (fd, json.dumps(tb[fd], ensure_ascii=False, default=str)[:220]) if fd < len(tb) else "  P: <none>")
    # 三物品事件侧写
    for side, st in (("O", a), ("P", b)):
        rows = []
        for i, e in enumerate(st):
            nm = origin_item(e)
            if nm in ITEMS:
                rows.append((i, e["t"], e["type"], e["params"].get("amount"),
                             e["params"].get("damage"), e["parent"], e["depth"],
                             e["actor"]))
        print("  %s(%d): %s" % (side, len(rows),
              "; ".join("[%d]t=%s T%d amt=%s%s p=%d d=%d %s" % r for r in rows[:40])))
