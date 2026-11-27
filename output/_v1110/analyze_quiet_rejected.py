"""Attribute rejected-candidate samples, without treating shares as saved time."""
import json
from prepare_quiet_round import WORK,STAGE,EXPECTED,sha,save


def roles(functions):
    def has(term):return any(term in name for name in functions)
    trigger=has('::fn_trigger(')
    helper=has('gd_diag_quiet_core_advance')
    return dict(trigger_chain=trigger,
                original_core_frame_without_trigger=has('CoreCombat::fn_physicsTick(') and not trigger,
                setup=has('build_side_items('),
                new_segment_entry_including_original_tail=helper,
                new_character_preparation=has('QuietCorePlan::character('),
                new_plan_any=has('QuietCorePlan::'),
                new_entry_type_proof=helper and any(has(s) for s in ('native_resolved_exact_row(', '__do_dyncast(', 'type_info::operator==')),
                new_entry_fenv=helper and any(has(s) for s in ('fegetenv','fesetenv','__mingw_setfp')))


def summarize(profile):
    total=profile['samples'];counts={k:0 for k in roles([])}
    for stack in profile['resolved_stacks']:
        for key,value in roles(stack['functions']).items():
            if value:counts[key]+=stack['samples']
    return dict(samples=total,counts=counts,share_pct={k:100*v/total for k,v in counts.items()},
                shares_are_overlapping_not_additive=True,top_leaf=profile['leaf'][:20])


def main():
    baseline_path=STAGE/'native_perf50/measurement_structure_bundle/profile_baseline.json'
    candidate_path=WORK/'rejected_cost_profile.json'
    baseline=json.loads(baseline_path.read_bytes());candidate=json.loads(candidate_path.read_bytes())
    assert baseline['dll_sha256']==EXPECTED
    assert candidate['dll_sha256']==sha(WORK/'bundle.dll') and candidate['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    assert baseline['inputs_sha256']==candidate['inputs_sha256'] and baseline['samples']>=8000 and candidate['samples']>=8000
    full=json.loads((WORK/'formal_quiet_fast_full_tests.json').read_bytes())
    fixed=json.loads((WORK/'formal_quiet_core_tests.json').read_bytes())['exercised_core_counts']
    def counters(r):return dict(**r,rejected_fraction=r['rejected']/r['attempts'])
    result=dict(passed=True,baseline=summarize(baseline),candidate=summarize(candidate),
                fixed200=counters(fixed),full2604=counters(full['coverage']),
                profile_sha256={'baseline':sha(baseline_path),'candidate':sha(candidate_path)},
                interpretation='Repeated graph/type proof and plan preparation are a substantial new cost; fallback attempts pay this work too. The helper share includes retained original tail work and is not wholly removable overhead.',
                static_source_findings=['Entry captures fenv and allocates/initializes the plan before prepare checks all mode eligibility',
                                        'Rejected attempts build the graph again on the next original frame',
                                        'Each certificate visits buff, item, gem and timer objects and repeats RTTI/row proof',
                                        'Original per-frame RNG/idle/visual tails and trigger/damage chain still execute'],
                no_profile_based_speed_claim=True,no_same_source_additional_AB=True,
                next_architecture_requirement='Amortize a closed-scene certificate with proven callback/watch invalidation and reuse nearest-due information; test this cost in an instrumented prototype before another full PGO round.',
                conclusion='Reject this per-attempt certificate/precomputation implementation; this does not falsify all idle-interval or local-event scheduling designs.')
    save('rejected_cost_analysis.json',result)
    print(json.dumps({k:result[k]['share_pct'] for k in ('baseline','candidate')},indent=2))


if __name__=='__main__':main()
