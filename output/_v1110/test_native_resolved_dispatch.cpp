#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core_items__Gems__Gem.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MagicRing.hpp"
#include <cassert>
#include <iostream>

using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;
using Gem=Gd__gd_core_items__Gems__Gem;

// Inherits the generated metadata but intercepts the method in custom C++.
struct CustomItem:Item {
    mutable int metadata_reads=0;
    int calls=0,argc_seen=0;
    int64_t bound_seen=0;
    explicit CustomItem(gd::BattleCtx* ctx):Item(ctx){}
    const gd::GdClassMeta* meta() const override {++metadata_reads;return Item::meta();}
    bool call_method(gd::BattleCtx& ctx,gd::SymId method,const V* args,int argc,V& out) override {
        if(method!=SYM_GEN_character_74)return Item::call_method(ctx,method,args,argc,out);
        ++calls;argc_seen=argc;bound_seen=argc?args[argc-1].as_int():0;out=V::from_int(40);return true;
    }
};

int main(){
    register_gen_syms();
    gd::BattleCtx ctx;
    ctx.native_resolved_dispatch=true;ctx.native_resolved_collect=true;ctx.native_resolved_audit=true;
    auto call=[&](gd::GdObj& object,gd::SymId method,const V* args=nullptr,int argc=0){
        return gd::call_method(ctx,V::from_obj(&object),method,args,argc);
    };
    Item item(&ctx);item.init_fields(ctx);item.f_character_=V::from_int(11);
    assert(item.native_call_row_==nullptr);
    assert(call(item,SYM_GEN_character_74).as_int()==11 && item.native_call_row_);
    Gd__gd_core__CoreContext context(&ctx);context.init_fields(ctx);context.f_player=V::from_int(22);
    Gem gem(&ctx);gem.init_fields(ctx);gem.f_character_=V::from_int(11);
    gem.f_ctx=V::from_obj(&context);gem.f_socket=V::null();gem.f_placed=V::from_bool(false);
    assert(call(gem,SYM_GEN_character_74).as_int()==22); // Most-derived method, not CoreItem's.
    Item sliced(gem);assert(sliced.native_call_row_==nullptr);
    assert(call(sliced,SYM_GEN_character_74).as_int()==11);
    item=gem;assert(item.native_call_row_==nullptr);
    assert(call(item,SYM_GEN_character_74).as_int()==11);
    Gem copied(gem);assert(copied.native_call_row_==nullptr);
    assert(call(copied,SYM_GEN_character_74).as_int()==22);
    Gd__gd_core_items__Exclusive__MagicRing ring(&ctx);ring.init_fields(ctx);
    ring.f_ringTypes=V::from_arr(gd::GdArr::from_init(ctx.arena,{V::from_int(777)}));
    const V type=V::from_int(777);
    assert(gd::gd_truth(call(ring,SYM_GEN_hasType_79,&type,1)));
    assert(!gd::gd_truth(ring.Item::fn_hasType(&type,1)));
    CustomItem custom(&ctx);custom.init_fields(ctx);
    assert(call(custom,SYM_GEN_character_74).as_int()==40);
    assert(custom.calls==1 && custom.metadata_reads==0);
    const auto* unsupported=custom.native_call_row_;assert(unsupported);
    assert(call(custom,SYM_GEN_character_74).as_int()==40 && custom.native_call_row_==unsupported);
    assert(custom.metadata_reads==0);
    gd::GdFuncRef ref;
    ref.instance=&item;ref.method=SYM_GEN_character_74;
    ref.binds=gd::GdArr::from_init(ctx.arena,{V::from_int(99)});
    const V argument=V::from_int(7);
    assert(ref.call_func(ctx,&argument,1).as_int()==11);
    ref.instance=&custom;
    assert(ref.call_func(ctx,&argument,1).as_int()==40);
    assert(custom.argc_seen==2 && custom.bound_seen==99 && custom.metadata_reads==0);
    ref.method=gd::intern_sym("unhandled_native_dispatch_test");
    assert(ref.call_func(ctx,&argument,1).is_null());
    const auto hits=ctx.native_resolved_counts[0];
    ctx.native_resolved_dispatch=false;
    assert(call(gem,SYM_GEN_character_74).as_int()==22 && ctx.native_resolved_counts[0]==hits);
    assert(ctx.native_resolved_counts[0]>0 && ctx.native_resolved_counts[1]>0);
    assert(ctx.native_resolved_counts[3]>0 && ctx.native_resolved_counts[4]==0);
    std::cout<<"Resolved generated overrides, shared-metadata C++ overrides, copy/slicing/assignment, rebound FuncRef binds, unknown method and disabled fallback passed\n";
}
