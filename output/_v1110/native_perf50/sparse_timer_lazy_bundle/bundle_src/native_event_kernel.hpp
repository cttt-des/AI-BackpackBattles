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
