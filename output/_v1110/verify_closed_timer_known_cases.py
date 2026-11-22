"""Exercise sealed mode on known-only mutations against frozen actual-old-DLL hashes."""
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile

STAGE=Path(__file__).resolve().parent
ORACLE=STAGE/'native_perf50/targeted_timer_prototype'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def verify(source,dll,out):
    assert not out.exists(),out
    gold=json.loads((ORACLE/'baseline_expanded_cases.json').read_bytes())
    original=STAGE/'test_native_targeted_timers.cpp'
    assert sha(original)==gold['dependency_sha256'][original.name]
    text=original.read_text('utf8')
    old='        c.native_timer_watch.enabled=true;'
    assert text.count(old)==1
    # The fixture still contains custom-callback tests, but this executable
    # selects only cases which never invoke those unknown objects.
    text=text.replace(old,old+'\n        c.native_timer_watch.closed_world=true;',1)
    selected=[];index=0
    for family in range(7):
        count=4 if family==4 else 6 if family==5 else 20
        for scenario in range(count):
            known=(family in (0,4,5) or family==1 and scenario not in (16,17) or family==6 and scenario not in (6,19))
            for config in range(4):
                for rounding in range(4):
                    if known:selected.append((index,family,scenario,config,rounding))
                    index+=1
    assert index==gold['cases']==1760 and len(selected)==1056
    main=r'''
#define main retained_targeted_timer_main
#include "sealed_fixture.cpp"
#undef main
extern "C" uint64_t gd_diag_native_targeted_timer_stat(unsigned);
int main(){register_gen_syms();std::vector<uint64_t> states,legacy;
const int rounding[]={FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO};
const unsigned cases[][4]={CASES};
for(const auto& test:cases){auto [a,b]=run(test[0],test[1],test[2],rounding[test[3]]);states.push_back(a);legacy.push_back(b);}
std::cout<<"{\"cases\":"<<states.size()<<",\"state_hashes\":[";
for(unsigned i=0;i<states.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<states[i]<<std::dec<<'"';}
std::cout<<"],\"legacy_hashes\":[";
for(unsigned i=0;i<legacy.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<legacy[i]<<std::dec<<'"';}
std::cout<<"],\"timer_counts\":[";
for(unsigned i=0;i<10;++i){if(i)std::cout<<',';std::cout<<gd_diag_native_targeted_timer_stat(i);}
std::cout<<"]}\n";}
'''.replace('CASES',','.join('{'+','.join(map(str,row[1:]))+'}' for row in selected))
    with tempfile.TemporaryDirectory(prefix='native-closed-known-') as directory:
        root=Path(directory);(root/'sealed_fixture.cpp').write_text(text,encoding='utf8',newline='\n')
        (root/'known.cpp').write_text(main,encoding='utf8',newline='\n')
        shutil.copyfile(dll,root/'libgdcore.dll');exe=root/'known.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-DGD_TIMER_NEW','-I',str(ORACLE),'-I',str(source),str(root/'known.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        raw=subprocess.check_output([str(exe)],text=True);actual=json.loads(raw)
        assert actual['cases']==len(selected)
        assert actual['state_hashes']==[gold['state_hashes'][row[0]] for row in selected]
        assert actual['legacy_hashes']==[gold['legacy_hashes'][row[0]] for row in selected]
        counts=actual['timer_counts']
        assert counts[0]>0 and counts[1]>0 and counts[2]>0 and counts[6]>0 and counts[9]==0,counts
    raw_path=out.with_name(out.stem+'_cases.json');assert not raw_path.exists()
    raw_path.write_text(raw,encoding='utf8')
    report=dict(passed=True,dll_sha256=sha(dll),cases=1056,baseline_receipt_sha256=sha(ORACLE/'baseline_expanded_cases.json'),
        original_fixture_sha256=sha(original),only_fixture_change='Enable closed_world alongside enabled; run only known-object cases',
        known_generated_same_pass_newItemTimer_callback_retained=True,unknown_callback_cases_excluded_from_sealed_mode=True,
        all_original_state_fenv_rng_and_legacy_hashes_equal=True,timer_counts=counts,raw_sha256=sha(raw_path))
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2))
    return report

def main():
    p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--dll',type=Path,required=True);p.add_argument('--out',type=Path,required=True)
    a=p.parse_args();verify(a.source,a.dll,a.out)

if __name__=='__main__':main()
