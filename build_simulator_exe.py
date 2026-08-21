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

    args = [
        PYTHON, "-m", "PyInstaller",
        "--noconfirm",
        "--onefile",
        "--windowed",                     # GUI：无控制台窗口
        "--name", APP_NAME,
        # 打包物品/角色数据（data.py 冻结态从 sys._MEIPASS/assets 读取）
        "--add-data", str(PROJECT_DIR / "assets") + ";assets",
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
