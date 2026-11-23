"""Actual baseline and candidate DLL differential for lazy event arguments."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_literal_spans import STAGE,WORK,ACCEPTED,EXPECTED,sha

def verify(source,dll,out):
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not out.exists()
    fixture=STAGE/'test_native_literal_spans.cpp';records={}
    for name,headers,library in [('baseline',ACCEPTED/'bundle_src',ACCEPTED/'bundle.dll'),('candidate',source,dll)]:
        assert sha(ACCEPTED/'bundle.dll')==EXPECTED
        with tempfile.TemporaryDirectory(prefix='native-literal-check-') as directory:
            root=Path(directory);shutil.copyfile(library,root/'libgdcore.dll');exe=root/'check.exe'
            log=out.parent/(name+'_literal_first.log')
            with log.open('w',encoding='utf8') as stream:
                command=['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off',
                    *(['-DLITERAL_SPANS_CANDIDATE'] if name=='candidate' else []),'-I',str(headers),
                    str(fixture),str(root/'libgdcore.dll'),'-o',str(exe)]
                subprocess.run(command,stdout=stream,stderr=subprocess.STDOUT,check=True)
                run=subprocess.run([str(exe)],capture_output=True,text=True)
                stream.write(run.stdout+run.stderr);stream.flush();run.check_returncode()
            raw=out.parent/(name+'_literal_cases.json');assert not raw.exists()
            raw.write_text(run.stdout,encoding='utf8');records[name]=json.loads(run.stdout)
    before,after=records['baseline'],records['candidate']
    assert before['passed'] and after['passed'] and before['cases']==after['cases']==5184
    assert after['span_checks']>0 and before['span_checks']==0
    differences=[i for i,(a,b) in enumerate(zip(before['hashes'],after['hashes'])) if a!=b]
    result=dict(passed=not differences,cases=before['cases'],difference_count=len(differences),
        first_differences=differences[:60],canonical_no_materialization_checks=after['span_checks'],
        fixture_sha256=sha(fixture),baseline_dll_sha256=EXPECTED,dll_sha256=sha(dll),
        raw_cases_sha256={p.name:sha(p) for p in out.parent.glob('*_literal_cases.json')},
        independent_actual_baseline_dll=True,no_throughput_claim=True)
    out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result,indent=2),flush=True)
    assert result['passed'],differences[:60]
    return result

if __name__=='__main__':verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'correctness.json')
