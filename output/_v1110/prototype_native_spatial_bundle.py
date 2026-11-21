"""Replace only three exact spatial method bodies, retaining all layouts."""
import json
from prepare_native_spatial import prepare,sha,STAGE,WORK as PROBE,EXPECTED
BASE=STAGE/'native_perf50/dispatch_chain_bundle'

def optimize(native):
    before=json.loads((BASE/'source_before_build.json').read_bytes())
    assert before=={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    screen=json.loads((PROBE/'screen.json').read_bytes())
    assert screen['passed'] and screen['cases']==11760 and screen['baseline_dll_sha256']==EXPECTED
    assert sha(STAGE/'test_native_spatial.cpp')==screen['test_source_sha256']
    assert sha(PROBE/'preflight_spatial.hpp')==screen['header_sha256']
    design=prepare(native)
    path=native/'gen/shards/shard_13.cpp';text=path.read_text('utf8')
    assert 'native_spatial_lookup' not in text
    text=text.replace('#pragma STDC FP_CONTRACT OFF\n','#pragma STDC FP_CONTRACT OFF\n\n'+design['helper'],1)
    for name,old in design['originals'].items():
        assert text.count(old)==1;text=text.replace(old,design['updates'][name],1)
    text+='\nextern "C" uint64_t gd_diag_native_spatial_stat(unsigned field){return field<4?gd::native_spatial_counts[field]:0;}\n'
    path.write_text(text,encoding='utf8',newline='\n')
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    changed=sorted(name for name in before if before[name]!=after[name]);assert changed==['gen/shards/shard_13.cpp']
    result=json.loads((BASE/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,components=['single dictionary lookup in three spatial methods','stable object pointer deduplication'],modified_native_files=changed,
        local_differential_cases=11760,all_layouts_arithmetic_rng_and_callback_order_unchanged=True,
        original_counters_preserved_in_local_differentials=True,no_whole_fight_gain_claim=True)
    return result
