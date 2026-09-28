"""
build_simulator_exe.py — 将战斗模拟器 GUI 打包为单个 exe。

  打包:  python build_simulator_exe.py
  输出:  dist/BackpackSimulator.exe

说明:
  - GUI 使用 tkinter，需 Tcl/Tk 支持；请用自带 Tcl/Tk 的 Python（如系统 3.14）运行本脚本。
  - 运行本 exe 时，把 lineups/ 文件夹（含若干阵容 JSON）放在 exe 同目录下即可。
  - 物品/角色数据（assets/）会被打包进 exe；如有更新需重新打包。
  - assets/gd_core_runtime.json 是 gd_core 内核的运行时数据（由
    `tools/gen_gd_core_data.py` 生成）。物品库/网格/socket 数有改动时，先跑那个
    工具再打包，否则 exe 里的 gd_core 内核拿的是旧几何（会安静算错摆位）。
    打包前会自动 `gen_gd_core_data.py --check` 守住这一点。
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


def _preflight_gd_core_data() -> bool:
    """打包前守住 gd_core 运行时数据与源数据同步。

    为什么要在**打包前**卡这一步：`assets/gd_core_runtime.json` 里的物品网格几何
    是从 `assets/battle_items.json` + `extracted/Items/*.tscn` 编译出来的快照。
    改了物品库（或重新解包了 tscn）却忘了重生成，exe 里的 gd_core 内核就会拿旧几何
    装配 —— 表现是战斗照跑、结果偏差，**不报任何错**。
    """
    script = PROJECT_DIR / "tools" / "gen_gd_core_data.py"
    if not script.exists():
        print("WARNING: 缺少 %s，跳过 gd_core 数据同步检查" % script)
        return True
    print("Preflight: 校验 gd_core 运行时数据是否与源数据同步 ...")
    r = subprocess.run([PYTHON, str(script), "--check"], cwd=str(PROJECT_DIR))
    if r.returncode != 0:
        print("BUILD FAILED: gd_core 运行时数据不同步。")
        print("  请先跑: %s %s" % (PYTHON, script))
        return False
    return True


def build():
    dist_dir = PROJECT_DIR / "dist"
    work_dir = PROJECT_DIR / "build"
    dist_dir.mkdir(parents=True, exist_ok=True)
    work_dir.mkdir(parents=True, exist_ok=True)

    if not _preflight_gd_core_data():
        return 1

    _clear_old_exe(dist_dir)

    args = [
        PYTHON, "-m", "PyInstaller",
        "--noconfirm",
        "--onefile",
        "--windowed",                     # GUI：无控制台窗口
        "--name", APP_NAME,
        # 打包物品/角色数据（data.py 冻结态从 sys._MEIPASS/assets 读取）
        "--add-data", str(PROJECT_DIR / "assets") + ";assets",
        # v2 引擎（engine/）在 simulate._get_combat_engine 内延迟导入，显式声明
        "--hidden-import", "engine",
        "--hidden-import", "engine.combat",
        "--hidden-import", "engine.data",
        "--hidden-import", "engine.gen.behaviors",
        "--collect-submodules", "engine",
        # gd_core 内核（原版战斗逻辑 1:1 移植版）同样是延迟导入：
        # simulate._get_combat_engine('gd_core') → simulator.gd_core_engine → gd_core_py.*
        # （gd_core_engine.kernel() 里逐个 import，_bootstrap.load_all() 再补 521 个模块，
        #   故用 --collect-submodules 全量收，别靠静态分析漏掉）
        "--paths", str(PROJECT_DIR),
        "--hidden-import", "gd_core_py",
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
