"""Prove two complete source generations and reject unknown edits before writes."""
import importlib.util,json,os,shutil,subprocess,sys,tempfile
from native_build_storage import isolated_build
from pathlib import Path
from prepare_frame_guard_reuse import REPO,STAGE,WORK,BASE,ACCEPTED,HEADER,sha,save,verify_projection
@isolated_build
def main():
    verify_projection(WORK/'bundle_src')
    manifest=json.loads((ACCEPTED/'regeneration_manifest.json').read_bytes());rows={r['path']:r for r in manifest['inventory']}
    def canonical_sha(p):return __import__('hashlib').sha256(p.read_bytes().replace(b'\r\n',b'\n')).hexdigest()
    row=rows[HEADER];before=row['after_canonical_sha256'];after=canonical_sha(WORK/'bundle_src'/HEADER)
    row['intermediate_canonical_sha256']=list(dict.fromkeys([*row.get('intermediate_canonical_sha256',[]),before]));row['after_canonical_sha256']=after
    manifest['candidate_dll_sha256']=None;manifest['files']=[r for r in manifest['inventory'] if r['before_canonical_sha256']!=r['after_canonical_sha256']]
    save('regeneration_manifest.json',manifest);shutil.copytree(ACCEPTED/'before_runtime',WORK/'before_runtime')
    helper=(ACCEPTED/'verified_bundle_pending.py').read_text('utf8');assert "native_perf50/ordering_correctness_bundle" in helper
    helper=helper.replace('native_perf50/ordering_correctness_bundle','native_perf50/frame_guard_reuse_bundle');(WORK/'verified_bundle_pending.py').write_text(helper,encoding='utf8',newline='\n')
    root=Path(tempfile.mkdtemp(prefix='frame-guard-regeneration-'));stage=root/'output/_v1110';stage.mkdir(parents=True)
    save('full_regeneration_directory.json',dict(root=str(root)))
    for p in STAGE.glob('*.py'):shutil.copyfile(p,stage/p.name)
    shutil.copyfile(STAGE/'native_lovers_particles_probe_result.json',stage/'native_lovers_particles_probe_result.json')
    sim=STAGE/'sim_native';target=stage/'sim_native'
    for relative in ('gd_core','gd_core_items','native_sim_cpp/gd_core','native_sim_cpp/gd_core_items','native_sim_cpp/tools','native_sim_cpp/native_sim'):
        shutil.copytree(sim/relative,target/relative,ignore=shutil.ignore_patterns('__pycache__','*.pyc','*.o','*.gcda','*.gcno'))
    pending=stage/'native_perf50/frame_guard_reuse_bundle';pending.mkdir(parents=True)
    for name in ('regeneration_manifest.json','verified_bundle_pending.py'):shutil.copyfile(WORK/name,pending/name)
    for name in ('bundle_src','before_runtime'):shutil.copytree(WORK/name,pending/name)
    (stage/'optimize_native_verified_bundle.py').write_text(helper,encoding='utf8',newline='\n')
    source=(STAGE/'rebuild_native_lovers_candidate.py').read_text('utf8');prefix=source.split('os.environ["NATIVE_SIM_CXX"] =',1)[0];assert prefix!=source
    (stage/'rebuild_source_only.py').write_text(prefix+'\nprint("Frame guard source-only pipeline complete")\n',encoding='utf8',newline='\n')
    objects=root/'objects';objects.mkdir();shutil.copyfile(BASE/'libgdcore.dll',objects/'libgdcore.dll')
    command=[sys.executable,'-u','-X','utf8',str(stage/'rebuild_source_only.py'),'--baseline',str(target/'native_sim_cpp/native_sim/libgdcore.dll'),'--out',str(root/'not_built.dll'),'--native-perf50']
    expected=json.loads((WORK/'source_before_build.json').read_bytes());prior=None
    for iteration in (1,2):
        with (WORK/f'full_regeneration_{iteration}.log').open('wb') as log:subprocess.run(command,cwd=stage,env=dict(os.environ,NATIVE_SIM_OBJ=str(objects)),stdout=log,stderr=subprocess.STDOUT,check=True)
        native=target/'native_sim_cpp/native_sim';actual={p.relative_to(native).as_posix():(sha(p),p.stat().st_mtime_ns) for p in native.rglob('*') if p.is_file() and (p.suffix in ('.hpp','.cpp') or p.name=='build_windows.py')}
        assert len(actual)==710 and {n:v[0] for n,v in actual.items()}=={n:h for n,h in expected.items() if Path(n).suffix in ('.hpp','.cpp') or Path(n).name=='build_windows.py'}
        if prior is not None:assert actual==prior
        prior=actual
    spec=importlib.util.spec_from_file_location('frame_guard_recipe',WORK/'verified_bundle_pending.py');module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
    check=root/'guard_test';shutil.copytree(WORK/'bundle_src',check)
    state=lambda:{p.relative_to(check).as_posix():(sha(p),p.stat().st_mtime_ns) for p in check.rglob('*') if p.is_file()}
    initial=state();module.optimize(check);assert state()==initial
    victim=check/'gen/hdrs/Gd__gd_core__CoreRng.hpp';victim.write_bytes(victim.read_bytes()+b'\n// unsupported user edit\n');unknown=state()
    for prepare in (False,True):
        try:module.optimize(check,prepare)
        except ValueError:pass
        else:raise AssertionError('Unknown source accepted')
        assert state()==unknown
    save('full_regeneration_test.json',dict(passed=True,source_files=710,full_gdscript_and_all_retained_optimization_pipeline=True,source_generation_twice_bytes_and_mtimes_identical=True,unknown_edits_rejected_before_writes=True,compiler_invoked=False,source_manifest_sha256=sha(WORK/'source_before_build.json')))
    print('Two full source generations reproduced all710 C++ files; unknown-edit guards passed',flush=True)
if __name__=='__main__':main()
