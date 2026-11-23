// Reuse only serialization/FP helpers; the baseline calls its original DLL.
#define main retained_params_main
#include "test_native_event_capacity.cpp"
#undef main
#include "native_event_kernel.hpp"
#include <algorithm>

#if defined(CANDIDATE_FACTORY)
gd::GdVal gd_native_create_event(gd::BattleCtx&,const gd::GdVal*,int);
#endif

static uint64_t factory_case(unsigned scenario,bool closed,unsigned mode,unsigned daz,int argc) {
    gd::BattleCtx ctx(1024);
    ctx.native_timer_watch.closed_world=closed;
    ctx.native_resolved_dispatch=true;
    Gd__gd_core__CoreEvent parent(&ctx);
    auto* arr=gd::GdArr::from_init(ctx.arena,{V::from_int(11),V::null()});
    auto* dict=gd::GdDict::create(ctx.arena);
    const double snan=std::bit_cast<double>(UINT64_C(0x7ff0000000000042));
    const std::array<V,20> values{V::null(),V::from_bool(true),V::from_int(42),V::from_int(-7),
        V::from_float(-0.0),V::from_float(2.75),V::from_float(snan),
        V::from_float(std::bit_cast<double>(UINT64_C(1))),V::from_float(INFINITY),
        V::from_float(std::bit_cast<double>(UINT64_C(0x7ff8000000000042))),
        V::from_str(gd::make_str(ctx.arena,"123")),V::from_str(gd::make_str(ctx.arena,"bad")),
        V::from_vec2(1,-0.0),V::from_arr(arr),V::from_dict(dict),V::from_obj(&parent),
        V::from_str(nullptr),V::from_arr(nullptr),V::from_dict(nullptr),V::from_obj(nullptr)};
    V args[]={values[scenario],values[(scenario+6)%20],values[(scenario+15)%20],
              values[(scenario+13)%20],values[(scenario+9)%20],V::from_int(777)};
    const int rounds[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};
    std::fesetround(rounds[mode]);
    _mm_setcsr((_mm_getcsr()&~0x8040u)|((daz&1)?0x40u:0)|((daz&2)?0x8000u:0));
    flags_clear();
#if defined(CANDIDATE_FACTORY)
    V result=gd_native_create_event(ctx,argc>0?args:nullptr,argc);
#else
    V result=native_event_new<Gd__gd_core__CoreEvent>(ctx,argc>0?args:nullptr,argc);
#endif
    auto* event=static_cast<Gd__gd_core__CoreEvent*>(result.obj);
    uint64_t trace=1469598103934665603ULL;
    auto state=[&]() {
        for(const V* v:{&event->f_id,&event->f_timestamp,&event->f_parentEvent,&event->f_origin,
                       &event->f_type,&event->f_target,&event->f_params,&event->f_formatParams})
            trace=mix(trace,hash(*v));
        trace=mix(trace,event->rt_ctx_==&ctx);
        trace=mix(trace,event->gid_);trace=mix(trace,event->gid_epoch_);
        trace=mix(trace,event->native_call_row_==nullptr);trace=mix(trace,event->conns_head_==nullptr);
        trace=mix(trace,ctx.next_gid);trace=mix(trace,ctx.math_rng.pcg.state);trace=mix(trace,ctx.math_rng.pcg.inc);
        trace=mix(trace,std::fetestexcept(FE_ALL_EXCEPT));trace=mix(trace,_mm_getcsr()&0x3f);
    };
    // A factory must preserve the exact container/object aliases passed as fields.
    auto aliases=[&](const V& actual,const V& expected) {
        if(actual.kind!=expected.kind){trace=mix(trace,987);return;}
        if(actual.kind==V::Kind::Obj)trace=mix(trace,actual.obj==expected.obj);
        if(actual.kind==V::Kind::Arr)trace=mix(trace,actual.arr==expected.arr);
        if(actual.kind==V::Kind::Dict)trace=mix(trace,actual.dict==expected.dict);
        if(actual.kind==V::Kind::Str)trace=mix(trace,actual.str==expected.str);
    };
    aliases(event->f_timestamp,argc>1?args[1]:V::from_float(0));
    aliases(event->f_parentEvent,argc>2?args[2]:V::null());
    aliases(event->f_origin,argc>3?args[3]:V::null());
    aliases(event->f_type,argc>4?args[4]:V::null());
    state();
    auto* params=event->f_params.dict;
    auto* format=event->f_formatParams.dict;
    assert(params && format && params!=format);
    if(closed) {
#if defined(CANDIDATE_FACTORY)
        auto address=reinterpret_cast<uintptr_t>(event);
        assert(reinterpret_cast<uintptr_t>(params)>address);
        assert(reinterpret_cast<uintptr_t>(format)>reinterpret_cast<uintptr_t>(params));
        assert(reinterpret_cast<uintptr_t>(params->entries)>reinterpret_cast<uintptr_t>(format));
        assert(params->cap==4 && params->len==0 && format->cap==0);
#endif
    }
    Gd__gd_core__CoreEvent copy=*event;
    // Force several arena blocks, grow/erase/clear both independent dictionaries,
    // retain copies, replace fields and reinitialize the event with aliases alive.
    ctx.arena.alloc_raw(200000,16);
    for(unsigned i=0;i<20;++i) {
        V key=V::from_str(gd::make_str(ctx.arena,"key"+std::to_string(i)));
        V set_args[]={key,values[(scenario+i)%20]};
        flags_clear();event->fn_setParam(set_args,2);state();
        format->set(ctx.arena,key,V::from_int(100+i));state();
        if(i%3==0){copy.fn_setParam(set_args,2);state();}
        if(i==7){flags_clear();params->erase(key);state();}
    }
    flags_clear();auto* duplicate=params->duplicate(ctx.arena,false);state();
    flags_clear();params->clear();state();trace=mix(trace,hash(V::from_dict(duplicate)));
    flags_clear();event->init_fields(ctx);state();
    trace=mix(trace,event->f_params.dict!=params && event->f_formatParams.dict!=format);
    trace=mix(trace,hash(copy.f_params));trace=mix(trace,hash(copy.f_formatParams));
    V later[]={V::from_int(99),V::from_float(-0.0),V::from_obj(&parent),V::null(),V::from_int(3)};
    flags_clear();event->fn__init(later,5);state();
    return trace;
}

int main() {
    const auto old_mxcsr=_mm_getcsr();const int old_round=std::fegetround();
    std::vector<uint64_t> hashes;
    for(unsigned s=0;s<20;++s)for(unsigned c=0;c<2;++c)for(unsigned m=0;m<4;++m)for(unsigned d=0;d<4;++d)
        for(int argc:{-1,0,1,2,3,4,5,6})hashes.push_back(factory_case(s,c,m,d,argc));
    std::fesetround(old_round);_mm_setcsr(old_mxcsr);
    std::cout<<"{\"cases\":"<<hashes.size()<<",\"CoreEvent\":"<<sizeof(Gd__gd_core__CoreEvent)
             <<",\"GdDict\":"<<sizeof(gd::GdDict)<<",\"GdVal\":"<<sizeof(V)
             <<",\"BattleCtx\":"<<sizeof(gd::BattleCtx)<<",\"hashes\":[";
    for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<hashes[i]<<std::dec<<'"';}
    std::cout<<"]}\n";
}
