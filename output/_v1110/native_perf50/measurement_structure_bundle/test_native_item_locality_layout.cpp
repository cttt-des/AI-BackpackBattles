#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core_items__Item.hpp"
#include "gen/hdrs/Gd__gd_core_items__Weapon.hpp"
#include <cassert>
#include <iostream>
#include <utility>
using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;
bool inside(const Item& item,const gd::GdArr* array){
    const auto start=reinterpret_cast<uintptr_t>(&item),p=reinterpret_cast<uintptr_t>(array);
    return p>=start && p-start+sizeof(*array)<=sizeof(item);
}
int main(){
    register_gen_syms();unsigned checks=0;
    gd::BattleCtx native(256);native.native_inline_timer_headers=true;
#if defined(GD_ITEM_LOCALITY_LAYOUT_ONLY)
    Item layout(&native);const auto base=reinterpret_cast<uintptr_t>(&layout);
    std::cout<<"{\"core_item_size\":"<<sizeof(Item)
        <<",\"derived_item_size\":"<<sizeof(Gd__gd_core_items__Item)
        <<",\"weapon_size\":"<<sizeof(Gd__gd_core_items__Weapon)
        <<",\"alignment\":"<<alignof(Item)
        <<",\"timers_offset\":"<<reinterpret_cast<uintptr_t>(&layout.f_timers)-base
        <<",\"gems_offset\":"<<reinterpret_cast<uintptr_t>(&layout.f_gems)-base
        <<",\"cooldown_active_offset\":"<<reinterpret_cast<uintptr_t>(&layout.f__cooldown_active)-base
        <<",\"timer_length_offset\":"<<reinterpret_cast<uintptr_t>(&layout.native_timer_header_.len)-base<<"}\n";
    return 0;
#else
    for(uint32_t count:{0u,1u,3u,33u,1024u}){
        auto* item=native.arena.make<Item>(&native);item->init_fields(native);
        auto* original=item->f_gems.arr;
        original->push_back(native.arena,V::from_int(10));
        auto* header=item->native_make_bridge_gems(native,count);
        assert(inside(*item,header) && header!=original && header->len==0 && header->cap==count);
        header->resize(native.arena,count);
        for(uint32_t j=0;j<count;++j)assert(header->data[j].is_null());
        item->f_gems=V::from_arr(header);header->push_back(native.arena,V::from_int(20));
        assert(original->len==1 && original->data[0].i==10);
        const auto line=reinterpret_cast<uintptr_t>(&item->f_timers)/64;
        assert(reinterpret_cast<uintptr_t>(&item->f_gems)-reinterpret_cast<uintptr_t>(item)==480u);
        assert(line==reinterpret_cast<uintptr_t>(&item->native_timer_header_.len)/64);
#ifdef GD_HOT_CONTROL_CANDIDATE
        assert(reinterpret_cast<uintptr_t>(&item->f__cooldown_active)-reinterpret_cast<uintptr_t>(item)==48u);
        assert(reinterpret_cast<uintptr_t>(&item->native_bridge_gems_header_)-reinterpret_cast<uintptr_t>(item)==1936u);
#endif
        auto* second=item->native_make_bridge_gems(native,count);
        assert(second!=header && !inside(*item,second) && second->len==0);
        auto* copy=native.arena.make<Item>(*item);
        assert(copy->f_gems.arr==header);
        auto* copied_replacement=copy->native_make_bridge_gems(native,count);
        assert(copied_replacement!=header && !inside(*copy,copied_replacement));
        item->init_fields(native);
        assert(item->f_gems.arr!=original && item->f_gems.arr!=header && header->len==count+1);
        assert(original->len==1 && original->data[0].i==10);
        checks+=8;
    }
    gd::GdArr* escaped=nullptr;
    {
        Item stack(&native);stack.init_fields(native);
        escaped=stack.native_make_bridge_gems(native,1);assert(!inside(stack,escaped));
    }
    escaped->push_back(native.arena,V::from_int(30));assert(escaped->len==1);++checks;
    gd::BattleCtx ordinary(256);
    auto* external=ordinary.arena.make<Item>(&ordinary);external->init_fields(ordinary);
    assert(!inside(*external,external->native_make_bridge_gems(ordinary,1)));++checks;
    auto* foreign=native.arena.make<Item>(&native);foreign->init_fields(native);
    ordinary.native_inline_timer_headers=true;
    assert(!inside(*foreign,foreign->native_make_bridge_gems(ordinary,1)));++checks;
    Item layout(&native);
    const auto origin=reinterpret_cast<uintptr_t>(&layout);
    std::cout<<"{\"checks\":"<<checks<<",\"core_item_size\":"<<sizeof(Item)
        <<",\"derived_item_size\":"<<sizeof(Gd__gd_core_items__Item)
        <<",\"weapon_size\":"<<sizeof(Gd__gd_core_items__Weapon)
        <<",\"alignment\":"<<alignof(Item)
        <<",\"timers_offset\":"<<reinterpret_cast<uintptr_t>(&layout.f_timers)-origin
        <<",\"gems_offset\":"<<reinterpret_cast<uintptr_t>(&layout.f_gems)-origin
        <<",\"cooldown_active_offset\":"<<reinterpret_cast<uintptr_t>(&layout.f__cooldown_active)-origin
        <<",\"timer_length_offset\":"<<reinterpret_cast<uintptr_t>(&layout.native_timer_header_.len)-origin
        <<",\"bridge_gems_length_offset\":"<<reinterpret_cast<uintptr_t>(&layout.native_bridge_gems_header_.len)-origin<<"}\n";
#endif
}
