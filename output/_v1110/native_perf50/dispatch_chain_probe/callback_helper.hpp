namespace gd {
void native_dispatch_chain_hit(unsigned);
inline bool native_try_flat_funcref(BattleCtx& ctx,const GdVal& value,const GdVal& arguments,GdVal& out) {
    if(!ctx.native_resolved_dispatch || value.kind!=GdVal::Kind::FuncRef || !value.fr)return false;
    const auto* reference=value.fr;
    if(!reference->instance || reference->method==SYM_NONE || (reference->binds && reference->binds->len))return false;
    const auto method=reference->method;
    const int slot=method<native_resolved_slots.size()?native_resolved_slots[method]:-1;
    if(slot<0)return false;
    auto* object=reference->instance;const auto* row=object->native_call_row_;
    if(!row || (ctx.native_resolved_audit && !native_resolved_row_matches(object,row)))return false;
    const auto function=row->methods[slot];if(!function)return false;
    const GdVal* args=nullptr;int count=0;
    if(arguments.kind==GdVal::Kind::Arr && arguments.arr){args=arguments.arr->data;count=static_cast<int>(arguments.arr->len);}
    if(ctx.native_resolved_collect){++ctx.native_resolved_counts[1];if(slot>=112)native_inline_hot_slot_hit(0);native_dispatch_chain_hit(3);}
    out=function(object,args,count);return true;
}
}
