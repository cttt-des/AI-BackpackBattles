#include "native_cooldown_scan.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCombat.hpp"
#include "gen/hdrs/Gd__gd_core__CoreHooks.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>

using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;
struct Comparator : Gd__gd_core__CoreHooks {
    std::function<void()> callback;
    std::vector<Item*>* items;
    gd::SymId method;
    Comparator(gd::BattleCtx* c,std::vector<Item*>* list):Gd__gd_core__CoreHooks(c),items(list),method(gd::intern_sym("cooldown_index_sort")) {}
    bool call_method(gd::BattleCtx& c,gd::SymId m,const V* args,int argc,V& out) override {
        if(m!=method)return Gd__gd_core__CoreHooks::call_method(c,m,args,argc,out);
        if(callback)callback();
        auto index=[&](const V& v){return std::find(items->begin(),items->end(),v.obj);};
        out=V::from_bool(index(args[0])>index(args[1]));return true;
    }
};

std::vector<int> run(bool enabled,int scenario) {
    gd::BattleCtx battle;
    battle.native_inline_timer_headers=true;battle.native_sparse_cooldown_scans=enabled;
    auto& arena=battle.arena;
    Gd__gd_core__CoreCombat combat(&battle);combat.init_fields(battle);
    auto& cache=combat.native_cooldown_scan_caches_[0];
    std::vector<Item*> items;
    std::vector<int> events;
    for(int i=0;i<8;++i){auto* item=arena.make<Item>(&battle);item->init_fields(battle);items.push_back(item);}
    auto set=[&](int i,gd::SymId property,V value){auto receiver=V::from_obj(items[i]);gd::set_prop(battle,receiver,property,value);};
    auto active=[&](int i,bool value=true){set(i,SYM_GEN__cooldown_active_44,V::from_bool(value));};
    auto gems=[&](int i,std::initializer_list<V> values){set(i,SYM_GEN_gems_41,V::from_arr(gd::GdArr::from_init(arena,values)));};
    active(0);active(4);
    auto* inventory=gd::GdArr::create(arena,16);
    for(int i=0;i<6;++i)inventory->push_back(arena,V::from_obj(items[i]));
    std::function<void(int)> callback;
    auto visit=[&](Item* item) {
        if(!gd::gd_truth(item->f__cooldown_active))return;
        int id=static_cast<int>(std::find(items.begin(),items.end(),item)-items.begin());
        events.push_back(id);if(callback)callback(id);
    };
    // Use the production selector with the original parent/gem processing order.
    auto step=[&] {
        const auto* captured=inventory;const uint32_t count=captured->len;
        gd::NativeCooldownCursor cursor(battle,cache,captured,count);
        for(uint32_t i=cursor.next();i<count;i=cursor.next()) {
            auto* item=static_cast<Item*>(captured->data[i].obj);visit(item);
            const auto* sockets=item->f_gems.arr;
            for(uint32_t j=0,n=sockets->len;j<n;++j) {
                const auto slot=sockets->data[j];
                if(!slot.is_null())visit(static_cast<Item*>(slot.obj));
            }
        }
    };
    step();assert((events==std::vector<int>{0,4}));events.clear();
    if(enabled && gd::native_cooldown_scan_state().epoch!=UINT64_MAX)assert(cache.count==2);
    if(scenario==11)inventory->set_idx(2,V::from_obj(reinterpret_cast<gd::GdObj*>(uintptr_t{0x1234})));
    if(scenario==12)inventory->set_idx(2,V::from_int(123));
    if(scenario==17 || scenario==18){active(6);gems(0,{V::from_obj(items[6])});}
    if(scenario==24)set(2,SYM_GEN__cooldown_active_44,V::from_float(0.0));
    if(scenario==25)set(2,SYM_GEN__cooldown_active_44,V::from_int(1));
    bool done=false;
    callback=[&](int id) {
        if(id==6) {
            if(scenario==17){active(7);gems(0,{V::from_obj(items[6]),V::from_obj(items[7])});}
            if(scenario==18)active(3);
            return;
        }
        if(id!=0 || done)return;done=true;
        switch(scenario) {
            case 1:active(3);break;
            case 2:active(2);active(0,false);break;
            case 3:active(6);gems(1,{V::from_obj(items[6])});break;
            case 4:active(6);gems(0,{V::from_obj(items[6])});break;
            case 5:inventory=gd::GdArr::from_init(arena,{V::from_obj(items[4])});break;
            case 6:active(6);inventory->push_back(arena,V::from_obj(items[6]));break;
            case 7:inventory->invert();break;
            case 8:inventory->remove_at(2);break;
            case 9:inventory->resize(arena,2);break;
            case 10:active(4,false);break;
            case 11:case 12:active(2);inventory->set_idx(2,V::from_obj(items[2]));break;
            case 13:active(2);step();break;
            case 14:inventory->set_idx(2,V::from_obj(items[4]));break;
            case 15:inventory->insert_at(arena,1,V::from_obj(items[4]));break;
            case 16:gd::call_method(battle,V::from_arr(items[4]->f_gems.arr),gd::SYM_clear,nullptr,0);break;
            case 19:inventory->fill(V::from_obj(items[4]));break;
            case 20:cache={};active(2);break;
            case 26:active(3);active(3,false);active(3);break;
            case 27:active(4,false);active(4);break;
        }
    };
    if(scenario>=21 && scenario<=23) {
        Comparator comparator(&battle,&items);comparator.init_fields(battle);bool compared=false;
        comparator.callback=[&] {
            if(compared)return;compared=true;
            if(scenario==23)gd::native_cooldown_scan_mark(battle,V::from_arr(inventory));
            active(2);step();
        };
        if(scenario==22 || scenario==23)inventory->native_cooldown_scan_tracked=false;
        gd::sort_custom_stable(battle,inventory,&comparator,comparator.method);step();
    } else {step();step();}
    assert(gd::native_cooldown_scan_state().depth==0 && gd::native_cooldown_scan_state().sorting==0);
    return events;
}

int main() {
    register_gen_syms();
    for(int scenario=0;scenario<28;++scenario) {
        auto dense=run(false,scenario),indexed=run(true,scenario);
        if(dense!=indexed){std::cerr<<"Cooldown differential scenario failed: "<<scenario<<"\n";return 1;}
    }
    gd::native_cooldown_scan_state().epoch=UINT64_MAX;
    for(int scenario=0;scenario<28;++scenario)assert(run(false,scenario)==run(true,scenario));
    std::cout<<"28 cooldown selector/dense and 28 saturated scenarios passed: active changes, stop/restart, aliases, gem insertion, captured lengths, repaired placeholders, nested phases, sort callbacks, nonbool values and cache reset\n";
}
