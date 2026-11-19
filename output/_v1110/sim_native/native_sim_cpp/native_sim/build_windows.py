#!/usr/bin/env python3
"""Windows (MinGW g++) build: compile stale C++20 units in parallel, link native_sim/libgdcore.dll.

Mirrors build.py (macOS clang++), with the platform-specific bits swapped:
  clang++ -> g++, -install_name dropped, -static added (self-contained DLL),
  -ffp-contract=off kept on BOTH compile and link (determinism: no FMA contraction).

Usage:
    python native_sim/build_windows.py [--clean]
"""
from concurrent.futures import ThreadPoolExecutor
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import time

ROOT = Path(__file__).resolve().parent
# ★ MinGW 的 as/ld 无法向含中文的路径写产物（GBK 乱码 → "No such file or directory"）。
#   因此中间产物与 DLL 一律落在 ASCII 临时目录编译，成功后用 Python 复制回 bundle
#   （shutil 处理 Unicode 路径无碍）。可用 NATIVE_SIM_OBJ 覆盖缓存目录。
OBJ_DIR = Path(os.environ.get("NATIVE_SIM_OBJ") or os.path.join(tempfile.gettempdir(), "native_sim_obj"))
OUT_TMP = OBJ_DIR / "libgdcore.dll"
OUT_LIB = ROOT / "libgdcore.dll"
CXX = os.environ.get("NATIVE_SIM_CXX", "g++")

COMMON = ["-O3", "-std=c++20", "-march=native", "-ffp-contract=off", "-Wall",
          "-Wno-unused-variable", "-Wno-unused-but-set-variable", "-I", str(ROOT)]


class CompileError(RuntimeError):
    def __init__(self, src: Path, msg: str):
        super().__init__(f"{src}\n{msg}")
        self.msg = msg


def _compile_unit(src: Path, obj: Path) -> None:
    cxx = [CXX, *COMMON, "-c", str(src), "-o", str(obj)]
    # 中文 Windows 上 g++ 诊断输出是 GBK——按字节捕获再宽松解码，防 UnicodeDecodeError 吞错
    r = subprocess.run(cxx, capture_output=True)
    if r.returncode != 0:
        err = (r.stderr + r.stdout).decode("utf-8", errors="replace")
        raise CompileError(src, err[-4000:] or f"rc={r.returncode}")


def build(force: bool = False) -> Path:
    t0 = time.perf_counter()
    OBJ_DIR.mkdir(parents=True, exist_ok=True)

    srcs = [
        ROOT / "gd_rt.cpp",
        ROOT / "engine_wrapper.cpp",
        ROOT / "gen" / "sym_ids.cpp",
        ROOT / "gen" / "register_all.cpp",
        *sorted((ROOT / "gen" / "shards").glob("*.cpp")),
    ]
    hdr_deps = [
        ROOT / "gd_rt.hpp",
        ROOT / "builtin_syms.hpp",
        ROOT / "gen" / "sym_ids.hpp",
        ROOT / "gen" / "class_metas.hpp",
    ]
    max_hdr_mtime = max(p.stat().st_mtime for p in hdr_deps if p.exists())

    to_compile: list[tuple[Path, Path]] = []
    objs: list[str] = []
    for src in srcs:
        obj = OBJ_DIR / f"{src.stem}.o"
        objs.append(str(obj))
        if force or not obj.exists():
            to_compile.append((src, obj))
        else:
            om = obj.stat().st_mtime
            if src.stat().st_mtime > om or max_hdr_mtime > om:
                to_compile.append((src, obj))

    if to_compile:
        workers = min(len(to_compile), max(2, os.cpu_count() or 8))
        errs = []

        def _one(pair):
            try:
                _compile_unit(*pair)
                return None
            except CompileError as e:
                return (str(pair[0]), e.msg)

        with ThreadPoolExecutor(max_workers=workers) as ex:
            for r in ex.map(_one, to_compile):
                if r:
                    errs.append(r)
        if errs:
            for name, err in errs:
                print(f"COMPILE FAIL {name}\n{err}", file=sys.stderr)
            raise SystemExit(1)

    link = [CXX, *COMMON, "-shared", "-static", "-o", str(OUT_TMP), *objs]
    subprocess.run(link, check=True)
    shutil.copyfile(OUT_TMP, OUT_LIB)
    dt = time.perf_counter() - t0
    print(f"Built {OUT_LIB} (compiled {len(to_compile)}/{len(srcs)}, linked {len(objs)} objs) in {dt:.2f}s")
    return OUT_LIB


if __name__ == "__main__":
    build(force="--clean" in sys.argv)
