"""
Build script: package the bridge injector GUI into a single exe.

Run:
    python build_bridge_injector.py

Output: dist/BackpackAI-BridgeInjector.exe
"""

import os
import shutil
import subprocess
import sys
import time
from pathlib import Path

PROJECT_DIR = Path(__file__).parent
PYTHON = sys.executable
APP_NAME = "BackpackAI-BridgeInjector"


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
    _clear_old_exe(dist_dir)

    # Bundle bridge.gd so the injector can find it at runtime
    bridge_gd = PROJECT_DIR / "bridge" / "bridge.gd"
    if not bridge_gd.exists():
        print(f"ERROR: {bridge_gd} not found!")
        return 1

    args = [
        PYTHON, "-m", "PyInstaller",
        "--noconfirm",
        "--clean",
        "--onefile",
        "--windowed",
        "--name", APP_NAME,
        # Bundle bridge.gd as a runtime resource (accessed via _MEIPASS)
        "--add-data", str(bridge_gd) + ";bridge",
        # Bundle the inject module
        "--hidden-import", "bridge.inject",
        # stdlib imports for logging
        "--hidden-import", "logging",
        "--distpath", str(dist_dir),
        "--workpath", str(work_dir),
        "--specpath", str(work_dir),
        str(PROJECT_DIR / "bridge" / "injector_app.py"),
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

    size_mb = exe_path.stat().st_size / 1024 / 1024
    print()
    print("=" * 50)
    print(f"BUILD OK: {exe_path}")
    print(f"Size: {size_mb:.1f} MB")
    print("=" * 50)
    return 0


if __name__ == "__main__":
    sys.exit(build())
