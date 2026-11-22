// Appended once to engine_wrapper.cpp by the guarded transform.
#include "native_packed_display.hpp"
#include "native_targeted_timers.hpp"

namespace gd {
thread_local NativePackedDisplayScope* NativePackedDisplayScope::current_=nullptr;
static thread_local uint64_t native_default_display_counts[8]{};
void native_default_display_hit(unsigned n,uint64_t amount) {
    if(n<8)native_default_display_counts[n]+=amount;
}
namespace {
bool display_owned_array(BattleCtx& c,const GdVal& v,std::vector<GdArr*>& arrays) {
    if(v.kind!=GdVal::Kind::Arr || !v.arr ||
       !c.arena.owns_storage(v.arr,sizeof(GdArr)))return false;
    const auto* a=v.arr;
    if(a->len>a->cap || (a->timer_watch && a->timer_watch!=&c.native_timer_watch) ||
       (a->cap && !c.arena.owns_storage(a->data,size_t(a->cap)*sizeof(GdVal))))return false;
    arrays.push_back(v.arr);return true;
}
Gd__gd_core__CoreItem* display_owned_item(BattleCtx& c,const GdVal& v) {
    if(v.kind!=GdVal::Kind::Obj || !v.obj || v.obj->rt_ctx_!=&c ||
       !c.arena.owns_storage(v.obj,sizeof(Gd__gd_core__CoreItem)) ||
       !native_timer_known_object(v.obj))return nullptr;
    return dynamic_cast<Gd__gd_core__CoreItem*>(v.obj);
}
bool display_owned_defaults(BattleCtx& c,Gd__gd_core__CoreItem* item,std::vector<GdArr*>& arrays) {
    if(!display_owned_array(c,item->f_statDisplayOverrides,arrays))return false;
    const auto* a=item->f_statDisplayOverrides.arr;
    // Null reads have no FP, RNG, instance-ID or user-call effects to replay.
    for(uint32_t i=0;i<a->len;++i)if(a->data[i].kind!=GdVal::Kind::Null)return false;
    return true;
}
bool display_owned_side(BattleCtx& c,Gd__gd_core__CoreCharacter* chr,std::vector<GdArr*>& arrays) {
    if(!chr || chr->rt_ctx_!=&c || !c.arena.owns_storage(chr,sizeof(*chr)) ||
       !native_timer_known_object(chr))return false;
    const auto& v=chr->f_inventory;
    if(v.kind!=GdVal::Kind::Obj || !v.obj || v.obj->rt_ctx_!=&c ||
       !c.arena.owns_storage(v.obj,sizeof(Gd__gd_core__CoreGrid)) ||
       !native_timer_known_object(v.obj))return false;
    const auto* grid=dynamic_cast<Gd__gd_core__CoreGrid*>(v.obj);
    if(!grid || !display_owned_array(c,grid->f_items,arrays))return false;
    const auto* items=grid->f_items.arr;
    for(uint32_t i=0;i<items->len;++i) {
        auto* item=display_owned_item(c,items->data[i]);
        if(!item || !display_owned_defaults(c,item,arrays) ||
           !display_owned_array(c,item->f_gems,arrays))return false;
        const auto* gems=item->f_gems.arr;
        for(uint32_t j=0;j<gems->len;++j) {
            if(gems->data[j].kind==GdVal::Kind::Null)continue;
            auto* gem=display_owned_item(c,gems->data[j]);
            if(!gem || !display_owned_defaults(c,gem,arrays))return false;
        }
    }
    return true;
}
}
NativePackedDisplayScope::NativePackedDisplayScope(BattleCtx& c,
        Gd__gd_core__CoreCharacter* player,Gd__gd_core__CoreCharacter* opponent)
    :context_(&c),previous_(current_) {
    // Failed registration also shadows a previous same-context scope. No
    // watcher is attached until the complete live graph has been validated.
    auto& w=c.native_timer_watch;
    if(c.native_resolved_collect)native_default_display_hit(0);
    if(w.enabled && w.closed_world && w.usable && !w.depth &&
       w.version!=UINT64_MAX && native_timer_registry_closed()) {
        std::vector<GdArr*> arrays;
        if(display_owned_side(c,player,arrays) && display_owned_side(c,opponent,arrays)) {
            for(auto* a:arrays)a->timer_watch=&w;
            version_=w.version;epoch_=c.gid_epoch;
            if(c.native_resolved_collect) {
                native_default_display_hit(1);native_default_display_hit(2,arrays.size());
            }
        }
    }
    // Publish only after all potentially allocating validation has completed.
    // An allocation exception therefore leaves the previous TLS scope intact.
    current_=this;
}
NativePackedDisplayScope::~NativePackedDisplayScope() {
    // The bridge's arena owns all watched headers until reset, as for the
    // existing inventory/gem/timer watchers. No arena pointer is dereferenced
    // here, so an epoch change cannot restore stale headers or a stale view.
    current_=previous_;
}
uint64_t native_default_display_version(BattleCtx& c) {
    for(auto* s=NativePackedDisplayScope::current_;s;s=s->previous_) {
        if(s->context_!=&c)continue;
        const bool valid=native_default_display_valid(c,s->version_,s->epoch_);
        if(c.native_resolved_collect)native_default_display_hit(valid?3:5);
        return valid?s->version_:0;
    }
    if(c.native_resolved_collect)native_default_display_hit(6);
    return 0;
}
void native_default_display_field_changed(BattleCtx* c) {
    if(!c)return;
    bool invalidate=false;
    for(auto* s=NativePackedDisplayScope::current_;s;s=s->previous_)if(s->context_==c && s->version_) {
        invalidate|=s->epoch_==c->gid_epoch && s->version_==c->native_timer_watch.version;
        s->version_=0;
    }
    if(invalidate) {
        c->native_timer_watch.change();
        if(c->native_resolved_collect)native_default_display_hit(7);
    }
}
}
extern "C" uint64_t gd_diag_native_display_defaults_stat(unsigned n) {
    return n<8?gd::native_default_display_counts[n]:0;
}
