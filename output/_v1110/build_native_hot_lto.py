"""Build an isolated MinGW DLL with link-time optimization on the sampled hot units."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import os
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile


HOT_UNITS = {"gd_rt", "engine_wrapper", "shard_00", "shard_02", "shard_03", "shard_07"}
LTO = "-flto=2"


def build_candidate(native, out, jobs):
    with tempfile.TemporaryDirectory(prefix="native-hot-lto-") as objects:
        os.environ["NATIVE_SIM_OBJ"] = objects
        make = shutil.which("mingw32-make")
        if make:
            os.environ.setdefault("MAKE", make)
        module = runpy.run_path(str(native / "build_windows.py"))
        standard_flags = tuple(module["COMMON"])

        def compile_unit(source, obj):
            flags = (*standard_flags, LTO) if source.stem in HOT_UNITS else standard_flags
            command = [module["CXX"], *flags, "-c", str(source), "-o", str(obj)]
            result = subprocess.run(command, capture_output=True)
            if result.returncode:
                diagnostic = (result.stderr + result.stdout).decode("utf8", errors="replace")
                raise module["CompileError"](source, diagnostic[-4000:] or f"rc={result.returncode}")

        build = module["build"]
        namespace = build.__globals__
        namespace["_compile_unit"] = compile_unit
        namespace["ThreadPoolExecutor"] = lambda max_workers: ThreadPoolExecutor(
            max_workers=min(jobs, max_workers),
        )
        namespace["OUT_LIB"] = out
        module["COMMON"].append(LTO)
        return build()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("native", type=Path)
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--jobs", type=int, default=2)
    args = parser.parse_args()
    if args.jobs < 1:
        parser.error("--jobs must be positive")
    native = args.native.resolve()
    out = args.out.resolve()
    if out.exists():
        parser.error("Use a new output path for the candidate DLL")
    build_candidate(native, out, args.jobs)
