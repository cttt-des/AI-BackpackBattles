"""Compose the integer grid with cache-hit guard hoisting before any formal timing."""
import json
from pathlib import Path
import shutil
from prepare_native_integer_grid import STAGE,BASE,EXPECTED,ARCHIVE,sha,once
GRID=STAGE/'native_perf50/integer_grid_prototype'
WORK=STAGE/'native_perf50/grid_cooldown_prototype'

def transform_cached_cooldowns(native):
    path=native/'native_active_cooldowns.hpp';text=path.read_text('utf8');original=text
    text=once(text,'    uint32_t count=0,items_count=0;','    uint32_t count=0,items_count=0;\n    const Gd__gd_core__CoreGrid* grid=nullptr;')
    text=once(text,'cache={character,items,watch.version,watch.cooldown_version,entries,n,items->len};',
        'cache={character,items,watch.version,watch.cooldown_version,entries,n,items->len,static_cast<const Gd__gd_core__CoreGrid*>(character->f_inventory.obj)};')
    old='''    if(!watch.enabled || !watch.closed_world || !watch.usable || watch.depth ||
       watch.cooldown_version==UINT64_MAX || !character || character->rt_ctx_!=&ctx ||
       !ctx.arena.owns_storage(character,sizeof(*character)))return false;
    const auto& pid=character->f_playerId;
    const auto& inventory=character->f_inventory;
    if(pid.kind!=GdVal::Kind::Int || pid.i<0 || pid.i>1 ||
       inventory.kind!=GdVal::Kind::Obj || !inventory.obj || inventory.obj->rt_ctx_!=&ctx ||
       !ctx.arena.owns_storage(inventory.obj,sizeof(Gd__gd_core__CoreGrid)) ||
       !native_timer_known_object(inventory.obj))return false;
    auto* grid=dynamic_cast<Gd__gd_core__CoreGrid*>(inventory.obj);
    if(!grid || grid->f_items.kind!=GdVal::Kind::Arr || !grid->f_items.arr)return false;
    const auto* items=grid->f_items.arr;const uint32_t count=items->len;
    auto*& pointer=watch.cooldown_cache[unsigned(pid.i)];
    auto* cache=static_cast<ActiveCooldownCache*>(pointer);
    if(!cache){cache=ctx.arena.make<ActiveCooldownCache>();pointer=cache;}
    if(cache->character!=character || cache->items!=items || cache->items_count!=count ||
       cache->structure!=watch.version || cache->eligibility!=watch.cooldown_version) {
        if(!active_cooldown_build(ctx,character,items,*cache)) {
            active_cooldown_count(ctx,4);return false;
        }
    }else active_cooldown_count(ctx,2);'''
    new='''    if(!watch.enabled || !watch.closed_world || !watch.usable || watch.depth ||
       watch.cooldown_version==UINT64_MAX || !character || character->rt_ctx_!=&ctx)return false;
    const auto& pid=character->f_playerId;
    if(pid.kind!=GdVal::Kind::Int || pid.i<0 || pid.i>1)return false;
    const auto& inventory=character->f_inventory;
    auto*& pointer=watch.cooldown_cache[unsigned(pid.i)];
    auto* cache=static_cast<ActiveCooldownCache*>(pointer);
    // A cache hit has already proved the complete owned object/array graph.
    // Tracked structure writes and every eligibility store invalidate it;
    // live inventory/items identity and length checks also retain raw-field
    // replacements used by direct C++ callers. Reset clears all cache pointers.
    const bool hit=cache && cache->character==character && cache->grid &&
        cache->structure==watch.version && cache->eligibility==watch.cooldown_version &&
        inventory.kind==GdVal::Kind::Obj && inventory.obj==cache->grid &&
        cache->grid->f_items.kind==GdVal::Kind::Arr && cache->grid->f_items.arr==cache->items &&
        cache->items && cache->items->len==cache->items_count;
    const GdArr* items=nullptr;uint32_t count=0;
    if(hit) {
        items=cache->items;count=cache->items_count;active_cooldown_count(ctx,2);
    }else {
        if(!ctx.arena.owns_storage(character,sizeof(*character)) ||
           inventory.kind!=GdVal::Kind::Obj || !inventory.obj || inventory.obj->rt_ctx_!=&ctx ||
           !ctx.arena.owns_storage(inventory.obj,sizeof(Gd__gd_core__CoreGrid)) ||
           !native_timer_known_object(inventory.obj))return false;
        auto* grid=dynamic_cast<Gd__gd_core__CoreGrid*>(inventory.obj);
        if(!grid || grid->f_items.kind!=GdVal::Kind::Arr || !grid->f_items.arr)return false;
        items=grid->f_items.arr;count=items->len;
        if(!cache){cache=ctx.arena.make<ActiveCooldownCache>();pointer=cache;}
        if(!active_cooldown_build(ctx,character,items,*cache)) {
            active_cooldown_count(ctx,4);return false;
        }
    }'''
    text=once(text,old,new)
    old='''        if(active_cooldown_truth(entry.owner->f__cooldown_active)) {
            if(entry.gem_index==UINT32_MAX)item_tick(entry.owner);else gem_tick(entry.owner);
        }'''
    new='''        // Entry eligibility is Bool true; any intervening tracked store is
        // detected immediately after the preceding callback and resumes the
        // original suffix. The physical tick still retains its own checks.
        if(entry.gem_index==UINT32_MAX)item_tick(entry.owner);else gem_tick(entry.owner);'''
    text=once(text,old,new);path.write_text(text,encoding='utf8',newline='\n')
    return dict(original_header_sha256=sha(STAGE/'sim_native/native_sim_cpp/native_sim/native_active_cooldowns.hpp'),
        candidate_header_sha256=sha(path),cache_hit_skips_repeated_arena_and_rtti_checks=True,
        live_inventory_items_identity_and_length_guards_retained=True,all_write_hooks_and_suffix_recovery_unchanged=True,
        outer_true_bool_check_elided_only_for_valid_index_entries=True,original_physical_tick_checks_unchanged=True,
        private_cache_gains_grid_pointer_only=True,public_object_and_BattleCtx_layouts_unchanged=True)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    for name in ('dictionary_correctness.json','query_correctness.json','slot_correctness.json'):
        assert json.loads((GRID/name).read_bytes())['passed']
    assert not WORK.exists();WORK.mkdir();source=WORK/'prototype_src'
    shutil.copytree(GRID/'prototype_src',source)
    grid=json.loads((GRID/'transform.json').read_bytes())
    assert grid['source_sha256']=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    cooldown=transform_cached_cooldowns(source)
    after={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert [n for n in after if after[n]!=grid['source_sha256'][n]]==['native_active_cooldowns.hpp']
    report=dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,
        components=['bounded integer filledCells index','cooldown cache-hit guard hoisting','omit redundant indexed Bool-true check'],
        grid_component_receipt_sha256=sha(GRID/'transform.json'),cooldown_component=cooldown,source_sha256=after,
        before_any_formal_timing=True,no_standalone_component_speed_claim=True)
    (WORK/'transform.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in report.items() if k!='source_sha256'},indent=2))

if __name__=='__main__':main()
