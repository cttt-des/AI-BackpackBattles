#include "gen/hdrs/Gd__gd_core__CoreCombat.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreTimer.hpp"
#include "gen/hdrs/Gd__gd_core__CoreHooks.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;
struct Timer : Gd__gd_core__CoreTimer {
    int id;
    std::vector<int>* events;
    std::function<void()> callback;
    Timer(gd::BattleCtx* c,int i,std::vector<int>* e):Gd__gd_core__CoreTimer(c),id(i),events(e) {}
    bool call_method(gd::BattleCtx& c,gd::SymId method,const V* args,int argc,V& out) override {
        if(method!=SYM_GEN_tick_1516) return Gd__gd_core__CoreTimer::call_method(c,method,args,argc,out);
        assert(argc==1 && args[0].as_float()==0.25);
        events->push_back(id);if(callback)callback();out=V::null();return true;
    }
};
struct Comparator : Gd__gd_core__CoreHooks {
    std::function<void()> callback;
    gd::SymId method;
    Comparator(gd::BattleCtx* c):Gd__gd_core__CoreHooks(c),method(gd::intern_sym("sparse_timer_sort")) {}
    bool call_method(gd::BattleCtx& c,gd::SymId m,const V* args,int argc,V& out) override {
        if(m!=method)return Gd__gd_core__CoreHooks::call_method(c,m,args,argc,out);
        if(callback)callback();out=V::from_bool(args[0].obj>args[1].obj);return true;
    }
};

std::vector<int> run(bool enabled,int scenario) {
    gd::BattleCtx battle;
    battle.native_inline_timer_headers=true;
    battle.native_resolved_dispatch=true;
    battle.native_sparse_timer_scans=enabled;
    auto& arena=battle.arena;
    Gd__gd_core__CoreCombat combat(&battle);combat.init_fields(battle);
    Gd__gd_core__CoreCharacter character(&battle);character.init_fields(battle);
    Gd__gd_core__CoreGrid grid(&battle);grid.init_fields(battle);
    character.f_inventory=V::from_obj(&grid);
    std::vector<int> events;
    std::vector<Item*> items;
    std::vector<Timer*> timers;
    for(int i=0;i<8;++i) {
        auto* item=static_cast<Item*>(META_Gd__gd_core__CoreItem.alloc_fn(battle));item->init_fields(battle);items.push_back(item);
        auto* timer=arena.make<Timer>(&battle,i,&events);timer->init_fields(battle);timers.push_back(timer);
    }
    auto activate=[&](int i) {items[i]->f_timers.arr->push_back(arena,V::from_obj(timers[i]));};
    activate(0);activate(4);
    auto* inventory=gd::GdArr::create(arena,16);
    for(int i=0;i<6;++i)inventory->push_back(arena,V::from_obj(items[i]));
    grid.f_items=V::from_arr(inventory);
    const V args[]={V::from_obj(&character),V::from_float(0.25)};
    auto tick=[&]{combat.fn__tickCharacterTimers(args,2);};
    tick();assert((events==std::vector<int>{0,4}));events.clear();
    if(enabled && gd::native_timer_scan_state().epoch!=UINT64_MAX)
        assert(character.native_timer_scan_cache_.count==2);
    bool done=false;
    auto replace=[&](int i,gd::SymId property,std::initializer_list<V> values) {
        auto receiver=V::from_obj(items[i]);
        gd::set_prop(battle,receiver,property,V::from_arr(gd::GdArr::from_init(arena,values)));
    };
    if(scenario==11)inventory->set_idx(2,V::from_obj(reinterpret_cast<gd::GdObj*>(uintptr_t{0x1234})));
    if(scenario==12)inventory->set_idx(2,V::from_int(123));
    if(scenario==17 || scenario==18) {
        activate(6);replace(0,SYM_GEN_gems_41,{V::from_obj(items[6])});
    }
    timers[0]->callback=[&] {
        if(done)return;done=true;
        switch(scenario) {
            case 1:activate(3);break;
            case 2:replace(2,SYM_GEN_timers_67,{V::from_obj(timers[2])});break;
            case 3:activate(6);replace(1,SYM_GEN_gems_41,{V::from_obj(items[6])});break;
            case 4:activate(6);replace(0,SYM_GEN_gems_41,{V::from_obj(items[6])});break;
            case 5:grid.f_items=V::from_arr(gd::GdArr::from_init(arena,{V::from_obj(items[4])}));break;
            case 6:activate(6);inventory->push_back(arena,V::from_obj(items[6]));break;
            case 7:inventory->invert();break;
            case 8:inventory->remove_at(2);break;
            case 9:inventory->resize(arena,2);break;
            case 10:items[4]->f_timers.arr->resize(arena,0);break;
            case 11:case 12:activate(2);inventory->set_idx(2,V::from_obj(items[2]));break;
            case 13:activate(2);tick();break;
            case 14:inventory->set_idx(2,V::from_obj(items[4]));break;
            case 15:inventory->insert_at(arena,1,V::from_obj(items[4]));break;
            case 16:gd::call_method(battle,V::from_arr(items[4]->f_timers.arr),gd::SYM_clear,nullptr,0);break;
            case 19:inventory->fill(V::from_obj(items[4]));break;
            case 20:activate(2);items[2]->f_timers.arr->push_back(arena,V::from_obj(timers[3]));break;
        }
    };
    timers[6]->callback=[&] {
        if(scenario==17) {activate(7);replace(0,SYM_GEN_gems_41,{V::from_obj(items[6]),V::from_obj(items[7])});}
        if(scenario==18)activate(3);
    };
    if(scenario>=21 && scenario<=23) {
        Comparator comparator(&battle);comparator.init_fields(battle);
        bool compared=false;
        comparator.callback=[&] {
            if(compared)return;compared=true;
            if(scenario==23)gd::native_timer_scan_mark(battle,V::from_arr(inventory));
            activate(2);tick();
        };
        if(scenario==22 || scenario==23)inventory->native_timer_scan_tracked=false;
        gd::sort_custom_stable(battle,inventory,&comparator,comparator.method);
        tick();
    } else {tick();tick();}
    assert(gd::native_timer_scan_state().depth==0 && gd::native_timer_scan_state().sorting==0);
    return events;
}

int main() {
    register_gen_syms();
    for(int scenario=0;scenario<24;++scenario) {
        auto dense=run(false,scenario),sparse=run(true,scenario);
        if(dense!=sparse) {std::cerr<<"Differential scenario failed: "<<scenario<<"\n";return 1;}
    }
    // Saturation must permanently fall back rather than reuse an ambiguous epoch.
    gd::native_timer_scan_state().epoch=UINT64_MAX;
    for(int scenario=0;scenario<21;++scenario)assert(run(false,scenario)==run(true,scenario));
    std::cout<<"24 dense/indexed scenarios and 21 saturated-epoch scenarios passed: aliases, mutation order, same-frame timers/gems, captured length, repaired placeholders, nested phases and sort callbacks\n";
}
