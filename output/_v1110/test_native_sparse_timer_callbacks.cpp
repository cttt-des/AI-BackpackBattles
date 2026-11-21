#include "native_inline_dispatch.hpp"
#include "native_array_index.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCombat.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreTimer.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;
extern "C" void gd_init_all_classes();
static gd::SymId mutate_symbol;
static std::function<void()> static_action;
static unsigned static_calls=0;
static bool static_handled=true;
static bool static_callback(gd::BattleCtx&,gd::SymId,const V*,int,V& out) {
    ++static_calls;auto action=std::move(static_action);if(action)action();
    out=V::from_int(77);return static_handled;
}
static bool static_getter(gd::SymId,V& out) {
    ++static_calls;auto action=std::move(static_action);if(action)action();
    out=V::from_int(77);return true;
}
struct Callback:Item {
    mutable std::function<void()> action;
    explicit Callback(gd::BattleCtx* ctx):Item(ctx) {}
    void fire() const {auto call=std::move(action);if(call)call();}
    bool get_prop(gd::SymId p,V& out) const override {
        if(p!=mutate_symbol)return Item::get_prop(p,out);
        fire();out=V::from_int(1);return true;
    }
    bool set_prop(gd::BattleCtx& ctx,gd::SymId p,const V& v) override {
        if(p!=mutate_symbol)return Item::set_prop(ctx,p,v);
        fire();return true;
    }
    bool has_own_method(gd::SymId m) const override {
        if(m!=mutate_symbol)return Item::has_own_method(m);
        fire();return true;
    }
    bool call_method(gd::BattleCtx& ctx,gd::SymId m,const V* a,int n,V& out) override {
        if(m!=mutate_symbol)return Item::call_method(ctx,m,a,n,out);
        fire();out=V::from_int(n);return true;
    }
};
struct Timer:Gd__gd_core__CoreTimer {
    std::vector<int>* trace;
    explicit Timer(gd::BattleCtx* c,std::vector<int>* events):Gd__gd_core__CoreTimer(c),trace(events) {}
    bool call_method(gd::BattleCtx& ctx,gd::SymId m,const V* a,int n,V& out) override {
        if(m!=SYM_GEN_tick_1516)return Gd__gd_core__CoreTimer::call_method(ctx,m,a,n,out);
        assert(n==1 && a[0].as_float()==0.25);trace->push_back(1);out=V::null();return true;
    }
};

static void outside_callback(unsigned mode) {
    gd::BattleCtx ctx;
    ctx.native_resolved_dispatch=true;ctx.native_resolved_audit=true;
    ctx.native_inline_timer_headers=true;ctx.native_sparse_timer_scans=true;
    Gd__gd_core__CoreCombat combat(&ctx);combat.init_fields(ctx);
    Gd__gd_core__CoreCharacter character(&ctx);character.init_fields(ctx);
    Gd__gd_core__CoreGrid grid(&ctx);grid.init_fields(ctx);
    character.f_inventory=V::from_obj(&grid);
    auto* item=static_cast<Item*>(META_Gd__gd_core__CoreItem.alloc_fn(ctx));item->init_fields(ctx);
    grid.f_items=V::from_arr(gd::GdArr::from_init(ctx.arena,{V::from_obj(item)}));
    const V args[]={V::from_obj(&character),V::from_float(0.25)};
    std::vector<int> trace;
    auto* timer=ctx.arena.make<Timer>(&ctx,&trace);timer->init_fields(ctx);
    // An unmarked replacement and direct public-field assignment bypass every
    // array/setter hook. The external callback boundary must invalidate first.
    auto replace=[&] {item->f_timers=V::from_arr(gd::GdArr::from_init(ctx.arena,{V::from_obj(timer)}));};
    Callback object(&ctx);object.init_fields(ctx);object.action=replace;
    auto receiver=V::from_obj(&object);
    combat.fn__tickCharacterTimers(args,2);
    assert(character.native_timer_scan_cache_.count==0);
    const auto old_epoch=gd::native_timer_scan_state().epoch;
    if(mode==0)gd::get_prop(ctx,receiver,mutate_symbol);
    if(mode==1)gd::set_prop(ctx,receiver,mutate_symbol,V::null());
    if(mode==2)gd::native_inline_call(ctx,receiver,mutate_symbol,nullptr,0);
    if(mode==3 || mode==4) {
        gd::GdFuncRef ref;ref.instance=&object;ref.method=mutate_symbol;
        if(mode==4)ref.binds=gd::GdArr::from_init(ctx.arena,{V::from_int(5)});
        const V empty=V::null();
        const auto result=ref.call_func(ctx,&empty,0);assert(result.i==(mode==4?1:0));
    }
    if(mode==5 || mode==6 || mode==7) {
        gd::GdClassMeta type={gd::CLS_NONE,"ExternalStatic","",nullptr,false,nullptr,static_getter,static_callback};
        static_action=replace;static_calls=0;static_handled=mode!=6;
        auto cls=V::from_cls(&type);
        const auto result=mode==7 ? gd::get_prop(ctx,cls,mutate_symbol)
            : gd::native_inline_call(ctx,cls,mutate_symbol,nullptr,0);
        assert(static_calls==1);
        assert(mode==6?result.is_null():result.i==77);
    }
    if(mode==8) {
        // Repaired an incorrect cached row must be classified by exact RTTI
        // before treating this C++ override as a generated pure getter.
        object.native_call_row_=item->native_call_row_;
        gd::get_prop(ctx,receiver,mutate_symbol);
    }
    if(mode==9) {
        gd::GdFuncRef ref;ref.instance=&object;ref.method=mutate_symbol;
        assert(ref.is_valid());
    }
    assert(gd::native_timer_scan_state().epoch>old_epoch);
    combat.fn__tickCharacterTimers(args,2);
    assert((trace==std::vector<int>{1}));
    assert(gd::native_timer_scan_state().depth==0 && gd::native_timer_scan_state().sorting==0);
}

int main() {
    gd_init_all_classes();mutate_symbol=gd::intern_sym("sparse_timer_external_mutation");
    unsigned allocated=0;
    for(bool enabled:{false,true}) {
        gd::BattleCtx ctx;ctx.native_resolved_dispatch=enabled;
        const auto rng=ctx.math_rng.pcg.state;
        unsigned count=0;
        for(unsigned id=0;id<4096;++id) {
            const auto* type=gd::find_class_by_id(id);if(!type)continue;
            assert(gd::native_resolved_generated_class(type));
            auto* object=type->alloc_fn(ctx);assert(object && object->meta()==type);
            if(enabled)assert(object->native_call_row_ && gd::native_resolved_row_matches(object,object->native_call_row_));
            else assert(!object->native_call_row_);
            ++count;
        }
        assert(count==674 && ctx.math_rng.pcg.state==rng);allocated+=count;
    }
    for(unsigned mode=0;mode<10;++mode)outside_callback(mode);
    gd::BattleCtx ctx;ctx.native_sparse_timer_scans=true;
    auto* array=gd::GdArr::from_init(ctx.arena,{V::from_int(1),V::from_int(2)});
    gd::native_timer_scan_mark(ctx,V::from_arr(array));
    const auto epoch=gd::native_timer_scan_state().epoch;
    auto receiver=V::from_arr(array);
    gd::native_array_set_index(ctx,receiver,V::from_int(-1),V::from_int(9));
    assert(array->data[1].i==9 && gd::native_timer_scan_state().epoch>epoch);
    Gd__gd_core__CoreCharacter original(&ctx);original.init_fields(ctx);
    uint32_t indices[2]{0,1};
    original.native_timer_scan_cache_.indices=indices;
    original.native_timer_scan_cache_.capacity=2;
    original.f_inventory=V::from_int(44);
    Gd__gd_core__CoreCharacter copied(original),assigned(&ctx);
    assigned=original;
    Gd__gd_core__CoreCharacter moved(std::move(original));
    assert(!copied.native_timer_scan_cache_.indices && !assigned.native_timer_scan_cache_.indices &&
        !moved.native_timer_scan_cache_.indices && original.native_timer_scan_cache_.indices==indices);
    original=original;assert(!original.native_timer_scan_cache_.indices);
    for(const auto* c:{&original,&copied,&assigned,&moved})assert(c->f_inventory.i==44);
    std::cout<<"{\"exact_allocations_checked\":"<<allocated<<",\"outside_callback_cases\":10,\"character_copy_cases\":4,\"inline_write_tracking\":true}\n";
}
