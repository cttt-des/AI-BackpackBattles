#include "preflight_dispatch_chain.hpp"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <bit>
#include <cassert>
#include <cfenv>
#include <chrono>
#include <iostream>
#include <memory>
using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;
#ifndef GD_CHAIN_PRODUCTION
namespace gd {void native_dispatch_chain_hit(unsigned){}}
#endif
static const char* names[]={"onCombatStart","getGatedDescriptor","getReplaceDescriptor","onChargeReceived","onChargeLeft","chargedItemStatChange","onPreDealDamage_early","onPreDealDamage_late","onDealtDamage","doCooldownEffect","missing_behavior",""};
static uint64_t mix(uint64_t h,uint64_t x){return(h^x)*1099511628211ULL;}
static uint64_t text(const char* s,size_t length){uint64_t h=1469598103934665603ULL;for(size_t i=0;i<length;++i)h=mix(h,static_cast<unsigned char>(s[i]));return h;}
static uint64_t hash(const V& v){uint64_t h=mix(1469598103934665603ULL,unsigned(v.kind));switch(v.kind){
case V::Kind::Null:return h;case V::Kind::Bool:return mix(h,v.b);case V::Kind::Int:return mix(h,uint64_t(v.i));case V::Kind::Float:return mix(h,std::bit_cast<uint64_t>(v.f));
case V::Kind::Vec2:return mix(mix(h,std::bit_cast<uint64_t>(v.v2.x)),std::bit_cast<uint64_t>(v.v2.y));case V::Kind::Str:return mix(h,v.str?text(v.str->data,v.str->len):0);
case V::Kind::Arr:if(!v.arr)return mix(h,0);h=mix(h,v.arr->len);for(unsigned i=0;i<v.arr->len;++i)h=mix(h,hash(v.arr->data[i]));return h;
case V::Kind::Dict:if(!v.dict)return mix(h,0);h=mix(h,v.dict->len);for(unsigned i=0;i<v.dict->len;++i){h=mix(h,hash(v.dict->entries[i].key));h=mix(h,hash(v.dict->entries[i].val));}return h;
case V::Kind::Obj:return mix(h,v.obj?text(v.obj->meta()->class_name,std::strlen(v.obj->meta()->class_name)):0);
case V::Kind::ClassRef:return mix(h,v.cls?text(v.cls->class_name,std::strlen(v.cls->class_name)):0);
case V::Kind::Enum:return mix(h,v.en?v.en->len:0);case V::Kind::FuncRef:return mix(h,v.fr?uint64_t(v.fr->method):0);
case V::Kind::Rng:return mix(h,v.rng?v.rng->pcg.state:0);case V::Kind::Color:return mix(h,v.col?std::bit_cast<uint64_t>(v.col->r):0);
}assert(false);return 0;}
static std::vector<V> inputs(gd::BattleCtx& c,Item& item){std::vector<V> v={V::null(),V::from_bool(false),V::from_bool(true),V::from_int(INT64_MIN),V::from_int(INT64_MAX),V::from_int(100)};
    for(uint64_t bits:{UINT64_C(0),UINT64_C(0x8000000000000000),UINT64_C(0x7ff8000000001234),UINT64_C(0x7ff0000000001234),UINT64_C(0x7ff0000000000000),UINT64_C(1)})v.push_back(V::from_float(std::bit_cast<double>(bits)));
    v.push_back(V::from_vec2(-0.0,1.25));v.push_back(V::from_str(nullptr));v.push_back(V::from_arr(nullptr));v.push_back(V::from_dict(nullptr));v.push_back(V::from_obj(&item));v.push_back(V::from_cls(&META_Gd__gd_core__CoreItem));
    for(const auto* s:names)v.push_back(V::from_cstr(c.arena,s));return v;}
static V invoke(bool candidate,bool probe,Item& item,const V* args,int count){
#ifdef GD_CHAIN_PRODUCTION
    candidate=false;
#endif
    if(probe)return candidate?candidate__hasBehaviorMethod(item,args,count):item.fn__hasBehaviorMethod(args,count);
    return candidate?candidate__behavior_call(item,args,count):item.fn__behavior_call(args,count);
}
static V callback(bool candidate,gd::BattleCtx& c,const V& ref,const V* args,int count){
#ifdef GD_CHAIN_PRODUCTION
    candidate=false;
#endif
    return candidate?candidate_funcv(c,ref,args,count):native_event_funcv(c,ref,args,count);
}
static uint64_t state(gd::BattleCtx& c,const V& result,int flags){uint64_t h=mix(mix(hash(result),flags),c.next_gid);h=mix(mix(h,c.math_rng.pcg.state),c.math_rng.pcg.inc);for(auto n:c.native_resolved_counts)h=mix(h,n);for(auto n:c.native_event_counts)h=mix(h,n);return h;}
static void warm(gd::BattleCtx& c,Item& item,bool cached){c.native_resolved_dispatch=true;c.native_resolved_collect=false;V value;(void)gd::try_native_resolved_property(c,&item,SYM_GEN_ctx_3,value);if(!cached)item.native_call_row_=nullptr;}
struct Fixture {
    gd::BattleCtx c{65536};gd::GdObj* object;Item* item;
    Fixture(const gd::GdClassMeta* meta,bool native,bool cached){c.native_resolved_dispatch=true;c.native_resolved_audit=true;object=meta->alloc_fn(c);item=dynamic_cast<Item*>(object);if(item){item->f__behavior=V::null();warm(c,*item,cached);}c.native_resolved_dispatch=native;c.native_resolved_collect=true;}
};
struct Custom:Item {
    mutable unsigned queries=0,metadata_reads=0;unsigned calls=0;bool mutate=false;gd::GdFuncRef* reference=nullptr;
    explicit Custom(gd::BattleCtx* c):Item(c){}
    const gd::GdClassMeta* meta()const override{++metadata_reads;return Item::meta();}
    bool has_own_method(gd::SymId)const override{++queries;return true;}
    bool call_method(gd::BattleCtx& c,gd::SymId method,const V* args,int count,V& out)override{
        ++calls;if(method==gd::SYM_callv || method==gd::SYM_has_method)return Item::call_method(c,method,args,count,out);
        uint64_t h=uint64_t(count);for(int i=0;i<count;++i)h=mix(h,hash(args[i]));
        if(mutate && reference){reference->method=SYM_GEN_getSpeed_92;reference->binds=nullptr;reference->instance=nullptr;}
        out=V::from_int(int64_t(h));return true;
    }
};
struct Surface:gd::GdObj {
    unsigned calls=0;
    explicit Surface(gd::BattleCtx* c):gd::GdObj(c){}
    const gd::GdClassMeta* meta()const override{return &META_Gd__gd_core__CoreItem;}
    bool call_method(gd::BattleCtx&,gd::SymId method,const V* args,int count,V& out)override{
        assert(method==gd::SYM_call_funcv && args==nullptr);++calls;out=V::from_int(count);return true;
    }
};
static uint64_t surface_case(bool candidate,unsigned kind,int count,int rounding){
    gd::BattleCtx c(65536);c.native_resolved_dispatch=true;c.native_resolved_audit=true;Surface surface(&c);
    V value=kind==0?V::from_obj(&surface):kind==1?V::from_funcref(nullptr):kind==2?V::null():kind==3?V::from_str(nullptr):V::from_arr(nullptr);
    assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);V result=callback(candidate,c,value,nullptr,count);const int flags=std::fetestexcept(FE_ALL_EXCEPT);return mix(state(c,result,flags),surface.calls);
}
static uint64_t probe_case(bool candidate,const gd::GdClassMeta* meta,const V& name,bool native,bool cached,int rounding){
    Fixture f(meta,native,cached);assert(f.item);V args[]={name};assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);const V result=invoke(candidate,true,*f.item,args,1);const int flags=std::fetestexcept(FE_ALL_EXCEPT);return mix(state(f.c,result,flags),f.item->native_call_row_!=nullptr);
}
static uint64_t empty_call_case(bool candidate,const gd::GdClassMeta* meta,unsigned mode,bool native,bool cached,int rounding){
    Fixture f(meta,native,cached);assert(f.item);V arg[]={V::from_cstr(f.c.arena,"onCombatStart"),mode==0?V::from_arr(gd::GdArr::from_init(f.c.arena,{V::from_int(31)})):mode==1?V::from_arr(nullptr):V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234)))};
    assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);const V result=invoke(candidate,false,*f.item,arg,mode==3?1:2);const int flags=std::fetestexcept(FE_ALL_EXCEPT);return state(f.c,result,flags);
}
static uint64_t malformed_case(bool candidate,const gd::GdClassMeta* meta,unsigned variant,bool probe,bool native,bool cached,int rounding){
    gd::GdStr name{variant==1?reinterpret_cast<const char*>(uintptr_t(1)):"onCombatStart",13u,variant==2?1467360435u:0u};
    Fixture f(meta,native,cached);assert(f.item);const V args[]={V::from_str(&name),V::null()};
    assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);const V result=invoke(candidate,probe,*f.item,args,2);const int flags=std::fetestexcept(FE_ALL_EXCEPT);return state(f.c,result,flags);
}
static uint64_t custom_case(bool candidate,unsigned mode,int rounding){
    gd::BattleCtx c(65536);c.native_resolved_dispatch=true;c.native_resolved_audit=true;c.native_resolved_collect=true;Custom item(&c);item.f__behavior=V::null();const V args[]={V::from_cstr(c.arena,"onCombatStart"),V::from_arr(gd::GdArr::from_init(c.arena,{V::from_int(7)}))};
    if(mode==1)item.f__behavior=V::from_obj(&item);if(mode==2)item.native_call_row_=reinterpret_cast<const gd::NativeMethodRow*>(uintptr_t(1));
    assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);const V result=invoke(candidate,mode>=3,item,args,2);const int flags=std::fetestexcept(FE_ALL_EXCEPT);uint64_t h=state(c,result,flags);return mix(mix(mix(h,item.queries),item.calls),item.metadata_reads);
}
static uint64_t callback_case(bool candidate,unsigned mode,bool native,bool cached,int rounding){
    gd::BattleCtx c(65536);c.native_resolved_dispatch=true;c.native_resolved_audit=true;Item item(&c);warm(c,item,cached);Custom custom(&c);gd::GdFuncRef reference;reference.instance=mode>=6?static_cast<gd::GdObj*>(&custom):static_cast<gd::GdObj*>(&item);reference.method=SYM_GEN_character_74;
    item.f_character_=V::from_float(std::bit_cast<double>(UINT64_C(0x7ff8000000001234)));V arguments=V::from_arr(gd::GdArr::from_init(c.arena,{V::from_int(12),V::from_vec2(-0.0,1.25)}));
    if(mode==1)reference.binds=gd::GdArr::create(c.arena);if(mode==2)reference.binds=gd::GdArr::from_init(c.arena,{V::from_int(99)});if(mode==3)reference.method=gd::SYM_get_instance_id;if(mode==4)reference.method=gd::SYM_has_method;if(mode==5)reference.method=0xffffffffu;
    if(mode==7)reference.binds=arguments.arr;if(mode==8){custom.mutate=true;custom.reference=&reference;reference.binds=gd::GdArr::from_init(c.arena,{V::null()});}
    if(mode==9)arguments=V::null();if(mode==10)reference.instance=nullptr;if(mode==11)reference.method=gd::SYM_NONE;if(mode==12)arguments=V::from_arr(nullptr);
    c.native_resolved_dispatch=native;c.native_resolved_collect=true;assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);const V result=callback(candidate,c,V::from_funcref(&reference),&arguments,1);const int flags=std::fetestexcept(FE_ALL_EXCEPT);
    uint64_t h=state(c,result,flags);h=mix(mix(mix(h,custom.calls),custom.queries),custom.metadata_reads);h=mix(h,reference.method);h=mix(h,reference.instance!=nullptr);return mix(h,reference.binds?reference.binds->len:0);
}
static uint64_t redirected_case(bool candidate,bool probe,int rounding){
    gd::BattleCtx c(65536);c.native_resolved_dispatch=true;c.native_resolved_audit=true;Item item(&c);warm(c,item,true);item.f_character_=V::from_int(123);
    const V args[]={V::from_cstr(c.arena,"onCombatStart"),V::null()};c.native_resolved_collect=true;assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);V result=invoke(candidate,probe,item,args,2);const int flags=std::fetestexcept(FE_ALL_EXCEPT);return state(c,result,flags);
}
static uint64_t stamp(FILETIME x){return(uint64_t{x.dwHighDateTime}<<32)|x.dwLowDateTime;}
static uint64_t cpu(){FILETIME a,b,c,d;assert(GetThreadTimes(GetCurrentThread(),&a,&b,&c,&d));return(stamp(c)+stamp(d))*100;}
static uint64_t cycles(){ULONG64 n=0;assert(QueryThreadCycleTime(GetCurrentThread(),&n));return n;}
struct Timing{double cpu_s,wall_s;uint64_t cycle_count,digest;};static volatile uint64_t sink;
static Timing bench(bool candidate,unsigned mode,unsigned count){
    gd::BattleCtx c(65536);c.native_resolved_dispatch=true;Gd__gd_core__PlatinCustomerCard card(&c);card.f__behavior=V::null();warm(c,card,true);Item target(&c);warm(c,target,true);target.f_character_=V::from_int(123);
    gd::GdFuncRef ref;ref.instance=&target;ref.method=SYM_GEN_character_74;V list[]={V::from_int(7)};gd::GdArr arr;arr.data=list;arr.len=arr.cap=1;V arguments=V::from_arr(&arr);const V call_args[]={V::from_cstr(c.arena,"onCombatStart"),arguments};uint64_t h=0;
    // Keep the name outside the resettable arena used for per-call temporaries.
    V stable_args[]={V::from_str(gd::make_static_str("onCombatStart")),arguments};
    const auto before=cpu(),cy=cycles();const auto start=std::chrono::steady_clock::now();
    for(unsigned i=0;i<count;++i){if(i%64==0)c.arena.reset();const V value=mode?callback(candidate,c,V::from_funcref(&ref),&arguments,1):invoke(candidate,false,card,stable_args,2);h=mix(h,hash(value));}
    const double wall=std::chrono::duration<double>(std::chrono::steady_clock::now()-start).count();sink=h;return{(cpu()-before)*1e-9,wall,cycles()-cy,h};
}
static void write(const Timing& t){std::cout<<"{\"cpu_s\":"<<t.cpu_s<<",\"wall_s\":"<<t.wall_s<<",\"cycles\":"<<t.cycle_count<<",\"digest\":"<<t.digest<<'}';}
int main(int argc,char**){register_gen_syms();assert(SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS));assert(SetProcessAffinityMask(GetCurrentProcess(),255));std::vector<uint64_t> hashes;unsigned classes=0;
    gd::BattleCtx inputs_ctx;Item inputs_item(&inputs_ctx);const auto values=inputs(inputs_ctx,inputs_item);
    for(const auto& entry:chain_classes){Fixture check(entry.metadata,true,true);if(!check.item)continue;++classes;
        for(bool native:{false,true})for(bool cached:{false,true})for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO})for(unsigned i=0;i<values.size();++i){auto a=probe_case(false,entry.metadata,values[i],native,cached,rounding),b=probe_case(true,entry.metadata,values[i],native,cached,rounding);if(a!=b){std::cerr<<"probe mismatch "<<entry.metadata->class_name<<" value="<<i<<" native="<<native<<" cached="<<cached<<'\n';return 2;}hashes.push_back(a);}
    }
    for(const auto& entry:safe_calls)for(bool native:{false,true})for(bool cached:{false,true})for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO})for(unsigned mode=0;mode<4;++mode){auto a=empty_call_case(false,entry.metadata,mode,native,cached,rounding),b=empty_call_case(true,entry.metadata,mode,native,cached,rounding);assert(a==b);hashes.push_back(a);}
    for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}){
        for(unsigned mode=0;mode<4;++mode){auto a=custom_case(false,mode,rounding),b=custom_case(true,mode,rounding);assert(a==b);hashes.push_back(a);}
        for(bool native:{false,true})for(bool cached:{false,true})for(unsigned mode=0;mode<13;++mode){auto a=callback_case(false,mode,native,cached,rounding),b=callback_case(true,mode,native,cached,rounding);if(a!=b){std::cerr<<"callback mismatch mode="<<mode<<" native="<<native<<" cached="<<cached<<'\n';return 3;}hashes.push_back(a);}
    }
    gd::register_sym(SYM_GEN_character_74,"onCombatStart");for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO})for(bool probe:{false,true}){auto a=redirected_case(false,probe,rounding),b=redirected_case(true,probe,rounding);assert(a==b);hashes.push_back(a);}gd::register_sym(SYM_GEN_character_74,"character");gd::register_sym(SYM_GEN_onCombatStart_934,"onCombatStart");
    for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO})for(unsigned kind=0;kind<5;++kind)for(int count:{-1,0,1}){auto a=surface_case(false,kind,count,rounding),b=surface_case(true,kind,count,rounding);assert(a==b);hashes.push_back(a);}
    for(const auto& entry:chain_classes){Fixture check(entry.metadata,true,true);if(!check.item)continue;for(bool native:{false,true})for(bool cached:{false,true})for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO})for(unsigned variant=0;variant<3;++variant){auto a=malformed_case(false,entry.metadata,variant,true,native,cached,rounding),b=malformed_case(true,entry.metadata,variant,true,native,cached,rounding);assert(a==b);hashes.push_back(a);}}
    for(const auto& entry:safe_calls)for(bool native:{false,true})for(bool cached:{false,true})for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO})for(unsigned variant=0;variant<3;++variant){auto a=malformed_case(false,entry.metadata,variant,false,native,cached,rounding),b=malformed_case(true,entry.metadata,variant,false,native,cached,rounding);assert(a==b);hashes.push_back(a);}
    assert(std::fesetround(FE_TONEAREST)==0);std::cout<<"{\"passed\":true,\"cases\":"<<hashes.size()<<",\"item_classes\":"<<classes<<",\"input_cases\":"<<values.size();
    if(argc>1){std::cout<<",\"case_hashes\":[";for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'\"'<<std::hex<<hashes[i]<<std::dec<<'\"';}std::cout<<"]}\n";return 0;}
    std::cout<<",\"workloads\":[";for(unsigned mode=0;mode<2;++mode){const unsigned count=mode?1000000:100000;(void)bench(false,mode,1000);(void)bench(true,mode,1000);if(mode)std::cout<<',';std::cout<<"{\"mode\":"<<mode<<",\"calls_per_arm\":"<<count<<",\"pairs\":[";for(unsigned pair=0;pair<8;++pair){Timing a,b;if(pair%2){b=bench(true,mode,count);a=bench(false,mode,count);}else{a=bench(false,mode,count);b=bench(true,mode,count);}assert(a.digest==b.digest);if(pair)std::cout<<',';std::cout<<"{\"baseline\":";write(a);std::cout<<",\"candidate\":";write(b);std::cout<<'}';}std::cout<<"]}";}std::cout<<"]}\n";
}
