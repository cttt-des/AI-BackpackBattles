#pragma once
#include "native_event_kernel.hpp"
#include "native_array_index.hpp"
#include "static_setup_helper.hpp"
#include "gen/hdrs/Gd__gd_core__Bag.hpp"
#include "gen/hdrs/Gd__gd_core__CoreBuff.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCombat.hpp"
#include "gen/hdrs/Gd__gd_core__CoreConst.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreDamageSource.hpp"
#include "gen/hdrs/Gd__gd_core__CoreEvent.hpp"
#include "gen/hdrs/Gd__gd_core__CoreEventBus.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItemData.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng__INNER__BalancedRng.hpp"
#include "gen/hdrs/Gd__gd_core__CoreUtil.hpp"
#include "gen/hdrs/Gd__gd_core__Crown.hpp"
#include "gen/hdrs/Gd__gd_core__DjinnLamp.hpp"
#include "gen/hdrs/Gd__gd_core__HolySpear.hpp"
#include "gen/hdrs/Gd__gd_core__Item.hpp"
#include "gen/hdrs/Gd__gd_core_items__Bag.hpp"
#include "gen/hdrs/Gd__gd_core_items__Crown.hpp"
#include "gen/hdrs/Gd__gd_core_items__DjinnLamp.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chainsaw.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ChessMaster.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__ChessPiece.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Eat_o_matic.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__FrogPrince.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__KingGoobert.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Laboratory.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Lootbox.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MagicRing.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PortableAltar.hpp"
#include "gen/hdrs/Gd__gd_core_items__Gems__Gem.hpp"
#include "gen/hdrs/Gd__gd_core_items__HolySpear.hpp"
#include "gen/hdrs/Gd__gd_core_items__Item.hpp"
struct StaticCase {const gd::GdClassMeta* meta; gd::SymId prop; bool (*candidate)(gd::BattleCtx&,gd::SymId,gd::GdVal&); bool fast;};
inline bool candidate_Gd__gd_core__CoreItem(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_BASE_CRIT_SEVERITY_0: out = Gd__gd_core__CoreItem::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_cdEncodingFactor_1: out = Gd__gd_core__CoreItem::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_CoreElectricalCharge_507: out = Gd__gd_core__CoreItem::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_CoreSignalConnection_508: out = Gd__gd_core__CoreItem::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__CoreItem::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core__CoreBuff(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_TemporaryStacks_1040: out = Gd__gd_core__CoreBuff::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__CoreBuff::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core_items__Crown(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_CrownState_1822: out = Gd__gd_core_items__Crown::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core_items__Crown::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core_items__Exclusive__ChessMaster(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_firstKnightRound_2176: out = Gd__gd_core_items__Exclusive__ChessMaster::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_firstRookRound_2177: out = Gd__gd_core_items__Exclusive__ChessMaster::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_firstQueenRound_2178: out = Gd__gd_core_items__Exclusive__ChessMaster::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core_items__Exclusive__ChessMaster::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core__Item(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_Owner_854: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Type_855: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Priority_856: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_CraftingPriority_857: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Tag_858: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Stack_859: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Mat_860: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Physics_861: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Rarity_862: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_FaceDirection_863: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_StatModified_864: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_DropResult_865: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_PickupType_866: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Affected_867: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Tiles_868: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_ActivationAni_869: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Stat_870: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_StackChangeType_871: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_offset_516: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_impulse_517: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_momentumFactor_518: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_DRAG_PRIORITY_527: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_angleStep_585: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_moveRotationMouseFactor_588: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_backforce_589: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_fric_590: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_maxAngle_591: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_moveRotationSpeed_592: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_MISS_OFFSET_602: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_PRE_FUSE_DUR_603: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_PRE_FUSE_DUR_COG_604: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_FUSE_DUR_605: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_TRANSFORMATION_DUR_606: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_SignalConnection_877: out = Gd__gd_core__Item::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__Item::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core__HolySpear(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_SpearState_1902: out = Gd__gd_core__HolySpear::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__HolySpear::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core_items__Exclusive__PortableAltar(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_valueFactor_2434: out = Gd__gd_core_items__Exclusive__PortableAltar::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core_items__Exclusive__PortableAltar::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core__CoreCharacter(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_ID_1297: out = Gd__gd_core__CoreCharacter::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Stat_870: out = Gd__gd_core__CoreCharacter::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_StaminaResult_1298: out = Gd__gd_core__CoreCharacter::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_AUTO_RAGE_DELAY_1044: out = Gd__gd_core__CoreCharacter::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_AUTO_RAGE_DUR_1045: out = Gd__gd_core__CoreCharacter::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__CoreCharacter::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core__CoreItemData(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_ReleaseState_1727: out = Gd__gd_core__CoreItemData::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__CoreItemData::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core_items__Exclusive__Chess__ChessPiece(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_PieceColor_2150: out = Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core_items__Exclusive__FrogPrince(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_FrogState_2277: out = Gd__gd_core_items__Exclusive__FrogPrince::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core_items__Exclusive__FrogPrince::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core__CoreCombat(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_RoundResult_1340: out = Gd__gd_core__CoreCombat::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_FATIGUE_TIME_1299: out = Gd__gd_core__CoreCombat::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_FATIGUE_START_DELAY_1300: out = Gd__gd_core__CoreCombat::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_FATIGUE_SLOW_TIME_1301: out = Gd__gd_core__CoreCombat::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_CoreItemSort_1344: out = Gd__gd_core__CoreCombat::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__CoreCombat::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core__CoreRng(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_BalancedRng_1749: out = Gd__gd_core__CoreRng::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_BalancedRange_1750: out = Gd__gd_core__CoreRng::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__CoreRng::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core_items__Exclusive__Lootbox(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_OFFSET_2353: out = Gd__gd_core_items__Exclusive__Lootbox::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core_items__Exclusive__Lootbox::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core__CoreRng__INNER__BalancedRng(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_luckBalance_1758: out = Gd__gd_core__CoreRng__INNER__BalancedRng::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__CoreRng__INNER__BalancedRng::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core_items__Exclusive__Eat_o_matic(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_ArmState_2236: out = Gd__gd_core_items__Exclusive__Eat_o_matic::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_SLOW_SPEED_2228: out = Gd__gd_core_items__Exclusive__Eat_o_matic::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_FAST_SPEED_2229: out = Gd__gd_core_items__Exclusive__Eat_o_matic::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core_items__Exclusive__Eat_o_matic::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core_items__HolySpear(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_SpearState_1902: out = Gd__gd_core_items__HolySpear::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core_items__HolySpear::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core_items__Item(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_Owner_854: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Type_855: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Priority_856: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_CraftingPriority_857: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Tag_858: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Stack_859: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Mat_860: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Physics_861: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Rarity_862: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_FaceDirection_863: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_StatModified_864: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_DropResult_865: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_PickupType_866: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Affected_867: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Tiles_868: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_ActivationAni_869: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Stat_870: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_StackChangeType_871: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_offset_516: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_impulse_517: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_momentumFactor_518: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_DRAG_PRIORITY_527: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_angleStep_585: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_moveRotationMouseFactor_588: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_backforce_589: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_fric_590: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_maxAngle_591: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_moveRotationSpeed_592: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_MISS_OFFSET_602: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_PRE_FUSE_DUR_603: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_PRE_FUSE_DUR_COG_604: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_FUSE_DUR_605: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_TRANSFORMATION_DUR_606: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_SignalConnection_877: out = Gd__gd_core_items__Item::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core_items__Item::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core__CoreConst(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_EventType_1395: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_ItemMetrics_1396: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_CharID_1397: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_StaminaResult_1298: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_ItemStat_1398: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Rarity_862: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_StuffedClasses_1399: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Owner_854: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_GameMode_1400: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Affected_867: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Stack_859: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Tag_858: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Priority_856: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_StackChangeType_871: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_StatModified_864: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_FaceDirection_863: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Classes_1401: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Classes_Full_1402: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Type_855: out = Gd__gd_core__CoreConst::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__CoreConst::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core__CoreContext(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_PHYSICS_FPS_1403: out = Gd__gd_core__CoreContext::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_PHYSICS_DELTA_1404: out = Gd__gd_core__CoreContext::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_COMBAT_DELAY_1405: out = Gd__gd_core__CoreContext::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_FATIGUE_TIME_1299: out = Gd__gd_core__CoreContext::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_CRITICAL_SHAKE_WINDOW_1456: out = Gd__gd_core__CoreContext::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_NativeFlicker_1509: out = Gd__gd_core__CoreContext::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__CoreContext::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core__CoreUtil(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_DictSorter_1808: out = Gd__gd_core__CoreUtil::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__CoreUtil::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core__DjinnLamp(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_numIngredients_1856: out = Gd__gd_core__DjinnLamp::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__DjinnLamp::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core_items__Bag(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_BagTiles_933: out = Gd__gd_core_items__Bag::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core_items__Bag::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core_items__Exclusive__KingGoobert(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_CrownState_1822: out = Gd__gd_core_items__Exclusive__KingGoobert::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core_items__Exclusive__KingGoobert::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core__Bag(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_BagTiles_933: out = Gd__gd_core__Bag::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__Bag::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core_items__Gems__Gem(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_GemMode_994: out = Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core_items__Gems__Gem::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core__CoreDamageSource(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_Type_855: out = Gd__gd_core__CoreDamageSource::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_Flags_1565: out = Gd__gd_core__CoreDamageSource::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_chipDamageFlags_1536: out = Gd__gd_core__CoreDamageSource::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_meleeFlags_1537: out = Gd__gd_core__CoreDamageSource::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_rangedFlags_1538: out = Gd__gd_core__CoreDamageSource::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__CoreDamageSource::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core_items__DjinnLamp(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_numIngredients_1856: out = Gd__gd_core_items__DjinnLamp::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core_items__DjinnLamp::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core_items__Exclusive__MagicRing(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_TriggerType_2385: out = Gd__gd_core_items__Exclusive__MagicRing::get_static_const_or_enum(scratch,prop); return true;
    case SYM_GEN_RingEffect_2386: out = Gd__gd_core_items__Exclusive__MagicRing::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core_items__Exclusive__MagicRing::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core__CoreEvent(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_Target_1583: out = Gd__gd_core__CoreEvent::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__CoreEvent::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core_items__Exclusive__Laboratory(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_DUR_2341: out = Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core_items__Exclusive__Laboratory::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core__CoreEventBus(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_LoggingMode_1599: out = Gd__gd_core__CoreEventBus::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__CoreEventBus::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core__Crown(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_CrownState_1822: out = Gd__gd_core__Crown::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core__Crown::get_static_prop_fn(prop,out);
    }
}
inline bool candidate_Gd__gd_core_items__Exclusive__Chainsaw(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {
    switch(prop) {
    case SYM_GEN_sawSpeed_2122: out = Gd__gd_core_items__Exclusive__Chainsaw::get_static_const_or_enum(scratch,prop); return true;
    default: return Gd__gd_core_items__Exclusive__Chainsaw::get_static_prop_fn(prop,out);
    }
}
inline std::vector<StaticCase> static_cases(){return {
{&META_Gd__gd_core__CoreItem,SYM_GEN_BASE_CRIT_SEVERITY_0,candidate_Gd__gd_core__CoreItem,true},
{&META_Gd__gd_core__CoreItem,SYM_GEN_cdEncodingFactor_1,candidate_Gd__gd_core__CoreItem,true},
{&META_Gd__gd_core__CoreItem,SYM_GEN_SELF_BEHAVIOR_METHODS_61,candidate_Gd__gd_core__CoreItem,false},
{&META_Gd__gd_core__CoreItem,SYM_GEN_CoreElectricalCharge_507,candidate_Gd__gd_core__CoreItem,true},
{&META_Gd__gd_core__CoreItem,SYM_GEN_CoreSignalConnection_508,candidate_Gd__gd_core__CoreItem,true},
{&META_Gd__gd_core__CoreItem,gd::SymId(0),candidate_Gd__gd_core__CoreItem,false},
{&META_Gd__gd_core__CoreItem,gd::SymId(0xffffffffu),candidate_Gd__gd_core__CoreItem,false},
{&META_Gd__gd_core__BloodGoobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__BloodGoobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreBuff,SYM_GEN_TemporaryStacks_1040,candidate_Gd__gd_core__CoreBuff,true},
{&META_Gd__gd_core__CoreBuff,gd::SymId(0),candidate_Gd__gd_core__CoreBuff,false},
{&META_Gd__gd_core__CoreBuff,gd::SymId(0xffffffffu),candidate_Gd__gd_core__CoreBuff,false},
{&META_Gd__gd_core__CoreItem__INNER__CoreSignalConnection,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CoreItem__INNER__CoreSignalConnection,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__DancingDragon,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__DancingDragon,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__FannyPack,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__FannyPack,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__HolyArmor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__HolyArmor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__ManaOrb,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__ManaOrb,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__PoisonGoobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__PoisonGoobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__SpectralDagger,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__SpectralDagger,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__StoneSkinPotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__StoneSkinPotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__WoodenSword,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__WoodenSword,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Dagger,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Dagger,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Crown,SYM_GEN_CrownState_1822,candidate_Gd__gd_core_items__Crown,true},
{&META_Gd__gd_core_items__Crown,gd::SymId(0),candidate_Gd__gd_core_items__Crown,false},
{&META_Gd__gd_core_items__Crown,gd::SymId(0xffffffffu),candidate_Gd__gd_core_items__Crown,false},
{&META_Gd__gd_core_items__Exclusive__AmethystWhelp,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmethystWhelp,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ArmoredCouragePuppy,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ArmoredCouragePuppy,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Bewitchment,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Bewitchment,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BrassKnuckles,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BrassKnuckles,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Cheese,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Cheese,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ChessMaster,SYM_GEN_firstKnightRound_2176,candidate_Gd__gd_core_items__Exclusive__ChessMaster,true},
{&META_Gd__gd_core_items__Exclusive__ChessMaster,SYM_GEN_firstRookRound_2177,candidate_Gd__gd_core_items__Exclusive__ChessMaster,true},
{&META_Gd__gd_core_items__Exclusive__ChessMaster,SYM_GEN_firstQueenRound_2178,candidate_Gd__gd_core_items__Exclusive__ChessMaster,true},
{&META_Gd__gd_core_items__Exclusive__ChessMaster,gd::SymId(0),candidate_Gd__gd_core_items__Exclusive__ChessMaster,false},
{&META_Gd__gd_core_items__Exclusive__ChessMaster,gd::SymId(0xffffffffu),candidate_Gd__gd_core_items__Exclusive__ChessMaster,false},
{&META_Gd__gd_core_items__Exclusive__Daggerang,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Daggerang,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DragonscaleArmor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DragonscaleArmor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Everburning,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Everburning,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FriendlyFire,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FriendlyFire,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Hardwood,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Hardwood,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__InnerPower,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__InnerPower,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LightningStaff,SYM_GEN_chargeCells_2055,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LightningStaff,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LightningStaff,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Markswoman,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Markswoman,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__OilLamp,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__OilLamp,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Pop,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Pop,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RainbowGoobertEngineer,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RainbowGoobertEngineer,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SapphireEgg,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SapphireEgg,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SliceofBread,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SliceofBread,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpellScrollIce,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpellScrollIce,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StoneBadge,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StoneBadge,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ThunderDrake,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ThunderDrake,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Wand,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Wand,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__FlyAgaric,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__FlyAgaric,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__HeroicPotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__HeroicPotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__ManaOrb,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__ManaOrb,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__ProtectivePurse,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__ProtectivePurse,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__StrongDemonicFlask,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__StrongDemonicFlask,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__WoodenSword,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__WoodenSword,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Item,SYM_GEN_Owner_854,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_Type_855,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_Priority_856,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_CraftingPriority_857,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_Tag_858,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_Stack_859,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_Mat_860,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_Physics_861,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_Rarity_862,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_FaceDirection_863,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_StatModified_864,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_DropResult_865,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_PickupType_866,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_Affected_867,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_Tiles_868,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_ActivationAni_869,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_Stat_870,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_StackChangeType_871,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_affectedColorToTileId_509,candidate_Gd__gd_core__Item,false},
{&META_Gd__gd_core__Item,SYM_GEN_rarityColors_511,candidate_Gd__gd_core__Item,false},
{&META_Gd__gd_core__Item,SYM_GEN_offset_516,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_impulse_517,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_momentumFactor_518,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_affectedSoundsVolume_521,candidate_Gd__gd_core__Item,false},
{&META_Gd__gd_core__Item,SYM_GEN_cellSize_522,candidate_Gd__gd_core__Item,false},
{&META_Gd__gd_core__Item,SYM_GEN_halfCellSize_523,candidate_Gd__gd_core__Item,false},
{&META_Gd__gd_core__Item,SYM_GEN_shadowOffset_shop_524,candidate_Gd__gd_core__Item,false},
{&META_Gd__gd_core__Item,SYM_GEN_shadowOffset_dropped_525,candidate_Gd__gd_core__Item,false},
{&META_Gd__gd_core__Item,SYM_GEN_shadowOffset_dragged_526,candidate_Gd__gd_core__Item,false},
{&META_Gd__gd_core__Item,SYM_GEN_DRAG_PRIORITY_527,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_correction_583,candidate_Gd__gd_core__Item,false},
{&META_Gd__gd_core__Item,SYM_GEN_angleStep_585,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_moveRotationMouseFactor_588,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_backforce_589,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_fric_590,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_maxAngle_591,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_moveRotationSpeed_592,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_hoverableWhenMenuOpen_598,candidate_Gd__gd_core__Item,false},
{&META_Gd__gd_core__Item,SYM_GEN_MISS_OFFSET_602,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_PRE_FUSE_DUR_603,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_PRE_FUSE_DUR_COG_604,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_FUSE_DUR_605,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_TRANSFORMATION_DUR_606,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,SYM_GEN_labelOffsets_613,candidate_Gd__gd_core__Item,false},
{&META_Gd__gd_core__Item,SYM_GEN_SignalConnection_877,candidate_Gd__gd_core__Item,true},
{&META_Gd__gd_core__Item,gd::SymId(0),candidate_Gd__gd_core__Item,false},
{&META_Gd__gd_core__Item,gd::SymId(0xffffffffu),candidate_Gd__gd_core__Item,false},
{&META_Gd__gd_core__Weapon,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Weapon,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreItemBook,SYM_GEN_DESCRIPTOR_IDS_1659,nullptr,false},
{&META_Gd__gd_core__CoreItemBook,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CoreItemBook,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__DarkestLotus,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__DarkestLotus,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Flute,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Flute,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__HolySpear,SYM_GEN_SpearState_1902,candidate_Gd__gd_core__HolySpear,true},
{&META_Gd__gd_core__HolySpear,gd::SymId(0),candidate_Gd__gd_core__HolySpear,false},
{&META_Gd__gd_core__HolySpear,gd::SymId(0xffffffffu),candidate_Gd__gd_core__HolySpear,false},
{&META_Gd__gd_core__ManaPotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__ManaPotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__PoisonIvy,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__PoisonIvy,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__SpikedShield,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__SpikedShield,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__StrongStoneSkinPotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__StrongStoneSkinPotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__YggdrasilLeaf,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__YggdrasilLeaf,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__BloodyDagger,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__BloodyDagger,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__CursedDagger,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__CursedDagger,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofAgility,SYM_GEN_amuletColor_2020,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofAgility,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofAgility,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PowerPuppy,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PowerPuppy,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Greatsword,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Greatsword,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Broccoli,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Broccoli,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CheeseGoobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CheeseGoobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ChiliGoobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ChiliGoobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DarkLantern,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DarkLantern,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DragonSet,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DragonSet,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EvilHat,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EvilHat,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Toad,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Toad,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__HawkRune,SYM_GEN_gemColor_995,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__HawkRune,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__HawkRune,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__InvestmentOpportunity,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__InvestmentOpportunity,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LittleMimic,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LittleMimic,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MechaBat,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MechaBat,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__OnionCutter,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__OnionCutter,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PortableAltar,SYM_GEN_valueFactor_2434,candidate_Gd__gd_core_items__Exclusive__PortableAltar,true},
{&META_Gd__gd_core_items__Exclusive__PortableAltar,gd::SymId(0),candidate_Gd__gd_core_items__Exclusive__PortableAltar,false},
{&META_Gd__gd_core_items__Exclusive__PortableAltar,gd::SymId(0xffffffffu),candidate_Gd__gd_core_items__Exclusive__PortableAltar,false},
{&META_Gd__gd_core_items__Exclusive__RainbowGoobertMage,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RainbowGoobertMage,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SapphireWhelp,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SapphireWhelp,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SliceofToast,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SliceofToast,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpellScrollLight,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpellScrollLight,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Stoned,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Stoned,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__TigerRune,SYM_GEN_gemColor_995,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__TigerRune,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__TigerRune,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__WandofDissonance,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__WandofDissonance,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Garlic,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Garlic,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__HeroLongsword,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__HeroLongsword,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__ManaPotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__ManaPotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Pumpkin,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Pumpkin,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__StrongHealthPotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__StrongHealthPotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__YggdrasilLeaf,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__YggdrasilLeaf,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Card,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Card,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Bloodthorne,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Bloodthorne,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreCharacter,SYM_GEN_ID_1297,candidate_Gd__gd_core__CoreCharacter,true},
{&META_Gd__gd_core__CoreCharacter,SYM_GEN_Stat_870,candidate_Gd__gd_core__CoreCharacter,true},
{&META_Gd__gd_core__CoreCharacter,SYM_GEN_StaminaResult_1298,candidate_Gd__gd_core__CoreCharacter,true},
{&META_Gd__gd_core__CoreCharacter,SYM_GEN_AUTO_RAGE_DELAY_1044,candidate_Gd__gd_core__CoreCharacter,true},
{&META_Gd__gd_core__CoreCharacter,SYM_GEN_AUTO_RAGE_DUR_1045,candidate_Gd__gd_core__CoreCharacter,true},
{&META_Gd__gd_core__CoreCharacter,SYM_GEN_CLASS_SOUND_COUNTS_1127,candidate_Gd__gd_core__CoreCharacter,false},
{&META_Gd__gd_core__CoreCharacter,gd::SymId(0),candidate_Gd__gd_core__CoreCharacter,false},
{&META_Gd__gd_core__CoreCharacter,gd::SymId(0xffffffffu),candidate_Gd__gd_core__CoreCharacter,false},
{&META_Gd__gd_core__CoreItemData,SYM_GEN_ReleaseState_1727,candidate_Gd__gd_core__CoreItemData,true},
{&META_Gd__gd_core__CoreItemData,SYM_GEN_PARAM_DELIMITER_1710,candidate_Gd__gd_core__CoreItemData,false},
{&META_Gd__gd_core__CoreItemData,gd::SymId(0),candidate_Gd__gd_core__CoreItemData,false},
{&META_Gd__gd_core__CoreItemData,gd::SymId(0xffffffffu),candidate_Gd__gd_core__CoreItemData,false},
{&META_Gd__gd_core__Darksaber,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Darksaber,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__FlyAgaric,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__FlyAgaric,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__HungryBlade,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__HungryBlade,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Manathirst,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Manathirst,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__PotionBelt,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__PotionBelt,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__StaffofUnhealing,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__StaffofUnhealing,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__TheFool,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__TheFool,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Card,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Card,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Blueberries,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Blueberries,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__CursedHairComb,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__CursedHairComb,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofAlchemy,SYM_GEN_amuletColor_2020,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofAlchemy,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofAlchemy,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ArmoredPowerPuppy,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ArmoredPowerPuppy,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BigBloodthorne,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BigBloodthorne,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BroccoliGoobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BroccoliGoobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__ChessPiece,SYM_GEN_PieceColor_2150,candidate_Gd__gd_core_items__Exclusive__Chess__ChessPiece,true},
{&META_Gd__gd_core_items__Exclusive__Chess__ChessPiece,gd::SymId(0),candidate_Gd__gd_core_items__Exclusive__Chess__ChessPiece,false},
{&META_Gd__gd_core_items__Exclusive__Chess__ChessPiece,gd::SymId(0xffffffffu),candidate_Gd__gd_core_items__Exclusive__Chess__ChessPiece,false},
{&META_Gd__gd_core_items__Exclusive__ChiliPepper,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ChiliPepper,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DarkRitual,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DarkRitual,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DragonskinBoots,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DragonskinBoots,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ExtraAngy,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ExtraAngy,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FrogPrince,SYM_GEN_FrogState_2277,candidate_Gd__gd_core_items__Exclusive__FrogPrince,true},
{&META_Gd__gd_core_items__Exclusive__FrogPrince,gd::SymId(0),candidate_Gd__gd_core_items__Exclusive__FrogPrince,false},
{&META_Gd__gd_core_items__Exclusive__FrogPrince,gd::SymId(0xffffffffu),candidate_Gd__gd_core_items__Exclusive__FrogPrince,false},
{&META_Gd__gd_core_items__Exclusive__HeartoftheCards,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__HeartoftheCards,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Joker,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Joker,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LongSpear,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LongSpear,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MegaClover,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MegaClover,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__OwlSpirit,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__OwlSpirit,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Pot,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Pot,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Scale,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Scale,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SlimeTime,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SlimeTime,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpellScrollNature,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpellScrollNature,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StoneGloves,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StoneGloves,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__TimeDilator,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__TimeDilator,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__WarScythe,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__WarScythe,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Gems__Amethyst,SYM_GEN_gemColor_995,nullptr,false},
{&META_Gd__gd_core_items__Gems__Amethyst,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Gems__Amethyst,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__HeroSword,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__HeroSword,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Manathirst,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Manathirst,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__RainbowGoobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__RainbowGoobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__StrongPestilenceFlask,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__StrongPestilenceFlask,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__AceofSpades,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__AceofSpades,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Dagger,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Dagger,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreCombat,SYM_GEN_RoundResult_1340,candidate_Gd__gd_core__CoreCombat,true},
{&META_Gd__gd_core__CoreCombat,SYM_GEN_FATIGUE_TIME_1299,candidate_Gd__gd_core__CoreCombat,true},
{&META_Gd__gd_core__CoreCombat,SYM_GEN_FATIGUE_START_DELAY_1300,candidate_Gd__gd_core__CoreCombat,true},
{&META_Gd__gd_core__CoreCombat,SYM_GEN_FATIGUE_SLOW_TIME_1301,candidate_Gd__gd_core__CoreCombat,true},
{&META_Gd__gd_core__CoreCombat,SYM_GEN_CoreItemSort_1344,candidate_Gd__gd_core__CoreCombat,true},
{&META_Gd__gd_core__CoreCombat,gd::SymId(0),candidate_Gd__gd_core__CoreCombat,false},
{&META_Gd__gd_core__CoreCombat,gd::SymId(0xffffffffu),candidate_Gd__gd_core__CoreCombat,false},
{&META_Gd__gd_core__CoreRng,SYM_GEN_BalancedRng_1749,candidate_Gd__gd_core__CoreRng,true},
{&META_Gd__gd_core__CoreRng,SYM_GEN_BalancedRange_1750,candidate_Gd__gd_core__CoreRng,true},
{&META_Gd__gd_core__CoreRng,gd::SymId(0),candidate_Gd__gd_core__CoreRng,false},
{&META_Gd__gd_core__CoreRng,gd::SymId(0xffffffffu),candidate_Gd__gd_core__CoreRng,false},
{&META_Gd__gd_core__DeathScythe,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__DeathScythe,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Garlic,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Garlic,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Item__INNER__SignalConnection,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Item__INNER__SignalConnection,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Shield,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Shield,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Present,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Present,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__StaminaSack,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__StaminaSack,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__TheLovers,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__TheLovers,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__AceofSpades,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__AceofSpades,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Bow,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Bow,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__CustomerCard,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__CustomerCard,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofDarkness,SYM_GEN_amuletColor_2020,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofDarkness,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofDarkness,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__WisdomPuppy,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__WisdomPuppy,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BionicArmor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BionicArmor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Broccotree,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Broccotree,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__BlackBishop,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__BlackBishop,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ChromeCube,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ChromeCube,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DeathLotus,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DeathLotus,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DualWielding,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DualWielding,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ExtraBags,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ExtraBags,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Frostbite,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Frostbite,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__HeartShield,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__HeartShield,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__JustStats,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__JustStats,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Lootbox,SYM_GEN_OFFSET_2353,candidate_Gd__gd_core_items__Exclusive__Lootbox,true},
{&META_Gd__gd_core_items__Exclusive__Lootbox,gd::SymId(0),candidate_Gd__gd_core_items__Exclusive__Lootbox,false},
{&META_Gd__gd_core_items__Exclusive__Lootbox,gd::SymId(0xffffffffu),candidate_Gd__gd_core_items__Exclusive__Lootbox,false},
{&META_Gd__gd_core_items__Exclusive__MercuryElemental,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MercuryElemental,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ParadiseBirb,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ParadiseBirb,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PoweroftheMoon,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PoweroftheMoon,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RainbowOrb,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RainbowOrb,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ScholarBag,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ScholarBag,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Sloth,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Sloth,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpicyBanana,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpicyBanana,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StoneGolem,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StoneGolem,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__TimeMelting,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__TimeMelting,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__WaterElemental,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__WaterElemental,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Gems__CorruptedCrystal,SYM_GEN_gemColor_995,nullptr,false},
{&META_Gd__gd_core_items__Gems__CorruptedCrystal,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Gems__CorruptedCrystal,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__HoloFireLizard,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__HoloFireLizard,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__MoonShield,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__MoonShield,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__RainbowGoobertRanger,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__RainbowGoobertRanger,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__StrongStoneSkinPotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__StrongStoneSkinPotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__RangerCollar,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__RangerCollar,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__BloodyDagger,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__BloodyDagger,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreCombat__INNER__CoreItemSort,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CoreCombat__INNER__CoreItemSort,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreRng__INNER__BalancedRng,SYM_GEN_luckBalance_1758,candidate_Gd__gd_core__CoreRng__INNER__BalancedRng,true},
{&META_Gd__gd_core__CoreRng__INNER__BalancedRng,gd::SymId(0),candidate_Gd__gd_core__CoreRng__INNER__BalancedRng,false},
{&META_Gd__gd_core__CoreRng__INNER__BalancedRng,gd::SymId(0xffffffffu),candidate_Gd__gd_core__CoreRng__INNER__BalancedRng,false},
{&META_Gd__gd_core__DeckofCards,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__DeckofCards,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__GingerbreadMan,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__GingerbreadMan,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Jynxtorquilla,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Jynxtorquilla,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__MoonShield,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__MoonShield,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__ProtectivePurse,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__ProtectivePurse,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__SteelGoobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__SteelGoobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__ThornBow,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__ThornBow,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__RangerCollar,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__RangerCollar,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__BowandArrow,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__BowandArrow,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__DancingDragon,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__DancingDragon,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofFeasting,SYM_GEN_amuletColor_2020,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofFeasting,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofFeasting,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Cube,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Cube,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BurningBanner,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BurningBanner,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__BlackKing,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__BlackKing,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Cog,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Cog,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DeerTotem,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DeerTotem,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Eat_o_matic,SYM_GEN_ArmState_2236,candidate_Gd__gd_core_items__Exclusive__Eat_o_matic,true},
{&META_Gd__gd_core_items__Exclusive__Eat_o_matic,SYM_GEN_SLOW_SPEED_2228,candidate_Gd__gd_core_items__Exclusive__Eat_o_matic,true},
{&META_Gd__gd_core_items__Exclusive__Eat_o_matic,SYM_GEN_FAST_SPEED_2229,candidate_Gd__gd_core_items__Exclusive__Eat_o_matic,true},
{&META_Gd__gd_core_items__Exclusive__Eat_o_matic,gd::SymId(0),candidate_Gd__gd_core_items__Exclusive__Eat_o_matic,false},
{&META_Gd__gd_core_items__Exclusive__Eat_o_matic,gd::SymId(0xffffffffu),candidate_Gd__gd_core_items__Exclusive__Eat_o_matic,false},
{&META_Gd__gd_core_items__Exclusive__FalseLife,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FalseLife,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Shield,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Shield,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__HeavyDrinking,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__HeavyDrinking,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__JynxStaff,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__JynxStaff,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LuckyCat,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LuckyCat,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MissFortune,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MissFortune,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PerpetuumMobile,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PerpetuumMobile,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PrismaticSword,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PrismaticSword,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RainbowPotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RainbowPotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Lightsaber,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Lightsaber,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SmellyBarrier,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SmellyBarrier,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpikedCollar,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpikedCollar,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StoneShoes,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StoneShoes,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__TimePendant,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__TimePendant,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Whetstone,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Whetstone,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Gems__Emerald,SYM_GEN_gemColor_995,nullptr,false},
{&META_Gd__gd_core_items__Gems__Emerald,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Gems__Emerald,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__HolyArmor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__HolyArmor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__MrStruggles,SYM_GEN_plushies_1949,nullptr,false},
{&META_Gd__gd_core_items__MrStruggles,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__MrStruggles,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__RangerBag,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__RangerBag,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__TheFool,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__TheFool,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__AcornCollar,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__AcornCollar,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Blueberries,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Blueberries,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreCombatLog,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CoreCombatLog,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreRng__INNER__BalancedRange,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CoreRng__INNER__BalancedRange,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Potion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Potion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__GlovesofHaste,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__GlovesofHaste,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__LeatherArmor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__LeatherArmor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__MrStruggles,SYM_GEN_plushies_1949,nullptr,false},
{&META_Gd__gd_core__MrStruggles,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__MrStruggles,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Pumpkin,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Pumpkin,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Stone,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Stone,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__ThornWhip,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__ThornWhip,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__AcornCollar,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__AcornCollar,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__BoxofRiches,SYM_GEN_gemOdds_955,nullptr,false},
{&META_Gd__gd_core_items__BoxofRiches,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__BoxofRiches,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__DarkestLotus,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__DarkestLotus,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofFortune,SYM_GEN_amuletColor_2020,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofFortune,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofFortune,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ArtifactStoneDeath,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ArtifactStoneDeath,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BismuthCube,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BismuthCube,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BurningSword,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BurningSword,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__BlackKnight,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__BlackKnight,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CogBadge,SYM_GEN_chargeCells_2055,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CogBadge,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CogBadge,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DevouringSphere,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DevouringSphere,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EchoingBattlecry,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EchoingBattlecry,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Fedora,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Fedora,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FrozenBuckler,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FrozenBuckler,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Hedgehog,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Hedgehog,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__RibSawBlade,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__RibSawBlade,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LuckyShortbow,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LuckyShortbow,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MoltenDagger,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MoltenDagger,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Phoenix,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Phoenix,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PrismaticWand,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PrismaticWand,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RandomLoadoutBag,SYM_GEN_bagRarityWeights_2459,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RandomLoadoutBag,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RandomLoadoutBag,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Scissorswords,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Scissorswords,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SmithingForDummies,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SmithingForDummies,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpikedStaff,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpikedStaff,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StrongDivinePotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StrongDivinePotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ToastGoobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ToastGoobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Whetstone3,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Whetstone3,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Gems__LumpofCoal,SYM_GEN_gemColor_995,nullptr,false},
{&META_Gd__gd_core_items__Gems__LumpofCoal,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Gems__LumpofCoal,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__HolySpear,SYM_GEN_SpearState_1902,candidate_Gd__gd_core_items__HolySpear,true},
{&META_Gd__gd_core_items__HolySpear,gd::SymId(0),candidate_Gd__gd_core_items__HolySpear,false},
{&META_Gd__gd_core_items__HolySpear,gd::SymId(0xffffffffu),candidate_Gd__gd_core_items__HolySpear,false},
{&META_Gd__gd_core_items__Pandamonium,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Pandamonium,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__RubyChonk,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__RubyChonk,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__TheLovers,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__TheLovers,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Item,SYM_GEN_Owner_854,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_Type_855,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_Priority_856,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_CraftingPriority_857,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_Tag_858,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_Stack_859,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_Mat_860,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_Physics_861,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_Rarity_862,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_FaceDirection_863,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_StatModified_864,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_DropResult_865,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_PickupType_866,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_Affected_867,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_Tiles_868,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_ActivationAni_869,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_Stat_870,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_StackChangeType_871,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_affectedColorToTileId_509,candidate_Gd__gd_core_items__Item,false},
{&META_Gd__gd_core_items__Item,SYM_GEN_rarityColors_511,candidate_Gd__gd_core_items__Item,false},
{&META_Gd__gd_core_items__Item,SYM_GEN_offset_516,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_impulse_517,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_momentumFactor_518,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_affectedSoundsVolume_521,candidate_Gd__gd_core_items__Item,false},
{&META_Gd__gd_core_items__Item,SYM_GEN_cellSize_522,candidate_Gd__gd_core_items__Item,false},
{&META_Gd__gd_core_items__Item,SYM_GEN_halfCellSize_523,candidate_Gd__gd_core_items__Item,false},
{&META_Gd__gd_core_items__Item,SYM_GEN_shadowOffset_shop_524,candidate_Gd__gd_core_items__Item,false},
{&META_Gd__gd_core_items__Item,SYM_GEN_shadowOffset_dropped_525,candidate_Gd__gd_core_items__Item,false},
{&META_Gd__gd_core_items__Item,SYM_GEN_shadowOffset_dragged_526,candidate_Gd__gd_core_items__Item,false},
{&META_Gd__gd_core_items__Item,SYM_GEN_DRAG_PRIORITY_527,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_correction_583,candidate_Gd__gd_core_items__Item,false},
{&META_Gd__gd_core_items__Item,SYM_GEN_angleStep_585,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_moveRotationMouseFactor_588,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_backforce_589,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_fric_590,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_maxAngle_591,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_moveRotationSpeed_592,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_hoverableWhenMenuOpen_598,candidate_Gd__gd_core_items__Item,false},
{&META_Gd__gd_core_items__Item,SYM_GEN_MISS_OFFSET_602,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_PRE_FUSE_DUR_603,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_PRE_FUSE_DUR_COG_604,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_FUSE_DUR_605,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_TRANSFORMATION_DUR_606,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,SYM_GEN_labelOffsets_613,candidate_Gd__gd_core_items__Item,false},
{&META_Gd__gd_core_items__Item,SYM_GEN_SignalConnection_877,candidate_Gd__gd_core_items__Item,true},
{&META_Gd__gd_core_items__Item,gd::SymId(0),candidate_Gd__gd_core_items__Item,false},
{&META_Gd__gd_core_items__Item,gd::SymId(0xffffffffu),candidate_Gd__gd_core_items__Item,false},
{&META_Gd__gd_core__Bow,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Bow,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreConst,SYM_GEN_EventType_1395,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_ItemMetrics_1396,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_CharID_1397,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_StaminaResult_1298,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_ItemStat_1398,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_Rarity_862,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_StuffedClasses_1399,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_Owner_854,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_GameMode_1400,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_Affected_867,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_Stack_859,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_Tag_858,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_Priority_856,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_StackChangeType_871,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_StatModified_864,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_FaceDirection_863,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_Classes_1401,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_Classes_Full_1402,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,SYM_GEN_Type_855,candidate_Gd__gd_core__CoreConst,true},
{&META_Gd__gd_core__CoreConst,gd::SymId(0),candidate_Gd__gd_core__CoreConst,false},
{&META_Gd__gd_core__CoreConst,gd::SymId(0xffffffffu),candidate_Gd__gd_core__CoreConst,false},
{&META_Gd__gd_core__CoreTimer,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CoreTimer,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__DemonicFlask,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__DemonicFlask,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Greatsword,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Greatsword,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__LeatherBoots,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__LeatherBoots,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Pan,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Pan,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__RainbowGoobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__RainbowGoobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__LeatherHelm,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__LeatherHelm,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Torch,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Torch,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__ArtifactStoneCold,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__ArtifactStoneCold,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Broom,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Broom,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Darksaber,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Darksaber,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofLife,SYM_GEN_amuletColor_2020,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofLife,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofLife,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Automanaton,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Automanaton,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BloodManipulation,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BloodManipulation,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BurningBlade,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BurningBlade,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__BlackPawn,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__BlackPawn,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Coil,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Coil,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DigDeeper,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DigDeeper,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ElectricTorch,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ElectricTorch,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FirePit,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FirePit,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FrozenFlame,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FrozenFlame,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__WoodenBuckler,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__WoodenBuckler,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Katana,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Katana,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MageHat,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MageHat,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MoltenGreatsword,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MoltenGreatsword,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Phoenix2,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Phoenix2,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PuzzleBadge,SYM_GEN_puzzlebags_2447,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PuzzleBadge,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PuzzleBadge,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Rat,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Rat,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SealtheDeal,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SealtheDeal,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Snake,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Snake,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpikedWall,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpikedWall,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__VampiricPotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__VampiricPotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Toolbox,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Toolbox,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__WingedBoots,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__WingedBoots,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Gems__Ruby,SYM_GEN_gemColor_995,nullptr,false},
{&META_Gd__gd_core_items__Gems__Ruby,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Gems__Ruby,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__HungryBlade,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__HungryBlade,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__PiercingArrow,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__PiercingArrow,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__RubyEgg,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__RubyEgg,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__ThornBow,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__ThornBow,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Stone,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Stone,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__BowandArrow,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__BowandArrow,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreContext,SYM_GEN_PHYSICS_FPS_1403,candidate_Gd__gd_core__CoreContext,true},
{&META_Gd__gd_core__CoreContext,SYM_GEN_PHYSICS_DELTA_1404,candidate_Gd__gd_core__CoreContext,true},
{&META_Gd__gd_core__CoreContext,SYM_GEN_COMBAT_DELAY_1405,candidate_Gd__gd_core__CoreContext,true},
{&META_Gd__gd_core__CoreContext,SYM_GEN_FATIGUE_TIME_1299,candidate_Gd__gd_core__CoreContext,true},
{&META_Gd__gd_core__CoreContext,SYM_GEN_CRITICAL_SHAKE_WINDOW_1456,candidate_Gd__gd_core__CoreContext,true},
{&META_Gd__gd_core__CoreContext,SYM_GEN_MEGA_CLOVER_PARTICLE_DRAWS_1461,candidate_Gd__gd_core__CoreContext,false},
{&META_Gd__gd_core__CoreContext,SYM_GEN_LOVERS_PARTICLE_DRAWS_1462,candidate_Gd__gd_core__CoreContext,false},
{&META_Gd__gd_core__CoreContext,SYM_GEN_LOVERS_PARTICLE_RESTART_DRAWS_1463,candidate_Gd__gd_core__CoreContext,false},
{&META_Gd__gd_core__CoreContext,SYM_GEN_NativeFlicker_1509,candidate_Gd__gd_core__CoreContext,true},
{&META_Gd__gd_core__CoreContext,gd::SymId(0),candidate_Gd__gd_core__CoreContext,false},
{&META_Gd__gd_core__CoreContext,gd::SymId(0xffffffffu),candidate_Gd__gd_core__CoreContext,false},
{&META_Gd__gd_core__CoreUtil,SYM_GEN_DictSorter_1808,candidate_Gd__gd_core__CoreUtil,true},
{&META_Gd__gd_core__CoreUtil,gd::SymId(0),candidate_Gd__gd_core__CoreUtil,false},
{&META_Gd__gd_core__CoreUtil,gd::SymId(0xffffffffu),candidate_Gd__gd_core__CoreUtil,false},
{&META_Gd__gd_core__DjinnLamp,SYM_GEN_numIngredients_1856,candidate_Gd__gd_core__DjinnLamp,true},
{&META_Gd__gd_core__DjinnLamp,gd::SymId(0),candidate_Gd__gd_core__DjinnLamp,false},
{&META_Gd__gd_core__DjinnLamp,gd::SymId(0xffffffffu),candidate_Gd__gd_core__DjinnLamp,false},
{&META_Gd__gd_core__Hammer,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Hammer,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__LeatherHelm,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__LeatherHelm,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Pandamonium,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Pandamonium,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__RainbowGoobertRanger,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__RainbowGoobertRanger,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__StoneHelm,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__StoneHelm,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__VampiricArmor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__VampiricArmor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__ArtifactStoneHeat,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__ArtifactStoneHeat,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__BurningCoal,SYM_GEN_gemColor_995,nullptr,false},
{&META_Gd__gd_core_items__BurningCoal,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__BurningCoal,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__DeathScythe,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__DeathScythe,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofLight,SYM_GEN_amuletColor_2020,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofLight,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofLight,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Axe,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Axe,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Bomb,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Bomb,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BurningSpikes,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BurningSpikes,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__BlackQueen,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__BlackQueen,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ConTrapTron,SYM_GEN_chargeCells1_2133,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ConTrapTron,SYM_GEN_chargeCells2_2134,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ConTrapTron,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ConTrapTron,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DivinePotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DivinePotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ElephantRune,SYM_GEN_gemColor_995,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ElephantRune,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ElephantRune,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Shelly,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Shelly,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FullBodyProtection,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FullBodyProtection,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__HeroShield,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__HeroShield,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__KingCrown,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__KingCrown,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MagicBadge,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MagicBadge,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MoltenSpear,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MoltenSpear,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PiggyofRiches,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PiggyofRiches,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PuzzlebagJ,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PuzzlebagJ,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RatChef,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RatChef,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SerpentStaff,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SerpentStaff,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Snowball,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Snowball,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpintoWin,SYM_GEN_colors_2538,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpintoWin,SYM_GEN_neutralColor_2539,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpintoWin,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpintoWin,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StrongVampiricPotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StrongVampiricPotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Turtle,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Turtle,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Wisp,SYM_GEN_gemColor_995,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Wisp,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Wisp,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Gems__Sapphire,SYM_GEN_gemColor_995,nullptr,false},
{&META_Gd__gd_core_items__Gems__Sapphire,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Gems__Sapphire,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Item__INNER__SignalConnection,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Item__INNER__SignalConnection,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Pineapple,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Pineapple,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__ShieldofValor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__ShieldofValor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__ThornWhip,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__ThornWhip,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__ArtifactStoneCold,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__ArtifactStoneCold,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__BoxofRiches,SYM_GEN_gemOdds_955,nullptr,false},
{&META_Gd__gd_core__BoxofRiches,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__BoxofRiches,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreContext__INNER__NativeFlicker,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CoreContext__INNER__NativeFlicker,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreUtil__INNER__DictSorter,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CoreUtil__INNER__DictSorter,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__DragonEgg,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__DragonEgg,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__HealingHerbs,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__HealingHerbs,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__LightGoobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__LightGoobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__PestilenceFlask,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__PestilenceFlask,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__RangerBag,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__RangerBag,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__StoneSkinPotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__StoneSkinPotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__VampiricGloves,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__VampiricGloves,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Bag,SYM_GEN_BagTiles_933,candidate_Gd__gd_core_items__Bag,true},
{&META_Gd__gd_core_items__Bag,gd::SymId(0),candidate_Gd__gd_core_items__Bag,false},
{&META_Gd__gd_core_items__Bag,gd::SymId(0xffffffffu),candidate_Gd__gd_core_items__Bag,false},
{&META_Gd__gd_core_items__BurningTorch,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__BurningTorch,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__DeckofCards,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__DeckofCards,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofSteel,SYM_GEN_amuletColor_2020,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofSteel,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletofSteel,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BadgerRune,SYM_GEN_gemColor_995,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BadgerRune,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BadgerRune,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BookofBasics,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BookofBasics,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BustedBlade,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BustedBlade,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__BlackRook,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__BlackRook,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CriticalPoison,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CriticalPoison,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DoomCap,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DoomCap,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EmeraldEgg,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EmeraldEgg,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FireShelly,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FireShelly,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FurciferPrime,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FurciferPrime,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__HogusBogus,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__HogusBogus,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__KingGoobert,SYM_GEN_CrownState_1822,candidate_Gd__gd_core_items__Exclusive__KingGoobert,true},
{&META_Gd__gd_core_items__Exclusive__KingGoobert,gd::SymId(0),candidate_Gd__gd_core_items__Exclusive__KingGoobert,false},
{&META_Gd__gd_core_items__Exclusive__KingGoobert,gd::SymId(0xffffffffu),candidate_Gd__gd_core_items__Exclusive__KingGoobert,false},
{&META_Gd__gd_core_items__Exclusive__MagicCollar,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MagicCollar,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MoltenSpear2,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MoltenSpear2,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PiggyPinata,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PiggyPinata,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PuzzlebagL,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PuzzlebagL,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Recombobulator,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Recombobulator,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SewingCase,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SewingCase,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Snowcake,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Snowcake,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpiritBells,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpiritBells,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SunArmor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SunArmor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Twine,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Twine,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__WolfBadge,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__WolfBadge,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Gems__Skull,SYM_GEN_gemColor_995,nullptr,false},
{&META_Gd__gd_core_items__Gems__Skull,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Gems__Skull,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Jynxtorquilla,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Jynxtorquilla,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__PlatinCustomerCard,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__PlatinCustomerCard,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Shovel,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Shovel,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Torch,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Torch,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__ArtifactStoneHeat,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__ArtifactStoneHeat,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Broom,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Broom,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreDamageResult,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CoreDamageResult,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CorruptedArmor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CorruptedArmor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Weapon,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Weapon,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__HealthPotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__HealthPotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Lightsaber,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Lightsaber,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__PiercingArrow,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__PiercingArrow,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__RibSawBlade,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__RibSawBlade,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__StorageCoffin,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__StorageCoffin,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__VampiricScythe,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__VampiricScythe,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__BagofStones,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__BagofStones,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Carrot,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Carrot,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__DemonicFlask,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__DemonicFlask,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletoftheWild,SYM_GEN_amuletColor_2020,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletoftheWild,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletoftheWild,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpiritCompanion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpiritCompanion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BookofDarkness,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BookofDarkness,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BuytheHolyLight,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BuytheHolyLight,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__WhiteBishop,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__WhiteBishop,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Crow,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Crow,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DoubleAxe,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DoubleAxe,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EmeraldWhelp,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EmeraldWhelp,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Flame,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Flame,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Generator,SYM_GEN_chargeCells_2055,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Generator,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Generator,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Holdall,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Holdall,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__KingoftheBling,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__KingoftheBling,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MagicMirror,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MagicMirror,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MoonArmor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MoonArmor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__SpikedShield,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__SpikedShield,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PuzzlebagS,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PuzzlebagS,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RelicCase,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RelicCase,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ShamanMask,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ShamanMask,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Snowman,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Snowman,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpringLoader,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpringLoader,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SunShield,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SunShield,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__TwineBadge,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__TwineBadge,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__WolfEmblem,SYM_GEN_puppies_2626,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__WolfEmblem,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__WolfEmblem,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Gems__Topaz,SYM_GEN_gemColor_995,nullptr,false},
{&META_Gd__gd_core_items__Gems__Topaz,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Gems__Topaz,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__LeatherBoots,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__LeatherBoots,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__PocketSand,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__PocketSand,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Spear,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Spear,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__VampiricArmor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__VampiricArmor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Bag,SYM_GEN_BagTiles_933,candidate_Gd__gd_core__Bag,true},
{&META_Gd__gd_core__Bag,gd::SymId(0),candidate_Gd__gd_core__Bag,false},
{&META_Gd__gd_core__Bag,gd::SymId(0xffffffffu),candidate_Gd__gd_core__Bag,false},
{&META_Gd__gd_core_items__Gems__Gem,SYM_GEN_GemMode_994,candidate_Gd__gd_core_items__Gems__Gem,true},
{&META_Gd__gd_core_items__Gems__Gem,gd::SymId(0),candidate_Gd__gd_core_items__Gems__Gem,false},
{&META_Gd__gd_core_items__Gems__Gem,gd::SymId(0xffffffffu),candidate_Gd__gd_core_items__Gems__Gem,false},
{&META_Gd__gd_core__CoreDamageSource,SYM_GEN_Type_855,candidate_Gd__gd_core__CoreDamageSource,true},
{&META_Gd__gd_core__CoreDamageSource,SYM_GEN_Flags_1565,candidate_Gd__gd_core__CoreDamageSource,true},
{&META_Gd__gd_core__CoreDamageSource,SYM_GEN_damTypeNames_1535,candidate_Gd__gd_core__CoreDamageSource,false},
{&META_Gd__gd_core__CoreDamageSource,SYM_GEN_chipDamageFlags_1536,candidate_Gd__gd_core__CoreDamageSource,true},
{&META_Gd__gd_core__CoreDamageSource,SYM_GEN_meleeFlags_1537,candidate_Gd__gd_core__CoreDamageSource,true},
{&META_Gd__gd_core__CoreDamageSource,SYM_GEN_rangedFlags_1538,candidate_Gd__gd_core__CoreDamageSource,true},
{&META_Gd__gd_core__CoreDamageSource,SYM_GEN_effectFlags_1539,candidate_Gd__gd_core__CoreDamageSource,false},
{&META_Gd__gd_core__CoreDamageSource,SYM_GEN_unhealingFlags_1540,candidate_Gd__gd_core__CoreDamageSource,false},
{&META_Gd__gd_core__CoreDamageSource,SYM_GEN_selfDamageFlags_1541,candidate_Gd__gd_core__CoreDamageSource,false},
{&META_Gd__gd_core__CoreDamageSource,gd::SymId(0),candidate_Gd__gd_core__CoreDamageSource,false},
{&META_Gd__gd_core__CoreDamageSource,gd::SymId(0xffffffffu),candidate_Gd__gd_core__CoreDamageSource,false},
{&META_Gd__gd_core__CritwoodStaff,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CritwoodStaff,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Pan,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Pan,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__HeartContainer,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__HeartContainer,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__LuckyBow,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__LuckyBow,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Piggybank,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Piggybank,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__RubyChonk,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__RubyChonk,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__StrongDemonicFlask,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__StrongDemonicFlask,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__VillainSword,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__VillainSword,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Food,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Food,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__CarrotGoobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__CarrotGoobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__DjinnLamp,SYM_GEN_numIngredients_1856,candidate_Gd__gd_core_items__DjinnLamp,true},
{&META_Gd__gd_core_items__DjinnLamp,gd::SymId(0),candidate_Gd__gd_core_items__DjinnLamp,false},
{&META_Gd__gd_core_items__DjinnLamp,gd::SymId(0xffffffffu),candidate_Gd__gd_core_items__DjinnLamp,false},
{&META_Gd__gd_core_items__Exclusive__AmuletUnidentified,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmuletUnidentified,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BadgerSpirit,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BadgerSpirit,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BookofIce,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BookofIce,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CapofBrilliance,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CapofBrilliance,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__WhiteKing,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__WhiteKing,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Cthulhu,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Cthulhu,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DoubleRainbow,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DoubleRainbow,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__LeatherArmor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__LeatherArmor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FlameBadge,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FlameBadge,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Ghost,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Ghost,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__HolyCollar,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__HolyCollar,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__KnifetoMeetYou,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__KnifetoMeetYou,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MagicRing,SYM_GEN_TriggerType_2385,candidate_Gd__gd_core_items__Exclusive__MagicRing,true},
{&META_Gd__gd_core_items__Exclusive__MagicRing,SYM_GEN_RingEffect_2386,candidate_Gd__gd_core_items__Exclusive__MagicRing,true},
{&META_Gd__gd_core_items__Exclusive__MagicRing,gd::SymId(0),candidate_Gd__gd_core_items__Exclusive__MagicRing,false},
{&META_Gd__gd_core_items__Exclusive__MagicRing,gd::SymId(0xffffffffu),candidate_Gd__gd_core_items__Exclusive__MagicRing,false},
{&META_Gd__gd_core_items__Exclusive__MoreStats,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MoreStats,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PineProtector,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PineProtector,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PuzzlebagT,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PuzzlebagT,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Repeater,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Repeater,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ShellTotem,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ShellTotem,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Snowmaster,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Snowmaster,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Squirrel,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Squirrel,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__TeslaCoil,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__TeslaCoil,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Ukulele,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Ukulele,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Wrench,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Wrench,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__GingerbreadMan,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__GingerbreadMan,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__LightGoobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__LightGoobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__PoisonBow,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__PoisonBow,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__SpectralDagger,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__SpectralDagger,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__VampiricGloves,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__VampiricGloves,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__BagofStones,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__BagofStones,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__BurningCoal,SYM_GEN_gemColor_995,nullptr,false},
{&META_Gd__gd_core__BurningCoal,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__BurningCoal,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreEvent,SYM_GEN_Target_1583,candidate_Gd__gd_core__CoreEvent,true},
{&META_Gd__gd_core__CoreEvent,gd::SymId(0),candidate_Gd__gd_core__CoreEvent,false},
{&META_Gd__gd_core__CoreEvent,gd::SymId(0xffffffffu),candidate_Gd__gd_core__CoreEvent,false},
{&META_Gd__gd_core__Crossblades,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Crossblades,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Eggscalibur,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Eggscalibur,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__HeartofDarkness,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__HeartofDarkness,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__LuckyClover,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__LuckyClover,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Pineapple,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Pineapple,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__RubyEgg,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__RubyEgg,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Potion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Potion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__WalrusTusk,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__WalrusTusk,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Banana,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Banana,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__ClawsofAttack,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__ClawsofAttack,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__DragonEgg,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__DragonEgg,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AngelCrystal,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AngelCrystal,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BagofGiving,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BagofGiving,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BookofLight,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BookofLight,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CatSpirit,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CatSpirit,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__WhiteKnight,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__WhiteKnight,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Cubert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Cubert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DraconicOrb,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DraconicOrb,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EmployeeUniform,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EmployeeUniform,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FlameWhip,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FlameWhip,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Gigawatz,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Gigawatz,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Hypercube,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Hypercube,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Laboratory,SYM_GEN_params_1570,candidate_Gd__gd_core_items__Exclusive__Laboratory,false},
{&META_Gd__gd_core_items__Exclusive__Laboratory,SYM_GEN_flashColor_2340,candidate_Gd__gd_core_items__Exclusive__Laboratory,false},
{&META_Gd__gd_core_items__Exclusive__Laboratory,SYM_GEN_DUR_2341,candidate_Gd__gd_core_items__Exclusive__Laboratory,true},
{&META_Gd__gd_core_items__Exclusive__Laboratory,gd::SymId(0),candidate_Gd__gd_core_items__Exclusive__Laboratory,false},
{&META_Gd__gd_core_items__Exclusive__Laboratory,gd::SymId(0xffffffffu),candidate_Gd__gd_core_items__Exclusive__Laboratory,false},
{&META_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MrsStruggles,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MrsStruggles,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PlasticCube,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PlasticCube,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PuzzlebagZ,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PuzzlebagZ,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Resistor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Resistor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ShepherdsCrook,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ShepherdsCrook,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SnowStick,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SnowStick,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SquirrelArcher,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SquirrelArcher,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Thornbloom,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Thornbloom,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Ultima,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Ultima,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__FalconBlade,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__FalconBlade,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__GlovesofHaste,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__GlovesofHaste,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__LuckyBow,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__LuckyBow,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__PoisonDagger,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__PoisonDagger,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__StaffofUnhealing,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__StaffofUnhealing,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__VampiricScythe,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__VampiricScythe,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Food,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Food,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__BurningTorch,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__BurningTorch,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreEventBus,SYM_GEN_LoggingMode_1599,candidate_Gd__gd_core__CoreEventBus,true},
{&META_Gd__gd_core__CoreEventBus,gd::SymId(0),candidate_Gd__gd_core__CoreEventBus,false},
{&META_Gd__gd_core__CoreEventBus,gd::SymId(0xffffffffu),candidate_Gd__gd_core__CoreEventBus,false},
{&META_Gd__gd_core__Crown,SYM_GEN_CrownState_1822,candidate_Gd__gd_core__Crown,true},
{&META_Gd__gd_core__Crown,gd::SymId(0),candidate_Gd__gd_core__Crown,false},
{&META_Gd__gd_core__Crown,gd::SymId(0xffffffffu),candidate_Gd__gd_core__Crown,false},
{&META_Gd__gd_core__EvilCap,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__EvilCap,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__HeroicPotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__HeroicPotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Piggybank,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Piggybank,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__PlatinCustomerCard,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__PlatinCustomerCard,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__RubyWhelp,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__RubyWhelp,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__HealthPotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__HealthPotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Whetstone,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Whetstone,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__BloodAmulet,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__BloodAmulet,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Coins,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Coins,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Eggscalibur,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Eggscalibur,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Anvil,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Anvil,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Bagtacular,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Bagtacular,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BookofNature,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BookofNature,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Cauldron,SYM_GEN_healColor_2119,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Cauldron,SYM_GEN_manaColor_2120,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Cauldron,SYM_GEN_heatColor_2121,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Cauldron,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Cauldron,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__WhitePawn,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__WhitePawn,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Cupcake,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Cupcake,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DragonClaws,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DragonClaws,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EnchantedWeapons,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EnchantedWeapons,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ForestDragon,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ForestDragon,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__GirlPower,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__GirlPower,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__HyperHedgehog,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__HyperHedgehog,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LeafBadge,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LeafBadge,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MagiteccArmor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MagiteccArmor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MushroomFarm,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__MushroomFarm,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PoisonFrog,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PoisonFrog,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Puzzlebox,SYM_GEN_puzzlebags_2447,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Puzzlebox,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Puzzlebox,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Reverse,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Reverse,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Shielded,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Shielded,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Solaris,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Solaris,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StaffofFire,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StaffofFire,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Thornburst,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Thornburst,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__UnidentifiedSkill,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__UnidentifiedSkill,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__FancyFencingRapier,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__FancyFencingRapier,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Hammer,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Hammer,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__LuckyClover,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__LuckyClover,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__PoisonGoobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__PoisonGoobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__StaminaSack,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__StaminaSack,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__VillainSword,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__VillainSword,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Banana,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Banana,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Carrot,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Carrot,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreGrid,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CoreGrid,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CursedDagger,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CursedDagger,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__FalconBlade,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__FalconBlade,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__HeroLongsword,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__HeroLongsword,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__LuckyPiggy,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__LuckyPiggy,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__PocketSand,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__PocketSand,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__ShieldofValor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__ShieldofValor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__StrongHealthPotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__StrongHealthPotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__White_EyesBlueDragon,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__White_EyesBlueDragon,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Goobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Goobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__CorruptedArmor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__CorruptedArmor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__EvilCap,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__EvilCap,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ArcaneBoots,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ArcaneBoots,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Battery,SYM_GEN_chargeCells_2055,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Battery,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Battery,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Boomerang,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Boomerang,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chainsaw,SYM_GEN_sawSpeed_2122,candidate_Gd__gd_core_items__Exclusive__Chainsaw,true},
{&META_Gd__gd_core_items__Exclusive__Chainsaw,gd::SymId(0),candidate_Gd__gd_core_items__Exclusive__Chainsaw,false},
{&META_Gd__gd_core_items__Exclusive__Chainsaw,gd::SymId(0xffffffffu),candidate_Gd__gd_core_items__Exclusive__Chainsaw,false},
{&META_Gd__gd_core_items__Exclusive__Chess__WhiteQueen,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__WhiteQueen,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CupcakeDragon,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CupcakeDragon,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__RubyWhelp,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__RubyWhelp,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EnergyConversion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EnergyConversion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ForestFriend,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ForestFriend,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__GoldArmor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__GoldArmor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__IceArmor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__IceArmor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LevelUp,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LevelUp,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ManaCrystal,SYM_GEN_chargeCells_2055,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ManaCrystal,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ManaCrystal,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__NoRushPlease,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__NoRushPlease,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PoisonGrenade,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PoisonGrenade,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RainbowBadge,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RainbowBadge,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Robodog,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Robodog,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ShinyMantle,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ShinyMantle,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpeakwithAnimals,SYM_GEN_pets_2524,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpeakwithAnimals,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpeakwithAnimals,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StarofCourage,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StarofCourage,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ThornElemental,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ThornElemental,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__UniquelyUnique,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__UniquelyUnique,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Fanfare,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Fanfare,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__HealingHerbs,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__HealingHerbs,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__LuckyPiggy,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__LuckyPiggy,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__PoisonIvy,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__PoisonIvy,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__SteelGoobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__SteelGoobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__WalrusTusk,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__WalrusTusk,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__BloodAmulet,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__BloodAmulet,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CarrotGoobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CarrotGoobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreHooks,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CoreHooks,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CursedHairComb,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CursedHairComb,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__FancyFencingRapier,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__FancyFencingRapier,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__HeroSword,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__HeroSword,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__MagicStaff,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__MagicStaff,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__PoisonBow,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__PoisonBow,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Shovel,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Shovel,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__PestilenceFlask,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__PestilenceFlask,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Wolpertinger,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Wolpertinger,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__BloodGoobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__BloodGoobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__CritwoodStaff,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__CritwoodStaff,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AcornAce,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AcornAce,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ArcaneIntellect,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ArcaneIntellect,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Bazooka,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Bazooka,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BowlofTreats,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BowlofTreats,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ChainWhip,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ChainWhip,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__WhiteRook,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Chess__WhiteRook,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CupcakeGoobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CupcakeGoobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DragonKnight,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DragonKnight,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EngineerBag2,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EngineerBag2,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ForgingHammer,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ForgingHammer,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__GoldCube,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__GoldCube,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__IceDragon,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__IceDragon,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LightFlower,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LightFlower,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ManaMastery,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ManaMastery,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__NullBlade,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__NullBlade,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PoisonShortbow,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PoisonShortbow,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Rope,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Rope,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ShinyShell,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ShinyShell,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpellScrollDark,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpellScrollDark,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SteelDragon,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SteelDragon,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ThornShortbow,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ThornShortbow,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__VampiricCollar,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__VampiricCollar,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__FannyPack,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__FannyPack,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__HeartContainer,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__HeartContainer,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__MagicStaff,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__MagicStaff,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__PotionBelt,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__PotionBelt,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__StoneHelm,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__StoneHelm,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__White_EyesBlueDragon,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__White_EyesBlueDragon,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Goobert,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Goobert,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__ClawsofAttack,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__ClawsofAttack,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CoreItem__INNER__CoreElectricalCharge,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CoreItem__INNER__CoreElectricalCharge,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__CustomerCard,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__CustomerCard,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Fanfare,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Fanfare,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__HoloFireLizard,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__HoloFireLizard,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__MagicTorch,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__MagicTorch,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__PoisonDagger,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__PoisonDagger,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__Spear,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__Spear,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__StrongPestilenceFlask,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__StrongPestilenceFlask,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core__WoodenBuckler,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core__WoodenBuckler,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Bloodthorne,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Bloodthorne,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Crossblades,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Crossblades,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmethystEgg,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__AmethystEgg,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CouragePuppy,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CouragePuppy,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BerserkerBag,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BerserkerBag,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BoxofProsperity,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__BoxofProsperity,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ChargeSplitter,SYM_GEN_chargeCells1_2133,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ChargeSplitter,SYM_GEN_chargeCells2_2134,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ChargeSplitter,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ChargeSplitter,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ChessBoard,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ChessBoard,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CupcakeStaff,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__CupcakeStaff,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DragonNest,SYM_GEN_gatedItems_1691,nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DragonNest,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__DragonNest,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EngineerBox,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__EngineerBox,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FortunasKiss,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__FortunasKiss,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Halberd,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Halberd,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__IceFlower,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__IceFlower,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LightningPotion,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__LightningPotion,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Mananana,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Mananana,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ObsidianDragon,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ObsidianDragon,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PoisonSpear,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__PoisonSpear,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RainbowGoobertBerserker,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__RainbowGoobertBerserker,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Sandbag,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__Sandbag,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SkullBadge,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SkullBadge,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpellScrollFrostbolt,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__SpellScrollFrostbolt,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StoneArmor,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__StoneArmor,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ThorsHammer,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__ThorsHammer,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__VineweaveBasket,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Exclusive__VineweaveBasket,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Flute,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Flute,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__HeartofDarkness,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__HeartofDarkness,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__MagicTorch,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__MagicTorch,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Present,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Present,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__StorageCoffin,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__StorageCoffin,gd::SymId(0xffffffffu),nullptr,false},
{&META_Gd__gd_core_items__Wolpertinger,gd::SymId(0),nullptr,false},
{&META_Gd__gd_core_items__Wolpertinger,gd::SymId(0xffffffffu),nullptr,false},
};}
inline gd::GdVal candidate_setup(Gd__gd_core__CoreItem& item,const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *item.rt_ctx_;
    gd::GdVal lv__ctx = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__descriptor = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__character = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    item.f_ctx = lv__ctx;
    item.f_descriptor = lv__descriptor;
    item.f_character_ = lv__character;
    item.f_name = gd::native_inline_get_prop(gd_ctx, lv__descriptor, SYM_GEN_name_7);
    item.f_chanceRng = ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, item.f_ctx, SYM_GEN_rng_1406)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, item.f_ctx, SYM_GEN_rng_1406), SYM_GEN_BalancedRng_1749), gd::SYM_new, _ca, 1); })();
    item.f_damageRangeRng = ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, item.f_ctx, SYM_GEN_rng_1406)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, item.f_ctx, SYM_GEN_rng_1406), SYM_GEN_BalancedRange_1750), gd::SYM_new, _ca, 1); })();
    {
        gd::GdVal _t1 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::gd_max(gd::GdVal::from_int(0LL), gd::gd_sub(gd::gd_coerce_int(gd::native_inline_get_prop(gd_ctx, item.f_descriptor, SYM_GEN_sceneDepth_1703)), gd::GdVal::from_int(1LL)))}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
        gd::GdArr* _t2 = (_t1.kind == gd::GdVal::Kind::Arr) ? _t1.arr : nullptr;
        uint32_t _len__t3 = _t2 ? _t2->len : 0u;
        for (uint32_t _t3 = 0; _t3 < _len__t3; ++_t3) {
            gd::GdVal lv__i = _t2->data[_t3];
            item.f_chanceRng = ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, item.f_ctx, SYM_GEN_rng_1406)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, item.f_ctx, SYM_GEN_rng_1406), SYM_GEN_BalancedRng_1749), gd::SYM_new, _ca, 1); })();
        }
    }
    item.f_baseCooldownOverride = gd::gd_coerce_float(gd::native_inline_get_prop(gd_ctx, lv__descriptor, SYM_GEN_cd_1679));
    if (gd_ctx.native_resolved_dispatch) {
        if (!gd::native_setup_empty_stack_tables(gd_ctx, item.f_buffPowers, item.f_buffAmplificationChances)) {
            if (gd_ctx.native_resolved_collect) gd::native_static_setup_hit(1);
            for (int64_t stack = 100; stack <= 110; ++stack) {
                gd::GdVal lv_buff = gd::GdVal::from_int(stack);
                { gd::GdVal target = item.f_buffPowers; gd::native_array_set_index(gd_ctx, target, lv_buff, gd::GdVal::from_float(1.0)); }
                { gd::GdVal target = item.f_buffAmplificationChances; gd::native_array_set_index(gd_ctx, target, lv_buff, gd::GdVal::from_float(0.0)); }
            }
        }
    } else {
        gd::GdVal _t4 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getStacks_1023, nullptr, 0));
        gd::GdArr* _t5 = (_t4.kind == gd::GdVal::Kind::Arr) ? _t4.arr : nullptr;
        uint32_t _len__t6 = _t5 ? _t5->len : 0u;
        for (uint32_t _t6 = 0; _t6 < _len__t6; ++_t6) {
            gd::GdVal lv_buff = _t5->data[_t6];
            { gd::GdVal _t7 = item.f_buffPowers; gd::GdVal _t8 = lv_buff; gd::native_array_set_index(gd_ctx, _t7, _t8, gd::GdVal::from_float(1.0)); }
            { gd::GdVal _t9 = item.f_buffAmplificationChances; gd::GdVal _t10 = lv_buff; gd::native_array_set_index(gd_ctx, _t9, _t10, gd::GdVal::from_float(0.0)); }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreItem::call_static_fn(gd_ctx, SYM_GEN_getNumItemMetrics_227, nullptr, 0, _out); return _out; })()}; return gd::native_inline_call(gd_ctx, item.f_itemMetrics, gd::SYM_resize, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, item.f_itemMetrics, gd::SYM_fill, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1398), gd::SYM_size, nullptr, 0)}; return gd::native_inline_call(gd_ctx, item.f_statDisplayOverrides, gd::SYM_resize, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null()}; return gd::native_inline_call(gd_ctx, item.f_statDisplayOverrides, gd::SYM_fill, _ca, 1); })();
    if (gd_ctx.native_resolved_dispatch) {
        if (gd_ctx.native_resolved_collect) gd::native_static_setup_hit(3);
        for (int64_t color = 0; color < 4; ++color) {
            gd::GdVal lv_color = gd::GdVal::from_int(color);
            { gd::GdVal _t14 = item.f_currentAffectedItems; gd::GdVal _t15 = lv_color; gd::native_array_set_index(gd_ctx, _t14, _t15, gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena))); }
        }
    } else {
        gd::GdVal _t11 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t12 = (_t11.kind == gd::GdVal::Kind::Arr) ? _t11.arr : nullptr;
        uint32_t _len__t13 = _t12 ? _t12->len : 0u;
        for (uint32_t _t13 = 0; _t13 < _len__t13; ++_t13) {
            gd::GdVal lv_color = _t12->data[_t13];
            { gd::GdVal _t14 = item.f_currentAffectedItems; gd::GdVal _t15 = lv_color; gd::native_array_set_index(gd_ctx, _t14, _t15, gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena))); }
        }
    }
    return gd::GdVal::from_obj(&item);
    return gd::GdVal::null();
}
inline void baseline_stack_block(Gd__gd_core__CoreItem& item) {gd::BattleCtx& gd_ctx = *item.rt_ctx_;
    {
        gd::GdVal _t4 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getStacks_1023, nullptr, 0));
        gd::GdArr* _t5 = (_t4.kind == gd::GdVal::Kind::Arr) ? _t4.arr : nullptr;
        uint32_t _len__t6 = _t5 ? _t5->len : 0u;
        for (uint32_t _t6 = 0; _t6 < _len__t6; ++_t6) {
            gd::GdVal lv_buff = _t5->data[_t6];
            { gd::GdVal _t7 = item.f_buffPowers; gd::GdVal _t8 = lv_buff; gd::native_array_set_index(gd_ctx, _t7, _t8, gd::GdVal::from_float(1.0)); }
            { gd::GdVal _t9 = item.f_buffAmplificationChances; gd::GdVal _t10 = lv_buff; gd::native_array_set_index(gd_ctx, _t9, _t10, gd::GdVal::from_float(0.0)); }
        }
    }
}
inline void candidate_stack_block(Gd__gd_core__CoreItem& item) {gd::BattleCtx& gd_ctx = *item.rt_ctx_;
    if (gd_ctx.native_resolved_dispatch) {
        if (!gd::native_setup_empty_stack_tables(gd_ctx, item.f_buffPowers, item.f_buffAmplificationChances)) {
            if (gd_ctx.native_resolved_collect) gd::native_static_setup_hit(1);
            for (int64_t stack = 100; stack <= 110; ++stack) {
                gd::GdVal lv_buff = gd::GdVal::from_int(stack);
                { gd::GdVal target = item.f_buffPowers; gd::native_array_set_index(gd_ctx, target, lv_buff, gd::GdVal::from_float(1.0)); }
                { gd::GdVal target = item.f_buffAmplificationChances; gd::native_array_set_index(gd_ctx, target, lv_buff, gd::GdVal::from_float(0.0)); }
            }
        }
    } else {
        gd::GdVal _t4 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getStacks_1023, nullptr, 0));
        gd::GdArr* _t5 = (_t4.kind == gd::GdVal::Kind::Arr) ? _t4.arr : nullptr;
        uint32_t _len__t6 = _t5 ? _t5->len : 0u;
        for (uint32_t _t6 = 0; _t6 < _len__t6; ++_t6) {
            gd::GdVal lv_buff = _t5->data[_t6];
            { gd::GdVal _t7 = item.f_buffPowers; gd::GdVal _t8 = lv_buff; gd::native_array_set_index(gd_ctx, _t7, _t8, gd::GdVal::from_float(1.0)); }
            { gd::GdVal _t9 = item.f_buffAmplificationChances; gd::GdVal _t10 = lv_buff; gd::native_array_set_index(gd_ctx, _t9, _t10, gd::GdVal::from_float(0.0)); }
        }
    }
}
inline gd::GdVal candidate_getNumNonStackItemMetrics(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    if (gd_ctx.native_resolved_dispatch) { if (gd_ctx.native_resolved_collect) gd::native_static_setup_hit(2); return gd::GdVal::from_int(14LL); }
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(8LL), gd::gd_mul(gd::gd_sub(gd::GdVal::from_int(9LL), gd::GdVal::from_int(8LL)), gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), gd::SYM_size, nullptr, 0)));
    return gd::GdVal::null();
}
inline gd::GdVal candidate_getNumItemMetrics(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    if (gd_ctx.native_resolved_dispatch) { if (gd_ctx.native_resolved_collect) gd::native_static_setup_hit(2); return gd::GdVal::from_int(80LL); }
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(8LL), gd::gd_mul(gd::gd_sub(gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1396), gd::SYM_size, nullptr, 0), gd::GdVal::from_int(8LL)), gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), gd::SYM_size, nullptr, 0)));
    return gd::GdVal::null();
}
