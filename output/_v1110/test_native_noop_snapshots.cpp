#include "gen/hdrs/Gd__gd_core__CoreCombatLog.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreHooks.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

using Value = gd::GdVal;
using Context = Gd__gd_core__CoreContext;
using Log = Gd__gd_core__CoreCombatLog;
using Hooks = Gd__gd_core__CoreHooks;

// Inherit the same metadata getter as NativeBattleHooks while overriding the callback.
// A metadata-only guard would incorrectly discard these snapshots.
struct CustomHooks : Hooks {
    std::vector<int64_t> characters;
    std::vector<int64_t> stats;
    std::function<void()> on_snapshot;
    explicit CustomHooks(gd::BattleCtx* battle) : Hooks(battle) {}
    bool call_method(gd::BattleCtx& battle, gd::SymId method, const Value* args, int argc, Value& out) override {
        if (method != SYM_GEN_snapshotCharacterStat_1387)
            return Hooks::call_method(battle, method, args, argc, out);
        assert(argc == 2);
        characters.push_back(args[0].as_int());
        stats.push_back(args[1].as_int());
        if (on_snapshot) on_snapshot();
        out = Value::null();
        return true;
    }
};

struct CustomContext : Context {
    mutable std::vector<gd::SymId> reads;
    explicit CustomContext(gd::BattleCtx* battle) : Context(battle) {}
    bool get_prop(gd::SymId property, Value& out) const override {
        reads.push_back(property);
        return Context::get_prop(property, out);
    }
};

void setup(Context& context, Log& log, gd::BattleCtx& battle, CustomHooks& hooks) {
    context.init_fields(battle);
    context.f_player = Value::from_int(11);
    context.f_opponent = Value::from_int(22);
    context.f_combat_time = Value::from_float(1.25);
    context.f_hooks = Value::from_obj(&hooks);
    log.init_fields(battle);
    log.f__ctx = Value::from_obj(&context);
}

int main() {
    register_gen_syms();
    gd::BattleCtx battle;
    const auto stat = gd::get_prop(battle,
        Gd__gd_core__CoreCharacter::get_static_const_or_enum(battle, SYM_GEN_Stat_870),
        SYM_GEN_Stamina_2673).as_int();
    Context context(&battle);
    Log log(&battle);
    CustomHooks first(&battle), second(&battle);
    setup(context, log, battle, first);
    first.on_snapshot = [&] { context.f_hooks = Value::from_obj(&second); };
    const Value args[] = {Value::null(), Value::null(), Value::from_int(0)};
    const auto event = log.fn_createEvent(args, 3);
    assert(event.kind == Value::Kind::Obj && event.obj && log.f_eventNum.as_int() == 1);
    assert((first.characters == std::vector<int64_t>{11}));
    assert((second.characters == std::vector<int64_t>{22}));
    assert(first.stats[0] == stat && second.stats[0] == stat);

    CustomContext custom(&battle);
    CustomHooks third(&battle);
    setup(custom, log, battle, third);
    log.fn_createEvent(args, 3);
    assert((third.characters == std::vector<int64_t>{11, 22}));
    assert((third.stats == std::vector<int64_t>{stat, stat}));
    assert((custom.reads == std::vector<gd::SymId>{SYM_GEN_combat_time_1306,
        SYM_GEN_player_1302, SYM_GEN_opponent_75, SYM_GEN_hooks_1409, SYM_GEN_hooks_1409}));
    std::cout << "Custom hooks with shared base metadata, callback replacement and observable context getter order passed\n";
}
