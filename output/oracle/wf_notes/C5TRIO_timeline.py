# -*- coding: utf-8 -*-
"""C5TRIO 取证：语料 vs py 时间线对拍——各 origin 的 proc 时刻序列对比（只读）。"""
import io, json, sys, importlib.util

ROOT = r"D:/文件资料/学习/自动背包AI"
spec = importlib.util.spec_from_file_location("vo", ROOT + "/tools/verify_oracle.py")
vo = importlib.util.module_from_spec(spec)
sys.argv = ["verify_oracle.py", "--nothing"]
spec.loader.exec_module(vo)
ET = vo._et_names()

def stream(p):
    return vo.canonical_stream(p, ET)

def origin_key(e):
    o = e["origin"]
    if o and o[0] in ("item", "src"):
        return "%s:%s" % (o[0], o[1])
    return "other"

case = "run608_r18"
if len(sys.argv) > 1 and not sys.argv[1].startswith("-"):
    case = sys.argv[1]
a = stream(ROOT + "/output/oracle/fights/%s/events.json" % case)
b = stream(ROOT + "/output/oracle/align/py/%s/events.json" % case)

from collections import defaultdict
ta, tb = defaultdict(list), defaultdict(list)
for e in a:
    if e["type"] in (100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110) or e["type"] in (0,):
        ta[origin_key(e)].append((round(e["t"], 3), e["type"]))
for e in b:
    if e["type"] in (100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110) or e["type"] in (0,):
        tb[origin_key(e)].append((round(e["t"], 3), e["type"]))

keys = sorted(set(ta) | set(tb))
for k in keys:
    la, lb = ta.get(k, []), tb.get(k, [])
    mark = "SAME" if la == lb else ("SHIFT" if len(la) == len(lb) else "COUNT-DIFF")
    print("%-34s %-10s nO=%d nP=%d" % (k, mark, len(la), len(lb)))
    if mark != "SAME":
        print("   O:", la[:12])
        print("   P:", lb[:12])
