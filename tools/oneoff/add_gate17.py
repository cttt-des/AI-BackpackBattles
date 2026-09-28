# -*- coding: utf-8 -*-
"""把 16 道闸门扩成 17 道：追加门 17（Python 侧全物品）。

★ 教训（本项目 2026-09-27 实际踩过）：改结构的脚本**必须先算命中数、再核对总行数**。
  早前用脚本在文档里搬块，漏了一段切片，把整节搬丢且无法还原。
  故这里每一步都 assert，宁可中止也不写出半成品。
"""
import io
import re

P = r"D:\文件资料\学习\自动背包AI\tools\run_gd_core.py"

with io.open(P, encoding="utf-8") as fh:
    src = fh.read()
n_before = len(src.splitlines())

hits = re.findall(r"(\d+)/16", src)
assert len(hits) == 26, "预期 26 处 x/16，实为 %d" % len(hits)
assert sorted(set(hits), key=int) == [str(i) for i in range(17)], sorted(set(hits))

src = re.sub(r"(\d+)/16", r"\1/17", src)
assert "/16" not in src, "仍有 /16 残留"

ANCHOR = "    if with_bench:"
assert src.count(ANCHOR) == 1, "锚点不唯一：%d" % src.count(ANCHOR)

BLOCK = '''    # ★ 17 补的是**覆盖缺口**，不是新能力：门 9 把 517 件物品逐一带上
    #   GDScript 侧内核的场，而门 13/14 只跑 8 套阵容的 56 局 —— 于是 Python 侧
    #   （模拟器真正跑的那一份）**从未把全部物品过一遍**。代价是实测的：
    #   19 件物品在模拟器里一用就崩，而整条流水线全绿、一行红都不报。
    #   缺口六类（件间有重叠）：`call_deferred` 未映射 8 件 / `typeof`+`TYPE_VECTOR2`
    #   未提供 12 件（棋类）/ 变量名遮蔽基类方法 4 件（`speed` 撞 `CoreItem.speed()`）
    #   / `tr` 未提供 3 件 / `PCG32.randi` 缺失 1 件 / 装配期空值 1 件。
    #   ★ 它与门 9 是**同一次序的两侧实现**：只验一侧，另一侧就是盲区。
    #   ★ 排最后：517 场是全部闸门里最慢的一道，且不产出下游要用的文件。
    if run([PY, os.path.join(ROOT, "tools", "check_gd_py_items.py")],
           "17/17 Python 侧全物品逐一上场（517 件，须零异常）") != 0:
        return 1

'''

src = src.replace(ANCHOR, BLOCK + ANCHOR)
src = src.replace("依次执行十六道闸门", "依次执行十七道闸门")
assert "十六道" not in src

n_after = len(src.splitlines())
assert n_after == n_before + len(BLOCK.splitlines()), \
    "行数对不上：%d -> %d（预期 +%d）" % (n_before, n_after, len(BLOCK.splitlines()))

with io.open(P, "w", encoding="utf-8", newline="\n") as fh:
    fh.write(src)
print("OK：%d 行 -> %d 行" % (n_before, n_after))
