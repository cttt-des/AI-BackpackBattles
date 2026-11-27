"""Finish only the interrupted current trial, without restarting observed timings."""
import ast
import hashlib
import json
from pathlib import Path
import runpy
import subprocess
import sys
import psutil
STAGE=Path(__file__).resolve().parent
WORK=STAGE/'native_perf50/assembly_membership_bundle'
REPO=STAGE.parents[1]
EXPECTED='291d58514d69e9bdf8eb30b875a133bcfa7d8a2af357d95fb92773c9ebff851d'
BASELINE='d2064b3f17d8168cf87a2e9f46e9fb336ffe4aaf6581c27d93350b2c41477a57'
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def save(name,value):
    p=WORK/name;assert not p.exists();p.write_text(json.dumps(value,indent=2)+'\n',encoding='utf8')

def main():
    proc=psutil.Process();proc.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    identity=WORK/'live_formal_driver.json';old=json.loads(identity.read_bytes())
    for row in old.values():
        try:
            p=psutil.Process(row['pid']);assert p.create_time()!=row['created'] or not p.is_running()
        except psutil.NoSuchProcess:pass
    frozen=json.loads((WORK/'source_before_build.json').read_bytes());src=WORK/'bundle_src';dll=WORK/'bundle.dll'
    assert sha(dll)==EXPECTED and frozen=={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    assert sha(STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==BASELINE
    objects=json.loads((WORK/'release_objects.json').read_bytes());assert len(objects['objects_sha256'])==20
    assert all(sha(Path(objects['object_directory'])/n)==h for n,h in objects['objects_sha256'].items())
    assert not (WORK/'comparison.log').exists() and not list(WORK.glob('ab_*.json'))
    kept=WORK/'live_formal_driver_before_user_pause.json'
    if not kept.exists():identity.rename(kept)
    else:
        assert (WORK/'resume_after_pause_attempt1_identity.json').read_bytes()==identity.read_bytes()
    live={'driver':dict(pid=proc.pid,created=proc.create_time())};identity.write_text(json.dumps(live,indent=2)+'\n',encoding='utf8')
    original=(WORK/'verify_resolved.py').read_text('utf8');suffix=original[original.index('    tests=('):original.index("\nif __name__=='__main__':")]
    prefix=original[:original.index('def main():')]
    setup='''def main():
    dll=WORK/'bundle.dll';src=WORK/'bundle_src'
    before={p.relative_to(src).as_posix():digest(p) for p in src.rglob('*') if p.is_file()}
    directory=Path((WORK/'inline_candidate_test_directory.txt').read_text('utf8'))
    assert directory.is_dir() and digest(directory/'libgdcore.dll')==digest(dll)
    for name in ['resolved_abi.json','item_layout_offsets.json','resolved_boundary_test.json','buff_chunk_differential.json','addspeed_trace_differential.json']:
        r=json.loads((WORK/name).read_bytes());assert r.get('dll_sha256',r.get('candidate_dll_sha256'))==digest(dll)
'''
    anchor='    for number,(file,receipt,extra) in enumerate(tests):\n'
    addition='''        saved=WORK/receipt
        if saved.exists():
            r=json.loads(saved.read_bytes());assert r['passed'] and r['dll_sha256']==digest(dll) and r['compiled_against_candidate_headers']
            print('Retained completed '+receipt,flush=True);continue
'''
    assert suffix.count(anchor)==1;suffix=suffix.replace(anchor,anchor+addition)
    code=prefix+setup+suffix+"\nif __name__=='__main__':main()\n";ast.parse(code)
    resumed=WORK/'verify_resolved_remaining_after_pause.py'
    if resumed.exists():assert resumed.read_text('utf8')==code
    else:resumed.write_text(code,encoding='utf8')
    module=ast.parse(original);main_node=next(n for n in module.body if isinstance(n,ast.FunctionDef) and n.name=='main')
    assignment=next(n for n in main_node.body if isinstance(n,ast.Assign) and any(isinstance(x,ast.Name) and x.id=='tests' for x in n.targets))
    tests=eval(compile(ast.Expression(assignment.value),'owned_fixture_list','eval'),dict(WORK=WORK))
    fixture_hashes={}
    for filename,_,_ in tests:
        p=STAGE/filename;archived=subprocess.check_output(['git','show','f03dec6f9937ac6c829a8d277ca981917c1f9e32:'+p.relative_to(REPO).as_posix()],cwd=REPO)
        current=p.read_bytes()
        assert archived.replace(b'\r\n',b'\n')==current.replace(b'\r\n',b'\n'),filename
        fixture_hashes[filename]=dict(local_sha256=sha(p),archive_sha256=hashlib.sha256(archived).hexdigest(),equal_after_CRLF_normalization=True)
    save('user_pause_continuation_evidence.json',dict(passed=True,reason='User requested finishing the current interrupted optimization before a potion ordering audit',dll_sha256=sha(dll),source_manifest_sha256=sha(WORK/'source_before_build.json'),all20_objects_unchanged=True,no_AB_samples_observed_before_pause=True,fixture_sha256=fixture_hashes,original_verify_log_sha256=sha(WORK/'verify.log')))
    run=runpy.run_path(str(WORK/'validate_then_compare.py'))['run']
    run(resumed.name,'verify_remaining_after_pause.log')
    steps=[('inspect_variant.py','release_audit.log',['--dll',dll,'--out',WORK/'release_audit.json']),('test_regeneration_guards.py','regeneration_guards.log',[]),('test_full_regeneration.py','full_regeneration.log',[]),('run_comparison.py','comparison.log',[])]
    for script,log,args in steps:
        assert not (WORK/log).exists();run(script,log,*args)
    ready=dict(passed=True,all_remaining_prechecks_passed=True,first24_completed_once=True,dll_sha256=sha(dll),source_manifest_sha256=sha(WORK/'source_before_build.json'),ab_assessment_sha256=sha(WORK/'ab_assessment.json'))
    save('preflight_resume_receipt.json',ready)
    path=WORK/'qualification_after_pause.log';assert not path.exists()
    with path.open('w',encoding='utf8') as output:
        child=subprocess.Popen([sys.executable,'-u','-X','utf8',str(WORK/'qualify_when_ready.py'),'--pid','0','--created','0','--ready-receipt',str(WORK/'preflight_resume_receipt.json')],stdout=output,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
        live['qualifier']=dict(pid=child.pid,created=psutil.Process(child.pid).create_time());identity.write_text(json.dumps(live,indent=2)+'\n',encoding='utf8')
        assert child.wait()==0,'Inspect original logs; never restart observed timings'
    print('Current optimization qualification finished',flush=True)

if __name__=='__main__':main()
