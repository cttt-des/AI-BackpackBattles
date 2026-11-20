#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreBuff.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreHooks.hpp"
#include "gen/hdrs/Gd__gd_core_items__Gems__Gem.hpp"
#include <bit>
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;
#ifdef GD_SHARED_SPEED_CANDIDATE
extern V gd_native_cached_physics_tick(Item*,const V*,int,gd::NativeCooldownSpeedCache*);
#endif

struct TriggerItem:Item {
    std::function<void()> callback;
    using Item::Item;
    bool call_method(gd::BattleCtx& battle,gd::SymId method,const V* args,int argc,V& out) override {
        if(method!=SYM_GEN_trigger_143)return Item::call_method(battle,method,args,argc,out);
        if(callback)callback();out=V::null();return true;
    }
};
struct Hooks:Gd__gd_core__CoreHooks {
    std::function<void()> callback;
    using Gd__gd_core__CoreHooks::Gd__gd_core__CoreHooks;
    bool call_method(gd::BattleCtx& battle,gd::SymId method,const V* args,int argc,V& out) override {
        if(method!=SYM_GEN_showCooldown_794)return Gd__gd_core__CoreHooks::call_method(battle,method,args,argc,out);
        if(callback)callback();out=V::null();return true;
    }
};
struct Gem:Gd__gd_core_items__Gems__Gem {
    std::function<void()> callback;
    std::function<void()> fallback;
    using Gd__gd_core_items__Gems__Gem::Gd__gd_core_items__Gems__Gem;
    bool call_method(gd::BattleCtx& battle,gd::SymId method,const V* args,int argc,V& out) override {
        if(method==SYM_GEN_hasCharacter_73 && fallback){fallback();out=V::from_bool(false);return true;}
        if(method!=SYM_GEN_getGemMode_972)return Gd__gd_core_items__Gems__Gem::call_method(battle,method,args,argc,out);
        if(callback)callback();out=V::from_int(3);return true;
    }
};

std::vector<uint64_t> run(bool cached,int scenario,double scale,bool reversed) {
    gd::BattleCtx battle;
    auto& arena=battle.arena;
    Gd__gd_core__CoreContext context(&battle);context.init_fields(battle);
    Gd__gd_core__CoreCharacter character(&battle),other(&battle);
    character.init_fields(battle);other.init_fields(battle);
    Gd__gd_core__CoreBuff haste(&battle),cold(&battle),dummy(&battle),replacement(&battle);
    for(auto* buff:{&haste,&cold,&dummy,&replacement})buff->init_fields(battle);
    haste.f_current=V::from_float(17.75);cold.f_current=V::from_int(4);replacement.f_current=V::from_int(52);
    auto* dict=gd::GdDict::create(arena);
    for(int j=0;j<14;++j){int key=reversed?113-j:100+j;dict->set(arena,V::from_int(key),V::from_obj(key==107?&haste:key==110?&cold:&dummy));}
    character.f_buffs=V::from_dict(dict);other.f_buffs=V::from_dict(dict);
    context.f_player=V::from_obj(&character);
    Hooks hooks(&battle);hooks.init_fields(battle);context.f_hooks=V::from_obj(&hooks);
    TriggerItem first(&battle),second(&battle),third(&battle);
    Gem gem(&battle);
    for(Item* item:{static_cast<Item*>(&first),static_cast<Item*>(&second),static_cast<Item*>(&third),static_cast<Item*>(&gem)}) {
        item->Item::init_fields(battle);
        item->f_ctx=V::from_obj(&context);item->f_character_=V::from_obj(&character);
        item->f_placed=V::from_bool(true);item->f_speedScale=V::from_float(scale);
        item->f__cooldown_active=V::from_bool(true);item->f_triggerTime=V::from_float(10);
        item->f_iterationCooldown=V::from_float(12);
    }
    std::vector<uint64_t> result;
    auto record=[&](uint64_t v){result.push_back(v);};
#ifdef GD_SHARED_SPEED_CANDIDATE
    gd::NativeCooldownSpeedCache cache;
#endif
    auto tick=[&](Item& item,double delta=.25) {
        V arg=V::from_float(delta);
#ifdef GD_SHARED_SPEED_CANDIDATE
        if(cached)gd_native_cached_physics_tick(&item,&arg,1,&cache);
        else item.fn_physicsTick(&arg,1);
#else
        item.fn_physicsTick(&arg,1);
#endif
        record(std::bit_cast<uint64_t>(item.f_triggerTime.as_float()));
    };
    tick(first);tick(second); // Populate and reuse before a boundary.
    if(scenario==1){first.f_triggerTime=V::from_float(0);first.callback=[&]{haste.f_current=V::from_int(73);record(1);};tick(first);}
    if(scenario==2){first.f_triggerTime=V::from_float(0);first.callback=[&]{dict->set(arena,V::from_int(107),V::from_obj(&replacement));record(2);};tick(first);}
    if(scenario==3){context.f_show_cooldown_progress=V::from_bool(true);hooks.callback=[&]{cold.f_current=V::from_int(90);record(3);};tick(first);context.f_show_cooldown_progress=V::from_bool(false);}
    if(scenario==4){gem.callback=[&]{haste.f_current=V::from_int(42);record(4);};tick(gem);}
    if(scenario==5){third.f_character_=V::from_obj(&other);}
    if(scenario==6){third.f_placed=V::from_bool(false);}
    if(scenario==7){third.f_statDisplayOverrides=V::from_arr(gd::GdArr::from_init(arena,{V::null(),V::null(),V::null(),V::from_float(2)}));}
    if(scenario==8){third.f_statDisplayOverrides=V::from_arr(gd::GdArr::from_init(arena,{V::null(),V::null(),V::null(),V::from_bool(true)}));}
    if(scenario==9){first.f_triggerTime=V::from_float(0);first.callback=[&]{cold.f_current=V::from_int(55);third.f_speedScale=V::from_float(-0.0);tick(third);cold.f_current=V::from_int(2);record(9);};tick(first);}
    if(scenario==10){third.f__cooldown_blocked_epoch=context.f_timer_pass_epoch;}
    if(scenario==11){character.f_stunnedDuration=V::from_float(.5);}
    if(scenario==12){third.f_speedScale=V::from_float(-0.0);}
    if(scenario==13){third.f_speedScale=V::from_float(.12345);}
    if(scenario==14){third.f__cooldown_active=V::from_bool(false);}
    if(scenario==15){first.f_triggerTime=V::from_float(0);first.callback=[&]{character.f_buffs=V::from_dict(gd::GdDict::create(arena));record(15);};tick(first);}
    if(scenario==16){context.f_player=V::null();gem.fallback=[&]{haste.f_current=V::from_int(61);tick(third);haste.f_current=V::from_int(3);record(16);};tick(gem);context.f_player=V::from_obj(&character);}
    if(scenario==17){context.f_show_cooldown_progress=V::from_bool(true);hooks.callback=[&]{context.f_show_cooldown_progress=V::from_bool(false);haste.f_current=V::from_int(64);tick(third);haste.f_current=V::from_int(5);record(17);};tick(first);}
    if(scenario==18){gem.callback=[&]{haste.f_current=V::from_int(62);tick(third);haste.f_current=V::from_int(7);record(18);};tick(gem);}
    tick(third);tick(second);tick(third,0.0);tick(second,-0.0);
    return result;
}

int main(){
    register_gen_syms();
    const double values[]={0.0,-0.0,.1,-.1,.5,-.5,9.0,-9.0,100,-100,1e-300,-1e-300,1e300,-1e300,
        std::numeric_limits<double>::infinity(),-std::numeric_limits<double>::infinity(),
        std::bit_cast<double>(uint64_t{0x7ff8000000000042}),std::bit_cast<double>(uint64_t{0xfff8000000000042})};
    uint64_t digest=1469598103934665603ull;unsigned cases=0;
    for(bool reversed:{false,true})for(int scenario=0;scenario<19;++scenario)for(double scale:values){
        auto baseline=run(false,scenario,scale,reversed),candidate=run(true,scenario,scale,reversed);
        assert(baseline==candidate);
        for(auto value:baseline){digest^=value;digest*=1099511628211ull;}
        ++cases;
    }
    std::cout<<"{\"cases\":"<<cases<<",\"state_and_callback_digest\":"<<digest<<",\"all_bitwise_equal\":true}\n";
}
