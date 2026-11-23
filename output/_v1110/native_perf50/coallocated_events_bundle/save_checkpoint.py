"""Archive only the inconclusive coallocated-event round; never install it."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import tempfile

WORK = Path(__file__).resolve().parent
STAGE = WORK.parents[1]
REPO = STAGE.parents[1]
BASE_SHA = 'e0bedc4960077407e85763cb5e4af70175a0623cca15e923403fa89174390687'
SCRIPTS = (
    'prepare_native_coallocated_events.py', 'setup_coallocated_event_checks.py',
    'build_native_coallocated_events.py', 'validate_coallocated_when_built.py',
    'test_coallocated_event_storage.cpp', 'verify_coallocated_frame.py',
    'verify_coallocated_params.py', 'verify_coallocated_storage.py',
    'verify_native_coallocated_events.py', 'prototype_native_coallocated_events_bundle.py',
    'setup_coallocated_events_bundle.py', 'preflight_native_coallocated_events_bundle.py',
    'run_coallocated_formal_when_ready.py', 'close_coallocated_round.py',
)

def git(*args):
    return subprocess.check_output(['git', *args], cwd=REPO)

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def collect():
    decision = json.loads((WORK / 'candidate_decision.json').read_bytes())
    assert decision['status'] == 'inconclusive_retained'
    assert decision['not_deployed'] and decision['no_more_same_source_groups']
    assert sha(WORK / 'ab_assessment_32.json') == decision['assessment_sha256']
    assert sha(WORK / 'bundle.dll') == decision['candidate_dll_sha256']
    for p in (STAGE / 'sim_native/native_sim_cpp/native_sim/libgdcore.dll',
              REPO / 'dist/native_1_1_10/libgdcore.dll'):
        assert sha(p) == BASE_SHA
    paths = {STAGE / name for name in SCRIPTS}
    # Entire round-specific source and evidence trees, excluding interpreter caches.
    for root in (WORK, WORK.parent / 'coallocated_events_prototype'):
        paths.update(p for p in root.rglob('*') if p.is_file()
                     and '__pycache__' not in p.parts and p.suffix not in ('.pyc', '.o', '.gcda', '.gcno')
                     and not p.name.startswith('checkpoint_'))
    paths.update(REPO / name for name in (
        'docs/C++模拟器性能优化清单.md', 'docs/C++模拟器下一阶段优化评估.md',
        'docs/C++模拟器优化交接_2026-11-23.md'))
    assert all(p.is_file() for p in paths)
    relative = sorted(p.relative_to(REPO).as_posix() for p in paths)
    assert all(p.startswith(('output/_v1110/native_perf50/coallocated_events_', 'docs/'))
               or p in {'output/_v1110/' + n for n in SCRIPTS} for p in relative)
    return relative

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--commit', action='store_true')
    args = parser.parse_args()
    assert not git('diff', '--cached', '--name-only').strip(), 'Preserve existing staged work'
    paths = collect()
    inventory = {name: sha(REPO / name) for name in paths}
    (WORK / 'checkpoint_inventory.json').write_text(
        json.dumps(inventory, indent=2, ensure_ascii=False) + '\n', encoding='utf8')
    print(json.dumps(dict(files=len(paths), bytes=sum((REPO / p).stat().st_size for p in paths),
                          unchanged_production_dll_sha256=BASE_SHA)))
    if not args.commit:
        return
    with tempfile.NamedTemporaryFile(prefix='coallocated-archive-', delete=False) as output:
        path = Path(output.name)
        output.write(b''.join(p.encode('utf8') + b'\0' for p in paths))
    try:
        git('-c', 'core.autocrlf=false', 'add', '-f', f'--pathspec-from-file={path}', '--pathspec-file-nul')
    finally:
        path.unlink()
    staged = set(filter(None, git('diff', '--cached', '--name-only', '-z').decode('utf8').split('\0')))
    assert staged.issubset(paths), sorted(staged - set(paths))
    assert inventory == {name: sha(REPO / name) for name in paths}
    git('commit', '-m', 'perf: archive inconclusive32 coallocated event trials')
    commit = git('rev-parse', 'HEAD').decode().strip()
    git('update-ref', 'refs/heads/codex/coallocated-events-inconclusive-20261123', commit)
    receipt = dict(local_commit=commit, local_preservation_ref='refs/heads/codex/coallocated-events-inconclusive-20261123',
                   own_files_saved=len(paths), unchanged_production_dll_sha256=BASE_SHA,
                   candidate_not_deployed=True, remote_upload_verified=False)
    (WORK / 'checkpoint_receipt.json').write_text(json.dumps(receipt, indent=2) + '\n', encoding='utf8')
    print(json.dumps(receipt))

if __name__ == '__main__':
    main()
