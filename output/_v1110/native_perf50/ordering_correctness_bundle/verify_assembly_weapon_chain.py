"""Compare public entrypoints in independent production and candidate DLLs."""
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import psutil
from prepare_ordering_retained import STAGE,WORK,ACCEPTED,EXPECTED,sha,inventory,verify_projection

def verify(source,dll,out,baseline_source=None,baseline_dll=None):
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not out.exists();verify_projection(source)
    checks=out.parent/(out.stem+'_checks');assert not checks.exists();checks.mkdir()
    fixture=STAGE/'test_native_weapon_chain.cpp'
    dependencies=[fixture,*[WORK/n for n in ['damage_fixture.hpp','damage_state_fields.hpp','weapon_fixture_base.cpp']]]
    for p in dependencies:shutil.copyfile(p,checks/p.name)
    root=Path(tempfile.mkdtemp(prefix='weapon-chain-diff-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    scratch=root/'scratch';scratch.mkdir();env=dict(os.environ,TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch))
    reports={};raws={}
    reference_source=ACCEPTED/'bundle_src' if baseline_source is None else baseline_source
    reference_dll=ACCEPTED/'bundle.dll' if baseline_dll is None else baseline_dll
    assert inventory(reference_source)==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    reference_sha=sha(reference_dll)
    if baseline_dll is None:assert reference_sha==EXPECTED
    else:assert reference_sha=='293b87e24986dd9dcf2dbecff5510fb7a0b0e993324478bd09ba22bb88aadfba'
    for label,headers,library in [('baseline',reference_source,reference_dll),('candidate',source,dll)]:
        assert sha(ACCEPTED/'bundle.dll')==EXPECTED
        local=root/label;local.mkdir();shutil.copyfile(library,local/'libgdcore.dll')
        exports=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-p',str(local/'libgdcore.dll')]).decode('utf8',errors='replace').split('The Export Tables',1)[1]
        name=re.search(r'(?m)^Name\s+[0-9a-fA-F]+\s+(\S+)',exports).group(1)
        assert '/' not in name and '\\' not in name and name.endswith('.dll')
        if name!='libgdcore.dll':shutil.copyfile(library,local/name)
        for p in dependencies:shutil.copyfile(p,local/p.name)
        exe=local/'check.exe'
        with (checks/(label+'_compile.log')).open('wb') as log:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-std=c++20','-march=native','-ffp-contract=off',
                '-I',str(local),'-I',str(headers),str(local/fixture.name),str(local/'libgdcore.dll'),'-o',str(exe)],stdout=log,stderr=subprocess.STDOUT,env=env,check=True)
        run=subprocess.run([str(exe)],capture_output=True,env=env)
        p=checks/(label+'_cases.json');p.write_bytes(run.stdout);(checks/(label+'_execution.log')).write_bytes(run.stderr);run.check_returncode()
        reports[label]=json.loads(run.stdout);raws[p.name]=sha(p)
    a,b=reports['baseline'],reports['candidate'];differences={}
    for r in (a,b):assert r['passed'] and r['cases']==136128 and r['retained_damage_cases']==103360 and r['whole_chain_cases']==32768
    for key in ['case_hashes','legacy_counter_hashes']:
        assert len(a[key])==len(b[key])==136128
        differences[key]=[i for i,(u,v) in enumerate(zip(a[key],b[key])) if u!=v]
    result=dict(passed=not any(differences.values()),cases=136128,retained_damage_cases=103360,whole_chain_cases=32768,
        difference_counts={k:len(v) for k,v in differences.items()},first_differences={k:v[:16] for k,v in differences.items()},
        dll_sha256=sha(dll),baseline_dll_sha256=reference_sha,actual_independent_dll_public_entrypoints=True,
        all16_fp_modes_open_and_closed_contexts=True,callbacks_nested_calls_foreign_sources_and_input_coercions=True,
        both_weapon_hierarchies_cached_binding_overrides_null_and_copied_rows=True,
        argument_snapshot_before_mutating_receiver_getter=True,all_retained_state_rng_counters_flags_and_mxcsr=True,
        dependencies_sha256={p.name:sha(p) for p in dependencies},raw_sha256=raws,no_speed_claim=True)
    out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result),flush=True)
    assert result['passed'],result['first_differences']
    return result

if __name__=='__main__':verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'weapon_chain_tests.json')
