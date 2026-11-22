"""Cache native objects for quick semantic prototypes; formal timing still uses real PGO builds."""
import json
import os
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile
import psutil
from inspect_native_geometry_cost import STAGE,BASE,EXPECTED,ARCHIVE,ACCEPTED,sha
from build_native_hot_lto import build_dll
WORK=STAGE/'native_perf50/semantic_base_55b6'

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not WORK.exists();WORK.mkdir();src=WORK/'source'
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    assert subprocess.check_output(['git','ls-remote','--exit-code','origin','refs/heads/codex/native-perf50-verified']).decode().split()[0]==ARCHIVE
    shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    frozen={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    assert frozen==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    (WORK/'source_manifest.json').write_text(json.dumps(frozen,indent=2)+'\n',encoding='utf8')
    objects=Path(tempfile.mkdtemp(prefix='native-semantic-base-55b6-'));(WORK/'objects.txt').write_text(str(objects),encoding='utf8')
    os.environ.update(NATIVE_SIM_OBJ=str(objects),NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe',MAKE='D:/mingw64/bin/mingw32-make.exe')
    print('Caching20 native units, same O3/FP flags, max2 jobs; no release/performance claim',flush=True)
    out=WORK/'semantic.dll';build_dll(src,out,2,hot_units=set())
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    hashes={name:sha(objects/(name+'.o')) for name in names}
    for name in names:
        headers=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-h',str(objects/(name+'.o'))])
        assert b'.gnu.lto_' not in headers,name
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    import hashlib
    sim=load_simulator(out);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    result=measure(sim,jobs,1,0,continuous=True);old=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==old['inputs_sha256'] and result['results_sha256']==old['results_sha256'] and result['matched_original_terminal']==200
    assert frozen=={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    report=dict(passed=True,baseline_deployed_sha256=EXPECTED,semantic_dll_sha256=sha(out),verified_remote_backup=ARCHIVE,
        source_manifest_sha256=sha(WORK/'source_manifest.json'),objects_sha256=hashes,compiled_all20_native_units=True,
        floating_and_standard_optimization_flags=runpy.run_path(str(src/'build_windows.py'))['COMMON'],
        no_lto_sections_in_cached_objects=True,results_sha256=result['results_sha256'],matched_original_terminal=200,
        not_an_independent_truth_oracle=True,not_for_formal_timing_or_deployment=True,
        use='Only reuse ABI/source-identical objects for candidate semantics; oracle remains actual accepted55b6 DLL, release candidates keep full formal gates')
    (WORK/'build.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2))

if __name__=='__main__':main()
