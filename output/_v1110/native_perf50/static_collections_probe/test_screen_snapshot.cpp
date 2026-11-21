#include "preflight_static_collections.hpp"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <bit>
#include <cassert>
#include <cfenv>
#include <chrono>
#include <iostream>
#include <vector>
using V=gd::GdVal;
using Character=Gd__gd_core__CoreCharacter;
using Constants=Gd__gd_core__CoreConst;
struct Result{unsigned kind;int64_t value;uint64_t rng,inc,gid;int flags;bool operator==(const Result&)const=default;};
static std::vector<V> values(gd::BattleCtx& c,Character& character,gd::GdColor& color,gd::GdEnum& enumeration){
    std::vector<V> out={V::null(),V::from_bool(false),V::from_bool(true),V::from_int(INT64_MIN),V::from_int(INT64_MAX)};
    for(int64_t i=-2;i<=8;++i)out.push_back(V::from_int(i));
    for(uint64_t bits:{UINT64_C(0),UINT64_C(0x8000000000000000),UINT64_C(0x4008000000000000),UINT64_C(0x400a000000000000),UINT64_C(0x7ff0000000000000),UINT64_C(0xfff0000000000000),UINT64_C(0x7ff8000000001234),UINT64_C(0x7ff0000000001234),UINT64_C(1)})out.push_back(V::from_float(std::bit_cast<double>(bits)));
    out.push_back(V::from_str(nullptr));for(const auto* s:{"","0","Ranger","3"})out.push_back(V::from_cstr(c.arena,s));
    out.push_back(V::from_vec2(1.25,-0.0));out.push_back(V::from_arr(gd::GdArr::create(c.arena,0)));
    auto* array=gd::GdArr::create(c.arena,1);array->push_back(c.arena,V::from_int(1));out.push_back(V::from_arr(array));
    out.push_back(V::from_dict(gd::GdDict::create(c.arena,0)));out.push_back(V::from_obj(&character));
    out.push_back(V::from_cls(&META_Gd__gd_core__CoreCharacter));out.push_back(V::from_enum(&enumeration));
    out.push_back(V::from_rng(&c.math_rng));out.push_back(V::from_funcref(nullptr));out.push_back(V::from_color(&color));return out;
}
static Result run(bool candidate,unsigned function,unsigned cls,unsigned win,bool native,int rounding){
    gd::BattleCtx c(65536);c.native_resolved_dispatch=native;c.native_resolved_audit=true;
    Character character(&c);character.init_fields(c);gd::GdColor color{1,0,0,1};gd::GdEnum enumeration{};enumeration.name="probe";
    const auto inputs=values(c,character,color,enumeration);assert(cls<inputs.size() && win<inputs.size());
    character.f_characterClass=inputs[cls];const V args[]={inputs[win]};
    assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);V result;
    if(function==0)result=candidate?candidate_classAttackSoundCount(character,args,1):character.fn_classAttackSoundCount(args,1);
    else if(function==1)result=candidate?candidate_classRoundSoundCount(character,args,1):character.fn_classRoundSoundCount(args,1);
    else result=candidate?candidate_numStackTypes(c,args,1):Constants::sf_numStackTypes(c,args,1);
    const int flags=std::fetestexcept(FE_ALL_EXCEPT);assert(result.kind==V::Kind::Null || result.kind==V::Kind::Int);
    return{static_cast<unsigned>(result.kind),result.kind==V::Kind::Int?result.i:0,c.math_rng.pcg.state,c.math_rng.pcg.inc,c.next_gid,flags};
}
static uint64_t hash(const Result& r){uint64_t h=1469598103934665603ULL;for(auto v:{uint64_t(r.kind),uint64_t(r.value),r.rng,r.inc,r.gid,uint64_t(r.flags)})h=(h^v)*1099511628211ULL;return h;}
static uint64_t stamp(FILETIME x){return(uint64_t{x.dwHighDateTime}<<32)|x.dwLowDateTime;}
static uint64_t cpu(){FILETIME a,b,c,d;assert(GetThreadTimes(GetCurrentThread(),&a,&b,&c,&d));return(stamp(c)+stamp(d))*100;}
static uint64_t cycles(){ULONG64 x=0;assert(QueryThreadCycleTime(GetCurrentThread(),&x));return x;}
struct Timing{double cpu_s,wall_s;uint64_t cycles,digest;};static volatile uint64_t sink;
static Timing bench(bool candidate,unsigned mode,unsigned repeats){
    gd::BattleCtx c(65536);c.native_resolved_dispatch=true;Character character(&c);character.init_fields(c);uint64_t h=0;
    auto before=cpu(),cy=cycles();auto start=std::chrono::steady_clock::now();
    for(unsigned i=0;i<repeats;++i){
        if(i%64==0)c.arena.reset();character.f_characterClass=V::from_int(i%7);const V args[]={V::from_bool(i&1)};V value;
        if(mode)value=candidate?candidate_numStackTypes(c,args,1):Constants::sf_numStackTypes(c,args,1);
        else if(i&1)value=candidate?candidate_classRoundSoundCount(character,args,1):character.fn_classRoundSoundCount(args,1);
        else value=candidate?candidate_classAttackSoundCount(character,args,1):character.fn_classAttackSoundCount(args,1);
        assert(value.kind==V::Kind::Int);h=(h^static_cast<uint64_t>(value.i))*1099511628211ULL;
    }
    const double wall=std::chrono::duration<double>(std::chrono::steady_clock::now()-start).count();sink=h;return{(cpu()-before)*1e-9,wall,cycles()-cy,h};
}
static void write(const Timing& t){std::cout<<"{\"cpu_s\":"<<t.cpu_s<<",\"wall_s\":"<<t.wall_s<<",\"cycles\":"<<t.cycles<<",\"digest\":"<<t.digest<<'}';}
int main(int argc,char**){register_gen_syms();assert(SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS));assert(SetProcessAffinityMask(GetCurrentProcess(),255));
    gd::BattleCtx inputs_ctx;Character inputs_character(&inputs_ctx);inputs_character.init_fields(inputs_ctx);gd::GdColor color{1,0,0,1};gd::GdEnum enumeration{};enumeration.name="probe";
    const unsigned count=values(inputs_ctx,inputs_character,color,enumeration).size();unsigned cases=0;std::vector<uint64_t> hashes;
    for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO})for(bool native:{false,true})for(unsigned cls=0;cls<count;++cls){
        for(unsigned function:{0u,2u}){const auto a=run(false,function,cls,cls,native,rounding),b=run(true,function,cls,cls,native,rounding);assert(a==b);hashes.push_back(hash(a));++cases;}
        for(unsigned win=0;win<count;++win){const auto a=run(false,1,cls,win,native,rounding),b=run(true,1,cls,win,native,rounding);if(!(a==b)){std::cerr<<"round mismatch class="<<cls<<" win="<<win<<" flags="<<a.flags<<','<<b.flags<<'\n';return 2;}hashes.push_back(hash(a));++cases;}
    }
    assert(std::fesetround(FE_TONEAREST)==0);std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"input_kinds_and_boundaries\":"<<count;
    if(argc>1){std::cout<<",\"case_hashes\":[";for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'\"'<<std::hex<<hashes[i]<<std::dec<<'\"';}std::cout<<"]}\n";return 0;}
    std::cout<<",\"scope\":\"numeric collection consumer functions only; not whole-fight throughput\",\"workloads\":[";
    for(unsigned mode=0;mode<2;++mode){const unsigned repeats=mode?1000000:100000;(void)bench(false,mode,1000);(void)bench(true,mode,1000);if(mode)std::cout<<',';std::cout<<"{\"mode\":"<<mode<<",\"calls_per_arm\":"<<repeats<<",\"pairs\":[";
        for(unsigned pair=0;pair<8;++pair){Timing a,b;if(pair%2){b=bench(true,mode,repeats);a=bench(false,mode,repeats);}else{a=bench(false,mode,repeats);b=bench(true,mode,repeats);}assert(a.digest==b.digest);if(pair)std::cout<<',';std::cout<<"{\"baseline\":";write(a);std::cout<<",\"candidate\":";write(b);std::cout<<'}';}std::cout<<"]}";
    }std::cout<<"]}\n";
}
