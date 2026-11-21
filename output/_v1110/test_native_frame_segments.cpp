#ifdef GD_FRAME_PREFLIGHT
#include "preflight_frame_helper.hpp"
namespace gd {static uint64_t preflight_frame_counts[17]{};void native_frame_segment_hit(unsigned i){if(i<17)++preflight_frame_counts[i];}}
#else
#include "native_inline_dispatch.hpp"
extern "C" uint64_t gd_diag_native_frame_segment_stat(unsigned);
#endif
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include <bit>
#include <cassert>
#include <cfenv>
#include <functional>
#include <iostream>
#include <vector>

using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;
using Character=Gd__gd_core__CoreCharacter;
using Buff=Gd__gd_core__CoreBuff;
using Context=Gd__gd_core__CoreContext;
using Rng=Gd__gd_core__CoreRng;
static uint64_t bits(double value){return std::bit_cast<uint64_t>(value);}

struct Callback:gd::GdObj {
    std::function<void(gd::SymId,const V*,int)> callback;
    explicit Callback(gd::BattleCtx* ctx):GdObj(ctx){}
    const gd::GdClassMeta* meta()const override{return nullptr;}
    bool call_method(gd::BattleCtx&,gd::SymId method,const V* args,int argc,V& out)override {
        if(method!=SYM_GEN_showCooldown_794 && method!=SYM_GEN_callBehavior_2689)return false;
        callback(method,args,argc);out=V::null();return true;
    }
};
struct UnknownItem:Item {
    mutable std::function<void()> read_meta;
    explicit UnknownItem(gd::BattleCtx* ctx):Item(ctx){}
    const gd::GdClassMeta* meta()const override {
        if(read_meta)read_meta();return &META_Gd__gd_core__CoreItem;
    }
};
template<class T> T* make(gd::BattleCtx& battle,const gd::GdClassMeta& meta) {
    auto* object=static_cast<T*>(meta.alloc_fn(battle));object->init_fields(battle);return object;
}
struct Result {
    std::vector<uint64_t> values,trace;
    uint64_t state,inc;int flags;
    bool operator==(const Result&)const=default;
};

static Result run(bool candidate,unsigned seed,unsigned mode,unsigned position,unsigned variant) {
    gd::BattleCtx battle(65536);battle.bind_battle(91+seed);
    battle.native_resolved_dispatch=true;battle.native_resolved_collect=true;
    auto* context=make<Context>(battle,META_Gd__gd_core__CoreContext);
    auto* rng=make<Rng>(battle,META_Gd__gd_core__CoreRng);
    rng->f_rng=V::from_rng(&battle.math_rng);context->f_rng=V::from_obj(rng);
    context->f_timer_pass_epoch=V::from_int(17);
    context->f_show_cooldown_progress=V::from_bool(mode==2);
    Character* characters[2];Buff* heat[2];Buff* cold[2];
    for(unsigned side=0;side<2;++side) {
        auto* c=make<Character>(battle,META_Gd__gd_core__CoreCharacter);characters[side]=c;
        auto* buffs=gd::GdDict::create(battle.arena);
        c->f_buffs=V::from_dict(buffs);c->f_stunnedDuration=V::from_float(0.0);
        for(int64_t key=100;key<=110;++key) {
            auto* buff=make<Buff>(battle,META_Gd__gd_core__CoreBuff);
            buff->f_current=V::from_int((key+seed+side)%7);
            buffs->set(battle.arena,V::from_int(key),V::from_obj(buff));
            if(key==107)heat[side]=buff;if(key==110)cold[side]=buff;
        }
    }
    context->f_player=V::from_obj(characters[1]);
    std::vector<Item*> items;std::vector<uint64_t> trace;
    Callback callback(&battle);context->f_hooks=V::from_obj(&callback);
    for(unsigned i=0;i<12;++i) {
        Item* item;
        if(mode==10 && i==position) {
            auto* unknown=battle.arena.make<UnknownItem>(&battle);unknown->init_fields(battle);
            unknown->read_meta=[&]{heat[0]->f_current=V::from_int(83);trace.push_back(991);};
            item=unknown;
        } else if((mode==16 || mode==17) && i==position)
            item=make<Gd__gd_core_items__Gems__Gem>(battle,META_Gd__gd_core_items__Gems__Gem);
        else item=make<Item>(battle,META_Gd__gd_core__CoreItem);
        item->f_ctx=V::from_obj(context);item->f_character_=V::from_obj(characters[0]);
        item->f_placed=V::from_bool(true);item->f__cooldown_active=V::from_bool(true);
        item->f__cooldown_blocked_epoch=V::from_int(-1);
        item->f_triggerTime=V::from_float(3.0+i*.1);
        item->f_speedScale=V::from_float((int(i+seed)%9-4)*.13);
        item->f_iterationCooldown=V::from_float(1.0);item->f_baseCooldownOverride=V::from_float(1.0);
        item->f_doubleActivationChance=V::from_float(0.0);item->f__behavior=V::from_obj(&callback);
        item->f_statDisplayOverrides=V::from_arr(gd::GdArr::create(battle.arena,5));
        item->f_statDisplayOverrides.arr->resize(battle.arena,5);
        items.push_back(item);
    }
    if(mode>=1 && mode<=8 && mode!=2)
        items[position]->f_triggerTime=V::from_float(0.001);
    if(mode==9) {
        for(unsigned i=0;i<12;++i)items[i]->f_character_=V::from_obj(characters[i%2]);
        items[position]->f_speedScale=V::from_float(-0.0);
        characters[0]->f_stunnedDuration=V::from_float(-0.0);
        if(seed==0)items[position]->f_character_=V::from_obj(nullptr);
    }
    if(mode==11)items[position]->f__cooldown_blocked_epoch=V::from_int(17);
    if(mode==12)items[position]->f_placed=V::from_bool(false);
    if(mode==13)items[position]->f_statDisplayOverrides.arr->data[3]=V::from_float(1.75);
    if(mode==14)items[position]->f_statDisplayOverrides.arr->data[3]=V::from_str(gd::make_static_str("override"));
    if(mode==15) {
        const uint64_t payloads[]={UINT64_C(0x7ff8000000000123),UINT64_C(0x7ff0000000000123),
            UINT64_C(0xfff8000000000456),UINT64_C(0xfff0000000000456),
            UINT64_C(0x7ff0000000000000),UINT64_C(0xfff0000000000000),UINT64_C(1),UINT64_C(0x8000000000000000)};
        items[position]->f_speedScale=V::from_float(std::bit_cast<double>(payloads[seed%8]));
        characters[0]->f_stunnedDuration=V::from_float(std::bit_cast<double>(payloads[(seed+1)%8]));
    }
    if(mode==17)items[position]->f_placed=V::from_bool(false);
    if(variant==1)items[(position+1)%12]->f__cooldown_active=V::from_int(1);
    if(variant==2)battle.native_resolved_audit=true;
    if(variant==3)battle.native_resolved_dispatch=false;
    bool done=false;
    callback.callback=[&](gd::SymId method,const V* args,int argc) {
        assert(argc>=2);const auto* caller=static_cast<const Item*>(args[0].obj);
        unsigned id=0;while(id<items.size() && items[id]!=caller)++id;assert(id<items.size());
        trace.push_back(method);trace.push_back(id);
        if(method==SYM_GEN_showCooldown_794)trace.push_back(bits(args[1].as_float()));
        if(done)return;done=true;
        (void)battle.math_rng.randf();
        switch(mode) {
            case 1:heat[0]->f_current=V::from_int(47);break;
            case 2:
                context->f_show_cooldown_progress=V::from_bool(false);cold[0]->f_current=V::from_int(36);
                if(seed&1)items[id]->f_triggerTime=V::from_float(0.0);
                if(seed&2)characters[0]->f_stunnedDuration=V::from_float(1.0);
                break;
            case 3:characters[0]->f_stunnedDuration=V::from_float(2.0);break;
            case 4:items[(id+1)%12]->f_character_=V::from_obj(characters[1]);heat[1]->f_current=V::from_int(59);break;
            case 5:items[(id+1)%12]->f_speedScale=V::from_float(-7.3);break;
            case 6:items[(id+1)%12]->f__cooldown_active=V::from_bool(false);break;
            case 7:{auto* dict=gd::GdDict::create(battle.arena);dict->set(battle.arena,V::from_int(107),V::from_obj(heat[1]));dict->set(battle.arena,V::from_int(110),V::from_obj(cold[1]));characters[0]->f_buffs=V::from_dict(dict);break;}
            case 8:{gd::NativeFrameSegmentSnapshot nested;const V delta=V::from_float(0.0001);for(auto* item:items){if(candidate)gd::native_frame_segment_tick(item,nested,delta);else item->fn_physicsTick(&delta,1);}heat[0]->f_current=V::from_int(67);break;}
            default:break;
        }
    };
    const auto delta=V::from_float(1.0/60.0);gd::NativeFrameSegmentSnapshot snapshot;
    std::feclearexcept(FE_ALL_EXCEPT);
    for(unsigned frame=0;frame<2;++frame) {
        snapshot.clear();
        for(auto* item:items) {
            if(candidate)gd::native_frame_segment_tick(item,snapshot,delta);
            else item->fn_physicsTick(&delta,1);
        }
    }
    Result result;result.flags=std::fetestexcept(FE_ALL_EXCEPT);result.trace=trace;
    result.state=battle.math_rng.pcg.state;result.inc=battle.math_rng.pcg.inc;
    for(auto* item:items) {
        for(const auto& value:{item->f_triggerTime,item->f_iterationCooldown,item->f_speedScale}) {
            result.values.push_back(unsigned(value.kind));result.values.push_back(bits(value.as_float()));
        }
        result.values.push_back(item->f__cooldown_active.as_int());
    }
    for(unsigned side=0;side<2;++side) {
        result.values.push_back(bits(characters[side]->f_stunnedDuration.as_float()));
        result.values.push_back(heat[side]->f_current.as_int());result.values.push_back(cold[side]->f_current.as_int());
    }
    result.values.push_back(rng->f_draw_seq.as_int());
    return result;
}

int main() {
    register_gen_syms();unsigned cases=0;
    for(unsigned seed=0;seed<8;++seed)for(unsigned mode=0;mode<18;++mode)
        for(unsigned position=0;position<12;++position)for(unsigned variant=0;variant<4;++variant) {
            auto a=run(false,seed,mode,position,variant),b=run(true,seed,mode,position,variant);
            if(!(a==b)){std::cerr<<"frame mismatch seed="<<seed<<" mode="<<mode<<" position="<<position<<" variant="<<variant<<" values="<<(a.values==b.values)<<" trace="<<(a.trace==b.trace)<<" rng="<<(a.state==b.state)<<" flags="<<a.flags<<","<<b.flags<<"\n";return 2;}
            ++cases;
        }
    auto counter=[](unsigned i){
#ifdef GD_FRAME_PREFLIGHT
        return gd::preflight_frame_counts[i];
#else
        return gd_diag_native_frame_segment_stat(i);
#endif
    };
    for(unsigned i:{0u,1u,2u,3u,4u,5u,6u,7u,8u})assert(counter(i)>0);
    std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"counts\":[";
    for(unsigned i=0;i<17;++i){if(i)std::cout<<',';std::cout<<counter(i);}std::cout<<"]}\n";
}
