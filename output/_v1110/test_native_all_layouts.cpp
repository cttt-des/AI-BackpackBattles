#include "gd_rt.hpp"
#include "gen/class_metas.hpp"
#include <cassert>
#include <iomanip>
#include <iostream>
extern "C" void gd_init_all_classes();
int main(){
    gd_init_all_classes();unsigned count=0;
    std::cout<<"{\"types\":[";
    for(unsigned id=0;id<4096;++id){
        const auto* type=gd::find_class_by_id(id);if(!type)continue;
        gd::BattleCtx ctx(4u<<20);ctx.native_resolved_dispatch=false;
        const auto rng=ctx.math_rng.pcg.state;
        auto* first=type->alloc_fn(ctx);auto* second=type->alloc_fn(ctx);
        assert(first && second && first->meta()==type && second->meta()==type);
        const auto a=reinterpret_cast<uintptr_t>(first),b=reinterpret_cast<uintptr_t>(second);
        assert(b>a);const auto stride=b-a;
        // Each frozen generated allocator performs exactly one arena.make<T>.
        // sizeof(T) is a multiple of alignof(T); two consecutive allocations
        // within the same arena block therefore differ by exactly sizeof(T).
        assert(ctx.arena.owns_storage(first,2*stride));
        assert(ctx.math_rng.pcg.state==rng);
        if(count++)std::cout<<',';
        std::cout<<"{\"id\":"<<id<<",\"name\":"<<std::quoted(type->class_name)
            <<",\"bytes\":"<<stride<<",\"item\":"
            <<(type->is_subclass_of(&META_Gd__gd_core__CoreItem)?"true":"false")<<'}';
    }
    assert(count==674);
    std::cout<<"],\"count\":"<<count<<",\"rng_unchanged\":true}\n";
}
