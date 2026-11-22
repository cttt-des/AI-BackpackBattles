#pragma once
#include "native_targeted_timers.hpp"

namespace gd {
struct ActiveCooldownEntry {
    Gd__gd_core__CoreItem* owner;
    const GdArr* gems;
    uint32_t item_index,gem_index,sockets;
};
struct ActiveCooldownCache {
    const Gd__gd_core__CoreCharacter* character=nullptr;
    const GdArr* items=nullptr;
    uint64_t structure=0,eligibility=0;
    const ActiveCooldownEntry* entries=nullptr;
    uint32_t count=0,items_count=0;
    const Gd__gd_core__CoreGrid* grid=nullptr;
};
inline void active_cooldown_count(BattleCtx& ctx,unsigned field,uint64_t amount=1) {
    if(ctx.native_resolved_collect)native_active_cooldown_hit(field,amount);
}
inline bool active_cooldown_truth(const GdVal& value) {
    if(value.kind==GdVal::Kind::Bool) [[likely]] return value.b;
    return gd_truth(value);
}
template<class ItemTick,class GemTick>
inline void active_cooldown_scan_gems(const GdArr* gems,uint32_t start,uint32_t sockets,
                                      ItemTick& item_tick,GemTick& gem_tick) {
    for(uint32_t j=start;j<sockets;++j) {
        const GdVal slot=gems->data[j];
        if(!slot.is_null()) {
            auto* gem=static_cast<Gd__gd_core__CoreItem*>(slot.obj);
            if(active_cooldown_truth(gem->f__cooldown_active))gem_tick(gem);
        }
    }
}
template<class ItemTick,class GemTick>
inline void active_cooldown_scan_items(const GdArr* items,uint32_t start,uint32_t count,
                                       ItemTick& item_tick,GemTick& gem_tick) {
    for(uint32_t i=start;i<count;++i) {
        const GdVal slot=items->data[i];
        auto* item=static_cast<Gd__gd_core__CoreItem*>(slot.obj);
        if(active_cooldown_truth(item->f__cooldown_active))item_tick(item);
        const GdVal gems_value=item->f_gems;
        const GdArr* gems=gems_value.kind==GdVal::Kind::Arr?gems_value.arr:nullptr;
        const uint32_t sockets=gems?gems->len:0;
        active_cooldown_scan_gems(gems,0,sockets,item_tick,gem_tick);
    }
}
inline Gd__gd_core__CoreItem* active_cooldown_owned_item(BattleCtx& ctx,const GdVal& value) {
    if(value.kind!=GdVal::Kind::Obj || !value.obj || value.obj->rt_ctx_!=&ctx ||
       !ctx.arena.owns_storage(value.obj,sizeof(Gd__gd_core__CoreItem)) ||
       !native_timer_known_object(value.obj))return nullptr;
    return dynamic_cast<Gd__gd_core__CoreItem*>(value.obj);
}
// No user methods, truth conversions, object allocations or RNG calls here.
// Every candidate flag must be Bool before any future flag is consumed early.
__attribute__((noinline)) inline bool active_cooldown_build(BattleCtx& ctx,
    Gd__gd_core__CoreCharacter* character,const GdArr* items,ActiveCooldownCache& cache) {
    uint64_t slots=items->len,active=0;
    if(!targeted_timer_watch_array(ctx,const_cast<GdArr*>(items)))return false;
    for(uint32_t i=0;i<items->len;++i) {
        auto* item=active_cooldown_owned_item(ctx,items->data[i]);
        if(!item || item->f__cooldown_active.kind!=GdVal::Kind::Bool ||
           item->f_gems.kind!=GdVal::Kind::Arr || !item->f_gems.arr ||
           !targeted_timer_watch_array(ctx,item->f_gems.arr))return false;
        active+=item->f__cooldown_active.b;
        const auto* gems=item->f_gems.arr;slots+=gems->len;
        if(slots>UINT32_MAX)return false;
        for(uint32_t j=0;j<gems->len;++j) {
            const auto& value=gems->data[j];
            if(value.is_null())continue;
            auto* gem=active_cooldown_owned_item(ctx,value);
            if(!gem || gem->f__cooldown_active.kind!=GdVal::Kind::Bool)return false;
            active+=gem->f__cooldown_active.b;
        }
    }
    // Fresh storage: a nested phase can rebuild the same player-id cache while
    // an outer phase still retains the previous ordered entries.
    auto* entries=ctx.arena.alloc_array<ActiveCooldownEntry>(size_t(active));uint32_t n=0;
    for(uint32_t i=0;i<items->len;++i) {
        auto* item=static_cast<Gd__gd_core__CoreItem*>(items->data[i].obj);
        if(item->f__cooldown_active.b)entries[n++]={item,nullptr,i,UINT32_MAX,0};
        const auto* gems=item->f_gems.arr;
        for(uint32_t j=0;j<gems->len;++j) {
            const auto& value=gems->data[j];
            if(value.kind==GdVal::Kind::Obj && value.obj) {
                auto* gem=static_cast<Gd__gd_core__CoreItem*>(value.obj);
                if(gem->f__cooldown_active.b)entries[n++]={gem,gems,i,j,gems->len};
            }
        }
    }
    auto& watch=ctx.native_timer_watch;
    cache={character,items,watch.version,watch.cooldown_version,entries,n,items->len,static_cast<const Gd__gd_core__CoreGrid*>(character->f_inventory.obj)};
    active_cooldown_count(ctx,1);active_cooldown_count(ctx,7,slots);active_cooldown_count(ctx,8,n);
    return true;
}
// False means no callback has run: the caller executes its unchanged original
// phase. Once an indexed callback runs, suffix recovery completes this phase.
template<class ItemTick,class GemTick>
inline bool active_cooldown_visit(BattleCtx& ctx,Gd__gd_core__CoreCharacter* character,
                                  ItemTick&& item_tick,GemTick&& gem_tick) {
    auto& watch=ctx.native_timer_watch;
    if(!watch.enabled || !watch.closed_world || !watch.usable || watch.depth ||
       watch.cooldown_version==UINT64_MAX || !character || character->rt_ctx_!=&ctx)return false;
    const auto& pid=character->f_playerId;
    if(pid.kind!=GdVal::Kind::Int || pid.i<0 || pid.i>1)return false;
    const auto& inventory=character->f_inventory;
    auto*& pointer=watch.cooldown_cache[unsigned(pid.i)];
    auto* cache=static_cast<ActiveCooldownCache*>(pointer);
    // A cache hit has already proved the complete owned object/array graph.
    // Tracked structure writes and every eligibility store invalidate it;
    // live inventory/items identity and length checks also retain raw-field
    // replacements used by direct C++ callers. Reset clears all cache pointers.
    const bool hit=cache && cache->character==character && cache->grid &&
        cache->structure==watch.version && cache->eligibility==watch.cooldown_version &&
        inventory.kind==GdVal::Kind::Obj && inventory.obj==cache->grid &&
        cache->grid->f_items.kind==GdVal::Kind::Arr && cache->grid->f_items.arr==cache->items &&
        cache->items && cache->items->len==cache->items_count;
    const GdArr* items=nullptr;uint32_t count=0;
    if(hit) {
        items=cache->items;count=cache->items_count;active_cooldown_count(ctx,2);
    }else {
        if(!ctx.arena.owns_storage(character,sizeof(*character)) ||
           inventory.kind!=GdVal::Kind::Obj || !inventory.obj || inventory.obj->rt_ctx_!=&ctx ||
           !ctx.arena.owns_storage(inventory.obj,sizeof(Gd__gd_core__CoreGrid)) ||
           !native_timer_known_object(inventory.obj))return false;
        auto* grid=dynamic_cast<Gd__gd_core__CoreGrid*>(inventory.obj);
        if(!grid || grid->f_items.kind!=GdVal::Kind::Arr || !grid->f_items.arr)return false;
        items=grid->f_items.arr;count=items->len;
        if(!cache){cache=ctx.arena.make<ActiveCooldownCache>();pointer=cache;}
        if(!active_cooldown_build(ctx,character,items,*cache)) {
            active_cooldown_count(ctx,4);return false;
        }
    }
    active_cooldown_count(ctx,0);
    const auto structure=watch.version,eligibility=watch.cooldown_version;
    const auto* entries=cache->entries;const uint32_t length=cache->count;
    for(uint32_t k=0;k<length;++k) {
        const auto entry=entries[k];
        active_cooldown_count(ctx,3);
        // Entry eligibility is Bool true; any intervening tracked store is
        // detected immediately after the preceding callback and resumes the
        // original suffix. The physical tick still retains its own checks.
        if(entry.gem_index==UINT32_MAX)item_tick(entry.owner);else gem_tick(entry.owner);
        if(watch.version!=structure || watch.cooldown_version!=eligibility ||
           !watch.usable || watch.depth || !watch.enabled || !watch.closed_world) {
            active_cooldown_count(ctx,5);
            if(entry.gem_index==UINT32_MAX) {
                const GdVal value=entry.owner->f_gems;
                const auto* gems=value.kind==GdVal::Kind::Arr?value.arr:nullptr;
                active_cooldown_scan_gems(gems,0,gems?gems->len:0,item_tick,gem_tick);
            }else active_cooldown_scan_gems(entry.gems,entry.gem_index+1,entry.sockets,item_tick,gem_tick);
            active_cooldown_scan_items(items,entry.item_index+1,count,item_tick,gem_tick);
            return true;
        }
    }
    return true;
}
inline bool active_cooldown_phase(BattleCtx& ctx,Gd__gd_core__CoreCharacter* character,
                                  NativeFrameSegmentSnapshot& snapshot,const GdVal& delta) {
    const NativeDefaultDisplayToken display_defaults{&ctx,native_default_display_version(ctx),ctx.gid_epoch};
    const auto* display_token=display_defaults.version?&display_defaults:nullptr;
    return active_cooldown_visit(ctx,character,
        [&](Gd__gd_core__CoreItem* item){native_frame_segment_tick(item,snapshot,delta,display_token);},
        [&](Gd__gd_core__CoreItem* gem){snapshot.clear();gem->fn_physicsTick(&delta,1);});
}
}
