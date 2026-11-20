#include "gd_rt.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreHooks.hpp"
#include <cassert>
#include <iostream>
#include <vector>

using V=gd::GdVal;
uint64_t native_epoch() {
#ifdef GD_SPARSE_TIMER_CANDIDATE
    return gd::native_timer_scan_state().epoch;
#else
    return gd::native_timer_scan_epoch();
#endif
}
gd::SymId compare_method=0;
struct Compare : Gd__gd_core__CoreHooks {
    explicit Compare(gd::BattleCtx* context):Gd__gd_core__CoreHooks(context) {}
    bool call_method(gd::BattleCtx& context,gd::SymId method,const V* args,int argc,V& out) override {
        if(method==compare_method) {
            assert(argc==2);out=V::from_bool(args[0].as_int()<args[1].as_int());return true;
        }
        return Gd__gd_core__CoreHooks::call_method(context,method,args,argc,out);
    }
};

int main() {
    register_gen_syms();
    static_assert(sizeof(gd::GdArr)==24);
    gd::BattleCtx context;
    auto& arena=context.arena;
    auto* array=gd::GdArr::create(arena);
    auto epoch=native_epoch();
    array->push_back(arena,V::from_int(1));
    assert(native_epoch()==epoch && !array->native_timer_scan_tracked);
    context.native_sparse_timer_scans=true;
    gd::native_timer_scan_mark(context,V::from_arr(array));
    assert(native_epoch()>epoch && array->native_timer_scan_tracked);
    auto changed=[&](auto action) {
        const auto before=native_epoch();action();
        assert(native_epoch()>before);
    };
    changed([&]{array->push_back(arena,V::from_int(2));});
    changed([&]{array->insert_at(arena,1,V::from_int(3));});
    auto* other=gd::GdArr::from_init(arena,{V::from_int(4),V::from_int(5)});
    changed([&]{array->append_array(arena,other);});
    changed([&]{array->pop_at(1);});
    changed([&]{array->pop_front();});
    changed([&]{array->pop_back();});
    changed([&]{array->push_back(arena,V::from_int(6));});
    changed([&]{array->remove_at(0);});
    changed([&]{array->erase_val(V::from_int(6));});
    changed([&]{array->resize(arena,4);});
    changed([&]{array->fill(V::from_int(7));});
    changed([&]{array->invert();});
    // All aliases refer to the same tracked header.
    auto* alias=array;
    changed([&]{alias->set_idx(0,V::from_int(8));});
    assert(array->get_idx(0).i==8);
    auto receiver=V::from_arr(array);
    changed([&]{gd::call_method(context,receiver,gd::SYM_clear,nullptr,0);});
    assert(array->len==0 && array->native_timer_scan_tracked);
    array->push_back(arena,V::from_int(3));array->push_back(arena,V::from_int(1));array->push_back(arena,V::from_int(2));
    auto* plain=array->duplicate(arena);
    gd::BattleCtx reference;
    context.math_rng=gd::GdRng(42);reference.math_rng=gd::GdRng(42);
    auto plain_receiver=V::from_arr(plain);
    changed([&]{gd::call_method(context,receiver,gd::SYM_shuffle,nullptr,0);});
    gd::call_method(reference,plain_receiver,gd::SYM_shuffle,nullptr,0);
    assert(context.math_rng.pcg.state==reference.math_rng.pcg.state);
    for(uint32_t i=0;i<array->len;++i) assert(gd::gd_eq(array->data[i],plain->data[i]));
    compare_method=gd::intern_sym("native_timer_probe_less");
    Compare comparator(&context);comparator.init_fields(context);
    const V args[]={V::from_obj(&comparator),V::from_cstr(arena,"native_timer_probe_less")};
    changed([&]{gd::call_method(context,receiver,gd::SYM_sort_custom,args,2);});
    assert(array->data[0].i==1 && array->data[1].i==2 && array->data[2].i==3);

    context.native_inline_timer_headers=true;
    auto* item=arena.make<Gd__gd_core__CoreItem>(&context);item->init_fields(context);
    assert(item->f_timers.arr->native_timer_scan_tracked && item->f_gems.arr->native_timer_scan_tracked);
    auto value=V::from_obj(item);
    auto* replacement=gd::GdArr::create(arena);
    changed([&]{gd::set_prop(context,value,SYM_GEN_timers_67,V::from_arr(replacement));});
    assert(item->f_timers.arr==replacement && replacement->native_timer_scan_tracked);
    auto* gems=gd::GdArr::create(arena);
    changed([&]{gd::set_prop(context,value,SYM_GEN_gems_41,V::from_arr(gems));});
    assert(item->f_gems.arr==gems && gems->native_timer_scan_tracked);
    std::cout<<"Tracked mutators, aliases, clear, shuffle RNG, sort callback, inline headers and timer/gem field replacement passed\n";
}
