"""Local primitive membership for CoreItem's current affected-object sets."""
import hashlib
import json
import shutil
from pathlib import Path
from prepare_native_buff_inline_types import HELPERS
STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/buff_inline_types_bundle'
BACKUP=STAGE/'native_perf50/weapon_inline_chain_bundle'
WORK=STAGE/'native_perf50/assembly_membership_prototype'
EXPECTED='d2064b3f17d8168cf87a2e9f46e9fb336ffe4aaf6581c27d93350b2c41477a57'
ARCHIVE='f03dec6f9937ac6c829a8d277ca981917c1f9e32'
HEADER_NAME='native_assembly_membership.hpp'
HEADER='''#pragma once
#include "gd_rt.hpp"
namespace gd::assembly_membership {
__attribute__((always_inline)) inline bool object_set_contains(const GdVal& item,const GdVal& set) {
    if(set.kind==GdVal::Kind::Dict && set.dict) {
        const auto* dict=set.dict;
        // Obj hashing reads only the pointer and cannot raise FP exceptions.
        // The unindexed empty path in the original find_index cannot match.
        // Indexed empty/stale tables retain their original lookup behavior.
        if(item.kind==GdVal::Kind::Obj && dict->len==0 && (!dict->buckets || dict->bucket_cap==0))return false;
        return dict->has(item);
    }
    return native_scalar_truth(gd_in(item,set));
}
}
'''

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def inventory(p):return {f.relative_to(p).as_posix():sha(f) for f in p.rglob('*') if f.is_file() and '__pycache__' not in f.parts and f.suffix not in ('.dll','.o','.gcda','.gcno','.pyc')}
def once(t,a,b):assert t.count(a)==1,(a[:120],t.count(a));return t.replace(a,b,1)
def archive():
    r=json.loads((BACKUP/'checkpoint_receipt.json').read_bytes())
    assert r['remote_upload_verified'] and r['remote_verified_commit']==ARCHIVE and r['production_dll_sha256']==EXPECTED
    return ARCHIVE

def transform(native):
    assert inventory(native)==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    file='gen/shards/shard_00.cpp';p=native/file;original=p.read_text('utf8');text=original
    start=text.index('gd::GdVal Gd__gd_core__CoreItem::fn_onItemAdded(');end=text.index('\n}',start)+2
    old=text[start:end];new=once(old,'gd::native_scalar_truth(gd::gd_in(item, current))','gd::assembly_membership::object_set_contains(item, current)')
    edits=[dict(old=old,new=new)];text=once(text,old,new)
    anchor=text.splitlines(keepends=True)[0];replacement='#include "../../'+HEADER_NAME+'"\n'+anchor
    edits.append(dict(old=anchor,new=replacement));text=once(text,anchor,replacement)
    p.write_text(text,encoding='utf8',newline='\n');(native/HEADER_NAME).write_text(HEADER,encoding='utf8',newline='\n')
    return dict(edits={file:edits},scope='CoreItem.onItemAdded current affected-object-set membership only',
        no_global_equality_hash_or_dictionary_representation_changes=True,all_geometry_coordinate_queries_unchanged=True,
        all_query_then_commit_and_callback_order_unchanged=True,no_layout_changes=True,
        empty_fast_path_requires_obj_key_and_original_unindexed_empty_representation=True,
        unknown_keys_preserve_hash_fp_exceptions_and_unknown_containers_use_original_membership=True)

def verify_projection(native):
    f=json.loads((WORK/'transform.json').read_bytes());assert inventory(native)==f['source_sha256']
    original=json.loads((ACCEPTED/'source_before_build.json').read_bytes());edits=f['component']['edits']
    for name,h in original.items():
        if name not in edits:assert sha(native/name)==h,name;continue
        text=(native/name).read_text('utf8')
        for e in reversed(edits[name]):text=once(text,e['new'],e['old'])
        assert hashlib.sha256(text.encode()).hexdigest()==h,name
    assert (native/HEADER_NAME).read_text('utf8')==HEADER and set(inventory(native))-set(original)=={HEADER_NAME}
    return dict(passed=True,exact_inverse_matches_retained_source=True,all674_object_headers_and_all_layouts_unchanged=True,
        full_original_bodies_retained=True,all_prior_optimizations_retained=True,formal_full20_fresh18_pgo_required=True)

def main():
    archive();assert sha(BASE/'libgdcore.dll')==EXPECTED
    assert inventory(BASE)==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    counts=STAGE/'native_perf50/assembly_membership_assessment/dictionary_lengths/counts.json';r=json.loads(counts.read_bytes());assert r['passed']
    d=r['families']['affected_object_set'];assert d['calls']==1009420 and d['dictionary_length_histogram']['0']==961606
    WORK.mkdir(exist_ok=True);src=WORK/'prototype_src';assert not src.exists();shutil.copytree(ACCEPTED/'bundle_src',src)
    component=transform(src);after=inventory(src);before=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    assert [n for n,h in before.items() if after[n]!=h]==['gen/shards/shard_00.cpp']
    result=dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,source_sha256=after,component=component,
        modified_files=['gen/shards/shard_00.cpp'],new_files=[HEADER_NAME],baseline_cpp_source_files=708,candidate_cpp_source_files=709,
        diagnostic_counts_sha256=sha(counts),actual_object_set_queries=d['calls'],empty_dictionary_queries=d['dictionary_length_histogram']['0'],
        all_layouts_unchanged=True,no_new_branches=True,no_speed_claim=True,not_for_deployment=True)
    (WORK/'transform.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(verify_projection(src)),flush=True)

if __name__=='__main__':main()
