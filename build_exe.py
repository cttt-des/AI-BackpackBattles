"""
Build script: package the dashboard + bot into a single exe.
Run this after every code change to refresh the exe:

    python build_exe.py

Output: dist/BackpackAI.exe
"""

import os
import shutil
import subprocess
import sys
import time
from pathlib import Path

PROJECT_DIR = Path(__file__).parent
PYTHON = sys.executable
APP_NAME = "BackpackAI"


def _clear_old_exe(dist_dir: Path):
    """Remove/rename the previous exe so PyInstaller can write a fresh one.

    On some drives the OS recycle-bin trash operation fails, which makes a
    plain os.remove abort. We first try a direct delete, and if that fails we
    rename the old exe into an _old_builds folder so the build never blocks.
    """
    exe_path = dist_dir / f"{APP_NAME}.exe"
    if not exe_path.exists():
        return
    try:
        os.remove(str(exe_path))
        return
    except Exception:
        pass
    # Fallback: move it aside into an archive folder
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
    _clear_old_exe(dist_dir)

    # PyInstaller arguments (native GUI app — no console, no web deps)
    args = [
        PYTHON, "-m", "PyInstaller",
        "--noconfirm",
        "--onefile",
        "--windowed",                     # GUI app: no console window
        "--name", APP_NAME,
        # Bundle default config next to the app resources
        "--add-data", str(PROJECT_DIR / "config.yaml") + ";.",
        # Bundle reverse-extracted game assets (sprites + item_db.json) used by the GUI
        "--add-data", str(PROJECT_DIR / "assets") + ";assets",
        # Bundle item DB used by "导出阵容" to validate item names
        "--add-data", str(PROJECT_DIR / "assets" / "items_db_sim.json") + ";simulator",
        # Hidden imports that PyInstaller may miss
        "--hidden-import", "yaml",
        "--hidden-import", "tkinter",
        "--hidden-import", "PIL",
        "--hidden-import", "PIL.ImageTk",
        "--hidden-import", "PIL.Image",
        # Bridge client (lazy-imported by item_reader.py for TCP bridge data)
        "--hidden-import", "core.bridge_client",
        "--distpath", str(dist_dir),
        "--workpath", str(work_dir),
        "--specpath", str(work_dir),
        str(PROJECT_DIR / "launcher.py"),
    ]

    print("Running PyInstaller...")
    print(" ".join(args))
    result = subprocess.run(args, cwd=str(PROJECT_DIR))

    if result.returncode != 0:
        print("BUILD FAILED")
        return 1

    exe_path = dist_dir / f"{APP_NAME}.exe"
    if not exe_path.exists():
        print(f"BUILD FAILED: {exe_path} not found")
        return 1

    # Copy config.yaml next to the exe so users can edit it
    shutil.copy2(PROJECT_DIR / "config.yaml", dist_dir / "config.yaml")

    size_mb = exe_path.stat().st_size / 1024 / 1024
    print()
    print("=" * 50)
    print(f"BUILD OK: {exe_path}")
    print(f"Size: {size_mb:.1f} MB")
    print(f"Config: {dist_dir / 'config.yaml'} (editable)")
    print("=" * 50)
    return 0


if __name__ == "__main__":
    sys.exit(build())