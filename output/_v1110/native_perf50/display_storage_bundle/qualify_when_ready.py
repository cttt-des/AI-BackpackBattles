"""Qualify only after the complete predeclared AB decision, never a favorable subset."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import psutil
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
def run(script,log,*args):
    print('Starting '+script,flush=True);path=WORK/log;assert not path.exists(),path
    with path.open('w',encoding='utf8') as output:subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/script),*map(str,args)],stdout=output,stderr=subprocess.STDOUT,check=True)
    print('Passed '+script,flush=True)
def main():
    p=argparse.ArgumentParser();p.add_argument('--pid',type=int,required=True);p.add_argument('--created',type=float,required=True)
    p.add_argument('--ready-receipt',type=Path);a=p.parse_args()
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    if a.ready_receipt is not None:
        ready=json.loads(a.ready_receipt.read_bytes())
        assert ready['passed'] and ready['all_remaining_prechecks_passed'] and ready['first24_completed_once']
        assert ready['dll_sha256']==hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest()
        assert ready['source_manifest_sha256']==hashlib.sha256((WORK/'source_before_build.json').read_bytes()).hexdigest()
        assert ready['ab_assessment_sha256']==hashlib.sha256((WORK/'ab_assessment.json').read_bytes()).hexdigest()
        assert json.loads((WORK/'source_before_build.json').read_bytes())=={f.relative_to(WORK/'bundle_src').as_posix():hashlib.sha256(f.read_bytes()).hexdigest() for f in (WORK/'bundle_src').rglob('*') if f.is_file()}
        print('Completed unchanged-source validation and original first24 confirmed by receipt',flush=True)
        process=None
    else:
        try:process=psutil.Process(a.pid)
        except psutil.NoSuchProcess:process=None
    if process is not None:
        assert abs(process.create_time()-a.created)<0.001
        assert any('display_storage_bundle/build_bundle.py' in part.replace('\\','/') for part in process.cmdline())
        print('Awaiting identified live build '+str(process.pid),flush=True)
        while process.is_running():
            try:process.wait(timeout=30)
            except psutil.TimeoutExpired:continue
            break
    path=WORK/'ab_assessment.json';assert path.exists(),'Original runner incomplete; inspect its original log, do not restart'
    first=json.loads(path.read_bytes());assert all(x['pairs']==24 for x in first['metrics'].values())
    clean=first['status']=='positive_combined_evidence' and all(x['paired_median_time_reduction_pct']>0 and x['sum_time_reduction_pct']>0 for row in first['leave_one_group_out_sensitivity'] for x in row.values())
    selected=path
    if not clean and first['status']!='consistent_regression_bundle_only':
        run('run_bounded_followup.py','bounded_followup.log');selected=WORK/'ab_assessment_32.json'
    result=json.loads(selected.read_bytes());actual=hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest()
    assert result['candidate_dll_sha256']==actual
    decision=dict(selected_assessment=str(selected),assessment_sha256=hashlib.sha256(selected.read_bytes()).hexdigest(),candidate_dll_sha256=actual,status=result['status'],original24_retained=True,no_more_same_source_groups=True,not_deployed=True)
    out=WORK/'candidate_decision.json';assert not out.exists();out.write_text(json.dumps(decision,indent=2)+'\n',encoding='utf8')
    if result['status']!='positive_combined_evidence':print('All comparison evidence retained; no qualification: '+result['status'],flush=True);return
    run('verify_object_routes_after_ab.py','post_ab_directed_regressions.log')
    run('run_full_gate.py','full_gate.log','bundle');run('finish_gate.py','finish_gate.log');run('run_release_measurements.py','release_measurements.log')
    print('Qualification and first release measurements finished; installation still requires evidence review',flush=True)
if __name__=='__main__':main()
