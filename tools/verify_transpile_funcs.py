# -*- coding: utf-8 -*-
"""verify_transpile_funcs.py — 转写函数完整性对账（2026-09-28 定型）。

两段对账：decompiled_full(原版) → gd_core_items(直挂 gd) → gd_core_py(Python)：
  每个脚本列出「原版有、转写缺」的函数 → 静默剥离实锤。
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

FUNC_RE = re.compile(r"^\s*func\s+([A-Za-z_]\w*)\s*\(", re.M)
STATIC_RE = re.compile(r"^\s*static\s+func\s+([A-Za-z_]\w*)\s*\(", re.M)


def funcs_of_gd(path):
    txt = open(path, encoding="utf-8").read()
    names = set(FUNC_RE.findall(txt))
    # static func 也算
    return names


def funcs_of_py(path):
    txt = open(path, encoding="utf-8").read()
    return set(re.findall(r"^\s*def\s+([A-Za-z_]\w*)\s*\(", txt, re.M))


def map_orig_to_kern():
    """原版 Items/**/*.gd → 转写 gd_core_items/**/*.gd 的对应表（经 runtime json 的 script 字段）。"""
    import json
    d = json.load(open(os.path.join(ROOT, "assets", "gd_core_runtime.json"),
                       encoding="utf-8"))
    pairs = []
    for key, ent in d["items"].items():
        script = ent.get("script") or ""
        # res://gd_core_items/Exclusive/MagicRing.gd → gd_core_items/Exclusive/MagicRing.gd
        m = re.match(r"res://(.+\.gd)$", script)
        if not m:
            continue
        kern = os.path.join(ROOT, m.group(1).replace("/", os.sep))
        # 找原版脚本：同名 .gd 于 decompiled_full
        base = os.path.splitext(os.path.basename(kern))[0]
        cands = []
        for dp, dns, fns in os.walk(os.path.join(ROOT, "decompiled_full")):
            if ".import" in dp or "Sprites" in dp or ".autoconverted" in dp:
                continue
            if base + ".gd" in fns:
                cands.append(os.path.join(dp, base + ".gd"))
        # 原版优先 Items 目录
        cands.sort(key=lambda p: (0 if os.sep + "Items" + os.sep in p else 1))
        if cands and os.path.exists(kern):
            pairs.append((key, cands[0], kern))
    return pairs


def main():
    pairs = map_orig_to_kern()
    print("可比对脚本对数: %d" % len(pairs))
    bad1, bad2 = [], []
    for key, orig, kern_gd in pairs:
        # 段1：原版 gd vs 直挂 gd_core_items/*.gd（都是 GDScript，func 提取）
        f_orig = funcs_of_gd(orig)
        f_orig.discard("_ready")
        kern_py = kern_gd.replace(
            os.sep + "gd_core_items" + os.sep,
            os.sep + "gd_core_py" + os.sep + "gd_core_items" + os.sep)[:-3] + ".py"
        if not os.path.exists(kern_py):
            continue
        f_gd = funcs_of_gd(kern_gd)
        f_gd.discard("_readyInit")
        # 段2：直挂 gd vs Python py（gd_to_py.py 转写）
        f_py = funcs_of_py(kern_py)
        m1 = sorted(f_orig - f_gd)
        m2 = sorted(f_gd - f_py)
        if m1:
            bad1.append((key, m1, orig, kern_gd))
        if m2:
            bad2.append((key, m2, kern_gd, kern_py))
    print("\n=== 段1：原版 → 直挂 gd_core_items（缺失 %d 个脚本）===" % len(bad1))
    for key, missing, orig, kern in bad1:
        print("[%s] 缺: %s" % (key, ", ".join(missing)))
    print("\n=== 段2：直挂 gd → Python gd_core_py（缺失 %d 个脚本）===" % len(bad2))
    for key, missing, kern_gd, kern_py in bad2:
        print("[%s] 缺: %s" % (key, ", ".join(missing)))
    if not bad1 and not bad2:
        print("全部函数齐全")


if __name__ == "__main__":
    main()
