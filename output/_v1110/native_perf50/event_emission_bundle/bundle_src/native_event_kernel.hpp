#pragma once
#include "gd_rt.hpp"
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
    if(value.kind==gd::GdVal::Kind::FuncRef && value.fr && argc>=1)
        return value.fr->call_funcv(ctx,args[0]);
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

#include "native_inline_dispatch.hpp"

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
