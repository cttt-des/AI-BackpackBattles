#include "preflight_buff_diagnostics.hpp"
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
using V=gd::GdVal;
using Buff=Gd__gd_core__CoreBuff;
using Stacks=Gd__gd_core__CoreBuff__INNER__TemporaryStacks;
using Context=Gd__gd_core__CoreContext;
using Rng=Gd__gd_core__CoreRng;
template<class T> struct DiagnosticUnknown:T {
    std::function<void(gd::SymId)> action;
    explicit DiagnosticUnknown(gd::BattleCtx* c):T(c){}
    bool get_prop(gd::SymId p,V& out)const override{action(p);return T::get_prop(p,out);}
};
template<class T>static T* make(gd::BattleCtx& c,const gd::GdClassMeta& m){auto* p=static_cast<T*>(m.alloc_fn(c));p->init_fields(c);return p;}
template<class T>static DiagnosticUnknown<T>* unknown(gd::BattleCtx& c){auto* p=c.arena.make<DiagnosticUnknown<T>>(&c);p->init_fields(c);return p;}
struct Result{std::string diagnostics;std::vector<uint64_t> callbacks;uint64_t state,gid;int flags;bool operator==(const Result&)const=default;};
static uint64_t hits=0,misses=0;
static Result run(bool candidate,unsigned site,unsigned mode,unsigned tracing,bool native,bool audit,const V& value,unsigned repeat=1,bool performance=false){
    gd::BattleCtx c(65536);c.bind_battle(791);c.native_event_kernel=native;c.native_event_audit=true;c.native_resolved_dispatch=mode!=7;c.native_resolved_audit=audit;
    auto* context=mode==1?static_cast<Context*>(unknown<Context>(c)):make<Context>(c,META_Gd__gd_core__CoreContext);
    auto* rng=mode==2?static_cast<Rng*>(unknown<Rng>(c)):make<Rng>(c,META_Gd__gd_core__CoreRng);
    auto* stacks=mode==3?static_cast<Stacks*>(unknown<Stacks>(c)):make<Stacks>(c,META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks);
    auto* buff=make<Buff>(c,META_Gd__gd_core__CoreBuff);
    buff->f_ctx=V::from_obj(context);buff->f_nextTemporaryTimeout=value;buff->f_type=V::from_int(3);
    buff->f_temporaryStacks=V::from_arr(gd::GdArr::create(c.arena,0));
    context->f_rng=V::from_obj(rng);context->f_time=value;
    rng->f_rng=V::from_rng(&c.math_rng);rng->f_oracle_trace=V::from_bool(tracing&1);rng->f__stacktrace=V::from_bool(tracing&2);
    stacks->f_amount=value;
    Result result;
    auto callback=[&](gd::SymId s){result.callbacks.push_back(s);(void)c.math_rng.randi();rng->f_oracle_trace=V::from_bool(true);rng->f__stacktrace=V::from_bool(true);};
    if(mode==1)static_cast<DiagnosticUnknown<Context>*>(context)->action=callback;
    if(mode==2)static_cast<DiagnosticUnknown<Rng>*>(rng)->action=callback;
    if(mode==3)static_cast<DiagnosticUnknown<Stacks>*>(stacks)->action=callback;
    if(mode==4)context->native_call_row_=nullptr;
    if(mode==5)stacks->native_call_row_=nullptr;
    if(mode==6)rng->native_call_row_=nullptr;
    if(mode==8)rng->f_oracle_trace=V::from_int(0);
    if(mode==9){rng->f_oracle_trace=V::from_bool(true);rng->f__stacktrace=V::from_int(0);}
    if(mode==10)stacks->native_call_row_=audit?context->native_call_row_:nullptr;
    if(mode==11)context->native_call_row_=audit?stacks->native_call_row_:nullptr;
    std::feclearexcept(FE_ALL_EXCEPT);
    for(unsigned i=0;i<repeat;++i){
        if(candidate){if(!performance){bool skip=site==75?gd::native_skip_buff_farthest_diagnostic(c,*buff,value,V::from_obj(stacks)):site==90?gd::native_skip_buff_timeout_diagnostic(c,*buff,value,value):gd::native_skip_buff_diagnostic(c,*buff,{value});if(skip)++hits;else ++misses;}
            candidate_buff_diagnostic(site,*buff,value,value,V::from_obj(stacks),value,value);}
        else original_buff_diagnostic(site,*buff,value,value,V::from_obj(stacks),value,value);
    }
    result.flags=std::fetestexcept(FE_ALL_EXCEPT);result.state=c.math_rng.pcg.state;result.gid=c.next_gid;
    const auto* log=gd::gd_to_str(c.arena,rng->f_oracle_trace_log);result.diagnostics=std::string(log->data,log->len);return result;
}
static uint64_t hash(const Result& r){uint64_t h=1469598103934665603ULL;auto mix=[&](uint64_t v){h=(h^v)*1099511628211ULL;};for(auto v:r.diagnostics)mix(static_cast<unsigned char>(v));for(auto v:r.callbacks)mix(v);mix(r.state);mix(r.gid);mix(r.flags);return h;}
static uint64_t stamp(FILETIME x){return(uint64_t{x.dwHighDateTime}<<32)|x.dwLowDateTime;}
static uint64_t cpu_ns(){FILETIME a,b,c,d;assert(GetThreadTimes(GetCurrentThread(),&a,&b,&c,&d));return(stamp(c)+stamp(d))*100;}
static uint64_t cycles(){ULONG64 x=0;assert(QueryThreadCycleTime(GetCurrentThread(),&x));return x;}
struct Timing{double cpu_s,wall_s;uint64_t cycles,digest;};
static volatile uint64_t sink;
static Timing bench(bool candidate){auto c=cpu_ns(),cy=cycles();auto t=std::chrono::steady_clock::now();uint64_t h=0;
    for(unsigned group=0;group<100;++group)for(unsigned site:{72u,75u,77u,88u,89u,90u})h=h*1099511628211ULL+hash(run(candidate,site,0,0,true,false,V::from_float(3.0),1000,true));
    auto elapsed=std::chrono::duration<double>(std::chrono::steady_clock::now()-t).count();sink=h;return{(cpu_ns()-c)*1e-9,elapsed,cycles()-cy,h};}
static void write(const Timing& t){std::cout<<"{\"cpu_s\":"<<t.cpu_s<<",\"wall_s\":"<<t.wall_s<<",\"cycles\":"<<t.cycles<<",\"digest\":"<<t.digest<<'}';}
int main(int argc,char**){register_gen_syms();assert(SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS));assert(SetProcessAffinityMask(GetCurrentProcess(),255));
    gd::BattleCtx inputs(65536);
    std::vector<V> values={V::null(),V::from_bool(false),V::from_bool(true),V::from_int(0),V::from_int(INT64_MIN),V::from_int(INT64_MAX),V::from_float(0.0),V::from_float(-0.0),V::from_float(3.0),V::from_float(-7.0),V::from_float(0.5),V::from_float(3.25),V::from_float(1e16),V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234))),V::from_float(std::bit_cast<double>(UINT64_C(0x7ff8000000005678))),V::from_str(nullptr),V::from_cstr(inputs.arena,"a\0b"),V::from_vec2(1.25,2.5)};
    uint64_t random=0xabcdef1234567890ULL;
    std::vector<V> numeric;
    for(unsigned i=0;i<10000;++i){random=random*6364136223846793005ULL+1;numeric.push_back(V::from_float(std::bit_cast<double>(random)));numeric.push_back(V::from_float(static_cast<double>(static_cast<int64_t>(random%UINT64_C(10000000000000000)))));}
    unsigned pure_checks=0;
    for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}){assert(std::fesetround(rounding)==0);for(const auto& v:numeric)if(gd::native_diagnostic_format_pure(v)){std::feclearexcept(FE_ALL_EXCEPT);(void)gd::gd_str_fn(inputs.arena,&v,1);assert(std::fetestexcept(FE_ALL_EXCEPT)==0);++pure_checks;}}
    assert(std::fesetround(FE_TONEAREST)==0);
    unsigned cases=0;std::vector<uint64_t> hashes;
    for(unsigned site:{72u,75u,77u,88u,89u,90u})for(unsigned mode=0;mode<12;++mode)for(unsigned trace=0;trace<4;++trace)for(bool native:{false,true})for(bool audit:{false,true})for(const auto& v:values){
        const auto a=run(false,site,mode,trace,native,audit,v),b=run(true,site,mode,trace,native,audit,v);
        if(!(a==b)){std::cerr<<"buff diagnostic mismatch site="<<site<<" mode="<<mode<<" trace="<<trace<<" native="<<native<<" audit="<<audit<<" kind="<<static_cast<unsigned>(v.kind)<<" flags="<<a.flags<<','<<b.flags<<" callbacks="<<(a.callbacks==b.callbacks)<<" diag="<<(a.diagnostics==b.diagnostics)<<'\n';return 2;}hashes.push_back(hash(a));++cases;}
    assert(hits>0 && misses>0);
    std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"pure_float_flags_checks\":"<<pure_checks<<",\"fast_hits\":"<<hits<<",\"fallbacks\":"<<misses;
    if(argc>1){std::cout<<",\"case_hashes\":[";for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'\"'<<std::hex<<hashes[i]<<std::dec<<'\"';}std::cout<<"]}\n";return 0;}
    (void)bench(false);(void)bench(true);
    std::cout<<",\"calls_per_arm\":600000,\"scope\":\"six buff diagnostic fixtures only; not whole-fight throughput\",\"pairs\":[";
    for(unsigned p=0;p<8;++p){Timing a,b;if(p%2){b=bench(true);a=bench(false);}else{a=bench(false);b=bench(true);}assert(a.digest==b.digest);if(p)std::cout<<',';std::cout<<"{\"baseline\":";write(a);std::cout<<",\"candidate\":";write(b);std::cout<<'}';}
    std::cout<<"]}\n";
}
