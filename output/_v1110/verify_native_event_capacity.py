"""Check the actual new DLL against the frozen deployed DLL, including aliases and FP flags."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_event_capacity import STAGE,WORK,ACCEPTED,EXPECTED,sha

def verify(source,dll,out):
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not out.exists();work=out.parent
    baseline_source=ACCEPTED/'bundle_src';baseline_dll=ACCEPTED/'bundle.dll'
    assert sha(baseline_dll)==EXPECTED
    records={}
    for name,headers,library in [('baseline',baseline_source,baseline_dll),('candidate',source,dll)]:
        with tempfile.TemporaryDirectory(prefix='native-event-param-test-') as directory:
            root=Path(directory);shutil.copyfile(library,root/'libgdcore.dll');exe=root/'params.exe'
            with (work/(name+'_event_param_first.log')).open('w',encoding='utf8') as log:
                subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',
                    '-I',str(headers),str(STAGE/'test_native_event_capacity.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],
                    stdout=log,stderr=subprocess.STDOUT,check=True)
                run=subprocess.run([str(exe)],capture_output=True,text=True);log.write(run.stdout+run.stderr);log.flush()
                if run.returncode:print(run.stdout+run.stderr,flush=True)
                run.check_returncode();records[name]=json.loads(run.stdout)
                result_path=work/(name+'_event_param_cases.json');assert not result_path.exists()
                result_path.write_text(run.stdout,encoding='utf8')
    old,new=records['baseline'],records['candidate'];assert old['cases']==new['cases']==1024
    differences=[i for i,(a,b) in enumerate(zip(old['hashes'],new['hashes'])) if a!=b]
    assert all(old[k]==new[k] for k in ('GdDict','GdVal','CoreEvent','BattleCtx'))
    assert new['small_cap_observations']>old['small_cap_observations']
    report=dict(passed=not differences,cases=1024,difference_count=len(differences),first_differences=differences[:30],
        baseline_dll_sha256=EXPECTED,dll_sha256=sha(dll),actual_independent_baseline_dll_oracle=True,
        canonical_entries_order_values_aliases_rng_ids_fenv_mxcsr=True,rounding_modes=4,daz_ftz_modes=4,
        baseline_small_capacity_observations=old['small_cap_observations'],candidate_small_capacity_observations=new['small_cap_observations'],
        layouts={k:new[k] for k in ('GdDict','GdVal','CoreEvent','BattleCtx')},
        fixture_sha256=sha(STAGE/'test_native_event_capacity.cpp'),no_throughput_claim=True)
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2));assert report['passed'],differences[:30]
    return report

if __name__=='__main__':verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'correctness.json')
