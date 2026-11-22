"""Preliminary independent-DLL checks before expanding the damage-chain matrix."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prepare_native_damage_records import BASE,STAGE,WORK,EXPECTED,sha

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    attempt=len(list(WORK.glob('preliminary_*.log')))+1
    log=WORK/f'preliminary_{attempt}.log'
    with tempfile.TemporaryDirectory(prefix='native-damage-records-') as directory:
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'test.exe'
        with log.open('w',encoding='utf8') as output:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-I',str(WORK),'-I',str(BASE),str(STAGE/'test_native_damage_records.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],stdout=output,stderr=subprocess.STDOUT,check=True)
            result=subprocess.run([str(exe)],capture_output=True,text=True)
            output.write(result.stdout+result.stderr)
        if result.returncode:print(result.stdout+result.stderr,flush=True)
        result.check_returncode();report=json.loads(result.stdout)
    report.update(baseline_dll_sha256=EXPECTED,test_source_sha256=sha(STAGE/'test_native_damage_records.cpp'),header_sha256=sha(WORK/'preflight_damage_records.hpp'),no_performance_claim=True)
    target=WORK/f'preliminary_{attempt}.json';assert not target.exists()
    target.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()
