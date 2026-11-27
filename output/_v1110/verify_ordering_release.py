"""Run correctness gates once the identified full PGO build has terminated."""
import hashlib,json,psutil,subprocess,sys,time
from pathlib import Path
from prepare_ordering_correctness import STAGE,WORK,BASE,EXPECTED,sha,inventory,save,verify_projection

def main():
    process=psutil.Process();process.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    save('live_qualification.json',dict(pid=process.pid,created=process.create_time(),script=str(Path(__file__).resolve())))
    row=json.loads((WORK/'live_formal_build.json').read_bytes())
    try:p=psutil.Process(row['pid'])
    except psutil.NoSuchProcess:p=None
    if p is not None and p.create_time()==row['created']:
        print('Waiting for the identified full20/fresh18 build',flush=True)
        while p.is_running():
            try:p.wait(timeout=30)
            except psutil.TimeoutExpired:continue
            break
    dll=WORK/'bundle.dll';assert dll.exists() and (WORK/'compiled_option_receipt.json').exists(),'Build not complete; inspect original build log'
    assert sha(BASE/'libgdcore.dll')==EXPECTED;verify_projection(WORK/'bundle_src')
    assert json.loads((WORK/'full_regeneration_test.json').read_bytes())['passed']
    steps=[
        ('original_ordering',STAGE/'verify_ordering_contracts.py',['--dll',dll,'--source',WORK/'bundle_src','--tag','formal']),
        ('original_potion_chains',STAGE/'verify_ordering_extra_potions.py',['--dll',dll,'--source',WORK/'bundle_src','--tag','formal']),
    ]
    scripts=['generate_property_tests.py','generate_type_constructor_tests.py',
        'verify_event_identity.py','verify_lazy_diagnostics.py','verify_components.py','verify_static_collections.py','verify_static_setup.py','verify_dispatch_chain.py','verify_spatial.py','verify_motion_indices.py','verify_targeted_timers.py','verify_active_cooldowns.py',
        'verify_buff_integer.py','verify_container_builtins.py','verify_scalar_truth.py','verify_private_snapshots.py','verify_control_word.py','verify_display_storage.py','verify_integer_grid.py','verify_event_factory.py','verify_literal_spans.py','verify_callback_dispatch.py','verify_object_routes.py','verify_full_pgo_buff.py','verify_assembly_membership.py','verify_resolved.py','verify_retained_weapon_chain.py']
    steps += [(Path(n).stem,WORK/n,[]) for n in scripts]
    steps += [('fixed200_release_audit',WORK/'inspect_variant.py',['--dll',dll,'--out',WORK/'release_audit.json']),('full2604',WORK/'run_full_gate.py',['bundle']),('full_event_and_type_audit',WORK/'finish_gate.py',[])]
    completed=WORK/'qualification_steps.json';state=json.loads(completed.read_bytes()) if completed.exists() else {}
    actual=sha(dll)
    for name,script,args in steps:
        if name in state:
            record=state[name];assert record['passed'] and record['dll_sha256']==actual and record['script_sha256']==sha(script) and record['log_sha256']==sha(WORK/record['log'])
            print('Retained passed '+name,flush=True);continue
        number=1
        while (WORK/f'{name}_qualification_attempt{number}.log').exists():number+=1
        log=WORK/f'{name}_qualification_attempt{number}.log'
        print('Starting '+name,flush=True)
        with log.open('wb') as output:
            result=subprocess.run([sys.executable,'-u','-X','utf8',str(script),*map(str,args)],stdout=output,stderr=subprocess.STDOUT)
        if result.returncode:
            print('Gate failed '+name+'; original log retained: '+str(log),flush=True)
            raise SystemExit(result.returncode)
        verify_projection(WORK/'bundle_src')
        state[name]=dict(passed=True,dll_sha256=actual,script_sha256=sha(script),log=log.name,log_sha256=sha(log))
        completed.write_text(json.dumps(state,indent=2)+'\n',encoding='utf8')
        print('Passed '+name,flush=True)
    save('complete_correctness_gate.json',dict(passed=True,dll_sha256=actual,source_manifest_sha256=sha(WORK/'source_before_build.json'),all_declared_steps=len(steps),retained_checks_and_original_Godot_contracts_passed=True,full2604_original_events_verified=True,original_input_corpus_unchanged=True,no_performance_win_gate_for_correctness_fix=True,not_deployed_yet=True))
    print('Complete correctness verification finished; runtime still unchanged',flush=True)
if __name__=='__main__':main()
