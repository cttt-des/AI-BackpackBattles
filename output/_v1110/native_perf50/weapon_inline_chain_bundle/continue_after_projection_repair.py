"""Continue unchanged-code checks after a report-key repair, before first timing."""
import ast
import json
from pathlib import Path
import runpy
import subprocess
import sys
import psutil
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
sys.path.insert(0,str(STAGE))
from prepare_native_weapon_inline_chain import sha,verify_projection,EXPECTED,BASE

def save(name,value):
    p=WORK/name;assert not p.exists();p.write_text(json.dumps(value,indent=2)+'\n',encoding='utf8')

def main():
    p=psutil.Process();p.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    identity=WORK/'live_formal_driver.json'
    for row in json.loads(identity.read_bytes()).values():
        try:
            q=psutil.Process(row['pid']);assert abs(q.create_time()-row['created'])>=0.001 or not q.is_running()
        except psutil.NoSuchProcess:pass
    old=WORK/'live_formal_driver_attempt1.json';assert not old.exists();identity.rename(old)
    live=dict(driver=dict(pid=p.pid,created=p.create_time()))
    identity.write_text(json.dumps(live,indent=2)+'\n',encoding='utf8')
    repair=json.loads((WORK/'projection_contract_repair.json').read_bytes());assert repair['passed'] and repair['no_benchmark_has_started']
    dll=WORK/'bundle.dll';assert sha(dll)==repair['dll_sha256']
    assert sha(WORK/'source_before_build.json')==repair['source_manifest_sha256']
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    frozen=json.loads((WORK/'source_before_build.json').read_bytes())
    assert frozen=={x.relative_to(WORK/'bundle_src').as_posix():sha(x) for x in (WORK/'bundle_src').rglob('*') if x.is_file()}
    assert verify_projection(WORK/'bundle_src')['exact_inverse_matches_retained_source']
    assert not list(WORK.glob('ab_*.json')) and not (WORK/'comparison.log').exists()
    options=json.loads((WORK/'compiled_option_receipt.json').read_bytes());assert options['passed'] and options['dll_sha256']==sha(dll)
    obj=json.loads((WORK/'release_objects.json').read_bytes());assert len(obj['objects_sha256'])==20
    assert all(sha(Path(obj['object_directory'])/n)==h for n,h in obj['objects_sha256'].items())
    original=(WORK/'build_first.log').read_text('utf8',errors='replace')
    tree=ast.parse((WORK/'validate_then_compare.py').read_text('utf8'))
    main_node=next(n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name=='main')
    calls=[n.value for n in main_node.body if isinstance(n,ast.Expr) and isinstance(n.value,ast.Call) and isinstance(n.value.func,ast.Name) and n.value.func.id=='run']
    at=next(i for i,n in enumerate(calls) if n.args[0].value=='verify_motion_indices.py')
    completed=[n.args[0].value for n in calls[:at]]
    assert all('Passed '+n in original for n in completed)
    save('preserved_precheck_receipts.json',dict(passed=True,dll_sha256=sha(dll),completed_without_repetition=completed,
        original_build_log_sha256=sha(WORK/'build_first.log'),original_identity_sha256=sha(old),source_manifest_sha256=sha(WORK/'source_before_build.json')))
    run=runpy.run_path(str(WORK/'validate_then_compare.py'))['run']
    continued=[]
    for call in calls[at:]:
        script,log=call.args[0].value,call.args[1].value
        if script=='verify_motion_indices.py':log='motion_indices_tests_after_projection_contract.log'
        assert not (WORK/log).exists(),log
        extra=[]
        if script=='inspect_variant.py':extra=['--dll',dll,'--out',WORK/'release_audit.json']
        else:assert len(call.args)==2
        if script=='run_comparison.py':assert json.loads((WORK/'buff_chunk_differential.json').read_bytes())['passed']
        run(script,log,*extra);continued.append(script)
    assert continued[-1]=='run_comparison.py'
    assessment=json.loads((WORK/'ab_assessment.json').read_bytes())
    assert all(row['pairs']==24 for row in assessment['metrics'].values())
    receipt=dict(passed=True,all_remaining_prechecks_passed=True,first24_completed_once=True,dll_sha256=sha(dll),
        source_manifest_sha256=sha(WORK/'source_before_build.json'),ab_assessment_sha256=sha(WORK/'ab_assessment.json'),
        continued_checks=continued,preserved_passed_checks_sha256=sha(WORK/'preserved_precheck_receipts.json'),
        projection_contract_repair_sha256=sha(WORK/'projection_contract_repair.json'),no_candidate_source_dll_or_pgo_rebuild=True)
    save('preflight_resume_receipt.json',receipt)
    log=WORK/'qualification_continued.log';assert not log.exists()
    with log.open('w',encoding='utf8') as out:
        q=subprocess.Popen([sys.executable,'-u','-X','utf8',str(WORK/'qualify_when_ready.py'),'--pid','0','--created','0',
            '--ready-receipt',str(WORK/'preflight_resume_receipt.json')],stdout=out,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
        live['qualifier']=dict(pid=q.pid,created=psutil.Process(q.pid).create_time())
        identity.write_text(json.dumps(live,indent=2)+'\n',encoding='utf8')
        assert q.wait()==0,'Inspect original continuation logs; do not restart observed timings'
    print('Continuation and complete qualification protocol terminated',flush=True)

if __name__=='__main__':main()
