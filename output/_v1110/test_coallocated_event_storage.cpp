#include "gd_rt.hpp"
#include "gen/hdrs/Gd__gd_core__CoreEvent.hpp"
#include <cassert>
#include <cstdint>
#include <iostream>
int main() {
    unsigned cases=0;
    for(unsigned iteration=0;iteration<32;++iteration)for(bool closed:{false,true}) {
        gd::BattleCtx ctx(65536);ctx.native_timer_watch.closed_world=closed;
        Gd__gd_core__CoreEvent event(&ctx);event.init_fields(ctx);
        auto* original=event.f_params.dict;assert(original && original->len==0);
        if(closed) {
            constexpr size_t offset=(sizeof(gd::GdDict)+alignof(gd::GdDictEntry)-1)
                /alignof(gd::GdDictEntry)*alignof(gd::GdDictEntry);
            assert(original->cap==4);
            assert(reinterpret_cast<uintptr_t>(original->entries)==reinterpret_cast<uintptr_t>(original)+offset);
            assert(ctx.arena.owns_storage(original,offset+4*sizeof(gd::GdDictEntry)));
        } else assert(!original->cap && !original->entries);
        auto* inline_entries=original->entries;
        for(int64_t i=0;i<12;++i)original->set(ctx.arena,gd::GdVal::from_int(i),gd::GdVal::from_int(i+100));
        assert(event.f_params.dict==original && original->len==12);
        if(closed)assert(original->entries!=inline_entries && inline_entries[0].val.i==100);
        for(int64_t i=0;i<12;++i)assert(original->get(gd::GdVal::from_int(i)).i==i+100);
        Gd__gd_core__CoreEvent copy=event;assert(copy.f_params.dict==original);
        event.init_fields(ctx);assert(event.f_params.dict!=original && original->len==12);
        original->erase(gd::GdVal::from_int(4));assert(copy.f_params.dict->len==11);
        assert(event.f_params.dict->len==0);++cases;
    }
    std::cout<<"{\"passed\":true,\"cases\":"<<cases<<"}\n";
}
