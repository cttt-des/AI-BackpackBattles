#include "native_type_constructor_test_cases.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include <bit>
#include <cassert>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>
using V=gd::GdVal;
extern "C" void gd_init_all_classes();
extern "C" uint64_t gd_diag_native_type_constructor_stat(unsigned);

struct Graph {
    struct PairMap {
        std::unordered_map<const void*,const void*> forward,reverse;
        bool enter(const void* a,const void* b){
            assert(bool(a)==bool(b));if(!a)return false;
            if(auto found=forward.find(a);found!=forward.end()){assert(found->second==b);return false;}
            assert(!reverse.contains(b));forward[a]=b;reverse[b]=a;return true;
        }
    } objects,arrays,dicts,colors,rngs,refs;
    gd::BattleCtx& a;gd::BattleCtx& b;uint64_t fields=0;
    explicit Graph(gd::BattleCtx& x,gd::BattleCtx& y):a(x),b(y){}
    void number(double x,double y){assert(std::bit_cast<uint64_t>(x)==std::bit_cast<uint64_t>(y));}
    void arr(const gd::GdArr* x,const gd::GdArr* y){
        if(!arrays.enter(x,y))return;
        assert(x->len==y->len && x->cap==y->cap && x->is_pool_real==y->is_pool_real);
        for(uint32_t i=0;i<x->len;++i)value(x->data[i],y->data[i]);
    }
    void obj(const gd::GdObj* x,const gd::GdObj* y){
        if(!objects.enter(x,y))return;
        const auto* mx=x->meta();const auto* my=y->meta();assert(mx==my);
        const auto* test=mx->id<constructor_case_index.size()?constructor_case_index[mx->id]:nullptr;
        if(test && test->meta==mx){
            for(size_t i=0;i<test->count;++i){value(*test->fields[i](x),*test->fields[i](y));++fields;}
        }else{
            const auto* sx=gd::gd_to_str(a.arena,V::from_obj(const_cast<gd::GdObj*>(x)));
            const auto* sy=gd::gd_to_str(b.arena,V::from_obj(const_cast<gd::GdObj*>(y)));
            assert(sx->len==sy->len && std::memcmp(sx->data,sy->data,sx->len)==0);
        }
        assert(x->gid_==y->gid_ && x->gid_epoch_==y->gid_epoch_);
    }
    void value(const V& x,const V& y){
        assert(x.kind==y.kind);
        switch(x.kind){
            case V::Kind::Null:return;
            case V::Kind::Bool:assert(x.b==y.b);return;
            case V::Kind::Int:assert(x.i==y.i);return;
            case V::Kind::Float:number(x.f,y.f);return;
            case V::Kind::Vec2:number(x.v2.x,y.v2.x);number(x.v2.y,y.v2.y);return;
            case V::Kind::Str:
                assert(bool(x.str)==bool(y.str));if(x.str)assert(x.str->len==y.str->len && x.str->hash==y.str->hash && std::memcmp(x.str->data,y.str->data,x.str->len)==0);return;
            case V::Kind::Obj:obj(x.obj,y.obj);return;
            case V::Kind::Arr:arr(x.arr,y.arr);return;
            case V::Kind::Dict:
                if(!dicts.enter(x.dict,y.dict))return;
                assert(x.dict->len==y.dict->len && x.dict->cap==y.dict->cap);
                for(uint32_t i=0;i<x.dict->len;++i){value(x.dict->entries[i].key,y.dict->entries[i].key);value(x.dict->entries[i].val,y.dict->entries[i].val);}return;
            case V::Kind::ClassRef:assert(x.cls==y.cls);return;
            case V::Kind::Enum:assert(x.en==y.en);return;
            case V::Kind::Color:
                if(!colors.enter(x.col,y.col))return;
                number(x.col->r,y.col->r);number(x.col->g,y.col->g);number(x.col->b,y.col->b);number(x.col->a,y.col->a);return;
            case V::Kind::Rng:
                if(!rngs.enter(x.rng,y.rng))return;
                assert(x.rng->pcg.state==y.rng->pcg.state && x.rng->pcg.inc==y.rng->pcg.inc && x.rng->current_seed==y.rng->current_seed && x.rng->inc==y.rng->inc && x.rng->randomized_flag==y.rng->randomized_flag);return;
            case V::Kind::FuncRef:
                if(!refs.enter(x.fr,y.fr))return;
                assert(x.fr->method==y.fr->method);obj(x.fr->instance,y.fr->instance);arr(x.fr->binds,y.fr->binds);return;
        }
    }
};

struct CustomMeta:Gd__gd_core__CoreItem {
    mutable unsigned calls=0;
    explicit CustomMeta(gd::BattleCtx* ctx):Gd__gd_core__CoreItem(ctx){}
    const gd::GdClassMeta* meta() const override{
        ++calls;rt_ctx_->math_rng.randf();
        return calls%2?&META_Gd__gd_core_items__Gems__Gem:&META_Gd__gd_core__CoreItem;
    }
};
static std::vector<int>* ctor_events=nullptr;
struct CustomConstructor:gd::GdObj {
    explicit CustomConstructor(gd::BattleCtx* ctx):GdObj(ctx){}
    const gd::GdClassMeta* meta() const override{return &META_Gd__gd_core__CoreItem;}
    void init_fields(gd::BattleCtx& ctx) override{ctor_events->push_back(2);ctx.math_rng.randf();}
    bool call_method(gd::BattleCtx& ctx,gd::SymId method,const V* args,int argc,V& out) override{
        assert(method==gd::SYM__init && argc==2 && args[0].i==17 && args[1].b);
        ctor_events->push_back(3);ctx.math_rng.randf();out=V::from_int(999);return true;
    }
};
gd::GdObj* custom_alloc(gd::BattleCtx& ctx){ctor_events->push_back(1);ctx.math_rng.randf();return ctx.arena.make<CustomConstructor>(&ctx);}

int main(){
    gd_init_all_classes();uint64_t predicates=0,fields=0;unsigned constructors=0,boundaries=0;
    for(const auto& type:constructor_cases){
        gd::BattleCtx ctx;ctx.native_resolved_dispatch=true;ctx.native_resolved_audit=true;ctx.native_resolved_collect=true;
        auto* object=type.meta->alloc_fn(ctx);assert(object && object->native_call_row_);
        const auto value=V::from_obj(object);
        for(const auto& target:constructor_cases){
            const bool expected=gd::gd_is_type(value,target.meta);
            assert(gd::native_inline_is_type(ctx,value,target.meta)==expected);
            ++predicates;
        }
        gd::GdClassMeta copied=*type.meta;
        assert(!gd::gd_is_type(value,&copied) && !gd::native_inline_is_type(ctx,value,&copied));++boundaries;
        assert(!gd::native_inline_is_type(ctx,value,nullptr));
        assert(!gd::native_inline_is_type(ctx,V::null(),type.meta));
        auto* cached=object->native_call_row_;object->native_call_row_=nullptr;
        assert(gd::native_inline_is_type(ctx,value,type.meta));assert(!object->native_call_row_);++boundaries;
        object->native_call_row_=cached;ctx.native_resolved_dispatch=false;
        assert(gd::native_inline_is_type(ctx,value,type.meta));++boundaries;
        for(bool inline_headers:{false,true}){
            gd::BattleCtx slow,fast;slow.bind_battle(123);fast.bind_battle(123);
            slow.native_resolved_dispatch=fast.native_resolved_dispatch=true;
            slow.native_resolved_audit=fast.native_resolved_audit=true;
            slow.native_inline_timer_headers=fast.native_inline_timer_headers=inline_headers;
            fast.native_resolved_collect=true;
            auto* original=type.meta->alloc_fn(slow);original->init_fields(slow);
            auto* fused=gd::try_native_allocate_initialized(fast,type.meta);assert(fused);
            assert(original->meta()==type.meta && fused->meta()==type.meta);
            assert(original->rt_ctx_==&slow && fused->rt_ctx_==&fast);
            assert(gd::native_resolved_row_matches(fused,fused->native_call_row_));
            Graph graph(slow,fast);graph.obj(original,fused);fields+=graph.fields;
            assert(slow.next_gid==fast.next_gid && slow.math_rng.pcg.state==fast.math_rng.pcg.state);
            assert(slow.native_resolved_counts[4]==0 && fast.native_resolved_counts[4]==0);++constructors;
        }
    }
    gd::BattleCtx slow,fast;slow.bind_battle(17);fast.bind_battle(17);
    fast.native_resolved_dispatch=true;fast.native_resolved_audit=true;fast.native_resolved_collect=true;
    CustomMeta a(&slow),b(&fast);
    for(unsigned i=0;i<8;++i){
        const auto* target=i%2?&META_Gd__gd_core__CoreItem:&META_Gd__gd_core_items__Gems__Gem;
        assert(gd::gd_is_type(V::from_obj(&a),target)==gd::native_inline_is_type(fast,V::from_obj(&b),target));
        assert(a.calls==b.calls && slow.math_rng.pcg.state==fast.math_rng.pcg.state && !b.native_call_row_);++boundaries;
    }
    const auto calls=b.calls;
    assert(!gd::native_inline_is_type(fast,V::from_obj(&b),nullptr) && b.calls==calls);
    assert(!gd::native_inline_is_type(fast,V::from_int(2),&META_Gd__gd_core__CoreItem));
    assert(gd::native_inline_self_type(nullptr,&b,&META_Gd__gd_core__CoreItem)==b.Gd__gd_core__CoreItem::meta()->is_subclass_of(&META_Gd__gd_core__CoreItem));
    // The preceding null-context predicate calls the custom metadata exactly once.
    assert(b.calls==calls+1);++boundaries;
    auto* known=constructor_cases[0].meta->alloc_fn(fast);
    known->native_call_row_=reinterpret_cast<const gd::NativeMethodRow*>(uintptr_t(1));
    assert(gd::native_inline_is_type(fast,V::from_obj(known),constructor_cases[0].meta));
    assert(fast.native_resolved_counts[4]==1);++boundaries;
    const V args[]={V::from_int(17),V::from_bool(true)};
    for(gd::ClsId id:{gd::ClsId(CLS_Gd__gd_core__CoreItem),gd::ClsId(0),gd::ClsId(1000000)}){
        gd::BattleCtx old_ctx,new_ctx;old_ctx.bind_battle(19);new_ctx.bind_battle(19);new_ctx.native_resolved_dispatch=true;
        gd::GdClassMeta custom=META_Gd__gd_core__CoreItem;custom.id=id;custom.alloc_fn=custom_alloc;
        std::vector<int> first,second;ctor_events=&first;
        const auto old_value=gd::construct_class(old_ctx,&custom,args,2);
        ctor_events=&second;const auto new_value=gd::construct_class(new_ctx,&custom,args,2);
        assert(old_value.kind==V::Kind::Obj && new_value.kind==V::Kind::Obj);
        assert((first==std::vector<int>{1,2,3}) && first==second);
        assert(old_ctx.math_rng.pcg.state==new_ctx.math_rng.pcg.state);++boundaries;
        custom.alloc_fn=nullptr;assert(gd::construct_class(new_ctx,&custom,args,2).is_null());++boundaries;
    }
    assert(gd::construct_class(fast,nullptr,args,2).is_null());
    fast.native_resolved_dispatch=false;
    assert(!gd::try_native_allocate_initialized(fast,&META_Gd__gd_core__CoreItem));++boundaries;
    assert(predicates==674ULL*674 && constructors==1348 && fields>10000);
    assert(gd_diag_native_type_constructor_stat(0)>0 && gd_diag_native_type_constructor_stat(2)>=1348);
    std::cout<<"{\"type_predicates\":"<<predicates<<",\"original_fused_initializations\":"<<constructors
        <<",\"graph_fields\":"<<fields<<",\"boundaries\":"<<boundaries
        <<",\"aliases_payloads_rng_ids_order_checked\":true}\n";
}
