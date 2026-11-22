#include "gd_rt.hpp"
#include "gen/hdrs/Gd__gd_core__CoreEvent.hpp"
#include <array>
#include <bit>
#include <cassert>
#include <cfenv>
#include <iostream>
#include <vector>
#include <xmmintrin.h>
using V=gd::GdVal;
static uint64_t mix(uint64_t h,uint64_t x){return(h^x)*1099511628211ULL;}
static uint64_t small_caps=0,old_caps=0;
static uint64_t hash(const V& v,unsigned depth=0) {
    uint64_t h=mix(1469598103934665603ULL,unsigned(v.kind));
    switch(v.kind) {
    case V::Kind::Bool:return mix(h,v.b);
    case V::Kind::Int:return mix(h,uint64_t(v.i));
    case V::Kind::Float:return mix(h,std::bit_cast<uint64_t>(v.f));
    case V::Kind::Vec2:return mix(mix(h,std::bit_cast<uint64_t>(v.v2.x)),std::bit_cast<uint64_t>(v.v2.y));
    case V::Kind::Str:if(v.str){h=mix(h,v.str->len);for(unsigned i=0;i<v.str->len;++i)h=mix(h,uint8_t(v.str->data[i]));}return h;
    case V::Kind::Arr:if(v.arr && depth<2){h=mix(h,v.arr->len);for(unsigned i=0;i<v.arr->len;++i)h=mix(h,hash(v.arr->data[i],depth+1));}return h;
    case V::Kind::Dict:if(v.dict && depth<2){h=mix(h,v.dict->len);for(unsigned i=0;i<v.dict->len;++i){auto& e=v.dict->entries[i];h=mix(mix(h,hash(e.key,depth+1)),hash(e.val,depth+1));
        if(e.key.kind==V::Kind::Str || e.key.kind==V::Kind::Int || e.key.kind==V::Kind::Float || e.key.kind==V::Kind::Vec2)h=mix(h,e.hash);}}return h;
    default:return h;
    }
}
static void flags_clear(){std::feclearexcept(FE_ALL_EXCEPT);_mm_setcsr(_mm_getcsr()&~0x3fu);}
static uint64_t one(unsigned scenario,bool closed,unsigned mode,unsigned daz) {
    gd::BattleCtx ctx(65536),other(65536);ctx.native_timer_watch.closed_world=closed;
    Gd__gd_core__CoreEvent event(&ctx),alias(&ctx);event.init_fields(ctx);alias.init_fields(ctx);
    std::vector<V> keys;
    for(unsigned i=0;i<24;++i)keys.push_back(V::from_str(gd::make_str(ctx.arena,"k"+std::to_string(i))));
    keys.push_back(V::from_str(nullptr));keys.push_back(V::from_str(gd::make_str(ctx.arena,"")));
    keys.push_back(V::from_str(gd::make_str(ctx.arena,std::string("a\0b",3))));
    auto* d=event.f_params.dict;
    switch(scenario) {
    case 1:d=gd::GdDict::create(ctx.arena,1);break;
    case 2:d=gd::GdDict::create(ctx.arena,4);break;
    case 3:d=gd::GdDict::create(ctx.arena,8);break;
    case 4:d=gd::GdDict::create(ctx.arena,16);break;
    case 5:d->set(ctx.arena,keys[0],V::from_int(801));d->clear();break;
    case 6:d->set(ctx.arena,keys[0],V::from_int(802));d->erase(keys[0]);break;
    case 7:d=gd::GdDict::create(other.arena);break;
    case 8:d->entries=ctx.arena.alloc_array<gd::GdDictEntry>(4);break;
    case 9:d->buckets=ctx.arena.alloc_array<int32_t>(32);d->bucket_cap=32;std::memset(d->buckets,-1,128);break;
    default:break;
    }
    event.f_params=V::from_dict(d);alias.f_params=event.f_params;
    if(scenario==10)event.f_params=V::from_arr(gd::GdArr::from_init(ctx.arena,{V::null(),V::from_int(2),V::from_int(3)}));
    if(scenario==11)event.f_params=V::null();
    if(scenario==12)event.f_params=V::from_dict(nullptr);
    if(scenario==13)event.f_params=V::from_str(gd::make_str(ctx.arena,"abc"));
    if(scenario==14)event.f_params=V::from_obj(nullptr);
    uint64_t trace=1469598103934665603ULL;
    const int rounds[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};
    std::fesetround(rounds[mode]);_mm_setcsr((_mm_getcsr()&~0x8040u)|((daz&1)?0x40u:0)|((daz&2)?0x8000u:0));
    auto state=[&](const V& result) {
        trace=mix(trace,hash(result));trace=mix(trace,hash(event.f_params));trace=mix(trace,hash(alias.f_params));
        trace=mix(trace,event.f_params.kind!=V::Kind::Dict || event.f_params.dict==d);
        trace=mix(trace,ctx.math_rng.pcg.state);trace=mix(trace,ctx.math_rng.pcg.inc);trace=mix(trace,ctx.next_gid);
        trace=mix(trace,std::fetestexcept(FE_ALL_EXCEPT));trace=mix(trace,_mm_getcsr()&0x3f);
    };
    auto set=[&](Gd__gd_core__CoreEvent& receiver,const V& key,const V& value,int argc=2) {
        V args[]={key,value};flags_clear();state(receiver.fn_setParam(args,argc));
    };
    const double snan=std::bit_cast<double>(UINT64_C(0x7ff0000000000042));
    const std::array<V,13> nonstring{V::null(),V::from_bool(true),V::from_int(1),V::from_int(-1),V::from_float(-0.0),V::from_float(snan),
        V::from_float(std::bit_cast<double>(UINT64_C(1))),V::from_vec2(0,0),V::from_arr(nullptr),V::from_dict(nullptr),V::from_obj(nullptr),V::from_float(1.5),V::from_vec2(-1,snan)};
    if(scenario>=15 && scenario<28)set(event,nonstring[scenario-15],V::from_float(snan));
    if(scenario==28)set(event,keys[0],V::from_float(snan),0);
    if(scenario==29)set(event,keys[0],V::from_float(snan),1);
    if(scenario==30){event.f_params=V::from_dict(gd::GdDict::create(ctx.arena));d=event.f_params.dict;alias.f_params=event.f_params;}
    if(scenario==31){set(event,keys[0],V::from_dict(d));d->erase(keys[0]);}
    set(event,keys[0],V::from_float(-0.0));
    if(event.f_params.kind==V::Kind::Dict && event.f_params.dict){small_caps+=event.f_params.dict->cap==4;old_caps+=event.f_params.dict->cap==8;}
    for(unsigned i=1;i<keys.size();++i) {
        set(event,keys[i],V::from_float(i%2?snan:double(i)));
        if(i%3==0)set(alias,keys[i],V::from_int(1000+i));
        V args[]={keys[i],V::from_int(-91)};flags_clear();state(event.fn_getParam(args,2));
        flags_clear();state(event.fn_hasParam(args,1));
        if(i==7 && event.f_params.kind==V::Kind::Dict && event.f_params.dict){flags_clear();event.f_params.dict->erase(keys[2]);state(V::null());}
        if(i==15 && event.f_params.kind==V::Kind::Dict && event.f_params.dict){flags_clear();event.f_params.dict->clear();state(V::null());}
    }
    if(event.f_params.kind==V::Kind::Dict && event.f_params.dict) {
        flags_clear();auto* copy=event.f_params.dict->duplicate(ctx.arena,false);state(V::from_dict(copy));
        set(alias,keys[0],V::from_float(snan));flags_clear();state(V::from_dict(copy));
    }
    flags_clear();state(event.fn_getAmount(nullptr,0));
    return trace;
}
int main() {
    static_assert(sizeof(gd::GdDictEntry)==56);
    const auto old_mxcsr=_mm_getcsr();const int old_round=std::fegetround();std::vector<uint64_t> hashes;
    for(unsigned scenario=0;scenario<32;++scenario)for(unsigned closed=0;closed<2;++closed)
        for(unsigned mode=0;mode<4;++mode)for(unsigned daz=0;daz<4;++daz)hashes.push_back(one(scenario,closed,mode,daz));
    std::fesetround(old_round);_mm_setcsr(old_mxcsr);
    std::cout<<"{\"cases\":"<<hashes.size()<<",\"small_cap_observations\":"<<small_caps<<",\"old_cap_observations\":"<<old_caps
        <<",\"GdDict\":"<<sizeof(gd::GdDict)<<",\"GdVal\":"<<sizeof(V)<<",\"CoreEvent\":"<<sizeof(Gd__gd_core__CoreEvent)
        <<",\"BattleCtx\":"<<sizeof(gd::BattleCtx)<<",\"hashes\":[";
    for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<hashes[i]<<std::dec<<'"';}
    std::cout<<"]}\n";
}
