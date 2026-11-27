"""Real small LTO build, child redirect, failure cleanup, receipt-only flags."""
import ast,ctypes,json,os,shutil,subprocess,sys
from pathlib import Path
import psutil
from native_build_storage import ROOT,STAGE,workspace,sha,frozen_flags
OUT=STAGE/'build_storage/storage_tests'
def main():
    assert not OUT.exists();OUT.mkdir(parents=True);psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    for name in ('native_build_storage.py','run_native_managed.py','structure_round.py','structure_goal_driver.py','next_two.py','build_native_hot_lto.py','retire_native_c_cache.py'):ast.parse((STAGE/name).read_text('utf8'))
    src=OUT/'source';(src/'gen/shards').mkdir(parents=True)
    baseline=STAGE/'sim_native/native_sim_cpp/native_sim'
    shutil.copyfile(baseline/'build_windows.py',src/'build_windows.py')
    for i,name in enumerate(('gd_rt.cpp','engine_wrapper.cpp','gen/sym_ids.cpp','gen/register_all.cpp','gen/shards/shard_00.cpp')):(src/name).write_text('extern "C" int native_storage_test_'+str(i)+'(){return '+str(i+7)+';}\n',encoding='utf8')
    from build_native_hot_lto import build_dll
    with workspace('storage-real-lto-test') as root:
        os.environ['NATIVE_SIM_CXX']='D:/mingw64/bin/g++.exe'
        objects=Path(os.environ['NATIVE_SIM_OBJ']);objects.mkdir()
        dll=build_dll(src,OUT/'final.dll',2,link_flags=('-save-temps=obj',))
        assert dll.read_bytes()[:2]==b'MZ' and len(list(objects.glob('*.o')))==5
        assert not list(objects.glob('*.ltrans*.o')) and not list(objects.glob('*.ltrans*.s'))
        (root/'keep.json').write_text('{"evidence":true}',encoding='utf8')
        code="import tempfile,json,os;from pathlib import Path;p=Path(tempfile.mkdtemp(prefix='storage-child-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'));assert p.drive.upper()=='D:';(p/'keep.json').write_text('{}');print(p)"
        child=subprocess.check_output([sys.executable,'-X','utf8','-c',code],text=True).strip();assert Path(child).is_relative_to(root)
        first=str(root)
    assert not Path(first).exists() and (OUT/'final.dll').exists()
    try:
        with workspace('storage-exception-test') as root:
            second=str(root);(root/'partial.o').write_bytes(b'discard');(root/'error.log').write_text('retained failure',encoding='utf8');raise RuntimeError('planned build failure')
    except RuntimeError as error:assert str(error)=='planned build failure'
    assert not Path(second).exists()
    bundle=STAGE/'native_perf50/frame_guard_reuse_bundle';manifest=json.loads((bundle/'release_objects.json').read_bytes())
    flags={name:frozen_flags(bundle,name,digest) for name,digest in manifest['objects_sha256'].items() if Path(name).stem in __import__('build_native_hot_lto').HOT_UNITS};assert len(flags)==18
    copy=OUT/'receipt_only_baseline';(copy/'compiled_options').mkdir(parents=True)
    for name in ('release_objects.json','compiled_option_receipt.json'):shutil.copyfile(bundle/name,copy/name)
    for name in flags:shutil.copyfile(bundle/'compiled_options'/(Path(name).stem+'.txt'),copy/'compiled_options'/(Path(name).stem+'.txt'))
    row=json.loads((copy/'release_objects.json').read_bytes());row['object_directory']='D:/nonexistent-retired-objects';(copy/'release_objects.json').write_text(json.dumps(row),encoding='utf8')
    assert all(frozen_flags(copy,name,manifest['objects_sha256'][name])==value for name,value in flags.items())
    victim=copy/'compiled_options/gd_rt.txt';victim.write_bytes(victim.read_bytes()+b'bad')
    try:frozen_flags(copy,'gd_rt.o',manifest['objects_sha256']['gd_rt.o'])
    except AssertionError:pass
    else:raise AssertionError('Tampered option receipt accepted')
    shutil.copyfile(bundle/'compiled_options/gd_rt.txt',victim)
    result=dict(passed=True,actual_MinGW_LTO_units=5,final_dll_sha256=sha(OUT/'final.dll'),LTO_parts_removed_before_return=True,source_objects_removed_after_full_build_scope=True,child_explicit_legacy_C_path_redirected_to_D=True,success_and_exception_workspaces_removed=True,original18_baseline_option_receipts_match_without_old_objects=True,tampered_receipts_rejected=True,workspaces=[first,second],optimization_goal_not_resumed=True)
    (OUT/'receipt.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result,indent=2),flush=True)
if __name__=='__main__':main()
