"""Exclusive sampling attribution and original log inactivity (not skip proof)."""
import json,sys
from pathlib import Path
from collections import Counter
from calibrate_structure_measurement import WORK,STAGE,REPO,write
from prepare_frame_guard_reuse import sha
def main():
    r=json.loads((WORK/'profile_baseline.json').read_bytes());totals=Counter()
    for row in r['resolved_stacks']:
        f=row['functions']
        if any('::fn_trigger(' in x for x in f):phase='trigger_chain'
        elif any('CoreCombat::fn_physicsTick(' in x for x in f):phase='frame_without_trigger'
        elif any('build_side_items(' in x for x in f):phase='item_assembly'
        else:phase='other_setup_and_export'
        totals[phase]+=row['samples']
    from bench_native_corpus import select_cases
    from check_native_corpus_gate import reference_index
    references=reference_index(STAGE/'native_host_observed_reference_plan.json');index={k:v for cases in references.values() for k,v in cases.items()}
    cases=[]
    for _,name,_ in select_cases(200):
        ref=index[name];path=STAGE/ref['path']/name/'events.json';record=json.loads(path.read_bytes());ticks=int(record['ticks'])
        occupied={min(ticks,max(1,round(float(e['timestamp'])*60))) for e in record['events'] if float(e['timestamp'])>0}
        cases.append(dict(case_id=name,ticks=ticks,logged_event_tick_bins=len(occupied),ticks_without_logged_event=ticks-len(occupied)))
    total=sum(c['ticks'] for c in cases);quiet=sum(c['ticks_without_logged_event'] for c in cases)
    out=dict(samples=r['samples'],exclusive_sample_counts=dict(totals),exclusive_sample_pct={k:v*100/r['samples'] for k,v in totals.items()},sampling_is_attribution_not_achievable_gain=True,
        original_log_inactivity=dict(total_ticks=total,ticks_without_logged_event=quiet,percent=quiet*100/total,timestamp_rounding_to_60Hz_bins=True,not_proof_of_semantic_empty_frames=True,cases=cases),
        original_source_sha256={p:sha(REPO/p) for p in ['oracle/Items/Item.gd','oracle/Core/Character.gd','oracle/Interface/CombatTimer/CombatTimer.gd','oracle/Utility/Util.gd']},
        whole_frame_skip_obstacles=['Item._physics_process decrements triggerTime and reads character stun/speed every tick','Character stun and stamina evolve between attacks','timer passes preserve phase order and float32/double recurrences','motion/particles/critical shake consume RNG in apparently log-free frames','host RNG injection and deferred callbacks are observation boundaries'],
        safe_architectural_candidate_classes=['compact hot execution state or field layout; preserve each original operation and callback visibility','immutable lineup assembly plan with mutable per-fight graph; separately measure cold and repeated use','certified quiet segments only with exact recurrences and complete observer/deadline proof'])
    if (WORK/'diagnostic_counts.json').exists():out['operation_counts']=json.loads((WORK/'diagnostic_counts.json').read_bytes())['counts']
    write('structural_cost_assessment.json',out)
    print(json.dumps({k:v for k,v in out.items() if k not in ('original_log_inactivity','original_source_sha256')},indent=2));print('log-free tick bins',quiet,total,quiet*100/total)
if __name__=='__main__':main()
