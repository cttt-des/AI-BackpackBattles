#pragma once
#include "native_inline_dispatch.hpp"
#include "native_scalar_equal.hpp"
#include "native_array_index.hpp"
namespace gd { static thread_local uint64_t native_motion_index_counts[3]{}; }
gd::GdVal candidate_tickMotion(Gd__gd_core__CoreContext& context,const gd::GdVal* _args,int _argc) {
    gd::BattleCtx& gd_ctx = *context.rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (context.f__motion_queue.kind == gd::GdVal::Kind::Arr && context.f__motion_queue.arr) {
    const bool native_collect = gd_ctx.native_resolved_collect;
    if (native_collect) ++gd::native_motion_index_counts[0];
    const uint32_t native_limit = static_cast<uint32_t>(gd::native_inline_call(gd_ctx, context.f__motion_queue, gd::SYM_size, nullptr, 0).as_int());
    uint32_t native_read = 0;
    uint32_t native_write = 0;
    while (native_read < native_limit) {
        if (native_collect) ++gd::native_motion_index_counts[1];
        gd::GdVal lv_entry = gd::native_array_index(gd_ctx, context.f__motion_queue, gd::GdVal::from_int(native_read));
        bool native_keep = false;
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(0LL)), gd::GdVal::from_int(0LL))))) {
            gd::GdVal lv_character = gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(1LL));
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN__visual_generation_1125), gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(2LL))))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN__visual_kind_1123), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::native_inline_call(gd_ctx, lv_character, SYM_GEN_tickVisualMotion_1137, _ca, 1); })();
                native_keep = gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN__visual_kind_1123), gd::GdVal::from_int(0LL));
            }
        }
        else {
            gd::GdVal lv_charge = gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(2LL));
            (void)([&]() { gd::GdVal _ca[] = {lv_charge, lv_delta}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(1LL)), SYM_GEN__tickChargePath_506, _ca, 2); })();
            native_keep = gd::gd_truth(gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_active_1653));
        }
        if (native_keep) {
            if (native_collect) ++gd::native_motion_index_counts[2];
            if (native_write != native_read) {
                { gd::GdVal _t1186 = context.f__motion_queue; gd::GdVal _t1187 = gd::GdVal::from_int(native_write); gd::native_array_set_index(gd_ctx, _t1186, _t1187, lv_entry); }
            }
            ++native_write;
        }
        ++native_read;
    }
    gd::GdVal lv_limit = gd::GdVal::from_int(native_limit);
    gd::GdVal lv_read = gd::GdVal::from_int(native_read);
    gd::GdVal lv_write = gd::GdVal::from_int(native_write);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_write, lv_limit)))) {
        gd::GdVal lv_end = gd::native_inline_call(gd_ctx, context.f__motion_queue, gd::SYM_size, nullptr, 0);
        while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_read, lv_end)))) {
            { gd::GdVal _t1188 = context.f__motion_queue; gd::GdVal _t1189 = lv_write; gd::native_array_set_index(gd_ctx, _t1188, _t1189, gd::native_array_index(gd_ctx, context.f__motion_queue, lv_read)); }
            lv_write = gd::gd_add(gd_ctx, lv_write, gd::GdVal::from_int(1LL));
            lv_read = gd::gd_add(gd_ctx, lv_read, gd::GdVal::from_int(1LL));
        }
        (void)([&]() { gd::GdVal _ca[] = {lv_write}; return gd::native_inline_call(gd_ctx, context.f__motion_queue, gd::SYM_resize, _ca, 1); })();
    }
    return gd::GdVal::null();
    }
    gd::GdVal lv_limit = gd::native_inline_call(gd_ctx, context.f__motion_queue, gd::SYM_size, nullptr, 0);
    gd::GdVal lv_read = gd::GdVal::from_int(0LL);
    gd::GdVal lv_write = gd::GdVal::from_int(0LL);
    while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_read, lv_limit)))) {
        gd::GdVal lv_entry = gd::native_array_index(gd_ctx, context.f__motion_queue, lv_read);
        gd::GdVal lv_keep = gd::GdVal::from_bool(false);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(0LL)), gd::GdVal::from_int(0LL))))) {
            gd::GdVal lv_character = gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(1LL));
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN__visual_generation_1125), gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(2LL))))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN__visual_kind_1123), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::native_inline_call(gd_ctx, lv_character, SYM_GEN_tickVisualMotion_1137, _ca, 1); })();
                lv_keep = gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN__visual_kind_1123), gd::GdVal::from_int(0LL)));
            }
        }
        else {
            gd::GdVal lv_charge = gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(2LL));
            (void)([&]() { gd::GdVal _ca[] = {lv_charge, lv_delta}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(1LL)), SYM_GEN__tickChargePath_506, _ca, 2); })();
            lv_keep = gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_active_1653);
        }
        if (gd::gd_truth(lv_keep)) {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_write, lv_read)))) {
                { gd::GdVal _t1186 = context.f__motion_queue; gd::GdVal _t1187 = lv_write; gd::native_array_set_index(gd_ctx, _t1186, _t1187, lv_entry); }
            }
            lv_write = gd::gd_add(gd_ctx, lv_write, gd::GdVal::from_int(1LL));
        }
        lv_read = gd::gd_add(gd_ctx, lv_read, gd::GdVal::from_int(1LL));
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_write, lv_limit)))) {
        gd::GdVal lv_end = gd::native_inline_call(gd_ctx, context.f__motion_queue, gd::SYM_size, nullptr, 0);
        while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_read, lv_end)))) {
            { gd::GdVal _t1188 = context.f__motion_queue; gd::GdVal _t1189 = lv_write; gd::native_array_set_index(gd_ctx, _t1188, _t1189, gd::native_array_index(gd_ctx, context.f__motion_queue, lv_read)); }
            lv_write = gd::gd_add(gd_ctx, lv_write, gd::GdVal::from_int(1LL));
            lv_read = gd::gd_add(gd_ctx, lv_read, gd::GdVal::from_int(1LL));
        }
        (void)([&]() { gd::GdVal _ca[] = {lv_write}; return gd::native_inline_call(gd_ctx, context.f__motion_queue, gd::SYM_resize, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal reference_tickMotion(Gd__gd_core__CoreContext& context,const gd::GdVal* _args,int _argc) {
    gd::BattleCtx& gd_ctx = *context.rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    gd::GdVal lv_limit = gd::native_inline_call(gd_ctx, context.f__motion_queue, gd::SYM_size, nullptr, 0);
    gd::GdVal lv_read = gd::GdVal::from_int(0LL);
    gd::GdVal lv_write = gd::GdVal::from_int(0LL);
    while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_read, lv_limit)))) {
        gd::GdVal lv_entry = gd::native_array_index(gd_ctx, context.f__motion_queue, lv_read);
        gd::GdVal lv_keep = gd::GdVal::from_bool(false);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(0LL)), gd::GdVal::from_int(0LL))))) {
            gd::GdVal lv_character = gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(1LL));
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN__visual_generation_1125), gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(2LL))))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN__visual_kind_1123), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::native_inline_call(gd_ctx, lv_character, SYM_GEN_tickVisualMotion_1137, _ca, 1); })();
                lv_keep = gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN__visual_kind_1123), gd::GdVal::from_int(0LL)));
            }
        }
        else {
            gd::GdVal lv_charge = gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(2LL));
            (void)([&]() { gd::GdVal _ca[] = {lv_charge, lv_delta}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(1LL)), SYM_GEN__tickChargePath_506, _ca, 2); })();
            lv_keep = gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_active_1653);
        }
        if (gd::gd_truth(lv_keep)) {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_write, lv_read)))) {
                { gd::GdVal _t1186 = context.f__motion_queue; gd::GdVal _t1187 = lv_write; gd::native_array_set_index(gd_ctx, _t1186, _t1187, lv_entry); }
            }
            lv_write = gd::gd_add(gd_ctx, lv_write, gd::GdVal::from_int(1LL));
        }
        lv_read = gd::gd_add(gd_ctx, lv_read, gd::GdVal::from_int(1LL));
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_write, lv_limit)))) {
        gd::GdVal lv_end = gd::native_inline_call(gd_ctx, context.f__motion_queue, gd::SYM_size, nullptr, 0);
        while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_read, lv_end)))) {
            { gd::GdVal _t1188 = context.f__motion_queue; gd::GdVal _t1189 = lv_write; gd::native_array_set_index(gd_ctx, _t1188, _t1189, gd::native_array_index(gd_ctx, context.f__motion_queue, lv_read)); }
            lv_write = gd::gd_add(gd_ctx, lv_write, gd::GdVal::from_int(1LL));
            lv_read = gd::gd_add(gd_ctx, lv_read, gd::GdVal::from_int(1LL));
        }
        (void)([&]() { gd::GdVal _ca[] = {lv_write}; return gd::native_inline_call(gd_ctx, context.f__motion_queue, gd::SYM_resize, _ca, 1); })();
    }
    return gd::GdVal::null();
}
