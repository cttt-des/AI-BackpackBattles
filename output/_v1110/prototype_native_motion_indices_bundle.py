"""Apply one frozen bounded-motion transformation to a baseline source copy."""
import json
from prepare_native_motion_indices import prepare,STAGE,WORK as PROBE,EXPECTED,sha
BASE=STAGE/'native_perf50/spatial_bundle'

def optimize(native):
    before=json.loads((BASE/'source_before_build.json').read_bytes())
    assert before=={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    oracle=json.loads((PROBE/'correctness_baseline.json').read_bytes())
    matched=json.loads((PROBE/'correctness_matched.json').read_bytes())
    screen=json.loads((PROBE/'screen_matched.json').read_bytes())
    assert oracle['passed'] and oracle['cases']==matched['cases']==5840
    assert oracle['case_hashes']==matched['case_hashes'] and oracle['legacy_counter_hashes']==matched['legacy_counter_hashes']
    assert screen['passed'] and screen['matching_local_compilation']
    for name,digest in screen['dependency_sha256'].items():
        path=STAGE/name if name.endswith('.cpp') else PROBE/name if name=='preflight_motion_indices.hpp' else native/name
        assert sha(path)==digest,name
    design=prepare(native);analysis=json.loads((PROBE/'source_analysis.json').read_bytes())
    assert design['candidate_sha256']==analysis['candidate_sha256']
    path=native/'gen/shards/shard_07.cpp';text=path.read_text('utf8')
    assert text.count(design['original'])==1 and 'native_motion_index_counts' not in text
    text=text.replace('#pragma STDC FP_CONTRACT OFF\n','#pragma STDC FP_CONTRACT OFF\n\n'+design['helper'],1)
    text=text.replace(design['original'],design['candidate'],1)
    text+='\nextern "C" uint64_t gd_diag_native_motion_index_stat(unsigned field){return field<3?gd::native_motion_index_counts[field]:0;}\n'
    path.write_text(text,encoding='utf8',newline='\n')
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    changed=sorted(name for name in before if before[name]!=after[name]);assert changed==['gen/shards/shard_07.cpp']
    result=json.loads((BASE/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,components=['bounded uint32 motion controls','native Bool keep flag'],modified_native_files=changed,
        independent_original_dll_cases=5840,candidate_method_sha256=design['candidate_sha256'],
        exact_initial_array_bound=True,all_entry_operations_live_after_callbacks=True,original_tail_and_unknown_queue_retained=True,
        all_layouts_public_arithmetic_rng_and_callback_order_unchanged=True,no_whole_fight_gain_claim=True)
    return result
