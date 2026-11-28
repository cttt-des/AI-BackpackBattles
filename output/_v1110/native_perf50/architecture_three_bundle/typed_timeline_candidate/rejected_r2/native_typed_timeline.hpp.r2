#pragma once
#include "native_inline_dispatch.hpp"
#include "native_scalar_equal.hpp"
#include "native_array_index.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem__INNER__CoreElectricalCharge.hpp"
#include <bit>
#include <xmmintrin.h>
namespace gd::typed_timeline {
using V=GdVal;using Context=Gd__gd_core__CoreContext;using Character=Gd__gd_core__CoreCharacter;using Item=Gd__gd_core__CoreItem;using Charge=Gd__gd_core__CoreItem__INNER__CoreElectricalCharge;
inline thread_local bool collect=false;
inline thread_local uint64_t counts[4]{};
inline void hit(unsigned n){if(collect)++counts[n];}
// Every F32 boundary remains a separate SSE conversion; do not collapse lerp.
static double f32(double x){volatile float f=static_cast<float>(x);return double(f);}
static bool floats(std::initializer_list<V> vs){for(auto& v:vs)if(v.kind!=V::Kind::Float)return false;return true;}
static double lerp(double a,double b,double t,double duration){return f32(a+f32(f32(f32(b-a)*t)/duration));}
static void typed_visual(Character* c,const V* delta){
    if(c->f__visual_kind.kind!=V::Kind::Int || c->f__visual_kind.i==0 || c->f__visual_stage.kind!=V::Kind::Int || c->f__visual_stage.i!=2 || !floats({c->f__visual_elapsed,c->f__visual_back,c->f__visual_from_x,c->f__visual_to_x,c->f__visual_to_y}) || (std::bit_cast<uint64_t>(c->f__visual_back.f)>>63) || !(std::bit_cast<uint64_t>(c->f__visual_back.f)&0x7fffffffffffffffULL) || ((std::bit_cast<uint64_t>(c->f__visual_back.f)>>52)&2047)==2047){
        c->fn_tickVisualMotion(delta,1);return;
    }
    hit(1);
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
    hit(2);
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



inline bool motion_entry(BattleCtx& b,const V& entry,const V& delta,bool& keep){
    if(!b.native_resolved_dispatch || b.native_resolved_audit || b.native_event_audit || b.native_resolved_collect || (_mm_getcsr()&~63u)!=0x1f80u || entry.kind!=V::Kind::Arr || !entry.arr || entry.arr->len!=3)return false;
    const auto* data=entry.arr->data;
    if(data[0].kind!=V::Kind::Int || data[1].kind!=V::Kind::Obj || !data[1].obj)return false;
    const auto* row=data[1].obj->native_call_row_;
    if(!row || row->metadata!=(data[0].i==0?&META_Gd__gd_core__CoreCharacter:&META_Gd__gd_core__CoreItem))return false;
    hit(0);keep=false;
    if(data[0].i==0){auto* c=static_cast<Character*>(data[1].obj);
        if(native_scalar_eq(c->f__visual_generation,data[2]) && native_scalar_ne(c->f__visual_kind,V::from_int(0))){typed_visual(c,&delta);keep=native_scalar_ne(c->f__visual_kind,V::from_int(0));}
    }else{const V args[]={data[2],delta};typed_charge(static_cast<Item*>(data[1].obj),args);keep=native_scalar_truth(native_inline_get_prop(b,args[0],SYM_GEN_active_1653));}
    return true;
}

__attribute__((noinline)) static V typed_delay(Context& ctx,const V& delta){auto& b=*ctx.rt_ctx_;
    if(ctx.f__timed.kind!=V::Kind::Arr || !ctx.f__timed.arr)return ctx.fn__step_native_delays(&delta,1);
    const uint32_t limit=ctx.f__timed.arr->len;uint32_t read=0,write=0;
    while(read<limit){hit(3);const auto entry=gd::native_array_index(b,ctx.f__timed,V::from_int(read));
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
}
