"""Repeat the affected actual-DLL and original-order contracts after A/B."""
import argparse,json,subprocess,sys,shutil
from prepare_frame_guard_reuse import STAGE,WORK,sha,save,verify_projection
def main():
    parser=argparse.ArgumentParser();parser.add_argument('--finish-existing',action='store_true');args=parser.parse_args()
    decision=json.loads((WORK/'candidate_decision.json').read_bytes());assert decision['accepted'];verify_projection(WORK/'bundle_src')
    log_path=WORK/('post_ab_summary_corrected.log' if args.finish_existing else 'post_ab_affected_checks.log');assert not log_path.exists()
    with log_path.open('wb') as log:
        commands=[
            [STAGE/'verify_frame_guard_actual.py','--formal','--tag','post_ab'],
            [WORK/'verify_ordering_contracts.py','--dll',WORK/'bundle.dll','--source',WORK/'bundle_src','--tag','post_ab'],
            [WORK/'verify_ordering_extra_potions.py','--dll',WORK/'bundle.dll','--source',WORK/'bundle_src','--tag','post_ab'],
        ]
        if not args.finish_existing:
            for command in commands:subprocess.run([sys.executable,'-u','-X','utf8',*map(str,command)],stdout=log,stderr=subprocess.STDOUT,check=True)
        # Fresh post-timing processes run every original event case again.
        if not args.finish_existing:
            shutil.copyfile(WORK/'bundle.dll',WORK/'post_ab.dll')
            subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'run_full_gate.py'),'post_ab'],stdout=log,stderr=subprocess.STDOUT,check=True)
        else:
            gate=json.loads((WORK/'post_ab_full_gate.json').read_bytes())
            assert gate['complete'] and gate['dll_sha256']==sha(WORK/'bundle.dll')==sha(WORK/'post_ab.dll')
            for label,count in [('base',914),('expand',1690)]:assert gate['cohorts'][label]['passed']==count and not gate['cohorts'][label]['pending']
        finish=(WORK/'finish_gate.py').read_text('utf8')
        finish=finish.replace("WORK/'bundle_full_gate.json'","WORK/'post_ab_full_gate.json'").replace('native_frame_guard_reuse_bundle_bundle_','native_frame_guard_reuse_bundle_post_ab_')
        for name in ('bundle_vs_deployed_hashes.json','legacy_counter_equivalence.json','full_type_audit.json'):finish=finish.replace("WORK/'"+name+"'","WORK/'post_ab_"+name+"'")
        if args.finish_existing:finish=finish.replace("'post_ab_bundle_vs_deployed_hashes.json'","'post_ab_summary_verified_events.json'")
        script=WORK/('finish_post_ab_corrected.py' if args.finish_existing else 'finish_post_ab.py');assert not script.exists();script.write_text(finish,encoding='utf8',newline='\n')
        subprocess.run([sys.executable,'-u','-X','utf8',str(script)],stdout=log,stderr=subprocess.STDOUT,check=True)
    names=['post_ab_actual_frame_tests.json','post_ab_ordering_tests.json','post_ab_extra_potion_tests.json']
    for name in names:
        row=json.loads((WORK/name).read_bytes());assert row['passed'] and row['dll_sha256']==sha(WORK/'bundle.dll')
    post=json.loads((WORK/'post_ab_full_type_audit.json').read_bytes());assert post['fights']==2604 and post['coverage']['audit_mismatch']==post['old_event_kernel_type_mismatches']==0
    if args.finish_existing:assert json.loads((WORK/'post_ab_summary_verified_events.json').read_bytes())==json.loads((WORK/'post_ab_bundle_vs_deployed_hashes.json').read_bytes())
    save('post_ab_directed_checks.json',dict(passed=True,dll_sha256=sha(WORK/'bundle.dll'),actual_frame_cases=135168,original_ordering_and_all_three_bus_paths=True,original_potions_and60_uninjected_activation_cases=True,fresh_post_AB_original_event_cases=2604,receipts_sha256={n:sha(WORK/n) for n in [*names,'post_ab_full_gate.json','post_ab_full_type_audit.json']}))
    print('Post-A/B actual frame and original ordering/potion checks passed',flush=True)
if __name__=='__main__':main()
