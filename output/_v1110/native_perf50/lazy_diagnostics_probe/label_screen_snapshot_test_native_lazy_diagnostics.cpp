#include "preflight_label.hpp"
#include "gen/hdrs/Gd__gd_core_items__Gems__Gem.hpp"
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
#include <limits>
#include <string>
#include <vector>
using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;
using Data=Gd__gd_core__CoreItemData;
using Context=Gd__gd_core__CoreContext;
using Character=Gd__gd_core__CoreCharacter;
using Rng=Gd__gd_core__CoreRng;
template<class T> struct DiagnosticUnknown:T {
    std::function<void(gd::SymId)> callback;
    explicit DiagnosticUnknown(gd::BattleCtx* ctx):T(ctx){}
    bool get_prop(gd::SymId p,V& out)const override {callback(p);return T::get_prop(p,out);}
    bool call_method(gd::BattleCtx& c,gd::SymId m,const V* a,int n,V& out)override {callback(m);return T::call_method(c,m,a,n,out);}
};
template<class T> static T* make(gd::BattleCtx& c,const gd::GdClassMeta& m){auto* p=static_cast<T*>(m.alloc_fn(c));p->init_fields(c);return p;}
template<class T> static DiagnosticUnknown<T>* unknown(gd::BattleCtx& c){auto* p=c.arena.make<DiagnosticUnknown<T>>(&c);p->init_fields(c);return p;}
static uint64_t fast_hits=0,fallbacks=0;
struct Result {
    std::vector<uint64_t> values,callbacks;std::string diagnostics;uint64_t state,inc,gid;int flags;
    bool operator==(const Result&)const=default;
};
static void add(std::vector<uint64_t>& out,const V& v){out.push_back(static_cast<unsigned>(v.kind));if(v.kind==V::Kind::Float)out.push_back(std::bit_cast<uint64_t>(v.f));else if(v.kind==V::Kind::Int)out.push_back(static_cast<uint64_t>(v.i));else if(v.kind==V::Kind::Bool)out.push_back(v.b);}
static Result run(bool candidate,unsigned mode,unsigned tracing,bool native,bool audit,unsigned size,unsigned repeats=3,bool performance=false) {
    gd::BattleCtx battle(65536);battle.bind_battle(791);
    battle.native_event_kernel=native;battle.native_event_audit=true;
    battle.native_resolved_dispatch=mode!=24;battle.native_resolved_audit=audit;
    auto* ctx=mode==12?static_cast<Context*>(unknown<Context>(battle)):make<Context>(battle,META_Gd__gd_core__CoreContext);
    auto* rng=mode==14?static_cast<Rng*>(unknown<Rng>(battle)):make<Rng>(battle,META_Gd__gd_core__CoreRng);
    auto* character=mode==15?static_cast<Character*>(unknown<Character>(battle)):make<Character>(battle,META_Gd__gd_core__CoreCharacter);
    auto* data=mode==13?static_cast<Data*>(unknown<Data>(battle)):make<Data>(battle,META_Gd__gd_core__CoreItemData);
    Item* item=mode==16?static_cast<Item*>(unknown<Item>(battle)):
        mode==28?static_cast<Item*>(make<Gd__gd_core_items__Gems__Gem>(battle,META_Gd__gd_core_items__Gems__Gem)):make<Item>(battle,META_Gd__gd_core__CoreItem);
    ctx->f_rng=V::from_obj(rng);ctx->f_time=V::from_float(0.0);
    rng->f_rng=V::from_rng(&battle.math_rng);rng->f_oracle_trace=V::from_bool(tracing&1);rng->f__stacktrace=V::from_bool(tracing&2);
    character->f_playerId=V::from_bool(true);
    data->f_identifier=V::from_cstr(battle.arena,"FixtureWeapon");
    item->f_ctx=V::from_obj(ctx);item->f_descriptor=V::from_obj(data);item->f_ownerType=V::from_int(3);item->f_character_=V::from_obj(character);
    item->f_buffLabelPositionTimestamps=V::from_arr(gd::GdArr::create(battle.arena,size));
    for(unsigned i=0;i<size;++i)item->f_buffLabelPositionTimestamps.arr->push_back(battle.arena,V::from_float(i%2?0.125:-0.5));
    Result result;
    auto callback=[&](gd::SymId symbol){result.callbacks.push_back(symbol);(void)battle.math_rng.randi();if(mode==12||mode==13){rng->f_oracle_trace=V::from_bool(true);rng->f__stacktrace=V::from_bool(true);}if(mode==15)ctx->f_time=V::from_float(1.5);};
    if(mode==12)static_cast<DiagnosticUnknown<Context>*>(ctx)->callback=callback;
    if(mode==13)static_cast<DiagnosticUnknown<Data>*>(data)->callback=callback;
    if(mode==14)static_cast<DiagnosticUnknown<Rng>*>(rng)->callback=callback;
    if(mode==15)static_cast<DiagnosticUnknown<Character>*>(character)->callback=callback;
    if(mode==16)static_cast<DiagnosticUnknown<Item>*>(item)->callback=callback;
    if(mode==1)item->f_character_=V::null();
    if(mode==2)data->f_identifier=V::from_str(nullptr);
    if(mode==3)item->f_ownerType=V::from_int(INT64_MIN);
    if(mode==4)item->f_ownerType=V::from_int(INT64_MAX);
    if(mode==5)character->f_playerId=V::from_int(-7);
    if(mode==6)character->f_playerId=V::from_float(1.25);
    if(mode==7)character->f_playerId=V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234)));
    if(mode==8)data->f_identifier=V::from_int(179);
    if(mode==9 || mode==30)data->f_identifier=V::from_obj(character);
    if(mode==10)item->f_ownerType=V::from_float(2.25);
    if(mode==11)item->f_ownerType=V::from_cstr(battle.arena,"3");
    if(mode==17)item->native_call_row_=nullptr;
    if(mode==18)data->native_call_row_=nullptr;
    if(mode==19)ctx->native_call_row_=nullptr;
    if(mode==20)rng->native_call_row_=nullptr;
    if(mode==21)character->native_call_row_=nullptr;
    if(mode==22)data->native_call_row_=audit?item->native_call_row_:nullptr;
    if(mode==23)item->native_call_row_=audit?data->native_call_row_:nullptr;
    if(mode==25)rng->f_oracle_trace=V::from_int(0);
    if(mode==26){rng->f_oracle_trace=V::from_bool(true);rng->f__stacktrace=V::from_int(0);}
    if(mode==27)item->f_character_=V::from_obj(nullptr);
    if(mode==28)ctx->f_player=V::from_obj(character);
    std::feclearexcept(FE_ALL_EXCEPT);
    for(unsigned i=0;i<repeats;++i){
        if(mode==31)ctx->f_time=V::from_float(std::bit_cast<double>(UINT64_C(0x7ff8000000004321)));
        else ctx->f_time=V::from_float(i/60.0);
        if(candidate){if(!performance){if(gd::native_skip_label_diagnostic(battle,*item))++fast_hits;else ++fallbacks;}(void)candidate_label(*item,nullptr,0);}
        else (void)item->Item::fn_getNextFreeLabelPosition(nullptr,0);
    }
    result.flags=std::fetestexcept(FE_ALL_EXCEPT);result.state=battle.math_rng.pcg.state;result.inc=battle.math_rng.pcg.inc;result.gid=battle.next_gid;
    for(unsigned i=0;i<item->f_buffLabelPositionTimestamps.arr->len;++i)add(result.values,item->f_buffLabelPositionTimestamps.arr->data[i]);
    add(result.values,ctx->f_time);add(result.values,item->f_ownerType);add(result.values,rng->f_oracle_trace);add(result.values,rng->f__stacktrace);
    const auto* log=gd::gd_to_str(battle.arena,rng->f_oracle_trace_log);result.diagnostics=std::string(log->data,log->len);
    return result;
}
static uint64_t stamp(FILETIME x){return (uint64_t{x.dwHighDateTime}<<32)|x.dwLowDateTime;}
static uint64_t cpu_ns(){FILETIME a,b,c,d;assert(GetThreadTimes(GetCurrentThread(),&a,&b,&c,&d));return(stamp(c)+stamp(d))*100;}
static uint64_t cycles(){ULONG64 x=0;assert(QueryThreadCycleTime(GetCurrentThread(),&x));return x;}
static uint64_t hash(const Result& r){uint64_t h=1469598103934665603ULL;auto mix=[&](uint64_t v){h=(h^v)*1099511628211ULL;};for(auto v:r.values)mix(v);for(auto v:r.callbacks)mix(v);for(auto v:r.diagnostics)mix(static_cast<unsigned char>(v));mix(r.state);mix(r.inc);mix(r.gid);mix(r.flags);return h;}
struct Timing{double cpu_s,wall_s;uint64_t cycles,digest;};
static volatile uint64_t sink;
static Timing bench(bool candidate){auto c=cpu_ns(),cy=cycles();auto t=std::chrono::steady_clock::now();uint64_t h=0;
    for(unsigned i=0;i<1000;++i)h=h*1099511628211ULL+hash(run(candidate,0,0,true,false,8,500,true));
    auto elapsed=std::chrono::duration<double>(std::chrono::steady_clock::now()-t).count();sink=h;return{(cpu_ns()-c)*1e-9,elapsed,cycles()-cy,h};}
static void write(const Timing& t){std::cout<<"{\"cpu_s\":"<<t.cpu_s<<",\"wall_s\":"<<t.wall_s<<",\"cycles\":"<<t.cycles<<",\"digest\":"<<t.digest<<'}';}
int main(int argc,char**){register_gen_syms();assert(SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS));assert(SetProcessAffinityMask(GetCurrentProcess(),255));
    unsigned cases=0;std::vector<uint64_t> hashes;
    for(unsigned mode=0;mode<32;++mode)for(unsigned tracing=0;tracing<4;++tracing)for(bool native:{false,true})for(bool audit:{false,true})for(unsigned size:{0u,1u,8u,20u}){
        const auto a=run(false,mode,tracing,native,audit,size),b=run(true,mode,tracing,native,audit,size);
        if(!(a==b)){std::cerr<<"label mismatch mode="<<mode<<" trace="<<tracing<<" native="<<native<<" audit="<<audit<<" size="<<size<<" rng="<<(a.state==b.state)<<" diag="<<(a.diagnostics==b.diagnostics)<<" values="<<(a.values==b.values)<<" callbacks="<<(a.callbacks==b.callbacks)<<" flags="<<a.flags<<','<<b.flags<<'\n';return 2;}hashes.push_back(hash(a));++cases;}
    assert(fast_hits>0 && fallbacks>0);
    std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"fast_hits\":"<<fast_hits<<",\"fallbacks\":"<<fallbacks;
    if(argc>1){std::cout<<",\"case_hashes\":[";for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'\"'<<std::hex<<hashes[i]<<std::dec<<'\"';}std::cout<<"]}\n";return 0;}
    (void)run(false,0,0,true,false,8,10000,true);(void)run(true,0,0,true,false,8,10000,true);
    std::cout<<",\"calls_per_arm\":500000,\"scope\":\"label function fixture only; not whole-fight throughput\",\"pairs\":[";
    for(unsigned p=0;p<8;++p){Timing a,b;if(p%2){b=bench(true);a=bench(false);}else{a=bench(false);b=bench(true);}assert(a.digest==b.digest);if(p)std::cout<<',';std::cout<<"{\"baseline\":";write(a);std::cout<<",\"candidate\":";write(b);std::cout<<'}';}
    std::cout<<"]}\n";
}
