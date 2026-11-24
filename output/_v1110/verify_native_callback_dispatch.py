"""Independent real-DLL differential for exact callbacks and unsafe boundaries."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_callback_dispatch import STAGE,WORK,ACCEPTED,EXPECTED,sha

def symbols_header():
    proof=json.loads((WORK/'callback_source_proof.json').read_bytes())
    symbols=proof['selected'];assert len(symbols)==65
    text='#pragma once\n#include <array>\n'
    text+='static constexpr std::array<gd::SymId,65> callback_test_symbols={'+','.join(symbols)+'};\n'
    for key,name in [('darksaber','onDebuffsChanged'),('djinn','checkStacks'),('acorn','onLuckyChanged')]:
        matches=[s for s in symbols if s.startswith('SYM_GEN_'+name+'_')];assert len(matches)==1
        text+='static constexpr gd::SymId callback_'+key+'_symbol='+matches[0]+';\n'
    return text

def verify(source,dll,out):
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not out.exists();fixture=STAGE/'test_native_callback_dispatch.cpp'
    header=out.parent/'callback_test_symbols.hpp';header_text=symbols_header()
    if header.exists():assert header.read_text('utf8')==header_text
    else:header.write_text(header_text,encoding='utf8',newline='\n')
    records={}
    for label,headers,library in [('baseline',ACCEPTED/'bundle_src',ACCEPTED/'bundle.dll'),('candidate',source,dll)]:
        assert sha(ACCEPTED/'bundle.dll')==EXPECTED
        with tempfile.TemporaryDirectory(prefix='native-extra-callback-check-') as directory:
            root=Path(directory);shutil.copyfile(library,root/'libgdcore.dll');exe=root/'check.exe'
            log=out.parent/(label+'_callbacks_first.log')
            with log.open('w',encoding='utf8') as stream:
                command=['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off',
                    *(['-DCALLBACK_DISPATCH_CANDIDATE'] if label=='candidate' else []),'-I',str(headers),
                    '-I',str(out.parent),str(fixture),str(root/'libgdcore.dll'),'-o',str(exe)]
                subprocess.run(command,stdout=stream,stderr=subprocess.STDOUT,check=True)
                run=subprocess.run([str(exe)],capture_output=True,text=True)
                stream.write(run.stdout+run.stderr);stream.flush();run.check_returncode()
            raw=out.parent/(label+'_callbacks_cases.json');assert not raw.exists()
            raw.write_text(run.stdout,encoding='utf8');records[label]=json.loads(run.stdout)
    before,after=records['baseline'],records['candidate']
    assert before['passed'] and after['passed'] and before['cases']==after['cases']==126192
    assert before['unknown_cases']==after['unknown_cases']==15600
    assert before['fast_assertions']==0 and after['fast_assertions']>0
    differences=[i for i,(a,b) in enumerate(zip(before['hashes'],after['hashes'])) if a!=b]
    result=dict(passed=not differences,cases=before['cases'],unknown_override_cases=15600,
        real_generated_handler_cases=110592,difference_count=len(differences),first_differences=differences[:60],
        fast_no_materialization_assertions=after['fast_assertions'],fixture_sha256=sha(fixture),
        symbols_header_sha256=sha(header),baseline_dll_sha256=EXPECTED,dll_sha256=sha(dll),
        raw_cases_sha256={p.name:sha(p) for p in out.parent.glob('*_callbacks_cases.json')},
        independent_actual_baseline_dll=True,no_throughput_claim=True)
    out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result,indent=2),flush=True)
    assert result['passed'],differences[:60]
    return result

if __name__=='__main__':verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'correctness.json')
