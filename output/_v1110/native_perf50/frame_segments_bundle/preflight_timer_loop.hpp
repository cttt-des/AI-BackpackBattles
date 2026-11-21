#pragma once
static void candidate_timer_loop(gd::BattleCtx& battle,const gd::GdArr* items,const gd::GdVal& delta) {
    const bool collect=battle.native_resolved_collect;
    const auto count=items->len;
    if(collect) {gd::native_frame_segment_hit(9);for(uint32_t k=0;k<count;++k)gd::native_frame_segment_hit(10);}
    const auto inactive=[&](uint32_t index) {
        if(collect)gd::native_frame_segment_hit(15);
        const auto* item=static_cast<const Gd__gd_core__CoreItem*>(items->data[index].obj);
        if(item->f_timers.arr->len)return false;
        const auto* gems=item->f_gems.arr;
        for(uint32_t j=0,n=gems->len;j<n;++j) {
            if(collect)gd::native_frame_segment_hit(16);
            const auto& slot=gems->data[j];
            if(slot.kind==gd::GdVal::Kind::Obj && slot.obj &&
               static_cast<const Gd__gd_core__CoreItem*>(slot.obj)->f_timers.arr->len)return false;
        }
        return true;
    };
    uint32_t i=0;
    while(count-i>=8) {
        if(collect)gd::native_frame_segment_hit(11);
        // Stop at the first callback-capable parent. No later eligibility is read.
        if(inactive(i+0)
            && inactive(i+1)
            && inactive(i+2)
            && inactive(i+3)
            && inactive(i+4)
            && inactive(i+5)
            && inactive(i+6)
            && inactive(i+7)) {
            if(collect) {gd::native_frame_segment_hit(12);for(unsigned k=0;k<8;++k)gd::native_frame_segment_hit(13);}
            i+=8;continue;
        }
        const auto end=i+8;
        for(;i<end;++i) {
            if(collect)gd::native_frame_segment_hit(14);
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
    }
    for(;i<count;++i) {
        if(collect)gd::native_frame_segment_hit(14);
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
}
