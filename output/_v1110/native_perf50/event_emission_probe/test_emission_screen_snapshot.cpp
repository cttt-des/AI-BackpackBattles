#include "preflight_event_bus.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItemData.hpp"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <bit>
#include <cassert>
#include <cfenv>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
namespace gd {static uint64_t emission_probe_counts[4]{};void native_event_identity_hit(unsigned i){if(i<4)++emission_probe_counts[i];}}
using V=gd::GdVal;
using Bus=Gd__gd_core__CoreEventBus;
static unsigned callbacks=0;
struct Override:gd::GdObj {
    unsigned mode;
    Override(gd::BattleCtx* c,unsigned m):GdObj(c),mode(m){}
    const gd::GdClassMeta* meta()const override{return nullptr;}
    bool call_method(gd::BattleCtx& c,gd::SymId method,const V*,int,V& out)override {
        if(method!=gd::SYM_get_instance_id)return false;
        ++callbacks;(void)c.math_rng.randi();
        if(mode==0){out=V::from_int(42);return true;}
        if(mode==1){out=V::from_float(3.25);return true;}
        if(mode==2){out=V::from_str(gd::make_str(c.arena,"custom"));return true;}
        if(mode==3){out=V::null();return true;}
        return false;
    }
};
static bool class_callback(gd::BattleCtx& c,gd::SymId,const V*,int,V& out){++callbacks;out=V::from_int(c.math_rng.randi()%1000);return true;}
static const gd::GdClassMeta custom_class{65000,"IdOverride","",nullptr,false,nullptr,nullptr,class_callback};
struct Result {
    V value;uint64_t state,inc,gid,object_gid,epoch;unsigned calls;int flags;
};
static bool same(const Result& a,const Result& b){
    if(a.value.kind!=b.value.kind || a.state!=b.state || a.inc!=b.inc || a.gid!=b.gid || a.object_gid!=b.object_gid || a.epoch!=b.epoch || a.calls!=b.calls || a.flags!=b.flags)return false;
    if(a.value.kind==V::Kind::Null)return true;
    if(a.value.kind==V::Kind::Int)return a.value.i==b.value.i;
    if(a.value.kind==V::Kind::Float)return std::bit_cast<uint64_t>(a.value.f)==std::bit_cast<uint64_t>(b.value.f);
    return false;
}
static Result run(bool candidate,unsigned emitter_mode,unsigned signal_mode,bool dispatch,bool audit,unsigned initial) {
    gd::BattleCtx battle;battle.bind_battle(78);battle.native_resolved_dispatch=dispatch;battle.native_resolved_audit=audit;battle.native_resolved_collect=true;
    Bus bus(&battle);bus.init_fields(battle);
    gd::GdObj* object=nullptr;V emitter;
    if(emitter_mode<4){const gd::GdClassMeta* metas[]={&META_Gd__gd_core__CoreItem,&META_Gd__gd_core__CoreCharacter,&META_Gd__gd_core__CoreRng,&META_Gd__gd_core__CoreItemData};object=metas[emitter_mode]->alloc_fn(battle);object->init_fields(battle);emitter=V::from_obj(object);}
    else if(emitter_mode<9){object=battle.arena.make<Override>(&battle,emitter_mode-4);emitter=V::from_obj(object);}
    else if(emitter_mode==9)emitter=V::from_obj(nullptr);
    else if(emitter_mode==10)emitter=V::from_arr(gd::GdArr::create(battle.arena));
    else emitter=V::from_cls(&custom_class);
    if(object && initial==1){object->gid_epoch_=battle.gid_epoch;object->gid_=83;}
    if(initial==2)battle.next_gid=UINT64_C(0x8000000000000001);
    if(object && initial==3)object->native_call_row_=nullptr;
    const V signals[]={V::from_int(0),V::from_int(1),V::from_int(31),V::from_int(-1),V::from_int(-2),V::from_int(INT32_MAX),V::from_int(INT64_C(2147483648)),V::from_int(INT64_MIN),V::from_int(INT64_MAX),V::from_int(INT64_C(4294967296)),
        V::from_bool(false),V::from_bool(true),V::from_float(0.0),V::from_float(-0.0),V::from_float(1.25),V::from_float(-1.25),V::from_float(1e8),V::from_str(gd::make_str(battle.arena,"7")),V::from_str(gd::make_str(battle.arena,"-7")),V::from_str(gd::make_str(battle.arena,"x")),V::null(),V::from_vec2(1,2),V::from_obj(object)};
    const V args[]={emitter,signals[signal_mode]};callbacks=0;
    std::feclearexcept(FE_ALL_EXCEPT);
    const auto value=candidate?candidate_emission_id(bus,args,2):bus.fn_getEmissionID(args,2);
    const auto flags=std::fetestexcept(FE_ALL_EXCEPT);
    return {value,battle.math_rng.pcg.state,battle.math_rng.pcg.inc,battle.next_gid,object?object->gid_:0,object?object->gid_epoch_:0,callbacks,flags};
}
static uint64_t stamp(FILETIME x){return (uint64_t{x.dwHighDateTime}<<32)|x.dwLowDateTime;}
static uint64_t cpu_ns(){FILETIME a,b,c,d;assert(GetThreadTimes(GetCurrentThread(),&a,&b,&c,&d));return (stamp(c)+stamp(d))*100;}
static uint64_t cycles(){ULONG64 x=0;assert(QueryThreadCycleTime(GetCurrentThread(),&x));return x;}
struct Timing{double cpu_s,wall_s;uint64_t cycles,digest;};
static volatile uint64_t sink=0;
static Timing bench(bool candidate) {
    gd::BattleCtx battle;battle.native_resolved_dispatch=true;
    Bus bus(&battle);bus.init_fields(battle);
    auto* object=META_Gd__gd_core__CoreItem.alloc_fn(battle);object->init_fields(battle);
    V args[]={V::from_obj(object),V::from_int(0)};uint64_t digest=0;
    (void)object->get_instance_id();const auto old_cpu=cpu_ns(),old_cycles=cycles();const auto start=std::chrono::steady_clock::now();
    for(unsigned i=0;i<5000000;++i){args[1]=V::from_int(i%32);const auto v=candidate?candidate_emission_id(bus,args,2):bus.fn_getEmissionID(args,2);assert(v.kind==V::Kind::Int);digest=digest*1099511628211ULL+static_cast<uint64_t>(v.i);}
    const auto elapsed=std::chrono::duration<double>(std::chrono::steady_clock::now()-start).count();sink=digest;
    return {(cpu_ns()-old_cpu)*1e-9,elapsed,cycles()-old_cycles,digest};
}
static void write(const Timing& t){std::cout<<"{\"cpu_s\":"<<t.cpu_s<<",\"wall_s\":"<<t.wall_s<<",\"cycles\":"<<t.cycles<<",\"digest\":"<<t.digest<<'}';}
int main(int argc,char**) {
    register_gen_syms();assert(SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS));assert(SetProcessAffinityMask(GetCurrentProcess(),255));unsigned cases=0;
    for(unsigned emitter=0;emitter<12;++emitter)for(unsigned signal=0;signal<23;++signal)for(bool dispatch:{false,true})for(bool audit:{false,true})for(unsigned initial=0;initial<4;++initial){
        const auto a=run(false,emitter,signal,dispatch,audit,initial),b=run(true,emitter,signal,dispatch,audit,initial);
        if(!same(a,b)){std::cerr<<"emission mismatch emitter="<<emitter<<" signal="<<signal<<" dispatch="<<dispatch<<" audit="<<audit<<" initial="<<initial<<"\n";return 2;}++cases;
    }
    {gd::BattleCtx c;c.native_resolved_dispatch=true;Bus bus(&c);bus.init_fields(c);auto* object=META_Gd__gd_core__CoreItem.alloc_fn(c);object->init_fields(c);object->rt_ctx_=nullptr;const V args[]={V::from_obj(object),V::from_int(3)};const auto a=bus.fn_getEmissionID(args,2),b=candidate_emission_id(bus,args,2);assert(a.kind==b.kind && a.i==b.i);++cases;}
    assert(gd::emission_probe_counts[2]>0 && gd::emission_probe_counts[3]>0);
    std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"fast_hits\":"<<gd::emission_probe_counts[2]<<",\"fallbacks\":"<<gd::emission_probe_counts[3];
    if(argc>1){std::cout<<"}\n";return 0;}
    std::cout<<",\"iterations_per_arm\":5000000,\"scope\":\"emission ID only; not whole-fight throughput\",\"pairs\":[";
    for(unsigned pair=0;pair<8;++pair){Timing a,b;if(pair%2){b=bench(true);a=bench(false);}else{a=bench(false);b=bench(true);}assert(a.digest==b.digest);if(pair)std::cout<<',';std::cout<<"{\"baseline\":";write(a);std::cout<<",\"candidate\":";write(b);std::cout<<'}';}
    std::cout<<"]}\n";
}
