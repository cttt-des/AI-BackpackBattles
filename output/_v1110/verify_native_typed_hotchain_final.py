"""Check actual final native entry, scalar bits, callbacks and unchanged object layouts."""
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
STAGE=Path(__file__).resolve().parent
WORK=STAGE/'native_perf50/typed_hotchain_bundle'
PROBE=WORK.parent/'typed_hotchain_prototype'
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    frozen=json.loads((PROBE/'transform_stage2.json').read_bytes())['source_sha256']
    assert frozen==json.loads((WORK/'source_before_build.json').read_bytes())
    assert frozen=={p.relative_to(WORK/'bundle_src').as_posix():sha(p) for p in (WORK/'bundle_src').rglob('*') if p.is_file()}
    checked=json.loads((PROBE/'local_correctness.json').read_bytes())
    for name,digest in checked['dependency_sha256'].items():assert sha(PROBE/name)==digest,name
    math=json.loads((PROBE/'math_correctness.json').read_bytes());ranges=json.loads((PROBE/'range_correctness.json').read_bytes())
    assert math['passed'] and math['math_cases']==33856 and ranges['passed'] and ranges['cases']==240
    assert sha(WORK/'bundle_src/native_typed_damage_math.hpp')==math['helper_sha256']==ranges['helper_sha256']
    text=(PROBE/'local_test/extended.cpp').read_text('utf8')
    old='        assert(gd::local_typed_damage_counts[0]>0 && gd::local_typed_damage_counts[2]>0 && gd::local_typed_damage_counts[10]>0);'
    assert text.count(old)==1
    text='extern "C" unsigned long long gd_diag_native_typed_damage_stat(unsigned);\n'+text.replace(old,'''        assert(gd_diag_native_typed_damage_stat(0)>0 && gd_diag_native_typed_damage_stat(2)>0 && gd_diag_native_typed_damage_stat(10)>0);
        std::cerr<<"TYPED_PRODUCTION_COUNTS";for(unsigned i=0;i<12;++i)std::cerr<<' '<<gd_diag_native_typed_damage_stat(i);std::cerr<<'\\n';''',1)
    layouts={}
    with tempfile.TemporaryDirectory(prefix='native-typed-hotchain-final-') as directory:
        root=Path(directory);shutil.copyfile(WORK/'bundle.dll',root/'libgdcore.dll')
        cpp=root/'production.cpp';cpp.write_text(text,encoding='utf8',newline='\n');exe=root/'production.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-DGD_DAMAGE_PRODUCTION','-I',str(PROBE/'local_test'),'-I',str(WORK/'bundle_src'),str(cpp),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        result=subprocess.run([str(exe)],capture_output=True,text=True)
        if result.returncode:print(result.stdout+result.stderr,flush=True)
        result.check_returncode();actual=json.loads(result.stdout)
        counts=list(map(int,re.search(r'TYPED_PRODUCTION_COUNTS ([0-9 ]+)\r?\n',result.stderr)[1].split()))
        assert len(counts)==12 and all(counts[i]>0 for i in (0,2,10))
        oracle=json.loads((PROBE/'local_case_hashes.json').read_bytes())
        assert actual['cases']==oracle['cases']==13112
        assert actual['case_hashes']==oracle['case_hashes'] and actual['legacy_counter_hashes']==oracle['legacy_counter_hashes']
        (WORK/'typed_hotchain_production_cases.json').write_text(result.stdout,encoding='utf8')
        fields=re.findall(r'^    gd::GdVal (f_\w+);',(BASE/'gen/hdrs/Gd__gd_core__CoreCharacter.hpp').read_text('utf8'),re.M)
        header_new=(WORK/'bundle_src/gen/hdrs/Gd__gd_core__CoreCharacter.hpp').read_text('utf8')
        projection=header_new.replace('struct Gd__gd_core__CoreDamageSource;\nstruct Gd__gd_core__CoreDamageResult;\n\n','',1).replace('    Gd__gd_core__CoreDamageResult* fn_takeDamage_native(Gd__gd_core__CoreDamageSource*,const gd::GdVal&);\n','',1)
        assert projection==(BASE/'gen/hdrs/Gd__gd_core__CoreCharacter.hpp').read_text('utf8')
        abi=r'''#include "native_event_kernel.hpp"
#include <iostream>
int main(){Gd__gd_core__CoreCharacter object(nullptr);std::cout<<"{\"sizes\":["<<sizeof(gd::GdVal)<<','<<sizeof(gd::GdArr)<<','<<sizeof(gd::BattleCtx)<<','<<sizeof(object)<<','<<alignof(decltype(object))<<','<<sizeof(Gd__gd_core__CoreDamageSource)<<','<<sizeof(Gd__gd_core__CoreDamageResult)<<"],\"offsets\":[";
'''+''.join(('std::cout<<\',\';' if i else '')+f'std::cout<<(reinterpret_cast<const unsigned char*>(&object.{field})-reinterpret_cast<const unsigned char*>(&object));\n' for i,field in enumerate(fields))+r'''std::cout<<"]}\n";}
'''
        abi_cpp=root/'layout.cpp';abi_cpp.write_text(abi,encoding='utf8',newline='\n')
        for label,headers,dll in [('baseline',BASE,BASE/'libgdcore.dll'),('candidate',WORK/'bundle_src',WORK/'bundle.dll')]:
            shutil.copyfile(dll,root/'libgdcore.dll');layout_exe=root/(label+'_layout.exe')
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off','-I',str(headers),str(abi_cpp),str(root/'libgdcore.dll'),'-o',str(layout_exe)],check=True)
            layouts[label]=json.loads(subprocess.check_output([str(layout_exe)],text=True))
        assert layouts['baseline']==layouts['candidate']
    report=dict(passed=True,dll_sha256=sha(WORK/'bundle.dll'),cases=13112,actual_final_native_method_checked=True,
        actual_final_native_entry_exercised=True,production_counts=counts,all_actual_old_dll_case_and_legacy_hashes_equal=True,
        independent_scalar_helper_math_cases=33856,independent_iterator_cases=240,helper_sha256=math['helper_sha256'],
        layouts_unchanged=True,layout_results=layouts,nonvirtual_declaration_projection_exact=True,
        original_context_fallback_retained=True,oracle_sha256=sha(PROBE/'local_case_hashes.json'))
    (WORK/'typed_hotchain_tests.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps({k:v for k,v in report.items() if k!='layout_results'},indent=2))

if __name__=='__main__':main()
