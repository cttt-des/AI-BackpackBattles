"""Check identity/lookup values and FP state against independent original DLLs."""
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
from prepare_native_identity_lookup import STAGE,WORK,ACCEPTED,EXPECTED,sha,verify_projection

def verify(source,dll,out):
    assert not out.exists();verify_projection(source)
    checks=out.parent/(out.stem+'_checks');assert not checks.exists();checks.mkdir()
    root=Path(tempfile.mkdtemp(prefix='identity-lookup-check-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    scratch=root/'scratch';scratch.mkdir();env=dict(os.environ,TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch))
    fixture=STAGE/'test_native_identity_lookup.cpp';reports={};raws={}
    for label,library in [('baseline',ACCEPTED/'bundle.dll'),('candidate',dll)]:
        assert sha(ACCEPTED/'bundle.dll')==EXPECTED
        local=root/label;local.mkdir();shutil.copyfile(library,local/'libgdcore.dll')
        exports=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-p',str(local/'libgdcore.dll')]).decode('utf8',errors='replace').split('The Export Tables',1)[1]
        name=re.search(r'(?m)^Name\s+[0-9a-fA-F]+\s+(\S+)',exports).group(1)
        assert '/' not in name and '\\' not in name and name.endswith('.dll')
        if name!='libgdcore.dll':shutil.copyfile(library,local/name)
        cpp=local/fixture.name;shutil.copyfile(fixture,cpp);exe=local/'check.exe'
        log=checks/('identity_lookup_'+label+'_compile.log');assert not log.exists()
        with log.open('wb') as stream:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-std=c++20','-march=native','-ffp-contract=off',
                '-I',str(source),str(cpp),str(local/'libgdcore.dll'),'-o',str(exe)],stdout=stream,stderr=subprocess.STDOUT,env=env,check=True)
        run=subprocess.run([str(exe)],capture_output=True,env=env)
        raw=checks/('identity_lookup_'+label+'_cases.json');assert not raw.exists();raw.write_bytes(run.stdout)
        (checks/('identity_lookup_'+label+'_execution.log')).write_bytes(run.stderr);run.check_returncode()
        reports[label]=json.loads(run.stdout);raws[raw.name]=sha(raw)
    a,b=reports['baseline'],reports['candidate']
    assert a==b and a['passed'] and a['cases']==396400 and a['value_shapes']==112
    assert a['pair_cases']==200704 and a['array_cases']==145152 and a['alias_cases']==2144 and a['dictionary_cases']==48384 and a['once_cases']==16
    assert a['full_observations_compared'] and a['all16_fp_modes'] and len(a['grid_observations'])==10752
    result=dict(passed=True,cases=a['cases'],value_shapes=a['value_shapes'],dll_sha256=sha(dll),baseline_dll_sha256=EXPECTED,
        pair_cases=a['pair_cases'],array_cases=a['array_cases'],alias_cases=a['alias_cases'],dictionary_cases=a['dictionary_cases'],
        actual_original_binary_gd_eq_reference=True,exact_value_flags_and_mxcsr_observations_compared=True,
        integer_grid_full_observations_equal_between_independent_dlls=True,readonly_input_bytes_and_container_layout_preserved=True,
        unknown_kinds_all_pointer_kinds_null_nan_denormal_large_int_mixed_numeric_and_nested_arrays=True,
        original_hash_gates_collision_buckets_grid_fallback_and_integer_wrap_boundaries=True,
        all16_fp_modes_and_no_callbacks=True,raw_sha256=raws,fixture_sha256=sha(fixture),no_speed_claim=True)
    out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result),flush=True)
    return result

if __name__=='__main__':verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'identity_lookup_tests.json')
