#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItemData.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCombatLog.hpp"
#include <cassert>
#include <bit>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;
using Data=Gd__gd_core__CoreItemData;
using Context=Gd__gd_core__CoreContext;
using Rng=Gd__gd_core__CoreRng;
extern "C" void gd_init_all_classes();

struct Record {
    uint64_t hash=1469598103934665603ULL;
    unsigned snapshots=0,coordinate_calls=0,trace_calls=0,getters=0,metas=0;
    void bytes(const void* data,size_t size) {
        const auto* p=static_cast<const unsigned char*>(data);
        for(size_t i=0;i<size;++i){hash^=p[i];hash*=1099511628211ULL;}
    }
    void number(uint64_t n){bytes(&n,sizeof(n));}
    void tag(const char* s){while(*s){bytes(s,1);++s;}}
    void value(gd::BattleCtx& ctx,const V& v){
        number(static_cast<unsigned>(v.kind));
        if(v.kind==V::Kind::Float)number(std::bit_cast<uint64_t>(v.f));
        else {const auto* s=gd::gd_to_str(ctx.arena,v);bytes(s->data,s->len);}
    }
};

struct Log:gd::GdObj {
    Record& r;
    Log(gd::BattleCtx* c,Record& rec):GdObj(c),r(rec){}
    const gd::GdClassMeta* meta() const override{return &META_Gd__gd_core__CoreCombatLog;}
    bool has_own_method(gd::SymId s) const override{return s==SYM_GEN_snapshotItemTooltipStat_1384;}
    bool call_method(gd::BattleCtx& c,gd::SymId s,const V* a,int n,V& out) override {
        if(s!=SYM_GEN_snapshotItemTooltipStat_1384)return false;
        assert(n==2 && a[0].kind==V::Kind::Obj);
        auto* item=static_cast<Item*>(a[0].obj);
        ++r.snapshots;r.tag("snapshot");r.number(a[1].as_int());
        r.number(item->get_instance_id());r.value(c,item->f_speedScale);
        out=V::null();return true;
    }
};
struct CustomItem:Item {
    Record& r;std::function<void()> callback;
    CustomItem(gd::BattleCtx* c,Record& rec):Item(c),r(rec){}
    bool call_method(gd::BattleCtx& c,gd::SymId s,const V* a,int n,V& out) override {
        if(s!=SYM_GEN_getTopLeftCell_443)return Item::call_method(c,s,a,n,out);
        ++r.coordinate_calls;r.tag("coordinate");if(callback)callback();
        out=fn_getTopLeftCell(a,n);return true;
    }
};
struct CustomRng:Rng {
    Record& r;
    CustomRng(gd::BattleCtx* c,Record& rec):Rng(c),r(rec){}
    bool call_method(gd::BattleCtx& c,gd::SymId s,const V* a,int n,V& out) override {
        if(s!=SYM_GEN_trace_diag_1741)return Rng::call_method(c,s,a,n,out);
        ++r.trace_calls;r.tag("trace");for(int i=0;i<n;++i)r.value(c,a[i]);
        out=fn_trace_diag(a,n);return true;
    }
};
struct CustomData:Data {
    Record& r;std::function<void()> callback;
    CustomData(gd::BattleCtx* c,Record& rec):Data(c),r(rec){}
    bool get_prop(gd::SymId s,V& out) const override {
        if(s==SYM_GEN_identifier_1673){++r.getters;r.tag("identifier");if(callback)callback();}
        return Data::get_prop(s,out);
    }
};
struct CustomContext:Context {
    Record& r;
    CustomContext(gd::BattleCtx* c,Record& rec):Context(c),r(rec){}
    bool get_prop(gd::SymId s,V& out) const override {
        ++r.getters;r.tag("context");r.number(s);return Context::get_prop(s,out);
    }
};
struct ObservedObject:gd::GdObj {
    Record& r;std::function<void()> callback;
    ObservedObject(gd::BattleCtx* c,Record& rec):GdObj(c),r(rec){}
    const gd::GdClassMeta* meta() const override{++r.metas;r.tag("meta");return &META_Gd__gd_core__CoreItemData;}
    bool get_prop(gd::SymId s,V& out) const override {
        ++r.getters;r.tag("cell");r.number(s);if(callback)callback();
        out=V::from_float(s==gd::SYM_x ? 2.0:3.0);return true;
    }
};

int main(){
    gd_init_all_classes();unsigned cases=0;
    std::cout<<"{\"case_hashes\":[";
    for(unsigned flags=0;flags<4;++flags)for(unsigned mode=0;mode<31;++mode){
        if(std::getenv("GD_TRACE_TEST_CASES"))std::cerr<<"case "<<flags<<":"<<mode<<std::endl;
        gd::BattleCtx ctx;ctx.bind_battle(12345);
        ctx.native_event_kernel=mode!=1;ctx.native_resolved_dispatch=mode!=2;
        ctx.native_resolved_audit=true;
        Record r;
        Context plain_context(&ctx);CustomContext custom_context(&ctx,r);
        Context* context=mode==6 ? &custom_context:&plain_context;
        Rng plain_rng(&ctx);CustomRng custom_rng(&ctx,r);
        Rng* rng=mode==4 ? &custom_rng:&plain_rng;
        Data plain_data(&ctx);CustomData custom_data(&ctx,r);
        Data* data=(mode==5 || mode==10 || mode==13) ? &custom_data:&plain_data;
        auto* ordinary=static_cast<Item*>(META_Gd__gd_core__CoreItem.alloc_fn(ctx));
        CustomItem custom_item(&ctx,r);
        Item* item=(mode==3 || mode==12 || mode==29) ? &custom_item:ordinary;
        Item unseeded(&ctx);if(mode==30)item=&unseeded;
        ObservedObject observed(&ctx,r);Log log(&ctx,r);
        context->init_fields(ctx);rng->init_fields(ctx);data->init_fields(ctx);item->init_fields(ctx);
        context->f_rng=V::from_obj(rng);context->f_combat_log=V::from_obj(&log);
        rng->f_oracle_trace=V::from_bool(flags&1);rng->f__stacktrace=V::from_bool(flags&2);
        rng->f_oracle_trace_log=V::from_arr(gd::GdArr::from_init(ctx.arena,{}));
        data->f_identifier=V::from_str(gd::make_static_str("test-item"));
        item->f_descriptor=V::from_obj(data);item->f_ctx=V::from_obj(context);
        item->f_ownerType=V::from_int(1);item->f_speedScale=V::from_float(1.0);
        const V good_cells=V::from_arr(gd::GdArr::from_init(ctx.arena,{V::from_vec2(2,3),V::from_vec2(1,4)}));
        item->f_occupiedCells=good_cells;V amount=V::from_float(0.25);
        if(mode==3)custom_item.callback=[&]{ctx.math_rng.randf();};
        if(mode==7)amount=V::from_obj(&observed);
        if(mode==8)data->f_identifier=V::from_obj(&observed);
        if(mode==9 || mode==11){
            item->f_occupiedCells=V::from_arr(gd::GdArr::from_init(ctx.arena,{V::from_obj(&observed)}));
            observed.callback=[&]{ctx.math_rng.randf();if(mode==11)context->f_rng=V::from_obj(rng);};
        }
        if(mode==10){
            // The nested gd_add argument evaluation can read coordinates before
            // the descriptor. Keep coordinates valid, and repair the later RNG
            // receiver instead of assuming a nonexistent left-to-right order.
            item->f_occupiedCells=V::from_arr(gd::GdArr::from_init(ctx.arena,{}));
            context->f_rng=V::from_obj(reinterpret_cast<gd::GdObj*>(uintptr_t(0x1234)));
            custom_data.callback=[&]{item->f_occupiedCells=good_cells;context->f_rng=V::from_obj(rng);};
        }
        if(mode==11)context->f_rng=V::from_obj(reinterpret_cast<gd::GdObj*>(uintptr_t(0x1234)));
        if(mode==12)custom_item.callback=[&]{rng->f_oracle_trace=V::from_bool(true);rng->f__stacktrace=V::from_bool(true);};
        if(mode==13)custom_data.callback=[&]{rng->f_oracle_trace=V::from_bool(true);rng->f__stacktrace=V::from_bool(true);};
        if(mode==14)item->f_occupiedCells=V::from_arr(gd::GdArr::from_init(ctx.arena,{}));
        if(mode==15 || mode==16)item->f_occupiedCells=V::from_arr(gd::GdArr::from_init(ctx.arena,{V::from_vec2(mode==15 ? INFINITY:NAN,2)}));
        if(mode==17){item->f_occupiedCells=V::from_arr(gd::GdArr::from_init(ctx.arena,{V::from_vec2(-0.0,0.0)}));amount=V::from_float(-0.0);}
        if(mode==18)item->f_speedScale=V::from_float(NAN);
        if(mode==19)amount=V::from_str(gd::make_static_str("0.25"));
        if(mode==20)amount=V::from_bool(true);
        if(mode==21)amount=V::null();
        if(mode==22)item->f_ownerType=V::from_float(1.0);
        if(mode==23)item->f_descriptor=V::null();
        if(mode==24)item->f_ctx=V::null();
        if(mode==25)context->f_rng=V::null();
        if(mode==26)amount=good_cells;
        if(mode==27)amount=V::from_dict(ctx.arena.make<gd::GdDict>());
        if(mode==28)item->f_occupiedCells=V::from_int(2);
        item->fn_addSpeed(&amount,1);
        assert(r.snapshots==(mode==24 ? 0u:2u));
        if(mode==3 || mode==12 || mode==29)assert(r.coordinate_calls==1);
        if(mode==4)assert(r.trace_calls==1);
        if(mode==5 || mode==10 || mode==13)assert(r.getters==1);
        if(mode==9 || mode==11)assert(r.getters==2);
        r.value(ctx,item->f_speedScale);r.value(ctx,rng->f_oracle_trace_log);
        r.number(ctx.math_rng.pcg.state);r.number(ctx.next_gid);r.number(item->gid_);r.number(observed.gid_);
        r.number(r.snapshots);r.number(r.coordinate_calls);r.number(r.trace_calls);r.number(r.getters);r.number(r.metas);
        if(cases++)std::cout<<',';std::cout<<r.hash;
    }
    std::cout<<"],\"cases\":"<<cases<<",\"snapshots_and_custom_callbacks_asserted\":true}\n";
}
