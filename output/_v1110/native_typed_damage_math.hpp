#pragma once
#include "native_event_kernel.hpp"
#include <bit>
#include <cmath>
#include <cstdint>

namespace gd {
void native_typed_damage_hit(unsigned);
inline void native_typed_damage_count(BattleCtx& ctx,unsigned field) {
    if(ctx.native_resolved_collect)native_typed_damage_hit(field);
}
inline bool native_typed_damage_small_int(const GdVal& value) {
    return value.kind==GdVal::Kind::Int && value.i>=-INT64_C(9007199254740992) && value.i<=INT64_C(9007199254740992);
}
inline bool native_typed_damage_finite(double value) {
    return (std::bit_cast<uint64_t>(value)&UINT64_C(0x7ff0000000000000))!=UINT64_C(0x7ff0000000000000);
}
inline void native_typed_damage_resistance(BattleCtx& ctx,Gd__gd_core__CoreDamageResult& result,const GdVal& resistance) {
    if(native_typed_damage_small_int(result.f_damage) && resistance.kind==GdVal::Kind::Float && native_typed_damage_finite(resistance.f)) {
        native_typed_damage_count(ctx,2);
        const double quotient=resistance.f/100.0;
        const double active=quotient < -10.0 ? -10.0 : (quotient > 1.0 ? 1.0 : quotient);
        const double factor=1.0-active;
        const double damage=static_cast<double>(result.f_damage.i)*factor;
        const double rounded=std::round(damage);
        // |damage| <= 11*2^53, inside the exact int64 conversion domain.
        result.f_damage=GdVal::from_int(static_cast<int64_t>(rounded));
        return;
    }
    native_typed_damage_count(ctx,3);
    const auto active=gd_clamp(gd_div(ctx,resistance,GdVal::from_int(100)),GdVal::from_int(-10),GdVal::from_int(1));
    result.f_damage=gd_coerce_int(gd_round(gd_mul(result.f_damage,gd_sub(GdVal::from_float(1.0),active))));
}
inline bool native_typed_damage_bounded_int(const GdVal& value) {
    return value.kind==GdVal::Kind::Int && value.i>=-INT64_C(1152921504606846976) && value.i<=INT64_C(1152921504606846976);
}
inline GdVal native_typed_damage_subtract(BattleCtx& ctx,const GdVal& value,const GdVal& reduction) {
    if(native_typed_damage_bounded_int(value) && native_typed_damage_bounded_int(reduction)) {
        native_typed_damage_count(ctx,4);
        return GdVal::from_int(value.i-reduction.i);
    }
    if(native_typed_damage_small_int(value) && reduction.kind==GdVal::Kind::Float &&
       (std::bit_cast<uint64_t>(reduction.f)&UINT64_C(0x7fffffffffffffff))<UINT64_C(0x4340000000000000)) {
        native_typed_damage_count(ctx,5);
        const double difference=static_cast<double>(value.i)-reduction.f;
        return GdVal::from_int(static_cast<int64_t>(difference));
    }
    native_typed_damage_count(ctx,6);
    return gd_coerce_int(gd_sub(value,reduction));
}
inline void native_typed_damage_after_signal(BattleCtx& ctx,Gd__gd_core__CoreDamageResult& result) {
    if(native_typed_damage_bounded_int(result.f_damage) && native_typed_damage_bounded_int(result.f_damageReduction)) {
        native_typed_damage_count(ctx,7);
        const int64_t difference=result.f_damage.i-result.f_damageReduction.i;
        result.f_damage=GdVal::from_int(difference>0?difference:0);
        return;
    }
    result.f_damage=gd_coerce_int(gd_sub(result.f_damage,result.f_damageReduction));
    result.f_damage=gd_coerce_int(gd_max(GdVal::from_int(0),result.f_damage));
}
inline void native_typed_damage_health(BattleCtx& ctx,GdVal& health,const GdVal& damage) {
    if(health.kind==GdVal::Kind::Float && native_typed_damage_finite(health.f) && native_typed_damage_small_int(damage)) {
        native_typed_damage_count(ctx,8);
        health=GdVal::from_float(health.f-static_cast<double>(damage.i));
        return;
    }
    native_typed_damage_count(ctx,9);
    health=gd_coerce_float(gd_sub(health,damage));
}
template<class Function> inline void native_typed_damage_each(BattleCtx& ctx,const GdVal& count,Function&& function) {
    if(count.kind==GdVal::Kind::Int && count.i>=0 && count.i<=128) {
        native_typed_damage_count(ctx,10);
        const auto limit=static_cast<uint32_t>(count.i);
        for(uint32_t index=0;index<limit;++index)function();
        return;
    }
    native_typed_damage_count(ctx,11);
    const auto sequence=gd_iter_seq(ctx.arena,count);
    auto* array=sequence.kind==GdVal::Kind::Arr?sequence.arr:nullptr;
    const auto limit=array?array->len:0u;
    for(uint32_t index=0;index<limit;++index) {
        const auto value=array->data[index];(void)value;
        function();
    }
}
}
