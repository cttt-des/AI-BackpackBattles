"""Recover vanished temporary build files using the unchanged frozen profiles."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import psutil
from prepare_native_object_routes import STAGE,BASE,EXPECTED,sha
from build_native_hot_lto import HOT_UNITS,build_dll

WORK=STAGE/'native_perf50/object_routes_bundle'

def read(n):return json.loads((WORK/n).read_bytes())
def save(n,v):
    p=WORK/n;assert not p.exists();p.write_text(json.dumps(v,indent=2)+'\n',encoding='utf8')
def run(script,log,*args):
    p=WORK/log;assert not p.exists(),p
    print('Starting '+script,flush=True)
    with p.open('w',encoding='utf8') as stream:
        subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/script),*map(str,args)],stdout=stream,stderr=subprocess.STDOUT,check=True)
    print('Passed '+script,flush=True)

def main():
    process=psutil.Process();process.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not (WORK/'live_recovered_build.json').exists(),'Inspect original recovery process and records before any further continuation'
    assert not (WORK/'bundle.dll').exists() and not (WORK/'comparison.log').exists() and not (WORK/'ab_assessment.json').exists()
    assert not (WORK/'regeneration_pipeline.log').exists()
    original=read('interrupted_link_inputs.json');failed=read('live_link_resume.json')
    for entry in [original['original_build'],failed]:
        if psutil.pid_exists(entry['pid']):assert abs(psutil.Process(entry['pid']).create_time()-entry['created'])>=.001
    source=WORK/'bundle_src';expected=read('source_before_build.json')
    def source_and_profiles():
        assert expected=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
        assert all(sha(WORK/'frozen_pgo_counts'/(n+'.gcda'))==h for n,h in original['hot_profiles_sha256'].items())
        assert sha(BASE/'libgdcore.dll')==sha(STAGE.parents[1]/'dist/native_1_1_10/libgdcore.dll')==EXPECTED
    source_and_profiles();assert len(original['hot_profiles_sha256'])==len(HOT_UNITS)==18
    previous=Path(original['object_directory'])
    missing=[n for n in original['objects_sha256'] if not (previous/(n+'.o')).exists()]
    assert missing,'Do not rebuild still-available20 objects without reviewing their current inputs'
    error=(WORK/'link_resume_first.log').read_text('utf8')
    assert 'ltrans3.o failed: No such file or directory' in error
    cache=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds';cache.mkdir(exist_ok=True)
    assert str(cache).isascii() and 'Temp' not in cache.parts
    root=Path(tempfile.mkdtemp(prefix='object-routes-recovery-',dir=cache))
    objects=root/'objects';objects.mkdir();scratch=root/'scratch';scratch.mkdir()
    os.environ.update(TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch),
        MAKE='D:/mingw64/bin/mingw32-make.exe',NATIVE_SIM_OBJ=str(objects),NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe')
    tempfile.tempdir=str(scratch)
    profile=objects/'pgo';profile.mkdir()
    for n,h in original['hot_profiles_sha256'].items():
        shutil.copyfile(WORK/'frozen_pgo_counts'/(n+'.gcda'),profile/(n+'.gcda'));assert sha(profile/(n+'.gcda'))==h
    lookup=profile/objects.drive.replace(':','~')/objects.relative_to(objects.anchor);lookup.mkdir(parents=True)
    for n in HOT_UNITS:shutil.copyfile(profile/(n+'.gcda'),lookup/(n+'.gcda'))
    preserved=WORK/'link_temp_failure_1';assert not preserved.exists();preserved.mkdir()
    for name in ('bundle_objects.txt','link_resume_first.log','live_link_resume.json'):
        shutil.copyfile(WORK/name,preserved/name)
    save('temporary_file_loss_recovery.json',dict(reason='Second link explicitly reported a missing LTO input; original temporary object and root-profile files subsequently missing',
        root_cause_of_file_removal_unknown=True,missing_original_objects=missing,
        original_source_and18_preserved_profiles_unchanged=True,original_instrumentation_and_training_not_repeated=True,
        old_object_directory=str(previous),new_build_root=str(root),new_object_directory=str(objects),new_temporary_directory=str(scratch),
        whole_standard_temp_directory_not_used=True,release_all20_recompiled=True,release_hot_units=sorted(HOT_UNITS),
        optimization_fp_and_lto_jobs_unchanged=True,link_only_added_option='-save-temps=obj',
        documentation=['https://gcc.gnu.org/onlinedocs/gcc/Overall-Options.html','https://gcc.gnu.org/onlinedocs/gcc/Environment-Variables.html'],
        original_source_manifest_sha256=sha(WORK/'source_before_build.json'),profile_counts_sha256=original['hot_profiles_sha256'],
        failed_log_sha256=sha(WORK/'link_resume_first.log'),no_formal_timing_had_started=True))
    (WORK/'bundle_objects.txt').write_text(str(objects),encoding='utf8')
    save('live_recovered_build.json',dict(pid=process.pid,created=process.create_time(),script=str(Path(__file__).resolve()),
        build_root=str(root),object_directory=str(objects),previous_resume=failed))
    print('Rebuilding20 release objects with18 identical saved profiles; isolated persistent ASCII build directory; max2 BelowNormal jobs',flush=True)
    dll=build_dll(source,objects/'release.dll',2,(f'-fprofile-use={profile.as_posix()}','-fprofile-partial-training','-fprofile-correction'),
        hot_units=HOT_UNITS,link_flags=('-save-temps=obj',))
    source_and_profiles()
    assert original['hot_profiles_sha256']=={n:sha(profile/(n+'.gcda')) for n in HOT_UNITS}
    shutil.copyfile(dll,WORK/'bundle.dll');actual=sha(WORK/'bundle.dll')
    save('fresh_profile_source.json',dict(dll_sha256=actual,source_manifest_sha256=sha(WORK/'source_before_build.json'),
        profile_training_and_release_source_identical=True,hot_profiles_sha256=original['hot_profiles_sha256'],
        full20_instrumentation_and18_release_hot_units=True,floating_options_unchanged=True,
        original_instrumentation_and_training_not_repeated=True,all20_release_objects_rebuilt_after_temporary_file_loss=True,
        preserved_original18_profile_hashes=True,link_only_temporary_file_retention=True,
        recovery_receipt_sha256=sha(WORK/'temporary_file_loss_recovery.json')))
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    save('recovered_release_objects.json',dict(passed=True,dll_sha256=actual,objects_sha256={n:sha(objects/(n+'.o')) for n in names},
        source_manifest_sha256=sha(WORK/'source_before_build.json'),profile_counts_sha256=original['hot_profiles_sha256']))
    print('Recovered release completed: '+actual,flush=True)
    run('freeze_pgo.py','freeze_pgo_recovered_first.log')
    run('validate_then_compare.py','prechecks_and_comparison_recovered_first.log','--build-pid','0','--created','0')
    source_and_profiles()
    assert all(r['pairs']==24 for r in read('ab_assessment.json')['metrics'].values())
    for n,count in [('object_routes_tests.json',320256),('callback_dispatch_tests.json',126192),('literal_span_tests.json',5184)]:
        r=read(n);assert r['passed'] and r['cases']==count and r['dll_sha256']==actual
    save('recovered_ready_receipt.json',dict(passed=True,all_remaining_prechecks_passed=True,first24_completed_once=True,
        dll_sha256=actual,source_manifest_sha256=sha(WORK/'source_before_build.json'),ab_assessment_sha256=sha(WORK/'ab_assessment.json'),
        original_profile_training_retained=True,temporary_file_loss_recovered=True))
    old=original['original_build']
    run('qualify_when_ready.py','qualification_recovered_first.log','--pid',old['pid'],'--created',old['created'],
        '--ready-receipt',WORK/'recovered_ready_receipt.json')
    save('recovered_protocol_complete.json',dict(passed=True,dll_sha256=actual,original_first24_and_at_most_one_extra8=True,
        candidate_status=read('candidate_decision.json')['status'],installation_still_requires_evidence_review=True))
    print('Original predeclared protocol completed; original failed build records retained; installation remains gated',flush=True)

if __name__=='__main__':main()
