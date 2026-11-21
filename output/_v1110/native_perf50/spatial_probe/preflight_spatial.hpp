#pragma once
#include "native_inline_dispatch.hpp"
#include "native_scalar_equal.hpp"
#include "native_array_index.hpp"
#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"
#include "gen/hdrs/Gd__gd_core__CoreUtil.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
namespace gd {
static thread_local uint64_t native_spatial_counts[4]{};
inline bool native_spatial_lookup(BattleCtx& ctx,const GdVal& receiver,const GdVal& key,GdVal& value) {
    if(ctx.native_resolved_dispatch && receiver.kind==GdVal::Kind::Dict && receiver.dict) {
        if(ctx.native_resolved_collect){native_inline_variant_hit(7);++native_spatial_counts[0];}
        const auto* dict=receiver.dict;
        const auto index=dict->find_index(key);
        if(index<0)return false;
        value=dict->entries[index].val;
        if(ctx.native_resolved_collect)++native_spatial_counts[1];
        return true;
    }
    if(ctx.native_resolved_collect)++native_spatial_counts[3];
    // receiver is a reference to the live field: a custom has callback can replace it.
    if(!gd_truth(native_inline_call(ctx,receiver,SYM_has,&key,1)))return false;
    value=native_array_index(ctx,receiver,key);
    return true;
}
inline bool native_spatial_contains(BattleCtx& ctx,const GdVal& needle,const GdVal& result) {
    if(ctx.native_resolved_dispatch && needle.kind==GdVal::Kind::Obj) {
        if(ctx.native_resolved_collect)++native_spatial_counts[2];
        const auto* items=result.arr;
        for(uint32_t i=0;i<items->len;++i) {
            const auto& entry=items->data[i];
            if(entry.kind==GdVal::Kind::Obj && entry.obj==needle.obj)return true;
        }
        return false;
    }
    return gd_truth(gd_in(needle,result));
}
}

#ifndef GD_SPATIAL_PRODUCTION
gd::GdVal candidate_getItemsInCells(Gd__gd_core__CoreGrid& grid,const gd::GdVal* _args,int _argc) {
    gd::BattleCtx& gd_ctx = *grid.rt_ctx_;
    gd::GdVal lv_cells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_itemsInCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1707 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1708 = (_t1707.kind == gd::GdVal::Kind::Arr) ? _t1707.arr : nullptr;
        uint32_t _len__t1709 = _t1708 ? _t1708->len : 0u;
        for (uint32_t _t1709 = 0; _t1709 < _len__t1709; ++_t1709) {
            gd::GdVal lv_cell = _t1708->data[_t1709];
            gd::GdVal lv_spatial_value;
            if (gd::native_spatial_lookup(gd_ctx, grid.f_filledCells, lv_cell, lv_spatial_value)) {
                gd::GdVal lv_item = lv_spatial_value;
                if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::native_spatial_contains(gd_ctx, lv_item, lv_itemsInCells))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_placed_6))) : gd::GdVal::from_bool(false)))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, lv_itemsInCells, gd::SYM_push_back, _ca, 1); })();
                }
            }
        }
    }
    return lv_itemsInCells;
    return gd::GdVal::null();
}
gd::GdVal candidate_countItemsInCells(Gd__gd_core__CoreGrid& grid,const gd::GdVal* _args,int _argc) {
    gd::BattleCtx& gd_ctx = *grid.rt_ctx_;
    gd::GdVal lv_cells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_itemCounter = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t1710 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1711 = (_t1710.kind == gd::GdVal::Kind::Arr) ? _t1710.arr : nullptr;
        uint32_t _len__t1712 = _t1711 ? _t1711->len : 0u;
        for (uint32_t _t1712 = 0; _t1712 < _len__t1712; ++_t1712) {
            gd::GdVal lv_cell = _t1711->data[_t1712];
            gd::GdVal lv_spatial_value;
            if (gd::native_spatial_lookup(gd_ctx, grid.f_filledCells, lv_cell, lv_spatial_value)) {
                (void)([&]() { gd::GdVal _ca[] = {lv_itemCounter, lv_spatial_value}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictAdd_1789, _ca, 2); })();
            }
        }
    }
    return lv_itemCounter;
    return gd::GdVal::null();
}
gd::GdVal candidate_getBagsInCells(Gd__gd_core__CoreGrid& grid,const gd::GdVal* _args,int _argc) {
    gd::BattleCtx& gd_ctx = *grid.rt_ctx_;
    gd::GdVal lv_cells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_bags = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1713 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1714 = (_t1713.kind == gd::GdVal::Kind::Arr) ? _t1713.arr : nullptr;
        uint32_t _len__t1715 = _t1714 ? _t1714->len : 0u;
        for (uint32_t _t1715 = 0; _t1715 < _len__t1715; ++_t1715) {
            gd::GdVal lv_cell = _t1714->data[_t1715];
            gd::GdVal lv_spatial_value;
            if (gd::native_spatial_lookup(gd_ctx, grid.f_bagCells, lv_cell, lv_spatial_value)) {
                gd::GdVal lv_bag = lv_spatial_value;
                if (gd::gd_truth(gd::GdVal::from_bool(!gd::native_spatial_contains(gd_ctx, lv_bag, lv_bags)))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_bag}; return gd::native_inline_call(gd_ctx, lv_bags, gd::SYM_push_back, _ca, 1); })();
                }
            }
        }
    }
    return lv_bags;
    return gd::GdVal::null();
}

#endif
