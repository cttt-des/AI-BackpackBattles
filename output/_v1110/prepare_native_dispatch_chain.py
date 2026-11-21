"""Prove generated behavior routing and prepare a flat callback transport."""
import hashlib
import json
from pathlib import Path
import re
from analyze_native_dispatch import analyze

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/dispatch_chain_probe'
EXPECTED='00cbcf9d9467feab8d8d99aa437683af507c5f924ee90a9b9f076b661d5c6a60'

def body(source, signature):
    begin=source.index(signature);return source[begin:source.index('\n}',begin)+2]

def prepare(native):
    runtime=(native/'gd_rt.cpp').read_text('utf8')
    assert 'return a.str->len == b.str->len && a.str->hash == b.str->hash &&\n                       std::memcmp(a.str->data, b.str->data, a.str->len) == 0;' in runtime
    source='\n'.join(path.read_text('utf8') for path in sorted((native/'gen/shards').glob('shard_*.cpp')))
    core=(native/'gen/shards/shard_00.cpp').read_text('utf8')
    literals=re.search(r'constexpr gd::GdStr battle_string_literals\[\] = \{(.*?)^\};',core,re.M|re.S);assert literals
    literal_rows=[(json.loads('"'+s+'"'),int(length),int(stored_hash)) for s,length,stored_hash in re.findall(r'\{"((?:\\.|[^"\\])*)", (\d+)u, (\d+)u\}',literals[1])]
    strings=[row[0] for row in literal_rows]
    names=strings[1:10]
    assert names==['onCombatStart','getGatedDescriptor','getReplaceDescriptor','onChargeReceived','onChargeLeft','chargedItemStatChange','onPreDealDamage_early','onPreDealDamage_late','onDealtDamage']
    literal='case SYM_GEN_SELF_BEHAVIOR_METHODS_61: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {'+', '.join(f'gd::GdVal::from_str(&battle_string_literals[{i}])' for i in range(1,10))+'}));'
    assert literal in core
    symbols={}
    for name in names:
        candidates=set(re.findall(r'case ([\w:]+): out = (?:fn|sf)_'+name+r'\(',source))
        assert len(candidates)<=1,(name,candidates)
        symbols[name]=next(iter(candidates)) if candidates else None
    profile=json.loads((STAGE/'native_perf50/static_setup_bundle/profile_depth64.json').read_bytes())
    plan=analyze(native,profile,limit=0,extra_symbols=[symbol for symbol in symbols.values() if symbol])
    assert plan['generated_classes']==plan['eligible_classes_with_pure_inheritance']==674
    dispatch=(native/'native_resolved_dispatch.hpp').read_text('utf8')
    table=dispatch[dispatch.index('static const NativeMethodRow native_resolved_rows[]'):dispatch.index('static const NativeMethodRow native_resolved_empty')]
    row_classes=re.findall(r'^    \{&META_(Gd__\w+),',table,re.M)
    registrations=re.findall(r'value.emplace\(&typeid\((Gd__\w+)\),&native_resolved_rows\[(\d+)\]\);',dispatch)
    assert len(row_classes)==len(registrations)==674
    assert all(row_classes[int(index)]==cls for cls,index in registrations),'New method routing requires exact per-class metadata, not a representative shared row'
    primary_cells={cls:re.findall(r'&native_resolved_invoke<[^>]+>|nullptr',line) for cls,line in zip(row_classes,[line for line in table.splitlines() if line.startswith('    {&META_')])}
    assert all(len(cells)==128 for cells in primary_cells.values())
    inline=(native/'native_inline_dispatch.hpp').read_text('utf8')
    slot_block=inline[inline.index('inline constexpr auto native_resolved_slots='):inline.index('    return value; }();',inline.index('inline constexpr auto native_resolved_slots='))]
    primary_slots={symbol:int(slot) for symbol,slot in re.findall(r'value\[([\w:]+)\]=(\d+);',slot_block)}
    parents={}
    for path in (native/'gen/hdrs').glob('*.hpp'):
        match=re.search(r'^struct (Gd__\w+) : public ([\w:]+) \{',path.read_text('utf8'),re.M);assert match
        parents[match[1]]=match[2]
    own={}
    for match in re.finditer(r'^bool (Gd__\w+)::has_own_method\([^\n]*\n(.*?)^\}',source,re.M|re.S):
        cls,block=match[1],match[2]
        own[cls]=set(re.findall(r'case ([\w:]+): return true;',block))
        leftover=re.sub(r'case [\w:]+: return true;','',block)
        leftover=re.sub(r'return [\w:]+::has_own_method\(m\);','',leftover)
        for text in ('switch (m) {','default: break;','return false;','}'):leftover=leftover.replace(text,'')
        assert not leftover.strip(),cls
        edges=re.findall(r'return ([\w:]+)::has_own_method\(m\);',block)
        assert edges==[parents[cls]] if parents[cls] in parents else edges in ([],['gd::GdObj'])
    assert set(own)==set(parents)
    present={}
    def resolve(cls):
        if cls not in present:present[cls]=own[cls] | (resolve(parents[cls]) if parents[cls] in parents else set())
        return present[cls]
    for cls in own:resolve(cls)
    selected=[item['symbol'] for item in plan['selected_methods']]
    owners=set();entries=[];safe=[]
    for cls,row in sorted(plan['class_rows'].items()):
        methods=plan['resolved_rows'][row];functions=[];mask=0;callable_mask=0
        for key,name in enumerate(names):
            symbol=symbols[name]
            method=methods[selected.index(symbol)] if symbol else None
            if method:
                owner,fn=method;owners.add(owner);mask|=1<<key;callable_mask|=1<<key
                if symbol in primary_slots:
                    actual=re.sub(r'\s+','',primary_cells[cls][primary_slots[symbol]])
                    assert actual==f'&native_resolved_invoke<{owner},&{owner}::fn_{fn}>',(cls,symbol,actual)
                functions.append(f'&native_chain_invoke<{owner},&{owner}::fn_{fn}>')
                definition=body(source,f'gd::GdVal {owner}::fn_{fn}(')
                simple=definition[definition.index('{')+1:-1].replace('gd::BattleCtx& gd_ctx = *this->rt_ctx_;','').strip()
                simple=simple.replace('return gd::GdVal::null();','').strip()
                if not simple:safe.append((cls,key))
            else:
                functions.append('nullptr')
                if symbol and symbol not in present[cls]:mask|=1<<key
        entries.append((cls,mask,callable_mask,functions))
    metadata=(native/'gen/class_metas.hpp').read_text('utf8')
    last=re.findall(r'^    (CLS_Gd__\w+),?$',metadata,re.M)[-1]
    helper='''namespace gd {
void native_dispatch_chain_hit(unsigned);
template<class T,GdVal (T::*Method)(const GdVal*,int)>
GdVal native_chain_invoke(GdObj* object,const GdVal* args,int count){return (static_cast<T*>(object)->*Method)(args,count);}
struct NativeBehaviorChainRow {const GdClassMeta* metadata;uint16_t supported;uint16_t callable;std::array<NativeResolvedFn,9> methods;};
static const auto native_behavior_chain_rows=[] {
    std::array<NativeBehaviorChainRow,static_cast<size_t>('''+last+''')+1> rows{};
'''
    for cls,mask,callable_mask,functions in entries:
        helper+=f'    rows[CLS_{cls}]={{&META_{cls},{mask}u,{callable_mask}u,{{'+','.join(functions)+'}};\n'
    helper+='''    return rows;
}();
bool native_try_behavior_chain(BattleCtx& ctx,GdObj* object,const GdVal& name,const GdVal& arguments,bool probe,GdVal& out) {
    if(!ctx.native_resolved_dispatch || !object || name.kind!=GdVal::Kind::Str || !name.str)return false;
    const auto* row=object->native_call_row_;
    if(!row || (ctx.native_resolved_audit && !native_resolved_row_matches(object,row)))return false;
    const auto* meta=row->metadata;
    if(!meta || meta->id>=native_behavior_chain_rows.size())return false;
    const auto& selected=native_behavior_chain_rows[meta->id];
    if(selected.metadata!=meta)return false;
    unsigned key=9;
'''
    for key,name in enumerate(names):
        assert literal_rows[key+1][1]==len(name)
        helper+=f'    if(name.str->len=={len(name)}u && name.str->hash=={literal_rows[key+1][2]}u && std::memcmp(name.str->data,"{name}",{len(name)})==0)key={key};\n'
    helper+='''    if(key==9){out=probe?GdVal::from_bool(false):GdVal::null();if(ctx.native_resolved_collect)native_dispatch_chain_hit(probe?2:1);return true;}
    if(!(selected.supported & (uint16_t(1)<<key)))return false;
    static const SymId symbols[9]={'''+','.join(symbols[name] or 'SYM_NONE' for name in names)+'''};
    // Keep registration and re-registration behavior of the original has_method.
    const auto method=intern_sym(std::string_view(name.str->data,name.str->len));
    if(method!=symbols[key])return false;
    if(ctx.native_resolved_collect)++ctx.native_resolved_counts[0];
    const bool callable=(selected.callable & (uint16_t(1)<<key))!=0;
    if(probe){out=GdVal::from_bool(callable);if(ctx.native_resolved_collect)native_dispatch_chain_hit(2);return true;}
    if(!callable){out=GdVal::null();if(ctx.native_resolved_collect)native_dispatch_chain_hit(1);return true;}
    const GdVal* args=nullptr;int count=0;
    if(arguments.kind==GdVal::Kind::Arr && arguments.arr){args=arguments.arr->data;count=static_cast<int>(arguments.arr->len);}
    const int slot=method<native_resolved_slots.size()?native_resolved_slots[method]:-1;
    if(ctx.native_resolved_collect){native_dispatch_chain_hit(0);if(slot>=0 && row->methods[slot]){++ctx.native_resolved_counts[0];if(slot>=112)native_inline_hot_slot_hit(0);}}
    out=selected.methods[key](object,args,count);return true;
}
}
'''
    callback='''namespace gd {
void native_dispatch_chain_hit(unsigned);
inline bool native_try_flat_funcref(BattleCtx& ctx,const GdVal& value,const GdVal& arguments,GdVal& out) {
    if(!ctx.native_resolved_dispatch || value.kind!=GdVal::Kind::FuncRef || !value.fr)return false;
    const auto* reference=value.fr;
    if(!reference->instance || reference->method==SYM_NONE || (reference->binds && reference->binds->len))return false;
    const auto method=reference->method;
    const int slot=method<native_resolved_slots.size()?native_resolved_slots[method]:-1;
    if(slot<0)return false;
    auto* object=reference->instance;const auto* row=object->native_call_row_;
    if(!row || (ctx.native_resolved_audit && !native_resolved_row_matches(object,row)))return false;
    const auto function=row->methods[slot];if(!function)return false;
    const GdVal* args=nullptr;int count=0;
    if(arguments.kind==GdVal::Kind::Arr && arguments.arr){args=arguments.arr->data;count=static_cast<int>(arguments.arr->len);}
    if(ctx.native_resolved_collect){++ctx.native_resolved_counts[1];if(slot>=112)native_inline_hot_slot_hit(0);native_dispatch_chain_hit(3);}
    out=function(object,args,count);return true;
}
}
'''
    originals={};updates={}
    for name,probe in [('_behavior_call',False),('_hasBehaviorMethod',True)]:
        old=body(core,f'gd::GdVal Gd__gd_core__CoreItem::fn_{name}(')
        anchor='    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f__behavior, gd::GdVal::null())))) {'
        assert old.count(anchor)==1
        inserted='''    if(gd_ctx.native_resolved_dispatch && this->f__behavior.kind==gd::GdVal::Kind::Null){
        gd::GdVal result;
        if(gd::native_try_behavior_chain(gd_ctx,this,lv_methodName,'''+('gd::GdVal::null(),true' if probe else 'lv_args,false')+''',result))return result;
    }
'''
        originals[name]=old;updates[name]=old.replace(anchor,inserted+anchor,1)
    return dict(names=names,symbols=symbols,owners=sorted(owners),classes=plan['generated_classes'],eligible_classes=plan['eligible_classes_with_pure_inheritance'],helper=helper,callback=callback,originals=originals,updates=updates,safe_calls=sorted(set(safe)),entries=entries)

def main():
    assert hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest()==EXPECTED
    WORK.mkdir(exist_ok=True);design=prepare(BASE)
    header='#pragma once\n#include <vector>\n#include "native_event_kernel.hpp"\n#include "native_inline_dispatch.hpp"\n#include "native_scalar_equal.hpp"\n'
    header+=''.join(f'#include "gen/hdrs/{owner}.hpp"\n' for owner in design['owners'])
    header+='#ifndef GD_CHAIN_PRODUCTION\n'+design['helper']+design['callback']+'#endif\n'
    for name,updated in design['updates'].items():
        updated=updated.replace(f'Gd__gd_core__CoreItem::fn_{name}(const',f'candidate_{name}(Gd__gd_core__CoreItem& item,const').replace('this->','item.').replace('gd_ctx,this,','gd_ctx,&item,')
        updated=updated.replace('gd::GdVal::from_obj(this)','gd::GdVal::from_obj(&item)')
        # The untouched fallback uses this shard's literal whitelist builder.
        header+='inline '+updated+'\n'
    header+='inline gd::GdVal candidate_funcv(gd::BattleCtx& ctx,const gd::GdVal& value,const gd::GdVal* args,int count){if(value.kind==gd::GdVal::Kind::FuncRef && value.fr && count>=1){gd::GdVal out;if(gd::native_try_flat_funcref(ctx,value,args[0],out))return out;}return native_event_funcv(ctx,value,args,count);}\n'
    header+='struct ChainClass {const gd::GdClassMeta* metadata;};\ninline const ChainClass chain_classes[]={\n'+''.join(f'{{&META_{cls}}},\n' for cls,_,_,_ in design['entries'])+'};\n'
    header+='struct SafeCall {const gd::GdClassMeta* metadata;unsigned key;};\ninline const SafeCall safe_calls[]={\n'+''.join(f'{{&META_{cls},{key}}},\n' for cls,key in design['safe_calls'])+'};\n'
    (WORK/'preflight_dispatch_chain.hpp').write_text(header,encoding='utf8',newline='\n')
    (WORK/'behavior_helper.hpp').write_text(design['helper'],encoding='utf8',newline='\n')
    (WORK/'callback_helper.hpp').write_text(design['callback'],encoding='utf8',newline='\n')
    report=dict(baseline_dll_sha256=EXPECTED,generated_classes=design['classes'],pure_dispatch_and_has_method_classes=design['eligible_classes'],names=design['names'],symbols=design['symbols'],safe_noop_cases=len(design['safe_calls']),
        existing_object_context_method_row_and_funcref_layout_unchanged=True,unsupported_uncached_unknown_audit_mismatch_and_bound_references_fallback=True,
        helper_sha256=hashlib.sha256(design['helper'].encode()).hexdigest(),callback_sha256=hashlib.sha256(design['callback'].encode()).hexdigest(),
        original_functions_sha256={name:hashlib.sha256(value.encode()).hexdigest() for name,value in design['originals'].items()},
        local_protocol=dict(pairs=8,behavior_calls_per_arm=100000,callback_calls_per_arm=1000000,retain_first_and_all_results=True,no_whole_fight_gain_claim=True))
    if (WORK/'hash_negative.json').exists():
        report['hash_guard_revision']={'reason':'Original gd_eq uses stored string hashes before comparing bytes; preserve mismatched-hash short circuit including unread data pointers',
            'old_prototype_screen_retained':'screen.json','first_corrected_variant_screen':'screen_hash_guard.json','additional_malformed_cases':31104,
            'original310500_case_hashes_must_remain_identical':True,'performance_protocol_unchanged':True}
    (WORK/'evaluation_plan.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()
