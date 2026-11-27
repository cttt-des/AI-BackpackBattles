import sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[2]))
"""Compare exact typed helper bytes with actual old/new runtime operations."""
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
from prepare_frame_guard_retained import STAGE,WORK,ACCEPTED,EXPECTED,HELPERS,sha,verify_projection

def verify(source,dll,out):
    assert not out.exists();verify_projection(source)
    checks=out.parent/(out.stem+'_checks');assert not checks.exists();checks.mkdir()
    assert (source/'gen/shards/shard_00.cpp').read_text('utf8').count(HELPERS)==1
    retained=(STAGE/'test_native_identity_lookup.cpp').read_text('utf8')
    start=retained.index('    gd::BattleCtx ctx;Foreign first');end=retained.index('    std::vector<gd::GdArr*> arrays=',start)
    values=retained[start:end];assert 'values.push_back(v);' in values
    (checks/'buff_integer_helpers.hpp').write_text(HELPERS,encoding='utf8',newline='\n')
    (checks/'buff_integer_values.hpp').write_text(values,encoding='utf8',newline='\n')
    root=Path(tempfile.mkdtemp(prefix='buff-integer-helpers-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    scratch=root/'scratch';scratch.mkdir();env=dict(os.environ,TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch))
    fixture=STAGE/'test_native_buff_integer_helpers.cpp';reports={};raws={}
    for label,library in [('baseline',ACCEPTED/'bundle.dll'),('candidate',dll)]:
        assert sha(ACCEPTED/'bundle.dll')==EXPECTED
        local=root/label;local.mkdir();shutil.copyfile(library,local/'libgdcore.dll')
        exports=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-p',str(local/'libgdcore.dll')]).decode('utf8',errors='replace').split('The Export Tables',1)[1]
        name=re.search(r'(?m)^Name\s+[0-9a-fA-F]+\s+(\S+)',exports).group(1)
        assert '/' not in name and '\\' not in name and name.endswith('.dll')
        if name!='libgdcore.dll':shutil.copyfile(library,local/name)
        for f in (fixture,checks/'buff_integer_helpers.hpp',checks/'buff_integer_values.hpp'):shutil.copyfile(f,local/f.name)
        exe=local/'check.exe'
        with (checks/(label+'_compile.log')).open('wb') as log:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-std=c++20','-march=native','-ffp-contract=off',
                '-I',str(source),str(local/fixture.name),str(local/'libgdcore.dll'),'-o',str(exe)],stdout=log,stderr=subprocess.STDOUT,env=env,check=True)
        run=subprocess.run([str(exe)],capture_output=True,env=env)
        raw=checks/(label+'_cases.json');raw.write_bytes(run.stdout);(checks/(label+'_execution.log')).write_bytes(run.stderr);run.check_returncode()
        reports[label]=json.loads(run.stdout);raws[raw.name]=sha(raw)
    a,b=reports['baseline'],reports['candidate']
    for r in (a,b):
        assert r['passed'] and r['cases']==204288 and r['value_shapes']==112
        assert r['pair_cases']==200704 and r['unary_cases']==3584 and r['operation_checks']==806160 and r['all16_fp_modes']
        assert r['original_undefined_null_string_comparisons_skipped']==240
    assert a['fast_operation_checks']==b['fast_operation_checks'] and a['fast_operation_checks']>9000
    assert a['fast_operations_hash']==b['fast_operations_hash']
    result=dict(passed=True,cases=a['cases'],operation_checks=a['operation_checks'],dll_sha256=sha(dll),baseline_dll_sha256=EXPECTED,
        exact_private_helper_bytes_compared=True,actual_original_runtime_operation_reference=True,
        full_value_vectors_flags_mxcsr_and_input_bytes_compared=True,full_int64_overflow_small53_boundary_nan_and_complex_fallbacks=True,
        four_rounding_and_four_daz_ftz_modes=True,no_object_callbacks=True,fixture_sha256=sha(fixture),
        within_each_actual_dll_all_operations_exact=True,cross_dll_new_fast_operations_exact=True,
        cross_dll_fast_operation_checks=a['fast_operation_checks'],
        unchanged_fallback_runtime_cross_compiler_hash_equal=a['hash']==b['hash'],
        helper_sha256=sha(checks/'buff_integer_helpers.hpp'),value_matrix_sha256=sha(checks/'buff_integer_values.hpp'),
        raw_sha256=raws,original_undefined_null_string_comparisons_skipped=240,
        scope='Exact private helper bytes instantiated in fixture; actual Buff integration additionally verified through DLL methods and full corpus',no_speed_claim=True)
    out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result),flush=True);return result
if __name__=='__main__':verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'typed_helper_tests.json')
