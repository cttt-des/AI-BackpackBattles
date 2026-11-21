"""Re-evaluate sparse timer parents with exact generated allocation row seeding."""
import hashlib
import json
from pathlib import Path
import re
from optimize_native_sparse_timers import DECLARATIONS,RUNTIME,HELPERS,PREPARE
from optimize_native_inline_timers import FLAG,NEW_ASSIGN

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'native_perf50/scan_bundle'

def replace(text,old,new):
    assert text.count(old)==1,old[:100]
    return text.replace(old,new,1)

def optimize(native):
    expected=json.loads((BASE/'source_before_build.json').read_bytes())
    actual={p.relative_to(native).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in native.rglob('*') if p.is_file()}
    assert actual==expected,'Use the complete accepted704-source baseline'
    path=native/'gd_rt.hpp';text=path.read_text('utf8')
    text=replace(text,'    bool is_pool_real = false;\n','    bool is_pool_real = false;\n    bool native_timer_scan_tracked = false;\n')
    anchor='    bool native_inline_timer_headers = false;\n'
    text=replace(text,anchor,'    bool native_sparse_timer_scans = false;\n\n'+anchor)
    text=replace(text,'        native_inline_timer_headers = false;\n','        native_inline_timer_headers = false;\n        native_sparse_timer_scans = false;\n')
    cache_declarations=replace(DECLARATIONS,'    uint32_t* indices = nullptr;\n};',
        '''    uint32_t* indices = nullptr;
    NativeTimerScanCache() = default;
    NativeTimerScanCache(const NativeTimerScanCache&) {}
    NativeTimerScanCache& operator=(const NativeTimerScanCache&) {
        items=nullptr;context=nullptr;generation=epoch=0;
        length=count=capacity=0;indices=nullptr;return *this;
    }
};''')
    declarations=cache_declarations+'''
void native_resolved_seed(GdObj*,unsigned);
bool native_resolved_cached_generated(const BattleCtx&,const GdObj*);
bool native_resolved_generated_class(const GdClassMeta*);
void native_timer_scan_external(BattleCtx&);
void native_timer_scan_before_object(BattleCtx&,GdObj*);
void native_timer_scan_before_class(BattleCtx&,const GdClassMeta*);
'''
    text=replace(text,'// Uniform Variant property / subscript / call helpers\n',declarations+'\n// Uniform Variant property / subscript / call helpers\n')
    path.write_text(text,encoding='utf8',newline='\n')

    path=native/'gd_rt.cpp';text=path.read_text('utf8')
    runtime=RUNTIME+'''
void native_timer_scan_external(BattleCtx& context) {
    if(context.native_sparse_timer_scans) advance_native_scan_epoch();
}
void native_timer_scan_before_object(BattleCtx& context,GdObj* object) {
    if(context.native_sparse_timer_scans && object &&
       !native_resolved_cached_generated(context,object)) advance_native_scan_epoch();
}
void native_timer_scan_before_class(BattleCtx& context,const GdClassMeta* type) {
    if(context.native_sparse_timer_scans && type &&
       !native_resolved_generated_class(type)) advance_native_scan_epoch();
}
void native_timer_scan_validity_probe(GdObj* object) {
    if(object && (!object->rt_ctx_ ||
       !native_resolved_cached_generated(*object->rt_ctx_,object))) advance_native_scan_epoch();
}
'''
    text=replace(text,'GdArr* GdArr::create(BattleArena& arena, uint32_t reserve_cap) {',runtime+'\nGdArr* GdArr::create(BattleArena& arena, uint32_t reserve_cap) {')
    for method in ('push_back','insert_at','pop_at','append_array','pop_front','pop_back','remove_at','erase_val','resize','fill','invert','set_idx'):
        text,count=re.subn(rf'^((?:void|GdVal) GdArr::{method}\([^\n]*\{{)\n',r'\1\n    native_timer_scan_mutated(this);\n',text,flags=re.M)
        assert count==1,method
    text=replace(text,'case SYM_clear: a->len = 0;','case SYM_clear: native_timer_scan_mutated(a); a->len = 0;')
    for signature in ('void shuffle_array(BattleCtx& ctx, GdArr* arr) {','void godot_sort_custom_items(BattleCtx& ctx, GdArr* arr) {','void sort_custom_stable(BattleCtx& ctx, GdArr* arr, GdObj* obj, SymId method) {'):
        extra='    native_timer_scan_mutated(arr);\n' if 'shuffle_array' in signature else '    NativeTimerSortScope native_sort_scope(arr);\n'
        text=replace(text,signature+'\n',signature+'\n'+extra)
    # Unknown C++ callbacks may write public fields or array data directly, without
    # the generated setters. Invalidate before entry, even outside an active scan.
    text=replace(text,'GdVal get_prop(BattleCtx& ctx, const GdVal& recv, SymId prop) {',
        '''GdVal get_prop(BattleCtx& ctx, const GdVal& recv, SymId prop) {
    if(recv.kind==GdVal::Kind::Obj) native_timer_scan_before_object(ctx,recv.obj);
    else if(recv.kind==GdVal::Kind::ClassRef) native_timer_scan_before_class(ctx,recv.cls);''')
    text=replace(text,'void set_prop(BattleCtx& ctx, GdVal& recv, SymId prop, const GdVal& val) {',
        '''void set_prop(BattleCtx& ctx, GdVal& recv, SymId prop, const GdVal& val) {
    if(recv.kind==GdVal::Kind::Obj) native_timer_scan_before_object(ctx,recv.obj);''')
    # Runtime object dispatch and FuncRef's two bind/no-bind fallbacks.
    pattern=r'(?m)^(\s*)(if \(!try_native_resolved_dispatch\([^\n]+\))\n(\s*)([^\n]*instance->call_method\([^\n]+;)'
    def funcref(m):
        return m[1]+m[2]+' {\n'+m[3]+'native_timer_scan_before_object(ctx,instance);\n'+m[3]+m[4]+'\n'+m[1]+'}'
    text,count=re.subn(pattern,funcref,text);assert count==2,count
    text=replace(text,'return instance != nullptr && method != SYM_NONE && instance->has_own_method(method);',
        'return instance != nullptr && method != SYM_NONE && (native_timer_scan_validity_probe(instance), instance->has_own_method(method));')
    anchor='            if (recv.obj->call_method(ctx, m, args, argc, out)) return out;'
    text=replace(text,anchor,'            native_timer_scan_before_object(ctx,recv.obj);\n'+anchor)
    # ClassRef new and un-inlined static calls retain a single original callback.
    anchor='GdVal call_method(BattleCtx& ctx, const GdVal& recv, SymId m, const GdVal* args, int argc) {'
    text=replace(text,anchor,anchor+'\n    if(recv.kind==GdVal::Kind::ClassRef) native_timer_scan_before_class(ctx,recv.cls);')
    path.write_text(text,encoding='utf8',newline='\n')

    path=native/'native_inline_dispatch.hpp';text=path.read_text('utf8')
    anchor='        } else if(recv.kind==GdVal::Kind::ClassRef && method!=SYM_new) {'
    text=replace(text,anchor,anchor+'\n            native_timer_scan_before_class(ctx,recv.cls);')
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'native_array_index.hpp';text=path.read_text('utf8')
    text=replace(text,'        recv.arr->data[index]=value;return;',
        '        native_timer_scan_mutated(recv.arr);\n        recv.arr->data[index]=value;return;')
    path.write_text(text,encoding='utf8',newline='\n')

    path=native/'gen/shards/shard_00.cpp';text=path.read_text('utf8')
    anchor='    this->f_gems = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));\n'
    text=replace(text,anchor,anchor+'    gd::native_timer_scan_mark(gd_ctx,this->f_gems);\n')
    text=replace(text,NEW_ASSIGN,NEW_ASSIGN+'    gd::native_timer_scan_mark(gd_ctx,this->f_timers);\n')
    for field,symbol in (('gems','SYM_GEN_gems_41'),('timers','SYM_GEN_timers_67')):
        old=f'case {symbol}: this->f_{field} = val; return true;'
        text=replace(text,old,f'case {symbol}: this->f_{field} = val; gd::native_timer_scan_mark(gd_ctx,this->f_{field}); return true;')
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'engine_wrapper.cpp';text=path.read_text('utf8')
    anchor='    battle.native_inline_timer_headers = true;\n'
    text=replace(text,anchor,anchor+'    battle.native_sparse_timer_scans = true;\n')
    anchor='    ci->f_gems = gd::GdVal::from_arr(gems_arr);\n'
    text=replace(text,anchor,anchor+'    gd::native_timer_scan_mark(battle,ci->f_gems);\n')
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'gen/hdrs/Gd__gd_core__CoreCharacter.hpp';text=path.read_text('utf8')
    text=replace(text,'    gd::GdVal f_ctx;\n','    gd::NativeTimerScanCache native_timer_scan_cache_;\n    gd::GdVal f_ctx;\n')
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'gen/shards/shard_02.cpp';text=path.read_text('utf8')
    anchor='void Gd__gd_core__CoreCharacter::init_fields(gd::BattleCtx& gd_ctx) {\n'
    text=replace(text,anchor,anchor+'    this->native_timer_scan_cache_ = {};\n')
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'gen/shards/shard_03.cpp';text=path.read_text('utf8')
    text=replace(text,'    for (uint32_t i = 0, count = items->len; i < count; ++i) {\n',PREPARE)
    helpers=HELPERS.replace('native_scan_item','native_scan_item_exact').replace('native_scan_has_timers','native_scan_has_timers_exact')
    helpers=replace(helpers,'    if (!slot.obj->meta()->is_subclass_of(&META_Gd__gd_core__CoreItem)) return nullptr;',
        '    if (!gd::native_resolved_cached_generated(battle,slot.obj)) return nullptr;\n    if (!slot.obj->meta()->is_subclass_of(&META_Gd__gd_core__CoreItem)) return nullptr;')
    helpers=helpers.replace('const Gd__gd_core__CoreItem* native_scan_item_exact(', '__attribute__((noinline)) const Gd__gd_core__CoreItem* native_scan_item_exact(')
    helpers=helpers.replace('bool native_scan_has_timers_exact(', '__attribute__((noinline)) bool native_scan_has_timers_exact(')
    text=text.replace('native_scan_has_timers(battle,items->data[i])','native_scan_has_timers_exact(battle,items->data[i])')
    text='#include "../../gd_rt.hpp"\n#include "../hdrs/Gd__gd_core__CoreItem.hpp"\n'+helpers+text
    path.write_text(text,encoding='utf8',newline='\n')

    # Exact generated allocators already know the most-derived C++ type. Store
    # its existing immutable row once; custom allocators and stack objects keep
    # lazy RTTI resolution and the original audit before dereferencing the row.
    path=native/'native_resolved_dispatch.hpp';text=path.read_text('utf8')
    rows={name:int(index) for name,index in re.findall(r'value\.emplace\(&typeid\((\w+)\),&native_resolved_rows\[(\d+)\]\);',text)}
    assert len(rows)==674 and len(set(rows.values()))==665
    seeded={};classes=[]
    pattern=re.compile(r'static gd::GdObj\* _alloc_(\w+)\(gd::BattleCtx& ctx\) \{ return ctx.arena.make<\1>\(&ctx\); \}')
    for file in sorted((native/'gen/shards').glob('*.cpp')):
        source=file.read_text('utf8')
        def seed(m):
            name=m[1];classes.append(name)
            if name not in rows:return m[0]
            seeded[name]=rows[name]
            return f'static gd::GdObj* _alloc_{name}(gd::BattleCtx& ctx) {{ auto* object=ctx.arena.make<{name}>(&ctx); if(ctx.native_resolved_dispatch) gd::native_resolved_seed(object,{rows[name]}u); return object; }}'
        source=pattern.sub(seed,source)
        file.write_text(source,encoding='utf8',newline='\n')
    assert len(classes)==674 and seeded==rows,(len(classes),len(seeded))
    # Use all generated metadata pointers, including the nine empty method types.
    text=text.replace('#pragma once\n','#pragma once\n#include <unordered_set>\n#include "gen/class_metas.hpp"\n',1)
    anchor='bool native_resolved_row_matches(const GdObj* object,const NativeMethodRow* row) {'
    functions='''void native_resolved_seed(GdObj* object,unsigned row) {
    if(object && row<std::size(native_resolved_rows)) object->native_call_row_=&native_resolved_rows[row];
}
bool native_resolved_cached_generated(const BattleCtx& context,const GdObj* object) {
    const auto* row=object->native_call_row_;
    return row && row!=&native_resolved_empty &&
        (!context.native_resolved_audit || row==native_resolved_exact_row(object));
}
bool native_resolved_generated_class(const GdClassMeta* type) {
    static const std::unordered_set<const GdClassMeta*> classes={
'''+''.join('        &META_'+name+',\n' for name in classes)+'''    };
    return classes.find(type)!=classes.end();
}
'''
    text=replace(text,anchor,functions+anchor)
    path.write_text(text,encoding='utf8',newline='\n')
    return {'baseline_dll_sha256':'7af5ff948b949859339f0897a6d857953ae8e3b30ec451cee030672ba9c5129b',
        'components':['ordered sparse item/gem timer parent index','674 exact allocator row seeds using665 deduplicated rows','unknown object/static callback invalidation'],
        'prior_sparse_result':'24 pairs CPU median0.73%,wall0.89%; retained and re-evaluated under current composition policy',
        'generated_allocators':len(classes),'seeded_rows':seeded,
        'safety':['tracked array aliases and field replacement','captured length and live ordered callback visibility','unknown future placeholders conservatively eligible','mutation switches to dense remainder','nested/sort/saturation dense fallback','invalidate before unknown callbacks even outside scan','unchanged math, RNG, frame phases and original timer bodies'],
        'layout_changed':['BattleCtx opt-in flag','CoreCharacter cache'],'gdarr_size_remains24':True,
        'full20_rebuild_and18_pgo_required':True}
