"""Freeze a second, materially different timeline mechanism before timing."""
from pathlib import Path
STAGE=Path(__file__).resolve().parent
text=(STAGE/'test_timeline_resume_probe.cpp').read_text('utf8')
extra=r'''
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
'''
anchor='__attribute__((noinline)) static void typed(Scene& s'
assert text.count(anchor)==1
text=text.replace(anchor,extra+'\n'+anchor)
assert text.count('c->fn_tickVisualMotion(&delta,1);')==1
text=text.replace('c->fn_tickVisualMotion(&delta,1);','typed_visual(c,&delta);')
assert text.count('static_cast<Item*>(d.subject)->fn__tickChargePath(args,2);')==1
text=text.replace('static_cast<Item*>(d.subject)->fn__tickChargePath(args,2);','typed_charge(static_cast<Item*>(d.subject),args);')
text=text.replace('comparison<3','comparison<2')
out=STAGE/'test_timeline_step_resume_probe.cpp';assert not out.exists();out.write_text(text,encoding='utf8',newline='\n')
print('Frozen typed per-step probe; no timing data read')
