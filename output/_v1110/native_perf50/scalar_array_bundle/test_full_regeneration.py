"""Exercise the real GDScript-to-C++ and performance pipeline in an isolated copy."""
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
SIM=STAGE/'sim_native'

def canon(data):return data.decode('utf8').replace('\r\n','\n').encode('utf8')

def main():
    root=Path(tempfile.mkdtemp(prefix='native-source-regeneration-'))
    (WORK/'full_regeneration_directory.txt').write_text(str(root),encoding='utf8')
    stage=root/'output/_v1110';stage.mkdir(parents=True)
    for p in STAGE.glob('*.py'):shutil.copyfile(p,stage/p.name)
    shutil.copyfile(STAGE/'native_lovers_particles_probe_result.json',stage/'native_lovers_particles_probe_result.json')
    target_sim=stage/'sim_native'
    target_cpp=target_sim/'native_sim_cpp'
    for relative in ('gd_core','gd_core_items','native_sim_cpp/gd_core','native_sim_cpp/gd_core_items','native_sim_cpp/tools','native_sim_cpp/native_sim'):
        shutil.copytree(SIM/relative,target_sim/relative,ignore=shutil.ignore_patterns('__pycache__','*.pyc','*.o','*.gcda','*.gcno'))
    data=stage/'native_perf50/scalar_array_bundle';data.mkdir(parents=True)
    shutil.copyfile(WORK/'verified_bundle_pending.py',stage/'optimize_native_verified_bundle.py')
    shutil.copyfile(WORK/'regeneration_manifest.json',data/'regeneration_manifest.json')
    shutil.copytree(WORK/'before_runtime',data/'before_runtime')
    shutil.copytree(WORK/'bundle_src',data/'bundle_src',ignore=shutil.ignore_patterns('__pycache__','*.pyc'))
    script=(STAGE/'rebuild_native_lovers_candidate.py').read_text('utf8')
    prefix=script.split('os.environ["NATIVE_SIM_CXX"] =',1)[0]
    assert prefix!=script
    source_only=stage/'rebuild_source_only.py'
    source_only.write_text(prefix+'\nprint("Full source-generation pipeline completed without compiling")\n',encoding='utf8',newline='\n')
    baseline=target_cpp/'native_sim/libgdcore.dll'
    objects=root/'objects';objects.mkdir();shutil.copyfile(baseline,objects/'libgdcore.dll')
    environment=dict(os.environ,NATIVE_SIM_OBJ=str(objects))
    command=[sys.executable,'-u','-X','utf8',str(source_only),'--baseline',str(baseline),'--out',str(root/'not_built.dll'),'--native-perf50']
    manifest=json.loads((WORK/'regeneration_manifest.json').read_bytes())
    for iteration in (1,2):
        with (WORK/f'full_regeneration_{iteration}.log').open('wb') as log:
            subprocess.run(command,cwd=stage,env=environment,stdout=log,stderr=subprocess.STDOUT,check=True)
        for row in manifest['inventory']:
            p=target_cpp/'native_sim'/row['path']
            assert hashlib.sha256(canon(p.read_bytes())).hexdigest()==row['after_canonical_sha256'],row['path']
        current={p.relative_to(target_cpp/'native_sim').as_posix():(hashlib.sha256(p.read_bytes()).hexdigest(),p.stat().st_mtime_ns)
                 for p in (target_cpp/'native_sim').rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py')}
        if iteration==1:before=current
        else:assert current==before,'Second generation changed source bytes or timestamps'
    result={'passed':True,'full_gdscript_transpiler_and_performance_pipeline':True,
            'source_files_matching_compiled_candidate':len(manifest['inventory']),
            'repeat_bytes_and_mtime_idempotent':True,'compiler_invoked':False,'isolated_directory':str(root)}
    (WORK/'full_regeneration_test.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps(result,indent=2))

if __name__=='__main__':main()
