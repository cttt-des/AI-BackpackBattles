"""Direct observed, previously uncached callbacks without changing public layouts."""
import hashlib
import json
from pathlib import Path
import re
import shutil
from analyze_native_dispatch import analyze

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/literal_spans_bundle'
COUNT=STAGE/'native_perf50/bound_callbacks_prototype'
WORK=STAGE/'native_perf50/callback_dispatch_prototype'
EXPECTED='c46cc19c06fb3c424a470f04bb7a0ef5acf8b7ff01caaccd5f41a5c44d955ee1'
ARCHIVE='a27d289f2009c3ad42145d61334d50647b2c060f'

def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def once(text,old,new):
    assert text.count(old)==1,(old[:90],text.count(old))
    return text.replace(old,new,1)

HELPER=r'''
// Additional callback routes have their own side table. The original128-slot
// row, object layouts, cache state and legacy diagnostic totals stay unchanged.
static thread_local uint64_t native_extra_callback_counts[2]{};
static NativeResolvedFn native_extra_callback_function(BattleCtx& ctx,GdObj* object,SymId method) {
    if(!ctx.native_resolved_dispatch || !object || method>=native_extra_callback_slots.size())return nullptr;
    const int slot=native_extra_callback_slots[method];if(slot<0)return nullptr;
    const auto first=reinterpret_cast<uintptr_t>(native_resolved_rows);
    const auto selected=reinterpret_cast<uintptr_t>(object->native_call_row_);
    if(selected<first || selected-first>=sizeof(native_resolved_rows) ||
       (selected-first)%sizeof(NativeMethodRow))return nullptr;
    const auto index=(selected-first)/sizeof(NativeMethodRow);
    const auto& row=native_extra_callback_rows[index];
    // Always validate the actual C++ type, including when audit is disabled.
    // A subclass with shared metadata or a copied/corrupt row keeps virtual dispatch.
    if(row.exact_type!=&typeid(*object))return nullptr;
    return row.methods[slot];
}
bool native_try_extra_callback(BattleCtx& ctx,GdObj* object,SymId method,
        const GdVal* args,int count,GdVal& out) {
    const auto function=native_extra_callback_function(ctx,object,method);
    if(!function)return false;
    if(ctx.native_resolved_collect)++native_extra_callback_counts[0];
    out=function(object,args,count);return true;
}
bool native_try_literal_extra_callback(BattleCtx& ctx,const GdVal& value,
        const GdVal* args,int count,GdVal& out) {
    if(value.kind!=GdVal::Kind::FuncRef || !value.fr)return false;
    const auto* reference=value.fr;
    if(!reference->instance || reference->method==SYM_NONE ||
       (reference->binds && reference->binds->len))return false;
    auto* object=reference->instance;
    const auto function=native_extra_callback_function(ctx,object,reference->method);
    if(!function)return false;
    // This route was formerly rejected before audit by the old flat dispatcher.
    // The exact generated receiver has a real non-null row metadata pointer;
    // observe_object therefore cannot mutate either the reference or arguments.
    native_timer_observe_object(ctx,object);
    if(ctx.native_resolved_collect)++native_extra_callback_counts[1];
    out=function(object,args,count);return true;
}
} // namespace gd
extern "C" uint64_t gd_diag_native_extra_callback_stat(unsigned i){return i<2?gd::native_extra_callback_counts[i]:0;}
'''

def plan(native):
    probe=json.loads((COUNT/'bound_argument_probe.json').read_bytes())
    assert probe['passed'] and probe['baseline_dll_sha256']==EXPECTED
    assert probe['calls']==probe['unbound_slow_calls']==101340 and probe['heap_bound_concatenations']==0
    builtins=(native/'builtin_syms.hpp').read_text('utf8')
    first_gen=len(re.findall(r'X\((SYM_\w+),',builtins))+2
    gen=re.findall(r'^\s+(SYM_GEN_\w+),\s*$',(native/'gen/sym_ids.hpp').read_text('utf8'),re.M)
    symbols={first_gen+i:name for i,name in enumerate(gen)}
    inline=(native/'native_inline_dispatch.hpp').read_text('utf8')
    block=inline.split('inline constexpr auto native_resolved_slots=',1)[1].split('    return value; }();',1)[0]
    primary=set(re.findall(r'value\[([\w:]+)\]=\d+;',block));assert len(primary)==128
    selected=[symbols[int(i)] for i in probe['slow_method_symbols'] if symbols[int(i)] not in primary]
    selected.sort(key=lambda s:next(i for i,n in symbols.items() if n==s))
    assert selected and len(selected)<128
    profile=json.loads((ACCEPTED/'profile_depth64.json').read_bytes())
    design=analyze(native,profile,limit=0,extra_symbols=selected)
    assert design['generated_classes']==design['pure_dispatch_classes']==design['eligible_classes_with_pure_inheritance']==674
    assert [row['symbol'] for row in design['selected_methods']]==selected
    resolved=(native/'native_resolved_dispatch.hpp').read_text('utf8')
    primary_table=resolved.split('static const NativeMethodRow native_resolved_rows[] = {',1)[1].split('\n};',1)[0]
    classes=re.findall(r'^    \{&META_(Gd__\w+),',primary_table,re.M)
    registrations=re.findall(r'value.emplace\(&typeid\((Gd__\w+)\),&native_resolved_rows\[(\d+)\]\);',resolved)
    assert len(classes)==len(registrations)==674 and all(classes[int(i)]==cls for cls,i in registrations)
    rows=[]
    for cls in classes:rows.append(design['resolved_rows'][design['class_rows'][cls]])
    # Reuse the original exact signatures audit. Every canonical method consumes
    # argument cells by value; the seven additional accesses consume scalars.
    signatures=copies=0;other=[]
    for path in sorted((native/'gen/shards').glob('*.cpp')):
        for line in path.read_text('utf8').splitlines():
            if not re.search(r'\b_args\b',line):continue
            if re.match(r'^gd::GdVal \w+::(?:fn|sf)_\w+\(.*const gd::GdVal\* _args, int _argc\) \{$',line):signatures+=1
            elif re.match(r'^\s*gd::GdVal lv_\w+ = \(_argc > \d+\) \? _args\[\d+\] : .*;\s*$',line):copies+=1
            else:other.append(line)
    assert signatures==4992 and copies==3268 and len(other)==7
    assert all('gd_coerce_float' in line or '.as_int()' in line for line in other)
    runtime=(native/'gd_rt.cpp').read_text('utf8')
    assert 'return (row && row->metadata) || native_resolved_exact_row(object)!=&native_resolved_empty;' in runtime
    assert '''    if(w.closed_world)return;
    if(w.enabled && w.usable && object && object!=w.trusted_hooks && !native_timer_known_object(object)) {''' in runtime
    return dict(selected=selected,classes=classes,rows=rows,analysis=design,
        observed_unbound_slow_calls=probe['unbound_slow_calls'],observed_bound_concatenations=0,
        generated_argument_signatures=signatures,argument_value_copies=copies,remaining_scalar_reads=other)

def transform(native):
    design=plan(native);symbols=design['selected'];classes=design['classes']
    lines=['\nnamespace gd {',
        'static constexpr auto native_extra_callback_slots=[] {',
        '    std::array<int8_t,native_resolved_slots.size()> slots{};slots.fill(-1);']
    for i,symbol in enumerate(symbols):lines.append(f'    slots[{symbol}]={i};')
    lines+=['    return slots;','}();']
    for symbol in symbols:lines.append(f'static_assert(native_resolved_slots[{symbol}]<0);')
    lines.append(f'struct NativeExtraCallbackRow {{const std::type_info* exact_type;std::array<NativeResolvedFn,{len(symbols)}> methods;}};')
    lines.append('static const NativeExtraCallbackRow native_extra_callback_rows[] = {')
    for cls,row in zip(classes,design['rows']):
        functions=[f'&native_resolved_invoke<{cell[0]},&{cell[0]}::fn_{cell[1]}>' if cell else 'nullptr' for cell in row]
        lines.append('    {&typeid('+cls+'),{'+','.join(functions)+'}},')
    lines+=['};','static_assert(std::size(native_extra_callback_rows)==std::size(native_resolved_rows));']
    path=native/'native_resolved_dispatch.hpp'
    with path.open('a',encoding='utf8',newline='\n') as stream:stream.write('\n'.join(lines)+'\n'+HELPER)
    path=native/'gd_rt.cpp';text=path.read_text('utf8')
    marker='\nnamespace gd {'
    text=once(text,marker+'\n\nstruct FastInternedSymbol {',marker+'\nbool native_try_extra_callback(BattleCtx&,GdObj*,SymId,const GdVal*,int,GdVal&);\n\nstruct FastInternedSymbol {')
    old='''    } else {
        if (!try_native_resolved_dispatch(ctx,instance,method,args,argc,out,1))
            instance->call_method(ctx, method, args, argc, out);
    }
    return out;
}

GdVal GdFuncRef::call_funcv'''
    new='''    } else {
        if (!try_native_resolved_dispatch(ctx,instance,method,args,argc,out,1) &&
            !native_try_extra_callback(ctx,instance,method,args,argc,out))
            instance->call_method(ctx, method, args, argc, out);
    }
    return out;
}

GdVal GdFuncRef::call_funcv'''
    text=once(text,old,new);path.write_text(text,encoding='utf8',newline='\n')
    path=native/'native_event_kernel.hpp';text=path.read_text('utf8')
    text=once(text,'namespace gd { bool native_literal_canonical_row(const NativeMethodRow*); }',
        'namespace gd { bool native_literal_canonical_row(const NativeMethodRow*);\nbool native_try_literal_extra_callback(BattleCtx&,const GdVal&,const GdVal*,int,GdVal&); }')
    anchor='''            if(gd::native_try_flat_funcref(ctx,receiver,gd::GdVal::from_arr(&borrowed),out))return out;
            // A failed audit may have observable effects. Do not audit twice.'''
    text=once(text,anchor,'''            if(gd::native_try_flat_funcref(ctx,receiver,gd::GdVal::from_arr(&borrowed),out))return out;
            if(gd::native_try_literal_extra_callback(ctx,receiver,data,count,out))return out;
            // A failed audit may have observable effects. Do not audit twice.''')
    path.write_text(text,encoding='utf8',newline='\n')
    return dict(component='exact-type side table for observed uncached unbound callbacks, including private literal spans',
        selected_callback_symbols=symbols,classes=674,pure_inheritance_and_switches=674,
        side_table_cells=674*len(symbols),original128_slot_rows_unchanged=True,
        selected_methods_previously_rejected_before_audit=True,legacy_six_counters_unchanged=True,
        actual_cpp_type_always_checked_without_metadata_callbacks=True,
        null_copied_wrong_unknown_rows_and_cpp_overrides_fall_back=True,
        unbound_only_bound_vector_original_unchanged=True,
        original_observation_preserved_and_known_receiver_proof=True,
        original_arithmetic_rng_target_bodies_unchanged=True,
        raw_argument_non_escape_proof=design['generated_argument_signatures'],
        observed_slow_unbound_calls=101340,observed_bound_concatenations=0)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    receipt=json.loads((ACCEPTED/'checkpoint_receipt.json').read_bytes())
    assert receipt['remote_upload_verified'] and receipt['remote_verified_commit']==ARCHIVE
    assert not WORK.exists();WORK.mkdir()
    source=WORK/'prototype_src'
    shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    before={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    original_plan=plan(source)
    (WORK/'callback_source_proof.json').write_text(json.dumps(original_plan,indent=2)+'\n',encoding='utf8')
    design=transform(source)
    after={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    changed=sorted(name for name in before if before[name]!=after[name])
    assert changed==['gd_rt.cpp','native_event_kernel.hpp','native_resolved_dispatch.hpp']
    (WORK/'transform.json').write_text(json.dumps(dict(baseline_dll_sha256=EXPECTED,
        verified_backup=ARCHIVE,source_sha256=after,modified_files=changed,component=design,
        source_proof_sha256=sha(WORK/'callback_source_proof.json'),not_for_deployment=True),indent=2)+'\n',encoding='utf8')
    print(json.dumps(dict(selected_symbols=len(design['selected_callback_symbols']),pure_generated_classes=674,
        source_changes=changed,no_layout_change=True,no_speed_claim=True)))

if __name__=='__main__':main()
