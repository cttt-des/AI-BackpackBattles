"""Independent actual-DLL oracles for runtime storage and all generated constructors."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_storage_bundle import STAGE,WORK,ACCEPTED,EXPECTED,sha

def verify(source,dll,out):
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not out.exists()
    records={};components={}
    for component,fixture,count in [('runtime','test_native_storage_runtime.cpp',1025),
                                     ('constructors','test_native_storage_constructors.cpp',86400)]:
        retained=out.parent/(component+'_correctness.json')
        if retained.exists():
            record=json.loads(retained.read_bytes())
            assert record['passed'] and record['cases']==count and record['dll_sha256']==sha(dll)
            assert record['baseline_dll_sha256']==EXPECTED and record['fixture_sha256']==sha(STAGE/fixture)
            before=json.loads((out.parent/(component+'_baseline_cases.json')).read_bytes())
            after=json.loads((out.parent/(component+'_candidate_cases.json')).read_bytes())
            assert before==after
            components[component]=record
            print('Retained first passed '+component+' result',flush=True)
            continue
        for name,headers,library in [('baseline',ACCEPTED/'bundle_src',ACCEPTED/'bundle.dll'),
                                     ('candidate',source,dll)]:
            assert sha(ACCEPTED/'bundle.dll')==EXPECTED
            with tempfile.TemporaryDirectory(prefix='native-storage-check-') as directory:
                root=Path(directory);shutil.copyfile(library,root/'libgdcore.dll');exe=root/(component+'.exe')
                log=out.parent/(component+'_'+name+'_first.log')
                with log.open('w',encoding='utf8') as stream:
                    command=['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off',
                        *(['-DSTORAGE_CANDIDATE'] if name=='candidate' else []),'-I',str(headers),
                        '-I',str(ACCEPTED),str(STAGE/fixture),str(root/'libgdcore.dll'),'-o',str(exe)]
                    subprocess.run(command,stdout=stream,stderr=subprocess.STDOUT,check=True)
                    run=subprocess.run([str(exe)],capture_output=True,text=True)
                    stream.write(run.stdout+run.stderr);stream.flush();run.check_returncode()
                raw=out.parent/(component+'_'+name+'_cases.json');assert not raw.exists()
                raw.write_text(run.stdout,encoding='utf8');records[name]=json.loads(run.stdout)
        before,after=records['baseline'],records['candidate']
        assert before['cases']==after['cases']==count
        differences=[i for i,(a,b) in enumerate(zip(before['hashes'],after['hashes'])) if a!=b]
        for key in before:
            if key!='hashes':assert before[key]==after[key],(component,key)
        record=dict(passed=not differences,cases=count,difference_count=len(differences),
                    first_differences=differences[:30],fixture_sha256=sha(STAGE/fixture),
                    baseline_dll_sha256=EXPECTED,dll_sha256=sha(dll),
                    original_metadata={k:v for k,v in before.items() if k!='hashes'},
                    actual_independent_baseline_dll=True)
        (out.parent/(component+'_correctness.json')).write_text(json.dumps(record,indent=2)+'\n',encoding='utf8')
        print(json.dumps(record,indent=2),flush=True)
        assert record['passed'],(component,differences[:30])
        components[component]=record
    result=dict(passed=True,cases=87425,dll_sha256=sha(dll),baseline_dll_sha256=EXPECTED,
                components=components,shared_fixture_sha256=sha(STAGE/'test_native_event_capacity.cpp'),
                constructor_inventory_sha256=sha(ACCEPTED/'native_type_constructor_test_cases.hpp'),
                raw_cases_sha256={p.name:sha(p) for p in out.parent.glob('*_cases.json')},
                canonical_values_alias_graphs_caps_watcher_epochs_rng_ids_fenv_mxcsr=True,
                independent_actual_baseline_dll=True,no_throughput_claim=True)
    out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result,indent=2))
    return result

if __name__=='__main__':verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'correctness.json')
