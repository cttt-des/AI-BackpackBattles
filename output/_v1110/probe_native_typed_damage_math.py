"""Check scalar blocks against actual baseline DLL operators, before whole-kernel compilation."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prepare_native_typed_hotchain import BASE,WORK,STAGE,EXPECTED,sha

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    out=WORK/'math_correctness.json';assert not out.exists()
    attempt=len(list(WORK.glob('math_attempt_*.log')))+1;log=WORK/f'math_attempt_{attempt}.log'
    with tempfile.TemporaryDirectory(prefix='native-typed-damage-math-') as directory:
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'math.exe'
        with log.open('w',encoding='utf8') as output:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-I',str(STAGE),'-I',str(BASE),str(STAGE/'test_native_typed_damage_math.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],stdout=output,stderr=subprocess.STDOUT,check=True)
            result=subprocess.run([str(exe)],capture_output=True,text=True);output.write(result.stdout+result.stderr)
        if result.returncode:print(result.stdout+result.stderr,flush=True)
        result.check_returncode();report=json.loads(result.stdout)
    report.update(baseline_dll_sha256=EXPECTED,independent_dll_math=True,helper_sha256=sha(STAGE/'native_typed_damage_math.hpp'),fixture_sha256=sha(STAGE/'test_native_typed_damage_math.cpp'))
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2))

if __name__=='__main__':main()
