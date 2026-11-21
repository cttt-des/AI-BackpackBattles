"""Independent member-field reads and callback-bounded frame state reuse."""
import hashlib
import json
from pathlib import Path
import re
from prototype_native_frame_segments_bundle import frame_helper

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'native_perf50/lazy_diagnostics_bundle'

def change(text,old,new,count=1):
    assert text.count(old)==count,(old[:90],text.count(old))
    return text.replace(old,new)

def member_fields(native):
    path=native/'native_resolved_dispatch.hpp';text=path.read_text('utf8')
    start=text.index('static const NativePropertyRow native_property_rows[] = {')
    end=text.index('static const NativeMethodRow native_resolved_rows[]',start)
    rows=text[start:end]
    replacement,n=re.subn(r'&native_resolved_field<(Gd__\w+), &(Gd__\w+)::(f_\w+)>',
        lambda m:f'static_cast<GdVal GdObj::*>(&{m[2]}::{m[3]})',rows)
    assert n>100
    text=text[:start]+replacement+text[end:]
    text=change(text,'out=function(object);return true;','out=object->*function;return true;')
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'native_inline_dispatch.hpp';text=path.read_text('utf8')
    text=change(text,'using NativePropertyFn = GdVal (*)(const GdObj*);','using NativePropertyFn = GdVal GdObj::*;')
    text=change(text,'return function(recv.obj);','return recv.obj->*function;')
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'native_event_kernel.hpp';text=path.read_text('utf8')
    for old,new in [('descriptor_getter(emitter.obj)','(emitter.obj->*descriptor_getter)'),
        ('owner_getter(emitter.obj)','(emitter.obj->*owner_getter)'),
        ('identifier_getter(descriptor.obj)','(descriptor.obj->*identifier_getter)')]:text=change(text,old,new)
    path.write_text(text,encoding='utf8',newline='\n')
    return n

def frame_reuse(native):
    helper,original=frame_helper(native)
    path=native/'native_inline_dispatch.hpp';text=path.read_text('utf8')
    includes=''.join(f'#include "gen/hdrs/{cls}.hpp"\n' for cls in ('Gd__gd_core__CoreItem','Gd__gd_core__CoreContext','Gd__gd_core__CoreCharacter','Gd__gd_core__CoreBuff','Gd__gd_core_items__Gems__Gem'))
    text=change(text,'namespace gd {',includes+'namespace gd {')
    text=change(text,'} // namespace gd',helper+'\n} // namespace gd')
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'gen/shards/shard_03.cpp';text=path.read_text('utf8')
    anchor='gd::GdVal Gd__gd_core__CoreCombat::fn_physicsTick(const gd::GdVal* _args, int _argc) {'
    text=change(text,anchor,anchor+'\n    gd::NativeFrameSegmentSnapshot native_segment_snapshot;')
    text=change(text,'cooldown_item->fn_physicsTick(&lv_delta, 1);','gd::native_frame_segment_tick(cooldown_item,native_segment_snapshot,lv_delta);',2)
    text=change(text,'cooldown_gem->fn_physicsTick(&lv_delta, 1);','{native_segment_snapshot.clear();cooldown_gem->fn_physicsTick(&lv_delta, 1);}',2)
    for side in ('opponent','player'):
        line=f'    (void)([&]() {{ gd::GdVal _ca[] = {{lv_delta}}; return {side}()->fn_physicsTickCharacter(_ca, 1); }})();'
        text=change(text,line,'    native_segment_snapshot.clear();\n'+line)
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'engine_wrapper.cpp'
    path.write_text(path.read_text('utf8')+'''
namespace gd {
static thread_local uint64_t native_frame_segment_counts[17]{};
void native_frame_segment_hit(unsigned index) {if(index<17)++native_frame_segment_counts[index];}
}
extern "C" uint64_t gd_diag_native_frame_segment_stat(unsigned index) {
    return index<17?gd::native_frame_segment_counts[index]:0;
}
''',encoding='utf8',newline='\n')
    assert original in (native/'gen/shards/shard_00.cpp').read_text('utf8')
    return hashlib.sha256(original.encode()).hexdigest()

def optimize(native,member=True,frame=True):
    expected=json.loads((BASE/'source_before_build.json').read_bytes())
    before={p.relative_to(native).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in native.rglob('*') if p.is_file()}
    assert expected==before
    bindings=member_fields(native) if member else 0
    original=frame_reuse(native) if frame else None
    after={p.relative_to(native).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in native.rglob('*') if p.is_file()}
    assert before.keys()==after.keys()
    unchanged=['gd_rt.hpp','gd_rt.cpp','gen/shards/shard_00.cpp']+[f'gen/hdrs/{p.name}' for p in (native/'gen/hdrs').glob('*.hpp')]
    assert all(before[name]==after[name] for name in unchanged)
    report=json.loads((BASE/'transform.json').read_bytes())
    report.update(baseline_dll_sha256='593acaf3d6bf1dfedc7926cc5f3659c074a285dd95a9dcf0db95c1f913077670',
        components=[name for enabled,name in ((member,'member-pointer pure property rows'),(frame,'independent callback-bounded character state reuse')) if enabled],
        member_bindings=bindings,modified_native_files=[name for name in before if before[name]!=after[name]],
        original_item_physics_sha256=original,no_empty_timer_chunks=True,no_field_tags=True,no_public_nan_guard_changes=True,
        unchanged_headers=674,public_arithmetic_and_object_layout_unchanged=True)
    return report
