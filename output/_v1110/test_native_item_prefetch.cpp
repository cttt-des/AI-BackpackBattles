#include "gen/hdrs/Gd__gd_core__CoreCombat.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreTimer.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;

struct Timer : Gd__gd_core__CoreTimer {
    int identifier;
    std::vector<int>* calls;
    std::function<void()> callback;
    Timer(gd::BattleCtx* battle,int id,std::vector<int>* events)
        : Gd__gd_core__CoreTimer(battle),identifier(id),calls(events) {}
    bool call_method(gd::BattleCtx& battle,gd::SymId method,const V* args,int argc,V& out) override {
        if (method != SYM_GEN_tick_1516)
            return Gd__gd_core__CoreTimer::call_method(battle,method,args,argc,out);
        assert(argc==1 && args[0].as_float()==0.25);
        calls->push_back(identifier);
        if(callback)callback();
        out=V::null();return true;
    }
};

int main() {
    register_gen_syms();
    gd::BattleCtx battle;
    auto& arena=battle.arena;
    Gd__gd_core__CoreCombat combat(&battle);combat.init_fields(battle);
    Gd__gd_core__CoreCharacter character(&battle);character.init_fields(battle);
    Gd__gd_core__CoreGrid grid(&battle);grid.init_fields(battle);
    character.f_inventory=V::from_obj(&grid);
    std::vector<int> events;
    std::vector<Item*> items;
    std::vector<Timer*> timers;
    for(int i=0;i<8;++i) {
        auto* item=arena.make<Item>(&battle);item->init_fields(battle);
        auto* timer=arena.make<Timer>(&battle,i,&events);timer->init_fields(battle);
        item->f_timers=V::from_arr(gd::GdArr::from_init(arena,{V::from_obj(timer)}));
        item->f_gems=V::from_arr(gd::GdArr::create(arena));
        items.push_back(item);timers.push_back(timer);
    }
    gd::GdArr* inventory=nullptr;
    auto reset=[&] {
        events.clear();
        for(int i=0;i<8;++i) {
            timers[i]->callback={};
            items[i]->f_timers=V::from_arr(gd::GdArr::from_init(arena,{V::from_obj(timers[i])}));
            items[i]->f_gems=V::from_arr(gd::GdArr::create(arena));
        }
        inventory=gd::GdArr::create(arena,8);
        for(int i=0;i<6;++i)inventory->push_back(arena,V::from_obj(items[i]));
        grid.f_items=V::from_arr(inventory);
    };
    auto run=[&](std::vector<int> expected) {
        const V args[]={V::from_obj(&character),V::from_float(0.25)};
        combat.fn__tickCharacterTimers(args,2);
        assert(events==expected);
    };

    reset();run({0,1,2,3,4,5});
    reset();
    // This placeholder is repaired by the preceding callback before its real visit.
    // A prefetch may form its integer address, but must never dereference it.
    inventory->set_idx(2,V::from_obj(reinterpret_cast<gd::GdObj*>(uintptr_t{0x1234})));
    timers[0]->callback=[&]{inventory->set_idx(2,V::from_obj(items[2]));};
    run({0,1,2,3,4,5});

    reset();
    inventory->set_idx(2,V::from_int(123));
    timers[0]->callback=[&]{inventory->set_idx(2,V::from_obj(items[7]));};
    run({0,1,7,3,4,5});

    reset();
    timers[0]->callback=[&]{inventory->push_back(arena,V::from_obj(items[6]));};
    run({0,1,2,3,4,5});assert(inventory->len==7);

    reset();
    timers[0]->callback=[&]{items[3]->f_timers.arr->len=0;};
    run({0,1,2,4,5});

    reset();
    timers[0]->callback=[&]{
        grid.f_items=V::from_arr(gd::GdArr::from_init(arena,{V::from_obj(items[7])}));
    };
    run({0,1,2,3,4,5});

    reset();
    timers[0]->callback=[&]{items[0]->f_gems=V::from_arr(gd::GdArr::from_init(arena,{V::from_obj(items[6])}));};
    run({0,6,1,2,3,4,5});

    reset();
    timers[0]->callback=[&]{inventory->resize(arena,2);};
    run({0,1,2,3,4,5});assert(inventory->len==2);
    std::cout<<"Timer traversal, repaired future placeholder, replacement, append, disable, array swap, gem insertion and captured-length shrink passed\n";
}
