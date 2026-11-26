#pragma once
#include "native_event_kernel.hpp"
#include "native_scalar_equal.hpp"
#include "gen/hdrs/Gd__gd_core__Weapon.hpp"
#include "gen/hdrs/Gd__gd_core_items__Weapon.hpp"

namespace gd {
template<class C,GdVal (C::*Method)(const GdVal*,int)>
GdVal native_resolved_invoke(GdObj*,const GdVal*,int);
namespace weapon_chain {
using Item=Gd__gd_core__CoreItem;
using Character=Gd__gd_core__CoreCharacter;
using Source=Gd__gd_core__CoreDamageSource;
using Result=Gd__gd_core__CoreDamageResult;

inline bool enabled(const BattleCtx& ctx) {
    return ctx.native_event_kernel && ctx.native_resolved_dispatch && ctx.native_timer_watch.closed_world;
}
inline bool source_exact(const GdVal& value) {
    return value.kind==GdVal::Kind::Obj && value.obj && &typeid(*value.obj)==&typeid(Source);
}
GdVal item_stamina(Item&,const GdVal&);
int64_t character_stamina(Character&,const GdVal&);
GdVal item_damage(Item&,const GdVal&);
GdVal character_damage(Character&,Source*,const GdVal&);
Result* take_damage(Character&,Source*,const GdVal&);
template<class W> __attribute__((always_inline)) inline GdVal weapon_attack(W&,const GdVal&);
template<class W> __attribute__((always_inline)) inline GdVal weapon_cooldown(W&);

// A cached binding is inspected without resolving, calling metadata, or
// changing counters. Failed probes leave all original fallback work intact.
template<class C,GdVal (C::*Method)(const GdVal*,int),SymId Symbol>
inline C* resolved_receiver(BattleCtx& ctx,const GdVal& value) {
    if(!enabled(ctx) || value.kind!=GdVal::Kind::Obj || !value.obj || value.obj->rt_ctx_!=&ctx)return nullptr;
    const auto* row=value.obj->native_call_row_;
    if(!row || (ctx.native_resolved_audit && !native_resolved_row_matches(value.obj,row)))return nullptr;
    constexpr int slot=native_resolved_slots[Symbol];static_assert(slot>=0);
    if(row->methods[slot]!=&native_resolved_invoke<C,Method>)return nullptr;
    if(ctx.native_resolved_collect){++ctx.native_resolved_counts[0];if constexpr(slot>=112)native_inline_hot_slot_hit(0);}
    return static_cast<C*>(value.obj);
}

inline GdVal call_character_stamina(BattleCtx& ctx,const GdVal& receiver,const GdVal& amount) {
    if(auto* p=resolved_receiver<Character,&Character::fn_useStamina,SYM_GEN_useStamina_116>(ctx,receiver))
        return GdVal::from_int(character_stamina(*p,amount));
    const GdVal args[]={amount};return native_inline_call(ctx,receiver,SYM_GEN_useStamina_116,args,1);
}
inline GdVal call_item_stamina_default(BattleCtx& ctx,Item& self) {
    const auto receiver=GdVal::from_obj(&self);
    if(auto* p=resolved_receiver<Item,&Item::fn_useStamina,SYM_GEN_useStamina_116>(ctx,receiver))
        return item_stamina(*p,GdVal::null());
    return native_inline_call(ctx,receiver,SYM_GEN_useStamina_116,nullptr,0);
}
inline GdVal call_item_damage(BattleCtx& ctx,const GdVal& receiver,const GdVal& trigger) {
    if(auto* p=resolved_receiver<Item,&Item::fn_dealDamage,SYM_GEN_dealDamage_220>(ctx,receiver))return item_damage(*p,trigger);
    const GdVal args[]={trigger};return native_inline_call(ctx,receiver,SYM_GEN_dealDamage_220,args,1);
}
inline GdVal call_character_damage(BattleCtx& ctx,const GdVal& receiver,const GdVal& source,const GdVal& trigger) {
    if(source_exact(source))
        if(auto* p=resolved_receiver<Character,&Character::fn_dealDamage,SYM_GEN_dealDamage_220>(ctx,receiver))
            return character_damage(*p,static_cast<Source*>(source.obj),trigger);
    const GdVal args[]={source,trigger};return native_inline_call(ctx,receiver,SYM_GEN_dealDamage_220,args,2);
}
inline GdVal call_take_damage(BattleCtx& ctx,const GdVal& receiver,Source* source,const GdVal& trigger) {
    // The original native_event_call deliberately calls the Character base
    // method. Audit mismatch and cross-context cases retain that exact helper.
    if(enabled(ctx) && receiver.kind==GdVal::Kind::Obj && receiver.obj && receiver.obj->rt_ctx_==&ctx &&
       (!ctx.native_event_audit || &typeid(*receiver.obj)==&typeid(Character)))
        return GdVal::from_obj(take_damage(*static_cast<Character*>(receiver.obj),source,trigger));
    const GdVal args[]={GdVal::from_obj(source),trigger};
    return native_event_call<Character,&Character::fn_takeDamage>(ctx,receiver,SYM_GEN_takeDamage_1148,args,2);
}
inline GdVal call_attack_default(BattleCtx& ctx,Item& self) {
    const auto receiver=GdVal::from_obj(&self);
    using A=Gd__gd_core_items__Weapon;using B=Gd__gd_core__Weapon;
    if(auto* p=resolved_receiver<A,&A::fn_attack,SYM_GEN_attack_941>(ctx,receiver))return weapon_attack(*p,GdVal::null());
    if(auto* p=resolved_receiver<B,&B::fn_attack,SYM_GEN_attack_941>(ctx,receiver))return weapon_attack(*p,GdVal::null());
    return native_inline_call(ctx,receiver,SYM_GEN_attack_941,nullptr,0);
}

template<class W> __attribute__((always_inline)) inline GdVal weapon_attack(W& self,const GdVal& trigger) {
    gd::BattleCtx& gd_ctx = *self.rt_ctx_;
    gd::GdVal lv_triggerEvent = trigger;
    gd::GdVal lv_res = ([&]() { const gd::GdVal event=lv_triggerEvent; return call_item_damage(gd_ctx,gd::GdVal::from_obj(&self),event); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(&self), SYM_GEN_activate_150, _ca, 1); })();
    return gd::GdVal::null();
}
template<class W> __attribute__((always_inline)) inline GdVal weapon_cooldown(W& self) {
    gd::BattleCtx& gd_ctx = *self.rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(call_item_stamina_default(gd_ctx,self), gd::GdVal::from_int(0LL))))) {
        (void)call_attack_default(gd_ctx,self);
    }
    return gd::GdVal::null();
}
} // namespace weapon_chain
} // namespace gd
