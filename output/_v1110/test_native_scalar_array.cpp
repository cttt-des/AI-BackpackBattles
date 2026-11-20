#include "native_scalar_equal.hpp"
#include "native_array_index.hpp"
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>
using V=gd::GdVal;

struct Observer:gd::GdObj {
    int writes=0;
    V last=V::null();
    explicit Observer(gd::BattleCtx* ctx):gd::GdObj(ctx){}
    const gd::GdClassMeta* meta() const override {return nullptr;}
    bool set_prop(gd::BattleCtx&,gd::SymId,const V& v) override {++writes;last=v;return true;}
};

int main(){
    gd::BattleCtx ctx;
    auto* a=gd::GdArr::from_init(ctx.arena,{V::from_int(1),V::from_int(2)});
    auto* b=gd::GdArr::from_init(ctx.arena,{V::from_int(1),V::from_int(2)});
    auto* dict=gd::GdDict::create(ctx.arena);
    Observer first(&ctx),second(&ctx);
    const std::vector<V> values={V::null(),V::from_bool(false),V::from_bool(true),V::from_int(0),V::from_int(1),
        V::from_int(INT64_MIN),V::from_int(INT64_MAX),V::from_int(1LL<<53),V::from_int((1LL<<53)+1),
        V::from_float(0.0),V::from_float(-0.0),V::from_float(1.0),V::from_float(static_cast<double>(1LL<<53)),
        V::from_float(std::numeric_limits<double>::infinity()),V::from_float(-std::numeric_limits<double>::infinity()),
        V::from_float(std::numeric_limits<double>::quiet_NaN()),V::from_float(-1.25),
        V::from_cstr(ctx.arena,"x"),V::from_cstr(ctx.arena,"x"),V::from_cstr(ctx.arena,"different"),
        V::from_arr(a),V::from_arr(b),V::from_arr(nullptr),V::from_dict(dict),V::from_dict(nullptr),
        V::from_obj(&first),V::from_obj(&second),V::from_vec2(2,3),V::from_vec2(2,3)};
    unsigned comparisons=0;
    for(const auto& x:values)for(const auto& y:values){
        const bool expected=gd::gd_eq(x,y);
        assert(gd::native_scalar_eq(x,y)==expected);
        assert(gd::native_scalar_ne(x,y)==gd::gd_ne(x,y));++comparisons;
    }
    assert(!gd::native_scalar_eq(V::from_int(1LL<<53),V::from_int((1LL<<53)+1)));
    assert(gd::native_scalar_eq(V::from_int((1LL<<53)+1),V::from_float(static_cast<double>(1LL<<53))));
    const std::vector<V> keys={V::from_int(INT64_MIN),V::from_int(INT64_MAX),V::from_int(-4),V::from_int(-3),
        V::from_int(-1),V::from_int(0),V::from_int(2),V::from_int(3),V::from_bool(true),
        V::from_float(-1.0),V::from_float(1.25),V::null(),V::from_cstr(ctx.arena,"x")};
    unsigned writes=0;
    for(int kind=0;kind<6;++kind)for(const auto& key:keys){
        auto* left=gd::GdArr::from_init(ctx.arena,{V::from_int(1),V::from_int(2),V::from_int(3)});
        auto* right=left->duplicate(ctx.arena);
        auto* ld=gd::GdDict::create(ctx.arena);auto* rd=gd::GdDict::create(ctx.arena);
        V lv=kind==0?V::from_arr(left):kind==1?V::from_dict(ld):kind==2?V::null():
            kind==3?V::from_arr(nullptr):kind==4?V::from_arr(gd::GdArr::create(ctx.arena)):V::from_obj(&first);
        V rv=kind==0?V::from_arr(right):kind==1?V::from_dict(rd):kind==2?V::null():
            kind==3?V::from_arr(nullptr):kind==4?V::from_arr(gd::GdArr::create(ctx.arena)):V::from_obj(&second);
        const auto value=V::from_int(99);
        gd::set_index(ctx,lv,key,value);gd::native_array_set_index(ctx,rv,key,value);
        if(kind==0 || kind==4)assert(gd::gd_eq(lv,rv));
        if(kind==1)assert(gd::gd_eq(V::from_arr(ld->keys(ctx.arena)),V::from_arr(rd->keys(ctx.arena))) && gd::gd_eq(ld->get(key),rd->get(key)));
        if(kind==5)assert(first.writes==second.writes && gd::gd_eq(first.last,second.last));
        ++writes;
    }
    // The receiver itself can be the overwritten array element.
    auto* la=gd::GdArr::from_init(ctx.arena,{V::null()});
    auto* ra=gd::GdArr::from_init(ctx.arena,{V::null()});
    la->data[0]=V::from_arr(la);ra->data[0]=V::from_arr(ra);
    gd::set_index(ctx,la->data[0],V::from_int(0),V::from_int(17));
    gd::native_array_set_index(ctx,ra->data[0],V::from_int(0),V::from_int(17));
    assert(la->data[0].kind==V::Kind::Int && ra->data[0].i==17);
    auto* alias=gd::GdArr::from_init(ctx.arena,{V::from_int(1),V::from_int(2)});
    auto receiver=V::from_arr(alias);
    gd::native_array_set_index(ctx,receiver,V::from_int(0),alias->data[1]);
    assert(alias->data[0].i==2 && alias->data[1].i==2);
    std::cout<<comparisons<<" equality/inequality pairs and "<<writes<<" write cases; NaN, signed zero, mixed large ints/floats, container equality, custom setter calls and overwritten receiver aliases passed\n";
}
