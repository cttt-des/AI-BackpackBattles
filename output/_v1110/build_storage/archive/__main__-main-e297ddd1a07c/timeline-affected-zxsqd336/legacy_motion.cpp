#include "preflight_motion_indices.hpp"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <bit>
#include <cassert>
#include <cfenv>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
using V=gd::GdVal;
using Context=Gd__gd_core__CoreContext;
using Character=Gd__gd_core__CoreCharacter;
static uint64_t mix(uint64_t h,uint64_t x){return(h^x)*1099511628211ULL;}
static uint64_t hash(const V& v){uint64_t h=mix(1469598103934665603ULL,unsigned(v.kind));switch(v.kind){
case V::Kind::Null:return h;case V::Kind::Bool:return mix(h,v.b);case V::Kind::Int:return mix(h,uint64_t(v.i));case V::Kind::Float:return mix(h,std::bit_cast<uint64_t>(v.f));
case V::Kind::Vec2:return mix(mix(h,std::bit_cast<uint64_t>(v.v2.x)),std::bit_cast<uint64_t>(v.v2.y));case V::Kind::Obj:return mix(h,v.obj?v.obj->gid_:0);
case V::Kind::Arr:if(v.arr){h=mix(h,v.arr->len);for(unsigned i=0;i<v.arr->len;++i)h=mix(h,hash(v.arr->data[i]));}return h;
case V::Kind::Dict:if(v.dict){h=mix(h,v.dict->len);for(unsigned i=0;i<v.dict->len;++i){h=mix(h,hash(v.dict->entries[i].key));h=mix(h,hash(v.dict->entries[i].val));}}return h;
case V::Kind::Str:if(v.str){h=mix(h,v.str->len);for(unsigned i=0;i<v.str->len;++i)h=mix(h,(unsigned char)v.str->data[i]);}return h;
case V::Kind::ClassRef:return mix(h,v.cls?v.cls->id:0);default:return h;}}
extern "C" uint64_t gd_diag_native_variant_stat(unsigned);
extern "C" uint64_t gd_diag_native_property_stat(unsigned);
extern "C" uint64_t gd_diag_native_hot_slot_stat(unsigned);
extern "C" uint64_t gd_diag_native_dispatch_chain_stat(unsigned);
extern "C" uint64_t gd_diag_native_type_constructor_stat(unsigned);
static const std::pair<uint64_t(*)(unsigned),unsigned> legacy_counters[]={{gd_diag_native_variant_stat,10},{gd_diag_native_property_stat,2},{gd_diag_native_hot_slot_stat,2},{gd_diag_native_dispatch_chain_stat,4},{gd_diag_native_type_constructor_stat,4}};
static V invoke(bool candidate,Context& context,const V* args,int argc){
#ifdef GD_MOTION_PRODUCTION
    return context.fn_tickMotion(args,argc);
#elif defined(GD_MATCHED_LOCAL)
    return candidate?candidate_tickMotion(context,args,argc):reference_tickMotion(context,args,argc);
#else
    return candidate?candidate_tickMotion(context,args,argc):context.fn_tickMotion(args,argc);
#endif
}
static const gd::GdClassMeta mock_meta{65001,"MotionMutation"};
struct Actor:gd::GdObj {
    V generation=V::from_int(7),kind=V::from_int(1),active=V::from_bool(true),size=V::from_int(0);
    std::function<void(unsigned)> action;std::vector<uint64_t>* trace=nullptr;
    mutable unsigned reads=0;unsigned calls=0;bool fired=false;
    explicit Actor(gd::BattleCtx* c):GdObj(c){}
    const gd::GdClassMeta* meta()const override{return &mock_meta;}
    bool get_prop(gd::SymId prop,V& out)const override{
        ++reads;if(trace)trace->push_back(mix(gid_,prop));
        if(action)action(prop);
        if(prop==SYM_GEN__visual_generation_1125)out=generation;
        else if(prop==SYM_GEN__visual_kind_1123)out=kind;
        else if(prop==SYM_GEN_active_1653)out=active;
        else return false;
        return true;
    }
    bool call_method(gd::BattleCtx&,gd::SymId method,const V* args,int argc,V& out)override{
        ++calls;if(trace){trace->push_back(mix(gid_,method));trace->push_back(argc);for(int i=0;i<argc;++i)trace->push_back(hash(args[i]));}
        if(action)action(method);
        out=method==gd::SYM_size?size:V::null();return true;
    }
};
struct Fixture {
    gd::BattleCtx c{65536};Context ctx{&c};Character character{&c};
    Actor container{&c};std::vector<std::unique_ptr<Actor>> actors;
    std::vector<V> entries;gd::GdArr* queue;gd::GdArr* replacement;gd::GdDict* dictionary;
    std::vector<uint64_t> trace;unsigned mutation=0,trigger=0;bool candidate=false,busy=false;
    Fixture(unsigned count=6){
        ctx.gid_=500;character.gid_=501;container.gid_=502;container.trace=&trace;
        c.native_resolved_dispatch=true;c.native_resolved_audit=true;
        queue=gd::GdArr::create(c.arena,count+8);replacement=gd::GdArr::create(c.arena,count+8);dictionary=gd::GdDict::create(c.arena,count+8);
        for(unsigned i=0;i<count;++i){auto a=std::make_unique<Actor>(&c);a->gid_=600+i;a->trace=&trace;
            auto e=V::from_arr(gd::GdArr::from_init(c.arena,{V::from_int(i%2),V::from_obj(a.get()),i%2?V::from_obj(a.get()):V::from_int(7)}));
            actors.push_back(std::move(a));entries.push_back(e);queue->push_back(c.arena,e);replacement->push_back(c.arena,e);dictionary->set(c.arena,V::from_int(i),e);
        }
        ctx.f__motion_queue=V::from_arr(queue);container.size=V::from_float(2.5);
        for(auto& a:actors){Actor* actor=a.get();actor->action=[this,actor](unsigned point){mutate(*actor,point);};}
        character.f__visual_generation=V::from_int(7);character.f__visual_kind=V::from_int(1);character.f__visual_stage=V::from_int(0);
        character.f__visual_elapsed=V::from_float(0.01);character.f__visual_forward=V::from_float(0.2);character.f__visual_back=V::from_float(0.3);
        character.f__visual_from_x=V::from_float(-0.0);character.f__visual_from_y=V::from_float(2.25);
        character.f__visual_to_x=V::from_float(10.5);character.f__visual_to_y=V::from_float(-3.75);
    }
    void mutate(Actor& actor,unsigned point){
        if(!mutation||actor.fired||busy||actors.empty()||&actor!=actors[0].get())return;
        const bool selected=trigger==0?(point==SYM_GEN_tickVisualMotion_1137||point==SYM_GEN__tickChargePath_506):trigger==1?point==SYM_GEN__visual_generation_1125:point==SYM_GEN__visual_kind_1123;
        if(!selected)return;actor.fired=true;busy=true;trace.push_back(9000+mutation);
        switch(mutation){
        case 1:actor.kind=V::from_int(0);actor.active=V::from_bool(false);break;
        case 2:queue->push_back(c.arena,entries.back());break;
        case 3:if(queue->len>1){for(unsigned i=1;i+1<queue->len;++i)queue->data[i]=queue->data[i+1];--queue->len;}break;
        case 4:queue->len=0;break;
        case 5:ctx.f__motion_queue=V::from_arr(replacement);break;
        case 6:ctx.f__motion_queue=V::from_dict(dictionary);break;
        case 7:entries[0].arr->data[2]=V::from_int(999);break;
        case 8:queue->push_back(c.arena,entries.back());actor.kind=V::from_int(0);break;
        case 9:{V delta=V::from_float(0.025);trace.push_back(hash(invoke(candidate,ctx,&delta,1)));break;}
        case 10:c.native_resolved_dispatch=!c.native_resolved_dispatch;break;
        case 11:entries[0].arr->data[1]=V::from_obj(actors.back().get());actor.active=V::null();break;
        case 12:actors[1]->kind=V::from_int(0);actors[1]->active=V::from_bool(false);break;
        case 13:ctx.f__motion_queue=V::null();break;
        case 14:ctx.f__motion_queue=V::from_arr(nullptr);break;
        case 15:if(queue->len>1)queue->data[1]=entries[0];actor.kind=V::from_int(0);break;
        case 16:ctx.f__motion_queue=V::from_obj(&container);actor.kind=V::from_int(0);break;
        case 17:ctx.f__motion_queue=V::from_str(gd::make_static_str("abc"));actor.kind=V::from_int(0);break;
        case 18:queue->len=2;queue->push_back(c.arena,entries[0]);actor.kind=V::from_int(0);break;
        case 19:queue->data[0]=V::null();break;
        case 20:ctx.f__motion_queue=V::from_dict(nullptr);actor.kind=V::from_int(0);break;
        }busy=false;
    }
};
static V value(unsigned n){switch(n%10){case 0:return V::null();case 1:return V::from_bool(false);case 2:return V::from_bool(true);case 3:return V::from_int(7);case 4:return V::from_float(7.0);case 5:return V::from_float(-0.0);case 6:return V::from_float(std::bit_cast<double>(UINT64_C(0x7ff8000000001234)));case 7:return V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234)));case 8:return V::from_str(gd::make_static_str("seven"));default:return V::from_int(INT64_MAX);}}
static uint64_t latest_legacy=0;
static uint64_t run_case(bool candidate,unsigned family,unsigned scenario,unsigned config,int rounding){
    assert(std::fesetround(FE_TONEAREST)==0);Fixture f;f.candidate=candidate;
    f.c.native_resolved_dispatch=config!=0;f.c.native_resolved_collect=config>=2;f.c.native_resolved_audit=config!=3;
    f.c.native_event_kernel=config!=0;f.c.native_event_audit=config>=2;
    V delta=value(scenario%10);int argc=scenario%13==0?0:scenario%17==0?-1:1;
    if(family==0){f.mutation=scenario%21;f.trigger=(scenario/21)%3;}
    else if(family==1){const unsigned n=scenario%10;f.actors[0]->generation=value(n);f.entries[0].arr->data[2]=value((scenario/10)%10);f.actors[0]->kind=value((scenario/100)%10);f.actors[1]->active=value(n);}
    else if(family==2){switch(scenario%12){case 0:f.ctx.f__motion_queue=V::null();break;case 1:f.ctx.f__motion_queue=V::from_arr(nullptr);break;case 2:f.ctx.f__motion_queue=V::from_dict(f.dictionary);break;case 3:f.ctx.f__motion_queue=V::from_obj(&f.container);break;case 4:f.ctx.f__motion_queue=V::from_str(gd::make_static_str("abc"));break;case 5:f.ctx.f__motion_queue=V::from_int(3);break;case 6:f.ctx.f__motion_queue=V::from_dict(nullptr);break;case 7:f.queue->len=0;break;case 8:f.queue->len=1;break;case 9:f.queue->data[0]=V::null();break;case 10:f.queue->data[0]=V::from_dict(f.dictionary);break;case 11:f.queue->data[0]=V::from_arr(nullptr);break;}}
    else {f.entries[0].arr->data[1]=V::from_obj(&f.character);f.character.f__visual_stage=V::from_int(scenario%3);f.character.f__visual_kind=V::from_int((scenario/3)%3);f.character.f__visual_elapsed=value((scenario/9)%10);}
    std::vector<uint64_t> before;for(auto[fn,n]:legacy_counters)for(unsigned i=0;i<n;++i)before.push_back(fn(i));
    assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);
    V result=invoke(candidate,f.ctx,&delta,argc);const int flags=std::fetestexcept(FE_ALL_EXCEPT);
    uint64_t h=mix(hash(result),flags);for(auto v:{f.ctx.f__motion_queue,V::from_arr(f.queue),V::from_arr(f.replacement),V::from_dict(f.dictionary)})h=mix(h,hash(v));
    for(auto v:f.entries)h=mix(h,hash(v));for(auto& a:f.actors){for(auto v:{a->generation,a->kind,a->active})h=mix(h,hash(v));h=mix(mix(mix(h,a->reads),a->calls),a->fired);}
    h=mix(mix(h,f.container.reads),f.container.calls);for(auto n:f.trace)h=mix(h,n);
    for(auto v:{f.character.f__visual_kind,f.character.f__visual_stage,f.character.f__visual_elapsed,f.character.f__visual_x,f.character.f__visual_y,f.character.f_attack_moving_forward})h=mix(h,hash(v));
    for(auto n:f.c.native_resolved_counts)h=mix(h,n);for(auto n:f.c.native_event_counts)h=mix(h,n);h=mix(mix(mix(h,f.c.next_gid),f.c.math_rng.pcg.state),f.c.math_rng.pcg.inc);
    latest_legacy=1469598103934665603ULL;unsigned j=0;for(auto[fn,n]:legacy_counters)for(unsigned i=0;i<n;++i)latest_legacy=mix(latest_legacy,fn(i)-before[j++]);return h;
}
static uint64_t cycles(){ULONG64 n;assert(QueryThreadCycleTime(GetCurrentThread(),&n));return n;}
static double cpu(){FILETIME a,b,k,u;assert(GetThreadTimes(GetCurrentThread(),&a,&b,&k,&u));ULARGE_INTEGER x,y;x.LowPart=k.dwLowDateTime;x.HighPart=k.dwHighDateTime;y.LowPart=u.dwLowDateTime;y.HighPart=u.dwHighDateTime;return(x.QuadPart+y.QuadPart)*1e-7;}
static volatile uint64_t sink=0;
static void bench(bool candidate,unsigned workload){Fixture f(workload==0?0:16);for(auto& a:f.actors){a->action={};a->trace=nullptr;}if(workload==2)for(auto& a:f.actors)a->kind=V::from_int(0);if(workload==3)for(unsigned i=0;i<f.entries.size();++i){f.entries[i].arr->data[0]=V::from_int(1);f.entries[i].arr->data[2]=V::from_obj(f.actors[i].get());}V delta=V::from_float(1.0/60);for(unsigned i=0;i<30000;++i){f.queue->len=f.entries.size();for(unsigned j=0;j<f.entries.size();++j)f.queue->data[j]=f.entries[j];sink=hash(invoke(candidate,f.ctx,&delta,1));}}
int main(int argc,char**argv){register_gen_syms();assert(SetPriorityClass(GetCurrentProcess(),BELOW_NORMAL_PRIORITY_CLASS));assert(SetProcessAffinityMask(GetCurrentProcess(),4));
    if(argc>1&&std::string(argv[1])=="--screen"){std::cout<<"{\"workloads\":[";for(unsigned w=0;w<4;++w){if(w)std::cout<<',';std::cout<<"{\"workload\":"<<w<<",\"pairs\":[";for(unsigned p=0;p<8;++p){if(p)std::cout<<',';std::cout<<'{';for(unsigned arm=0;arm<2;++arm){if(arm)std::cout<<',';bool c=(p%2==0)?arm==0:arm==1;const auto t=std::chrono::steady_clock::now();const auto ct=cpu();const auto cy=cycles();bench(c,w);const auto elapsed=std::chrono::duration<double>(std::chrono::steady_clock::now()-t).count();const auto ce=cpu()-ct;const auto cyc=cycles()-cy;std::cout<<'"'<<(c?"candidate":"baseline")<<"\":{\"wall_s\":"<<elapsed<<",\"cpu_s\":"<<ce<<",\"cycles\":"<<cyc<<'}';}std::cout<<'}';}std::cout<<"]}";}std::cout<<"]}\n";return 0;}
    std::vector<uint64_t> hashes,counters;for(unsigned family=0;family<4;++family){unsigned n=family==0?63:family==1?200:family==2?12:90;for(unsigned s=0;s<n;++s)for(unsigned config=0;config<4;++config)for(int r:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}){const auto a=run_case(false,family,s,config,r),la=latest_legacy;const auto b=run_case(true,family,s,config,r),lb=latest_legacy;if(a!=b||la!=lb){std::cerr<<"mismatch family="<<family<<" scenario="<<s<<" config="<<config<<" rounding="<<r<<" state="<<std::hex<<a<<'/'<<b<<" counters="<<la<<'/'<<lb<<'\n';return 2;}hashes.push_back(a);counters.push_back(la);}}
    std::cout<<"{\"passed\":true,\"cases\":"<<hashes.size()<<",\"case_hashes\":[";for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<hashes[i]<<std::dec<<'"';}std::cout<<"],\"legacy_counter_hashes\":[";for(unsigned i=0;i<counters.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<counters[i]<<std::dec<<'"';}std::cout<<"]}\n";
}
