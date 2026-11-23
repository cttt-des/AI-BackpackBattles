#define main retained_params_main
#include "test_native_event_capacity.cpp"
#undef main
#include <atomic>
#include <thread>

static uint64_t runtime_case(unsigned scenario,bool locked,unsigned mode,unsigned daz) {
    gd::BattleArena arena(64,locked);
    gd::BattleCtx ctx(4096);ctx.native_timer_watch.enabled=true;
    const int rounds[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};
    std::fesetround(rounds[mode]);
    _mm_setcsr((_mm_getcsr()&~0x8040u)|((daz&1)?0x40u:0)|((daz&2)?0x8000u:0));
    uint64_t trace=1469598103934665603ULL;
    auto state=[&](const V& v) {
        trace=mix(trace,hash(v));trace=mix(trace,std::fetestexcept(FE_ALL_EXCEPT));
        trace=mix(trace,_mm_getcsr()&0x3f);trace=mix(trace,ctx.native_timer_watch.version);
        trace=mix(trace,ctx.native_timer_watch.depth);trace=mix(trace,ctx.native_timer_watch.usable);
        trace=mix(trace,ctx.math_rng.pcg.state);trace=mix(trace,ctx.next_gid);
    };
    for(unsigned cycle=0;cycle<3;++cycle) {
        for(unsigned size:{0,1,7,15,16,31,32,65,255,1024,4097}) {
            std::string bytes(size,'\0');
            for(unsigned i=0;i<size;++i)bytes[i]=char((i*37+scenario+cycle)%256);
            flags_clear();auto* first=gd::make_str(arena,bytes.data(),size);state(V::from_str(first));
            auto* second=gd::make_str(arena,std::string_view(bytes.data(),size));state(V::from_str(second));
            assert(first!=second && first->data[size]=='\0' && second->data[size]=='\0');
            auto* joined=gd::str_concat(arena,first,second);state(V::from_str(joined));
            state(V::from_str(gd::str_concat(arena,nullptr,first)));
            state(V::from_str(gd::str_concat(arena,second,nullptr)));
            state(V::from_str(gd::str_concat(arena,nullptr,nullptr)));
            assert(joined->data[size*2]=='\0');
#if defined(STORAGE_CANDIDATE)
            assert(first->data==reinterpret_cast<const char*>(first)+sizeof(gd::GdStr));
            assert(joined->data==reinterpret_cast<const char*>(joined)+sizeof(gd::GdStr));
#endif
        }
        const unsigned capacities[]={0,1,2,4,5,8,9,32,65};
        const auto capacity=capacities[(scenario+cycle)%9];
        flags_clear();auto* a=gd::GdArr::create(arena,capacity);
        assert(a->len==0 && a->cap==capacity && !a->is_pool_real && !a->timer_watch);
        assert(bool(a->data)==bool(capacity));state(V::from_arr(a));
        auto* d=gd::GdDict::create(arena,capacity);
        assert(d->len==0 && d->cap==capacity && !d->buckets && d->bucket_cap==0);
        assert(bool(d->entries)==bool(capacity));state(V::from_dict(d));
#if defined(STORAGE_CANDIDATE)
        if(capacity) {
            assert(reinterpret_cast<uintptr_t>(a->data)==reinterpret_cast<uintptr_t>(a)+sizeof(gd::GdArr));
            assert(reinterpret_cast<uintptr_t>(d->entries)==reinterpret_cast<uintptr_t>(d)+sizeof(gd::GdDict));
        }
#endif
        auto* alias=a;auto* dict_alias=d;
        if(scenario&4)a->timer_watch=&ctx.native_timer_watch;
        if(scenario&8)a->is_pool_real=true;
        const double snan=std::bit_cast<double>(UINT64_C(0x7ff0000000000042));
        const std::array<V,12> values{V::null(),V::from_bool(true),V::from_int(77),V::from_int(-1),
            V::from_float(-0.0),V::from_float(snan),V::from_float(std::bit_cast<double>(UINT64_C(1))),
            V::from_vec2(-0.0,1.25),V::from_str(gd::make_str(arena,"key")),V::from_arr(a),
            V::from_dict(d),V::from_float(1.25)};
        for(unsigned i=0;i<24;++i) {
            flags_clear();a->push_back(arena,values[(scenario+i)%values.size()]);state(V::from_arr(a));
            auto key=i<12?values[i]:V::from_str(gd::make_str(arena,"k"+std::to_string(i)));
            // Cyclic/identity keys retain aliases; hash serialization deliberately
            // excludes raw address hashes, as independent DLLs have different addresses.
            flags_clear();d->set(arena,key,values[(scenario+i+3)%values.size()]);state(V::from_dict(d));
            flags_clear();state(d->get(key,V::from_int(-99)));
            if(i%4==0){flags_clear();d->erase(key);state(V::from_dict(d));}
        }
        flags_clear();auto* copied=a->duplicate(arena,false);state(V::from_arr(copied));
        auto* dict_copy=d->duplicate(arena,false);state(V::from_dict(dict_copy));
        assert(a==alias && d==dict_alias && copied!=a && dict_copy!=d);
        flags_clear();a->resize(arena,72);state(V::from_arr(a));
        flags_clear();a->set_idx(2,V::from_float(snan));state(V::from_arr(alias));
        flags_clear();a->insert_at(arena,-1,V::from_int(12));state(V::from_arr(a));
        flags_clear();a->remove_at(3);state(V::from_arr(a));
        flags_clear();a->invert();state(V::from_arr(a));
        flags_clear();a->resize(arena,-1);state(V::from_arr(a));
        state(V::from_arr(copied));
        flags_clear();d->clear();state(V::from_dict(d));state(V::from_dict(dict_copy));
        auto* literal=gd::GdArr::from_init(arena,{values[4],values[5],values[6],values[7]});
        assert(literal->len==literal->cap && literal->cap==4);state(V::from_arr(literal));
        // Reuse all arena blocks only after every old alias has been observed.
        arena.reset();
    }
    return trace;
}

int main() {
    const auto old_mxcsr=_mm_getcsr();const int old_round=std::fegetround();
    std::vector<uint64_t> hashes;
    for(unsigned s=0;s<32;++s)for(unsigned lock=0;lock<2;++lock)
        for(unsigned r=0;r<4;++r)for(unsigned daz=0;daz<4;++daz)
            hashes.push_back(runtime_case(s,lock,r,daz));
    std::fesetround(old_round);_mm_setcsr(old_mxcsr);
    std::array<std::vector<const gd::GdStr*>,4> strings;
    std::array<std::thread,4> workers;
    for(unsigned t=0;t<4;++t)workers[t]=std::thread([&,t] {
        for(unsigned i=0;i<200;++i) {
            std::string content="thread-"+std::to_string(t)+"-"+std::to_string(i);
            auto* value=gd::make_static_str(content);assert(value->len==content.size());
            assert(value->hash==gd::fnv1a_32(content.data(),uint32_t(content.size())));
            assert(std::memcmp(value->data,content.data(),content.size())==0 && value->data[value->len]=='\0');
            strings[t].push_back(value);
        }
    });
    for(auto& t:workers)t.join();
    uint64_t parallel=1469598103934665603ULL;
    for(const auto& row:strings)for(auto* s:row)parallel=mix(parallel,hash(V::from_str(s)));
    hashes.push_back(parallel);
    std::cout<<"{\"cases\":"<<hashes.size()<<",\"parallel_strings\":800,\"GdArr\":"<<sizeof(gd::GdArr)
             <<",\"GdDict\":"<<sizeof(gd::GdDict)<<",\"GdVal\":"<<sizeof(V)<<",\"hashes\":[";
    for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<hashes[i]<<std::dec<<'"';}
    std::cout<<"]}\n";
}
