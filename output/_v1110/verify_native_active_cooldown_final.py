"""Check the final DLL's actual index and exact suffixes against the frozen old oracle."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prepare_native_active_cooldowns import WORK as PROBE,STAGE,sha

def verify(source,dll,out):
    assert not out.exists()
    local=PROBE/'test_src';frozen=json.loads((PROBE/'differential.json').read_bytes());assert frozen['passed']
    for name,digest in frozen['dependencies'].items():assert sha(local/name)==digest
    text=(local/'test.cpp').read_text('utf8').replace('int main() {','void retained_cases() {',1)+r'''
extern "C" uint64_t gd_diag_native_active_cooldown_stat(unsigned);
int main(){retained_cases();uint64_t counts[10]{};for(unsigned i=0;i<10;++i)counts[i]=gd_diag_native_active_cooldown_stat(i);
assert(counts[0]>0 && counts[1]>0 && counts[2]>0 && counts[3]>0 && counts[4]>0 && counts[5]>0 && counts[6]>0);
std::cerr<<"{\"counts\":[";for(unsigned i=0;i<10;++i){if(i)std::cerr<<',';std::cerr<<counts[i];}std::cerr<<"]}\n";}
'''
    with tempfile.TemporaryDirectory(prefix='native-active-cooldown-final-') as directory:
        root=Path(directory);(root/'test.cpp').write_text(text,encoding='utf8',newline='\n');shutil.copyfile(dll,root/'libgdcore.dll');exe=root/'coverage.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-DGD_ACTIVE_NEW','-I',str(local),'-I',str(source),str(root/'test.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        run=subprocess.run([str(exe)],capture_output=True,text=True)
        if run.returncode:print(run.stdout+run.stderr,flush=True)
        run.check_returncode();actual=json.loads(run.stdout);counts=json.loads(run.stderr)['counts']
        old=json.loads((PROBE/'baseline_case_hashes.json').read_bytes())
        assert actual['cases']==old['cases']==1856
        assert actual['state_hashes']==old['state_hashes'] and actual['legacy_hashes']==old['legacy_hashes']
        assert actual['layout']==dict(GdVal=24,GdArr=32,CoreItem=1792,BattleCtx=328)
    raw=out.with_name(out.stem+'_cases.json');assert not raw.exists();raw.write_text(run.stdout,encoding='utf8')
    report=dict(passed=True,cases=1856,dll_sha256=sha(dll),counts=counts,
        actual_index_and_suffix_recovery_exercised=True,all_independent_states_fenv_rng_and_old_counters_equal=True,
        layouts=dict(baseline=old['layout'],candidate=actual['layout']),original_fixture_sha256=sha(local/'test.cpp'),
        raw_sha256=sha(raw),baseline_oracle_sha256=sha(PROBE/'baseline_case_hashes.json'))
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2));return report

def main():
    work=STAGE/'native_perf50/active_cooldown_bundle';verify(work/'bundle_src',work/'bundle.dll',work/'active_cooldown_tests.json')

if __name__=='__main__':main()
