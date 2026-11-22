"""Keep the complete release gates, with one prospectively bounded ambiguity follow-up."""
import ast
import json
from pathlib import Path
STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/closed_timer_bundle'
WORK=STAGE/'native_perf50/active_cooldown_bundle'
BASE='686f0d6cdb2fc223d4ed50319b31e786eea14383b4ffb9a8fe8633395ee07b43'
ARCHIVE='e5356be288c04804dc645fced2ab24fd360b2238'
FIELDS=('indexed_phases','rebuilds','cache_hits','indexed_owners','build_fallbacks','same_pass_resumes','eligibility_changes','build_slots','build_active_owners','reserved')

def once(t,a,b):
    assert t.count(a)==1,(a[:100],t.count(a));return t.replace(a,b,1)

QUALIFIER='''"""Qualify only after the complete predeclared AB decision, never a favorable subset."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import psutil
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
def run(script,log,*args):
    print('Starting '+script,flush=True);path=WORK/log;assert not path.exists(),path
    with path.open('w',encoding='utf8') as output:subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/script),*map(str,args)],stdout=output,stderr=subprocess.STDOUT,check=True)
    print('Passed '+script,flush=True)
def main():
    p=argparse.ArgumentParser();p.add_argument('--pid',type=int,required=True);p.add_argument('--created',type=float,required=True);a=p.parse_args()
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    try:process=psutil.Process(a.pid)
    except psutil.NoSuchProcess:process=None
    if process is not None:
        assert abs(process.create_time()-a.created)<0.001
        assert any('active_cooldown_bundle/build_bundle.py' in part.replace('\\\\','/') for part in process.cmdline())
        print('Awaiting identified live build '+str(process.pid),flush=True)
        while process.is_running():
            try:process.wait(timeout=30)
            except psutil.TimeoutExpired:continue
            break
    path=WORK/'ab_assessment.json';assert path.exists(),'Original runner incomplete; inspect its original log, do not restart'
    first=json.loads(path.read_bytes());assert all(x['pairs']==24 for x in first['metrics'].values())
    clean=first['status']=='positive_combined_evidence' and all(x['paired_median_time_reduction_pct']>0 and x['sum_time_reduction_pct']>0 for row in first['leave_one_group_out_sensitivity'] for x in row.values())
    selected=path
    if not clean and first['status']!='consistent_regression_bundle_only':
        run('run_bounded_followup.py','bounded_followup.log');selected=WORK/'ab_assessment_32.json'
    result=json.loads(selected.read_bytes());actual=hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest()
    assert result['candidate_dll_sha256']==actual
    decision=dict(selected_assessment=str(selected),assessment_sha256=hashlib.sha256(selected.read_bytes()).hexdigest(),candidate_dll_sha256=actual,status=result['status'],original24_retained=True,no_more_same_source_groups=True,not_deployed=True)
    out=WORK/'candidate_decision.json';assert not out.exists();out.write_text(json.dumps(decision,indent=2)+'\\n',encoding='utf8')
    if result['status']!='positive_combined_evidence':print('All comparison evidence retained; no qualification: '+result['status'],flush=True);return
    run('run_full_gate.py','full_gate.log','bundle');run('finish_gate.py','finish_gate.log');run('run_release_measurements.py','release_measurements.log')
    print('Qualification and first release measurements finished; installation still requires evidence review',flush=True)
if __name__=='__main__':main()
'''

FOLLOWUP='''"""At most one extra independent eight-pair group, combining every original pair."""
import json
from pathlib import Path
import subprocess
import sys
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
assert (WORK/'bounded_followup_policy.json').exists()
plan=WORK/'followup_plan.json';assert not plan.exists()
plan.write_text(json.dumps(dict(maximum_extra_groups=1,all_original24_retained=True,all32_must_be_used=True,no_more_same_source_groups=True,policy='First24 inconclusive or leave-one-group sensitivity not positive: one independent baseline-first group, then stop'),indent=2)+'\\n',encoding='utf8')
subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'compare_native_isolated_blocks.py'),'--baseline',str(STAGE.parents[1]/'dist/native_1_1_10/libgdcore.dll'),'--candidate',str(WORK/'bundle.dll'),'--reference',str(STAGE/'native_perf50_event_bus_serial.json'),'--out',str(WORK/'ab_4.json'),'--pairs','8','--batch-repetitions','4','--warmup-seconds','120','--quiet','--candidate-load-first'],check=True)
subprocess.run([sys.executable,'-X','utf8',str(WORK/'assess_resolved.py'),'--reports',*[str(WORK/f'ab_{i}.json') for i in (1,2,3,4)],'--out',str(WORK/'ab_assessment_32.json')],check=True)
'''

def main():
    assert not WORK.exists();WORK.mkdir()
    for p in OLD.glob('*.py'):
        t=p.read_text('utf8').replace('closed_timer_bundle','active_cooldown_bundle').replace('motion_indices_bundle','closed_timer_bundle')
        t=t.replace('7a57d09b81ba62fcd985fbb14a5999c72ff550ba328d5cae3add6167e4fbc058',BASE).replace('4a5388b7161d765cafe5515f263ee0f762fe7c88',ARCHIVE).replace('native-closed-timer-','native-active-cooldown-')
        if p.name=='profile_deployed.py':t=once(t,"EXPECTED='"+BASE+"'","EXPECTED=json.loads((WORK/'post_install_verification.json').read_bytes())['dll_sha256']")
        if p.name=='build_bundle.py':t=t.replace('==704','==705').replace("'verified_source_files':704","'verified_source_files':705").replace('and704 sources','and705 sources')
        if p.name in ('prepare_regeneration.py','test_regeneration_guards.py','verify_installed.py','save_checkpoint.py'):
            t=t.replace('==705','==706').replace("'source_inventory_verified':705","'source_inventory_verified':706").replace("'production_source_files':705","'production_source_files':706")
        if p.name=='resume_build.py':t=once(t,"    exports.add('gd_diag_native_targeted_timer_stat')","    exports.add('gd_diag_native_targeted_timer_stat')\n    exports.add('gd_diag_native_active_cooldown_stat')")
        if p.name=='validate_then_compare.py':t=once(t,"    run('verify_targeted_timers.py','targeted_timer_tests.log')","    run('verify_targeted_timers.py','targeted_timer_tests.log')\n    run('verify_active_cooldowns.py','active_cooldown_tests.log')")
        if p.name=='inspect_variant.py':
            t=once(t,'    targeted=sim.lib.gd_diag_native_targeted_timer_stat',"    active=sim.lib.gd_diag_native_active_cooldown_stat;active.argtypes=[ctypes.c_uint];active.restype=ctypes.c_uint64\n    active_before=[active(i) for i in range(10)]\n    targeted=sim.lib.gd_diag_native_targeted_timer_stat")
            t=once(t,"    report['targeted_timer_coverage']=",f"    report['active_cooldown_coverage']=dict(zip({FIELDS!r},[active(i)-active_before[i] for i in range(10)]))\n    assert all(report['active_cooldown_coverage'][name]>0 for name in ('indexed_phases','rebuilds','cache_hits','indexed_owners','same_pass_resumes'))\n    report['targeted_timer_coverage']=")
        if p.name=='audit_verify.py':
            t=once(t,'targeted_stat=lib.gd_diag_native_targeted_timer_stat',"active_stat=lib.gd_diag_native_active_cooldown_stat;active_stat.argtypes=[ctypes.c_uint];active_stat.restype=ctypes.c_uint64\nactive_before=[active_stat(i) for i in range(10)]\ntargeted_stat=lib.gd_diag_native_targeted_timer_stat")
            t=once(t,'raise SystemExit(exit_code)',"(out/'native_active_cooldown_audit.json').write_text(json.dumps(dict(dll_sha256=report['dll_sha256'],verifier_exit_code=exit_code,counts=[active_stat(i)-active_before[i] for i in range(10)]),indent=2)+'\\n',encoding='utf8')\nraise SystemExit(exit_code)")
        if p.name=='finish_gate.py':
            t=once(t,'    targeted_counts=[0]*10','    targeted_counts=[0]*10\n    active_counts=[0]*10')
            t=once(t,"        summary=json.loads((root/'summary.json').read_bytes())","        active=json.loads((root/'native_active_cooldown_audit.json').read_bytes());assert active['dll_sha256']==dll and active['verifier_exit_code']==0 and len(active['counts'])==10\n        for i,value in enumerate(active['counts']):active_counts[i]+=value\n        summary=json.loads((root/'summary.json').read_bytes())")
            t=once(t,'    assert all(targeted_counts[i]>0','    assert all(active_counts[i]>0 for i in (0,1,2,3,5))\n    assert all(targeted_counts[i]>0')
            t=once(t,"        'targeted_timer_coverage':",f"        'active_cooldown_coverage':dict(zip({FIELDS!r},active_counts)),\n        'targeted_timer_coverage':")
        if p.name=='verify_targeted_timers.py':
            t=once(t,"    frozen=json.loads((closed/'transform.json').read_bytes())['source_sha256']","    frozen=json.loads((WORK.parent/'active_cooldown_prototype/transform.json').read_bytes())['source_sha256']")
            t=once(t,"layouts['candidate']['BattleCtx']==304","layouts['candidate']['BattleCtx']==328")
            t=once(t,'    import sys',"    layouts={'historical_oracle':layouts['baseline'],'baseline':json.loads((WORK.parent/'closed_timer_bundle/targeted_timer_tests.json').read_bytes())['layouts']['candidate'],'candidate':layouts['candidate']}\n    assert layouts['baseline']['BattleCtx']==304 and layouts['candidate']['BattleCtx']==328\n    import sys")
            t=t.replace('from verify_closed_timer_registry import verify as registry_verify','from verify_closed_registry_current import verify as registry_verify')
        if p.name=='verify_installed.py':
            t=once(t,"'targeted_timer_tests.json','closed_known_tests.json'","'targeted_timer_tests.json','active_cooldown_tests.json','closed_known_tests.json'")
            t=once(t,"    assert read('targeted_timer_tests.json')['cases']==2016",f"    active_counts=[0]*10\n    for receipt in audit['receipts']:\n        row=json.loads((Path(receipt)/'native_active_cooldown_audit.json').read_bytes())\n        assert row['dll_sha256']==actual and row['verifier_exit_code']==0 and len(row['counts'])==10\n        for i,value in enumerate(row['counts']):active_counts[i]+=value\n    assert dict(zip({FIELDS!r},active_counts))==audit['active_cooldown_coverage']\n    assert all(active_counts[i]>0 for i in (0,1,2,3,5))\n    assert read('active_cooldown_tests.json')['cases']==1856\n    assert read('targeted_timer_tests.json')['cases']==2016")
            t=once(t,"'sealed_known_cases':1056,","'active_cooldown_cases':1856,'active_cooldown_coverage':audit['active_cooldown_coverage'],'sealed_known_cases':1056,")
            t=once(t,"'closed_known_tests_cases.json','closed_registry_tests.json'","'closed_known_tests_cases.json','closed_registry_tests.json','active_cooldown_tests.json','active_cooldown_tests_cases.json'")
        if p.name=='install_verified.py':
            t=once(t,'    args = parser.parse_args()',"    args = parser.parse_args()\n    if (WORK/'followup_plan.json').exists():\n        assert args.assessment.resolve()==(WORK/'ab_assessment_32.json').resolve(), 'Declared bounded follow-up requires all32 pairs'")
            t=once(t,"assert plan['additional_groups']==1 and plan['additional_pairs']==8 and plan['all_original_samples_retained']","assert plan['maximum_extra_groups']==1 and plan['all_original24_retained'] and plan['all32_must_be_used'] and plan['no_more_same_source_groups']")
        if p.name=='save_checkpoint.py':
            t=once(t,'    audit=json.loads',"    paths.update(STAGE/p for p in ('prepare_native_active_cooldowns.py','build_native_active_cooldown_prototype.py','native_active_cooldowns.hpp','test_native_active_cooldowns.cpp','verify_native_active_cooldown_prototype.py','verify_native_active_cooldown_coverage.py','inspect_native_active_cooldown_fixed200.py','prototype_native_active_cooldown_bundle.py','verify_native_active_cooldown_final.py','setup_active_cooldown_bundle.py'))\n    for folder in ('active_cooldown_prototype','typed_hotchain_prototype','typed_hotchain_bundle','cooldown_sparsity_probe','dict_cost_probe'):\n        paths.update(p for p in (WORK.parent/folder).rglob('*') if p.is_file())\n    audit=json.loads")
            t=once(t,'    audit=json.loads',"    paths.update(STAGE/p for p in ('prepare_native_typed_hotchain.py','extend_native_typed_hotchain.py','native_typed_damage_math.hpp','test_native_typed_damage_math.cpp','probe_native_typed_damage_math.py','probe_native_typed_hotchain.py','prototype_native_typed_hotchain_bundle.py','setup_typed_hotchain_bundle.py','preflight_native_typed_hotchain_bundle.py','verify_native_typed_hotchain_final.py','test_native_typed_damage_ranges.cpp','inspect_native_dict_cost.py','inspect_native_cooldown_sparsity.py'))\n    audit=json.loads")
            t=t.replace('perf: specialize sealed-input sparse timer traversal','perf: index active cooldown owners in original order').replace('backup: preserve verified sealed-input timer traversal','backup: preserve verified active cooldown index')
        if p.name=='qualify_when_ready.py':t=QUALIFIER
        ast.parse(t,filename=p.name);(WORK/p.name).write_text(t,encoding='utf8',newline='\n')
    registry=(STAGE/'verify_closed_timer_registry.py').read_text('utf8').replace('from prepare_native_closed_timer import BASE,STAGE,EXPECTED,sha','from prepare_native_active_cooldowns import BASE,STAGE,EXPECTED,sha')
    (WORK/'verify_closed_registry_current.py').write_text(registry,encoding='utf8',newline='\n')
    wrapper="import sys\nfrom pathlib import Path\nsys.path.insert(0,str(Path(__file__).resolve().parents[2]))\nfrom verify_native_active_cooldown_final import main\nif __name__=='__main__':main()\n"
    (WORK/'verify_active_cooldowns.py').write_text(wrapper,encoding='utf8',newline='\n')
    ast.parse(FOLLOWUP);(WORK/'run_bounded_followup.py').write_text(FOLLOWUP,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp'):(WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=BASE,verified_remote_backup=ARCHIVE,components=['existing structural watcher reuse','independent eligibility version','ordered active item/gem entries','exact same-pass suffix recovery'],
        local_independent_cases=1856,baseline_source_files=705,candidate_source_files=706,
        intentional_layout_changes=['NativeTimerWatch40->64','BattleCtx304->328'],GdArr_size_remains=32,
        previous_cooldown_index_flat_ab_preserved=True,typed_damage_candidate_not_included=True)
    plan['required'][0]+=';1856 active cooldown mutation, FENV, ownership and nested-cache cases, indexed recovery coverage required'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    policy=dict(frozen_before_first_measurement=True,initial_groups=3,pairs_per_group=8,
        clean_positive='Both aggregate medians positive and every leave-one-group-out median and sum positive',
        extra_group_condition='Not clean positive and not consistent_regression_bundle_only',maximum_extra_groups=1,
        extra_order='Baseline-first, candidate-load-first to balance original groups',
        decision='Both full selected CPU and wall paired medians must be positive; retain all original pairs',
        qualify_only_after_final_comparison_decision=True,no_per_component_significance_required=True)
    (WORK/'bounded_followup_policy.json').write_text(json.dumps(policy,indent=2)+'\n',encoding='utf8')
    print('Prepared ordered cooldown candidate: all20/new18PGO, fixed200 24-or-bounded32,2604 and first24 release gates')

if __name__=='__main__':main()
