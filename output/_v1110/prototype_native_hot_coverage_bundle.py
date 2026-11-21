"""Compose retained type/initialization changes with measured dispatch gaps."""
from collections import Counter
import hashlib
import json
from pathlib import Path
import re
from prototype_native_type_constructor_bundle import optimize as retained
from prototype_native_property_control_bundle import property_calls

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'native_perf50/property_control_bundle'
PROFILE=STAGE/'native_perf50/post_property_control_profile'


def replace(text,old,new):
    assert text.count(old)==1,old[:100]
    return text.replace(old,new,1)


def fields_and_calls(native):
    parents={};declared={}
    for path in sorted((native/'gen/hdrs').glob('*.hpp')):
        text=path.read_text('utf8');match=re.search(r'^struct (Gd__\w+) : public ([\w:]+) \{',text,re.M)
        if match:parents[match[1]]=match[2];declared[match[1]]=set(re.findall(r'\bgd::GdVal (f_\w+);',text))
    source='\n'.join(path.read_text('utf8') for path in sorted((native/'gen/shards').glob('*.cpp')))
    own={};case=re.compile(r'^        case ([\w:]+): out = ([^\n]*); return true;\n',re.M)
    for match in re.finditer(r'^bool (Gd__\w+)::get_prop\([^\n]*\n(.*?)^\}',source,re.M|re.S):
        cls,body=match[1],match[2];entries={}
        for item in case.finditer(body):
            field=re.fullmatch(r'this->(f_\w+)',item[2])
            if field:assert field[1] in declared[cls]
            entries[item[1]]=(cls,field[1]) if field else None
        left=case.sub('',body);fallbacks=re.findall(r'return ([\w:]+)::get_prop\(prop, out\);',left)
        parent=parents[cls]
        assert (fallbacks==[parent] if parent in parents else parent=='gd::GdObj' and fallbacks in ([],['gd::GdObj']))
        left=re.sub(r'return [\w:]+::get_prop\(prop, out\);','',left)
        for token in ('switch (prop) {','default: break;','return false;','}'):left=left.replace(token,'')
        assert not left.strip(),cls
        own[cls]=entries
    assert set(own)==set(parents) and len(own)==674
    resolved={}
    def resolve(cls):
        if cls not in resolved:
            parent=parents[cls];row=resolve(parent).copy() if parent in parents else {}
            row.update(own[cls]);resolved[cls]=row
        return resolved[cls]
    for cls in parents:resolve(cls)
    eligible={symbol for row in resolved.values() for symbol,value in row.items() if value and 'resource_path' not in symbol}
    normalized=source.replace('gd::native_inline_get_prop(','gd::get_prop(')
    calls=Counter(symbol for symbol in property_calls(normalized) if symbol in eligible)
    return resolved,calls


def optimize(native):
    result=retained(native)
    plan=json.loads((PROFILE/'hot_slot_gaps.json').read_bytes())
    assert plan['baseline_dll_sha256']==result['baseline_dll_sha256']
    assert plan['profile_sha256']==hashlib.sha256((PROFILE/'profile_depth64.json').read_bytes()).hexdigest()
    old_symbols=plan['original_slot_order_preserved'];new_methods=plan['new_methods']
    assert len(old_symbols)==112 and len(new_methods)==16
    fields,calls=fields_and_calls(native)
    old_props=[row['symbol'] for row in result['selected_properties']]
    extra=[symbol for symbol,count in calls.most_common() if symbol not in old_props][:32]
    properties=old_props+extra;assert len(properties)==64 and len(set(properties))==64
    prop_rows={};class_props={}
    for cls in sorted(fields):
        key=tuple(fields[cls].get(symbol) for symbol in properties)
        previous=result['property_rows'][result['class_property_rows'][cls]]
        assert [list(value) if value else None for value in key[:32]]==previous
        if key not in prop_rows:prop_rows[key]=len(prop_rows)
        class_props[cls]=prop_rows[key]
    path=native/'native_resolved_dispatch.hpp';source=path.read_text('utf8')
    start=source.index('static const NativePropertyRow native_property_rows[] = {\n')
    end=source.index('static const NativeMethodRow native_resolved_rows[] = {\n',start)
    lines=['static const NativePropertyRow native_property_rows[] = {']
    for key in prop_rows:
        cells=[f'&native_resolved_field<{value[0]}, &{value[0]}::{value[1]}>' if value else 'nullptr' for value in key]
        lines.append('    {{'+','.join(cells)+'}},')
    lines+=['};','']
    source=source[:start]+'\n'.join(lines)+source[end:]
    # A formerly unselected method never populated an unknown C++ receiver's
    # cache. Preserve that state before its original virtual callback executes.
    start=source.index('bool try_native_resolved_dispatch(')
    end=source.index('\nstatic thread_local uint64_t native_property_counts',start)
    cold=source[start:end]
    cold=replace(cold,'    const NativeMethodRow* row=object->native_call_row_;',
        '    const NativeMethodRow* row=object->native_call_row_;\n    if(slot>=112 && row==&native_resolved_empty)return false;')
    cold=replace(cold,'        row=native_resolved_exact_row(object);object->native_call_row_=row;',
        '        row=native_resolved_exact_row(object);\n        if(slot>=112 && row==&native_resolved_empty)return false;\n        object->native_call_row_=row;')
    source=source[:start]+cold+source[end:]
    start=source.index('static const NativeMethodRow native_resolved_rows[] = {\n')
    end=source.index('\n};\nstatic const NativeMethodRow native_resolved_empty',start)+len('\n};')
    rows=re.findall(r'^    \{&META_(Gd__\w+),&native_property_rows\[(\d+)\],(\d+)ULL,\{(.*?)\}\},$',source[start:end],re.M)
    assert len(rows)==674
    lines=['static const NativeMethodRow native_resolved_rows[] = {']
    for index,(cls,pid,mask,methods) in enumerate(rows):
        assert result['class_rows'][cls]==index and int(pid)==result['class_property_rows'][cls]
        cells=re.findall(r'&native_resolved_invoke<[^>]+>|nullptr',methods)
        assert len(cells)==112 and ','.join(cells)==methods
        extras=plan['new_rows'][plan['new_class_rows'][cls]]
        assert len(extras)==16
        added=[f'&native_resolved_invoke<{value[0]}, &{value[0]}::fn_{value[1]}>' if value else 'nullptr' for value in extras]
        lines.append(f'    {{&META_{cls},&native_property_rows[{class_props[cls]}],{mask}ULL,{{'+','.join(cells+added)+'}},')
    lines+=['};']
    source=source[:start]+'\n'.join(lines)+source[end:]
    source=replace(source,'    if(ctx.native_resolved_collect)++ctx.native_resolved_counts[route<2?route:0];',
        '    if(ctx.native_resolved_collect) {++ctx.native_resolved_counts[route<2?route:0];if(slot>=112)native_inline_hot_slot_hit(0);}')
    source=replace(source,'    if(ctx.native_resolved_collect)native_inline_property_hit(0);',
        '    if(ctx.native_resolved_collect) {native_inline_property_hit(0);if(slot>=32)native_inline_hot_slot_hit(1);}')
    marker='} // namespace gd';assert source.count(marker)==1
    counters='static thread_local uint64_t native_hot_slot_counts[2]{};\nvoid native_inline_hot_slot_hit(unsigned index) { if(index<2)++native_hot_slot_counts[index]; }\n'
    source=source.replace(marker,counters+marker,1)
    source+='\nextern "C" uint64_t gd_diag_native_hot_slot_stat(unsigned index) { return index<2 ? gd::native_hot_slot_counts[index] : 0; }\n'
    path.write_text(source,encoding='utf8',newline='\n')
    path=native/'native_inline_dispatch.hpp';header=path.read_text('utf8')
    header=replace(header,'std::array<NativeResolvedFn,112> methods','std::array<NativeResolvedFn,128> methods')
    header=replace(header,'std::array<NativePropertyFn,32> getters','std::array<NativePropertyFn,64> getters')
    start=header.index('inline constexpr auto native_resolved_slots=');end=header.index('    return value; }();',start)
    existing=re.findall(r'value\[([\w:]+)\]=(\d+);',header[start:end])
    assert existing==[(symbol,str(index)) for index,symbol in enumerate(old_symbols)]
    header=header[:end]+''.join(f'    value[{row["symbol"]}]={index};\n' for index,row in enumerate(new_methods,112))+header[end:]
    start=header.index('inline constexpr auto native_property_slots=');end=header.index('    return value; }();',start)
    existing=re.findall(r'value\[([\w:]+)\]=(\d+);',header[start:end])
    assert existing==[(symbol,str(index)) for index,symbol in enumerate(old_props)]
    header=header[:end]+''.join(f'    value[{symbol}]={index};\n' for index,symbol in enumerate(extra,32))+header[end:]
    header=replace(header,'void native_inline_property_hit(unsigned);','void native_inline_property_hit(unsigned);\nvoid native_inline_hot_slot_hit(unsigned);')
    header=replace(header,'                if(ctx.native_resolved_collect)native_inline_property_hit(0);',
        '                if(ctx.native_resolved_collect) {native_inline_property_hit(0);if(slot>=32)native_inline_hot_slot_hit(1);}')
    header=replace(header,'                if(ctx.native_resolved_collect)++ctx.native_resolved_counts[0];',
        '                if(ctx.native_resolved_collect) {++ctx.native_resolved_counts[0];if(slot>=112)native_inline_hot_slot_hit(0);}')
    path.write_text(header,encoding='utf8',newline='\n')
    result.update(status='implemented_uncompiled_unmeasured',
        components=result['components']+['16 missing hot method slots','32 additional pure field slots'],
        method_slots=128,property_slots=64,shared_property_rows=len(prop_rows),
        class_property_rows=class_props,property_rows=[[list(value) if value else None for value in key] for key in prop_rows],
        selected_properties=[{'symbol':symbol,'static_property_call_sites':calls[symbol]} for symbol in properties],
        hot_method_additions=new_methods,old112_methods_and32_fields_preserved=True,
        new_method_unknown_cache_unchanged=True,
        counter_release_overhead='Additional counters only inside existing diagnostic-collection branches',
        next_source_reference='Retained7426 components rebuilt together from the deployed1426 source; no candidate binary reuse')
    return result
