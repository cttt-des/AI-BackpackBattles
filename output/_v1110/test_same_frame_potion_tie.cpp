#define main audit_other_contracts_main
#include "test_same_frame_potions.cpp"
#undef main
int main(){
    register_gen_syms();std::cout<<'{';bool comma=false;
    for(bool specialized:{false,true}){
        Fixture f;auto* a=f.potion(false,"A",4);auto* b=f.potion(false,"B",4);
        auto* items=gd::GdArr::create(f.c.arena);items->push_back(f.c.arena,V::from_obj(a));
        for(int i=0;i<15;++i)items->push_back(f.c.arena,V::from_obj(f.receiver([]{})));
        items->push_back(f.c.arena,V::from_obj(b));
        Receiver comparator(&f.c);
        // A comparator that calls the actual per-item priority method.
        struct Compare:Receiver {
            explicit Compare(gd::BattleCtx* c):Receiver(c){}
            bool call_method(gd::BattleCtx& c,gd::SymId m,const V* args,int argc,V& out)override{
                if(m==gd::intern_sym("compare")){
                    const auto priority=gd::intern_sym("getTriggerPriority");
                    auto x=gd::call_method(c,args[0],priority,nullptr,0);auto y=gd::call_method(c,args[1],priority,nullptr,0);
                    out=V::from_bool(x.as_int()>y.as_int());return true;
                }
                return Receiver::call_method(c,m,args,argc,out);
            }
        } compare(&f.c);
        if(specialized)gd::godot_sort_custom_items(f.c,items);
        else gd::sort_custom_stable(f.c,items,&compare,gd::intern_sym("compare"));
        for(unsigned i=0;i<items->len;++i)if(items->data[i].obj==a || items->data[i].obj==b){V out;items->data[i].obj->call_method(f.c,gd::intern_sym("onPrepare"),nullptr,0,out);}
        V amount=V::from_int(2);f.actor->fn_useStamina(&amount,1);
        if(comma)std::cout<<',';comma=true;std::cout<<'"'<<(specialized?"specialized":"generic")<<"\":{\"trace\":";print_strings(f.trace);
        std::cout<<",\"full\":["<<(gd::gd_truth(a->f_isFull)?"true":"false")<<','<<(gd::gd_truth(b->f_isFull)?"true":"false")<<"]}";
    }
    std::cout<<"}\n";
}
