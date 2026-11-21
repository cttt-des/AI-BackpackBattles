"""Fold proven literal numeric consumers without sharing mutable collections."""
import hashlib
import json
from pathlib import Path
from prepare_native_static_collections import transformed
STAGE=Path(__file__).resolve().parent
BASE=STAGE/'native_perf50/frame_ablation_bundle'
PROBE=STAGE/'native_perf50/static_collections_probe'
def optimize(native):
    sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
    before=json.loads((BASE/'source_before_build.json').read_bytes())
    assert before=={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    screen=json.loads((PROBE/'screen.json').read_bytes());assert screen['passed'] and screen['cases']==13440
    helper=(PROBE/'static_collection_helper.hpp').read_text('utf8')
    assert sha(PROBE/'static_collection_helper.hpp')==screen['helper_sha256']
    _,rows,old,new=transformed(native)
    path=native/'gen/shards/shard_02.cpp';text=path.read_text('utf8')
    for slot,name in enumerate(('classAttackSoundCount','classRoundSoundCount')):
        replacement=new[name].replace('))return folded;',f')){{if(gd_ctx.native_resolved_collect)gd::native_static_collection_hit({slot});return folded;}}')
        assert replacement!=new[name] and text.count(old[name])==1
        text=text.replace(old[name],replacement,1)
    anchor='gd::GdVal Gd__gd_core__CoreCharacter::fn_classAttackSoundCount('
    text=text.replace(anchor,helper.replace('#pragma once\n','').replace('#include "gd_rt.hpp"\n','')+'\nnamespace gd {void native_static_collection_hit(unsigned);}\n'+anchor,1)
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'gen/shards/shard_06.cpp';text=path.read_text('utf8')
    replacement=new['numStackTypes'].replace('if(gd_ctx.native_resolved_dispatch)return gd::GdVal::from_int(11LL);',
        'if(gd_ctx.native_resolved_dispatch){if(gd_ctx.native_resolved_collect)gd::native_static_collection_hit(2);return gd::GdVal::from_int(11LL);}')
    assert text.count(old['numStackTypes'])==1
    text=text.replace(old['numStackTypes'],'namespace gd {void native_static_collection_hit(unsigned);}\n'+replacement,1)
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'engine_wrapper.cpp'
    path.write_text(path.read_text('utf8')+'''
namespace gd {
static thread_local uint64_t native_static_collection_counts[3]{};
void native_static_collection_hit(unsigned index){if(index<3)++native_static_collection_counts[index];}
}
extern "C" uint64_t gd_diag_native_static_collection_stat(unsigned index){return index<3?gd::native_static_collection_counts[index]:0;}
''',encoding='utf8',newline='\n')
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    changed=sorted(p for p in before if before[p]!=after[p])
    assert changed==['engine_wrapper.cpp','gen/shards/shard_02.cpp','gen/shards/shard_06.cpp'],changed
    report=json.loads((BASE/'transform.json').read_bytes())
    report.update(baseline_dll_sha256=screen['baseline_dll_sha256'],components=['retained member reads and frame state reuse','literal class sound count consumers','literal stack type count consumer'],
        modified_native_files=changed,sound_count_rows=rows,folded_stack_type_count=11,
        original_numeric_consumers_sha256={name:hashlib.sha256(value.encode()).hexdigest() for name,value in old.items()},
        mutable_global_collection_getters_unchanged=True,unsupported_class_and_disabled_dispatch_fallbacks_preserved=True,
        object_context_layout_headers_and_public_arithmetic_unchanged=True,local_differential_cases=13440,
        no_whole_fight_gain_claim=True)
    return report
