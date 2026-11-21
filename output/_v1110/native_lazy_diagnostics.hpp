#pragma once
#include "native_inline_dispatch.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItemData.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include "gen/hdrs/Gd__gd_core__CoreBuff.hpp"
#include "gen/hdrs/Gd__gd_core__CoreBuff__INNER__TemporaryStacks.hpp"
#include <bit>
#include <initializer_list>

namespace gd {
template<class T>
inline const T* native_diagnostic_exact(BattleCtx& ctx,const GdVal& value,const GdClassMeta* metadata) {
    if(value.kind!=GdVal::Kind::Obj || !value.obj)return nullptr;
    const auto* row=value.obj->native_call_row_;
    if(!row || (ctx.native_resolved_audit && !native_resolved_row_matches(value.obj,row)))return nullptr;
    return row->metadata==metadata?static_cast<const T*>(value.obj):nullptr;
}

inline bool native_diagnostic_context_off(BattleCtx& ctx,const GdVal& value) {
    if(!ctx.native_event_kernel || !ctx.native_resolved_dispatch)return false;
    const auto* context=native_diagnostic_exact<Gd__gd_core__CoreContext>(ctx,value,&META_Gd__gd_core__CoreContext);
    if(!context)return false;
    const auto* rng=native_diagnostic_exact<Gd__gd_core__CoreRng>(ctx,context->f_rng,&META_Gd__gd_core__CoreRng);
    if(!rng || rng->f_oracle_trace.kind!=GdVal::Kind::Bool)return false;
    return !rng->f_oracle_trace.b || (rng->f__stacktrace.kind==GdVal::Kind::Bool && !rng->f__stacktrace.b);
}

inline bool native_diagnostic_format_pure(const GdVal& value) {
    switch(value.kind) {
        case GdVal::Kind::Null:case GdVal::Kind::Bool:case GdVal::Kind::Int:case GdVal::Kind::Str:return true;
        case GdVal::Kind::Float: {
            // Match only the original formatter's exact integral Float branch.
            // Fractional, large and nonfinite inputs retain all original FP
            // operations and printf behavior. Bit inspection raises no flags.
            const uint64_t bits=std::bit_cast<uint64_t>(value.f)&UINT64_C(0x7fffffffffffffff);
            if(bits==0)return true;
            if(bits>=std::bit_cast<uint64_t>(1e16))return false;
            const auto exponent=static_cast<unsigned>(bits>>52);
            if(exponent<1023)return false;
            if(exponent>=1075)return true;
            return (bits&((UINT64_C(1)<<(1075-exponent))-1))==0;
        }
        default:return false;
    }
}

inline bool native_skip_buff_diagnostic(BattleCtx& ctx,const Gd__gd_core__CoreBuff& buff,std::initializer_list<GdVal> values) {
    if(!native_diagnostic_context_off(ctx,buff.f_ctx))return false;
    for(const auto& value:values)if(!native_diagnostic_format_pure(value))return false;
    return true;
}
inline bool native_skip_buff_farthest_diagnostic(BattleCtx& ctx,const Gd__gd_core__CoreBuff& buff,const GdVal& index,const GdVal& farthest) {
    if(!native_skip_buff_diagnostic(ctx,buff,{index}))return false;
    const auto* stacks=native_diagnostic_exact<Gd__gd_core__CoreBuff__INNER__TemporaryStacks>(ctx,farthest,&META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks);
    return stacks && native_diagnostic_format_pure(stacks->f_amount);
}
inline bool native_skip_buff_timeout_diagnostic(BattleCtx& ctx,const Gd__gd_core__CoreBuff& buff,const GdVal& delay,const GdVal& earliest) {
    if(!native_skip_buff_diagnostic(ctx,buff,{delay,earliest}))return false;
    const auto* context=native_diagnostic_exact<Gd__gd_core__CoreContext>(ctx,buff.f_ctx,&META_Gd__gd_core__CoreContext);
    return context && native_diagnostic_format_pure(context->f_time);
}

// The omitted arguments contain only proven pure field reads and Bool/Int/Str
// formatting. In particular, no Float conversion, object meta callback, RNG,
// instance ID or call to an overridable character() method may be skipped.
inline bool native_skip_label_diagnostic(BattleCtx& ctx,const Gd__gd_core__CoreItem& item) {
    if(!ctx.native_event_kernel || !ctx.native_resolved_dispatch)return false;
    if(!native_diagnostic_context_off(ctx,item.f_ctx))return false;
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
