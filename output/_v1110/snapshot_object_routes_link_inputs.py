"""Freeze the interrupted link's inputs before resuming the original protocol."""
import ast
import json
from pathlib import Path
import runpy
import shutil
import psutil
from prepare_native_object_routes import STAGE,BASE,WORK as PROBE,EXPECTED,sha
from build_native_hot_lto import HOT_UNITS,LTO

WORK=STAGE/'native_perf50/object_routes_bundle'

def main():
    out=WORK/'interrupted_link_inputs.json';assert not out.exists()
    assert not (WORK/'bundle.dll').exists() and not (WORK/'comparison.log').exists() and not (WORK/'ab_assessment.json').exists()
    original=json.loads((WORK/'live_build.json').read_bytes())
    if psutil.pid_exists(original['pid']):assert abs(psutil.Process(original['pid']).create_time()-original['created'])>=.001
    source=WORK/'bundle_src';frozen=json.loads((WORK/'source_before_build.json').read_bytes())
    assert frozen==json.loads((PROBE/'transform.json').read_bytes())['source_sha256']
    assert frozen=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert sha(BASE/'libgdcore.dll')==sha(STAGE.parents[1]/'dist/native_1_1_10/libgdcore.dll')==EXPECTED
    objects=Path((WORK/'bundle_objects.txt').read_text('utf8'));profile=objects/'pgo'
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    assert all((objects/(n+'.o')).is_file() for n in names)
    counts={n:sha(profile/(n+'.gcda')) for n in sorted(HOT_UNITS)};assert len(counts)==18
    lookup=profile/objects.drive.replace(':','~')/objects.relative_to(objects.anchor)
    assert all(sha(lookup/(n+'.gcda'))==h for n,h in counts.items())
    saved=WORK/'frozen_pgo_counts';saved.mkdir(exist_ok=True)
    for n,h in counts.items():
        p=saved/(n+'.gcda')
        if p.exists():assert sha(p)==h
        else:shutil.copyfile(profile/(n+'.gcda'),p)
    module=runpy.run_path(str(source/'build_windows.py'))
    flags=[*module['COMMON'],LTO,f'-fprofile-use={profile.as_posix()}','-fprofile-partial-training','-fprofile-correction']
    command=['D:/mingw64/bin/g++.exe',*flags,'-shared','-static','-o',str(objects/'libgdcore.dll'),*[str(objects/(n+'.o')) for n in names]]
    log=(WORK/'build_first.log').read_text('utf8')
    command_line=next(line for line in reversed(log.splitlines()) if 'CalledProcessError: Command ' in line)
    recorded=ast.literal_eval(command_line.split("Command '",1)[1].rsplit("' returned non-zero exit status",1)[0])
    assert command==recorded,'Resume must use the identical original release-link command'
    audit=json.loads((WORK/'instrumented_audit.json').read_bytes())
    assert audit['dll_sha256']==sha(objects/'instrumented.dll')
    assert audit['object_route_coverage']==dict(instance_methods=901392,static_context_f32=88491)
    result=dict(original_build=original,reason='Release link stopped during user-reported manual LTO termination',
        user_reported_manual_lto_termination=True,user_statement='手动结束过',
        all20_release_objects_compiled=True,no_formal_timing_started=True,source_and_original_method_bodies_unchanged=True,
        source_manifest_sha256=sha(WORK/'source_before_build.json'),baseline_dll_sha256=EXPECTED,
        object_directory=str(objects),objects_sha256={n:sha(objects/(n+'.o')) for n in names},
        hot_profiles_sha256=counts,original_link_command=command,link_compile_and_floating_flags_unchanged=True,
        failure_log_sha256={n:sha(WORK/n) for n in ('build_first.log','qualification_first.log')},
        instrumented_dll_sha256=audit['dll_sha256'],training_receipts_sha256={n:sha(objects/(n+'.json')) for n in ('smoke','replays','training')})
    out.write_text(json.dumps(result,indent=2,ensure_ascii=False)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in result.items() if k not in ('original_link_command','objects_sha256','hot_profiles_sha256')},ensure_ascii=False,indent=2))

if __name__=='__main__':main()
