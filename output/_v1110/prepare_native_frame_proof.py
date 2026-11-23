"""Reuse the already checked tick row across the callback-free header interval."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/grid_cooldown_bundle'
WORK=STAGE/'native_perf50/frame_proof_prototype'
EXPECTED='e0bedc4960077407e85763cb5e4af70175a0623cca15e923403fa89174390687'
ARCHIVE='1b18298e39ed36f0fd0dbe5d0e00699d9407c643'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def once(t,a,b):
    assert t.count(a)==1,(a[:120],t.count(a));return t.replace(a,b,1)

def transform(native):
    p=native/'native_inline_dispatch.hpp';t=p.read_text('utf8')
    start=t.index('inline void native_frame_segment_tick(')
    end=t.index('\n} // namespace gd',start)
    frame=t[start:end]
    frame=once(frame,
        '    const auto receiver = gd::native_inline_self_type(item->rt_ctx_,item,&META_Gd__gd_core_items__Gems__Gem)',
        '''    // The entry has checked this exact row and its metadata. Between
    // that check and here, gd_truth/as_int and diagnostic increments make no
    // application calls and cannot replace rt_ctx, the row, or its metadata.
    // Keep the original type-hit diagnostic at its original execution point.
    if(collect)native_type_constructor_hit(0);
    const auto receiver = (row->type_mask & uint64_t{1})!=0''')
    frame=once(frame,'gd::gd_truth(item->f_placed)','native_frame_flag_truth(item->f_placed)')
    frame=once(frame,'gd::gd_truth(context.f_show_cooldown_progress)',
        'native_frame_flag_truth(context.f_show_cooldown_progress)')
    helper='''// Avoid the out-of-line variant conversion for the common Bool flags.
// Every other kind retains the original conversion, including FP exceptions.
inline bool native_frame_flag_truth(const GdVal& value) {
    if(value.kind==GdVal::Kind::Bool) [[likely]] return value.b;
    return gd_truth(value);
}
'''
    t=t[:start]+helper+frame+t[end:];p.write_text(t,encoding='utf8',newline='\n')
    p=native/'engine_wrapper.cpp';t=p.read_text('utf8')
    t+='''
// Test-only entry points call the same inline bodies as the combat shard.
#include "native_active_cooldowns.hpp"
extern "C" void gd_diag_native_frame_proof_tick(Gd__gd_core__CoreItem* item,
        gd::NativeFrameSegmentSnapshot* snapshot,const gd::GdVal* delta) {
    gd::native_frame_segment_tick(item,*snapshot,*delta);
}
extern "C" int gd_diag_native_frame_proof_phase(Gd__gd_core__CoreCharacter* character,
        gd::NativeFrameSegmentSnapshot* snapshot,const gd::GdVal* delta) {
    return gd::active_cooldown_phase(*character->rt_ctx_,character,*snapshot,*delta)?1:0;
}
'''
    p.write_text(t,encoding='utf8',newline='\n')
    return dict(component='reuse validated tick row and specialize two Bool flags',
        reuse_interval='entry audit through active/blocked checks, before Gem.character callback',
        original_type_counter_at_original_position=True,all_non_Bool_flag_conversions_retained=True,
        no_new_scope_cache_or_per_owner_guard=True,all_object_container_context_layouts_unchanged=True,
        original_FENV_and_floating_operations_retained=True,
        rejected_display_and_event_capacity_changes_included=False)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    backup=json.loads((STAGE/'native_perf50/display_defaults_bundle/checkpoint_rejection_receipt.json').read_bytes())
    assert backup['remote_verified_commit']==ARCHIVE
    assert subprocess.check_output(['git','ls-remote','--exit-code','origin','refs/heads/codex/native-perf50-verified']).decode().split()[0]==ARCHIVE
    assert not WORK.exists();WORK.mkdir();src=WORK/'prototype_src'
    shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    before={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    component=transform(src)
    after={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    modified=sorted(n for n in before if before[n]!=after[n])
    assert modified==['engine_wrapper.cpp','native_inline_dispatch.hpp'] and set(after)==set(before)
    report=dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,component=component,
        source_sha256=after,modified_files=modified,new_files=[],not_for_deployment=True,
        pure_truth_source_sha256=sha(BASE/'gd_rt.cpp'),transform_script_sha256=sha(Path(__file__)))
    (WORK/'transform.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in report.items() if k!='source_sha256'},indent=2))

if __name__=='__main__':main()
