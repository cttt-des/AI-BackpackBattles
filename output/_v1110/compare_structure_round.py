"""Frozen calibrated A/B: exactly24 quads in two independent sessions."""
import json,math,subprocess,sys
from prepare_structure_round import WORK,STAGE,BASE,EXPECTED,sha,save,verify_projection
from install_ordering_correctness import boundary
def timing():
    boundary();verify_projection(WORK/'bundle_src');assert sha(BASE/'libgdcore.dll')==EXPECTED
    gate=json.loads((WORK/'complete_correctness_gate.json').read_bytes());assert gate['passed'] and gate['dll_sha256']==sha(WORK/'bundle.dll')
    plan=json.loads((WORK/'formal_ab_protocol.json').read_bytes());assert not (WORK/'ab_fixed_1.json').exists()
    calibration=json.loads((WORK/'calibration_plan.json').read_bytes())
    for name in ('measure_native_quads.py','measurement_platform.py','measure_native_corpus_blocks.py'):
        assert sha(STAGE/name)==calibration['scripts_sha256'][name],name
    assert sha(WORK/'calibration_plan.json')==plan['calibration_plan_sha256'] and sha(WORK/'aa_analysis.json')==plan['aa_analysis_sha256']
    assert sha(WORK/'formal_ab_protocol.json')==json.loads((WORK/'architecture_selection.json').read_bytes())['frozen_AB_protocol_sha256']
    assert not (WORK/'formal_timing_inputs.json').exists()
    save('formal_timing_inputs.json',dict(candidate_dll_sha256=sha(WORK/'bundle.dll'),baseline_dll_sha256=EXPECTED,protocol_sha256=sha(WORK/'formal_ab_protocol.json'),source_manifest_sha256=sha(WORK/'source_before_build.json'),scripts_sha256={name:sha(STAGE/name) for name in ('measure_native_quads.py','measurement_platform.py','measure_native_corpus_blocks.py','compare_structure_round.py','analyze_structure_aa.py')},written_before_any_warmup_or_arm=True))
    for i,seed in enumerate(plan['seeds'],1):
        args=[sys.executable,'-u','-X','utf8',str(STAGE/'measure_native_quads.py'),'--baseline',str(WORK/'baseline.dll'),'--candidate',str(WORK/'bundle.dll'),'--reference',str(WORK/'fixed200_reference.json'),'--out',str(WORK/f'ab_fixed_{i}.json'),'--logical-cpu',str(plan['logical_cpu']),'--quads',str(plan['quads_per_session']),'--repetitions',str(plan['repetitions']),'--warmup-seconds',str(plan['warmup_seconds']),'--seed',str(seed)]
        if i==2:args.append('--candidate-load-first')
        with (WORK/f'ab_fixed_{i}.log').open('xb') as log:subprocess.run(args,stdout=log,stderr=subprocess.STDOUT,check=True)
    boundary();verify_projection(WORK/'bundle_src');assert sha(BASE/'libgdcore.dll')==EXPECTED
    save('ab_timing_complete.json',dict(passed=True,all_predeclared24_quads_completed=True,no_analysis_or_compiles_during_timing=True))
    print('All frozen A/B timing completed',flush=True)
def analyze():
    import numpy as np
    from analyze_structure_aa import bootstrap,METRICS,pct
    assert (WORK/'ab_timing_complete.json').exists();plan=json.loads((WORK/'formal_ab_protocol.json').read_bytes())
    reports=[json.loads((WORK/f'ab_fixed_{i}.json').read_bytes()) for i in (1,2)]
    assert all(r['baseline_dll_sha256']==EXPECTED and r['candidate_dll_sha256']==sha(WORK/'bundle.dll') and len(r['quads'])==12 for r in reports)
    sessions=[np.array([[q['log_time_reduction'][k] for k in METRICS] for q in r['quads']]) for r in reports];point=np.median(np.concatenate(sessions),axis=0)
    intervals={str(b):np.quantile(bootstrap(sessions,b,plan['bootstrap_seed']),[.025,.975],axis=0).tolist() for b in plan['block_lengths']}
    positive_intervals=all(np.all(np.array(v)[0]>0) for v in intervals.values());above_null=bool(np.all(point>np.array(plan['minimum_point_log_reduction'])))
    directions=[np.median(s,axis=0).tolist() for s in sessions];consistent=bool(np.all(np.array(directions)>0));accepted=positive_intervals and above_null and consistent
    metrics={}
    for j,k in enumerate(METRICS):
        sums={label:sum(a[k] for r in reports for q in r['quads'] for a in q['arms'] if a['label']==label) for label in ('A','B')}
        metrics[k]=dict(quads=24,paired_median_time_reduction_pct=pct(point[j]),sum_time_reduction_pct=100*(1-sums['B']/sums['A']),median95_interval_pct_by_block={b:pct(np.array(v)[:,j]) for b,v in intervals.items()},minimum_AA_point_reduction_pct=pct(plan['minimum_point_log_reduction'][j]))
    negative_intervals=(all(np.all(np.array(v)[1]<0) for v in intervals.values())
        and bool(np.all(-point>np.array(plan['minimum_point_log_reduction'])))
        and bool(np.all(np.array(directions)<0)))
    status='positive_calibrated_evidence' if accepted else 'consistent_regression_retained' if negative_intervals else 'inconclusive_retained'
    assessment=dict(status=status,baseline_dll_sha256=EXPECTED,candidate_dll_sha256=sha(WORK/'bundle.dll'),metrics=metrics,session_median_reduction_pct=[pct(d) for d in directions],log95_intervals_by_block=intervals,acceptance=dict(both_interval_lower_bounds_positive=positive_intervals,points_exceed_frozen_AA_null_envelopes=above_null,both_sessions_both_directions_positive=consistent),all24_quads_and_extremes_retained=True,no_same_source_retiming=True,protocol_sha256=sha(WORK/'formal_ab_protocol.json'))
    save('ab_assessment.json',assessment);save('candidate_decision.json',dict(status=status,accepted=accepted,selected_assessment='ab_assessment.json',assessment_sha256=sha(WORK/'ab_assessment.json'),candidate_dll_sha256=sha(WORK/'bundle.dll'),baseline_dll_sha256=EXPECTED,quads=24,bracketed_inner_contrasts=48,all_original_pairs_and_extremes_retained=True,no_same_source_retiming=True,not_deployed_yet=True))
    print(json.dumps(assessment,indent=2),flush=True)
if __name__=='__main__':{'timing':timing,'analyze':analyze}[sys.argv[1]]()
