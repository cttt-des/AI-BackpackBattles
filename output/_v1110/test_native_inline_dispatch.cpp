#include "native_inline_dispatch.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core_items__Gems__Gem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include <bit>
#include <cassert>
#include <cstring>
#include <iostream>
using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;
using Gem=Gd__gd_core_items__Gems__Gem;

struct Custom:Item {
    int calls=0;
    mutable int metadata_reads=0;
    explicit Custom(gd::BattleCtx* c):Item(c){}
    const gd::GdClassMeta* meta() const override {++metadata_reads;return Item::meta();}
    bool call_method(gd::BattleCtx& c,gd::SymId method,const V* args,int argc,V& out) override {
        if(method==SYM_GEN_character_74 || method==UINT32_MAX){++calls;out=V::from_int(71);return true;}
        return Item::call_method(c,method,args,argc,out);
    }
};

int main(){
    register_gen_syms();
    gd::BattleCtx ctx;
    ctx.native_resolved_dispatch=true;ctx.native_resolved_collect=true;ctx.native_resolved_audit=true;
    auto call=[&](gd::GdObj* object,gd::SymId method=SYM_GEN_character_74){
        return gd::native_inline_call(ctx,V::from_obj(object),method,nullptr,0);
    };
    Item item(&ctx);item.init_fields(ctx);item.f_character_=V::from_int(11);
    assert(item.native_call_row_==nullptr);
    auto hits=ctx.native_resolved_counts[0];
    assert(call(&item).i==11 && item.native_call_row_ && ctx.native_resolved_counts[0]==hits+1);
    const auto resolutions=ctx.native_resolved_counts[2];
    assert(call(&item).i==11 && ctx.native_resolved_counts[2]==resolutions && ctx.native_resolved_counts[0]==hits+2);
    // Return values must retain payload bits as well as their Variant kind.
    for(bool audit: {false,true})for(const uint64_t bits: {UINT64_C(0x8000000000000000),UINT64_C(0x7ff8000000001234),UINT64_C(0x3ff8000000000000)}){
        ctx.native_resolved_audit=audit;
        item.f_character_=V::from_float(std::bit_cast<double>(bits));
        const auto before=gd::call_method(ctx,V::from_obj(&item),SYM_GEN_character_74,nullptr,0);
        const auto after=call(&item);
        assert(after.kind==before.kind && std::bit_cast<uint64_t>(after.f)==std::bit_cast<uint64_t>(before.f));
    }
    item.f_character_=V::from_int(11);
    Gd__gd_core__CoreContext context(&ctx);context.init_fields(ctx);context.f_player=V::from_int(22);
    Gem gem(&ctx);gem.init_fields(ctx);gem.f_character_=V::from_int(11);gem.f_ctx=V::from_obj(&context);
    gem.f_socket=V::null();gem.f_placed=V::from_bool(false);
    assert(call(&gem).i==22 && call(&gem).i==22);
    Item sliced(gem);assert(!sliced.native_call_row_ && call(&sliced).i==11);
    item=gem;assert(!item.native_call_row_ && call(&item).i==11);
    Custom custom(&ctx);custom.init_fields(ctx);
    assert(call(&custom).i==71 && custom.calls==1);
    assert(call(&custom).i==71 && custom.calls==2 && custom.metadata_reads==0);
    assert(call(&custom,UINT32_MAX).i==71 && custom.calls==3);
    // Corrupt/wrong rows must be audited before their methods are read.
    assert(ctx.native_resolved_counts[4]==0);
    item.native_call_row_=reinterpret_cast<const gd::NativeMethodRow*>(uintptr_t{1});
    const auto mismatches=ctx.native_resolved_counts[4];
    assert(call(&item).i==11 && ctx.native_resolved_counts[4]==mismatches+1);
    item.native_call_row_=nullptr;ctx.native_resolved_counts[4]=0;
    V null_object;null_object.kind=V::Kind::Obj;null_object.obj=nullptr;
    assert(gd::native_inline_call(ctx,null_object,SYM_GEN_character_74,nullptr,0).is_null());
    auto* array=gd::GdArr::create(ctx.arena);const auto value=V::from_int(9);
    gd::native_inline_call(ctx,V::from_arr(array),gd::SYM_push_back,&value,1);
    assert(array->len==1 && array->data[0].i==9);
    auto* dict=gd::GdDict::create(ctx.arena);const auto key=V::from_cstr(ctx.arena,"key");dict->set(ctx.arena,key,value);
    assert(gd::native_inline_call(ctx,V::from_dict(dict),gd::SYM_get,&key,1).i==9);
    hits=ctx.native_resolved_counts[0];ctx.native_resolved_dispatch=false;
    assert(call(&gem).i==22 && ctx.native_resolved_counts[0]==hits);
    ctx.native_resolved_dispatch=true;ctx.native_resolved_audit=false;
    gd::BattleCtx slow;
    Gd__gd_core__CoreRng a(&ctx),b(&slow);a.init_fields(ctx);b.init_fields(slow);
    const auto seed=V::from_int(773190);a.fn__init(&seed,1);b.fn__init(&seed,1);
    for(int i=0;i<512;++i){
        const V args[]={V::from_float(-i-0.125),V::from_float(i+0.75)};
        const auto x=gd::native_inline_call(ctx,V::from_obj(&a),gd::SYM_randf_range,args,2);
        const auto y=gd::call_method(slow,V::from_obj(&b),gd::SYM_randf_range,args,2);
        assert(x.kind==y.kind && !std::memcmp(&x.f,&y.f,sizeof(double)) && gd::gd_eq(a.f_draw_seq,b.f_draw_seq));
    }
    assert(ctx.native_resolved_counts[4]==0);
    std::cout<<"Cached/uncached exact dispatch, generated/C++ overrides, single fallback, copy/slicing, audit-before-row-read, null/array/dictionary/disabled paths, return payload bits and512 RNG comparisons passed\n";
}
