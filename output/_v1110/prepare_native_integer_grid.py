"""Keep canonical dictionary entries while adding a bounded coordinate bucket format."""
import json
from pathlib import Path
import shutil
from inspect_native_geometry_cost import STAGE,BASE,EXPECTED,ARCHIVE,sha
WORK=STAGE/'native_perf50/integer_grid_prototype'

def once(t,a,b):
    assert t.count(a)==1,(a[:100],t.count(a));return t.replace(a,b,1)

HELPER=r'''
namespace {
static thread_local uint64_t native_integer_grid_counts[6]{};
void rebuild_integer_grid_buckets(GdDict& dict) {
    std::memset(dict.buckets,-1,sizeof(int32_t)*integer_grid_detail::cells);
    for(uint32_t i=0;i<dict.len;++i) {
        uint32_t slot;
        if(!integer_grid_detail::stored_slot(dict.entries[i].key,slot)) {
            // A noncanonical external edit retains canonical entries and falls
            // back to the original linear lookup, without allocating in erase.
            dict.buckets=nullptr;dict.bucket_cap=0;return;
        }
        if(dict.buckets[slot]<0)dict.buckets[slot]=int32_t(i);
    }
}
}
void native_integer_grid_hit(unsigned field){if(field<6)++native_integer_grid_counts[field];}
bool GdDict::enable_integer_grid(BattleArena& arena) {
    if(integer_grid_detail::enabled(*this))return true;
    for(uint32_t i=0;i<len;++i) {
        uint32_t slot;
        if(!integer_grid_detail::stored_slot(entries[i].key,slot) ||
           entries[i].hash!=gd_val_hash(entries[i].key))return false;
    }
    auto* table=arena.alloc_array<int32_t>(integer_grid_detail::cells);
    buckets=table;bucket_cap=integer_grid_detail::format_flag|integer_grid_detail::cells;
    rebuild_integer_grid_buckets(*this);return true;
}
bool GdDict::try_integer_grid_index(const GdVal& key,int32_t& index)const {
    if(!integer_grid_detail::enabled(*this) || !buckets)return false;
    int32_t slot;
    if(!integer_grid_detail::query_slot(key,slot))return false;
    index=slot<0?-1:buckets[uint32_t(slot)];return true;
}
'''

def transform(native):
    before={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    accepted=STAGE/'native_perf50/active_cooldown_bundle/source_before_build.json'
    assert before==json.loads(accepted.read_bytes())
    header=native/'gd_rt.hpp';text=header.read_text('utf8')
    marker='    int32_t find_index(const GdVal& key, uint64_t h) const;'
    declarations='    bool enable_integer_grid(BattleArena& arena);\n    bool try_integer_grid_index(const GdVal& key,int32_t& index) const;\n'
    text=once(text,marker,declarations+marker)
    assert text.replace(declarations,'',1)==header.read_text('utf8')
    header.write_text(text,encoding='utf8',newline='\n')
    shutil.copyfile(STAGE/'native_integer_grid.hpp',native/'native_integer_grid.hpp')
    path=native/'gd_rt.cpp';text=path.read_text('utf8')
    text=once(text,'#include "gd_rt.hpp"','#include "gd_rt.hpp"\n#include "native_integer_grid.hpp"')
    text=once(text,'GdDict* GdDict::create(BattleArena& arena, uint32_t reserve_cap) {',HELPER+'\nGdDict* GdDict::create(BattleArena& arena, uint32_t reserve_cap) {')
    start=text.index('int32_t GdDict::find_index(');end=text.index('\n}',start)+2;method=text[start:end]
    marker='    uint32_t mask = bucket_cap - 1;'
    addition='''    if(integer_grid_detail::enabled(*this)) {
        int32_t slot;
        if(integer_grid_detail::query_slot(key,slot)) {
            const int32_t index=slot<0?-1:buckets[uint32_t(slot)];
            return index>=0 && entries[index].hash==h?index:-1;
        }
        // Unknown types, subnormals and nonfinite inputs retain the original
        // hash and equality operations. The table contains only finite Vec2 keys.
        for(uint32_t i=0;i<len;++i)
            if(entries[i].hash==h && gd_eq(entries[i].key,key))return int32_t(i);
        return -1;
    }
'''
    method=once(method,marker,addition+marker);text=text[:start]+method+text[end:]
    start=text.index('void GdDict::set(');end=text.index('\n}',start)+2;method=text[start:end]
    marker='    if (len == cap) {'
    addition='''    uint32_t grid_slot=0;
    bool grid_mode=integer_grid_detail::enabled(*this);
    if(grid_mode && !integer_grid_detail::stored_slot(key,grid_slot)) {
        // Existing-key updates above never replace the stored key. Only a new
        // incompatible key switches back to the ordinary hash representation.
        buckets=nullptr;bucket_cap=0;rebuild_index(arena);grid_mode=false;
        ++native_integer_grid_counts[4];
    }
'''
    method=once(method,marker,addition+marker)
    method=once(method,'        rebuild_index(arena);','        if(grid_mode)buckets[grid_slot]=int32_t(len-1);else rebuild_index(arena);')
    method=once(method,'    if (buckets && bucket_cap > 0) {','    if(grid_mode){buckets[grid_slot]=int32_t(ei);return;}\n    if (buckets && bucket_cap > 0) {')
    text=text[:start]+method+text[end:]
    start=text.index('void GdDict::erase(');end=text.index('\n}',start)+2;method=text[start:end]
    method=once(method,'    if (buckets && bucket_cap > 0) {','    if(integer_grid_detail::enabled(*this)){rebuild_integer_grid_buckets(*this);return;}\n    if (buckets && bucket_cap > 0) {')
    text=text[:start]+method+text[end:]
    old='if (buckets && bucket_cap > 0) std::memset(buckets, -1, sizeof(int32_t) * bucket_cap);'
    new='if (buckets && bucket_cap > 0) std::memset(buckets, -1, sizeof(int32_t) * (integer_grid_detail::enabled(*this)?integer_grid_detail::cells:bucket_cap));'
    text=once(text,old,new)
    text+='\nextern "C" uint64_t gd_diag_native_integer_grid_stat(unsigned i){return i<6?gd::native_integer_grid_counts[i]:0;}\n'
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'gen/shards/shard_13.cpp';text=path.read_text('utf8')
    text=once(text,'#pragma STDC FP_CONTRACT OFF','#pragma STDC FP_CONTRACT OFF\n#include "../../native_integer_grid.hpp"\nnamespace gd {void native_integer_grid_hit(unsigned);}')
    text=once(text,'        const auto index=dict->find_index(key);','''        int32_t index;
        if(dict->try_integer_grid_index(key,index)) {
            if(ctx.native_resolved_collect)native_integer_grid_hit(0);
        }else {
            index=dict->find_index(key);
            if(ctx.native_resolved_collect)native_integer_grid_hit(1);
        }''')
    signature='gd::GdVal Gd__gd_core__CoreGrid::fn__init('
    start=text.index(signature);end=text.index('\n}',start)+2;method=text[start:end]
    old='    this->f_character = lv__character;'
    new=old+'''
    if(gd_ctx.native_timer_watch.closed_world && this->f_filledCells.kind==gd::GdVal::Kind::Dict && this->f_filledCells.dict) {
        const bool enabled=this->f_filledCells.dict->enable_integer_grid(gd_ctx.arena);
        if(gd_ctx.native_resolved_collect)gd::native_integer_grid_hit(enabled?2:3);
    }'''
    method=once(method,old,new);text=text[:start]+method+text[end:]
    path.write_text(text,encoding='utf8',newline='\n')
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    return dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,source_sha256=after,
        modified_files=[n for n in before if before[n]!=after[n]],new_files=sorted(set(after)-set(before)),
        declarations_only_header_addition=declarations,no_layout_or_existing_inline_body_changes=True,
        bounded_grid_extent=[0,15,0,15],table_slots=256,canonical_entries_hashes_and_order_retained=True,
        original_hash_function_unchanged=True,only_closed_graph_filledCells_opt_in=True,bag_cells_not_opted_in=True,
        direct_lookup_preserves_nonfinite_and_denormal_fenv=True,new_unsupported_keys_disable_special_mode=True,
        ordinary_contexts_and_replacement_dictionaries_retain_generic_queries=True,
        no_semantics_or_throughput_claim_before_tests=True)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    slots=json.loads((WORK/'slot_correctness.json').read_bytes());assert slots['passed'] and slots['cases']==132576
    assert slots['helper_sha256']==sha(STAGE/'native_integer_grid.hpp')
    WORK.mkdir(exist_ok=True);src=WORK/'prototype_src';assert not src.exists()
    shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    report=transform(src);(WORK/'transform.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in report.items() if k!='source_sha256'},indent=2))

if __name__=='__main__':main()
