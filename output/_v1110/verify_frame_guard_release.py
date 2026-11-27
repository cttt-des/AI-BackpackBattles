"""Qualify one new release against the complete repaired-production contract."""
import json,subprocess,sys,time
from pathlib import Path
import psutil
from prepare_frame_guard_reuse import STAGE,WORK,EXPECTED,BASE,sha,save,verify_projection
from setup_frame_guard_checks import NAMES
def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    row=json.loads((WORK/'live_formal_build.json').read_bytes())
    try:process=psutil.Process(row['pid'])
    except psutil.NoSuchProcess:process=None
    if process and process.create_time()==row['created']:
        print('Waiting for identified full20/fresh18 build',flush=True)
        while process.is_running():
            try:process.wait(timeout=30)
            except psutil.TimeoutExpired:continue
            break
    dll=WORK/'bundle.dll';assert dll.exists() and json.loads((WORK/'compiled_option_receipt.json').read_bytes())['passed'];actual=sha(dll)
    assert sha(BASE/'libgdcore.dll')==EXPECTED and json.loads((WORK/'full_regeneration_test.json').read_bytes())['passed'];verify_projection(WORK/'bundle_src')
    steps=[('actual_frame',STAGE/'verify_frame_guard_actual.py',['--formal']),('original_ordering',WORK/'verify_ordering_contracts.py',['--dll',dll,'--source',WORK/'bundle_src','--tag','formal']),('original_potions',WORK/'verify_ordering_extra_potions.py',['--dll',dll,'--source',WORK/'bundle_src','--tag','formal'])]
    scripts=NAMES[:NAMES.index('inspect_variant.py')]
    steps += [(Path(name).stem,WORK/name,[]) for name in scripts]
    steps += [('fixed200',WORK/'inspect_variant.py',['--dll',dll,'--out',WORK/'release_audit.json']),('full2604',WORK/'run_full_gate.py',['bundle']),('full_type_and_events',WORK/'finish_gate.py',[])]
    state_path=WORK/'qualification_steps.json';state=json.loads(state_path.read_bytes()) if state_path.exists() else {}
    for name,script,args in steps:
        if name in state:
            r=state[name];assert r['dll_sha256']==actual and r['script_sha256']==sha(script) and r['log_sha256']==sha(WORK/r['log']);print('Retained '+name,flush=True);continue
        number=1
        while (WORK/f'{name}_qualification_attempt{number}.log').exists():number+=1
        log=WORK/f'{name}_qualification_attempt{number}.log';print('Starting '+name,flush=True)
        with log.open('wb') as stream:result=subprocess.run([sys.executable,'-u','-X','utf8',str(script),*map(str,args)],stdout=stream,stderr=subprocess.STDOUT)
        if result.returncode:print('Failed '+name+'; preserved '+str(log),flush=True);raise SystemExit(result.returncode)
        verify_projection(WORK/'bundle_src');state[name]=dict(passed=True,dll_sha256=actual,script_sha256=sha(script),log=log.name,log_sha256=sha(log));save('qualification_steps.json',state);print('Passed '+name,flush=True)
    save('complete_correctness_gate.json',dict(passed=True,dll_sha256=actual,baseline_dll_sha256=EXPECTED,steps=len(steps),actual_frame_cases=135168,all_repaired_original_sort_and_listener_oracles=True,full_original_event_cases=2604,all_current_production_weapon_cases=136128,all_original_counters_unchanged=True))
    print('Complete frame-guard correctness gate passed; no timing yet',flush=True)
if __name__=='__main__':main()
