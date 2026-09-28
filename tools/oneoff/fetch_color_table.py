# -*- coding: utf-8 -*-
"""取 Godot 3.6-stable core/color_names.inc，生成 _rt.Color 的具名色表源码。

★ 为什么不凭记忆写：Godot 的具名色来自 X11 表（140 余条），记忆容易串值。
  这里从 3.6-stable 的 `core/color_names.inc`（`Color::hex(0xRRGGBBAA)`）直接抽，
  通道值按 `Color::hex` 的 float32 除法复算（`f32(v / 255.0)`），与引擎一致。
"""
import base64
import io
import os
import re
import struct
import subprocess
import sys

sys.stdout.reconfigure(encoding="utf-8")
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GH = os.path.join(ROOT, "gh_tmp", "bin", "gh.exe")
OUT = os.path.join(ROOT, "output", "godot_src")


def f32(x):
    return struct.unpack("<f", struct.pack("<f", x))[0]


r = subprocess.run([GH, "api",
                    "repos/godotengine/godot/contents/core/color_names.inc?ref=3.6-stable",
                    "--jq", ".content"], capture_output=True)
if r.returncode != 0:
    print("FAIL", r.stderr.decode("utf-8", "replace")[:300])
    raise SystemExit(1)
data = base64.b64decode(r.stdout)
io.open(os.path.join(OUT, "color_names.inc"), "wb").write(data)
text = data.decode("utf-8", "replace")

pairs = re.findall(r'_named_colors\.insert\("([a-z0-9]+)",\s*Color::hex\(0x([0-9A-Fa-f]{8})\)\)',
                   text)
print("具名颜色 %d 条" % len(pairs))
rows, width = [], 0
for name, hx in pairs:
    rr, gg, bb, aa = (int(hx[i:i + 2], 16) for i in (0, 2, 4, 6))
    vals = tuple(f32(c / 255.0) for c in (rr, gg, bb, aa))
    rows.append('    "%s": (%s),' % (name, ", ".join(repr(v) for v in vals)))
    width = max(width, len(name))

src = ("# Godot 3.6-stable core/color_names.inc（X11 表）—— 通道按 Color::hex 的\n"
       "# float32 除法复算。生成：output/fetch_color_table.py\n"
       "_COLOR_NAMES = {\n" + "\n".join(rows) + "\n}\n")
p = os.path.join(ROOT, "output", "color_table.py")
io.open(p, "w", encoding="utf-8").write(src)
print("写出 %s（%d 条，最长名 %d）" % (p, len(rows), width))
print(rows[0])
print([x for x in rows if x.startswith('    "white"')][0])
