"""Build a native-only, typed execution path across the core event chain.

Arithmetic, callbacks and their original expression nesting are retained. The
ordinary paths remain intact for C++ callers outside the closed native bridge.
"""
from collections import Counter
import hashlib
from pathlib import Path
import re

CLASSES=['CoreContext','CoreCharacter','CoreBuff','CoreCombatLog','CoreEventBus',
         'CoreRng','CoreDamageSource','CoreDamageResult','CoreEvent','CoreRng__INNER__BalancedRng']
PREFIX='Gd__gd_core__'
HEADER='''#pragma once
#include "gd_rt.hpp"
'''+''.join(f'#include "gen/hdrs/{PREFIX}{name}.hpp"\n' for name in CLASSES)+'''
#include <typeinfo>

gd::GdVal gd_native_event_hooks_call(gd::BattleCtx&,const gd::GdVal&,gd::SymId,const gd::GdVal*,int);

template<class T> bool native_event_type_ok(gd::BattleCtx& ctx,const gd::GdVal& value) {
    if(!ctx.native_event_audit)return true;
    if(&typeid(*value.obj)==&typeid(T))return true;
    ++ctx.native_event_counts[4];return false;
}
template<class T, gd::GdVal T::* Field>
gd::GdVal native_event_get(gd::BattleCtx& ctx,const gd::GdVal& value,gd::SymId property) {
    if(value.kind==gd::GdVal::Kind::Obj && value.obj && native_event_type_ok<T>(ctx,value))
        return static_cast<T*>(value.obj)->*Field;
    return gd::get_prop(ctx,value,property);
}
template<class T, gd::GdVal (T::*Method)(const gd::GdVal*,int)>
gd::GdVal native_event_call(gd::BattleCtx& ctx,const gd::GdVal& value,gd::SymId method,const gd::GdVal* args,int argc) {
    if(value.kind==gd::GdVal::Kind::Obj && value.obj && native_event_type_ok<T>(ctx,value))
        return (static_cast<T*>(value.obj)->*Method)(args,argc);
    return gd::call_method(ctx,value,method,args,argc);
}
template<class T>
void native_event_set(gd::BattleCtx& ctx,gd::GdVal& value,gd::SymId property,const gd::GdVal& input) {
    if(value.kind==gd::GdVal::Kind::Obj && value.obj && native_event_type_ok<T>(ctx,value)) {
        static_cast<T*>(value.obj)->T::set_prop(ctx,property,input);return;
    }
    gd::set_prop(ctx,value,property,input);
}
template<class T>
gd::GdVal native_event_new(gd::BattleCtx& ctx,const gd::GdVal* args,int argc) {
    auto* object=ctx.arena.make<T>(&ctx);
    object->T::init_fields(ctx);
    gd::GdVal result;
    object->T::call_method(ctx,gd::SYM__init,args,argc,result);
    return gd::GdVal::from_obj(object);
}
inline gd::GdVal native_event_funcv(gd::BattleCtx& ctx,const gd::GdVal& value,const gd::GdVal* args,int argc) {
    if(value.kind==gd::GdVal::Kind::FuncRef && value.fr && argc>=1)
        return value.fr->call_funcv(ctx,args[0]);
    return gd::call_method(ctx,value,gd::SYM_call_funcv,args,argc);
}
'''
FIELDS={
 'CoreCharacter':{'ctx':'CoreContext','opponent':'CoreCharacter','accuracyRng':'CoreRng__INNER__BalancedRng',
                  'critRng':'CoreRng__INNER__BalancedRng','critResistanceRng':'CoreRng__INNER__BalancedRng'},
 'CoreBuff':{'ctx':'CoreContext','character':'CoreCharacter'},
 'CoreCombatLog':{'_ctx':'CoreContext'},'CoreEventBus':{'_ctx':'CoreContext'},
 'CoreContext':{'rng':'CoreRng','bus':'CoreEventBus','combat_log':'CoreCombatLog','hooks':'CoreHooks',
                'player':'CoreCharacter','opponent':'CoreCharacter'},
 'CoreDamageSource':{'_rng':'CoreRng'},
 'CoreDamageResult':{'damageSource':'CoreDamageSource','_ctx':'CoreContext','event':'CoreEvent'},
 'CoreEvent':{'parentEvent':'CoreEvent'},
}

def digest(s):return hashlib.sha256(s.encode()).hexdigest()

def parts(text):
    """Split generated call arguments, including nested lambdas and arrays."""
    result=[];begin=0;depth=0;quote=None;escape=False
    for i,c in enumerate(text):
        if quote:
            if escape:escape=False
            elif c=='\\':escape=True
            elif c==quote:quote=None
        elif c in ('"',"'"):quote=c
        elif c in '([{':depth+=1
        elif c in ')]}':depth-=1
        elif c==',' and depth==0:result.append(text[begin:i].strip());begin=i+1
    result.append(text[begin:].strip());return result

def closing(text,opening):
    depth=0;quote=None;escape=False
    for i in range(opening,len(text)):
        c=text[i]
        if quote:
            if escape:escape=False
            elif c=='\\':escape=True
            elif c==quote:quote=None
        elif c in ('"',"'"):quote=c
        elif c=='(':depth+=1
        elif c==')':
            depth-=1
            if not depth:return i
    raise ValueError('Unbalanced generated call')

def class_methods(sources,cls):
    full=PREFIX+cls
    dispatch=re.search(r'^bool '+full+r'::call_method\([^\n]*\n(.*?)^\}',sources,re.M|re.S)
    getter=re.search(r'^bool '+full+r'::get_prop\([^\n]*\n(.*?)^\}',sources,re.M|re.S)
    assert dispatch and getter,cls
    methods=dict(re.findall(r'case ([\w:]+): out = fn_(\w+)\(args, argc\); return true;',dispatch[1]))
    fields=dict(re.findall(r'case ([\w:]+): out = this->f_(\w+); return true;',getter[1]))
    return methods,fields

def optimize(native):
    header=native/'native_event_kernel.hpp'
    if header.exists():
        assert header.read_text('utf8')==HEADER
        return
    originals={p:p.read_text('utf8') for p in (native/'gen/shards').glob('*.cpp')}
    joined='\n'.join(originals.values());methods={};fields={}
    for cls in CLASSES:
        for path in (native/'gen/hdrs').glob('*.hpp'):
            assert not re.search(r': public '+re.escape(PREFIX+cls)+r'\b',path.read_text('utf8')),(cls,path)
        methods[cls],fields[cls]=class_methods(joined,cls)
    site_counts=Counter();method_counts=Counter();audit=[]
    pattern=re.compile(r'gd::(get_prop|set_prop|call_method)\(')
    for path,source in originals.items():
        output=source
        matches=list(re.finditer(r'^gd::GdVal ('+PREFIX+r'(?:'+ '|'.join(map(re.escape,CLASSES))+r'))::fn_(\w+)\([^\n]*\n.*?^\}',source,re.M|re.S))
        for match in reversed(matches):
            cls=match[1][len(PREFIX):];name=match[2];body=match[0]
            if name=='_init':continue
            typed={};produced={};counts=Counter()
            if cls=='CoreCharacter' and name=='takeDamage':typed.update(lv_damageRes='CoreDamageResult',lv_damageSource='CoreDamageSource')
            if cls=='CoreCharacter' and name=='dealDamage':typed.update(lv_damageSource='CoreDamageSource',lv_res='CoreDamageResult')
            if cls=='CoreCombatLog' and name.startswith('createEvent'):
                typed.update(lv_event='CoreEvent',lv_damageRes='CoreDamageResult',lv_character='CoreCharacter',
                             lv_attackedCharacter='CoreCharacter',lv_damagingCharacter='CoreCharacter',lv_damagedCharacter='CoreCharacter')
            if cls=='CoreBuff':typed.update(lv_event='CoreEvent',lv_resistedEvent='CoreEvent')
            def infer(expr):
                if expr in produced:return produced[expr]
                if expr in typed:return typed[expr]
                if expr=='gd::GdVal::from_obj(this)':return cls
                m=re.fullmatch(r'this->f_(\w+)',expr)
                return FIELDS.get(cls,{}).get(m[1]) if m else None
            def rewrite(text):
                out=[];at=0
                while m:=pattern.search(text,at):
                    end=closing(text,m.end()-1);args=[rewrite(x) for x in parts(text[m.end():end])]
                    replacement=None;target=None;field=None;method=None
                    if len(args)>=3 and args[0]=='gd_ctx':
                        target=infer(args[1])
                        if m[1]=='get_prop' and target in fields and args[2] in fields[target]:
                            field=fields[target][args[2]]
                            replacement=f'native_event_get<{PREFIX}{target}, &{PREFIX}{target}::f_{field}>(gd_ctx, {args[1]}, {args[2]})'
                            if t:=FIELDS.get(target,{}).get(field):produced[replacement]=t
                        elif m[1]=='set_prop' and target in methods and len(args)==4:
                            replacement=f'native_event_set<{PREFIX}{target}>(gd_ctx, {args[1]}, {args[2]}, {args[3]})'
                        elif m[1]=='call_method' and len(args)==5:
                            if target in methods and args[2] in methods[target]:
                                method=methods[target][args[2]]
                                if args[1]=='gd::GdVal::from_obj(this)':replacement=f'this->fn_{method}({args[3]}, {args[4]})'
                                else:replacement=f'native_event_call<{PREFIX}{target}, &{PREFIX}{target}::fn_{method}>(gd_ctx, {args[1]}, {args[2]}, {args[3]}, {args[4]})'
                                if target=='CoreCombatLog' and method.startswith('createEvent'):produced[replacement]='CoreEvent'
                            elif target=='CoreHooks':replacement=f'gd_native_event_hooks_call(gd_ctx, {args[1]}, {args[2]}, {args[3]}, {args[4]})'
                            elif args[2]=='gd::SYM_new':
                                c=re.fullmatch(r'gd::GdVal::from_cls\(&META_('+PREFIX+r'\w+)\)',args[1])
                                if c and c[1][len(PREFIX):] in CLASSES:
                                    replacement=f'native_event_new<{c[1]}>(gd_ctx, {args[3]}, {args[4]})';produced[replacement]=c[1][len(PREFIX):]
                            elif args[2]=='gd::SYM_call_funcv' and cls=='CoreEventBus':replacement=f'native_event_funcv(gd_ctx, {args[1]}, {args[3]}, {args[4]})'
                    if replacement is None:replacement='gd::'+m[1]+'('+', '.join(args)+')'
                    else:counts[m[1]]+=1
                    out.extend((text[at:m.start()],replacement));at=end+1
                out.append(text[at:]);return ''.join(out)
            lowered=rewrite(body)
            if not counts:continue
            anchor='    gd::BattleCtx& gd_ctx = *this->rt_ctx_;\n'
            assert body.count(anchor)==1 and lowered.count(anchor)==1,(cls,name)
            first=body.index(anchor)+len(anchor)
            transformed=lowered[lowered.index(anchor)+len(anchor):].removesuffix('}')
            counter=''
            counter_index={('CoreEventBus','emitAndLog'):0,('CoreCharacter','takeDamage'):1,('CoreBuff','gainTemporary'):2,('CoreCombatLog','createEvent'):3}.get((cls,name))
            if counter_index is not None:counter=f'        ++gd_ctx.native_event_counts[{counter_index}];\n'
            native_body=body[:first]+'    if (gd_ctx.native_event_kernel) {\n'+counter+transformed+'    }\n'+body[first:]
            output=output[:match.start()]+native_body+output[match.end():]
            site_counts.update(counts);method_counts[cls]+=1
            audit.append({'class':cls,'method':name,'sites':dict(counts),'original_sha256':digest(body),'native_sha256':digest(lowered)})
        if output!=source:
            path.write_text('#include "../../native_event_kernel.hpp"\n'+output,encoding='utf8',newline='\n')
    header.write_text(HEADER,encoding='utf8',newline='\n')
    path=native/'gd_rt.hpp';source=path.read_text('utf8')
    anchor='    bool native_inline_timer_headers = false;\n';assert source.count(anchor)==1
    source=source.replace(anchor,anchor+'    bool native_event_kernel = false;\n    bool native_event_audit = false;\n    uint64_t native_event_counts[5]{};\n',1)
    anchor='        native_inline_timer_headers = false;\n';assert source.count(anchor)==1
    source=source.replace(anchor,anchor+'        native_event_kernel = false;\n',1)
    path.write_text(source,encoding='utf8',newline='\n')
    path=native/'engine_wrapper.cpp';source=path.read_text('utf8');anchor='    battle.native_inline_timer_headers = true;\n';assert source.count(anchor)==1
    source=source.replace(anchor,anchor+'    battle.native_event_kernel = true;\n',1)
    source+='''
gd::GdVal gd_native_event_hooks_call(gd::BattleCtx& ctx,const gd::GdVal& hooks,gd::SymId method,const gd::GdVal* args,int argc) {
    if(hooks.kind!=gd::GdVal::Kind::Obj || !hooks.obj)return gd::call_method(ctx,hooks,method,args,argc);
    if(ctx.native_event_audit && &typeid(*hooks.obj)!=&typeid(NativeBattleHooks)) {
        ++ctx.native_event_counts[4];return gd::call_method(ctx,hooks,method,args,argc);
    }
    gd::GdVal out=gd::GdVal::null();
    static_cast<NativeBattleHooks*>(hooks.obj)->NativeBattleHooks::call_method(ctx,method,args,argc,out);
    return out;
}
extern "C" uint64_t gd_diag_native_event_stat(unsigned field) {return field<5?tl_battle_ctx.native_event_counts[field]:0;}
extern "C" void gd_diag_native_event_audit(int enabled) {tl_battle_ctx.native_event_audit=enabled!=0;}
'''
    path.write_text(source,encoding='utf8',newline='\n')
    report={'methods':dict(method_counts),'sites':dict(site_counts),'audit':audit,
            'native_scope':'closed native bridge only; generic paths retained',
            'arithmetic_and_rng_calls':'original helpers and source order retained',
            'copying_or_caching_mutable_values':False}
    print('Native event chain methods',dict(method_counts),'sites',dict(site_counts),flush=True)
    return report
