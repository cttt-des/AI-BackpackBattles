"""Check actual release functions against all saved independent old-DLL cases."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
PROBE=WORK.parent/'static_setup_probe'

def main():
    baseline=json.loads((PROBE/'correctness_baseline.json').read_bytes())
    assert baseline['passed'] and baseline['cases']==6436
    screen=json.loads((PROBE/'screen.json').read_bytes())
    assert hashlib.sha256((PROBE/'test_screen_snapshot.cpp').read_bytes()).hexdigest()==screen['test_source_sha256']
    with tempfile.TemporaryDirectory(prefix='native-event-capacity-production-') as directory:
        root=Path(directory);shutil.copyfile(WORK/'bundle.dll',root/'libgdcore.dll');exe=root/'test.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-DGD_STATIC_SETUP_PRODUCTION','-I',str(WORK/'bundle_src'),'-I',str(PROBE),str(STAGE/'test_native_static_setup.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        output=subprocess.check_output([str(exe),'--correctness-only'],text=True)
    report=json.loads(output)
    assert report['passed'] and report['cases']==baseline['cases'] and report['case_hashes']==baseline['case_hashes']
    (WORK/'static_setup_production_cases.json').write_text(output,encoding='utf8')
    result={'passed':True,'dll_sha256':hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest(),'cases':report['cases'],
            'all_original_case_hashes_equal':True,'actual_production_getters_setup_and_metrics_checked':True,
            'original_reference_sha256':hashlib.sha256((PROBE/'correctness_baseline.json').read_bytes()).hexdigest(),
            'test_fixture_revision':'Guard dictionary-alias comparison by both Kind tags; original screen source preserved; per-case oracle unchanged'}
    (WORK/'static_setup_tests.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(result,indent=2))

if __name__=='__main__':main()
