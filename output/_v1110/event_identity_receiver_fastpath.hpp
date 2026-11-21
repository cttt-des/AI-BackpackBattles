#pragma once
#include "native_inline_dispatch.hpp"
#include "event_identity_fastpath.hpp"

namespace gd {
void native_event_identity_hit(unsigned);
inline NativePropertyFn native_event_identity_getter(BattleCtx& ctx,const GdVal& value,unsigned slot) {
    if(value.kind!=GdVal::Kind::Obj || !value.obj)return nullptr;
    const auto* row=value.obj->native_call_row_;
    // Validate an audited row before reading any data from it. Do not resolve
    // unknown receivers here; the original expression owns every fallback.
    if(!row || (ctx.native_resolved_audit && !native_resolved_row_matches(value.obj,row)))return nullptr;
    return row->properties?row->properties->getters[slot]:nullptr;
}
inline bool native_try_event_identity(BattleCtx& ctx,const GdVal& emitter,
        const GdStr* delimiter,GdVal& out) {
    const auto miss=[&]{if(ctx.native_resolved_collect)native_event_identity_hit(1);return false;};
    if(!ctx.native_resolved_dispatch)return miss();
    static_assert(native_property_slots[SYM_GEN_descriptor_2]==8);
    static_assert(native_property_slots[SYM_GEN_identifier_1673]==9);
    static_assert(native_property_slots[SYM_GEN_ownerType_49]==18);
    const auto descriptor_getter=native_event_identity_getter(ctx,emitter,8);
    const auto owner_getter=native_event_identity_getter(ctx,emitter,18);
    if(!descriptor_getter || !owner_getter)return miss();
    const auto descriptor=descriptor_getter(emitter.obj);
    const auto identifier_getter=native_event_identity_getter(ctx,descriptor,9);
    if(!identifier_getter)return miss();
    const auto owner=owner_getter(emitter.obj);
    const auto identifier=identifier_getter(descriptor.obj);
    if(!native_event_identity_string(ctx.arena,identifier,delimiter,owner,out))return miss();
    if(ctx.native_resolved_collect) {
        native_event_identity_hit(0);
        // Preserve the diagnostic totals for the same three proven field reads.
        native_inline_property_hit(0);native_inline_property_hit(0);native_inline_property_hit(0);
    }
    return true;
}
}
