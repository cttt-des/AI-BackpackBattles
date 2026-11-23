#include "native_inline_dispatch.hpp"
#include "native_array_index.hpp"
#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"
#include "cooldown_original_phase.hpp"
#ifdef GD_DISPLAY_NEW
extern "C" void gd_diag_native_frame_proof_tick(Gd__gd_core__CoreItem*,gd::NativeFrameSegmentSnapshot*,const gd::GdVal*);
extern "C" int gd_diag_native_frame_proof_phase(Gd__gd_core__CoreCharacter*,gd::NativeFrameSegmentSnapshot*,const gd::GdVal*);

#endif
extern "C" uint64_t gd_diag_native_frame_segment_stat(unsigned);
extern "C" uint64_t gd_diag_native_type_constructor_stat(unsigned);
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <array>
#include <bit>
#include <cassert>
#include <cfenv>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <xmmintrin.h>
extern "C" void gd_init_all_classes();
using V=gd::GdVal;using Item=Gd__gd_core__CoreItem;using Character=Gd__gd_core__CoreCharacter;
using Context=Gd__gd_core__CoreContext;using Grid=Gd__gd_core__CoreGrid;using Gem=Gd__gd_core_items__Gems__Gem;
static uint64_t mix(uint64_t h,uint64_t x){return(h^x)*1099511628211ULL;}
static double snan(){return std::bit_cast<double>(UINT64_C(0x7ff0000000001234));}
struct Hook:gd::GdObj {
    std::function<bool(gd::SymId,const V*,int,V&)> action;
    using GdObj::GdObj;
    const gd::GdClassMeta* meta()const override{return nullptr;}
    bool call_method(gd::BattleCtx&,gd::SymId m,const V* a,int n,V& out)override{return action && action(m,a,n,out);}
};
struct Fixture {
    gd::BattleCtx c{65536},foreign{8192};Context* context;Character* characters[2];Grid* grids[2];
    std::vector<Item*> items,gems;std::vector<gd::GdObj*> identities;std::vector<gd::GdArr*> arrays;
    Hook hooks{&c},socket{&c};gd::GdArr external;unsigned scenario,configuration,nesting=0;
    bool armed=true,getter_armed=true;uint64_t trace=1469598103934665603ULL;
    Fixture(unsigned s,unsigned config):scenario(s),configuration(config) {
        c.bind_battle(42);c.native_resolved_dispatch=true;c.native_resolved_audit=true;c.native_resolved_collect=true;
        c.native_event_kernel=true;c.native_event_audit=true;c.native_inline_timer_headers=true;
        c.native_timer_watch.enabled=true;c.native_timer_watch.closed_world=config!=2;c.native_timer_watch.trusted_hooks=&hooks;
        V seed=V::from_int(42);context=static_cast<Context*>(gd::construct_class(c,&META_Gd__gd_core__CoreContext,&seed,1).obj);
        context->f_hooks=V::from_obj(&hooks);context->f_show_cooldown_progress=V::from_bool(true);
        context->f_timer_pass_epoch=V::from_int(17);context->f_in_item_physics_pass=V::from_bool(true);
        context->f_in_physics_timer_pass=V::from_bool(false);identities.push_back(context);
        for(unsigned side=0;side<2;++side) {
            V args[]={V::from_obj(context),V::from_int(side)};
            auto* chr=static_cast<Character*>(gd::construct_class(c,&META_Gd__gd_core__CoreCharacter,args,2).obj);
            characters[side]=chr;identities.push_back(chr);grids[side]=static_cast<Grid*>(chr->f_inventory.obj);
            identities.push_back(grids[side]);track(grids[side]->f_items.arr);
            chr->f_stunnedDuration=V::from_float(0.0);
            for(unsigned i=0;i<4;++i) {
                const bool as_gem=(s==43 || s==44 || s==61 || s==62) && side==0 && i==1;
                auto* item=make_item(chr,as_gem);items.push_back(item);
                grids[side]->f_items.arr->push_back(c.arena,V::from_obj(item));
                if(i==0){auto* gem=make_item(chr,false);gems.push_back(gem);item->f_gems.arr->push_back(c.arena,V::from_obj(gem));}
            }
        }
        identities.push_back(&hooks);identities.push_back(&socket);
        context->f_player=V::from_obj(characters[0]);context->f_opponent=V::from_obj(characters[1]);
        if(s==18)items[3]->f_statDisplayOverrides=items[1]->f_statDisplayOverrides;
        if(s==24)items[1]->f_statDisplayOverrides.arr->data[3]=V::from_float(2.75);
        if(s==25)items[1]->f_statDisplayOverrides.arr->data[3]=V::from_float(snan());
        if(s==26){external.data=items[1]->f_statDisplayOverrides.arr->data;external.len=external.cap=5;items[1]->f_statDisplayOverrides=V::from_arr(&external);track(&external);}
        if(s==27){auto* a=gd::GdArr::create(foreign.arena,5);a->resize(foreign.arena,5);items[1]->f_statDisplayOverrides=V::from_arr(a);track(a);}
        if(s==28)items[1]->f_statDisplayOverrides.arr->timer_watch=&foreign.native_timer_watch;
        if(s==29)items[1]->f_statDisplayOverrides=V::from_arr(nullptr);
        if(s==30)items[1]->f_statDisplayOverrides.arr->resize(c.arena,3);
        if(s==39)c.native_timer_watch.cooldown_version=UINT64_MAX;
        if(s==40)items[1]->f__cooldown_active=V::from_int(1);
        if(s==41)items[1]->f_statDisplayOverrides.arr->data=gd::GdArr::from_init(foreign.arena,{V::null(),V::null(),V::null(),V::null(),V::null()})->data;
        if(s==42)items[1]->set_prop(c,SYM_GEN__cooldown_active_44,V::from_bool(false));
        if(s==43 || s==44 || s==61 || s==62)static_cast<Gem*>(items[1])->f_socket=V::from_obj(&socket);
        if(s==54)items[1]->f__cooldown_active=V::from_float(1.0);
        if(s==55)items[1]->f_placed=V::from_float(1.0);
        if(s==56)context->f_show_cooldown_progress=V::from_int(1);
        if(s==57)context->f_show_cooldown_progress=V::from_float(snan());
        if(s==58)items[1]->f__cooldown_active=V::from_float(snan());
        if(s==59)items[1]->f_placed=V::null();
        if(s==60)items[1]->f_placed=V::from_obj(context);
        if(s==63)items[1]->f__cooldown_active=V::from_bool(false);
        hooks.action=[this](gd::SymId m,const V* args,int argc,V& out) {
            if(m!=SYM_GEN_showCooldown_794 && m!=SYM_GEN_queueTooltipUpdate_708)return false;
            trace=mix(trace,m);trace=mix(trace,nesting);
            if(argc && args[0].kind==V::Kind::Obj)trace=mix(trace,id(args[0].obj));
            if(m==SYM_GEN_showCooldown_794){assert(argc==2);trace=mix(trace,hash(args[1]));
                if(armed && !nesting && args[0].obj==items[0]){armed=false;(void)c.math_rng.randf();mutate();}}
            out=V::null();return true;
        };
        socket.action=[this](gd::SymId m,const V*,int,V& out) {
            if(m!=SYM_GEN_getItem_389)return false;
            trace=mix(trace,0xabc0123);
            if(getter_armed){getter_armed=false;const V value=V::from_float(3.25);
                if(scenario==61) {
                    V seed=V::from_int(43);
                    auto* other=static_cast<Context*>(gd::construct_class(c,&META_Gd__gd_core__CoreContext,&seed,1).obj);
                    identities.push_back(other);other->f_show_cooldown_progress=V::from_bool(false);
                    items[1]->f_ctx=V::from_obj(other);
                    items[1]->f_statDisplayOverrides.arr->set_idx(3,value);
                } else if(scenario==62) {
                    items[1]->rt_ctx_=&foreign;
                    items[1]->f_statDisplayOverrides.arr->set_idx(3,value);
                } else if(scenario==43)items[1]->f_statDisplayOverrides.arr->set_idx(3,value);
                else {auto* a=new_display(value);items[1]->set_prop(foreign,SYM_GEN_statDisplayOverrides_33,V::from_arr(a));}}
            out=V::from_obj(items[2]);return true;
        };
    }
    Item* make_item(Character* chr,bool gem) {
        auto* p=static_cast<Item*>(gd::construct_class(c,gem?&META_Gd__gd_core_items__Gems__Gem:&META_Gd__gd_core__CoreItem,nullptr,0).obj);
        identities.push_back(p);p->f_ctx=V::from_obj(context);p->f_character_=V::from_obj(chr);p->f_placed=V::from_bool(true);
        p->f__cooldown_active=V::from_bool(true);p->f__cooldown_blocked_epoch=V::from_int(-1);
        p->f_triggerTime=V::from_float(20.0+identities.size()*0.125);p->f_iterationCooldown=V::from_float(1.5);
        p->f_speedScale=V::from_float(identities.size()%2?-.125:.25);p->f_statDisplayOverrides=V::from_arr(new_display(V::null()));
        track(p->f_gems.arr);track(p->f_timers.arr);return p;
    }
    void track(gd::GdArr* a){arrays.push_back(a);}
    gd::GdArr* new_display(V value){auto* a=gd::GdArr::create(c.arena,5);a->resize(c.arena,5);a->data[3]=value;track(a);return a;}
    uint64_t id(const gd::GdObj* p)const{for(unsigned i=0;i<identities.size();++i)if(identities[i]==p)return i+1;return p?UINT64_MAX:0;}
    uint64_t hash(const V& v,unsigned depth=0)const {
        uint64_t h=mix(1469598103934665603ULL,unsigned(v.kind));
        switch(v.kind) {
        case V::Kind::Int:return mix(h,uint64_t(v.i));case V::Kind::Bool:return mix(h,v.b);
        case V::Kind::Float:return mix(h,std::bit_cast<uint64_t>(v.f));case V::Kind::Obj:return mix(h,id(v.obj));
        case V::Kind::Arr:if(v.arr && depth<2){h=mix(h,v.arr->len);for(unsigned i=0;i<v.arr->len;++i)h=mix(h,hash(v.arr->data[i],depth+1));}return h;
        case V::Kind::Str:if(v.str)for(unsigned i=0;i<v.str->len;++i)h=mix(h,uint8_t(v.str->data[i]));return h;
        default:return h;
        }
    }
    void phase(Character* who) {
        gd::NativeFrameSegmentSnapshot snapshot;const V delta=V::from_float(0.01666666753590107);
#ifdef GD_DISPLAY_NEW
        if(gd_diag_native_frame_proof_phase(who,&snapshot,&delta))return;
#endif
        auto item_tick=[&](Item* item) {
#ifdef GD_DISPLAY_NEW
            gd_diag_native_frame_proof_tick(item,&snapshot,&delta);
#else
            using Tick=void(*)(Item*,gd::NativeFrameSegmentSnapshot&,const V&);
            static auto module=GetModuleHandleW(L"libgdcore.dll");assert(module);
            const auto tick=reinterpret_cast<Tick>(reinterpret_cast<uintptr_t>(module)+GD_OLD_FRAME_RVA);
            tick(item,snapshot,delta);
#endif
        };
        auto gem_tick=[&](Item* item){snapshot.clear();item->fn_physicsTick(&delta,1);};
        cooldown_original_phase(c,who,item_tick,gem_tick);
    }
    void tick(){phase(characters[0]);phase(characters[1]);}
    void mutate() {
        auto* a=items[1]->f_statDisplayOverrides.arr;const V value=V::from_float(1.75);
        switch(scenario) {
        case 1:{V args[]={V::from_int(3),value};items[1]->fn_setStat(args,2);break;}
        case 2:{V alias=items[1]->f_statDisplayOverrides;gd::native_array_set_index(c,alias,V::from_int(3),value);break;}
        case 3:a->set_idx(3,value);break;
        case 4:a->fill(V::null());break;
        case 5:a->fill(value);break;
        case 6:a->resize(c.arena,0);a->resize(c.arena,5);a->set_idx(3,value);break;
        case 7:a->remove_at(3);a->push_back(c.arena,value);break;
        case 8:a->set_idx(1,value);a->invert();break;
        case 9:a->resize(c.arena,3);break;
        case 10:{auto* copy=a->duplicate(c.arena,false);track(copy);copy->set_idx(3,value);items[1]->set_prop(c,SYM_GEN_statDisplayOverrides_33,V::from_arr(copy));break;}
        case 11:items[1]->set_prop(foreign,SYM_GEN_statDisplayOverrides_33,V::from_arr(new_display(value)));break;
        case 12:{auto* p=make_item(characters[0],false);p->f_statDisplayOverrides.arr->set_idx(3,value);grids[0]->f_items.arr->push_back(c.arena,V::from_obj(p));break;}
        case 13:{auto* p=make_item(characters[0],false);p->f_statDisplayOverrides.arr->set_idx(3,value);items[2]->f_gems.arr->push_back(c.arena,V::from_obj(p));break;}
        case 14:{auto* b=gd::GdArr::from_init(c.arena,{V::from_obj(gems[0])});track(b);items[2]->set_prop(c,SYM_GEN_gems_41,V::from_arr(b));gems[0]->f_statDisplayOverrides.arr->set_idx(3,value);break;}
        case 15:{V arr=grids[0]->f_items;gd::call_method(c,arr,gd::SYM_clear,nullptr,0);break;}
        case 16:grids[0]->f_items.arr->remove_at(1);break;
        case 17:{auto* p=make_item(characters[0],false);p->f_statDisplayOverrides.arr->set_idx(3,value);grids[0]->f_items.arr->insert_at(c.arena,1,V::from_obj(p));break;}
        case 18:a->set_idx(3,value);break;
        case 19:items[0]->f_statDisplayOverrides.arr->set_idx(3,value);break;
        case 20:++nesting;tick();--nesting;a->set_idx(3,value);break;
        case 21:{
#ifdef GD_DISPLAY_NEW
            
#endif
            ++nesting;tick();--nesting;items[1]->set_prop(c,SYM_GEN_statDisplayOverrides_33,V::from_arr(new_display(value)));break;}
        case 22:{
#ifdef GD_DISPLAY_NEW
            
#endif
            items[1]->set_prop(foreign,SYM_GEN_statDisplayOverrides_33,V::from_arr(new_display(value)));break;}
        case 23:{
#ifdef GD_DISPLAY_NEW
            
#endif
            a->set_idx(3,value);break;}
        case 30:a->resize(c.arena,5);a->set_idx(3,value);break;
        case 31:items[1]->set_prop(c,SYM_GEN_statDisplayOverrides_33,V::from_arr(nullptr));break;
        case 32:c.bind_battle(123);a->set_idx(3,value);break;
        case 33:c.native_timer_watch.version+=1;a->set_idx(3,value);break;
        case 34:c.native_timer_watch.depth=1;a->set_idx(3,value);break;
        case 35:c.native_timer_watch.usable=false;a->set_idx(3,value);break;
        case 36:c.native_timer_watch.closed_world=false;a->set_idx(3,value);break;
        case 37:c.native_timer_watch.enabled=false;a->set_idx(3,value);break;
        case 38:c.native_timer_watch.version=UINT64_MAX;a->set_idx(3,value);break;
        case 42:{V on=V::from_bool(true);items[1]->fn_setCooldownActive(&on,1);a->set_idx(3,value);break;}
        case 45:{auto* p=make_item(characters[0],false);p->f_statDisplayOverrides.arr->set_idx(3,value);auto* b=gd::GdArr::from_init(c.arena,{V::from_obj(p)});track(b);grids[0]->set_prop(c,SYM_GEN_items_1092,V::from_arr(b));break;}
        case 46:c.native_resolved_collect=false;a->set_idx(3,value);break;
        case 47:{V args[]={V::from_int(3),V::from_float(snan())};items[1]->fn_setStat(args,2);break;}
        case 48:items[1]->native_call_row_=nullptr;break;
        case 49:items[1]->native_call_row_=context->native_call_row_;break;
        case 50:items[1]->rt_ctx_=&foreign;break;
        case 51:{
            V seed=V::from_int(43);
            auto* other=static_cast<Context*>(gd::construct_class(c,&META_Gd__gd_core__CoreContext,&seed,1).obj);
            identities.push_back(other);other->f_show_cooldown_progress=V::from_bool(false);
            other->f_timer_pass_epoch=V::from_int(17);items[1]->f_ctx=V::from_obj(other);break;
        }
        case 52:c.native_resolved_dispatch=false;break;
        case 53:c.native_resolved_audit=false;break;
        case 64:{static const gd::GdClassMeta unknown{65031,"DisplayScopeUnknownRegistration"};gd::register_class(&unknown);a->set_idx(3,value);break;}
        default:break;
        }
    }
    uint64_t state()const {
        uint64_t h=trace;
        for(auto* o:identities)if(auto* item=dynamic_cast<Item*>(o)) {
            h=mix(h,id(item));for(const V* v:{&item->f_ctx,&item->f_placed,&item->f_triggerTime,&item->f_statDisplayOverrides,&item->f_gems,&item->f__cooldown_active,&item->f__cooldown_blocked_epoch})h=mix(h,hash(*v));
            h=mix(h,item->gid_);
        }
        for(auto* a:arrays){h=mix(h,a->len);h=mix(h,a->cap);for(unsigned i=0;i<a->len;++i)h=mix(h,hash(a->data[i]));}
        for(auto* g:grids)h=mix(h,hash(g->f_items));
        h=mix(h,c.next_gid);h=mix(h,c.gid_epoch);h=mix(h,c.math_rng.pcg.state);h=mix(h,c.math_rng.pcg.inc);
        for(auto n:c.native_resolved_counts)h=mix(h,n);for(auto n:c.native_event_counts)h=mix(h,n);
        h=mix(h,std::fetestexcept(FE_ALL_EXCEPT));h=mix(h,_mm_getcsr()&0x3f);return h;
    }
};
static uint64_t run(unsigned s,unsigned config,unsigned mode,unsigned daz) {
    Fixture f(s,config);const int rounds[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};
    std::fesetround(rounds[mode]);_mm_setcsr((_mm_getcsr()&~0x8040u)|((daz&1)?0x40u:0)|((daz&2)?0x8000u:0));

    std::array<uint64_t,21> counters{};
    for(unsigned i=0;i<17;++i)counters[i]=gd_diag_native_frame_segment_stat(i);
    for(unsigned i=0;i<4;++i)counters[17+i]=gd_diag_native_type_constructor_stat(i);
    std::feclearexcept(FE_ALL_EXCEPT);_mm_setcsr(_mm_getcsr()&~0x3fu);
    f.tick();f.tick();if(s==43 || s==44 || s==61 || s==62)assert(!f.getter_armed);auto result=f.state();
    for(unsigned i=0;i<17;++i)result=mix(result,gd_diag_native_frame_segment_stat(i)-counters[i]);
    for(unsigned i=0;i<4;++i)result=mix(result,gd_diag_native_type_constructor_stat(i)-counters[17+i]);

    return result;
}
int main(int argc,char**) {
    gd_init_all_classes();const auto saved_mxcsr=_mm_getcsr();const auto saved_round=std::fegetround();std::vector<uint64_t> hashes;
    if(argc>1)hashes.push_back(run(64,1,0,0));
    else for(unsigned s=0;s<64;++s)for(unsigned config=0;config<3;++config)for(unsigned mode=0;mode<4;++mode)for(unsigned daz=0;daz<4;++daz)
        hashes.push_back(run(s,config,mode,daz));
    std::fesetround(saved_round);_mm_setcsr(saved_mxcsr);
    std::cout<<"{\"cases\":"<<hashes.size()<<",\"layout\":{\"GdVal\":"<<sizeof(V)<<",\"GdArr\":"<<sizeof(gd::GdArr)
        <<",\"CoreItem\":"<<sizeof(Item)<<",\"BattleCtx\":"<<sizeof(gd::BattleCtx)<<",\"snapshot\":"<<sizeof(gd::NativeFrameSegmentSnapshot)<<"},\"counts\":[";
    for(unsigned i=0;i<8;++i){if(i)std::cout<<',';
#ifdef GD_DISPLAY_NEW
        std::cout<<0;
#else
        std::cout<<0;
#endif
    }
    std::cout<<"],\"hashes\":[";for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<hashes[i]<<std::dec<<'"';}std::cout<<"]}\n";
}
