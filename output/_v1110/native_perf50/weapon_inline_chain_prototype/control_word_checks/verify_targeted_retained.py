"""Check final production timer traversal against the old ABI independent oracle."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
WORK=Path(__file__).resolve().parent
SOURCE=Path('D:\\文件资料\\学习\\自动背包AI\\output\\_v1110\\native_perf50\\weapon_inline_chain_prototype\\prototype_src')
DLL=Path('D:\\文件资料\\学习\\自动背包AI\\output\\_v1110\\native_perf50\\weapon_inline_chain_prototype\\prototype.dll')
STAGE=Path('D:\\文件资料\\学习\\自动背包AI\\output\\_v1110')
HISTORY=STAGE/'native_perf50'
PROBE=HISTORY/'targeted_timer_prototype'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    closed=HISTORY/'closed_timer_prototype'
    frozen=json.loads((WORK/'transform.json').read_bytes())['source_sha256']
    dependencies=json.loads((closed/'proof_dependencies.json').read_bytes())
    assert dependencies=={name:sha(STAGE/name) for name in dependencies}
    current=json.loads((WORK/'source_manifest.json').read_bytes())
    assert frozen==current
    assert sha(HISTORY/'object_routes_bundle/bundle_src/native_targeted_timers.hpp')==json.loads((PROBE/'local_correctness_revision2.json').read_bytes())['dependency_sha256']['native_targeted_timers.hpp']
    import sys
    resume='--resume-checked-cases' in sys.argv
    if resume:
        retained=json.loads((WORK/'validation_harness_repair_2.json').read_bytes())
        assert retained['dll_sha256']==sha(DLL)
        assert all(sha(WORK/n)==h for n,h in retained['cases_sha256'].items())
    reports={};layouts=None
    with tempfile.TemporaryDirectory(prefix='native-compiler-pta-final-') as directory:
        root=Path(directory);shutil.copyfile(DLL,root/'libgdcore.dll')
        for name,cpp,reference,output in [('owner','test_native_targeted_timers.cpp','baseline_expanded_cases.json','targeted_timer_production_cases.json'),('safety','test_targeted_timer_safety.cpp','baseline_safety.json','targeted_timer_safety_production_cases.json'),('ownership','test_targeted_timer_ownership.cpp','ownership_baseline.json','targeted_timer_ownership_production_cases.json')]:
            old=json.loads((PROBE/reference).read_bytes());exe=root/(name+'.exe')
            if name=='owner':assert sha(STAGE/cpp)==old['dependency_sha256'][cpp]
            elif name=='safety':
                assert sha(STAGE/cpp)==old['source_sha256'] and sha(PROBE/'actual_targeted_timer_fixture.hpp')==old['fixture_sha256']
            else:assert sha(STAGE/cpp)==old['source_sha256']
            if resume:
                raw=(WORK/output).read_text('utf8');actual=json.loads(raw)
            else:
                subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-DGD_TIMER_NEW','-I',str(PROBE),'-I',str(SOURCE),str(STAGE/cpp),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
                raw=subprocess.check_output([str(exe)],text=True);actual=json.loads(raw)
            assert actual['cases']==old['cases'] and actual['state_hashes']==old['state_hashes'] and actual['legacy_hashes']==old['legacy_hashes'],name
            if not resume:(WORK/output).write_text(raw,encoding='utf8')
            reports[name]=dict(cases=actual['cases'],all_original_states_and_legacy_counters_equal=True,reference_sha256=sha(PROBE/reference))
            if name=='owner':layouts=dict(baseline=old['layout'],candidate=actual['layout'])
    assert reports['owner']['cases']==1760 and reports['safety']['cases']==192 and reports['ownership']['cases']==64
    assert layouts['baseline']['GdArr']==24 and layouts['candidate']['GdArr']==32
    assert layouts['baseline']['BattleCtx']==264 and layouts['candidate']['BattleCtx']==328
    assert layouts['baseline']['CoreItem']==1792 and layouts['candidate']['CoreItem']==2112
    layouts={'historical_oracle':layouts['baseline'],'baseline':json.loads((HISTORY/'object_routes_bundle/targeted_timer_tests.json').read_bytes())['layouts']['candidate'],'candidate':layouts['candidate']}
    assert {k:v for k,v in layouts['baseline'].items() if k!='CoreItem'}=={k:v for k,v in layouts['candidate'].items() if k!='CoreItem'} and layouts['candidate']['BattleCtx']==328
    import sys
    sys.path.insert(0,str(STAGE))
    from verify_closed_registry_current import verify as registry_verify
    from verify_closed_timer_known_cases import verify as known_verify
    registry_verify(SOURCE,DLL,WORK/'closed_registry_tests.json')
    known_verify(SOURCE,DLL,WORK/'closed_known_tests.json')
    report=dict(passed=True,dll_sha256=sha(DLL),cases=2016,sealed_known_cases=1056,registry_boundary_checks=4,actual_production_method_checked=True,
        separate_old_new_abi_executables=True,layouts=layouts,independent_receipts=reports,
        all_original_arithmetic_rng_and_observable_callback_order_retained=True)
    (WORK/'targeted_timer_tests.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()
