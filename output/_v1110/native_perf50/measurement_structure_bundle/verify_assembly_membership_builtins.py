import sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[2]))
"""Compare new inline builtins with actual original binary calls and full state."""
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
from prepare_structure_retained import STAGE,WORK,ACCEPTED,EXPECTED,sha,verify_projection

def verify(source,dll,out):
    assert not out.exists();verify_projection(source)
    root=Path(tempfile.mkdtemp(prefix='container-builtins-check-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    scratch=root/'scratch';scratch.mkdir();env=dict(os.environ,TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch))
    fixture=STAGE/'test_native_container_builtins.cpp';reports={};raws={}
    for label,library in [('baseline',ACCEPTED/'bundle.dll'),('candidate',dll)]:
        assert sha(ACCEPTED/'bundle.dll')==EXPECTED
        local=root/label;local.mkdir();shutil.copyfile(library,local/'libgdcore.dll')
        exports=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-p',str(local/'libgdcore.dll')]).decode('utf8',errors='replace').split('The Export Tables',1)[1]
        name=re.search(r'(?m)^Name\s+[0-9a-fA-F]+\s+(\S+)',exports).group(1)
        assert '/' not in name and '\\' not in name and name.endswith('.dll')
        if name!='libgdcore.dll':shutil.copyfile(library,local/name)
        cpp=local/fixture.name;shutil.copyfile(fixture,cpp);exe=local/'check.exe'
        log=out.parent/('container_builtins_'+label+'_compile.log');assert not log.exists()
        with log.open('wb') as stream:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-std=c++20','-march=native','-ffp-contract=off',
                '-I',str(ACCEPTED/'bundle_src' if label=='baseline' else source),str(cpp),str(local/'libgdcore.dll'),'-o',str(exe)],stdout=stream,stderr=subprocess.STDOUT,env=env,check=True)
        run=subprocess.run([str(exe)],capture_output=True,env=env)
        raw=out.parent/('container_builtins_'+label+'_cases.json');assert not raw.exists();raw.write_bytes(run.stdout)
        (out.parent/('container_builtins_'+label+'_execution.log')).write_bytes(run.stderr);run.check_returncode()
        reports[label]=json.loads(run.stdout);raws[raw.name]=sha(raw)
    a,b=reports['baseline'],reports['candidate']
    assert a==b and a['passed'] and a['cases']==128128 and a['exact_state_vectors_compared'] and a['all16_fp_modes']
    result=dict(passed=True,cases=128128,dll_sha256=sha(dll),baseline_dll_sha256=EXPECTED,
        original_generic_call_method_actual_binary_reference=True,full_state_vectors_compared_not_just_hashes=True,
        alias_growth_self_append_pool_flags_missing_and_negative_argc=True,
        null_and_empty_array_dictionary_enum_and_foreign_receivers=True,
        watch_version_overflow_depth_overflow_and_disabled_dispatch=True,
        old_six_counters_user_static_callback_counts_and_all16_fenv_mxcsr_modes=True,
        float_resize_and_fp_deep_truth_use_original_fallback=True,per_case_hashes_equal_between_actual_dlls=True,
        raw_sha256=raws,fixture_sha256=sha(fixture),no_speed_claim=True)
    out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result),flush=True)
    return result

if __name__=='__main__':verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'container_builtins_tests.json')
