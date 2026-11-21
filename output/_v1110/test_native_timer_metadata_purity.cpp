#include "gen/hdrs/Gd__gd_core__CoreCombat.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include <iostream>
using V=gd::GdVal;
struct Observable:Gd__gd_core__CoreItem {
    mutable unsigned reads=0;
    explicit Observable(gd::BattleCtx* c):Gd__gd_core__CoreItem(c) {}
    const gd::GdClassMeta* meta() const override {++reads;return &META_Gd__gd_core__CoreItem;}
};
int main() {
    register_gen_syms();gd::BattleCtx ctx;
    ctx.native_resolved_dispatch=true;ctx.native_sparse_timer_scans=true;
    Gd__gd_core__CoreCombat combat(&ctx);combat.init_fields(ctx);
    Gd__gd_core__CoreCharacter character(&ctx);character.init_fields(ctx);
    Gd__gd_core__CoreGrid grid(&ctx);grid.init_fields(ctx);
    character.f_inventory=V::from_obj(&grid);
    auto* item=ctx.arena.make<Observable>(&ctx);item->init_fields(ctx);
    grid.f_items=V::from_arr(gd::GdArr::from_init(ctx.arena,{V::from_obj(item)}));
    item->reads=0;
    const V args[]={V::from_obj(&character),V::from_float(0.25)};
    combat.fn__tickCharacterTimers(args,2);
    std::cout<<"{\"unexpected_meta_calls\":"<<item->reads<<"}\n";
    return item->reads==0 ? 0 : 1;
}
