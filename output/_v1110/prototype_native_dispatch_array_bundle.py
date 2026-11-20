"""Expand proven exact-type dispatch and inline only Array/Int indexing."""
import hashlib
import json
from pathlib import Path
import re
from analyze_native_dispatch import analyze

STAGE=Path(__file__).resolve().parent
PREVIOUS=STAGE/'native_perf50/resolved_dispatch_a'
PROFILE=STAGE/'native_perf50/post_resolved_profile'

ARRAY_HEADER='''#pragma once
#include "gd_rt.hpp"
namespace gd {
inline GdVal native_array_index(BattleCtx& ctx,const GdVal& recv,const GdVal& key) {
    if(recv.kind==GdVal::Kind::Arr && recv.arr && key.kind==GdVal::Kind::Int) {
        int64_t index=key.i;
        if(index<0)index+=static_cast<int64_t>(recv.arr->len);
        if(index<0 || static_cast<uint64_t>(index)>=recv.arr->len)return GdVal::null();
        return recv.arr->data[index];
    }
    return gd::get_index(ctx,recv,key);
}
} // namespace gd
'''

# Generated shards contain ordinary quoted strings, character literals, and comments.
# Match those whole before looking for a call; never rewrite their contents.
TOKEN=re.compile(r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|gd::get_index(?=\s*\()')

def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def optimize(native):
    expected=json.loads((PREVIOUS/'source_before_build.json').read_bytes())
    current={p.relative_to(native).as_posix():digest(p) for p in native.rglob('*') if p.is_file()}
    assert current==expected,'Start with the entire accepted source inventory'
    selected=json.loads((PROFILE/'expanded_dispatch_design.json').read_bytes())
    symbols=[row['symbol'] for row in selected['selected_methods']]
    design=analyze(native,json.loads((PROFILE/'profile_depth64.json').read_bytes()),limit=0,extra_symbols=symbols)
    assert design['selected_methods']==selected['selected_methods']
    assert design['resolved_rows']==selected['resolved_rows'] and design['class_rows']==selected['class_rows']
    assert design['generated_classes']==design['eligible_classes_with_pure_inheritance']==674
    slots=len(symbols);assert slots==112 and slots<=128
    path=native/'native_resolved_dispatch.hpp';text=path.read_text('utf8')
    old='std::array<NativeResolvedFn,48>';assert text.count(old)==1
    text=text.replace(old,f'std::array<NativeResolvedFn,{slots}>',1)
    start=text.index('static const NativeMethodRow native_resolved_rows[] = {\n')
    end=text.index('};\nstatic const NativeMethodRow native_resolved_empty{};',start)
    lines=['static const NativeMethodRow native_resolved_rows[] = {']
    for row in design['resolved_rows']:
        values=[f'&native_resolved_invoke<{v[0]}, &{v[0]}::fn_{v[1]}>' if v else 'nullptr' for v in row]
        lines.append('    {{'+','.join(values)+'}},')
    text=text[:start]+'\n'.join(lines)+'\n'+text[end:]
    text,count=re.subn(r'    value\[[\w:]+\]=\d+;\n','',text)
    assert count==48
    anchor='    return value; }();';assert text.count(anchor)==1
    text=text.replace(anchor,''.join(f'    value[{symbol}]={i};\n' for i,symbol in enumerate(symbols))+anchor,1)
    pattern=re.compile(r'value\.emplace\(&typeid\((Gd__\w+)\),&native_resolved_rows\[\d+\]\);')
    def registry(m):return f'value.emplace(&typeid({m[1]}),&native_resolved_rows[{design["class_rows"][m[1]]}]);'
    text,count=pattern.subn(registry,text);assert count==674
    path.write_text(text,encoding='utf8',newline='\n')
    assert not (native/'native_array_index.hpp').exists()
    (native/'native_array_index.hpp').write_text(ARRAY_HEADER,encoding='utf8',newline='\n')
    site_counts={}
    for path in sorted((native/'gen/shards').glob('*.cpp')):
        source=path.read_text('utf8');count=0
        def rewrite(match):
            nonlocal count
            if match[0]=='gd::get_index':count+=1;return 'gd::native_array_index'
            return match[0]
        result=TOKEN.sub(rewrite,source)
        assert count>0,path
        result='#include "../../native_array_index.hpp"\n'+result
        path.write_text(result,encoding='utf8',newline='\n')
        site_counts[path.relative_to(native).as_posix()]=count
    assert len(site_counts)==16
    design.update({'array_index_sites':site_counts,'total_array_index_sites':sum(site_counts.values()),
        'object_layout_changed':False,'full_rebuild_required':True,
        'array_fast_case':'Array with nonnull pointer and Int key only; exact original bounds and negative-index rules',
        'all_other_index_cases':'Original gd::get_index unchanged',
        'counter_overhead':'No new per-index runtime counters',
        'arithmetic_rng_argument_binds':'unchanged'})
    print(f'Expanded {slots} method slots; {len(design["resolved_rows"])} rows; {sum(site_counts.values())} index call sites',flush=True)
    return design
