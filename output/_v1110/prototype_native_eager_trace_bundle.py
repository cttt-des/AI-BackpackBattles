"""Compose eager exact-row allocation and pure dead diagnostic construction."""
import hashlib
import json
from pathlib import Path
import re
from prototype_native_addspeed_trace import optimize as trace
STAGE=Path(__file__).resolve().parent
BASE=STAGE/'native_perf50/scan_bundle'

def replace(text,old,new):
    assert text.count(old)==1,old[:100]
    return text.replace(old,new,1)

def optimize(native):
    expected=json.loads((BASE/'source_before_build.json').read_bytes())
    assert expected=={p.relative_to(native).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in native.rglob('*') if p.is_file()},'Start from accepted7af, with original dense timer traversal and layouts'
    path=native/'gd_rt.hpp';text=path.read_text('utf8')
    anchor='bool try_native_resolved_dispatch(BattleCtx&,GdObj*,SymId,const GdVal*,int,GdVal&,unsigned);'
    text=replace(text,anchor,anchor+'\nvoid native_resolved_seed(GdObj*,unsigned);\nbool native_resolved_cached_generated(const BattleCtx&,const GdObj*);')
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'native_resolved_dispatch.hpp';text=path.read_text('utf8')
    rows={name:int(index) for name,index in re.findall(r'value\.emplace\(&typeid\((\w+)\),&native_resolved_rows\[(\d+)\]\);',text)}
    assert len(rows)==674 and len(set(rows.values()))==665
    anchor='bool native_resolved_row_matches(const GdObj* object,const NativeMethodRow* row) {'
    functions='''void native_resolved_seed(GdObj* object,unsigned row) {
    if(object && row<std::size(native_resolved_rows))object->native_call_row_=&native_resolved_rows[row];
}
bool native_resolved_cached_generated(const BattleCtx& context,const GdObj* object) {
    const auto* row=object->native_call_row_;
    return row && row!=&native_resolved_empty &&
        (!context.native_resolved_audit || row==native_resolved_exact_row(object));
}
'''
    text=replace(text,anchor,functions+anchor)
    path.write_text(text,encoding='utf8',newline='\n')
    seeded={}
    pattern=re.compile(r'static gd::GdObj\* _alloc_(\w+)\(gd::BattleCtx& ctx\) \{ return ctx.arena.make<\1>\(&ctx\); \}')
    for file in (native/'gen/shards').glob('*.cpp'):
        source=file.read_text('utf8')
        def seed(m):
            name=m[1];assert name in rows
            seeded[name]=rows[name]
            return f'static gd::GdObj* _alloc_{name}(gd::BattleCtx& ctx) {{ auto* object=ctx.arena.make<{name}>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,{rows[name]}u); return object; }}'
        file.write_text(pattern.sub(seed,source),encoding='utf8',newline='\n')
    assert seeded==rows
    after_seed={p.relative_to(native).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in native.rglob('*') if p.is_file()}
    report=trace(native,expected=after_seed)
    report.update({'baseline_dll_sha256':'7af5ff948b949859339f0897a6d857953ae8e3b30ec451cee030672ba9c5129b',
        'components':['674 exact generated allocator row seeds','known-pure dead AddSpeed trace arguments'],
        'sparse_index_or_callback_tracking_added':False,'object_and_context_layout_changed':False,
        'timer_traversal':'Original accepted7af dense traversal, unchanged',
        'source_start':'Accepted7af frozen full704 source','seeded_rows':seeded,
        'prior_sparse_evidence':'Two full packages regressed; retained separately. Eager and trace components are re-evaluated together, not assigned individual gains.'})
    return report
