#include "gen/hdrs/Gd__gd_core__CoreBuff.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include <bit>
#include <cfenv>
#include <xmmintrin.h>
#include "gen/hdrs/Gd__gd_core__CoreBuff__INNER__TemporaryStacks.hpp"
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
    fenv_t saved;std::fegetenv(&saved);unsigned saved_csr=_mm_getcsr(),mode=0;bool native=false;
    std::vector<uint64_t> hashes;
    uint64_t digest=1469598103934665603ULL,cases=0,total_draws=0;
    auto word=[&](uint64_t value){digest^=value;digest*=1099511628211ULL;};
    auto value=[&](const V& item) {
        word(static_cast<unsigned>(item.kind));
        if(item.kind==V::Kind::Int)word(static_cast<uint64_t>(item.i));
        else if(item.kind==V::Kind::Bool)word(item.b);
        else if(item.kind==V::Kind::Float)word(std::bit_cast<uint64_t>(item.f));
        else if(item.kind==V::Kind::Arr){word(item.arr?item.arr->len:0);if(item.arr)for(unsigned i=0;i<item.arr->len;++i){
            const auto& v=item.arr->data[i];assert(v.kind==V::Kind::Obj && v.obj);auto* stack=static_cast<Gd__gd_core__CoreBuff__INNER__TemporaryStacks*>(v.obj);
            word(unsigned(stack->f_amount.kind));word(uint64_t(stack->f_amount.as_int()));word(unsigned(stack->f_timeout.kind));word(std::bit_cast<uint64_t>(stack->f_timeout.as_float()));
        }}
        else assert(item.is_null());
    };
    auto run=[&](const V& amount,const V& reflection,double duration,bool is_buff,bool fractional_resistance) {
        battle.bind_battle(149);battle.native_event_kernel=native;battle.native_event_audit=true;
        context.init_fields(battle);character.init_fields(battle);buff.init_fields(battle);rng.init_fields(battle);rng.draws.clear();
        context.f_rng=V::from_obj(&rng);character.f_ctx=V::from_obj(&context);
        buff.f_ctx=V::from_obj(&context);buff.f_character=V::from_obj(&character);
        buff.f_MAX_STACKS=V::from_int(17);buff.f_isBuff=V::from_bool(is_buff);
        buff.f_resistChancePercent=V::from_float(0.0);buff.f_reflectChancePercent=V::from_float(35.0);
        if(fractional_resistance){buff.f_resistStacks=V::from_float(2.5);character.f_debuffResistStacks=V::from_float(1.5);}
        const V args[]={amount,V::from_float(duration),V::null(),V::null(),reflection};
        std::feclearexcept(FE_ALL_EXCEPT);_mm_setcsr(mode);
        const auto result=buff.fn_gainTemporary(args,5);int flags=std::fetestexcept(FE_ALL_EXCEPT);unsigned csr=_mm_getcsr();assert(result.is_null());
        word(unsigned(flags));word(csr);
        word(++cases);value(buff.f_current);value(buff.f_permanentStacks);value(buff.f_resistStacks);
        value(character.f_debuffResistStacks);value(buff.f__timer_active);value(buff.f__timer_left);
        value(buff.f_nextTemporaryTimeout);value(buff.f_temporaryStacks);
        word(rng.draws.size());for(auto chance:rng.draws)word(std::bit_cast<uint64_t>(chance));
        word(battle.math_rng.pcg.state);word(battle.math_rng.pcg.inc);hashes.push_back(digest);total_draws+=rng.draws.size();
    };
    const auto nan=std::numeric_limits<double>::quiet_NaN();
    std::vector<V> amounts={V::null(),V::from_bool(false),V::from_bool(true),V::from_int(-7),V::from_int(0),
        V::from_int(3),V::from_int(INT64_MIN),V::from_int(INT64_MAX),V::from_float(-0.0),V::from_float(2.75),
        V::from_float(-2.75),V::from_float(nan),V::from_cstr(battle.arena,"12"),V::from_cstr(battle.arena,"-7"),
        V::from_cstr(battle.arena,"nonnumeric")};
    std::vector<V> reflections={V::null(),V::from_bool(false),V::from_bool(true),V::from_int(0),V::from_int(3),
        V::from_float(0.0),V::from_float(nan),V::from_cstr(battle.arena,""),V::from_cstr(battle.arena,"yes")};
    for(int rounding:{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO})for(unsigned denorm:{0u,0x40u,0x8000u,0x8040u})for(bool kernel:{false,true}){
        assert(std::fesetround(rounding)==0);mode=(_mm_getcsr()&~(0x8040u|0x3fu))|denorm|4u;native=kernel;
    for(const auto& amount:amounts)for(const auto& reflect:reflections)for(double duration:{-1.0,-0.0,0.25})
        run(amount,reflect,duration,true,false);
    for(const auto& reflect:reflections)for(double duration:{-1.0,0.25}) {
        run(V::from_int(3),reflect,duration,false,false);
        run(V::from_int(10),reflect,duration,false,true);
    }
    }
    assert(cases==14112);std::fesetenv(&saved);_mm_setcsr(saved_csr);
    std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"hashes\":[";
    for(size_t i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<hashes[i];}
    std::cout<<"],\"state_and_rng_digest\":"<<digest<<",\"rng_draws\":"<<total_draws<<",\"all16_fp_modes_native_and_generic\":true}\n";
}
