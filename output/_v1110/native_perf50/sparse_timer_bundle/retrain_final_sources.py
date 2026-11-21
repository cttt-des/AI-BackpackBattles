"""Train fresh profiles on the final corrected source, then validate and compare."""
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import psutil
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
sys.path.insert(0,str(STAGE))
from build_native_hot_lto import HOT_UNITS,build_dll,collect_profiles
from prototype_native_sparse_timer_bundle import optimize
from resume_build import create_instrumented_exports

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def save(name,value):(WORK/name).write_text(json.dumps(value,indent=2)+'\n',encoding='utf8')

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    src=WORK/'bundle_src'
    expected=json.loads((WORK/'source_before_build.json').read_bytes())
    assert expected=={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    assert not (WORK/'fresh_profile_source.json').exists()
    negative=json.loads((WORK/'metadata_purity_preflight.json').read_bytes())
    assert negative['negative_return_code']==1 and negative['negative_result']['unexpected_meta_calls']>0
    assert json.loads((WORK/'copy_fix_rebuild.json').read_bytes())['fixed_after_change']['return_code']==0
    with tempfile.TemporaryDirectory(prefix='native-sparse-final-transform-') as directory:
        check=Path(directory)/'native'
        shutil.copytree(STAGE/'sim_native/native_sim_cpp/native_sim',check,
            ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        design=optimize(check)
        assert expected=={p.relative_to(check).as_posix():sha(p) for p in check.rglob('*') if p.is_file()}
    design['additional_verified_corrections']=['cache copy/move/assignment clears private indices',
        'unknown meta() is not called in eligibility pre-read','unknown FuncRef.is_valid callbacks invalidate before entry']
    save('transform.json',design)
    objects=Path(tempfile.mkdtemp(prefix='native-sparse-timer-bundle-final-'))
    shutil.copyfile(WORK/'bundle_objects.txt',WORK/'bundle_objects_before_retrain.txt')
    (WORK/'bundle_objects.txt').write_text(str(objects),encoding='utf8')
    os.environ.update(NATIVE_SIM_OBJ=str(objects),MAKE='D:/mingw64/bin/mingw32-make.exe',NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe')
    profile=objects/'pgo';profile.mkdir()
    definition,exports=create_instrumented_exports(objects)
    save('final_instrumented_export_policy.json',{'instrumentation_only':True,'exports':exports,'release_link_policy':'Original automatic export'})
    print('Final source matches transform; fresh full20 instrumentation and18-hot-unit PGO',flush=True)
    instrumented=build_dll(src,objects/'instrumented.dll',2,(f'-fprofile-generate={profile.as_posix()}',),
        hot_units=HOT_UNITS,link_flags=('-Wl,--exclude-all-symbols',str(definition)))
    audit=objects/'audit';audit.mkdir()
    subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'inspect_variant.py'),
        '--dll',str(instrumented),'--out',str(WORK/'final_instrumented_audit.json')],check=True,
        env=dict(os.environ,GCOV_PREFIX=str(audit),GCOV_PREFIX_STRIP='99'))
    collect_profiles(instrumented,objects,profile,HOT_UNITS)
    profiles={name:sha(profile/(name+'.gcda')) for name in sorted(HOT_UNITS)}
    assert len(profiles)==18
    for name in HOT_UNITS:
        path=(objects/(name+'.o')).resolve()
        assert path.is_relative_to(objects.resolve()) and path.parent==objects.resolve()
        path.unlink()
    print('Compiling release with profiles trained on the identical final source',flush=True)
    release=build_dll(src,objects/'release.dll',2,
        (f'-fprofile-use={profile.as_posix()}','-fprofile-partial-training','-fprofile-correction'),hot_units=HOT_UNITS)
    shutil.copyfile(release,WORK/'bundle.dll')
    assert expected=={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    report={'dll_sha256':sha(WORK/'bundle.dll'),'source_manifest_sha256':sha(WORK/'source_before_build.json'),
        'profile_training_and_release_source_identical':True,'hot_profiles_sha256':profiles,
        'full20_instrumentation_and18_release_hot_units':True,'floating_options_unchanged':True,
        'prior_profile_reuse_rejected_by_compiler':True}
    save('fresh_profile_source.json',report)
    negative.update({'corrected_dll_sha256':report['dll_sha256'],'fresh_profile_source_sha256':sha(WORK/'fresh_profile_source.json')})
    save('metadata_purity_rebuild.json',negative)
    subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'validate_then_compare.py'),
        '--build-pid','0','--created','0'],check=True)

if __name__=='__main__':main()
