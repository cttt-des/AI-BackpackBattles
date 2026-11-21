#ifdef GD_FRAME_PREFLIGHT
#include "preflight_frame_helper.hpp"
namespace gd {void native_frame_segment_hit(unsigned){}}
#include "preflight_timer_loop.hpp"
#else
#include "native_inline_dispatch.hpp"
#endif
#include "gen/hdrs/Gd__gd_core__CoreCombat.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"
#include "gen/hdrs/Gd__gd_core__CoreTimer.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>
using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;

struct Timer:Gd__gd_core__CoreTimer {
    unsigned id;std::vector<uint64_t>& trace;std::function<void()> callback;
    Timer(gd::BattleCtx* ctx,unsigned i,std::vector<uint64_t>& t):Gd__gd_core__CoreTimer(ctx),id(i),trace(t){}
    bool call_method(gd::BattleCtx& ctx,gd::SymId method,const V* args,int argc,V& out)override {
        if(method!=SYM_GEN_tick_1516)return Gd__gd_core__CoreTimer::call_method(ctx,method,args,argc,out);
        assert(argc==1 && args[0].as_float()==0.25);
        trace.push_back(id);trace.push_back(ctx.math_rng.randi());if(callback)callback();out=V::null();return true;
    }
};
static void original(const gd::GdArr* items,const V& delta) {
    for(uint32_t i=0,count=items->len;i<count;++i) {
        auto* item=static_cast<Item*>(items->data[i].obj);
        if(item->f_timers.arr->len)item->fn__tickTimers(&delta,1);
        const auto* gems=item->f_gems.arr;
        for(uint32_t j=0,count=gems->len;j<count;++j) {
            const auto& slot=gems->data[j];
            if(slot.kind==V::Kind::Obj && slot.obj) {
                auto* gem=static_cast<Item*>(slot.obj);
                if(gem->f_timers.arr->len)gem->fn__tickTimers(&delta,1);
            }
        }
    }
}
static std::vector<uint64_t> run(bool candidate,unsigned count,unsigned mode,unsigned position) {
    gd::BattleCtx ctx;ctx.bind_battle(83);ctx.native_resolved_dispatch=true;ctx.native_resolved_collect=true;
    auto& arena=ctx.arena;
    Gd__gd_core__CoreCombat combat(&ctx);combat.init_fields(ctx);
    Gd__gd_core__CoreCharacter character(&ctx);character.init_fields(ctx);
    Gd__gd_core__CoreGrid grid(&ctx);grid.init_fields(ctx);
    character.f_inventory=V::from_obj(&grid);character.f_buffs=V::from_dict(gd::GdDict::create(arena));
    std::vector<uint64_t> trace;std::vector<Item*> items;std::vector<Timer*> timers;
    for(unsigned i=0;i<count+4;++i) {
        auto* item=arena.make<Item>(&ctx);item->init_fields(ctx);items.push_back(item);
        auto* timer=arena.make<Timer>(&ctx,i,trace);timer->init_fields(ctx);timers.push_back(timer);
    }
    auto activate=[&](unsigned i){items[i]->f_timers.arr->push_back(arena,V::from_obj(timers[i]));};
    auto* inventory=gd::GdArr::create(arena,count+8);
    for(unsigned i=0;i<count;++i)inventory->push_back(arena,V::from_obj(items[i]));
    grid.f_items=V::from_arr(inventory);
    if(count)activate(position);
    if(mode==0 && count>2)activate(count-1);
    if(mode==1 && count)for(unsigned i=0;i<count;++i)if(i!=position && i%3==0)activate(i);
    const auto next=count?(position+1)%count:0;
    if(mode==13 && position+1<count)inventory->data[position+1]=V::from_obj(reinterpret_cast<gd::GdObj*>(uintptr_t{0x1234}));
    if(mode==14 && count) {
        items[position]->f_timers.arr->len=0;activate(count);
        items[position]->f_gems=V::from_arr(gd::GdArr::from_init(arena,{V::from_obj(items[count]),V::from_obj(reinterpret_cast<gd::GdObj*>(uintptr_t{0x1234}))}));
    }
    const V delta=V::from_float(0.25);
    const auto step=[&] {
        const auto* captured=grid.f_items.arr;
        if(!candidate)original(captured,delta);
        else {
#ifdef GD_FRAME_PREFLIGHT
            candidate_timer_loop(ctx,captured,delta);
#else
            const V args[]={V::from_obj(&character),delta};combat.fn__tickCharacterTimers(args,2);
#endif
        }
    };
    bool done=false;
    auto action=[&] {
        if(done)return;done=true;
        switch(mode) {
            case 2:activate(next);break;
            case 3:items[next]->f_timers=V::from_arr(gd::GdArr::from_init(arena,{V::from_obj(timers[next])}));break;
            case 4:activate(count);items[next]->f_gems=V::from_arr(gd::GdArr::from_init(arena,{V::from_obj(items[count])}));break;
            case 5:activate(count);items[position]->f_gems=V::from_arr(gd::GdArr::from_init(arena,{V::from_obj(items[count])}));break;
            case 6:items[next]->f_timers.arr->len=0;break;
            case 7:inventory->invert();break;
            case 8:inventory->data[next]=V::from_obj(items[position]);break;
            case 9:activate(count);inventory->push_back(arena,V::from_obj(items[count]));break;
            case 10:grid.f_items=V::from_arr(gd::GdArr::from_init(arena,{V::from_obj(items[position])}));break;
            case 11:activate(next);step();break;
            case 12:activate(next);items[position]->f_timers.arr->len=0;break;
            case 13:if(position+1<count){activate(position+1);inventory->data[position+1]=V::from_obj(items[position+1]);}break;
            case 14:items[position]->f_gems.arr->data[1]=V::from_obj(items[count+1]);activate(count+1);break;
            case 15:inventory->resize(arena,count+8);for(unsigned i=count;i<count+8;++i)inventory->data[i]=V::from_obj(items[0]);break;
            case 16:items[next]->f_gems=V::from_arr(gd::GdArr::from_init(arena,{V::from_int(1),V::null(),V::from_obj(nullptr)}));break;
        }
    };
    if(count)timers[mode==14?count:position]->callback=action;
    step();step();trace.push_back(ctx.math_rng.pcg.state);trace.push_back(ctx.math_rng.pcg.inc);
    for(auto* item:items){trace.push_back(item->f_timers.arr->len);trace.push_back(item->f_gems.arr->len);}
    return trace;
}
int main() {
    register_gen_syms();unsigned cases=0;
    for(unsigned count=0;count<=33;++count)for(unsigned mode=0;mode<17;++mode)
        for(unsigned position=0;position<std::max(1u,count);++position) {
            auto a=run(false,count,mode,position),b=run(true,count,mode,position);
            if(a!=b){std::cerr<<"timer chunk mismatch n="<<count<<" mode="<<mode<<" position="<<position<<"\n";return 2;}++cases;
        }
    std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"callback_order_rng_live_fields_and_capture_checked\":true}\n";
}
