"""Recompile only shard05 against the retained ABI-identical semantic objects."""
import ctypes
import hashlib
import json
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_event_factory import STAGE, BASE, WORK, ACCEPTED, EXPECTED, sha

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    src, out = WORK / 'prototype_src', WORK / 'prototype.dll'
    assert not out.exists()
    frozen = json.loads((WORK / 'transform.json').read_bytes())['source_sha256']
    assert frozen == {p.relative_to(src).as_posix(): sha(p) for p in src.rglob('*') if p.is_file()}
    old = STAGE / 'native_perf50/grid_cooldown_prototype'
    before = json.loads((old / 'transform.json').read_bytes())['source_sha256']
    assert sorted(n for n in before if before[n] != frozen[n]) == ['gen/shards/shard_05.cpp']
    original = Path((old / 'objects.txt').read_text('utf8'))
    objects = Path(tempfile.mkdtemp(prefix='native-event-factory-'))
    (WORK / 'objects.txt').write_text(str(objects), encoding='utf8')
    names = ['gd_rt', 'engine_wrapper', 'sym_ids', 'register_all', *[f'shard_{i:02d}' for i in range(16)]]
    hashes = {n: sha(original / (n+'.o')) for n in names}
    for n in names:
        if n != 'shard_05':
            shutil.copyfile(original / (n+'.o'), objects / (n+'.o'))
    flags = runpy.run_path(str(src / 'build_windows.py'))['COMMON']
    compiler = 'D:/mingw64/bin/g++.exe'
    with (WORK / 'shard05_compile_first.log').open('wb') as log:
        subprocess.run([compiler, *flags, '-c', str(src / 'gen/shards/shard_05.cpp'),
                        '-o', str(objects / 'shard_05.o')], stdout=log, stderr=subprocess.STDOUT, check=True)
    with (WORK / 'link_first.log').open('wb') as log:
        subprocess.run([compiler, *flags, '-shared', '-static', '-o', str(objects / 'libgdcore.dll'),
                        *[str(objects / (n+'.o')) for n in names]], stdout=log, stderr=subprocess.STDOUT, check=True)
    assert hashes == {n: sha(original / (n+'.o')) for n in names}
    shutil.copyfile(objects / 'libgdcore.dll', out)
    from bench_native_corpus import load_simulator, measure, prepare, select_cases
    sim = load_simulator(out)
    signature = hashlib.sha256()
    jobs = list(prepare(sim, select_cases(200), signature))
    audit = sim.lib.gd_diag_native_resolved_audit
    audit.argtypes, audit.restype = [ctypes.c_int], None
    audit(1)
    count = sim.lib.gd_diag_native_resolved_stat
    count.argtypes, count.restype = [ctypes.c_uint], ctypes.c_uint64
    initial = [count(i) for i in range(6)]
    result = measure(sim, jobs, 1, 0, continuous=True)
    coverage = dict(zip(('generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback'),
                        [count(i)-initial[i] for i in range(6)]))
    assert coverage == json.loads((ACCEPTED / 'release_audit.json').read_bytes())['coverage']
    ref = json.loads((STAGE / 'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest() == ref['inputs_sha256']
    assert result['results_sha256'] == ref['results_sha256'] and result['matched_original_terminal'] == 200
    report = dict(passed=True, semantic_only=True, dll_sha256=sha(out), baseline_dll_sha256=EXPECTED,
                  source_manifest_sha256=sha(WORK/'transform.json'), reused_objects=19, recompiled_units=1,
                  original_objects_unchanged=True, original_six_counters=coverage,
                  inputs_sha256=signature.hexdigest(), results_sha256=result['results_sha256'],
                  matched_original_terminal=200, no_throughput_claim=True, not_for_deployment=True)
    (WORK/'build.json').write_text(json.dumps(report, indent=2)+'\n', encoding='utf8')
    print(json.dumps(report, indent=2), flush=True)

if __name__ == '__main__':
    main()
