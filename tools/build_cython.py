# -*- coding: utf-8 -*-
"""build_cython.py — F1 Cython 编译批（docs/性能优化执行路径.md S5-F1）

单模块编译：.py → (cython) → .c → (gcc/MinGW) → .pyd，产物落原目录——
importlib 扩展优先级（.pyd > .py）使内核自动走编译件；.py 保留为回落腿
（模块导入失败时 _bootstrap 记失败并回退——GD_CYTHON=0 环境门可强制回落：
  删除 .pyd 或设 GD_CYTHON=0？注：Python 无法按 env 选扩展，回落手段=删
  .pyd 或 _bootstrap 捕获 ImportError。故 .pyd 缺陷即删文件回滚，单模块粒度）。

后端：MinGW gcc（D:/mingw64，x86_64-w64-mingw32/msvcrt）直链 python314.dll。
Cython 产物只用 Python C API（无跨 CRT 堆/FILE 交互），msvcrt gcc + UCRT
Python 实践兼容。MSVC（winget BuildTools）为后续正式化路径，当前不可用。

用法:
    python tools/build_cython.py gd_core_py/gd_core/CoreItem.py
    python tools/build_cython.py --all          # F1 热 8 模块
"""
import argparse
import os
import subprocess
import sys
import sysconfig

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GCC = r"D:\mingw64\bin\gcc.exe"
PY_DIR = os.path.dirname(sys.executable)

# F1 热 8 模块（规划顺序：CoreItem → CoreCombat → CoreCharacter → CoreTimer →
# CoreRng → CoreBuff → CoreGrid → CoreEventBus）；逐一单独上闸
HOT8 = [
    "gd_core_py/gd_core/CoreItem.py",
    "gd_core_py/gd_core/CoreCombat.py",
    "gd_core_py/gd_core/CoreCharacter.py",
    "gd_core_py/gd_core/CoreTimer.py",
    "gd_core_py/gd_core/CoreRng.py",
    "gd_core_py/gd_core/CoreBuff.py",
    "gd_core_py/gd_core/CoreGrid.py",
    "gd_core_py/gd_core/CoreEventBus.py",
]


def build_one(py_path: str) -> str:
    """编译单模块，返回 .pyd 路径。任一步失败抛异常（单模块回落=删 .pyd）。"""
    py_path = os.path.relpath(os.path.join(ROOT, py_path), ROOT)
    if not os.path.exists(os.path.join(ROOT, py_path)):
        raise FileNotFoundError(py_path)
    base = os.path.splitext(py_path)[0]          # gd_core_py/gd_core/CoreItem
    c_path = base + ".c"
    pyd_path = base + ".pyd"
    modname = os.path.basename(base)             # PyInit_<modname>

    # ① cython：.py → .c（-3 = Python 3 语言语义；module-name 由文件名推断）
    # ★ 严禁 -2（Py2 语义会把 `/` 变整除——REG9 run1514 ev@71 抓获的正是它）
    r = subprocess.run([sys.executable, "-m", "cython", "-3",
                        py_path, "-o", c_path],
                       cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        raise RuntimeError(f"cython 失败 {py_path}:\n{r.stdout[-800:]}\n{r.stderr[-800:]}")

    # ② gcc：.c → .pyd（直链 python314.dll；-O2；无 RTTI/异常需求）
    inc = sysconfig.get_paths()["include"]
    r = subprocess.run(
        [GCC, "-O2", "-shared", "-fno-strict-aliasing",
         "-I", inc, "-I", os.path.join(PY_DIR, "Include"),
         "-L", PY_DIR, "-lpython314",
         "-o", pyd_path, c_path],
        cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        raise RuntimeError(f"gcc 失败 {py_path}:\n{r.stderr[-1500:]}")
    if not os.path.exists(os.path.join(ROOT, pyd_path)):
        raise RuntimeError(f"pyd 未产出: {pyd_path}")
    return pyd_path


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("targets", nargs="*", help="相对 ROOT 的 .py 路径")
    ap.add_argument("--all", action="store_true", help="F1 热 8 模块")
    ap.add_argument("--clean", action="store_true",
                    help="删除目标 .pyd/.c（回滚手段）")
    a = ap.parse_args()
    targets = HOT8 if a.all else a.targets
    if not targets:
        ap.error("需要 targets 或 --all")

    rc = 0
    for t in targets:
        base = os.path.splitext(os.path.join(ROOT, t))[0]
        if a.clean:
            for ext in (".pyd", ".c"):
                p = base + ext
                if os.path.exists(p):
                    os.remove(p)
                    print(f"removed {p}")
            continue
        try:
            pyd = build_one(t)
            print(f"OK  {t} → {pyd}  ({os.path.getsize(os.path.join(ROOT, pyd))//1024} KB)")
        except Exception as e:  # noqa: BLE001
            print(f"FAIL {t}: {e}")
            rc = 1
    return rc


if __name__ == "__main__":
    raise SystemExit(main())
