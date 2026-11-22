"""Retain every old spatial-query case, then exercise explicit grid-mode dictionaries."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prepare_native_integer_grid import STAGE,WORK,sha
ORACLE=STAGE/'native_perf50/spatial_probe'

def verify(source,dll,out):
    assert not out.exists()
    baseline=json.loads((ORACLE/'correctness_baseline.json').read_bytes())
    screen=json.loads((ORACLE/'screen.json').read_bytes())
    original=STAGE/'test_native_spatial.cpp';assert sha(original)==screen['test_source_sha256']
    text=original.read_text('utf8')
    for name in ('getItemsInCells','countItemsInCells','getBagsInCells'):
        a=f'candidate?candidate_{name}(grid,args,argc):grid.fn_{name}(args,argc)'
        assert text.count(a)==1;text=text.replace(a,f'grid.fn_{name}(args,argc)',1)
    rows={}
    for label in ('ordinary','forced_grid'):
        fixture=text
        if label=='forced_grid':
            marker='    const V result=invoke(candidate,mode,f.grid,&f.cells,scenario==244?0:1);'
            assert fixture.count(marker)==1
            fixture=fixture.replace(marker,'''    if(f.grid.f_filledCells.kind==V::Kind::Dict && f.grid.f_filledCells.dict)
        (void)f.grid.f_filledCells.dict->enable_integer_grid(f.persistent.arena);
'''+marker,1)
        with tempfile.TemporaryDirectory(prefix='native-integer-grid-queries-') as directory:
            root=Path(directory);shutil.copyfile(dll,root/'libgdcore.dll');exe=root/'queries.exe'
            (root/'fixture.cpp').write_text(fixture,encoding='utf8',newline='\n')
            wrapper='''#define main retained_spatial_main
#include "fixture.cpp"
#undef main
extern "C" uint64_t gd_diag_native_integer_grid_stat(unsigned);
int main(){char name[]="queries",arg[]="--correctness-only";char* args[]={name,arg};const int status=retained_spatial_main(2,args);if(status)return status;
'''+('assert(gd_diag_native_integer_grid_stat(0)>0);' if label=='forced_grid' else '')+'''
std::cerr<<"{\\"fast\\":"<<gd_diag_native_integer_grid_stat(0)<<"}\\n";return 0;}
'''
            (root/'main.cpp').write_text(wrapper,encoding='utf8',newline='\n')
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-DGD_SPATIAL_PRODUCTION','-I',str(source),'-I',str(ORACLE),str(root/'main.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
            run=subprocess.run([str(exe)],capture_output=True,text=True)
            if run.returncode:print(run.stdout+run.stderr,flush=True)
            run.check_returncode();actual=json.loads(run.stdout);counts=json.loads(run.stderr)
        assert actual['passed'] and actual['cases']==baseline['cases']==11760
        path=out.with_name(out.stem+'_'+label+'_cases.json');assert not path.exists();path.write_text(run.stdout,encoding='utf8')
        differences=[i for i,(a,b) in enumerate(zip(actual['case_hashes'],baseline['case_hashes'])) if a!=b]
        rows[label]=dict(passed=not differences,cases=actual['cases'],first_differences=differences[:30],count=len(differences),fast_queries=counts['fast'],raw_sha256=sha(path))
    report=dict(passed=all(v['passed'] for v in rows.values()),cases=23520,dll_sha256=sha(dll),variants=rows,
        original_fixture_sha256=sha(original),independent_baseline_receipt_sha256=sha(ORACLE/'correctness_baseline.json'),
        ordinary_cases_untouched=True,forced_variant_only_enables_compatible_current_field_before_invoke=True,
        compares_original_return_alias_mutation_callbacks_rng_fenv_and_old_counters=True,no_performance_claim=True)
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2));assert report['passed']
    return report

def main():verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'query_correctness.json')

if __name__=='__main__':main()
