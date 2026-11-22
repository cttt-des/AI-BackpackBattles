"""Combine exact record propagation with typed flag and ordered type probes."""
import hashlib
import json
from pathlib import Path
import re
import shutil
from prepare_native_damage_records import prepare as prepare_records,BASE,STAGE,EXPECTED,ARCHIVE,sha
WORK=STAGE/'native_perf50/damage_combo_probe'
OLD=STAGE/'native_perf50/damage_records_probe'

HELPER='''namespace gd {
static thread_local uint64_t native_damage_record_counts[6]{};
inline void native_damage_record_hit(Gd__gd_core__CoreDamageSource* source,unsigned field){
    if(source->rt_ctx_->native_resolved_collect)++native_damage_record_counts[field];
}
template<int64_t Mask,GdVal (Gd__gd_core__CoreDamageSource::*Method)(const GdVal*,int)>
inline GdVal native_damage_record_flag(Gd__gd_core__CoreDamageSource* source){
    const auto& flags=source->f_flags;
    if(flags.kind==GdVal::Kind::Int){native_damage_record_hit(source,1);return GdVal::from_int(flags.i & Mask);}
    native_damage_record_hit(source,2);return (source->*Method)(nullptr,0);
}
inline GdVal native_damage_record_has_type(Gd__gd_core__CoreDamageSource* source,const GdVal* args,int argc){
    const GdVal key=gd_coerce_int(argc>0?args[0]:GdVal::null());
    const auto& types=source->f_types;
    if(types.kind==GdVal::Kind::Arr && types.arr){
        native_damage_record_hit(source,3);
        const auto* array=types.arr;
        for(uint32_t i=0;i<array->len;++i){
            const auto& entry=array->data[i];
            if(entry.kind==GdVal::Kind::Int ? entry.i==key.i : gd_eq(entry,key))return GdVal::from_bool(true);
        }
        return GdVal::from_bool(false);
    }
    native_damage_record_hit(source,4);return gd_in(key,types);
}
inline bool native_damage_record_has_int(Gd__gd_core__CoreDamageSource* source,int64_t key){
    const GdVal value=GdVal::from_int(key);return gd_truth(native_damage_record_has_type(source,&value,1));
}
inline GdVal native_damage_record_is_attack(Gd__gd_core__CoreDamageSource* source){
    if(!source->rt_ctx_->native_event_kernel){native_damage_record_hit(source,5);return source->fn_isAttack(nullptr,0);}
    return GdVal::from_bool(native_damage_record_has_int(source,0) || native_damage_record_has_int(source,1));
}
inline GdVal native_damage_record_is_attack_or_effect(Gd__gd_core__CoreDamageSource* source){
    if(!source->rt_ctx_->native_event_kernel){native_damage_record_hit(source,5);return source->fn_isAttackOrEffect(nullptr,0);}
    return GdVal::from_bool(native_damage_record_has_int(source,0) || native_damage_record_has_int(source,1)
        || native_damage_record_has_int(source,2) || native_damage_record_has_int(source,98));
}
}
'''

def prepare(native):
    data=prepare_records(native)
    source=(native/'gen/shards/shard_10.cpp').read_text('utf8')
    runtime=(native/'gd_rt.cpp').read_text('utf8')
    assert 'GdVal gd_bitand(const GdVal& a, const GdVal& b) { return GdVal::from_int(a.as_int() & b.as_int()); }' in runtime
    has_type=source[source.index('gd::GdVal Gd__gd_core__CoreDamageSource::fn_hasType('):]
    has_type=has_type[:has_type.index('\n}')+2]
    assert 'lv__type = gd::gd_coerce_int(lv__type);\n    return gd::gd_in(lv__type, this->f_types);' in has_type
    changes={};candidate=data['candidate']
    for name,mask in [('canMiss',16),('canCrit',32),('canBeBlocked',1)]:
        start=source.index(f'gd::GdVal Gd__gd_core__CoreDamageSource::fn_{name}(')
        method=source[start:source.index('\n}',start)+2]
        assert f'return gd::gd_bitand(this->f_flags, gd::GdVal::from_int({mask}LL));' in method
        assert method.count('return ')==2 and method.count('gd::gd_')==1
        old=f'native_damage_source->fn_{name}(nullptr, 0)'
        changes[name]=candidate.count(old);assert changes[name]>0
        candidate=candidate.replace(old,f'gd::native_damage_record_flag<{mask}LL,&Gd__gd_core__CoreDamageSource::fn_{name}>(native_damage_source)')
    for name,helper in [('isAttack','is_attack'),('isAttackOrEffect','is_attack_or_effect')]:
        start=source.index(f'gd::GdVal Gd__gd_core__CoreDamageSource::fn_{name}(')
        method=source[start:source.index('\n}',start)+2]
        assert 'if (gd_ctx.native_event_kernel)' in method
        if name=='isAttack':
            assert method.count('this->fn_hasType(_ca, 1)')==2 and 'from_int(0LL)' in method and 'from_int(1LL)' in method
        else:assert 'this->fn_isAttack(nullptr, 0)' in method and 'this->fn_isEffectDamage(nullptr, 0)' in method
        old=f'native_damage_source->fn_{name}(nullptr, 0)';changes[name]=candidate.count(old);assert changes[name]>0
        candidate=candidate.replace(old,f'gd::native_damage_record_{helper}(native_damage_source)')
    effect_start=source.index('gd::GdVal Gd__gd_core__CoreDamageSource::fn_isEffectDamage(')
    effect=source[effect_start:source.index('\n}',effect_start)+2]
    assert effect.count('this->fn_hasType(_ca, 1)')==2 and 'from_int(2LL)' in effect and 'from_int(98LL)' in effect
    old='native_damage_source->fn_hasType(_ca, 1)';changes['hasType']=candidate.count(old);assert changes['hasType']>0
    candidate=candidate.replace(old,'gd::native_damage_record_has_type(native_damage_source, _ca, 1)')
    line='        ++gd_ctx.native_event_counts[1];';assert candidate.count(line)==1
    candidate=candidate.replace(line,line+'\n        if(gd_ctx.native_resolved_collect)++gd::native_damage_record_counts[0];',1)
    data.update(candidate=candidate,helper=HELPER,typed_source_sites=changes,source_helpers_sha256=hashlib.sha256(source.encode()).hexdigest())
    return data

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    WORK.mkdir(exist_ok=True);data=prepare(BASE)
    for name in ('native_event_kernel.hpp','damage_state_fields.hpp','damage_fixture.hpp'):
        shutil.copyfile(OLD/name,WORK/name)
    header='#pragma once\n#include "native_event_kernel.hpp"\n#include "native_scalar_equal.hpp"\n#include "native_array_index.hpp"\n'+data['literals']+'\n'+HELPER
    wrapper=data['candidate'].replace('Gd__gd_core__CoreCharacter::fn_takeDamage(const gd::GdVal* _args, int _argc)','candidate_takeDamage(Gd__gd_core__CoreCharacter& character,const gd::GdVal* _args,int _argc)').replace('this->','character.')
    wrapper=re.sub(r'\bthis\b','(&character)',wrapper)
    (WORK/'preflight_damage_records.hpp').write_text(header+'\n'+wrapper+'\n',encoding='utf8',newline='\n')
    shutil.copyfile(OLD/'reference_damage_records.hpp',WORK/'reference_damage_records.hpp')
    for filename,marker,output in [('test_native_damage_records_extended.cpp','int main(int argc','damage_extended_fixture.hpp'),('test_native_damage_source_helpers.cpp','int main(){','damage_source_fixture.hpp')]:
        text=(STAGE/filename).read_text('utf8');assert text.count(marker)==1
        if output=='damage_source_fixture.hpp':
            assert text.count('#include "damage_fixture.hpp"\n')==1
            text=text.replace('#include "damage_fixture.hpp"\n','',1)
        (WORK/output).write_text(text[:text.index(marker)],encoding='utf8',newline='\n')
    report=dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,record_sites=data['counts'],typed_source_sites=data['typed_source_sites'],
                candidate_sha256=hashlib.sha256(data['candidate'].encode()).hexdigest(),helper_sha256=hashlib.sha256(HELPER.encode()).hexdigest(),
                original_arithmetic_rng_callback_order_and_layouts_retained=True,no_cross_callback_field_snapshot=True,no_whole_fight_gain_claim=True,
                previous_record_only_screen_retained=str(OLD/'screen_matched.json'))
    (WORK/'source_analysis.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()
