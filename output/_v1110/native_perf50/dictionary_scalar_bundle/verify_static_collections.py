import sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[2]))
"""Compare actual production functions to all independent old-DLL case hashes."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
PROBE=WORK.parent/'static_collections_probe'
def main():
    baseline=json.loads((PROBE/'correctness_baseline.json').read_bytes());assert baseline['cases']==13440
    with tempfile.TemporaryDirectory(prefix='native-static-production-test-') as directory:
        root=Path(directory);shutil.copyfile(WORK/'bundle.dll',root/'libgdcore.dll');exe=root/'test.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-DGD_STATIC_PRODUCTION','-I',str(WORK/'bundle_src'),'-I',str(PROBE),str(STAGE/'test_native_static_collections.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        output=subprocess.check_output([str(exe),'--correctness-only'],text=True)
        record=json.loads(output);assert record['passed'] and record['cases']==baseline['cases'] and record['case_hashes']==baseline['case_hashes']
    (WORK/'static_collection_production_cases.json').write_text(output,encoding='utf8')
    result={'passed':True,'dll_sha256':hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest(),
        'cases':record['cases'],'all_original_case_hashes_equal':True,'actual_production_methods_checked':True,
        'rounding_modes':4,'input_kind_and_boundary_cases':40,'original_reference_sha256':hashlib.sha256((PROBE/'correctness_baseline.json').read_bytes()).hexdigest()}
    (WORK/'static_collections_tests.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(result,indent=2))
if __name__=='__main__':main()
