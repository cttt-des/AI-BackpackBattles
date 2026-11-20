#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreTimer.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include <cassert>
#include <cstring>
#include <iostream>
using V=gd::GdVal;

struct Custom: Gd__gd_core__CoreItem {
    int calls=0;
    explicit Custom(gd::BattleCtx* c):Gd__gd_core__CoreItem(c){}
    bool call_method(gd::BattleCtx& c,gd::SymId method,const V* args,int argc,V& out) override {
        if(method==SYM_GEN_isBag_83){++calls;out=V::from_bool(true);return true;}
        return Gd__gd_core__CoreItem::call_method(c,method,args,argc,out);
    }
};

int main(){
    register_gen_syms();
    gd::BattleCtx fast,slow;
    fast.native_resolved_dispatch=true;fast.native_resolved_audit=true;fast.native_resolved_collect=true;
    slow.native_resolved_dispatch=false;
    Gd__gd_core__CoreRng fr(&fast),sr(&slow);fr.init_fields(fast);sr.init_fields(slow);
    const auto seed=V::from_int(815367);
    fr.fn__init(&seed,1);sr.fn__init(&seed,1);
    for(int i=0;i<512;++i){
        const V args[]={V::from_float(-i-0.125),V::from_float(i+0.75)};
        const auto a=gd::call_method(fast,V::from_obj(&fr),gd::SYM_randf_range,args,2);
        const auto b=gd::call_method(slow,V::from_obj(&sr),gd::SYM_randf_range,args,2);
        assert(a.kind==b.kind && !std::memcmp(&a.f,&b.f,sizeof(a.f)));
        assert(gd::gd_eq(fr.f_draw_seq,sr.f_draw_seq));
    }
    Gd__gd_core__CoreTimer ft(&fast),st(&slow);ft.init_fields(fast);st.init_fields(slow);
    ft.f__stopped=st.f__stopped=V::from_bool(false);
    ft.f__left=st.f__left=V::from_float(10.0);
    ft.f__ctx=st.f__ctx=V::null();
    const auto delta=V::from_float(0.125);
    for(int i=0;i<32;++i){
        gd::call_method(fast,V::from_obj(&ft),SYM_GEN_tick_1516,&delta,1);
        gd::call_method(slow,V::from_obj(&st),SYM_GEN_tick_1516,&delta,1);
        assert(ft.f__left.kind==st.f__left.kind && !std::memcmp(&ft.f__left.f,&st.f__left.f,sizeof(double)));
    }
    Custom custom(&fast);custom.init_fields(fast);
    for(int i=0;i<3;++i)assert(gd::gd_truth(gd::call_method(fast,V::from_obj(&custom),SYM_GEN_isBag_83,nullptr,0)));
    assert(custom.calls==3 && fast.native_resolved_counts[3]>0 && fast.native_resolved_counts[5]>=3);
    assert(fast.native_resolved_counts[0]>=544 && fast.native_resolved_counts[4]==0);
    std::cout<<"512 RNG bitwise/state comparisons, 32 timer ticks, new-slot C++ override fallback and exact-type audit passed\n";
}
