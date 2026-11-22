"""Install one frozen damage-chain transformation into an isolated source copy."""
import json
from prepare_native_damage_combo import prepare,STAGE,WORK as PROBE,EXPECTED,sha
BASE=STAGE/'native_perf50/spatial_bundle'

def optimize(native):
    before=json.loads((BASE/'source_before_build.json').read_bytes())
    assert before=={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    screen=json.loads((PROBE/'screen_matched.json').read_bytes());oracle=json.loads((PROBE/'extended_correctness.json').read_bytes())
    assert screen['passed'] and screen['matching_local_compilation'] and oracle['cases']==12920
    for name,expected in screen['dependency_sha256'].items():
        path=STAGE/name if name.endswith('.cpp') else PROBE/name
        assert sha(path)==expected,name
    for name,count in [('source_helper_cases.json',10464),('active_helper_cases.json',6480)]:
        row=json.loads((PROBE/name).read_bytes());assert row['passed'] and row['cases']==count and row['baseline_dll_sha256']==EXPECTED
        assert row['helper_header_sha256']==sha(PROBE/'preflight_damage_records.hpp')
    assert json.loads((PROBE/'reference_proof.json').read_bytes())['all_original_hashes_and_legacy_counters_equal']
    design=prepare(native)
    analysis=json.loads((PROBE/'source_analysis.json').read_bytes())
    import hashlib
    assert hashlib.sha256(design['helper'].encode()).hexdigest()==analysis['helper_sha256']
    assert hashlib.sha256(design['candidate'].encode()).hexdigest()==analysis['candidate_sha256']
    path=native/'gen/shards/shard_02.cpp';text=path.read_text('utf8')
    assert text.count(design['original'])==1 and 'native_damage_record_counts' not in text
    text=text.replace('#pragma STDC FP_CONTRACT OFF\n','#pragma STDC FP_CONTRACT OFF\n\n'+design['helper'],1)
    text=text.replace(design['original'],design['candidate'],1)
    text+='\nextern "C" uint64_t gd_diag_native_damage_record_stat(unsigned field){return field<6?gd::native_damage_record_counts[field]:0;}\n'
    path.write_text(text,encoding='utf8',newline='\n')
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    changed=sorted(name for name in before if before[name]!=after[name]);assert changed==['gen/shards/shard_02.cpp']
    result=json.loads((BASE/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,components=['exact local damage record propagation','typed integer flag probes','ordered integer type membership probes'],modified_native_files=changed,
        independent_parent_damage_cases=19400,independent_source_helper_cases=10464,record_sites=design['counts'],typed_source_sites=design['typed_source_sites'],
        helper_sha256=analysis['helper_sha256'],candidate_method_sha256=analysis['candidate_sha256'],
        all_layouts_public_arithmetic_rng_and_callback_order_unchanged=True,probe_rtti_adaptation_excluded_from_production=True,no_whole_fight_gain_claim=True)
    return result
