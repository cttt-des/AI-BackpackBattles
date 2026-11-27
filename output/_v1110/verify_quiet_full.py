"""All2604 strict original-event comparisons with numerical segments enabled."""
import argparse,json,shutil,subprocess,sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from prepare_quiet_round import WORK,STAGE,ACCEPTED,sha,save

def main():
    parser=argparse.ArgumentParser();parser.add_argument('--dll',type=Path,required=True);parser.add_argument('--tag',required=True);a=parser.parse_args()
    prefix='native_quiet_fast_'+a.tag+'_';gate=WORK/(a.tag+'_quiet_fast_full_gate.json');assert not (WORK/(a.tag+'_quiet_fast_full_tests.json')).exists()
    if gate.exists():
        preserved=WORK/(a.tag+'_quiet_fast_passed_gate_before_report_path_fix.json');assert not preserved.exists();shutil.copyfile(gate,preserved)
    plan=json.loads((STAGE/'native_host_phases_reuse_plan.json').read_bytes())
    plan.extend([dict(source='native_host_observed_expand/expand',name='native_host_rng_phases_new_expand',total=19),dict(source='native_host_observed_base/base',name='native_host_phases_observed_base_current',total=124),dict(source='native_host_observed_base/base',name='native_host_phases_observed_base_last',total=8)])
    placement=STAGE/'native_controlled_prismatic_run948_placement'
    def check(row):
        name=row['name'];inputs=STAGE/(name+'_cpp')
        if name=='native_host_phases_observed_base_current':inputs=STAGE/'native_hot_verify_host_phases_observed_base_current'
        output=STAGE/(prefix+name.removeprefix('native_'))
        if name=='native_host_phases_observed_base_current':output=output/'cpp'
        if (output/'summary.json').exists():
            summary=json.loads((output/'summary.json').read_bytes());coverage=json.loads((output/'quiet_core_coverage.json').read_bytes())
            assert summary['passed']==summary['total']==row['total'] and summary['dll_sha256']==sha(a.dll)
            assert coverage['verifier_exit_code']==0 and coverage['dll_sha256']==sha(a.dll) and coverage['verifier_source_sha256']==sha(STAGE/'sim_native/tools/_cpp_verify_events.py')
            print(name+': retained '+str(row['total'])+' strict passes, identical DLL and verifier',flush=True)
            return output,coverage
        assert not output.exists()
        command=[sys.executable,'-u','-X','utf8',str(STAGE/'run_native_managed.py'),str(STAGE/'quiet_fast_verify.py'),'--case-ids',str(inputs/'cases.json'),'--fights-root',str(inputs/'fights'),'--align-root',str(inputs/'align'),'--cases-json',str(inputs/'fixtures.json'),'--strict-gem-origins','--strict-item-origins','--original-dir',str(STAGE/row['source']),'--native-only','--out',str(output),'--dll',str(a.dll)]
        if name=='native_host_phases_observed_base_current':command+=['--ring-placement-observations',str(placement)]
        with (WORK/(a.tag+'_fast_'+name+'.log')).open('xb') as log:subprocess.run(command,stdout=log,stderr=subprocess.STDOUT,check=True)
        summary=json.loads((output/'summary.json').read_bytes());assert summary['passed']==summary['total']==row['total']
        coverage=json.loads((output/'quiet_core_coverage.json').read_bytes());assert coverage['verifier_exit_code']==0 and coverage['dll_sha256']==sha(a.dll)
        print(name+': '+str(row['total'])+' strict passes; '+str(coverage['counts']['frames'])+' optimized frames',flush=True)
        return output,coverage
    plan.sort(key=lambda row:row['total'],reverse=True)
    with ThreadPoolExecutor(max_workers=2) as pool:results=list(pool.map(check,plan))
    subprocess.run([sys.executable,'-X','utf8',str(STAGE/'check_native_corpus_gate.py'),'--dll',str(a.dll),'--report',*[str(path) for path,_ in results],'--host-observed-plan',str(STAGE/'native_host_observed_reference_plan.json'),'--ring-placement-observations',str(placement),'--out',str(gate)],check=True)
    subprocess.run([sys.executable,'-X','utf8',str(STAGE/'compare_native_event_receipts.py'),'--baseline',str(ACCEPTED/'bundle_full_gate.json'),'--candidate',str(gate),'--baseline-prefix','native_frame_guard_reuse_bundle_bundle_','--candidate-prefix',prefix,'--out',str(WORK/(a.tag+'_quiet_fast_event_hashes.json'))],check=True)
    counts={key:sum(c['counts'][key] for _,c in results) for key in ('attempts','rejected','segments','frames','lanes')};assert counts['frames']>100000,counts
    save(a.tag+'_quiet_fast_full_tests.json',dict(passed=True,dll_sha256=sha(a.dll),cases=2604,coverage=counts,full_gate_sha256=sha(gate),event_hash_comparison_sha256=sha(WORK/(a.tag+'_quiet_fast_event_hashes.json')),all_original_strict_event_receipts_retained=True))
if __name__=='__main__':main()
