"""Prove finite-coordinate shortcuts against the actual deployed hash/equality implementation."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import psutil
from inspect_native_geometry_cost import STAGE,BASE,EXPECTED,sha
WORK=STAGE/'native_perf50/integer_grid_prototype'

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    WORK.mkdir(exist_ok=True);out=WORK/'slot_correctness.json';assert not out.exists()
    with tempfile.TemporaryDirectory(prefix='native-grid-slots-') as directory:
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'slots.exe'
        with (WORK/'slot_test_first.log').open('w',encoding='utf8') as log:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-I',str(STAGE),'-I',str(BASE),str(STAGE/'test_native_integer_grid_slots.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True,stdout=log,stderr=subprocess.STDOUT)
            result=subprocess.run([str(exe)],capture_output=True,text=True);log.write(result.stdout+result.stderr);log.flush()
            if result.returncode:print(result.stdout+result.stderr,flush=True)
            result.check_returncode();actual=json.loads(result.stdout)
    assert actual['passed'] and actual['cases']==132576
    actual.update(baseline_dll_sha256=EXPECTED,actual_current_dll_oracle=True,compared_index_fenv_and_all_mxcsr_exception_flags=True,
        helper_sha256=sha(STAGE/'native_integer_grid.hpp'),fixture_sha256=sha(STAGE/'test_native_integer_grid_slots.cpp'),no_throughput_claim=True)
    out.write_text(json.dumps(actual,indent=2)+'\n',encoding='utf8');print(json.dumps(actual,indent=2))

if __name__=='__main__':main()
