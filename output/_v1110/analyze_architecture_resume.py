"""Retain all small-screen contrasts; distinguish leaf and subtree weights."""
import json,math,statistics
from pathlib import Path
from native_build_storage import sha
STAGE=Path(__file__).resolve().parent;WORK=STAGE/'native_perf50/architecture_three_bundle'
def save(name,value):(WORK/name).write_text(json.dumps(value,indent=2,ensure_ascii=False)+'\n',encoding='utf8')
def analyze(prefix,keys):
    receipt=json.loads((WORK/(prefix+'_resume_probe_receipt.json')).read_bytes());raw=WORK/receipt['raw_path'];assert sha(raw)==receipt['raw_sha256'];data=json.loads(raw.read_bytes());groups={}
    for r in data['samples']:groups.setdefault(tuple(r[k] for k in keys),[]).append(r)
    results=[]
    for group,rows in groups.items():
        assert len({r['signature'] for r in rows})==1
        labels=sorted({r['label'] for r in rows});left='R' if 'R' in labels else 'A';right='C' if 'C' in labels else 'B';metrics={}
        for metric in ['wall_s','cycles']:
            reductions=[]
            for quad in range(4):
                a=[r[metric] for r in rows if r['quad']==quad and r['label']==left];b=[r[metric] for r in rows if r['quad']==quad and r['label']==right];assert len(a)==len(b)==2
                reductions.append((1-math.exp((sum(map(math.log,b))-sum(map(math.log,a)))/2))*100)
            metrics[metric]=dict(median_reduction_pct=statistics.median(reductions),all4_quad_reductions_pct=reductions)
        results.append(dict(group=dict(zip(keys,group)),reference=left,candidate=right,metrics=metrics))
    save(prefix+'_resume_analysis.json',dict(raw_sha256=sha(raw),receipt_sha256=sha(WORK/(prefix+'_resume_probe_receipt.json')),all_samples_retained=True,statistic='median of 4 time-bracketed geometric contrasts',not_formal_workload_AB=True,rows=results));return results
def main():
    invariant=analyze('invariant',['period']);timeline=analyze('timeline',['mode','comparison']);step=analyze('timeline_step',['mode','comparison']);delay=analyze('delay',['count','comparison'])
    profile=STAGE/'native_perf50/measurement_structure_bundle/profile_baseline.json';d=json.loads(profile.read_bytes());terms=['::fn_tickMotion(','::fn__tickChargePath(','::fn_tickVisualMotion(','::fn_stepCharacterIdle(','::fn__step_native_delays(']
    selected=[r for r in d['resolved_stacks'] if any(any(t in f for t in terms) for f in r['functions'])]
    union=sum(r['samples'] for r in selected);leaf=sum(n for f,n in d['leaf'] if any(t in f for t in terms));assert (union,leaf)==(708,448)
    callbacks=sum(r['samples'] for r in selected if any('::fn__chargeEnterCell(' in f for f in r['functions']));idle=sum(r['samples'] for r in selected if any('::fn_stepCharacterIdle(' in f for f in r['functions']))
    assert callbacks==156 and idle==158
    save('profile_weight_correction.json',dict(profile_sha256=sha(profile),samples=d['samples'],five_function_leaf_sum=leaf,five_function_leaf_pct=leaf*100/d['samples'],five_subtree_union=union,five_subtree_union_pct=union*100/d['samples'],charge_callback_subtree_retained=callbacks,idle_subtree_retained=idle,remaining_sampled_upper_bound=union-callbacks-idle,remaining_upper_bound_pct=(union-callbacks-idle)*100/d['samples'],handoff_5_55_percent_was_leaf_sum_not_subtree_union=True,not_all_remaining_cost_is_removable=True))
    save('resume_gate_decisions.json',dict(baseline_dll_sha256=d['dll_sha256'],phase_plan=dict(decision='no_go_for_this_round',semantic_cases=9792,reason='Complete live raw-input qualification and sticky replay leave only a small/noisy target-segment margin. Per-frame input churn is slower. Projected game gain is below the calibrated wall envelope; no full build for this path.',source='invariant_resume_analysis.json'),exact_deadlines=dict(decision='no_go_for_current_watch_reuse_design',model_scenarios=128,observation_comparisons=13440,untracked_actual_DLL_writers=5,reason='Current structure/eligibility versions are not numeric invalidation certificates. Direct and resolved getters see stale pending storage; materialization must precede writes and cannot re-raise cleared flags. Correct bounded model still scans lanes. A complete observer/writer instrumentation project is required to remove that traversal; not justified by short-window arithmetic cost and invariant screen.',model_is_not_game_scheduler_proof=True,source='frontier_resume_probe_receipt.json'),typed_timeline=dict(decision='go_to_isolated_normal_candidate',reason='Typed original FP32 stepping has substantially more margin than record caching alone. Actual DLL controls used; local-only delay speedup discounted. Full normal build and directed actual-DLL tests precede fresh PGO; complete optimized2604 and frozen24-quad AB still required.',source=['timeline_step_resume_analysis.json','delay_resume_analysis.json','profile_weight_correction.json']),no_deployment_or_whole_game_gain_claim=True))
    progress=json.loads((WORK/'assessment_progress.json').read_bytes());progress['goal_status']='active';progress['resume_decisions']='resume_gate_decisions.json';progress['directions'][2]['component_upper_bound_pct']=union*100/d['samples'];progress['directions'][2]['upper_bound_note']='Corrected from raw stacks:708/8070 subtree-union samples;448/8070 is leaf sum.156 callback samples inside this union and158 idle subtree samples retained. Remaining394 samples are an optimistic opportunity boundary, not removable gain. Global195 chargeEnterCell inclusive samples also contain39 outside the selected timeline union.';save('assessment_progress.json',progress)
    print('All probe arms analyzed; leaf/subtree correction and concrete gates saved')
if __name__=='__main__':main()
