"""Exercise two complete generations without compiling or changing live sources."""
import hashlib,json,os,re,shutil,subprocess,sys,tempfile,importlib.util
from pathlib import Path
from prepare_ordering_correctness import REPO,STAGE,WORK,BASE,ACCEPTED,sha,save,once

def main():
    root=Path(tempfile.mkdtemp(prefix='ordering-source-regeneration-'));stage=root/'output/_v1110';stage.mkdir(parents=True)
    save('full_regeneration_directory.json',dict(root=str(root),stage=str(stage)))
    for p in STAGE.glob('*.py'):shutil.copyfile(p,stage/p.name)
    shutil.copyfile(STAGE/'native_lovers_particles_probe_result.json',stage/'native_lovers_particles_probe_result.json')
    sim=STAGE/'sim_native';target=stage/'sim_native'
    for relative in ('gd_core','gd_core_items','native_sim_cpp/gd_core','native_sim_cpp/gd_core_items','native_sim_cpp/tools','native_sim_cpp/native_sim'):
        shutil.copytree(sim/relative,target/relative,ignore=shutil.ignore_patterns('__pycache__','*.pyc','*.o','*.gcda','*.gcno'))
    pending=stage/'native_perf50/ordering_correctness_bundle';pending.mkdir(parents=True)
    old=stage/'native_perf50/assembly_membership_bundle';old.mkdir(parents=True)
    for n in ('regeneration_manifest.json','verified_bundle_pending.py'):shutil.copyfile(ACCEPTED/n,old/n)
    shutil.copytree(ACCEPTED/'before_runtime',old/'before_runtime');shutil.copytree(ACCEPTED/'bundle_src',old/'bundle_src')
    shutil.copytree(WORK/'bundle_src',pending/'bundle_src')
    helper=(ACCEPTED/'verified_bundle_pending.py').read_text('utf8').replace('native_perf50/assembly_membership_bundle','native_perf50/ordering_correctness_bundle')
    (WORK/'verified_bundle_pending.py').write_text(helper,encoding='utf8',newline='\n');(pending/'verified_bundle_pending.py').write_text(helper,encoding='utf8',newline='\n')
    shutil.copyfile(WORK/'gd_to_cpp_pending.py',target/'native_sim_cpp/tools/gd_to_cpp.py')
    # Normalize the known corrected raw loop only for the original source hash
    # check. Reject a stale generator rather than silently accepting old behavior.
    event=(STAGE/'optimize_native_event_bus.py').read_text('utf8')
    a='''        if not match or hashlib.sha256(match[0].encode()).hexdigest() != expected_hash:
            raise ValueError(f"Unexpected generated body for {OWNER}::{name}")'''
    b='''        checked = match[0] if match else ""
        if name == "emitAndLog":
            fixed = "for (uint32_t _t1646 = 0; _t1645 && _t1646 < _t1645->len; ++_t1646) {"
            original = "for (uint32_t _t1646 = 0; _t1646 < _len__t1646; ++_t1646) {"
            if checked.count(fixed) != 1:
                raise ValueError("EventBus requires the Godot live-listener generator")
            checked = checked.replace(fixed, original, 1)
        if not match or hashlib.sha256(checked.encode()).hexdigest() != expected_hash:
            raise ValueError(f"Unexpected generated body for {OWNER}::{name}")'''
    event=once(event,a,b);(WORK/'optimize_native_event_bus_pending.py').write_text(event,encoding='utf8',newline='\n');(stage/'optimize_native_event_bus.py').write_text(event,encoding='utf8',newline='\n')
    shutil.copyfile(STAGE/'ordering_regeneration_bridge.py',stage/'optimize_native_verified_bundle.py')
    script=(STAGE/'rebuild_native_lovers_candidate.py').read_text('utf8');prefix=script.split('os.environ["NATIVE_SIM_CXX"] =',1)[0];assert prefix!=script
    (stage/'rebuild_source_only.py').write_text(prefix+'\nprint("Ordering source pipeline completed without compilation")\n',encoding='utf8',newline='\n')
    objects=root/'objects';objects.mkdir();shutil.copyfile(BASE/'libgdcore.dll',objects/'libgdcore.dll')
    command=[sys.executable,'-u','-X','utf8',str(stage/'rebuild_source_only.py'),'--baseline',str(target/'native_sim_cpp/native_sim/libgdcore.dll'),'--out',str(root/'not_built.dll'),'--native-perf50']
    env=dict(os.environ,NATIVE_SIM_OBJ=str(objects));expected=json.loads((WORK/'source_before_build.json').read_bytes());before=None
    for iteration in (1,2):
        with (WORK/f'full_regeneration_{iteration}.log').open('wb') as log:subprocess.run(command,cwd=stage,env=env,stdout=log,stderr=subprocess.STDOUT,check=True)
        native=target/'native_sim_cpp/native_sim'
        current={p.relative_to(native).as_posix():(sha(p),p.stat().st_mtime_ns) for p in native.rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py')}
        assert len(current)==710 and {n:x[0] for n,x in current.items()}=={n:h for n,h in expected.items() if Path(n).suffix in ('.cpp','.hpp') or Path(n).name=='build_windows.py'}
        if before is None:before=current
        else:assert current==before,'Repeat regeneration changed source bytes or timestamps'
    for n in ('regeneration_manifest.json','raw_generation_inverse_checks.json'):shutil.copyfile(pending/n,WORK/n)
    shutil.copytree(pending/'before_runtime',WORK/'before_runtime')
    spec=importlib.util.spec_from_file_location('ordering_verified_transform',WORK/'verified_bundle_pending.py');module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
    check=root/'guarded_source';shutil.copytree(WORK/'bundle_src',check)
    state=lambda:{p.relative_to(check).as_posix():(sha(p),p.stat().st_mtime_ns) for p in check.rglob('*') if p.is_file()}
    start=state();module.optimize(check);assert state()==start
    victim=check/'gen/hdrs/Gd__gd_core__CoreRng.hpp';victim.write_bytes(victim.read_bytes()+b'\n// unknown edit\n');changed=state()
    for mode in (False,True):
        try:module.optimize(check,mode)
        except ValueError:pass
        else:raise AssertionError('Unreviewed source edit accepted')
        assert state()==changed,'Guard wrote before rejecting an unreviewed edit'
    save('full_regeneration_test.json',dict(passed=True,full_gdscript_and_performance_pipeline=True,pending_generator_and_event_optimizer_used=True,source_files_matching_compiled_candidate=710,repeat_bytes_and_mtime_idempotent=True,compiler_invoked=False,unknown_edits_rejected_before_writes=True,raw_source_inverse_checks_passed=True,isolated_directory=str(root)))
    print('Two full source generations reproduce the corrected710 C++ files; guards passed',flush=True)
if __name__=='__main__':main()
