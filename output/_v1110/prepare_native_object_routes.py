"""Generate object-only routes from measured types and pure original switches."""
import hashlib
import json
from pathlib import Path
import re
import shutil
from analyze_native_dispatch import analyze

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/callback_dispatch_bundle'
WORK=STAGE/'native_perf50/object_routes_prototype'
EXPECTED='80a0681c1c93268af2b29c21e5439b6444de36a29ad39486b3f4afadf548a44a'
ARCHIVE='72dd9c1575087596ad0409b939104a0113033e40'
STATIC='SYM_GEN__nativeF32_1502'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def once(text,old,new):
    assert text.count(old)==1,(old[:90],text.count(old));return text.replace(old,new,1)

HELPER=r'''
bool native_try_object_route(BattleCtx& ctx,GdObj* object,SymId method,
        const GdVal* args,int count,GdVal& out) {
    if(!ctx.native_resolved_dispatch || !object || method>=native_object_route_slots.size())return false;
    const int slot=native_object_route_slots[method];if(slot<0)return false;
    const auto first=reinterpret_cast<uintptr_t>(native_resolved_rows);
    const auto selected=reinterpret_cast<uintptr_t>(object->native_call_row_);
    if(selected<first || selected-first>=sizeof(native_resolved_rows) ||
       (selected-first)%sizeof(NativeMethodRow))return false;
    const auto index=(selected-first)/sizeof(NativeMethodRow);
    // Cached row metadata alone never proves a C++ dynamic type.
    if(native_extra_callback_rows[index].exact_type!=&typeid(*object))return false;
    const auto function=native_object_route_rows[index][slot];if(!function)return false;
    if(ctx.native_resolved_collect)++native_object_route_counts[slot==96?1:0];
    // Pass the original caller context, argument pointer and count unchanged.
    out=function(object,ctx,args,count);return true;
}
}
extern "C" uint64_t gd_diag_native_object_route_stat(unsigned i){return i<2?gd::native_object_route_counts[i]:0;}
'''

def plan(native):
    scope=json.loads((WORK/'route_scope_analysis.json').read_bytes())
    probe=json.loads((WORK/'object_route_probe.json').read_bytes())
    assert scope['baseline_dll_sha256']==probe['baseline_dll_sha256']==EXPECTED and probe['passed']
    assert scope['probe_receipt_sha256']==sha(WORK/'object_route_probe.json')
    selected=[r['symbol'] for r in scope['top_methods'][:96]]
    assert len(selected)==len(set(selected))==96 and STATIC not in selected
    old=(native/'native_inline_dispatch.hpp').read_text('utf8')
    assigned=set(re.findall(r'value\[(SYM_\w+)\]=\d+;',old.split('inline constexpr auto native_resolved_slots=',1)[1].split('}();',1)[0]))
    assert not (set(selected)|{STATIC})&assigned
    profile=json.loads((ACCEPTED/'profile_depth64.json').read_bytes())
    design=analyze(native,profile,limit=0,extra_symbols=selected)
    assert design['generated_classes']==design['pure_dispatch_classes']==design['eligible_classes_with_pure_inheritance']==674
    assert [r['symbol'] for r in design['selected_methods']]==selected
    resolved=(native/'native_resolved_dispatch.hpp').read_text('utf8')
    primary=resolved.split('static const NativeMethodRow native_resolved_rows[] = {',1)[1].split('\n};',1)[0]
    classes=re.findall(r'^    \{&META_(Gd__\w+),',primary,re.M)
    registrations=re.findall(r'value.emplace\(&typeid\((Gd__\w+)\),&native_resolved_rows\[(\d+)\]\);',resolved)
    assert len(classes)==len(registrations)==674 and all(classes[int(i)]==c for c,i in registrations)
    extra=resolved.split('static const NativeExtraCallbackRow native_extra_callback_rows[] = {',1)[1].split('\n};',1)[0]
    assert re.findall(r'^    \{&typeid\((Gd__\w+)\)',extra,re.M)==classes
    sources='\n'.join(p.read_text('utf8') for p in sorted((native/'gen/shards').glob('*.cpp')))
    signature='gd::GdVal Gd__gd_core__CoreContext::sf__nativeF32(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {'
    body=sources.split(signature,1)[1].split('\n}',1)[0]
    assert body=='\n    (void)gd_ctx;\n    const auto value = gd::gd_coerce_float(_argc > 0 ? _args[0] : gd::GdVal::null());\n    return gd::GdVal::from_float(static_cast<double>(static_cast<float>(value.as_float())));'
    context_switch=re.search(r'^bool Gd__gd_core__CoreContext::call_method\([^\n]*\n(.*?)^\}',sources,re.M|re.S)[1]
    assert f'case {STATIC}: out = sf__nativeF32(gd_ctx, args, argc); return true;' in context_switch
    rows=[design['resolved_rows'][design['class_rows'][c]] for c in classes]
    assert sum(r['count'] for r in probe['rows'] if r['method']==STATIC and r['receiver_cpp_type']=='24Gd__gd_core__CoreContext' and r['canonical_exact_row_index'] is not None)==88491
    return dict(selected=selected,static_symbol=STATIC,classes=classes,rows=rows,analysis=design,
        measured_eligible_instance_calls=901392,measured_static_context_calls=88491,
        static_original_body_sha256=hashlib.sha256(body.encode()).hexdigest(),all_selected_old_slots_negative=True)

def transform(native):
    design=plan(native);symbols=design['selected'];classes=design['classes']
    lines=['\nnamespace gd {','using NativeObjectRouteFn=GdVal(*)(GdObj*,BattleCtx&,const GdVal*,int);',
        'template<class T,auto Method> static GdVal native_object_route_member(GdObj* object,BattleCtx&,const GdVal* args,int count) {',
        '    return (static_cast<T*>(object)->*Method)(args,count);','}',
        'static GdVal native_object_route_f32(GdObj*,BattleCtx& ctx,const GdVal* args,int count) {',
        '    return Gd__gd_core__CoreContext::sf__nativeF32(ctx,args,count);','}',
        'static constexpr auto native_object_route_slots=[] {',
        '    std::array<int8_t,native_resolved_slots.size()> slots{};slots.fill(-1);']
    for i,s in enumerate([*symbols,STATIC]):lines.append(f'    slots[{s}]={i};')
    lines+=['    return slots;','}();']
    for s in [*symbols,STATIC]:lines.append(f'static_assert(native_resolved_slots[{s}]<0);')
    lines.append('static const std::array<NativeObjectRouteFn,97> native_object_route_rows[] = {')
    for cls,row in zip(classes,design['rows']):
        cells=[f'&native_object_route_member<{c[0]},&{c[0]}::fn_{c[1]}>' if c else 'nullptr' for c in row]
        cells.append('&native_object_route_f32' if cls=='Gd__gd_core__CoreContext' else 'nullptr')
        lines.append('    {'+','.join(cells)+'},')
    lines+=['};','static_assert(std::size(native_object_route_rows)==std::size(native_resolved_rows));',
        'static thread_local uint64_t native_object_route_counts[2]{};']
    path=native/'native_resolved_dispatch.hpp'
    with path.open('a',encoding='utf8',newline='\n') as stream:stream.write('\n'.join(lines)+'\n'+HELPER)
    path=native/'gd_rt.cpp';text=path.read_text('utf8')
    marker='bool native_try_extra_callback(BattleCtx&,GdObj*,SymId,const GdVal*,int,GdVal&);'
    text=once(text,marker,marker+'\nbool native_try_object_route(BattleCtx&,GdObj*,SymId,const GdVal*,int,GdVal&);')
    marker='            if (recv.obj->call_method(ctx, m, args, argc, out)) return out;'
    text=once(text,marker,'            if (native_try_object_route(ctx,recv.obj,m,args,argc,out)) return out;\n'+marker)
    path.write_text(text,encoding='utf8',newline='\n')
    return dict(component='96 measured object instance routes plus original static context float conversion',
        selected_symbols=[*symbols,STATIC],source_proof_classes=674,slots=97,
        original128_rows_and65_callback_routes_unchanged=True,actual_cpp_type_always_checked=True,
        original_object_observation_once_and_original_caller_context=True,
        no_lazy_row_seed_and_no_old_counter_changes=True,not_used_for_funcref_or_literal_entries=True,
        original_method_bodies_rng_fenv_argument_pointer_and_order_retained=True,
        measured_candidate_instance_calls=901392,measured_candidate_static_calls=88491)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    backup=json.loads((ACCEPTED/'checkpoint_receipt.json').read_bytes())
    assert backup['remote_upload_verified'] and backup['remote_verified_commit']==ARCHIVE
    source=WORK/'prototype_src';assert not source.exists()
    shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    before={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    proof=plan(source);(WORK/'object_routes_source_proof.json').write_text(json.dumps(proof,indent=2)+'\n',encoding='utf8')
    component=transform(source)
    after={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    changed=sorted(n for n in before if before[n]!=after[n]);assert changed==['gd_rt.cpp','native_resolved_dispatch.hpp']
    (WORK/'transform.json').write_text(json.dumps(dict(baseline_dll_sha256=EXPECTED,verified_backup=ARCHIVE,
        source_sha256=after,modified_files=changed,component=component,source_proof_sha256=sha(WORK/'object_routes_source_proof.json'),
        not_for_deployment=True),indent=2)+'\n',encoding='utf8')
    print(json.dumps(dict(methods=97,classes=674,source_changes=changed,counts_not_speed=True)))

if __name__=='__main__':main()
