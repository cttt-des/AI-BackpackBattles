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
#include <functional>
#ifdef GD_BUFF_CONTEXT_CANDIDATE
extern Gd__gd_core__CoreContext* gd_native_buff_context(gd::BattleCtx&,const gd::GdVal&);
#endif
struct Context : Gd__gd_core__CoreContext {
    mutable std::vector<gd::SymId> reads;
    std::function<void(gd::SymId)> on_read;
    explicit Context(gd::BattleCtx* c):Gd__gd_core__CoreContext(c){}
    bool get_prop(gd::SymId property,gd::GdVal& out) const override {
        reads.push_back(property);if(on_read)on_read(property);
        return Gd__gd_core__CoreContext::get_prop(property,out);
    }
};
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
    Context context(&battle);
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
        context.reads.clear();
        const V args[]={amount,V::from_float(duration),V::null(),V::null(),reflection};
        const auto result=buff.fn_gainTemporary(args,5);assert(result.is_null());
        word(++cases);value(buff.f_current);value(buff.f_permanentStacks);value(buff.f_resistStacks);
        value(character.f_debuffResistStacks);value(buff.f__timer_active);value(buff.f__timer_left);
        value(buff.f_nextTemporaryTimeout);word(buff.f_temporaryStacks.arr->len);
        word(rng.draws.size());for(auto chance:rng.draws)word(std::bit_cast<uint64_t>(chance));
        total_draws+=rng.draws.size();
        word(context.reads.size());for(auto property:context.reads)word(property);
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
    Context second(&battle);Rng replacement(&battle);
    context.init_fields(battle);second.init_fields(battle);character.init_fields(battle);
    buff.init_fields(battle);rng.init_fields(battle);replacement.init_fields(battle);
    rng.draws.clear();replacement.draws.clear();context.reads.clear();second.reads.clear();
    context.f_rng=V::from_obj(&rng);second.f_rng=V::from_obj(&replacement);
    character.f_ctx=V::from_obj(&context);buff.f_ctx=V::from_obj(&context);
    buff.f_character=V::from_obj(&character);buff.f_isBuff=V::from_bool(true);
    buff.f_MAX_STACKS=V::from_int(17);buff.f_resistChancePercent=V::from_int(75);
    bool changed=false;
    context.on_read=[&](gd::SymId property) {
        if(property==SYM_GEN_rng_1406 && !changed){changed=true;buff.f_ctx=V::from_obj(&second);}
    };
    const V replacement_args[]={V::from_int(3),V::from_float(-1),V::null(),V::null(),V::from_bool(false)};
    buff.fn_gainTemporary(replacement_args,5);
    assert(rng.draws.size()==1 && replacement.draws.size()==2 && buff.f_current.as_int()==3);
    word(context.reads.size());for(auto property:context.reads)word(property);
    word(second.reads.size());for(auto property:second.reads)word(property);
    ++cases;total_draws+=3;
    // No original getter is reached on these paths, so a future context may be invalid.
    buff.init_fields(battle);buff.f_isBuff=V::from_bool(true);buff.f_MAX_STACKS=V::from_int(0);
    buff.f_ctx=V::from_obj(reinterpret_cast<gd::GdObj*>(uintptr_t{0x1234}));
    const V unused_args[]={V::from_int(0),V::from_float(-1),V::null(),V::null(),V::from_bool(false)};
    assert(buff.fn_gainTemporary(unused_args,5).is_null());
    assert(buff.fn_gainTemporary(replacement_args,5).is_null());
    cases+=2;
#ifdef GD_BUFF_CONTEXT_CANDIDATE
    assert(gd_native_buff_context(battle,buff.f_ctx)==nullptr);
    assert(gd_native_buff_context(battle,V::from_obj(&context))==nullptr);
#endif
    std::cout<<"{\"cases\":"<<cases<<",\"state_and_rng_digest\":"<<digest<<",\"rng_draws\":"<<total_draws
             <<",\"coercions_timers_getter_order_receiver_swap_and_unused_invalid_context\":true}\n";
}
