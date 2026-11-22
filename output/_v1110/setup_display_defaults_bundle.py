"""Retain the fixed comparison and release gates for the owned display-default view."""
import ast
import json
from pathlib import Path
STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/event_capacity_bundle'
WORK=STAGE/'native_perf50/display_defaults_bundle'
ARCHIVE='e53ca96c4e96c9bc7dabd8aee4122f76fe572f1e'
FIELDS=('constructed_scopes','eligible_scopes','watch_attachments','eligible_phases','skipped_override_reads','invalidated_phases','outside_scope_phases','field_replacements')

def once(t,a,b):
    assert t.count(a)==1,(a[:130],t.count(a));return t.replace(a,b,1)

def main():
    assert not WORK.exists();WORK.mkdir()
    for p in OLD.glob('*.py'):
        if p.name in ('verified_bundle_pending.py','verify_event_capacity.py'):continue
        t=p.read_text('utf8').replace('event_capacity_bundle','display_defaults_bundle')
        t=t.replace('0526a5b0b241cc76c25c9f5d3dfaf9ef24710114',ARCHIVE)
        t=t.replace('native-event-capacity-','native-display-defaults-')
        if p.name in ('prepare_regeneration.py','test_regeneration_guards.py','verify_installed.py','save_checkpoint.py'):
            t=t.replace('==707','==708').replace("'source_inventory_verified':707","'source_inventory_verified':708").replace("'production_source_files':707","'production_source_files':708")
        if p.name=='resume_build.py':
            t=once(t,"    exports.add('gd_diag_native_integer_grid_stat')","    exports.add('gd_diag_native_integer_grid_stat')\n    exports.add('gd_diag_native_display_defaults_stat')")
        if p.name=='validate_then_compare.py':
            t=once(t,"    run('verify_event_capacity.py','event_capacity_tests.log')","    run('verify_display_defaults.py','display_defaults_tests.log')")
        if p.name=='verify_targeted_timers.py':t=t.replace('event_capacity_prototype/transform.json','display_defaults_prototype_r3/transform.json')
        if p.name in ('verify_closed_registry_current.py','verify_integer_grid.py'):
            t=t.replace('from prepare_native_event_capacity import','from prepare_native_display_defaults import')
        if p.name=='inspect_variant.py':
            t=once(t,'    grid_index=sim.lib.gd_diag_native_integer_grid_stat',"    display=sim.lib.gd_diag_native_display_defaults_stat;display.argtypes=[ctypes.c_uint];display.restype=ctypes.c_uint64\n    display_before=[display(i) for i in range(8)]\n    grid_index=sim.lib.gd_diag_native_integer_grid_stat")
            t=once(t,"    report['integer_grid_coverage']=",f"    report['display_default_coverage']=dict(zip({FIELDS!r},[display(i)-display_before[i] for i in range(8)]))\n    assert all(report['display_default_coverage'][name]>0 for name in ('eligible_scopes','eligible_phases','skipped_override_reads'))\n    report['integer_grid_coverage']=")
        if p.name=='audit_verify.py':
            t=once(t,'grid_stat=lib.gd_diag_native_integer_grid_stat',"display_stat=lib.gd_diag_native_display_defaults_stat;display_stat.argtypes=[ctypes.c_uint];display_stat.restype=ctypes.c_uint64\ndisplay_before=[display_stat(i) for i in range(8)]\ngrid_stat=lib.gd_diag_native_integer_grid_stat")
            t=once(t,'raise SystemExit(exit_code)',"(out/'native_display_defaults_audit.json').write_text(json.dumps(dict(dll_sha256=report['dll_sha256'],verifier_exit_code=exit_code,counts=[display_stat(i)-display_before[i] for i in range(8)]),indent=2)+'\\n',encoding='utf8')\nraise SystemExit(exit_code)")
        if p.name=='finish_gate.py':
            t=once(t,'    grid_counts=[0]*6','    grid_counts=[0]*6\n    display_counts=[0]*8')
            t=once(t,"        grid=json.loads((root/'native_integer_grid_audit.json').read_bytes())","        display=json.loads((root/'native_display_defaults_audit.json').read_bytes());assert display['dll_sha256']==dll and display['verifier_exit_code']==0 and len(display['counts'])==8\n        for i,value in enumerate(display['counts']):display_counts[i]+=value\n        grid=json.loads((root/'native_integer_grid_audit.json').read_bytes())")
            t=once(t,'    assert grid_counts[0]>0','    assert all(display_counts[i]>0 for i in (0,1,2,3,4))\n    assert grid_counts[0]>0')
            t=once(t,"        'integer_grid_coverage':",f"        'display_default_coverage':dict(zip({FIELDS!r},display_counts)),\n        'integer_grid_coverage':")
        if p.name=='verify_installed.py':
            t=t.replace('# Generated header text is retained; GdArr/BattleCtx layout changes are intentional and were fully rebuilt.',
                '# Generated headers and current layouts are retained; historical ABI changes remain in the timer evidence.')
            t=t.replace('event_capacity_tests.json','display_defaults_tests.json')
            t=once(t,"assert read('display_defaults_tests.json')['cases']==1024","assert read('display_defaults_tests.json')['cases']==2305")
            t=t.replace("'event_param_capacity_cases':1024","'display_default_cases':2305")
            marker="    assert read('display_defaults_tests.json')['cases']==2305"
            extra=f"    display_counts=[0]*8\n    for receipt in audit['receipts']:\n        row=json.loads((Path(receipt)/'native_display_defaults_audit.json').read_bytes())\n        assert row['dll_sha256']==actual and row['verifier_exit_code']==0 and len(row['counts'])==8\n        for i,value in enumerate(row['counts']):display_counts[i]+=value\n    assert dict(zip({FIELDS!r},display_counts))==audit['display_default_coverage']\n    assert all(display_counts[i]>0 for i in (0,1,2,3,4))\n"
            t=once(t,marker,extra+marker)
            t=once(t,"'display_default_cases':2305,","'display_default_coverage':audit['display_default_coverage'],'display_default_cases':2305,")
        if p.name=='save_checkpoint.py':
            extra="    paths.update(STAGE/p for p in ('native_packed_display.hpp','native_packed_display_impl.hpp','prepare_native_display_defaults.py','build_native_display_defaults_prototype.py','test_native_display_defaults.cpp','verify_native_display_defaults.py','prototype_native_display_defaults_bundle.py','setup_display_defaults_bundle.py','preflight_native_display_defaults_bundle.py','save_rejected_event_capacity.py'))\n    paths.update(STAGE.glob('native_display_defaults*.log'))\n    for folder in ('display_defaults_prototype','display_defaults_prototype_r2','display_defaults_prototype_r3'):\n        paths.update(p for p in (WORK.parent/folder).rglob('*') if p.is_file() and '__pycache__' not in p.parts)\n"
            t=once(t,'    audit=json.loads',extra+'    audit=json.loads')
            t=t.replace('perf: reduce event parameter dictionary initial capacity','perf: reuse watched default display state in cooldown frames')
            t=t.replace('backup: preserve verified event parameter storage','backup: preserve verified packed display view')
        ast.parse(t,filename=p.name);(WORK/p.name).write_text(t,encoding='utf8',newline='\n')
    wrapper="import sys\nfrom pathlib import Path\nWORK=Path(__file__).resolve().parent\nsys.path.insert(0,str(WORK.parents[1]))\nfrom verify_native_display_defaults import verify\nif __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'display_defaults_tests.json')\n"
    (WORK/'verify_display_defaults.py').write_text(wrapper,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp'):(WORK/name).write_bytes((OLD/name).read_bytes())
    (WORK/'bounded_followup_policy.json').write_bytes((OLD/'bounded_followup_policy.json').read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(verified_remote_backup=ARCHIVE,baseline_source_files=707,candidate_source_files=708,
        components=['owned packed default-display view using existing mutation watchers'],
        intentional_layout_changes=[],local_independent_cases=dict(display_defaults=2305),
        rejected_event_capacity_change_included=False,full20_fresh18_pgo_required=True,
        exact_read_point_recheck_after_getter_and_in_original_suffix=True)
    plan['required'][0]='All retained regressions plus2305 actual-DLL default-display/alias/callback/registry/FP cases'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared708-source display view; unchanged layouts/FP; fixed200 24/bounded32,2604 and first24 gates retained')

if __name__=='__main__':main()
