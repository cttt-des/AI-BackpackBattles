#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCombat.hpp"
#include "gen/hdrs/Gd__gd_core__CoreTimer.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;

bool within(const Item* object,const gd::GdArr* header) {
    const auto base=reinterpret_cast<uintptr_t>(object);
    const auto address=reinterpret_cast<uintptr_t>(header);
    return address>=base && address-base+sizeof(gd::GdArr)<=sizeof(Item);
}

struct Timer : Gd__gd_core__CoreTimer {
    int id;
    std::vector<int>* events;
    std::function<void()> callback;
    Timer(gd::BattleCtx* battle,int number,std::vector<int>* calls)
        : Gd__gd_core__CoreTimer(battle),id(number),events(calls) {}
    bool call_method(gd::BattleCtx& battle,gd::SymId method,const V* args,int argc,V& out) override {
        if(method!=SYM_GEN_tick_1516)
            return Gd__gd_core__CoreTimer::call_method(battle,method,args,argc,out);
        assert(argc==1 && args[0].as_float()==0.25);
        events->push_back(id);
        if(callback)callback();
        out=V::null();return true;
    }
};

int main() {
    register_gen_syms();
    gd::BattleCtx external(256);
    gd::GdArr* escaped=nullptr;
    {
        Item stack(&external);stack.init_fields(external);
        escaped=stack.f_timers.arr;
        assert(!within(&stack,escaped));
        escaped->push_back(external.arena,V::from_int(10));
    }
    escaped->push_back(external.arena,V::from_int(11));
    assert(escaped->len==2 && escaped->data[0].i==10);
    auto* destroyed=external.arena.make<Item>(&external);destroyed->init_fields(external);
    auto* after_destruction=destroyed->f_timers.arr;
    assert(!within(destroyed,after_destruction));
    destroyed->~Item();
    after_destruction->push_back(external.arena,V::from_int(12));
    assert(after_destruction->len==1);

    Item reinitialized(&external);reinitialized.init_fields(external);
    auto* old=reinitialized.f_timers.arr;
    old->push_back(external.arena,V::from_int(20));
    reinitialized.init_fields(external);
    assert(reinitialized.f_timers.arr!=old && reinitialized.f_timers.arr->len==0);
    assert(old->len==1 && old->data[0].i==20);

#ifdef GD_INLINE_TIMER_CANDIDATE
    gd::BattleCtx native(256);native.native_inline_timer_headers=true;
    // Opt-in alone does not embed headers in objects outside the owning arena.
    {
        Item stack(&native);stack.init_fields(native);
        escaped=stack.f_timers.arr;
        assert(!within(&stack,escaped) && !stack.native_timer_header_used_);
    }
    escaped->push_back(native.arena,V::from_int(30));assert(escaped->len==1);

    auto* item=native.arena.make<Item>(&native);item->init_fields(native);
    assert(reinterpret_cast<uintptr_t>(item)%64==0);
    assert(item->f_timers.arr==&item->native_timer_header_ && within(item,item->f_timers.arr));
    const auto value_line=reinterpret_cast<uintptr_t>(&item->f_timers)/64;
    assert(value_line==reinterpret_cast<uintptr_t>(&item->f_timers.arr->len)/64);
    auto* first=item->f_timers.arr;
    first->push_back(native.arena,V::from_int(40));
    item->init_fields(native);
    auto* second=item->f_timers.arr;
    assert(second!=first && !within(item,second) && second->len==0);
    first->push_back(native.arena,V::from_int(41));
    assert(first->len==2 && second->len==0);
    second->push_back(native.arena,V::from_int(42));
    item->init_fields(native);
    assert(item->f_timers.arr!=second && item->f_timers.arr->len==0);
    assert(first->len==2 && second->len==1);

    auto* original=native.arena.make<Item>(&native);original->init_fields(native);
    original->f_timers.arr->push_back(native.arena,V::from_int(50));
    auto* original_alias=original->f_timers.arr;
    auto* copy=native.arena.make<Item>(*original);
    assert(copy->f_timers.arr==original_alias);
    copy->init_fields(native);
    assert(copy->f_timers.arr!=original_alias && !within(copy,copy->f_timers.arr));
    assert(original_alias->len==1 && original_alias->data[0].i==50);
    Item moved(std::move(*original));
    assert(moved.f_timers.arr==original_alias);
    moved.init_fields(native);
    assert(moved.f_timers.arr!=original_alias && original_alias->len==1);

    gd::BattleCtx other(256);other.native_inline_timer_headers=true;
    auto* foreign=native.arena.make<Item>(&native);
    foreign->init_fields(other);
    assert(!within(foreign,foreign->f_timers.arr));
    assert(other.arena.owns_storage(foreign->f_timers.arr,sizeof(gd::GdArr)));

    Gd__gd_core__CoreCharacter character(&native);character.init_fields(native);
    Gd__gd_core__CoreGrid grid(&native);grid.init_fields(native);
    Gd__gd_core__CoreCombat combat(&native);combat.init_fields(native);
    character.f_inventory=V::from_obj(&grid);
    auto* a=native.arena.make<Item>(&native);a->init_fields(native);
    auto* b=native.arena.make<Item>(&native);b->init_fields(native);
    assert(within(a,a->f_timers.arr) && within(b,b->f_timers.arr));
    grid.f_items=V::from_arr(gd::GdArr::from_init(native.arena,{V::from_obj(a),V::from_obj(b)}));
    std::vector<int> calls;
    auto* zero=native.arena.make<Timer>(&native,0,&calls);zero->init_fields(native);
    auto* one=native.arena.make<Timer>(&native,1,&calls);one->init_fields(native);
    a->f_timers.arr->push_back(native.arena,V::from_obj(zero));
    zero->callback=[&]{b->f_timers.arr->push_back(native.arena,V::from_obj(one));};
    const V args[]={V::from_obj(&character),V::from_float(0.25)};
    combat.fn__tickCharacterTimers(args,2);
    assert((calls==std::vector<int>{0,1}));
    native.reset_for_battle(1);
    assert(!native.native_inline_timer_headers);
#endif
    std::cout<<"External lifetime, escaped aliases and reinit passed";
#ifdef GD_INLINE_TIMER_CANDIDATE
    std::cout<<"; native inline identity, cache line, repeated reinit, copy/move, foreign arena and same-frame timer insertion passed";
#endif
    std::cout<<"\n";
}
