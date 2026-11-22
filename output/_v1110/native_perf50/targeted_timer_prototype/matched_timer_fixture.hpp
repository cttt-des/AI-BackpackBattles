#include "reference_targeted_timers.hpp"
#include "native_inline_dispatch.hpp"
#include "native_array_index.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCombat.hpp"
#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"
#include "gen/hdrs/Gd__gd_core__CoreTimer.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "targeted_timer_fields.hpp"
#ifdef GD_TIMER_NEW
#include "native_targeted_timers.hpp"
#endif
#include <algorithm>
#include <bit>
#include <cassert>
#include <cfenv>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
using V=gd::GdVal;using Item=Gd__gd_core__CoreItem;using Character=Gd__gd_core__CoreCharacter;
using Context=Gd__gd_core__CoreContext;using Combat=Gd__gd_core__CoreCombat;using Grid=Gd__gd_core__CoreGrid;using Timer=Gd__gd_core__CoreTimer;
static uint64_t mix(uint64_t h,uint64_t x){return(h^x)*1099511628211ULL;}
static std::vector<const gd::GdObj*> identities;
static uint64_t hash(const V& v){uint64_t h=mix(1469598103934665603ULL,unsigned(v.kind));switch(v.kind){
case V::Kind::Null:return h;case V::Kind::Bool:return mix(h,v.b);case V::Kind::Int:return mix(h,uint64_t(v.i));case V::Kind::Float:return mix(h,std::bit_cast<uint64_t>(v.f));
case V::Kind::Vec2:return mix(mix(h,std::bit_cast<uint64_t>(v.v2.x)),std::bit_cast<uint64_t>(v.v2.y));
case V::Kind::Obj:if(v.obj){auto it=std::find(identities.begin(),identities.end(),v.obj);h=mix(h,v.obj->meta()->id);h=mix(h,it==identities.end()?v.obj->gid_:10000+size_t(it-identities.begin()));}return h;
case V::Kind::Arr:if(v.arr){h=mix(h,v.arr->len);for(unsigned i=0;i<v.arr->len;++i)h=mix(h,hash(v.arr->data[i]));}return h;
case V::Kind::Dict:if(v.dict){h=mix(h,v.dict->len);for(unsigned i=0;i<v.dict->len;++i){h=mix(h,hash(v.dict->entries[i].key));h=mix(h,hash(v.dict->entries[i].val));}}return h;
case V::Kind::Str:if(v.str){h=mix(h,v.str->len);for(unsigned i=0;i<v.str->len;++i)h=mix(h,(unsigned char)v.str->data[i]);}return h;
case V::Kind::ClassRef:return mix(h,v.cls?v.cls->id:0);default:return h;}}
extern "C" uint64_t gd_diag_native_variant_stat(unsigned);
extern "C" uint64_t gd_diag_native_property_stat(unsigned);
extern "C" uint64_t gd_diag_native_hot_slot_stat(unsigned);
extern "C" uint64_t gd_diag_native_dispatch_chain_stat(unsigned);
extern "C" uint64_t gd_diag_native_type_constructor_stat(unsigned);
static const std::pair<uint64_t(*)(unsigned),unsigned> counters[]={{gd_diag_native_variant_stat,10},{gd_diag_native_property_stat,2},{gd_diag_native_hot_slot_stat,2},{gd_diag_native_dispatch_chain_stat,4},{gd_diag_native_type_constructor_stat,4}};
static const gd::GdClassMeta mock_meta{65002,"TargetedTimerCallback"};
struct Callback:gd::GdObj {
    std::function<void()> action;unsigned calls=0;bool busy=false;
    explicit Callback(gd::BattleCtx* c):GdObj(c){}
    const gd::GdClassMeta* meta()const override{return &mock_meta;}
    void fire(){++calls;if(action&&!busy){busy=true;action();busy=false;}}
    bool call_method(gd::BattleCtx&,gd::SymId,const V*,int,V& out)override{fire();out=V::null();return true;}
    bool get_prop(gd::SymId,V& out)const override{const_cast<Callback*>(this)->fire();out=V::from_int(1);return true;}
    bool set_prop(gd::BattleCtx&,gd::SymId,const V&)override{fire();return true;}
    bool has_own_method(gd::SymId)const override{const_cast<Callback*>(this)->fire();return true;}
};
struct Fixture {
    gd::BattleCtx c{65536};Context* ctx;Character* chr;Combat* combat;Grid* grid;
    std::vector<Item*> items,gems;std::vector<Timer*> timers;std::vector<gd::GdArr*> arrays;
    Callback callback{&c};std::vector<uint64_t> trace;
    gd::GdArr external;gd::BattleCtx foreign{4096};
    explicit Fixture(unsigned n=8){setup(n);}
    void setup(unsigned n){
        items.clear();gems.clear();timers.clear();arrays.clear();trace.clear();callback.action={};callback.calls=0;callback.busy=false;
        identities.clear();c.native_event_kernel=true;c.native_event_audit=true;c.native_resolved_dispatch=true;c.native_resolved_audit=true;c.native_inline_timer_headers=true;
        V seed=V::from_int(42);ctx=static_cast<Context*>(gd::construct_class(c,&META_Gd__gd_core__CoreContext,&seed,1).obj);remember(ctx);
        V a[]={V::from_obj(ctx),V::from_int(0)};chr=static_cast<Character*>(gd::construct_class(c,&META_Gd__gd_core__CoreCharacter,a,2).obj);remember(chr);
        V x=V::from_obj(ctx);combat=static_cast<Combat*>(gd::construct_class(c,&META_Gd__gd_core__CoreCombat,&x,1).obj);remember(combat);
        grid=static_cast<Grid*>(chr->f_inventory.obj);remember(grid);remember(&callback);
        ctx->f_player=V::from_obj(chr);ctx->f_timer_pass_epoch=V::from_int(3);
        chr->f__tick_timer_active=chr->f__rage_active=chr->f__invul_active=chr->f__autoRage_active=V::from_bool(false);
        for(unsigned i=0;i<n;++i){auto* item=make_item();items.push_back(item);grid->f_items.arr->push_back(c.arena,V::from_obj(item));for(unsigned j=0;j<2;++j){auto* gem=make_item();gems.push_back(gem);item->f_gems.arr->push_back(c.arena,V::from_obj(gem));}}
        arrays.push_back(grid->f_items.arr);
    }
    void remember(gd::GdObj* p){identities.push_back(p);}
    Item* make_item(){auto* p=static_cast<Item*>(gd::construct_class(c,&META_Gd__gd_core__CoreItem,nullptr,0).obj);remember(p);p->f_ctx=V::from_obj(ctx);p->f_character_=V::from_obj(chr);arrays.push_back(p->f_timers.arr);arrays.push_back(p->f_gems.arr);return p;}
    Timer* make_timer(Item* owner,bool stopped=true){V a[]={V::from_obj(ctx),V::from_obj(owner),V::from_str(gd::make_static_str("initial"))};auto* t=static_cast<Timer*>(gd::construct_class(c,&META_Gd__gd_core__CoreTimer,a,3).obj);remember(t);timers.push_back(t);t->f__stopped=V::from_bool(stopped);t->f__left=V::from_float(-.01);t->f__first_pass=V::from_int(0);t->f_one_shot=V::from_bool(true);t->f_multi=V::from_bool(false);return t;}
    Timer* add(Item* owner,bool stopped=true){auto* t=make_timer(owner,stopped);owner->f_timers.arr->push_back(c.arena,V::from_obj(t));return t;}
    void enable(){
#ifdef GD_TIMER_NEW
        c.native_timer_watch.enabled=true;
#endif
    }
    void tick(V delta){V a[]={V::from_obj(chr),delta};auto r=invoke_timer_local(*combat,a,2);trace.push_back(hash(r));trace.push_back(state());}
    uint64_t state(){uint64_t h=1469598103934665603ULL;auto consume=[&](const V& v){h=mix(h,hash(v));};
        timer_visit(*ctx,consume);timer_visit(*chr,consume);timer_visit(*combat,consume);timer_visit(*grid,consume);
        for(auto* p:items)timer_visit(*p,consume);for(auto* p:gems)timer_visit(*p,consume);for(auto* p:timers)timer_visit(*p,consume);
        for(auto* a:arrays)consume(V::from_arr(a));h=mix(h,callback.calls);h=mix(h,c.next_gid);h=mix(h,c.math_rng.pcg.state);h=mix(h,c.math_rng.pcg.inc);
        for(auto n:c.native_resolved_counts)h=mix(h,n);for(auto n:c.native_event_counts)h=mix(h,n);return h;
    }
    void mutation(unsigned action,bool gem_stage){
        auto* list=grid->f_items.arr;auto* sockets=items[0]->f_gems.arr;
        switch(action){
        case 0:break;
        case 1:add(items[3],false);break;
        case 2:items[3]->f_timers.arr->resize(c.arena,0);break;
        case 3:items[3]->f_timers=V::from_arr(gd::GdArr::from_init(c.arena,{V::from_obj(make_timer(items[3],false))}));break;
        case 4:list->remove_at(0);break;
        case 5:list->remove_at(2);break;
        case 6:list->resize(c.arena,0);break;
        case 7:list->set_idx(1,V::from_obj(items.back()));break;
        case 8:{auto* a=gd::GdArr::from_init(c.arena,{V::from_obj(items.back())});arrays.push_back(a);grid->set_prop(c,SYM_GEN_items_1092,V::from_arr(a));break;}
        case 9:{auto* a=gd::GdArr::from_init(c.arena,{V::from_obj(gems.back())});arrays.push_back(a);items[0]->set_prop(c,SYM_GEN_gems_41,V::from_arr(a));add(gems.back(),false);break;}
        case 10:sockets->remove_at(0);break;
        case 11:sockets->resize(c.arena,0);break;
        case 12:sockets->set_idx(1,V::from_obj(gems.back()));add(gems.back(),false);break;
        case 13:items[0]->f_gems=V::from_arr(gd::GdArr::from_init(c.arena,{V::from_obj(gems.back())}));break;
        case 14:add(gem_stage?gems[1]:items[0],false);break;
        case 15:tick(V::from_float(.005));break;
        case 16:list->invert();break;
        case 17:list->push_back(c.arena,V::from_obj(items[0]));break;
        case 18:sockets->push_back(c.arena,V::from_obj(gems.back()));add(gems.back(),false);break;
        case 19:items[0]->f_timers.arr->resize(c.arena,0);break;
        }
    }
};
static V delta_value(unsigned n){switch(n%6){case 0:return V::from_float(.05);case 1:return V::from_float(-0.0);case 2:return V::from_int(1);case 3:return V::from_float(std::bit_cast<double>(UINT64_C(0x7ff8000000001234)));case 4:return V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234)));default:return V::null();}}
static std::pair<uint64_t,uint64_t> run(unsigned family,unsigned scenario,unsigned config,int rounding){
    assert(std::fesetround(FE_TONEAREST)==0);Fixture f(family==0?(scenario%5==0?0:scenario%5==1?1:scenario%5==2?4:scenario%5==3?16:48):8);
    f.c.native_resolved_dispatch=config!=0;f.c.native_resolved_collect=config>=2;f.c.native_resolved_audit=config!=3;f.c.native_event_kernel=config!=0;f.c.native_event_audit=config>=2;
    if(family==0){for(unsigned i=0;i<f.items.size();++i)if(i%(scenario/5+1)==0)f.add(f.items[i]);for(unsigned i=0;i<f.gems.size();++i)if(i%7==0)f.add(f.gems[i]);}
    else if(family==2||family==3){for(unsigned i=3;i<f.items.size();i+=3)f.add(f.items[i],false);auto* t=f.add(family==3?f.gems[0]:f.items[0],false);t->f__owner=V::from_obj(&f.callback);t->f_callback_method=V::from_str(gd::make_static_str("mutate"));f.callback.action=[&]{f.mutation(scenario,family==3);};}
    else if(family==4){auto* target=scenario%4==0?f.items[0]:scenario%4==1?f.items[3]:scenario%4==2?f.gems[0]:f.gems[7];auto* t=f.add(scenario%2?f.gems[0]:f.items[0],false);t->f__owner=V::from_obj(target);t->f_callback_method=V::from_str(gd::make_static_str("newItemTimer"));}
    else {for(unsigned i=0;i<f.items.size();i+=3)f.add(f.items[i]);}
    f.enable();std::vector<uint64_t> before;for(auto[fn,n]:counters)for(unsigned i=0;i<n;++i)before.push_back(fn(i));
    assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);
    f.tick(family==0?delta_value(scenario):V::from_float(.05));
    if(family==1){auto* item=f.items[3];auto* a=item->f_timers.arr;switch(scenario){
        case 0:f.add(f.items[1],false);break;case 1:a->resize(f.c.arena,0);break;case 2:a->pop_back();break;case 3:a->pop_front();break;case 4:a->pop_at(-1);break;
        case 5:a->insert_at(f.c.arena,0,V::from_obj(f.make_timer(item,false)));break;
        case 6:{auto* b=gd::GdArr::from_init(f.c.arena,{V::from_obj(f.make_timer(item,false))});a->append_array(f.c.arena,b);break;}
        case 7:a->fill(V::from_obj(f.make_timer(item,false)));break;case 8:a->invert();break;case 9:a->set_idx(0,V::from_obj(f.make_timer(item,false)));break;
        case 10:{V recv=V::from_arr(a);gd::native_array_set_index(f.c,recv,V::from_int(0),V::from_obj(f.make_timer(item,false)));break;}
        case 11:{V recv=V::from_arr(a);gd::call_method(f.c,recv,gd::SYM_clear,nullptr,0);break;}
        case 12:gd::shuffle_array(f.c,a);break;case 13:item->set_prop(f.c,SYM_GEN_timers_67,V::from_arr(gd::GdArr::create(f.c.arena)));break;
        case 14:item->set_prop(f.c,SYM_GEN_gems_41,V::from_arr(gd::GdArr::create(f.c.arena)));break;
        case 15:f.grid->set_prop(f.c,SYM_GEN_items_1092,V::from_arr(gd::GdArr::from_init(f.c.arena,{V::from_obj(item)})));break;
        case 16:f.callback.action=[&]{f.mutation(1,false);};{V recv=V::from_obj(&f.callback);gd::get_prop(f.c,recv,SYM_GEN_name_7);}break;
        case 17:f.callback.action=[&]{f.mutation(1,false);};{gd::GdFuncRef r;r.instance=&f.callback;r.method=SYM_GEN_tick_1516;assert(r.is_valid());}break;
        case 18:{
#ifdef GD_TIMER_NEW
            gd::NativeTimerMutation mutation(f.grid->f_items.arr->timer_watch);
#endif
            f.tick(V::from_float(.005));break;}
        case 19:f.grid->f_items.arr->remove_at(1);break;
        }}
    if(family==5){switch(scenario){case 0:f.chr->f_playerId=V::from_int(3);break;case 1:f.chr->f_playerId=V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234)));break;case 2:f.chr->f_playerId=V::null();break;case 3:f.chr->f_playerId=V::from_int(1);break;case 4:f.grid->f_items.arr->push_back(f.c.arena,V::from_obj(f.items[0]));break;case 5:f.items[0]->f_gems.arr->push_back(f.c.arena,V::from_obj(f.gems[0]));break;}}
    if(family==6){switch(scenario){
        case 0:f.external=*f.grid->f_items.arr;f.grid->set_prop(f.c,SYM_GEN_items_1092,V::from_arr(&f.external));break;
        case 1:{auto* a=gd::GdArr::create(f.c.arena,0);a->len=a->cap=1;a->data=f.foreign.arena.alloc_array<V>(1);a->data[0]=V::from_obj(f.items[0]);f.grid->set_prop(f.c,SYM_GEN_items_1092,V::from_arr(a));break;}
        case 2:
#ifdef GD_TIMER_NEW
            f.grid->f_items.arr->timer_watch=&f.foreign.native_timer_watch;
#endif
            break;
        case 3:f.items[1]->set_prop(f.c,SYM_GEN_timers_67,f.items[0]->f_timers);break;
        case 4:f.items[1]->set_prop(f.c,SYM_GEN_gems_41,f.items[0]->f_gems);break;
        case 5:gd::godot_sort_custom_items(f.c,f.grid->f_items.arr);break;
        case 6:{f.callback.action=[&]{f.add(f.items[1],false);};V a[]={V::from_obj(&f.callback),V::from_str(gd::make_static_str("sort"))};gd::native_inline_call(f.c,f.grid->f_items,gd::SYM_sort_custom,a,2);break;}
        case 7:f.c.reset_for_battle(42);f.setup(8);f.c.native_resolved_dispatch=config!=0;f.c.native_resolved_collect=config>=2;f.c.native_resolved_audit=config!=3;f.enable();f.add(f.items[0],false);break;
        case 8:f.items[0]->f_timers.arr->erase_val(f.items[0]->f_timers.arr->data[0]);break;
        case 9:f.grid->f_items.arr->resize(f.c.arena,2);break;
        case 10:f.items[0]->f_gems.arr->fill(V::null());break;
        case 11:f.items[0]->f_gems.arr->invert();break;
        case 12:{V a[]={V::from_int(1),V::from_obj(f.gems.back())};f.items[0]->fn_setGem(a,2);break;}
        case 13:f.items[0]->f_gems.arr->pop_at(-1);break;
        case 14:{auto* a=gd::GdArr::from_init(f.c.arena,{V::from_obj(f.items[0])});f.grid->f_items.arr->append_array(f.c.arena,a);break;}
        case 15:{auto* grid=static_cast<Grid*>(gd::construct_class(f.c,&META_Gd__gd_core__CoreGrid,nullptr,0).obj);grid->f_items.arr->push_back(f.c.arena,V::from_obj(f.items[3]));f.chr->set_prop(f.c,SYM_GEN_inventory_5,V::from_obj(grid));break;}
        case 16:f.items[0]->f_timers.arr->insert_at(f.c.arena,0,V::from_obj(f.make_timer(f.items[0],false)));break;
        case 17:f.items[0]->f_timers.arr->pop_front();break;
        case 18:f.items[0]->f_timers.arr->pop_back();break;
        case 19:f.callback.action=[&]{f.mutation(3,false);};{auto v=V::from_obj(&f.callback);gd::set_prop(f.c,v,SYM_GEN_timers_67,V::null());}break;
    }}
    f.tick(family==0?delta_value(scenario+1):V::from_float(.01));f.tick(V::from_float(.005));const auto flags=std::fetestexcept(FE_ALL_EXCEPT);
    uint64_t h=mix(f.state(),flags);for(auto n:f.trace)h=mix(h,n);uint64_t legacy=1469598103934665603ULL;unsigned j=0;
    for(auto[fn,n]:counters)for(unsigned i=0;i<n;++i)legacy=mix(legacy,fn(i)-before[j++]);return{h,legacy};
}
