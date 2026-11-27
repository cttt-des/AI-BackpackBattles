"""Independent original-DLL state/FP comparison and exercised corpus smoke."""
import argparse,ctypes,hashlib,json,re,shutil,subprocess,tempfile
import psutil
from pathlib import Path
from native_build_storage import isolated_build
from prepare_quiet_round import WORK,STAGE,ACCEPTED,sha,save,verify_projection

CLASSES=['CoreContext','CoreCombat','CoreCharacter','CoreRng','CoreBuff','CoreItem','CoreGrid','CoreTimer','CoreContext__INNER__NativeFlicker']

@isolated_build
def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    p=argparse.ArgumentParser();p.add_argument('--tag',required=True);p.add_argument('--dll',type=Path,required=True);a=p.parse_args()
    verify_projection(WORK/'bundle_src');checks=WORK/(a.tag+'_quiet_core_checks');assert not checks.exists();checks.mkdir()
    text=(STAGE/'test_quiet_core.cpp').read_text('utf8');functions=[];fields={}
    for name in CLASSES:
        cls='Gd__gd_core__'+name;header=ACCEPTED/'bundle_src/gen/hdrs'/(cls+'.hpp');names=re.findall(r'^    gd::GdVal (f_\w+);$',header.read_text('utf8'),re.M);assert names
        fields[cls]=names;functions.append('void capture(const '+cls+'& o){'+''.join('val(o.'+n+');' for n in names)+'}')
    assert text.count('// GENERATED_CAPTURE_FUNCTIONS')==1;text=text.replace('// GENERATED_CAPTURE_FUNCTIONS','\n'.join(functions))
    fixture=checks/'test_actual_quiet_core.cpp';fixture.write_text(text,encoding='utf8',newline='\n');root=Path(tempfile.mkdtemp(prefix='quiet-core-actual-'))
    baseline=ACCEPTED/('prototype.dll' if a.tag.startswith(('development','prototype')) else 'bundle.dll');data={}
    for label,dll in [('candidate',a.dll),('baseline',baseline)]:
        folder=root/label;folder.mkdir();shutil.copyfile(dll,folder/'libgdcore.dll');shutil.copyfile(fixture,folder/'test.cpp')
        with (checks/(label+'_compile.log')).open('wb') as stream:subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off','-I',str(ACCEPTED/'bundle_src'),str(folder/'test.cpp'),str(folder/'libgdcore.dll'),'-o',str(folder/'check.exe')],stdout=stream,stderr=subprocess.STDOUT,check=True)
        args=[str(folder/'check.exe')]
        if label=='baseline':
            lengths=folder/'lengths.txt';lengths.write_text('\n'.join(map(str,data['candidate']['lengths']))+'\n',encoding='ascii');args.append(str(lengths))
        result=subprocess.run(args,capture_output=True,timeout=180);(checks/(label+'_raw.json')).write_bytes(result.stdout);(checks/(label+'_stderr.log')).write_bytes(result.stderr);result.check_returncode();data[label]=json.loads(result.stdout)
    cases=16*8*42*6*2
    assert data['candidate']==data['baseline'] and data['candidate']['cases']==cases and data['candidate']['accepted_segments']>=400
    from bench_native_corpus import load_simulator,prepare,select_cases,measure
    sim=load_simulator(a.dll);enable=sim.lib.gd_diag_quiet_core_enable;enable.argtypes=[ctypes.c_int];enable.restype=None;enable(1)
    stat=sim.lib.gd_diag_quiet_core_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    digest=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),digest));before=[stat(i) for i in range(5)];r=measure(sim,jobs,1,0,continuous=True);counts=[stat(i)-before[i] for i in range(5)]
    assert digest.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef' and r['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    assert counts[2]>0 and counts[3]>10000,counts
    save(a.tag+'_quiet_core_tests.json',dict(passed=True,dll_sha256=sha(a.dll),baseline_dll_sha256=sha(baseline),actual_separate_DLLs=True,cases=cases,accepted_segments=data['candidate']['accepted_segments'],all_declared_game_fields_compared=fields,all16_FP_modes_and_preexisting_flags=True,RNG_state_and_errno_and_MXCSR_compared=True,unknowns_and_aliases_fall_back_without_writes=True,original_frame_function_source_unchanged=True,fixed200_results_sha256=r['results_sha256'],fixed200_inputs_sha256=digest.hexdigest(),exercised_core_counts=dict(zip(['attempts','rejected','segments','frames','lanes'],counts)),fixed200_no_speed_claim=True,fixture_sha256=sha(fixture),raw_sha256={label:sha(checks/(label+'_raw.json')) for label in data}))
    print(a.tag+' quiet core'+str(cases)+' passed; exercised '+str(counts[3])+' corpus frames',flush=True)

if __name__=='__main__':main()
