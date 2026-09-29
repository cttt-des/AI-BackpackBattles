"""
build_combatlog_exporter_exe.py — 将战斗日志导出 GUI 打包为单个 exe。

  打包:  python build_combatlog_exporter_exe.py
  输出:  dist/BackpackCombatLog.exe

说明:
  - GUI 使用 tkinter，需 Tcl/Tk 支持；请用自带 Tcl/Tk 的 Python 运行本脚本。
  - assets/（物品中文名库 item_db.json）打包进 exe；更新物品库后需重新打包。
  - 运行时读取 exe 同目录的 config.yaml（godot RVA 标定）；缺失时自动发现。
  - 导出目录为 exe 同目录的 output/combat_logs/。
"""
import subprocess
import sys
from pathlib import Path

PROJECT_DIR = Path(__file__).parent
PYTHON = sys.executable
APP_NAME = "BackpackCombatLog"


def build():
    dist_dir = PROJECT_DIR / "dist"
    work_dir = PROJECT_DIR / "build"
    dist_dir.mkdir(parents=True, exist_ok=True)
    work_dir.mkdir(parents=True, exist_ok=True)

    old = dist_dir / f"{APP_NAME}.exe"
    if old.exists():
        old.unlink()

    args = [
        PYTHON, "-m", "PyInstaller",
        "--noconfirm",
        "--onefile",
        "--windowed",                     # GUI：无控制台窗口
        "--name", APP_NAME,
        # 物品中文名库（core/item_db.py 冻结态从 _MEIPASS/assets 读取）
        "--add-data", str(PROJECT_DIR / "assets") + ";assets",
        # config.yaml 的 godot 段读取在函数内 import yaml，显式声明
        "--hidden-import", "yaml",
        # 结构性读取链均为静态导入（core.*），无需额外 collect；
        # tkinter 完整收齐（与 build_simulator_exe.py 同款配置）
        "--paths", str(PROJECT_DIR),
        "--hidden-import", "tkinter",
        "--hidden-import", "tkinter.ttk",
        "--collect-all", "tkinter",
        "--hidden-import", "_tkinter",
        "--add-binary",
        str(Path(sys.base_prefix) / "DLLs" / "_tkinter.pyd") + ";.",
        "--add-data",
        str(Path(sys.base_prefix) / "tcl") + ";tcl",
        "--distpath", str(dist_dir),
        "--workpath", str(work_dir),
        "--specpath", str(work_dir),
        str(PROJECT_DIR / "combatlog_exporter.py"),
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

    size_mb = exe_path.stat().st_size / 1024 / 1024
    print()
    print("=" * 50)
    print(f"BUILD OK: {exe_path}")
    print(f"Size: {size_mb:.1f} MB")
    print("与 BackpackSimulator.exe 同目录使用；日志导出到 exe 同目录的 "
          "output/combat_logs/。")
    print("=" * 50)
    return 0


if __name__ == "__main__":
    sys.exit(build())
