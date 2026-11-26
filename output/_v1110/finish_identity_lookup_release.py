"""Run the review, deployment and local archive only after formal work terminates."""
import json
import subprocess
import sys
import psutil
from prepare_native_identity_lookup import STAGE
from record_identity_lookup_round import terminal
WORK=STAGE/'native_perf50/identity_lookup_bundle'

def run(path,log,*args):
    target=WORK/log;assert not target.exists()
    print('Starting '+path.name,flush=True)
    with target.open('w',encoding='utf8') as output:
        subprocess.run([sys.executable,'-u','-X','utf8',str(path),*map(str,args)],stdout=output,stderr=subprocess.STDOUT,check=True)
    print('Passed '+path.name,flush=True)

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    terminal()
    d=json.loads((WORK/'candidate_decision.json').read_bytes())
    assert d['status']=='positive_combined_evidence'
    m=json.loads((WORK/'measurements_summary.json').read_bytes());assert m['raw24_gate_passed']
    run(STAGE/'review_identity_lookup_release.py','pre_install_review_first.log')
    run(WORK/'install_verified.py','installation_first.log','bundle','--assessment',d['selected_assessment'],'--speed-report',WORK/'bundle_serial.json')
    run(WORK/'verify_installed.py','post_install_verification_first.log')
    run(STAGE/'record_identity_lookup_round.py','terminal_record_first.log')
    run(STAGE/'archive_identity_lookup_round.py','checkpoint_prepare_first.log','--commit')
    print('Deployment verified and archive prepared; upload requires no further timing',flush=True)

if __name__=='__main__':main()
