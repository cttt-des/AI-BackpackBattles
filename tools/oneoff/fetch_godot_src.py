# -*- coding: utf-8 -*-
"""取 Godot 3.6-stable 的 RNG 相关源码，作为 Python 侧位对齐的权威依据。"""
import base64
import io
import os
import subprocess
import sys

sys.stdout.reconfigure(encoding="utf-8")
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GH = os.path.join(ROOT, "gh_tmp", "bin", "gh.exe")
OUT = os.path.join(ROOT, "output", "godot_src")
os.makedirs(OUT, exist_ok=True)

FILES = [
    "core/math/random_pcg.h",
    "core/math/random_number_generator.cpp",
    "core/math/random_number_generator.h",
    "core/math/math_funcs.h",
]

for f in FILES:
    r = subprocess.run([GH, "api",
                        "repos/godotengine/godot/contents/%s?ref=3.6-stable" % f,
                        "--jq", ".content"],
                       capture_output=True)
    if r.returncode != 0:
        print("FAIL", f, r.stderr.decode("utf-8", "replace")[:200])
        continue
    data = base64.b64decode(r.stdout)
    p = os.path.join(OUT, os.path.basename(f))
    io.open(p, "wb").write(data)
    print("ok  %-46s %7d bytes -> %s" % (f, len(data), p))
