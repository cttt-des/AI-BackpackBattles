#pragma once
#include "gd_rt.hpp"
#include <bit>
#include <cstddef>
#include <cstring>
#include <type_traits>
namespace gd::control_word_portable {
using ::gd::NativeTimerWatch;

// Every call reads the current state at its original check position. There is
// no cached readiness bit, additional invalidation write, or removed guard.
#if defined(__MINGW32__) && defined(__x86_64__) && !defined(GD_TIMER_CONTROL_WORD_FORCE_PORTABLE)
inline constexpr bool native_timer_control_word_compatible=
    sizeof(bool)==1 && sizeof(uint32_t)==4 && sizeof(uint64_t)==8 &&
    std::endian::native==std::endian::little &&
    std::is_standard_layout_v<NativeTimerWatch> &&
    std::bit_cast<uint8_t>(true)==1 &&
    offsetof(NativeTimerWatch,enabled)==offsetof(NativeTimerWatch,depth)+4 &&
    offsetof(NativeTimerWatch,usable)==offsetof(NativeTimerWatch,depth)+5 &&
    offsetof(NativeTimerWatch,collect)==offsetof(NativeTimerWatch,depth)+6 &&
    offsetof(NativeTimerWatch,closed_world)==offsetof(NativeTimerWatch,depth)+7;
#else
inline constexpr bool native_timer_control_word_compatible=false;
#endif
template<uint64_t Mask,uint64_t Expected>
inline bool native_timer_control_matches(const NativeTimerWatch& watch) {
    uint64_t word;
    // Read object representation through the complete watch object, rather
    // than extending a pointer past its uint32_t depth subobject.
    std::memcpy(&word,reinterpret_cast<const unsigned char*>(&watch)+
        offsetof(NativeTimerWatch,depth),sizeof(word));
    return (word&Mask)==Expected;
}
inline bool native_timer_active_ready(const NativeTimerWatch& watch) {
    if constexpr(native_timer_control_word_compatible)
        return native_timer_control_matches<UINT64_C(0xff00ffffffffffff),UINT64_C(0x0100010100000000)>(watch);
    return watch.enabled && watch.closed_world && watch.usable && !watch.depth;
}
inline bool native_timer_index_ready(const NativeTimerWatch& watch) {
    if constexpr(native_timer_control_word_compatible)
        return native_timer_control_matches<UINT64_C(0x0000ffffffffffff),UINT64_C(0x0000010100000000)>(watch);
    // Original timer traversal does not require closed_world here.
    return watch.enabled && watch.usable && !watch.depth;
}
inline bool native_timer_suffix_ready(const NativeTimerWatch& watch) {
    if constexpr(native_timer_control_word_compatible)
        return native_timer_control_matches<UINT64_C(0x0000ff00ffffffff),UINT64_C(0x0000010000000000)>(watch);
    // Original timer suffix guard does not check enabled or closed_world.
    return watch.usable && !watch.depth;
}

}
