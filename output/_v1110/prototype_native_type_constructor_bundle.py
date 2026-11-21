"""Cache pure generated metadata and combine exact allocation/field initialization."""
import hashlib
import json
from pathlib import Path
import re
from analyze_native_type_construction import analyze

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'native_perf50/property_control_bundle'

def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def replace(text,old,new):
    assert text.count(old)==1,old[:120]
    return text.replace(old,new,1)

INLINE='''
void native_type_constructor_hit(unsigned);
#if defined(_MSC_VER)
__forceinline
#elif defined(__GNUC__)
__attribute__((always_inline)) inline
#else
inline
#endif
bool native_inline_is_type(BattleCtx& ctx,const GdVal& value,const GdClassMeta* target) {
    if(!target || value.kind!=GdVal::Kind::Obj || !value.obj)return false;
    if(ctx.native_resolved_dispatch) {
        const NativeMethodRow* row=value.obj->native_call_row_;
        if(row) {
            if(ctx.native_resolved_audit && !native_resolved_row_matches(value.obj,row)) {
                ++ctx.native_resolved_counts[4];
            } else if(row->metadata) {
                if(ctx.native_resolved_collect)native_type_constructor_hit(0);
                for(unsigned i=0;i<native_type_targets.size();++i)
                    if(target==native_type_targets[i])return (row->type_mask & (uint64_t{1}<<i))!=0;
                return row->metadata->is_subclass_of(target);
            }
        }
        if(ctx.native_resolved_collect)native_type_constructor_hit(1);
    }
    return gd::gd_is_type(value,target);
}
inline bool native_inline_self_type(BattleCtx* ctx,GdObj* object,const GdClassMeta* target) {
    if(ctx)return native_inline_is_type(*ctx,GdVal::from_obj(object),target);
    return gd::gd_is_type(GdVal::from_obj(object),target);
}
'''

def optimize(native):
    expected=json.loads((BASE/'source_before_build.json').read_bytes())
    assert expected=={p.relative_to(native).as_posix():digest(p) for p in native.rglob('*') if p.is_file()}
    design=analyze(native);classes=sorted(design['parents']);assert len(classes)==674
    targets=[t['class'] for t in design['selected_type_targets']]
    path=native/'native_resolved_dispatch.hpp';text=path.read_text('utf8')
    old_map={c:int(i) for c,i in re.findall(r'value\.emplace\(&typeid\((\w+)\),&native_resolved_rows\[(\d+)\]\);',text)}
    assert old_map==design['allocator_rows']
    begin=text.index('static const NativeMethodRow native_resolved_rows[] = {\n')
    end=text.index('\n};\nstatic const NativeMethodRow native_resolved_empty',begin)+len('\n};')
    old_rows=re.findall(r'^    \{&native_property_rows\[(\d+)\],\{(.*?)\}\},$',text[begin:end],re.M)
    assert len(old_rows)==667
    mapping={c:i for i,c in enumerate(classes)}
    lines=['static const NativeMethodRow native_resolved_rows[] = {']
    masks={}
    for cls in classes:
        prop,methods=old_rows[old_map[cls]]
        cells=re.findall(r'&native_resolved_invoke<[^>]+>|nullptr',methods)
        assert len(cells)==112 and ','.join(cells)==methods
        mask=sum(1<<i for i,t in enumerate(targets) if t in design['ancestors'][cls]);masks[cls]=mask
        lines.append(f'    {{&META_{cls},&native_property_rows[{prop}],{mask}ULL,{{'+methods+'}},')
    lines+=['};']
    text=text[:begin]+'\n'.join(lines)+text[end:]
    text=re.sub(r'value\.emplace\(&typeid\((\w+)\),&native_resolved_rows\[(\d+)\]\);',
        lambda m:f'value.emplace(&typeid({m[1]}),&native_resolved_rows[{mapping[m[1]]}]);',text)
    factory=['template<class C,unsigned Row>','GdObj* native_allocate_and_init(BattleCtx& ctx) {',
        '    auto* object=ctx.arena.make<C>(&ctx);',
        '    if(ctx.native_resolved_dispatch)native_resolved_seed(object,Row);',
        '    object->C::init_fields(ctx);','    return object;','}',
        'struct NativeInitializedFactory { const GdClassMeta* metadata; GdObj* (*make)(BattleCtx&); };',
        'GdObj* try_native_allocate_initialized(BattleCtx& ctx,const GdClassMeta* cls) {',
        '    if(!ctx.native_resolved_dispatch || !cls || !cls->alloc_fn)return nullptr;',
        f'    static constexpr auto factories=[] {{ std::array<NativeInitializedFactory,static_cast<size_t>({design["last_class_id_symbol"]})+1> value{{}};']
    for cls in classes:factory.append(f'        value[CLS_{cls}]={{&META_{cls},&native_allocate_and_init<{cls},{mapping[cls]}u>}};')
    factory += ['        return value; }();',
        '    if(cls->id<factories.size()) {',
        '        const auto& entry=factories[cls->id];',
        '        if(entry.metadata==cls && entry.make) {',
        '            if(ctx.native_resolved_collect)native_type_constructor_hit(2);',
        '            return entry.make(ctx);','        }','    }',
        '    if(ctx.native_resolved_collect)native_type_constructor_hit(3);',
        '    return nullptr;','}',
        'static thread_local uint64_t native_type_constructor_counts[4]{};',
        'void native_type_constructor_hit(unsigned index) { if(index<4)++native_type_constructor_counts[index]; }']
    marker='} // namespace gd';assert text.count(marker)==1
    text=text.replace(marker,'\n'+'\n'.join(factory)+'\n'+marker+'\nextern "C" uint64_t gd_diag_native_type_constructor_stat(unsigned index) {\n    return index<4 ? gd::native_type_constructor_counts[index] : 0;\n}\n',1)
    changes={path:text}
    path=native/'native_inline_dispatch.hpp';header=path.read_text('utf8')
    header=replace(header,'#include "gen/sym_ids.hpp"','#include "gen/sym_ids.hpp"\n#include "gen/class_metas.hpp"')
    old='struct NativeMethodRow { const NativePropertyRow* properties; std::array<NativeResolvedFn,112> methods; };'
    new='struct NativeMethodRow { const GdClassMeta* metadata; const NativePropertyRow* properties; uint64_t type_mask; std::array<NativeResolvedFn,112> methods; };'
    header=replace(header,old,new)
    target_def='inline constexpr std::array<const GdClassMeta*,8> native_type_targets={'+','.join('&META_'+t for t in targets)+'};\n'
    anchor='bool native_resolved_row_matches(const GdObj*,const NativeMethodRow*);'
    header=replace(header,anchor,anchor+'\n'+target_def+INLINE)
    changes[path]=header
    path=native/'gd_rt.hpp';header=path.read_text('utf8')
    anchor='GdVal construct_class(BattleCtx& ctx, const GdClassMeta* cls, const GdVal* args, int argc);'
    header=replace(header,anchor,'GdObj* try_native_allocate_initialized(BattleCtx&,const GdClassMeta*);\n'+anchor)
    changes[path]=header
    path=native/'gd_rt.cpp';runtime=path.read_text('utf8')
    old=design['construct_class_body']
    new=old.replace('    GdObj* obj = cls->alloc_fn(ctx);\n    obj->init_fields(ctx);',
        '    GdObj* obj = try_native_allocate_initialized(ctx,cls);\n    if(!obj) {\n        obj = cls->alloc_fn(ctx);\n        obj->init_fields(ctx);\n    }')
    runtime=replace(runtime,old,new);changes[path]=runtime
    seeded={};is_type_sites=0;hot_gem=0
    pattern=re.compile(r'(static gd::GdObj\* _alloc_(\w+)\(gd::BattleCtx& ctx\) \{ auto\* object=ctx.arena.make<\2>\(&ctx\); if\(ctx.native_resolved_dispatch\)gd::native_resolved_seed\(object,)(\d+)(u\); return object; \})')
    for path in sorted((native/'gen/shards').glob('*.cpp')):
        source=path.read_text('utf8')
        def seed(m):
            assert int(m[3])==old_map[m[2]];seeded[m[2]]=mapping[m[2]]
            return m[1]+str(mapping[m[2]])+m[4]
        source=pattern.sub(seed,source)
        # Generated call sites have an explicit live gd_ctx; the public
        # contextless gd_is_type implementation stays untouched.
        sites=source.count('gd::gd_is_type(');is_type_sites+=sites
        source=source.replace('gd::gd_is_type(','gd::native_inline_is_type(gd_ctx, ')
        old='this->meta()->is_subclass_of(&META_Gd__gd_core_items__Gems__Gem)'
        if old in source:
            hot_gem+=source.count(old)
            source=source.replace(old,'gd::native_inline_self_type(this->rt_ctx_,this,&META_Gd__gd_core_items__Gems__Gem)')
        changes[path]=source
    assert seeded==mapping and is_type_sites>0 and hot_gem==1
    # Check every rewritten generated type query has the expected context scope.
    # Compilation and predicate/constructor tests are still required.
    for path,value in changes.items():path.write_text(value,encoding='utf8',newline='\n')
    result={'status':'implemented_uncompiled_unmeasured','baseline_dll_sha256':'14263d42d22021a83849baffddf2f6288694886f2733a66c0473850b37407548',
        'components':['exact generated metadata/subtype cache','typed default-allocation and init_fields fusion'],
        'method_rows':674,'method_slots':112,'shared_property_rows':14,'type_targets':targets,
        'class_rows':mapping,'type_masks':masks,'type_call_sites':is_type_sites,'hot_gem_predicates':hot_gem,
        'default_initializers_preserved':True,'original_init_call_and_args_preserved':True,
        'object_context_classmeta_layout_changed':False,'numeric_operations_changed':False,
        'source_proof':design}
    prior=json.loads((BASE/'transform.json').read_bytes())
    for key in ('property_rows','class_property_rows','selected_properties'):result[key]=prior[key]
    return result
