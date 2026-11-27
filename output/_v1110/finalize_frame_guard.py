"""Finish the predeclared experiment, then deploy only an accepted winner."""
import argparse,json,subprocess,sys
from prepare_frame_guard_reuse import STAGE,WORK,sha
def run(name):subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/name)],check=True)
def main():
    parser=argparse.ArgumentParser();parser.add_argument('--resume-after-ab',action='store_true');args=parser.parse_args()
    assert json.loads((WORK/'complete_correctness_gate.json').read_bytes())['passed']
    if not args.resume_after_ab:run('review_frame_guard_machine.py');run('run_frame_guard_comparison.py')
    decision=json.loads((WORK/'candidate_decision.json').read_bytes())
    assert decision['assessment_sha256']==sha(WORK/decision['selected_assessment']) and decision['candidate_dll_sha256']==sha(WORK/'bundle.dll')
    if decision['accepted']:
        if args.resume_after_ab:
            proof=json.loads((WORK/'post_ab_directed_checks.json').read_bytes());assert proof['passed'] and proof['dll_sha256']==sha(WORK/'bundle.dll')
            for name,digest in proof['receipts_sha256'].items():assert sha(WORK/name)==digest
        else:run('post_frame_guard_checks.py')
    run('measure_frame_guard.py')
    if decision['accepted'] and json.loads((WORK/'measurements_summary.json').read_bytes())['raw24_gate_passed']:run('install_frame_guard.py')
    run('close_frame_guard.py');run('archive_frame_guard.py')
    subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'archive_frame_guard.py'),'--upload'],check=True)
    print('Frame guard experiment closed and existing remote ref verified',flush=True)
if __name__=='__main__':main()
