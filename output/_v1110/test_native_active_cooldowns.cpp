#include "native_inline_dispatch.hpp"
#include "native_array_index.hpp"
#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCombat.hpp"
#include "cooldown_original_phase.hpp"
#ifdef GD_ACTIVE_NEW
#include "native_active_cooldowns.hpp"
#endif
#include <bit>
#include <cassert>
#include <cfenv>
#include <functional>
#include <iostream>
#include <vector>
using V=gd::GdVal;using Item=Gd__gd_core__CoreItem;using Character=Gd__gd_core__CoreCharacter;
using Context=Gd__gd_core__CoreContext;using Grid=Gd__gd_core__CoreGrid;
static uint64_t mix(uint64_t h,uint64_t n){return(h^n)*1099511628211ULL;}
extern "C" uint64_t gd_diag_native_variant_stat(unsigned);
extern "C" uint64_t gd_diag_native_property_stat(unsigned);
extern "C" uint64_t gd_diag_native_hot_slot_stat(unsigned);
extern "C" uint64_t gd_diag_native_dispatch_chain_stat(unsigned);
extern "C" uint64_t gd_diag_native_type_constructor_stat(unsigned);
static const std::pair<uint64_t(*)(unsigned),unsigned> counters[]={{gd_diag_native_variant_stat,10},{gd_diag_native_property_stat,2},{gd_diag_native_hot_slot_stat,2},{gd_diag_native_dispatch_chain_stat,4},{gd_diag_native_type_constructor_stat,4}};
static const gd::GdClassMeta unknown_meta{65009,"CooldownForeignImplementation"};
struct UnknownItem:Item {using Item::Item;const gd::GdClassMeta* meta()const override{return &unknown_meta;}};
struct Fixture {
    gd::BattleCtx c{65536},foreign{8192};Context* ctx;Character* chr;Character* alternate;Grid* grid;
    std::vector<Item*> items,gems;std::vector<gd::GdObj*> objects;std::vector<gd::GdArr*> arrays;
    std::vector<uint64_t> trace;gd::GdArr external;std::function<void()> action;
    Item* trigger=nullptr;bool armed=false;unsigned nesting=0;uint64_t progressed=0;
    explicit Fixture(unsigned n,unsigned density){setup(n,density);}
    void setup(unsigned n,unsigned density) {
        items.clear();gems.clear();objects.clear();arrays.clear();trace.clear();action={};trigger=nullptr;armed=false;nesting=0;progressed=0;
        c.native_event_kernel=true;c.native_event_audit=true;c.native_resolved_dispatch=true;c.native_resolved_audit=true;c.native_inline_timer_headers=true;
        c.native_timer_watch.enabled=true;c.native_timer_watch.closed_world=true;
        V seed=V::from_int(42);ctx=static_cast<Context*>(gd::construct_class(c,&META_Gd__gd_core__CoreContext,&seed,1).obj);remember(ctx);
        V args[]={V::from_obj(ctx),V::from_int(0)};chr=static_cast<Character*>(gd::construct_class(c,&META_Gd__gd_core__CoreCharacter,args,2).obj);remember(chr);
        alternate=static_cast<Character*>(gd::construct_class(c,&META_Gd__gd_core__CoreCharacter,args,2).obj);remember(alternate);
        grid=static_cast<Grid*>(chr->f_inventory.obj);remember(grid);remember(static_cast<Grid*>(alternate->f_inventory.obj));
        ctx->f_timer_pass_epoch=V::from_int(17);ctx->f_in_item_physics_pass=V::from_bool(true);ctx->f_in_physics_timer_pass=V::from_bool(false);
        track(grid->f_items.arr);track(static_cast<Grid*>(alternate->f_inventory.obj)->f_items.arr);
        for(unsigned i=0;i<n;++i) {
            auto* item=make_item();items.push_back(item);grid->f_items.arr->push_back(c.arena,V::from_obj(item));
            raw(item,V::from_bool(density==2 || (density==0?i==0:density==1?i%2==0:false)));
            for(unsigned j=0;j<3;++j){auto* gem=make_item();gems.push_back(gem);item->f_gems.arr->push_back(c.arena,V::from_obj(gem));raw(gem,V::from_bool(density==2 || (density==3?j==1:density==1?j==2:false)));}
        }
        if(n){raw(items[0],V::from_bool(true));raw(gems[0],V::from_bool(true));}
        for(unsigned i=0;i<3;++i){auto* item=make_item();raw(item,V::from_bool(i!=1));static_cast<Grid*>(alternate->f_inventory.obj)->f_items.arr->push_back(c.arena,V::from_obj(item));}
    }
    void remember(gd::GdObj* p){objects.push_back(p);}
    void track(gd::GdArr* p){arrays.push_back(p);}
    Item* make_item(){auto* p=static_cast<Item*>(gd::construct_class(c,&META_Gd__gd_core__CoreItem,nullptr,0).obj);remember(p);p->f_ctx=V::from_obj(ctx);p->f_character_=V::from_obj(chr);track(p->f_gems.arr);track(p->f_timers.arr);return p;}
    gd::GdArr* list(std::initializer_list<V> values){auto* a=gd::GdArr::from_init(c.arena,values);track(a);return a;}
    void raw(Item* item,V value,bool wrong_context=false){item->set_prop(wrong_context?foreign:c,SYM_GEN__cooldown_active_44,value);}
    void set(Item* item,bool value){const auto version=c.native_timer_watch.version;V v=V::from_bool(value);item->fn_setCooldownActive(&v,1);assert(c.native_timer_watch.version==version);}
    uint64_t identity(const gd::GdObj* p)const{for(unsigned i=0;i<objects.size();++i)if(objects[i]==p)return i+1;return p?UINT64_MAX:0;}
    uint64_t hash(const V& v)const {
        uint64_t h=mix(1469598103934665603ULL,unsigned(v.kind));
        switch(v.kind){case V::Kind::Null:return h;case V::Kind::Bool:return mix(h,v.b);case V::Kind::Int:return mix(h,uint64_t(v.i));case V::Kind::Float:return mix(h,std::bit_cast<uint64_t>(v.f));case V::Kind::Obj:return mix(h,identity(v.obj));case V::Kind::Arr:{uint64_t id=0;for(unsigned i=0;i<arrays.size();++i)if(arrays[i]==v.arr){id=i+1;break;}return mix(h,id);}default:return h;}
    }
    void visit(Item* item,bool gem) {
        trace.push_back(mix(identity(item),gem));
        const bool blocked=item->f__cooldown_blocked_epoch.kind==V::Kind::Int && item->f__cooldown_blocked_epoch.i>=0 &&
            item->f__cooldown_blocked_epoch.i==ctx->f_timer_pass_epoch.i;
        if(!blocked)++progressed;
        if(armed && item==trigger && !nesting){armed=false;if(action)action();}
    }
    void tick(Character* who=nullptr) {
        if(!who)who=chr;trace.push_back(mix(0xaabbccdd,identity(who)));
        auto item_tick=[&](Item* p){visit(p,false);};auto gem_tick=[&](Item* p){visit(p,true);};
#ifdef GD_ACTIVE_NEW
        if(!gd::active_cooldown_visit(c,who,item_tick,gem_tick))
#endif
            cooldown_original_phase(c,who,item_tick,gem_tick);
        trace.push_back(0xddeeff00);
    }
    void nested(Character* who=nullptr){++nesting;tick(who);--nesting;}
    uint64_t state()const {
        uint64_t h=mix(1469598103934665603ULL,progressed);
        for(auto* object:objects) {
            h=mix(h,identity(object));h=mix(h,object->gid_);
            if(auto* item=dynamic_cast<Item*>(object))for(const V* v:{&item->f__cooldown_active,&item->f__cooldown_changed_epoch,&item->f__cooldown_blocked_epoch,&item->f_gems,&item->f_triggerTime})h=mix(h,hash(*v));
            if(auto* character=dynamic_cast<Character*>(object)){h=mix(h,hash(character->f_inventory));h=mix(h,hash(character->f_playerId));}
            if(auto* g=dynamic_cast<Grid*>(object))h=mix(h,hash(g->f_items));
        }
        for(auto* a:arrays){h=mix(h,a->len);h=mix(h,a->cap);for(unsigned i=0;i<a->len;++i)h=mix(h,hash(a->data[i]));}
        h=mix(h,hash(ctx->f_timer_pass_epoch));h=mix(h,hash(ctx->f_in_item_physics_pass));
        h=mix(h,c.next_gid);h=mix(h,c.math_rng.pcg.state);h=mix(h,c.math_rng.pcg.inc);
        for(auto x:c.native_event_counts)h=mix(h,x);for(auto x:c.native_resolved_counts)h=mix(h,x);
        return h;
    }
    void mutate(unsigned action_number,bool gem_stage) {
        auto* a=grid->f_items.arr;auto* b=items[0]->f_gems.arr;
        switch(action_number) {
        case 0:break;
        case 1:set(items[3],true);break;
        case 2:set(items[3],false);break;
        case 3:set(items[3],false);set(items[3],true);break;
        case 4:raw(items[3],V::from_bool(true));break;
        case 5:raw(items[3],V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234))));break;
        case 6:raw(items[3],V::from_bool(false));break;
        case 7:a->remove_at(0);break;
        case 8:a->remove_at(3);break;
        case 9:a->resize(c.arena,0);break;
        case 10:a->set_idx(0,V::from_obj(items.back()));break;
        case 11:a->set_idx(3,V::from_obj(items.back()));break;
        case 12:a->invert();break;
        case 13:a->push_back(c.arena,V::from_obj(items[0]));break;
        case 14:a->append_array(c.arena,list({V::from_obj(items[0]),V::from_obj(items[3])}));break;
        case 15:gd::call_method(c,V::from_arr(a),gd::SYM_clear,nullptr,0);break;
        case 16:a->pop_front();break;
        case 17:case 18:items[0]->set_prop(c,SYM_GEN_gems_41,V::from_arr(list({V::from_obj(gems.back()),V::from_obj(gems[0])})));break;
        case 19:b->resize(c.arena,0);break;
        case 20:b->remove_at(0);break;
        case 21:b->set_idx(1,V::from_obj(gems.back()));raw(gems.back(),V::from_bool(true));break;
        case 22:b->push_back(c.arena,V::from_obj(gems.back()));break;
        case 23:b->fill(V::null());break;
        case 24:b->invert();break;
        case 25:grid->set_prop(c,SYM_GEN_items_1092,V::from_arr(list({V::from_obj(items.back()),V::from_obj(items[0])})));break;
        case 26:chr->set_prop(c,SYM_GEN_inventory_5,alternate->f_inventory);break;
        case 27:set(items[3],true);nested();break;
        case 28:nested(alternate);break;
        case 29:nested();set(gems[2],true);break;
        case 30:{gd::NativeTimerMutation mutation(a->timer_watch);nested();break;}
        case 31:raw(items[3],V::from_bool(true),true);break;
        case 32:set(gems[2],true);break;
        case 33:set(gems[2],false);set(gems[2],true);break;
        case 34:items[1]->set_prop(c,SYM_GEN_gems_41,items[0]->f_gems);break;
        case 35:gd::shuffle_array(c,a);break;
        case 36:a->insert_at(c.arena,1,V::from_obj(items.back()));break;
        case 37:b->insert_at(c.arena,1,V::from_obj(gems.back()));break;
        case 38:{V recv=V::from_arr(a);gd::native_array_set_index(c,recv,V::from_int(3),V::from_obj(items.back()));break;}
        case 39:raw(gem_stage?gems[0]:items[0],V::from_bool(false));break;
        }
    }
};
static std::pair<uint64_t,uint64_t> run(unsigned family,unsigned scenario,unsigned config,int rounding) {
    std::fesetround(rounding);std::feclearexcept(FE_ALL_EXCEPT);
    const unsigned n=family==0?std::array<unsigned,4>{0,1,8,33}[scenario]:8;
    Fixture f(n,config);f.c.native_resolved_collect=config>=2;
    std::vector<uint64_t> before;for(auto [fn,count]:counters)for(unsigned i=0;i<count;++i)before.push_back(fn(i));
    f.tick();
    if(family==1) {
        const bool gem=scenario>=40;const unsigned operation=scenario%40;
        if(operation==6)f.raw(f.items[3],V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234))));
        f.trigger=gem?f.gems[0]:f.items[0];f.armed=true;f.action=[&]{f.mutate(operation,gem);};
    }
    if(family==2) {
        auto* a=f.grid->f_items.arr;auto* b=f.items[0]->f_gems.arr;
        switch(scenario) {
        case 0:f.raw(f.items[3],V::from_bool(true));break;
        case 1:f.set(f.items[3],true);break;
        case 2:f.raw(f.items[3],V::from_int(1));break;
        case 3:f.raw(f.items[3],V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234))));break;
        case 4:f.raw(f.items[3],V::null());break;
        case 5:f.raw(f.items[3],V::from_str(gd::make_static_str("active")));break;
        case 6:f.chr->f_playerId=V::from_int(1);break;
        case 7:f.chr->f_playerId=V::from_int(-1);break;
        case 8:f.chr->f_playerId=V::from_int(2);break;
        case 9:f.chr->f_playerId=V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234)));break;
        case 10:f.chr->f_playerId=V::null();break;
        case 11:f.external=*a;f.grid->set_prop(f.c,SYM_GEN_items_1092,V::from_arr(&f.external));f.track(&f.external);break;
        case 12:{auto* x=gd::GdArr::from_init(f.foreign.arena,{V::from_obj(f.gems[0])});f.track(x);f.items[0]->set_prop(f.c,SYM_GEN_gems_41,V::from_arr(x));break;}
        case 13:{auto* x=static_cast<Item*>(gd::construct_class(f.foreign,&META_Gd__gd_core__CoreItem,nullptr,0).obj);f.remember(x);f.track(x->f_gems.arr);f.raw(x,V::from_bool(true));a->set_idx(3,V::from_obj(x));break;}
        case 14:{auto* x=f.c.arena.make<UnknownItem>(&f.c);x->init_fields(f.c);f.remember(x);f.track(x->f_gems.arr);f.raw(x,V::from_bool(true));a->set_idx(3,V::from_obj(x));break;}
        case 15:f.grid->set_prop(f.c,SYM_GEN_items_1092,V::from_arr(a));a->timer_watch=&f.foreign.native_timer_watch;break;
        case 16:f.items[1]->set_prop(f.c,SYM_GEN_gems_41,f.items[0]->f_gems);break;
        case 17:a->push_back(f.c.arena,V::from_obj(f.items[0]));break;
        case 18:b->push_back(f.c.arena,V::from_obj(f.gems[0]));break;
        case 19:f.c.native_timer_watch.closed_world=false;break;
        case 20:f.c.native_timer_watch.enabled=false;break;
        case 21:f.c.native_timer_watch.usable=false;break;
        case 22:f.c.native_timer_watch.version=UINT64_MAX;f.c.native_timer_watch.change();break;
        case 23:f.c.native_timer_watch.depth=1;break;
        case 24:
#ifdef GD_ACTIVE_NEW
            f.c.native_timer_watch.cooldown_version=UINT64_MAX;
#endif
            break;
        case 25:
#ifdef GD_ACTIVE_NEW
            f.c.native_timer_watch.cooldown_version=UINT64_MAX-1;
#endif
            f.trigger=f.items[0];f.armed=true;f.action=[&]{f.raw(f.items[3],V::from_bool(!f.items[3]->f__cooldown_active.b));};break;
        case 26:f.grid->set_prop(f.c,SYM_GEN_items_1092,V::from_arr(f.list({})));break;
        case 27:f.items[0]->set_prop(f.c,SYM_GEN_gems_41,V::null());break;
        case 28:f.items[0]->set_prop(f.c,SYM_GEN_gems_41,V::from_int(3));break;
        case 29:f.set(f.items[0],false);f.set(f.items[0],true);break;
        case 30:f.c.reset_for_battle(42);f.setup(8,config);f.c.native_resolved_collect=config>=2;f.tick();break;
        case 31:{auto* x=gd::GdArr::create(f.c.arena,1);x->data=f.foreign.arena.alloc_array<V>(1);x->len=1;x->data[0]=V::from_obj(f.items[0]);f.track(x);f.grid->set_prop(f.c,SYM_GEN_items_1092,V::from_arr(x));break;}
        }
    }
    f.tick();f.tick();
    uint64_t h=mix(f.state(),std::fetestexcept(FE_ALL_EXCEPT));for(auto n:f.trace)h=mix(h,n);
    uint64_t legacy=1469598103934665603ULL;unsigned index=0;
    for(auto [fn,count]:counters)for(unsigned i=0;i<count;++i)legacy=mix(legacy,fn(i)-before[index++]);
    return {h,legacy};
}
int main() {
    register_gen_syms();std::vector<uint64_t> state,legacy;
    for(unsigned family=0;family<3;++family){const unsigned count=family==0?4:family==1?80:32;
        for(unsigned s=0;s<count;++s)for(unsigned c=0;c<4;++c)for(int r:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}){
            const auto [a,b]=run(family,s,c,r);state.push_back(a);legacy.push_back(b);
        }
    }
    std::cout<<"{\"cases\":"<<state.size()<<",\"state_hashes\":[";
    for(unsigned i=0;i<state.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<state[i]<<std::dec<<'"';}
    std::cout<<"],\"legacy_hashes\":[";for(unsigned i=0;i<legacy.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<legacy[i]<<std::dec<<'"';}
    std::cout<<"],\"layout\":{\"GdVal\":"<<sizeof(V)<<",\"GdArr\":"<<sizeof(gd::GdArr)<<",\"CoreItem\":"<<sizeof(Item)<<",\"BattleCtx\":"<<sizeof(gd::BattleCtx)<<"}}\n";
}
