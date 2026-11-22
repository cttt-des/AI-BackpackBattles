"""Separate old/new ABI executables compare original-DLL state and legacy counts."""
import json
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile
from prepare_native_targeted_timers import BASE,WORK,STAGE,EXPECTED,sha

def prepare_fields():
    text='#pragma once\n'
    for cls in ('CoreContext','CoreCharacter','CoreCombat','CoreGrid','CoreItem','CoreTimer'):
        name='Gd__gd_core__'+cls
        fields=re.findall(r'^    gd::GdVal (f_\w+);',(BASE/'gen/hdrs'/f'{name}.hpp').read_text('utf8'),re.M)
        assert fields
        text+=f'template<class F> void timer_visit({name}& object,F consume){{\n'+''.join(f' consume(object.{field});\n' for field in fields)+'}\n'
    p=WORK/'targeted_timer_fields.hpp'
    if p.exists():assert p.read_text('utf8')==text
    else:p.write_text(text,encoding='utf8',newline='\n')

def main():
    candidate='--candidate' in sys.argv
    label='candidate' if candidate else 'baseline'
    prepare_fields()
    source=WORK/'prototype_src' if candidate else BASE
    dll=WORK/'prototype.dll' if candidate else BASE/'libgdcore.dll'
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    expanded='--expanded' in sys.argv
    revision2='--revision2' in sys.argv
    name=label+('_revision2' if revision2 else '')+('_expanded' if expanded else '')
    output=WORK/(name+'_cases.json');assert not output.exists()
    log=WORK/f'{name}_cases_attempt_{len(list(WORK.glob(name+"_cases_attempt_*.log")))+1}.log'
    deps={p.name:sha(p) for p in (STAGE/'test_native_targeted_timers.cpp',WORK/'targeted_timer_fields.hpp')}
    with tempfile.TemporaryDirectory(prefix='native-targeted-timer-cases-') as directory:
        root=Path(directory);shutil.copyfile(dll,root/'libgdcore.dll');exe=root/'test.exe'
        with log.open('w',encoding='utf8') as out:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',*(['-DGD_TIMER_NEW'] if candidate else []),'-I',str(WORK),'-I',str(source),str(STAGE/'test_native_targeted_timers.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],stdout=out,stderr=subprocess.STDOUT,check=True)
            run=subprocess.run([str(exe)],capture_output=True,text=True)
            out.write(run.stdout+run.stderr)
        if run.returncode:print(run.stderr,flush=True)
        run.check_returncode();report=json.loads(run.stdout)
    assert report['cases']==(1760 if expanded else 1440)
    if expanded:
        retained=json.loads((WORK/(label+'_cases.json')).read_bytes())
        assert report['state_hashes'][:1440]==retained['state_hashes'] and report['legacy_hashes'][:1440]==retained['legacy_hashes']
        report['original1440_unchanged']=True
    report.update(dll_sha256=sha(dll),dependency_sha256=deps,independent_actual_dll=True)
    output.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    if candidate:
        baseline_path=WORK/('baseline_expanded_cases.json' if expanded else 'baseline_cases.json')
        old=json.loads(baseline_path.read_bytes());assert old['dependency_sha256']==deps
        mismatches={key:[i for i,(a,b) in enumerate(zip(old[key],report[key])) if a!=b] for key in ('state_hashes','legacy_hashes')}
        result=dict(passed=not any(mismatches.values()),cases=report['cases'],baseline_dll_sha256=EXPECTED,candidate_dll_sha256=sha(dll),
            baseline_receipt_sha256=sha(baseline_path),candidate_receipt_sha256=sha(output),layouts={'baseline':old['layout'],'candidate':report['layout']},
            mismatch_counts={k:len(v) for k,v in mismatches.items()},first_mismatches={k:v[:16] for k,v in mismatches.items()})
        (WORK/('differential_expanded_revision2.json' if revision2 else 'differential_expanded.json' if expanded else 'differential.json')).write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
        print(json.dumps(result,indent=2));assert result['passed'],result
    else:print(json.dumps(dict(original_cases=report['cases'],dll_sha256=sha(dll),layout=report['layout'])))

if __name__=='__main__':main()
