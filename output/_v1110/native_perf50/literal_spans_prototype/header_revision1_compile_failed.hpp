#pragma once
#include "gd_rt.hpp"
#include "native_inline_dispatch.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreBuff.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCombatLog.hpp"
#include "gen/hdrs/Gd__gd_core__CoreEventBus.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include "gen/hdrs/Gd__gd_core__CoreDamageSource.hpp"
#include "gen/hdrs/Gd__gd_core__CoreDamageResult.hpp"
#include "gen/hdrs/Gd__gd_core__CoreEvent.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng__INNER__BalancedRng.hpp"

#include <typeinfo>

gd::GdVal gd_native_event_hooks_call(gd::BattleCtx&,const gd::GdVal&,gd::SymId,const gd::GdVal*,int);

template<class T> bool native_event_type_ok(gd::BattleCtx& ctx,const gd::GdVal& value) {
    if(!ctx.native_event_audit)return true;
    if(&typeid(*value.obj)==&typeid(T))return true;
    ++ctx.native_event_counts[4];return false;
}
template<class T, gd::GdVal T::* Field>
gd::GdVal native_event_get(gd::BattleCtx& ctx,const gd::GdVal& value,gd::SymId property) {
    if(value.kind==gd::GdVal::Kind::Obj && value.obj && native_event_type_ok<T>(ctx,value))
        return static_cast<T*>(value.obj)->*Field;
    return gd::get_prop(ctx,value,property);
}
template<class T, gd::GdVal (T::*Method)(const gd::GdVal*,int)>
gd::GdVal native_event_call(gd::BattleCtx& ctx,const gd::GdVal& value,gd::SymId method,const gd::GdVal* args,int argc) {
    if(value.kind==gd::GdVal::Kind::Obj && value.obj && native_event_type_ok<T>(ctx,value))
        return (static_cast<T*>(value.obj)->*Method)(args,argc);
    return gd::call_method(ctx,value,method,args,argc);
}
template<class T>
void native_event_set(gd::BattleCtx& ctx,gd::GdVal& value,gd::SymId property,const gd::GdVal& input) {
    if(value.kind==gd::GdVal::Kind::Obj && value.obj && native_event_type_ok<T>(ctx,value)) {
        static_cast<T*>(value.obj)->T::set_prop(ctx,property,input);return;
    }
    gd::set_prop(ctx,value,property,input);
}
template<class T>
gd::GdVal native_event_new(gd::BattleCtx& ctx,const gd::GdVal* args,int argc) {
    auto* object=ctx.arena.make<T>(&ctx);
    object->T::init_fields(ctx);
    gd::GdVal result;
    object->T::call_method(ctx,gd::SYM__init,args,argc,result);
    return gd::GdVal::from_obj(object);
}
inline gd::GdVal native_event_funcv(gd::BattleCtx& ctx,const gd::GdVal& value,const gd::GdVal* args,int argc) {
    if(value.kind==gd::GdVal::Kind::FuncRef && value.fr && argc>=1) {
        gd::GdVal result;
        if(gd::native_try_flat_funcref(ctx,value,args[0],result))return result;
        return value.fr->call_funcv(ctx,args[0]);
    }
    return gd::call_method(ctx,value,gd::SYM_call_funcv,args,argc);
}

#include "gd_rt.hpp"
#include <charconv>
#include <cstring>
#include <limits>

namespace gd {
// The input values have already been read. This primitive performs no object
// lookup, callback, identifier assignment, random draw or floating operation.
inline bool native_event_identity_string(BattleArena& arena,const GdVal& identifier,
        const GdStr* delimiter,const GdVal& owner,GdVal& out) {
    if(identifier.kind!=GdVal::Kind::Str || owner.kind!=GdVal::Kind::Int)return false;
    char digits[32];
    const auto converted=std::to_chars(digits,digits+sizeof(digits),owner.i);
    if(converted.ec!=std::errc{})return false;
    const uint32_t id_length=identifier.str?identifier.str->len:0;
    const uint32_t delimiter_length=delimiter?delimiter->len:0;
    const uint32_t digit_length=static_cast<uint32_t>(converted.ptr-digits);
    const uint64_t total=uint64_t{id_length}+delimiter_length+digit_length;
    if(total>=std::numeric_limits<uint32_t>::max())return false;
    auto* value=arena.make<GdStr>();
    const auto length=static_cast<uint32_t>(total);
    char* data=arena.alloc_array<char>(size_t{length}+1);
    if(id_length)std::memcpy(data,identifier.str->data,id_length);
    if(delimiter_length)std::memcpy(data+id_length,delimiter->data,delimiter_length);
    std::memcpy(data+id_length+delimiter_length,digits,digit_length);data[length]='\0';
    value->data=data;value->len=length;value->hash=fnv1a_32(data,length);
    out=GdVal::from_str(value);return true;
}
}


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
    const auto descriptor=(emitter.obj->*descriptor_getter);
    const auto identifier_getter=native_event_identity_getter(ctx,descriptor,9);
    if(!identifier_getter)return miss();
    const auto owner=(emitter.obj->*owner_getter);
    const auto identifier=(descriptor.obj->*identifier_getter);
    if(!native_event_identity_string(ctx.arena,identifier,delimiter,owner,out))return miss();
    if(ctx.native_resolved_collect) {
        native_event_identity_hit(0);
        // Preserve the diagnostic totals for the same three proven field reads.
        native_inline_property_hit(0);native_inline_property_hit(0);native_inline_property_hit(0);
    }
    return true;
}
}

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

namespace gd {
void native_lazy_diagnostic_hit(unsigned,bool);
inline bool native_lazy_diagnostic_required(BattleCtx& ctx,unsigned site,bool skipped) {
    if(ctx.native_resolved_collect)native_lazy_diagnostic_hit(site,skipped);
    return !skipped;
}
}


namespace gd { bool native_literal_canonical_row(const NativeMethodRow*); }

// This view is used only for fresh, unaliased literals at frozen call sites.
// A callback that may retain or mutate the array receives a real arena array.
struct NativeLiteralEventArguments {
    gd::BattleArena& arena;
    const gd::GdVal* data;
    int count;
    gd::GdVal array;
    gd::GdVal materialize() {
        if(array.is_null()) {
            auto* a=gd::GdArr::create(arena,static_cast<uint32_t>(count));
            for(int i=0;i<count;++i)a->push(arena,data[i]);
            array=gd::GdVal::from_arr(a);
        }
        return array;
    }
    gd::GdVal invoke(gd::BattleCtx& ctx,const gd::GdVal& receiver) {
        if(array.is_null() && ctx.native_resolved_dispatch &&
           receiver.kind==gd::GdVal::Kind::FuncRef && receiver.fr &&
           receiver.fr->instance && receiver.fr->method!=gd::SYM_NONE &&
           (!receiver.fr->binds || !receiver.fr->binds->len) &&
           gd::native_literal_canonical_row(receiver.fr->instance->native_call_row_)) {
            // The canonical method wrappers copy every argument cell before any
            // callback. The header is never passed to a method or opaque code.
            gd::GdArr borrowed;
            borrowed.data=const_cast<gd::GdVal*>(data);
            borrowed.len=borrowed.cap=static_cast<uint32_t>(count);
            gd::GdVal out;
            if(gd::native_try_flat_funcref(ctx,receiver,gd::GdVal::from_arr(&borrowed),out))return out;
            // A failed audit may have observable effects. Do not audit twice.
            return receiver.fr->call_funcv(ctx,materialize());
        }
        const gd::GdVal args[]={materialize()};
        return native_event_funcv(ctx,receiver,args,1);
    }
};

gd::GdVal gd_native_emit_literal_body(Gd__gd_core__CoreEventBus*,const gd::GdVal*,NativeLiteralEventArguments&);

inline gd::GdVal gd_native_emit_literal_event(gd::BattleCtx& caller,const gd::GdVal& receiver,
        const gd::GdVal* prefix,const gd::GdVal* payload,int count) {
    NativeLiteralEventArguments arguments{caller.arena,payload,count,gd::GdVal::null()};
    if(receiver.kind==gd::GdVal::Kind::Obj && receiver.obj &&
       native_event_type_ok<Gd__gd_core__CoreEventBus>(caller,receiver)) {
        auto* bus=static_cast<Gd__gd_core__CoreEventBus*>(receiver.obj);
        if(bus->rt_ctx_->native_event_kernel)return gd_native_emit_literal_body(bus,prefix,arguments);
        const gd::GdVal args[]={prefix[0],prefix[1],prefix[2],arguments.materialize()};
        return bus->fn_emitEvent(args,4);
    }
    const gd::GdVal args[]={prefix[0],prefix[1],prefix[2],arguments.materialize()};
    return gd::call_method(caller,receiver,SYM_GEN_emitEvent_1593,args,4);
}
