"""Reuse pure cooldown speed work inside callback-free native role phases."""
import argparse
import hashlib
from pathlib import Path
import re
from optimize_native_serial_paths import method_body

# Whole-file guards from the independently archived, verified input.
ORIGINAL_PHYSICS = 'gd::GdVal Gd__gd_core__CoreItem::fn_physicsTick(const gd::GdVal* args, int argc) {\n    if (!gd::gd_truth(this->f__cooldown_active)) return gd::GdVal::null();\n    auto& context = *static_cast<Gd__gd_core__CoreContext*>(this->f_ctx.obj);\n    const auto blocked = this->f__cooldown_blocked_epoch.as_int();\n    if (blocked >= 0 && blocked == context.f_timer_pass_epoch.as_int()) return gd::GdVal::null();\n\n    const auto receiver = this->meta()->is_subclass_of(&META_Gd__gd_core_items__Gems__Gem)\n        ? static_cast<Gd__gd_core_items__Gems__Gem*>(this)->fn_character(nullptr, 0)\n        : this->f_character_;\n    const auto* character = receiver.kind == gd::GdVal::Kind::Obj\n        ? static_cast<const Gd__gd_core__CoreCharacter*>(receiver.obj) : nullptr;\n    if (character && character->f_stunnedDuration.as_float() > 0.0) return gd::GdVal::null();\n\n    const auto* display = this->f_statDisplayOverrides.arr;\n    const auto override = display && display->len > 3 ? display->data[3] : gd::GdVal::null();\n    double speed = 1.0;\n    const bool uses_override = !override.is_null() && gd::gd_truth(override);\n    if (uses_override) {\n        speed = override.as_float();\n    } else if (gd::gd_truth(this->f_placed) && !this->f_character_.is_null()) {\n        if (character) {\n            const auto* buffs = character->f_buffs.dict;\n            const auto stacks = [&](int64_t type) {\n                const auto slot = static_cast<uint32_t>(type - 100);\n                const auto* entries = buffs->entries;\n                if (slot < buffs->len && entries[slot].key.i == type)\n                    return static_cast<const Gd__gd_core__CoreBuff*>(entries[slot].val.obj)->f_current.as_int();\n                const auto stack = buffs->get(gd::GdVal::from_int(type));\n                return stack.kind == gd::GdVal::Kind::Obj && stack.obj\n                    ? static_cast<const Gd__gd_core__CoreBuff*>(stack.obj)->f_current.as_int() : int64_t{0};\n            };\n            const auto bonus = this->f_speedScale.as_float() + static_cast<double>(stacks(107) - stacks(110)) * 0.02;\n            const auto modified = bonus >= 0.0 ? 1.0 + bonus : 1.0 / (1.0 - bonus);\n            speed = modified < 0.1 ? 0.1 : (modified > 10.0 ? 10.0 : modified);\n        } else {\n            speed = this->fn_getSpeed(nullptr, 0).as_float();\n        }\n    }\n\n    const auto delta = argc > 0 ? args[0].as_float() : 0.0;\n    const auto left = uses_override && !override.is_num() ? 0.0 : this->f_triggerTime.as_float() - delta * speed;\n    this->f_triggerTime = gd::GdVal::from_float(left);\n    auto& gd_ctx = *this->rt_ctx_;\n    if (gd::gd_truth(context.f_show_cooldown_progress)) {\n        const gd::GdVal progress[] = {gd::GdVal::from_obj(this), gd::GdVal::from_float(1.0 - left / this->f_iterationCooldown.as_float())};\n        gd::call_method(gd_ctx, context.f_hooks, SYM_GEN_showCooldown_794, progress, 2);\n    }\n    if (this->f_triggerTime.as_float() <= 0.0) gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_trigger_143, nullptr, 0);\n    return gd::GdVal::null();\n}\n'
INPUTS = {'gd_rt.hpp': 'bf6ee43ba5c5a40ced3b217602b01444b5324ecabd4977ba42e13266c52903e0', 'engine_wrapper.cpp': '1dd69d3aa317890b1be03e1e65acb837322ce8ca0c4cbdcbacf85a8aabd45a88', 'gen/shards/shard_00.cpp': 'e39d297289c832f5237609815630ba3cc4bd435345572c04114bfb42e2d1bced', 'gen/shards/shard_03.cpp': '8d7c84ec9a22f4305b9d848e5c80c52e15e7702313349a5592ae379b4b70f3bf'}
OUTPUTS = {'gd_rt.hpp': 'ea652fc873bab9398c8eb5b6b81c54d2a0342bf07c41dbc3df32ac11fccb0837', 'engine_wrapper.cpp': '1b52b9cb1039edc85bfa8ff0b04d06c8804672e3186f8a92496193d7d680bdc8', 'gen/shards/shard_00.cpp': '89d18939aed4537208ecb1db319cfcdbb2b0f88af99bf60e205991c5657b5491', 'gen/shards/shard_03.cpp': '8331645fb7e2aeb9b810635fd2b811e9609499d6340d84c84c583104803ba922'}

CACHE='''// Internal stack cache: discarded at each role phase and around every callback.
struct NativeCooldownSpeedCache {
    const void* character=nullptr;
    double stat_bonus=0.0;
    void invalidate(){character=nullptr;}
};

'''
DECL='''extern gd::GdVal gd_native_cached_physics_tick(Gd__gd_core__CoreItem*,const gd::GdVal*,int,gd::NativeCooldownSpeedCache*);
'''
STATS='''            double stat_bonus;
            if(native_speed_cache && native_speed_cache->character==character) {
                stat_bonus=native_speed_cache->stat_bonus;
            } else {
                stat_bonus=static_cast<double>(stacks(107) - stacks(110)) * 0.02;
                if(native_speed_cache) {
                    native_speed_cache->character=character;
                    native_speed_cache->stat_bonus=stat_bonus;
                }
            }
            const auto bonus = item->f_speedScale.as_float() + stat_bonus;
            const auto modified = bonus >= 0.0 ? 1.0 + bonus : 1.0 / (1.0 - bonus);
            speed = modified < 0.1 ? 0.1 : (modified > 10.0 ? 10.0 : modified);'''

def digest(s):return hashlib.sha256(s.encode()).hexdigest()

def once(s,old,new):
    if s.count(old)!=1:raise ValueError(f'Changed shared-speed source region: {old[:100]}')
    return s.replace(old,new,1)

def patches(native):
    result={}
    result['gd_rt.hpp']=[('struct BattleCtx {',CACHE+'struct BattleCtx {'),
       ('    bool native_inline_timer_headers = false;','    bool native_inline_timer_headers = false;\n    bool native_shared_cooldown_speed = false;'),
       ('        native_inline_timer_headers = false;','        native_inline_timer_headers = false;\n        native_shared_cooldown_speed = false;')]
    result['engine_wrapper.cpp']=[('    battle.native_inline_timer_headers = true;',
       '    battle.native_inline_timer_headers = true;\n    battle.native_shared_cooldown_speed = true;')]
    path='gen/shards/shard_00.cpp'
    old=ORIGINAL_PHYSICS
    body=old.replace('this->','item->')
    body=re.sub(r'\bthis\b','item',body)
    header='gd::GdVal Gd__gd_core__CoreItem::fn_physicsTick(const gd::GdVal* args, int argc) {'
    body=once(body,header,'gd::GdVal gd_native_cached_physics_tick(Gd__gd_core__CoreItem* item,const gd::GdVal* args,int argc,gd::NativeCooldownSpeedCache* native_speed_cache) {')
    body=once(body,'    const auto receiver =',
       '    const bool is_gem=item->meta()->is_subclass_of(&META_Gd__gd_core_items__Gems__Gem);\n    if(is_gem && native_speed_cache) native_speed_cache->invalidate();\n    const auto receiver =')
    body=once(body,'item->meta()->is_subclass_of(&META_Gd__gd_core_items__Gems__Gem)\n        ?', 'is_gem\n        ?')
    body=once(body,'    const auto* character =','    if(is_gem && native_speed_cache) native_speed_cache->invalidate();\n    const auto* character =')
    original='''            const auto bonus = item->f_speedScale.as_float() + static_cast<double>(stacks(107) - stacks(110)) * 0.02;
            const auto modified = bonus >= 0.0 ? 1.0 + bonus : 1.0 / (1.0 - bonus);
            speed = modified < 0.1 ? 0.1 : (modified > 10.0 ? 10.0 : modified);'''
    body=once(body,original,STATS)
    anchor='            speed = item->fn_getSpeed(nullptr, 0).as_float();'
    body=once(body,anchor,'            if(native_speed_cache) native_speed_cache->invalidate();\n'+anchor+'\n            if(native_speed_cache) native_speed_cache->invalidate();')
    anchor='        gd::call_method(gd_ctx, context.f_hooks, SYM_GEN_showCooldown_794, progress, 2);'
    body=once(body,anchor,'        if(native_speed_cache) native_speed_cache->invalidate();\n'+anchor+'\n        if(native_speed_cache) native_speed_cache->invalidate();')
    anchor='    if (item->f_triggerTime.as_float() <= 0.0) gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_trigger_143, nullptr, 0);'
    # from_obj(this) is the only non-member-reference use of this in this method.
    body=body.replace('gd::GdVal::from_obj(this)','gd::GdVal::from_obj(item)')
    anchor=anchor.replace('from_obj(this)','from_obj(item)')
    body=once(body,anchor,'''    if (item->f_triggerTime.as_float() <= 0.0) {
        if(native_speed_cache) native_speed_cache->invalidate();
        gd::call_method(gd_ctx, gd::GdVal::from_obj(item), SYM_GEN_trigger_143, nullptr, 0);
        if(native_speed_cache) native_speed_cache->invalidate();
    }''')
    assert 'this' not in body
    wrapper=header+'\n    return gd_native_cached_physics_tick(this,args,argc,nullptr);\n}'
    result[path]=[('#include "../hdrs/Gd__gd_core__CoreContext.hpp"\n','#include "../hdrs/Gd__gd_core__CoreContext.hpp"\n'),(old,body+'\n\n'+wrapper)]
    path='gen/shards/shard_03.cpp'
    rows=[('#include "../hdrs/Gd__gd_core__CoreItem.hpp"\n','#include "../hdrs/Gd__gd_core__CoreItem.hpp"\n'+DECL)]
    for array,length in (('_t757','_len__t758'),('_t763','_len__t764')):
        anchor=f'        uint32_t {length} = {array} ? {array}->len : 0u;'
        rows.append((anchor,anchor+'\n        gd::NativeCooldownSpeedCache native_speed_state;\n        auto* native_speed_cache=gd_ctx.native_shared_cooldown_speed ? &native_speed_state : nullptr;'))
    for item in ('cooldown_item','cooldown_gem'):
        rows.append((f'{item}->fn_physicsTick(&lv_delta, 1);',f'gd_native_cached_physics_tick({item},&lv_delta,1,native_speed_cache);'))
    result[path]=rows
    return result

def remove_layer(sources):
    """Remove this whole guarded layer; older generator inputs pass through."""
    result=dict(sources)
    if not any('native_shared_cooldown_speed' in sources[name] or 'gd_native_cached_physics_tick' in sources[name]
               for name in INPUTS):return result
    changes=patches(None)
    for name,rows in changes.items():
        s=sources[name]
        if digest(s)!=OUTPUTS[name]:raise ValueError(f'Cannot remove changed shared-speed layer: {name}')
        for old,new in reversed(rows):
            count=2 if old.startswith('cooldown_') else 1
            if s.count(new)!=count:raise ValueError(f'Changed shared-speed reverse site: {name}')
            s=s.replace(new,old)
        if digest(s)!=INPUTS[name]:raise ValueError(f'Cannot normalize changed shared-speed input: {name}')
        result[name]=s
    return result

def add_layer(sources):
    result=remove_layer(sources)
    for name,rows in patches(None).items():
        s=result[name]
        if digest(s)!=INPUTS[name]:raise ValueError(f'Verified shared-speed input changed: {name}')
        for old,new in rows:
            count=2 if old.startswith('cooldown_') else 1
            if s.count(old)!=count:raise ValueError(f'Changed shared-speed site count: {name} {old[:70]}')
            s=s.replace(old,new)
        if digest(s)!=OUTPUTS[name]:raise ValueError(f'Unexpected shared-speed output: {name}')
        result[name]=s
    return result

def optimize(native):
    sources={name:(native/name).read_text('utf8') for name in INPUTS}
    for name,s in add_layer(sources).items():
        path=native/name
        if path.read_bytes()!=s.encode():path.write_text(s,encoding='utf8',newline='\n')
    print('Native role-phase speed cache, live item scale, invalidation around all callback boundaries',flush=True)

if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('native',type=Path);optimize(p.parse_args().native)
