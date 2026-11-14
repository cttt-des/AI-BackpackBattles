#pragma once
#pragma STDC FP_CONTRACT OFF
#include "../../gd_rt.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__CoreUtil : public gd::GdObj {
    explicit Gd__gd_core__CoreUtil(gd::BattleCtx* ctx) : gd::GdObj(ctx) {}
    gd::GdVal f_rng;
    gd::GdVal f__ctx;
    gd::GdVal fn__init(const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_truth(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_vec2_tile_data(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_vec2_less_yx(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_dictAdd(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_dictSub(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_dictAddDict(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_dictAppend(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_dictErase(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_sortDict(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    gd::GdVal fn_roll(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_flip(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_flipPercent(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_flipRound(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_flipWeighted(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_pickRandomElement(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getArrayElement(const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_changeTimer(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    gd::GdVal fn_callNextFrame(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_callDelayed(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_callDelayed_process(const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_arrayAsIndexDict(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_invertDictionary(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_filterDuplicates(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_countDuplicates(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_flatten(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_rotDif(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_isItemDescriptor(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_eassert(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_eprint(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    const gd::GdClassMeta* meta() const override;
    void init_fields(gd::BattleCtx& gd_ctx) override;
    bool get_prop(gd::SymId prop, gd::GdVal& out) const override;
    bool set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) override;
    bool has_own_method(gd::SymId m) const override;
    bool call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) override;
    static gd::GdVal get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop);
    static bool get_static_prop_fn(gd::SymId prop, gd::GdVal& out);
    static bool call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out);
};
