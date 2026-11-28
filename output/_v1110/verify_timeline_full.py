"""One optimization-enabled2604 event validation for the final candidate DLL."""
import json,subprocess,sys
from concurrent.futures import ThreadPoolExecutor
from prepare_timeline_round import WORK,STAGE,ACCEPTED,sha,save,verify_projection
from native_build_schedule import select_jobs
def main():
    dll=WORK/'bundle.dll';verify_projection(WORK/'bundle_src');assert not (WORK/'complete_correctness_gate.json').exists()
    prefix='native_timeline_typed_'+sha(dll)[:8]+'_';gate=WORK/'bundle_full_gate.json'
    plan=json.loads((STAGE/'native_host_phases_reuse_plan.json').read_bytes());plan.extend([dict(source='native_host_observed_expand/expand',name='native_host_rng_phases_new_expand',total=19),dict(source='native_host_observed_base/base',name='native_host_phases_observed_base_current',total=124),dict(source='native_host_observed_base/base',name='native_host_phases_observed_base_last',total=8)])
    placement=STAGE/'native_controlled_prismatic_run948_placement'
    def check(row):
        name=row['name'];inputs=STAGE/(name+'_cpp');output=STAGE/(prefix+name.removeprefix('native_'))
        if name=='native_host_phases_observed_base_current':inputs=STAGE/'native_hot_verify_host_phases_observed_base_current';output=output/'cpp'
        if (output/'summary.json').exists():
            summary=json.loads((output/'summary.json').read_bytes());coverage=json.loads((output/'timeline_coverage.json').read_bytes());assert summary['passed']==summary['total']==row['total'] and summary['dll_sha256']==sha(dll);assert coverage['verifier_exit_code']==0 and coverage['dll_sha256']==sha(dll) and coverage['verifier_source_sha256']==sha(STAGE/'sim_native/tools/_cpp_verify_events.py');return output,coverage
        assert not output.exists();command=[sys.executable,'-u','-X','utf8',str(STAGE/'run_native_managed.py'),str(STAGE/'timeline_fast_verify.py'),'--case-ids',str(inputs/'cases.json'),'--fights-root',str(inputs/'fights'),'--align-root',str(inputs/'align'),'--cases-json',str(inputs/'fixtures.json'),'--strict-gem-origins','--strict-item-origins','--original-dir',str(STAGE/row['source']),'--native-only','--out',str(output),'--dll',str(dll)]
        if name=='native_host_phases_observed_base_current':command+=['--ring-placement-observations',str(placement)]
        with (WORK/('formal_full_'+name+'.log')).open('xb') as log:subprocess.run(command,stdout=log,stderr=subprocess.STDOUT,check=True)
        summary=json.loads((output/'summary.json').read_bytes());assert summary['passed']==summary['total']==row['total'];coverage=json.loads((output/'timeline_coverage.json').read_bytes());assert coverage['verifier_exit_code']==0 and coverage['dll_sha256']==sha(dll);print(name,row['total'],'strict passes',coverage['counts'],flush=True);return output,coverage
    plan.sort(key=lambda r:r['total'],reverse=True)
    with ThreadPoolExecutor(max_workers=min(2,select_jobs(0,0)['frontend_jobs'])) as pool:results=list(pool.map(check,plan))
    subprocess.run([sys.executable,'-X','utf8',str(STAGE/'check_native_corpus_gate.py'),'--dll',str(dll),'--report',*[str(path) for path,_ in results],'--host-observed-plan',str(STAGE/'native_host_observed_reference_plan.json'),'--ring-placement-observations',str(placement),'--out',str(gate)],check=True)
    events=WORK/'bundle_event_hashes.json';subprocess.run([sys.executable,'-X','utf8',str(STAGE/'compare_native_event_receipts.py'),'--baseline',str(ACCEPTED/'bundle_full_gate.json'),'--candidate',str(gate),'--baseline-prefix','native_frame_guard_reuse_bundle_bundle_','--candidate-prefix',prefix,'--out',str(events)],check=True)
    counts={key:sum(r['counts'][key] for _,r in results) for key in ['motion_entries','typed_visual_steps','typed_charge_steps','delay_entries']};assert all(v>0 for v in counts.values())
    directed=json.loads((WORK/'formal_affected_tests.json').read_bytes());assert directed['passed'] and directed['dll_sha256']==sha(dll)
    container=json.loads((WORK/'formal_container_receipt.json').read_bytes());assert container['passed'] and container['dll_sha256']==sha(dll)
    rows=WORK.parent/'r3_formal_rows_resume_probe_receipt.json';row_proof=json.loads(rows.read_bytes());assert row_proof['passed'] and row_proof['tested_dll_sha256']==sha(dll)
    save('complete_correctness_gate.json',dict(passed=True,dll_sha256=sha(dll),optimization_enabled_full2604=True,all_original_strict_event_receipts_retained=True,coverage=counts,full_gate_sha256=sha(gate),events_sha256=sha(events),directed_receipt_sha256=sha(WORK/'formal_affected_tests.json'),container_receipt_sha256=sha(WORK/'formal_container_receipt.json'),cached_row_proof_sha256=sha(rows),no_second_fallback_only_full_corpus=True))
    print('One complete optimization-enabled2604 gate passed',counts,flush=True)
if __name__=='__main__':main()
