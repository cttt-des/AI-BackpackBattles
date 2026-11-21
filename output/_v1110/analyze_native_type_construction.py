"""Read-only proofs for an exact generated metadata/constructor composition."""
from collections import Counter
import hashlib
import json
from pathlib import Path
import re

STAGE=Path(__file__).resolve().parent

def analyze(native):
    source='\n'.join(p.read_text('utf8') for p in sorted((native/'gen/shards').glob('*.cpp')))
    parents={}
    for p in (native/'gen/hdrs').glob('*.hpp'):
        m=re.search(r'^struct (Gd__\w+) : public ([\w:]+) \{',p.read_text('utf8'),re.M)
        if m:parents[m[1]]=m[2]
    meta_bodies={a:b for a,b in re.findall(r'^const gd::GdClassMeta\* (Gd__\w+)::meta\(\) const \{ return &META_(Gd__\w+); \}',source,re.M)}
    assert len(meta_bodies)==674 and set(meta_bodies)==set(parents)
    assert all(a==b for a,b in meta_bodies.items())
    quoted=r'"(?:[^"\\]|\\.)*"'
    pattern=rf'^const gd::GdClassMeta META_(Gd__\w+) = \{{CLS_\1, {quoted}, {quoted}, (nullptr|&META_Gd__\w+),'
    metadata={c:(base.removeprefix('&META_') if base!='nullptr' else None) for c,base in re.findall(pattern,source,re.M)}
    assert set(metadata)==set(parents)
    assert all(metadata[c]==(base if base in parents else None) for c,base in parents.items())
    def ancestors(cls):
        result=[]
        while cls:
            assert cls not in result;result.append(cls);cls=metadata[cls]
        return result
    ancestry={c:ancestors(c) for c in parents}
    counts=Counter()
    for match in re.finditer(r'gd::gd_is_type\([^\n;]*?&META_(Gd__\w+)\)',source):counts[match[1]]+=1
    gem='Gd__gd_core_items__Gems__Gem';assert gem in parents
    selected=[gem]+[c for c,n in counts.most_common() if c!=gem][:7]
    assert len(selected)==8
    alloc_pattern=r'static gd::GdObj\* _alloc_(Gd__\w+)\(gd::BattleCtx& ctx\) \{ auto\* object=ctx.arena.make<\1>\(&ctx\); if\(ctx.native_resolved_dispatch\)gd::native_resolved_seed\(object,(\d+)u\); return object; \}'
    allocators={c:int(row) for c,row in re.findall(alloc_pattern,source)}
    assert set(allocators)==set(parents)
    cpp=(native/'gd_rt.cpp').read_text('utf8')
    start=cpp.index('GdVal construct_class(');end=cpp.index('\n}\n',start)+2
    body=cpp[start:end]
    expected='''GdVal construct_class(BattleCtx& ctx, const GdClassMeta* cls, const GdVal* args, int argc) {
    if (!cls || !cls->alloc_fn) return GdVal::null();
    GdObj* obj = cls->alloc_fn(ctx);
    obj->init_fields(ctx);
    GdVal dummy;
    obj->call_method(ctx, SYM__init, args, argc, dummy);
    return GdVal::from_obj(obj);
}'''
    assert body==expected
    ids=re.findall(r'^    (CLS_Gd__\w+),$',(native/'gen/class_metas.hpp').read_text('utf8'),re.M)
    assert len(ids)==674
    return {'status':'source_proofs_only_uncompiled_unmeasured','pure_own_metadata_getters':674,
        'metadata_parent_edges_verified':674,'generated_allocators_verified':674,
        'parents':metadata,'ancestors':ancestry,'allocator_rows':allocators,
        'selected_type_targets':[{'class':c,'static_calls_approx':counts[c]} for c in selected],
        'last_class_id_symbol':ids[-1],'construct_class_body_sha256':hashlib.sha256(body.encode()).hexdigest(),
        'construct_class_body':body,
        'required':'Runtime tests must independently compare metadata pointer predicates, original alloc+virtual init snapshots, _init order/RNG and unknown/custom metadata fallback. Source proofs are not speed or runtime-equivalence evidence.'}

if __name__=='__main__':
    work=STAGE/'native_perf50/type_constructor_bundle';work.mkdir(exist_ok=True)
    result=analyze(STAGE/'sim_native/native_sim_cpp/native_sim')
    (work/'source_design.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps({k:v for k,v in result.items() if k not in ('parents','ancestors','allocator_rows','construct_class_body')},indent=2))
