"""Reuse verified native objects to test the exact new dictionary implementation quickly."""
import ctypes
import hashlib
import json
import os
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile
from concurrent.futures import ThreadPoolExecutor
import psutil
from prepare_native_integer_grid import STAGE,BASE,WORK,EXPECTED,ARCHIVE,sha
SEMANTIC=STAGE/'native_perf50/semantic_base_55b6'

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    report_path=WORK/'build.json';assert not report_path.exists()
    cached=json.loads((SEMANTIC/'build.json').read_bytes());assert cached['passed'] and cached['not_for_formal_timing_or_deployment']
    src=WORK/'prototype_src';frozen=json.loads((WORK/'transform.json').read_bytes())
    assert frozen['source_sha256']=={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    before=json.loads((SEMANTIC/'source_manifest.json').read_bytes());after=frozen['source_sha256']
    assert sorted(n for n in before if before[n]!=after[n])==['gd_rt.cpp','gd_rt.hpp','gen/shards/shard_13.cpp']
    header=(src/'gd_rt.hpp').read_text('utf8');original=(SEMANTIC/'source/gd_rt.hpp').read_text('utf8')
    assert header.replace(frozen['declarations_only_header_addition'],'',1)==original
    objects=Path(tempfile.mkdtemp(prefix='native-integer-grid-prototype-'));(WORK/'objects.txt').write_text(str(objects),encoding='utf8')
    base_objects=Path((SEMANTIC/'objects.txt').read_text('utf8'));changed={'gd_rt','shard_13'}
    for name,digest in cached['objects_sha256'].items():
        assert sha(base_objects/(name+'.o'))==digest
        if name not in changed:shutil.copyfile(base_objects/(name+'.o'),objects/(name+'.o'))
    flags=runpy.run_path(str(src/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    def compile_one(name):
        source=src/('gd_rt.cpp' if name=='gd_rt' else 'gen/shards/shard_13.cpp')
        subprocess.run([compiler,*flags,'-c',str(source),'-o',str(objects/(name+'.o'))],check=True)
    print('Only2 changed native units,18 byte-identical cached objects; semantic tests, not timing',flush=True)
    with ThreadPoolExecutor(max_workers=2) as pool:list(pool.map(compile_one,sorted(changed)))
    names=list(cached['objects_sha256']);subprocess.run([compiler,*flags,'-shared','-static','-o',str(objects/'libgdcore.dll'),*[str(objects/(n+'.o')) for n in names]],check=True)
    assert all(sha(base_objects/(n+'.o'))==digest for n,digest in cached['objects_sha256'].items())
    out=WORK/'prototype.dll';shutil.copyfile(objects/'libgdcore.dll',out)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(out);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    audit=sim.lib.gd_diag_native_resolved_audit;audit.argtypes=[ctypes.c_int];audit.restype=None;audit(1)
    stat=sim.lib.gd_diag_native_integer_grid_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    stats_before=[stat(i) for i in range(6)]
    old_stat=sim.lib.gd_diag_native_resolved_stat;old_stat.argtypes=[ctypes.c_uint];old_stat.restype=ctypes.c_uint64
    old_before=[old_stat(i) for i in range(6)];result=measure(sim,jobs,1,0,continuous=True)
    reference=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==reference['inputs_sha256'] and result['results_sha256']==reference['results_sha256'] and result['matched_original_terminal']==200
    counts=[stat(i)-stats_before[i] for i in range(6)]
    old_counts=dict(zip(('generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback'),[old_stat(i)-old_before[i] for i in range(6)]))
    assert old_counts==json.loads((STAGE/'native_perf50/active_cooldown_bundle/release_audit.json').read_bytes())['coverage']
    assert counts[0]>0 and counts[2]>0 and counts[0]+counts[1]==652011
    record=dict(passed=True,semantic_only=True,dll_sha256=sha(out),baseline_dll_sha256=EXPECTED,
        verified_remote_backup=ARCHIVE,reused_native_objects=18,recompiled_native_units=2,
        unchanged_existing_header_definitions=True,source_manifest_sha256=sha(WORK/'transform.json'),
        semantic_base_receipt_sha256=sha(SEMANTIC/'build.json'),counts=dict(zip(('fast_queries','ordinary_queries','enabled_dicts','rejected_dicts','mode_conversions','reserved'),counts)),
        inputs_sha256=signature.hexdigest(),results_sha256=result['results_sha256'],matched_original_terminal=200,
        original_six_counters=old_counts,no_throughput_claim=True,not_for_deployment=True)
    report_path.write_text(json.dumps(record,indent=2)+'\n',encoding='utf8');print(json.dumps(record,indent=2))

if __name__=='__main__':main()
