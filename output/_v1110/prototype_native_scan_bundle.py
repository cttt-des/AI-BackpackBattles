"""Combine short-circuit inactive Buff chunks with retained dispatch components."""
import hashlib
import json
from pathlib import Path
STAGE=Path(__file__).resolve().parent
PREVIOUS=STAGE/'native_perf50/variant_inline_bundle'

def optimize(native):
    expected=json.loads((PREVIOUS/'source_before_build.json').read_bytes())
    actual={p.relative_to(native).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in native.rglob('*') if p.is_file()}
    assert actual==expected,'Start from the complete retained candidate, never mixed headers or objects'
    path=native/'gen/shards/shard_02.cpp';text=path.read_text('utf8')
    old='''    for (uint32_t i = 0, count = buffs->len; i < count; ++i) {
        auto* buff = static_cast<Gd__gd_core__CoreBuff*>(entries[i].val.obj);
        const auto& active = buff->f__timer_active;
        if (active.kind == gd::GdVal::Kind::Bool ? active.b : gd::gd_truth(active)) buff->fn__tick(&delta, 1);
    }'''
    tick='''        auto* buff = static_cast<Gd__gd_core__CoreBuff*>(entries[i].val.obj);
        const auto& active = buff->f__timer_active;
        if (active.kind == gd::GdVal::Kind::Bool ? active.b : gd::gd_truth(active)) buff->fn__tick(&delta, 1);'''
    checks='\n            && '.join(f'inactive(i+{j})' for j in range(8))
    new='''    uint32_t i=0;
    const uint32_t count=buffs->len;
    const auto inactive=[entries](uint32_t index) {
        const auto* buff=static_cast<Gd__gd_core__CoreBuff*>(entries[index].val.obj);
        const auto& active=buff->f__timer_active;
        return active.kind==gd::GdVal::Kind::Bool && !active.b;
    };
    while(count-i>=8) {
        // Short circuit before any callback: never pre-read past an active/unknown flag.
        if ('''+checks+''') {
            i+=8;
            continue;
        }
        const uint32_t end=i+8;
        for(;i<end;++i) {
'''+tick+'''
        }
    }
    for(;i<count;++i) {
'''+tick+'''
    }'''
    assert text.count(old)==1
    path.write_text(text.replace(old,new,1),encoding='utf8',newline='\n')
    from optimize_native_cooldown_flags import optimize as flags
    flags(native)
    return {'baseline_dll_sha256':'1be75dced83e9e90fdbe61dd86f91bc27e19bb44acf9449d295849e928d9cec5',
        'retained_candidate_dll_sha256':'8bdcd96dcdf1d35819db619d635c726b72166dcee706558cca91e1ba1b3709af',
        'components':['retained pure container and static ClassRef lanes','eight-entry inactive Buff short-circuit chunks','five Bool cooldown checks with original non-Bool fallback'],
        'preserved':['original entries pointer and count capture','ordered live checks after first active/unknown flag','same-frame callback changes to future entries','original timer bodies and RNG','object/context layouts and floating options'],
        'scan_counts_source':'native_perf50/scan_activity_probe/scan_counts.json',
        'no_persistent_eligibility_cache':True,'full_rebuild_required':True}
