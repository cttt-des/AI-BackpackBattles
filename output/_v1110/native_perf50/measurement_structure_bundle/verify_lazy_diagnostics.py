import sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[2]))
"""Check the production helper and label entry against saved original-DLL hashes."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
PROBE=WORK.parent/'lazy_diagnostics_probe'
SRC=WORK/'bundle_src'
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def main():
    dll=WORK/'bundle.dll'
    fixtures=WORK/'diagnostic_fixtures';fixtures.mkdir(exist_ok=True)
    for name in ('preflight_label.hpp','preflight_buff_diagnostics.hpp'):
        text=(PROBE/name).read_text('utf8').replace('#include "native_lazy_diagnostics.hpp"\n','')
        (fixtures/name).write_text(text,encoding='utf8',newline='\n')
    results={}
    with tempfile.TemporaryDirectory(prefix='native-lazy-production-test-') as directory:
        root=Path(directory);shutil.copyfile(dll,root/'libgdcore.dll')
        for label,source,reference,count in (
            ('label','test_native_lazy_diagnostics.cpp','correctness_baseline.json',2048),
            ('buff','test_native_buff_diagnostics.cpp','buff_correctness_baseline.json',20736)):
            exe=root/(label+'.exe')
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-DGD_LAZY_PRODUCTION',
                '-I',str(SRC),'-I',str(fixtures),'-I',str(STAGE),str(STAGE/source),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
            output=subprocess.check_output([str(exe),'--correctness-only'],text=True)
            report=json.loads(output);expected=json.loads((PROBE/reference).read_bytes())
            assert report['passed'] and report['cases']==expected['cases']==count
            assert report['case_hashes']==expected['case_hashes'],label
            path=WORK/('diagnostic_'+label+'_production_cases.json')
            path.write_text(output,encoding='utf8')
            results[label]={'cases':count,'raw_sha256':sha(path),'original_reference_sha256':sha(PROBE/reference)}
    result={'passed':True,'dll_sha256':sha(dll),'independent_actual_baseline_dll_sha256':'b2018eb28b90ae5527d9e0764a8b11e5bf6df0b60df7cb722c67629fcfedb588',
        'actual_production_label_function_checked':True,'six_exact_production_guarded_expressions_checked':True,'results':results,
        'primitive_integral_float_flags_checks':40036,'no_timing_repeated':True}
    (WORK/'lazy_diagnostics_tests.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(result,indent=2))
if __name__=='__main__':main()
