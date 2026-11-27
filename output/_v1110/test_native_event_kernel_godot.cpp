#include "native_event_kernel.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

using V=gd::GdVal;
using Context=Gd__gd_core__CoreContext;
using Bus=Gd__gd_core__CoreEventBus;
const gd::GdClassMeta receiver_meta{65000,"NativeEventRegression"};
struct Receiver:gd::GdObj {
    std::function<void(const V*,int)> action;
    explicit Receiver(gd::BattleCtx* ctx):GdObj(ctx){}
    const gd::GdClassMeta* meta() const override{return &receiver_meta;}
    bool call_method(gd::BattleCtx&,gd::SymId method,const V* args,int argc,V& out) override {
        if(method!=gd::intern_sym("native_event_regression"))return false;
        action(args,argc);out=V::null();return true;
    }
};

std::vector<int64_t> run(bool native,int scenario) {
    gd::BattleCtx battle;
    battle.native_event_kernel=native;
    battle.native_event_audit=true;
    Context ctx(&battle);ctx.init_fields(battle);ctx.f_fight_ended=V::from_bool(false);
    Bus bus(&battle);bus.init_fields(battle);bus.f__ctx=V::from_obj(&ctx);
    Receiver emitter(&battle),first(&battle),second(&battle),third(&battle);
    const auto signal=V::from_cstr(battle.arena,"regression_signal");
    const auto method=V::from_cstr(battle.arena,"native_event_regression");
    auto connect=[&](Receiver& receiver){
        V args[]{V::from_obj(&emitter),signal,V::from_obj(&receiver),method};
        bus.fn_connectEvent(args,4);
    };
    connect(first);connect(second);
    const V idargs[]{V::from_obj(&emitter),V::from_int(0)};
    const auto id=bus.fn_getEmissionID(idargs,2);
    const auto listeners=gd::get_index(battle,bus.f_connections,id);
    auto* bound=listeners.arr->data[1].arr->data[0].fr;
    bound->binds=gd::GdArr::from_init(battle.arena,{V::from_int(99)});
    std::vector<int64_t> trace;
    auto emit=[&]{
        V args[]{V::from_obj(&emitter),signal,V::null(),
            V::from_arr(gd::GdArr::from_init(battle.arena,{V::from_int(7)}))};
        bus.fn_emitAndLog(args,4);
    };
    bool nested=false;
    first.action=[&](const V* args,int argc){
        assert(argc==1 && args[0].as_int()==7);trace.push_back(1);
        if(scenario==0)connect(third); // Godot visits appended listeners during the current emission.
        if(scenario==1){ // Replacement of a future slot is visible immediately.
            connect(third);
            listeners.arr->set_idx(1,listeners.arr->data[2]);
        }
        if(scenario==2 && !nested){nested=true;emit();}
        if(scenario==3)ctx.f_fight_ended=V::from_bool(true);
    };
    second.action=[&](const V* args,int argc){
        assert(argc==2 && args[0].as_int()==7 && args[1].as_int()==99);
        trace.push_back(2);
    };
    third.action=[&](const V* args,int argc){assert(argc==1 && args[0].as_int()==7);trace.push_back(3);};
    emit();
    if(scenario==0){assert((trace==std::vector<int64_t>{1,2,3}));emit();assert((trace==std::vector<int64_t>{1,2,3,1,2,3,3}));}
    if(scenario==1)assert((trace==std::vector<int64_t>{1,3,3}));
    if(scenario==2)assert((trace==std::vector<int64_t>{1,1,2,2}));
    if(scenario==3)assert((trace==std::vector<int64_t>{1}));
    assert(battle.native_event_counts[4]==0);
    assert((battle.native_event_counts[0]>0)==native);
    return trace;
}

int main(){
    register_gen_syms();
    for(int scenario=0;scenario<4;++scenario)assert(run(false,scenario)==run(true,scenario));
    std::cout<<"Native/generic event chains matched: appended and replaced listeners, bound arguments, nested emissions, and same-frame terminal interruption\n";
}
