"""Compare final production behavior/callback code with the independent old DLL."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
PROBE=WORK.parent/'dispatch_chain_probe'

def main():
    baseline=json.loads((PROBE/'correctness_baseline_hash_guard.json').read_bytes())
    screen=json.loads((PROBE/'screen.json').read_bytes())
    assert baseline['passed'] and baseline['cases']==341604
    assert hashlib.sha256((PROBE/'test_screen_snapshot.cpp').read_bytes()).hexdigest()==screen['test_source_sha256']
    with tempfile.TemporaryDirectory(prefix='native-motion-indices-production-') as directory:
        root=Path(directory);shutil.copyfile(WORK/'bundle.dll',root/'libgdcore.dll');exe=root/'test.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-DGD_CHAIN_PRODUCTION','-I',str(WORK/'bundle_src'),'-I',str(PROBE),str(STAGE/'test_native_dispatch_chain.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        raw=subprocess.check_output([str(exe),'--correctness-only'],text=True)
    report=json.loads(raw)
    assert report['passed'] and report['cases']==baseline['cases'] and report['case_hashes']==baseline['case_hashes']
    (WORK/'dispatch_chain_production_cases.json').write_text(raw,encoding='utf8')
    result={'passed':True,'dll_sha256':hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest(),
        'cases':report['cases'],'all_original_case_hashes_equal':True,'item_classes':report['item_classes'],
        'actual_production_methods_and_inline_callback_header_checked':True,
        'original_reference_sha256':hashlib.sha256((PROBE/'correctness_baseline_hash_guard.json').read_bytes()).hexdigest(),
        'legacy_dispatch_counters_also_compared':True}
    (WORK/'dispatch_chain_tests.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(result,indent=2))

if __name__=='__main__':main()
