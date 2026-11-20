#include "native_array_index.hpp"
#include <cassert>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>
using V=gd::GdVal;

struct Observer:gd::GdObj {
    mutable int reads=0;
    explicit Observer(gd::BattleCtx* c):gd::GdObj(c){}
    const gd::GdClassMeta* meta() const override {return nullptr;}
    bool get_prop(gd::SymId, V& out) const override {out=V::from_int(++reads);return true;}
};

bool same(const V& a,const V& b) {
    if(a.kind!=b.kind)return false;
    if(a.kind==V::Kind::Null)return true;
    if(a.kind==V::Kind::Str)return a.str->len==b.str->len && !std::memcmp(a.str->data,b.str->data,a.str->len);
    if(a.kind==V::Kind::Float)return std::memcmp(&a.f,&b.f,sizeof(a.f))==0;
    if(a.kind==V::Kind::Arr)return a.arr==b.arr;
    if(a.kind==V::Kind::Dict)return a.dict==b.dict;
    return gd::gd_eq(a,b);
}

int main(){
    gd::BattleCtx ctx;
    auto* nested=gd::GdArr::from_init(ctx.arena,{V::from_int(71)});
    auto* array=gd::GdArr::from_init(ctx.arena,{V::from_int(7),V::null(),V::from_float(-0.0),
        V::from_cstr(ctx.arena,"x"),V::from_arr(nested)});
    auto* empty=gd::GdArr::create(ctx.arena);
    auto* dict=gd::GdDict::create(ctx.arena);
    dict->set(ctx.arena,V::from_int(-1),V::from_int(92));
    dict->set(ctx.arena,V::from_cstr(ctx.arena,"x"),V::from_int(93));
    const std::vector<V> receivers={V::from_arr(array),V::from_arr(empty),V::from_arr(nullptr),
        V::from_dict(dict),V::from_dict(nullptr),V::null(),V::from_int(12),V::from_cstr(ctx.arena,"abc")};
    const std::vector<V> keys={V::from_int(INT64_MIN),V::from_int(INT64_MAX),V::from_int(-6),
        V::from_int(-5),V::from_int(-1),V::from_int(0),V::from_int(4),V::from_int(5),
        V::from_float(-1.0),V::from_float(1.25),V::from_float(0.0),V::from_bool(true),
        V::from_bool(false),V::null(),V::from_cstr(ctx.arena,"x")};
    unsigned cases=0;
    for(const auto& recv:receivers)for(const auto& key:keys){
        assert(same(gd::get_index(ctx,recv,key),gd::native_array_index(ctx,recv,key)));++cases;
    }
    for(int i=-80;i<80;++i){
        assert(same(gd::get_index(ctx,V::from_arr(array),V::from_int(i)),
                    gd::native_array_index(ctx,V::from_arr(array),V::from_int(i))));++cases;
    }
    auto escaped=gd::native_array_index(ctx,V::from_arr(array),V::from_int(-1));
    escaped.arr->push_back(ctx.arena,V::from_int(72));assert(nested->len==2);
    array->set_idx(0,V::from_int(81));
    assert(gd::native_array_index(ctx,V::from_arr(array),V::from_int(0)).i==81);
    Observer legacy(&ctx),candidate(&ctx);
    const auto key=V::from_cstr(ctx.arena,"observed");
    for(int i=0;i<5;++i){
        assert(same(gd::get_index(ctx,V::from_obj(&legacy),key),gd::native_array_index(ctx,V::from_obj(&candidate),key)));
        assert(legacy.reads==candidate.reads && candidate.reads==i+1);
    }
    std::cout<<cases<<" index differential cases; boundary, null, mixed key, object getter count and reference alias checks passed\n";
}
