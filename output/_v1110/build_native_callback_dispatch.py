"""Build a semantic DLL for the side table and literal callback entry."""
from concurrent.futures import ThreadPoolExecutor
import ctypes
import hashlib
import json
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_callback_dispatch import STAGE,BASE,WORK,ACCEPTED,EXPECTED,sha

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    source=WORK/'prototype_src';out=WORK/'prototype.dll';assert not out.exists()
    frozen=json.loads((WORK/'transform.json').read_bytes())['source_sha256']
    assert frozen=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    old=STAGE/'native_perf50/literal_spans_prototype'
    original=Path((old/'objects.txt').read_text('utf8'))
    objects=Path(tempfile.mkdtemp(prefix='native-callback-dispatch-semantic-'))
    (WORK/'objects.txt').write_text(str(objects),encoding='utf8')
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    changes={'gd_rt':source/'gd_rt.cpp','shard_12':source/'gen/shards/shard_12.cpp'}
    hashes={n:sha(original/(n+'.o')) for n in names}
    for name in names:
        if name not in changes:shutil.copyfile(original/(name+'.o'),objects/(name+'.o'))
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    def compile_one(row):
        name,path=row
        with (WORK/(name+'_compile_first.log')).open('wb') as log:
            subprocess.run([compiler,*flags,'-c',str(path),'-o',str(objects/(name+'.o'))],stdout=log,stderr=subprocess.STDOUT,check=True)
    with ThreadPoolExecutor(max_workers=2) as pool:list(pool.map(compile_one,changes.items()))
    with (WORK/'link_first.log').open('wb') as log:
        subprocess.run([compiler,*flags,'-shared','-static','-o',str(objects/'libgdcore.dll'),
            *[str(objects/(name+'.o')) for name in names]],stdout=log,stderr=subprocess.STDOUT,check=True)
    assert hashes=={name:sha(original/(name+'.o')) for name in names}
    shutil.copyfile(objects/'libgdcore.dll',out)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(out);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    audit=sim.lib.gd_diag_native_resolved_audit;audit.argtypes=[ctypes.c_int];audit.restype=None;audit(1)
    stat=sim.lib.gd_diag_native_resolved_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    extra=sim.lib.gd_diag_native_extra_callback_stat;extra.argtypes=[ctypes.c_uint];extra.restype=ctypes.c_uint64
    before=[stat(i) for i in range(6)];before_extra=[extra(i) for i in range(2)]
    result=measure(sim,jobs,1,0,continuous=True)
    counts=dict(zip(('generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback'),[stat(i)-before[i] for i in range(6)]))
    coverage=[extra(i)-before_extra[i] for i in range(2)]
    assert counts==json.loads((ACCEPTED/'release_audit.json').read_bytes())['coverage'],counts
    assert all(n>0 for n in coverage),coverage
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert result['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    assert result['matched_original_terminal']==200 and sha(BASE/'libgdcore.dll')==EXPECTED
    report=dict(passed=True,semantic_only=True,dll_sha256=sha(out),baseline_dll_sha256=EXPECTED,
        source_manifest_sha256=sha(WORK/'transform.json'),reused_objects=18,recompiled_units=2,
        old_object_layouts_and128_slot_rows_unchanged=True,added_inline_entry_unused_in_reused_units=True,
        original_six_counters=counts,extra_callback_coverage=dict(zip(('generic_funcref','private_literal'),coverage)),
        inputs_sha256=signature.hexdigest(),results_sha256=result['results_sha256'],matched_original_terminal=200,
        no_throughput_claim=True,not_for_deployment=True)
    (WORK/'build.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2),flush=True)

if __name__=='__main__':main()
