"""Reassess saved timings only; never launch a simulator or a compiler."""
from collections import defaultdict
import hashlib
import json
from pathlib import Path
import statistics

WORK=Path(__file__).resolve().parent
PERF=WORK.parent

def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def summarize(pairs,metric):
    reductions=[100*(1-p['candidate'][metric]/p['baseline'][metric]) for p in pairs]
    return {'paired_median_time_reduction_pct':statistics.median(reductions),
            'candidate_wins':sum(x>0 for x in reductions),'ties':sum(x==0 for x in reductions),
            'pairs':len(pairs),'sum_time_reduction_pct':100*(1-
                sum(p['candidate'][metric] for p in pairs)/sum(p['baseline'][metric] for p in pairs))}

def main():
    groups=defaultdict(list)
    accepted=set()
    folders=[PERF,*sorted(p for p in PERF.iterdir() if p.is_dir() and
        (p.name.startswith('cycles') or p.name in ('followup','assembly','native_event_kernel_a')))]
    for folder in folders:
        for path in sorted(folder.glob('*.json')):
            if 'pooled' in path.name:continue # Aggregate files duplicate the raw pairs.
            r=json.loads(path.read_bytes())
            if not isinstance(r,dict):continue
            if 'runtime' in r and r.get('training_matched_baseline') and r.get('changed_native_files'):
                accepted.add(r['dll_sha256'])
            if not isinstance(r.get('pairs'),list) or not r.get('candidate_dll_sha256'):continue
            if not all(isinstance(p,dict) and all(k in p for k in ('baseline','candidate'))
                       and all(m in p[a] for a in ('baseline','candidate') for m in ('main_thread_cpu_s','wall_s'))
                       for p in r['pairs']):continue
            groups[r['baseline_dll_sha256'],r['candidate_dll_sha256']].append((path,r))
    rows=[]
    for (baseline,candidate),reports in groups.items():
        raw=[p for _,r in reports for p in r['pairs']]
        clean=[p for _,r in reports if not r.get('concurrent_activity') for p in r['pairs']]
        row={'baseline_sha256':baseline,'candidate_sha256':candidate,
             'same_dll_control':baseline==candidate,'historically_deployed':candidate in accepted,
             'all_saved_pairs':{m:summarize(raw,m) for m in ('main_thread_cpu_s','wall_s')},
             'without_explicitly_contaminated_reports':{m:summarize(clean,m) for m in ('main_thread_cpu_s','wall_s')} if clean else None,
             'reports':[{'path':p.relative_to(PERF).as_posix(),'sha256':sha(p),
                         'cpu_median_reduction_pct':r['main_thread_cpu_s']['median_reduction_pct'],
                         'wall_median_reduction_pct':r['wall_s']['median_reduction_pct'],
                         'pairs':len(r['pairs']),'concurrent_activity':r.get('concurrent_activity'),
                         'execution_mode':r.get('execution_mode','legacy in-process comparison'),
                         'minimum_warmup_seconds':r.get('warmup',{}).get('minimum_seconds'),
                         'worker_priority_class':r.get('worker_priority_class'),
                         'worker_cpu_affinity':r.get('worker_cpu_affinity')} for p,r in reports]}
        rows.append(row)
    result={'scope':'Existing structured fixed200 paired records in followup, assembly and all cycles through native event kernel. Older small training-throughput observations are contextual only.',
            'method':'Time reduction, not throughput increase; pool only identical baseline and candidate SHA; retain every pair; do not mix pooled reports back into raw data. Different protocol strata remain listed and are not proof of a universal gain.',
            'timing_reports':sum(len(r['reports']) for r in rows),'unique_baseline_candidate_comparisons':len(rows),
            'raw_pairs':sum(r['all_saved_pairs']['wall_s']['pairs'] for r in rows),
            'new_measurements_run':False,'rows':rows}
    out=WORK/'prior_trials_matrix.json'
    out.write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps({k:v for k,v in result.items() if k!='rows'},ensure_ascii=False,indent=2))

if __name__=='__main__':main()
