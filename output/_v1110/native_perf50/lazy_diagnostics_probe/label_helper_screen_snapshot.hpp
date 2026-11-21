#pragma once
#include "native_inline_dispatch.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItemData.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"

namespace gd {
template<class T>
inline const T* native_diagnostic_exact(BattleCtx& ctx,const GdVal& value,const GdClassMeta* metadata) {
    if(value.kind!=GdVal::Kind::Obj || !value.obj)return nullptr;
    const auto* row=value.obj->native_call_row_;
    if(!row || (ctx.native_resolved_audit && !native_resolved_row_matches(value.obj,row)))return nullptr;
    return row->metadata==metadata?static_cast<const T*>(value.obj):nullptr;
}

// The omitted arguments contain only proven pure field reads and Bool/Int/Str
// formatting. In particular, no Float conversion, object meta callback, RNG,
// instance ID or call to an overridable character() method may be skipped.
inline bool native_skip_label_diagnostic(BattleCtx& ctx,const Gd__gd_core__CoreItem& item) {
    if(!ctx.native_event_kernel || !ctx.native_resolved_dispatch)return false;
    const auto* context=native_diagnostic_exact<Gd__gd_core__CoreContext>(ctx,item.f_ctx,&META_Gd__gd_core__CoreContext);
    if(!context)return false;
    const auto* rng=native_diagnostic_exact<Gd__gd_core__CoreRng>(ctx,context->f_rng,&META_Gd__gd_core__CoreRng);
    if(!rng || rng->f_oracle_trace.kind!=GdVal::Kind::Bool)return false;
    if(rng->f_oracle_trace.b && (rng->f__stacktrace.kind!=GdVal::Kind::Bool || rng->f__stacktrace.b))return false;
    if(item.f_ownerType.kind!=GdVal::Kind::Int)return false;
    const auto* descriptor=native_diagnostic_exact<Gd__gd_core__CoreItemData>(ctx,item.f_descriptor,&META_Gd__gd_core__CoreItemData);
    if(!descriptor || descriptor->f_identifier.kind!=GdVal::Kind::Str)return false;
    const auto* row=item.native_call_row_;
    if(!row || (ctx.native_resolved_audit && !native_resolved_row_matches(&item,row)))return false;
    static_assert(native_type_targets[0]==&META_Gd__gd_core_items__Gems__Gem);
    static_assert(native_type_targets[1]==&META_Gd__gd_core__CoreItem);
    // Generation preflight checks every matching row's actual character slot:
    // only Gem overrides CoreItem::character(), and Gem is excluded here.
    if((row->type_mask & 3u)!=2u)return false;
    if(item.f_character_.kind==GdVal::Kind::Null)return true;
    const auto* character=native_diagnostic_exact<Gd__gd_core__CoreCharacter>(ctx,item.f_character_,&META_Gd__gd_core__CoreCharacter);
    return character && (character->f_playerId.kind==GdVal::Kind::Bool || character->f_playerId.kind==GdVal::Kind::Int);
}
}
