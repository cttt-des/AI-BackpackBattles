import sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[2]))
"""Test inline truth against the actual independent old/new runtime functions."""
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
from prepare_next_two_retained import STAGE,WORK,ACCEPTED,EXPECTED,sha,verify_projection

def verify(source,dll,out):
    assert not out.exists();verify_projection(source)
    root=Path(tempfile.mkdtemp(prefix='scalar-truth-check-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    scratch=root/'scratch';scratch.mkdir();env=dict(os.environ,TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch))
    fixture=STAGE/'test_native_scalar_truth.cpp';reports={};files={}
    for label,library in [('baseline',ACCEPTED/'bundle.dll'),('candidate',dll)]:
        assert sha(ACCEPTED/'bundle.dll')==EXPECTED
        folder=root/label;folder.mkdir();shutil.copyfile(library,folder/'libgdcore.dll')
        exports=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-p',str(folder/'libgdcore.dll')]).decode('utf8',errors='replace').split('The Export Tables',1)[1]
        name=re.search(r'(?m)^Name\s+[0-9a-fA-F]+\s+(\S+)',exports).group(1)
        assert '/' not in name and '\\' not in name and name.endswith('.dll')
        if name!='libgdcore.dll':shutil.copyfile(library,folder/name)
        local=folder/fixture.name;shutil.copyfile(fixture,local);exe=folder/'check.exe'
        log=out.parent/('scalar_truth_'+label+'_compile.log');assert not log.exists()
        with log.open('wb') as stream:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-std=c++20','-march=native','-ffp-contract=off',
                '-I',str(source),str(local),str(folder/'libgdcore.dll'),'-o',str(exe)],stdout=stream,stderr=subprocess.STDOUT,env=env,check=True)
        run=subprocess.run([str(exe)],capture_output=True,env=env)
        raw=out.parent/('scalar_truth_'+label+'_cases.json');assert not raw.exists();raw.write_bytes(run.stdout)
        (out.parent/('scalar_truth_'+label+'_execution.log')).write_bytes(run.stderr);run.check_returncode()
        reports[label]=json.loads(run.stdout);files[raw.name]=sha(raw)
    a,b=reports['baseline'],reports['candidate']
    assert a==b and a['passed'] and a['cases']>30000 and a['four_roundings_four_daz_ftz']
    result=dict(passed=True,cases=a['cases'],value_shapes=a['value_shapes'],dll_sha256=sha(dll),baseline_dll_sha256=EXPECTED,
        independent_original_gd_truth_actual_dll_reference=True,baseline_and_candidate_case_hashes_equal=True,
        null_bool_full_int64_float_bit_patterns_vec2_color_string_arrays_dicts_pointer_and_unknown_kinds=True,
        signaling_nan_subnormals_signed_zero_fenv_mxcsr_and_single_evaluation_checked=True,
        all16_rounding_daz_ftz_modes=True,fixture_sha256=sha(fixture),raw_sha256=files,no_speed_claim=True)
    out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result),flush=True)
    return result

if __name__=='__main__':verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'scalar_truth_tests.json')
