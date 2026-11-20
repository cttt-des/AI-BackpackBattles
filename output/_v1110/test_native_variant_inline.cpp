#include "native_inline_dispatch.hpp"
#include <bit>
#include <cassert>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>
using V=gd::GdVal;
extern "C" uint64_t gd_diag_native_variant_stat(unsigned);

bool same(const V& a,const V& b){
    if(a.kind!=b.kind)return false;
    if(a.kind==V::Kind::Float)return std::bit_cast<uint64_t>(a.f)==std::bit_cast<uint64_t>(b.f);
    return gd::gd_eq(a,b);
}
int calls=0,forward_calls=0;
bool handled=true;
bool callback(gd::BattleCtx&,gd::SymId,const V* args,int argc,V& out){
    ++calls;out=argc>0?args[argc-1]:V::from_int(77);return handled;
}
bool forward(gd::BattleCtx& ctx,gd::SymId m,const V* args,int argc,V& out){
    ++forward_calls;return callback(ctx,m,args,argc,out);
}
extern gd::GdClassMeta tiny_meta;
struct Tiny:gd::GdObj {
    int initialized=0,init_calls=0,method_calls=0;
    V value=V::null();
    explicit Tiny(gd::BattleCtx* ctx):gd::GdObj(ctx){}
    const gd::GdClassMeta* meta() const override {return &tiny_meta;}
    void init_fields(gd::BattleCtx&) override {++initialized;}
    bool call_method(gd::BattleCtx&,gd::SymId method,const V* args,int argc,V& out) override {
        if(method==gd::SYM__init){++init_calls;value=argc?args[0]:V::null();out=V::null();return true;}
        if(method==gd::SYM_size){++method_calls;out=V::from_int(909);return true;}
        return false;
    }
};
gd::GdObj* allocate(gd::BattleCtx& ctx){return ctx.arena.make<Tiny>(&ctx);}
gd::GdClassMeta tiny_meta={gd::CLS_NONE,"Tiny","",nullptr,false,allocate,nullptr,callback};

int main(){
    register_gen_syms();gd::BattleCtx ctx;
    ctx.native_resolved_dispatch=true;ctx.native_resolved_collect=true;ctx.native_resolved_audit=true;
    const auto nan=V::from_float(std::bit_cast<double>(UINT64_C(0x7ff8000000001234)));
    auto* array=gd::GdArr::from_init(ctx.arena,{V::from_int(1),V::from_bool(false),V::null(),V::from_float(-0.0),nan});
    auto* empty=gd::GdArr::create(ctx.arena);
    auto* dict=gd::GdDict::create(ctx.arena);
    dict->set(ctx.arena,V::from_int(1),V::from_int(41));
    dict->set(ctx.arena,V::null(),V::from_float(-0.0));
    const auto text=V::from_cstr(ctx.arena,"text");dict->set(ctx.arena,text,nan);
    auto* missing=gd::GdDict::create(ctx.arena);
    const std::vector<V> receivers={V::from_arr(array),V::from_arr(empty),V::from_arr(nullptr),
        V::from_dict(dict),V::from_dict(missing),V::from_dict(nullptr),V::null(),V::from_int(1),text};
    const std::vector<gd::SymId> methods={gd::SYM_size,gd::SYM_empty,gd::SYM_has,gd::SYM_front,gd::SYM_back,gd::SYM_get};
    const std::vector<V> keys={V::from_int(1),V::from_float(1.0),V::from_bool(true),V::from_bool(false),
        V::null(),text,V::from_cstr(ctx.arena,"missing"),nan,V::from_int(INT64_MAX)};
    unsigned checks=0;
    for(const auto& recv:receivers)for(const auto method:methods){
        assert(same(gd::call_method(ctx,recv,method,nullptr,0),gd::native_inline_call(ctx,recv,method,nullptr,0)));++checks;
        for(const auto& key:keys)for(int argc: {1,2}){
            const V args[]={key,V::from_float(-0.0)};
            assert(same(gd::call_method(ctx,recv,method,args,argc),gd::native_inline_call(ctx,recv,method,args,argc)));++checks;
        }
    }
    // Mutations are still handled by the original paths, and queries see them.
    const auto item=V::from_int(19);
    gd::native_inline_call(ctx,V::from_arr(array),gd::SYM_push_back,&item,1);
    assert(array->len==6 && gd::native_inline_call(ctx,V::from_arr(array),gd::SYM_back,nullptr,0).i==19);
    dict->set(ctx.arena,V::from_int(1),item);
    assert(gd::native_inline_call(ctx,V::from_dict(dict),gd::SYM_get,&item,1).is_null());
    const auto one=V::from_int(1);
    assert(gd::native_inline_call(ctx,V::from_dict(dict),gd::SYM_get,&one,1).i==19);
    gd::GdClassMeta parent={gd::CLS_NONE,"Parent","",nullptr,false,nullptr,nullptr,callback};
    gd::GdClassMeta child={gd::CLS_NONE,"Child","",&parent,false,nullptr,nullptr,forward};
    gd::GdClassMeta no_callback=child;no_callback.call_static_fn=nullptr;
    V null_class;null_class.kind=V::Kind::ClassRef;null_class.cls=nullptr;
    const V args[]={V::from_int(9),nan};
    for(bool result: {false,true})for(const auto& recv: {V::from_cls(&parent),V::from_cls(&child),V::from_cls(&no_callback),null_class}){
        handled=result;calls=forward_calls=0;
        const auto expected=gd::call_method(ctx,recv,gd::SYM_size,args,2);
        const auto expected_calls=calls,expected_forward=forward_calls;
        calls=forward_calls=0;
        const auto actual=gd::native_inline_call(ctx,recv,gd::SYM_size,args,2);
        assert(same(expected,actual) && calls==expected_calls && forward_calls==expected_forward);
        assert(calls<=1 && forward_calls<=1);++checks;
    }
    handled=true;calls=0;
    const auto before_ctor=gd_diag_native_variant_stat(9);
    const auto a=gd::call_method(ctx,V::from_cls(&tiny_meta),gd::SYM_new,&item,1);
    const auto b=gd::native_inline_call(ctx,V::from_cls(&tiny_meta),gd::SYM_new,&item,1);
    auto* first=static_cast<Tiny*>(a.obj);auto* second=static_cast<Tiny*>(b.obj);
    assert(first->initialized==1 && second->initialized==1 && first->init_calls==1 && second->init_calls==1);
    assert(same(first->value,second->value) && calls==0 && gd_diag_native_variant_stat(9)==before_ctor);
    assert(gd::native_inline_call(ctx,b,gd::SYM_size,nullptr,0).i==909 && second->method_calls==1);
    uint64_t before[10];for(int i=0;i<10;++i)before[i]=gd_diag_native_variant_stat(i);
    ctx.native_resolved_dispatch=false;
    for(const auto& recv:receivers)for(const auto method:methods)
        assert(same(gd::call_method(ctx,recv,method,nullptr,0),gd::native_inline_call(ctx,recv,method,nullptr,0)));
    for(int i=0;i<10;++i)assert(gd_diag_native_variant_stat(i)==before[i]);
    assert(ctx.native_resolved_counts[4]==0);
    std::cout<<checks<<" variant differential cases; null/empty/default/mixed-key/numeric-alias/NaN, container mutation visibility, one static callback/false Null, forwarded static dispatch, new constructor, object override and disabled path passed\n";
}
