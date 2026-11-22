#include "native_integer_grid.hpp"
#include <array>
#include <bit>
#include <cassert>
#include <cfenv>
#include <iostream>
#include <vector>
#include <xmmintrin.h>
using V=gd::GdVal;
struct Result {int32_t index;int flags;unsigned mxcsr;bool operator==(const Result&)const=default;};
int main() {
    const unsigned original_csr=_mm_getcsr();const int original_rounding=std::fegetround();
    gd::BattleCtx context(65536);auto* dict=gd::GdDict::create(context.arena);
    for(unsigned y=0;y<16;++y)for(unsigned x=0;x<16;++x)
        dict->set(context.arena,V::from_vec2(x?double(x):-0.0,y?double(y):-0.0),V::from_int(y*16+x));
    std::vector<double> values;for(int i=-32;i<=32;++i)values.push_back(double(i));
    for(uint64_t bits:std::array<uint64_t,26>{0,UINT64_C(0x8000000000000000),1,UINT64_C(0x8000000000000001),UINT64_C(0x000fffffffffffff),UINT64_C(0x800fffffffffffff),
        UINT64_C(0x0010000000000000),UINT64_C(0x8010000000000000),UINT64_C(0x3fe0000000000000),UINT64_C(0xbfe0000000000000),
        UINT64_C(0x3ff8000000000000),UINT64_C(0xbff8000000000000),UINT64_C(0x402dffffffffffff),UINT64_C(0x402e000000000001),
        UINT64_C(0x4030000000000001),UINT64_C(0x7fefffffffffffff),UINT64_C(0xffefffffffffffff),UINT64_C(0x7ff0000000000000),UINT64_C(0xfff0000000000000),
        UINT64_C(0x7ff8000000001234),UINT64_C(0x7ff0000000001234),UINT64_C(0xfff8000000001234),UINT64_C(0xfff0000000001234),
        UINT64_C(0x3ff0000000000001),UINT64_C(0x3fefffffffffffff),UINT64_C(0x4340000000000000)})values.push_back(std::bit_cast<double>(bits));
    uint64_t cases=0,fast=0,miss=0,fallback=0;
    for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO})for(unsigned denorm=0;denorm<4;++denorm) {
        std::fesetround(rounding);unsigned csr=_mm_getcsr();csr=(csr&~unsigned(0x8040))|((denorm&1)?0x40:0)|((denorm&2)?0x8000:0);_mm_setcsr(csr);
        auto evaluate=[&](const V& key,bool candidate){std::feclearexcept(FE_ALL_EXCEPT);_mm_setcsr(_mm_getcsr()&~unsigned(0x3f));int32_t index=0;
            if(candidate && gd::integer_grid_detail::query_slot(key,index)){++fast;miss+=index<0;}else{index=dict->find_index(key);if(candidate)++fallback;}
            return Result{index,std::fetestexcept(FE_ALL_EXCEPT),_mm_getcsr()&0x3f};};
        for(double x:values)for(double y:values) {
            const V key=V::from_vec2(x,y);const auto old=evaluate(key,false),actual=evaluate(key,true);assert(old==actual);++cases;
        }
        for(const V key:{V::null(),V::from_bool(true),V::from_int(0),V::from_float(0),V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234)))}) {
            const auto old=evaluate(key,false),actual=evaluate(key,true);assert(old==actual);++cases;
        }
    }
    _mm_setcsr(original_csr);std::fesetround(original_rounding);
    assert(fast>0 && miss>0 && fallback>0);
    std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"fast\":"<<fast<<",\"fast_misses\":"<<miss<<",\"fallback\":"<<fallback<<",\"rounding_modes\":4,\"daz_ftz_modes\":4}\n";
}
