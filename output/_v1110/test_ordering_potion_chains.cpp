#define main retained_potion_audit_unused
#include "test_same_frame_potions.cpp"
#undef main
#include "gen/hdrs/Gd__gd_core_items__PotionBelt.hpp"
#include "gen/hdrs/Gd__gd_core_items__StrongHealthPotion.hpp"

static const gd::GdClassMeta belt_meta{65001,"OriginalPotionBeltFixture"};
struct BeltFixture:Gd__gd_core_items__PotionBelt {
    Fixture* f;
    explicit BeltFixture(Fixture* fixture):Gd__gd_core_items__PotionBelt(&fixture->c),f(fixture){init_fields(fixture->c);native_call_row_=nullptr;}
    const gd::GdClassMeta* meta()const override{return &belt_meta;}
    bool call_method(gd::BattleCtx& c,gd::SymId method,const V* args,int argc,V& out)override{
        if(method==gd::intern_sym("isTypeInInventory")){out=V::from_bool(false);return true;}
        if(method==gd::intern_sym("giveRandomBuffs")){f->trace.push_back("buff:Belt");out=V();return true;}
        if(method==gd::intern_sym("cleanseRandomDebuffs")){f->trace.push_back("cleanse:Belt");out=V();return true;}
        return Gd__gd_core_items__PotionBelt::call_method(c,method,args,argc,out);
    }
};
static void chain_case(const std::string& kind){
    Fixture f;auto* a=f.potion(false,"A",4);auto* b=f.potion(false,"B",4);
    BeltFixture belt(&f);
    auto* data=static_cast<Gd__gd_core__CoreItemData*>(gd::construct_class(f.c,&META_Gd__gd_core__CoreItemData,nullptr,0).obj);
    data->f_name=data->f_identifier=V::from_cstr(f.c.arena,"Belt");data->f_params=V::from_arr(gd::GdArr::from_init(f.c.arena,{V::from_int(1)}));
    V setup[]={V::from_obj(f.ctx),V::from_obj(data),V::from_obj(f.actor)};belt.fn_setup(setup,3);belt.native_call_row_=nullptr;belt.f_inventory=f.actor->f_inventory;belt.f_numConsumed=V::from_int(0);
    f.connect(&belt,"activated",f.receiver([&]{f.trace.push_back("activated:Belt");}));
    auto connect_belt=[&](Potion* p){V args[]={V::from_obj(p),V::from_cstr(f.c.arena,"potion_emptied"),V::from_obj(&belt),V::from_cstr(f.c.arena,"onPotionEmptied")};f.bus->fn_connectEvent(args,4);};
    connect_belt(a);connect_belt(b);
    if(kind=="four_drinks"){
        auto* c=f.potion(false,"C",4);auto* d=f.potion(false,"D",4);connect_belt(c);connect_belt(d);
        for(auto* p:{a,b,c,d})p->fn_consumePotion(nullptr,0);
        a->fn_consumePotion(nullptr,0);
    } else if(kind=="without_activate"){
        V args[]={V(),V::from_bool(false)};a->fn_consumePotion(args,2);
    } else if(kind=="trigger_empty"){
        a->f_isFull=V::from_bool(false);a->fn_triggerPotion(nullptr,0);
    } else {
        if(kind=="linked" || kind=="nested_linked")a->f_cachedAffectedItems.dict->set(f.c.arena,V::from_int(0),V::from_arr(gd::GdArr::from_init(f.c.arena,{V::from_obj(b)})));
        if(kind=="nested" || kind=="nested_linked")f.connect(a,"potion_triggered",f.receiver([&]{b->fn_consumePotion(nullptr,0);}));
        a->fn_consumePotion(nullptr,0);
    }
    std::cout<<"{\"trace\":";print_strings(f.trace);std::cout<<",\"full\":["<<(gd::gd_truth(a->f_isFull)?"true":"false")<<','<<(gd::gd_truth(b->f_isFull)?"true":"false")<<"],\"numConsumed\":"<<belt.f_numConsumed.as_int()<<'}';
}
int main(){
    register_gen_syms();std::cout<<'{';bool comma=false;
    for(const char* kind:{"four_drinks","without_activate","trigger_empty","linked","nested","nested_linked"}){if(comma)std::cout<<',';comma=true;std::cout<<'"'<<kind<<"\":";chain_case(kind);}
    Fixture f;auto* normal=f.potion(true,"Health",20);auto* strong=gd::construct_class(f.c,&META_Gd__gd_core_items__StrongHealthPotion,nullptr,0).obj;
    const auto priority=gd::intern_sym("getTriggerPriority");std::cout<<",\"health_priorities\":["<<gd::call_method(f.c,V::from_obj(normal),priority,nullptr,0).as_int()<<','<<gd::call_method(f.c,V::from_obj(strong),priority,nullptr,0).as_int()<<"]}\n";return 0;
}
