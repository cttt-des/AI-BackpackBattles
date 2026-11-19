"""Build an isolated MinGW DLL with LTO and optional PGO on the sampled hot units."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import os
from pathlib import Path
import runpy
import shutil
import subprocess
import sys
import tempfile


HOT_UNITS = {"gd_rt", "engine_wrapper", "shard_00", "shard_02", "shard_03", "shard_07"}
LTO = "-flto=2"


def build_dll(native, out, jobs, profile_flags=()):
    module = runpy.run_path(str(native / "build_windows.py"))
    standard_flags = tuple(module["COMMON"])
    hot_flags = (*standard_flags, LTO, *profile_flags)
    using_profiles = any(flag.startswith("-fprofile-use=") for flag in profile_flags)

    def compile_unit(source, obj):
        hot = source.stem in HOT_UNITS
        flags = hot_flags if hot else standard_flags
        # Relative -o gives MinGW the normalized drive component for profile lookup.
        output = obj.name if hot and using_profiles else str(obj)
        command = [module["CXX"], *flags, "-c", str(source), "-o", output]
        result = subprocess.run(command, cwd=obj.parent, capture_output=True)
        if result.returncode or b"profile count data file not found" in result.stderr:
            diagnostic = (result.stderr + result.stdout).decode("utf8", errors="replace")
            raise module["CompileError"](source, diagnostic[-4000:] or f"rc={result.returncode}")

    build = module["build"]
    namespace = build.__globals__
    namespace["_compile_unit"] = compile_unit
    namespace["ThreadPoolExecutor"] = lambda max_workers: ThreadPoolExecutor(
        max_workers=min(jobs, max_workers),
    )
    namespace["OUT_LIB"] = out
    module["COMMON"].extend((LTO, *profile_flags))
    return build()


def collect_profiles(instrumented, objects, profile):
    stage = Path(__file__).resolve().parent
    env = dict(os.environ, GCOV_PREFIX=str(profile), GCOV_PREFIX_STRIP="99")
    workloads = (
        ("bench_native_corpus.py", "smoke", ("--size", "3")),
        ("bench_native_corpus.py", "replays", ()),
        ("bench_native_hot_path.py", "training", ()),
    )
    for script, name, args in workloads:
        subprocess.run([sys.executable, str(stage / script), "--dll", str(instrumented),
                        "--out", str(objects / f"{name}.json"), *args], check=True, env=env)

    # MinGW normalizes the drive colon to '~' when reading a prefixed profile.
    # Collect into a flat directory, then mirror the lookup path used by g++.
    lookup = profile / objects.drive.replace(":", "~") / objects.relative_to(objects.anchor)
    lookup.mkdir(parents=True, exist_ok=True)
    for name in sorted(HOT_UNITS):
        counts = profile / f"{name}.gcda"
        if not counts.is_file() or not counts.stat().st_size:
            raise ValueError(f"Missing profile counts for {name}")
        shutil.copy2(counts, lookup / counts.name)


def build_candidate(native, out, jobs, pgo=False):
    with tempfile.TemporaryDirectory(prefix="native-hot-lto-") as objects:
        previous = {name: os.environ.get(name) for name in ("NATIVE_SIM_OBJ", "MAKE")}
        os.environ["NATIVE_SIM_OBJ"] = objects
        make = shutil.which("mingw32-make")
        if make:
            os.environ.setdefault("MAKE", make)
        try:
            if not pgo:
                return build_dll(native, out, jobs)
            objects = Path(objects)
            profile = objects / "pgo"
            profile.mkdir()
            path = profile.as_posix()
            instrumented = build_dll(native, objects / "instrumented.dll", jobs, (f"-fprofile-generate={path}",))
            collect_profiles(instrumented, objects, profile)
            for name in HOT_UNITS:
                (objects / f"{name}.o").unlink()
            flags = (f"-fprofile-use={path}", "-fprofile-partial-training", "-fprofile-correction")
            return build_dll(native, out, jobs, flags)
        finally:
            for name, value in previous.items():
                if value is None:
                    os.environ.pop(name, None)
                else:
                    os.environ[name] = value


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("native", type=Path)
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--jobs", type=int, default=2)
    parser.add_argument("--pgo", action="store_true", help="Train the hot units on the local replay and batch benchmarks")
    args = parser.parse_args()
    if args.jobs < 1:
        parser.error("--jobs must be positive")
    native = args.native.resolve()
    out = args.out.resolve()
    if out.exists():
        parser.error("Use a new output path for the candidate DLL")
    out.parent.mkdir(parents=True, exist_ok=True)
    build_candidate(native, out, args.jobs, args.pgo)
