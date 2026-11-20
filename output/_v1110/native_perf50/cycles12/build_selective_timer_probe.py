"""Rebuild every dependent unit for an isolated hot-field layout candidate."""
import hashlib
import io
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import psutil
psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
import tempfile

STAGE = Path(__file__).resolve().parents[2]
REPO = STAGE.parents[1]
WORK = Path(__file__).resolve().parent
NATIVE = STAGE / "sim_native/native_sim_cpp/native_sim"
BASELINE = "58383a1158e951d7aae8b4d4c34df4d52332446156946d31a488f5dff323ec39"
ARCHIVE = "8ada702c62aa100ec26b29f9a443f1b658609d67"
sys.path.insert(0, str(STAGE))
from build_native_hot_lto import HOT_UNITS, build_dll, collect_profiles
from probe_native_selective_timer_scan import instrument as optimize


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    name = "selective_timer_probe_v2"
    assert digest(NATIVE / "libgdcore.dll") == digest(REPO / "dist/native_1_1_10/libgdcore.dll") == BASELINE
    prefix = NATIVE.relative_to(REPO).as_posix()
    names = subprocess.check_output(["git", "ls-tree", "-r", "--name-only", "-z", ARCHIVE, prefix], cwd=REPO)
    paths = [Path(name.decode("utf8")) for name in names.split(b"\0") if name]
    paths = [path for path in paths if path.suffix in (".cpp", ".hpp") or path.name == "build_windows.py"]
    requests = "".join(f"{ARCHIVE}:{path.as_posix()}\n" for path in paths).encode("utf8")
    # git archive applies checkout newline conversion; cat-file returns exact stored bytes.
    raw = subprocess.run(["git", "cat-file", "--batch"], input=requests, capture_output=True, check=True, cwd=REPO)
    stream = io.BytesIO(raw.stdout)
    expected_sources = {}
    for path in paths:
        header = stream.readline().split()
        assert len(header) == 3 and header[1] == b"blob", header
        data = stream.read(int(header[2]))
        assert stream.read(1) == b"\n"
        assert (REPO / path).read_bytes() == data, f"Source differs from the verified archive: {path}"
        expected_sources[path.relative_to(prefix).as_posix()] = hashlib.sha256(data).hexdigest()
    actual = {path.relative_to(NATIVE).as_posix() for path in NATIVE.rglob("*")
              if path.is_file() and (path.suffix in (".cpp", ".hpp") or path.name == "build_windows.py")}
    assert actual == set(expected_sources), "The source inventory differs from the archived version"
    (WORK / "selective_timer_probe_baseline_archive.json").write_text(json.dumps({
        "archive_commit": ARCHIVE, "dll_sha256": BASELINE,
        "source_reader": "git cat-file --batch (raw objects)",
        "verified_sources": len(expected_sources), "source_sha256": expected_sources,
    }, indent=2) + "\n", encoding="utf8")
    source = WORK / (name + "_src")
    shutil.copytree(NATIVE, source, ignore=shutil.ignore_patterns("*.dll", "*.dylib", "*.o", "*.gcda", "*.gcno", "__pycache__"))
    optimize(source)
    test_dir=Path(tempfile.mkdtemp(prefix="native-inline-arena-unit-"))
    executable=test_dir/"arena_test.exe"
    subprocess.run(["D:/mingw64/bin/g++.exe","-static","-O2","-std=c++20","-Wno-invalid-offsetof",
                    "-DGD_INLINE_TIMER_CANDIDATE","-I",str(source),str(STAGE/"test_native_inline_timer_arena.cpp"),
                    "-o",str(executable)],check=True)
    unit=subprocess.check_output([str(executable)],text=True)
    (WORK/"arena_candidate_test.json").write_text(unit,encoding="utf8")
    print(unit,flush=True)
    changed = [relative for relative in expected_sources
               if digest(source / relative) != expected_sources[relative]]
    assert set(changed) == {"gd_rt.hpp", "gd_rt.cpp", "engine_wrapper.cpp", "gen/shards/shard_00.cpp", "gen/shards/shard_03.cpp"}, changed
    assert HOT_UNITS == {"gd_rt", "engine_wrapper", *(f"shard_{i:02d}" for i in range(16))}
    objects = Path(tempfile.mkdtemp(prefix="native-selective-timer-"))
    (WORK / (name + "_objects.txt")).write_text(str(objects), encoding="utf8")
    os.environ["NATIVE_SIM_OBJ"] = str(objects)
    os.environ["MAKE"] = "D:/mingw64/bin/mingw32-make.exe"
    os.environ["NATIVE_SIM_CXX"] = "D:/mingw64/bin/g++.exe"
    print("Building diagnostic only: all dependent units fresh, no throughput claim",flush=True)
    dll=build_dll(source,objects/"probe.dll",2,hot_units=HOT_UNITS)
    output = WORK / (name + ".dll")
    shutil.copyfile(dll, output)
    print(name, digest(output), flush=True)


if __name__ == "__main__":
    main()
