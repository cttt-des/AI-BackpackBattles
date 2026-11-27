"""Retain every timer case while replacing the old sort callback expectation."""
import json,os,shutil,subprocess,tempfile
from pathlib import Path
from prepare_ordering_correctness import REPO,STAGE,WORK,sha,save,once

def main():
    import psutil
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    root=Path(tempfile.mkdtemp(prefix='ordering-timer-sort-'));(root/'project.godot').write_text('config_version=4\n',encoding='utf8')
    script='''extends SceneTree
var comparisons = []
func compare(a,b):
    comparisons.append(a)
    comparisons.append(b)
    return null
func _init():
    var items = range(8)
    items.sort_custom(self,"compare")
    var file = File.new()
    file.open("res://result.json",File.WRITE)
    file.store_string(JSON.print({"order":items,"comparisons":comparisons}))
    file.close()
    quit()
'''
    (root/'sort.gd').write_text(script,encoding='utf8');run=subprocess.run([str(REPO/'output/godot36/Godot_v3.6-stable_win64.exe'),'--no-window','--path',str(root),'--script','res://sort.gd'],capture_output=True,timeout=60)
    (WORK/'timer_sort_original_stdout.log').write_bytes(run.stdout);(WORK/'timer_sort_original_stderr.log').write_bytes(run.stderr);run.check_returncode();assert b'SCRIPT ERROR' not in run.stderr
    oracle=json.loads((root/'result.json').read_bytes());assert oracle==dict(order=list(range(8)),comparisons=[v for i in range(1,8) for v in (i,0,i,i-1)])
    save('timer_sort_original.json',dict(passed=True,result=oracle,godot_sha256=sha(REPO/'output/godot36/Godot_v3.6-stable_win64.exe'),script=script))
    fixture=(STAGE/'test_native_targeted_timers.cpp').read_text('utf8')
    anchor='gd::native_inline_call(f.c,f.grid->f_items,gd::SYM_sort_custom,a,2);break;'
    fixture=once(fixture,anchor,'const auto calls_before=f.callback.calls;gd::native_inline_call(f.c,f.grid->f_items,gd::SYM_sort_custom,a,2);assert(f.callback.calls-calls_before==14);for(unsigned i=0;i<8;++i)assert(f.grid->f_items.arr->data[i].obj==f.items[i]);break;')
    (WORK/'test_native_targeted_timers_godot.cpp').write_text(fixture,encoding='utf8',newline='\n')
    shutil.copyfile(WORK/'prototype.dll',root/'libgdcore.dll')
    with (WORK/'timer_sort_reference_compile.log').open('wb') as log:
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-DGD_TIMER_NEW','-I',str(WORK.parent/'targeted_timer_prototype'),'-I',str(WORK/'bundle_src'),str(WORK/'test_native_targeted_timers_godot.cpp'),str(root/'libgdcore.dll'),'-o',str(root/'test.exe')],stdout=log,stderr=subprocess.STDOUT,check=True)
    run=subprocess.run([str(root/'test.exe')],capture_output=True);(WORK/'timer_sort_reference_raw.json').write_bytes(run.stdout);(WORK/'timer_sort_reference_execution.log').write_bytes(run.stderr);run.check_returncode();actual=json.loads(run.stdout)
    old=json.loads((WORK.parent/'targeted_timer_prototype/baseline_expanded_cases.json').read_bytes());differences={key:[i for i,(a,b) in enumerate(zip(old[key],actual[key])) if a!=b] for key in ('state_hashes','legacy_hashes')}
    assert differences==dict(state_hashes=list(range(1536,1552)),legacy_hashes=list(range(1544,1552))),differences
    corrected=dict(old,state_hashes=actual['state_hashes'],legacy_hashes=actual['legacy_hashes'])
    save('targeted_timer_godot_reference.json',corrected)
    save('timer_sort_expectation_correction.json',dict(passed=True,all1760_original_cases_retained=True,changed_family=6,changed_scenario=6,comparator_returns_null_and_creates_one_timer_per_call=True,original_Godot_calls=14,original_Godot_order=list(range(8)),changed_cases=differences,all_other_frozen_state_and_counter_hashes_equal=True,corrected_normal_reference_dll_sha256=sha(WORK/'prototype.dll'),reference_scope='Only 16 sorting side-effect cases updated; normal/reference vs formal PGO still compared in full. Godot independently specifies comparator schedule and order.',original_fixture_sha256=sha(STAGE/'test_native_targeted_timers.cpp'),assertion_only_fixture_sha256=sha(WORK/'test_native_targeted_timers_godot.cpp')))
    failed=WORK/'targeted_timer_failed_attempt';failed.mkdir();shutil.copyfile(WORK/'targeted_timer_production_cases.json',failed/'targeted_timer_production_cases.json')
    p=WORK/'verify_targeted_timers.py';text=p.read_text('utf8');text=once(text,"old=json.loads((PROBE/reference).read_bytes());exe=root/(name+'.exe')","old=json.loads(((WORK/'targeted_timer_godot_reference.json') if name=='owner' else PROBE/reference).read_bytes());exe=root/(name+'.exe')")
    text=once(text,"str(STAGE/cpp),str(root/'libgdcore.dll')","str(WORK/'test_native_targeted_timers_godot.cpp' if name=='owner' else STAGE/cpp),str(root/'libgdcore.dll')")
    text=text.replace('all_original_arithmetic_rng_and_observable_callback_order_retained=True','all_unaffected_original_states_retained_and_Godot_sort_side_effects_checked=True')
    p.write_text(text,encoding='utf8',newline='\n')
    p=WORK/'verify_assembly_membership_control.py';text=p.read_text('utf8');anchor="    wrapper.write_text(text,encoding='utf8',newline='\\n')"
    text=once(text,anchor,"    text=text.replace(\"'baseline_expanded_cases.json'\",repr(str(WORK/'targeted_timer_godot_reference.json')))\n"+anchor)
    p.write_text(text,encoding='utf8',newline='\n')
    print('Godot sort side-effect oracle:14 calls, input order; all1760 timer cases preserved')
if __name__=='__main__':main()
