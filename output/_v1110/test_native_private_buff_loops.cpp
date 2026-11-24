#include "gen/hdrs/Gd__gd_core__CoreBuff.hpp"
#include "gen/hdrs/Gd__gd_core__CoreBuff__INNER__TemporaryStacks.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include <array>
#include <bit>
#include <cassert>
#include <cfenv>
#include <functional>
#include <iostream>
#include <vector>
#include <xmmintrin.h>
extern "C" uint64_t gd_diag_native_resolved_stat(unsigned);
using V=gd::GdVal;
using Buff=Gd__gd_core__CoreBuff;
using Context=Gd__gd_core__CoreContext;
using Character=Gd__gd_core__CoreCharacter;
using Stack=Gd__gd_core__CoreBuff__INNER__TemporaryStacks;
static uint64_t mix(uint64_t h,uint64_t v){return(h^v)*1099511628211ULL;}
static uint64_t hash(const V& v,unsigned depth=0){
    uint64_t h=mix(1469598103934665603ULL,unsigned(v.kind));
    if(v.kind==V::Kind::Int)return mix(h,uint64_t(v.i));
    if(v.kind==V::Kind::Bool)return mix(h,v.b);
    if(v.kind==V::Kind::Float)return mix(h,std::bit_cast<uint64_t>(v.f));
    if(v.kind==V::Kind::Arr && v.arr && depth<3){h=mix(h,v.arr->len);for(unsigned i=0;i<v.arr->len;++i)h=mix(h,hash(v.arr->data[i],depth+1));}
    if(v.kind==V::Kind::Obj && v.obj && v.obj->meta()==&META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks){
        const auto* s=static_cast<Stack*>(v.obj);h=mix(h,hash(s->f_amount));h=mix(h,hash(s->f_timeout));
    }
    return h;
}
struct Rng:Gd__gd_core__CoreRng {
    std::function<void(unsigned)> action;
    std::vector<uint64_t> trace;
    bool answer=false;
    explicit Rng(gd::BattleCtx* ctx):Gd__gd_core__CoreRng(ctx){}
    bool call_method(gd::BattleCtx& ctx,gd::SymId method,const V* args,int count,V& out)override {
        if(method!=SYM_GEN_flipPercent_1736)return Gd__gd_core__CoreRng::call_method(ctx,method,args,count,out);
        assert(count==1);trace.push_back(hash(args[0]));(void)ctx.math_rng.randi();
        if(action)action(unsigned(trace.size()));out=V::from_bool(answer);return true;
    }
};
static uint64_t one(unsigned phase,int amount,unsigned scenario,bool native,bool audit,bool dispatch){
    gd::BattleCtx ctx(8192);ctx.bind_battle(149);ctx.native_event_kernel=native;ctx.native_event_audit=true;
    ctx.native_resolved_dispatch=dispatch;ctx.native_resolved_audit=audit;ctx.native_resolved_collect=true;
    Context context(&ctx);Character character(&ctx);Buff buff(&ctx);Rng first(&ctx),second(&ctx);
    context.init_fields(ctx);character.init_fields(ctx);buff.init_fields(ctx);first.init_fields(ctx);second.init_fields(ctx);
    context.f_rng=V::from_obj(&first);context.f_native_frame_rng=V::from_bool(true);
    character.f_ctx=V::from_obj(&context);buff.f_ctx=V::from_obj(&context);buff.f_character=V::from_obj(&character);
    buff.f_MAX_STACKS=V::from_int(4096);buff.f_isBuff=V::from_bool(scenario!=3);
    buff.f_resistChancePercent=V::from_int(scenario==1?-25:75);buff.f_reflectChancePercent=V::from_int(35);
    buff.f_cleanseProtectionChancePercent=V::from_int(scenario==1?-25:75);
    first.answer=second.answer=scenario==1;
    first.action=[&](unsigned count){
        if(count==1 && scenario==2)context.f_rng=V::from_obj(&second);
        if(scenario==3)buff.f_reflectChancePercent=V::from_int(45);
        if(scenario==4){buff.f_resistChancePercent=V::from_int(0);buff.f_cleanseProtectionChancePercent=V::from_int(0);}
    };
    if(phase==1){buff.f_current=V::from_int(2048);buff.f_permanentStacks=V::from_int(scenario==5?0:2048);}
    if(phase==2 || phase==1 && scenario==5){
        auto* a=gd::GdArr::create(ctx.arena);buff.f_temporaryStacks=V::from_arr(a);
        for(int i=0;i<5;++i){auto* s=ctx.arena.make<Stack>(&ctx);s->init_fields(ctx);s->f_amount=V::from_int(500);s->f_timeout=V::from_float(5-i*0.5);a->push_back(ctx.arena,V::from_obj(s));}
        buff.f_current=V::from_int(2500);buff.f_nextTemporaryTimeout=V::from_int(phase==2?2:-1);
    }
    std::array<uint64_t,6> before;for(unsigned i=0;i<6;++i)before[i]=gd_diag_native_resolved_stat(i);
    std::feclearexcept(FE_ALL_EXCEPT);V result;
    if(phase==0){const V args[]={V::from_int(amount),V::from_float(scenario==5?0.25:-1),V::null(),V::null(),V::from_bool(false)};result=buff.fn_gainTemporary(args,5);}
    if(phase==1){const V args[]={V::from_int(amount),V::null(),V::null(),V::from_bool(false)};result=buff.fn_loseStacks(args,4);}
    if(phase==2)result=buff.fn_onTimeout(nullptr,0);
    uint64_t h=mix(1469598103934665603ULL,std::fetestexcept(FE_ALL_EXCEPT));
    for(const auto& v:{result,buff.f_current,buff.f_permanentStacks,buff.f_resistStacks,buff.f_temporaryStacks,
        buff.f_nextTemporaryTimeout,buff.f__timer_active,buff.f__timer_left,character.f_debuffResistStacks})h=mix(h,hash(v));
    for(auto* r:{&first,&second}){h=mix(h,r->trace.size());for(auto x:r->trace)h=mix(h,x);}
    h=mix(h,ctx.math_rng.pcg.state);h=mix(h,ctx.math_rng.pcg.inc);h=mix(h,ctx.next_gid);
    for(unsigned i=0;i<6;++i)h=mix(h,gd_diag_native_resolved_stat(i)-before[i]);return h;
}
int main(){
    register_gen_syms();std::vector<uint64_t> hashes;
    for(auto rounding:{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO})for(unsigned daz=0;daz<4;++daz){
        assert(std::fesetround(rounding)==0);_mm_setcsr((_mm_getcsr()&~0x8040u)|((daz&1)?0x40u:0)|((daz&2)?0x8000u:0));
        for(unsigned phase=0;phase<3;++phase)for(int amount:{-7,0,1,3,85,1023,1024,1025})
        for(unsigned scenario=0;scenario<6;++scenario)for(bool native:{false,true})for(bool audit:{false,true})for(bool dispatch:{false,true})
            hashes.push_back(one(phase,amount,scenario,native,audit,dispatch));
    }
    std::cout<<"{\"passed\":true,\"cases\":"<<hashes.size()<<",\"hashes\":[";
    for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'\"'<<std::hex<<hashes[i]<<std::dec<<'\"';}
    std::cout<<"]}\n";
}
