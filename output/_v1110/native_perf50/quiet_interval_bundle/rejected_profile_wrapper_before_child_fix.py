"""Diagnose the rejected DLL after frozen timing; never an adoption speed test."""
import ctypes,json,os,sys,tempfile,shutil
from pathlib import Path
import psutil
from native_build_storage import isolated_build
from prepare_quiet_round import WORK,STAGE,sha,save,verify_projection


@isolated_build
def main():
    assert json.loads((WORK/'candidate_decision.json').read_bytes())['status']=='consistent_regression_retained'
    assert json.loads((WORK/'measurements_summary.json').read_bytes())['nonrelease_only']
    out=WORK/'rejected_cost_profile.json';assert not out.exists()
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS);psutil.Process().cpu_affinity([2])
    verify_projection(WORK/'bundle_src');root=Path(tempfile.mkdtemp(prefix='quiet-rejected-profile-'))
    dll=root/'libgdcore.dll';shutil.copyfile(WORK/'bundle.dll',dll)
    script=STAGE/'profile_native_windows.py';text=script.read_text('utf8')
    anchor='    args.out.write_text(json.dumps(report, indent=2) + "\\n", encoding="utf8")'
    assert text.count(anchor)==1
    text=text.replace(anchor,'''    result_digest=hashlib.sha256()
    for result in results:result_digest.update(ct.string_at(ct.addressof(result),ct.sizeof(result)))
    report['results_sha256']=result_digest.hexdigest()
    assert report['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    report['diagnostic_only_after_rejected_AB']=True
'''+anchor)
    sys.argv=[str(script),'--dll',str(dll),'--corpus','--min-samples','8000','--max-depth','64','--full-output','--instruction-locations','--out',str(out)]
    exec(compile(text,str(script),'exec'),dict(__name__='__main__',__file__=str(script)))
    r=json.loads(out.read_bytes());assert r['dll_sha256']==sha(WORK/'bundle.dll') and r['inputs_sha256']=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    save('rejected_cost_profile_receipt.json',dict(passed=True,dll_sha256=r['dll_sha256'],profile_sha256=sha(out),original_profiler_sha256=sha(script),wrapper_sha256=sha(Path(__file__)),only_profiler_adaptation='Validate the last result vector outside the sampled interval',profiled_native_samples=r['samples'],actual_fixed200_inputs_and_results_checked=True,not_a_second_AB_or_speed_adoption_test=True,baseline_profile='native_perf50/measurement_structure_bundle/profile_baseline.json',below_normal=True,one_logical_cpu=True))


if __name__=='__main__':main()
