"""Fuse one closed-world event construction without changing generated layouts."""
import json
from pathlib import Path
import shutil
import subprocess
from prepare_native_frame_proof import STAGE, BASE, ACCEPTED, EXPECTED, sha, once

WORK = STAGE / 'native_perf50/event_factory_prototype'
ARCHIVE = 'a3e6658fea86d306fbfb3e84dcc7d65918853b24'
HELPER = '''
// Closed-world construction has no callback/escape before _init completes.
// Each event and each dictionary still has its own stable object identity.
gd::GdVal gd_native_create_event(gd::BattleCtx& ctx,const gd::GdVal* args,int argc) {
    if(!ctx.native_timer_watch.closed_world)
        return native_event_new<Gd__gd_core__CoreEvent>(ctx,args,argc);
    using Event=Gd__gd_core__CoreEvent;
    using Dict=gd::GdDict;
    using Entry=gd::GdDictEntry;
    constexpr auto aligned=[](size_t n,size_t a){return (n+a-1)/a*a;};
    constexpr size_t params_offset=aligned(sizeof(Event),alignof(Dict));
    constexpr size_t format_offset=aligned(params_offset+sizeof(Dict),alignof(Dict));
    constexpr size_t entries_offset=aligned(format_offset+sizeof(Dict),alignof(Entry));
    constexpr size_t alignment=std::max(alignof(Event),std::max(alignof(Dict),alignof(Entry)));
    auto* raw=static_cast<unsigned char*>(ctx.arena.alloc_raw(
        entries_offset+4*sizeof(Entry),alignment));
    auto* event=new(raw) Event(&ctx);
    auto* params=new(raw+params_offset) Dict();
    auto* format=new(raw+format_offset) Dict();
    // Slots have raw storage only. Normal setters construct used entries.
    params->entries=reinterpret_cast<Entry*>(raw+entries_offset);
    params->cap=4;
    event->f_params=gd::GdVal::from_dict(params);
    event->f_formatParams=gd::GdVal::from_dict(format);
    // These are the original _init defaults, coercion and assignment order.
    // The constructor already set target to Null. The other default stores
    // in init_fields are unobservable before these unconditional assignments.
    gd::GdVal id=argc>0?args[0]:gd::GdVal::null();
    gd::GdVal timestamp=argc>1?args[1]:gd::GdVal::from_float(0.0);
    gd::GdVal parent=argc>2?args[2]:gd::GdVal::null();
    gd::GdVal origin=argc>3?args[3]:gd::GdVal::null();
    gd::GdVal type=argc>4?args[4]:gd::GdVal::null();
    event->f_id=gd::gd_coerce_int(id);
    event->f_timestamp=timestamp;
    event->f_parentEvent=parent;
    event->f_origin=origin;
    event->f_type=type;
    return gd::GdVal::from_obj(event);
}

'''

def transform(native):
    p = native / 'gen/shards/shard_05.cpp'
    t = p.read_text('utf8')
    marker = 'gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent(const gd::GdVal* _args, int _argc) {'
    t = once(t, marker, HELPER + marker)
    t = once(t, 'return native_event_new<Gd__gd_core__CoreEvent>(gd_ctx, _ca, 5);',
                'return gd_native_create_event(gd_ctx, _ca, 5);')
    p.write_text(t, encoding='utf8', newline='\n')
    return dict(component='closed event object + two distinct dictionaries + four raw slots in one allocation',
                redundant_init_fields_stores_removed_only_before_unconditional_init=True,
                original_constructor_target_default_and_id_coercion_preserved=True,
                open_world_uses_original_factory=True, original_frame_kernel_unchanged=True,
                object_layouts_unchanged=True, callbacks_rng_arithmetic_order_unchanged=True)

def main():
    assert sha(BASE / 'libgdcore.dll') == EXPECTED
    backed = subprocess.check_output(['git', 'show', ARCHIVE + ':output/_v1110/sim_native/native_sim_cpp/native_sim/libgdcore.dll'])
    import hashlib
    assert hashlib.sha256(backed).hexdigest() == EXPECTED
    assert not WORK.exists()
    WORK.mkdir()
    src = WORK / 'prototype_src'
    shutil.copytree(BASE, src, ignore=shutil.ignore_patterns('*.dll', '*.o', '*.gcda', '*.gcno', '__pycache__'))
    before = {p.relative_to(src).as_posix(): sha(p) for p in src.rglob('*') if p.is_file()}
    assert before == json.loads((ACCEPTED / 'source_before_build.json').read_bytes())
    component = transform(src)
    after = {p.relative_to(src).as_posix(): sha(p) for p in src.rglob('*') if p.is_file()}
    changed = sorted(n for n in before if before[n] != after[n])
    assert changed == ['gen/shards/shard_05.cpp']
    (WORK / 'transform.json').write_text(json.dumps(dict(
        baseline_dll_sha256=EXPECTED, verified_backup=ARCHIVE, source_sha256=after,
        modified_files=changed, component=component, not_for_deployment=True), indent=2)+'\n', encoding='utf8')
    print('Prepared new closed-event factory from unchanged production; no speed claim')

if __name__ == '__main__':
    main()
