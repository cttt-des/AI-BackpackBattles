import argparse
from concurrent.futures import ThreadPoolExecutor
import os
from pathlib import Path
import runpy
import shutil
import subprocess
import sys
import tempfile

stage = Path(__file__).resolve().parent
sim = stage / "sim_native"
cpp = sim / "native_sim_cpp"
native = cpp / "native_sim"
objects = Path(os.environ.get("NATIVE_SIM_OBJ") or Path(tempfile.gettempdir()) / "native_idle_scene_order_obj").resolve()
parser = argparse.ArgumentParser()
parser.add_argument("--baseline", type=Path, required=True)
parser.add_argument("--out", type=Path, required=True)
parser.add_argument("--jobs", type=int, default=1)
parser.add_argument("--native-hot-path", action="store_true")
parser.add_argument("--native-perf50", action="store_true",
                    help="Apply the placement and frame optimizations after the native hot-path pass")
args = parser.parse_args()
if args.jobs < 1:
    parser.error("--jobs must be positive")
baseline = args.baseline.resolve()
if baseline == args.out.resolve():
    parser.error("Use a new path for the candidate DLL")
assert (objects / "libgdcore.dll").read_bytes() == baseline.read_bytes()
assert (native / "libgdcore.dll").read_bytes() == baseline.read_bytes()

def generate(script, cwd, *arguments):
    subprocess.run([sys.executable, "-u", str(script), *arguments], cwd=cwd, check=True)

generated = native / "gen"
previous = {p: (p.read_bytes(), p.stat().st_atime_ns, p.stat().st_mtime_ns)
            for p in generated.rglob("*") if p.suffix in (".cpp", ".hpp")}
generate(stage / "stage_native_lovers_rng.py", stage)
generate(cpp / "tools/gd_to_cpp.py", cpp)
for name in ("float", "cooldowns", "buff_timers", "item_timers"):
    generate(stage / f"optimize_native_{name}.py", stage)
if "gd_sim_run_one_replay_host_phases" in (native / "engine_wrapper.cpp").read_text("utf8"):
    generate(stage / "stage_native_host_idle_phase.py", stage, "--generated-only")
if args.native_hot_path or args.native_perf50:
    generate(stage / "optimize_native_hot_path.py", stage)
if args.native_perf50:
    generate(stage / "optimize_native_placement.py", stage, str(native), "--fast-predicates")
    generate(stage / "optimize_native_frames.py", stage, str(native), "--part", "all")
for path, (body, atime, mtime) in previous.items():
    if path.exists() and path.read_bytes() == body:
        os.utime(path, ns=(atime, mtime))

os.environ["NATIVE_SIM_CXX"] = "D:/mingw64/bin/g++.exe"
os.environ["NATIVE_SIM_OBJ"] = str(objects)
build = runpy.run_path(str(native / "build_windows.py"))
compile_native = build["build"]
compile_native.__globals__["ThreadPoolExecutor"] = (
    lambda max_workers: ThreadPoolExecutor(max_workers=min(max_workers, args.jobs))
)
result = compile_native()
shutil.copyfile(result, args.out.resolve())
