# -*- coding: utf-8 -*-
"""把 output/_colors_header.txt + output/color_table.py 合成 gd_core_py/_colors.py。"""
import io
import os
import sys

sys.stdout.reconfigure(encoding="utf-8")
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
hdr = io.open(os.path.join(ROOT, "output", "_colors_header.txt"), encoding="utf-8").read()
tbl = io.open(os.path.join(ROOT, "output", "color_table.py"), encoding="utf-8").read()
body = tbl[tbl.index("_COLOR_NAMES"):]
io.open(os.path.join(ROOT, "gd_core_py", "_colors.py"), "w", encoding="utf-8").write(hdr + body)
print("写入 gd_core_py/_colors.py（%d 行）" % (hdr + body).count("\n"))
