"""Compare the actual three production methods with the saved old-DLL oracle."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
PROBE=WORK.parent/'spatial_probe'

def main():
    baseline=json.loads((PROBE/'correctness_baseline.json').read_bytes())
    screen=json.loads((PROBE/'screen.json').read_bytes())
    source=(STAGE/'test_native_spatial.cpp').read_text('utf8')
    assert hashlib.sha256((STAGE/'test_native_spatial.cpp').read_bytes()).hexdigest()==screen['test_source_sha256']
    assert baseline['passed'] and baseline['cases']==11760
    for name in ('getItemsInCells','countItemsInCells','getBagsInCells'):
        old=f'candidate?candidate_{name}(grid,args,argc):grid.fn_{name}(args,argc)'
        assert source.count(old)==1;source=source.replace(old,f'grid.fn_{name}(args,argc)')
    with tempfile.TemporaryDirectory(prefix='native-targeted-timer-production-') as directory:
        root=Path(directory);shutil.copyfile(WORK/'bundle.dll',root/'libgdcore.dll');exe=root/'test.exe'
        test=root/'production_test.cpp';test.write_text(source,encoding='utf8',newline='\n')
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-DGD_SPATIAL_PRODUCTION','-I',str(WORK/'bundle_src'),'-I',str(PROBE),str(test),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        raw=subprocess.check_output([str(exe),'--correctness-only'],text=True)
    report=json.loads(raw)
    assert report['passed'] and report['cases']==baseline['cases'] and report['case_hashes']==baseline['case_hashes']
    (WORK/'spatial_production_cases.json').write_text(raw,encoding='utf8')
    result=dict(passed=True,dll_sha256=hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest(),cases=report['cases'],
                all_original_case_hashes_equal=True,actual_production_methods_checked=True,legacy_dispatch_and_variant_counters_compared=True,
                original_reference_sha256=hashlib.sha256((PROBE/'correctness_baseline.json').read_bytes()).hexdigest(),
                test_adaptation='Only three candidate/original ternaries replaced by production DLL calls; all cases and hashes unchanged')
    (WORK/'spatial_tests.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(result,indent=2))

if __name__=='__main__':main()
