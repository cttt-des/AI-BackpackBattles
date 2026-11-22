#pragma once
#include "native_inline_dispatch.hpp"
#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"

namespace gd {
struct TargetedTimerEntry {
    Gd__gd_core__CoreItem* owner;
    const GdArr* gems;
    uint32_t item_index,gem_index,sockets;
};
struct TargetedTimerCache {
    const Gd__gd_core__CoreCharacter* character=nullptr;
    const GdArr* items=nullptr;
    uint64_t version=0;
    TargetedTimerEntry* entries=nullptr;
    uint32_t count=0,items_count=0;
};
inline bool targeted_timer_watch_array(BattleCtx& ctx,GdArr* array) {
    auto& watch=ctx.native_timer_watch;
    if(!array || (array->timer_watch && array->timer_watch!=&watch) ||
       !ctx.arena.owns_storage(array,sizeof(GdArr)) ||
       (array->len && !ctx.arena.owns_storage(array->data,sizeof(GdVal)*size_t(array->len))))return false;
    array->timer_watch=&watch;return true;
}
inline void targeted_timer_scan_gems(const GdArr* gems,uint32_t start,uint32_t sockets,const GdVal& delta) {
    for(uint32_t j=start;j<sockets;++j) {
        const auto& slot=gems->data[j];
        if(slot.kind==GdVal::Kind::Obj && slot.obj) {
            auto* gem=static_cast<Gd__gd_core__CoreItem*>(slot.obj);
            if(gem->f_timers.arr->len)gem->fn__tickTimers(&delta,1);
        }
    }
}
inline void targeted_timer_scan_items(const GdArr* items,uint32_t start,uint32_t count,const GdVal& delta) {
    for(uint32_t i=start;i<count;++i) {
        auto* item=static_cast<Gd__gd_core__CoreItem*>(items->data[i].obj);
        if(item->f_timers.arr->len)item->fn__tickTimers(&delta,1);
        const auto* gems=item->f_gems.arr;
        targeted_timer_scan_gems(gems,0,gems->len,delta);
    }
}
inline bool targeted_timer_build(BattleCtx& ctx,Gd__gd_core__CoreCharacter* character,
                                 const GdArr* items,TargetedTimerCache& cache) {
    auto& watch=ctx.native_timer_watch;
    const auto* grid=static_cast<Gd__gd_core__CoreGrid*>(character->f_inventory.obj);
    if(!ctx.arena.owns_storage(character,sizeof(*character)) || !native_timer_known_object(grid) ||
       !ctx.arena.owns_storage(grid,sizeof(*grid)))return false;
    if(!targeted_timer_watch_array(ctx,const_cast<GdArr*>(items)))return false;
    uint64_t capacity=items->len;
    for(uint32_t i=0;i<items->len;++i) {
        const auto& value=items->data[i];
        if(value.kind!=GdVal::Kind::Obj || !value.obj || value.obj->rt_ctx_!=&ctx ||
           !ctx.arena.owns_storage(value.obj,sizeof(Gd__gd_core__CoreItem)) || !native_timer_known_object(value.obj))return false;
        auto* item=static_cast<Gd__gd_core__CoreItem*>(value.obj);
        if(!targeted_timer_watch_array(ctx,item->f_timers.arr) || !targeted_timer_watch_array(ctx,item->f_gems.arr))return false;
        for(uint32_t t=0;t<item->f_timers.arr->len;++t) {
            const auto& timer=item->f_timers.arr->data[t];
            if(timer.kind==GdVal::Kind::Obj && timer.obj && timer.obj->rt_ctx_!=&ctx)return false;
        }
        const auto* gems=item->f_gems.arr;capacity+=gems->len;
        if(capacity>UINT32_MAX)return false;
        for(uint32_t j=0;j<gems->len;++j) {
            const auto& gem=gems->data[j];
            if(gem.kind==GdVal::Kind::Obj && gem.obj) {
                if(gem.obj->rt_ctx_!=&ctx || !ctx.arena.owns_storage(gem.obj,sizeof(Gd__gd_core__CoreItem)) || !native_timer_known_object(gem.obj) ||
                   !targeted_timer_watch_array(ctx,static_cast<Gd__gd_core__CoreItem*>(gem.obj)->f_timers.arr))return false;
                const auto* timers=static_cast<Gd__gd_core__CoreItem*>(gem.obj)->f_timers.arr;
                for(uint32_t t=0;t<timers->len;++t) {
                    const auto& timer=timers->data[t];
                    if(timer.kind==GdVal::Kind::Obj && timer.obj && timer.obj->rt_ctx_!=&ctx)return false;
                }
            }
        }
    }
    auto* entries=ctx.arena.alloc_array<TargetedTimerEntry>(size_t(capacity));uint32_t count=0;
    for(uint32_t i=0;i<items->len;++i) {
        auto* item=static_cast<Gd__gd_core__CoreItem*>(items->data[i].obj);
        if(item->f_timers.arr->len)entries[count++]={item,nullptr,i,UINT32_MAX,0};
        auto* gems=item->f_gems.arr;
        for(uint32_t j=0;j<gems->len;++j) {
            const auto& gem=gems->data[j];
            if(gem.kind==GdVal::Kind::Obj && gem.obj) {
                auto* owner=static_cast<Gd__gd_core__CoreItem*>(gem.obj);
                if(owner->f_timers.arr->len)entries[count++]={owner,gems,i,j,gems->len};
            }
        }
    }
    cache={character,items,watch.version,entries,count,items->len};
    if(watch.collect){native_timer_index_hit(1);native_timer_index_hit(7,capacity);native_timer_index_hit(8,count);}
    return true;
}
inline void targeted_timer_tick(BattleCtx& ctx,Gd__gd_core__CoreCharacter* character,const GdVal& delta) {
    const auto* grid=static_cast<Gd__gd_core__CoreGrid*>(character->f_inventory.obj);
    const auto* items=grid->f_items.arr;
    const uint32_t count=items->len;
    auto& watch=ctx.native_timer_watch;watch.collect=ctx.native_resolved_collect;
    const auto& player_id=character->f_playerId;
    const bool eligible=watch.enabled && watch.usable && !watch.depth && character->rt_ctx_==&ctx && grid->rt_ctx_==&ctx &&
        player_id.kind==GdVal::Kind::Int && player_id.i>=0 && player_id.i<2;
    if(!eligible) {
        if(watch.collect)native_timer_index_hit(4);
        targeted_timer_scan_items(items,0,count,delta);return;
    }
    auto*& pointer=watch.cache[unsigned(player_id.i)];
    auto* cache=static_cast<TargetedTimerCache*>(pointer);
    if(cache && cache->character!=character){targeted_timer_scan_items(items,0,count,delta);return;}
    if(!cache){cache=ctx.arena.make<TargetedTimerCache>();pointer=cache;}
    if(cache->version!=watch.version || cache->items!=items || cache->items_count!=count) {
        if(!targeted_timer_build(ctx,character,items,*cache)) {
            watch.usable=false;
            if(watch.collect)native_timer_index_hit(4);
            targeted_timer_scan_items(items,0,count,delta);return;
        }
    }else if(watch.collect)native_timer_index_hit(2);
    if(watch.collect)native_timer_index_hit(0);
    const auto version=watch.version;
    const auto* entries=cache->entries;const uint32_t length=cache->count;
    for(uint32_t k=0;k<length;++k) {
        // Copy before calling: a nested tick may replace this cache's storage.
        const auto entry=entries[k];
        if(watch.collect)native_timer_index_hit(3);
        if(entry.owner->f_timers.arr->len)entry.owner->fn__tickTimers(&delta,1);
        if(watch.version!=version || !watch.usable || watch.depth) {
            if(watch.collect)native_timer_index_hit(5);
            if(entry.gem_index==UINT32_MAX) {
                // The original item local survives replacement of its slot.
                const auto* gems=entry.owner->f_gems.arr;
                targeted_timer_scan_gems(gems,0,gems->len,delta);
            }else {
                // Keep the original gems object and captured sockets bound.
                targeted_timer_scan_gems(entry.gems,entry.gem_index+1,entry.sockets,delta);
            }
            targeted_timer_scan_items(items,entry.item_index+1,count,delta);return;
        }
    }
}
}
