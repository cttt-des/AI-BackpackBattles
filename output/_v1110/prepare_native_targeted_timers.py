"""Create an isolated watcher/index prototype from the verified7a57 baseline."""
import hashlib
import json
from pathlib import Path
import re
import shutil
STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/targeted_timer_prototype'
EXPECTED='7a57d09b81ba62fcd985fbb14a5999c72ff550ba328d5cae3add6167e4fbc058'
ARCHIVE='4a5388b7161d765cafe5515f263ee0f762fe7c88'

WATCH=r'''
void native_timer_index_hit(unsigned,uint64_t amount=1);
struct NativeTimerWatch {
    uint64_t version=1;
    uint32_t depth=0;
    bool enabled=false,usable=true,collect=false;
    const GdObj* trusted_hooks=nullptr;
    void* cache[2]{};
    void change() {
        if(version==UINT64_MAX){usable=false;return;}
        ++version;if(collect)native_timer_index_hit(6);
    }
};
struct NativeTimerMutation {
    NativeTimerWatch* watch;
    bool entered=false;
    explicit NativeTimerMutation(NativeTimerWatch* w):watch(w) {
        if(watch){watch->change();if(watch->depth==UINT32_MAX)watch->usable=false;else {++watch->depth;entered=true;}}
    }
    ~NativeTimerMutation(){if(watch){if(entered)--watch->depth;watch->change();}}
    NativeTimerMutation(const NativeTimerMutation&)=delete;
    NativeTimerMutation& operator=(const NativeTimerMutation&)=delete;
};
bool native_timer_known_object(const GdObj*);
bool native_timer_known_class(const GdClassMeta*);
void native_timer_observe_object(BattleCtx&,const GdObj*);
void native_timer_observe_class(BattleCtx&,const GdClassMeta*);
'''
AFTER_CONTEXT=r'''
inline void native_timer_fields_changed(BattleCtx* context) {
    if(context && context->native_timer_watch.enabled)context->native_timer_watch.change();
}
'''
RUNTIME=r'''
namespace gd {
static thread_local uint64_t native_timer_index_counts[10]{};
void native_timer_index_hit(unsigned i,uint64_t amount){if(i<10)native_timer_index_counts[i]+=amount;}
bool native_timer_known_object(const GdObj* object) {
    if(!object)return true;
    const auto* row=object->native_call_row_;
    return (row && row->metadata) || native_resolved_exact_row(object)!=&native_resolved_empty;
}
bool native_timer_known_class(const GdClassMeta* cls) {
    if(!cls)return true;
    static const auto known=[] {std::unordered_set<const GdClassMeta*> result;
        for(const auto& row:native_resolved_rows)result.insert(row.metadata);
        return result;}();
    return known.contains(cls);
}
void native_timer_observe_object(BattleCtx& ctx,const GdObj* object) {
    auto& w=ctx.native_timer_watch;
    if(w.enabled && w.usable && object && object!=w.trusted_hooks && !native_timer_known_object(object)) {
        w.change();w.usable=false;if(w.collect)native_timer_index_hit(9);
    }
}
void native_timer_observe_class(BattleCtx& ctx,const GdClassMeta* cls) {
    auto& w=ctx.native_timer_watch;
    if(w.enabled && w.usable && !native_timer_known_class(cls)) {
        w.change();w.usable=false;if(w.collect)native_timer_index_hit(9);
    }
}
}
extern "C" uint64_t gd_diag_native_targeted_timer_stat(unsigned i){return i<10?gd::native_timer_index_counts[i]:0;}
'''

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def once(text,old,new):
    assert text.count(old)==1,(old,text.count(old));return text.replace(old,new,1)
def body(text,signature):
    start=text.index(signature);return text[start:text.index('\n}',start)+2]

def transform(native):
    baseline={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    h=native/'gd_rt.hpp';text=h.read_text('utf8')
    text=once(text,'struct GdArr {',WATCH+'\nstruct GdArr {')
    text=once(text,'    bool is_pool_real = false;','    bool is_pool_real = false;\n    NativeTimerWatch* timer_watch = nullptr;')
    text=once(text,'    explicit BattleCtx(size_t arena_bytes', '    NativeTimerWatch native_timer_watch;\n\n    explicit BattleCtx(size_t arena_bytes')
    text=once(text,'        arena.reset();','        native_timer_watch=NativeTimerWatch{};\n        arena.reset();')
    text=once(text,'// ─────────────────────────── Class Registry & Dispatch Helpers',AFTER_CONTEXT+'\n// ─────────────────────────── Class Registry & Dispatch Helpers')
    h.write_text(text,encoding='utf8',newline='\n')
    p=native/'gd_rt.cpp';text=p.read_text('utf8')
    text=once(text,'#include <unordered_map>','#include <unordered_map>\n#include <unordered_set>')
    mutations=[]
    for method in ('push_back','insert_at','pop_at','append_array','pop_front','pop_back','remove_at','resize','fill','invert','set_idx'):
        start=text.index('GdArr::'+method+'(');opening=text.index('{',start)
        text=text[:opening+1]+'\n    NativeTimerMutation native_mutation(timer_watch);'+text[opening+1:];mutations.append(method)
    for signature in ('void shuffle_array(','void godot_sort_custom_items(','void sort_custom_stable('):
        start=text.index(signature);opening=text.index('{',start)
        text=text[:opening+1]+'\n    NativeTimerMutation native_mutation(arr?arr->timer_watch:nullptr);'+text[opening+1:]
    text=once(text,'case SYM_clear: a->len = 0; return GdVal::null();','case SYM_clear: {NativeTimerMutation native_mutation(a->timer_watch);a->len = 0;return GdVal::null();}')
    # Observe before arbitrary virtual code, without resolving/caching any old row
    # or changing legacy dispatch counters. Generated/native hooks remain trusted.
    replacements=[
        ('            c.target->call_method(ctx,','            native_timer_observe_object(ctx,c.target);\n            c.target->call_method(ctx,'),
        ('        obj->call_method(ctx, method, args, 2, out);','        native_timer_observe_object(ctx,obj);\n        obj->call_method(ctx, method, args, 2, out);'),
        ('            if (prop == SYM_resource_path) return GdVal::from_cstr(ctx.arena, recv.obj->meta()->res_path);','            native_timer_observe_object(ctx,recv.obj);\n            if (prop == SYM_resource_path) return GdVal::from_cstr(ctx.arena, recv.obj->meta()->res_path);'),
        ('            if (recv.obj) recv.obj->set_prop(ctx, prop, val);','            if (recv.obj) {native_timer_observe_object(ctx,recv.obj);recv.obj->set_prop(ctx, prop, val);}'),
        ('        recv.obj->set_prop(ctx, s, val);','        native_timer_observe_object(ctx,recv.obj);recv.obj->set_prop(ctx, s, val);'),
        ('            // Dispatch user/generated methods first so subclass overrides win if any','            native_timer_observe_object(ctx,recv.obj);\n            // Dispatch user/generated methods first so subclass overrides win if any'),
    ]
    for old,new in replacements:
        assert old in text; text=text.replace(old,new)
    text=once(text,'    if (!instance || method == SYM_NONE) return GdVal::null();',
        '    if (!instance || method == SYM_NONE) return GdVal::null();\n    native_timer_observe_object(ctx,instance);')
    text=once(text,'    return instance != nullptr && method != SYM_NONE && instance->has_own_method(method);',
        '    if(instance && instance->rt_ctx_)native_timer_observe_object(*instance->rt_ctx_,instance);\n    return instance != nullptr && method != SYM_NONE && instance->has_own_method(method);')
    # Class allocation/static callbacks and the no-context meta helpers also have
    # user-code boundaries. The ordinary bridge supplies owned non-null contexts.
    start=text.index('GdVal construct_class(');opening=text.index('{',start)
    text=text[:opening+1]+'\n    native_timer_observe_class(ctx,cls);'+text[opening+1:]
    text=text.replace('if (recv.cls->get_static_prop) {','if (recv.cls->get_static_prop) {\n                    native_timer_observe_class(ctx,recv.cls);')
    text=text.replace('if (recv.cls->call_static_fn) {','if (recv.cls->call_static_fn) {\n                    native_timer_observe_class(ctx,recv.cls);')
    text=once(text,'    return v.obj->meta()->is_subclass_of(cls);','    if(v.obj->rt_ctx_)native_timer_observe_object(*v.obj->rt_ctx_,v.obj);\n    return v.obj->meta()->is_subclass_of(cls);')
    text=once(text,'            out += v.obj ? v.obj->meta()->class_name : "Null";','            if(v.obj && v.obj->rt_ctx_)native_timer_observe_object(*v.obj->rt_ctx_,v.obj);\n            out += v.obj ? v.obj->meta()->class_name : "Null";')
    text+=RUNTIME;p.write_text(text,encoding='utf8',newline='\n')
    p=native/'native_array_index.hpp';text=p.read_text('utf8')
    text=once(text,'        recv.arr->data[index]=value;return;','        NativeTimerMutation native_mutation(recv.arr->timer_watch);\n        recv.arr->data[index]=value;return;')
    p.write_text(text,encoding='utf8',newline='\n')
    p=native/'native_inline_dispatch.hpp';text=p.read_text('utf8')
    text=once(text,'            if(recv.cls && recv.cls->call_static_fn) {','            if(recv.cls && recv.cls->call_static_fn) {\n                native_timer_observe_class(ctx,recv.cls);')
    p.write_text(text,encoding='utf8',newline='\n')
    assignments=[]
    for p in sorted((native/'gen/shards').glob('*.cpp')):
        text=p.read_text('utf8')
        def change(m):
            assignments.append(dict(path=p.relative_to(native).as_posix(),field=m.group(1)))
            return 'gd::native_timer_fields_changed(this->rt_ctx_); '+m.group(0)
        text=re.sub(r'this->(f_(?:timers|gems|items|inventory))\s*=',change,text)
        p.write_text(text,encoding='utf8',newline='\n')
    p=native/'engine_wrapper.cpp';text=p.read_text('utf8')
    text=once(text,'    battle.reset_for_battle(opts.seed);','    battle.reset_for_battle(opts.seed);\n    battle.native_timer_watch.enabled=true;')
    text=once(text,'    hooks->init_fields(battle);','    hooks->init_fields(battle);\n    battle.native_timer_watch.trusted_hooks=hooks;')
    text=once(text,'    ci->f_gems = gd::GdVal::from_arr(gems_arr);','    gd::native_timer_fields_changed(ci->rt_ctx_);\n    ci->f_gems = gd::GdVal::from_arr(gems_arr);')
    p.write_text(text,encoding='utf8',newline='\n')
    p=native/'gen/shards/shard_03.cpp';text=p.read_text('utf8')
    original=body(text,'gd::GdVal Gd__gd_core__CoreCombat::fn__tickCharacterTimers(')
    prefix=original[:original.index('    const auto* inventory =')]
    candidate=prefix+'    gd::targeted_timer_tick(*this->rt_ctx_,character,delta);\n    return gd::GdVal::null();\n}'
    text=once(text,'#pragma STDC FP_CONTRACT OFF','#pragma STDC FP_CONTRACT OFF\n#include "../../native_targeted_timers.hpp"')
    text=once(text,original,candidate);p.write_text(text,encoding='utf8',newline='\n')
    shutil.copyfile(STAGE/'native_targeted_timers.hpp',native/'native_targeted_timers.hpp')
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    return dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,
        modified_files=sorted(k for k in baseline if baseline[k]!=after[k]),new_files=sorted(set(after)-set(baseline)),
        watched_array_mutators=mutations,field_write_sites=assignments,
        original_tick_character_timers=original,source_sha256=after,
        floating_options_rng_event_and_callback_order_retained=True,layout_changes_require_full_rebuild=True,
        no_throughput_or_equivalence_claim_before_tests=True)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    WORK.mkdir(exist_ok=True);native=WORK/'prototype_src';assert not native.exists()
    shutil.copytree(BASE,native,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    report=transform(native)
    (WORK/'transform.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in report.items() if k not in ('source_sha256','original_tick_character_timers','field_write_sites')},indent=2))

if __name__=='__main__':main()
