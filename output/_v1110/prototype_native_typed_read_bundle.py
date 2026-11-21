"""Replace proven pure getters with typed reads, keeping the original fallbacks."""
import hashlib
import json
from pathlib import Path
import re
from analyze_native_typed_reads import analyze

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'native_perf50/hot_coverage_bundle'
SHA='401376afb48e5340be48578aa534eac0b823a69d3447044639e3d3ee5cb7a259'

INLINE='''#if defined(_MSC_VER)
__forceinline
#elif defined(__GNUC__)
__attribute__((always_inline)) inline
#else
inline
#endif
'''


def replace(text,old,new):
    assert text.count(old)==1,old[:100]
    return text.replace(old,new,1)


def typed_switch(name,symbols,bindings,tag_field):
    lines=[INLINE+f'bool {name}(const NativePropertyRow* row,const GdObj* object,SymId symbol,GdVal& out) {{','    switch(symbol) {']
    for index,(symbol,values) in enumerate(zip(symbols,bindings)):
        lines += [f'        case {symbol}:',f'            switch(row->{tag_field}[{index}]) {{']
        for tag,(owner,field) in enumerate(values,1):
            lines.append(f'                case {tag}: out=static_cast<const {owner}*>(object)->{field};return true;')
        lines += ['                default:return false;','            }']
    lines += ['        default:return false;','    }','}','']
    return '\n'.join(lines)


def optimize(native):
    expected=json.loads((BASE/'source_before_build.json').read_bytes())
    assert expected=={path.relative_to(native).as_posix():hashlib.sha256(path.read_bytes()).hexdigest() for path in native.rglob('*') if path.is_file()}
    design=analyze(native);previous=json.loads((BASE/'transform.json').read_bytes())
    count=len(design['pure_method_slots']);assert count==4
    path=native/'native_resolved_dispatch.hpp';source=path.read_text('utf8')
    start=source.index('static const NativePropertyRow native_property_rows[] = {\n')
    end=source.index('static const NativeMethodRow native_resolved_rows[] = {\n',start)
    rows=re.findall(r'^    \{\{(.*?)\}\},$',source[start:end],re.M)
    assert len(rows)==43
    for text,row in zip(rows,previous['property_rows']):
        cells=[f'&native_resolved_field<{value[0]}, &{value[0]}::{value[1]}>' if value else 'nullptr' for value in row]
        assert ','.join(cells)==text
    lines=['static const std::array<NativePropertyFn,64> native_property_getters[] = {']
    lines += ['    {{'+row+'}},' for row in rows]
    lines += ['};','static const NativePropertyRow native_property_rows[] = {']
    for row in design['read_rows']:
        lines.append('    {{'+','.join(map(str,row['property_tags']))+'},{'+','.join(map(str,row['method_tags']))+'},native_property_getters['+str(row['getter_row'])+'].data()},')
    lines+=['};','']
    source=source[:start]+'\n'.join(lines)+source[end:]
    pattern=re.compile(r'^(    \{&META_(Gd__\w+),&native_property_rows\[)(\d+)(\],\d+ULL,\{)(.*?)(\}\},)$',re.M)
    seen=set()
    def update_row(match):
        cls=match[2];assert match[5]==design['original_method_cells'][cls]
        assert int(match[3])==previous['class_property_rows'][cls];seen.add(cls)
        return match[1]+str(design['class_read_rows'][cls])+match[4]+match[5]+match[6]
    source=pattern.sub(update_row,source);assert len(seen)==674
    # The original slot arrays, class-row indices, methods and seeded allocators
    # remain untouched. These additions happen only after the existing audit.
    method='''    if(row->properties && native_direct_method_field(row->properties,object,method,out)) {
        if(ctx.native_resolved_collect) {
            ++ctx.native_resolved_counts[route<2?route:0];
            if(slot>=112)native_inline_hot_slot_hit(0);
            native_inline_typed_read_hit(1);
        }
        return true;
    }
'''
    source=replace(source,'    const auto function=row->methods[slot];',method+'    const auto function=row->methods[slot];')
    prop='''    if(row->properties && native_direct_property_field(row->properties,object,prop,out)) {
        if(ctx.native_resolved_collect) {
            native_inline_property_hit(0);if(slot>=32)native_inline_hot_slot_hit(1);
            native_inline_typed_read_hit(0);
        }
        return true;
    }
'''
    source=replace(source,'    const auto function=row->properties ? row->properties->getters[slot] : nullptr;',prop+'    const auto function=row->properties ? row->properties->getters[slot] : nullptr;')
    marker='} // namespace gd';assert source.count(marker)==1
    source=source.replace(marker,'static thread_local uint64_t native_typed_read_counts[2]{};\nvoid native_inline_typed_read_hit(unsigned index) {if(index<2)++native_typed_read_counts[index];}\n'+marker,1)
    source+='\nextern "C" uint64_t gd_diag_native_typed_read_stat(unsigned index) {return index<2 ? gd::native_typed_read_counts[index] : 0;}\n'
    path.write_text(source,encoding='utf8',newline='\n')
    path=native/'native_inline_dispatch.hpp';header=path.read_text('utf8')
    old='struct NativePropertyRow { std::array<NativePropertyFn,64> getters; };'
    new='''struct alignas(64) NativePropertyRow {
    std::array<uint8_t,64> property_tags;
    std::array<uint8_t,4> method_tags;
    const NativePropertyFn* getters;
};
static_assert(alignof(NativePropertyRow)==64 && sizeof(NativePropertyRow)==128);
static_assert(offsetof(NativePropertyRow,property_tags)==0);'''
    header=replace(header,old,new)
    owners=sorted({owner for row in design['property_bindings']+design['pure_method_bindings'] for owner,field in row})
    includes='\n'.join(f'#include "gen/hdrs/{owner}.hpp"' for owner in owners)
    for owner in owners:assert 'native_inline_dispatch.hpp' not in (native/f'gen/hdrs/{owner}.hpp').read_text('utf8')
    header=replace(header,'#include <array>','#include <array>\n#include <cstddef>\n'+includes)
    anchor='void native_inline_hot_slot_hit(unsigned);'
    functions='void native_inline_typed_read_hit(unsigned);\n'+typed_switch('native_direct_property_field',design['property_symbols'],design['property_bindings'],'property_tags')
    functions+=typed_switch('native_direct_method_field',design['pure_method_symbols'],design['pure_method_bindings'],'method_tags')
    header=replace(header,anchor,anchor+'\n'+functions)
    prop_inline='''            GdVal direct_out;
            if(row->properties && native_direct_property_field(row->properties,recv.obj,prop,direct_out)) {
                if(ctx.native_resolved_collect) {
                    native_inline_property_hit(0);if(slot>=32)native_inline_hot_slot_hit(1);
                    native_inline_typed_read_hit(0);
                }
                return direct_out;
            }
'''
    header=replace(header,'            const auto function=row->properties ? row->properties->getters[slot] : nullptr;',prop_inline+'            const auto function=row->properties ? row->properties->getters[slot] : nullptr;')
    method_inline='''            GdVal direct_out;
            if(row->properties && native_direct_method_field(row->properties,recv.obj,method,direct_out)) {
                if(ctx.native_resolved_collect) {
                    ++ctx.native_resolved_counts[0];if(slot>=112)native_inline_hot_slot_hit(0);
                    native_inline_typed_read_hit(1);
                }
                return direct_out;
            }
'''
    header=replace(header,'            const auto function=row->methods[slot];',method_inline+'            const auto function=row->methods[slot];')
    path.write_text(header,encoding='utf8',newline='\n')
    result=previous.copy()
    result.update(status='implemented_uncompiled_unmeasured',baseline_dll_sha256=SHA,
        components=['typed pure property reads','typed pure method reads','compact cache-aligned read tags with shared original getter tables'],
        typed_read_design=design,shared_property_rows=len(design['read_rows']),
        class_property_rows=design['class_read_rows'],
        property_rows=[previous['property_rows'][row['getter_row']] for row in design['read_rows']],
        original_getter_table_rows=43,property_row_bytes_before=512,property_row_bytes_after=128,
        original_methods_getters_and_arguments_unchanged=True,object_layout_changed=False,
        unknown_receivers_and_disabled_paths='Original helpers and callbacks, including existing null-cache guards',
        layout_scope='Internal read rows only. GdObj, BattleCtx, ClassMeta and generated class headers unchanged.',
        counter_release_overhead='Additional counts only inside existing diagnostic-collection branches')
    return result
