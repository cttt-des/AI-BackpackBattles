#pragma once
#pragma STDC FP_CONTRACT OFF
#include "../../gd_rt.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__CoreEvent : public gd::GdObj {
    explicit Gd__gd_core__CoreEvent(gd::BattleCtx* ctx) : gd::GdObj(ctx) {}
    gd::GdVal f_id;
    gd::GdVal f_timestamp;
    gd::GdVal f_parentEvent;
    gd::GdVal f_origin;
    gd::GdVal f_type;
    gd::GdVal f_target;
    gd::GdVal f_params;
    gd::GdVal f_formatParams;
    gd::GdVal fn__init(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getType(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_setTarget(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_setParam(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getParam(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getAmount(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getAmountWithDefault(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_hasParam(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getMainActor(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getOrigin(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_fromCharacter(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getDepth(const gd::GdVal* _args, int _argc);
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
