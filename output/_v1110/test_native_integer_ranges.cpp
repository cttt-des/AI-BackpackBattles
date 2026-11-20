#include "gen/hdrs/Gd__gd_core__CoreBuff.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

using V = gd::GdVal;
using Buff = Gd__gd_core__CoreBuff;
using Context = Gd__gd_core__CoreContext;

struct Rng : Gd__gd_core__CoreRng {
    std::vector<double> chances;
    bool answer = false;
    std::function<void()> callback;
    explicit Rng(gd::BattleCtx* battle) : Gd__gd_core__CoreRng(battle) {}
    bool call_method(gd::BattleCtx& battle, gd::SymId method, const V* args, int argc, V& out) override {
        if (method != SYM_GEN_flipPercent_1736)
            return Gd__gd_core__CoreRng::call_method(battle, method, args, argc, out);
        assert(argc == 1);
        chances.push_back(args[0].as_float());
        if (callback) callback();
        out = V::from_bool(answer);
        return true;
    }
};

void setup(Buff& buff, Context& context, gd::BattleCtx& battle,
           Gd__gd_core__CoreCharacter& character, Rng& rng) {
    context.init_fields(battle);
    character.init_fields(battle);
    rng.init_fields(battle);
    buff.init_fields(battle);
    context.f_rng = V::from_obj(&rng);
    character.f_ctx = V::from_obj(&context);
    buff.f_ctx = V::from_obj(&context);
    buff.f_character = V::from_obj(&character);
    buff.f_MAX_STACKS = V::from_int(100000);
    buff.f_isBuff = V::from_bool(true);
}

void gain(Buff& buff, int amount) {
    const V args[] = {V::from_int(amount), V::from_float(-1), V::null(), V::null(), V::from_bool(false)};
    buff.fn_gainTemporary(args, 5);
}

int main() {
    register_gen_syms();
    gd::BattleCtx battle;
    Context context(&battle);
    Gd__gd_core__CoreCharacter character(&battle);
    Buff buff(&battle);
    Rng first(&battle), second(&battle);

    setup(buff, context, battle, character, first);
    second.init_fields(battle);
    buff.f_resistChancePercent = V::from_int(75);
    first.callback = [&] { context.f_rng = V::from_obj(&second); };
    gain(buff, 3);
    assert(first.chances.size() == 1 && second.chances.size() == 2);
    assert(buff.f_current.as_int() == 3 && buff.f_permanentStacks.as_int() == 3);

    first.chances.clear(); first.callback = {}; first.answer = true;
    setup(buff, context, battle, character, first);
    buff.f_resistChancePercent = V::from_int(-25);
    gain(buff, 3);
    // Every success increases amount; iteration count must remain the initial three.
    assert(first.chances.size() == 3);
    assert((first.chances == std::vector<double>{25, 25, 25}));
    assert(buff.f_current.as_int() == 6 && buff.f_permanentStacks.as_int() == 6);

    first.chances.clear(); first.answer = false;
    setup(buff, context, battle, character, first);
    buff.f_isBuff = V::from_bool(false);
    buff.f_reflectChancePercent = V::from_int(35);
    first.callback = [&] { buff.f_reflectChancePercent = V::from_int(45); };
    gain(buff, 3);
    assert((first.chances == std::vector<double>{35, 45, 45}));
    assert(buff.f_current.as_int() == 3 && buff.f_permanentStacks.as_int() == 3);

    first.chances.clear(); first.callback = {};
    setup(buff, context, battle, character, first);
    buff.f_resistChancePercent = V::from_int(75);
    gain(buff, 0); gain(buff, -5);
    assert(first.chances.empty() && buff.f_current.as_int() == 0);
    std::cout << "Resistance RNG replacement, amplification snapshot count, reflection changes and nonpositive amounts passed\n";
}
