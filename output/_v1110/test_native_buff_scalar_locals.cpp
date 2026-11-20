#include "gen/hdrs/Gd__gd_core__CoreBuff.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include <bit>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

using V=gd::GdVal;
struct Rng : Gd__gd_core__CoreRng {
    std::vector<double> draws;
    explicit Rng(gd::BattleCtx* c):Gd__gd_core__CoreRng(c){}
    bool call_method(gd::BattleCtx& c,gd::SymId method,const V* args,int argc,V& out) override {
        if(method!=SYM_GEN_flipPercent_1736)return Gd__gd_core__CoreRng::call_method(c,method,args,argc,out);
        assert(argc==1);draws.push_back(args[0].as_float());out=V::from_bool(false);return true;
    }
};

int main() {
    register_gen_syms();
    gd::BattleCtx battle;
    Gd__gd_core__CoreContext context(&battle);
    Gd__gd_core__CoreCharacter character(&battle);
    Gd__gd_core__CoreBuff buff(&battle);
    Rng rng(&battle);
    uint64_t digest=1469598103934665603ULL,cases=0,total_draws=0;
    auto word=[&](uint64_t value){digest^=value;digest*=1099511628211ULL;};
    auto value=[&](const V& item) {
        word(static_cast<unsigned>(item.kind));
        if(item.kind==V::Kind::Int)word(static_cast<uint64_t>(item.i));
        else if(item.kind==V::Kind::Bool)word(item.b);
        else if(item.kind==V::Kind::Float)word(std::bit_cast<uint64_t>(item.f));
        else assert(item.is_null());
    };
    auto run=[&](const V& amount,const V& reflection,double duration,bool is_buff,bool fractional_resistance) {
        context.init_fields(battle);character.init_fields(battle);buff.init_fields(battle);rng.init_fields(battle);rng.draws.clear();
        context.f_rng=V::from_obj(&rng);character.f_ctx=V::from_obj(&context);
        buff.f_ctx=V::from_obj(&context);buff.f_character=V::from_obj(&character);
        buff.f_MAX_STACKS=V::from_int(17);buff.f_isBuff=V::from_bool(is_buff);
        buff.f_resistChancePercent=V::from_float(0.0);buff.f_reflectChancePercent=V::from_float(35.0);
        if(fractional_resistance){buff.f_resistStacks=V::from_float(2.5);character.f_debuffResistStacks=V::from_float(1.5);}
        const V args[]={amount,V::from_float(duration),V::null(),V::null(),reflection};
        const auto result=buff.fn_gainTemporary(args,5);assert(result.is_null());
        word(++cases);value(buff.f_current);value(buff.f_permanentStacks);value(buff.f_resistStacks);
        value(character.f_debuffResistStacks);value(buff.f__timer_active);value(buff.f__timer_left);
        value(buff.f_nextTemporaryTimeout);word(buff.f_temporaryStacks.arr->len);
        word(rng.draws.size());for(auto chance:rng.draws)word(std::bit_cast<uint64_t>(chance));
        total_draws+=rng.draws.size();
    };
    const auto nan=std::numeric_limits<double>::quiet_NaN();
    std::vector<V> amounts={V::null(),V::from_bool(false),V::from_bool(true),V::from_int(-7),V::from_int(0),
        V::from_int(3),V::from_int(INT64_MIN),V::from_int(INT64_MAX),V::from_float(-0.0),V::from_float(2.75),
        V::from_float(-2.75),V::from_float(nan),V::from_cstr(battle.arena,"12"),V::from_cstr(battle.arena,"-7"),
        V::from_cstr(battle.arena,"nonnumeric")};
    std::vector<V> reflections={V::null(),V::from_bool(false),V::from_bool(true),V::from_int(0),V::from_int(3),
        V::from_float(0.0),V::from_float(nan),V::from_cstr(battle.arena,""),V::from_cstr(battle.arena,"yes")};
    for(const auto& amount:amounts)for(const auto& reflect:reflections)for(double duration:{-1.0,-0.0,0.25})
        run(amount,reflect,duration,true,false);
    for(const auto& reflect:reflections)for(double duration:{-1.0,0.25}) {
        run(V::from_int(3),reflect,duration,false,false);
        run(V::from_int(10),reflect,duration,false,true);
    }
    assert(cases==441);
    std::cout<<"{\"cases\":"<<cases<<",\"state_and_rng_digest\":"<<digest<<",\"rng_draws\":"<<total_draws
             <<",\"coercions_int64_limits_fractional_resistance_and_temporary_timers\":true}\n";
}
