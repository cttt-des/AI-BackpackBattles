"""Compare the complete local typed kernel with actual686f DLL, including callback cases."""
import hashlib
import json
import re
from pathlib import Path
import shutil
import subprocess
import tempfile
from prepare_native_typed_hotchain import BASE,WORK,STAGE,EXPECTED,sha
from prepare_native_damage_records import body

def once(text,old,new):
    assert text.count(old)==1,(old[:100],text.count(old));return text.replace(old,new,1)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    out=WORK/'local_correctness.json';assert not out.exists()
    source=WORK/'prototype_src';manifest=json.loads((WORK/'transform_stage2.json').read_bytes())
    assert manifest['source_sha256']=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    local=WORK/'local_test';assert not local.exists();local.mkdir()
    old=STAGE/'native_perf50/damage_records_probe'
    # Only adapt the test EXE's RTTI audit to the actual DLL's type_info.
    frozen=(old/'native_event_kernel.hpp').read_text('utf8')
    a=frozen.index('\n#ifndef NOMINMAX');z=frozen.index('template<class T> bool native_event_type_ok',a)
    canonical=frozen[a:z]
    kernel=(BASE/'native_event_kernel.hpp').read_text('utf8')
    kernel=once(kernel,'template<class T> bool native_event_type_ok',canonical+'template<class T> bool native_event_type_ok')
    kernel=once(kernel,'if(&typeid(*value.obj)==&typeid(T))return true;','if(&typeid(*value.obj)==probe_dll_type_info<T>())return true;')
    (local/'native_event_kernel.hpp').write_text(kernel,encoding='utf8',newline='\n')
    shutil.copyfile(STAGE/'native_typed_damage_math.hpp',local/'native_typed_damage_math.hpp')
    shard=(source/'gen/shards/shard_02.cpp').read_text('utf8')
    native=body(shard,'Gd__gd_core__CoreDamageResult* Gd__gd_core__CoreCharacter::fn_takeDamage_native(')
    native=once(native,'Gd__gd_core__CoreCharacter::fn_takeDamage_native(Gd__gd_core__CoreDamageSource* input_source,const gd::GdVal& trigger_event)',
                'candidate_takeDamage_native(Gd__gd_core__CoreCharacter& character,Gd__gd_core__CoreDamageSource* input_source,const gd::GdVal& trigger_event)')
    wrapper=body(shard,'gd::GdVal Gd__gd_core__CoreCharacter::fn_takeDamage(')
    wrapper=once(wrapper,'Gd__gd_core__CoreCharacter::fn_takeDamage(const gd::GdVal* _args, int _argc)',
                 'candidate_takeDamage(Gd__gd_core__CoreCharacter& character,const gd::GdVal* _args,int _argc)')
    wrapper=once(wrapper,'fn_takeDamage_native(static_cast<','candidate_takeDamage_native(character,static_cast<')
    def localize(text):return re.sub(r'\bthis\b','(&character)',text.replace('this->','character.'))
    literals=re.search(r'constexpr gd::GdStr battle_string_literals\[\] = \{.*?^\};',shard,re.M|re.S)[0]
    header='''#pragma once
#include "native_typed_damage_math.hpp"
#include "native_scalar_equal.hpp"
#include "native_array_index.hpp"
namespace gd {inline uint64_t local_typed_damage_counts[12]{};void native_typed_damage_hit(unsigned i){if(i<12)++local_typed_damage_counts[i];}}
'''+literals+'\n'+localize(native)+'\n'+localize(wrapper)+'\n'
    (local/'preflight_damage_records.hpp').write_text(header,encoding='utf8',newline='\n')
    fixture=(old/'damage_fixture.hpp').read_text('utf8')
    fixture=once(fixture,'        c.native_event_kernel=true;','        c.native_timer_watch.closed_world=true;c.native_event_kernel=true;')
    (local/'damage_fixture.hpp').write_text(fixture,encoding='utf8',newline='\n')
    shutil.copyfile(old/'damage_state_fields.hpp',local/'damage_state_fields.hpp')
    text=(STAGE/'test_native_damage_records_extended.cpp').read_text('utf8')
    marker='    ExtendedFixture f(scenario,family==1 || family==2);f.candidate=candidate;'
    text=once(text,marker,marker+'''
    if(family==6){f.source->f_origin=V::from_obj(f.weapon);f.source->f_types=V::from_arr(gd::GdArr::from_init(f.c.arena,{V::from_int(0)}));f.source->f_flags=V::from_int(63);f.source->f_accuracy=V::from_float(100);f.defender->f_isDead=f.defender->f_invulnerable=V::from_bool(false);f.weapon->f_hasPreDealDamageEarlyEffect=f.weapon->f_hasPreDealDamageLateEffect=f.weapon->f_hasDealtDamageEffect=V::from_bool(true);}
''')
    marker='        std::cout<<"{\\\"passed\\\":true,\\\"cases\\\":"<<hashes.size()'
    assert text.count(marker)==1
    text=text.replace(marker,'''        for(unsigned scenario=0;scenario<16;++scenario)for(unsigned config=0;config<3;++config)for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO})check(6,scenario,config,rounding);
        assert(gd::local_typed_damage_counts[0]>0 && gd::local_typed_damage_counts[2]>0 && gd::local_typed_damage_counts[10]>0);
'''+marker,1)
    (local/'extended.cpp').write_text(text,encoding='utf8',newline='\n')
    attempt=len(list(WORK.glob('local_attempt_*.log')))+1;log=WORK/f'local_attempt_{attempt}.log'
    with tempfile.TemporaryDirectory(prefix='native-typed-kernel-local-') as directory:
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'extended.exe'
        with log.open('w',encoding='utf8') as output:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-I',str(local),'-I',str(BASE),str(local/'extended.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],stdout=output,stderr=subprocess.STDOUT,check=True)
            result=subprocess.run([str(exe)],capture_output=True,text=True);output.write(result.stdout+result.stderr)
        if result.returncode:print(result.stdout+result.stderr,flush=True)
        result.check_returncode();actual=json.loads(result.stdout)
    previous=json.loads((old/'extended_correctness.json').read_bytes())
    assert actual['case_hashes'][:previous['cases']]==previous['case_hashes']
    assert actual['legacy_counter_hashes'][:previous['cases']]==previous['legacy_counter_hashes']
    assert actual['cases']==13112
    raw=WORK/'local_case_hashes.json';raw.write_text(result.stdout,encoding='utf8')
    report=dict(passed=True,cases=13112,original_prefix_cases=previous['cases'],added_integer_behavior_loop_cases=192,
        baseline_dll_sha256=EXPECTED,actual_current_dll_independent_oracle=True,old_case_hash_prefix_retained=True,
        four_rounding_modes=True,unknown_source_getters_callbacks_and_reentrancy_retained=True,
        complete_native_kernel_source_checked=True,no_throughput_claim=True,case_hashes_sha256=sha(raw),
        test_only_canonical_dll_rtti=True,fixture_closed_mode_forces_kernel_exercise=True,
        dependency_sha256={p.relative_to(WORK).as_posix():sha(p) for p in local.iterdir() if p.is_file()})
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps({k:v for k,v in report.items() if k!='dependency_sha256'},indent=2))

if __name__=='__main__':main()
