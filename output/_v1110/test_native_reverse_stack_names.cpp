#include "gen/hdrs/Gd__gd_core__CoreConst.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include "gen/hdrs/Gd__gd_core__CoreBuff.hpp"
#include <cassert>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using V=gd::GdVal;
#ifdef GD_REVERSE_NAMES_CANDIDATE
extern V gd_native_stack_type_name(gd::BattleCtx&,const V&);
#endif

std::string text(const V& value){
    assert(value.kind==V::Kind::Str && value.str);
    return std::string(value.str->data,value.str->len);
}

V original(gd::BattleCtx& battle,const V& value){
    V name=V::from_cstr(battle.arena,"");
    V owner=V::from_cls(&META_Gd__gd_core__CoreConst);
    auto* keys=gd::gd_iter_seq(battle.arena,gd::get_prop(battle,owner,SYM_GEN_EventType_1395)).arr;
    for(uint32_t i=0;i<keys->len;++i){
        auto key=keys->data[i];
        if(gd::gd_eq(gd::get_index(battle,gd::get_prop(battle,owner,SYM_GEN_EventType_1395),key),value)){
            name=key;break;
        }
    }
    return name;
}

int main(){
    register_gen_syms();
    uint64_t digest=1469598103934665603ull;unsigned cases=0,constructors=0,recognized=0;
    auto mix=[&](uint64_t value){digest^=value;digest*=1099511628211ull;};
    auto mix_text=[&](const std::string& value){for(unsigned char c:value)mix(c);mix(0xff);};
    {
        gd::BattleCtx battle;
        std::vector<V> values;
        for(int64_t i=-130;i<=250;++i)values.push_back(V::from_int(i));
        values.push_back(V::from_int(INT64_MIN));values.push_back(V::from_int(INT64_MAX));
        values.push_back(V::null());values.push_back(V::from_bool(false));values.push_back(V::from_bool(true));
        for(double x:{-0.0,0.0,1.0,100.0,100.5,110.0,1e300,std::numeric_limits<double>::infinity(),std::numeric_limits<double>::quiet_NaN()})values.push_back(V::from_float(x));
        for(const char* s:{"","100","Heat","Block","Win","Poison"})values.push_back(V::from_cstr(battle.arena,s));
        for(const auto& value:values){
            auto expected=original(battle,value);
#ifdef GD_REVERSE_NAMES_CANDIDATE
            auto actual=gd_native_stack_type_name(battle,value);
            if(!actual.is_null()){
                assert(text(actual)==text(expected));++recognized;
            }else actual=original(battle,value);
            assert(text(actual)==text(expected));
#endif
            mix_text(text(expected));++cases;
        }
    }
    for(uint64_t seed:{uint64_t{0},uint64_t{42},UINT64_MAX})for(int64_t id:{int64_t{0},int64_t{1},int64_t{-1}}){
        gd::BattleCtx battle;battle.bind_battle(seed);
        gd::GdRng raw(seed);
        Gd__gd_core__CoreRng rng(&battle);rng.init_fields(battle);rng.f_rng=V::from_rng(&raw);
        Gd__gd_core__CoreContext context(&battle);context.init_fields(battle);context.f_rng=V::from_obj(&rng);
        Gd__gd_core__CoreCharacter character(&battle);character.init_fields(battle);
        const V args[]={V::from_obj(&context),V::from_int(id)};
        character.fn__init(args,2);
        auto* buffs=character.f_buffs.dict;mix(buffs->len);
        for(uint32_t i=0;i<buffs->len;++i){
            const auto& pair=buffs->entries[i];auto* buff=static_cast<Gd__gd_core__CoreBuff*>(pair.val.obj);
            mix(pair.key.as_int());mix(buff->f_type.as_int());mix_text(text(buff->f_signalName));
            mix(buff->gid_);mix(buff->gid_epoch_);
        }
        mix(raw.get_state());mix(battle.math_rng.get_state());mix(battle.next_gid);++constructors;
    }
#ifdef GD_REVERSE_NAMES_CANDIDATE
    assert(recognized==40);
#endif
    std::cout<<"{\"lookup_cases\":"<<cases<<",\"constructors\":"<<constructors
             <<",\"names_object_ids_and_rng_digest\":"<<digest<<"}\n";
}
