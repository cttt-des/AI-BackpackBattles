"""Index cooldown-bearing native parents while preserving callback-visible order."""
import argparse
import hashlib
from pathlib import Path
import re

from optimize_native_inline_timers import FLAG as INLINE_FLAG
from optimize_native_sparse_timers import DECLARATIONS as TIMER_DECLARATIONS, RUNTIME as TIMER_RUNTIME
from probe_native_selective_timer_scan import replace_one


def names(source):
    return source.replace('native_scan_state','native_cooldown_storage').replace('NativeTimer','NativeCooldown').replace('native_timer','native_cooldown').replace('native_sparse_timer','native_sparse_cooldown').replace('native_scan','native_cooldown_scan')


INPUT_SHA256 = {'gd_rt.hpp': 'bf6ee43ba5c5a40ced3b217602b01444b5324ecabd4977ba42e13266c52903e0', 'gd_rt.cpp': '63dc2c0e53827722349a306430930caef50640d334fc527764ad1ae0dddac8ac', 'engine_wrapper.cpp': '1dd69d3aa317890b1be03e1e65acb837322ce8ca0c4cbdcbacf85a8aabd45a88', 'gen/hdrs/Gd__gd_core__CoreCombat.hpp': '09ebcad23c2b0917480f8495ecd1ab0ff5b5c0ee08cc7ef4ca04c67d20aca32b', 'gen/shards/shard_00.cpp': 'e39d297289c832f5237609815630ba3cc4bd435345572c04114bfb42e2d1bced', 'gen/shards/shard_03.cpp': '8d7c84ec9a22f4305b9d848e5c80c52e15e7702313349a5592ae379b4b70f3bf'}
OUTPUT_SHA256 = {'gd_rt.hpp': '70e17a6b931705d0fa85baa0772047bc1868cb7219d0dceb935286a0c0ebbc20', 'gd_rt.cpp': 'cc7bb68ddc528b69de1f014da57d9e0a45950969164311f586257a1ea7f2761d', 'engine_wrapper.cpp': '5177ea37dc3f2ce4c88b12afe0f924668be8700756a1909035e338d6de02a1fe', 'gen/hdrs/Gd__gd_core__CoreCombat.hpp': 'd4c3c179a3d70e1a150c23c5b2d33352f09e19466cc65bef4763d748b42b1350', 'gen/shards/shard_00.cpp': 'a3434df589b5f3ed3ce6b657566df05db67f61959d87efbe457c407a54ab8be1', 'gen/shards/shard_03.cpp': 'a6e09816b36079ee10faf53200e2857608fbf5e69432eeca29f84abc675029fa'}
CURSOR_SHA256 = 'c987b914f23c99bfd671af7472e93231fc3f0bc058a6ec74eb348eebbacd454c'

DECLARATIONS=names(TIMER_DECLARATIONS)+'''
void native_cooldown_scan_assignment(BattleCtx& context, const GdVal& before, const GdVal& after);
'''
RUNTIME=names(TIMER_RUNTIME)+'''
void native_cooldown_scan_assignment(BattleCtx& context, const GdVal& before, const GdVal& after) {
    if(!context.native_sparse_cooldown_scans) return;
    if(before.kind==GdVal::Kind::Bool && after.kind==GdVal::Kind::Bool && before.b==after.b) return;
    advance_native_cooldown_scan_epoch();
}
'''
CURSOR='''#pragma once
#include "gd_rt.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"

namespace gd {
namespace native_cooldown_detail {
inline const Gd__gd_core__CoreItem* item(BattleCtx& battle,const GdVal& value) {
    if(value.kind!=GdVal::Kind::Obj || !value.obj ||
       !battle.arena.owns_storage(value.obj,sizeof(Gd__gd_core__CoreItem)))return nullptr;
    if(!value.obj->meta()->is_subclass_of(&META_Gd__gd_core__CoreItem))return nullptr;
    return static_cast<const Gd__gd_core__CoreItem*>(value.obj);
}
inline bool active(BattleCtx& battle,const GdVal& slot) {
    const auto* parent=item(battle,slot);
    if(!parent || parent->f__cooldown_active.kind!=GdVal::Kind::Bool || parent->f__cooldown_active.b)return true;
    const auto gems=parent->f_gems;
    if(gems.kind!=GdVal::Kind::Arr || !gems.arr || !gems.arr->native_cooldown_scan_tracked)return true;
    for(uint32_t j=0;j<gems.arr->len;++j) {
        const auto& value=gems.arr->data[j];
        if(value.is_null())continue;
        const auto* gem=item(battle,value);
        if(!gem || gem->f__cooldown_active.kind!=GdVal::Kind::Bool || gem->f__cooldown_active.b)return true;
    }
    return false;
}
// Keep the rare rebuild out of the frame loop's instruction footprint.
__attribute__((noinline)) inline void rebuild(BattleCtx& battle,NativeCooldownScanCache& cache,
                                             const GdArr* items,uint32_t count,uint64_t epoch) {
    if(cache.capacity<count) {
        cache.indices=battle.arena.alloc_array<uint32_t>(count);cache.capacity=count;
    }
    cache.count=0;
    for(uint32_t i=0;i<count;++i)if(active(battle,items->data[i]))cache.indices[cache.count++]=i;
    cache.items=items;cache.context=&battle;cache.generation=battle.gid_epoch;
    cache.length=count;cache.epoch=epoch;
}
}

class NativeCooldownCursor {
    NativeCooldownScanState* state_=nullptr;
    const uint32_t* indices_=nullptr;
    uint64_t epoch_=0;
    uint32_t count_, cursor_=0, position_=0, eligible_=0;
    bool indexed_=false;
public:
    NativeCooldownCursor(BattleCtx& battle,NativeCooldownScanCache& cache,const GdArr* items,uint32_t count)
        :count_(count) {
        if(!battle.native_sparse_cooldown_scans)return;
        state_=&native_cooldown_scan_state();
        indexed_=!state_->depth && !state_->sorting && state_->epoch!=UINT64_MAX && items;
        ++state_->depth;
        if(!indexed_)return;
        if(!items->native_cooldown_scan_tracked)
            native_cooldown_scan_mark(battle,GdVal::from_arr(const_cast<GdArr*>(items)));
        epoch_=state_->epoch;
        if(cache.items!=items || cache.context!=&battle || cache.generation!=battle.gid_epoch ||
           cache.length!=count || cache.epoch!=epoch_)
            native_cooldown_detail::rebuild(battle,cache,items,count,epoch_);
        // Nested callbacks may reset the combat/cache; retain this phase's arena buffer.
        indices_=cache.indices;eligible_=cache.count;
    }
    ~NativeCooldownCursor(){if(state_)--state_->depth;}
    NativeCooldownCursor(const NativeCooldownCursor&)=delete;
    NativeCooldownCursor& operator=(const NativeCooldownCursor&)=delete;
    inline uint32_t next() {
        if(indexed_ && state_->epoch!=epoch_)indexed_=false;
        if(indexed_) {
            if(position_==eligible_)return count_;
            const auto next=indices_[position_++];cursor_=next+1;return next;
        }
        return cursor_++;
    }
};
}
'''


def optimize(native):
    actual={name:hashlib.sha256((native/name).read_bytes()).hexdigest() for name in INPUT_SHA256}
    extra=native/'native_cooldown_scan.hpp'
    if actual==OUTPUT_SHA256 and extra.is_file() and hashlib.sha256(extra.read_bytes()).hexdigest()==CURSOR_SHA256:
        print('Verified sparse cooldown pass already applied',flush=True);return
    if actual!=INPUT_SHA256 or extra.exists():
        raise ValueError('Sparse cooldown sources differ from the verified input/output versions')
    path=native/'gd_rt.hpp';s=path.read_text('utf8')
    if 'native_sparse_cooldown_scans' in s:raise ValueError('Use fresh verified sources')
    s=replace_one(s,'    bool is_pool_real = false;\n','    bool is_pool_real = false;\n    bool native_cooldown_scan_tracked = false;\n')
    s=replace_one(s,INLINE_FLAG,'    bool native_sparse_cooldown_scans = false;\n\n'+INLINE_FLAG)
    s=replace_one(s,'        native_inline_timer_headers = false;\n','        native_inline_timer_headers = false;\n        native_sparse_cooldown_scans = false;\n')
    s=replace_one(s,'// Uniform Variant property / subscript / call helpers\n',DECLARATIONS+'\n// Uniform Variant property / subscript / call helpers\n')
    path.write_text(s,encoding='utf8',newline='\n')
    path=native/'gd_rt.cpp';s=path.read_text('utf8')
    s=replace_one(s,'GdArr* GdArr::create(BattleArena& arena, uint32_t reserve_cap) {',RUNTIME+'\nGdArr* GdArr::create(BattleArena& arena, uint32_t reserve_cap) {')
    for method in ('push_back','insert_at','pop_at','append_array','pop_front','pop_back','remove_at','erase_val','resize','fill','invert','set_idx'):
        s,count=re.subn(rf'^((?:void|GdVal) GdArr::{method}\([^\n]*\{{)\n',r'\1\n    native_cooldown_scan_mutated(this);\n',s,flags=re.M)
        if count!=1:raise ValueError(f'Unexpected array mutator {method}')
    s=replace_one(s,'case SYM_clear: a->len = 0;','case SYM_clear: native_cooldown_scan_mutated(a); a->len = 0;')
    for signature in ('void shuffle_array(BattleCtx& ctx, GdArr* arr) {',
                      'void godot_sort_custom_items(BattleCtx& ctx, GdArr* arr) {',
                      'void sort_custom_stable(BattleCtx& ctx, GdArr* arr, GdObj* obj, SymId method) {'):
        extra='    native_cooldown_scan_mutated(arr);\n' if 'shuffle_array' in signature else '    NativeCooldownSortScope native_sort_scope(arr);\n'
        s=replace_one(s,signature+'\n',signature+'\n'+extra)
    path.write_text(s,encoding='utf8',newline='\n')
    path=native/'gen/shards/shard_00.cpp';s=path.read_text('utf8')
    gems='    this->f_gems = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));\n'
    s=replace_one(s,gems,gems+'    gd::native_cooldown_scan_mark(gd_ctx,this->f_gems);\n')
    old='case SYM_GEN_gems_41: this->f_gems = val; return true;'
    s=replace_one(s,old,'case SYM_GEN_gems_41: this->f_gems = val; gd::native_cooldown_scan_mark(gd_ctx,this->f_gems); return true;')
    for value in ('gd::GdVal::from_bool(false)','val','lv_active'):
        anchor=f'this->f__cooldown_active = {value};'
        assert s.count(anchor)==(2 if value.endswith('(false)') else 1)
        s=s.replace(anchor,f'gd::native_cooldown_scan_assignment(gd_ctx,this->f__cooldown_active,{value}); '+anchor)
    path.write_text(s,encoding='utf8',newline='\n')
    path=native/'engine_wrapper.cpp';s=path.read_text('utf8')
    s=replace_one(s,'    battle.native_inline_timer_headers = true;\n','    battle.native_inline_timer_headers = true;\n    battle.native_sparse_cooldown_scans = true;\n')
    gems='    ci->f_gems = gd::GdVal::from_arr(gems_arr);\n'
    s=replace_one(s,gems,gems+'    gd::native_cooldown_scan_mark(battle,ci->f_gems);\n')
    path.write_text(s,encoding='utf8',newline='\n')
    path=native/'gen/hdrs/Gd__gd_core__CoreCombat.hpp';s=path.read_text('utf8')
    s=replace_one(s,'    gd::GdVal f__pending_deferred;\n','    gd::GdVal f__pending_deferred;\n    gd::NativeCooldownScanCache native_cooldown_scan_caches_[2];\n')
    path.write_text(s,encoding='utf8',newline='\n')
    path=native/'gen/shards/shard_03.cpp';s=path.read_text('utf8')
    anchor='void Gd__gd_core__CoreCombat::init_fields(gd::BattleCtx& gd_ctx) {\n'
    s=replace_one(s,anchor,anchor+'    for(auto& cache:this->native_cooldown_scan_caches_)cache={};\n')
    for slot,array,length,index in ((0,'_t757','_len__t758','_t758'),(1,'_t763','_len__t764','_t764')):
        old=f'        for (uint32_t {index} = 0; {index} < {length}; ++{index}) {{\n'
        new=f'        gd::NativeCooldownCursor native_scan_{slot}(gd_ctx,this->native_cooldown_scan_caches_[{slot}],{array},{length});\n        for (uint32_t {index} = native_scan_{slot}.next(); {index} < {length}; {index} = native_scan_{slot}.next()) {{\n'
        s=replace_one(s,old,new)
    path.write_text('#include "../../native_cooldown_scan.hpp"\n'+s,encoding='utf8',newline='\n')
    path=native/'native_cooldown_scan.hpp';assert not path.exists();path.write_text(CURSOR,encoding='utf8',newline='\n')
    print('Sparse cooldown parents: original bodies, live state invalidation, dense remainder and sort/reentry guards',flush=True)


if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('native',type=Path);optimize(p.parse_args().native)
