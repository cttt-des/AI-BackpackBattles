"""Generate field-reference fixtures; original virtual getters remain the oracle."""
import json
from pathlib import Path

WORK=Path(__file__).resolve().parent

def main():
    report=json.loads((WORK/'retained_fixture_transform.json').read_bytes())
    rows=report['property_rows'];owners=sorted({v[0] for row in rows for v in row if v})
    lines=['#pragma once','#include "native_inline_dispatch.hpp"','#include "gen/class_metas.hpp"']
    lines += [f'#include "gen/hdrs/{owner}.hpp"' for owner in owners]
    lines += ['using PropertyTestRef=gd::GdVal* (*)(gd::GdObj*);',
        'template<class C,gd::GdVal C::*Member>',
        'gd::GdVal* property_test_ref(gd::GdObj* object) { return &(static_cast<C*>(object)->*Member); }',
        'struct PropertyTestRow { std::array<PropertyTestRef,64> refs; };',
        'static const PropertyTestRow property_test_rows[] = {']
    for row in rows:
        cells=[f'&property_test_ref<{v[0]}, &{v[0]}::{v[1]}>' if v else 'nullptr' for v in row]
        lines.append('    {{'+','.join(cells)+'}},')
    lines+=['};','struct PropertyTestClass { const gd::GdClassMeta* meta; const PropertyTestRow* row; };',
        'static const PropertyTestClass property_test_classes[] = {']
    for cls,pid in sorted(report['class_property_rows'].items()):
        lines.append(f'    {{&META_{cls},&property_test_rows[{pid}]}},')
    lines+=['};','static constexpr gd::SymId property_test_symbols[] = {']
    lines += ['    '+p['symbol']+',' for p in report['selected_properties']]
    lines+=['};','static_assert(std::size(property_test_classes)==674);','']
    (WORK/'native_property_test_cases.hpp').write_text('\n'.join(lines),encoding='utf8',newline='\n')
    print(f'Generated674 classes,64 columns,{len(rows)} reference rows,{len(owners)} field owners; original get_prop verifies each assignment')

if __name__=='__main__':main()
