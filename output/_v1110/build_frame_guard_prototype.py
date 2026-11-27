"""Only shard03 consumes the changed frame body; reuse19 verified normal units."""
import json,os,runpy,shutil,subprocess,tempfile
from pathlib import Path
import psutil
from prepare_frame_guard_reuse import STAGE,WORK,ACCEPTED,sha,inventory,save,verify_projection
def main():
    process=psutil.Process();process.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS);verify_projection(WORK/'bundle_src')
    assert not (WORK/'prototype.dll').exists()
    old=json.loads((ACCEPTED/'prototype_build.json').read_bytes())['objects_sha256']
    repaired=json.loads((ACCEPTED/'live_semantic_build.json').read_bytes())
    prior=STAGE/'native_perf50/assembly_membership_prototype';state=json.loads((prior/'live_semantic_build.json').read_bytes())
    paths={}
    for name,h in old.items():
        candidates=[Path(repaired['object_directory'])/name,Path(state['object_directory'])/name]
        if name in state.get('reused_objects',{}):candidates.append(Path(state['reused_objects'][name]))
        paths[name]=next(p for p in candidates if p.exists() and sha(p)==h)
    root=Path(tempfile.mkdtemp(prefix='frame-guard-semantic-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'));objects=root/'objects';objects.mkdir();scratch=root/'scratch';scratch.mkdir()
    env=dict(os.environ,TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch))
    save('live_semantic_build.json',dict(pid=process.pid,created=process.create_time(),root=str(root),object_directory=str(objects),reused_objects={n:str(p) for n,p in paths.items() if n!='shard_03.o'}))
    source=WORK/'bundle_src';flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];cxx='D:/mingw64/bin/g++.exe'
    # Reject another consumer before relying on the unchanged19 objects.
    consumers=[p.name for p in (source/'gen/shards').glob('*.cpp') if 'native_frame_segment_tick(' in p.read_text('utf8')];assert consumers==['shard_03.cpp']
    with (WORK/'prototype_compile.log').open('wb') as log:subprocess.run([cxx,*flags,'-c',str(source/'gen/shards/shard_03.cpp'),'-o',str(objects/'shard_03.o')],stdout=log,stderr=subprocess.STDOUT,env=env,check=True)
    paths['shard_03.o']=objects/'shard_03.o'
    with (WORK/'prototype_link.log').open('wb') as log:subprocess.run([cxx,*flags,'-shared','-static','-o',str(objects/'libgdcore.dll'),*map(str,paths.values())],stdout=log,stderr=subprocess.STDOUT,env=env,check=True)
    shutil.copyfile(objects/'libgdcore.dll',WORK/'prototype.dll');verify_projection(source)
    save('prototype_build.json',dict(passed=True,dll_sha256=sha(WORK/'prototype.dll'),source_sha256=inventory(source),changed_normal_units=['shard_03.o'],unchanged19_objects_verified=True,objects_sha256={n:sha(p) for n,p in paths.items()},semantic_only=True,not_for_deployment_or_speed_claims=True))
    print('Normal candidate ready; source and19 reused objects verified',flush=True)
if __name__=='__main__':main()
