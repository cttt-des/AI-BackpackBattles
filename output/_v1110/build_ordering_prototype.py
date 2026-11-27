"""Two changed normal units for semantics only; the release rebuilds all20."""
from concurrent.futures import ThreadPoolExecutor
import json,os,runpy,shutil,subprocess,tempfile,psutil
from pathlib import Path
from prepare_ordering_correctness import STAGE,WORK,BASE,ACCEPTED,EXPECTED,sha,inventory,save

def main():
    p=psutil.Process();p.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert sha(BASE/'libgdcore.dll')==EXPECTED and not (WORK/'prototype.dll').exists()
    normal=STAGE/'native_perf50/assembly_membership_prototype'
    old=json.loads((normal/'build.json').read_bytes())['objects_sha256'];state=json.loads((normal/'live_semantic_build.json').read_bytes())
    assert inventory(WORK/'bundle_src')==json.loads((WORK/'source_before_build.json').read_bytes())
    assert json.loads((normal/'transform.json').read_bytes())['source_sha256']==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    old_paths={n:Path(state['object_directory'])/n if (Path(state['object_directory'])/n).exists() else Path(state['reused_objects'][n]) for n in old}
    assert all(sha(old_paths[n])==h for n,h in old.items())
    root=Path(tempfile.mkdtemp(prefix='ordering-semantic-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'));objects=root/'objects';objects.mkdir();scratch=root/'scratch';scratch.mkdir()
    os.environ.update(TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch));tempfile.tempdir=str(scratch)
    save('live_semantic_build.json',dict(pid=p.pid,created=p.create_time(),root=str(root),object_directory=str(objects)))
    source=WORK/'bundle_src';flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    changed={'gd_rt.o','shard_12.o'}
    def compile_one(name):
        cpp=source/('gd_rt.cpp' if name=='gd_rt.o' else 'gen/shards/shard_12.cpp')
        with (WORK/('prototype_compile_'+Path(name).stem+'.log')).open('wb') as log:
            subprocess.run([compiler,*flags,'-c',str(cpp),'-o',str(objects/name)],stdout=log,stderr=subprocess.STDOUT,check=True)
    with ThreadPoolExecutor(max_workers=2) as pool:list(pool.map(compile_one,sorted(changed)))
    paths={n:objects/n if n in changed else old_paths[n] for n in old}
    with (WORK/'prototype_link_first.log').open('wb') as log:
        subprocess.run([compiler,*flags,'-shared','-static','-save-temps=obj','-o',str(objects/'libgdcore.dll'),*[str(paths[n]) for n in old]],stdout=log,stderr=subprocess.STDOUT,check=True)
    shutil.copyfile(objects/'libgdcore.dll',WORK/'prototype.dll')
    assert all(sha(old_paths[n])==h for n,h in old.items())
    save('prototype_build.json',dict(passed=True,dll_sha256=sha(WORK/'prototype.dll'),source_sha256=inventory(source),changed_normal_units=sorted(changed),reused_objects=18,all_unchanged_objects_sha256_verified=True,no_layout_changes=True,semantic_only=True,not_for_deployment_or_speed_claims=True,objects_sha256={n:sha(p) for n,p in paths.items()}))
    print('Normal semantic DLL ready',flush=True)
if __name__=='__main__':main()
