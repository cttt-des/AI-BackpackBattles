"""Specialize sealed packed-input battles while retaining open-runtime observers."""
import hashlib
import json
from pathlib import Path
import re
import shutil
import prepare_native_targeted_timers as base
STAGE=base.STAGE
BASE=base.BASE
WORK=STAGE/'native_perf50/closed_timer_prototype'
EXPECTED=base.EXPECTED
ARCHIVE=base.ARCHIVE
sha=base.sha

REGISTRY=r'''
namespace gd {
static std::atomic<bool> native_timer_registry_sealed{true};
void native_timer_registered_class(const GdClassMeta* metadata) {
    if(metadata && !native_timer_known_class(metadata))native_timer_registry_sealed.store(false,std::memory_order_release);
}
bool native_timer_registry_closed(){return native_timer_registry_sealed.load(std::memory_order_acquire);}
}
extern "C" int gd_diag_native_timer_registry_closed(){return gd::native_timer_registry_closed()?1:0;}
'''

def closure_proof(native):
    engine=(native/'engine_wrapper.cpp').read_text('utf8')
    before=(BASE/'engine_wrapper.cpp').read_text('utf8')
    def structs(text):
        begin=text.index('extern "C" {\n\nstruct PackedEffect')
        return text[begin:text.index('void gd_sim_init()',begin)]
    assert structs(before)==structs(engine),'Packed inputs and outputs must remain byte-for-byte declared the same'
    assert 'GdObj' not in structs(engine) and 'GdClassMeta' not in structs(engine) and '(*' not in structs(engine)
    signatures=re.findall(r'^(?:void|int32_t|const char\*|const int32_t\*)\s+(gd_sim_\w+)\s*\((.*?)\)\s*\{',engine,re.M|re.S)
    assert len(signatures)==22,len(signatures)
    assert all('GdObj' not in args and 'GdClassMeta' not in args and '(*' not in args for _,args in signatures)
    sites=[]
    for p in native.rglob('*'):
        if not p.is_file() or p.suffix not in ('.cpp','.hpp'):continue
        for number,line in enumerate(p.read_text('utf8').splitlines(),1):
            if re.search(r'\b(?:register_class|gd_init_all_classes)\s*\(',line):sites.append(dict(path=p.relative_to(native).as_posix(),line=number,text=line.strip()))
    assert {r['path'] for r in sites}=={'gd_rt.cpp','gd_rt.hpp','gen/register_all.cpp','engine_wrapper.cpp'}
    register=(native/'gen/register_all.cpp').read_text('utf8')
    assert len(re.findall(r'gd::register_class\(&META_',register))==674
    assert 'proto.cls = gd::find_class(script_path ? script_path : "res://gd_core_items/Item.gd");' in engine
    assert 'if (!proto.cls) proto.cls = &META_Gd__gd_core_items__Item;' in engine
    return dict(packed_struct_declarations_sha256=hashlib.sha256(structs(engine).encode()).hexdigest(),c_abi_names=sorted(name for name,_ in signatures),
        no_object_metadata_or_callback_handles_in_packed_inputs=True,no_object_or_callback_parameters_in_22_c_abi_entrypoints=True,
        known_generated_registrations=674,class_registry_mutation_and_initialization_sites=sites,
        trust_boundary='Only run_one_internal sets closed_world, from the registry seal before constructing its entire private graph. Packed input is scalar/string data; script paths resolve the registry, not executable code. Any registered foreign metadata permanently unseals future battles. No generated battle method registers classes.',
        open_cpp_contexts_default_to_observers=True,concurrent_cpp_class_registry_mutation_not_newly_supported='The existing registry is not a concurrent mutation API; packed entrypoints provide no callbacks during run_one_internal')

def transform(native):
    old_watch,old_runtime=base.WATCH,base.RUNTIME
    try:
        base.WATCH=base.once(old_watch,'bool enabled=false,usable=true,collect=false;','bool enabled=false,usable=true,collect=false,closed_world=false;')
        base.WATCH+='\nvoid native_timer_registered_class(const GdClassMeta*);\nbool native_timer_registry_closed();\n'
        marker='    auto& w=ctx.native_timer_watch;'
        assert old_runtime.count(marker)==2
        base.RUNTIME=old_runtime.replace(marker,marker+'\n    if(w.closed_world)return;')
        result=base.transform(native)
    finally:base.WATCH,base.RUNTIME=old_watch,old_runtime
    p=native/'gd_rt.cpp';text=p.read_text('utf8')
    text=base.once(text,'void register_class(const GdClassMeta* meta) {','void register_class(const GdClassMeta* meta) {\n    native_timer_registered_class(meta);')
    text+=REGISTRY;p.write_text(text,encoding='utf8',newline='\n')
    p=native/'engine_wrapper.cpp';text=p.read_text('utf8')
    text=base.once(text,'    battle.native_timer_watch.enabled=true;','    battle.native_timer_watch.enabled=true;\n    battle.native_timer_watch.closed_world=gd::native_timer_registry_closed();')
    text+='\nextern "C" int gd_diag_native_timer_closed_mode(){return tl_battle_ctx.native_timer_watch.closed_world?1:0;}\n'
    p.write_text(text,encoding='utf8',newline='\n')
    result['source_sha256']={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    result['closed_world_proof']=closure_proof(native)
    result['revision']='sealed packed-input observer specialization'
    return result

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    WORK.mkdir(exist_ok=True);source=WORK/'prototype_src';assert not source.exists()
    shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    report=transform(source)
    (WORK/'transform.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in report['closed_world_proof'].items() if k!='class_registry_mutation_and_initialization_sites'},indent=2))

if __name__=='__main__':main()
