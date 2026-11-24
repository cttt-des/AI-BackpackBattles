"""Resume the manually interrupted link, then the untouched first timing protocol."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import psutil
from prepare_native_object_routes import STAGE,BASE,EXPECTED,sha

WORK=STAGE/'native_perf50/object_routes_bundle'

def read(name):return json.loads((WORK/name).read_bytes())
def save(name,value):
    p=WORK/name;assert not p.exists();p.write_text(json.dumps(value,indent=2)+'\n',encoding='utf8')
def run(script,log,*args):
    p=WORK/log;assert not p.exists(),p
    print('Starting '+script,flush=True)
    with p.open('w',encoding='utf8') as stream:
        subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/script),*map(str,args)],stdout=stream,stderr=subprocess.STDOUT,check=True)
    print('Passed '+script,flush=True)

def main():
    process=psutil.Process();process.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    marker=WORK/'link_resume_first.log';assert not marker.exists(),'Inspect the current resume process or original log; never restart observed timings'
    assert not (WORK/'bundle.dll').exists() and not (WORK/'comparison.log').exists() and not (WORK/'ab_assessment.json').exists()
    assert not (WORK/'regeneration_pipeline.log').exists(),'Existing prechecks require an explicit continuation audit'
    frozen=read('interrupted_link_inputs.json');original=frozen['original_build']
    if psutil.pid_exists(original['pid']):assert abs(psutil.Process(original['pid']).create_time()-original['created'])>=.001
    assert frozen['user_reported_manual_lto_termination'] and frozen['no_formal_timing_started']
    assert frozen['source_manifest_sha256']==sha(WORK/'source_before_build.json')
    source=WORK/'bundle_src';objects=Path(frozen['object_directory']);profile=objects/'pgo'
    def check_inputs():
        assert read('source_before_build.json')=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
        assert frozen['objects_sha256']=={n:sha(objects/(n+'.o')) for n in frozen['objects_sha256']}
        assert frozen['hot_profiles_sha256']=={n:sha(profile/(n+'.gcda')) for n in frozen['hot_profiles_sha256']}
        assert all(sha(WORK/'frozen_pgo_counts'/(n+'.gcda'))==h for n,h in frozen['hot_profiles_sha256'].items())
        assert sha(BASE/'libgdcore.dll')==sha(STAGE.parents[1]/'dist/native_1_1_10/libgdcore.dll')==EXPECTED
    check_inputs()
    save('live_link_resume.json',dict(pid=process.pid,created=process.create_time(),script=str(Path(__file__).resolve()),
        original_build=original,input_receipt_sha256=sha(WORK/'interrupted_link_inputs.json')))
    os.environ.update(MAKE='D:/mingw64/bin/mingw32-make.exe',NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe',NATIVE_SIM_OBJ=str(objects))
    print('Resuming identical original release link; no source compilation or profile training repeated',flush=True)
    with marker.open('w',encoding='utf8') as stream:
        subprocess.run(frozen['original_link_command'],cwd=STAGE.parents[1],stdout=stream,stderr=subprocess.STDOUT,check=True)
    check_inputs()
    assert not (WORK/'bundle.dll').exists()
    shutil.copyfile(objects/'libgdcore.dll',objects/'release.dll')
    shutil.copyfile(objects/'release.dll',WORK/'bundle.dll');actual=sha(WORK/'bundle.dll')
    save('fresh_profile_source.json',dict(dll_sha256=actual,source_manifest_sha256=frozen['source_manifest_sha256'],
        profile_training_and_release_source_identical=True,hot_profiles_sha256=frozen['hot_profiles_sha256'],
        full20_instrumentation_and18_release_hot_units=True,floating_options_unchanged=True,
        resumed_original_link_after_user_manual_termination=True,all20_original_objects_reused=True,
        original_instrumentation_and_training_not_repeated=True,input_receipt_sha256=sha(WORK/'interrupted_link_inputs.json')))
    save('link_resume_receipt.json',dict(passed=True,dll_sha256=actual,original_link_command_unchanged=True,
        all20_release_objects_and18_profiles_unchanged=True,source707_unchanged=True,
        original_failure_logs_retained=True,no_formal_timing_repeated=True))
    print('Original link completed: '+actual,flush=True)
    run('freeze_pgo.py','freeze_pgo_resumed_first.log')
    run('validate_then_compare.py','prechecks_and_comparison_resumed_first.log','--build-pid','0','--created','0')
    check_inputs()
    assessment=read('ab_assessment.json');assert all(r['pairs']==24 for r in assessment['metrics'].values())
    assert read('object_routes_tests.json')['passed'] and read('object_routes_tests.json')['cases']==320256
    assert read('object_routes_tests.json')['dll_sha256']==actual
    assert read('callback_dispatch_tests.json')['passed'] and read('literal_span_tests.json')['passed']
    save('resumed_ready_receipt.json',dict(passed=True,all_remaining_prechecks_passed=True,first24_completed_once=True,
        dll_sha256=actual,source_manifest_sha256=sha(WORK/'source_before_build.json'),ab_assessment_sha256=sha(WORK/'ab_assessment.json'),
        interrupted_link_only_repeated=True,original20_compilation_and_training_retained=True))
    run('qualify_when_ready.py','qualification_resumed_first.log','--pid',original['pid'],'--created',original['created'],
        '--ready-receipt',WORK/'resumed_ready_receipt.json')
    save('resumed_protocol_complete.json',dict(passed=True,dll_sha256=actual,original_first24_and_at_most_one_extra8=True,
        candidate_status=read('candidate_decision.json')['status'],installation_still_requires_evidence_review=True))
    print('Original declared protocol completed; candidate decision retained; installation remains gated',flush=True)

if __name__=='__main__':main()
