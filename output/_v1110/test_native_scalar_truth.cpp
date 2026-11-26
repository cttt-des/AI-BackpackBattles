#include "gd_rt.hpp"
#include <bit>
#include <cassert>
#include <cfenv>
#include <iostream>
#include <vector>
#include <xmmintrin.h>

using V=gd::GdVal;
static uint64_t mix(uint64_t h,uint64_t v){return(h^v)*1099511628211ULL;}
struct Observation { bool value;int exceptions;unsigned mxcsr; };
static bool same(Observation a,Observation b){return a.value==b.value && a.exceptions==b.exceptions && a.mxcsr==b.mxcsr;}
template<class F> static Observation observe(F f,const V& v,unsigned mode){
    std::feclearexcept(FE_ALL_EXCEPT);_mm_setcsr(mode & ~0x3fu);
    bool result=f(v);int exceptions=std::fetestexcept(FE_ALL_EXCEPT);
    return {result,exceptions,_mm_getcsr()};
}
int main(){
    static_assert(sizeof(V)==24 && alignof(V)==8 && sizeof(gd::GdArr)==32 && sizeof(gd::BattleCtx)==328);
    fenv_t old_env;std::fegetenv(&old_env);unsigned old_csr=_mm_getcsr();
    gd::BattleArena arena;std::vector<V> values={V::null(),V::from_bool(false),V::from_bool(true)};
    for(int64_t i:{INT64_MIN,INT64_MIN+1,-9007199254740993LL,-1LL,0LL,1LL,9007199254740993LL,INT64_MAX})values.push_back(V::from_int(i));
    std::vector<uint64_t> floats={0,0x8000000000000000ULL,1,0x8000000000000001ULL,0xfffffffffffffULL,
        0x10000000000000ULL,0x3ff0000000000000ULL,0xbff0000000000000ULL,0x7fefffffffffffffULL,
        0x7ff0000000000000ULL,0xfff0000000000000ULL,0x7ff8000000000001ULL,0xfff8000000000042ULL,
        0x7ff0000000000001ULL,0xfff0000000000042ULL};
    for(auto bits:floats){double f=std::bit_cast<double>(bits);values.push_back(V::from_float(f));
        values.push_back(V::from_vec2(f,0));values.push_back(V::from_vec2(0,f));values.push_back(V::from_vec2(f,f));}
    uint64_t rng=0x4680375b64abc91dULL;
    for(unsigned n=0;n<2048;++n){rng^=rng<<13;rng^=rng>>7;rng^=rng<<17;
        values.push_back((n&1)?V::from_float(std::bit_cast<double>(rng)):V::from_int(std::bit_cast<int64_t>(rng)));}
    gd::GdColor colors[6]={{0,0,0,0},{0,0,0,1},{1,0,0,0},{0,1,0,0},{0,0,1,0},
        {0,0,0,std::bit_cast<double>(0x7ff0000000000001ULL)}};
    values.push_back(V::from_color(nullptr));for(auto& c:colors)values.push_back(V::from_color(&c));
    values.push_back(V::from_str(nullptr));values.push_back(V::from_str(gd::make_str(arena,"")));
    values.push_back(V::from_str(gd::make_str(arena,"a\xc3\xa9")));
    gd::GdArr arrays[2];arrays[1].len=1;values.push_back(V::from_arr(nullptr));
    for(auto& a:arrays)values.push_back(V::from_arr(&a));
    gd::GdDict dictionaries[2];dictionaries[1].len=1;values.push_back(V::from_dict(nullptr));
    for(auto& d:dictionaries)values.push_back(V::from_dict(&d));
    for(unsigned kind:{9u,10u,11u,12u,13u,14u,255u})for(unsigned pointer=0;pointer<2;++pointer){
        V v;v.kind=static_cast<V::Kind>(kind);v.i=pointer?0x12345678:0;values.push_back(v);}
    uint64_t hash=1469598103934665603ULL,cases=0;std::vector<uint64_t> hashes;
    for(int rounding:{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO}){
        assert(std::fesetround(rounding)==0);
        for(unsigned bits:{0u,0x40u,0x8000u,0x8040u}){
            unsigned mode=(_mm_getcsr() & ~(0x8040u|0x3fu))|bits;
            for(const auto& v:values){
                unsigned char before[sizeof(V)];std::memcpy(before,&v,sizeof(V));
                auto reference=observe([](const V& x){return gd::gd_truth(x);},v,mode);
                auto actual=observe([](const V& x){return gd::native_scalar_truth(x);},v,mode);
                assert(same(reference,actual));assert(std::memcmp(before,&v,sizeof(V))==0);
                hash=mix(mix(mix(hash,actual.value),unsigned(actual.exceptions)),actual.mxcsr);hashes.push_back(hash);++cases;
            }
            unsigned calls=0;auto once=[&](){++calls;return V::from_bool(true);};
            assert(gd::native_scalar_truth(once()) && calls==1);++cases;
        }
    }
    std::fesetenv(&old_env);_mm_setcsr(old_csr);
    std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"value_shapes\":"<<values.size()<<",\"hashes\":[";
    for(size_t i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<hashes[i];}
    std::cout<<"],\"hash\":"<<hash<<",\"four_roundings_four_daz_ftz\":true}";
}
