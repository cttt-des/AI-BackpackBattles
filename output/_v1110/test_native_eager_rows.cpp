#include "native_inline_dispatch.hpp"
#include <cassert>
#include <iostream>
extern "C" void gd_init_all_classes();
int main() {
    gd_init_all_classes();unsigned total=0;
    for(bool enabled:{false,true}) {
        gd::BattleCtx ctx;ctx.native_resolved_dispatch=enabled;ctx.native_resolved_audit=true;
        const auto rng=ctx.math_rng.pcg.state;unsigned count=0;
        for(unsigned id=0;id<4096;++id) {
            const auto* type=gd::find_class_by_id(id);if(!type)continue;
            auto* object=type->alloc_fn(ctx);assert(object && object->meta()==type);
            if(enabled)assert(object->native_call_row_ && gd::native_resolved_cached_generated(ctx,object) && gd::native_resolved_row_matches(object,object->native_call_row_));
            else assert(!object->native_call_row_);
            ++count;
        }
        assert(count==674 && ctx.math_rng.pcg.state==rng);total+=count;
    }
    std::cout<<"{\"exact_allocations\":"<<total<<",\"rng_unchanged\":true}\n";
}
