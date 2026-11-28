"""Cheap phase-plan screen against the actual production helper; no full build."""
import argparse,json,os,shutil,subprocess,tempfile
from pathlib import Path
import psutil
from native_build_storage import isolated_build
from prepare_quiet_round import STAGE,ACCEPTED,EXPECTED,sha
WORK=STAGE/'native_perf50/architecture_three_bundle'


@isolated_build
def main():
    parser=argparse.ArgumentParser();parser.add_argument('--live',action='store_true');args=parser.parse_args()
    prefix='phase_plan_live_probe' if args.live else 'phase_plan_probe'
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    root=Path(tempfile.mkdtemp(prefix='phase-plan-probe-'));source=STAGE/('test_phase_plan_live_probe.cpp' if args.live else 'test_phase_plan_probe.cpp')
    assert not (WORK/(prefix+'_receipt.json')).exists()
    shutil.copyfile(source,root/'probe.cpp');shutil.copyfile(ACCEPTED/'bundle.dll',root/'libgdcore.dll')
    assert sha(root/'libgdcore.dll')==EXPECTED
    with (WORK/(prefix+'_compile.log')).open('xb') as stream:
        subprocess.run(['D:/mingw64/bin/g++.exe','-O3','-std=c++20','-march=native','-ffp-contract=off','-static','-I',str(STAGE),'-I',str(ACCEPTED/'bundle_src'),str(root/'probe.cpp'),str(root/'libgdcore.dll'),'-o',str(root/'probe.exe')],stdout=stream,stderr=subprocess.STDOUT,check=True,cwd=root)
    process=psutil.Popen([str(root/'probe.exe')],stdout=subprocess.PIPE,stderr=subprocess.PIPE,creationflags=subprocess.CREATE_NO_WINDOW|subprocess.BELOW_NORMAL_PRIORITY_CLASS)
    process.cpu_affinity([2]);out,error=process.communicate(timeout=120)
    (WORK/(prefix+'_raw.json')).write_bytes(out);(WORK/(prefix+'_stderr.log')).write_bytes(error)
    if process.returncode:raise RuntimeError(f'Phase probe failed {process.returncode}: '+error.decode('utf8','replace')[-1000:])
    r=json.loads(out);assert r['semantic_cases']==48 and len(r['samples'])==48
    for mode in range(3):assert len({x['signature'] for x in r['samples'] if x['mode']==mode})==1
    (WORK/(prefix+'_receipt.json')).write_text(json.dumps(dict(passed=True,source_sha256=sha(source),baseline_dll_sha256=EXPECTED,raw_sha256=sha(WORK/(prefix+'_raw.json')),semantic_cases=48,actual_production_function_via_GetProcAddress=True,ideal_no_callback_upper_bound_only=True,live_mutable_fields_read_each_step=args.live,no_full_DLL_or_PGO_build=True,no_release_speed_claim=True),indent=2)+'\n',encoding='utf8')
    print('Phase-plan ideal-cost probe passed;48 FP cases and48 timing arms retained',flush=True)


if __name__=='__main__':main()
