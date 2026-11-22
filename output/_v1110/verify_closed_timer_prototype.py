"""Keep all independent open-runtime cases and test the sealed ABI boundary."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prepare_native_closed_timer import WORK,BASE,STAGE,EXPECTED,sha
ORACLE=WORK.parent/'targeted_timer_prototype'

def main():
    assert not (WORK/'correctness.json').exists()
    engine=(BASE/'engine_wrapper.cpp').read_text('utf8');start=engine.index('extern "C" {\n\nstruct PackedEffect');stop=engine.index('void gd_sim_init()',start)
    abi=engine[start:stop]+'''void gd_sim_init();
void gd_sim_reset_registry();
void gd_sim_register_character(int32_t,const char*,double,double,double,int32_t);
void gd_sim_run_one(const PackedSide*,const PackedSide*,const BattleOptions*,BattleResult*);
}
'''
    (WORK/'frozen_timer_packed_abi.hpp').write_text(abi,encoding='utf8',newline='\n')
    reports={}
    with tempfile.TemporaryDirectory(prefix='native-closed-timer-tests-') as directory:
        root=Path(directory)
        for name,cpp,receipt,n in [('owners','test_native_targeted_timers.cpp','baseline_expanded_cases.json',1760),('safety','test_targeted_timer_safety.cpp','baseline_safety.json',192),('ownership','test_targeted_timer_ownership.cpp','ownership_baseline.json',64)]:
            shutil.copyfile(WORK/'prototype.dll',root/'libgdcore.dll');exe=root/(name+'.exe')
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-DGD_TIMER_NEW','-I',str(ORACLE),'-I',str(WORK/'prototype_src'),str(STAGE/cpp),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
            raw=subprocess.check_output([str(exe)],text=True);actual=json.loads(raw);old=json.loads((ORACLE/receipt).read_bytes())
            assert actual['cases']==n and actual['state_hashes']==old['state_hashes'] and actual['legacy_hashes']==old['legacy_hashes'],name
            (WORK/(name+'_cases.json')).write_text(raw,encoding='utf8');reports[name]=dict(cases=n,old_receipt_sha256=sha(ORACLE/receipt),all_original_states_and_legacy_counters_equal=True)
        results={}
        for label,source,dll in [('baseline',BASE,BASE/'libgdcore.dll'),('candidate',WORK/'prototype_src',WORK/'prototype.dll')]:
            shutil.copyfile(dll,root/'libgdcore.dll');exe=root/(label+'_registry.exe')
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-std=c++20','-ffp-contract=off',*(['-DGD_TIMER_CLOSED'] if label=='candidate' else []),'-I',str(WORK),'-I',str(source),str(STAGE/'test_closed_timer_registry.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
            raw=subprocess.check_output([str(exe)],text=True);results[label]=json.loads(raw);(WORK/(label+'_registry.json')).write_text(raw,encoding='utf8')
        assert results['baseline']==results['candidate'] and results['candidate']['passed']
    report=dict(passed=True,dll_sha256=sha(WORK/'prototype.dll'),baseline_dll_sha256=EXPECTED,open_runtime_cases=2016,
        sealed_registry_boundary_cases=4,three_packed_fights_match_original=True,foreign_registration_disables_sealed_mode_permanently=True,
        original_open_runtime_observer_and_cross_context_cases_retained=True,receipts=reports,
        no_performance_or_deployment_claim=True)
    (WORK/'correctness.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()
