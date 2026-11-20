"""Assess the whole bundle without a per-edit or group-unanimity requirement."""
import argparse
import hashlib
import json
from pathlib import Path
import statistics

def summarize(pairs,metric):
    changes=[100*(1-p['candidate'][metric]/p['baseline'][metric]) for p in pairs]
    return {'paired_median_time_reduction_pct':statistics.median(changes),
        'sum_time_reduction_pct':100*(1-sum(p['candidate'][metric] for p in pairs)/sum(p['baseline'][metric] for p in pairs)),
        'candidate_wins':sum(x>0 for x in changes),'ties':sum(x==0 for x in changes),'pairs':len(pairs)}

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--reports',type=Path,nargs='+',required=True)
    parser.add_argument('--out',type=Path,required=True)
    args=parser.parse_args()
    assert not args.out.exists(),'Use a new assessment path; retain prior decisions.'
    reports=[json.loads(p.read_bytes()) for p in args.reports]
    assert len({(r['baseline_dll_sha256'],r['candidate_dll_sha256'],r['inputs_sha256'],r['results_sha256']) for r in reports})==1
    assert all(r['workers']==1 and r['fights']==200 and r['execution_mode']=='separate_single_dll_processes' for r in reports)
    pairs=[p for r in reports for p in r['pairs']]
    metrics={m:summarize(pairs,m) for m in ('main_thread_cpu_s','wall_s')}
    positive=all(v['paired_median_time_reduction_pct']>0 for v in metrics.values())
    negative_groups=all(r[m]['median_reduction_pct']<0 for r in reports for m in metrics)
    status='positive_combined_evidence' if positive else 'consistent_regression_bundle_only' if negative_groups else 'inconclusive_retained'
    arms=[p[a] for p in pairs for a in ('baseline','candidate')]
    result={'baseline_dll_sha256':reports[0]['baseline_dll_sha256'],'candidate_dll_sha256':reports[0]['candidate_dll_sha256'],
        'status':status,'individual_components_not_rejected':True,'metrics':metrics,
        'group_medians':[{m:r[m]['median_reduction_pct'] for m in metrics} for r in reports],
        'leave_one_group_out_sensitivity':[{m:summarize([p for j,r in enumerate(reports) if j!=i for p in r['pairs']],m)
            for m in metrics} for i in range(len(reports))] if len(reports)>1 else [],
        'background_load_range_pct':[min(a['background_load_pct'] for a in arms),max(a['background_load_pct'] for a in arms)],
        'on_ac_all':all(a['on_ac_before'] and a['on_ac_after'] for a in arms),
        'reports':[{'path':str(p),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()} for p in args.reports],
        'semantics_and_raw24_required_before_deployment':True,
        'interpretation':'This measures a bundle. It does not prove each component helps or that old percentage estimates add together.'}
    args.out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps({k:v for k,v in result.items() if k not in ('reports','leave_one_group_out_sensitivity')},indent=2))

if __name__=='__main__':main()
