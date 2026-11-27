import sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[2]))
"""Compare the actual exported frame helper in independent old/new DLLs."""
import argparse,json,os,re,shutil,subprocess,tempfile
from pathlib import Path
from prepare_next_two_round import STAGE,WORK,ACCEPTED,EXPECTED,sha,save,verify_projection
SYMBOL='_ZN2gd25native_frame_segment_tickEP21Gd__gd_core__CoreItemRNS_26NativeFrameSegmentSnapshotERKNS_5GdValE'
def fixture():
    text=(STAGE/'test_native_frame_segments.cpp').read_text('utf8')
    text=text.replace('#include <vector>','#include <vector>\n#include <windows.h>\n#include <xmmintrin.h>')
    anchor='static Result run(';at=text.index(anchor)
    text=text[:at]+'using ActualTick=void (*)(Item*,gd::NativeFrameSegmentSnapshot&,const V&);\nstatic ActualTick actual_tick=nullptr;\nextern "C" uint64_t gd_diag_native_resolved_stat(unsigned);\nextern "C" uint64_t gd_diag_native_type_constructor_stat(unsigned);\n'+text[at:]
    text=text.replace('gd::native_frame_segment_tick(', 'actual_tick(')
    text=text.replace('V::from_bool(mode==2);','V::from_bool(mode==2 || mode>=18);',1)
    at=text.index('    bool done=false;');text=text[:at]+'    gd::NativeMethodRow copied_row{};\n'+text[at:]
    anchor='        switch(mode) {';assert text.count(anchor)==1
    text=text.replace(anchor,anchor+'''
            case 18:items[(id+1)%12]->native_call_row_=nullptr;break;
            case 19:{auto* next=items[(id+1)%12];copied_row=*next->native_call_row_;copied_row.metadata=nullptr;next->native_call_row_=&copied_row;break;}
            case 20:battle.native_resolved_dispatch=false;break;
            case 21:battle.native_resolved_collect=false;break;''',1)
    start=text.index('int main() {')
    text=text[:start]+'''
int main() {
    register_gen_syms();auto module=GetModuleHandleA("libgdcore.dll");assert(module);
    actual_tick=reinterpret_cast<ActualTick>(GetProcAddress(module,"'''+SYMBOL+'''"));assert(actual_tick);
    fenv_t saved;std::fegetenv(&saved);const auto saved_csr=_mm_getcsr();std::vector<uint64_t> hashes;
    const int rounds[]={FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO};
    for(auto rounding:rounds)for(unsigned daz=0;daz<4;++daz)
    for(unsigned seed=0;seed<8;++seed)for(unsigned mode=0;mode<22;++mode)
    for(unsigned position=0;position<12;++position)for(unsigned variant=0;variant<4;++variant){
        assert(std::fesetround(rounding)==0);_mm_setcsr((_mm_getcsr()&~(0x8040u|0x3fu))|((daz&1)?0x40u:0)|((daz&2)?0x8000u:0));
        uint64_t before[27];unsigned index=0;
        for(unsigned i=0;i<6;++i)before[index++]=gd_diag_native_resolved_stat(i);
        for(unsigned i=0;i<4;++i)before[index++]=gd_diag_native_type_constructor_stat(i);
        for(unsigned i=0;i<17;++i)before[index++]=gd_diag_native_frame_segment_stat(i);
        auto result=run(true,seed,mode,position,variant);uint64_t h=1469598103934665603ULL;
        const auto mix=[&](uint64_t x){h=(h^x)*1099511628211ULL;};
        for(auto v:result.values)mix(v);for(auto v:result.trace)mix(v);mix(result.state);mix(result.inc);mix(result.flags);mix(_mm_getcsr());
        index=0;for(unsigned i=0;i<6;++i)mix(gd_diag_native_resolved_stat(i)-before[index++]);
        for(unsigned i=0;i<4;++i)mix(gd_diag_native_type_constructor_stat(i)-before[index++]);
        for(unsigned i=0;i<17;++i)mix(gd_diag_native_frame_segment_stat(i)-before[index++]);
        hashes.push_back(h);
    }
    std::fesetenv(&saved);_mm_setcsr(saved_csr);assert(hashes.size()==135168);
    std::cout<<"{\\"passed\\":true,\\"cases\\":"<<hashes.size()<<",\\"hashes\\":[";
    for(size_t i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<hashes[i];}std::cout<<"]}\\n";
}
'''
    return text
def main():
    p=argparse.ArgumentParser();p.add_argument('--formal',action='store_true');p.add_argument('--tag');p.add_argument('--dll',type=Path);a=p.parse_args()
    import psutil
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    verify_projection(WORK/'bundle_src');tag=a.tag or ('formal' if a.formal else 'prototype')
    candidate=a.dll or WORK/('bundle.dll' if a.formal else 'prototype.dll')
    baseline=ACCEPTED/'bundle.dll' if a.formal else ACCEPTED/'prototype.dll'
    headers=ACCEPTED/'bundle_src';checks=WORK/(tag+'_actual_frame_checks');assert not checks.exists();checks.mkdir()
    text=fixture();(checks/'test_actual_frame.cpp').write_text(text,encoding='utf8',newline='\n')
    root=Path(tempfile.mkdtemp(prefix='frame-guard-actual-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'));results={}
    for label,dll in [('baseline',baseline),('candidate',candidate)]:
        folder=root/label;folder.mkdir();shutil.copyfile(dll,folder/'libgdcore.dll');shutil.copyfile(checks/'test_actual_frame.cpp',folder/'test.cpp')
        with (checks/(label+'_compile.log')).open('wb') as log:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off','-I',str(headers),str(folder/'test.cpp'),str(folder/'libgdcore.dll'),'-o',str(folder/'check.exe')],stdout=log,stderr=subprocess.STDOUT,check=True)
        run=subprocess.run([str(folder/'check.exe')],capture_output=True,timeout=180);(checks/(label+'_actual.json')).write_bytes(run.stdout);(checks/(label+'_stderr.log')).write_bytes(run.stderr);run.check_returncode();results[label]=json.loads(run.stdout)
    old,new=results['baseline'],results['candidate'];assert old['passed'] and new['passed'] and old['cases']==new['cases']==135168
    differences=[i for i,(x,y) in enumerate(zip(old['hashes'],new['hashes'])) if x!=y]
    save(tag+'_actual_frame_tests.json',dict(passed=not differences,cases=135168,dll_sha256=sha(candidate),baseline_dll_sha256=sha(baseline),actual_DLL_functions_via_GetProcAddress=True,no_inline_fixture_substitution=True,original18_scenarios_plus4_callback_guard_mutation_scenarios=True,all16_FP_modes=True,all_original_state_RNG_FPflags_MXCSR_and27_counters=True,difference_count=len(differences),first_differences=differences[:40],fixture_sha256=sha(checks/'test_actual_frame.cpp')))
    assert not differences,differences[:40];print(tag+' actual-DLL frame135168 passed',flush=True)
if __name__=='__main__':main()
