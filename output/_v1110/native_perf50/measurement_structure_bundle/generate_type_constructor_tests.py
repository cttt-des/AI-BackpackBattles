import sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[2]))
"""Generate complete inherited GdVal field snapshots for674 generated types."""
import json
from pathlib import Path
import re

WORK=Path(__file__).resolve().parent

def main():
    report=json.loads((WORK/'retained_fixture_transform.json').read_bytes());source=WORK/'bundle_src'
    own={}
    for path in (source/'gen/hdrs').glob('*.hpp'):
        text=path.read_text('utf8');m=re.search(r'^struct (Gd__\w+) : public ([\w:]+) \{',text,re.M)
        if m:own[m[1]]=re.findall(r'\bgd::GdVal (f_\w+);',text)
    assert len(own)==674
    fields={}
    for cls in sorted(own):
        fields[cls]=[(owner,field) for owner in reversed(report['source_proof']['ancestors'][cls]) for field in own[owner]]
    owners=sorted(c for c in own if own[c])
    lines=['#pragma once','#include "native_inline_dispatch.hpp"','#include "gen/class_metas.hpp"']
    lines += [f'#include "gen/hdrs/{cls}.hpp"' for cls in owners]
    lines += ['using ConstructorField=const gd::GdVal* (*)(const gd::GdObj*);',
        'template<class C,gd::GdVal C::*Member>',
        'const gd::GdVal* constructor_field(const gd::GdObj* object) { return &(static_cast<const C*>(object)->*Member); }']
    unique={};class_fields={}
    for cls,row in fields.items():
        key=tuple(row)
        if key not in unique:unique[key]=len(unique)
        class_fields[cls]=unique[key]
    for key,i in unique.items():
        entries=','.join(f'&constructor_field<{owner}, &{owner}::{field}>' for owner,field in key)
        lines.append(f'static constexpr std::array<ConstructorField,{len(key)}> constructor_fields_{i}={{{entries}}};')
    lines+=['struct ConstructorCase { const gd::GdClassMeta* meta; const ConstructorField* fields; size_t count; };',
        'static const ConstructorCase constructor_cases[] = {']
    for cls in sorted(own):
        i=class_fields[cls];lines.append(f'    {{&META_{cls},constructor_fields_{i}.data(),constructor_fields_{i}.size()}},')
    lines+=['};',f'static const auto constructor_case_index=[] {{ std::array<const ConstructorCase*,static_cast<size_t>({report["source_proof"]["last_class_id_symbol"]})+1> value{{}};']
    for i,cls in enumerate(sorted(own)):lines.append(f'    value[CLS_{cls}]=&constructor_cases[{i}];')
    lines += ['    return value; }();','static_assert(std::size(constructor_cases)==674);','']
    (WORK/'native_type_constructor_test_cases.hpp').write_text('\n'.join(lines),encoding='utf8',newline='\n')
    print(f'674 constructor classes, {len(unique)} complete inherited field layouts, '+str(sum(map(len,fields.values())))+' fields; includes shadowed parent fields')

if __name__=='__main__':main()
