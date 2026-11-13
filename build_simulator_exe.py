"""
build_simulator_exe.py — 将战斗模拟器 GUI 打包为单个 exe。

  打包:  python build_simulator_exe.py
  输出:  dist/BackpackSimulator.exe

说明:
  - GUI 使用 tkinter，需 Tcl/Tk 支持；请用自带 Tcl/Tk 的 Python（如系统 3.14）运行本脚本。
  - 运行本 exe 时，把 lineups/ 文件夹（含若干阵容 JSON）放在 exe 同目录下即可。
  - 物品/角色数据（assets/）会被打包进 exe；如有更新需重新打包。
"""
import os
import shutil
import subprocess
import sys
import time
from pathlib import Path

PROJECT_DIR = Path(__file__).parent
PYTHON = sys.executable
APP_NAME = "BackpackSimulator"


def _clear_old_exe(dist_dir: Path):
    exe_path = dist_dir / f"{APP_NAME}.exe"
    if not exe_path.exists():
        return
    try:
        os.remove(str(exe_path))
        return
    except Exception:
        pass
    archive = dist_dir / "_old_builds"
    archive.mkdir(parents=True, exist_ok=True)
    try:
        exe_path.rename(archive / f"{APP_NAME}.{int(time.time())}.exe")
        print(f"Old exe moved to {archive}")
    except Exception as e:
        print(f"WARNING: could not clear old exe: {e}")


def build():
    dist_dir = PROJECT_DIR / "dist"
    work_dir = PROJECT_DIR / "build"
    dist_dir.mkdir(parents=True, exist_ok=True)
    work_dir.mkdir(parents=True, exist_ok=True)
    _clear_old_exe(dist_dir)

    # ── S2-B3：预编译 pyc（docs/性能优化执行路径.md）──
    # PyInstaller 分析期即编译字节码，compileall 在此保证：①构建用到的
    # __pycache__ 全新鲜（PyInstaller 直接拾取现成 pyc，构建更快更稳）；
    # ②开发态 python -m simulator.gui 首启即命中缓存。
    import compileall
    print("Precompiling bytecode (compileall) ...")
    for pkg in ("gd_core_py", "simulator"):
        ok = compileall.compile_dir(str(PROJECT_DIR / pkg), quiet=1,
                                    maxlevels=10, force=True)
        if not ok:
            print(f"WARNING: compileall {pkg} 有编译失败项（继续打包，PyInstaller 会自行编译）")

    # ── M4-5（docs/性能优化下一步规划.md §4/§9.5）：Cython 编译步固化 ──
    # 此前 664 pyd 需手工先跑 tools/build_cython.py，漏跑则 exe 带旧 pyd
    # 甚至纯 py。build_cython --msvc --all 幂等（已编且源未变者跳过），
    # 全新机全量 ≈30-50 分钟，增量通常 <1 分钟。
    # 逃生口：GD_EXE_SKIP_CYTHON=1 跳过（已知 pyd 新鲜时的快速重打包）。
    if os.environ.get("GD_EXE_SKIP_CYTHON") != "1":
        print("Building Cython pyds (build_cython --msvc --all, idempotent) ...")
        r = subprocess.run(
            [PYTHON, "-X", "utf8", str(PROJECT_DIR / "tools" / "build_cython.py"),
             "--msvc", "--all"],
            cwd=str(PROJECT_DIR), text=True, encoding="utf-8", errors="replace")
        if r.returncode != 0:
            print("ERROR: build_cython --all 失败——中止打包（exe 不能带陈旧 pyd）",
                  file=sys.stderr)
            raise SystemExit(2)
    else:
        print("SKIP Cython build (GD_EXE_SKIP_CYTHON=1)")

    args = [
        PYTHON, "-m", "PyInstaller",
        "--noconfirm",
        "--onefile",
        "--windowed",                     # GUI：无控制台窗口
        "--name", APP_NAME,
        # 打包物品/角色数据（data.py 冻结态从 sys._MEIPASS/assets 读取）
        "--add-data", str(PROJECT_DIR / "assets") + ";assets",
        # 唯一默认内核 gd_core（2026-11-09 起）：适配层延迟导入；gd_core_py 的
        # 673 个转写模块经 _registry（importlib.import_module）动态导入，
        # 静态分析不可见，必须显式全量收集。数据面 assets/gd_core_runtime.json
        # 已由上方 --add-data assets 覆盖。
        "--hidden-import", "simulator.gd_core_engine",
        # ★ v0.5.4：simulator.behavior 以 __import__("simulator.damage"/"simulator.buff")
        #   字符串动态导入两个模块（静态分析不可见）——v0.5.4 selftest 抓出
        #   ModuleNotFoundError 后补。与 gd_core_py 同理：动态导入必须显式收集。
        "--collect-submodules", "simulator",
        "--collect-submodules", "gd_core_py",
        "--hidden-import", "tkinter",
        "--hidden-import", "tkinter.ttk",
        "--hidden-import", "tkinter.scrolledtext",
        "--hidden-import", "tkinter.filedialog",
        "--hidden-import", "tkinter.messagebox",
        "--collect-all", "tkinter",
        "--hidden-import", "_tkinter",
        "--add-binary",
        str(Path(sys.base_prefix) / "DLLs" / "_tkinter.pyd") + ";.",
        "--add-data",
        str(Path(sys.base_prefix) / "tcl") + ";tcl",
        # ── M4-4′（§12.2 新 P4，2026-11-11）：剔确认未用的标准库 ──
        #   对照构建开关：GD_NO_EXCLUDE=1 时跳过（量化 exclude 自身收益）
        #   逐一 grep 打包面（battle_simulator.py/launcher.py/simulator/
        #   gd_core_py/）零 import 命中才列入；pickle 不剔（multiprocessing
        #   依赖，simulate.py 在用）。命中保留：logging/argparse/csv/
        #   ctypes/multiprocessing。
        *([] if os.environ.get("GD_NO_EXCLUDE") == "1" else [
            "--exclude-module", "unittest",
            "--exclude-module", "pydoc",
            "--exclude-module", "doctest",
            "--exclude-module", "xml",
            "--exclude-module", "xmlrpc",
            "--exclude-module", "email",
            "--exclude-module", "http",
            "--exclude-module", "urllib",
            "--exclude-module", "sqlite3",
            "--exclude-module", "profile",
            "--exclude-module", "pstats",
            "--exclude-module", "lib2to3",
            "--exclude-module", "py_compile",
            "--exclude-module", "tabnanny",
            "--exclude-module", "symtable",
        ]),
        "--distpath", str(dist_dir),
        "--workpath", str(work_dir),
        "--specpath", str(work_dir),
        str(PROJECT_DIR / "battle_simulator.py"),
    ]

    print("Running PyInstaller for", APP_NAME, "...")
    result = subprocess.run(args, cwd=str(PROJECT_DIR))

    if result.returncode != 0:
        print("BUILD FAILED")
        return 1

    exe_path = dist_dir / f"{APP_NAME}.exe"
    if not exe_path.exists():
        print(f"BUILD FAILED: {exe_path} not found")
        return 1

    # 把示例 lineups/ 复制到 exe 同目录，开箱即用
    src_lineups = PROJECT_DIR / "lineups"
    dst_lineups = dist_dir / "lineups"
    if src_lineups.is_dir():
        # Merge instead of deleting; Windows may keep an example JSON open.
        shutil.copytree(str(src_lineups), str(dst_lineups), dirs_exist_ok=True)
        print(f"已复制示例阵容到: {dst_lineups}")

    size_mb = exe_path.stat().st_size / 1024 / 1024
    print()
    print("=" * 50)
    print(f"BUILD OK: {exe_path}")
    print(f"Size: {size_mb:.1f} MB")
    print("将 lineups/ 文件夹（含阵容 JSON）放在 exe 同目录下即可使用。")
    print("=" * 50)
    return 0


if __name__ == "__main__":
    sys.exit(build())