"""Full20/fresh18 PGO correctness build; no performance-win adoption gate."""
import hashlib,json,os,runpy,shutil,subprocess,sys,tempfile,psutil
from pathlib import Path
from prepare_ordering_correctness import STAGE,REPO,WORK,BASE,ACCEPTED,EXPECTED,sha,inventory,save
from build_native_hot_lto import HOT_UNITS,build_dll,collect_profiles

def main():
    process=psutil.Process();process.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not (WORK/'live_formal_build.json').exists() and not (WORK/'bundle.dll').exists()
    assert json.loads((WORK/'prototype_ordering_tests.json').read_bytes())['passed']
    assert all(json.loads((WORK/n).read_bytes())['passed'] for n in ('python_compiled_ordering_tests.json','python_source_ordering_tests.json'))
    src=WORK/'bundle_src';assert inventory(src)==json.loads((WORK/'source_before_build.json').read_bytes())
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    root=Path(tempfile.mkdtemp(prefix='ordering-formal-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    objects=root/'objects';objects.mkdir();scratch=root/'scratch';scratch.mkdir();profile=objects/'pgo';profile.mkdir()
    os.environ.update(TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch),NATIVE_SIM_OBJ=str(objects),MAKE='D:/mingw64/bin/mingw32-make.exe',NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe');tempfile.tempdir=str(scratch)
    save('live_formal_build.json',dict(pid=process.pid,created=process.create_time(),script=str(Path(__file__).resolve())))
    save('persistent_build_directory.json',dict(root=str(root),objects=str(objects),scratch=str(scratch)))
    (WORK/'bundle_objects.txt').write_text(str(objects),encoding='utf8')
    copied=root/'baseline.dll';shutil.copyfile(BASE/'libgdcore.dll',copied)
    names=subprocess.check_output(['D:/mingw64/bin/nm.exe','-g','--defined-only',str(copied)],text=True)
    exports={line.split()[-1] for line in names.splitlines() if line.split() and line.split()[-1].startswith('gd_')}
    assert sum(n.startswith('gd_sim_') for n in exports)==22
    definition=objects/'instrumented_exports.def';definition.write_text('EXPORTS\n'+''.join('    '+n+'\n' for n in sorted(exports)),encoding='ascii',newline='\n')
    save('instrumented_export_policy.json',dict(instrumentation_only=True,exports=sorted(exports),release_link_policy='Original automatic export unchanged'))
    print('Building complete20 instrumentation units with original FP flags; max2 jobs',flush=True)
    instrumented=build_dll(src,objects/'instrumented.dll',2,(f'-fprofile-generate={profile.as_posix()}',),hot_units=HOT_UNITS,link_flags=('-save-temps=obj','-Wl,--exclude-all-symbols',str(definition)))
    print('Collecting new18 profiles from the corrected source',flush=True)
    collect_profiles(instrumented,objects,profile,HOT_UNITS)
    for name in HOT_UNITS:(objects/(name+'.o')).unlink()
    print('Building corrected PGO release',flush=True)
    release=build_dll(src,objects/'release.dll',2,(f'-fprofile-use={profile.as_posix()}','-fprofile-partial-training','-fprofile-correction'),hot_units=HOT_UNITS,link_flags=('-save-temps=obj',))
    shutil.copyfile(release,WORK/'bundle.dll')
    assert inventory(src)==json.loads((WORK/'source_before_build.json').read_bytes())
    frozen=WORK/'frozen_pgo_counts';frozen.mkdir()
    counts={}
    for name in sorted(HOT_UNITS):
        p=profile/(name+'.gcda');counts[name]=sha(p);shutil.copyfile(p,frozen/p.name);assert sha(frozen/p.name)==counts[name]
    save('fresh_profile_source.json',dict(dll_sha256=sha(WORK/'bundle.dll'),source_manifest_sha256=sha(WORK/'source_before_build.json'),profile_training_and_release_source_identical=True,hot_profiles_sha256=counts,full20_instrumentation_and18_release_hot_units=True,floating_options_unchanged=True,compiler_optimization_flags=[],same_compiler_configuration_in_both_profile_phases=True))
    save('frozen_pgo_manifest.json',dict(dll_sha256=sha(WORK/'bundle.dll'),source_manifest_sha256=sha(WORK/'source_before_build.json'),counts=counts))
    options=runpy.run_path(str(STAGE/'verify_assembly_membership_build_options.py'))['options']
    baseline=json.loads((ACCEPTED/'release_objects.json').read_bytes());old_root=Path(baseline['object_directory']);actual={};records={};folder=WORK/'compiled_options';folder.mkdir()
    for name,digest in baseline['objects_sha256'].items():
        assert sha(old_root/name)==digest;actual[name]=sha(objects/name)
        if Path(name).stem not in HOT_UNITS:continue
        text,flags=options(objects/name);_,old_flags=options(old_root/name)
        strip=lambda xs:[x for x in xs if not x.startswith('-fprofile-use=')]
        assert strip(flags)==strip(old_flags),(name,flags,old_flags)
        assert '-fipa-pta' not in flags
        (folder/(Path(name).stem+'.txt')).write_text(text+'\n',encoding='utf8');records[name]=dict(object_sha256=actual[name],options_sha256=sha(folder/(Path(name).stem+'.txt')))
    assert len(actual)==20 and len(records)==18
    save('release_objects.json',dict(object_directory=str(objects),dll_sha256=sha(WORK/'bundle.dll'),objects_sha256=actual))
    save('compiled_option_receipt.json',dict(passed=True,checked_hot_objects=18,fp_contract_off_all=True,compiler_options_identical_except_profile_directory=True,no_compiler_pta=True,dll_sha256=sha(WORK/'bundle.dll'),objects=records))
    print('Corrected release ready '+sha(WORK/'bundle.dll'),flush=True)
if __name__=='__main__':main()
