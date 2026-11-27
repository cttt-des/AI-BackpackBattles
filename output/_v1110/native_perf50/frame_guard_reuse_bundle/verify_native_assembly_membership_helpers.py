import sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[2]))
"""Compare exact private helper bytes with actual DLL membership and FP state."""
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import psutil
from prepare_frame_guard_retained import STAGE,WORK,ACCEPTED,EXPECTED,HEADER_NAME,sha,verify_projection

def verify(source,dll,out,baseline_dll=None):
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not out.exists();verify_projection(source)
    checks=out.parent/(out.stem+'_checks');assert not checks.exists();checks.mkdir()
    helper=checks/HEADER_NAME;helper.write_bytes((source/HEADER_NAME).read_bytes())
    retained=(STAGE/'test_native_identity_lookup.cpp').read_text('utf8')
    a=retained.index('    gd::BattleCtx ctx;Foreign first');b=retained.index('    std::vector<gd::GdArr*> arrays=',a)
    values=checks/'assembly_membership_values.hpp';values.write_text(retained[a:b],encoding='utf8',newline='\n')
    fixture=STAGE/'test_native_assembly_membership.cpp';shutil.copyfile(fixture,checks/fixture.name)
    reference=ACCEPTED/'bundle.dll' if baseline_dll is None else baseline_dll
    assert sha(reference)==(EXPECTED if baseline_dll is None else '293b87e24986dd9dcf2dbecff5510fb7a0b0e993324478bd09ba22bb88aadfba')
    root=Path(tempfile.mkdtemp(prefix='assembly-membership-cases-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    scratch=root/'scratch';scratch.mkdir();env=dict(os.environ,TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch));reports={};raws={}
    for label,headers,library in [('baseline',ACCEPTED/'bundle_src',reference),('candidate',source,dll)]:
        local=root/label;local.mkdir();shutil.copyfile(library,local/'libgdcore.dll')
        exports=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-p',str(local/'libgdcore.dll')]).decode('utf8',errors='replace').split('The Export Tables',1)[1]
        name=re.search(r'(?m)^Name\s+[0-9a-fA-F]+\s+(\S+)',exports).group(1)
        assert '/' not in name and '\\' not in name and name.endswith('.dll')
        if name!='libgdcore.dll':shutil.copyfile(library,local/name)
        for p in (fixture,helper,values):shutil.copyfile(p,local/p.name)
        exe=local/'check.exe'
        with (checks/(label+'_compile.log')).open('wb') as log:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-std=c++20','-march=native','-ffp-contract=off','-I',str(local),'-I',str(headers),str(local/fixture.name),str(local/'libgdcore.dll'),'-o',str(exe)],stdout=log,stderr=subprocess.STDOUT,env=env,check=True)
        result=subprocess.run([str(exe)],capture_output=True,env=env)
        p=checks/(label+'_cases.json');p.write_bytes(result.stdout);(checks/(label+'_execution.log')).write_bytes(result.stderr);result.check_returncode()
        reports[label]=json.loads(result.stdout);raws[p.name]=sha(p)
    a,b=reports['baseline'],reports['candidate']
    for r in (a,b):assert r['passed'] and r['cases']==229376 and r['value_shapes']==112 and r['container_states']==128 and r['fp_modes']==16 and r['fast_empty_object_cases']>0
    assert a['fast_empty_object_cases']==b['fast_empty_object_cases']
    differences=[i for i,(u,v) in enumerate(zip(a['hashes'],b['hashes'])) if u!=v]
    assert len(a['hashes'])==len(b['hashes'])==229376
    report=dict(passed=not differences,cases=229376,value_shapes=112,container_states=128,fp_modes=16,
        dll_sha256=sha(dll),baseline_dll_sha256=sha(reference),within_each_actual_dll_original_membership_and_new_helper_exact=True,
        cross_dll_differences=len(differences),first_differences=differences[:16],fast_empty_object_cases=a['fast_empty_object_cases'],
        fast_hash_equal=a['fast_hash']==b['fast_hash'],actual_original_gd_in_reference=True,
        fenv_mxcsr_legacy_counters_input_bytes_container_state_metadata_and_rng_compared=True,
        indexed_stale_len_zero_tables_and_nonobject_empty_hash_effects_preserved=True,
        fixture_sha256=sha(fixture),helper_sha256=sha(helper),value_matrix_sha256=sha(values),raw_sha256=raws,
        exact_private_helper_bytes_instantiated_in_fixture=True,integration_scope='Actual CoreItem.onItemAdded additionally verified by spatial/current corpus tests',no_speed_claim=True)
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report),flush=True)
    assert report['passed'],report['first_differences'];return report

if __name__=='__main__':verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'assembly_membership_tests.json')
