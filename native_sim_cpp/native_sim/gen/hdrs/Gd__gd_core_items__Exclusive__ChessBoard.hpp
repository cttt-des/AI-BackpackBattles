#pragma once
#pragma STDC FP_CONTRACT OFF
#include "Gd__gd_core_items__Item.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core_items__Exclusive__ChessBoard : public Gd__gd_core_items__Item {
    explicit Gd__gd_core_items__Exclusive__ChessBoard(gd::BattleCtx* ctx) : Gd__gd_core_items__Item(ctx) {}
    gd::GdVal f_activeBlackPieces;
    gd::GdVal f_activeWhitePieces;
    gd::GdVal f_originCells;
    gd::GdVal f_turnColor;
    gd::GdVal f_goldCost;
    gd::GdVal f_blackPieces;
    gd::GdVal f_whitePieces;
    gd::GdVal f_chessMasterDescr;
    gd::GdVal fn_onBought(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onAddToInventory(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onItemAdded(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onItemRemoved(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getPiecesForColor(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onPrepare(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_doCooldownEffect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_findPieceToCapture(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_findBestPieceToCapture(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_capture(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_findSpaceToMove(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_movePiece(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_resetPieces(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getGatedDescriptor(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getRelatedItemHeight(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__readyInit(const gd::GdVal* _args, int _argc);
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
