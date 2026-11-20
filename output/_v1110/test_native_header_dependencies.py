"""Reproduce stale field offsets after a header edit, then verify the cache fix."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import ctypes
import hashlib
import json
from pathlib import Path
import runpy
import shutil
import tempfile

from optimize_native_header_dependencies import optimize


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("native", type=Path)
    parser.add_argument("--out", type=Path, required=True)
    args = parser.parse_args()
    directory = Path(tempfile.mkdtemp(prefix="native-header-dependencies-"))
    (directory / "gen/hdrs").mkdir(parents=True)
    (directory / "gen/shards").mkdir()
    shutil.copyfile(args.native / "build_windows.py", directory / "build_windows.py")
    for name in ("gd_rt.hpp", "builtin_syms.hpp", "gen/sym_ids.hpp", "gen/class_metas.hpp"):
        (directory / name).write_text("#pragma once\n", encoding="utf8")
    header = directory / "gen/hdrs/Model.hpp"
    header.write_text("struct Model { int first; int value; };\n", encoding="utf8")
    source = directory / "gd_rt.cpp"
    source.write_text('#include <cstddef>\n#include "gen/hdrs/Model.hpp"\n'
                      'extern "C" __declspec(dllexport) int probe_offset() { return offsetof(Model, value); }\n',
                      encoding="utf8")
    for index, name in enumerate(("engine_wrapper.cpp", "gen/sym_ids.cpp", "gen/register_all.cpp", "gen/shards/shard_00.cpp")):
        (directory / name).write_text(f"int header_probe_{index}() {{ return {index}; }}\n", encoding="utf8")
    original_source = hashlib.sha256(source.read_bytes()).hexdigest()

    def build():
        module = runpy.run_path(str(directory / "build_windows.py"))
        function = module["build"]
        namespace = function.__globals__
        objects = directory / "objects"
        namespace.update(OBJ_DIR=objects, OUT_TMP=objects / "libgdcore.dll", OUT_LIB=directory / "artifact.dll",
                         CXX="D:/mingw64/bin/g++.exe",
                         COMMON=["-O2", "-std=c++20", "-ffp-contract=off", "-I", str(directory)],
                         ThreadPoolExecutor=lambda max_workers: ThreadPoolExecutor(max_workers=min(2, max_workers)))
        return function()

    libraries = []

    def read(dll, label):
        copy = directory / (label + ".dll")
        shutil.copyfile(dll, copy)
        library = ctypes.CDLL(str(copy))
        libraries.append(library)
        function = library.probe_offset
        function.argtypes, function.restype = [], ctypes.c_int
        return function()

    first = read(build(), "initial")
    header.write_text("struct Model { int value; int first; };\n", encoding="utf8")
    stale = read(build(), "stale")
    optimize(directory)
    fixed = read(build(), "fixed")
    assert original_source == hashlib.sha256(source.read_bytes()).hexdigest()
    assert (first, stale, fixed) == (4, 4, 0), (first, stale, fixed)
    report = {"passed": True, "initial_offset": first, "stale_offset_after_header_edit": stale,
              "fixed_offset_after_header_edit": fixed, "cpp_source_unchanged": True,
              "real_compiler_and_dll_loads": True}
    args.out.write_text(json.dumps(report, indent=2) + "\n", encoding="utf8")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
