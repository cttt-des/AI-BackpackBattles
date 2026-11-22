"""Retain fixed200/2604/raw24 gates for the complete typed damage candidate."""
import ast
import json
from pathlib import Path
STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/closed_timer_bundle'
WORK=STAGE/'native_perf50/typed_hotchain_bundle'
BASE='686f0d6cdb2fc223d4ed50319b31e786eea14383b4ffb9a8fe8633395ee07b43'
ARCHIVE='e5356be288c04804dc645fced2ab24fd360b2238'
FIELDS=('native_entries','typed_deal_entries','resistance_fast','resistance_fallback','integer_subtraction','mixed_subtraction','subtraction_fallback','post_signal_fast','health_fast','health_fallback','integer_range_fast','range_fallback')

def once(t,a,b):
    assert t.count(a)==1,(a[:100],t.count(a));return t.replace(a,b,1)

def main():
    assert not WORK.exists();WORK.mkdir()
    for p in OLD.glob('*.py'):
        if p.name in ('profile_deployed.py','summarize_profile_for_brainstorm.py'):continue
        t=p.read_text('utf8').replace('closed_timer_bundle','typed_hotchain_bundle').replace('motion_indices_bundle','closed_timer_bundle')
        t=t.replace('7a57d09b81ba62fcd985fbb14a5999c72ff550ba328d5cae3add6167e4fbc058',BASE).replace('4a5388b7161d765cafe5515f263ee0f762fe7c88',ARCHIVE).replace('native-closed-timer-','native-typed-hotchain-')
        if p.name=='build_bundle.py':
            t=t.replace('==704','==705').replace("'verified_source_files':704","'verified_source_files':705").replace('and704 sources','and705 sources')
            t=once(t,"    src=WORK/'bundle_src'","    assert json.loads((WORK.parent/'typed_hotchain_prototype/range_correctness.json').read_bytes())['passed']\n    src=WORK/'bundle_src'")
        if p.name in ('prepare_regeneration.py','test_regeneration_guards.py','verify_installed.py','save_checkpoint.py'):
            t=t.replace('==705','==706').replace("'source_inventory_verified':705","'source_inventory_verified':706").replace("'production_source_files':705","'production_source_files':706")
        if p.name=='resume_build.py':t=once(t,"    exports.add('gd_diag_native_targeted_timer_stat')","    exports.add('gd_diag_native_targeted_timer_stat')\n    exports.add('gd_diag_native_typed_damage_stat')")
        if p.name=='validate_then_compare.py':t=once(t,"    run('verify_targeted_timers.py','targeted_timer_tests.log')","    run('verify_targeted_timers.py','targeted_timer_tests.log')\n    run('verify_typed_hotchain.py','typed_hotchain_tests.log')")
        if p.name=='inspect_variant.py':
            t=once(t,'    targeted=sim.lib.gd_diag_native_targeted_timer_stat',"    typed=sim.lib.gd_diag_native_typed_damage_stat;typed.argtypes=[ctypes.c_uint];typed.restype=ctypes.c_uint64\n    typed_before=[typed(i) for i in range(12)]\n    targeted=sim.lib.gd_diag_native_targeted_timer_stat")
            t=once(t,"    report['targeted_timer_coverage']=",f"    report['typed_damage_coverage']=dict(zip({FIELDS!r},[typed(i)-typed_before[i] for i in range(12)]))\n    assert all(report['typed_damage_coverage'][name]>0 for name in ('native_entries','typed_deal_entries','resistance_fast','post_signal_fast','health_fast'))\n    report['targeted_timer_coverage']=")
        if p.name=='audit_verify.py':
            t=once(t,'targeted_stat=lib.gd_diag_native_targeted_timer_stat',"typed_stat=lib.gd_diag_native_typed_damage_stat;typed_stat.argtypes=[ctypes.c_uint];typed_stat.restype=ctypes.c_uint64\ntyped_before=[typed_stat(i) for i in range(12)]\ntargeted_stat=lib.gd_diag_native_targeted_timer_stat")
            t=once(t,'raise SystemExit(exit_code)',"(out/'native_typed_damage_audit.json').write_text(json.dumps(dict(dll_sha256=report['dll_sha256'],verifier_exit_code=exit_code,counts=[typed_stat(i)-typed_before[i] for i in range(12)]),indent=2)+'\\n',encoding='utf8')\nraise SystemExit(exit_code)")
        if p.name=='finish_gate.py':
            t=once(t,'    targeted_counts=[0]*10','    targeted_counts=[0]*10\n    typed_counts=[0]*12')
            t=once(t,"        summary=json.loads((root/'summary.json').read_bytes())","        typed=json.loads((root/'native_typed_damage_audit.json').read_bytes());assert typed['dll_sha256']==dll and typed['verifier_exit_code']==0 and len(typed['counts'])==12\n        for i,value in enumerate(typed['counts']):typed_counts[i]+=value\n        summary=json.loads((root/'summary.json').read_bytes())")
            t=once(t,'    assert all(targeted_counts[i]>0', '    assert all(typed_counts[i]>0 for i in (0,1,2,7,8))\n    assert all(targeted_counts[i]>0')
            t=once(t,"        'targeted_timer_coverage':",f"        'typed_damage_coverage':dict(zip({FIELDS!r},typed_counts)),\n        'targeted_timer_coverage':")
        if p.name=='verify_targeted_timers.py':
            t=once(t,"    frozen=json.loads((closed/'transform.json').read_bytes())['source_sha256']","    frozen=json.loads((WORK.parent/'typed_hotchain_prototype/transform_stage2.json').read_bytes())['source_sha256']")
            t=once(t,'    import sys',"    layouts={'historical_oracle':layouts['baseline'],'baseline':json.loads((WORK.parent/'closed_timer_bundle/targeted_timer_tests.json').read_bytes())['layouts']['candidate'],'candidate':layouts['candidate']}\n    assert layouts['baseline']==layouts['candidate']\n    import sys")
            t=t.replace('from verify_closed_timer_registry import verify as registry_verify','from verify_closed_registry_current import verify as registry_verify')
        if p.name=='verify_installed.py':
            old="    assert all(path.read_bytes()==(old/path.relative_to(native)).read_bytes() for path in headers)"
            new="""    for path in headers:
        previous=(old/path.relative_to(native)).read_text('utf8');current=path.read_text('utf8')
        if path.name=='Gd__gd_core__CoreCharacter.hpp':
            current=current.replace('struct Gd__gd_core__CoreDamageSource;\\nstruct Gd__gd_core__CoreDamageResult;\\n\\n','',1)
            current=current.replace('    Gd__gd_core__CoreDamageResult* fn_takeDamage_native(Gd__gd_core__CoreDamageSource*,const gd::GdVal&);\\n','',1)
        assert current==previous,path
    assert read('typed_hotchain_tests.json')['layouts_unchanged']"""
            t=once(t,old,new)
            t=t.replace("'unchanged_object_headers':674","'unchanged_object_headers':673,'nonvirtual_only_header_extension':True")
            t=once(t,"'targeted_timer_tests.json','closed_known_tests.json'","'targeted_timer_tests.json','typed_hotchain_tests.json','closed_known_tests.json'")
            t=once(t,"    assert read('targeted_timer_tests.json')['cases']==2016",f"    typed_counts=[0]*12\n    for receipt in audit['receipts']:\n        row=json.loads((Path(receipt)/'native_typed_damage_audit.json').read_bytes())\n        assert row['dll_sha256']==actual and row['verifier_exit_code']==0 and len(row['counts'])==12\n        for i,value in enumerate(row['counts']):typed_counts[i]+=value\n    assert dict(zip({FIELDS!r},typed_counts))==audit['typed_damage_coverage']\n    assert all(typed_counts[i]>0 for i in (0,1,2,7,8))\n    assert read('typed_hotchain_tests.json')['cases']==13112\n    assert read('targeted_timer_tests.json')['cases']==2016")
            t=once(t,"'sealed_known_cases':1056,", "'typed_hotchain_cases':13112,'typed_damage_coverage':audit['typed_damage_coverage'],'sealed_known_cases':1056,")
            t=once(t,"'closed_known_tests_cases.json','closed_registry_tests.json'","'closed_known_tests_cases.json','closed_registry_tests.json','typed_hotchain_tests.json','typed_hotchain_production_cases.json'")
        if p.name=='install_verified.py':
            t=once(t,'    args = parser.parse_args()',"    args = parser.parse_args()\n    if (WORK/'followup_plan.json').exists():\n        assert args.assessment.resolve()==(WORK/'ab_assessment_32.json').resolve(), 'A declared bounded follow-up must use all32 pairs'")
        if p.name=='save_checkpoint.py':
            t=once(t,'    audit=json.loads',"    paths.update(STAGE/p for p in ('prepare_native_typed_hotchain.py','extend_native_typed_hotchain.py','native_typed_damage_math.hpp','test_native_typed_damage_math.cpp','probe_native_typed_damage_math.py','probe_native_typed_hotchain.py','prototype_native_typed_hotchain_bundle.py','setup_typed_hotchain_bundle.py','preflight_native_typed_hotchain_bundle.py','inspect_native_dict_cost.py','verify_native_typed_hotchain_final.py','test_native_typed_damage_ranges.cpp'))\n    paths.update(p for p in (WORK.parent/'typed_hotchain_prototype').rglob('*') if p.is_file())\n    paths.update(p for p in (WORK.parent/'dict_cost_probe').iterdir() if p.is_file())\n    audit=json.loads")
            t=t.replace('perf: specialize sealed-input sparse timer traversal','perf: lower sealed damage chain to native pointers and scalar blocks').replace('backup: preserve verified sealed-input timer traversal','backup: preserve verified native damage chain')
        ast.parse(t,filename=p.name);(WORK/p.name).write_text(t,encoding='utf8',newline='\n')
    registry=(STAGE/'verify_closed_timer_registry.py').read_text('utf8').replace('from prepare_native_closed_timer import BASE,STAGE,EXPECTED,sha','from prepare_native_typed_hotchain import BASE,STAGE,EXPECTED,sha')
    (WORK/'verify_closed_registry_current.py').write_text(registry,encoding='utf8',newline='\n')
    wrapper="import sys\nfrom pathlib import Path\nsys.path.insert(0,str(Path(__file__).resolve().parents[2]))\nfrom verify_native_typed_hotchain_final import main\nif __name__=='__main__':main()\n"
    (WORK/'verify_typed_hotchain.py').write_text(wrapper,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp'):(WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=BASE,verified_remote_backup=ARCHIVE,components=['native pointer damage entry','complete typed kernel','scalar damage blocks','non-escaping integer loops','sealed Hook fields'],
        local_independent_cases=13112,math_bit_and_fenv_cases=33856,baseline_source_files=705,candidate_source_files=706,
        intentional_layout_changes=[],nonvirtual_header_declaration_only=True,prior_damage_combo_negative_ab_preserved=True)
    plan['required'][0]+=';13112 complete damage cases and33856 scalar bit/FENV cases'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared complete typed damage candidate; full20/new18PGO, fixed200 3x8AB,2604 event truth and raw24 gates')

if __name__=='__main__':main()
