#!/usr/bin/env python3
"""Compile stale C++20 units in parallel and link native_sim/libgdcore.dylib."""

from concurrent.futures import ThreadPoolExecutor
import os
from pathlib import Path
import subprocess
import sys
import time

ROOT = Path(__file__).resolve().parent
OBJ_DIR = ROOT / "obj"
OUT_LIB = ROOT / "libgdcore.dylib"


def _compile_unit(src: Path, obj: Path) -> None:
    cxx = [
        "clang++",
        "-O3",
        "-std=c++20",
        "-march=native",
        "-fPIC",
        "-ffp-contract=off",
        "-Wall",
        "-Wno-unused-variable",
        "-Wno-unused-but-set-variable",
        "-I",
        str(ROOT),
        "-c",
        str(src),
        "-o",
        str(obj),
    ]
    subprocess.run(cxx, check=True)


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
        with ThreadPoolExecutor(max_workers=workers) as ex:
            list(ex.map(lambda pair: _compile_unit(*pair), to_compile))

    link = [
        "clang++",
        "-O3",
        "-std=c++20",
        "-march=native",
        "-shared",
        "-fPIC",
        "-install_name",
        f"@rpath/{OUT_LIB.name}",
        "-o",
        str(OUT_LIB),
        *objs,
    ]
    subprocess.run(link, check=True)
    dt = time.perf_counter() - t0
    print(f"Built {OUT_LIB} (compiled {len(to_compile)}/{len(srcs)}, linked {len(objs)} objs) in {dt:.2f}s")
    return OUT_LIB


if __name__ == "__main__":
    build(force="--clean" in sys.argv)
