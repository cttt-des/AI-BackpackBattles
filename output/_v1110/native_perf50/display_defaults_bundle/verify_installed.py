"""Verify deployed bytes and actual evidence for the full optimization goal."""
import hashlib
import json
import math
from pathlib import Path
import statistics
import sys

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
REPO=STAGE.parents[1]
BASE='e0bedc4960077407e85763cb5e4af70175a0623cca15e923403fa89174390687'
INPUT='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
RESULT='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
ROOT='b8066c9224bc418923c62f5a3dafb8912100b21bb0026c3b13669872f90e2f54'
DATA='55bdd068cf3308547de78b45abbed4bf4f57e8253fbec82313a99578defa00ae'


def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def read(name):return json.loads((WORK/name).read_bytes())


def main():
    native=STAGE/'sim_native/native_sim_cpp/native_sim'
    runtime=REPO/'dist/native_1_1_10'
    actual=sha(WORK/'bundle.dll')
    assert actual==sha(native/'libgdcore.dll')==sha(runtime/'libgdcore.dll') and actual!=BASE
    manifest=json.loads((runtime/'manifest.json').read_bytes())
    assert manifest['verified_fights']==2604 and manifest['gate_sha256']==sha(WORK/'bundle_full_gate.json')
    for name,expected in manifest['sha256'].items():assert sha(runtime/name)==expected,name
    inventory={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py')}
    expected=read('source_before_build.json')
    assert len(inventory)==708
    for name,digest in inventory.items():assert digest==expected[name]==sha(WORK/'bundle_src'/name),name
    # Generated headers and current object/container layouts are retained;
    # the historical ABI changes are distinguished in the timer evidence below.
    old=WORK.parent/'grid_cooldown_bundle/bundle_src'
    headers=list((native/'gen/hdrs').glob('*.hpp'));assert len(headers)==674
    assert all(path.read_bytes()==(old/path.relative_to(native)).read_bytes() for path in headers)
    assert (STAGE/'optimize_native_verified_bundle.py').read_bytes()==(WORK/'verified_bundle_pending.py').read_bytes()
    for name in ('regeneration_test.json','full_regeneration_test.json','type_constructor_test.json','hot_coverage_test.json','event_identity_tests.json','lazy_diagnostics_tests.json','member_frame_tests.json','static_collections_tests.json','static_setup_tests.json','dispatch_chain_tests.json','spatial_tests.json','motion_indices_tests.json','targeted_timer_tests.json','active_cooldown_tests.json','display_defaults_tests.json','integer_grid_tests.json','integer_grid_dictionary_tests.json','integer_grid_query_tests.json','closed_known_tests.json','closed_registry_tests.json','property_test.json','buff_chunk_differential.json','addspeed_trace_differential.json'):
        record=read(name);assert record['passed'],name
        if 'dll_sha256' in record:assert record['dll_sha256']==actual,name
    profile=read('fresh_profile_source.json')
    assert profile['dll_sha256']==actual and profile['profile_training_and_release_source_identical'] and profile['floating_options_unchanged']
    assert profile['source_manifest_sha256']==sha(WORK/'source_before_build.json')
    gate=read('bundle_full_gate.json');hashes=read('bundle_vs_deployed_hashes.json');audit=read('full_type_audit.json')
    assert gate['complete'] and gate['dll_sha256']==actual and gate['runtime_data_sha256']==DATA
    for name,count in (('base',914),('expand',1690)):
        row=gate['cohorts'][name]
        assert row['expected']==row['recorded']==row['verified']==row['passed']==count
        assert row['winner_mismatch']==0 and not row['pending']
    assert hashes['candidate_dll_sha256']==actual and hashes['baseline_dll_sha256']==BASE
    assert hashes['unchanged_cpp_event_streams']==2604 and hashes['ordered_case_and_cpp_event_hashes_sha256']==ROOT
    sys.path.insert(0,str(STAGE))
    from compare_native_event_receipts import read_gate,reference_index,FIELDS
    _,before=read_gate(WORK.parent/'grid_cooldown_bundle/bundle_full_gate.json','native_grid_cooldown_bundle_bundle_')
    _,after=read_gate(WORK/'bundle_full_gate.json','native_display_defaults_bundle_bundle_')
    references=reference_index(STAGE/'native_host_observed_reference_plan.json')
    checked=0;event_digest=hashlib.sha256()
    for cohort,cases in references.items():
        for case_id,reference in sorted(cases.items()):
            old=before[reference['path']][case_id];new=after[reference['path']][case_id]
            assert new['category']=='pass' and new['cpp_events_sha256']
            for field in FIELDS:assert old.get(field)==new.get(field),(case_id,field)
            event_digest.update(f"{case_id} {new['cpp_events_sha256']}\n".encode())
            checked+=1
    assert checked==2604 and event_digest.hexdigest()==ROOT
    assert audit['candidate_dll_sha256']==actual and audit['fights']==2604
    assert audit['coverage']['audit_mismatch']==audit['old_event_kernel_type_mismatches']==0
    assert audit['event_identity_coverage']['fast_identities']>0 and audit['event_identity_coverage']['fast_emissions']>0
    assert all(value>0 for value in audit['hot_slot_coverage'].values())
    assert audit['type_constructor_coverage']['type_hits']>0 and audit['type_constructor_coverage']['fused_initializations']>0
    setup_fields=('bulk_stack_tables','ordered_stack_fallback','metric_counts','affected_loops')
    setup_counts=[0]*4
    for receipt in audit['receipts']:
        row=json.loads((Path(receipt)/'native_static_setup_audit.json').read_bytes())
        assert row['dll_sha256']==actual and row['verifier_exit_code']==0 and len(row['counts'])==4
        for index,count in enumerate(row['counts']):setup_counts[index]+=count
    assert dict(zip(setup_fields,setup_counts))==audit['static_setup_coverage']
    assert all(setup_counts[index]>0 for index in (0,2,3))
    chain_fields=('behavior_methods','behavior_empty','behavior_probes','flat_callbacks')
    chain_counts=[0]*4
    for receipt in audit['receipts']:
        row=json.loads((Path(receipt)/'native_dispatch_chain_audit.json').read_bytes())
        assert row['dll_sha256']==actual and row['verifier_exit_code']==0 and len(row['counts'])==4
        for index,count in enumerate(row['counts']):chain_counts[index]+=count
    assert dict(zip(chain_fields,chain_counts))==audit['dispatch_chain_coverage']
    assert all(chain_counts[index]>0 for index in (0,2,3))
    spatial_fields=('lookups','hits','object_dedup','fallbacks');spatial_counts=[0]*4
    for receipt in audit['receipts']:
        row=json.loads((Path(receipt)/'native_spatial_audit.json').read_bytes())
        assert row['dll_sha256']==actual and row['verifier_exit_code']==0 and len(row['counts'])==4
        for index,count in enumerate(row['counts']):spatial_counts[index]+=count
    assert dict(zip(spatial_fields,spatial_counts))==audit['spatial_coverage']
    assert all(spatial_counts[index]>0 for index in (0,1,2))
    motion_counts=[0]*3
    for receipt in audit['receipts']:
        row=json.loads((Path(receipt)/'native_motion_index_audit.json').read_bytes())
        assert row['dll_sha256']==actual and row['verifier_exit_code']==0 and len(row['counts'])==3
        for index,count in enumerate(row['counts']):motion_counts[index]+=count
    assert all(value>0 for value in motion_counts) and motion_counts[2]<=motion_counts[1]
    assert dict(zip(('native_runs','native_entries','kept_entries'),motion_counts))==audit['motion_index_coverage']
    assert read('motion_indices_tests.json')['cases']==5840
    targeted_counts=[0]*10
    for receipt in audit['receipts']:
        row=json.loads((Path(receipt)/'native_targeted_timer_audit.json').read_bytes())
        assert row['dll_sha256']==actual and row['verifier_exit_code']==0 and len(row['counts'])==10
        for index,count in enumerate(row['counts']):targeted_counts[index]+=count
    targeted_fields=('indexed_passes','rebuilds','cache_hits','indexed_owners','fallback_passes','same_pass_resumes','watched_invalidations','build_slots','build_eligible_owners','unknown_boundaries')
    assert dict(zip(targeted_fields,targeted_counts))==audit['targeted_timer_coverage']
    assert all(targeted_counts[i]>0 for i in (0,1,2,3))
    active_counts=[0]*10
    for receipt in audit['receipts']:
        row=json.loads((Path(receipt)/'native_active_cooldown_audit.json').read_bytes())
        assert row['dll_sha256']==actual and row['verifier_exit_code']==0 and len(row['counts'])==10
        for i,value in enumerate(row['counts']):active_counts[i]+=value
    assert dict(zip(('indexed_phases', 'rebuilds', 'cache_hits', 'indexed_owners', 'build_fallbacks', 'same_pass_resumes', 'eligibility_changes', 'build_slots', 'build_active_owners', 'reserved'),active_counts))==audit['active_cooldown_coverage']
    assert all(active_counts[i]>0 for i in (0,1,2,3,5))
    grid_counts=[0]*6
    for receipt in audit['receipts']:
        row=json.loads((Path(receipt)/'native_integer_grid_audit.json').read_bytes())
        assert row['dll_sha256']==actual and row['verifier_exit_code']==0 and len(row['counts'])==6
        for i,value in enumerate(row['counts']):grid_counts[i]+=value
    assert dict(zip(('fast_queries', 'ordinary_queries', 'enabled_dicts', 'rejected_dicts', 'mode_conversions', 'reserved'),grid_counts))==audit['integer_grid_coverage']
    assert grid_counts[0]>0 and grid_counts[2]>0
    assert read('integer_grid_tests.json')['dictionary_cases']==1792 and read('integer_grid_tests.json')['query_cases']==23520
    display_counts=[0]*8
    for receipt in audit['receipts']:
        row=json.loads((Path(receipt)/'native_display_defaults_audit.json').read_bytes())
        assert row['dll_sha256']==actual and row['verifier_exit_code']==0 and len(row['counts'])==8
        for i,value in enumerate(row['counts']):display_counts[i]+=value
    assert dict(zip(('constructed_scopes', 'eligible_scopes', 'watch_attachments', 'eligible_phases', 'skipped_override_reads', 'invalidated_phases', 'outside_scope_phases', 'field_replacements'),display_counts))==audit['display_default_coverage']
    assert all(display_counts[i]>0 for i in (0,1,2,3,4))
    assert read('display_defaults_tests.json')['cases']==2305
    assert read('active_cooldown_tests.json')['cases']==1856
    assert read('targeted_timer_tests.json')['cases']==2016
    assert read('closed_known_tests.json')['cases']==1056
    assert read('closed_registry_tests.json')['four_boundary_checks']
    assert read('release_audit.json')['closed_packed_mode_verified']
    assert read('legacy_counter_equivalence.json')['passed']
    installed=read('bundle_installation.json')
    ab_path=Path(installed['ab_assessment_path'])
    assert sha(ab_path)==installed['ab_assessment_sha256']
    ab=json.loads(ab_path.read_bytes())
    assert ab['baseline_dll_sha256']==BASE and ab['candidate_dll_sha256']==actual
    assert ab['status']=='positive_combined_evidence' and installed['ab_pairs'] in (24,32) and len(ab['reports'])==installed['ab_pairs']//8
    for report in ab['reports']:
        path=Path(report['path']);assert sha(path)==report['sha256']
        raw=json.loads(path.read_bytes());assert raw['trial_batch_repetitions']==4
        for pair in raw['pairs']:
            for label in ('baseline','candidate'):
                arm=pair[label];assert arm['observed_fights']==800 and len(arm['raw_batches'])==4
                assert all(row['results_sha256']==RESULT and row['matched_original_terminal']==200 for row in arm['raw_batches'])
                assert abs(arm['main_thread_cpu_s']*4-arm['block_main_thread_cpu_s'])<1e-10
                assert abs(arm['wall_s']*4-arm['block_wall_s'])<1e-10
    for metric in ab['metrics'].values():assert metric['pairs']==installed['ab_pairs'] and metric['paired_median_time_reduction_pct']>0
    serial=read('bundle_serial.json');calibration=read('bundle_load_calibration.json');fit=read('bundle_load20.json')
    measurement=read('measurements_summary.json')
    for name,digest in measurement['report_sha256'].items():assert sha(WORK/name)==digest,name
    for record in (serial,calibration):
        assert record['dll_sha256']==actual and record['workers']==1 and record['fights']==200
        assert record['inputs_sha256']==INPUT and record['results_sha256']==RESULT
        assert len(record['samples'])==record['repeat']==24
        for row in record['samples']:
            assert row['matched_original_terminal']==200 and row['on_ac_before'] is True and row['on_ac_after'] is True
            assert math.isclose(row['fights_per_second'],200/row['wall_s'],rel_tol=1e-12)
    assert min(row['fights_per_second'] for row in serial['samples'])>=50
    assert fit['dll_sha256']==actual and fit['reference_load_pct']==20
    xs=[row['background_load_pct'] for row in calibration['samples']]
    ys=[math.log(row['wall_s']) for row in calibration['samples']]
    slope,intercept=statistics.linear_regression(xs,ys)
    recalculated=200/math.exp(intercept+20*slope)
    assert math.isclose(recalculated,fit['fitted_fights_per_second_at_reference_load'],rel_tol=1e-10)
    assert min(xs)<=20<=max(xs),'Reference load must be covered by actual observations'
    installed=read('bundle_installation.json')
    assert installed['dll_sha256']==actual and installed['gate_sha256']==sha(WORK/'bundle_full_gate.json')
    assert installed['speed_report_sha256']==sha(WORK/'bundle_serial.json')
    assert installed['training_matched_baseline']==12 and len(installed['training_outcomes'])==12
    assert installed['training_evaluation']['total_sims']==12 and installed['training_evaluation']['sim_errors']==0
    assert sha(REPO/installed['backup_runtime']/'libgdcore.dll')==BASE
    result={'passed':True,'dll_sha256':actual,'production_source_files':708,'unchanged_object_headers':674,
        'strict_event_cases':2604,'event_hash_root':ROOT,'raw_batches':24,'training_cases':12,
        'type_constructor_coverage':audit['type_constructor_coverage'],'hot_slot_coverage':audit['hot_slot_coverage'],'event_identity_coverage':audit['event_identity_coverage'],'static_setup_coverage':audit['static_setup_coverage'],'dispatch_chain_coverage':audit['dispatch_chain_coverage'],
        'spatial_coverage':audit['spatial_coverage'],'motion_index_coverage':audit['motion_index_coverage'],'targeted_timer_coverage':audit['targeted_timer_coverage'],
        'internal_layout_evidence':read('targeted_timer_tests.json')['layouts'],
        'display_default_coverage':audit['display_default_coverage'],'display_default_cases':2305,'integer_grid_dictionary_cases':1792,'integer_grid_query_cases':23520,'integer_grid_coverage':audit['integer_grid_coverage'],'active_cooldown_cases':1856,'active_cooldown_coverage':audit['active_cooldown_coverage'],'sealed_known_cases':1056,'sealed_registry_boundary_checks':4,'closed_packed_mode_verified':True,
        'target_at20_fps':recalculated,'goal_target_fps':200,'goal200_reached':recalculated>=200,
        'load_range_pct':[min(xs),max(xs)],'fit_validation':fit['validation'],
        'evidence_sha256':{name:sha(WORK/name) for name in ('display_defaults_tests.json','source_before_build.json','bundle_full_gate.json','bundle_vs_deployed_hashes.json','ab_assessment.json','bundle_serial.json','bundle_load_calibration.json','bundle_load20.json','bundle_installation.json','static_setup_tests.json','dispatch_chain_tests.json','spatial_tests.json','motion_indices_tests.json','targeted_timer_tests.json','dispatch_chain_production_cases.json','spatial_production_cases.json','motion_indices_production_cases.json','targeted_timer_production_cases.json','targeted_timer_safety_production_cases.json','targeted_timer_ownership_production_cases.json','closed_known_tests.json','closed_known_tests_cases.json','closed_registry_tests.json','active_cooldown_tests.json','active_cooldown_tests_cases.json','display_defaults_tests.json','integer_grid_tests.json','integer_grid_dictionary_tests.json','integer_grid_query_tests.json','static_setup_production_cases.json','full_type_audit.json')}}
    out=WORK/'post_install_verification.json';assert not out.exists()
    out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps(result,indent=2))


if __name__=='__main__':main()
