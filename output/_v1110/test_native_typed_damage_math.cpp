#include "native_typed_damage_math.hpp"
#include <bit>
#include <cassert>
#include <cfenv>
#include <iostream>
#include <limits>
#include <vector>
namespace gd {void native_typed_damage_hit(unsigned){}}
using V=gd::GdVal;using R=Gd__gd_core__CoreDamageResult;
static bool same(const V& a,const V& b){if(a.kind!=b.kind)return false;switch(a.kind){
case V::Kind::Int:return a.i==b.i;case V::Kind::Float:return std::bit_cast<uint64_t>(a.f)==std::bit_cast<uint64_t>(b.f);
case V::Kind::Bool:return a.b==b.b;case V::Kind::Null:return true;default:assert(false);return false;}}
__attribute__((noinline,noclone)) static V reference(gd::BattleCtx& c,unsigned operation,V a,V b){
    if(operation==0){const auto active=gd::gd_clamp(gd::gd_div(c,b,V::from_int(100)),gd::gd_neg(V::from_int(10)),V::from_int(1));return gd::gd_coerce_int(gd::gd_round(gd::gd_mul(a,gd::gd_sub(V::from_float(1.0),active))));}
    if(operation==1)return gd::gd_coerce_int(gd::gd_sub(a,b));
    if(operation==2){a=gd::gd_coerce_int(gd::gd_sub(a,b));return gd::gd_coerce_int(gd::gd_max(V::from_int(0),a));}
    return gd::gd_coerce_float(gd::gd_sub(a,b));
}
__attribute__((noinline,noclone)) static V candidate(gd::BattleCtx& c,unsigned operation,V a,V b){
    if(operation==1)return gd::native_typed_damage_subtract(c,a,b);
    if(operation==3){gd::native_typed_damage_health(c,a,b);return a;}
    R result(&c);result.f_damage=a;result.f_damageReduction=b;
    if(operation==0)gd::native_typed_damage_resistance(c,result,b);else gd::native_typed_damage_after_signal(c,result);
    return result.f_damage;
}
int main(){gd::BattleCtx ctx;std::vector<V> values={V::null(),V::from_bool(false),V::from_bool(true)};
    for(int64_t n:{INT64_MIN,INT64_MIN+1,-INT64_C(1152921504606846977),-INT64_C(9007199254740993),-INT64_C(9007199254740992),-INT64_C(4503599627370496),-100LL,-1LL,0LL,1LL,2LL,9LL,100LL,INT64_C(4503599627370496),INT64_C(9007199254740992),INT64_C(9007199254740993),INT64_C(1152921504606846977),INT64_MAX})values.push_back(V::from_int(n));
    for(double n:{-std::numeric_limits<double>::max(),-1e100,-9007199254740992.0,-1000.0,-100.0,-.5,-.1,-std::numeric_limits<double>::denorm_min(),-0.0,0.0,std::numeric_limits<double>::denorm_min(),1e-300,.1,.5,1.0,100.0,101.0,1e100,std::numeric_limits<double>::max()})values.push_back(V::from_float(n));
    for(uint64_t bits:{UINT64_C(0x7ff0000000000000),UINT64_C(0xfff0000000000000),UINT64_C(0x7ff8000000001234),UINT64_C(0xfff8000000004321),UINT64_C(0x7ff0000000001234),UINT64_C(0xfff0000000004321)})values.push_back(V::from_float(std::bit_cast<double>(bits)));
    unsigned checked=0;
    for(unsigned operation=0;operation<4;++operation)for(unsigned i=0;i<values.size();++i)for(unsigned j=0;j<values.size();++j)for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}){
        assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);auto old=reference(ctx,operation,values[i],values[j]);const int old_flags=std::fetestexcept(FE_ALL_EXCEPT);
        std::feclearexcept(FE_ALL_EXCEPT);auto now=candidate(ctx,operation,values[i],values[j]);const int flags=std::fetestexcept(FE_ALL_EXCEPT);
        if(!same(old,now)||old_flags!=flags){std::cerr<<"math mismatch op="<<operation<<" i="<<i<<" j="<<j<<" mode="<<rounding<<" flags="<<old_flags<<'/'<<flags<<" oldKind="<<int(old.kind)<<" newKind="<<int(now.kind)<<" oldBits="<<std::hex<<std::bit_cast<uint64_t>(old.f)<<" newBits="<<std::bit_cast<uint64_t>(now.f)<<'\n';return 2;}++checked;
    }
    assert(std::fesetround(FE_TONEAREST)==0);
    std::cout<<"{\"passed\":true,\"math_cases\":"<<checked<<",\"value_variants\":"<<values.size()<<",\"rounding_modes\":4,\"all_value_bits_and_fenv_equal\":true}\n";
}
