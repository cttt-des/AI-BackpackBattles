"""Real compiler/DLL test: changing only build flags must rebuild every unit."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import ctypes
import hashlib
import json
from pathlib import Path
import runpy
import shutil
import tempfile
from optimize_native_build_config_dependencies import with_self_dependency

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('native',type=Path);p.add_argument('--out',type=Path,required=True);a=p.parse_args()
    import psutil
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    root=Path(tempfile.mkdtemp(prefix='native-config-dependency-'))
    (root/'gen/hdrs').mkdir(parents=True);(root/'gen/shards').mkdir()
    config=root/'build_windows.py';shutil.copyfile(a.native/'build_windows.py',config)
    for name in ('gd_rt.hpp','builtin_syms.hpp','gen/sym_ids.hpp','gen/class_metas.hpp'):
        (root/name).write_text('#pragma once\n',encoding='utf8')
    source=root/'gd_rt.cpp'
    source.write_text('#ifndef NATIVE_CONFIG_PROBE\n#define NATIVE_CONFIG_PROBE 0\n#endif\n'
                      'extern "C" __declspec(dllexport) int config_probe(){return NATIVE_CONFIG_PROBE;}\n',encoding='utf8')
    for i,name in enumerate(('engine_wrapper.cpp','gen/sym_ids.cpp','gen/register_all.cpp','gen/shards/shard_00.cpp')):
        (root/name).write_text(f'int config_dummy_{i}(){{return {i};}}\n',encoding='utf8')
    cpp_hash=hashlib.sha256(source.read_bytes()).hexdigest();libraries=[];counts=[]
    def run(label):
        module=runpy.run_path(str(config));build=module['build'];namespace=build.__globals__;objects=root/'objects'
        original_compile=namespace['_compile_unit'];compiled=[]
        def compile_unit(src,obj):compiled.append(src.name);original_compile(src,obj)
        namespace.update(OBJ_DIR=objects,OUT_TMP=objects/'libgdcore.dll',OUT_LIB=root/'artifact.dll',CXX='D:/mingw64/bin/g++.exe',
                         _compile_unit=compile_unit,ThreadPoolExecutor=lambda max_workers:ThreadPoolExecutor(max_workers=1))
        dll=build();copied=root/(label+'.dll');shutil.copyfile(dll,copied)
        lib=ctypes.CDLL(str(copied));libraries.append(lib);lib.config_probe.argtypes=[];lib.config_probe.restype=ctypes.c_int
        counts.append(len(compiled));return lib.config_probe()
    first=run('initial')
    s=config.read_text('utf8');assert 'COMMON = ["-O3",' in s
    s=s.replace('COMMON = ["-O3",','COMMON = ["-DNATIVE_CONFIG_PROBE=1", "-O3",',1);config.write_text(s,encoding='utf8',newline='\n')
    stale=run('stale')
    config.write_text(with_self_dependency(config.read_text('utf8')),encoding='utf8',newline='\n')
    fixed=run('fixed');repeated=run('repeated')
    config.write_text(config.read_text('utf8').replace('-DNATIVE_CONFIG_PROBE=1','-DNATIVE_CONFIG_PROBE=2'),encoding='utf8',newline='\n')
    changed_again=run('changed_again')
    assert (first,stale,fixed,repeated,changed_again)==(0,0,1,1,2)
    assert counts==[5,0,5,0,5],counts
    assert hashlib.sha256(source.read_bytes()).hexdigest()==cpp_hash
    report={'passed':True,'initial':first,'stale_after_flags_only_edit':stale,'fixed':fixed,'unchanged_repeat':repeated,
            'second_flags_only_edit':changed_again,'compiled_units':counts,'cpp_source_unchanged':True,'real_compiler_and_loaded_dlls':True}
    a.out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8',newline='\n');print(json.dumps(report,indent=2))

if __name__=='__main__':main()
