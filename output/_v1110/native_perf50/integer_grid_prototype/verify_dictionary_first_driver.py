"""Compare full dictionary operations and FP environments using two independent DLLs."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_integer_grid import STAGE,BASE,WORK,EXPECTED,sha

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    out=WORK/'dictionary_correctness.json';assert not out.exists()
    source=WORK/'prototype_src'
    assert json.loads((WORK/'build.json').read_bytes())['passed']
    assert json.loads((WORK/'slot_correctness.json').read_bytes())['helper_sha256']==sha(source/'native_integer_grid.hpp')
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    local=WORK/'dict_test_src';assert not local.exists();local.mkdir()
    shutil.copyfile(STAGE/'test_native_integer_grid_dict.cpp',local/'test.cpp')
    shutil.copyfile(source/'native_integer_grid.hpp',local/'native_integer_grid.hpp')
    records={}
    for name,headers,dll in [('baseline',BASE,BASE/'libgdcore.dll'),('candidate',source,WORK/'prototype.dll')]:
        with tempfile.TemporaryDirectory(prefix='native-integer-grid-dictionary-') as directory:
            root=Path(directory);shutil.copyfile(dll,root/'libgdcore.dll');exe=root/'dict.exe'
            flags=['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-I',str(local),'-I',str(headers)]
            if name=='candidate':flags.append('-DGD_GRID_NEW')
            with (WORK/(name+'_dict_first.log')).open('w',encoding='utf8') as log:
                subprocess.run([*flags,str(local/'test.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True,stdout=log,stderr=subprocess.STDOUT)
                run=subprocess.run([str(exe)],capture_output=True,text=True);log.write(run.stdout+run.stderr);log.flush()
                if run.returncode:print(run.stdout+run.stderr,flush=True)
                run.check_returncode();actual=json.loads(run.stdout)
            path=WORK/(name+'_dict_hashes.json');assert not path.exists();path.write_text(run.stdout,encoding='utf8');records[name]=actual
    old,new=records['baseline'],records['candidate'];assert old['cases']==new['cases']==1792
    differences=[i for i,(a,b) in enumerate(zip(old['hashes'],new['hashes'])) if a!=b]
    report=dict(passed=not differences,cases=1792,first_differences=[dict(index=i,scenario=i//64,config=i%64//16,rounding=i%16//4,daz_ftz=i%4) for i in differences[:30]],
        difference_count=len(differences),baseline_dll_sha256=EXPECTED,candidate_dll_sha256=sha(WORK/'prototype.dll'),
        actual_independent_deployed_dll_oracle=True,compares_canonical_entries_order_hashes_values_results_fenv_and_mxcsr=True,
        all_original_rounding_and_daz_ftz_modes=True,fast_queries=new['fast_queries'],
        old_layout={k:old[k] for k in ('GdDict','GdVal','GdArr','BattleCtx')},new_layout={k:new[k] for k in ('GdDict','GdVal','GdArr','BattleCtx')},
        dependencies={p.name:sha(p) for p in local.iterdir() if p.is_file()},no_performance_claim=True)
    assert report['old_layout']==report['new_layout']==dict(GdDict=32,GdVal=24,GdArr=32,BattleCtx=328)
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2));assert report['passed'],differences[:30]

if __name__=='__main__':main()
