#pragma once
#include <cstdint>
#include <limits>

// A pure integer model of x := RN(x-d), restricted to a positive, normal
// result staying strictly inside x's original binade. No speculation writes
// state or changes the FPU. The caller applies returned sticky flags at the
// original observation frontier, after proving no intervening observer.
namespace exact_countdown {
struct Result {uint64_t bits;unsigned flags;};
inline bool jump(uint64_t x,uint64_t d,uint64_t count,unsigned csr,Result& out) {
    static_assert(std::numeric_limits<double>::is_iec559 && std::numeric_limits<double>::digits==53);
    if(!count){out={x,0};return true;}
    if((csr&~63u)!=0x1f80u)return false; // nearest, all masks, no DAZ/FTZ
    const unsigned xe=unsigned((x>>52)&2047),de=unsigned((d>>52)&2047);
    if((x>>63)||!xe||xe==2047||(d>>63)||de==2047)return false;
    const uint64_t fraction=(uint64_t{1}<<52)-1;
    const uint64_t dm=(d&fraction)|(de?(uint64_t{1}<<52):0);
    if(!dm){out={x,0};return true;}
    const int shift=int(xe)-int(de?de:1);
    if(shift<0)return false;
    const uint64_t xm=(uint64_t{1}<<52)|(x&fraction);
    uint64_t whole=0,rem=dm;bool tie=false,above=false;
    if(shift<64) {
        whole=dm>>shift;
        rem=shift?dm&((uint64_t{1}<<shift)-1):0;
        if(shift){const auto half=uint64_t{1}<<(shift-1);tie=rem==half;above=rem>half;}
    }
    unsigned __int128 drop;
    if(tie) {
        const uint64_t first=whole+((xm-whole)&1);
        const uint64_t stable=whole+(whole&1);
        drop=first+static_cast<unsigned __int128>(count-1)*stable;
    }else drop=static_cast<unsigned __int128>(count)*(whole+unsigned(above));
    // A rounded value at the lower boundary can have an unrounded result
    // below it, where the next binade has half the ulp. Reject that frontier.
    if(drop>=xm-(uint64_t{1}<<52))return false;
    const uint64_t mantissa=xm-static_cast<uint64_t>(drop);
    out={uint64_t(xe)<<52|(mantissa&fraction),unsigned(rem?32:0)|unsigned(de?0:2)};
    return true;
}
}
