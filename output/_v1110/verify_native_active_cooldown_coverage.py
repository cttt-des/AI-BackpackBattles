"""Ensure directed mutation cases actually used the indexed path and recovery."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prepare_native_active_cooldowns import BASE,WORK,STAGE,EXPECTED,sha

def main():
    out=WORK/'directed_coverage.json';assert not out.exists()
    first=json.loads((WORK/'differential.json').read_bytes());assert first['passed']
    local=WORK/'test_src'
    for name,digest in first['dependencies'].items():assert sha(local/name)==digest
    text=(local/'test.cpp').read_text('utf8');assert text.count('int main() {')==1
    text=text.replace('int main() {','void retained_cases() {',1)+r'''
extern "C" uint64_t gd_diag_native_active_cooldown_stat(unsigned);
int main(){retained_cases();uint64_t counts[10]{};for(unsigned i=0;i<10;++i)counts[i]=gd_diag_native_active_cooldown_stat(i);
assert(counts[0]>0 && counts[1]>0 && counts[2]>0 && counts[3]>0 && counts[4]>0 && counts[5]>0 && counts[6]>0);
std::cerr<<"{\"counts\":[";for(unsigned i=0;i<10;++i){if(i)std::cerr<<',';std::cerr<<counts[i];}std::cerr<<"]}\n";}
'''
    with tempfile.TemporaryDirectory(prefix='native-cooldown-directed-coverage-') as directory:
        root=Path(directory);(root/'test.cpp').write_text(text,encoding='utf8',newline='\n');shutil.copyfile(WORK/'prototype.dll',root/'libgdcore.dll');exe=root/'coverage.exe'
        with (WORK/'directed_coverage_first.log').open('w',encoding='utf8') as log:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-DGD_ACTIVE_NEW','-I',str(local),'-I',str(WORK/'prototype_src'),str(root/'test.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True,stdout=log,stderr=subprocess.STDOUT)
            result=subprocess.run([str(exe)],capture_output=True,text=True);log.write(result.stdout+result.stderr);log.flush();result.check_returncode()
        actual=json.loads(result.stdout);counts=json.loads(result.stderr)['counts'];old=json.loads((WORK/'baseline_case_hashes.json').read_bytes())
        assert actual['state_hashes']==old['state_hashes'] and actual['legacy_hashes']==old['legacy_hashes']
    report=dict(passed=True,cases=1856,dll_sha256=sha(WORK/'prototype.dll'),counts=counts,
        actual_index_build_hit_and_same_pass_recovery_observed=True,all_independent_old_states_and_legacy_hashes_retained=True,
        original_fixture_body_sha256=sha(local/'test.cpp'),no_performance_claim=True)
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2))

if __name__=='__main__':main()
