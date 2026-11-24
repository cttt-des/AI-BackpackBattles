#pragma once
#include "preflight_label.hpp"
inline void original_buff_diagnostic(unsigned site,Gd__gd_core__CoreBuff& buff,const gd::GdVal& lv_duration,const gd::GdVal& lv_farthestIndex,const gd::GdVal& lv_farthest,const gd::GdVal& lv_delay,const gd::GdVal& lv_earliestTimeout) {
    auto& gd_ctx=*buff.rt_ctx_;
    switch(site) {
        case 72: {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[72]), ([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return buff.fn__blnd_snap(_ca, 2); })();
            break;
        }
        case 75: {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[75]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_farthestIndex}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::GdVal::from_str(&battle_string_literals[76])), ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_farthest, SYM_GEN_amount_1041)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return buff.fn__blnd_snap(_ca, 2); })();
            break;
        }
        case 77: {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[77]), ([&]() { gd::GdVal _ca[] = {lv_farthestIndex}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return buff.fn__blnd_snap(_ca, 2); })();
            break;
        }
        case 88: {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[88]), ([&]() { gd::GdVal _ca[] = {buff.f_nextTemporaryTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return buff.fn__blnd_snap(_ca, 2); })();
            break;
        }
        case 89: {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[89]), ([&]() { gd::GdVal _ca[] = {buff.f_nextTemporaryTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return buff.fn__blnd_snap(_ca, 2); })();
            break;
        }
        case 90: {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[90]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[91]), ([&]() { gd::GdVal _ca[] = {lv_delay}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[92])), ([&]() { gd::GdVal _ca[] = {lv_earliestTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[93])), ([&]() { gd::GdVal _ca[] = {native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_time>(gd_ctx, buff.f_ctx, SYM_GEN_time_1411)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return buff.fn__blnd_snap(_ca, 2); })();
            break;
        }
    }
}
inline void candidate_buff_diagnostic(unsigned site,Gd__gd_core__CoreBuff& buff,const gd::GdVal& lv_duration,const gd::GdVal& lv_farthestIndex,const gd::GdVal& lv_farthest,const gd::GdVal& lv_delay,const gd::GdVal& lv_earliestTimeout) {
    auto& gd_ctx=*buff.rt_ctx_;
    switch(site) {
        case 72: {
            if(!gd::native_skip_buff_diagnostic(gd_ctx,buff,{lv_duration})) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[72]), ([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return buff.fn__blnd_snap(_ca, 2); })();
            }
            break;
        }
        case 75: {
            if(!gd::native_skip_buff_farthest_diagnostic(gd_ctx,buff,lv_farthestIndex,lv_farthest)) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[75]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_farthestIndex}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::GdVal::from_str(&battle_string_literals[76])), ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_farthest, SYM_GEN_amount_1041)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return buff.fn__blnd_snap(_ca, 2); })();
            }
            break;
        }
        case 77: {
            if(!gd::native_skip_buff_diagnostic(gd_ctx,buff,{lv_farthestIndex})) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[77]), ([&]() { gd::GdVal _ca[] = {lv_farthestIndex}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return buff.fn__blnd_snap(_ca, 2); })();
            }
            break;
        }
        case 88: {
            if(!gd::native_skip_buff_diagnostic(gd_ctx,buff,{buff.f_nextTemporaryTimeout})) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[88]), ([&]() { gd::GdVal _ca[] = {buff.f_nextTemporaryTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return buff.fn__blnd_snap(_ca, 2); })();
            }
            break;
        }
        case 89: {
            if(!gd::native_skip_buff_diagnostic(gd_ctx,buff,{buff.f_nextTemporaryTimeout})) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[89]), ([&]() { gd::GdVal _ca[] = {buff.f_nextTemporaryTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return buff.fn__blnd_snap(_ca, 2); })();
            }
            break;
        }
        case 90: {
            if(!gd::native_skip_buff_timeout_diagnostic(gd_ctx,buff,lv_delay,lv_earliestTimeout)) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[90]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[91]), ([&]() { gd::GdVal _ca[] = {lv_delay}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[92])), ([&]() { gd::GdVal _ca[] = {lv_earliestTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[93])), ([&]() { gd::GdVal _ca[] = {native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_time>(gd_ctx, buff.f_ctx, SYM_GEN_time_1411)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return buff.fn__blnd_snap(_ca, 2); })();
            }
            break;
        }
    }
}
