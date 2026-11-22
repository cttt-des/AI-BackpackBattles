"""Declare the sealed-input candidate; retain all first comparisons and release gates."""
import ast
import json
from pathlib import Path

STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/targeted_timer_bundle'
WORK=STAGE/'native_perf50/closed_timer_bundle'

def once(text,old,new):
    assert text.count(old)==1,(old,text.count(old))
    return text.replace(old,new,1)

def main():
    assert not WORK.exists();WORK.mkdir()
    for path in OLD.glob('*.py'):
        if path.name in ('resume_resolved_after_layout.py','continue_after_layout.py'):continue
        text=path.read_text('utf8').replace('targeted_timer_bundle','closed_timer_bundle').replace('native-targeted-timer-','native-closed-timer-')
        if path.name=='resume_build.py':
            text=once(text,"    exports.add('gd_diag_native_targeted_timer_stat')","    exports.add('gd_diag_native_targeted_timer_stat')\n    exports.update(('gd_diag_native_timer_registry_closed','gd_diag_native_timer_closed_mode'))")
        if path.name=='inspect_variant.py':
            text=once(text,"    targeted=sim.lib.gd_diag_native_targeted_timer_stat", "    for mode_name in ('gd_diag_native_timer_registry_closed','gd_diag_native_timer_closed_mode'):\n        mode=getattr(sim.lib,mode_name);mode.argtypes=[];mode.restype=ctypes.c_int\n    targeted=sim.lib.gd_diag_native_targeted_timer_stat")
            text=once(text,"    report['targeted_timer_coverage']=", "    assert sim.lib.gd_diag_native_timer_registry_closed()==sim.lib.gd_diag_native_timer_closed_mode()==1\n    report['closed_packed_mode_verified']=True\n    report['targeted_timer_coverage']=")
        if path.name=='verify_targeted_timers.py':
            text=once(text,"    frozen=json.loads((PROBE/'transform.json').read_bytes())['source_sha256']", "    closed=WORK.parent/'closed_timer_prototype'\n    frozen=json.loads((closed/'transform.json').read_bytes())['source_sha256']\n    dependencies=json.loads((closed/'proof_dependencies.json').read_bytes())\n    assert dependencies=={name:sha(STAGE/name) for name in dependencies}")
            text=once(text,"    report=dict(passed=True", "    import sys\n    sys.path.insert(0,str(STAGE))\n    from verify_closed_timer_registry import verify as registry_verify\n    from verify_closed_timer_known_cases import verify as known_verify\n    registry_verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'closed_registry_tests.json')\n    known_verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'closed_known_tests.json')\n    report=dict(passed=True")
            text=once(text,'cases=2016,actual_production_method_checked=True,','cases=2016,sealed_known_cases=1056,registry_boundary_checks=4,actual_production_method_checked=True,')
        if path.name=='verify_resolved.py':
            old='''        subprocess.run(["D:/mingw64/bin/g++.exe","-static","-O2","-std=c++20","-ffp-contract=off",
                        *extra,"-I",str(src),str(STAGE/file),str(directory/"libgdcore.dll"),"-o",str(executable)],check=True)'''
            new='''        test=STAGE/file
        if file=='test_native_arena_split.cpp':
            original=test.read_text('utf8');old='static_assert(sizeof(gd::GdArr)==24);';new='static_assert(sizeof(gd::GdArr)==32);'
            assert original.count(old)==1
            adapted=original.replace(old,new,1);test=directory/'arena_declared_layout32.cpp'
            test.write_text(adapted,encoding='utf8',newline='\\n');assert adapted.replace(new,old,1)==original
            (WORK/'arena_layout_test_adaptation.json').write_text(json.dumps(dict(original_test_sha256=digest(STAGE/file),adapted_test_sha256=digest(test),only_change=[old,new],semantic_checks_removed=False),indent=2)+'\\n',encoding='utf8')
        subprocess.run(["D:/mingw64/bin/g++.exe","-static","-O2","-std=c++20","-ffp-contract=off",
                        *extra,"-I",str(src),str(test),str(directory/"libgdcore.dll"),"-o",str(executable)],check=True)'''
            text=once(text,old,new)
        if path.name=='verify_installed.py':
            text=once(text,"read('motion_indices_tests.json','targeted_timer_tests.json')['cases']==5840", "read('motion_indices_tests.json')['cases']==5840")
            text=once(text,"    assert read('targeted_timer_tests.json')['cases']==2016", "    assert read('targeted_timer_tests.json')['cases']==2016\n    assert read('closed_known_tests.json')['cases']==1056\n    assert read('closed_registry_tests.json')['four_boundary_checks']\n    assert read('release_audit.json')['closed_packed_mode_verified']")
            text=once(text,"'targeted_timer_tests.json','property_test.json'", "'targeted_timer_tests.json','closed_known_tests.json','closed_registry_tests.json','property_test.json'")
            text=once(text,"'internal_layout_evidence':read('targeted_timer_tests.json')['layouts'],", "'internal_layout_evidence':read('targeted_timer_tests.json')['layouts'],\n        'sealed_known_cases':1056,'sealed_registry_boundary_checks':4,'closed_packed_mode_verified':True,")
            text=once(text,"'targeted_timer_ownership_production_cases.json','static_setup_production_cases.json'", "'targeted_timer_ownership_production_cases.json','closed_known_tests.json','closed_known_tests_cases.json','closed_registry_tests.json','static_setup_production_cases.json'")
        if path.name=='save_checkpoint.py':
            text=once(text,"'closed_timer_bundle_revision1_build'","'targeted_timer_bundle_revision1_build','targeted_timer_bundle'")
            text=once(text,'    audit=json.loads', "    paths.update(STAGE/p for p in ('prototype_native_targeted_timer_bundle.py','setup_targeted_timer_bundle.py','preflight_native_targeted_timer_bundle.py'))\n    audit=json.loads")
            text=once(text,'    audit=json.loads', "    paths.update(STAGE/p for p in ('prepare_native_closed_timer.py','repair_closed_timer_diagnostic.py','inspect_closed_timer_fixed200.py','test_closed_timer_registry.cpp','verify_closed_timer_prototype.py','verify_closed_timer_known_cases.py','verify_closed_timer_registry.py'))\n    paths.update(p for p in (WORK.parent/'closed_timer_prototype').iterdir() if p.is_file())\n    audit=json.loads")
            text=text.replace('perf: index nonempty timer owners with targeted invalidation','perf: specialize sealed-input sparse timer traversal').replace('backup: preserve verified targeted timer index','backup: preserve verified sealed-input timer traversal')
        ast.parse(text,filename=path.name);(WORK/path.name).write_text(text,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp'):(WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(components=['targeted array watchers','ordered timer owners','exact same-pass continuation','closed-input observer specialization'],
        sealed_known_cases=1056,sealed_registry_boundary_checks=4,prior_candidate_negative_ab_preserved=True,
        current_candidate_always_fresh20_instrumentation_and18_pgo=True)
    plan['required'][0]+=';1056 sealed known-only cases and4 registry boundary checks'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared closed-input candidate; full20/18PGO,3x8 AB,2604 truth,raw24 and fit24 retained')

if __name__=='__main__':main()
