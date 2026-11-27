"""Sequential authorized goal; never overlap timing with other work."""
import json,subprocess,sys
from prepare_structure_round import STAGE,WORK,sha,save
def read(name):return json.loads((WORK/name).read_bytes())
def run(script,phase,log):
    initial=WORK/log;path=initial;attempt=1
    while path.exists():attempt+=1;path=initial.with_name(initial.stem+f'_attempt{attempt}'+initial.suffix)
    save('goal_progress.json',dict(phase=phase,script=script,log=path.name,measurement_only_monitoring=phase in ('timing','measure'),finished=False))
    with path.open('wb') as stream:subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'run_native_managed.py'),str(STAGE/script),phase],stdout=stream,stderr=subprocess.STDOUT,check=True)
def main():
    assert (WORK/'prototype_build.json').exists()
    if not (WORK/'complete_correctness_gate.json').exists():run('structure_round.py','drive','qualification_driver_first.log')
    if not (WORK/'ab_timing_complete.json').exists():run('compare_structure_round.py','timing','comparison_first.log')
    if not (WORK/'candidate_decision.json').exists():run('compare_structure_round.py','analyze','ab_analysis.log')
    positive=read('candidate_decision.json')['accepted']
    if positive and not (WORK/'post_ab_directed_checks.json').exists():run('structure_round.py','post','post_first.log')
    if not (WORK/'measurements_summary.json').exists():run('structure_round.py','measure','measure_first.log')
    if positive and read('measurements_summary.json')['raw24_gate_passed'] and not (WORK/'installation.json').exists():run('structure_round.py','install','install_first.log')
    if not (WORK/'current_runtime_status.json').exists():run('finish_structure_round.py','close','close_first.log')
    # Freeze the goal progress before archival; only excluded driver/archive logs
    # and checkpoint receipts may change while the isolated-index backup runs.
    save('goal_progress.json',dict(phase='archival',finished=False,all_simulation_and_measurement_processes_finished=True))
    if not (WORK/'checkpoint_receipt.json').exists():
        with (WORK/'structure_archive_prepare.log').open('ab') as stream:subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'finish_structure_round.py'),'archive'],stdout=stream,stderr=subprocess.STDOUT,check=True)
    with (WORK/'structure_archive_upload.log').open('ab') as stream:subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'finish_structure_round.py'),'upload'],stdout=stream,stderr=subprocess.STDOUT,check=True)
    r=read('checkpoint_receipt.json');assert r['remote_upload_verified']
    print('Goal experiment and existing-ref remote verification completed '+r['remote_verified_commit'],flush=True)
if __name__=='__main__':main()
