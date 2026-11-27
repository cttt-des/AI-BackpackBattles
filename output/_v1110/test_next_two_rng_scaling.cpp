#include "gd_rt.hpp"
#include <array>
#include <bit>
#include <cassert>
#include <cerrno>
#include <cfenv>
#include <iostream>
#include <vector>
#include <xmmintrin.h>
using V=gd::GdVal;
static uint64_t mix(uint64_t h,uint64_t x){return(h^x)*1099511628211ULL;}
// Invert x ^ (x >> 18), keeping the rotation zero. Low bits remain free.
static uint64_t state_for(uint32_t output){const auto x=uint64_t{output}<<27;return x^(x>>18)^(x>>36)^(x>>54);}
static void floating(unsigned rounding,unsigned daz,bool preset){
    const int rounds[]={FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO};
    std::fesetround(rounds[rounding]);_mm_setcsr((_mm_getcsr()&~(0x8040u|0x3fu))|((daz&1)?0x40u:0)|((daz&2)?0x8000u:0));
    std::feclearexcept(FE_ALL_EXCEPT);_mm_setcsr(_mm_getcsr()&~0x3fu);
    if(preset)std::feraiseexcept(FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);
    errno=E2BIG;
}
static uint64_t operation(gd::BattleCtx& ctx,unsigned api,uint64_t h){
    auto expected=ctx.math_rng.pcg;const auto proto=expected.next_u32();if(proto)expected.next_u32();
    const V ranges[][2]={{V::from_float(-1.5),V::from_float(2.5)},
        {V::from_float(-0.0),V::from_float(0.0)},
        {V::from_float(double(std::numeric_limits<float>::max())),V::from_float(-double(std::numeric_limits<float>::max()))},
        {V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234))),V::from_float(std::numeric_limits<double>::infinity())}};
    // This external function is defined only in gd_rt.cpp in the actual DLL.
    // No fixture-inline GdRng::randf implementation is used for observations.
    const auto value=gd::call_method(ctx,V::from_rng(&ctx.math_rng),api?gd::SYM_randf_range:gd::SYM_randf,api?ranges[api-1]:nullptr,api?2:0);
    assert(value.kind==V::Kind::Float && ctx.math_rng.pcg.state==expected.state && ctx.math_rng.pcg.inc==expected.inc);
    h=mix(h,std::bit_cast<uint64_t>(value.f));h=mix(h,ctx.math_rng.pcg.state);h=mix(h,ctx.math_rng.pcg.inc);
    h=mix(h,ctx.math_rng.current_seed);h=mix(h,ctx.math_rng.inc);h=mix(h,ctx.math_rng.randomized_flag);
    h=mix(h,errno);h=mix(h,std::fetestexcept(FE_ALL_EXCEPT));h=mix(h,_mm_getcsr());
    for(auto n:ctx.native_resolved_counts)h=mix(h,n);return h;
}
int main(){
    gd::BattleCtx ctx(8192);std::array<uint32_t,64> significands{};
    const uint32_t edges[]={0,1,2,3,62,63,64,65,126,127,128,129,254,255,256,257,
        0x3fffff00u,0x3fffff7fu,0x3fffff80u,0x3fffff81u,0x3fffffffu,
        0x7ffffe00u,0x7ffffeffu,0x7fffff00u,0x7fffff7fu,0x7fffff80u,0x7fffff81u,0x7fffffffu,
        0x80000000u,0x80000001u,0xffffff00u,0xffffffffu};
    for(unsigned i=0;i<32;++i)significands[i]=edges[i];uint32_t random=0x13579bdf;
    for(unsigned i=32;i<64;++i){random=random*1664525u+1013904223u;significands[i]=random;}
    std::vector<uint64_t> hashes;
    for(unsigned rounding=0;rounding<4;++rounding)for(unsigned daz=0;daz<4;++daz)
    for(unsigned leading=0;leading<=32;++leading)for(auto sig:significands)
    for(unsigned api=0;api<5;++api)for(bool preset:{false,true}){
        const uint32_t proto=leading==32?0u:(uint32_t{1}<<(31-leading));
        const auto state=state_for(proto);auto next=state_for(sig);
        next=(next&~uint64_t{1})|((state&1)^1);
        const auto inc=next-state*gd::GdPCG32::MULT;assert(inc&1);
        gd::GdPCG32 check;check.state=state;check.inc=inc;assert(check.next_u32()==proto);assert(check.next_u32()==sig);
        ctx.math_rng.pcg.state=state;ctx.math_rng.pcg.inc=inc;ctx.math_rng.current_seed=0x123456789abcdef;
        ctx.math_rng.randomized_flag=preset;floating(rounding,daz,preset);
        hashes.push_back(operation(ctx,api,1469598103934665603ULL));
    }
    const auto boundary_cases=hashes.size();assert(boundary_cases==337920);
    for(unsigned rounding=0;rounding<4;++rounding)for(unsigned daz=0;daz<4;++daz)for(unsigned seed=0;seed<1024;++seed){
        ctx.math_rng.set_seed(uint64_t{seed}*UINT64_C(0x9e3779b97f4a7c15));floating(rounding,daz,seed&1);
        auto h=uint64_t{1469598103934665603ULL};for(unsigned i=0;i<64;++i)h=operation(ctx,i%5,h);hashes.push_back(h);
    }
    assert(hashes.size()==354304);
    std::cout<<"{\"passed\":true,\"cases\":"<<hashes.size()<<",\"boundary_cases\":"<<boundary_cases<<",\"sequence_cases\":16384,\"hashes\":[";
    for(size_t i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<hashes[i];}std::cout<<"]}\n";
}
