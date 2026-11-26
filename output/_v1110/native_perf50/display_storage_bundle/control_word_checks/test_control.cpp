#include "gd_rt.hpp"
#include <array>
#include <cassert>
#include <cfenv>
#include <cstring>
#include <iostream>
#include <xmmintrin.h>
#ifdef GD_CONTROL_WORD_PORTABLE
#define GD_TIMER_CONTROL_WORD_FORCE_PORTABLE
#include "control_word_portable_fixture.hpp"
static uint32_t read_control(const gd::NativeTimerWatch* w) {
    return (gd::control_word_portable::native_timer_active_ready(*w)?1u:0u) |
        (gd::control_word_portable::native_timer_index_ready(*w)?2u:0u) |
        (gd::control_word_portable::native_timer_suffix_ready(*w)?4u:0u) |
        (gd::control_word_portable::native_timer_control_word_compatible?8u:0u);
}
static constexpr bool expected_word=false;
#else
extern "C" uint32_t gd_test_native_timer_control(const gd::NativeTimerWatch*);
static uint32_t read_control(const gd::NativeTimerWatch* w) {return gd_test_native_timer_control(w);}
static constexpr bool expected_word=true;
#endif
int main() {
    const std::array<uint32_t,16> depths={0,1,2,3,7,255,256,65535,65536,65537,
        0x01000000u,0x01010101u,0x7fffffffu,0x80000000u,0xfffffffeu,0xffffffffu};
    const auto original_mxcsr=_mm_getcsr();unsigned cases=0;
    gd::NativeTimerWatch watch;
    for(auto rounding:{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO})for(unsigned mode=0;mode<4;++mode) {
        assert(std::fesetround(rounding)==0);
        _mm_setcsr((_mm_getcsr()&~0x8040u)|((mode&1)?0x40u:0)|((mode&2)?0x8000u:0));
        for(int raised:{0,FE_INVALID,FE_DIVBYZERO|FE_INEXACT,FE_UNDERFLOW|FE_OVERFLOW}) {
            std::feclearexcept(FE_ALL_EXCEPT);if(raised)std::feraiseexcept(raised);
            const auto mxcsr=_mm_getcsr();const auto fenv=std::fetestexcept(FE_ALL_EXCEPT);
            for(uint32_t depth:depths)for(unsigned flags=0;flags<16;++flags) {
                watch.depth=depth;watch.enabled=(flags&1)!=0;watch.usable=(flags&2)!=0;
                watch.collect=(flags&4)!=0;watch.closed_world=(flags&8)!=0;
                watch.version=(uint64_t(depth)<<32)^flags;
                watch.cooldown_version=UINT64_MAX-watch.version;
                // This independent oracle uses the original individual fields
                // and predicates. It does not read or construct a packed word.
                const uint32_t expected=(watch.enabled && watch.closed_world && watch.usable && !watch.depth?1u:0u) |
                    (watch.enabled && watch.usable && !watch.depth?2u:0u) |
                    (watch.usable && !watch.depth?4u:0u);
                std::array<unsigned char,sizeof(watch)> before;
                std::memcpy(before.data(),&watch,sizeof(watch));
                const auto actual=read_control(&watch);
                assert((actual&7)==expected && bool(actual&8)==expected_word && (actual&~15u)==0);
                assert(std::memcmp(before.data(),&watch,sizeof(watch))==0);
                assert(_mm_getcsr()==mxcsr && std::fetestexcept(FE_ALL_EXCEPT)==fenv);
                ++cases;
            }
        }
    }
    _mm_setcsr(original_mxcsr);std::fesetround(FE_TONEAREST);
    assert(cases==16384);
    std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"actual_word_path\":"
        <<(expected_word?"true":"false")<<",\"all_predicates_match_original\":true,"
        "\"all16_boolean_combinations\":true,\"depth_boundaries\":16,\"fenv_mxcsr_and_watch_bytes_preserved\":true}\n";
}
