#include "native_inline_dispatch.hpp"
static bool ordering_literal_path=false;
#define main retained_audit_main_unused
#include "test_same_frame_potions_all_dispatch.cpp"
#undef main
#include <sstream>

static std::vector<int> extra_bus_case(const std::string& name,bool native){
    Fixture f(native);std::vector<int> trace;bool nested=false;
    Receiver emitter(&f.c);gd::GdArr* listeners=nullptr;
    auto* third=f.receiver([&]{trace.push_back(3);});
    auto emit=[&]{f.emit(&emitter,"test",V::from_arr(gd::GdArr::create(f.c.arena)));};
    auto* first=f.receiver([&]{
        trace.push_back(1);
        if(name=="shrink")listeners->resize(f.c.arena,1);
        if(name=="erase_current")listeners->remove_at(0);
        if(name=="erase_future")listeners->remove_at(1);
        if(name=="replace_future")listeners->set_idx(1,listeners->data[2]);
        if(name=="clear_then_append"){listeners->resize(f.c.arena,0);f.connect(&emitter,"test",third);}
        if(name=="clear_dictionary")f.bus->fn_disconnectAll(nullptr,0);
        if(name=="replace_array"){
            auto* fr=f.c.arena.make<gd::GdFuncRef>();fr->instance=third;fr->method=gd::intern_sym("mark");
            const auto pair=V::from_arr(gd::GdArr::from_init(f.c.arena,{V::from_funcref(fr),V::from_obj(third)}));
            V args[]={V::from_obj(&emitter),gd::get_index(f.c,f.bus->f_signalIDs,V::from_cstr(f.c.arena,"test"))};
            f.bus->f_connections.dict->set(f.c.arena,f.bus->fn_getEmissionID(args,2),V::from_arr(gd::GdArr::from_init(f.c.arena,{pair})));
        }
        if(name=="append64")for(int i=0;i<64;++i)f.connect(&emitter,"test",f.receiver([&,i]{trace.push_back(i+3);}));
        if((name=="nested_append" || name=="nested_clear") && !nested){
            nested=true;if(name=="nested_append")f.connect(&emitter,"test",third);emit();
        } else if(name=="nested_clear" && nested)listeners->resize(f.c.arena,0);
        if(name=="append_ended"){f.connect(&emitter,"test",third);f.ctx->f_fight_ended=V::from_bool(true);}
        if(name=="delayed")f.connect(&emitter,"test",third);
    });
    f.connect(&emitter,"test",first);f.connect(&emitter,"test",f.receiver([&]{trace.push_back(2);}));
    if(name=="erase_current" || name=="erase_future" || name=="replace_future")f.connect(&emitter,"test",third);
    V idargs[]={V::from_obj(&emitter),gd::get_index(f.c,f.bus->f_signalIDs,V::from_cstr(f.c.arena,"test"))};
    listeners=gd::get_index(f.c,f.bus->f_connections,f.bus->fn_getEmissionID(idargs,2)).arr;
    if(name=="already_ended")f.ctx->f_fight_ended=V::from_bool(true);
    if(name=="delayed"){V mode=V::from_int(2);f.bus->fn_setLoggingMode(&mode,1);}
    emit();
    if(name=="delayed")f.bus->fn_flushLoggingQueue(nullptr,0);
    if(name=="replace_array")emit();
    return trace;
}

struct RecordingCompare:Receiver {
    std::vector<int> trace;
    explicit RecordingCompare(gd::BattleCtx* c):Receiver(c){}
    bool call_method(gd::BattleCtx& c,gd::SymId m,const V* args,int argc,V& out)override{
        if(m==gd::intern_sym("compare")){
            auto* a=static_cast<Receiver*>(args[0].obj);auto* b=static_cast<Receiver*>(args[1].obj);
            trace.push_back(a->index);trace.push_back(b->index);out=V::from_bool(a->priority>b->priority);return true;
        }
        return Receiver::call_method(c,m,args,argc,out);
    }
};
int main(){
    register_gen_syms();bool comma=false;
    std::cout<<"{\"potions\":[";
    for(bool reverse:{false,true}){
        for(int cost:{2,5,10}){if(comma)std::cout<<',';comma=true;potion_case("heroic",reverse,cost,true);}
        std::cout<<',';potion_case("health",reverse,0,true);
    }
    for(const char* kind:{"linked","without_activate","repeat_empty","trigger_empty"}){std::cout<<',';potion_case(kind,false,0,true);}
    std::cout<<"],\"bus\":{";comma=false;
    for(const char* name:{"ordinary","append","clear","nested","ended"}){
        if(comma)std::cout<<',';comma=true;auto trace=bus_case(name,true);assert(trace==bus_case(name,false));std::cout<<'"'<<name<<"\":";print_ints(trace);
    }
    std::cout<<"},\"bus_extra\":{";comma=false;
    for(const char* name:{"shrink","erase_current","erase_future","replace_future","clear_then_append","clear_dictionary","replace_array","append64","nested_append","nested_clear","append_ended","already_ended","delayed"}){
        if(comma)std::cout<<',';comma=true;auto trace=extra_bus_case(name,true);assert(trace==extra_bus_case(name,false));std::cout<<'"'<<name<<"\":";print_ints(trace);
    }
    std::cout<<"},\"bus_literal\":{";comma=false;ordering_literal_path=true;
    for(const char* name:{"ordinary","append","clear","nested","ended"}){
        if(comma)std::cout<<',';comma=true;auto trace=bus_case(name,true);assert(trace==bus_case(name,false));std::cout<<'"'<<name<<"\":";print_ints(trace);
    }
    std::cout<<"},\"bus_extra_literal\":{";comma=false;
    for(const char* name:{"shrink","erase_current","erase_future","replace_future","clear_then_append","clear_dictionary","replace_array","append64","nested_append","nested_clear","append_ended","already_ended","delayed"}){
        if(comma)std::cout<<',';comma=true;auto trace=extra_bus_case(name,true);assert(trace==extra_bus_case(name,false));std::cout<<'"'<<name<<"\":";print_ints(trace);
    }
    ordering_literal_path=false;
    std::cout<<"},\"sort_cases\":[";comma=false;int length;
    while(std::cin>>length){
        gd::BattleCtx c;std::vector<std::unique_ptr<Receiver>> items;auto* array=gd::GdArr::create(c.arena);
        for(int i=0;i<length;++i){int priority;std::cin>>priority;auto p=std::make_unique<Receiver>(&c);p->index=i;p->priority=priority;array->push_back(c.arena,V::from_obj(p.get()));items.push_back(std::move(p));}
        RecordingCompare compare(&c);gd::sort_custom_stable(c,array,&compare,gd::intern_sym("compare"));
        std::vector<int> order;for(unsigned i=0;i<array->len;++i)order.push_back(static_cast<Receiver*>(array->data[i].obj)->index);
        if(comma)std::cout<<',';comma=true;std::cout<<"{\"order\":";print_ints(order);std::cout<<",\"comparisons\":";print_ints(compare.trace);std::cout<<'}';
    }
    std::cout<<"]}\n";return 0;
}
