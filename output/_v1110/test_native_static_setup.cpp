#include <vector>
#include "preflight_static_setup.hpp"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <bit>
#include <cassert>
#include <cfenv>
#include <chrono>
#include <iostream>
#include <cstring>
using V = gd::GdVal;
using Item = Gd__gd_core__CoreItem;
using Descriptor = Gd__gd_core__CoreItemData;
namespace gd {
#ifndef GD_STATIC_SETUP_PRODUCTION
void native_static_setup_hit(unsigned) {}
#endif
}
static uint64_t mix(uint64_t a, uint64_t b) { return (a ^ b) * 1099511628211ULL; }
static uint64_t strhash(const char* data, size_t size) { uint64_t h=1469598103934665603ULL; for(size_t i=0;i<size;++i)h=mix(h,static_cast<unsigned char>(data[i]));return h; }
static uint64_t text(const char* s) { return strhash(s, std::strlen(s)); }
static uint64_t value_hash(const V& v, unsigned depth=0) {
    assert(depth < 12); uint64_t h=mix(1469598103934665603ULL,unsigned(v.kind));
    switch(v.kind) {
    case V::Kind::Null: return h;
    case V::Kind::Bool: return mix(h,v.b);
    case V::Kind::Int: return mix(h,uint64_t(v.i));
    case V::Kind::Float: return mix(h,std::bit_cast<uint64_t>(v.f));
    case V::Kind::Vec2: return mix(mix(h,std::bit_cast<uint64_t>(v.v2.x)),std::bit_cast<uint64_t>(v.v2.y));
    case V::Kind::Color: if(!v.col)return mix(h,0);return mix(mix(mix(mix(h,std::bit_cast<uint64_t>(v.col->r)),std::bit_cast<uint64_t>(v.col->g)),std::bit_cast<uint64_t>(v.col->b)),std::bit_cast<uint64_t>(v.col->a));
    case V::Kind::Str: return mix(h,v.str?strhash(v.str->data,v.str->len):0);
    case V::Kind::Enum: if(!v.en)return mix(h,0);h=mix(mix(h,text(v.en->name)),v.en->len);for(unsigned i=0;i<v.en->len;++i){h=mix(h,text(v.en->items[i].key));h=mix(h,uint64_t(v.en->items[i].val));}return h;
    case V::Kind::ClassRef: return mix(h,v.cls?text(v.cls->class_name):0);
    case V::Kind::Arr: if(!v.arr)return mix(h,0);h=mix(mix(h,v.arr->len),v.arr->is_pool_real);for(unsigned i=0;i<v.arr->len;++i)h=mix(h,value_hash(v.arr->data[i],depth+1));return h;
    case V::Kind::Dict: if(!v.dict)return mix(h,0);h=mix(h,v.dict->len);for(unsigned i=0;i<v.dict->len;++i){h=mix(mix(h,value_hash(v.dict->entries[i].key,depth+1)),value_hash(v.dict->entries[i].val,depth+1));h=mix(h,v.dict->entries[i].hash);}return h;
    case V::Kind::Obj: return mix(h,v.obj?text(v.obj->meta()->class_name):0);
    default: assert(false); return 0;
    }
}
static uint64_t dictionary_storage(const V& v) {
    uint64_t h=value_hash(v);if(v.kind!=V::Kind::Dict || !v.dict)return h;
    h=mix(mix(h,v.dict->cap),v.dict->bucket_cap);
    for(unsigned i=0;i<v.dict->bucket_cap;++i)h=mix(h,uint32_t(v.dict->buckets[i]));return h;
}
static bool getter(bool candidate,gd::BattleCtx& scratch,const StaticCase& entry,V& out) {
#ifdef GD_STATIC_SETUP_PRODUCTION
    candidate=false;
#endif
    return candidate && entry.candidate?entry.candidate(scratch,entry.prop,out):entry.meta->get_static_prop(entry.prop,out);
}
static uint64_t getter_case(bool candidate,const StaticCase& entry,int rounding) {
    gd::BattleCtx scratch(65536);V result=V::from_float(std::bit_cast<double>(UINT64_C(0x7ff8000000001234)));
    assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);
    const bool ok=getter(candidate,scratch,entry,result);const int flags=std::fetestexcept(FE_ALL_EXCEPT);
    const auto first=value_hash(result);V second=V::from_int(778);assert(getter(candidate,scratch,entry,second)==ok);
    uint64_t h=mix(mix(first,ok),flags);h=mix(mix(h,scratch.next_gid),scratch.math_rng.pcg.state);
    if(ok){assert(value_hash(second)==first);
        if(result.kind==V::Kind::Arr && result.arr){assert(result.arr!=second.arr);const auto before=value_hash(second);result.arr->push_back(scratch.arena,V::from_int(913));assert(value_hash(second)==before);h=mix(h,value_hash(result));}
        if(result.kind==V::Kind::Dict && result.dict){assert(result.dict!=second.dict);const auto before=value_hash(second);result.dict->set(scratch.arena,V::from_int(913),V::from_int(914));assert(value_hash(second)==before);h=mix(h,value_hash(result));}
        if(entry.fast && result.kind==V::Kind::Enum)assert(result.en==second.en);
    } else {assert(second.kind==V::Kind::Int && second.i==778);}
    return h;
}
struct DescriptorProxy:gd::GdObj {
    Descriptor* real;Item* target;unsigned mode;mutable unsigned calls=0;
    DescriptorProxy(gd::BattleCtx* c,Descriptor* d,Item* item,unsigned m):gd::GdObj(c),real(d),target(item),mode(m){}
    const gd::GdClassMeta* meta()const override{return &META_Gd__gd_core__CoreItemData;}
    bool get_prop(gd::SymId prop,V& out)const override{
        ++calls;
        if(prop==SYM_GEN_cd_1679 && mode>=13){auto* replacement=gd::GdDict::create(rt_ctx_->arena);target->f_buffPowers=V::from_dict(replacement);target->f_buffAmplificationChances=mode==13?target->f_buffPowers:V::from_dict(gd::GdDict::create(rt_ctx_->arena));}
        return real->get_prop(prop,out);
    }
};
static uint64_t setup_case(bool candidate,unsigned mode,bool native,int rounding) {
#ifdef GD_STATIC_SETUP_PRODUCTION
    candidate=false;
#endif
    gd::BattleCtx c(65536);c.reset_for_battle(123);c.native_resolved_dispatch=native;c.native_resolved_audit=true;
    Gd__gd_core__CoreContext context(&c);context.init_fields(c);
    Gd__gd_core__CoreRng rng(&c);rng.init_fields(c);rng.f_rng=V::from_rng(&c.math_rng);context.f_rng=V::from_obj(&rng);
    Descriptor descriptor(&c);descriptor.init_fields(c);descriptor.f_sceneDepth=V::from_int(mode%4);descriptor.f_cd=V::from_float(1.25);
    Item item(&c);item.init_fields(c);auto* a=item.f_buffPowers.dict;auto* b=item.f_buffAmplificationChances.dict;
    auto put=[&](gd::GdDict* d,int64_t k,double v){d->set(c.arena,V::from_int(k),V::from_float(v));};
    if(mode==1){put(a,-1,-0.0);put(a,105,2.5);put(b,110,9);}
    if(mode==2)item.f_buffAmplificationChances=item.f_buffPowers;
    if(mode==3){for(int64_t i=110;i>=100;--i)put(a,i,double(i));}
    if(mode==4)item.f_buffPowers=V::from_dict(gd::GdDict::create(c.arena,8));
    if(mode==5)item.f_buffAmplificationChances=V::from_dict(gd::GdDict::create(c.arena,32));
    if(mode==6){for(int64_t i=0;i<12;++i)put(a,i,double(i));a->clear();}
    if(mode==7){item.f_buffPowers=V::from_arr(gd::GdArr::create(c.arena,120));item.f_buffPowers.arr->resize(c.arena,120);}
    if(mode==8)item.f_buffPowers=V::null();
    if(mode==9)item.f_buffAmplificationChances=V::from_dict(nullptr);
    if(mode==10)item.f_buffPowers=V::from_obj(&descriptor);
    if(mode==11){put(a,100,0);*b=*a;}
    if(mode==12){put(a,101,1);a->erase(V::from_int(101));}
    V alias_powers=item.f_buffPowers,alias_chances=item.f_buffAmplificationChances;
    DescriptorProxy proxy(&c,&descriptor,&item,mode);const V args[]={V::from_obj(&context),mode>=13?V::from_obj(&proxy):V::from_obj(&descriptor),V::null()};
    assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);
    V result=candidate?candidate_setup(item,args,3):item.fn_setup(args,3);const int flags=std::fetestexcept(FE_ALL_EXCEPT);
    assert(result.kind==V::Kind::Obj && result.obj==&item);uint64_t h=mix(c.math_rng.pcg.state,c.math_rng.pcg.inc);h=mix(mix(h,c.next_gid),flags);h=mix(h,proxy.calls);
    for(const V* field:{&item.f_buffPowers,&item.f_buffAmplificationChances,&item.f_currentAffectedItems,&item.f_itemMetrics,&item.f_statDisplayOverrides,&item.f_baseCooldownOverride,&alias_powers,&alias_chances})h=mix(h,dictionary_storage(*field));
    h=mix(h,item.f_buffPowers.kind==V::Kind::Dict && item.f_buffAmplificationChances.kind==V::Kind::Dict && item.f_buffPowers.dict==item.f_buffAmplificationChances.dict);
    for(V field:{item.f_chanceRng,item.f_damageRangeRng}){
        h=mix(h,value_hash(field));for(const char* name:{"expectedWins","acc","startBias"}){V value;field.obj->get_prop(gd::intern_sym(name),value);h=mix(h,value_hash(value));}
    }
    if(item.f_buffPowers.kind==V::Kind::Dict && item.f_buffPowers.dict){
        auto* d=item.f_buffPowers.dict;for(int64_t i=99;i<113;++i)h=mix(h,value_hash(d->get(V::from_int(i))));
        d->erase(V::from_int(105));put(d,111,5);put(d,101,7);h=mix(h,dictionary_storage(item.f_buffPowers));
        auto* copy=d->duplicate(c.arena,true);copy->set(c.arena,V::from_int(106),V::from_float(8));h=mix(h,value_hash(V::from_dict(copy)));h=mix(h,dictionary_storage(item.f_buffPowers));
    }
    return h;
}
static uint64_t metric_case(bool candidate,unsigned which,int rounding,bool native){
#ifdef GD_STATIC_SETUP_PRODUCTION
    candidate=false;
#endif
    gd::BattleCtx c(65536);c.native_resolved_dispatch=native;assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);V v;
    if(which)v=candidate?candidate_getNumItemMetrics(c,nullptr,0):Item::sf_getNumItemMetrics(c,nullptr,0);
    else v=candidate?candidate_getNumNonStackItemMetrics(c,nullptr,0):Item::sf_getNumNonStackItemMetrics(c,nullptr,0);
    return mix(mix(value_hash(v),std::fetestexcept(FE_ALL_EXCEPT)),c.next_gid);
}
static uint64_t stamp(FILETIME x){return(uint64_t{x.dwHighDateTime}<<32)|x.dwLowDateTime;}
static uint64_t cpu(){FILETIME a,b,c,d;assert(GetThreadTimes(GetCurrentThread(),&a,&b,&c,&d));return(stamp(c)+stamp(d))*100;}
static uint64_t cycles(){ULONG64 n=0;assert(QueryThreadCycleTime(GetCurrentThread(),&n));return n;}
struct Timing{double cpu_s,wall_s;uint64_t cycle_count,digest;};static volatile uint64_t sink;
static Timing bench(bool candidate,unsigned mode,unsigned count,const std::vector<StaticCase>& entries){
    gd::BattleCtx c(65536);c.native_resolved_dispatch=true;Item item(&c);uint64_t h=0;
    std::vector<StaticCase> fast;for(const auto& e:entries)if(e.fast)fast.push_back(e);
    const auto before=cpu(),cy=cycles();const auto start=std::chrono::steady_clock::now();
    for(unsigned i=0;i<count;++i){
        if(!mode){V out;const auto& e=fast[i%fast.size()];assert(getter(candidate,c,e,out));h=mix(h,value_hash(out));}
        else {c.arena.reset();item.f_buffPowers=V::from_dict(gd::GdDict::create(c.arena));item.f_buffAmplificationChances=V::from_dict(gd::GdDict::create(c.arena));if(candidate)candidate_stack_block(item);else baseline_stack_block(item);h=mix(h,item.f_buffPowers.dict->entries[10].hash);}
    }
    const double wall=std::chrono::duration<double>(std::chrono::steady_clock::now()-start).count();sink=h;return{(cpu()-before)*1e-9,wall,cycles()-cy,h};
}
static void write(const Timing& t){std::cout<<"{\"cpu_s\":"<<t.cpu_s<<",\"wall_s\":"<<t.wall_s<<",\"cycles\":"<<t.cycle_count<<",\"digest\":"<<t.digest<<'}';}
int main(int argc,char**){register_gen_syms();assert(SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS));assert(SetProcessAffinityMask(GetCurrentProcess(),255));const auto entries=static_cases();std::vector<uint64_t> hashes;
    for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}){
        for(unsigned i=0;i<entries.size();++i){const auto a=getter_case(false,entries[i],rounding),b=getter_case(true,entries[i],rounding);if(a!=b){std::cerr<<"getter mismatch "<<i<<'\n';return 2;}hashes.push_back(a);}
        for(bool native:{false,true}){for(unsigned mode=0;mode<15;++mode){const auto a=setup_case(false,mode,native,rounding),b=setup_case(true,mode,native,rounding);if(a!=b){std::cerr<<"setup mismatch "<<mode<<" native="<<native<<" rounding="<<rounding<<'\n';return 3;}hashes.push_back(a);}for(unsigned i=0;i<2;++i){const auto a=metric_case(false,i,rounding,native),b=metric_case(true,i,rounding,native);assert(a==b);hashes.push_back(a);}}
    }
    assert(std::fesetround(FE_TONEAREST)==0);std::cout<<"{\"passed\":true,\"cases\":"<<hashes.size()<<",\"static_cases\":"<<entries.size();
    if(argc>1){std::cout<<",\"case_hashes\":[";for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'\"'<<std::hex<<hashes[i]<<std::dec<<'\"';}std::cout<<"]}\n";return 0;}
    std::cout<<",\"workloads\":[";for(unsigned mode=0;mode<2;++mode){const unsigned count=mode?20000:1000000;(void)bench(false,mode,1000,entries);(void)bench(true,mode,1000,entries);if(mode)std::cout<<',';std::cout<<"{\"mode\":"<<mode<<",\"calls_per_arm\":"<<count<<",\"pairs\":[";for(unsigned pair=0;pair<8;++pair){Timing a,b;if(pair%2){b=bench(true,mode,count,entries);a=bench(false,mode,count,entries);}else{a=bench(false,mode,count,entries);b=bench(true,mode,count,entries);}assert(a.digest==b.digest);if(pair)std::cout<<',';std::cout<<"{\"baseline\":";write(a);std::cout<<",\"candidate\":";write(b);std::cout<<'}';}std::cout<<"]}";}std::cout<<"]}\n";
}
