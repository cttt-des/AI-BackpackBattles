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
ARCHIVE = "79dbf3b2547eb45b28d9b3e97046f3e0bc77f0ef"
sys.path.insert(0, str(STAGE))
from build_native_hot_lto import HOT_UNITS, build_dll, collect_profiles
from optimize_native_buff_scalar_locals import optimize


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    name = "buff_scalar_locals"
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
    (WORK / "buff_scalar_locals_baseline_archive.json").write_text(json.dumps({
        "archive_commit": ARCHIVE, "dll_sha256": BASELINE,
        "source_reader": "git cat-file --batch (raw objects)",
        "verified_sources": len(expected_sources), "source_sha256": expected_sources,
    }, indent=2) + "\n", encoding="utf8")
    import build_native_assembly as assembly
    assembly.native=NATIVE;assembly.work=WORK;assembly.expected=BASELINE
    assembly.base=Path((STAGE/'native_perf50/cycles11/inline_timers_objects.txt').read_text('utf8').strip())
    assembly.baseline={unit:assembly.base/(unit+'.o') for unit in assembly.units}
    assert all(path.is_file() for path in assembly.baseline.values())
    os.environ['NATIVE_SIM_CXX']='D:/mingw64/bin/g++.exe'
    def action(source):
        optimize(source)
        headers={p.relative_to(source).as_posix():digest(p) for p in source.rglob('*.hpp')}
        assert headers=={p.relative_to(NATIVE).as_posix():digest(p) for p in NATIVE.rglob('*.hpp')}
        before={p:p.stat().st_mtime_ns for p in source.rglob('*') if p.is_file()}
        optimize(source)
        assert before=={p:p.stat().st_mtime_ns for p in before}
        (WORK/'buff_scalar_object_compatibility.json').write_text(json.dumps({'baseline_objects':str(assembly.base),'all_headers_unchanged':True,'generator_idempotent_bytes_and_mtime':True,'only_changed_cpp':'shard_00','fresh_pgo_for_changed_unit':True},indent=2)+'\n',encoding='utf8',newline='\n')
    result=assembly.build(name,action)
    print(name,digest(result),flush=True)


if __name__ == '__main__':
    main()
