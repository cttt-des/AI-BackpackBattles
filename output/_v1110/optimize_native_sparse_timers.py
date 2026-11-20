"""Index timer-bearing native parents, with ordered dense fallback after mutation."""
import argparse
import hashlib
from pathlib import Path
import re

from optimize_native_inline_timers import FLAG as INLINE_FLAG, NEW_ASSIGN
from optimize_native_serial_paths import method_body

INPUT_SHA256 = {'gd_rt.hpp': 'bf6ee43ba5c5a40ced3b217602b01444b5324ecabd4977ba42e13266c52903e0', 'gd_rt.cpp': '63dc2c0e53827722349a306430930caef50640d334fc527764ad1ae0dddac8ac', 'engine_wrapper.cpp': '1dd69d3aa317890b1be03e1e65acb837322ce8ca0c4cbdcbacf85a8aabd45a88', 'gen/hdrs/Gd__gd_core__CoreCharacter.hpp': '0f68f644e9cbe6523d8bf87fcfc917f956fe0e5351a2ff6893ea74fdc01f1b14', 'gen/shards/shard_00.cpp': 'e39d297289c832f5237609815630ba3cc4bd435345572c04114bfb42e2d1bced', 'gen/shards/shard_02.cpp': 'f8696da573e296e8cfaee470d29d36e309f3d84ce77d4cfd0c5942fd611bee8f', 'gen/shards/shard_03.cpp': '8d7c84ec9a22f4305b9d848e5c80c52e15e7702313349a5592ae379b4b70f3bf'}
OUTPUT_SHA256 = {'gd_rt.hpp': 'ac3fbd1ae7cefdd697072747b62abc7c8ea6b5cd097c9a6906646bf95e0e7357', 'gd_rt.cpp': '3c1bb948ca67552b86e1a88c296592c6b1ba945e6d418a00a919bf6cf0be6343', 'engine_wrapper.cpp': '31f83ad838d323aebc98c908635539de8963629f98084d4aab2c4cb7ee5b0685', 'gen/hdrs/Gd__gd_core__CoreCharacter.hpp': '9c1f8b60858a607eb6b433b5140d290f9e656edc0b5f9d7c1a90ed89b5141222', 'gen/shards/shard_00.cpp': '6c2d889b27391e5e1f27ce1888bac80cc0088dc64db4f4065efd2243380b5b1f', 'gen/shards/shard_02.cpp': '83b32e97e1bde7cc311a6f763e5373890727a712400ca62332b836bcfedc287a', 'gen/shards/shard_03.cpp': '067f8b6a822caeb1d93b042681d3ab72c70caf196591ad150f3baf39dee83bd8'}

DECLARATIONS = '''
struct NativeTimerScanState {
    uint64_t epoch = 1;
    unsigned depth = 0;
    unsigned sorting = 0;
};
struct NativeTimerScanCache {
    const GdArr* items = nullptr;
    const BattleCtx* context = nullptr;
    uint64_t generation = 0, epoch = 0;
    uint32_t length = 0, count = 0, capacity = 0;
    uint32_t* indices = nullptr;
};
NativeTimerScanState& native_timer_scan_state();
void native_timer_scan_mutated(const GdArr* array);
void native_timer_scan_mark(BattleCtx& context, const GdVal& value);
'''
RUNTIME = '''
namespace {
thread_local NativeTimerScanState native_scan_state;
void advance_native_scan_epoch() {
    if (native_scan_state.epoch != UINT64_MAX) ++native_scan_state.epoch;
}
struct NativeTimerSortScope {
    GdArr* array;
    explicit NativeTimerSortScope(GdArr* value) : array(value) {
        ++native_scan_state.sorting;
        native_timer_scan_mutated(array);
    }
    ~NativeTimerSortScope() {
        native_timer_scan_mutated(array);
        --native_scan_state.sorting;
    }
};
}
NativeTimerScanState& native_timer_scan_state() { return native_scan_state; }
void native_timer_scan_mutated(const GdArr* array) {
    if (array && array->native_timer_scan_tracked) advance_native_scan_epoch();
}
void native_timer_scan_mark(BattleCtx& context, const GdVal& value) {
    if (!context.native_sparse_timer_scans) return;
    if (value.kind == GdVal::Kind::Arr && value.arr) value.arr->native_timer_scan_tracked=true;
    advance_native_scan_epoch();
}
'''
HELPERS = '''
namespace {
// The bridge owns its item objects until the entire battle arena is reset.
// Unknown/future placeholders stay eligible; do not dereference them early.
const Gd__gd_core__CoreItem* native_scan_item(gd::BattleCtx& battle, const gd::GdVal& slot) {
    if (slot.kind != gd::GdVal::Kind::Obj || !slot.obj ||
        !battle.arena.owns_storage(slot.obj, sizeof(Gd__gd_core__CoreItem))) return nullptr;
    if (!slot.obj->meta()->is_subclass_of(&META_Gd__gd_core__CoreItem)) return nullptr;
    return static_cast<const Gd__gd_core__CoreItem*>(slot.obj);
}
bool native_scan_has_timers(gd::BattleCtx& battle, const gd::GdVal& slot) {
    const auto* item=native_scan_item(battle,slot);
    if (!item) return true;
    const auto timers=item->f_timers;
    const auto gems=item->f_gems;
    if (timers.kind!=gd::GdVal::Kind::Arr || !timers.arr ||
        !timers.arr->native_timer_scan_tracked || timers.arr->len) return true;
    if (gems.kind!=gd::GdVal::Kind::Arr || !gems.arr ||
        !gems.arr->native_timer_scan_tracked) return true;
    for(uint32_t j=0;j<gems.arr->len;++j) {
        const auto& gem_slot=gems.arr->data[j];
        if(gem_slot.kind!=gd::GdVal::Kind::Obj || !gem_slot.obj) continue;
        const auto* gem=native_scan_item(battle,gem_slot);
        if(!gem || gem->f_timers.kind!=gd::GdVal::Kind::Arr || !gem->f_timers.arr ||
           !gem->f_timers.arr->native_timer_scan_tracked || gem->f_timers.arr->len) return true;
    }
    return false;
}
struct NativeTimerKernelScope {
    gd::NativeTimerScanState* state;
    explicit NativeTimerKernelScope(gd::NativeTimerScanState* value):state(value) {if(state)++state->depth;}
    ~NativeTimerKernelScope() {if(state)--state->depth;}
};
}
'''
PREPARE = '''    auto& battle=*this->rt_ctx_;
    auto* state=battle.native_sparse_timer_scans ? &gd::native_timer_scan_state() : nullptr;
    bool indexed=state && !state->depth && !state->sorting && state->epoch!=UINT64_MAX;
    NativeTimerKernelScope kernel(state);
    const uint32_t count=items->len;
    const uint32_t* indices=nullptr;
    uint32_t eligible_count=0;
    uint64_t scan_epoch=0;
    if(indexed) {
        if(!items->native_timer_scan_tracked)
            gd::native_timer_scan_mark(battle,gd::GdVal::from_arr(const_cast<gd::GdArr*>(items)));
        scan_epoch=state->epoch;
        auto& cache=character->native_timer_scan_cache_;
        if(cache.items!=items || cache.context!=&battle || cache.generation!=battle.gid_epoch ||
           cache.length!=count || cache.epoch!=scan_epoch) {
            if(cache.capacity<count) {
                cache.indices=battle.arena.alloc_array<uint32_t>(count);
                cache.capacity=count;
            }
            cache.count=0;
            for(uint32_t i=0;i<count;++i)
                if(native_scan_has_timers(battle,items->data[i])) cache.indices[cache.count++]=i;
            cache.items=items;cache.context=&battle;cache.generation=battle.gid_epoch;
            cache.length=count;cache.epoch=scan_epoch;
        }
        // A nested callback may reset the character/cache. Keep this phase's buffer.
        indices=cache.indices;eligible_count=cache.count;
    }
    uint32_t cursor=0, position=0;
    while(cursor<count) {
        if(indexed && state->epoch!=scan_epoch) indexed=false;
        uint32_t i=cursor;
        if(indexed) {
            if(position==eligible_count) break;
            i=indices[position++];
        }
        cursor=i+1;
'''


def replace_one(source, old, new):
    if source.count(old)!=1: raise ValueError(f"Expected one anchor: {old[:100]}")
    return source.replace(old,new,1)


def optimize(native):
    actual={name:hashlib.sha256((native/name).read_bytes()).hexdigest() for name in INPUT_SHA256}
    if actual==OUTPUT_SHA256:
        print('Verified sparse timer pass already applied',flush=True);return
    if actual!=INPUT_SHA256:
        raise ValueError('Sparse timer source differs from the verified input/output versions')
    header_path=native/'gd_rt.hpp';header=header_path.read_text('utf8')
    if 'native_sparse_timer_scans' in header: raise ValueError('Use fresh verified sources')
    header=replace_one(header,'    bool is_pool_real = false;\n','    bool is_pool_real = false;\n    bool native_timer_scan_tracked = false;\n')
    header=replace_one(header,INLINE_FLAG,'    bool native_sparse_timer_scans = false;\n\n'+INLINE_FLAG)
    header=replace_one(header,'        native_inline_timer_headers = false;\n','        native_inline_timer_headers = false;\n        native_sparse_timer_scans = false;\n')
    header=replace_one(header,'// Uniform Variant property / subscript / call helpers\n',DECLARATIONS+'\n// Uniform Variant property / subscript / call helpers\n')
    header_path.write_text(header,encoding='utf8',newline='\n')

    path=native/'gd_rt.cpp';source=path.read_text('utf8')
    source=replace_one(source,'GdArr* GdArr::create(BattleArena& arena, uint32_t reserve_cap) {',RUNTIME+'\nGdArr* GdArr::create(BattleArena& arena, uint32_t reserve_cap) {')
    for method in ('push_back','insert_at','pop_at','append_array','pop_front','pop_back','remove_at','erase_val','resize','fill','invert','set_idx'):
        source,count=re.subn(rf'^((?:void|GdVal) GdArr::{method}\([^\n]*\{{)\n',r'\1\n    native_timer_scan_mutated(this);\n',source,flags=re.M)
        if count!=1:raise ValueError(f'Unexpected array mutation method: {method}')
    source=replace_one(source,'case SYM_clear: a->len = 0;','case SYM_clear: native_timer_scan_mutated(a); a->len = 0;')
    for signature in ('void shuffle_array(BattleCtx& ctx, GdArr* arr) {',
                      'void godot_sort_custom_items(BattleCtx& ctx, GdArr* arr) {',
                      'void sort_custom_stable(BattleCtx& ctx, GdArr* arr, GdObj* obj, SymId method) {'):
        addition='    native_timer_scan_mutated(arr);\n' if 'shuffle_array' in signature else '    NativeTimerSortScope native_sort_scope(arr);\n'
        source=replace_one(source,signature+'\n',signature+'\n'+addition)
    path.write_text(source,encoding='utf8',newline='\n')

    path=native/'gen/shards/shard_00.cpp';source=path.read_text('utf8')
    gems='    this->f_gems = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));\n'
    source=replace_one(source,gems,gems+'    gd::native_timer_scan_mark(gd_ctx,this->f_gems);\n')
    source=replace_one(source,NEW_ASSIGN,NEW_ASSIGN+'    gd::native_timer_scan_mark(gd_ctx,this->f_timers);\n')
    for field,symbol in (('gems','SYM_GEN_gems_41'),('timers','SYM_GEN_timers_67')):
        old=f'case {symbol}: this->f_{field} = val; return true;'
        source=replace_one(source,old,f'case {symbol}: this->f_{field} = val; gd::native_timer_scan_mark(gd_ctx,this->f_{field}); return true;')
    path.write_text(source,encoding='utf8',newline='\n')
    path=native/'engine_wrapper.cpp';source=path.read_text('utf8')
    source=replace_one(source,'    battle.native_inline_timer_headers = true;\n','    battle.native_inline_timer_headers = true;\n    battle.native_sparse_timer_scans = true;\n')
    gems='    ci->f_gems = gd::GdVal::from_arr(gems_arr);\n'
    source=replace_one(source,gems,gems+'    gd::native_timer_scan_mark(battle,ci->f_gems);\n')
    path.write_text(source,encoding='utf8',newline='\n')
    path=native/'gen/hdrs/Gd__gd_core__CoreCharacter.hpp';source=path.read_text('utf8')
    source=replace_one(source,'    gd::GdVal f_ctx;\n','    gd::NativeTimerScanCache native_timer_scan_cache_;\n    gd::GdVal f_ctx;\n')
    path.write_text(source,encoding='utf8',newline='\n')
    path=native/'gen/shards/shard_02.cpp';source=path.read_text('utf8')
    anchor='void Gd__gd_core__CoreCharacter::init_fields(gd::BattleCtx& gd_ctx) {\n'
    source=replace_one(source,anchor,anchor+'    this->native_timer_scan_cache_ = {};\n')
    path.write_text(source,encoding='utf8',newline='\n')
    path=native/'gen/shards/shard_03.cpp';source=path.read_text('utf8')
    method=method_body(source,'CoreCombat','_tickCharacterTimers')
    old='    for (uint32_t i = 0, count = items->len; i < count; ++i) {\n'
    body=replace_one(method[0],old,PREPARE)
    source=source[:method.start()]+body+source[method.end():]
    source='#include "../../gd_rt.hpp"\n#include "../hdrs/Gd__gd_core__CoreItem.hpp"\n'+HELPERS+source
    path.write_text(source,encoding='utf8',newline='\n')
    print('Sparse timer parents: tracked aliases, ordered dirty fallback, sort/reentry guards',flush=True)


if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('native',type=Path)
    optimize(parser.parse_args().native)
