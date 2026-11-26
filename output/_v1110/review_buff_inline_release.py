"""Review frozen full-round evidence before changing the production runtime."""
import json
from pathlib import Path
import statistics
import math
from prepare_native_buff_inline_types import STAGE,BASE,ACCEPTED,EXPECTED,sha

WORK=STAGE/'native_perf50/buff_inline_types_bundle'
REPO=STAGE.parents[1]
PROTECTED=['native_sim_cpp/native_sim/libgdcore.dll','oracle/Items/Item.gd',
    'output/perf/_cpp1690_final.json','output/perf/_cpp1690_chain.json',
    'output/perf/alignment_1690_chain.json','output/perf/alignment_1690_final.json']

def read(name):return json.loads((WORK/name).read_bytes())

def main():
    out=WORK/'pre_install_review.json';assert not out.exists()
    actual=sha(WORK/'bundle.dll')
    assert actual==read('fresh_profile_source.json')['dll_sha256'] and actual!=EXPECTED
    assert sha(BASE/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==EXPECTED
    frozen=read('source_before_build.json')
    assert sum(Path(n).suffix in ('.cpp','.hpp') or Path(n).name=='build_windows.py' for n in frozen)==708
    assert frozen=={p.relative_to(WORK/'bundle_src').as_posix():sha(p) for p in (WORK/'bundle_src').rglob('*') if p.is_file()}
    changed=[n for n,h in frozen.items() if not (BASE/n).exists() or sha(BASE/n)!=h]
    assert sorted(changed)==['gen/shards/shard_00.cpp'],changed
    assert frozen==json.loads((STAGE/'native_perf50/buff_inline_types_prototype/transform.json').read_bytes())['source_sha256']
    decision=read('candidate_decision.json');selected=Path(decision['selected_assessment']);ab=json.loads(selected.read_bytes())
    assert decision['status']==ab['status']=='positive_combined_evidence'
    assert decision['assessment_sha256']==sha(selected) and decision['candidate_dll_sha256']==actual
    assert ab['baseline_dll_sha256']==EXPECTED and ab['candidate_dll_sha256']==actual
    pairs=32 if (WORK/'followup_plan.json').exists() else 24
    assert selected.resolve()==(WORK/('ab_assessment_32.json' if pairs==32 else 'ab_assessment.json')).resolve()
    assert all(r['pairs']==pairs and r['paired_median_time_reduction_pct']>0 for r in ab['metrics'].values())
    assert len(ab['reports'])==pairs//8
    if pairs==24:
        for metrics in [ab['metrics'],*ab['leave_one_group_out_sensitivity']]:
            assert all(r['paired_median_time_reduction_pct']>0 and r['sum_time_reduction_pct']>0 for r in metrics.values())
    for row in ab['reports']:
        p=Path(row['path']);assert sha(p)==row['sha256'];raw=json.loads(p.read_bytes())
        assert raw['trial_batch_repetitions']==4 and len(raw['pairs'])==8
        for pair in raw['pairs']:
            for label in ('baseline','candidate'):
                arm=pair[label];assert arm['observed_fights']==800 and len(arm['raw_batches'])==4
                assert all(r['matched_original_terminal']==200 and r['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9' for r in arm['raw_batches'])
    names=('regeneration_test.json','full_regeneration_test.json','targeted_timer_tests.json',
        'active_cooldown_tests.json','event_factory_tests.json','integer_grid_tests.json',
        'literal_span_tests.json','callback_dispatch_tests.json','post_ab_directed_regressions.json',
        'closed_registry_tests.json','closed_known_tests.json','object_routes_tests.json','control_word_tests.json','display_storage_tests.json','private_snapshots_tests.json','scalar_truth_tests.json','container_builtins_tests.json','buff_integer_tests.json','buff_full_pgo_tests.json')
    for name in names:
        r=read(name);assert r['passed'],name
        if 'dll_sha256' in r:assert r['dll_sha256']==actual,name
    obj=read('object_routes_tests.json');assert obj['cases']==320256 and obj['active_route_assertions']==10240
    assert read('post_ab_directed_regressions.json')['affected_object_route_cases']==320256
    gate=read('bundle_full_gate.json');hashes=read('bundle_vs_deployed_hashes.json');audit=read('full_type_audit.json')
    assert gate['complete'] and gate['dll_sha256']==actual
    for n,count in [('base',914),('expand',1690)]:
        r=gate['cohorts'][n];assert r['expected']==r['recorded']==r['verified']==r['passed']==count
        assert r['winner_mismatch']==0 and not r['pending']
    assert audit['fights']==hashes['unchanged_cpp_event_streams']==2604
    assert audit['coverage']['audit_mismatch']==audit['old_event_kernel_type_mismatches']==0
    assert hashes['baseline_dll_sha256']==EXPECTED and hashes['candidate_dll_sha256']==actual
    assert hashes['ordered_case_and_cpp_event_hashes_sha256']=='b8066c9224bc418923c62f5a3dafb8912100b21bb0026c3b13669872f90e2f54'
    measurement=read('measurements_summary.json');assert measurement['raw24_gate_passed'] and measurement['dll_sha256']==actual
    for n,h in measurement['report_sha256'].items():assert sha(WORK/n)==h
    serial=read('bundle_serial.json');cal=read('bundle_load_calibration.json');fit=read('bundle_load20.json')
    assert fit['dll_sha256']==actual and fit['reference_load_pct']==20
    for r in (serial,cal):
        assert r['dll_sha256']==actual and r['repeat']==len(r['samples'])==24 and r['fights']==200 and r['workers']==1
        assert r['inputs_sha256']=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
        assert r['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
        assert all(s['on_ac_before'] is True and s['on_ac_after'] is True and s['matched_original_terminal']==200 for s in r['samples'])
    assert min(s['fights_per_second'] for s in serial['samples'])>=50
    xs=[s['background_load_pct'] for s in cal['samples']]
    policy=json.loads((WORK/'user_load20_policy_20261126.json').read_bytes())
    assert policy['empirical_estimate_allowed_outside_observed_range'] and policy['candidate_dll_sha256']==actual
    assert fit['reference_is_extrapolation']==(not min(xs)<=20<=max(xs))
    slope,intercept=statistics.linear_regression(xs,[math.log(s['wall_s']) for s in cal['samples']])
    assert math.isclose(200/math.exp(intercept+20*slope),fit['fitted_fights_per_second_at_reference_load'],rel_tol=1e-10)
    pgo=read('fresh_profile_source.json');frozen_pgo=read('frozen_pgo_manifest.json')
    assert pgo['dll_sha256']==actual and pgo['source_manifest_sha256']==sha(WORK/'source_before_build.json')
    assert pgo['profile_training_and_release_source_identical'] and pgo['floating_options_unchanged']
    assert frozen_pgo['counts']==pgo['hot_profiles_sha256'] and len(frozen_pgo['counts'])==18
    for n,h in frozen_pgo['counts'].items():assert sha(WORK/'frozen_pgo_counts'/(n+'.gcda'))==h
    assert read('control_word_tests.json')['cases']==44608
    assert read('private_snapshots_tests.json')['cases']==234880 and read('post_ab_directed_regressions.json')['private_snapshot_cases']==234880
    assert read('scalar_truth_tests.json')['cases']==read('post_ab_directed_regressions.json')['scalar_truth_cases']==34400
    assert read('container_builtins_tests.json')['cases']==read('post_ab_directed_regressions.json')['container_builtin_cases']==128128
    assert read('buff_integer_tests.json')['cases']==218400
    assert read('post_ab_directed_regressions.json')['buff_integer_helper_cases']==204288 and read('post_ab_directed_regressions.json')['buff_integer_method_cases']==14112
    display=read('display_storage_tests.json');assert display['cases']==21888 and display['candidate_core_item_bytes']==2112 and display['per_case_hashes_equal']
    assert read('post_ab_directed_regressions.json')['display_storage_cases']==21888
    from prepare_native_buff_inline_types import verify_projection
    assert verify_projection(WORK/'bundle_src')['passed']
    options=read('compiled_option_receipt.json')
    assert options['passed'] and options['checked_hot_objects']==18 and options['compiler_options_identical_except_profile_directory'] and options['fp_contract_off_all'] and options['no_compiler_pta']
    assert read('post_ab_directed_regressions.json')['control_word_cases']==44608
    assert read('fresh_profile_source.json')['compiler_optimization_flags']==[]
    policy=read('user_load20_policy_20261126.json')
    assert policy['empirical_estimate_allowed_outside_observed_range'] and not policy['low_idle_window_required']
    report=dict(passed=True,dll_sha256=actual,baseline_dll_sha256=EXPECTED,changed_source_files=changed,
        complete_predeclared_pair_count=pairs,all_original_reports_retained=True,strict_event_cases=2604,
        independent_calibration20_covered=min(xs)<=20<=max(xs),
        empirical20_is_extrapolation=fit['reference_is_extrapolation'],
        protected_user_files_sha256={n:sha(REPO/n) for n in PROTECTED},
        evidence_sha256={n:sha(WORK/n) for n in [*names,selected.name,'bundle_full_gate.json',
            'bundle_vs_deployed_hashes.json','full_type_audit.json','measurements_summary.json','user_load20_policy_20261126.json']})
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2))

if __name__=='__main__':main()
