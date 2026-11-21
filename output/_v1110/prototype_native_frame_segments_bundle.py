"""Reuse character reads only until the next callback; skip empty timer chunks."""
import hashlib
from pathlib import Path
from prototype_native_typed_read_bundle import optimize as retained
from optimize_native_ordered_nan import optimize as ordered_nan

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'


def replace(text,old,new,count=1):
    assert text.count(old)==count,(old[:120],text.count(old))
    return text.replace(old,new)


SNAPSHOT='''
void native_frame_segment_hit(unsigned);
struct NativeFrameSegmentSnapshot {
    const Gd__gd_core__CoreCharacter* stun_character=nullptr;
    const Gd__gd_core__CoreCharacter* speed_character=nullptr;
    bool stunned_value=false;
    double speed_value=0.0;
    void clear() {stun_character=nullptr;speed_character=nullptr;}
    bool stunned(const Gd__gd_core__CoreCharacter* character,bool collect) {
        if(stun_character!=character) {
            stunned_value=character->f_stunnedDuration.as_float()>0.0;
            stun_character=character;
            if(collect)native_frame_segment_hit(1);
        } else if(collect)native_frame_segment_hit(2);
        return stunned_value;
    }
    template<class Compute> double speed_increment(
            const Gd__gd_core__CoreCharacter* character,bool collect,Compute compute) {
        if(speed_character!=character) {
            speed_value=compute();speed_character=character;
            if(collect)native_frame_segment_hit(3);
        } else if(collect)native_frame_segment_hit(4);
        return speed_value;
    }
};
'''


def frame_helper(native):
    source=(native/'gen/shards/shard_00.cpp').read_text('utf8')
    start=source.index('gd::GdVal Gd__gd_core__CoreItem::fn_physicsTick(')
    end=source.index('\ngd::GdVal ',start+1)
    original=source[start:end]
    body=original[original.index('{')+1:original.rindex('}')]
    body=body.replace('this->','item->').replace('(this)', '(item)').replace(',this,',',item,')
    # The self-type predicate originally has the bare receiver as its argument.
    body=body.replace(',this,',',item,').replace('*>(this)', '*>(item)')
    body=body.replace('return gd::GdVal::null();','return;')
    body=replace(body,'argc > 0 ? args[0].as_float() : 0.0','delta_value.as_float()')
    body=replace(body,'static_cast<Gd__gd_core_items__Gems__Gem*>(item)->fn_character(nullptr, 0)',
        '(snapshot.clear(), native_frame_segment_hit_if(collect,6), static_cast<Gd__gd_core_items__Gems__Gem*>(item)->fn_character(nullptr, 0))')
    body=replace(body,'character && character->f_stunnedDuration.as_float() > 0.0',
        'character && snapshot.stunned(character,collect)')
    body=replace(body,'static_cast<double>(stacks(107) - stacks(110)) * 0.02',
        'snapshot.speed_increment(character,collect,[&] {return static_cast<double>(stacks(107) - stacks(110)) * 0.02;})')
    body=replace(body,'speed = item->fn_getSpeed(nullptr, 0).as_float();',
        'snapshot.clear(); speed = item->fn_getSpeed(nullptr, 0).as_float();')
    body=replace(body,'        gd::native_inline_call(gd_ctx, context.f_hooks, SYM_GEN_showCooldown_794, progress, 2);',
        '        snapshot.clear(); native_frame_segment_hit_if(collect,7);\n        gd::native_inline_call(gd_ctx, context.f_hooks, SYM_GEN_showCooldown_794, progress, 2);')
    body=replace(body,'if (item->f_triggerTime.as_float() <= 0.0) gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(item), SYM_GEN_trigger_143, nullptr, 0);',
        'if (item->f_triggerTime.as_float() <= 0.0) { snapshot.clear(); native_frame_segment_hit_if(collect,8); gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(item), SYM_GEN_trigger_143, nullptr, 0); }')
    assert 'this' not in body and 'argc' not in body and 'args[' not in body
    guard='''
    const auto* row=item->native_call_row_;
    auto* battle=item->rt_ctx_;
    const bool collect=battle && battle->native_resolved_collect;
    if(!battle || !battle->native_resolved_dispatch || !row ||
       (battle->native_resolved_audit && !native_resolved_row_matches(item,row)) || !row->metadata) {
        snapshot.clear();native_frame_segment_hit_if(collect,5);
        item->fn_physicsTick(&delta_value,1);return;
    }
    native_frame_segment_hit_if(collect,0);
'''
    helper=SNAPSHOT+'''inline void native_frame_segment_hit_if(bool collect,unsigned index) {
    if(collect)native_frame_segment_hit(index);
}
inline void native_frame_segment_tick(Gd__gd_core__CoreItem* item,
        NativeFrameSegmentSnapshot& snapshot,const GdVal& delta_value) {
'''+guard+body+'}\n'
    return helper,original


def timer_loop():
    tick='''        auto* item = static_cast<Gd__gd_core__CoreItem*>(items->data[i].obj);
        if (item->f_timers.arr->len) item->fn__tickTimers(&delta, 1);
        const auto* gems = item->f_gems.arr;
        for (uint32_t j = 0, sockets = gems->len; j < sockets; ++j) {
            const auto& slot = gems->data[j];
            if (slot.kind == gd::GdVal::Kind::Obj && slot.obj) {
                auto* gem = static_cast<Gd__gd_core__CoreItem*>(slot.obj);
                if (gem->f_timers.arr->len) gem->fn__tickTimers(&delta, 1);
            }
        }'''
    old='    for (uint32_t i = 0, count = items->len; i < count; ++i) {\n'+tick+'\n    }'
    checks='\n            && '.join(f'inactive(i+{j})' for j in range(8))
    new='''    const bool collect=this->rt_ctx_->native_resolved_collect;
    const auto count=items->len;
    if(collect) {gd::native_frame_segment_hit(9);for(uint32_t k=0;k<count;++k)gd::native_frame_segment_hit(10);}
    const auto inactive=[&](uint32_t index) {
        if(collect)gd::native_frame_segment_hit(15);
        const auto* item=static_cast<const Gd__gd_core__CoreItem*>(items->data[index].obj);
        if(item->f_timers.arr->len)return false;
        const auto* gems=item->f_gems.arr;
        for(uint32_t j=0,n=gems->len;j<n;++j) {
            if(collect)gd::native_frame_segment_hit(16);
            const auto& slot=gems->data[j];
            if(slot.kind==gd::GdVal::Kind::Obj && slot.obj &&
               static_cast<const Gd__gd_core__CoreItem*>(slot.obj)->f_timers.arr->len)return false;
        }
        return true;
    };
    uint32_t i=0;
    while(count-i>=8) {
        if(collect)gd::native_frame_segment_hit(11);
        // Stop at the first callback-capable parent. No later eligibility is read.
        if('''+checks+''') {
            if(collect) {gd::native_frame_segment_hit(12);for(unsigned k=0;k<8;++k)gd::native_frame_segment_hit(13);}
            i+=8;continue;
        }
        const auto end=i+8;
        for(;i<end;++i) {
            if(collect)gd::native_frame_segment_hit(14);
'''+tick+'''
        }
    }
    for(;i<count;++i) {
        if(collect)gd::native_frame_segment_hit(14);
'''+tick+'''
    }'''
    return old,new


def optimize(native):
    report=retained(native)
    report.update(ordered_nan(native))
    helper,original=frame_helper(native)
    path=native/'native_inline_dispatch.hpp';text=path.read_text('utf8')
    if '#include "gen/hdrs/Gd__gd_core_items__Gems__Gem.hpp"' not in text:
        text=replace(text,'#include <cstddef>','#include <cstddef>\n#include "gen/hdrs/Gd__gd_core_items__Gems__Gem.hpp"')
    text=replace(text,'} // namespace gd',helper+'\n} // namespace gd')
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'gen/shards/shard_03.cpp';text=path.read_text('utf8')
    anchor='gd::GdVal Gd__gd_core__CoreCombat::fn_physicsTick(const gd::GdVal* _args, int _argc) {'
    text=replace(text,anchor,anchor+'\n    gd::NativeFrameSegmentSnapshot native_segment_snapshot;')
    text=replace(text,'cooldown_item->fn_physicsTick(&lv_delta, 1);',
        'gd::native_frame_segment_tick(cooldown_item,native_segment_snapshot,lv_delta);',2)
    text=replace(text,'cooldown_gem->fn_physicsTick(&lv_delta, 1);',
        '{native_segment_snapshot.clear();cooldown_gem->fn_physicsTick(&lv_delta, 1);}',2)
    for side in ('opponent','player'):
        line=f'    (void)([&]() {{ gd::GdVal _ca[] = {{lv_delta}}; return {side}()->fn_physicsTickCharacter(_ca, 1); }})();'
        text=replace(text,line,'    native_segment_snapshot.clear();\n'+line)
    old,new=timer_loop();text=replace(text,old,new)
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'engine_wrapper.cpp';text=path.read_text('utf8')
    text+='''
namespace gd {
static thread_local uint64_t native_frame_segment_counts[17]{};
void native_frame_segment_hit(unsigned index) {if(index<17)++native_frame_segment_counts[index];}
}
extern "C" uint64_t gd_diag_native_frame_segment_stat(unsigned index) {
    return index<17 ? gd::native_frame_segment_counts[index] : 0;
}
'''
    path.write_text(text,encoding='utf8',newline='\n')
    assert original in (native/'gen/shards/shard_00.cpp').read_text('utf8')
    report.update(status='implemented_uncompiled_unmeasured',
        components=report['components']+['callback-bounded character stun/shared-speed snapshots','eight-parent short-circuit empty timer chunks','preserved deployed two-NaN operand choice'],
        original_item_physics_sha256=hashlib.sha256(original.encode()).hexdigest(),
        original_item_physics_preserved_as_oracle=True,
        no_new_object_context_or_array_layout=True,
        no_persistent_index_or_mutation_tracking=True,
        arithmetic_inline_package_removed=True,
        barriers=['before each character physics callback','before each active socket gem','Gem.character method','unknown/disabled/audit-mismatched receiver','getSpeed fallback','cooldown display callback','trigger callback'],
        timer_checks='Captured original count; ordered short-circuit stops before any callback-capable parent; failed chunks execute original live body and original gem count capture.')
    return report
