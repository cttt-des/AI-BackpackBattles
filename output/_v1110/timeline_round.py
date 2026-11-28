"""Full normal/fresh PGO build, restricted checks, release gate and frozen AB."""
import json,os,runpy,shutil,subprocess,sys,tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
import psutil
import prepare_timeline_round as p
from native_build_storage import isolated_build,adapt_formal_builder
from native_build_schedule import select_jobs

@isolated_build
def normal():
    p.verify_projection(p.WORK/'bundle_src');assert not (p.WORK/'prototype.dll').exists();psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    root=Path(tempfile.mkdtemp(prefix='timeline-normal-'));objects=root/'objects';os.environ.update(NATIVE_SIM_OBJ=str(objects),NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe')
    m=runpy.run_path(str(p.WORK/'bundle_src/build_windows.py'));schedule=select_jobs(0,0);m['build'].__globals__['ThreadPoolExecutor']=lambda max_workers:ThreadPoolExecutor(max_workers=min(schedule['frontend_jobs'],max_workers))
    library=m['build']();shutil.copyfile(library,p.WORK/'prototype.dll');files=list(objects.glob('*.o'));assert len(files)==20
    p.save('prototype_build.json',dict(passed=True,dll_sha256=p.sha(p.WORK/'prototype.dll'),source_manifest_sha256=p.sha(p.WORK/'source_before_build.json'),full20_fresh_normal=True,schedule=schedule,objects_sha256={s.name:p.sha(s) for s in files},semantic_only=True));print('Full normal timeline build complete',flush=True)

@isolated_build
def formal():
    assert json.loads((p.WORK/'prototype_affected_tests.json').read_bytes())['passed'];p.verify_projection(p.WORK/'bundle_src')
    assert json.loads((p.WORK/'prototype_container_receipt.json').read_bytes())['passed']
    assert json.loads((p.WORK/'prototype_real200_coverage.json').read_bytes())['passed']
    script=p.STAGE/'build_ordering_release.py';text=script.read_text('utf8').replace('from prepare_ordering_correctness import','from prepare_timeline_round import')
    text=text.replace("WORK/'prototype_ordering_tests.json'","WORK/'prototype_affected_tests.json'")
    old="    assert all(json.loads((WORK/n).read_bytes())['passed'] for n in ('python_compiled_ordering_tests.json','python_source_ordering_tests.json'))";assert text.count(old)==1;text=text.replace(old,"    verify_projection(WORK/'bundle_src')")
    text=text.replace('WORK,BASE,ACCEPTED,EXPECTED,sha,inventory,save','WORK,BASE,ACCEPTED,EXPECTED,sha,inventory,save,verify_projection')
    text=adapt_formal_builder(text).replace('ordering-formal-','timeline-formal-')
    text=text.replace("build_dll(src,objects/'instrumented.dll',2,","build_dll(src,objects/'instrumented.dll',0,").replace("build_dll(src,objects/'release.dll',2,","build_dll(src,objects/'release.dll',0,")
    exec(compile(text,str(script),'exec'),dict(__name__='__main__',__file__=str(Path(__file__).resolve())))

def compare(action):
    text=(p.STAGE/'compare_structure_round.py').read_text('utf8').replace('from prepare_structure_round import','from prepare_timeline_round import')
    sys.argv=[str(p.STAGE/'timeline_round.py'),action];exec(compile(text,str(p.STAGE/'compare_structure_round.py'),'exec'),dict(__name__='__main__',__file__=__file__))

if __name__=='__main__':{'normal':normal,'formal':formal,'timing':lambda:compare('timing'),'analyze':lambda:compare('analyze')}[sys.argv[1]]()
