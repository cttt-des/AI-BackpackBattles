#include "gd_rt.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__Item.hpp"
#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

int main() {
    size_t misaligned=0;
    std::vector<std::unique_ptr<gd::BattleArena>> arenas;
    for(size_t block : {size_t{63},size_t{127},size_t{1024},size_t{4096}}) {
        arenas.push_back(std::make_unique<gd::BattleArena>(block));
        auto& arena=*arenas.back();
        for(size_t alignment : {size_t{8},size_t{16},size_t{32},size_t{64},size_t{128},size_t{256}}) {
            for(size_t bytes : {size_t{1},size_t{17},size_t{63},size_t{129},block-1,block+1}) {
                auto* pointer=arena.alloc_raw(bytes,alignment);
                misaligned += reinterpret_cast<uintptr_t>(pointer)%alignment != 0;
#ifdef GD_INLINE_TIMER_CANDIDATE
                assert(arena.owns_storage(pointer,bytes));
#endif
            }
        }
#ifdef GD_INLINE_TIMER_CANDIDATE
        int stack_value=0;
        assert(!arena.owns_storage(&stack_value,sizeof(stack_value)));
        auto* last=arena.alloc_raw(13,64);
        assert(arena.owns_storage(last,13));
        arena.reset();
        assert(!arena.owns_storage(last,1));
        auto* reset_pointer=arena.alloc_raw(37,128);
        assert(reinterpret_cast<uintptr_t>(reset_pointer)%128==0);
#endif
    }
#ifdef GD_INLINE_TIMER_CANDIDATE
    assert(misaligned==0);
    static_assert(alignof(Gd__gd_core__CoreItem)==64);
    static_assert(offsetof(Gd__gd_core__CoreItem,native_timer_header_) ==
                  offsetof(Gd__gd_core__CoreItem,f_timers)+sizeof(gd::GdVal));
    static_assert(offsetof(Gd__gd_core__CoreItem,f_timers)%64==0);
    static_assert(offsetof(Gd__gd_core__CoreItem,native_timer_header_)%64+offsetof(gd::GdArr,len)<64);
#endif
    std::cout<<"{\"misaligned_raw_allocations\":"<<misaligned
             <<",\"core_item_bytes\":"<<sizeof(Gd__gd_core__CoreItem)
             <<",\"item_bytes\":"<<sizeof(Gd__gd_core__Item)
             <<",\"item_alignment\":"<<alignof(Gd__gd_core__CoreItem)
             <<",\"timer_field_offset\":"<<offsetof(Gd__gd_core__CoreItem,f_timers);
#ifdef GD_INLINE_TIMER_CANDIDATE
    std::cout<<",\"timer_header_offset\":"<<offsetof(Gd__gd_core__CoreItem,native_timer_header_);
#endif
    std::cout<<"}\n";
}
