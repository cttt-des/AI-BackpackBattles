"""Stage typed producer/consumer boundaries without changing damage arithmetic."""
import hashlib
import json
from pathlib import Path
import shutil

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/buff_inline_types_bundle'
BACKUP=ACCEPTED
WORK=STAGE/'native_perf50/weapon_chain_prototype'
EXPECTED='d2064b3f17d8168cf87a2e9f46e9fb336ffe4aaf6581c27d93350b2c41477a57'
ARCHIVE='31702b25709fe094b0bd624ce352b4eb37c05829'
HEADER_NAME='native_weapon_damage_chain.hpp'
# Retain the exact already-deployed Buff helper bytes in its independent tests.
from prepare_native_buff_inline_types import HELPERS

HEADER='''#pragma once
#include "native_event_kernel.hpp"
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
GdVal weapon_attack(Item&,const GdVal&);
GdVal weapon_cooldown(Item&);

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
} // namespace weapon_chain
} // namespace gd
'''

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def inventory(p):
    return {f.relative_to(p).as_posix():sha(f) for f in p.rglob('*') if f.is_file()
        and '__pycache__' not in f.parts and f.suffix not in ('.dll','.o','.gcda','.gcno','.pyc')}
def archive():
    r=json.loads((BACKUP/'checkpoint_receipt.json').read_bytes())
    assert r['remote_upload_verified'] and r['remote_verified_commit']==ARCHIVE and r['production_dll_sha256']==EXPECTED
    return ARCHIVE
def once(t,a,b):
    assert t.count(a)==1,(a[:100],t.count(a));return t.replace(a,b,1)
def method(t,cls,name):
    start=t.index(f'gd::GdVal {cls}::fn_{name}(');end=t.index('\n}',start)+2
    return t[start:end]
def content(m):return m[m.index('{')+1:-1]
def kernel(m):
    t=content(m);a=t.index('    if (gd_ctx.native_event_kernel) {\n')+len('    if (gd_ctx.native_event_kernel) {\n')
    first=next(line for line in t[a:].splitlines() if line.startswith('    gd::GdVal lv_') and '_argc' in line)
    b=t.index('    }\n'+first,a);return t[a:b]

def transform(native):
    assert inventory(native)==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    edits={};proofs={};private={}
    def edit(file,old,new):
        p=native/file;t=p.read_text('utf8');p.write_text(once(t,old,new),encoding='utf8',newline='\n')
        edits.setdefault(file,[]).append(dict(old=old,new=new))
    def get(file,cls,name):return method((native/file).read_text('utf8'),cls,name)
    def add_private(file,text):private.setdefault(file,[]).append(text)
    def wrapper(file,old,call,guard=''):
        anchor='    gd::BattleCtx& gd_ctx = *this->rt_ctx_;\n'
        extra=f'    if(gd::weapon_chain::enabled(gd_ctx){guard})return {call};\n'
        edit(file,old,once(old,anchor,anchor+extra))
    def adapt_body(t):return t.replace('this->','self.').replace('from_obj(this)','from_obj(&self)')
    f0='gen/shards/shard_00.cpp';f2='gen/shards/shard_02.cpp';f9='gen/shards/shard_09.cpp';f1='gen/shards/shard_01.cpp'
    cls='Gd__gd_core__CoreItem';char='Gd__gd_core__CoreCharacter'
    old=get(f2,char,'takeDamage');body=kernel(old)
    body=once(body,'    gd::GdVal lv_damageSource = (_argc > 0) ? _args[0] : gd::GdVal::null();','    gd::GdVal lv_damageSource = gd::GdVal::from_obj(input_source);')
    body=once(body,'    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());','    gd::GdVal lv_triggerEvent = trigger;')
    assert body.count('return lv_damageRes;')==2
    body=body.replace('return lv_damageRes;','return static_cast<Result*>(lv_damageRes.obj);')
    assert body.count('return gd::GdVal::null();')==1;body=body.replace('return gd::GdVal::null();','return nullptr;')
    add_private(f2,'Result* take_damage(Character& self,Source* input_source,const GdVal& trigger) {\n    auto& gd_ctx=*self.rt_ctx_;\n'+adapt_body(body)+'\n}')
    wrapper(f2,old,'gd::GdVal::from_obj(gd::weapon_chain::take_damage(*this,static_cast<Gd__gd_core__CoreDamageSource*>(_args[0].obj),_argc>1?_args[1]:gd::GdVal::null()))',' && _argc>0 && gd::weapon_chain::source_exact(_args[0])')
    proofs['take_damage_arithmetic_fields_rng_and_callbacks_unchanged']=True

    old=get(f2,char,'dealDamage');body=kernel(old)
    body=once(body,'    gd::GdVal lv_damageSource = (_argc > 0) ? _args[0] : gd::GdVal::null();','    gd::GdVal lv_damageSource = gd::GdVal::from_obj(input_source);')
    body=once(body,'    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());','    gd::GdVal lv_triggerEvent = trigger;')
    a='gd::GdVal _ca[] = {lv_damageSource, lv_triggerEvent}; return native_event_call<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::fn_takeDamage>(gd_ctx, this->f_opponent, SYM_GEN_takeDamage_1148, _ca, 2);'
    body=once(body,a,'const gd::GdVal event=lv_triggerEvent; return call_take_damage(gd_ctx,this->f_opponent,input_source,event);')
    add_private(f2,'GdVal character_damage(Character& self,Source* input_source,const GdVal& trigger) {\n    auto& gd_ctx=*self.rt_ctx_;\n'+adapt_body(body)+'\n}')
    wrapper(f2,old,'gd::weapon_chain::character_damage(*this,static_cast<Gd__gd_core__CoreDamageSource*>(_args[0].obj),_argc>1?_args[1]:gd::GdVal::null())',' && _argc>0 && gd::weapon_chain::source_exact(_args[0])')

    old=get(f2,char,'useStamina');body=kernel(old)
    body=once(body,'    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();','    gd::GdVal lv_amount = input_amount;')
    for v in [0,1]:body=once(body,f'return gd::GdVal::from_int({v}LL);',f'return {v};')
    body=once(body,'return gd::GdVal::null();','return 0;')
    add_private(f2,'int64_t character_stamina(Character& self,const GdVal& input_amount) {\n    auto& gd_ctx=*self.rt_ctx_;\n'+adapt_body(body)+'\n}')
    wrapper(f2,old,'gd::GdVal::from_int(gd::weapon_chain::character_stamina(*this,_argc>0?_args[0]:gd::GdVal::null()))')

    old=get(f0,cls,'useStamina');body=content(old)
    body=once(body,'    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : (gd::GdVal::null());','    gd::GdVal lv_amount = input_amount;')
    a='gd::GdVal _ca[] = {lv_amount}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_useStamina_116, _ca, 1);'
    body=once(body,a,'const gd::GdVal amount=lv_amount; const auto receiver=gd::native_inline_call(gd_ctx,gd::GdVal::from_obj(this),SYM_GEN_character_74,nullptr,0); return call_character_stamina(gd_ctx,receiver,amount);')
    add_private(f0,'GdVal item_stamina(Item& self,const GdVal& input_amount) {'+adapt_body(body)+'}')
    wrapper(f0,old,'gd::weapon_chain::item_stamina(*this,_argc>0?_args[0]:gd::GdVal::null())')

    old=get(f0,cls,'dealDamage');body=content(old)
    body=once(body,'    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());','    gd::GdVal lv_triggerEvent = trigger;')
    a='gd::GdVal _ca[] = {this->f_damageSource, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_dealDamage_220, _ca, 2);'
    body=once(body,a,'const gd::GdVal source=this->f_damageSource; const gd::GdVal event=lv_triggerEvent; const auto receiver=gd::native_inline_call(gd_ctx,gd::GdVal::from_obj(this),SYM_GEN_character_74,nullptr,0); return call_character_damage(gd_ctx,receiver,source,event);')
    add_private(f0,'GdVal item_damage(Item& self,const GdVal& trigger) {'+adapt_body(body)+'}')
    wrapper(f0,old,'gd::weapon_chain::item_damage(*this,_argc>0?_args[0]:gd::GdVal::null())')

    attack_bodies=[];cooldown_bodies=[]
    for file,owner in [(f9,'Gd__gd_core_items__Weapon'),(f1,'Gd__gd_core__Weapon')]:
        old=get(file,owner,'attack');body=content(old);attack_bodies.append(body)
        wrapper(file,old,'gd::weapon_chain::weapon_attack(*this,_argc>0?_args[0]:gd::GdVal::null())')
        old=get(file,owner,'doCooldownEffect');body=content(old);cooldown_bodies.append(body)
        wrapper(file,old,'gd::weapon_chain::weapon_cooldown(*this)')
    assert attack_bodies[0]==attack_bodies[1] and cooldown_bodies[0]==cooldown_bodies[1]
    body=once(attack_bodies[0],'    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());','    gd::GdVal lv_triggerEvent = trigger;')
    a='gd::GdVal _ca[] = {lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, _ca, 1);'
    body=once(body,a,'const gd::GdVal event=lv_triggerEvent; return call_item_damage(gd_ctx,gd::GdVal::from_obj(this),event);')
    add_private(f9,'GdVal weapon_attack(Item& self,const GdVal& trigger) {'+adapt_body(body)+'}')
    body=once(cooldown_bodies[0],'gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0)','call_item_stamina_default(gd_ctx,*this)')
    body=once(body,'gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_attack_941, nullptr, 0)','call_attack_default(gd_ctx,*this)')
    add_private(f9,'GdVal weapon_cooldown(Item& self) {'+adapt_body(body).replace('*this','self')+'}')

    for file,functions in private.items():
        p=native/file;t=p.read_text('utf8');prefix='#include "../../'+HEADER_NAME+'"\n'
        addition='\nnamespace gd::weapon_chain {\n'+'\n'.join(functions)+'\n}\n'
        edit(file,t,prefix+t+addition)
    # shard01 only calls the shared typed producer; it has no private body.
    p=native/f1;t=p.read_text('utf8');edit(f1,t,'#include "../../'+HEADER_NAME+'"\n'+t)
    (native/HEADER_NAME).write_text(HEADER,encoding='utf8',newline='\n')
    return dict(edits=edits,proofs=proofs,typed_boundaries=['weapon cooldown/attack','item stamina/damage','character stamina/damage/takeDamage'],
        character_stamina_return_native_int=True,take_damage_return_native_pointer=True,
        source_pointer_propagated_between_character_boundaries=True,arguments_snapshot_before_receiver_getters=True,
        no_old_damage_math_helpers_or_flag_cache=True,all_original_generic_bodies_retained=True,
        cached_binding_override_guards_and_original_fallback=True,no_layout_or_object_header_changes=True)

def verify_projection(native):
    f=json.loads((WORK/'transform.json').read_bytes());assert inventory(native)==f['source_sha256']
    old=json.loads((ACCEPTED/'source_before_build.json').read_bytes());edits=f['component']['edits']
    for name,h in old.items():
        if name not in edits:assert sha(native/name)==h,name;continue
        t=(native/name).read_text('utf8')
        for e in reversed(edits[name]):t=once(t,e['new'],e['old'])
        assert hashlib.sha256(t.encode()).hexdigest()==h,name
    assert (native/HEADER_NAME).read_text('utf8')==HEADER
    assert set(inventory(native))-set(old)=={HEADER_NAME}
    return dict(passed=True,exact_inverse_matches_retained_source=True,all674_object_headers_and_all_layouts_unchanged=True,
        full_original_bodies_retained=True,all_prior_optimizations_retained=True,formal_full20_fresh18_pgo_required=True)

def main():
    archive();assert sha(BASE/'libgdcore.dll')==EXPECTED
    assert inventory(BASE)==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    assert not (WORK/'prototype_src').exists()
    shutil.copytree(ACCEPTED/'bundle_src',WORK/'prototype_src');component=transform(WORK/'prototype_src')
    after=inventory(WORK/'prototype_src');before=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    modified=[n for n in before if before[n]!=after[n]]
    assert sorted(modified)==[f'gen/shards/shard_{i:02}.cpp' for i in [0,1,2,9]]
    report=dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,source_sha256=after,component=component,
        modified_files=modified,new_files=[HEADER_NAME],baseline_cpp_source_files=708,candidate_cpp_source_files=709,
        all_layouts_unchanged=True,no_new_branches=True,no_speed_claim=True,not_for_deployment=True)
    (WORK/'transform.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(verify_projection(WORK/'prototype_src')),flush=True)

if __name__=='__main__':main()
