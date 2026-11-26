"""Await the original semantic build, then run independent retained suites."""
import json
import os
import subprocess
import sys
import psutil
from prepare_restored_private_snapshots import STAGE,WORK,sha,verify_projection

def main():
    p=psutil.Process();p.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    identity=WORK/'live_semantic_suite.json';assert not identity.exists()
    identity.write_text(json.dumps(dict(pid=p.pid,created=p.create_time(),script=str(__file__)))+'\n',encoding='utf8')
    log=WORK/'private_checks_first.log';assert not log.exists()
    with log.open('w',encoding='utf8') as stream:
        subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'verify_restored_private_snapshots.py')],stdout=stream,stderr=subprocess.STDOUT,check=True)
    private=json.loads((WORK/'correctness.json').read_bytes());assert private['passed'] and private['cases']==234880
    from verify_restored_display_storage import verify as display_verify
    from verify_restored_control import verify as control_verify
    display=display_verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'retained_display.json')
    control=control_verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'retained_control.json')
    assert display['passed'] and display['cases']==21888 and control['passed'] and control['cases']==44608
    verify_projection(WORK/'prototype_src')
    result=dict(passed=True,private_cases=234880,retained_display_cases=21888,retained_control_cases=44608,
        total_cases=301376,dll_sha256=sha(WORK/'prototype.dll'),no_speed_claim=True,
        exact_combination_verified_without_dropping_deployed_components=True)
    (WORK/'semantic_suite.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result),flush=True)

if __name__=='__main__':main()
