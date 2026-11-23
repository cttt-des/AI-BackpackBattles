"""Coallocate independent item containers and ordinary runtime storage."""
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/event_factory_bundle'
WORK=STAGE/'native_perf50/storage_prototype'
EXPECTED='d8a7365191ad57a48ac378a7db77e8587169814f6f74298734f7d0b4786e3a76'
ARCHIVE='8e6ef3449e7a5a26d9d3fc7f268e380fbc7694fe'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def once(t,a,b):
    assert t.count(a)==1,(a[:100],t.count(a));return t.replace(a,b,1)

PROBE='''
#if defined(GD_STORAGE_PROBE)
static thread_local uint64_t storage_probe_counts[8]{};
extern "C" void gd_storage_probe_hit(unsigned index,uint64_t count) {
    if(index<8)storage_probe_counts[index]+=count;
}
extern "C" uint64_t gd_storage_probe_stat(unsigned index) {
    return index<8?storage_probe_counts[index]:0;
}
#endif
'''

def transform(native):
    p=native/'gd_rt.cpp';t=p.read_text('utf8')
    pos=t.index('\nnamespace gd {');t=t[:pos]+'\n'+PROBE+t[pos:]
    old='''    auto* gs = arena.make<GdStr>();
    char* buf = arena.alloc_array<char>(len + 1);'''
    new='''    GdStr* gs;
    char* buf;
    if(len==UINT32_MAX) {
        // Retain the original overflow path; valid sizes use one allocation.
        gs=arena.make<GdStr>();buf=arena.alloc_array<char>(len+1);
    } else {
        auto* raw=static_cast<unsigned char*>(arena.alloc_raw(
            sizeof(GdStr)+size_t{len}+1,alignof(GdStr)));
        gs=new(raw) GdStr();buf=reinterpret_cast<char*>(raw+sizeof(GdStr));
#if defined(GD_STORAGE_PROBE)
        ::gd_storage_probe_hit(0,1);
#endif
    }'''
    t=once(t,old,new)
    old='''    auto* gs = arena.make<GdStr>();
    char* buf = arena.alloc_array<char>(al + bl + 1);'''
    new='''    GdStr* gs;
    char* buf;
    if(uint64_t{al}+bl>=UINT32_MAX) {
        gs=arena.make<GdStr>();buf=arena.alloc_array<char>(al+bl+1);
    } else {
        auto* raw=static_cast<unsigned char*>(arena.alloc_raw(
            sizeof(GdStr)+size_t{al}+bl+1,alignof(GdStr)));
        gs=new(raw) GdStr();buf=reinterpret_cast<char*>(raw+sizeof(GdStr));
#if defined(GD_STORAGE_PROBE)
        ::gd_storage_probe_hit(1,1);
#endif
    }'''
    t=once(t,old,new)
    old='''    auto* a = arena.make<GdArr>();
    if (reserve_cap > 0) {
        a->data = arena.alloc_array<GdVal>(reserve_cap);
        a->cap = reserve_cap;
    }
    return a;'''
    new='''    if(reserve_cap==0)return arena.make<GdArr>();
    constexpr size_t offset=(sizeof(GdArr)+alignof(GdVal)-1)/alignof(GdVal)*alignof(GdVal);
    constexpr size_t alignment=alignof(GdArr)>alignof(GdVal)?alignof(GdArr):alignof(GdVal);
    auto* raw=static_cast<unsigned char*>(arena.alloc_raw(offset+sizeof(GdVal)*size_t{reserve_cap},alignment));
    auto* a=new(raw) GdArr();
    a->data=reinterpret_cast<GdVal*>(raw+offset);a->cap=reserve_cap;
#if defined(GD_STORAGE_PROBE)
    ::gd_storage_probe_hit(2,1);::gd_storage_probe_hit(6,reserve_cap);
#endif
    return a;'''
    t=once(t,old,new)
    old='''    auto* d = arena.make<GdDict>();
    if (reserve_cap > 0) {
        d->entries = arena.alloc_array<GdDictEntry>(reserve_cap);
        d->cap = reserve_cap;
    }
    return d;'''
    new='''    if(reserve_cap==0)return arena.make<GdDict>();
    constexpr size_t offset=(sizeof(GdDict)+alignof(GdDictEntry)-1)/alignof(GdDictEntry)*alignof(GdDictEntry);
    constexpr size_t alignment=alignof(GdDict)>alignof(GdDictEntry)?alignof(GdDict):alignof(GdDictEntry);
    auto* raw=static_cast<unsigned char*>(arena.alloc_raw(offset+sizeof(GdDictEntry)*size_t{reserve_cap},alignment));
    auto* d=new(raw) GdDict();
    d->entries=reinterpret_cast<GdDictEntry*>(raw+offset);d->cap=reserve_cap;
#if defined(GD_STORAGE_PROBE)
    ::gd_storage_probe_hit(3,1);::gd_storage_probe_hit(7,reserve_cap);
#endif
    return d;'''
    t=once(t,old,new);p.write_text(t,encoding='utf8',newline='\n')
    p=native/'gen/shards/shard_00.cpp';t=p.read_text('utf8')
    marker='void Gd__gd_core__CoreItem::init_fields(gd::BattleCtx& gd_ctx) {\n'
    a=t.index(marker)+len(marker);b=t.index('\n}\nconst gd::GdClassMeta* Gd__gd_core__CoreItem::meta()',a)
    original=t[a:b]
    arrays=['chargeFrame','statDisplayOverrides','itemMetrics','gems','combatConnections',
            'occupiedCells','collisionCells','extensionCells','affectedExtensionCells','buffLabelPositionTimestamps']
    dicts=['buffPowers','buffAmplificationChances','paramMult','paramAdd','dynamicTypes',
           'affectedCellsCache','currentAffectedItems','cachedAffectedItems','affectedTileCells']
    hot=original
    for slot,field in enumerate(arrays):
        lines=[s for s in hot.splitlines() if f'this->f_{field} = gd::GdVal::from_arr(' in s]
        assert len(lines)==1,(field,lines)
        line=lines[0]
        matches=list(re.finditer(r'gd::GdArr::from_init\(gd_ctx\.arena, (\{[^\n]*\})\)',line))
        assert len(matches)==1
        m=matches[0];values=m.group(1)
        if slot==0:assert values.count('from_vec2')==4
        elif slot==9:assert values.count('from_float')==5
        else:assert values=='{}'
        changed=line[:m.start()]+f'native_item_array({slot}, {values})'+line[m.end():]
        hot=once(hot,line,changed)
    for slot,field in enumerate(dicts):
        line=f'this->f_{field} = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));'
        hot=once(hot,line,f'this->f_{field} = gd::GdVal::from_dict(&storage->dictionaries[{slot}]);')
    assert hot.count('GdArr::from_init(gd_ctx.arena, {})')==1 # original timer fallback
    prefix='''    if(gd_ctx.native_timer_watch.closed_world) {
        // Independent headers retain their original field assignment points.
        // Both mutation helpers below only update counters/versions, never call
        // application code. Raw value slots are filled at the original points.
        struct NativeItemStorage {
            gd::GdArr arrays[10];
            gd::GdDict dictionaries[9];
            alignas(gd::GdVal) unsigned char values[sizeof(gd::GdVal)*9];
        };
        auto* storage=gd_ctx.arena.make<NativeItemStorage>();
#if defined(GD_STORAGE_PROBE)
        gd_storage_probe_hit(4,1);
#endif
        const auto native_item_array=[&](unsigned slot,std::initializer_list<gd::GdVal> values) {
            auto* array=&storage->arrays[slot];
            if(values.size()) {
                array->data=reinterpret_cast<gd::GdVal*>(storage->values)+(slot==0?0:4);
                array->cap=static_cast<uint32_t>(values.size());
                for(const auto& value:values)array->data[array->len++]=value;
            }
            return array;
        };
'''
    declaration='''#if defined(GD_STORAGE_PROBE)
extern "C" void gd_storage_probe_hit(unsigned,uint64_t);
#endif
'''
    t=t[:a]+prefix+hot+'\n        return;\n    }\n'+original+t[b:]
    t=once(t,marker,declaration+marker)
    p.write_text(t,encoding='utf8',newline='\n')
    return dict(components=['closed CoreItem 19 independent headers + 9 value slots in one allocation',
        'GdStr header and character bytes in one allocation','reserved GdArr header and raw value slots in one allocation',
        'reserved GdDict header and raw entries in one allocation'],
        original_capacities_and_raw_slot_behavior_preserved=True,
        no_redundant_default_constructor_savings_claim=True,
        all_original_watcher_and_field_store_positions_preserved=True,
        open_item_initialization_body_retained=True,inline_timer_header_logic_unchanged=True,
        layouts_unchanged=True,no_extra_production_counter_branches=True,
        previous_deployed_event_factory_retained=True)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED and not WORK.exists()
    raw=subprocess.check_output(['git','show',ARCHIVE+':output/_v1110/sim_native/native_sim_cpp/native_sim/libgdcore.dll'])
    assert hashlib.sha256(raw).hexdigest()==EXPECTED
    WORK.mkdir();src=WORK/'prototype_src'
    shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    before={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    components=transform(src)
    after={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    changed=sorted(n for n in before if before[n]!=after[n])
    assert changed==['gd_rt.cpp','gen/shards/shard_00.cpp']
    (WORK/'transform.json').write_text(json.dumps(dict(baseline_dll_sha256=EXPECTED,
        verified_backup=ARCHIVE,source_sha256=after,modified_files=changed,
        design=components,not_for_deployment=True),indent=2)+'\n',encoding='utf8')
    print('Prepared new storage bundle; no timing claim')

if __name__=='__main__':main()
