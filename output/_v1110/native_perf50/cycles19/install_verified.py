"""Install the winner of the follow-up replay trials on this workspace."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile

WORK = Path(__file__).resolve().parent
STAGE = WORK.parents[1]
REPO = STAGE.parents[1]
BASELINE = "58383a1158e951d7aae8b4d4c34df4d52332446156946d31a488f5dff323ec39"
ARCHIVE = "76847e3b8fdafb469184aa813b714a9362241848"


def digest(path):
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def replace(path, data):
    with tempfile.NamedTemporaryFile(dir=path.parent, prefix="native-followup-", delete=False) as temp:
        swap = Path(temp.name)
        temp.write(data)
    try:
        os.replace(swap, path)
    finally:
        swap.unlink(missing_ok=True)


def training_smoke(directory=None):
    code = """
import json
from trainer.evaluator import OpponentPool, _run_jobs, eval_vs_pool
from trainer.native_backend import runtime_directory
pool = OpponentPool().sample((450, 650), 50, seed=42)[:4]
jobs = [(pool[0], other, seed) for other in pool for seed in (0, 42, (1 << 64) - 1)]
assert len(jobs) == 12 and runtime_directory() is not None
public = eval_vs_pool(pool[0], pool, seeds_per_opp=3, workers=1)
assert public['total_sims'] == 12 and public['sim_errors'] == 0
print(json.dumps({'outcomes': _run_jobs(jobs, workers=1), 'evaluation': public}))
"""
    env = dict(os.environ, BACKPACK_TRAINER_BACKEND=str(directory) if directory else "auto")
    output = subprocess.check_output([sys.executable, "-c", code], cwd=REPO, env=env, text=True)
    return json.loads(output.splitlines()[-1])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("name")
    parser.add_argument("--speed-report", type=Path, required=True)
    args = parser.parse_args()
    name = args.name
    dll = WORK / f"{name}.dll"
    src = WORK / f"{name}_src"
    gate_path = WORK / f"{name}_full_gate.json"
    gate = json.loads(gate_path.read_bytes())
    hashes = json.loads((WORK / f"{name}_event_hashes.json").read_bytes())
    speed = json.loads(args.speed_report.read_bytes())
    native = STAGE / "sim_native/native_sim_cpp/native_sim"
    local_dll = native / "libgdcore.dll"
    dist = REPO / "dist"
    default = dist / "native_1_1_10"
    backup = dist / "native_1_1_10_before_cycle19"
    pending = dist / f"native_1_1_10_{name}_pending"
    for directory in (default, backup, pending):
        assert directory.resolve().is_relative_to(REPO.resolve()), directory
    reference = json.loads((STAGE / "native_perf50_event_bus_serial.json").read_bytes())
    actual = digest(dll)
    assert gate["complete"] and gate["dll_sha256"] == actual
    assert hashes["baseline_dll_sha256"] == BASELINE and hashes["candidate_dll_sha256"] == actual
    assert hashes["unchanged_cpp_event_streams"] == 2604
    assert speed["dll_sha256"] == actual and speed["workers"] == 1 and speed["fights"] == 200
    assert speed["inputs_sha256"] == reference["inputs_sha256"] and speed["results_sha256"] == reference["results_sha256"]
    assert len(speed["samples"]) == speed["repeat"] == 24
    assert min(sample["fights_per_second"] for sample in speed["samples"]) >= 50
    assert digest(local_dll) == digest(default / "libgdcore.dll") == BASELINE
    assert not backup.exists()
    shell = [sys.executable, str(STAGE / "package_native_training_runtime.py"),
             "--dll", str(dll), "--gate", str(gate_path), "--out", str(pending)]
    subprocess.run(shell, cwd=REPO, check=True)

    expected = training_smoke()
    staged = training_smoke(pending)
    assert expected == staged and all(value in (0, 1) for value in staged["outcomes"])

    changed = {}
    for source in sorted(path for path in src.rglob("*") if path.is_file() and (path.suffix in (".cpp", ".hpp") or path.name=="build_windows.py")):
        target = native / source.relative_to(src)
        old = target.read_bytes()
        new = source.read_bytes()
        if old == new:
            continue
        archived = subprocess.check_output(["git", "show", f"{ARCHIVE}:{target.relative_to(REPO).as_posix()}"], cwd=REPO)
        assert old == archived
        changed[target] = (old, new)
    changed[local_dll] = (local_dll.read_bytes(), dll.read_bytes())
    installed = []
    try:
        for target, (_, new) in changed.items():
            replace(target, new)
            installed.append(target)
        default.rename(backup)
        switched = False
        try:
            pending.rename(default)
            switched = True
            assert digest(default / "libgdcore.dll") == digest(local_dll) == actual
            manifest = json.loads((default / "manifest.json").read_bytes())
            assert manifest["gate_sha256"] == digest(gate_path) and manifest["sha256"]["libgdcore.dll"] == actual
            assert training_smoke() == expected
        except BaseException:
            if switched:
                default.rename(pending)
            backup.rename(default)
            raise
    except BaseException:
        for target in reversed(installed):
            replace(target, changed[target][0])
        raise
    report = {"dll_sha256": actual, "gate_sha256": digest(gate_path),
              "speed_report_sha256": digest(args.speed_report), "training_outcomes": expected["outcomes"],
              "training_matched_baseline": len(expected["outcomes"]), "training_evaluation": expected["evaluation"],
              "runtime": default.relative_to(REPO).as_posix(), "backup_runtime": backup.relative_to(REPO).as_posix(),
              "changed_native_files": [path.relative_to(REPO).as_posix() for path in installed]}
    (WORK / f"{name}_installation.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf8")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
