#include "actual_targeted_timer_fixture.hpp"
static std::pair<uint64_t,uint64_t> ownership_case(unsigned scenario,unsigned config,int rounding){
    assert(std::fesetround(FE_TONEAREST)==0);Fixture f;f.c.native_resolved_dispatch=config!=0;f.c.native_resolved_collect=config>=2;f.c.native_resolved_audit=config!=3;
    auto* normal=f.make_timer(f.items[0],false);normal->f__owner=V::from_obj(&f.callback);normal->f_callback_method=V::from_str(gd::make_static_str("mutate"));
    f.callback.action=[&]{f.mutation(3,false);};
    auto* borrowed=f.foreign.arena.make<Timer>(&f.foreign);*borrowed=*normal;borrowed->rt_ctx_=&f.foreign;f.remember(borrowed);f.timers.push_back(borrowed);
    if(scenario==0)f.items[0]->f_timers.arr->push_back(f.c.arena,V::from_obj(borrowed));
    else {
        auto* item=f.foreign.arena.make<Item>(&f.foreign);*item=*f.items[0];item->rt_ctx_=scenario==2?&f.c:&f.foreign;f.remember(item);
        item->f_timers=V::from_arr(gd::GdArr::from_init(f.c.arena,{V::from_obj(borrowed)}));item->f_gems=V::from_arr(gd::GdArr::create(f.c.arena));
        if(scenario==3){f.items[0]->f_gems.arr->set_idx(0,V::from_obj(item));f.gems.push_back(item);}
        else {f.grid->f_items.arr->set_idx(0,V::from_obj(item));f.items.push_back(item);}
    }
    f.enable();std::vector<uint64_t> before;for(auto[fn,n]:counters)for(unsigned i=0;i<n;++i)before.push_back(fn(i));
    assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);f.tick(V::from_float(.05));f.tick(V::from_float(.01));const auto flags=std::fetestexcept(FE_ALL_EXCEPT);
    uint64_t h=mix(f.state(),flags);for(auto x:f.trace)h=mix(h,x);uint64_t legacy=1469598103934665603ULL;unsigned j=0;for(auto[fn,n]:counters)for(unsigned i=0;i<n;++i)legacy=mix(legacy,fn(i)-before[j++]);return{h,legacy};
}
int main(){register_gen_syms();std::vector<uint64_t> states,legacy;for(unsigned s=0;s<4;++s)for(unsigned c=0;c<4;++c)for(int r:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}){auto[a,b]=ownership_case(s,c,r);states.push_back(a);legacy.push_back(b);}
    std::cout<<"{\"cases\":"<<states.size()<<",\"state_hashes\":[";for(unsigned i=0;i<states.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<states[i]<<std::dec<<'"';}std::cout<<"],\"legacy_hashes\":[";for(unsigned i=0;i<legacy.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<legacy[i]<<std::dec<<'"';}std::cout<<"]}\n";
}
