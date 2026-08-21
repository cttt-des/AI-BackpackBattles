# -*- coding: utf-8 -*-
"""diag_compile.py — 诊断哪些物品脚本的战斗方法无法编译（落入 methods_raw）。
输出每个失败方法的生成源码与编译错误，便于修复 transpile 规则。
"""
import os, sys, json
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import simulator.extract_items as E

DECOMP = os.path.join(os.path.dirname(__file__), "..", "decompiled_full", "Items")

def diagnose(relpath):
    p = os.path.join(DECOMP, relpath)
    if not os.path.exists(p):
        print(f"[MISS] {relpath}")
        return
    try:
        extends, iv, onready, td, methods = E.parse_script(p)
    except Exception as e:
        print(f"[PARSE ERR] {relpath}: {e}")
        return
    for name, info in methods.items():
        body_py, lv = E.transform_body(info["body"], iv)
        arglist = "_item" + (", " + E.strip_type_hints(info["args"]) if info["args"] else "")
        src = f"def {name}({arglist}):\n"
        if lv:
            src += "    " + "; ".join(f"{v}=None" for v in lv) + "\n"
        if body_py.strip() == "":
            src += "    pass\n"
        else:
            src += "    " + body_py.replace("\n", "\n    ")
        try:
            compile(src, p + ":" + name, "exec")
        except Exception as e:
            print(f"=== FAIL {relpath} :: {name} ===")
            print(f"  ERROR: {e}")
            print("  --- generated source ---")
            for i, ln in enumerate(src.split("\n")):
                print(f"  {i:2d}| {ln}")
            print()

def main():
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("paths", nargs="*")
    args = ap.parse_args()
    if args.paths:
        for r in args.paths:
            diagnose(r)
    else:
        for root, _, files in os.walk(DECOMP):
            for f in sorted(files):
                if f.endswith(".gd"):
                    diagnose(os.path.relpath(os.path.join(root, f), DECOMP))

if __name__ == "__main__":
    main()
