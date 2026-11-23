"""Coallocate event dictionary storage and inline the existing frame kernel."""
import json
from pathlib import Path
import shutil
import subprocess
from prepare_native_frame_proof import STAGE,BASE,ACCEPTED,EXPECTED,sha,once
WORK=STAGE/'native_perf50/coallocated_events_prototype'

def transform(native):
    p=native/'gen/shards/shard_11.cpp';t=p.read_text('utf8')
    t=once(t,'    this->f_params = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));', '''    this->f_params = gd::GdVal::from_dict([&]() -> gd::GdDict* {
        if(!gd_ctx.native_timer_watch.closed_world)return gd::GdDict::create(gd_ctx.arena);
        // One allocation for the independently owned header and four raw slots.
        // No GdVal constructors or FP operations touch unused entry storage.
        constexpr size_t alignment=alignof(gd::GdDict)>alignof(gd::GdDictEntry)
            ?alignof(gd::GdDict):alignof(gd::GdDictEntry);
        constexpr size_t offset=(sizeof(gd::GdDict)+alignof(gd::GdDictEntry)-1)
            /alignof(gd::GdDictEntry)*alignof(gd::GdDictEntry);
        auto* raw=static_cast<unsigned char*>(gd_ctx.arena.alloc_raw(
            offset+4*sizeof(gd::GdDictEntry),alignment));
        auto* dictionary=new(raw) gd::GdDict();
        dictionary->entries=reinterpret_cast<gd::GdDictEntry*>(raw+offset);
        dictionary->cap=4;
        // The ordinary setter owns all insertion, replacement and later growth.
        return dictionary;
    }());''')
    p.write_text(t,encoding='utf8',newline='\n')
    p=native/'native_inline_dispatch.hpp';t=p.read_text('utf8')
    t=once(t,'inline void native_frame_segment_tick(', '''#if defined(__GNUC__)
__attribute__((always_inline))
#elif defined(_MSC_VER)
__forceinline
#endif
inline void native_frame_segment_tick(''')
    p.write_text(t,encoding='utf8',newline='\n')
    # Use the identical diagnostic entry points already covered by the3073
    # actual-DLL differential; no rejected row/Bool changes are carried over.
    p=native/'engine_wrapper.cpp';t=p.read_text('utf8')
    previous=(STAGE/'native_perf50/frame_proof_prototype/prototype_src/engine_wrapper.cpp').read_text('utf8')
    t+='\n'+previous[previous.index('// Test-only entry points call the same inline bodies'):]
    p.write_text(t,encoding='utf8',newline='\n')
    return dict(component='one-allocation four-slot event dictionary plus frame kernel inline',
        dictionary_identity_aliases_and_normal_growth_retained=True,
        GdDict_GdVal_GdObj_and_generated_layouts_unchanged=True,
        unused_entries_not_initialized=True,ordinary_open_context_factory_unchanged=True,
        all_frame_arithmetic_callbacks_and_checks_unchanged=True,
        rejected_frame_proof_and_first_write_capacity_candidates_not_included=True)

def main():
    checkpoint_path=STAGE/'native_perf50/frame_proof_bundle/checkpoint_rejection_receipt.json'
    if not checkpoint_path.exists():
        # Production is byte-identical to the previously remote-verified backup.
        # A failed upload of rejected trials must not masquerade as a new push.
        checkpoint_path=STAGE/'native_perf50/display_defaults_bundle/checkpoint_rejection_receipt.json'
    checkpoint=json.loads(checkpoint_path.read_bytes())
    archive=checkpoint['remote_verified_commit']
    backed_dll=subprocess.check_output(['git','show',archive+':output/_v1110/sim_native/native_sim_cpp/native_sim/libgdcore.dll'])
    import hashlib
    assert hashlib.sha256(backed_dll).hexdigest()==EXPECTED
    assert sha(BASE/'libgdcore.dll')==EXPECTED and checkpoint['unchanged_runtime_dll_sha256']==EXPECTED
    assert not WORK.exists();WORK.mkdir();src=WORK/'prototype_src'
    shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    before={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    component=transform(src)
    after={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    changed=sorted(n for n in before if before[n]!=after[n])
    assert changed==['engine_wrapper.cpp','gen/shards/shard_11.cpp','native_inline_dispatch.hpp']
    report=dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=archive,source_sha256=after,
        modified_files=changed,new_files=[],component=component,not_for_deployment=True,
        production_unchanged_since_last_remote_verified_backup=True,
        rejected_trial_upload_pending=not (STAGE/'native_perf50/frame_proof_bundle/checkpoint_rejection_receipt.json').exists())
    (WORK/'transform.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print('Prepared coallocated-event/inline-frame semantic prototype; no timing claim')

if __name__=='__main__':main()
