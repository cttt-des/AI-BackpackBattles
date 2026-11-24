"""Compare actual independent DLLs at overrides, aliases, callbacks, RNG and fenv."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_object_routes import STAGE,WORK,ACCEPTED,EXPECTED,sha

def symbols_header():
    proof=json.loads((WORK/'object_routes_source_proof.json').read_bytes())
    symbols=[*proof['selected'],proof['static_symbol']];assert len(symbols)==97
    required=['SYM_GEN__nativeF32_1502','SYM_GEN_setCooldownActive_97','SYM_GEN_setDamage_1551',
        'SYM_GEN_canDamage_89','SYM_GEN_getRelativeHealth_302','SYM_GEN_getBuffDamageMod_1258',
        'SYM_GEN_pickRandomElement_1746','SYM_GEN_getItemInCell_1607','SYM_GEN_isEmpty_923']
    assert all(s in symbols for s in required)
    return '#pragma once\n#include <array>\nstatic constexpr std::array<gd::SymId,97> object_route_test_symbols={'+','.join(symbols)+'};\n'

def verify(source,dll,out):
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not out.exists();fixture=STAGE/'test_native_object_routes.cpp'
    text=symbols_header();header=out.parent/'object_route_test_symbols.hpp'
    if header.exists():assert header.read_text('utf8')==text
    else:header.write_text(text,encoding='utf8',newline='\n')
    records={}
    for label,headers,library in [('baseline',ACCEPTED/'bundle_src',ACCEPTED/'bundle.dll'),('candidate',source,dll)]:
        assert sha(ACCEPTED/'bundle.dll')==EXPECTED
        with tempfile.TemporaryDirectory(prefix='native-object-route-check-') as directory:
            root=Path(directory);shutil.copyfile(library,root/'libgdcore.dll');exe=root/'check.exe'
            log=out.parent/(label+'_object_routes_revision2.log');assert not log.exists()
            with log.open('w',encoding='utf8') as stream:
                command=['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off',
                    *(['-DOBJECT_ROUTES_CANDIDATE'] if label=='candidate' else []),'-I',str(headers),
                    '-I',str(out.parent),str(fixture),str(root/'libgdcore.dll'),'-o',str(exe)]
                subprocess.run(command,stdout=stream,stderr=subprocess.STDOUT,check=True)
                run=subprocess.run([str(exe)],capture_output=True,text=True)
                stream.write(run.stdout+run.stderr);stream.flush();run.check_returncode()
            raw=out.parent/(label+'_object_routes_cases.json');assert not raw.exists()
            raw.write_text(run.stdout,encoding='utf8');records[label]=json.loads(run.stdout)
    old,new=records['baseline'],records['candidate']
    assert old['passed'] and new['passed'] and old['cases']==new['cases']==320256
    assert old['unknown_cases']==new['unknown_cases']==74496
    assert old['fast_assertions']==0 and new['fast_assertions']==10240
    differences=[i for i,(a,b) in enumerate(zip(old['hashes'],new['hashes'])) if a!=b]
    result=dict(passed=not differences,fixture_revision=2,cases=320256,unknown_cpp_override_cases=74496,real_handler_cases=245760,
        active_route_assertions=10240,difference_count=len(differences),first_differences=differences[:60],
        fixture_sha256=sha(fixture),symbols_header_sha256=sha(header),baseline_dll_sha256=EXPECTED,dll_sha256=sha(dll),
        cross_contexts_original_argument_pointer_and_nested_calls=True,all_four_rounding_modes_and_daz_ftz=True,
        raw_cases_sha256={p.name:sha(p) for p in out.parent.glob('*_object_routes_cases.json')},
        independent_actual_baseline_dll=True,no_throughput_claim=True)
    out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result,indent=2),flush=True)
    assert result['passed'],differences[:60]
    return result

if __name__=='__main__':verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'correctness.json')
