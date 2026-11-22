#pragma once
#include "native_targeted_timers.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCombat.hpp"
gd::GdVal reference_timer_loop(Gd__gd_core__CoreCombat& combat,const gd::GdVal* args, int argc) {
    auto* character = static_cast<Gd__gd_core__CoreCharacter*>(args[0].obj);
    const auto delta = gd::gd_coerce_float(argc > 1 ? args[1] : gd::GdVal::null());
    character->fn_tickPhysicsTimers(&delta, 1);
    character->fn_tickBuffs(&delta, 1);
    const auto* inventory = static_cast<Gd__gd_core__CoreGrid*>(character->f_inventory.obj);
    const auto* items = inventory->f_items.arr;
    for (uint32_t i = 0, count = items->len; i < count; ++i) {
        auto* item = static_cast<Gd__gd_core__CoreItem*>(items->data[i].obj);
        if (item->f_timers.arr->len) item->fn__tickTimers(&delta, 1);
        const auto* gems = item->f_gems.arr;
        for (uint32_t j = 0, sockets = gems->len; j < sockets; ++j) {
            const auto& slot = gems->data[j];
            if (slot.kind == gd::GdVal::Kind::Obj && slot.obj) {
                auto* gem = static_cast<Gd__gd_core__CoreItem*>(slot.obj);
                if (gem->f_timers.arr->len) gem->fn__tickTimers(&delta, 1);
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal candidate_timer_loop(Gd__gd_core__CoreCombat& combat,const gd::GdVal* args, int argc) {
    auto* character = static_cast<Gd__gd_core__CoreCharacter*>(args[0].obj);
    const auto delta = gd::gd_coerce_float(argc > 1 ? args[1] : gd::GdVal::null());
    character->fn_tickPhysicsTimers(&delta, 1);
    character->fn_tickBuffs(&delta, 1);
    gd::targeted_timer_tick(*combat.rt_ctx_,character,delta);
    return gd::GdVal::null();
}
inline bool timer_local_candidate=false;
inline gd::GdVal invoke_timer_local(Gd__gd_core__CoreCombat& combat,const gd::GdVal* args,int count){return timer_local_candidate?candidate_timer_loop(combat,args,count):reference_timer_loop(combat,args,count);}
