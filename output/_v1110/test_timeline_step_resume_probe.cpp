// Actual [kind, subject, token] records and original per-step FP math.
#include "native_inline_dispatch.hpp"
#include "native_scalar_equal.hpp"
#include "native_array_index.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem__INNER__CoreElectricalCharge.hpp"
#include <windows.h>
#include <xmmintrin.h>
#include <bit>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
using V=gd::GdVal;using Context=Gd__gd_core__CoreContext;using Character=Gd__gd_core__CoreCharacter;using Item=Gd__gd_core__CoreItem;using Charge=Gd__gd_core__CoreItem__INNER__CoreElectricalCharge;
#include "local_motion.hpp"
template<class T>static T* make(gd::BattleCtx& b,const gd::GdClassMeta& meta){auto* p=static_cast<T*>(meta.alloc_fn(b));p->init_fields(b);return p;}
static uint64_t mix(uint64_t a,uint64_t b){return(a^b)*1099511628211ull;}
struct Decoded {gd::GdArr* record=nullptr;int64_t kind=0;gd::GdObj* subject=nullptr;V token;const gd::NativeMethodRow* row=nullptr;};
struct Scene {
    gd::BattleCtx b{1u<<20};Context* ctx;std::vector<Character*> chars;std::vector<Charge*> charges;std::vector<V> entries;std::vector<Decoded> decoded;
    Scene(unsigned mode){b.bind_battle(123);b.native_resolved_dispatch=true;ctx=make<Context>(b,META_Gd__gd_core__CoreContext);ctx->f_fight_ended=V::from_bool(false);
        const unsigned count=mode==3?16:mode==2?4:2;
        for(unsigned i=0;i<count;++i){V subject,token;const bool is_charge=mode==1 || (mode==2 && i%2);
            if(!is_charge){auto* c=make<Character>(b,META_Gd__gd_core__CoreCharacter);c->f__visual_generation=V::from_int(7);c->f__visual_kind=V::from_int(1);c->f__visual_stage=V::from_int(2);c->f__visual_elapsed=V::from_float(.01);c->f__visual_back=V::from_float(1000000);c->f__visual_from_x=V::from_float(-0.0);c->f__visual_to_x=V::from_float(10.5);c->f__visual_to_y=V::from_float(-3.75);chars.push_back(c);subject=V::from_obj(c);token=V::from_int(7);}
            else{auto* item=make<Item>(b,META_Gd__gd_core__CoreItem);auto* c=make<Charge>(b,META_Gd__gd_core__CoreItem__INNER__CoreElectricalCharge);c->f_inventoryCells=V::from_arr(gd::GdArr::from_init(b.arena,{V::null(),V::null()}));c->f_callbackDelays=V::from_arr(gd::GdArr::from_init(b.arena,{V::from_float(1000000)}));c->f_elapsed=V::from_float(.01);c->f_nextCell=V::from_int(2);c->f_active=V::from_bool(true);charges.push_back(c);subject=V::from_obj(item);token=V::from_obj(c);}
            auto e=V::from_arr(gd::GdArr::from_init(b.arena,{V::from_int(is_charge?1:0),subject,token}));entries.push_back(e);ctx->f__motion_queue.arr->push_back(b.arena,e);}
    }
    void reset(){for(auto* c:chars){c->f__visual_elapsed=V::from_float(.01);c->f__visual_kind=V::from_int(1);c->f__visual_generation=V::from_int(7);c->f__visual_back=V::from_float(1000000);}for(auto* c:charges){c->f_elapsed=V::from_float(.01);c->f_active=V::from_bool(true);c->f_nextCell=V::from_int(2);}ctx->f__motion_queue.arr->len=0;for(auto e:entries)ctx->f__motion_queue.arr->push_back(b.arena,e);decoded.clear();}
};
static bool same_token(const V& a,const V& b){return a.kind==b.kind && (a.kind==V::Kind::Int?a.i==b.i:a.kind==V::Kind::Obj?a.obj==b.obj:false);}

// Every F32 boundary remains a separate SSE conversion; do not collapse lerp.
static double f32(double x){volatile float f=static_cast<float>(x);return double(f);}
static bool floats(std::initializer_list<V> vs){for(auto& v:vs)if(v.kind!=V::Kind::Float)return false;return true;}
static double lerp(double a,double b,double t,double duration){return f32(a+f32(f32(f32(b-a)*t)/duration));}
static void typed_visual(Character* c,const V* delta){
    if(c->f__visual_kind.kind!=V::Kind::Int || c->f__visual_kind.i==0 || c->f__visual_stage.kind!=V::Kind::Int || c->f__visual_stage.i!=2 || !floats({c->f__visual_elapsed,c->f__visual_back,c->f__visual_from_x,c->f__visual_to_x,c->f__visual_to_y}) || !(c->f__visual_back.f>0)){
        c->fn_tickVisualMotion(delta,1);return;
    }
    c->f__visual_elapsed=V::from_float(f32(c->f__visual_elapsed.f+delta->as_float()));
    const double back=c->f__visual_kind.i==1?0:c->f__visual_from_x.f;
    if(c->f__visual_elapsed.f<c->f__visual_back.f){
        c->f__visual_x=V::from_float(lerp(c->f__visual_to_x.f,back,c->f__visual_elapsed.f,c->f__visual_back.f));
        c->f__visual_y=V::from_float(lerp(c->f__visual_to_y.f,0,c->f__visual_elapsed.f,c->f__visual_back.f));
    }else{c->f__visual_x=V::from_float(back);c->f__visual_y=V::from_float(0);c->f__visual_kind=V::from_int(0);}
}
static void typed_charge(Item* item,const V* args){
    const auto& v=args[0];auto& b=*item->rt_ctx_;
    if(v.kind!=V::Kind::Obj || !v.obj || !v.obj->native_call_row_ || v.obj->native_call_row_->metadata!=&META_Gd__gd_core__CoreItem__INNER__CoreElectricalCharge){item->fn__tickChargePath(args,2);return;}
    auto* c=static_cast<Charge*>(v.obj);
    if(c->f_elapsed.kind!=V::Kind::Float || c->f_nextCell.kind!=V::Kind::Int || c->f_inventoryCells.kind!=V::Kind::Arr || !c->f_inventoryCells.arr || c->f_callbackDelays.kind!=V::Kind::Arr || !c->f_callbackDelays.arr || c->f_nextCell.i<2 || c->f_nextCell.i>c->f_inventoryCells.arr->len || uint64_t(c->f_nextCell.i-2)>=c->f_callbackDelays.arr->len || c->f_callbackDelays.arr->data[c->f_nextCell.i-2].kind!=V::Kind::Float){item->fn__tickChargePath(args,2);return;}
    // No callback before this original store. Due paths resume the literal
    // original tail, so no duplicated elapsed update or speculative FP work.
    c->f_elapsed=V::from_float(f32(c->f_elapsed.f+args[1].as_float()));
    if(c->f_elapsed.f<c->f_callbackDelays.arr->data[c->f_nextCell.i-2].f)return;
    while(gd::gd_le(gd::native_inline_get_prop(b,v,SYM_GEN_nextCell_1652),gd::native_inline_call(b,gd::native_inline_get_prop(b,v,SYM_GEN_inventoryCells_1649),gd::SYM_size,nullptr,0))){
        if(gd::gd_lt(gd::native_inline_get_prop(b,v,SYM_GEN_elapsed_1651),gd::native_array_index(b,gd::native_inline_get_prop(b,v,SYM_GEN_callbackDelays_1650),gd::gd_sub(gd::native_inline_get_prop(b,v,SYM_GEN_nextCell_1652),V::from_int(2)))))return;
        V ca[]={v,gd::native_inline_get_prop(b,v,SYM_GEN_nextCell_1652),gd::native_inline_get_prop(b,v,SYM_GEN_inventoryCells_1649)};
        gd::native_inline_call(b,V::from_obj(item),SYM_GEN__chargeEnterCell_323,ca,3);
        V charge=v;gd::set_prop(b,charge,SYM_GEN_nextCell_1652,gd::gd_add(b,gd::native_inline_get_prop(b,v,SYM_GEN_nextCell_1652),V::from_int(1)));
    }
    V charge=v;gd::set_prop(b,charge,SYM_GEN_active_1653,V::from_bool(false));gd::set_prop(b,charge,SYM_GEN_lastChargedItem_1647,V::null());gd::set_prop(b,charge,SYM_GEN_curChargedItem_1648,V::null());
}

__attribute__((noinline)) static void typed(Scene& s,const V& delta,bool check){auto& ctx=*s.ctx;auto& b=s.b;
    // Prototype accepts exact production record/receiver types only. Unknown
    // objects require original dispatch and have no claimed coverage here.
    const unsigned limit=ctx.f__motion_queue.arr->len;if(s.decoded.size()<limit)s.decoded.resize(limit);
    unsigned write=0;
    for(unsigned read=0;read<limit;++read){auto entry=gd::native_array_index(b,ctx.f__motion_queue,V::from_int(read));auto& d=s.decoded[read];auto* a=entry.arr;assert(entry.kind==V::Kind::Arr && a && a->len==3);
        if(!d.record || (check && (d.record!=a || a->data[0].kind!=V::Kind::Int || d.kind!=a->data[0].i || a->data[1].kind!=V::Kind::Obj || d.subject!=a->data[1].obj || !same_token(d.token,a->data[2]) || d.subject->native_call_row_!=d.row))){
            assert(a->data[0].kind==V::Kind::Int && a->data[1].kind==V::Kind::Obj);d={a,a->data[0].i,a->data[1].obj,a->data[2],a->data[1].obj->native_call_row_};assert(d.row && d.row->metadata);
            assert(d.row->metadata==(d.kind==0?&META_Gd__gd_core__CoreCharacter:&META_Gd__gd_core__CoreItem));}
        bool keep=false;
        if(d.kind==0){auto* c=static_cast<Character*>(d.subject);
            if(gd::native_scalar_eq(c->f__visual_generation,d.token) && gd::native_scalar_ne(c->f__visual_kind,V::from_int(0))){typed_visual(c,&delta);keep=gd::native_scalar_ne(c->f__visual_kind,V::from_int(0));}}
        else{const V args[]={d.token,delta};typed_charge(static_cast<Item*>(d.subject),args);keep=gd::native_scalar_truth(gd::native_inline_get_prop(b,d.token,SYM_GEN_active_1653));}
        if(keep){if(write!=read){auto q=ctx.f__motion_queue;gd::native_array_set_index(b,q,V::from_int(write),entry);}++write;}
    }
    if(write!=limit){unsigned read=limit;const unsigned end=ctx.f__motion_queue.arr->len;while(read<end){auto q=ctx.f__motion_queue;gd::native_array_set_index(b,q,V::from_int(write++),gd::native_array_index(b,ctx.f__motion_queue,V::from_int(read++)));}const V n=V::from_int(write);gd::native_inline_call(b,ctx.f__motion_queue,gd::SYM_resize,&n,1);}
}
static uint64_t signature(const Scene& s){uint64_t h=s.ctx->f__motion_queue.arr->len;for(auto* c:s.chars){for(auto v:{c->f__visual_elapsed,c->f__visual_x,c->f__visual_y})h=mix(h,std::bit_cast<uint64_t>(v.as_float()));h=mix(h,c->f__visual_kind.as_int());}for(auto* c:s.charges){h=mix(h,std::bit_cast<uint64_t>(c->f_elapsed.as_float()));h=mix(h,gd::native_scalar_truth(c->f_active));h=mix(h,c->f_nextCell.as_int());}return h;}
__attribute__((noinline)) static void step(Scene& s,char label){const V delta=V::from_float(.01666666753590107);if(label=='A')s.ctx->fn_tickMotion(&delta,1);else if(label=='R')local_tick_motion(s.ctx,&delta,1);else typed(s,delta,label=='B');}
static uint64_t cycles(){ULONG64 n=0;assert(QueryThreadCycleTime(GetCurrentThread(),&n));return n;}
int main(){register_gen_syms();const auto saved=_mm_getcsr();unsigned cases=0;
    for(unsigned mode=0;mode<4;++mode)for(unsigned fp=0;fp<16;++fp)for(unsigned change=0;change<4;++change){Scene a(mode),b(mode),r(mode);const unsigned control=0x1f80u|((fp&3)<<13)|((fp&4)?0x40:0)|((fp&8)?0x8000:0);
        for(unsigned frame=0;frame<32;++frame){if(frame==4){for(Scene* s:{&a,&b,&r}){if(change==1 && !s->chars.empty())s->chars[0]->f__visual_back=V::from_float(.1);if(change==2 && !s->chars.empty())s->entries[0].arr->data[2]=V::from_int(99);if(change==3)s->ctx->f__motion_queue.arr->push_back(s->b.arena,s->entries.back());}}
            _mm_setcsr(control);step(a,'A');const auto ca=_mm_getcsr();_mm_setcsr(control);step(b,'B');const auto cb=_mm_getcsr();_mm_setcsr(control);step(r,'R');const auto cr=_mm_getcsr();
            if(signature(a)!=signature(b)||signature(a)!=signature(r)||ca!=cb||ca!=cr){std::cerr<<"mismatch "<<mode<<' '<<fp<<' '<<change<<' '<<frame<<' '<<ca<<' '<<cb<<' '<<cr<<'\n';return 2;}++cases;}}
    _mm_setcsr(saved);std::cout<<std::setprecision(17)<<"{\"passed\":true,\"semantic_cases\":"<<cases<<",\"samples\":[";bool comma=false;
    for(unsigned mode=0;mode<4;++mode)for(unsigned comparison=0;comparison<2;++comparison){Scene s(mode);const char left=comparison==1?'R':'A',right=comparison==2?'C':'B';for(char l:{left,right}){s.reset();for(unsigned i=0;i<2000;++i)step(s,l);}
        for(unsigned q=0;q<4;++q){const char* order=q%2?"BAAB":"ABBA";for(unsigned arm=0;arm<4;++arm){const char label=order[arm]=='A'?left:right;s.reset();const auto c=cycles();const auto start=std::chrono::steady_clock::now();for(unsigned i=0;i<30000;++i)step(s,label);const auto elapsed=std::chrono::duration<double>(std::chrono::steady_clock::now()-start).count();const auto cy=cycles()-c;if(comma)std::cout<<',';comma=true;std::cout<<"{\"mode\":"<<mode<<",\"comparison\":"<<comparison<<",\"quad\":"<<q<<",\"arm\":"<<arm<<",\"label\":\""<<label<<"\",\"wall_s\":"<<elapsed<<",\"cycles\":"<<cy<<",\"signature\":"<<signature(s)<<'}';}}}
    std::cout<<"]}\n";
}
