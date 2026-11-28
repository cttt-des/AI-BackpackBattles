#include "native_inline_dispatch.hpp"
#include "native_scalar_equal.hpp"
#include "native_array_index.hpp"
#include <windows.h>
#include <xmmintrin.h>
#include <bit>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
using V=gd::GdVal;using Context=Gd__gd_core__CoreContext;
#include "local_delay.hpp"
static double f32(double x){volatile float y=static_cast<float>(x);return double(y);}
static uint64_t mix(uint64_t a,uint64_t b){return(a^b)*1099511628211ull;}
static uint64_t hash(const V& v){uint64_t h=unsigned(v.kind);if(v.kind==V::Kind::Float)return mix(h,std::bit_cast<uint64_t>(v.f));if(v.kind==V::Kind::Int)return mix(h,v.i);if(v.kind==V::Kind::Bool)return mix(h,v.b);if(v.kind==V::Kind::Arr && v.arr)for(unsigned i=0;i<v.arr->len;++i)h=mix(h,hash(v.arr->data[i]));return h;}
struct Receiver:gd::GdObj {Context* ctx=nullptr;unsigned mutation=0,calls=0;gd::GdArr* queue=nullptr;V extra;
    explicit Receiver(gd::BattleCtx* b):GdObj(b){}
    const gd::GdClassMeta* meta()const override{return nullptr;}
    bool call_method(gd::BattleCtx& b,gd::SymId,const V*,int,V& out)override{++calls;if(calls==1){if(mutation==1)ctx->f__timed.arr->push_back(b.arena,extra);if(mutation==2)queue->len=0;if(mutation==3)extra.arr->data[2]=V::from_float(.2);if(mutation==4)ctx->f_fight_ended=V::from_bool(true);if(mutation==5)ctx->f__timed=V::from_arr(gd::GdArr::from_init(b.arena,{extra}));}out=V::null();return true;}
};
struct Scene {gd::BattleCtx b{1u<<20};Context ctx{&b};Receiver receiver{&b};std::vector<V> entries;
    Scene(unsigned count,unsigned mutation=0){b.bind_battle(123);b.native_resolved_dispatch=true;ctx.init_fields(b);ctx.f_fight_ended=V::from_bool(false);receiver.ctx=&ctx;receiver.mutation=mutation;receiver.queue=ctx.f__timed.arr;
        for(unsigned i=0;i<count;++i){auto e=V::from_arr(gd::GdArr::from_init(b.arena,{V::from_obj(&receiver),V::from_str(gd::make_static_str("done")),V::from_float(mutation?(i==0?.001:.2):1000000.0+i*.125),V::from_arr(gd::GdArr::create(b.arena))}));entries.push_back(e);ctx.f__timed.arr->push_back(b.arena,e);}receiver.extra=V::from_arr(gd::GdArr::from_init(b.arena,{V::from_obj(&receiver),V::from_str(gd::make_static_str("done")),V::from_float(.25),V::from_arr(gd::GdArr::create(b.arena))}));}
    void reset(){ctx.f__timed.arr->len=0;for(unsigned i=0;i<entries.size();++i){entries[i].arr->data[2]=V::from_float(1000000.0+i*.125);ctx.f__timed.arr->push_back(b.arena,entries[i]);}}
};
__attribute__((noinline)) static V typed_delay(Context& ctx,const V& delta){auto& b=*ctx.rt_ctx_;
    if(ctx.f__timed.kind!=V::Kind::Arr || !ctx.f__timed.arr)return ctx.fn__step_native_delays(&delta,1);
    const uint32_t limit=ctx.f__timed.arr->len;uint32_t read=0,write=0;
    while(read<limit){const auto entry=gd::native_array_index(b,ctx.f__timed,V::from_int(read));
        auto target=entry;V next;
        if(entry.kind==V::Kind::Arr && entry.arr && entry.arr->len>2 && entry.arr->data[2].kind==V::Kind::Float)next=V::from_float(f32(entry.arr->data[2].f-delta.as_float()));
        else{const V a=gd::gd_sub(gd::native_array_index(b,entry,V::from_int(2)),delta);Context::call_static_fn(b,SYM_GEN__nativeF32_1502,&a,1,next);}
        gd::native_array_set_index(b,target,V::from_int(2),next);
        if(gd::gd_lt(gd::native_array_index(b,entry,V::from_int(2)),V::from_float(0))){
            if(!gd::native_scalar_truth(ctx.f_fight_ended) && !gd::native_array_index(b,entry,V::from_int(0)).is_null()){const V ca[]={gd::native_array_index(b,entry,V::from_int(1)),gd::native_array_index(b,entry,V::from_int(3))};gd::native_inline_call(b,gd::native_array_index(b,entry,V::from_int(0)),gd::SYM_callv,ca,2);}
        }else{if(write!=read){auto q=ctx.f__timed;gd::native_array_set_index(b,q,V::from_int(write),entry);}++write;}++read;
    }
    if(write!=limit){const auto end=gd::native_inline_call(b,ctx.f__timed,gd::SYM_size,nullptr,0);V tail_read=V::from_int(read),tail_write=V::from_int(write);while(gd::gd_lt(tail_read,end)){auto q=ctx.f__timed;gd::native_array_set_index(b,q,tail_write,gd::native_array_index(b,ctx.f__timed,tail_read));tail_write=gd::gd_add(b,tail_write,V::from_int(1));tail_read=gd::gd_add(b,tail_read,V::from_int(1));}gd::native_inline_call(b,ctx.f__timed,gd::SYM_resize,&tail_write,1);}return V::null();
}
static uint64_t signature(const Scene& s){uint64_t h=mix(hash(s.ctx.f__timed),s.receiver.calls);for(auto e:s.entries)h=mix(h,hash(e));return mix(h,gd::native_scalar_truth(s.ctx.f_fight_ended));}
__attribute__((noinline)) static void step(Scene& s,char l){const V delta=V::from_float(.01666666753590107);if(l=='A')s.ctx.fn__step_native_delays(&delta,1);else if(l=='R')local_delay(&s.ctx,&delta,1);else typed_delay(s.ctx,delta);}
static uint64_t cycles(){ULONG64 n=0;assert(QueryThreadCycleTime(GetCurrentThread(),&n));return n;}
extern "C" void gd_diag_native_timeline_collect(int);extern "C" uint64_t gd_diag_native_timeline_stat(unsigned);
int main(){register_gen_syms();gd_diag_native_timeline_collect(1);const auto saved=_mm_getcsr();unsigned cases=0;for(unsigned fp=0;fp<16;++fp)for(unsigned mutation=0;mutation<22;++mutation){Scene a(4,mutation),b(4,mutation),r(4,mutation);const auto control=0x1f80u|((fp&3)<<13)|((fp&4)?0x40:0)|((fp&8)?0x8000:0);for(unsigned frame=0;frame<32;++frame){
            if(mutation>=6 && frame==3){const uint64_t payloads[]={0,0x8000000000000000ULL,1,0x8000000000000001ULL,0x3ff0000000000000ULL,0x412e848000000000ULL,0x7fefffffffffffffULL,0xffefffffffffffffULL,0x7ff0000000000000ULL,0xfff0000000000000ULL,0x7ff8000000000123ULL,0x7ff0000000000123ULL,0xfff8000000000456ULL,0xfff0000000000456ULL,0x3fd5555555555555ULL,0xbfd5555555555555ULL};for(Scene* s:{&a,&b,&r})s->entries[1].arr->data[2]=V::from_float(std::bit_cast<double>(payloads[mutation-6]));}
_mm_setcsr(control);step(a,'A');const auto ac=_mm_getcsr();_mm_setcsr(control);step(b,'B');const auto bc=_mm_getcsr();_mm_setcsr(control);step(r,'R');const auto rc=_mm_getcsr();if(signature(a)!=signature(b)||signature(a)!=signature(r)||ac!=bc||ac!=rc){std::cerr<<"mismatch "<<fp<<' '<<mutation<<' '<<frame<<'\n';return 2;}++cases;}}
    _mm_setcsr(saved);std::cout<<"{\"passed\":true,\"semantic_cases\":"<<cases<<",\"coverage\":[";for(unsigned i=0;i<4;++i){if(i)std::cout<<',';std::cout<<gd_diag_native_timeline_stat(i);}std::cout<<"]}\n";}
