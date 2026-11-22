"""Declare a layout-changing targeted timer candidate with unchanged outcome gates."""
import ast
import json
from pathlib import Path
STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/motion_indices_bundle'
WORK=STAGE/'native_perf50/targeted_timer_bundle'
BASE='7a57d09b81ba62fcd985fbb14a5999c72ff550ba328d5cae3add6167e4fbc058'
ARCHIVE='4a5388b7161d765cafe5515f263ee0f762fe7c88'

def once(text,old,new):
    assert text.count(old)==1,(old,text.count(old));return text.replace(old,new,1)

def main():
    WORK.mkdir(exist_ok=True);assert not (WORK/'build_bundle.py').exists()
    for path in OLD.glob('*.py'):
        if path.name in ('summarize_profile_for_brainstorm.py','profile_deployed.py'):continue
        text=path.read_text('utf8').replace('motion_indices_bundle','targeted_timer_bundle').replace('spatial_bundle','motion_indices_bundle')
        text=text.replace('fcfe317116882ad80e2dd59611c38c01690ba004',ARCHIVE).replace('3a9269887ace0ad9cd6dafdb9e0ee2a77b857b231f2a0d412888af2516e5b520',BASE).replace('native-motion-indices-','native-targeted-timer-')
        if path.name=='resume_build.py':text=once(text,"    definition=objects/'instrumented_exports.def'","    exports.add('gd_diag_native_targeted_timer_stat')\n    definition=objects/'instrumented_exports.def'")
        if path.name=='prepare_regeneration.py':text=text.replace('assert len(rows)==704','assert len(rows)==705')
        if path.name=='test_regeneration_guards.py':text=text.replace('==704','==705').replace("'source_inventory_verified':704","'source_inventory_verified':705")
        if path.name=='validate_then_compare.py':text=once(text,"    run('verify_motion_indices.py','motion_indices_tests.log')","    run('verify_motion_indices.py','motion_indices_tests.log')\n    run('verify_targeted_timers.py','targeted_timer_tests.log')")
        if path.name=='verify_motion_indices.py':
            text=once(text,'        assert sha(path)==digest,name',"        if name in ('gd_rt.hpp','native_array_index.hpp','native_inline_dispatch.hpp'):\n            frozen=json.loads((WORK/'source_before_build.json').read_bytes())\n            assert sha(path)==frozen[name],name\n        else:assert sha(path)==digest,name")
            begin=text.index('    from prepare_native_motion_indices import prepare')
            end=text.index('    with tempfile.TemporaryDirectory',begin)
            text=text[:begin]+'''    source=(WORK/'bundle_src/gen/shards/shard_07.cpp').read_text('utf8')
    signature='gd::GdVal Gd__gd_core__CoreContext::fn_tickMotion('
    start=source.index(signature);method=source[start:source.index('\\n}',start)+2]
    method_sha=hashlib.sha256(method.encode()).hexdigest()
    retained=json.loads((WORK.parent/'motion_indices_bundle/transform.json').read_bytes())
    assert method_sha==retained['candidate_method_sha256']
'''+text[end:]
            text=text.replace("source_method_sha256=design['candidate_sha256']","source_method_sha256=method_sha")
        if path.name=='inspect_variant.py':
            text=once(text,'    audit(1);before=',"    targeted=sim.lib.gd_diag_native_targeted_timer_stat;targeted.argtypes=[ctypes.c_uint];targeted.restype=ctypes.c_uint64\n    targeted_before=[targeted(i) for i in range(10)]\n    audit(1);before=")
            text=once(text,'    args.out.write_text',"    report['targeted_timer_coverage']=dict(zip(('indexed_passes','rebuilds','cache_hits','indexed_owners','fallback_passes','same_pass_resumes','watched_invalidations','build_slots','build_eligible_owners','unknown_boundaries'),[targeted(i)-targeted_before[i] for i in range(10)]))\n    assert all(report['targeted_timer_coverage'][k]>0 for k in ('indexed_passes','rebuilds','cache_hits','indexed_owners'))\n    retained=json.loads((Path(__file__).resolve().parent.parent/'motion_indices_bundle/release_audit.json').read_bytes())\n    assert report['coverage']==retained['coverage'],'Sparse traversal must not skip original dispatches'\n    args.out.write_text")
        if path.name=='audit_verify.py':
            text=once(text,'resolved_audit(1);resolved_before=',"targeted_stat=lib.gd_diag_native_targeted_timer_stat;targeted_stat.argtypes=[ctypes.c_uint];targeted_stat.restype=ctypes.c_uint64\ntargeted_before=[targeted_stat(i) for i in range(10)]\nresolved_audit(1);resolved_before=")
            text=once(text,'raise SystemExit(exit_code)',"targeted_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'counts':[targeted_stat(i)-targeted_before[i] for i in range(10)]}\n(out/'native_targeted_timer_audit.json').write_text(json.dumps(targeted_report,indent=2)+'\\n',encoding='utf8')\nraise SystemExit(exit_code)")
        if path.name=='finish_gate.py':
            text=once(text,'    motion_counts=[0]*3','    motion_counts=[0]*3\n    targeted_counts=[0]*10')
            text=once(text,"        summary=json.loads((root/'summary.json').read_bytes())","        targeted=json.loads((root/'native_targeted_timer_audit.json').read_bytes());assert targeted['dll_sha256']==dll and targeted['verifier_exit_code']==0 and len(targeted['counts'])==10\n        for i,value in enumerate(targeted['counts']):targeted_counts[i]+=value\n        summary=json.loads((root/'summary.json').read_bytes())")
            text=once(text,"    baseline=json.loads((WORK.parent/","    assert all(targeted_counts[i]>0 for i in (0,1,2,3))\n    baseline=json.loads((WORK.parent/")
            text=once(text,"        'motion_index_coverage':dict(zip(","        'targeted_timer_coverage':dict(zip(('indexed_passes','rebuilds','cache_hits','indexed_owners','fallback_passes','same_pass_resumes','watched_invalidations','build_slots','build_eligible_owners','unknown_boundaries'),targeted_counts)),\n        'motion_index_coverage':dict(zip(")
        if path.name=='verify_installed.py':
            text=text.replace('assert len(inventory)==704','assert len(inventory)==705').replace("'production_source_files':704","'production_source_files':705")
            text=text.replace('This round changes internal dispatch rows, never any generated object layout.','Generated header text is retained; GdArr/BattleCtx layout changes are intentional and were fully rebuilt.')
            text=text.replace("'motion_indices_tests.json'","'motion_indices_tests.json','targeted_timer_tests.json'")
            text=text.replace("'motion_indices_production_cases.json'","'motion_indices_production_cases.json','targeted_timer_production_cases.json','targeted_timer_safety_production_cases.json'")
            text=text.replace("'targeted_timer_safety_production_cases.json'","'targeted_timer_safety_production_cases.json','targeted_timer_ownership_production_cases.json'")
            text=once(text,"    assert read('legacy_counter_equivalence.json')['passed']","    targeted_counts=[0]*10\n    for receipt in audit['receipts']:\n        row=json.loads((Path(receipt)/'native_targeted_timer_audit.json').read_bytes())\n        assert row['dll_sha256']==actual and row['verifier_exit_code']==0 and len(row['counts'])==10\n        for index,count in enumerate(row['counts']):targeted_counts[index]+=count\n    targeted_fields=('indexed_passes','rebuilds','cache_hits','indexed_owners','fallback_passes','same_pass_resumes','watched_invalidations','build_slots','build_eligible_owners','unknown_boundaries')\n    assert dict(zip(targeted_fields,targeted_counts))==audit['targeted_timer_coverage']\n    assert all(targeted_counts[i]>0 for i in (0,1,2,3))\n    assert read('targeted_timer_tests.json')['cases']==2016\n    assert read('legacy_counter_equivalence.json')['passed']")
            text=once(text,"'motion_index_coverage':audit['motion_index_coverage'],","'motion_index_coverage':audit['motion_index_coverage'],'targeted_timer_coverage':audit['targeted_timer_coverage'],\n        'internal_layout_evidence':read('targeted_timer_tests.json')['layouts'],")
        if path.name=='save_checkpoint.py':
            text=once(text,'    audit=json.loads',"    paths.update(STAGE/p for p in ('native_targeted_timers.hpp','prepare_native_targeted_timers.py','review_fix_targeted_timer_prototype.py','build_native_targeted_timer_prototype.py','inspect_targeted_timer_fixed200.py','test_native_targeted_timers.cpp','probe_native_targeted_timers.py','test_targeted_timer_safety.cpp','probe_targeted_timer_safety.py','test_targeted_timer_local_cost.cpp','probe_targeted_timer_local_cost.py','test_targeted_timer_ownership.cpp','probe_targeted_timer_ownership.py','repair_targeted_timer_ownership.py','prototype_native_targeted_timer_bundle.py','setup_targeted_timer_bundle.py','inspect_native_timer_sparsity.py'))\n    for folder in ('targeted_timer_probe','targeted_timer_prototype','targeted_timer_bundle_revision1_build'):\n        paths.update(p for p in (WORK.parent/folder).iterdir() if p.is_file())\n    audit=json.loads")
            text=text.replace('assert len(source)==704','assert len(source)==705')
            text=text.replace('perf: specialize bounded motion queue controls','perf: index nonempty timer owners with targeted invalidation').replace('backup: preserve verified bounded motion controls','backup: preserve verified targeted timer index')
        ast.parse(text,filename=path.name);(WORK/path.name).write_text(text,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp'):(WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=BASE,verified_remote_backup=ARCHIVE,components=['targeted array watcher','ordered sparse timer owners','exact same-frame continuation','unknown boundary fallback'],
        local_original_dll_cases=2016,intentional_layout_changes=['GdArr24->32','BattleCtx264->304'],full20_rebuild_required=True,
        excluded=['global callback epoch','reordered callbacks','skipped timer updates','changed arithmetic or RNG','static unguarded eligibility cache'])
    plan['required'][0]='1760 owner/mutation cases,192 boundary/lifetime cases and64 cross-context counterexamples against actual7a57 DLL, both distinct ABI executables, and retained regressions'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared structural targeted timer candidate: full20/new18PGO, fixed200x4 and3x8AB,2604 truth and raw24 retained')

if __name__=='__main__':main()
