import os, sys
ROOT = r"D:\文件资料\学习\自动背包AI"
sys.path.insert(0, ROOT)
from simulator.gd_core_engine import GDCoreEngine
from simulator.lineup import load_lineup
a = load_lineup(os.path.join(ROOT, "lineups", "lineup_gem_test.json"))
b = load_lineup(os.path.join(ROOT, "lineups", "lineup_armor_wall.json"))
seeds, outs = [], []
for _ in range(6):
    e = GDCoreEngine(a, b, {}, {})
    seeds.append(e.seed)
    e.run()
    outs.append((e.combat_time, e._p.curHealth, e._o.curHealth))
print("自动种子:", seeds)
print("结果         :", outs)
print("种子去重数 %d/6，结果去重数 %d/6" % (len(set(seeds)), len(set(outs))))
assert len(set(seeds)) == 6, "自动种子出现重复 —— 无种子多场会退化成同一场"
assert len(set(outs)) > 1, "无种子多场结果全同 —— 随机性没生效"
# 显式种子必须可复现
e1 = GDCoreEngine(a, b, {}, {}, seed=12345); e1.run()
e2 = GDCoreEngine(a, b, {}, {}, seed=12345); e2.run()
assert (e1.combat_time, e1._p.curHealth, e1._o.curHealth) == \
       (e2.combat_time, e2._p.curHealth, e2._o.curHealth), "同种子不可复现"
print("同种子复现 ✓")
print("CHKSEED: PASS")
