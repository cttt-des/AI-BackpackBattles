#pragma once
#pragma STDC FP_CONTRACT OFF
#include "../../gd_rt.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__CoreEventBus : public gd::GdObj {
    explicit Gd__gd_core__CoreEventBus(gd::BattleCtx* ctx) : gd::GdObj(ctx) {}
    gd::GdVal f_loggingMode;
    gd::GdVal f_signalQueue;
    gd::GdVal f_connections;
    gd::GdVal f_signalIDs;
    gd::GdVal f__ctx;
    gd::GdVal fn_setLoggingMode(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getLoggingMode(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_queueSignal(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_flushLoggingQueue(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_emitSignal(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_emitEvent(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_logEvent(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_emitAndLog(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_connectEvent(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getEmissionID(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_disconnectAll(const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_Util_dictAppend(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
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
