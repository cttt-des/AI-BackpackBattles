#pragma once
#include "native_inline_dispatch.hpp"
#include <limits>
namespace gd {
void native_event_identity_hit(unsigned);
inline bool native_try_event_emission_id(BattleCtx& ctx,const GdVal& emitter,
        const GdVal& signal,GdVal& out) {
    const auto miss=[&]{if(ctx.native_resolved_collect)native_event_identity_hit(3);return false;};
    if(!ctx.native_resolved_dispatch || signal.kind!=GdVal::Kind::Int ||
       emitter.kind!=GdVal::Kind::Obj || !emitter.obj)return miss();
    const auto* row=emitter.obj->native_call_row_;
    if(!row || (ctx.native_resolved_audit && !native_resolved_row_matches(emitter.obj,row)) || !row->metadata)return miss();
    // The complete generated class inventory has no get_instance_id override.
    // Unknown C++ receivers retain their original virtual dispatch and callback.
    static_assert(native_resolved_slots[SYM_get_instance_id]<0);
    const auto id=static_cast<int64_t>(emitter.obj->get_instance_id());
    if(ctx.native_resolved_collect) {++ctx.native_resolved_counts[0];native_event_identity_hit(2);}
    if(signal.i>=0 && signal.i<=INT32_MAX && id>=0) {
        const auto shifted=static_cast<uint64_t>(signal.i)<<32;
        if(static_cast<uint64_t>(id)<=uint64_t{INT64_MAX}-shifted) {
            out=GdVal::from_int(static_cast<int64_t>(static_cast<uint64_t>(id)+shifted));return true;
        }
    }
    // Preserve the actual original evaluators for negative/large signals and
    // arithmetic limits. The instance ID was already read exactly once.
    out=gd_add(ctx,GdVal::from_int(id),gd_shl(signal,GdVal::from_int(32)));
    return true;
}
}
