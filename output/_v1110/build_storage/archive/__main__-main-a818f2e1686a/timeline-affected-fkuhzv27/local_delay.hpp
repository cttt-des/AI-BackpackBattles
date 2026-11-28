gd::GdVal local_delay(Context* self,const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *self->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    gd::GdVal lv_limit = gd::native_inline_call(gd_ctx, self->f__timed, gd::SYM_size, nullptr, 0);
    gd::GdVal lv_read = gd::GdVal::from_int(0LL);
    gd::GdVal lv_write = gd::GdVal::from_int(0LL);
    while (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(lv_read, lv_limit)))) {
        gd::GdVal lv_entry = gd::native_array_index(gd_ctx, self->f__timed, lv_read);
        { gd::GdVal _t1123 = lv_entry; gd::GdVal _t1124 = gd::GdVal::from_int(2LL); gd::native_array_set_index(gd_ctx, _t1123, _t1124, ([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(2LL)), lv_delta)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreContext::call_static_fn(gd_ctx, SYM_GEN__nativeF32_1502, _ca, 1, _out); return _out; })()); }
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(2LL)), gd::GdVal::from_float(0.0))))) {
            if (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(self->f_fight_ended))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(!(gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(0LL))).is_null()))) : gd::GdVal::from_bool(false)))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(1LL)), gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(3LL))}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(0LL)), gd::SYM_callv, _ca, 2); })();
            }
        }
        else {
            if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_write, lv_read)))) {
                { gd::GdVal _t1125 = self->f__timed; gd::GdVal _t1126 = lv_write; gd::native_array_set_index(gd_ctx, _t1125, _t1126, lv_entry); }
            }
            lv_write = gd::gd_add(gd_ctx, lv_write, gd::GdVal::from_int(1LL));
        }
        lv_read = gd::gd_add(gd_ctx, lv_read, gd::GdVal::from_int(1LL));
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_write, lv_limit)))) {
        gd::GdVal lv_end = gd::native_inline_call(gd_ctx, self->f__timed, gd::SYM_size, nullptr, 0);
        while (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(lv_read, lv_end)))) {
            { gd::GdVal _t1127 = self->f__timed; gd::GdVal _t1128 = lv_write; gd::native_array_set_index(gd_ctx, _t1127, _t1128, gd::native_array_index(gd_ctx, self->f__timed, lv_read)); }
            lv_write = gd::gd_add(gd_ctx, lv_write, gd::GdVal::from_int(1LL));
            lv_read = gd::gd_add(gd_ctx, lv_read, gd::GdVal::from_int(1LL));
        }
        (void)([&]() { gd::GdVal _ca[] = {lv_write}; return gd::native_inline_call(gd_ctx, self->f__timed, gd::SYM_resize, _ca, 1); })();
    }
    return gd::GdVal::null();
}
