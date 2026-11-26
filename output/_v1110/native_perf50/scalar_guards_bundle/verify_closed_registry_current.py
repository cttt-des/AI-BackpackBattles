"""Compare closed-mode and foreign-registration boundaries with the actual old ABI."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prepare_native_scalar_guards import BASE,STAGE,EXPECTED,sha

def verify(source,dll,out):
    assert not out.exists() and sha(BASE/'libgdcore.dll')==EXPECTED
    engine=(BASE/'engine_wrapper.cpp').read_text('utf8')
    begin=engine.index('extern "C" {\n\nstruct PackedEffect');end=engine.index('void gd_sim_init()',begin)
    abi=engine[begin:end]+'''void gd_sim_init();
void gd_sim_reset_registry();
void gd_sim_register_character(int32_t,const char*,double,double,double,int32_t);
void gd_sim_run_one(const PackedSide*,const PackedSide*,const BattleOptions*,BattleResult*);
}
'''
    results={}
    with tempfile.TemporaryDirectory(prefix='native-closed-registry-') as directory:
        root=Path(directory);(root/'frozen_timer_packed_abi.hpp').write_text(abi,encoding='utf8',newline='\n')
        for label,headers,binary in [('baseline',BASE,BASE/'libgdcore.dll'),('candidate',source,dll)]:
            shutil.copyfile(binary,root/'libgdcore.dll');exe=root/(label+'.exe')
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-std=c++20','-ffp-contract=off',*(['-DGD_TIMER_CLOSED'] if label=='candidate' else []),'-I',str(root),'-I',str(headers),str(STAGE/'test_closed_timer_registry.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
            raw=subprocess.check_output([str(exe)],text=True);results[label]=json.loads(raw)
        assert results['baseline']==results['candidate'] and results['candidate']['passed']
    report=dict(passed=True,dll_sha256=sha(dll),baseline_dll_sha256=EXPECTED,source_sha256=sha(STAGE/'test_closed_timer_registry.cpp'),
        ordinary_context_open=True,packed_context_closed=True,unknown_registration_opens_future_contexts=True,reset_does_not_reseal=True,
        four_boundary_checks=True,three_packed_fights_match_original=True,results=results)
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2));return report
