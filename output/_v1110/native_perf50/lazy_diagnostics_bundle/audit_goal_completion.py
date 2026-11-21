"""Audit the goal from raw timing, deployed bytes and independent event receipts."""
import ctypes
import hashlib
import json
import math
from pathlib import Path
import statistics
import sys
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
REPO=STAGE.parents[1]
sys.path.insert(0,str(REPO))
from trainer.native_backend import runtime_directory,load_native
EXPECTED='593acaf3d6bf1dfedc7926cc5f3659c074a285dd95a9dcf0db95c1f913077670'
BASE='b2018eb28b90ae5527d9e0764a8b11e5bf6df0b60df7cb722c67629fcfedb588'
INPUT='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
RESULT='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def read(name):return json.loads((WORK/name).read_bytes())
def main():
    verified=read('post_install_verification.json');assert verified['passed'] and verified['dll_sha256']==EXPECTED
    directory=runtime_directory();assert directory==(REPO/'dist/native_1_1_10').resolve()
    simulator=load_native(directory)
    kernel=ctypes.WinDLL('kernel32',use_last_error=True)
    module_path=kernel.GetModuleFileNameW
    module_path.argtypes=[ctypes.c_void_p,ctypes.c_wchar_p,ctypes.c_uint];module_path.restype=ctypes.c_uint
    buffer=ctypes.create_unicode_buffer(32768)
    assert module_path(simulator.lib._handle,buffer,len(buffer))
    actual_path=Path(buffer.value).resolve();assert actual_path==directory/'libgdcore.dll' and sha(actual_path)==EXPECTED
    assert sha(WORK/'bundle.dll')==sha(STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll')==EXPECTED
    assessment=read('ab_assessment_32.json');pairs=[]
    for entry in assessment['reports']:
        path=Path(entry['path']);assert sha(path)==entry['sha256'];report=json.loads(path.read_bytes())
        assert report['baseline_dll_sha256']==BASE and report['candidate_dll_sha256']==EXPECTED
        assert report['inputs_sha256']==INPUT and report['results_sha256']==RESULT
        assert report['workers']==1 and report['fights']==200 and report['trial_batch_repetitions']==4
        assert not report['report_writes_during_measurement'] and not report['console_writes_during_measurement']
        for pair in report['pairs']:
            for label in ('baseline','candidate'):
                arm=pair[label];assert arm['observed_fights']==800 and arm['batch_repetitions']==4
                assert len(arm['raw_batches'])==4 and all(row['results_sha256']==RESULT and row['matched_original_terminal']==200 for row in arm['raw_batches'])
                assert arm['on_ac_before'] is True and arm['on_ac_after'] is True
            pairs.append(pair)
    assert len(pairs)==32
    metrics={}
    for metric in ('main_thread_cpu_s','wall_s'):
        median=statistics.median(100*(1-p['candidate'][metric]/p['baseline'][metric]) for p in pairs)
        cumulative=100*(1-sum(p['candidate'][metric] for p in pairs)/sum(p['baseline'][metric] for p in pairs))
        expected=assessment['metrics'][metric]
        assert math.isclose(median,expected['paired_median_time_reduction_pct'],abs_tol=1e-10) and median>0
        assert math.isclose(cumulative,expected['sum_time_reduction_pct'],abs_tol=1e-10)
        metrics[metric]={'median_time_reduction_pct':median,'cumulative_time_reduction_pct':cumulative}
    gate=read('bundle_full_gate.json');hashes=read('bundle_vs_deployed_hashes.json');audit=read('full_type_audit.json')
    assert gate['complete'] and gate['dll_sha256']==EXPECTED
    assert [gate['cohorts'][k]['passed'] for k in ('base','expand')]==[914,1690]
    assert hashes['unchanged_cpp_event_streams']==verified['strict_event_cases']==2604
    assert audit['coverage']['audit_mismatch']==audit['old_event_kernel_type_mismatches']==0
    serial=read('bundle_serial.json');calibration=read('bundle_load_calibration.json')
    for report in (serial,calibration):
        assert report['dll_sha256']==EXPECTED and report['inputs_sha256']==INPUT and report['results_sha256']==RESULT
        assert report['workers']==1 and report['fights']==200 and len(report['samples'])==report['repeat']==24
        assert all(r['matched_original_terminal']==200 and r['on_ac_before'] is True and r['on_ac_after'] is True for r in report['samples'])
    minimum=min(200/r['wall_s'] for r in serial['samples']);assert minimum>=50
    xs=[r['background_load_pct'] for r in calibration['samples']]
    slope,intercept=statistics.linear_regression(xs,[math.log(r['wall_s']) for r in calibration['samples']])
    fitted=200/math.exp(intercept+20*slope)
    assert min(xs)<=20<=max(xs) and fitted>=140
    assert math.isclose(fitted,read('bundle_load20.json')['fitted_fights_per_second_at_reference_load'],rel_tol=1e-10)
    install=read('bundle_installation.json');assert install['training_matched_baseline']==12 and install['training_evaluation']['sim_errors']==0
    result={'passed':True,'default_training_loaded_module':str(actual_path),'dll_sha256':EXPECTED,
        'paired_observations':32,'independent_groups':4,'metrics':metrics,'strict_original_and_unchanged_cpp_cases':2604,
        'production_source_files_rechecked':verified['production_source_files'],'unchanged_headers':verified['unchanged_object_headers'],
        'first_only_raw_batches':24,'raw_minimum_fights_per_second':minimum,'first_only_calibration_batches':24,
        'recomputed_at20_fights_per_second':fitted,'targets_100_125_140_met_under_current_calibration':True,
        'calibration_load_range_pct':[min(xs),max(xs)],'training_cases':12,
        'limitations':['small code effect; group directions mixed','independent calibration changes do not measure code speedups','a calibrated point estimate does not guarantee future performance under every workload'],
        'evidence_sha256':{name:sha(WORK/name) for name in ('post_install_verification.json','ab_assessment_32.json','bundle_full_gate.json','bundle_vs_deployed_hashes.json','bundle_serial.json','bundle_load_calibration.json','bundle_load20.json','bundle_installation.json')}}
    (WORK/'goal_completion_audit.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(result,indent=2))
if __name__=='__main__':main()
