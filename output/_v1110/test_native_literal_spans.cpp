#include "native_event_kernel.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItemData.hpp"
#include <bit>
#include <array>
#include <cassert>
#include <cfenv>
#include <functional>
#include <iostream>
#include <vector>
#include <xmmintrin.h>

using V=gd::GdVal;
using Bus=Gd__gd_core__CoreEventBus;
using Context=Gd__gd_core__CoreContext;
using Rng=Gd__gd_core__CoreRng;
using Item=Gd__gd_core__CoreItem;
static uint64_t mix(uint64_t h,uint64_t n){return(h^n)*1099511628211ULL;}
static uint64_t hash(const V& value,unsigned depth=0){
    uint64_t h=mix(1469598103934665603ULL,unsigned(value.kind));
    switch(value.kind){
    case V::Kind::Bool:return mix(h,value.b);
    case V::Kind::Int:return mix(h,uint64_t(value.i));
    case V::Kind::Float:return mix(h,std::bit_cast<uint64_t>(value.f));
    case V::Kind::Str:if(value.str){h=mix(h,value.str->len);for(unsigned i=0;i<value.str->len;++i)h=mix(h,uint8_t(value.str->data[i]));}return h;
    case V::Kind::Arr:if(value.arr && depth<5){h=mix(h,value.arr->len);h=mix(h,value.arr->cap);h=mix(h,value.arr->is_pool_real);for(unsigned i=0;i<value.arr->len;++i)h=mix(h,hash(value.arr->data[i],depth+1));}return h;
    default:return h;
    }
}
static uint64_t checks=0;
static const gd::GdClassMeta receiver_meta{65001,"LiteralObserver"};
struct Observer:gd::GdObj {
    std::function<V(const V*,int)> action;
    gd::SymId accepted=gd::SYM_NONE;
    explicit Observer(gd::BattleCtx* ctx):GdObj(ctx){}
    const gd::GdClassMeta* meta()const override{return &receiver_meta;}
    bool call_method(gd::BattleCtx&,gd::SymId method,const V* args,int argc,V& out)override{
        if(method!=gd::SYM_call_funcv && method!=gd::intern_sym("literal_callback") && method!=accepted)return false;
        out=action(args,argc);return true;
    }
};
struct DerivedRng:Rng {using Rng::Rng;};
struct BusOverride:gd::GdObj {
    uint64_t& trace;
    BusOverride(gd::BattleCtx* c,uint64_t& t):GdObj(c),trace(t){}
    const gd::GdClassMeta* meta()const override{return &receiver_meta;}
    bool call_method(gd::BattleCtx& c,gd::SymId method,const V* args,int argc,V& out)override{
        if(method!=SYM_GEN_emitEvent_1593)return false;
        assert(argc==4);trace=mix(trace,hash(args[3]));(void)c.math_rng.randi();out=V::null();return true;
    }
};
template<class T>static T* make(gd::BattleCtx& c,const gd::GdClassMeta& meta){auto* p=static_cast<T*>(meta.alloc_fn(c));p->init_fields(c);return p;}
static V emit(gd::BattleCtx& caller,const V& bus,const V* prefix,const V* data,int count){
#ifdef LITERAL_SPANS_CANDIDATE
    return gd_native_emit_literal_event(caller,bus,prefix,data,count);
#else
    auto* a=gd::GdArr::create(caller.arena,static_cast<uint32_t>(count));
    for(int i=0;i<count;++i)a->data[a->len++]=data[i];
    const V args[]={prefix[0],prefix[1],prefix[2],V::from_arr(a)};
    return native_event_call<Bus,&Bus::fn_emitEvent>(caller,bus,SYM_GEN_emitEvent_1593,args,4);
#endif
}
static uint64_t one(unsigned mode,unsigned tracing,bool native,bool audit,bool dispatch,bool split,unsigned rounding,unsigned daz,unsigned count){
    gd::BattleCtx battle(8192),other(8192);battle.bind_battle(109);other.bind_battle(110);
    for(auto* c:{&battle,&other}){c->native_event_kernel=native;c->native_event_audit=true;c->native_resolved_dispatch=dispatch;c->native_resolved_audit=audit;c->native_resolved_collect=true;}
    Context context(&battle),switched(&battle);context.init_fields(battle);switched.init_fields(battle);context.f_fight_ended=V::from_bool(mode==9 || mode==23);
    auto* rng=make<Rng>(battle,META_Gd__gd_core__CoreRng);rng->f_rng=V::from_rng(&battle.math_rng);
    rng->f_oracle_trace=V::from_bool(tracing==1 || tracing==3);rng->f__stacktrace=V::from_bool(tracing==1 || tracing==3);
    context.f_rng=V::from_obj(rng);switched.f_rng=V::from_obj(rng);switched.f_fight_ended=V::from_bool(true);
    Bus bus(&battle);bus.init_fields(battle);bus.f__ctx=V::from_obj(&context);
    context.f_bus=V::from_obj(&bus);
    auto* emitter=make<Item>(battle,META_Gd__gd_core__CoreItem);
    auto* descriptor=make<Gd__gd_core__CoreItemData>(battle,META_Gd__gd_core__CoreItemData);
    descriptor->f_identifier=V::from_cstr(battle.arena,"literal_item");emitter->f_descriptor=V::from_obj(descriptor);emitter->f_ownerType=V::from_int(1);
    const auto signal=V::from_cstr(battle.arena,"literal_signal");
    const V id_args[]={V::from_obj(emitter),V::from_int(0)};const auto id=bus.fn_getEmissionID(id_args,2);
    bus.f_signalIDs.dict->set(battle.arena,signal,V::from_int(0));
    auto* listeners=gd::GdArr::create(battle.arena,3);
    bus.f_connections.dict->set(battle.arena,id,V::from_arr(listeners));
    auto* reference=battle.arena.make<gd::GdFuncRef>();reference->instance=rng;reference->method=SYM_GEN_flip_1735;
    Observer opaque(&battle),last(&battle);uint64_t trace=1469598103934665603ULL;
    const auto add=[&](const V& callback,const V& recv){listeners->push_back(battle.arena,V::from_arr(gd::GdArr::from_init(battle.arena,{callback,recv})));};
    if(mode!=1)add(V::from_funcref(reference),V::from_obj(rng));
    V retained;bool changed=false,nested=false;
    V prefix[]={mode==2?V::null():V::from_obj(emitter),mode==3?V::from_cstr(battle.arena,"absent"):signal,V::null()};
    V payload[]={V::from_float(mode==18?std::bit_cast<double>(UINT64_C(0x7ff0000000000042)):0.375),V::from_arr(gd::GdArr::from_init(battle.arena,{V::from_int(19)}))};
    gd::BattleCtx& caller=split?other:battle;
    std::function<void()> fire=[&]{emit(caller,V::from_obj(&bus),prefix,payload,int(count));};
    opaque.action=[&](const V* args,int argc){
        assert(argc==1 && args[0].kind==V::Kind::Arr);retained=args[0];auto* a=retained.arr;
        trace=mix(trace,hash(retained));(void)battle.math_rng.randi();
        if(tracing==2){rng->f_oracle_trace=V::from_bool(true);rng->f__stacktrace=V::from_bool(true);}
        if(tracing==3){rng->f_oracle_trace=V::from_bool(false);rng->f__stacktrace=V::from_bool(false);}
        if(changed)return V::null();changed=true;
        if(mode==5 || mode==16){for(unsigned i=0;i<17;++i)a->push_back(caller.arena,V::from_int(i));a->data[0]=V::from_float(0.125);}
        if(mode==6)add(V::from_obj(&last),V::from_obj(&last));
        if(mode==7)listeners->data[2]=listeners->data[1];
        if(mode==8 && !nested){nested=true;fire();}
        if(mode==10)context.f_fight_ended=V::from_bool(true);
        if(mode==11)bus.f_connections.dict->clear();
        if(mode==19 && a->len>1)a->data[1].arr->push_back(caller.arena,V::from_int(51));
        if(mode==21)battle.native_resolved_dispatch=!dispatch;
        return V::null();
    };
    last.action=[&](const V* args,int argc){assert(argc==1 && args[0].kind==V::Kind::Arr);trace=mix(trace,hash(args[0]));return V::null();};
    if(mode>=5 && mode!=9 && mode!=14 && mode!=15){add(V::from_obj(&opaque),V::from_obj(&opaque));add(V::from_funcref(reference),V::from_obj(rng));}
    Observer log(&battle);log.accepted=SYM_GEN_logEvent_1357;
    auto* event=make<Gd__gd_core__CoreEvent>(battle,META_Gd__gd_core__CoreEvent);
    event->f_type=V::from_cstr(battle.arena,"literal_event");
    if(mode>=22){
        prefix[2]=V::from_obj(event);context.f_combat_log=V::from_obj(&log);
        log.action=[&](const V* args,int argc){assert(argc==1 && args[0].obj==event);trace=mix(trace,991);(void)battle.math_rng.randi();
            if(mode==24){rng->f_oracle_trace=V::from_bool(true);rng->f__stacktrace=V::from_bool(true);}
            if(mode==25)add(V::from_obj(&last),V::from_obj(&last));
            if(mode==26)bus.f__ctx=V::from_obj(&switched);
            return V::null();};
    }
    if(mode==12)reference->binds=gd::GdArr::from_init(battle.arena,{V::from_int(97)});
    if(mode==13){auto* fr=battle.arena.make<gd::GdFuncRef>();fr->instance=&opaque;fr->method=gd::intern_sym("literal_callback");opaque.action=[&](const V* args,int argc){trace=mix(trace,unsigned(argc));for(int i=0;i<argc;++i)trace=mix(trace,hash(args[i]));if(argc)const_cast<V*>(args)[0]=V::from_float(0.25);return V::null();};listeners->data[0].arr->data[0]=V::from_funcref(fr);}
    if(mode==14)rng->native_call_row_=nullptr;
    if(mode==15){auto* derived=battle.arena.make<DerivedRng>(&battle);derived->init_fields(battle);derived->f_rng=rng->f_rng;derived->native_call_row_=rng->native_call_row_;reference->instance=derived;battle.native_resolved_audit=true;}
    gd::NativeMethodRow custom{};
    if(mode==16 && rng->native_call_row_){custom=*rng->native_call_row_;custom.methods[83]=[](gd::GdObj*,const V* args,int argc){if(argc)const_cast<V*>(args)[0]=V::from_float(0.75);return V::null();};rng->native_call_row_=&custom;battle.native_resolved_audit=false;}
    if(mode==17)reference->method=gd::SYM_NONE;
    if(mode==4)bus.f_loggingMode=V::from_int(2);
    BusOverride override_bus(&battle,trace);
    const int rounds[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(rounds[rounding]);
    _mm_setcsr((_mm_getcsr()&~0x8040u)|((daz&1)?0x40u:0)|((daz&2)?0x8000u:0));
    std::feclearexcept(FE_ALL_EXCEPT);_mm_setcsr(_mm_getcsr()&~0x3fu);
    std::array<uint64_t,5> before{};std::copy(std::begin(battle.native_event_counts),std::end(battle.native_event_counts),before.begin());
    if(mode==20)emit(caller,V::from_obj(&override_bus),prefix,payload,int(count));else fire();
    if(mode==4){trace=mix(trace,hash(bus.f_signalQueue));payload[0]=V::from_float(0.875);bus.fn_flushLoggingQueue(nullptr,0);}
    trace=mix(trace,std::fetestexcept(FE_ALL_EXCEPT));trace=mix(trace,_mm_getcsr());
    trace=mix(trace,hash(retained));trace=mix(trace,hash(rng->f_oracle_trace_log));trace=mix(trace,hash(bus.f_signalQueue));
    trace=mix(trace,battle.math_rng.pcg.state);trace=mix(trace,battle.math_rng.pcg.inc);trace=mix(trace,battle.next_gid);
    trace=mix(trace,other.math_rng.pcg.state);trace=mix(trace,other.next_gid);
    for(auto n:battle.native_resolved_counts)trace=mix(trace,n);
    for(auto n:other.native_resolved_counts)trace=mix(trace,n);
    for(unsigned i=0;i<before.size();++i)trace=mix(trace,battle.native_event_counts[i]-before[i]);
#ifdef LITERAL_SPANS_CANDIDATE
    // Exercise the exact direct-DLL canonical wrapper, and assert the array
    // really remains absent. This assertion cannot pass via materialization.
    if(mode==0 && native && dispatch && rng->native_call_row_){
        NativeLiteralEventArguments view{caller.arena,payload,int(count),V::null()};
        (void)view.invoke(battle,V::from_funcref(reference));assert(view.array.is_null());++checks;
    }
#endif
    return trace;
}
int main(){
    register_gen_syms();const auto csr=_mm_getcsr();const auto rounding=std::fegetround();std::vector<uint64_t> hashes;
    for(unsigned mode=0;mode<27;++mode)for(unsigned tracing=0;tracing<4;++tracing)
    for(bool native:{false,true})for(bool audit:{false,true})for(bool dispatch:{false,true})
    for(bool split:{false,true})for(unsigned count=0;count<3;++count){
        const auto index=hashes.size();
#ifdef LITERAL_SPANS_DEBUG
        std::cerr<<"case "<<index<<" mode "<<mode<<" trace "<<tracing<<" native "<<native<<" audit "<<audit<<" dispatch "<<dispatch<<" split "<<split<<" count "<<count<<'\n';
#endif
        hashes.push_back(one(mode,tracing,native,audit,dispatch,split,unsigned(index%4),unsigned((index/4)%4),count));
    }
    std::fesetround(rounding);_mm_setcsr(csr);
    std::cout<<"{\"passed\":true,\"cases\":"<<hashes.size()<<",\"span_checks\":"<<checks<<",\"hashes\":[";
    for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'\"'<<std::hex<<hashes[i]<<std::dec<<'\"';}std::cout<<"]}\n";
}
