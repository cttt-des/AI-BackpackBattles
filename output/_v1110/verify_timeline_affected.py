"""Actual candidate DLL vs literal CEA methods and retained mutation cases."""
import argparse,json,os,shutil,subprocess,tempfile
from pathlib import Path
import psutil
from native_build_storage import isolated_build
from prepare_timeline_round import STAGE,WORK,ACCEPTED,sha,save,verify_projection,TAIL_OLD,TAIL_NEW

@isolated_build
def main():
    parser=argparse.ArgumentParser();parser.add_argument('--formal',action='store_true');args=parser.parse_args();tag='formal' if args.formal else 'prototype'
    assert not (WORK/(tag+'_affected_tests.json')).exists();verify_projection(WORK/'bundle_src');dll=WORK/('bundle.dll' if args.formal else 'prototype.dll');root=Path(tempfile.mkdtemp(prefix='timeline-affected-'));shutil.copyfile(dll,root/'libgdcore.dll')
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    text=(ACCEPTED/'bundle_src/gen/shards/shard_07.cpp').read_text('utf8')
    for method,new,header in [('fn_tickMotion','local_tick_motion','local_motion.hpp'),('fn__step_native_delays','local_delay','local_delay.hpp')]:
        start=text.index('gd::GdVal Gd__gd_core__CoreContext::'+method+'(');body=text[start:text.index('\n}',start)+2].replace('gd::GdVal Gd__gd_core__CoreContext::'+method+'(', 'gd::GdVal '+new+'(Context* self,').replace('this->','self->')
        if method=='fn_tickMotion':body='namespace gd {static thread_local uint64_t native_motion_index_counts[3]{};}\n'+body
        (root/header).write_text(body+'\n',encoding='utf8')
    reports={}
    for kind in ('timeline_step','delay','legacy_motion'):
        if kind=='legacy_motion':
            source=(STAGE/'test_native_motion_indices.cpp').read_text('utf8').replace('NORMAL_PRIORITY_CLASS','BELOW_NORMAL_PRIORITY_CLASS').replace('GetCurrentProcess(),255','GetCurrentProcess(),4')
        else:
            source=(STAGE/f'test_{kind}_resume_probe.cpp').read_text('utf8')
            stop=source.index('    _mm_setcsr(saved);std::cout')
            source=source[:stop]+'''    _mm_setcsr(saved);std::cout<<"{\\"passed\\":true,\\"semantic_cases\\":"<<cases<<",\\"coverage\\":[";for(unsigned i=0;i<4;++i){if(i)std::cout<<',';std::cout<<gd_diag_native_timeline_stat(i);}std::cout<<"]}\\n";}
'''
            source=source.replace('int main(){register_gen_syms();','extern "C" void gd_diag_native_timeline_collect(int);extern "C" uint64_t gd_diag_native_timeline_stat(unsigned);\nint main(){register_gen_syms();gd_diag_native_timeline_collect(1);')
            if kind=='timeline_step':
                source=source.replace('change<4','change<(mode==0 || mode==3?52u:4u)')
                marker='for(unsigned frame=0;frame<32;++frame){'
                assert source.count(marker)==1
                source=source.replace(marker,marker+'''
            if(change>=4 && frame==3){const uint64_t payloads[]={0,0x8000000000000000ULL,1,0x8000000000000001ULL,0x3ff0000000000000ULL,0x412e848000000000ULL,0x7fefffffffffffffULL,0xffefffffffffffffULL,0x7ff0000000000000ULL,0xfff0000000000000ULL,0x7ff8000000000123ULL,0x7ff0000000000123ULL,0xfff8000000000456ULL,0xfff0000000000456ULL,0x3fd5555555555555ULL,0xbfd5555555555555ULL};for(Scene* s:{&a,&b,&r}){auto* c=s->chars[0];auto v=V::from_float(std::bit_cast<double>(payloads[(change-4)%16]));if((change-4)/16==0)c->f__visual_elapsed=v;else if((change-4)/16==1)c->f__visual_to_x=v;else c->f__visual_to_y=v;}}
''')
            if kind=='delay':
                assert source.count(TAIL_OLD)==1;source=source.replace(TAIL_OLD,TAIL_NEW,1)
                source=source.replace('mutation<6','mutation<22')
                marker='for(unsigned frame=0;frame<32;++frame){'
                assert source.count(marker)==1
                source=source.replace(marker,marker+'''
            if(mutation>=6 && frame==3){const uint64_t payloads[]={0,0x8000000000000000ULL,1,0x8000000000000001ULL,0x3ff0000000000000ULL,0x412e848000000000ULL,0x7fefffffffffffffULL,0xffefffffffffffffULL,0x7ff0000000000000ULL,0xfff0000000000000ULL,0x7ff8000000000123ULL,0x7ff0000000000123ULL,0xfff8000000000456ULL,0xfff0000000000456ULL,0x3fd5555555555555ULL,0xbfd5555555555555ULL};for(Scene* s:{&a,&b,&r})s->entries[1].arr->data[2]=V::from_float(std::bit_cast<double>(payloads[mutation-6]));}
''')
        path=root/(kind+'.cpp');path.write_text(source,encoding='utf8');exe=root/(kind+'.exe')
        options=['-DGD_MOTION_PRODUCTION','-I',str(STAGE/'native_perf50/motion_indices_probe')] if kind=='legacy_motion' else []
        with (WORK/(tag+'_'+kind+'_compile.log')).open('xb') as log:
            subprocess.run(['D:/mingw64/bin/g++.exe','-O3','-std=c++20','-march=native','-ffp-contract=off','-static',*options,'-I',str(root),'-I',str(WORK/'bundle_src'),str(path),str(root/'libgdcore.dll'),'-o',str(exe)],check=True,stdout=log,stderr=subprocess.STDOUT)
        proc=psutil.Popen([str(exe)],stdout=subprocess.PIPE,stderr=subprocess.PIPE,creationflags=subprocess.CREATE_NO_WINDOW|subprocess.BELOW_NORMAL_PRIORITY_CLASS);proc.cpu_affinity([2]);out,error=proc.communicate(timeout=120)
        raw=WORK/(tag+'_'+kind+'_cases.json');raw.write_bytes(out);(WORK/(tag+'_'+kind+'_stderr.log')).write_bytes(error)
        if proc.returncode:raise RuntimeError(kind+': '+error.decode('utf8','replace')[-2000:])
        report=json.loads(out);assert report['passed'];reports[kind]=dict(raw_sha256=sha(raw),source_sha256=sha(path),cases=report.get('semantic_cases',report.get('cases')),coverage=report.get('coverage'))
        if kind=='legacy_motion':
            old=json.loads((STAGE/'native_perf50/motion_indices_probe/correctness_baseline.json').read_bytes());assert report['case_hashes']==old['case_hashes'] and report['legacy_counter_hashes']==old['legacy_counter_hashes']
        else:assert sum(report['coverage'])>0
        print(tag,kind,reports[kind],flush=True)
    save(tag+'_affected_tests.json',dict(passed=True,dll_sha256=sha(dll),source_manifest_sha256=sha(WORK/'source_before_build.json'),reports=reports,actual_DLL_fast_path_exercised=True,reference_is_literal_CEA_methods_and_retained_independent_cases=True))

if __name__=='__main__':main()
