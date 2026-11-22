"""Guard a packed-battle default-display view with the existing array mutation watcher."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/grid_cooldown_bundle'
WORK=STAGE/'native_perf50/display_defaults_prototype_r3'
EXPECTED='e0bedc4960077407e85763cb5e4af70175a0623cca15e923403fa89174390687'
ARCHIVE='e53ca96c4e96c9bc7dabd8aee4122f76fe572f1e'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def once(t,a,b):
    assert t.count(a)==1,(a[:150],t.count(a));return t.replace(a,b,1)

def transform(native):
    p=native/'native_inline_dispatch.hpp';t=p.read_text('utf8')
    t=once(t,'#include "gd_rt.hpp"','#include "gd_rt.hpp"\n#include "native_packed_display.hpp"')
    t=once(t,'        NativeFrameSegmentSnapshot& snapshot,const GdVal& delta_value) {',
        '        NativeFrameSegmentSnapshot& snapshot,const GdVal& delta_value,const NativeDefaultDisplayToken* display_token=nullptr) {')
    old='''    const auto* display = item->f_statDisplayOverrides.arr;
    const auto override = display && display->len > 3 ? display->data[3] : gd::GdVal::null();'''
    new='''    gd::GdVal override=gd::GdVal::null();
    // Recheck here, after a possible Gem.character() call. A Bool computed by
    // the caller could otherwise become stale before this exact read point.
    if(native_default_display_valid(*battle,display_token)) {
        if(collect)native_default_display_hit(4);
    } else {
        const auto* display = item->f_statDisplayOverrides.arr;
        override = display && display->len > 3 ? display->data[3] : gd::GdVal::null();
    }'''
    t=once(t,old,new);p.write_text(t,encoding='utf8',newline='\n')
    p=native/'native_active_cooldowns.hpp';t=p.read_text('utf8')
    old='''    return active_cooldown_visit(ctx,character,
        [&](Gd__gd_core__CoreItem* item){native_frame_segment_tick(item,snapshot,delta);},'''
    new='''    const NativeDefaultDisplayToken display_defaults{&ctx,native_default_display_version(ctx),ctx.gid_epoch};
    const auto* display_token=display_defaults.version?&display_defaults:nullptr;
    return active_cooldown_visit(ctx,character,
        [&](Gd__gd_core__CoreItem* item){native_frame_segment_tick(item,snapshot,delta,display_token);},'''
    t=once(t,old,new);p.write_text(t,encoding='utf8',newline='\n')
    p=native/'gen/shards/shard_00.cpp';t=p.read_text('utf8')
    t=once(t,'case SYM_GEN_statDisplayOverrides_33: this->f_statDisplayOverrides = val; return true;',
        'case SYM_GEN_statDisplayOverrides_33: gd::native_default_display_field_changed(this->rt_ctx_); this->f_statDisplayOverrides = val; return true;')
    p.write_text(t,encoding='utf8',newline='\n')
    p=native/'engine_wrapper.cpp';t=p.read_text('utf8')
    t=once(t,'#include "gd_rt.hpp"','#include "gd_rt.hpp"\n#include "native_packed_display.hpp"')
    t=once(t,'    const int32_t max_ticks = opts.max_ticks > 0 ? opts.max_ticks : 20000;',
        '    gd::NativePackedDisplayScope native_display_scope(battle,p_chr,o_chr);\n\n    const int32_t max_ticks = opts.max_ticks > 0 ? opts.max_ticks : 20000;')
    t+='\n'+(STAGE/'native_packed_display_impl.hpp').read_text('utf8')
    p.write_text(t,encoding='utf8',newline='\n')
    shutil.copyfile(STAGE/'native_packed_display.hpp',native/'native_packed_display.hpp')
    return dict(component='owned packed default stat-display reads with version/epoch guarded invalidation',
        all_object_and_container_layouts_unchanged=True,old_floating_operations_unchanged=True,
        validation_completes_before_watch_attachment=True,per_owner_version_checks_in_recovery=True,
        recheck_at_actual_override_read_after_possible_getter_callbacks=True,
        field_replacement_uses_target_object_context=True,no_shared_mutable_arrays=True)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    assert json.loads((ACCEPTED/'post_install_verification.json').read_bytes())['passed']
    backup=json.loads((STAGE/'native_perf50/event_capacity_bundle/checkpoint_rejection_receipt.json').read_bytes())
    assert backup['remote_verified_commit']==ARCHIVE and backup['unchanged_runtime_dll_sha256']==EXPECTED
    assert subprocess.check_output(['git','ls-remote','--exit-code','origin','refs/heads/codex/native-perf50-verified']).decode().split()[0]==ARCHIVE
    assert not WORK.exists();WORK.mkdir();src=WORK/'prototype_src'
    shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    before={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    component=transform(src)
    after={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    modified=sorted(n for n in before if before[n]!=after[n]);new=sorted(set(after)-set(before))
    assert modified==['engine_wrapper.cpp','gen/shards/shard_00.cpp','native_active_cooldowns.hpp','native_inline_dispatch.hpp']
    assert new==['native_packed_display.hpp']
    report=dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,component=component,
        source_sha256=after,modified_files=modified,new_files=new,not_for_deployment=True,
        retained_rejected_event_capacity_change=False,dependencies={n:sha(STAGE/n) for n in
            ('native_packed_display.hpp','native_packed_display_impl.hpp','prepare_native_display_defaults.py')})
    (WORK/'transform.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in report.items() if k!='source_sha256'},indent=2))

if __name__=='__main__':main()
