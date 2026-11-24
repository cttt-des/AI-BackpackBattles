"""Prepare one distinct PTA trial with the existing complete evaluation gates."""
import ast
import json
from pathlib import Path
import re
import subprocess
from prepare_native_compiler_pta import STAGE,WORK,ACCEPTED,BACKUP,EXPECTED,ARCHIVE,FLAGS,sha

def once(text,old,new):
    assert text.count(old)==1,(old[:90],text.count(old));return text.replace(old,new,1)

def update(text):
    text=text.replace('object_routes_bundle','compiler_pta_bundle').replace('callback_dispatch_bundle','object_routes_bundle')
    text=text.replace('prepare_native_object_routes','prepare_native_compiler_pta')
    text=text.replace('prototype_native_object_routes_bundle','prepare_native_compiler_pta')
    text=text.replace('prototype_native_compiler_pta_bundle','prepare_native_compiler_pta')
    text=text.replace('80a0681c1c93268af2b29c21e5439b6444de36a29ad39486b3f4afadf548a44a',EXPECTED)
    text=text.replace('72dd9c1575087596ad0409b939104a0113033e40',ARCHIVE)
    text=text.replace('native-object-routes-','native-compiler-pta-')
    return text

WAIT_SCRIPT='''"""Wait before the first independent calibration; never resample an observed run."""
import json
from pathlib import Path
import time
import psutil
WORK=Path(__file__).resolve().parent
assert not (WORK/'bundle_load_calibration.json').exists()
assert not (WORK/'rejected_load_calibration.json').exists()
assert not (WORK/'calibration_eligibility.json').exists()
started=time.monotonic();consecutive=[];samples=0;last_log=started-30
print('Waiting for3 consecutive idle CPU observations<=12%, before the sole calibration',flush=True)
while len(consecutive)<3:
    load=psutil.cpu_percent(interval=1);samples+=1
    consecutive=consecutive+[load] if load<=12 else []
    now=time.monotonic()
    if now-last_log>=30:
        record=dict(status='waiting_before_first_calibration',latest_idle_cpu_pct=load,consecutive=len(consecutive),
            elapsed_seconds=now-started,observations=samples,no_candidate_benchmarks_used=True)
        (WORK/'calibration_wait_status.json').write_text(json.dumps(record,indent=2)+'\\n',encoding='utf8')
        print(f'Idle CPU={load:.1f}%; eligible observations={len(consecutive)}/3',flush=True);last_log=now
(WORK/'calibration_eligibility.json').write_text(json.dumps(dict(passed=True,maximum_idle_cpu_pct=12,
    qualifying_observations=consecutive,observations=samples,elapsed_seconds=time.monotonic()-started,
    no_candidate_benchmarks_used=True,calibration_not_yet_started=True),indent=2)+'\\n',encoding='utf8')
print('Eligible; start the original warm30/calibration24 once',flush=True)
'''

def main():
    assert not WORK.exists();WORK.mkdir()
    checkpoint=json.loads((BACKUP/'checkpoint_receipt.json').read_bytes())
    assert checkpoint['remote_upload_verified'] and checkpoint['remote_verified_commit']==ARCHIVE
    assert sha(STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll')==EXPECTED
    for path in ACCEPTED.glob('*.py'):
        if path.name=='verified_bundle_pending.py':continue
        text=update(path.read_text('utf8'))
        if path.name in ('build_bundle.py','resume_build.py'):
            text=text.replace('from build_native_hot_lto import','from build_native_compiler_pta import')
        if path.name=='build_bundle.py':
            text=once(text,"STAGE/'native_perf50/object_routes_bundle/checkpoint_receipt.json'", "STAGE/'native_perf50/private_snapshots_bundle/checkpoint_receipt.json'")
            text=once(text,"    objects=Path(tempfile.mkdtemp(prefix='native-compiler-pta-'))", "    cache=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds';cache.mkdir(exist_ok=True)\n    build_root=Path(tempfile.mkdtemp(prefix='compiler-pta-formal-',dir=cache))\n    objects=build_root/'objects';objects.mkdir();scratch=build_root/'scratch';scratch.mkdir()\n    os.environ.update(TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch))\n    tempfile.tempdir=str(scratch)\n    save('persistent_build_directory.json',dict(root=str(build_root),objects=str(objects),scratch=str(scratch)))")
            text=once(text,"link_flags=('-Wl,--exclude-all-symbols',str(definition)))", "link_flags=('-save-temps=obj','-Wl,--exclude-all-symbols',str(definition)))")
            text=once(text,"hot_units=HOT_UNITS)\n    shutil.copyfile(dll", "hot_units=HOT_UNITS,link_flags=('-save-temps=obj',))\n    shutil.copyfile(dll")
            text=once(text,"'floating_options_unchanged':True}", "'floating_options_unchanged':True,'compiler_optimization_flags':['-fipa-pta'],'same_compiler_configuration_in_both_profile_phases':True}")
        if path.name=='run_release_measurements.py':
            text=once(text,"    print('Starting one controlled load-calibration24 run',flush=True)", "    subprocess.run([*python,str(WORK/'wait_calibration_window.py')],check=True)\n    print('Starting one controlled load-calibration24 run',flush=True)")
        if path.name=='verify_installed.py':
            text=once(text,"    assert profile['floating_options_unchanged']", "    assert profile['floating_options_unchanged']") if "    assert profile['floating_options_unchanged']" in text else text
            needle="    assert profile['source_manifest_sha256']==sha(WORK/'source_before_build.json')"
            text=once(text,needle,needle+"\n    assert profile['compiler_optimization_flags']==['-fipa-pta'] and profile['same_compiler_configuration_in_both_profile_phases']")
        ast.parse(text,filename=path.name);(WORK/path.name).write_text(text,encoding='utf8',newline='\n')
    (WORK/'wait_calibration_window.py').write_text(WAIT_SCRIPT,encoding='utf8',newline='\n');ast.parse(WAIT_SCRIPT)
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json'):
        (WORK/name).write_bytes((ACCEPTED/name).read_bytes())
    compiler='D:/mingw64/bin/g++.exe'
    version=subprocess.check_output([compiler,'--version']).decode('utf8',errors='replace')
    options=subprocess.check_output([compiler,'-Q','-O3','--help=optimizers']).decode('utf8',errors='replace')
    selected=[line.strip() for line in options.splitlines() if '-fipa-pta ' in line]
    assert len(selected)==1 and '[disabled]' in selected[0]
    record=dict(compiler=compiler,compiler_sha256=sha(Path(compiler)),version=version.splitlines()[0],
        default_optimization_query=[compiler,'-Q','-O3','--help=optimizers'],observed_default=selected[0],
        candidate_flags=list(FLAGS),source_changes=[],source_file_count=707,private_snapshots_not_included=True,
        documentation='https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#index-fipa-pta',
        documented_purpose='interprocedural pointer and modification/reference analysis',
        documented_cost='can cause excessive memory and compile time; not enabled by default',
        compiler_memory_guard='min45% physical RAM,65% available RAM at each build phase; only owned compiler descendants',
        no_floating_option_change=True,no_speed_claim=True)
    (WORK/'compiler_configuration.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf8')
    plan=json.loads((ACCEPTED/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,latest_remote_verified_production_backup=ARCHIVE,
        prior_trial_remote_archive=ARCHIVE,components=['compiler -fipa-pta'],full_source_changes=[],candidate_source_files=707,
        new_layout_changes=False,compiler_optimization_flags=list(FLAGS),private_snapshots_not_included=True,
        first_calibration_eligibility=dict(maximum_idle_cpu_pct=12,consecutive_observations=3,interval_seconds=1,
            no_simulations_used=True,only_before_first_calibration=True,no_observed_measurements_repeated=True))
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    # Source is unchanged; its known prototype manifest must match exactly.
    assert json.loads((STAGE/'native_perf50/object_routes_prototype/transform.json').read_bytes())['source_sha256']==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    print('Prepared compiler-only PTA configuration; unchanged707-source baseline,full20/fresh18 and original complete gates')

if __name__=='__main__':main()
