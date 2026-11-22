"""Keep exact NaN/short-circuit and generic fallback coverage for typed probes."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prepare_native_damage_combo import BASE,STAGE,WORK,EXPECTED,sha

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    assert not (WORK/'source_helper_cases.json').exists()
    with tempfile.TemporaryDirectory(prefix='native-damage-source-helpers-') as directory:
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'test.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-I',str(WORK),'-I',str(BASE),str(STAGE/'test_native_damage_source_helpers.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        result=subprocess.run([str(exe)],capture_output=True,text=True)
        (WORK/'source_helper_cases.log').write_text(result.stdout+result.stderr,encoding='utf8')
        if result.returncode:print(result.stderr,flush=True)
        result.check_returncode();report=json.loads(result.stdout)
    report.update(baseline_dll_sha256=EXPECTED,test_source_sha256=sha(STAGE/'test_native_damage_source_helpers.cpp'),helper_header_sha256=sha(WORK/'preflight_damage_records.hpp'))
    (WORK/'source_helper_cases.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({key:value for key,value in report.items() if key!='case_hashes'},indent=2))

if __name__=='__main__':main()
