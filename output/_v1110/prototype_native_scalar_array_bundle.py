"""Inline exact same-kind scalar equality and Array/Int writes only."""
import hashlib
import json
from pathlib import Path
import re

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'native_perf50/dispatch_array_bundle'
HEADER='''#pragma once
#include "gd_rt.hpp"
namespace gd {
inline bool native_scalar_eq(const GdVal& a,const GdVal& b) {
    if(a.kind==b.kind) {
        switch(a.kind) {
            case GdVal::Kind::Null:return true;
            case GdVal::Kind::Bool:return a.b==b.b;
            case GdVal::Kind::Int:return a.i==b.i;
            case GdVal::Kind::Float:return a.f==b.f;
            default:break;
        }
    }
    return gd::gd_eq(a,b);
}
inline bool native_scalar_ne(const GdVal& a,const GdVal& b) {
    return !native_scalar_eq(a,b);
}
} // namespace gd
'''
WRITE='''inline void native_array_set_index(BattleCtx& ctx,GdVal& recv,const GdVal& key,const GdVal& value) {
    if(recv.kind==GdVal::Kind::Arr && recv.arr && key.kind==GdVal::Kind::Int) {
        int64_t index=key.i;
        if(index<0)index+=static_cast<int64_t>(recv.arr->len);
        if(index<0 || static_cast<uint64_t>(index)>=recv.arr->len)return;
        recv.arr->data[index]=value;return;
    }
    gd::set_index(ctx,recv,key,value);
}
'''
TOKEN=re.compile(r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|gd::(?:gd_eq|gd_ne|set_index)(?=\s*\()')

def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def optimize(native):
    before=json.loads((BASE/'source_before_build.json').read_bytes())
    actual={p.relative_to(native).as_posix():digest(p) for p in native.rglob('*') if p.is_file()}
    assert actual==before,'Use all accepted baseline source/config files'
    assert not (native/'native_scalar_equal.hpp').exists()
    (native/'native_scalar_equal.hpp').write_text(HEADER,encoding='utf8',newline='\n')
    path=native/'native_array_index.hpp';text=path.read_text('utf8')
    anchor='} // namespace gd\n';assert text.count(anchor)==1
    path.write_text(text.replace(anchor,WRITE+anchor),encoding='utf8',newline='\n')
    names={'gd::gd_eq':'gd::native_scalar_eq','gd::gd_ne':'gd::native_scalar_ne','gd::set_index':'gd::native_array_set_index'}
    sites={}
    for path in sorted((native/'gen/shards').glob('*.cpp')):
        counts=dict.fromkeys(names,0)
        def rewrite(match):
            if match[0] in names:counts[match[0]]+=1;return names[match[0]]
            return match[0]
        text=TOKEN.sub(rewrite,path.read_text('utf8'))
        assert sum(counts.values())>0
        text='#include "../../native_scalar_equal.hpp"\n'+text
        path.write_text(text,encoding='utf8',newline='\n')
        sites[path.relative_to(native).as_posix()]=counts
    totals={key:sum(row[key] for row in sites.values()) for key in names}
    assert all(value>0 for value in totals.values())
    report={'baseline_dll_sha256':'0904c29d124d7f8e4a97a2ed6a73f7e006d07ee63552fecda3ed064d0427b4f3',
        'comparison_fast_cases':['Null/Null','Bool/Bool','Int/Int (exact int64 equality)','Float/Float (original native double equality)'],
        'mixed_and_container_comparisons':'unchanged gd_eq fallback, including mixed numeric coercion, strings, arrays and object identity',
        'write_fast_case':'nonnull Array receiver and Int key; exact original bounds/negative-index/data assignment',
        'write_fallback':'unchanged set_index, including dictionary and custom object property writes',
        'arithmetic_rng_ordering':'No gd_lt/le/gt/ge, arithmetic, RNG or frame changes; same argument expressions and call shape',
        'sites':sites,'totals':totals,'object_layout_changed':False,'full_rebuild_required':True}
    print('Scalar equality and array write sites:',totals,flush=True)
    return report
