#pragma once
template<class ItemTick,class GemTick>
void cooldown_original_phase(gd::BattleCtx& gd_ctx,Gd__gd_core__CoreCharacter* character,ItemTick&& item_tick,GemTick&& gem_tick) {
    const auto opponent=[character]{return character;};
    {
        gd::GdVal _t756 = gd::gd_iter_seq(gd_ctx.arena, static_cast<Gd__gd_core__CoreGrid*>(opponent()->f_inventory.obj)->f_items);
        gd::GdArr* _t757 = (_t756.kind == gd::GdVal::Kind::Arr) ? _t756.arr : nullptr;
        uint32_t _len__t758 = _t757 ? _t757->len : 0u;
        for (uint32_t _t758 = 0; _t758 < _len__t758; ++_t758) {
            gd::GdVal lv_item = _t757->data[_t758];
            auto* cooldown_item = static_cast<Gd__gd_core__CoreItem*>(lv_item.obj);
            if (([&] { const auto& active = cooldown_item->f__cooldown_active; if (active.kind == gd::GdVal::Kind::Bool) [[likely]] return active.b; return gd::gd_truth(active); }())) item_tick(cooldown_item);
            {
                gd::GdVal _t759 = cooldown_item->f_gems;
                gd::GdArr* _t760 = (_t759.kind == gd::GdVal::Kind::Arr) ? _t759.arr : nullptr;
                uint32_t _len__t761 = _t760 ? _t760->len : 0u;
                for (uint32_t _t761 = 0; _t761 < _len__t761; ++_t761) {
                    gd::GdVal lv_gem = _t760->data[_t761];
                    if (!lv_gem.is_null()) {
                        auto* cooldown_gem = static_cast<Gd__gd_core__CoreItem*>(lv_gem.obj);
                        if (([&] { const auto& active = cooldown_gem->f__cooldown_active; if (active.kind == gd::GdVal::Kind::Bool) [[likely]] return active.b; return gd::gd_truth(active); }())) {gem_tick(cooldown_gem);}
                    }
                }
            }
        }
    }
}
