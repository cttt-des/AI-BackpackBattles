"""Address-only lookahead hints for the existing ordered active cooldown phase."""
import hashlib
import json
from pathlib import Path
import shutil

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/object_routes_bundle'
BACKUP=STAGE/'native_perf50/compiler_pta_bundle'
WORK=STAGE/'native_perf50/active_prefetch_prototype'
EXPECTED='f950b64c74684ae70ce4e41b9622541c849da0121e1235ab88b7aaface22a6d7'
ARCHIVE='bcad9e17d0af08821582759a44e0e4e8fe068be3'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def once(text,old,new):
    assert text.count(old)==1,(old[:100],text.count(old));return text.replace(old,new,1)

HELPERS=r'''
void native_active_prefetch_hit(unsigned,uint64_t);
// No dereference through a hinted address. The integer arithmetic also keeps
// stale/null test addresses out of C++ member-access or pointer-arithmetic UB.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalidoffsetof"
inline void active_prefetch_addresses(uintptr_t owner,uintptr_t display,bool collect) {
    if(owner) {
        __builtin_prefetch(reinterpret_cast<const void*>(owner),0,3);
        __builtin_prefetch(reinterpret_cast<const void*>(owner+offsetof(Gd__gd_core__CoreItem,f_statDisplayOverrides)),0,3);
        __builtin_prefetch(reinterpret_cast<const void*>(owner+offsetof(Gd__gd_core__CoreItem,f__cooldown_active)),0,3);
        __builtin_prefetch(reinterpret_cast<const void*>(owner+offsetof(Gd__gd_core__CoreItem,f_speedScale)),0,3);
        __builtin_prefetch(reinterpret_cast<const void*>(owner+offsetof(Gd__gd_core__CoreItem,f_triggerTime)),0,3);
        if(collect)native_active_prefetch_hit(3,5);
    }
    if(display) {
        __builtin_prefetch(reinterpret_cast<const void*>(display),0,3);
        __builtin_prefetch(reinterpret_cast<const void*>(display+96),0,3);
        __builtin_prefetch(reinterpret_cast<const void*>(display+120),0,3);
        if(collect)native_active_prefetch_hit(3,3);
    }
    if(collect)native_active_prefetch_hit(2,1);
}
#pragma GCC diagnostic pop
inline uintptr_t active_prefetch_display(BattleCtx& ctx,const Gd__gd_core__CoreItem* item) {
    // item was already proved to be an owned, known CoreItem by the original
    // build pass. Read only its ordinary value tag and pointer, never the array.
    const auto& value=item->f_statDisplayOverrides;
    if(value.kind!=GdVal::Kind::Arr || !value.arr)return 0;
    const auto address=reinterpret_cast<uintptr_t>(value.arr);
    if(address>UINTPTR_MAX-160 || !ctx.arena.owns_storage(value.arr,160))return 0;
    // The default header/data are adjacent. This is only a locality guess:
    // replacement, reallocation or a stale address never changes any value read.
    if(ctx.native_resolved_collect)native_active_prefetch_hit(1,1);
    return address;
}
'''

COUNTERS=r'''
namespace gd {
static thread_local uint64_t native_active_prefetch_counts[4]{};
void native_active_prefetch_hit(unsigned field,uint64_t amount) {
    if(field<4)native_active_prefetch_counts[field]+=amount;
}
}
extern "C" uint64_t gd_diag_native_active_prefetch_stat(unsigned field) {
    return field<4?gd::native_active_prefetch_counts[field]:0;
}
extern "C" void gd_test_native_active_prefetch(uintptr_t owner,uintptr_t display) {
    gd::active_prefetch_addresses(owner,display,false);
}
'''

def transform(native):
    path=native/'native_active_cooldowns.hpp';text=path.read_text('utf8')
    text=once(text,'#include "native_targeted_timers.hpp"','#include "native_targeted_timers.hpp"\n#include <cstddef>')
    text=once(text,'namespace gd {','namespace gd {\n'+HELPERS)
    text=once(text,'    const Gd__gd_core__CoreGrid* grid=nullptr;','    const Gd__gd_core__CoreGrid* grid=nullptr;\n    const uintptr_t* prefetch_bases=nullptr;')
    needle='    auto& watch=ctx.native_timer_watch;\n    cache={character,items,watch.version,watch.cooldown_version,entries,n,items->len,static_cast<const Gd__gd_core__CoreGrid*>(character->f_inventory.obj)};'
    replacement='''    auto* prefetch_bases=n?ctx.arena.alloc_array<uintptr_t>(n):nullptr;
    for(uint32_t k=0;k<n;++k)prefetch_bases[k]=active_prefetch_display(ctx,entries[k].owner);
    if(ctx.native_resolved_collect)native_active_prefetch_hit(0,n);
    auto& watch=ctx.native_timer_watch;
    cache={character,items,watch.version,watch.cooldown_version,entries,n,items->len,static_cast<const Gd__gd_core__CoreGrid*>(character->f_inventory.obj),prefetch_bases};'''
    text=once(text,needle,replacement)
    needle='    const auto* entries=cache->entries;const uint32_t length=cache->count;\n    for(uint32_t k=0;k<length;++k) {\n        const auto entry=entries[k];'
    replacement='''    const auto* entries=cache->entries;const uint32_t length=cache->count;
    const auto* prefetch_bases=cache->prefetch_bases;
    // Capture both private arrays. A nested rebuild allocates fresh storage,
    // and the outer phase retains its original entries and hint addresses.
    for(uint32_t ahead=0;ahead<length && ahead<3;++ahead)
        active_prefetch_addresses(reinterpret_cast<uintptr_t>(entries[ahead].owner),prefetch_bases?prefetch_bases[ahead]:0,ctx.native_resolved_collect);
    for(uint32_t k=0;k<length;++k) {
        if(length-k>3) {
            const uint32_t ahead=k+3;
            active_prefetch_addresses(reinterpret_cast<uintptr_t>(entries[ahead].owner),prefetch_bases?prefetch_bases[ahead]:0,ctx.native_resolved_collect);
        }
        const auto entry=entries[k];'''
    text=once(text,needle,replacement);path.write_text(text,encoding='utf8',newline='\n')
    path=native/'gen/shards/shard_03.cpp'
    with path.open('a',encoding='utf8',newline='\n') as out:out.write('\n'+COUNTERS)
    return dict(component='address-only active-owner and display-storage lookahead',distance=3,
        original_frame_body_and_all_real_reads_unchanged=True,no_math_or_frame_skips=True,
        no_new_object_observations_getters_or_rng=True,private_sidecar_layout_changed=True,
        GdVal_GdArr_BattleCtx_and674_object_headers_unchanged=True,
        array_addresses_not_dereferenced_or_reused_as_values=True,
        stale_addresses_only_prefetched=True,all_original_order_and_suffix_recovery_unchanged=True)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    backup=json.loads((BACKUP/'checkpoint_receipt.json').read_bytes())
    assert backup['remote_upload_verified'] and backup['remote_verified_commit']==ARCHIVE
    assert not WORK.exists();WORK.mkdir()
    source=WORK/'prototype_src'
    shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    before={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    includers=[p.relative_to(source).as_posix() for p in source.rglob('*.cpp') if 'native_active_cooldowns.hpp' in p.read_text('utf8')]
    assert includers==['gen/shards/shard_03.cpp'],includers
    component=transform(source)
    after={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    changed=sorted(n for n in before if before[n]!=after[n]);assert changed==['gen/shards/shard_03.cpp','native_active_cooldowns.hpp']
    result=dict(baseline_dll_sha256=EXPECTED,verified_backup=ARCHIVE,source_sha256=after,modified_files=changed,new_files=[],
        sole_cpp_consumer=includers[0],component=component,not_for_deployment=True,no_speed_claim=True,
        documentation='https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html')
    (WORK/'transform.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(dict(source_changes=changed,sole_cpp_consumer=includers,no_speed_claim=True)))

if __name__=='__main__':main()
