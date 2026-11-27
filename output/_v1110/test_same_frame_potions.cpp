#include "native_event_kernel.hpp"
#include "gen/hdrs/Gd__gd_core_items__HeroicPotion.hpp"
#include "gen/hdrs/Gd__gd_core_items__HealthPotion.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItemData.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using V=gd::GdVal;
using Context=Gd__gd_core__CoreContext;
using Bus=Gd__gd_core__CoreEventBus;
using Character=Gd__gd_core__CoreCharacter;
using Item=Gd__gd_core__CoreItem;
using Potion=Gd__gd_core_items__Potion;
static const gd::GdClassMeta meta{65000,"OrderAuditReceiver"};
struct Receiver:gd::GdObj {
    std::function<void()> action;
    int index=0,priority=0;
    explicit Receiver(gd::BattleCtx* ctx):GdObj(ctx){}
    const gd::GdClassMeta* meta()const override{return &::meta;}
    bool call_method(gd::BattleCtx&,gd::SymId method,const V* args,int,V& out)override{
        if(method==gd::intern_sym("mark")){action();out=V();return true;}
        if(method==gd::intern_sym("getTriggerPriority")){out=V::from_int(priority);return true;}
        if(method==gd::intern_sym("compare")){
            out=V::from_bool(static_cast<Receiver*>(args[0].obj)->priority>static_cast<Receiver*>(args[1].obj)->priority);return true;
        }
        return false;
    }
};
struct Fixture {
    gd::BattleCtx c;
    Context* ctx;
    Bus* bus;
    Character* actor;
    std::vector<std::unique_ptr<Receiver>> receivers;
    std::vector<std::string> trace;
    Fixture(bool native=true){
        c.native_event_kernel=native;c.native_event_audit=true;c.native_resolved_dispatch=native;
        ctx=static_cast<Context*>(gd::construct_class(c,&META_Gd__gd_core__CoreContext,nullptr,0).obj);
        ctx->f_native_label_mode=V::from_int(3);ctx->f_label_rng_enabled=V::from_bool(false);
        V args[]={V::from_obj(ctx),V::from_int(0)};
        actor=static_cast<Character*>(gd::construct_class(c,&META_Gd__gd_core__CoreCharacter,args,2).obj);
        ctx->f_player=V::from_obj(actor);ctx->f_opponent=V::from_obj(actor);
        actor->f_opponent=V::from_obj(actor);
        actor->f_curStamina=V::from_float(0);actor->f_maxStamina=V::from_float(2);actor->f_baseMaxStamina=V::from_float(2);
        actor->f_curHealth=V::from_float(40);actor->f_maxHealth=V::from_float(100);
        bus=static_cast<Bus*>(ctx->f_bus.obj);
    }
    Receiver* receiver(std::function<void()> action){auto r=std::make_unique<Receiver>(&c);r->action=std::move(action);auto* p=r.get();receivers.push_back(std::move(r));return p;}
    void connect(gd::GdObj* emitter,const char* signal,Receiver* target){
        V args[]={V::from_obj(emitter),V::from_cstr(c.arena,signal),V::from_obj(target),V::from_cstr(c.arena,"mark")};bus->fn_connectEvent(args,4);
    }
    void emit(gd::GdObj* emitter,const char* signal,const V& arguments){
        V args[]={V::from_obj(emitter),V::from_cstr(c.arena,signal),V(),arguments};bus->fn_emitAndLog(args,4);
    }
    Potion* potion(bool health,const std::string& label,int strength){
        const auto* cls=health?&META_Gd__gd_core_items__HealthPotion:&META_Gd__gd_core_items__HeroicPotion;
        auto* p=static_cast<Potion*>(gd::construct_class(c,cls,nullptr,0).obj);
        auto* data=static_cast<Gd__gd_core__CoreItemData*>(gd::construct_class(c,&META_Gd__gd_core__CoreItemData,nullptr,0).obj);
        data->f_name=data->f_identifier=V::from_cstr(c.arena,label.c_str());
        data->f_params=V::from_arr(gd::GdArr::from_init(c.arena,{V::from_int(strength),V::from_int(0),V::from_int(0)}));
        data->f_namedParams.dict->set(c.arena,V::from_cstr(c.arena,"heal"),V::from_int(strength));
        V setup[]={V::from_obj(ctx),V::from_obj(data),V::from_obj(actor)};p->fn_setup(setup,3);
        p->f_isFull=V::from_bool(true);p->f_placed=V::from_bool(true);p->f_ownerType=V::from_int(1);
        p->f_inventory=actor->f_inventory;
        auto* cached=gd::GdDict::create(c.arena);cached->set(c.arena,V::from_int(0),V::from_arr(gd::GdArr::create(c.arena)));
        p->f_cachedAffectedItems=V::from_dict(cached);
        if(health)static_cast<Gd__gd_core_items__HealthPotion*>(p)->f_healthThreshold=V::from_float(.5);
        for(const char* sig:{"potion_triggered","activated","potion_emptied"}){
            const std::string tag=std::string(sig)+":"+label;connect(p,sig,receiver([this,tag]{trace.push_back(tag);}));
        }
        return p;
    }
};
static void print_strings(const std::vector<std::string>& xs){std::cout<<'[';for(size_t i=0;i<xs.size();++i){if(i)std::cout<<',';std::cout<<'"'<<xs[i]<<'"';}std::cout<<']';}
static void potion_case(const std::string& kind,bool reverse,int cost,bool native){
    Fixture f(native);const bool health=kind=="health";
    auto* a=f.potion(health,"A",health?20:4);auto* b=f.potion(health,"B",health?20:4);
    if(kind=="heroic" || health){
        for(auto* p: reverse?std::vector<Potion*>{b,a}:std::vector<Potion*>{a,b}){
            V out;p->call_method(f.c,gd::intern_sym("onPrepare"),nullptr,0,out);
        }
        if(health)f.emit(f.actor,"character_damaged",V::from_arr(gd::GdArr::from_init(f.c.arena,{V::from_int(1),V()})));
        else{V amount=V::from_int(cost);f.actor->fn_useStamina(&amount,1);}
    } else if(kind=="linked"){
        a->f_cachedAffectedItems.dict->set(f.c.arena,V::from_int(0),V::from_arr(gd::GdArr::from_init(f.c.arena,{V::from_obj(b)})));
        a->fn_consumePotion(nullptr,0);
    } else if(kind=="without_activate"){
        V args[]={V(),V::from_bool(false)};a->fn_consumePotion(args,2);
    } else if(kind=="repeat_empty"){
        a->fn_consumePotion(nullptr,0);a->fn_consumePotion(nullptr,0);
    } else if(kind=="trigger_empty"){
        a->f_isFull=V::from_bool(false);a->fn_triggerPotion(nullptr,0);
    }
    std::cout<<"{\"kind\":\""<<kind<<"\",\"reverse\":"<<(reverse?"true":"false")<<",\"cost\":"<<cost<<",\"trace\":";print_strings(f.trace);
    std::cout<<",\"full\":["<<(gd::gd_truth(a->f_isFull)?"true":"false")<<','<<(gd::gd_truth(b->f_isFull)?"true":"false")<<"],\"stamina\":"<<f.actor->f_curStamina.as_float()<<",\"health\":"<<f.actor->f_curHealth.as_float()<<'}';
}
static std::vector<int> bus_case(const std::string& name,bool native){
    Fixture f(native);std::vector<int> trace;bool nested=false;
    Receiver emitter(&f.c);auto* third=f.receiver([&]{trace.push_back(3);});
    auto emit=[&]{f.emit(&emitter,"test",V::from_arr(gd::GdArr::create(f.c.arena)));};
    auto* first=f.receiver([&]{trace.push_back(1);
        if(name=="append")f.connect(&emitter,"test",third);
        if(name=="clear"){
            V args[]={V::from_obj(&emitter),gd::get_index(f.c,f.bus->f_signalIDs,V::from_cstr(f.c.arena,"test"))};
            gd::get_index(f.c,f.bus->f_connections,f.bus->fn_getEmissionID(args,2)).arr->resize(f.c.arena,0);
        }
        if(name=="nested" && !nested){nested=true;emit();}
        if(name=="ended")f.ctx->f_fight_ended=V::from_bool(true);
    });
    f.connect(&emitter,"test",first);f.connect(&emitter,"test",f.receiver([&]{trace.push_back(2);}));emit();return trace;
}
static void print_ints(const std::vector<int>& xs){std::cout<<'[';for(size_t i=0;i<xs.size();++i){if(i)std::cout<<',';std::cout<<xs[i];}std::cout<<']';}
int main(){
    register_gen_syms();std::cout<<"{\"potions\":[";bool comma=false;
    for(bool reverse:{false,true}){
        for(int cost:{2,5,10}){if(comma)std::cout<<',';comma=true;potion_case("heroic",reverse,cost,true);}
        std::cout<<',';potion_case("health",reverse,0,true);
    }
    for(const char* kind:{"linked","without_activate","repeat_empty","trigger_empty"}){std::cout<<',';potion_case(kind,false,0,true);}
    std::cout<<"],\"bus\":{";comma=false;
    for(const char* name:{"ordinary","append","clear","nested","ended"}){if(comma)std::cout<<',';comma=true;std::cout<<'"'<<name<<"\":";auto a=bus_case(name,true);assert(a==bus_case(name,false));print_ints(a);}
    std::cout<<"},\"sorts\":[";comma=false;
    for(int length:{16,17,32,40,80})for(int mode=0;mode<4;++mode){
        gd::BattleCtx c;std::vector<std::unique_ptr<Receiver>> items;auto* a=gd::GdArr::create(c.arena);auto* b=gd::GdArr::create(c.arena);Receiver compare(&c);
        for(int i=0;i<length;++i){auto p=std::make_unique<Receiver>(&c);p->index=i;p->priority=mode==0?0:((i*7+mode)%(mode+1))*1000;a->push_back(c.arena,V::from_obj(p.get()));b->push_back(c.arena,V::from_obj(p.get()));items.push_back(std::move(p));}
        gd::sort_custom_stable(c,a,&compare,gd::intern_sym("compare"));gd::godot_sort_custom_items(c,b);
        std::vector<int> generic,specialized;for(unsigned i=0;i<a->len;++i){generic.push_back(static_cast<Receiver*>(a->data[i].obj)->index);specialized.push_back(static_cast<Receiver*>(b->data[i].obj)->index);}
        if(comma)std::cout<<',';comma=true;std::cout<<"{\"length\":"<<length<<",\"mode\":"<<mode<<",\"generic\":";print_ints(generic);std::cout<<",\"specialized\":";print_ints(specialized);std::cout<<'}';
    }
    std::cout<<"]}\n";
}
