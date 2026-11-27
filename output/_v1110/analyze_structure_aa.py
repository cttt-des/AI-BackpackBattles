"""Full retained A/A bootstrap; no deletion or favorable resampling."""
import hashlib,json,math,sys
from pathlib import Path
import numpy as np
from calibrate_structure_measurement import WORK,STAGE,write
METRICS=('main_thread_cpu_s','wall_s')
def pct(x):return (100*(-np.expm1(-np.asarray(x)))).tolist()
def bootstrap(sessions,block,seed):
    rng=np.random.default_rng(seed);parts=[]
    for data in sessions:
        n=len(data);starts=rng.integers(n,size=(20000,math.ceil(n/block)))
        indices=((starts[:,:,None]+np.arange(block))%n).reshape(20000,-1)[:,:n]
        parts.append(data[indices])
    return np.median(np.concatenate(parts,axis=1),axis=1)
def main():
    assert (WORK/'aa_timing_complete.json').exists()
    reports=[json.loads((WORK/f'aa_fixed_{i}.json').read_bytes()) for i in (1,2)]
    sessions=[np.array([[q['log_time_reduction'][k] for k in METRICS] for q in r['quads']]) for r in reports]
    combined=np.concatenate(sessions);point=np.median(combined,axis=0)
    out=dict(same_dll=True,sessions=2,quads=24,all_samples_retained=True,metrics=list(METRICS),median_log_reduction=point.tolist(),median_reduction_pct=pct(point),session_median_reduction_pct=[pct(np.median(s,axis=0)) for s in sessions],bootstrap={})
    for block in (2,3):
        draws=bootstrap(sessions,block,271104)
        centered=[s-np.median(s,axis=0) for s in sessions]
        noise=bootstrap(centered,block,271104)
        null95=np.quantile(np.abs(draws),.95,axis=0)
        threshold=np.maximum(np.quantile(noise,.975,axis=0),null95)
        joint=np.quantile(np.max(threshold-noise,axis=1),.8)
        out['bootstrap'][str(block)]=dict(resamples=len(draws),median95_interval_pct=pct(np.quantile(draws,[.025,.975],axis=0)),absolute_null95_log_envelope=null95.tolist(),absolute_null95_envelope_pct=pct(null95),joint80_detectable_log_reduction=float(joint),joint80_detectable_reduction_pct=pct(joint),model='empirical block bootstrap of observed A/A; local environment estimate, not universal power guarantee')
    for i,(r,data) in enumerate(zip(reports,sessions),1):
        arms=[a for q in r['quads'] for a in q['arms']]
        ranges={k:dict(min=min(a[k] for a in arms),max=max(a[k] for a in arms),first4_median=float(np.median([a[k] for a in arms[:4]])),last4_median=float(np.median([a[k] for a in arms[-4:]]))) for k in METRICS}
        order={p:pct(np.median([data[j] for j,q in enumerate(r['quads']) if q['order']==p],axis=0)) for p in ('ABBA','BAAB')}
        out[f'session_{i}_diagnostics']=dict(cost_drift=ranges,order_medians_pct=order,lag1_correlation=[float(np.corrcoef(data[:-1,j],data[1:,j])[0,1]) for j in range(2)],background_load_range=[min(a['background_load_pct'] for a in arms),max(a['background_load_pct'] for a in arms)])
    old=json.loads((WORK/'aa_old.json').read_bytes());out['old_method_control']={k:old[k] for k in METRICS}
    write('aa_analysis.json',out)
    frozen=dict(version=1,calibration_plan_sha256=hashlib.sha256((WORK/'calibration_plan.json').read_bytes()).hexdigest(),aa_analysis_sha256=hashlib.sha256((WORK/'aa_analysis.json').read_bytes()).hexdigest(),logical_cpu=2,formal_sessions=2,quads_per_session=12,repetitions=4,warmup_seconds=120,seeds=[271201,271202],reverse_load_order_second_session=True,bootstrap_seed=271203,bootstrap_resamples=20000,block_lengths=[2,3],primary_estimator='median of time-bracketed quad log contrasts',minimum_point_log_reduction=np.maximum(*[np.array(out['bootstrap'][str(b)]['absolute_null95_log_envelope']) for b in (2,3)]).tolist(),acceptance=dict(both_CPU_and_wall95_lower_bounds_positive_for_both_block_lengths=True,both_point_gains_above_frozen_AA_envelopes=True,both_sessions_CPU_and_wall_direction_positive=True,raw24_all_batches_FPS_at_least50=True,full2604_original_event_identity=True),all_first_samples_retained=True,no_same_source_additional_timing=True,load20=dict(formula='log(wall_seconds)=a+b*background_load_pct',allow_extrapolation=True,no_load_coverage_gate=True))
    assert not (WORK/'formal_ab_protocol.json').exists();write('formal_ab_protocol.json',frozen)
    print(json.dumps(out,ensure_ascii=False,indent=2))
if __name__=='__main__':main()
