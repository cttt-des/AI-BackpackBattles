#include <array>
#include <cassert>
#include <cfenv>
#include <cstdint>
#include <iostream>
#include <xmmintrin.h>
extern "C" void gd_test_native_active_prefetch(uintptr_t,uintptr_t);
int main(){
    alignas(64) std::array<unsigned char,4096> storage{};
    const std::array<uintptr_t,8> addresses={0,1,0x1000,UINT64_C(0x0000800000000000),
        UINT64_C(0x8000000000000000),UINTPTR_MAX-127,UINTPTR_MAX,reinterpret_cast<uintptr_t>(storage.data())};
    const auto original=_mm_getcsr();unsigned cases=0;
    for(auto rounding:{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO})for(unsigned daz=0;daz<4;++daz){
        assert(std::fesetround(rounding)==0);
        _mm_setcsr((_mm_getcsr()&~0x8040u)|((daz&1)?0x40u:0)|((daz&2)?0x8000u:0));
        for(int flags:{0,FE_INVALID,FE_DIVBYZERO|FE_INEXACT,FE_UNDERFLOW|FE_OVERFLOW}){
            std::feclearexcept(FE_ALL_EXCEPT);if(flags)std::feraiseexcept(flags);
            const auto mxcsr=_mm_getcsr();const int before=std::fetestexcept(FE_ALL_EXCEPT);
            for(auto owner:addresses)for(auto display:addresses){
                gd_test_native_active_prefetch(owner,display);
                assert(_mm_getcsr()==mxcsr && std::fetestexcept(FE_ALL_EXCEPT)==before);++cases;
            }
        }
    }
    _mm_setcsr(original);std::fesetround(FE_TONEAREST);
    std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"invalid_stale_null_and_wrapping_addresses_no_fault\":true,\"fenv_and_mxcsr_preserved\":true}\n";
}
