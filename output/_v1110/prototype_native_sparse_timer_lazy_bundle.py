"""Keep unknown-callback protection while resolving known getter types only once."""
import hashlib
import json
from pathlib import Path
from prototype_native_sparse_timer_bundle import optimize as sparse

STAGE=Path(__file__).resolve().parent
PREVIOUS=STAGE/'native_perf50/sparse_timer_bundle'

def replace(text,old,new):
    assert text.count(old)==1,old[:100]
    return text.replace(old,new,1)

def optimize(native):
    report=sparse(native)
    expected=json.loads((PREVIOUS/'source_before_build.json').read_bytes())
    assert expected=={p.relative_to(native).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in native.rglob('*') if p.is_file()}
    path=native/'gd_rt.hpp';text=path.read_text('utf8')
    anchor='bool native_resolved_cached_generated(const BattleCtx&,const GdObj*);'
    text=replace(text,anchor,anchor+'\nbool native_resolved_resolve_generated(BattleCtx&,GdObj*);')
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'native_resolved_dispatch.hpp';text=path.read_text('utf8')
    anchor='bool native_resolved_generated_class(const GdClassMeta* type) {'
    helper='''bool native_resolved_resolve_generated(BattleCtx& context,GdObj* object) {
    if(!object)return false;
    if(!object->native_call_row_) {
        const auto* row=native_resolved_exact_row(object);
        object->native_call_row_=row;
        if(context.native_resolved_collect) {
            ++context.native_resolved_counts[2];
            if(row==&native_resolved_empty)++context.native_resolved_counts[3];
        }
    }
    return native_resolved_cached_generated(context,object);
}
'''
    text=replace(text,anchor,helper+anchor)
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'gd_rt.cpp';text=path.read_text('utf8')
    text=replace(text,'!native_resolved_cached_generated(context,object)) advance_native_scan_epoch();',
        '!native_resolved_resolve_generated(context,object)) advance_native_scan_epoch();')
    text=replace(text,'!native_resolved_cached_generated(*object->rt_ctx_,object))) advance_native_scan_epoch();',
        '''!(object->rt_ctx_->native_sparse_timer_scans
           ? native_resolved_resolve_generated(*object->rt_ctx_,object)
           : native_resolved_cached_generated(*object->rt_ctx_,object)))) advance_native_scan_epoch();''')
    path.write_text(text,encoding='utf8',newline='\n')
    report.update({'prior_candidate_dll_sha256':'4c14b0da2cdd92bb7f5563c6c5142978c46b99525c7bce84fa128348e5f311d4',
        'correction':'On actual getter/callback entry, resolve and cache the exact generated/unknown row once; invalidate only when genuinely unknown or audit-mismatched.',
        'negative_evidence':'Known unseeded getter invalidated twice without caching; fixed200462029 epoch increments. This is not an exact rebuild/time attribution.',
        'preserved':['unknown callbacks still invalidate on each entry','audit-before-row-read','disabled ordinary contexts retain prior behavior','lazy resolution diagnostic counts','eligibility pre-read does not resolve future unrecognized objects','copy reset, metadata purity, captured order/length and saturation protections'],
        'additional_layout_change_vs_prior_candidate':False,
        'requires_fresh_source_identical_pgo':True})
    return report
