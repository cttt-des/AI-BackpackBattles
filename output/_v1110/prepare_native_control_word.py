"""Combine fresh watch-state reads without changing checks, writes or layouts."""
import hashlib
import json
from pathlib import Path
import shutil

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/object_routes_bundle'
BACKUP=STAGE/'native_perf50/active_prefetch_bundle'
WORK=STAGE/'native_perf50/control_word_prototype'
EXPECTED='f950b64c74684ae70ce4e41b9622541c849da0121e1235ab88b7aaface22a6d7'
ARCHIVE='584aef472686dc09bb5abda831c358a2026a2fe3'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def once(text,old,new):
    assert text.count(old)==1,(old[:100],text.count(old));return text.replace(old,new,1)

HELPERS=r'''
// Every call reads the current state at its original check position. There is
// no cached readiness bit, additional invalidation write, or removed guard.
#if defined(__MINGW32__) && defined(__x86_64__) && !defined(GD_TIMER_CONTROL_WORD_FORCE_PORTABLE)
inline constexpr bool native_timer_control_word_compatible=
    sizeof(bool)==1 && sizeof(uint32_t)==4 && sizeof(uint64_t)==8 &&
    std::endian::native==std::endian::little &&
    std::is_standard_layout_v<NativeTimerWatch> &&
    std::bit_cast<uint8_t>(true)==1 &&
    offsetof(NativeTimerWatch,enabled)==offsetof(NativeTimerWatch,depth)+4 &&
    offsetof(NativeTimerWatch,usable)==offsetof(NativeTimerWatch,depth)+5 &&
    offsetof(NativeTimerWatch,collect)==offsetof(NativeTimerWatch,depth)+6 &&
    offsetof(NativeTimerWatch,closed_world)==offsetof(NativeTimerWatch,depth)+7;
#else
inline constexpr bool native_timer_control_word_compatible=false;
#endif
template<uint64_t Mask,uint64_t Expected>
inline bool native_timer_control_matches(const NativeTimerWatch& watch) {
    uint64_t word;
    // Read object representation through the complete watch object, rather
    // than extending a pointer past its uint32_t depth subobject.
    std::memcpy(&word,reinterpret_cast<const unsigned char*>(&watch)+
        offsetof(NativeTimerWatch,depth),sizeof(word));
    return (word&Mask)==Expected;
}
inline bool native_timer_active_ready(const NativeTimerWatch& watch) {
    if constexpr(native_timer_control_word_compatible)
        return native_timer_control_matches<UINT64_C(0xff00ffffffffffff),UINT64_C(0x0100010100000000)>(watch);
    return watch.enabled && watch.closed_world && watch.usable && !watch.depth;
}
inline bool native_timer_index_ready(const NativeTimerWatch& watch) {
    if constexpr(native_timer_control_word_compatible)
        return native_timer_control_matches<UINT64_C(0x0000ffffffffffff),UINT64_C(0x0000010100000000)>(watch);
    // Original timer traversal does not require closed_world here.
    return watch.enabled && watch.usable && !watch.depth;
}
inline bool native_timer_suffix_ready(const NativeTimerWatch& watch) {
    if constexpr(native_timer_control_word_compatible)
        return native_timer_control_matches<UINT64_C(0x0000ff00ffffffff),UINT64_C(0x0000010000000000)>(watch);
    // Original timer suffix guard does not check enabled or closed_world.
    return watch.usable && !watch.depth;
}
'''

ENTRY=r'''
extern "C" uint32_t gd_test_native_timer_control(const gd::NativeTimerWatch* watch) {
    return (gd::native_timer_active_ready(*watch)?1u:0u) |
        (gd::native_timer_index_ready(*watch)?2u:0u) |
        (gd::native_timer_suffix_ready(*watch)?4u:0u) |
        (gd::native_timer_control_word_compatible?8u:0u);
}
'''

def transform(native):
    p=native/'native_targeted_timers.hpp';t=p.read_text('utf8')
    t=once(t,'#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"',
        '#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"\n#include <bit>\n#include <cstddef>\n#include <cstring>\n#include <type_traits>')
    t=once(t,'namespace gd {','namespace gd {\n'+HELPERS)
    t=once(t,'watch.enabled && watch.usable && !watch.depth && character->rt_ctx_==&ctx',
        'native_timer_index_ready(watch) && character->rt_ctx_==&ctx')
    t=once(t,'watch.version!=version || !watch.usable || watch.depth',
        'watch.version!=version || !native_timer_suffix_ready(watch)')
    p.write_text(t,encoding='utf8',newline='\n')
    p=native/'native_active_cooldowns.hpp';t=p.read_text('utf8')
    t=once(t,'!watch.enabled || !watch.closed_world || !watch.usable || watch.depth ||',
        '!native_timer_active_ready(watch) ||')
    t=once(t,'!watch.usable || watch.depth || !watch.enabled || !watch.closed_world)',
        '!native_timer_active_ready(watch))')
    p.write_text(t,encoding='utf8',newline='\n')
    with (native/'gen/shards/shard_03.cpp').open('a',encoding='utf8',newline='\n') as f:f.write('\n'+ENTRY)
    return dict(component='fresh masked watch-control reads at original four guard positions',
        original_predicates_distinguished=True,active_checks_enabled_usable_depth_closed=True,
        timer_entry_checks_enabled_usable_depth_only=True,timer_suffix_checks_usable_depth_only=True,
        collect_ignored_in_all_predicates=True,all_version_checks_and_suffixes_unchanged=True,
        no_new_writes_or_cached_values=True,no_floating_rng_or_observation_changes=True,
        no_public_private_or_watch_layout_change=True,portable_original_boolean_fallback=True,
        no_prefetch_or_other_rejected_changes=True)

def verify_projection(native):
    reference=ACCEPTED/'bundle_src'
    targeted=(native/'native_targeted_timers.hpp').read_text('utf8')
    targeted=once(targeted,'#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"\n#include <bit>\n#include <cstddef>\n#include <cstring>\n#include <type_traits>',
        '#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"')
    targeted=once(targeted,'namespace gd {\n'+HELPERS,'namespace gd {')
    targeted=once(targeted,'native_timer_index_ready(watch) && character->rt_ctx_==&ctx',
        'watch.enabled && watch.usable && !watch.depth && character->rt_ctx_==&ctx')
    targeted=once(targeted,'watch.version!=version || !native_timer_suffix_ready(watch)',
        'watch.version!=version || !watch.usable || watch.depth')
    assert targeted==(reference/'native_targeted_timers.hpp').read_text('utf8')
    active=(native/'native_active_cooldowns.hpp').read_text('utf8')
    active=once(active,'!native_timer_active_ready(watch) ||',
        '!watch.enabled || !watch.closed_world || !watch.usable || watch.depth ||')
    active=once(active,'!native_timer_active_ready(watch))',
        '!watch.usable || watch.depth || !watch.enabled || !watch.closed_world)')
    assert active==(reference/'native_active_cooldowns.hpp').read_text('utf8')
    shard=(native/'gen/shards/shard_03.cpp').read_text('utf8')
    assert shard.endswith('\n'+ENTRY)
    assert shard[:-len('\n'+ENTRY)]==(reference/'gen/shards/shard_03.cpp').read_text('utf8')
    assert sha(native/'gd_rt.hpp')==sha(reference/'gd_rt.hpp')
    headers=list((native/'gen/hdrs').glob('*.hpp'));assert len(headers)==674
    assert all(sha(p)==sha(reference/p.relative_to(native)) for p in headers)
    return dict(passed=True,original_three_files_recovered_by_exact_inverse=True,
        original_all_versions_callbacks_suffixes_and_floating_operations_unchanged=True,
        original_watch_and674_object_header_bytes_unchanged=True,
        baseline_targeted_header_sha256=sha(reference/'native_targeted_timers.hpp'),
        candidate_targeted_header_sha256=sha(native/'native_targeted_timers.hpp'))

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    receipt=json.loads((BACKUP/'checkpoint_receipt.json').read_bytes())
    assert receipt['remote_upload_verified'] and receipt['remote_verified_commit']==ARCHIVE
    assert not WORK.exists();WORK.mkdir()
    source=WORK/'prototype_src'
    shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    before={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    # Prove the include closure for every existing source unit. This is only a
    # semantic prototype; formal qualification always rebuilds the full20.
    import re
    def closure(p,seen):
        p=p.resolve()
        if p in seen:return
        seen.add(p)
        for relative in re.findall(r'^\s*#include\s+"([^"]+)"',p.read_text('utf8'),re.M):
            child=p.parent/relative
            if child.is_file():closure(child,seen)
    consumers=[]
    target=(source/'native_targeted_timers.hpp').resolve()
    for p in source.rglob('*.cpp'):
        seen=set();closure(p,seen)
        if target in seen:consumers.append(p.relative_to(source).as_posix())
    assert sorted(consumers)==['gen/shards/shard_03.cpp'],consumers
    component=transform(source)
    after={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    changed=sorted(n for n in before if before[n]!=after[n])
    assert changed==['gen/shards/shard_03.cpp','native_active_cooldowns.hpp','native_targeted_timers.hpp']
    result=dict(baseline_dll_sha256=EXPECTED,verified_backup=ARCHIVE,source_sha256=after,
        modified_files=changed,new_files=[],sole_cpp_consumer=consumers[0],component=component,
        not_for_deployment=True,no_speed_claim=True)
    (WORK/'transform.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    (WORK/'source_projection.json').write_text(json.dumps(verify_projection(source),indent=2)+'\n',encoding='utf8')
    print(json.dumps(dict(source_changes=changed,sole_cpp_consumer=consumers,no_speed_claim=True)),flush=True)

if __name__=='__main__':main()
