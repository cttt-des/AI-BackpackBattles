"""One predeclared comparison for the grid plus cooldown cache-hit bundle."""
import ast
import json
from pathlib import Path
STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/active_cooldown_bundle'
WORK=STAGE/'native_perf50/grid_cooldown_bundle'
BASE='55b62a2044b87311a967878a91d88ef4702641d240594989a09c396f67172ece'
ARCHIVE='f67e7c55fd5d4c161b6ab3c81d925d2ba7ea5ffd'
GRID_FIELDS=('fast_queries','ordinary_queries','enabled_dicts','rejected_dicts','mode_conversions','reserved')

def once(t,a,b):
    assert t.count(a)==1,(a[:100],t.count(a));return t.replace(a,b,1)

def main():
    assert not WORK.exists();WORK.mkdir()
    for p in OLD.glob('*.py'):
        t=p.read_text('utf8').replace('active_cooldown_bundle','grid_cooldown_bundle').replace('closed_timer_bundle','active_cooldown_bundle')
        t=t.replace('686f0d6cdb2fc223d4ed50319b31e786eea14383b4ffb9a8fe8633395ee07b43',BASE).replace('e5356be288c04804dc645fced2ab24fd360b2238',ARCHIVE)
        t=t.replace('native-active-cooldown-','native-grid-cooldown-')
        if p.name=='build_bundle.py':
            t=t.replace('==705','==706').replace("'verified_source_files':705","'verified_source_files':706").replace('and705 sources','and706 sources')
        if p.name in ('prepare_regeneration.py','test_regeneration_guards.py','verify_installed.py','save_checkpoint.py'):
            t=t.replace('==706','==707').replace("'source_inventory_verified':706","'source_inventory_verified':707").replace("'production_source_files':706","'production_source_files':707")
        if p.name=='resume_build.py':t=once(t,"    exports.add('gd_diag_native_active_cooldown_stat')","    exports.add('gd_diag_native_active_cooldown_stat')\n    exports.add('gd_diag_native_integer_grid_stat')")
        if p.name=='validate_then_compare.py':t=once(t,"    run('verify_active_cooldowns.py','active_cooldown_tests.log')","    run('verify_active_cooldowns.py','active_cooldown_tests.log')\n    run('verify_integer_grid.py','integer_grid_tests.log')")
        if p.name=='inspect_variant.py':
            t=once(t,'    active=sim.lib.gd_diag_native_active_cooldown_stat',"    grid_index=sim.lib.gd_diag_native_integer_grid_stat;grid_index.argtypes=[ctypes.c_uint];grid_index.restype=ctypes.c_uint64\n    grid_before=[grid_index(i) for i in range(6)]\n    active=sim.lib.gd_diag_native_active_cooldown_stat")
            t=once(t,"    report['active_cooldown_coverage']=",f"    report['integer_grid_coverage']=dict(zip({GRID_FIELDS!r},[grid_index(i)-grid_before[i] for i in range(6)]))\n    assert report['integer_grid_coverage']['fast_queries']>0 and report['integer_grid_coverage']['enabled_dicts']>0\n    report['active_cooldown_coverage']=")
        if p.name=='audit_verify.py':
            t=once(t,'active_stat=lib.gd_diag_native_active_cooldown_stat',"grid_stat=lib.gd_diag_native_integer_grid_stat;grid_stat.argtypes=[ctypes.c_uint];grid_stat.restype=ctypes.c_uint64\ngrid_before=[grid_stat(i) for i in range(6)]\nactive_stat=lib.gd_diag_native_active_cooldown_stat")
            t=once(t,'raise SystemExit(exit_code)',"(out/'native_integer_grid_audit.json').write_text(json.dumps(dict(dll_sha256=report['dll_sha256'],verifier_exit_code=exit_code,counts=[grid_stat(i)-grid_before[i] for i in range(6)]),indent=2)+'\\n',encoding='utf8')\nraise SystemExit(exit_code)")
        if p.name=='finish_gate.py':
            t=once(t,'    active_counts=[0]*10','    active_counts=[0]*10\n    grid_counts=[0]*6')
            t=once(t,"        summary=json.loads((root/'summary.json').read_bytes())","        grid=json.loads((root/'native_integer_grid_audit.json').read_bytes());assert grid['dll_sha256']==dll and grid['verifier_exit_code']==0 and len(grid['counts'])==6\n        for i,value in enumerate(grid['counts']):grid_counts[i]+=value\n        summary=json.loads((root/'summary.json').read_bytes())")
            t=once(t,'    assert all(active_counts[i]>0','    assert grid_counts[0]>0 and grid_counts[2]>0\n    assert all(active_counts[i]>0')
            t=once(t,"        'active_cooldown_coverage':",f"        'integer_grid_coverage':dict(zip({GRID_FIELDS!r},grid_counts)),\n        'active_cooldown_coverage':")
        if p.name=='verify_targeted_timers.py':
            t=once(t,"WORK.parent/'active_cooldown_prototype/transform.json'","WORK.parent/'grid_cooldown_prototype/transform.json'")
            t=once(t,"    assert layouts['baseline']['BattleCtx']==304 and layouts['candidate']['BattleCtx']==328","    assert layouts['baseline']==layouts['candidate'] and layouts['candidate']['BattleCtx']==328")
        if p.name=='verify_installed.py':
            t=once(t,"'active_cooldown_tests.json','closed_known_tests.json'","'active_cooldown_tests.json','integer_grid_tests.json','integer_grid_dictionary_tests.json','integer_grid_query_tests.json','closed_known_tests.json'")
            marker="    assert read('active_cooldown_tests.json')['cases']==1856"
            addition=f"    grid_counts=[0]*6\n    for receipt in audit['receipts']:\n        row=json.loads((Path(receipt)/'native_integer_grid_audit.json').read_bytes())\n        assert row['dll_sha256']==actual and row['verifier_exit_code']==0 and len(row['counts'])==6\n        for i,value in enumerate(row['counts']):grid_counts[i]+=value\n    assert dict(zip({GRID_FIELDS!r},grid_counts))==audit['integer_grid_coverage']\n    assert grid_counts[0]>0 and grid_counts[2]>0\n    assert read('integer_grid_tests.json')['dictionary_cases']==1792 and read('integer_grid_tests.json')['query_cases']==23520\n"
            t=once(t,marker,addition+marker)
            t=once(t,"'active_cooldown_cases':1856,","'integer_grid_dictionary_cases':1792,'integer_grid_query_cases':23520,'integer_grid_coverage':audit['integer_grid_coverage'],'active_cooldown_cases':1856,")
            t=once(t,"'active_cooldown_tests.json','active_cooldown_tests_cases.json'","'active_cooldown_tests.json','active_cooldown_tests_cases.json','integer_grid_tests.json','integer_grid_dictionary_tests.json','integer_grid_query_tests.json'")
        if p.name=='save_checkpoint.py':
            t=once(t,'    audit=json.loads',"    paths.update(STAGE/p for p in ('inspect_native_geometry_cost.py','native_integer_grid.hpp','test_native_integer_grid_slots.cpp','probe_native_integer_grid_slots.py','build_native_semantic_base.py','prepare_native_integer_grid.py','build_native_integer_grid_prototype.py','test_native_integer_grid_dict.cpp','verify_native_integer_grid_dict.py','verify_native_integer_grid_queries.py','prepare_native_grid_cooldown.py','build_native_grid_cooldown_prototype.py','verify_native_grid_cooldown_prototype.py','prototype_native_grid_cooldown_bundle.py','verify_native_integer_grid_final.py','setup_grid_cooldown_bundle.py','preflight_native_grid_cooldown_bundle.py'))\n    for folder in ('geometry_cost_probe','integer_grid_prototype','grid_cooldown_prototype','semantic_base_55b6'):\n        paths.update(p for p in (WORK.parent/folder).rglob('*') if p.is_file())\n    audit=json.loads")
            t=t.replace('perf: index active cooldown owners in original order','perf: index integer grid cells and hoist cached cooldown guards').replace('backup: preserve verified active cooldown index','backup: preserve verified integer grid and cooldown bundle')
        if p.name=='verify_active_cooldowns.py':
            t="import sys\nfrom pathlib import Path\nWORK=Path(__file__).resolve().parent\nsys.path.insert(0,str(WORK.parents[1]))\nfrom verify_native_active_cooldown_final import verify\nif __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'active_cooldown_tests.json')\n"
        if p.name=='verify_closed_registry_current.py':
            t=(STAGE/'verify_closed_timer_registry.py').read_text('utf8').replace('from prepare_native_closed_timer import BASE,STAGE,EXPECTED,sha','from prepare_native_integer_grid import BASE,STAGE,EXPECTED,sha')
        ast.parse(t,filename=p.name);(WORK/p.name).write_text(t,encoding='utf8',newline='\n')
    wrapper="import sys\nfrom pathlib import Path\nsys.path.insert(0,str(Path(__file__).resolve().parents[2]))\nfrom verify_native_integer_grid_final import main\nif __name__=='__main__':main()\n"
    (WORK/'verify_integer_grid.py').write_text(wrapper,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp'):(WORK/name).write_bytes((OLD/name).read_bytes())
    policy=json.loads((OLD/'bounded_followup_policy.json').read_bytes())
    (WORK/'bounded_followup_policy.json').write_text(json.dumps(policy,indent=2)+'\n',encoding='utf8')
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=BASE,verified_remote_backup=ARCHIVE,baseline_source_files=706,candidate_source_files=707,
        components=['bounded integer filledCells bucket format','cooldown cache-hit guard hoisting','redundant indexed Bool check removal'],
        intentional_layout_changes=[],private_cooldown_cache_adds_grid_pointer=True,local_independent_cases=dict(coordinates=132576,dictionaries=1792,queries=23520,cooldowns=1856),
        semantic_native_cache_not_used_for_formal_timing=True,full20_fresh18_pgo_required=True,
        no_standalone_grid_or_guard_speed_claim=True,prior_declared_bounded_followup_rule_retained=True)
    plan['required'][0]+=';1792 dictionary operations and23520 original/forced spatial cases on the actual final DLL'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared composite grid/cooldown candidate; full20/new18PGO, fixed200 24/bounded32,2604 and first24 gates retained')

if __name__=='__main__':main()
