"""Lower the two exact, locally created records throughout native takeDamage."""
import hashlib
import json
from pathlib import Path
import re
STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/damage_records_probe'
EXPECTED='3a9269887ace0ad9cd6dafdb9e0ee2a77b857b231f2a0d412888af2516e5b520'
ARCHIVE='fcfe317116882ad80e2dd59611c38c01690ba004'

def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def body(source,signature):
    start=source.index(signature)
    return source[start:source.index('\n}',start)+2]

def closing_parenthesis(source,opening):
    depth=0;quote=None;escaped=False
    for i in range(opening,len(source)):
        ch=source[i]
        if quote:
            if escaped:escaped=False
            elif ch=='\\':escaped=True
            elif ch==quote:quote=None
            continue
        if ch in ('"',"'"):quote=ch
        elif ch=='(':depth+=1
        elif ch==')':
            depth-=1
            if depth==0:return i
    raise AssertionError('Unbalanced source call')

def prepare(native):
    source=(native/'gen/shards/shard_02.cpp').read_text('utf8')
    result_source=(native/'gen/shards/shard_09.cpp').read_text('utf8')
    damage_source=(native/'gen/shards/shard_10.cpp').read_text('utf8')
    original=body(source,'gd::GdVal Gd__gd_core__CoreCharacter::fn_takeDamage(')
    marker='\n    }\n    gd::GdVal lv_damageSource = (_argc > 0) ? _args[0] : gd::GdVal::null();'
    assert original.count(marker)==1
    boundary=original.index(marker)
    kernel=original[:boundary]
    constructors={}
    setters={}
    for cls,text in [('Gd__gd_core__CoreDamageResult',result_source),('Gd__gd_core__CoreDamageSource',damage_source)]:
        getter=body(text,f'bool {cls}::get_prop(')
        setter=body(text,f'bool {cls}::set_prop(')
        getters=dict(re.findall(r'case (\w+): out = this->(f_\w+); return true;',getter))
        rows=re.findall(r'case (\w+): this->(f_\w+) = (.*?); return true;',setter)
        for symbol,field,coercion in rows:
            assert getters[symbol]==field
            assert coercion in ('val','gd::gd_coerce_int(val)','gd::gd_coerce_float(val)','gd::gd_coerce_bool(val)')
            setters[(cls,symbol)]=(field,coercion)
        init=body(text,f'void {cls}::init_fields(')
        constructors[cls]=dict(init_fields_sha256=hashlib.sha256(init.encode()).hexdigest(),get_prop_sha256=hashlib.sha256(getter.encode()).hexdigest(),set_prop_sha256=hashlib.sha256(setter.encode()).hexdigest())
    copy=body(damage_source,'gd::GdVal Gd__gd_core__CoreDamageSource::fn_fromDamageSource(')
    assert copy.count('return gd::GdVal::from_obj(this);')==1
    assert not re.search(r'\breturn\b',copy[:copy.index('return gd::GdVal::from_obj(this);')])
    assert copy.count('gd::GdVal::from_obj(this)')==1
    assert 'if(value.kind==gd::GdVal::Kind::Obj && value.obj && native_event_type_ok<T>(ctx,value))' in (native/'native_event_kernel.hpp').read_text('utf8')
    locals={
        'lv_damageRes':('Gd__gd_core__CoreDamageResult','native_damage_result'),
        'lv_damageSource':('Gd__gd_core__CoreDamageSource','native_damage_source'),
    }
    result_init='    gd::GdVal lv_damageRes = native_event_new<Gd__gd_core__CoreDamageResult>(gd_ctx, nullptr, 0);'
    assert kernel.count(result_init)==1
    assert len(re.findall(r'\blv_damageRes\s*=',kernel))==1
    assert len(re.findall(r'\blv_damageSource\s*=',kernel))==2
    source_init=next(line for line in kernel.splitlines() if line.startswith('    lv_damageSource = '))
    assert 'native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_fromDamageSource>' in source_init
    assert 'native_event_new<Gd__gd_core__CoreDamageSource>(gd_ctx, nullptr, 0)' in source_init
    candidate=kernel
    counts=dict(gets=0,sets=0,calls=0)
    get_pattern=re.compile(r'native_event_get<(\w+), &(\w+)::(f_\w+)>\(gd_ctx, (lv_damageRes|lv_damageSource), (\w+)\)')
    def replace_get(match):
        cls,owner,field,local,symbol=match.groups();expected,pointer=locals[local]
        assert cls==owner==expected and setters[(cls,symbol)][0]==field
        counts['gets']+=1
        return f'({pointer}->{field})'
    candidate=get_pattern.sub(replace_get,candidate)
    set_pattern=re.compile(r'native_event_set<(\w+)>\(gd_ctx, (lv_damageRes|lv_damageSource), (\w+), ')
    while match:=set_pattern.search(candidate):
        cls,local,symbol=match.groups();expected,pointer=locals[local];assert cls==expected
        end=closing_parenthesis(candidate,candidate.index('(',match.start()))
        value=candidate[match.end():end]
        field,coercion=setters[(cls,symbol)]
        expression=value if coercion=='val' else coercion.replace('(val)',f'({value})')
        candidate=candidate[:match.start()]+f'({pointer}->{field} = {expression})'+candidate[end+1:]
        counts['sets']+=1
    call_pattern=re.compile(r'native_event_call<(\w+), &(\w+)::(fn_\w+)>\(gd_ctx, (lv_damageRes|lv_damageSource), (\w+), ')
    while match:=call_pattern.search(candidate):
        cls,owner,method,local,symbol=match.groups();expected,pointer=locals[local];assert cls==owner==expected
        target=result_source if local=='lv_damageRes' else damage_source
        assert f'case {symbol}: out = {method}(args, argc); return true;' in target
        end=closing_parenthesis(candidate,candidate.index('(',match.start()))
        arguments=candidate[match.end():end]
        candidate=candidate[:match.start()]+f'{pointer}->{method}({arguments})'+candidate[end+1:]
        counts['calls']+=1
    # Pointers refer to exact arena objects, not field snapshots. Callbacks keep
    # seeing and mutating the same records; every later field access stays live.
    candidate=candidate.replace(result_init,result_init+'\n    auto* const native_damage_result=static_cast<Gd__gd_core__CoreDamageResult*>(lv_damageRes.obj);',1)
    assert candidate.count(source_init)==1
    candidate=candidate.replace(source_init,source_init+'\n    auto* const native_damage_source=static_cast<Gd__gd_core__CoreDamageSource*>(lv_damageSource.obj);',1)
    assert sum(counts.values())>50 and counts['sets']==16
    candidate+=original[boundary:]
    assert candidate[candidate.index(marker):]==original[boundary:],'Generic fallback must remain byte-identical'
    # Preserve the original evaluation, arithmetic, RNG, methods and callbacks.
    for method in ('gd::gd_add(','gd::gd_sub(','gd::gd_mul(','gd::gd_div(','gd::gd_coerce_int(','gd::gd_coerce_float('):
        # Setter coercions now occur at the same assignment sites instead of in
        # the original generated set_prop. Extra occurrences are expected there.
        if 'coerce' not in method:assert original.count(method)==candidate.count(method),method
    return dict(original=original,candidate=candidate,counts=counts,constructors=constructors,from_source_sha256=hashlib.sha256(copy.encode()).hexdigest(),literals=re.search(r'constexpr gd::GdStr battle_string_literals\[\] = \{.*?^\};',source,re.M|re.S)[0])

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    WORK.mkdir(exist_ok=True)
    design=prepare(BASE)
    # Header-local instantiations live in the test EXE, while the independent
    # oracle's RTTI lives in the DLL. Compare with that DLL's exported _ZTI data
    # so the probe performs the same address comparison as code inside the DLL.
    # This adaptation never becomes part of the production candidate.
    kernel=(BASE/'native_event_kernel.hpp').read_text('utf8')
    old='if(&typeid(*value.obj)==&typeid(T))return true;'
    assert kernel.count(old)==1
    canonical='''
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <cassert>
#include <string>
template<class T> const std::type_info* probe_dll_type_info() {
    static const auto* canonical=[] {
        const auto module=GetModuleHandleA("libgdcore.dll");assert(module);
        const std::string name=std::string("_ZTI")+typeid(T).name();
        const auto* info=reinterpret_cast<const std::type_info*>(GetProcAddress(module,name.c_str()));
        assert(info);return info;
    }();
    return canonical;
}
'''
    kernel=kernel.replace('template<class T> bool native_event_type_ok',canonical+'\ntemplate<class T> bool native_event_type_ok',1)
    kernel=kernel.replace(old,'if(&typeid(*value.obj)==probe_dll_type_info<T>())return true;',1)
    (WORK/'native_event_kernel.hpp').write_text(kernel,encoding='utf8',newline='\n')
    header='#pragma once\n#include "native_event_kernel.hpp"\n#include "native_scalar_equal.hpp"\n#include "native_array_index.hpp"\n'
    wrapper=design['candidate'].replace('Gd__gd_core__CoreCharacter::fn_takeDamage(const gd::GdVal* _args, int _argc)','candidate_takeDamage(Gd__gd_core__CoreCharacter& character,const gd::GdVal* _args,int _argc)').replace('this->','character.')
    wrapper=re.sub(r'\bthis\b','(&character)',wrapper)
    header+=design['literals']+'\n'+wrapper+'\n'
    (WORK/'preflight_damage_records.hpp').write_text(header,encoding='utf8',newline='\n')
    reference=design['original'].replace('Gd__gd_core__CoreCharacter::fn_takeDamage(const gd::GdVal* _args, int _argc)','reference_takeDamage(Gd__gd_core__CoreCharacter& character,const gd::GdVal* _args,int _argc)').replace('this->','character.')
    reference=re.sub(r'\bthis\b','(&character)',reference)
    (WORK/'reference_damage_records.hpp').write_text('#pragma once\n#include "preflight_damage_records.hpp"\n'+reference+'\n',encoding='utf8',newline='\n')
    visitors='#pragma once\n'
    for cls in ('Gd__gd_core__CoreCharacter','Gd__gd_core__CoreContext','Gd__gd_core__CoreBuff','Gd__gd_core__CoreRng__INNER__BalancedRng','Gd__gd_core__CoreDamageSource','Gd__gd_core__CoreDamageResult','Gd__gd_core__CoreEvent','Gd__gd_core__CoreCombatLog','Gd__gd_core__CoreEventBus','Gd__gd_core__CoreItem'):
        fields=re.findall(r'^    gd::GdVal (f_\w+);',(BASE/'gen/hdrs'/f'{cls}.hpp').read_text('utf8'),re.M)
        assert fields
        visitors+=f'template<class F> void visit_damage_fields({cls}& object,F consume){{\n'+''.join(f'    consume(object.{field});\n' for field in fields)+'}\n'
    (WORK/'damage_state_fields.hpp').write_text(visitors,encoding='utf8',newline='\n')
    fixture=(STAGE/'test_native_damage_records.cpp').read_text('utf8')
    assert fixture.count('int main(){')==1
    (WORK/'damage_fixture.hpp').write_text(fixture[:fixture.index('int main(){')],encoding='utf8',newline='\n')
    report=dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,static_sites=design['counts'],exact_record_constructors=design['constructors'],from_source_sha256=design['from_source_sha256'],
                original_sha256=hashlib.sha256(design['original'].encode()).hexdigest(),candidate_sha256=hashlib.sha256(design['candidate'].encode()).hexdigest(),
                original_method_implementations_arithmetic_and_callback_order_retained=True,all_record_fields_read_live_after_callbacks=True,layouts_unchanged=True,
                no_performance_or_equivalence_claim_before_differentials=True,
                test_only_rtti_boundary='Header-local audit compares against actual independent DLL exported type_info; production kernel unchanged')
    (WORK/'source_analysis.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()
