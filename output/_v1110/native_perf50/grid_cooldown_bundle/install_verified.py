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
BASELINE = "55b62a2044b87311a967878a91d88ef4702641d240594989a09c396f67172ece"
ARCHIVE = "f67e7c55fd5d4c161b6ab3c81d925d2ba7ea5ffd"


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
    parser.add_argument("--assessment",type=Path,default=WORK/'ab_assessment.json')
    args = parser.parse_args()
    if (WORK/'followup_plan.json').exists():
        assert args.assessment.resolve()==(WORK/'ab_assessment_32.json').resolve(), 'Declared bounded follow-up requires all32 pairs'
    name = args.name
    dll = WORK / f"{name}.dll"
    src = WORK / f"{name}_src"
    gate_path = WORK / f"{name}_full_gate.json"
    gate = json.loads(gate_path.read_bytes())
    hashes = json.loads((WORK / f"{name}_vs_deployed_hashes.json").read_bytes())
    speed = json.loads(args.speed_report.read_bytes())
    native = STAGE / "sim_native/native_sim_cpp/native_sim"
    local_dll = native / "libgdcore.dll"
    dist = REPO / "dist"
    default = dist / "native_1_1_10"
    backup = dist / "native_1_1_10_before_grid_cooldown_bundle_20261122"
    pending = dist / f"native_1_1_10_{name}_pending"
    for directory in (default, backup, pending):
        assert directory.resolve().is_relative_to(REPO.resolve()), directory
    reference = json.loads((STAGE / "native_perf50_event_bus_serial.json").read_bytes())
    actual = digest(dll)
    assert gate["complete"] and gate["dll_sha256"] == actual
    cumulative = json.loads(args.assessment.read_bytes())
    expected_pairs=24
    if args.assessment.resolve()==(WORK/'ab_assessment_32.json').resolve():
        plan=json.loads((WORK/'followup_plan.json').read_bytes())
        assert plan['maximum_extra_groups']==1 and plan['all_original24_retained'] and plan['all32_must_be_used'] and plan['no_more_same_source_groups']
        expected_pairs=32
    assert all(row['pairs']==expected_pairs for row in cumulative['metrics'].values())
    assert cumulative['baseline_dll_sha256'] == BASELINE and cumulative['candidate_dll_sha256'] == actual
    assert cumulative['metrics']['main_thread_cpu_s']['paired_median_time_reduction_pct'] > 0 and cumulative['metrics']['wall_s']['paired_median_time_reduction_pct'] > 0
    audit = json.loads((WORK / 'full_type_audit.json').read_bytes())
    assert audit['fights'] == 2604 and audit['coverage']['audit_mismatch'] == 0 and audit['old_event_kernel_type_mismatches'] == 0
    source_manifest = json.loads((WORK / 'source_before_build.json').read_bytes())
    for relative, expected_sha in source_manifest.items():
        assert digest(src / relative) == expected_sha, relative
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
        assert target.resolve().is_relative_to(native.resolve())
        old = target.read_bytes() if target.exists() else None
        new = source.read_bytes()
        if old == new:
            continue
        relative = target.relative_to(REPO).as_posix()
        if old is None:
            assert not subprocess.check_output(["git","ls-tree",ARCHIVE,"--",relative],cwd=REPO).strip()
        else:
            archived = subprocess.check_output(["git", "show", f"{ARCHIVE}:{relative}"], cwd=REPO)
            assert old == archived
        changed[target] = (old, new)
    generator = STAGE/'optimize_native_verified_bundle.py'
    old_generator = generator.read_bytes()
    assert subprocess.check_output(['git','show',f'{ARCHIVE}:{generator.relative_to(REPO).as_posix()}'],cwd=REPO) == old_generator
    assert json.loads((WORK/'full_regeneration_test.json').read_bytes())['passed']
    changed[generator] = (old_generator, (WORK/'verified_bundle_pending.py').read_bytes())
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
            if changed[target][0] is None:
                target.unlink()
            else:
                replace(target, changed[target][0])
        raise
    report = {"dll_sha256": actual, "gate_sha256": digest(gate_path),
              "ab_assessment_path":str(args.assessment.resolve()),"ab_assessment_sha256":digest(args.assessment),"ab_pairs":expected_pairs,
              "speed_report_sha256": digest(args.speed_report), "training_outcomes": expected["outcomes"],
              "regeneration_test_sha256": digest(WORK/'regeneration_test.json'),
              "full_regeneration_test_sha256": digest(WORK/'full_regeneration_test.json'),
              "training_matched_baseline": len(expected["outcomes"]), "training_evaluation": expected["evaluation"],
              "runtime": default.relative_to(REPO).as_posix(), "backup_runtime": backup.relative_to(REPO).as_posix(),
              "changed_native_files": [path.relative_to(REPO).as_posix() for path in installed]}
    (WORK / f"{name}_installation.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf8")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
