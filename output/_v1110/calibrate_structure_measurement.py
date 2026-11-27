"""Predeclared same-DLL calibration. Never compile or analyze while timing."""
import hashlib,json,math,random,shutil,subprocess,sys
from pathlib import Path
from prepare_frame_guard_reuse import REPO,STAGE,BASE,sha,inventory
from install_ordering_correctness import boundary
from measurement_platform import topology
from measure_native_quads import contrasts
WORK=STAGE/'native_perf50/measurement_structure_bundle'
ACCEPTED=STAGE/'native_perf50/frame_guard_reuse_bundle'
EXPECTED='cea3c1c81a9294e05f0aac3b609ee4e474aa7019a1bf766ad12c22d876fe4b52'
PARENT='08c302e0ca056ab5ffff4853fc61b7705129e8d0'
def write(name,data):(WORK/name).write_text(json.dumps(data,indent=2,ensure_ascii=False)+'\n',encoding='utf8')
def prepare():
    boundary();assert not WORK.exists()
    assert sha(BASE/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==EXPECTED
    assert inventory(BASE)==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    assert subprocess.check_output(['git','ls-remote','--exit-code','https://github.com/cttt-des/AI-BackpackBattles.git','refs/heads/codex/native-perf50-verified'],cwd=REPO,text=True,timeout=40).split()[0]==PARENT
    WORK.mkdir();shutil.copyfile(BASE/'libgdcore.dll',WORK/'baseline.dll')
    shutil.copyfile(ACCEPTED/'user_boundary_before.json',WORK/'user_boundary_before.json')
    shutil.copyfile(ACCEPTED/'source_before_build.json',WORK/'baseline_source.json')
    reference=ACCEPTED/'release_audit.json'
    r=json.loads(reference.read_bytes());assert r['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    shutil.copyfile(reference,WORK/'fixed200_reference.json')
    t=topology();cpu=t['selected_logical_cpu']
    tests=[]
    # Synthetic nonuniform arm spacing: exact log-linear drift must cancel,
    # and a known 5% B cost reduction must have the same sign for both orders.
    for pattern in ('ABBA','BAAB'):
        for gain in (0,math.log(1.05),-math.log(1.05)):
            arms=[]
            for label,x in zip(pattern,(2,11,29,44)):
                cost=math.exp(.01*x-(gain if label=='B' else 0))
                arms.append(dict(label=label,measurement_start_qpc=x-1,measurement_end_qpc=x+1,main_thread_cpu_s=cost,wall_s=cost*1.4))
            result=contrasts(arms);assert all(abs(v-gain)<1e-12 for v in result.values())
            tests.append(dict(pattern=pattern,expected_log_reduction=gain,actual=result))
    write('contrast_math_checks.json',dict(passed=True,cases=tests))
    scripts=['measure_native_quads.py','measurement_platform.py','measure_native_corpus_blocks.py','compare_native_isolated_blocks.py','calibrate_structure_measurement.py']
    write('calibration_plan.json',dict(baseline_dll_sha256=EXPECTED,parent_remote_commit=PARENT,topology=t,
        scripts_sha256={s:sha(STAGE/s) for s in scripts},
        functional_smoke=dict(quads=2,repetitions=1,warmup_seconds=0,seed=271101,not_calibration_or_performance_claim=True),
        old_method_control=dict(pairs=8,repetitions=4,warmup_seconds=120,affinity='all allowed logical CPUs; exact old procedure'),
        corrected_sessions=[dict(name='aa_fixed_1',quads=12,repetitions=4,warmup_seconds=120,seed=271102,candidate_load_first=False),dict(name='aa_fixed_2',quads=12,repetitions=4,warmup_seconds=120,seed=271103,candidate_load_first=True)],
        every_batch_original_fixed200_signature=True,all_observations_and_extremes_retained=True,no_candidate_in_this_stage=True,
        primary_metrics=['main_thread_cpu_s','wall_s'],primary_estimator='median of time-bracketed quad log contrasts',
        analysis=dict(bootstrap_resamples=20000,seed=271104,moving_block_length=2,sensitivity_block_length=3,session_grouping=True,
          estimate=['absolute null bias and 95% envelope','joint 80% detection magnitude at 24 quads','time drift','order effects','lag correlation'],
          formal_AB_budget='two sessions of12 quads; no additional same-source sampling',
          acceptance='both CPU and wall95% lower bounds positive; both point gains exceed respective AA absolute95% null envelopes; both sessions direction positive'),
        no_edits_compiles_profiling_or_analysis_during_timing=True,load20=dict(empirical_formula=True,extrapolation_allowed=True,no_idle_or_coverage_gate=True),
        no_new_branches=True,preserve_user_files_index_HEAD=True))
    print('Calibration plan frozen; CPU '+str(cpu),flush=True)
def run(script,args,log):
    assert not (WORK/log).exists()
    with (WORK/log).open('wb') as stream:subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/script),*map(str,args)],stdout=stream,stderr=subprocess.STDOUT,check=True,cwd=REPO)
def timing():
    plan=json.loads((WORK/'calibration_plan.json').read_bytes());boundary()
    assert all(sha(STAGE/s)==h for s,h in plan['scripts_sha256'].items())
    shared=['--baseline',WORK/'baseline.dll','--candidate',WORK/'baseline.dll','--reference',WORK/'fixed200_reference.json']
    cpu=plan['topology']['selected_logical_cpu']
    s=plan['functional_smoke']
    run('measure_native_quads.py',shared+['--out',WORK/'functional_smoke.json','--logical-cpu',cpu,'--quads',s['quads'],'--repetitions',s['repetitions'],'--warmup-seconds',s['warmup_seconds'],'--seed',s['seed']],'functional_smoke.log')
    run('compare_native_isolated_blocks.py',shared+['--out',WORK/'aa_old.json','--pairs',8,'--batch-repetitions',4,'--warmup-seconds',120,'--quiet'],'aa_old.log')
    for s in plan['corrected_sessions']:
        run('measure_native_quads.py',shared+['--out',WORK/(s['name']+'.json'),'--logical-cpu',cpu,'--quads',s['quads'],'--repetitions',s['repetitions'],'--warmup-seconds',s['warmup_seconds'],'--seed',s['seed']]+(['--candidate-load-first'] if s['candidate_load_first'] else []),s['name']+'.log')
    boundary();assert sha(BASE/'libgdcore.dll')==EXPECTED
    write('aa_timing_complete.json',dict(passed=True,baseline_dll_sha256=EXPECTED,all3_sessions_and_smoke_completed=True))
    print('All predeclared A/A timing complete',flush=True)
if __name__=='__main__':
    {'prepare':prepare,'timing':timing}[sys.argv[1]]()
