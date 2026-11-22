#include "actual_targeted_timer_fixture.hpp"
static Fixture* class_fixture=nullptr;
static void class_mutation(){auto& f=*class_fixture;f.items[1]->f_timers=V::from_arr(gd::GdArr::from_init(f.c.arena,{V::from_obj(f.make_timer(f.items[1],false))}));}
static gd::GdObj* custom_allocate(gd::BattleCtx& c){class_mutation();return c.arena.make<Callback>(&c);}
static bool custom_static_get(gd::SymId,V& out){class_mutation();out=V::from_int(7);return true;}
static bool custom_static_call(gd::BattleCtx&,gd::SymId,const V*,int,V& out){class_mutation();out=V::from_int(8);return true;}
static gd::GdClassMeta custom_class=[] {gd::GdClassMeta x{};x.id=65003;x.class_name="TimerExternalClass";x.res_path="external";x.alloc_fn=&custom_allocate;x.get_static_prop=&custom_static_get;x.call_static_fn=&custom_static_call;return x;}();
static std::pair<uint64_t,uint64_t> boundary(unsigned scenario,unsigned config,int rounding){
    assert(std::fesetround(FE_TONEAREST)==0);Fixture f;class_fixture=&f;
    f.c.native_resolved_dispatch=config!=0;f.c.native_resolved_collect=config>=2;f.c.native_resolved_audit=config!=3;f.c.native_event_kernel=config!=0;f.c.native_event_audit=config>=2;
    f.add(f.items[3]);f.enable();
    if(scenario==3){
#ifdef GD_TIMER_NEW
        f.grid->f_items.arr->timer_watch=&f.foreign.native_timer_watch;
#endif
    }
    if(scenario==7)f.chr->f_playerId=V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234)));
    std::vector<uint64_t> before;for(auto[fn,n]:counters)for(unsigned i=0;i<n;++i)before.push_back(fn(i));
    assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);f.tick(V::from_float(.01));
    switch(scenario){
    case 0:{auto v=gd::construct_class(f.c,&custom_class,nullptr,0);f.remember(v.obj);f.trace.push_back(hash(v));break;}
    case 1:f.trace.push_back(hash(gd::native_inline_get_prop(f.c,V::from_cls(&custom_class),SYM_GEN_timers_67)));break;
    case 2:f.trace.push_back(hash(gd::native_inline_call(f.c,V::from_cls(&custom_class),SYM_GEN_tick_1516,nullptr,0)));break;
    case 3:f.grid->f_items.arr->set_idx(1,V::from_obj(f.items[3]));break;
    case 4:{
#ifdef GD_TIMER_NEW
        auto& w=f.c.native_timer_watch;const auto old=static_cast<gd::TargetedTimerCache*>(w.cache[0])->version;
        {gd::NativeTimerMutation mutation(f.grid->f_items.arr->timer_watch);
#endif
        f.tick(V::from_float(.005));f.grid->f_items.arr->data[1]=V::from_obj(f.items[3]);
#ifdef GD_TIMER_NEW
        assert(w.depth>0 && static_cast<gd::TargetedTimerCache*>(w.cache[0])->version==old);}
        assert(w.depth==0 && w.version!=old);
#endif
        break;}
    case 5:
#ifdef GD_TIMER_NEW
        f.c.native_timer_watch.version=UINT64_MAX;
#endif
        f.add(f.items[1],false);
#ifdef GD_TIMER_NEW
        assert(!f.c.native_timer_watch.usable);
#endif
        break;
    case 6:
#ifdef GD_TIMER_NEW
        f.c.native_timer_watch.depth=UINT32_MAX;
        {gd::NativeTimerMutation mutation(f.items[3]->f_timers.arr->timer_watch);assert(!f.c.native_timer_watch.usable);}
        assert(f.c.native_timer_watch.depth==UINT32_MAX);f.c.native_timer_watch.depth=0;
#endif
        break;
    case 7:break;
    case 8:f.external=*f.grid->f_items.arr;f.grid->set_prop(f.c,SYM_GEN_items_1092,V::from_arr(&f.external));f.external.set_idx(1,V::from_obj(f.items[3]));break;
    case 9:f.items[1]->set_prop(f.c,SYM_GEN_timers_67,f.items[3]->f_timers);f.items[3]->f_timers.arr->resize(f.c.arena,0);break;
    case 10:{V delta=V::from_float(.025);auto* timer=f.add(f.gems[0],false);timer->f__owner=V::from_obj(f.items[4]);timer->f_callback_method=V::from_str(gd::make_static_str("newItemTimer"));f.tick(delta);break;}
    case 11:f.c.reset_for_battle(123);f.setup(8);f.c.native_resolved_collect=config>=2;f.enable();f.add(f.items[1],false);break;
    }
    f.tick(V::from_float(.02));const auto flags=std::fetestexcept(FE_ALL_EXCEPT);uint64_t h=mix(f.state(),flags);for(auto n:f.trace)h=mix(h,n);
    uint64_t legacy=1469598103934665603ULL;unsigned j=0;for(auto[fn,n]:counters)for(unsigned i=0;i<n;++i)legacy=mix(legacy,fn(i)-before[j++]);return{h,legacy};
}
int main(){register_gen_syms();std::vector<uint64_t> hashes,legacy;for(unsigned s=0;s<12;++s)for(unsigned c=0;c<4;++c)for(int r:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}){auto[a,b]=boundary(s,c,r);hashes.push_back(a);legacy.push_back(b);}
    std::cout<<"{\"cases\":"<<hashes.size()<<",\"state_hashes\":[";for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<hashes[i]<<std::dec<<'"';}std::cout<<"],\"legacy_hashes\":[";for(unsigned i=0;i<legacy.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<legacy[i]<<std::dec<<'"';}std::cout<<"]}\n";
}
