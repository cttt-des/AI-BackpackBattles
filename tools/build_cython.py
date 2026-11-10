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
import io
import os
import subprocess
import sys
import sysconfig

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GCC = r"D:\mingw64\bin\gcc.exe"
PY_DIR = os.path.dirname(sys.executable)
MSVC_VCVARS = (r"C:\Program Files (x86)\Microsoft Visual Studio\2022"
               r"\BuildTools\VC\Auxiliary\Build\vcvars64.bat")
BACKEND = "mingw"

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
    # S5-F1 续批：_rt shim 床（f32/_iter/_div/Vector2/EnumDict/PCG32 全 C 化，
    # p50 252→216ms）——语义床本体，任何闸红先删 _rt.pyd 回滚
    "gd_core_py/_rt.py",
]


def build_one(py_path: str) -> str:
    """编译单模块，返回 .pyd 路径。任一步失败抛异常（单模块回落=删 .pyd）。"""
    py_path = os.path.relpath(os.path.join(ROOT, py_path), ROOT)
    if not os.path.exists(os.path.join(ROOT, py_path)):
        raise FileNotFoundError(py_path)
    base = os.path.splitext(py_path)[0]          # gd_core_py/gd_core/CoreItem
    c_path = base + ".c"
    pyd_path = base + ".pyd"

    # ① cython：.py → .c（-3 = Python 3 语言语义；module-name 由文件名推断）
    # ★ 严禁 -2（Py2 语义会把 `/` 变整除——REG9 run1514 ev@71 抓获的正是它）
    # ★ M1-4（2026-11-10）：-X binding=False——转写产物零内省依赖，CythonFunction
    #   机制（绑定方法对象/自省槽）整体旁路（实验：单类模块 C 产物 CyFunction
    #   引用 260→3）。embedsignature 在 Cython3 默认即 False（无产物差异）；
    #   freelist 判不可行：模块级指令被语法接受但 C 产物显式 "nofreelists"
    #   ABI 后缀（3.3.1 不再生成 freelist 池），装饰器形态被拒（class scope）。
    r = subprocess.run([sys.executable, "-m", "cython", "-3",
                        "-X", "binding=False",
                        py_path, "-o", c_path],
                       cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        raise RuntimeError(f"cython 失败 {py_path}:\n{r.stdout[-800:]}\n{r.stderr[-800:]}")

    # ② 编译 .c → .pyd：后端二选一（--msvc 切换）
    inc = sysconfig.get_paths()["include"]
    if BACKEND == "msvc":
        # MSVC：经 vcvars64 环境后 cl /O2 /LD /MD（与 Python 同族运行时/官方 ABI）
        # ★ python314.lib 在 <PY_DIR>\libs（首版 /LIBPATH 少 libs → LNK1181）
        libs_dir = os.path.join(PY_DIR, "libs")
        bat = os.path.join(ROOT, "tools", "_msvc_build_one.cmd")
        # ★ M1-5（2026-11-10）：/GL+/LTCG 全程序优化（实验）——GD_LTO=1 开启，
        #   默认关。跨翻译单元内联对单 .pyd 边际小（模块内符号为主），且
        #   link 期变慢（每模块 +2-5s）；闸红或无收益即弃。
        lto = "/GL" if os.environ.get("GD_LTO") == "1" else ""
        ltcg = "/LTCG" if os.environ.get("GD_LTO") == "1" else ""
        cmd_line = (
            f'call "{MSVC_VCVARS}" >nul 2>&1 && cl /O2 /LD /MD /nologo '
            f'{lto} /I "{inc}" {c_path} '
            f'/link {ltcg} /LIBPATH:"{libs_dir}" python314.lib '
            f'/OUT:{pyd_path}')
        with io.open(bat, "w", encoding="ascii", newline="") as fh:
            fh.write("@echo off\r\n" + cmd_line + "\r\n")
        r = subprocess.run(["cmd", "/c", bat], cwd=ROOT,
                           capture_output=True, text=True,
                           encoding="gbk", errors="replace")
        if r.returncode != 0 or not os.path.exists(os.path.join(ROOT, pyd_path)):
            raise RuntimeError(f"msvc 失败 {py_path}:\n{r.stdout[-1500:]}\n{r.stderr[-500:]}")
    else:
        # MinGW：直链 python314.dll；-static-libgcc 免带 gcc 运行时 DLL
        r = subprocess.run(
            [GCC, "-O2", "-shared", "-fno-strict-aliasing", "-static-libgcc",
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
    ap.add_argument("--list", default=None, help="目标清单文件（每行一个相对路径）")
    ap.add_argument("--msvc", action="store_true",
                    help="用 MSVC 后端（需 Build Tools；默认 MinGW）")
    ap.add_argument("--clean", action="store_true",
                    help="删除目标 .pyd/.c（回滚手段）")
    a = ap.parse_args()
    global BACKEND
    if a.msvc:
        BACKEND = "msvc"
    targets = HOT8 if a.all else a.targets
    if a.list:
        with open(a.list, encoding="utf-8") as fh:
            targets = [ln.strip() for ln in fh if ln.strip()]
    if not targets:
        ap.error("需要 targets/--all/--list")

    # ── MSVC 清单模式（S5-F1 续批）：单 bat 内 vcvars 一次 + 逐模块 cl——
    #    首版每模块重调 vcvars（5-8s 纯开销 × 643）不可行。cl 失败的模块无
    #    .pyd 产物 → 回落 .py（幂等重跑只补缺）。──
    if BACKEND == "msvc" and a.list:
        libs_dir = os.path.join(PY_DIR, "libs")
        inc = sysconfig.get_paths()["include"]
        bat = os.path.join(ROOT, "tools", "_msvc_list.cmd")
        out = ["@echo off",
               f'call "{MSVC_VCVARS}" >nul 2>&1']
        for t in targets:
            base = os.path.splitext(t)[0]
            out.append(
                f'if exist {base}.pyd goto :skip_{abs(hash(t)) % 10**8}\n'
                f'cl /O2 /LD /MD /nologo /I "{inc}" {base}.c '
                f'/link /LIBPATH:"{libs_dir}" python314.lib /OUT:{base}.pyd\n'
                f':skip_{abs(hash(t)) % 10**8}')
        with io.open(bat, "w", encoding="ascii", newline="") as fh:
            fh.write("\r\n".join(out) + "\r\n")
        r = subprocess.run(["cmd", "/c", bat], cwd=ROOT)
        print(f"[msvc-list] bat 执行完成 rc={r.returncode}")
        miss = [t for t in targets
                if not os.path.exists(os.path.join(ROOT, t[:-3] + ".pyd"))]
        for t in miss:
            print(f"  MISS {t}（无 .pyd → 回落 .py）")
        print(f"[msvc-list] 缺失 {len(miss)} / 目标 {len(targets)}")
        return 0

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
