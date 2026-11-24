"""Review frozen full-round evidence before changing the production runtime."""
import json
from pathlib import Path
import statistics
import math
from prepare_native_callback_dispatch import STAGE,BASE,EXPECTED,sha

WORK=STAGE/'native_perf50/callback_dispatch_bundle'
REPO=STAGE.parents[1]
PROTECTED=['native_sim_cpp/native_sim/libgdcore.dll','oracle/Items/Item.gd',
    'output/perf/_cpp1690_final.json','output/perf/_cpp1690_chain.json',
    'output/perf/alignment_1690_chain.json','output/perf/alignment_1690_final.json']

def read(name):return json.loads((WORK/name).read_bytes())

def main():
    out=WORK/'pre_install_review.json';assert not out.exists()
    actual=sha(WORK/'bundle.dll')
    assert actual=='80a0681c1c93268af2b29c21e5439b6444de36a29ad39486b3f4afadf548a44a'
    assert sha(BASE/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==EXPECTED
    frozen=read('source_before_build.json')
    assert sum(Path(n).suffix in ('.cpp','.hpp') or Path(n).name=='build_windows.py' for n in frozen)==707
    assert frozen=={p.relative_to(WORK/'bundle_src').as_posix():sha(p) for p in (WORK/'bundle_src').rglob('*') if p.is_file()}
    changed=[n for n,h in frozen.items() if sha(BASE/n)!=h]
    assert sorted(changed)==['gd_rt.cpp','native_event_kernel.hpp','native_resolved_dispatch.hpp']
    decision=read('candidate_decision.json');ab=read('ab_assessment_32.json')
    assert decision['status']==ab['status']=='positive_combined_evidence'
    assert decision['assessment_sha256']==sha(WORK/'ab_assessment_32.json')
    assert ab['baseline_dll_sha256']==EXPECTED and ab['candidate_dll_sha256']==actual
    for metrics in [ab['metrics'],*ab['leave_one_group_out_sensitivity']]:
        assert all(r['paired_median_time_reduction_pct']>0 and r['sum_time_reduction_pct']>0 for r in metrics.values())
    assert all(r['pairs']==32 for r in ab['metrics'].values()) and len(ab['reports'])==4
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
        'closed_registry_tests.json','closed_known_tests.json')
    for name in names:
        r=read(name);assert r['passed'],name
        if 'dll_sha256' in r:assert r['dll_sha256']==actual,name
    gate=read('bundle_full_gate.json');hashes=read('bundle_vs_deployed_hashes.json');audit=read('full_type_audit.json')
    assert gate['complete'] and gate['dll_sha256']==actual
    for n,count in [('base',914),('expand',1690)]:
        r=gate['cohorts'][n];assert r['expected']==r['recorded']==r['verified']==r['passed']==count
        assert r['winner_mismatch']==0 and not r['pending']
    assert audit['fights']==hashes['unchanged_cpp_event_streams']==2604
    assert audit['coverage']['audit_mismatch']==audit['old_event_kernel_type_mismatches']==0
    assert hashes['baseline_dll_sha256']==EXPECTED and hashes['candidate_dll_sha256']==actual
    assert hashes['ordered_case_and_cpp_event_hashes_sha256']=='b8066c9224bc418923c62f5a3dafb8912100b21bb0026c3b13669872f90e2f54'
    measurement=read('measurements_summary.json');assert measurement['raw24_gate_passed']
    for n,h in measurement['report_sha256'].items():assert sha(WORK/n)==h
    serial=read('bundle_serial.json');cal=read('bundle_load_calibration.json');fit=read('bundle_load20.json')
    for r in (serial,cal):
        assert r['dll_sha256']==actual and r['repeat']==len(r['samples'])==24 and r['fights']==200 and r['workers']==1
        assert all(s['on_ac_before'] is True and s['on_ac_after'] is True and s['matched_original_terminal']==200 for s in r['samples'])
    assert min(s['fights_per_second'] for s in serial['samples'])>=50
    xs=[s['background_load_pct'] for s in cal['samples']]
    assert min(xs)<=20<=max(xs)
    slope,intercept=statistics.linear_regression(xs,[math.log(s['wall_s']) for s in cal['samples']])
    assert math.isclose(200/math.exp(intercept+20*slope),fit['fitted_fights_per_second_at_reference_load'],rel_tol=1e-10)
    pgo=read('fresh_profile_source.json');frozen_pgo=read('frozen_pgo_manifest.json')
    assert pgo['dll_sha256']==actual and pgo['source_manifest_sha256']==sha(WORK/'source_before_build.json')
    assert pgo['profile_training_and_release_source_identical'] and pgo['floating_options_unchanged']
    assert frozen_pgo['counts']==pgo['hot_profiles_sha256'] and len(frozen_pgo['counts'])==18
    for n,h in frozen_pgo['counts'].items():assert sha(WORK/'frozen_pgo_counts'/(n+'.gcda'))==h
    report=dict(passed=True,dll_sha256=actual,baseline_dll_sha256=EXPECTED,changed_source_files=changed,
        complete32_and_all_leave_one_out_positive=True,strict_event_cases=2604,independent_calibration20_covered=True,
        protected_user_files_sha256={n:sha(REPO/n) for n in PROTECTED},
        evidence_sha256={n:sha(WORK/n) for n in [*names,'ab_assessment_32.json','bundle_full_gate.json',
            'bundle_vs_deployed_hashes.json','full_type_audit.json','measurements_summary.json']})
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2))

if __name__=='__main__':main()
