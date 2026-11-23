#include "native_type_constructor_test_cases.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include <bit>
#include <cassert>
#include <cfenv>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <xmmintrin.h>
using V=gd::GdVal;
extern "C" void gd_init_all_classes();
static uint64_t mix(uint64_t h,uint64_t v){return(h^v)*1099511628211ULL;}
static void clear_flags(){std::feclearexcept(FE_ALL_EXCEPT);_mm_setcsr(_mm_getcsr()&~0x3fu);}

struct Graph {
    uint64_t h=1469598103934665603ULL;
    std::unordered_map<const void*,uint64_t> seen;
    gd::BattleCtx& ctx;gd::BattleCtx& other;
    Graph(gd::BattleCtx& c,gd::BattleCtx& o):ctx(c),other(o){}
    void add(uint64_t v){h=mix(h,v);}
    bool enter(const void* p) {
        if(!p){add(0);return false;}
        if(auto it=seen.find(p);it!=seen.end()){add(it->second);add(0);return false;}
        auto id=seen.size()+1;seen[p]=id;add(id);add(1);return true;
    }
    void bytes(const char* p,unsigned n){add(n);for(unsigned i=0;i<n;++i)add(uint8_t(p[i]));}
    void number(double v){add(std::bit_cast<uint64_t>(v));}
    void arr(const gd::GdArr* a) {
        if(!enter(a))return;
        add(a->len);add(a->cap);add(a->is_pool_real);
        add(a->timer_watch==nullptr?0:a->timer_watch==&ctx.native_timer_watch?1:a->timer_watch==&other.native_timer_watch?2:3);
        for(unsigned i=0;i<a->len;++i)value(a->data[i]);
    }
    void obj(const gd::GdObj* o) {
        if(!enter(o))return;
        auto* meta=o->meta();add(meta->id);add(o->gid_);add(o->gid_epoch_);
        add(o->rt_ctx_==&ctx?1:o->rt_ctx_==&other?2:3);add(o->native_call_row_!=nullptr);
        const auto* test=meta->id<constructor_case_index.size()?constructor_case_index[meta->id]:nullptr;
        if(test && test->meta==meta)for(size_t i=0;i<test->count;++i)value(*test->fields[i](o));
        if(meta->is_subclass_of(&META_Gd__gd_core__CoreItem)) {
            auto* item=static_cast<const Gd__gd_core__CoreItem*>(o);
            add(item->native_timer_header_used_);add(item->f_timers.kind==V::Kind::Arr && item->f_timers.arr==&item->native_timer_header_);
        }
    }
    void value(const V& v) {
        add(unsigned(v.kind));
        switch(v.kind) {
        case V::Kind::Null:break;
        case V::Kind::Bool:add(v.b);break;
        case V::Kind::Int:add(uint64_t(v.i));break;
        case V::Kind::Float:number(v.f);break;
        case V::Kind::Vec2:number(v.v2.x);number(v.v2.y);break;
        case V::Kind::Str:if(v.str){add(1);bytes(v.str->data,v.str->len);add(v.str->hash);}else add(0);break;
        case V::Kind::Arr:arr(v.arr);break;
        case V::Kind::Dict:
            if(enter(v.dict)){add(v.dict->len);add(v.dict->cap);for(unsigned i=0;i<v.dict->len;++i){value(v.dict->entries[i].key);value(v.dict->entries[i].val);}}break;
        case V::Kind::Obj:obj(v.obj);break;
        case V::Kind::Rng:
            if(enter(v.rng)){add(v.rng->pcg.state);add(v.rng->pcg.inc);add(v.rng->current_seed);add(v.rng->inc);add(v.rng->randomized_flag);}break;
        case V::Kind::FuncRef:if(enter(v.fr)){add(v.fr->method);obj(v.fr->instance);arr(v.fr->binds);}break;
        case V::Kind::ClassRef:add(v.cls?v.cls->id:0);break;
        case V::Kind::Enum:if(v.en){add(v.en->len);for(unsigned i=0;i<v.en->len;++i){auto& e=v.en->items[i];bytes(e.key,unsigned(std::strlen(e.key)));add(uint64_t(e.val));}}else add(0);break;
        case V::Kind::Color:if(enter(v.col)){number(v.col->r);number(v.col->g);number(v.col->b);number(v.col->a);}break;
        }
    }
    void context(const gd::BattleCtx& c) {
        add(c.next_gid);add(c.gid_epoch);add(c.math_rng.pcg.state);add(c.math_rng.pcg.inc);
        const auto& w=c.native_timer_watch;add(w.version);add(w.cooldown_version);add(w.depth);add(w.usable);add(w.closed_world);
    }
};

static uint64_t one(const auto& type,unsigned mode,unsigned round,unsigned daz,bool on_stack=false) {
    gd::BattleCtx ctx(4096),other(4096);ctx.bind_battle(123);other.bind_battle(123);
    ctx.native_resolved_dispatch=other.native_resolved_dispatch=true;
    ctx.native_timer_watch.enabled=other.native_timer_watch.enabled=true;
    ctx.native_timer_watch.closed_world=bool(mode&1);other.native_timer_watch.closed_world=!(mode&1);
    ctx.native_inline_timer_headers=other.native_inline_timer_headers=bool(mode&2);
    if(type.meta->id%7==0)ctx.native_timer_watch.version=other.native_timer_watch.version=UINT64_MAX;
    auto& owner=mode&4?other:ctx;
    const int rounds[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};
    std::fesetround(rounds[round]);_mm_setcsr((_mm_getcsr()&~0x8040u)|((daz&1)?0x40u:0)|((daz&2)?0x8000u:0));
    Gd__gd_core__CoreItem stack_object(&owner);
    clear_flags();auto* object=on_stack?static_cast<gd::GdObj*>(&stack_object):type.meta->alloc_fn(owner);object->init_fields(ctx);
    uint64_t trace=1469598103934665603ULL;
    std::vector<V> old;
    auto state=[&]() {
        Graph graph(ctx,other);graph.obj(object);
        for(const auto& v:old)graph.value(v);
        graph.context(ctx);graph.context(other);
        graph.add(std::fetestexcept(FE_ALL_EXCEPT));graph.add(_mm_getcsr()&0x3f);
        trace=mix(trace,graph.h);
    };
    state();
    for(size_t i=0;i<type.count;++i) {
        const auto& value=*type.fields[i](object);
        if(value.kind==V::Kind::Arr || value.kind==V::Kind::Dict)old.push_back(value);
    }
    // All captured old containers remain independently mutable after re-init.
    for(unsigned i=0;i<old.size();++i) {
        clear_flags();auto& v=old[i];
        if(v.kind==V::Kind::Arr && v.arr){v.arr->push_back(ctx.arena,V::from_int(1000+i));}
        if(v.kind==V::Kind::Dict && v.dict){v.dict->set(ctx.arena,V::from_int(1000+i),V::from_int(2000+i));}
    }
    state();clear_flags();object->init_fields(ctx);state();
    clear_flags();object->init_fields(other);state();
    return trace;
}

int main() {
    gd_init_all_classes();const auto old_mxcsr=_mm_getcsr();const int old_round=std::fegetround();
    std::vector<uint64_t> hashes;
    for(const auto& type:constructor_cases)for(unsigned mode=0;mode<8;++mode)
        for(unsigned round=0;round<4;++round)for(unsigned daz=0;daz<4;++daz)
            hashes.push_back(one(type,mode,round,daz));
    const auto* base=constructor_case_index[CLS_Gd__gd_core__CoreItem];assert(base);
    for(unsigned mode=0;mode<8;++mode)for(unsigned round=0;round<4;++round)for(unsigned daz=0;daz<4;++daz)
        hashes.push_back(one(*base,mode,round,daz,true));
    std::fesetround(old_round);_mm_setcsr(old_mxcsr);
    std::cout<<"{\"cases\":"<<hashes.size()<<",\"classes\":"<<std::size(constructor_cases)
             <<",\"GdVal\":"<<sizeof(V)<<",\"GdArr\":"<<sizeof(gd::GdArr)<<",\"GdDict\":"<<sizeof(gd::GdDict)
             <<",\"CoreItem\":"<<sizeof(Gd__gd_core__CoreItem)<<",\"BattleCtx\":"<<sizeof(gd::BattleCtx)<<",\"hashes\":[";
    for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<hashes[i]<<std::dec<<'"';}
    std::cout<<"]}\n";
}
