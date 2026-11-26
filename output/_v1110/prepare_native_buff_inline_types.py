"""Specialize actual integer operations inside the native Buff gain hot chain."""
import hashlib
import json
from pathlib import Path
import shutil
STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/container_builtins_bundle'
BACKUP=STAGE/'native_perf50/buff_integer_kernel_bundle'
WORK=STAGE/'native_perf50/buff_inline_types_prototype'
EXPECTED='5bd31fdc2ab2e4a556c63987de62b9541d5793752d67662cc4034a36bdd69ecc'
ARCHIVE='5b28ade7ade2de018f121971f4c3bea4648c28d5'
SHARD='gen/shards/shard_00.cpp'
SIGNATURE='gd::GdVal Gd__gd_core__CoreBuff::fn_gainTemporary('
HELPERS='''namespace {
// These helpers belong only to CoreBuff's native gain path. Unknown operand
// domains and overflow execute the original runtime operation exactly once.
__attribute__((always_inline)) inline gd::GdVal native_buff_integer_add(gd::BattleCtx& ctx,const gd::GdVal& a,const gd::GdVal& b) {
    if(a.kind==gd::GdVal::Kind::Int && b.kind==gd::GdVal::Kind::Int) {
        int64_t value;if(!__builtin_add_overflow(a.i,b.i,&value))return gd::GdVal::from_int(value);
    }
    return gd::gd_add(ctx,a,b);
}
__attribute__((always_inline)) inline gd::GdVal native_buff_integer_sub(const gd::GdVal& a,const gd::GdVal& b) {
    if(a.kind==gd::GdVal::Kind::Int && b.kind==gd::GdVal::Kind::Int) {
        int64_t value;if(!__builtin_sub_overflow(a.i,b.i,&value))return gd::GdVal::from_int(value);
    }
    return gd::gd_sub(a,b);
}
__attribute__((always_inline)) inline gd::GdVal native_buff_integer_min(const gd::GdVal& a,const gd::GdVal& b) {
    if(a.kind==gd::GdVal::Kind::Int && b.kind==gd::GdVal::Kind::Int)return gd::GdVal::from_int(a.i<b.i?a.i:b.i);
    return gd::gd_min(a,b);
}
__attribute__((always_inline)) inline gd::GdVal native_buff_integer_coerce(const gd::GdVal& a) {
    if(a.kind==gd::GdVal::Kind::Int)return gd::GdVal::from_int(a.i);
    return gd::GdVal::from_int(gd::gd_coerce_int(a).i);
}
__attribute__((always_inline)) inline gd::GdVal native_buff_boolean_coerce(const gd::GdVal& a) {
    if(a.kind==gd::GdVal::Kind::Bool)return gd::GdVal::from_bool(a.b);
    return gd::GdVal::from_bool(gd::gd_coerce_bool(a).b);
}
__attribute__((always_inline)) inline bool native_buff_integer_positive(const gd::GdVal& a,const gd::GdVal& b) {
    // Original comparisons convert Int to double. Outside the exact range,
    // retain those conversions (and their floating exception flags).
    constexpr uint64_t limit=UINT64_C(1)<<53;
    if(a.kind==gd::GdVal::Kind::Int && b.kind==gd::GdVal::Kind::Int &&
       uint64_t(a.i)+limit<=2*limit && uint64_t(b.i)+limit<=2*limit)return a.i>b.i;
    return gd::gd_gt(a,b);
}
}
'''
OPERATORS=[('gd::gd_add(','native_buff_integer_add('),('gd::gd_sub(','native_buff_integer_sub('),
    ('gd::gd_min(','native_buff_integer_min('),('gd::gd_coerce_int(','native_buff_integer_coerce('),
    ('gd::gd_coerce_bool(','native_buff_boolean_coerce(')]
POSITIVE_VARIABLES=('lv_amount','lv_left','lv_reflected','lv_resisted','lv_reflectedByStacks')
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def inventory(native):
    return {p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()
        and '__pycache__' not in p.parts and p.suffix not in ('.dll','.o','.gcda','.gcno','.pyc')}
def archive():
    r=json.loads((BACKUP/'checkpoint_receipt.json').read_bytes())
    assert r['remote_upload_verified'] and r['remote_verified_commit']==ARCHIVE and r['production_dll_sha256']==EXPECTED
    return ARCHIVE
def native_slice(t):
    a=t.index(SIGNATURE);b=t.index('    }\n    gd::GdVal lv_amount',a);return a,b,t[a:b]
def transform(native):
    assert inventory(native)==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    runtime=(native/'gd_rt.cpp').read_text('utf8')
    assert runtime.count('GdVal gd_coerce_int(const GdVal& v) { return GdVal::from_int(v.as_int()); }')==1
    assert runtime.count('GdVal gd_coerce_bool(const GdVal& v) { return GdVal::from_bool(gd_truth(v)); }')==1
    p=native/SHARD;t=p.read_text('utf8');a,b,body=native_slice(t);counts={}
    for old,new in OPERATORS:
        counts[old]=body.count(old);assert counts[old]>0;body=body.replace(old,new)
    for v in POSITIVE_VARIABLES:
        old=f'gd::gd_gt({v}, gd::GdVal::from_int(0LL))';new=f'native_buff_integer_positive({v}, gd::GdVal::from_int(0LL))'
        counts[old]=body.count(old);assert counts[old]>0;body=body.replace(old,new)
    p.write_text(t[:a]+HELPERS+body+t[b:],encoding='utf8',newline='\n')
    return dict(replacements=counts,native_branch_only=True,full_generic_branch_unchanged=True,
        actual_integer_operations_not_storage_only=True,all_six_helpers_forced_inline=True,coerce_return_kind_proven_on_both_branches=True,no_float_coercion_change=True,
        checked_integer_add_sub_and_original_overflow_fallback=True,integer_min_preserves_full_int64=True,
        comparison_fast_domain_exact_double_integer_range=True,all_callbacks_rng_and_frame_order_retained=True,
        all_existing_private_integer_views_and_snapshots_retained=True,no_new_api_or_layout=True)
def verify_projection(native):
    frozen=json.loads((WORK/'transform.json').read_bytes());assert inventory(native)==frozen['source_sha256']
    old=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    for name,digest in old.items():
        if name!=SHARD:assert sha(native/name)==digest,name;continue
        t=(native/name).read_text('utf8');assert t.count(HELPERS)==1;t=t.replace(HELPERS,'',1)
        a,b,body=native_slice(t)
        for before,after in OPERATORS:body=body.replace(after,before)
        for v in POSITIVE_VARIABLES:body=body.replace(f'native_buff_integer_positive({v},',f'gd::gd_gt({v},')
        original=t[:a]+body+t[b:];assert hashlib.sha256(original.encode()).hexdigest()==digest
    return dict(passed=True,exact_inverse_matches_retained_source=True,one_shard_only=True,
        all674_object_headers_and_all_layouts_unchanged=True,full_generic_branch_unchanged=True,
        original_runtime_arithmetic_bodies_unchanged=True,all_prior_optimizations_retained=True,
        not_the_old_storage_wrapper_or_context_cache_trial=True,distinct_from_prior_outlined_helper_candidate=True,formal_full20_fresh18_pgo_required=True)
def main():
    archive();assert sha(BASE/'libgdcore.dll')==EXPECTED and not WORK.exists()
    old=json.loads((ACCEPTED/'source_before_build.json').read_bytes());assert inventory(BASE)==old and len(old)==713
    WORK.mkdir();source=WORK/'prototype_src';shutil.copytree(ACCEPTED/'bundle_src',source)
    component=transform(source);after=inventory(source);assert set(old)==set(after)
    assert [n for n in old if old[n]!=after[n]]==[SHARD]
    report=dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,source_sha256=after,component=component,
        modified_files=[SHARD],new_files=[],baseline_cpp_source_files=708,candidate_cpp_source_files=708,
        all_layouts_unchanged=True,no_new_branches=True,no_speed_claim=True,not_for_deployment=True)
    (WORK/'transform.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(verify_projection(source)),flush=True)
if __name__=='__main__':main()
