"""Keep a concrete cross-context counterexample and verify the ownership repair."""
import argparse
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prepare_native_targeted_timers import BASE,WORK,STAGE,EXPECTED,sha

def main():
    p=argparse.ArgumentParser();p.add_argument('--candidate',action='store_true');p.add_argument('--revision',type=int,default=1);args=p.parse_args()
    name=f'ownership_candidate_revision{args.revision}' if args.candidate else 'ownership_baseline'
    output=WORK/(name+'.json');assert not output.exists()
    dll=WORK/'prototype.dll' if args.candidate else BASE/'libgdcore.dll';source=WORK/'prototype_src' if args.candidate else BASE
    log=WORK/(name+'.log');assert not log.exists()
    with tempfile.TemporaryDirectory(prefix='native-targeted-timer-ownership-') as directory:
        root=Path(directory);shutil.copyfile(dll,root/'libgdcore.dll');exe=root/'test.exe'
        with log.open('w',encoding='utf8') as out:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',*(['-DGD_TIMER_NEW'] if args.candidate else []),'-I',str(WORK),'-I',str(source),str(STAGE/'test_targeted_timer_ownership.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],stdout=out,stderr=subprocess.STDOUT,check=True)
            run=subprocess.run([str(exe)],text=True,capture_output=True);out.write(run.stdout+run.stderr)
        run.check_returncode();report=json.loads(run.stdout)
    assert report['cases']==64;report.update(dll_sha256=sha(dll),source_sha256=sha(STAGE/'test_targeted_timer_ownership.cpp'))
    output.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    if args.candidate:
        old=json.loads((WORK/'ownership_baseline.json').read_bytes());assert old['source_sha256']==report['source_sha256']
        mismatches={k:[i for i,(a,b) in enumerate(zip(old[k],report[k])) if a!=b] for k in ('state_hashes','legacy_hashes')}
        result=dict(passed=not any(mismatches.values()),cases=64,revision=args.revision,candidate_dll_sha256=sha(dll),baseline_dll_sha256=EXPECTED,
            mismatches=mismatches,baseline_receipt_sha256=sha(WORK/'ownership_baseline.json'),candidate_receipt_sha256=sha(output))
        (WORK/f'ownership_differential_revision{args.revision}.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
        print(json.dumps({k:v for k,v in result.items() if k!='mismatches'}|dict(mismatch_counts={k:len(v) for k,v in mismatches.items()}),indent=2))
        if args.revision>=2:assert result['passed']
    else:print(json.dumps(dict(cases=64,baseline_dll_sha256=EXPECTED)))

if __name__=='__main__':main()
