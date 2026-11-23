"""Compare the real new factory with independent construction in production DLL."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_event_factory import STAGE, WORK, ACCEPTED, EXPECTED, sha

def verify(source,dll,out):
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not out.exists()
    records={}
    for name,headers,library in [('baseline',ACCEPTED/'bundle_src',ACCEPTED/'bundle.dll'),('candidate',source,dll)]:
        with tempfile.TemporaryDirectory(prefix='native-event-factory-test-') as directory:
            root=Path(directory);shutil.copyfile(library,root/'libgdcore.dll');exe=root/'factory.exe'
            with (out.parent/(name+'_factory_first.log')).open('w',encoding='utf8') as log:
                subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',
                    *(['-DCANDIDATE_FACTORY'] if name=='candidate' else []),'-I',str(headers),
                    str(STAGE/'test_native_event_factory.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],
                    stdout=log,stderr=subprocess.STDOUT,check=True)
                run=subprocess.run([str(exe)],capture_output=True,text=True)
                log.write(run.stdout+run.stderr);log.flush();run.check_returncode()
                records[name]=json.loads(run.stdout)
                (out.parent/(name+'_factory_cases.json')).write_text(run.stdout,encoding='utf8')
    old,new=records['baseline'],records['candidate']
    assert old['cases']==new['cases']==5120
    differences=[i for i,(a,b) in enumerate(zip(old['hashes'],new['hashes'])) if a!=b]
    assert all(old[k]==new[k] for k in ('CoreEvent','GdDict','GdVal','BattleCtx'))
    report=dict(passed=not differences,cases=5120,first_differences=differences[:30],difference_count=len(differences),
        baseline_dll_sha256=EXPECTED,dll_sha256=sha(dll),actual_independent_baseline_dll_oracle=True,
        constructor_defaults_coercions_aliases_growth_reinit_rng_ids_fenv_mxcsr=True,
        fixture_sha256=sha(STAGE/'test_native_event_factory.cpp'),shared_fixture_sha256=sha(STAGE/'test_native_event_capacity.cpp'),
        raw_cases_sha256={n:sha(out.parent/(n+'_factory_cases.json')) for n in records},
        layouts={k:new[k] for k in ('CoreEvent','GdDict','GdVal','BattleCtx')},no_throughput_claim=True)
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2));assert report['passed'],differences[:30]
    return report

if __name__=='__main__':
    verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'correctness.json')
