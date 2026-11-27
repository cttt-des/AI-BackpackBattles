#ifdef GD_EVENT_IDENTITY_PRODUCTION
#include "native_event_kernel.hpp"
extern "C" uint64_t gd_diag_native_event_identity_stat(unsigned);
#else
#include "preflight_event_bus.hpp"
#endif
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
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#ifndef GD_EVENT_IDENTITY_PRODUCTION
namespace gd {static uint64_t identity_probe_counts[2]{};void native_event_identity_hit(unsigned i){if(i<2)++identity_probe_counts[i];}}
#endif
using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;
using Data=Gd__gd_core__CoreItemData;
using Bus=Gd__gd_core__CoreEventBus;
using Context=Gd__gd_core__CoreContext;
using Rng=Gd__gd_core__CoreRng;
static const gd::GdClassMeta callback_meta{65000,"IdentityCallback"};
struct Receiver:gd::GdObj {
    std::function<void(const V*,int)> action;
    explicit Receiver(gd::BattleCtx* ctx):GdObj(ctx){}
    const gd::GdClassMeta* meta()const override{return &callback_meta;}
    bool call_method(gd::BattleCtx&,gd::SymId method,const V* args,int argc,V& out)override {
        if(method!=gd::intern_sym("event_identity_callback"))return false;
        action(args,argc);out=V::null();return true;
    }
};
struct UnknownItem:Item {
    std::function<void(unsigned)> action;
    explicit UnknownItem(gd::BattleCtx* ctx):Item(ctx){}
    bool get_prop(gd::SymId property,V& out)const override {
        if(property==SYM_GEN_ownerType_49 || property==SYM_GEN_descriptor_2)action(property);
        return Item::get_prop(property,out);
    }
};
struct UnknownData:Data {
    std::function<void()> action;
    explicit UnknownData(gd::BattleCtx* ctx):Data(ctx){}
    bool get_prop(gd::SymId property,V& out)const override {
        if(property==SYM_GEN_identifier_1673)action();return Data::get_prop(property,out);
    }
};
template<class T>static T* make(gd::BattleCtx& c,const gd::GdClassMeta& m){auto* p=static_cast<T*>(m.alloc_fn(c));p->init_fields(c);return p;}
struct Result {
    std::vector<uint64_t> trace;std::string diagnostics;uint64_t state,inc,gid;int flags;
    bool operator==(const Result&)const=default;
};
static Result run(bool candidate,unsigned mode,unsigned trace_mode,bool native,bool audit,unsigned repeats=1,bool performance=false) {
    gd::BattleCtx battle(65536);battle.bind_battle(191);
    battle.native_event_kernel=native;battle.native_event_audit=true;
    battle.native_resolved_dispatch=true;battle.native_resolved_audit=audit;
    if(mode==18)battle.native_resolved_dispatch=false;
    battle.native_resolved_collect=!performance;
    Context ctx(&battle);ctx.init_fields(battle);ctx.f_fight_ended=V::from_bool(false);
    auto* rng=make<Rng>(battle,META_Gd__gd_core__CoreRng);rng->f_rng=V::from_rng(&battle.math_rng);
    rng->f_oracle_trace=V::from_bool(trace_mode==1 || trace_mode==3);rng->f__stacktrace=V::from_bool(trace_mode==1 || trace_mode==3);
    ctx.f_rng=V::from_obj(rng);
    Bus bus(&battle);bus.init_fields(battle);bus.f__ctx=V::from_obj(&ctx);
    std::vector<uint64_t> trace;
    Item* emitter;
    if(mode==7){auto* p=battle.arena.make<UnknownItem>(&battle);p->init_fields(battle);emitter=p;
        p->action=[&](unsigned property){trace.push_back(property);(void)battle.math_rng.randi();};}
    else emitter=make<Item>(battle,META_Gd__gd_core__CoreItem);
    Data* descriptor;
    if(mode==8){auto* p=battle.arena.make<UnknownData>(&battle);p->init_fields(battle);descriptor=p;
        p->action=[&]{trace.push_back(999);emitter->f_ownerType=V::from_int(5);(void)battle.math_rng.randi();};}
    else descriptor=make<Data>(battle,META_Gd__gd_core__CoreItemData);
    descriptor->f_identifier=V::from_str(gd::make_str(battle.arena,"Longsword"));
    emitter->f_descriptor=V::from_obj(descriptor);emitter->f_ownerType=V::from_int(3);
    if(mode==9)emitter->f_ownerType=V::from_float(2.25);
    if(mode==10)emitter->f_ownerType=V::from_str(gd::make_str(battle.arena,"7"));
    if(mode==11)descriptor->f_identifier=V::from_str(nullptr);
    if(mode==12)descriptor->f_identifier=V::from_int(123);
    if(mode==13)descriptor->f_identifier=V::from_obj(emitter);
    if(mode==14)emitter->f_ownerType=V::from_int(INT64_MIN);
    if(mode==15)emitter->f_ownerType=V::from_int(INT64_MAX);
    if(mode==16)descriptor->native_call_row_=nullptr;
    if(mode==17)descriptor->native_call_row_=emitter->native_call_row_;
    if(mode==19)emitter->f_descriptor=V::null();
    Receiver first(&battle),second(&battle),third(&battle);
    const auto signal=V::from_cstr(battle.arena,"identity_signal");
    const auto method=V::from_cstr(battle.arena,"event_identity_callback");
    auto connect=[&](Receiver& receiver){V args[]={V::from_obj(emitter),signal,V::from_obj(&receiver),method};bus.fn_connectEvent(args,4);};
    connect(first);connect(second);
    const V id_args[]={V::from_obj(emitter),V::from_int(0)};
    const auto id=bus.fn_getEmissionID(id_args,2);
    const auto listeners=gd::get_index(battle,bus.f_connections,id);
    listeners.arr->data[1].arr->data[0].fr->binds=gd::GdArr::from_init(battle.arena,{V::from_int(99)});
    const auto arguments=V::from_arr(gd::GdArr::from_init(battle.arena,{V::from_int(7)}));
    bool nested=false,mutated=false;
    std::function<void()> emit=[&]{const V args[]={V::from_obj(emitter),signal,V::null(),arguments};
#ifdef GD_EVENT_IDENTITY_PRODUCTION
        (void)candidate;bus.fn_emitAndLog(args,4);};
#else
        if(candidate)candidate_emit_and_log(bus,args,4);else bus.fn_emitAndLog(args,4);};
#endif
    first.action=[&](const V* args,int argc){
        assert(argc==1 && args[0].as_int()==7);trace.push_back(1);
        if(performance)return;
        (void)battle.math_rng.randi();
        if(trace_mode==2){rng->f_oracle_trace=V::from_bool(true);rng->f__stacktrace=V::from_bool(true);}
        if(trace_mode==3){rng->f_oracle_trace=V::from_bool(false);rng->f__stacktrace=V::from_bool(false);}
        if(mutated)return;mutated=true;
        switch(mode) {
            case 1:connect(third);break;
            case 2:connect(third);listeners.arr->set_idx(1,listeners.arr->data[2]);break;
            case 3:if(!nested){nested=true;emit();}break;
            case 4:ctx.f_fight_ended=V::from_bool(true);break;
            case 5:descriptor->f_identifier=V::from_str(gd::make_str(battle.arena,"changed"));emitter->f_ownerType=V::from_int(4);break;
            case 6:const_cast<char*>(descriptor->f_identifier.str->data)[0]='X';emitter->f_ownerType=V::from_int(4);break;
            default:break;
        }
    };
    second.action=[&](const V* args,int argc){assert(argc==2 && args[0].as_int()==7 && args[1].as_int()==99);trace.push_back(2);};
    third.action=[&](const V* args,int argc){assert(argc==1 && args[0].as_int()==7);trace.push_back(3);};
    std::feclearexcept(FE_ALL_EXCEPT);
    for(unsigned i=0;i<repeats;++i)emit();
    Result result;result.flags=std::fetestexcept(FE_ALL_EXCEPT);result.trace=std::move(trace);
    result.state=battle.math_rng.pcg.state;result.inc=battle.math_rng.pcg.inc;result.gid=battle.next_gid;
    const auto* log=gd::gd_to_str(battle.arena,rng->f_oracle_trace_log);
    result.diagnostics=std::string(log->data,log->len);
    return result;
}
static uint64_t stamp(FILETIME x){return (uint64_t{x.dwHighDateTime}<<32)|x.dwLowDateTime;}
static uint64_t cpu_ns(){FILETIME a,b,c,d;assert(GetThreadTimes(GetCurrentThread(),&a,&b,&c,&d));return (stamp(c)+stamp(d))*100;}
static uint64_t cycles(){ULONG64 x=0;assert(QueryThreadCycleTime(GetCurrentThread(),&x));return x;}
struct Timing{double cpu_s,wall_s;uint64_t cycles,digest;};
static volatile uint64_t sink=0;
static Timing bench(bool candidate) {
    const auto before_cpu=cpu_ns(),before_cycles=cycles();const auto before=std::chrono::steady_clock::now();uint64_t digest=0;
    for(unsigned i=0;i<1000;++i){const auto result=run(candidate,0,0,true,false,1000,true);digest=digest*1099511628211ULL+result.gid+result.trace.size();}
    const auto elapsed=std::chrono::duration<double>(std::chrono::steady_clock::now()-before).count();
    sink=digest;return {(cpu_ns()-before_cpu)*1e-9,elapsed,cycles()-before_cycles,digest};
}
static void write(const Timing& t){std::cout<<"{\"cpu_s\":"<<t.cpu_s<<",\"wall_s\":"<<t.wall_s<<",\"cycles\":"<<t.cycles<<",\"digest\":"<<t.digest<<'}';}
static uint64_t result_hash(const Result& r) {
    uint64_t h=1469598103934665603ULL;
    const auto mix=[&](uint64_t v){h=(h^v)*1099511628211ULL;};
    mix(r.trace.size());for(auto v:r.trace)mix(v);
    mix(r.diagnostics.size());for(auto v:r.diagnostics)mix(static_cast<unsigned char>(v));
    mix(r.state);mix(r.inc);mix(r.gid);mix(static_cast<unsigned>(r.flags));return h;
}
int main(int argc,char**) {
    register_gen_syms();assert(SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS));assert(SetProcessAffinityMask(GetCurrentProcess(),255));
    unsigned cases=0;std::vector<uint64_t> hashes,original_hashes;
    for(unsigned mode=0;mode<20;++mode)for(unsigned tracing=0;tracing<4;++tracing)
        for(bool native:{false,true})for(bool audit:{false,true}) {
            const auto a=run(false,mode,tracing,native,audit);
#ifdef GD_EVENT_IDENTITY_PRODUCTION
            const auto& b=a;
#else
            const auto b=run(true,mode,tracing,native,audit);
#endif
            if(!(a==b)){std::cerr<<"bus mismatch mode="<<mode<<" trace="<<tracing<<" native="<<native<<" audit="<<audit<<" order="<<(a.trace==b.trace)<<" diagnostics="<<(a.diagnostics==b.diagnostics)<<" RNG="<<(a.state==b.state)<<" IDs="<<(a.gid==b.gid)<<" flags="<<a.flags<<','<<b.flags<<"\n";return 2;}
            hashes.push_back(result_hash(a));
            // Only the appended tail is projected out for comparison with the
            // frozen pre-fix DLL. All diagnostics, RNG, IDs and FP flags remain.
            auto old_contract=a;
            if(mode==1){assert((a.trace==std::vector<uint64_t>{1,2,3}));old_contract.trace.pop_back();}
            if(mode==2){assert((a.trace==std::vector<uint64_t>{1,3,3}));old_contract.trace.pop_back();}
            if((mode==1 || mode==2) && tracing==1){
                assert(a.diagnostics=="[[0, BUS, identity_signal, 2, emitter=Longsword/ot3], [1, BUSL, identity_signal, 0, ?], [2, BUSL, identity_signal, 1, ?], [3, BUSL, identity_signal, 2, ?], [4, BUSD, identity_signal, 3, emitter=Longsword/ot3]]");
                old_contract.diagnostics="[[0, BUS, identity_signal, 2, emitter=Longsword/ot3], [1, BUSL, identity_signal, 0, ?], [2, BUSL, identity_signal, 1, ?], [3, BUSD, identity_signal, 2, emitter=Longsword/ot3]]";
            }
            if((mode==1 || mode==2) && tracing==2){
                assert(a.diagnostics=="[[0, BUSL, identity_signal, 1, ?], [1, BUSL, identity_signal, 2, ?], [2, BUSD, identity_signal, 3, emitter=Longsword/ot3]]");
                old_contract.diagnostics="[[0, BUSL, identity_signal, 1, ?], [1, BUSD, identity_signal, 2, emitter=Longsword/ot3]]";
            }
            original_hashes.push_back(result_hash(old_contract));++cases;
        }
    const auto counter=[](unsigned i){
#ifdef GD_EVENT_IDENTITY_PRODUCTION
        return gd_diag_native_event_identity_stat(i);
#else
        return gd::identity_probe_counts[i];
#endif
    };
    assert(counter(0)>0 && counter(1)>0);
    if(argc>1){std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"fast_hits\":"<<counter(0)<<",\"fallbacks\":"<<counter(1)<<",\"case_hashes\":[";
        for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'\"'<<std::hex<<hashes[i]<<std::dec<<'\"';}std::cout<<"],\"original_contract_hashes\":[";
        for(unsigned i=0;i<original_hashes.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<original_hashes[i]<<std::dec<<'"';}std::cout<<"]}\n";return 0;}
#ifndef GD_EVENT_IDENTITY_PRODUCTION
    std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"fast_hits\":"<<gd::identity_probe_counts[0]<<",\"fallbacks\":"<<gd::identity_probe_counts[1]<<",\"events_per_arm\":1000000,\"scope\":\"event-bus fixture only; not whole-fight throughput\",\"pairs\":[";
    for(unsigned warm=0;warm<20;++warm){(void)run(false,0,0,true,false,1000,true);(void)run(true,0,0,true,false,1000,true);}
    for(unsigned pair=0;pair<8;++pair){Timing a,b;if(pair%2){b=bench(true);a=bench(false);}else{a=bench(false);b=bench(true);}assert(a.digest==b.digest);
        if(pair)std::cout<<',';std::cout<<"{\"baseline\":";write(a);std::cout<<",\"candidate\":";write(b);std::cout<<'}';}
    std::cout<<"]}\n";
#endif
}
