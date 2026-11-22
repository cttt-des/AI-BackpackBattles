#include "native_typed_damage_math.hpp"
#include <bit>
#include <cassert>
#include <cfenv>
#include <iostream>
#include <stdexcept>
namespace gd {uint64_t range_hits[12]{};void native_typed_damage_hit(unsigned i){++range_hits[i];}}
using V=gd::GdVal;
template<class Function>static void reference(gd::BattleCtx& c,const V& count,Function&& fn){const auto v=gd::gd_iter_seq(c.arena,count);auto* a=v.kind==V::Kind::Arr?v.arr:nullptr;const auto n=a?a->len:0u;for(uint32_t i=0;i<n;++i){const auto value=a->data[i];(void)value;fn();}}
static uint64_t run(bool native,unsigned scenario,unsigned mutation,int rounding){gd::BattleCtx c(4096);c.native_resolved_collect=true;
    V count;auto* values=gd::GdArr::from_init(c.arena,{V::from_int(1),V::from_int(2),V::from_int(3),V::from_int(4)});
    const int64_t integers[]={-2,-1,0,1,2,128,129,130};
    if(scenario<8)count=V::from_int(integers[scenario]);else if(scenario==8)count=V::from_float(2.0);else if(scenario==9)count=V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234)));else if(scenario==10)count=V::null();else count=V::from_arr(values);
    unsigned calls=0;uint64_t h=1469598103934665603ULL;
    const auto callback=[&]{++calls;h=(h^c.math_rng.pcg.next_u32())*1099511628211ULL;if(calls==1){if(mutation==1)values->remove_at(1);if(mutation==2)values->push_back(c.arena,V::from_int(5));if(mutation==3)count=V::null();}if(mutation==4&&calls==2)throw std::runtime_error("stop");};
    assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);bool threw=false;
    try{if(native)gd::native_typed_damage_each(c,count,callback);else reference(c,count,callback);}catch(const std::runtime_error&){threw=true;}
    const auto flags=std::fetestexcept(FE_ALL_EXCEPT);h=(h^calls)*1099511628211ULL;h=(h^unsigned(flags))*1099511628211ULL;h=(h^threw)*1099511628211ULL;h=(h^values->len)*1099511628211ULL;h=(h^c.next_gid)*1099511628211ULL;return h;
}
int main(){unsigned cases=0;for(unsigned scenario=0;scenario<12;++scenario)for(unsigned mutation=0;mutation<5;++mutation)for(int r:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}){const auto a=run(false,scenario,mutation,r),b=run(true,scenario,mutation,r);assert(a==b);++cases;}assert(gd::range_hits[10]>0&&gd::range_hits[11]>0);std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"fast_and_fallback_exercised\":true}\n";}
