"""Check final production damage settlement against independent old-DLL receipts."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
PROBE=WORK.parent/'damage_combo_probe'
def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def main():
    transform=json.loads((WORK/'transform.json').read_bytes())
    analysis=json.loads((PROBE/'source_analysis.json').read_bytes())
    assert transform['helper_sha256']==analysis['helper_sha256']
    import sys
    sys.path.insert(0,str(STAGE))
    from prepare_native_damage_combo import HELPER
    source=(WORK/'bundle_src/gen/shards/shard_02.cpp').read_text('utf8')
    assert source.count(HELPER)==1 and 'probe_dll_type_info' not in source
    assert hashlib.sha256(HELPER.encode()).hexdigest()==analysis['helper_sha256']
    reports={}
    with tempfile.TemporaryDirectory(prefix='native-damage-final-') as directory:
        root=Path(directory);shutil.copyfile(WORK/'bundle.dll',root/'libgdcore.dll')
        for name,cpp,reference,output in [
            ('parent','test_native_damage_records_extended.cpp','extended_correctness.json','damage_parent_production_cases.json'),
            ('active','test_native_damage_active_helpers.cpp','active_helper_cases.json','damage_active_production_cases.json'),
            ('source','test_native_damage_source_helpers.cpp','source_helper_cases.json','damage_source_production_cases.json')]:
            expected=json.loads((PROBE/reference).read_bytes());exe=root/(name+'.exe')
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-DGD_DAMAGE_PRODUCTION','-I',str(PROBE),'-I',str(WORK/'bundle_src'),str(STAGE/cpp),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
            raw=subprocess.check_output([str(exe)],text=True);actual=json.loads(raw)
            assert actual['passed'] and actual['cases']==expected['cases'] and actual['case_hashes']==expected['case_hashes'],name
            if 'legacy_counter_hashes' in expected:assert actual['legacy_counter_hashes']==expected['legacy_counter_hashes']
            (WORK/output).write_text(raw,encoding='utf8');reports[name]=dict(cases=actual['cases'],reference_sha256=sha(PROBE/reference),all_case_hashes_equal=True)
    assert reports['parent']['cases']==12920 and reports['active']['cases']==6480 and reports['source']['cases']==10464
    report=dict(passed=True,dll_sha256=sha(WORK/'bundle.dll'),actual_production_parent_damage_cases=19400,frozen_helper_boundary_cases=10464,
                helper_scope='Source probes use the same frozen helper body in the test EXE plus final DLL original class methods; parent and active cases call actual production takeDamage',
                independent_receipts=reports,original_legacy_counters_equal=True,probe_only_rtti_adaptation_not_in_production=True)
    (WORK/'damage_combo_tests.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2))
if __name__=='__main__':main()
