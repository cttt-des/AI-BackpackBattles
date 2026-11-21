"""Resolve pure generated fields into shared exact-type property rows."""
from collections import Counter
import hashlib
import json
from pathlib import Path
import re
from prototype_native_hot_control_bundle import optimize as controls

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'native_perf50/item_locality_bundle'

def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def replace(text,old,new):
    assert text.count(old)==1,old[:100]
    return text.replace(old,new,1)

def property_calls(source):
    token='gd::get_prop(';pos=0
    while True:
        start=source.find(token,pos)
        if start<0:return
        pos=start+len(token);depth=1;brackets=0;begin=pos;args=[];quote=None;escape=False
        for i in range(pos,len(source)):
            ch=source[i]
            if quote:
                if escape:escape=False
                elif ch=='\\':escape=True
                elif ch==quote:quote=None
                continue
            if ch in ('"',"'"):quote=ch;continue
            if ch=='(':depth+=1
            elif ch==')':
                depth-=1
                if depth==0:
                    args.append(source[begin:i].strip());break
            elif ch in '[{':brackets+=1
            elif ch in ']}':brackets-=1
            elif ch==',' and depth==1 and brackets==0:args.append(source[begin:i].strip());begin=i+1
        else:raise AssertionError('Unclosed generated property call')
        if len(args)==3:yield args[2]

def analyze(native):
    parents={};declared={}
    for p in sorted((native/'gen/hdrs').glob('*.hpp')):
        text=p.read_text('utf8');m=re.search(r'^struct (Gd__\w+) : public ([\w:]+) \{',text,re.M)
        if m:parents[m[1]]=m[2];declared[m[1]]=set(re.findall(r'\bgd::GdVal (f_\w+);',text))
    shards={p:p.read_text('utf8') for p in sorted((native/'gen/shards').glob('*.cpp'))}
    source='\n'.join(shards.values());own={}
    case=re.compile(r'^        case ([\w:]+): out = ([^\n]*); return true;\n',re.M)
    for m in re.finditer(r'^bool (Gd__\w+)::get_prop\([^\n]*\n(.*?)^\}',source,re.M|re.S):
        cls,body=m[1],m[2];entries={}
        for c in case.finditer(body):
            field=re.fullmatch(r'this->(f_\w+)',c[2])
            if field:assert field[1] in declared[cls]
            # Non-field cases still shadow the inherited property.
            entries[c[1]]=(cls,field[1]) if field else None
        left=case.sub('',body)
        fallbacks=re.findall(r'return ([\w:]+)::get_prop\(prop, out\);',left)
        base=parents[cls]
        assert (fallbacks==[base] if base in parents else base=='gd::GdObj' and fallbacks in ([],['gd::GdObj'])),cls
        left=re.sub(r'return [\w:]+::get_prop\(prop, out\);','',left)
        for token in ('switch (prop) {','default: break;','return false;','}'):left=left.replace(token,'')
        assert not left.strip(),(cls,left)
        own[cls]=entries
    assert set(own)==set(parents) and len(own)==674
    resolved={}
    def resolve(cls):
        if cls in resolved:return resolved[cls]
        base=parents[cls];row=resolve(base).copy() if base in parents else {}
        assert base in parents or base=='gd::GdObj'
        row.update(own[cls]);resolved[cls]=row;return row
    for cls in parents:resolve(cls)
    eligible={symbol for row in resolved.values() for symbol,value in row.items() if value}
    eligible={s for s in eligible if 'resource_path' not in s}
    calls=Counter(s for s in property_calls(source) if s in eligible)
    selected=[s for s,n in calls.most_common(32)];assert len(selected)==32
    return parents,resolved,shards,selected,calls

INLINE='''
bool try_native_resolved_property(BattleCtx&,GdObj*,SymId,GdVal&);
void native_inline_property_hit(unsigned);
#if defined(_MSC_VER)
__forceinline
#elif defined(__GNUC__)
__attribute__((always_inline)) inline
#else
inline
#endif
GdVal native_inline_get_prop(BattleCtx& ctx,const GdVal& recv,SymId prop) {
    const int slot=prop<native_property_slots.size()?native_property_slots[prop]:-1;
    if(slot>=0 && prop!=SYM_resource_path && ctx.native_resolved_dispatch &&
       recv.kind==GdVal::Kind::Obj && recv.obj) {
        const NativeMethodRow* row=recv.obj->native_call_row_;
        if(row && (!ctx.native_resolved_audit || native_resolved_row_matches(recv.obj,row))) {
            const auto function=row->properties ? row->properties->getters[slot] : nullptr;
            if(function) {
                if(ctx.native_resolved_collect)native_inline_property_hit(0);
                return function(recv.obj);
            }
            if(ctx.native_resolved_collect)native_inline_property_hit(1);
            return gd::get_prop(ctx,recv,prop);
        }
        GdVal out;
        if(try_native_resolved_property(ctx,recv.obj,prop,out))return out;
    }
    return gd::get_prop(ctx,recv,prop);
}
'''

COLD='''
static thread_local uint64_t native_property_counts[2]{};
void native_inline_property_hit(unsigned index) {
    if(index<2)++native_property_counts[index];
}
bool try_native_resolved_property(BattleCtx& ctx,GdObj* object,SymId prop,GdVal& out) {
    if(!ctx.native_resolved_dispatch || !object || prop==SYM_resource_path || prop>=native_property_slots.size())return false;
    const int slot=native_property_slots[prop];if(slot<0)return false;
    const NativeMethodRow* row=object->native_call_row_;
    if(!row) {
        row=native_resolved_exact_row(object);
        // An unknown getter must see the same null cache it saw before.
        if(row!=&native_resolved_empty) {
            object->native_call_row_=row;
            if(ctx.native_resolved_collect)++ctx.native_resolved_counts[2];
        }
    }
    if(ctx.native_resolved_audit && row!=native_resolved_exact_row(object)) {
        ++ctx.native_resolved_counts[4];return false;
    }
    const auto function=row->properties ? row->properties->getters[slot] : nullptr;
    if(!function) {
        if(ctx.native_resolved_collect)native_inline_property_hit(1);
        return false;
    }
    if(ctx.native_resolved_collect)native_inline_property_hit(0);
    out=function(object);return true;
}
'''

def optimize(native):
    expected=json.loads((BASE/'source_before_build.json').read_bytes())
    assert expected=={p.relative_to(native).as_posix():digest(p) for p in native.rglob('*') if p.is_file()}
    parents,fields,shards,symbols,calls=analyze(native)
    path=native/'native_resolved_dispatch.hpp';source=path.read_text('utf8')
    start=source.index('static const NativeMethodRow native_resolved_rows[] = {\n')
    end=source.index('\n};\nstatic const NativeMethodRow native_resolved_empty',start)+len('\n};')
    old=[]
    for row in re.findall(r'^    \{\{(.*?)\}\},$',source[start:end],re.M):
        cells=tuple(re.findall(r'&native_resolved_invoke<[^>]+>|nullptr',row))
        assert len(cells)==112 and ','.join(cells)==row;old.append(cells)
    assert len(old)==665
    old_types={c:int(i) for c,i in re.findall(r'value\.emplace\(&typeid\((\w+)\),&native_resolved_rows\[(\d+)\]\);',source)}
    assert set(old_types)==set(parents)
    props={};types_props={};rows={};types={}
    for cls in sorted(parents):
        key=tuple(fields[cls].get(s) for s in symbols)
        if key not in props:props[key]=len(props)
        types_props[cls]=props[key]
        key2=(old[old_types[cls]],props[key])
        if key2 not in rows:rows[key2]=len(rows)
        types[cls]=rows[key2]
    prop_lines=['template<class C,GdVal C::*Member>',
        'GdVal native_resolved_field(const GdObj* object) { return static_cast<const C*>(object)->*Member; }',
        'static const NativePropertyRow native_property_rows[] = {']
    for key in props:
        cells=[f'&native_resolved_field<{v[0]}, &{v[0]}::{v[1]}>' if v else 'nullptr' for v in key]
        prop_lines.append('    {{'+','.join(cells)+'}},')
    prop_lines+=['};','static const NativeMethodRow native_resolved_rows[] = {']
    for (methods,pid) in rows:prop_lines.append('    {&native_property_rows['+str(pid)+'],{'+','.join(methods)+'}},')
    prop_lines+=['};']
    updated=source[:start]+'\n'.join(prop_lines)+source[end:]
    updated=re.sub(r'value\.emplace\(&typeid\((\w+)\),&native_resolved_rows\[(\d+)\]\);',
        lambda m:f'value.emplace(&typeid({m[1]}),&native_resolved_rows[{types[m[1]]}]);',updated)
    marker='} // namespace gd';assert updated.count(marker)==1
    updated=updated.replace(marker,COLD+'\n'+marker+'\nextern "C" uint64_t gd_diag_native_property_stat(unsigned index) {\n    return index<2 ? gd::native_property_counts[index] : 0;\n}\n')
    changes={path:updated}
    path=native/'native_inline_dispatch.hpp';header=path.read_text('utf8')
    old_decl='struct NativeMethodRow { std::array<NativeResolvedFn,112> methods; };'
    new_decl='''using NativePropertyFn = GdVal (*)(const GdObj*);
struct NativePropertyRow { std::array<NativePropertyFn,32> getters; };
struct NativeMethodRow { const NativePropertyRow* properties; std::array<NativeResolvedFn,112> methods; };'''
    header=replace(header,old_decl,new_decl)
    slots=['inline constexpr auto native_property_slots=[] { std::array<int8_t,static_cast<size_t>(SYM_GEN_Dragon_2878)+1> value{}; value.fill(-1);']
    slots += [f'    value[{s}]={i};' for i,s in enumerate(symbols)]
    slots += ['    return value; }();']
    anchor='bool native_resolved_row_matches(const GdObj*,const NativeMethodRow*);'
    header=replace(header,anchor,anchor+'\n'+'\n'.join(slots)+INLINE)
    changes[path]=header
    seeded={};sites=0
    pattern=re.compile(r'(static gd::GdObj\* _alloc_(\w+)\(gd::BattleCtx& ctx\) \{ auto\* object=ctx.arena.make<\2>\(&ctx\); if\(ctx.native_resolved_dispatch\)gd::native_resolved_seed\(object,)(\d+)(u\); return object; \})')
    for path,text in shards.items():
        getter_pattern=r'^bool (Gd__\w+)::get_prop\([^\n]*\n(.*?)^\}'
        original_getters=dict(re.findall(getter_pattern,text,re.M|re.S))
        def seed(m):
            cls=m[2];assert int(m[3])==old_types[cls];seeded[cls]=types[cls]
            return m[1]+str(types[cls])+m[4]
        text=pattern.sub(seed,text);sites+=text.count('gd::get_prop(')
        text=text.replace('gd::get_prop(','gd::native_inline_get_prop(')
        assert dict(re.findall(getter_pattern,text,re.M|re.S))==original_getters,'Original virtual field switches are the independent oracle'
        assert '#include "../../native_inline_dispatch.hpp"' in text or 'native_inline_dispatch.hpp' in text
        changes[path]=text
    assert seeded==types and sites>1000
    control_report=controls(native,expected)
    for path,text in changes.items():path.write_text(text,encoding='utf8',newline='\n')
    return {'status':'implemented_uncompiled_unmeasured','baseline_dll_sha256':'8e7d574055c36e7535cb54139e11514729e72088c4314ad028c623d42ae32cfa',
        'components':['hot control member order','shared exact generated field getters'],
        'control':control_report,'generated_classes':674,'method_slots':112,'method_rows':len(rows),
        'property_slots':32,'shared_property_rows':len(props),'property_call_sites_rewritten':sites,
        'selected_properties':[{'symbol':s,'static_property_call_sites':calls[s]} for s in symbols],
        'class_rows':types,'class_property_rows':types_props,
        'property_rows':[[list(v) if v else None for v in key] for key in props],
        'global_resource_path_precedence_preserved':True,'unknown_null_cache_preserved':True,
        'original_virtual_getters_unchanged':True,
        'field_shadowing_and_nonfield_shadows_preserved':True,'numeric_and_rng_code_changed':False}
