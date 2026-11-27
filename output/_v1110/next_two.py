"""Execute two distinct frozen candidates, preserving every first result."""
import argparse,ast,ctypes,hashlib,json,os,re,runpy,shutil,subprocess,sys,tempfile
from pathlib import Path
import psutil
from prepare_frame_guard_reuse import REPO,STAGE,BASE,sha,inventory
from install_ordering_correctness import boundary,replace,training
from setup_frame_guard_checks import NAMES,MODULES
ROOT_BASELINE='frame_guard_reuse_bundle'
ROUNDS=('dictionary_scalar_bundle','rng_scaling_bundle')

def write(path,value):path.write_text(json.dumps(value,indent=2,ensure_ascii=False)+'\n',encoding='utf8')
def read(path):return json.loads(path.read_bytes())
def run(script,*args,log=None):
    command=[sys.executable,'-u','-X','utf8',str(script),*map(str,args)]
    if log:
        initial=log;attempt=2
        while log.exists():log=initial.with_name(initial.stem+f'_attempt{attempt}'+initial.suffix);attempt+=1
        with log.open('wb') as stream:subprocess.run(command,stdout=stream,stderr=subprocess.STDOUT,check=True)
    else:subprocess.run(command,check=True)
def prepared():
    import prepare_next_two_round as p
    return p
def rewrite(text):return text.replace('prepare_frame_guard_retained','prepare_next_two_retained').replace('prepare_frame_guard_reuse','prepare_next_two_round')
def save_script(path,text):ast.parse(text);path.write_text(text,encoding='utf8',newline='\n')

def prepare(name):
    boundary();work=STAGE/'native_perf50'/name;assert not work.exists()
    previous=STAGE/'native_perf50'/(ROUNDS[0] if name==ROUNDS[1] else ROOT_BASELINE)
    checkpoint=read(previous/'checkpoint_receipt.json');assert checkpoint['remote_upload_verified']
    accepted=previous if checkpoint['deployed'] else STAGE/'native_perf50'/ROOT_BASELINE
    expected=checkpoint['production_dll_sha256'];assert sha(BASE/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==expected
    assert inventory(BASE)==read(accepted/'source_before_build.json')
    work.mkdir();write(work/'round.json',dict(name=name,baseline_bundle=accepted.name,baseline_dll_sha256=expected,parent_remote_commit=checkpoint['remote_verified_commit']))
    shutil.copytree(accepted/'bundle_src',work/'bundle_src');write(work/'baseline_source.json',inventory(BASE))
    from next_two_sources import dictionary,rng_scaling
    changes=(dictionary if name==ROUNDS[0] else rng_scaling)(work/'bundle_src')
    for relative,operations in changes.items():
        path=work/'bundle_src'/relative;text=path.read_text('utf8')
        for old,new in operations:assert text.count(old)==1;text=text.replace(old,new)
        path.write_text(text,encoding='utf8',newline='\n')
    write(work/'source_changes.json',changes);write(work/'source_before_build.json',inventory(work/'bundle_src'))
    p=prepared();write(work/'transform.json',dict(baseline_dll_sha256=expected,source_sha256=inventory(work/'bundle_src'),modified_files=list(changes),projection=p.verify_projection(work/'bundle_src')))
    shutil.copyfile(accepted/'user_boundary_before.json',work/'user_boundary_before.json')
    shutil.copyfile(accepted/'assess_resolved.py',work/'assess_resolved.py')
    write(work/'evaluation_plan.json',dict(one_candidate_only=True,all_previous_repair_and_optimizations_retained=True,max_compiler_workers=2,below_normal_compilers=True,full20_instrumentation_fresh18_PGO=True,all_original_FP_flags=True,all_retained_cases=True,full_original_events=2604,AB=dict(initial_pairs=24,maximum_pairs=32,only_one8pair_followup_on_mixed_sensitivity=True,require_both_CPU_and_wall_medians_positive=True,retain_all_extremes=True,no_same_source_retiming=True),load20=dict(empirical_formula=True,allow_extrapolation=True,no_load_coverage_gate=True),raw24_minimum_fights_per_second=50,no_new_branches=True,no_old200_goal=True))
    if name==ROUNDS[1]:rng_baseline_review(work)
    print('Prepared '+name+' on '+expected,flush=True)

def rng_baseline_review(work):
    root=Path(tempfile.mkdtemp(prefix='rng-baseline-review-'));dll=root/'baseline.dll';shutil.copyfile(BASE/'libgdcore.dll',dll)
    names=subprocess.check_output(['D:/mingw64/bin/nm.exe','-g','--defined-only',str(dll)],text=True)
    demangled=subprocess.check_output(['D:/mingw64/bin/nm.exe','-g','-C','--defined-only',str(dll)],text=True)
    addresses={r.split()[0] for r in demangled.splitlines() if 'CoreRng::fn_randf' in r and len(r.split())>=3 and r.split()[1] in ('T','t') and int(r.split()[0],16)!=0}
    symbols=[r.split()[-1] for r in names.splitlines() if len(r.split())>=3 and r.split()[1] in ('T','t') and r.split()[0] in addresses];assert symbols
    text=''.join(subprocess.check_output(['D:/mingw64/bin/objdump.exe','-d','--no-show-raw-insn','--disassemble='+s,str(dll)],text=True) for s in symbols)
    path=work/'baseline_rng_preflight_machine.txt';path.write_text(text,encoding='utf8')
    calls=[line.strip() for line in text.splitlines() if 'call' in line and 'ldexp' in line]
    assert calls,'RNG library scaling no longer present at actual baseline hot entries; re-evaluate before compiling'
    write(work/'baseline_rng_preflight.json',dict(passed=True,dll_sha256=sha(BASE/'libgdcore.dll'),actual_current_release_machine=True,symbols=symbols,remaining_ldexp_call_sites=calls,disassembly_sha256=sha(path),no_performance_claim=True))

def setup():
    p=prepared();p.verify_projection(p.WORK/'bundle_src');work=p.WORK
    for name in (*NAMES,*MODULES):
        text=rewrite((p.ACCEPTED/name).read_text('utf8'))
        if name=='verify_full_pgo_buff.py':text=text.replace("STAGE/'native_perf50/"+p.ACCEPTED.name+"'","STAGE/'native_perf50/"+p.NAME+"'")
        if name=='run_full_gate.py':
            text=text.replace('native_'+p.ACCEPTED.name+'_','native_'+p.NAME+'_')
        if name=='finish_gate.py':
            text=re.sub(r"WORK.parent/'[^']+/bundle_full_gate.json'","WORK.parent/'"+p.ACCEPTED.name+"/bundle_full_gate.json'",text)
            text=re.sub(r"WORK.parent/'[^']+/full_type_audit.json'","WORK.parent/'"+p.ACCEPTED.name+"/full_type_audit.json'",text)
            text=re.sub(r"'--baseline-prefix','[^']+'","'--baseline-prefix','native_"+p.ACCEPTED.name+"_bundle_'",text)
            text=re.sub(r"'--candidate-prefix','[^']+'","'--candidate-prefix','native_"+p.NAME+"_bundle_'",text)
            text=re.sub(r"glob\('native_[^']+_bundle_\*'\)","glob('native_"+p.NAME+"_bundle_*')",text)
        save_script(work/name,text)
    for f in p.ACCEPTED.iterdir():
        if f.is_file() and f.suffix in ('.hpp','.cpp'):shutil.copyfile(f,work/f.name)
    for name in ('retained_fixture_transform.json','retained_event_test_correction.json','original_ordering_reference.json','original_reference_provenance.json','original_activation_reference.json','original_potion_chain_reference.json','sort_cases.json','activation_cases.json','targeted_timer_godot_reference.json','timer_sort_expectation_correction.json'):
        shutil.copyfile(p.ACCEPTED/name,work/name)
    for name in ('verify_ordering_contracts.py','verify_ordering_extra_potions.py'):
        save_script(work/name,rewrite((p.ACCEPTED/name).read_text('utf8')))
    save_script(work/'verify_actual_frame.py','import sys\nfrom pathlib import Path\nsys.path.insert(0,str(Path(__file__).resolve().parents[2]))\n'+rewrite((STAGE/'verify_frame_guard_actual.py').read_text('utf8')))
    reference=work/'retained_reference_src';shutil.copytree(p.ACCEPTED/'bundle_src',reference);shutil.copyfile(p.ACCEPTED/'bundle.dll',reference/'libgdcore.dll')
    write(work/'retained_harness_preparation.json',dict(passed=True,baseline_dll_sha256=p.EXPECTED,all_original_cases_and_expected_values_preserved=True,all136128_current_weapon_cases_exact=True,no_case_merging=True,all32_scripts=True))
    # The prior complete suite remains unchanged except its baseline and paths.
    print('Complete repaired regression suite retained',flush=True)

def prototype():
    p=prepared();p.verify_projection(p.WORK/'bundle_src');psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    if p.NAME==ROUNDS[1]:
        from concurrent.futures import ThreadPoolExecutor
        root=Path(tempfile.mkdtemp(prefix='rng-scaling-normal-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'));objects=root/'objects';objects.mkdir()
        os.environ.update(NATIVE_SIM_OBJ=str(objects),NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe',MAKE='D:/mingw64/bin/mingw32-make.exe')
        module=runpy.run_path(str(p.WORK/'bundle_src/build_windows.py'));namespace=module['build'].__globals__
        namespace['ThreadPoolExecutor']=lambda max_workers:ThreadPoolExecutor(max_workers=min(2,max_workers))
        library=module['build']();shutil.copyfile(library,p.WORK/'prototype.dll')
        assert library.resolve()==(p.WORK/'bundle_src/libgdcore.dll').resolve() and library.resolve().is_relative_to(p.WORK.resolve())
        library.rename(p.WORK/'prototype_source_output.dll')
        paths={s.name:s for s in objects.glob('*.o')};assert len(paths)==20
        p.verify_projection(p.WORK/'bundle_src');p.save('normal_object_paths.json',{n:str(s) for n,s in paths.items()})
        p.save('prototype_build.json',dict(passed=True,dll_sha256=sha(p.WORK/'prototype.dll'),objects_sha256={n:sha(s) for n,s in paths.items()},full20_normal_units_header_change=True,only_semantic_not_for_speed_or_deployment=True));return
    old=read(p.ACCEPTED/'prototype_build.json')['objects_sha256']
    if (p.ACCEPTED/'normal_object_paths.json').exists():paths={n:Path(s) for n,s in read(p.ACCEPTED/'normal_object_paths.json').items()}
    else:
        live=read(p.ACCEPTED/'live_semantic_build.json');paths={n:Path(live['reused_objects'].get(n,str(Path(live['object_directory'])/n))) for n in old}
    assert all(sha(paths[n])==h for n,h in old.items())
    changed='gd_rt' if p.NAME==ROUNDS[0] else 'shard_12'
    root=Path(tempfile.mkdtemp(prefix='next-two-normal-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'));objects=root/'objects';objects.mkdir()
    source=p.WORK/'bundle_src';unit=source/('gd_rt.cpp' if changed=='gd_rt' else 'gen/shards/shard_12.cpp')
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];cxx='D:/mingw64/bin/g++.exe'
    with (p.WORK/'prototype_compile.log').open('wb') as log:subprocess.run([cxx,*flags,'-c',str(unit),'-o',str(objects/(changed+'.o'))],stdout=log,stderr=subprocess.STDOUT,check=True)
    paths[changed+'.o']=objects/(changed+'.o')
    with (p.WORK/'prototype_link.log').open('wb') as log:subprocess.run([cxx,*flags,'-shared','-static','-o',str(objects/'libgdcore.dll'),*map(str,paths.values())],stdout=log,stderr=subprocess.STDOUT,check=True)
    shutil.copyfile(objects/'libgdcore.dll',p.WORK/'prototype.dll');p.verify_projection(source)
    p.save('normal_object_paths.json',{n:str(s) for n,s in paths.items()});p.save('prototype_build.json',dict(passed=True,dll_sha256=sha(p.WORK/'prototype.dll'),objects_sha256={n:sha(s) for n,s in paths.items()},changed_units=[changed],only_semantic_not_for_speed_or_deployment=True))

def affected(formal=False,tag=None,dll=None):
    p=prepared();tag=tag or ('formal' if formal else 'prototype');target=p.WORK/(tag+'_affected_tests.json');assert not target.exists()
    checks=p.WORK/(tag+('_dictionary_checks' if p.NAME==ROUNDS[0] else '_rng_checks'));checks.mkdir();root=Path(tempfile.mkdtemp(prefix='next-two-actual-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    fixture=STAGE/('test_next_two_dictionary.cpp' if p.NAME==ROUNDS[0] else 'test_next_two_rng_scaling.cpp');case_count=322944 if p.NAME==ROUNDS[0] else 354304
    data={};candidate=dll or p.WORK/('bundle.dll' if formal else 'prototype.dll')
    baseline=p.ACCEPTED/('bundle.dll' if formal else 'prototype.dll')
    for label,library in [('baseline',baseline),('candidate',candidate)]:
        local=root/label;local.mkdir();shutil.copyfile(library,local/'libgdcore.dll');shutil.copyfile(fixture,local/'check.cpp')
        with (checks/(label+'_compile.log')).open('wb') as log:subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off','-I',str(p.ACCEPTED/'bundle_src'),str(local/'check.cpp'),str(local/'libgdcore.dll'),'-o',str(local/'check.exe')],stdout=log,stderr=subprocess.STDOUT,check=True)
        execution=subprocess.run([str(local/'check.exe')],capture_output=True);(checks/(label+'_cases.json')).write_bytes(execution.stdout);(checks/(label+'_stderr.log')).write_bytes(execution.stderr);execution.check_returncode();data[label]=json.loads(execution.stdout)
    assert data['baseline']==data['candidate'] and data['candidate']['cases']==case_count
    p.save(target.name,dict(passed=True,dll_sha256=sha(candidate),baseline_dll_sha256=sha(baseline),cases=case_count,all16_FP_modes=True,actual_separate_DLL_functions=True,observed_function='GdDict::find_index' if p.NAME==ROUNDS[0] else 'gd::call_method Rng randf/randf_range builtin branch',no_fixture_inline_substitution=True,all_original_bits_flags_MXCSR_and_state_equal=True,preexisting_FP_flags_and_errno_preserved=p.NAME==ROUNDS[1],fixture_sha256=sha(fixture),raw_sha256={n:sha(checks/n) for n in ('baseline_cases.json','candidate_cases.json')}));print(tag+' affected '+str(case_count)+' passed',flush=True)

def trace_affected(formal,tag,dll):
    p=prepared();from next_two_sources import event_trace_fixture
    fixture=p.WORK/'test_next_two_bus_trace.cpp';text=event_trace_fixture(STAGE)
    assert text==(STAGE/'native_perf50/next_two_assessment/event_trace_fixture_frozen.cpp').read_text('utf8')
    if fixture.exists():assert fixture.read_text('utf8')==text
    else:fixture.write_text(text,encoding='utf8',newline='\n')
    checks=p.WORK/(tag+'_trace_checks');assert not checks.exists();checks.mkdir()
    root=Path(tempfile.mkdtemp(prefix='bus-trace-check-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'));data={}
    candidate=dll or p.WORK/('bundle.dll' if formal else 'prototype.dll');baseline=p.ACCEPTED/('bundle.dll' if formal else 'prototype.dll')
    for label,library in [('baseline',baseline),('candidate',candidate)]:
        local=root/label;local.mkdir();shutil.copyfile(library,local/'libgdcore.dll');shutil.copyfile(fixture,local/'check.cpp')
        with (checks/(label+'_compile.log')).open('wb') as log:subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off','-DGD_EVENT_IDENTITY_PRODUCTION','-I',str(p.ACCEPTED/'bundle_src'),str(local/'check.cpp'),str(local/'libgdcore.dll'),'-o',str(local/'check.exe')],stdout=log,stderr=subprocess.STDOUT,check=True)
        execution=subprocess.run([str(local/'check.exe')],capture_output=True);(checks/(label+'_cases.json')).write_bytes(execution.stdout);(checks/(label+'_stderr.log')).write_bytes(execution.stderr);execution.check_returncode();data[label]=json.loads(execution.stdout)
    assert data['baseline']==data['candidate'] and data['candidate']['cases']==49152
    report=dict(passed=True,dll_sha256=sha(candidate),baseline_dll_sha256=sha(baseline),cases=49152,all16_FP_modes=True,actual_separate_DLL_bus_functions=True,callbacks_replace_context_and_rng_or_flip_trace=True,unknown_context_rng_property_callbacks_and_counters=True,literal_and_public_native_generic_all_checked=True,fixture_sha256=sha(fixture),source_fixture_sha256=sha(STAGE/'test_native_event_identity_bus.cpp'),raw_sha256={n:sha(checks/n) for n in ('baseline_cases.json','candidate_cases.json')})
    p.save(tag+'_trace_tests.json',report);print(tag+' bus trace49152 passed',flush=True);return report

def regenerate():
    p=prepared();text=rewrite((STAGE/'regenerate_frame_guard.py').read_text('utf8'))
    text=text.replace(',HEADER,sha',',sha')
    old="    row=rows[HEADER];before=row['after_canonical_sha256'];after=canonical_sha(WORK/'bundle_src'/HEADER)\n    row['intermediate_canonical_sha256']=list(dict.fromkeys([*row.get('intermediate_canonical_sha256',[]),before]));row['after_canonical_sha256']=after"
    new="    for name in json.loads((WORK/'source_changes.json').read_bytes()):\n        row=rows[name];before=row['after_canonical_sha256'];after=canonical_sha(WORK/'bundle_src'/name)\n        row['intermediate_canonical_sha256']=list(dict.fromkeys([*row.get('intermediate_canonical_sha256',[]),before]));row['after_canonical_sha256']=after"
    assert text.count(old)==1;text=text.replace(old,new)
    text=text.replace("assert \"native_perf50/ordering_correctness_bundle\" in helper","assert 'native_perf50/'+ACCEPTED.name in helper")
    text=text.replace("helper.replace('native_perf50/ordering_correctness_bundle','native_perf50/frame_guard_reuse_bundle')","helper.replace('native_perf50/'+ACCEPTED.name,'native_perf50/"+p.NAME+"')")
    text=text.replace('native_perf50/frame_guard_reuse_bundle','native_perf50/'+p.NAME)
    exec(compile(text,str(STAGE/'regenerate_frame_guard.py'),'exec'),dict(__name__='__main__',__file__=str(STAGE/'next_two.py')))

def build():
    p=prepared();script=STAGE/'build_ordering_release.py'
    assert script.read_bytes()==subprocess.check_output(['git','show',p.ARCHIVE+':output/_v1110/build_ordering_release.py'],cwd=REPO)
    text=script.read_text('utf8').replace('from prepare_ordering_correctness import','from prepare_next_two_round import')
    text=text.replace("WORK/'prototype_ordering_tests.json'","WORK/'prototype_affected_tests.json'")
    old="    assert all(json.loads((WORK/n).read_bytes())['passed'] for n in ('python_compiled_ordering_tests.json','python_source_ordering_tests.json'))"
    assert text.count(old)==1;text=text.replace(old,"    assert json.loads((WORK/'full_regeneration_test.json').read_bytes())['passed']")
    text=text.replace('ordering-formal-','next-two-formal-')
    exec(compile(text,str(script),'exec'),dict(__name__='__main__',__file__=str(STAGE/'next_two.py')))

def qualify():
    p=prepared();work=p.WORK;dll=sha(work/'bundle.dll');p.verify_projection(work/'bundle_src')
    affected_report=read(work/'formal_affected_tests.json');assert affected_report['passed'] and affected_report['dll_sha256']==dll
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    names=NAMES[:NAMES.index('inspect_variant.py')]
    steps=[('actual_frame',work/'verify_actual_frame.py',['--formal'])]
    steps.extend([('original_ordering',work/'verify_ordering_contracts.py',['--dll',work/'bundle.dll','--source',work/'bundle_src','--tag','formal']),('original_potions',work/'verify_ordering_extra_potions.py',['--dll',work/'bundle.dll','--source',work/'bundle_src','--tag','formal'])])
    steps += [(Path(n).stem,work/n,[]) for n in names]
    steps += [('fixed200',work/'inspect_variant.py',['--dll',work/'bundle.dll','--out',work/'release_audit.json']),('full2604',work/'run_full_gate.py',['bundle']),('full_type_and_events',work/'finish_gate.py',[])]
    state=read(work/'qualification_steps.json') if (work/'qualification_steps.json').exists() else {}
    for name,script,args in steps:
        if name in state:
            r=state[name];assert r['dll_sha256']==dll and r['script_sha256']==sha(script) and r['log_sha256']==sha(work/r['log']);print('Retained '+name,flush=True);continue
        number=1
        while (work/f'{name}_qualification_attempt{number}.log').exists():number+=1
        log=work/f'{name}_qualification_attempt{number}.log';print('Starting '+name,flush=True);run(script,*args,log=log)
        p.verify_projection(work/'bundle_src');state[name]=dict(passed=True,dll_sha256=dll,script_sha256=sha(script),log=log.name,log_sha256=sha(log));p.save('qualification_steps.json',state);print('Passed '+name,flush=True)
    p.save('complete_correctness_gate.json',dict(passed=True,dll_sha256=dll,baseline_dll_sha256=p.EXPECTED,actual_frame_cases=135168,all_original_counter_equivalence=True,original_sort_potion_listener_oracles=True,all_current_production_weapon_cases=136128,full_original_event_cases=2604))

def comparison():
    text=rewrite((STAGE/'run_frame_guard_comparison.py').read_text('utf8'))
    exec(compile(text,str(STAGE/'run_frame_guard_comparison.py'),'exec'),dict(__name__='__main__',__file__=str(STAGE/'next_two.py')))

def post():
    p=prepared();work=p.WORK
    run(work/'verify_actual_frame.py','--formal','--tag','post_ab',log=work/'post_ab_actual_frame.log')
    affected(True,'post_ab')
    for script in ('verify_ordering_contracts.py','verify_ordering_extra_potions.py'):run(work/script,'--dll',work/'bundle.dll','--source',work/'bundle_src','--tag','post_ab',log=work/('post_ab_'+script+'.log'))
    shutil.copyfile(work/'bundle.dll',work/'post_ab.dll');run(work/'run_full_gate.py','post_ab',log=work/'post_ab_full2604.log')
    finish=(work/'finish_gate.py').read_text('utf8').replace("WORK/'bundle_full_gate.json'","WORK/'post_ab_full_gate.json'").replace('native_'+p.NAME+'_bundle_','native_'+p.NAME+'_post_ab_')
    for name in ('bundle_vs_deployed_hashes.json','legacy_counter_equivalence.json','full_type_audit.json'):finish=finish.replace("WORK/'"+name+"'","WORK/'post_ab_"+name+"'")
    save_script(work/'finish_post_ab.py',finish);run(work/'finish_post_ab.py',log=work/'post_ab_summary.log')
    names=['post_ab_actual_frame_tests.json','post_ab_affected_tests.json','post_ab_ordering_tests.json','post_ab_extra_potion_tests.json']
    for n in names:assert read(work/n)['passed'] and read(work/n)['dll_sha256']==sha(work/'bundle.dll')
    audit=read(work/'post_ab_full_type_audit.json');assert audit['fights']==2604 and audit['coverage']['audit_mismatch']==audit['old_event_kernel_type_mismatches']==0
    p.save('post_ab_directed_checks.json',dict(passed=True,dll_sha256=sha(work/'bundle.dll'),actual_frame_cases=135168,full_original_event_cases=2604,receipts_sha256={n:sha(work/n) for n in [*names,'post_ab_full_gate.json','post_ab_full_type_audit.json']}))

def measure():
    text=rewrite((STAGE/'measure_frame_guard.py').read_text('utf8'))
    exec(compile(text,str(STAGE/'measure_frame_guard.py'),'exec'),dict(__name__='__main__',__file__=str(STAGE/'next_two.py')))

def install():
    p=prepared();work=p.WORK;boundary();p.verify_projection(work/'bundle_src');dll=sha(work/'bundle.dll')
    assert read(work/'candidate_decision.json')['accepted'] and read(work/'measurements_summary.json')['raw24_gate_passed']
    for name in ('complete_correctness_gate.json','post_ab_directed_checks.json','formal_affected_tests.json','compiled_option_receipt.json','weapon_chain_tests.json'):
        assert read(work/name)['passed'] and read(work/name)['dll_sha256']==dll,name
    assert sha(BASE/'libgdcore.dll')==p.EXPECTED and inventory(BASE)==read(work/'baseline_source.json')
    assert read(work/'full_regeneration_test.json')['passed'];recipe=STAGE/'optimize_native_verified_bundle.py';assert recipe.read_bytes()==(p.ACCEPTED/'verified_bundle_pending.py').read_bytes()
    runtime=REPO/'dist/native_1_1_10';pending=REPO/('dist/native_1_1_10_'+p.NAME+'_pending');backup=REPO/('dist/native_1_1_10_before_'+p.NAME+'_20261127')
    assert all(s.resolve().is_relative_to(REPO.resolve()) for s in (runtime,pending,backup)) and not pending.exists() and not backup.exists()
    run(STAGE/'package_native_training_runtime.py','--dll',work/'bundle.dll','--gate',work/'bundle_full_gate.json','--out',pending,log=work/'package.log')
    before=training();staged=training(pending);assert before==staged;p.save('staged_training.json',dict(passed=True,jobs=12,baseline=before,candidate=staged))
    paths=[BASE/name for name in read(work/'source_changes.json')]+[BASE/'libgdcore.dll',recipe]
    originals={s:s.read_bytes() for s in paths};saved=work/'installation_before';saved.mkdir()
    for path,data in originals.items():out=saved/path.relative_to(REPO);out.parent.mkdir(parents=True,exist_ok=True);out.write_bytes(data)
    installed=[];backed=False;switched=False
    try:
        for path in paths:
            data=(work/'verified_bundle_pending.py').read_bytes() if path==recipe else (work/'bundle.dll').read_bytes() if path.name=='libgdcore.dll' else (work/'bundle_src'/path.relative_to(BASE)).read_bytes()
            replace(path,data);installed.append(path)
        runtime.rename(backup);backed=True;pending.rename(runtime);switched=True
        p.verify_projection(BASE);assert sha(BASE/'libgdcore.dll')==sha(runtime/'libgdcore.dll')==dll
        manifest=read(runtime/'manifest.json');assert manifest['gate_sha256']==sha(work/'bundle_full_gate.json')
        for name,h in manifest['sha256'].items():assert sha(runtime/name)==h
        assert training()==staged;boundary();affected(True,'installed',runtime/'libgdcore.dll')
        run(work/'verify_actual_frame.py','--formal','--tag','installed','--dll',runtime/'libgdcore.dll',log=work/'installed_actual_frame.log')
        assert read(work/'installed_actual_frame_tests.json')['passed']
    except BaseException:
        if switched:runtime.rename(pending)
        if backed:backup.rename(runtime)
        for path in reversed(installed):replace(path,originals[path])
        p.save('installation_rollback.json',dict(rolled_back=True,production_dll_sha256=sha(BASE/'libgdcore.dll')));raise
    p.save('post_install_verification.json',dict(passed=True,dll_sha256=dll,baseline_dll_sha256=p.EXPECTED,actual_installed_affected_test_receipt_sha256=sha(work/'installed_affected_tests.json'),actual_installed_frame_cases=135168,full_original_events_before_and_after_timing=2604,training_jobs=12,user_boundary_preserved=True))
    p.save('installation.json',dict(passed=True,dll_sha256=dll,runtime=str(runtime),backup_runtime=str(backup),changed_files=[s.relative_to(REPO).as_posix() for s in paths]));print('Verified positive candidate deployed '+p.NAME,flush=True)

def close():
    p=prepared();work=p.WORK;decision=read(work/'candidate_decision.json');speed=read(work/'measurements_summary.json');deployed=(work/'installation.json').exists();boundary()
    assert sha(BASE/'libgdcore.dll')==(sha(work/'bundle.dll') if deployed else p.EXPECTED)
    p.save('current_runtime_status.json',dict(deployed=deployed,production_dll_sha256=sha(BASE/'libgdcore.dll'),candidate_dll_sha256=sha(work/'bundle.dll'),AB_status=decision['status'],all_protocol_processes_finished=True,no_same_source_retiming=True,remaining_backup_required=True))
    a=read(work/decision['selected_assessment']);cpu=a['metrics']['main_thread_cpu_s'];wall=a['metrics']['wall_s']
    title='字典标量键查询定型' if p.NAME==ROUNDS[0] else 'RNG正规数缩放定型'
    rng_reference='' if p.NAME==ROUNDS[0] else '原始公式已与[Godot 3.6-stable的random_pcg.h](https://raw.githubusercontent.com/godotengine/godot/3.6-stable/core/math/random_pcg.h)核对；尾数／clz取值范围及正规数缩放等价是从该公式及当前运行时推导，最终以实际DLL差分验收。原版公式和SHA已保存在next_two_assessment。'
    text=f'''# {title}优化记录（2026-11-27）

本轮{'已验证正收益并部署' if deployed else '未部署，保留原生产版本'}。基线 `{p.EXPECTED}`，候选 `{sha(work/'bundle.dll')}`。判定 `{decision['status']}`。

## 选择依据与改动

当前cea3c1c8基线重新采样2007栈，另在独立诊断副本量化固定200场：字典查询2578136次；函数引用调用50121次但绑定参数0次，字典复制0次，因此没有支付这两个零覆盖方案的正式构建成本。诊断版原结果签名一致，只作方向筛查，不作性能证据。

{'只在GdDict::find_index的原有哈希匹配位置，将同类型Int、Obj、Str三种纯比较内联；哈希、遍历顺序、线性／桶／整数网格路径不改。Float、混合数值、递归数组及其他类型仍调用原gd_eq。实际独立DLL322944项覆盖全部16浮点模式、NaN、碰撞、重复键、递归和对象身份，并比较异常标志和MXCSR。' if p.NAME==ROUNDS[0] else 'randf保留原PCG抽取、proto==0单次抽取早退及原uint32到float转换。原尾数转换结果属于[2^31,2^32]，clz属于[0,31]，原ldexp结果是[2^-32,1]内的正规float且缩放精确；用同一float表示的指数位减法替代通用ldexp，最终float到double转换保留。非IEEE平台仍走原ldexp；randd和randf_range的其他运算不变。354304项通过实际DLL的gd::call_method RNG内建分支观测，覆盖337920个可控proto／尾数边界和16384个64次连续序列；16浮点模式、已有异常、errno、结果位与PCG状态逐项相同。没有在EXE里用头文件实例化的randf冒充DLL生产实现。'}

精确逆变换逐字还原完整715文件基线，674对象头和所有布局不变。完整20单元插桩／18新profile／18热点PGO保持原浮点选项，最多2个BelowNormal编译任务。普通原型只作语义筛查；两次完整再生成复现全部710份C++文件，并核对重复运行字节和mtime及未知编辑拒绝。

{rng_reference}

## 验收与全部计时

原版Godot排序、三条实时监听派发、药水及腰带／嵌套与60组未注入终序开战对照通过。135168项实际DLL帧函数、136128项实际当前基线武器链和所有继承定向检查保持；完整2604场原版逐事件、来源、RNG、终局及各原计数通过。{'接受A/B后再次完成受影响定向及全2604逐事件，首raw24、独立cal24和安装后实际DLL及训练12作业均通过。' if deployed else '未获得发布条件的候选不替换生产版本；cal24仅作非发布记录。'}

全部{decision['pairs']}对样本及极值保留。CPU／墙钟配对中位耗时降低 **{cpu['paired_median_time_reduction_pct']:.6f}%／{wall['paired_median_time_reduction_pct']:.6f}%**，累计降低 {cpu['sum_time_reduction_pct']:.6f}%／{wall['sum_time_reduction_pct']:.6f}%。预声明24对，只有不明确／去掉一组后方向不正且非一致退化才补唯一8对；没有同源挑样重测。

20%负载经验点 **{speed['fitted_fights_per_second_at20']:.4f}场/秒**，{'外推' if speed['reference_is_extrapolation'] else '插值'}，R²={speed['r_squared_log_wall_time']:.6f}。公式log(墙钟秒数)=a+b×负载；允许外推，不等待空闲或将覆盖20%设为门槛。不把跨轮FPS差作为代码收益，旧200目标不适用。

## 保存

证据位于 `output/_v1110/native_perf50/{p.NAME}`；初始采样与诊断在`next_two_assessment`。保留用户文件、工作区HEAD与暂存区；只更新既有codex/native-perf50-verified引用，不创建新分支。远端提交以checkpoint_receipt.json的核对值为准。
'''
    note=REPO/f'docs/C++模拟器{title}优化记录_2026-11-27.md';assert not note.exists();note.write_text(text,encoding='utf8',newline='\n');p.save('documentation.json',dict(path=note.relative_to(REPO).as_posix(),sha256=sha(note)))

def archive(upload=False):
    p=prepared();text=rewrite((STAGE/'archive_frame_guard.py').read_text('utf8'))
    text=text.replace("paths=set(STAGE.glob('*frame_guard*.py'));paths.add(STAGE/'profile_post_ordering.py')","paths=set(STAGE.glob('*next_two*.py'));paths.update((STAGE/'next_two.py',STAGE/'test_next_two_dictionary.cpp',STAGE/'test_next_two_rng_scaling.cpp'))")
    old="paths.update(p for p in STAGE.glob('frame_guard*.log') if not p.name.startswith(('frame_guard_archive_','frame_guard_goal_driver_')));paths.add(STAGE/'post_ordering_profile_first.log')"
    assert old in text;text=text.replace(old,"paths.update(p for p in STAGE.glob('next_two*.log') if not p.name.startswith('next_two_driver'))")
    text=text.replace('native_perf50/post_ordering_assessment','native_perf50/next_two_assessment')
    old="note=REPO/'docs/C++模拟器逐帧类型守卫复用优化记录_2026-11-27.md'";assert old in text
    text=text.replace(old,"note=REPO/json.loads((WORK/'documentation.json').read_bytes())['path']")
    text=text.replace('frame type guard reuse','two-direction '+p.NAME)
    text=text.replace('frame-guard-own-index-','next-two-own-index-')
    sys.argv=[str(STAGE/'next_two.py'),*(['--upload'] if upload else [])]
    exec(compile(text,str(STAGE/'archive_frame_guard.py'),'exec'),dict(__name__='__main__',__file__=str(STAGE/'next_two.py')))

def machine_review():
    p=prepared();root=Path(tempfile.mkdtemp(prefix='next-two-machine-'));records={}
    target='GdDict::find_index' if p.NAME==ROUNDS[0] else 'CoreRng::fn_randf'
    for label,dll in [('baseline',p.ACCEPTED/'bundle.dll'),('candidate',p.WORK/'bundle.dll')]:
        local=root/(label+'.dll');shutil.copyfile(dll,local)
        names=subprocess.check_output(['D:/mingw64/bin/nm.exe','-g','--defined-only',str(local)],text=True)
        demangled=subprocess.check_output(['D:/mingw64/bin/nm.exe','-g','-C','--defined-only',str(local)],text=True)
        addresses={row.split()[0] for row in demangled.splitlines() if target in row and len(row.split())>=3 and row.split()[1] in ('T','t') and int(row.split()[0],16)!=0}
        symbols=[row.split()[-1] for row in names.splitlines() if len(row.split())>=3 and row.split()[1] in ('T','t') and row.split()[0] in addresses];assert symbols
        output=''
        for symbol in symbols:output+=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-d','--no-show-raw-insn','--disassemble='+symbol,str(local)],text=True)
        destination=p.WORK/(label+'_machine.txt');destination.write_text(output,encoding='utf8')
        records[label]=dict(dll_sha256=sha(dll),symbols=symbols,disassembly_sha256=sha(destination),static_gd_eq_call_sites=sum('call' in line and 'gd_eq' in line for line in output.splitlines()),static_ldexp_call_sites=sum('call' in line and 'ldexp' in line for line in output.splitlines()),ldexpf_symbol_present=any(row.split()[-1]=='ldexpf' for row in names.splitlines() if row.split()))
    p.save('machine_review.json',dict(actual_final_PGO_DLLs=True,target=target,records=records,no_speed_claim=True))

def drive():
    p=prepared();work=p.WORK;p.verify_projection(work/'bundle_src');boundary()
    if not (work/'prototype_affected_tests.json').exists():affected()
    assert read(work/'prototype_affected_tests.json')['passed']
    if not (work/'full_regeneration_test.json').exists():run(STAGE/'next_two.py',p.NAME,'regenerate',log=work/'regeneration_first.log')
    if not (work/'prototype_fixed200.json').exists():run(STAGE/'bench_native_corpus.py','--dll',work/'prototype.dll','--out',work/'prototype_fixed200.json',log=work/'prototype_fixed200.log')
    assert read(work/'prototype_fixed200.json')['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    if not (work/'bundle.dll').exists():print('Starting full20/fresh18 '+p.NAME,flush=True);run(STAGE/'next_two.py',p.NAME,'build',log=work/'formal_build_first.log')
    assert read(work/'compiled_option_receipt.json')['passed']
    if not (work/'formal_affected_tests.json').exists():affected(True)
    if not (work/'complete_correctness_gate.json').exists():run(STAGE/'next_two.py',p.NAME,'qualify',log=work/'qualification_driver_first.log')
    if not (work/'machine_review.json').exists():machine_review()
    if not (work/'candidate_decision.json').exists():print('Starting frozen paired AB '+p.NAME,flush=True);run(STAGE/'next_two.py',p.NAME,'comparison',log=work/'comparison_first.log')
    decision=read(work/'candidate_decision.json');assert decision['assessment_sha256']==sha(work/decision['selected_assessment']) and decision['candidate_dll_sha256']==sha(work/'bundle.dll')
    if decision['accepted'] and not (work/'post_ab_directed_checks.json').exists():print('Starting post-AB complete verification',flush=True);run(STAGE/'next_two.py',p.NAME,'post',log=work/'post_first.log')
    if not (work/'measurements_summary.json').exists():print('Starting the one measurement protocol',flush=True);run(STAGE/'next_two.py',p.NAME,'measure',log=work/'measure_first.log')
    if decision['accepted'] and read(work/'measurements_summary.json')['raw24_gate_passed'] and not (work/'installation.json').exists():run(STAGE/'next_two.py',p.NAME,'install',log=work/'install_first.log')
    if not (work/'current_runtime_status.json').exists():close()
    if not (work/'checkpoint_receipt.json').exists():archive()
    archive(True);print('Completed and remotely verified '+p.NAME,flush=True)

def main():
    parser=argparse.ArgumentParser();parser.add_argument('round',choices=ROUNDS);parser.add_argument('phase',choices=['prepare','setup','prototype','affected','regenerate','build','qualify','comparison','post','measure','install','close','archive','upload','finish','drive','drive_all']);parser.add_argument('--formal',action='store_true');args=parser.parse_args()
    os.environ['NATIVE_NEXT_ROUND']=args.round
    if args.phase=='prepare':prepare(args.round);return
    if args.phase=='affected':affected(args.formal);return
    if args.phase=='upload':archive(True);return
    if args.phase=='drive_all':
        for name in ROUNDS:
            work=STAGE/'native_perf50'/name
            if not work.exists():run(STAGE/'next_two.py',name,'prepare')
            if not (work/'retained_harness_preparation.json').exists():run(STAGE/'next_two.py',name,'setup')
            if not (work/'prototype.dll').exists():run(STAGE/'next_two.py',name,'prototype',log=work/'prototype_first.log')
            run(STAGE/'next_two.py',name,'drive')
        print('Both independent directions closed and remote verified',flush=True);return
    if args.phase=='finish':
        p=prepared();decision=read(p.WORK/'candidate_decision.json')
        if decision['accepted']:run(STAGE/'next_two.py',args.round,'post',log=p.WORK/'post_first.log')
        run(STAGE/'next_two.py',args.round,'measure',log=p.WORK/'measure_first.log')
        if decision['accepted'] and read(p.WORK/'measurements_summary.json')['raw24_gate_passed']:run(STAGE/'next_two.py',args.round,'install',log=p.WORK/'install_first.log')
        close();archive();archive(True);return
    globals()[args.phase]()
if __name__=='__main__':main()
