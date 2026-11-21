"""Prove pure literal construction before folding only numeric consumers."""
import hashlib
import json
from pathlib import Path
import re
STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/static_collections_probe'
EXPECTED='d3c47cdfe1b3218e7936cc02f706e8452464c1420c5e1fe4bf6963f2e3844c14'
def body(source,signature):
    start=source.index(signature);end=source.index('\n}',start)+2
    return source[start:end]
def transformed(native):
    source=(native/'gen/shards/shard_02.cpp').read_text('utf8')
    line=next(s.strip() for s in source.splitlines() if s.strip().startswith('case SYM_GEN_CLASS_SOUND_COUNTS_1127: return'))
    numbers=list(map(int,re.findall(r'GdVal::from_int\((-?\d+)LL\)',line)))
    assert len(numbers)==28
    rows=[numbers[i:i+4] for i in range(0,28,4)];assert [r[0] for r in rows]==list(range(7))
    expected='case SYM_GEN_CLASS_SOUND_COUNTS_1127: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 7); '
    for key,*counts in rows:
        inner='([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); '
        for slot,value in zip((9,10,11),counts):inner+=f'd->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[{slot}]), gd::GdVal::from_int({value}LL)); '
        inner+='return gd::GdVal::from_dict(d); })()'
        expected+=f'd->set(gd_ctx.arena, gd::GdVal::from_int({key}LL), {inner}); '
    expected+='return gd::GdVal::from_dict(d); })();'
    assert line==expected,'Reject nonliteral or effectful constant builders'
    originals={};candidates={}
    for name,column in (('classAttackSoundCount','0'),('classRoundSoundCount','gd::gd_truth(lv_win)?1:2')):
        signature=f'gd::GdVal Gd__gd_core__CoreCharacter::fn_{name}('
        original=body(source,signature)
        assert original.count('SYM_GEN_CLASS_SOUND_COUNTS_1127')==2
        anchor='    gd::BattleCtx& gd_ctx = *this->rt_ctx_;' if name.startswith('classAttack') else '    lv_win = gd::gd_coerce_bool(lv_win);'
        guard=f'''\n    if(gd_ctx.native_resolved_dispatch) {{
        gd::GdVal folded;
        if(gd::native_static_sound_count(this->f_characterClass,{column},folded))return folded;
    }}'''
        originals[name]=original;candidates[name]=original.replace(anchor,anchor+guard,1)
    constants=(native/'gen/shards/shard_06.cpp').read_text('utf8')
    original=body(constants,'gd::GdVal Gd__gd_core__CoreConst::sf_numStackTypes(')
    for name,start,end in (('getBuffs',101,107),('getDebuffs',108,110)):
        actual=body(constants,f'gd::GdVal Gd__gd_core__CoreConst::sf_{name}(')
        expected=f'''gd::GdVal Gd__gd_core__CoreConst::sf_{name}(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {{
    return ([&]() {{ gd::GdVal _ca[] = {{gd::GdVal::from_int({start}LL), gd::gd_add(gd_ctx, gd::GdVal::from_int({end}LL), gd::GdVal::from_int(1LL))}}; return gd::gd_range(gd_ctx.arena, _ca, 2); }})();
    return gd::GdVal::null();
}}'''
        assert actual==expected
        assert f'case SYM_GEN_{name}_' in constants
    stacks=body(constants,'gd::GdVal Gd__gd_core__CoreConst::sf_getStacks(')
    expected_stacks='''gd::GdVal Gd__gd_core__CoreConst::sf_getStacks(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(100LL)})), ([&]() { gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreConst::call_static_fn(gd_ctx, SYM_GEN_getBuffs_1390, nullptr, 0, _out); return _out; })()), ([&]() { gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreConst::call_static_fn(gd_ctx, SYM_GEN_getDebuffs_1391, nullptr, 0, _out); return _out; })());
    return gd::GdVal::null();
}'''
    assert stacks==expected_stacks
    for name,symbol in (('getStacks','SYM_GEN_getStacks_1023'),('getBuffs','SYM_GEN_getBuffs_1390'),('getDebuffs','SYM_GEN_getDebuffs_1391')):
        compact=re.sub(r'\s+','',constants)
        assert f'case{symbol}:out=sf_{name}(gd_ctx,args,argc);returntrue;' in compact
    originals['numStackTypes']=original
    candidates['numStackTypes']=original.replace('{\n','{\n    if(gd_ctx.native_resolved_dispatch)return gd::GdVal::from_int(11LL);\n',1)
    return source,rows,originals,candidates
def main():
    WORK.mkdir(exist_ok=True)
    assert hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest()==EXPECTED
    source,rows,originals,candidates=transformed(BASE)
    helper='''#pragma once
#include "gd_rt.hpp"
namespace gd {
inline bool native_static_sound_count(const GdVal& character_class,unsigned column,GdVal& out) {
    if(character_class.kind!=GdVal::Kind::Int || character_class.i<0 || character_class.i>=7 || column>=3)return false;
    static constexpr int64_t counts[7][3]={
'''+''.join('        {'+','.join(map(str,row[1:]))+'},\n' for row in rows)+'''    };
    out=GdVal::from_int(counts[character_class.i][column]);return true;
}
}
'''
    (WORK/'static_collection_helper.hpp').write_text(helper,encoding='utf8',newline='\n')
    strings=re.search(r'constexpr gd::GdStr battle_string_literals\[\] = \{.*?^\};',source,re.M|re.S);assert strings
    header='''#pragma once
#include "native_event_kernel.hpp"
#include "native_array_index.hpp"
#include "gen/hdrs/Gd__gd_core__CoreConst.hpp"
#include "static_collection_helper.hpp"
namespace {
'''+strings[0]+'\n}\n'
    for name,text in candidates.items():
        if name=='numStackTypes':text=text.replace('Gd__gd_core__CoreConst::sf_numStackTypes','candidate_numStackTypes')
        else:
            text=text.replace(f'Gd__gd_core__CoreCharacter::fn_{name}(const',f'candidate_{name}(Gd__gd_core__CoreCharacter& character,const')
            text=text.replace('this->','character.')
        header+='inline '+text+'\n'
    (WORK/'preflight_static_collections.hpp').write_text(header,encoding='utf8',newline='\n')
    plan={'baseline_dll_sha256':EXPECTED,'sound_count_rows':rows,'folded_stack_type_count':11,
        'original_function_sha256':{name:hashlib.sha256(text.encode()).hexdigest() for name,text in originals.items()},
        'global_mutable_collection_getters_unchanged':True,'round_win_coercion_before_guard':True,
        'unknown_class_kinds_and_disabled_optimization_original_fallback':True,
        'screen_protocol':{'pairs':8,'sound_calls_per_arm':100000,'stack_count_calls_per_arm':1000000,'normal_priority_single_thread_all8_cpus':True,'retain_first_and_all_results':True,'local_functions_only_no_whole_fight_claim':True}}
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared literal7x3 count consumers and11-stack count; mutable getters unchanged')
if __name__=='__main__':main()
