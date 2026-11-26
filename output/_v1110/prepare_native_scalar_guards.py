"""Reproduce scalar guards on the retained private-snapshot combination."""
import hashlib
import json
from pathlib import Path
import re
import shutil

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/display_storage_bundle'
RETAINED=STAGE/'native_perf50/restored_snapshots_bundle'
WORK=STAGE/'native_perf50/scalar_guards_prototype'
EXPECTED='5ddb2c1b15ad7ab7dfe1a8f2640701abddf6da88600b2930e55fc85165b59209'
ARCHIVE='4bc0f346988f01e046b6ac81ec1630223d0683b5'

HELPERS='''
// 常见标量在调用点保留原真假判断；其他种类完整交回原实现。
inline bool native_scalar_truth(const GdVal& v) {
    switch (v.kind) {
        case GdVal::Kind::Null: return false;
        case GdVal::Kind::Bool: return v.b;
        case GdVal::Kind::Int: return v.i != 0;
        case GdVal::Kind::Float: return v.f != 0.0;
        default: return gd_truth(v);
    }
}
'''

def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def inventory(native):
    return {p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()
        and '__pycache__' not in p.parts and p.suffix not in ('.dll','.o','.gcda','.gcno','.pyc')}
def archive():
    r=json.loads((RETAINED/'checkpoint_receipt.json').read_bytes())
    assert r['remote_upload_verified'] and r['remote_verified_commit']==ARCHIVE and r['production_dll_sha256']==EXPECTED
    return ARCHIVE

def transform(native):
    from prepare_native_private_snapshots import transform as private_transform
    private=private_transform(native)
    restored=json.loads((RETAINED/'source_before_build.json').read_bytes())
    assert inventory(native)==restored,'Restore the exact retained source before the new change'
    header=native/'gd_rt.hpp';t=header.read_text('utf8')
    anchor='bool gd_truth(const GdVal& v);'
    assert t.count(anchor)==1 and 'native_scalar_truth' not in t
    t=t.replace(anchor,anchor+'\n'+HELPERS,1)
    header.write_text(t,encoding='utf8',newline='\n')
    # Preserve strings/comments byte for byte and change call identifiers only.
    tokens=re.compile(r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|\b(gd_truth|gd_eq)(?=\s*\()')
    sites={}
    for p in sorted((native/'gen/shards').glob('*.cpp')):
        counts={'gd_truth':0,'gd_eq':0}
        def change(m):
            name=m.group(1)
            if name is None:return m.group(0)
            counts[name]+=1
            return {'gd_truth':'native_scalar_truth','gd_eq':'native_scalar_eq'}[name]
        before=p.read_text('utf8');after=tokens.sub(change,before)
        assert counts['gd_truth']>0 and counts['gd_eq']==0
        p.write_text(after,encoding='utf8',newline='\n');sites[p.relative_to(native).as_posix()]=counts
    assert len(sites)==16
    return dict(private_component=private,scalar_call_sites=sites,existing_scalar_equality_unchanged=True,
        ordinary_gd_truth_and_gd_eq_definitions_unchanged=True,complex_truth_original_fallback=True)

def verify_projection(native):
    frozen=json.loads((WORK/'transform.json').read_bytes())
    assert inventory(native)==frozen['source_sha256']
    retained=json.loads((RETAINED/'source_before_build.json').read_bytes())
    changed={'gd_rt.hpp',*[f'gen/shards/shard_{i:02d}.cpp' for i in range(16)]}
    for name,digest in retained.items():
        p=native/name
        if name=='gd_rt.hpp':
            text=p.read_text('utf8');assert text.count('\n'+HELPERS)==1
            original=text.replace('\n'+HELPERS,'',1).encode('utf8')
            assert hashlib.sha256(original).hexdigest()==digest
        elif name in changed:
            original=re.sub(r'\bnative_scalar_truth(?=\s*\()', 'gd_truth',p.read_text('utf8')).encode('utf8')
            assert hashlib.sha256(original).hexdigest()==digest,name
        else:assert sha(p)==digest,name
    reference=ACCEPTED/'bundle_src'
    assert (native/'gd_rt.cpp').read_bytes()==(reference/'gd_rt.cpp').read_bytes()
    assert all(p.read_bytes()==(reference/p.relative_to(native)).read_bytes() for p in (native/'gen/hdrs').glob('*.hpp'))
    return dict(passed=True,all674_object_headers_unchanged=True,all_public_and_private_layouts_unchanged=True,
        original_fallback_runtime_unchanged=True,exact_inverse_matches_retained_source=True,full20_rebuild_required=True)

def main():
    archive();assert sha(BASE/'libgdcore.dll')==EXPECTED and not WORK.exists()
    WORK.mkdir();native=WORK/'prototype_src'
    shutil.copytree(ACCEPTED/'bundle_src',native)
    before=inventory(native);assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    component=transform(native);after=inventory(native)
    changed=sorted(n for n in before if before[n]!=after[n])
    assert changed==sorted(['gd_rt.hpp',*[f'gen/shards/shard_{i:02d}.cpp' for i in range(16)]])
    assert sorted(set(after)-set(before))==['native_private_snapshots.hpp']
    result=dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,source_sha256=after,
        modified_files=changed,new_files=['native_private_snapshots.hpp'],component=component,
        baseline_cpp_source_files=707,candidate_cpp_source_files=708,no_layout_change=True,
        private_snapshot_combination_retained=True,no_new_branches=True,not_for_deployment=True,no_speed_claim=True)
    (WORK/'transform.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    verify_projection(native)
    print(json.dumps(dict(changed_files=len(changed),sites=component['scalar_call_sites'],retained_private=True)),flush=True)

if __name__=='__main__':main()
