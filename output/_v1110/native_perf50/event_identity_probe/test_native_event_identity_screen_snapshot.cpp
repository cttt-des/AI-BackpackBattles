#include "event_identity_fastpath.hpp"
#define NOMINMAX
#include <windows.h>
#include <algorithm>
#include <bit>
#include <cassert>
#include <cfenv>
#include <chrono>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using V=gd::GdVal;
static V original(gd::BattleCtx& ctx,const V& identifier,const gd::GdStr* delimiter,const V& owner) {
    // Preserve the exact shape of the current event-bus expression, including
    // the original integer coercion and original DLL string formatter.
    return gd::gd_add(ctx,gd::gd_add(ctx,V::from_str(gd::gd_to_str(ctx.arena,identifier)),V::from_str(delimiter)),
        [&]{const V args[]={gd::gd_coerce_int(owner)};return gd::gd_str_fn(ctx.arena,args,1);}());
}
static bool same(const V& a,const V& b) {
    return a.kind==b.kind && a.kind==V::Kind::Str && a.str && b.str &&
        a.str->len==b.str->len && a.str->hash==b.str->hash &&
        std::memcmp(a.str->data,b.str->data,a.str->len)==0 &&
        a.str->data[a.str->len]=='\0' && b.str->data[b.str->len]=='\0';
}
static uint64_t stamp(FILETIME x){return (uint64_t{x.dwHighDateTime}<<32)|x.dwLowDateTime;}
static uint64_t cpu_ns(){FILETIME a,b,c,d;assert(GetThreadTimes(GetCurrentThread(),&a,&b,&c,&d));return (stamp(c)+stamp(d))*100;}
static uint64_t cycles(){ULONG64 value=0;assert(QueryThreadCycleTime(GetCurrentThread(),&value));return value;}
static volatile uint64_t sink=0;
struct Timing{double cpu_s,wall_s;uint64_t cycle_count,hash;};
static Timing bench(bool candidate,unsigned iterations,const std::vector<V>& names,const gd::GdStr* delimiter) {
    gd::BattleCtx ctx(65536);uint64_t hash=0;
    const auto before_cpu=cpu_ns(),before_cycles=cycles();const auto before=std::chrono::steady_clock::now();
    for(unsigned i=0;i<iterations;++i) {
        if(i%512==0)ctx.arena.reset();
        const auto& name=names[i%names.size()];const auto owner=V::from_int(i%6);V result;
        if(candidate){const bool ok=gd::native_event_identity_string(ctx.arena,name,delimiter,owner,result);assert(ok);}
        else result=original(ctx,name,delimiter,owner);
        hash=hash*UINT64_C(1099511628211)^result.str->hash;
    }
    const auto elapsed=std::chrono::duration<double>(std::chrono::steady_clock::now()-before).count();
    const auto elapsed_cycles=cycles()-before_cycles,elapsed_cpu=cpu_ns()-before_cpu;
    sink=hash;return {elapsed_cpu*1e-9,elapsed,elapsed_cycles,hash};
}
static void write(const Timing& t){std::cout<<"{\"cpu_s\":"<<t.cpu_s<<",\"wall_s\":"<<t.wall_s<<",\"cycles\":"<<t.cycle_count<<",\"result_hash\":\""<<std::hex<<t.hash<<std::dec<<"\"}";}
int main() {
    assert(SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS));
    assert(SetProcessAffinityMask(GetCurrentProcess(),255));
    gd::BattleCtx old_ctx(65536),new_ctx(65536),inputs(65536);
    std::vector<V> names={V::from_str(nullptr)};
    for(const std::string& text:{std::string(),std::string("a"),std::string("Longsword"),std::string("Items/Exclusive/LongIdentifierWeapon"),std::string("A\0B",3),std::string("\xe5\xae\x9d\xe7\x9f\xb3"),std::string(4096,'x')})
        names.push_back(V::from_str(gd::make_str(inputs.arena,text)));
    std::vector<int64_t> owners={0,1,2,3,4,5,-1,10,-10,INT64_C(9007199254740993),
        std::numeric_limits<int64_t>::min(),std::numeric_limits<int64_t>::max()};
    uint64_t random=UINT64_C(0x1122334455667788);
    for(unsigned i=0;i<1000;++i){random=random*UINT64_C(6364136223846793005)+1;owners.push_back(std::bit_cast<int64_t>(random));}
    const gd::GdStr* delimiters[]={gd::make_str(inputs.arena,"/ot"),gd::make_str(inputs.arena,""),nullptr};
    unsigned cases=0;
    for(const auto& name:names)for(auto owner:owners)for(auto* delimiter:delimiters) {
        old_ctx.arena.reset();new_ctx.arena.reset();const auto value=V::from_int(owner);
        const auto rng_before=new_ctx.math_rng.pcg.state,ids_before=new_ctx.next_gid;
        std::feclearexcept(FE_ALL_EXCEPT);const auto expected=original(old_ctx,name,delimiter,value);const auto old_flags=std::fetestexcept(FE_ALL_EXCEPT);
        std::feclearexcept(FE_ALL_EXCEPT);V actual;assert(gd::native_event_identity_string(new_ctx.arena,name,delimiter,value,actual));const auto new_flags=std::fetestexcept(FE_ALL_EXCEPT);
        assert(same(expected,actual) && old_flags==new_flags);
        assert(new_ctx.math_rng.pcg.state==rng_before && new_ctx.next_gid==ids_before);++cases;
    }
    V unchanged=V::from_int(91);
    for(const auto& value:{V::null(),V::from_bool(true),V::from_float(1.25),V::from_vec2(2,3),V::from_obj(nullptr),V::from_arr(nullptr),V::from_dict(nullptr)}) {
        assert(!gd::native_event_identity_string(new_ctx.arena,value,delimiters[0],V::from_int(3),unchanged));assert(unchanged.kind==V::Kind::Int && unchanged.i==91);
        assert(!gd::native_event_identity_string(new_ctx.arena,names[2],delimiters[0],value,unchanged));assert(unchanged.kind==V::Kind::Int && unchanged.i==91);
    }
    // The callback-phase lifetime contract: the finished value is a snapshot,
    // even if the identifier's mutable backing storage changes afterwards.
    auto source=V::from_str(gd::make_str(inputs.arena,"before"));V result;
    assert(gd::native_event_identity_string(new_ctx.arena,source,delimiters[0],V::from_int(3),result));
    const auto snapshot=std::string(result.str->data,result.str->len);const_cast<char*>(source.str->data)[0]='X';assert(snapshot==std::string(result.str->data,result.str->len));
    std::vector<V> workload;
    for(const auto& text:{"Longsword","Ruby","Shield","BookofLight","Exclusive_FastBlade"})workload.push_back(V::from_str(gd::make_str(inputs.arena,text)));
    (void)bench(false,10000,workload,delimiters[0]);(void)bench(true,10000,workload,delimiters[0]);
    std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"snapshot_alias_rng_ids_flags_checked\":true,\"benchmark_scope\":\"primitive only; not whole-fight throughput\",\"iterations_per_arm\":500000,\"pairs\":[";
    for(unsigned pair=0;pair<8;++pair) {
        Timing baseline,candidate;
        if(pair%2){candidate=bench(true,500000,workload,delimiters[0]);baseline=bench(false,500000,workload,delimiters[0]);}
        else{baseline=bench(false,500000,workload,delimiters[0]);candidate=bench(true,500000,workload,delimiters[0]);}
        assert(baseline.hash==candidate.hash);if(pair)std::cout<<',';
        std::cout<<"{\"baseline\":";write(baseline);std::cout<<",\"candidate\":";write(candidate);std::cout<<'}';
    }
    std::cout<<"]}\n";
}
