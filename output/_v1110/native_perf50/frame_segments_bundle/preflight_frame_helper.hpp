#pragma once
#include "native_inline_dispatch.hpp"
#include "gen/hdrs/Gd__gd_core__CoreBuff.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core_items__Gems__Gem.hpp"
namespace gd {

void native_frame_segment_hit(unsigned);
struct NativeFrameSegmentSnapshot {
    const Gd__gd_core__CoreCharacter* stun_character=nullptr;
    const Gd__gd_core__CoreCharacter* speed_character=nullptr;
    bool stunned_value=false;
    double speed_value=0.0;
    void clear() {stun_character=nullptr;speed_character=nullptr;}
    bool stunned(const Gd__gd_core__CoreCharacter* character,bool collect) {
        if(stun_character!=character) {
            stunned_value=character->f_stunnedDuration.as_float()>0.0;
            stun_character=character;
            if(collect)native_frame_segment_hit(1);
        } else if(collect)native_frame_segment_hit(2);
        return stunned_value;
    }
    template<class Compute> double speed_increment(
            const Gd__gd_core__CoreCharacter* character,bool collect,Compute compute) {
        if(speed_character!=character) {
            speed_value=compute();speed_character=character;
            if(collect)native_frame_segment_hit(3);
        } else if(collect)native_frame_segment_hit(4);
        return speed_value;
    }
};
inline void native_frame_segment_hit_if(bool collect,unsigned index) {
    if(collect)native_frame_segment_hit(index);
}
inline void native_frame_segment_tick(Gd__gd_core__CoreItem* item,
        NativeFrameSegmentSnapshot& snapshot,const GdVal& delta_value) {

    const auto* row=item->native_call_row_;
    auto* battle=item->rt_ctx_;
    const bool collect=battle && battle->native_resolved_collect;
    if(!battle || !battle->native_resolved_dispatch || !row ||
       (battle->native_resolved_audit && !native_resolved_row_matches(item,row)) || !row->metadata) {
        snapshot.clear();native_frame_segment_hit_if(collect,5);
        item->fn_physicsTick(&delta_value,1);return;
    }
    native_frame_segment_hit_if(collect,0);

    if (!([&] { const auto& active = item->f__cooldown_active; if (active.kind == gd::GdVal::Kind::Bool) [[likely]] return active.b; return gd::gd_truth(active); }())) return;
    auto& context = *static_cast<Gd__gd_core__CoreContext*>(item->f_ctx.obj);
    const auto blocked = item->f__cooldown_blocked_epoch.as_int();
    if (blocked >= 0 && blocked == context.f_timer_pass_epoch.as_int()) return;

    const auto receiver = gd::native_inline_self_type(item->rt_ctx_,item,&META_Gd__gd_core_items__Gems__Gem)
        ? (snapshot.clear(), native_frame_segment_hit_if(collect,6), static_cast<Gd__gd_core_items__Gems__Gem*>(item)->fn_character(nullptr, 0))
        : item->f_character_;
    const auto* character = receiver.kind == gd::GdVal::Kind::Obj
        ? static_cast<const Gd__gd_core__CoreCharacter*>(receiver.obj) : nullptr;
    if (character && snapshot.stunned(character,collect)) return;

    const auto* display = item->f_statDisplayOverrides.arr;
    const auto override = display && display->len > 3 ? display->data[3] : gd::GdVal::null();
    double speed = 1.0;
    const bool uses_override = !override.is_null() && gd::gd_truth(override);
    if (uses_override) {
        speed = override.as_float();
    } else if (gd::gd_truth(item->f_placed) && !item->f_character_.is_null()) {
        if (character) {
            const auto* buffs = character->f_buffs.dict;
            const auto stacks = [&](int64_t type) {
                const auto slot = static_cast<uint32_t>(type - 100);
                const auto* entries = buffs->entries;
                if (slot < buffs->len && entries[slot].key.i == type)
                    return static_cast<const Gd__gd_core__CoreBuff*>(entries[slot].val.obj)->f_current.as_int();
                const auto stack = buffs->get(gd::GdVal::from_int(type));
                return stack.kind == gd::GdVal::Kind::Obj && stack.obj
                    ? static_cast<const Gd__gd_core__CoreBuff*>(stack.obj)->f_current.as_int() : int64_t{0};
            };
            const auto bonus = item->f_speedScale.as_float() + snapshot.speed_increment(character,collect,[&] {return static_cast<double>(stacks(107) - stacks(110)) * 0.02;});
            const auto modified = bonus >= 0.0 ? 1.0 + bonus : 1.0 / (1.0 - bonus);
            speed = modified < 0.1 ? 0.1 : (modified > 10.0 ? 10.0 : modified);
        } else {
            snapshot.clear(); speed = item->fn_getSpeed(nullptr, 0).as_float();
        }
    }

    const auto delta = delta_value.as_float();
    const auto left = uses_override && !override.is_num() ? 0.0 : item->f_triggerTime.as_float() - delta * speed;
    item->f_triggerTime = gd::GdVal::from_float(left);
    auto& gd_ctx = *item->rt_ctx_;
    if (gd::gd_truth(context.f_show_cooldown_progress)) {
        const gd::GdVal progress[] = {gd::GdVal::from_obj(item), gd::GdVal::from_float(1.0 - left / item->f_iterationCooldown.as_float())};
        snapshot.clear(); native_frame_segment_hit_if(collect,7);
        gd::native_inline_call(gd_ctx, context.f_hooks, SYM_GEN_showCooldown_794, progress, 2);
    }
    if (item->f_triggerTime.as_float() <= 0.0) { snapshot.clear(); native_frame_segment_hit_if(collect,8); gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(item), SYM_GEN_trigger_143, nullptr, 0); }
    return;
}
}
