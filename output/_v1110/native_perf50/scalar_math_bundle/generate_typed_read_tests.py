"""Reference actual fields and compare pure reads with original virtual methods."""
import json
from pathlib import Path

WORK=Path(__file__).resolve().parent


def main():
    design=json.loads((WORK/'transform.json').read_bytes())['typed_read_design']
    slots=design['pure_method_slots'];bindings=design['class_method_bindings']
    owners=sorted({value[0] for row in bindings.values() for slot in slots if (value:=row[slot])})
    lines=['#pragma once','#include "native_inline_dispatch.hpp"','#include "gen/class_metas.hpp"']
    lines += [f'#include "gen/hdrs/{owner}.hpp"' for owner in owners]
    lines += ['using TypedReadRef=gd::GdVal* (*)(gd::GdObj*);',
        'template<class C,gd::GdVal C::*Member>',
        'gd::GdVal* typed_read_ref(gd::GdObj* object){return &(static_cast<C*>(object)->*Member);}',
        f'struct TypedReadRefs {{ std::array<TypedReadRef,{len(slots)}> values; }};']
    rows={};classes={}
    for cls in sorted(bindings):
        key=tuple(tuple(bindings[cls][slot]) if bindings[cls][slot] else None for slot in slots)
        if key not in rows:rows[key]=len(rows)
        classes[cls]=rows[key]
    lines += ['static const TypedReadRefs typed_read_refs[] = {']
    for row in rows:
        cells=[f'&typed_read_ref<{value[0]},&{value[0]}::{value[1]}>' if value else 'nullptr' for value in row]
        lines.append('    {{'+','.join(cells)+'}},')
    lines += ['};','struct TypedReadClass {const gd::GdClassMeta* meta;const TypedReadRefs* refs;};',
        'static const TypedReadClass typed_read_classes[] = {']
    lines += [f'    {{&META_{cls},&typed_read_refs[{row}]}},' for cls,row in classes.items()]
    lines += ['};','static constexpr gd::SymId typed_read_methods[] = {']
    lines += [f'    {symbol},' for symbol in design['pure_method_symbols']]
    lines += ['};','static_assert(std::size(typed_read_classes)==674);','']
    (WORK/'native_typed_read_test_cases.hpp').write_text('\n'.join(lines),encoding='utf8',newline='\n')
    print(f'674 classes, {len(slots)} method columns, {len(rows)} independent field-reference rows')


if __name__=='__main__':main()
