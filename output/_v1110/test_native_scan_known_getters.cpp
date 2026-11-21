#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include <iostream>
using V=gd::GdVal;
using Context=Gd__gd_core__CoreContext;
struct Custom:Context {
    mutable unsigned calls=0;
    explicit Custom(gd::BattleCtx* c):Context(c) {}
    bool get_prop(gd::SymId p,V& out) const override {
        if(p!=SYM_GEN_frame_counter_1413)return Context::get_prop(p,out);
        ++calls;out=V::from_int(0);return true;
    }
};
int main() {
    register_gen_syms();gd::BattleCtx ctx;
    ctx.native_resolved_dispatch=true;ctx.native_sparse_timer_scans=true;
    ctx.native_resolved_collect=true;
    Context plain(&ctx);plain.init_fields(ctx);
    auto* seeded=static_cast<Context*>(META_Gd__gd_core__CoreContext.alloc_fn(ctx));seeded->init_fields(ctx);
    Custom custom(&ctx);custom.init_fields(ctx);
    const auto twice=[&](gd::GdObj* object) {
        const auto before=gd::native_timer_scan_state().epoch;
        for(unsigned i=0;i<2;++i) {
            const auto value=gd::get_prop(ctx,V::from_obj(object),SYM_GEN_frame_counter_1413);
            if(value.kind!=V::Kind::Int || value.i!=0)return UINT64_MAX;
        }
        return gd::native_timer_scan_state().epoch-before;
    };
    const auto cold=twice(&plain),warm=twice(seeded),unknown=twice(&custom);
    const bool cached=plain.native_call_row_!=nullptr;
    std::cout<<"{\"known_unseeded_invalidations\":"<<cold
        <<",\"known_seeded_invalidations\":"<<warm<<",\"unknown_invalidations\":"<<unknown
        <<",\"unknown_getter_calls\":"<<custom.calls<<",\"known_row_cached\":"<<(cached?"true":"false")
        <<",\"lazy_resolutions\":"<<ctx.native_resolved_counts[2]
        <<",\"unsupported_types\":"<<ctx.native_resolved_counts[3]<<"}\n";
    return cold==0 && warm==0 && unknown==2 && custom.calls==2 && cached &&
        ctx.native_resolved_counts[2]==2 && ctx.native_resolved_counts[3]==1 ? 0 : 1;
}
