namespace {
// These helpers belong only to CoreBuff's native gain path. Unknown operand
// domains and overflow execute the original runtime operation exactly once.
__attribute__((always_inline)) inline gd::GdVal native_buff_integer_add(gd::BattleCtx& ctx,const gd::GdVal& a,const gd::GdVal& b) {
    if(a.kind==gd::GdVal::Kind::Int && b.kind==gd::GdVal::Kind::Int) {
        int64_t value;if(!__builtin_add_overflow(a.i,b.i,&value))return gd::GdVal::from_int(value);
    }
    return gd::gd_add(ctx,a,b);
}
__attribute__((always_inline)) inline gd::GdVal native_buff_integer_sub(const gd::GdVal& a,const gd::GdVal& b) {
    if(a.kind==gd::GdVal::Kind::Int && b.kind==gd::GdVal::Kind::Int) {
        int64_t value;if(!__builtin_sub_overflow(a.i,b.i,&value))return gd::GdVal::from_int(value);
    }
    return gd::gd_sub(a,b);
}
__attribute__((always_inline)) inline gd::GdVal native_buff_integer_min(const gd::GdVal& a,const gd::GdVal& b) {
    if(a.kind==gd::GdVal::Kind::Int && b.kind==gd::GdVal::Kind::Int)return gd::GdVal::from_int(a.i<b.i?a.i:b.i);
    return gd::gd_min(a,b);
}
__attribute__((always_inline)) inline gd::GdVal native_buff_integer_coerce(const gd::GdVal& a) {
    if(a.kind==gd::GdVal::Kind::Int)return gd::GdVal::from_int(a.i);
    return gd::GdVal::from_int(gd::gd_coerce_int(a).i);
}
__attribute__((always_inline)) inline gd::GdVal native_buff_boolean_coerce(const gd::GdVal& a) {
    if(a.kind==gd::GdVal::Kind::Bool)return gd::GdVal::from_bool(a.b);
    return gd::GdVal::from_bool(gd::gd_coerce_bool(a).b);
}
__attribute__((always_inline)) inline bool native_buff_integer_positive(const gd::GdVal& a,const gd::GdVal& b) {
    // Original comparisons convert Int to double. Outside the exact range,
    // retain those conversions (and their floating exception flags).
    constexpr uint64_t limit=UINT64_C(1)<<53;
    if(a.kind==gd::GdVal::Kind::Int && b.kind==gd::GdVal::Kind::Int &&
       uint64_t(a.i)+limit<=2*limit && uint64_t(b.i)+limit<=2*limit)return a.i>b.i;
    return gd::gd_gt(a,b);
}
}
