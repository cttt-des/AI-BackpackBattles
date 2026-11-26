#pragma once
#include "gd_rt.hpp"
#include <cstring>

namespace gd::integer_grid_detail {
inline constexpr uint32_t format_flag=UINT32_C(0x80000000);
inline constexpr uint32_t cells=256;
enum class AxisKind { unsupported,inside,missing };
struct Axis {AxisKind kind;uint32_t coordinate;};

inline Axis axis(double value) {
    uint64_t bits;std::memcpy(&bits,&value,sizeof(bits));
    const uint64_t magnitude=bits&UINT64_C(0x7fffffffffffffff);
    if(!magnitude)return {AxisKind::inside,0};
    const unsigned exponent=unsigned(magnitude>>52);
    // Subnormals depend on MXCSR DAZ. NaN comparisons can raise exceptions.
    // Retain the original hash/equality path for both, as well as infinities.
    if(!exponent || exponent==2047)return {AxisKind::unsupported,0};
    if((bits>>63) || exponent<1023 || exponent>1026)return {AxisKind::missing,0};
    const unsigned shift=52-(exponent-1023);
    const uint64_t mantissa=(magnitude&UINT64_C(0xfffffffffffff))|UINT64_C(0x10000000000000);
    if(mantissa&((UINT64_C(1)<<shift)-1))return {AxisKind::missing,0};
    return {AxisKind::inside,uint32_t(mantissa>>shift)};
}

// True means the original finite coordinate lookup is proven, including a
// definite miss. False retains all original floating-point work and flags.
inline bool query_slot(const GdVal& key,int32_t& result) {
    if(key.kind!=GdVal::Kind::Vec2)return false;
    const Axis x=axis(key.v2.x),y=axis(key.v2.y);
    // Inspect both before returning a miss: the other axis may be a NaN.
    if(x.kind==AxisKind::unsupported || y.kind==AxisKind::unsupported)return false;
    result=(x.kind==AxisKind::missing || y.kind==AxisKind::missing)
        ? -1:int32_t(y.coordinate*16+x.coordinate);
    return true;
}
inline bool stored_slot(const GdVal& key,uint32_t& result) {
    int32_t slot;if(!query_slot(key,slot) || slot<0)return false;
    result=uint32_t(slot);return true;
}
inline bool enabled(const GdDict& dict){return (dict.bucket_cap&format_flag)!=0;}
}
