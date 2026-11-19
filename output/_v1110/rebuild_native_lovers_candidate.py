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
objects = Path(tempfile.gettempdir()) / "native_idle_scene_order_obj"
parser = argparse.ArgumentParser()
parser.add_argument("--baseline", type=Path, required=True)
parser.add_argument("--out", type=Path, required=True)
parser.add_argument("--jobs", type=int, default=1)
args = parser.parse_args()
if args.jobs < 1:
    parser.error("--jobs must be positive")
baseline = args.baseline.resolve()
if baseline == args.out.resolve():
    parser.error("Use a new path for the candidate DLL")
assert (objects / "libgdcore.dll").read_bytes() == baseline.read_bytes()
assert (native / "libgdcore.dll").read_bytes() == baseline.read_bytes()

def generate(script, cwd):
    subprocess.run([sys.executable, "-u", str(script)], cwd=cwd, check=True)

generated = native / "gen"
previous = {p: (p.read_bytes(), p.stat().st_atime_ns, p.stat().st_mtime_ns)
            for p in generated.rglob("*") if p.suffix in (".cpp", ".hpp")}
generate(stage / "stage_native_lovers_rng.py", stage)
generate(cpp / "tools/gd_to_cpp.py", cpp)
for name in ("float", "cooldowns", "buff_timers", "item_timers"):
    generate(stage / f"optimize_native_{name}.py", stage)
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
