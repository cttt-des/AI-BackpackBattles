"""Extra unknown-class, lifetime, mutation nesting and overflow differentials."""
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
from prepare_native_targeted_timers import BASE,WORK,STAGE,EXPECTED,sha

def main():
    candidate='--candidate' in sys.argv;label='candidate' if candidate else 'baseline'
    fields=WORK/'actual_targeted_timer_fixture.hpp'
    text=(STAGE/'test_native_targeted_timers.cpp').read_text('utf8').split('int main(){',1)[0]
    if fields.exists():assert fields.read_text('utf8')==text
    else:fields.write_text(text,encoding='utf8',newline='\n')
    name=label+('_revision2' if '--revision2' in sys.argv else '')
    output=WORK/(name+'_safety.json');assert not output.exists()
    dll=WORK/'prototype.dll' if candidate else BASE/'libgdcore.dll';source=WORK/'prototype_src' if candidate else BASE
    log=WORK/f'{name}_safety_attempt_{len(list(WORK.glob(name+"_safety_attempt_*.log")))+1}.log'
    with tempfile.TemporaryDirectory(prefix='native-targeted-timer-safety-') as directory:
        root=Path(directory);shutil.copyfile(dll,root/'libgdcore.dll');exe=root/'test.exe'
        with log.open('w',encoding='utf8') as out:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',*(['-DGD_TIMER_NEW'] if candidate else []),'-I',str(WORK),'-I',str(source),str(STAGE/'test_targeted_timer_safety.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],stdout=out,stderr=subprocess.STDOUT,check=True)
            r=subprocess.run([str(exe)],text=True,capture_output=True);out.write(r.stdout+r.stderr)
        if r.returncode:print(r.stderr,flush=True)
        r.check_returncode();report=json.loads(r.stdout)
    assert report['cases']==192
    report.update(dll_sha256=sha(dll),source_sha256=sha(STAGE/'test_targeted_timer_safety.cpp'),fixture_sha256=sha(fields))
    output.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    if candidate:
        old=json.loads((WORK/'baseline_safety.json').read_bytes())
        assert old['source_sha256']==report['source_sha256'] and old['fixture_sha256']==report['fixture_sha256']
        result=dict(passed=all(old[k]==report[k] for k in ('state_hashes','legacy_hashes')),cases=192,
            first_mismatches={k:[i for i,(a,b) in enumerate(zip(old[k],report[k])) if a!=b][:16] for k in ('state_hashes','legacy_hashes')},
            baseline_dll_sha256=EXPECTED,candidate_dll_sha256=sha(dll),baseline_receipt_sha256=sha(WORK/'baseline_safety.json'),candidate_receipt_sha256=sha(output))
        (WORK/('safety_differential_revision2.json' if '--revision2' in sys.argv else 'safety_differential.json')).write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
        print(json.dumps(result,indent=2));assert result['passed'],result
    else:print(json.dumps(dict(cases=192,baseline_dll_sha256=EXPECTED)))

if __name__=='__main__':main()
