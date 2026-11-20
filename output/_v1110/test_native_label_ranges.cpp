#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

using V = gd::GdVal;
using ItemBase = Gd__gd_core__CoreItem;

struct Item : ItemBase {
    int character_calls = 0;
    explicit Item(gd::BattleCtx* battle) : ItemBase(battle) {}
    bool call_method(gd::BattleCtx& battle, gd::SymId method, const V* args, int argc, V& out) override {
        if (method == SYM_GEN_character_74) {
            ++character_calls;
            out = f_character_;
            return true;
        }
        return ItemBase::call_method(battle, method, args, argc, out);
    }
};

struct Context : Gd__gd_core__CoreContext {
    mutable int time_reads = 0;
    std::function<void(int)> on_time;
    explicit Context(gd::BattleCtx* battle) : Gd__gd_core__CoreContext(battle) {}
    bool get_prop(gd::SymId property, V& out) const override {
        if (property == SYM_GEN_time_1411) {
            ++time_reads;
            if (on_time) on_time(time_reads);
        }
        return Gd__gd_core__CoreContext::get_prop(property, out);
    }
};

struct Rng : Gd__gd_core__CoreRng {
    std::vector<double> bounds;
    std::vector<char> order;
    explicit Rng(gd::BattleCtx* battle) : Gd__gd_core__CoreRng(battle) {}
    bool call_method(gd::BattleCtx& battle, gd::SymId method, const V* args, int argc, V& out) override {
        if (method == SYM_GEN_trace_diag_1741) {
            order.push_back('T'); out = V::null(); return true;
        }
        if (method == gd::SYM_randf_range) {
            assert(argc == 2);
            bounds.push_back(args[0].as_float()); bounds.push_back(args[1].as_float());
            order.push_back('R'); out = V::from_float(0); return true;
        }
        return Gd__gd_core__CoreRng::call_method(battle, method, args, argc, out);
    }
};

int main() {
    register_gen_syms();
    gd::BattleCtx battle;
    auto& arena = battle.arena;
    Context context(&battle); context.init_fields(battle);
    Gd__gd_core__CoreCharacter character(&battle); character.init_fields(battle);
    Rng rng(&battle); rng.init_fields(battle);
    Item item(&battle); item.init_fields(battle);
    item.f_ctx = V::from_obj(&context);
    item.f_character_ = V::from_obj(&character);
    context.f_rng = V::from_obj(&rng);
    context.f_time = V::from_float(1.0);

    auto array = [&](std::initializer_list<double> values) {
        auto* result = gd::GdArr::create(arena);
        for (double value : values) result->push_back(arena, V::from_float(value));
        return result;
    };
    auto run = [&](double bound, int reads) {
        context.time_reads = 0; item.character_calls = 0;
        rng.bounds.clear(); rng.order.clear();
        item.fn_getNextFreeLabelPosition(nullptr, 0);
        assert((rng.bounds == std::vector<double>{-bound, bound, -bound, bound}));
        assert((rng.order == std::vector<char>{'T', 'R', 'R'}));
        assert(item.character_calls == 2 && context.time_reads == reads);
    };

    auto* stamps = array({0, 0, 0, 0, 0});
    item.f_buffLabelPositionTimestamps = V::from_arr(stamps);
    run(10, 2); assert(stamps->data[0].as_float() == 1.5);

    stamps = array({5, 5, 0, 5, 5});
    item.f_buffLabelPositionTimestamps = V::from_arr(stamps);
    run(10, 4); assert(stamps->data[2].as_float() == 1.5);

    item.f_buffLabelPositionTimestamps = V::from_arr(array({5, 5, 5, 5, 5}));
    run(30, 5);
    item.f_buffLabelPositionTimestamps = V::from_arr(array({}));
    run(30, 0);

    stamps = array({5, 5});
    item.f_buffLabelPositionTimestamps = V::from_arr(stamps);
    context.on_time = [&](int reads) { if (reads == 1) stamps->push_back(arena, V::from_float(0)); };
    run(30, 2); assert(stamps->len == 3 && stamps->data[2].as_float() == 0);

    stamps = array({5, 5});
    item.f_buffLabelPositionTimestamps = V::from_arr(stamps);
    context.on_time = [&](int reads) { if (reads == 1) stamps->set_idx(1, V::from_float(0)); };
    run(10, 3); assert(stamps->data[1].as_float() == 1.5);

    item.f_buffLabelPositionTimestamps = V::from_arr(array({5, 5}));
    auto* replacement = array({5, 0, 0, 0});
    context.on_time = [&](int reads) {
        if (reads == 1) item.f_buffLabelPositionTimestamps = V::from_arr(replacement);
    };
    run(10, 3); assert(replacement->data[1].as_float() == 1.5);

    context.on_time = {};
    auto* dictionary = gd::GdDict::create(arena);
    dictionary->set(arena, V::from_int(0), V::from_float(5));
    dictionary->set(arena, V::from_int(1), V::from_float(0));
    item.f_buffLabelPositionTimestamps = V::from_dict(dictionary);
    run(10, 3); assert(dictionary->get(V::from_int(1)).as_float() == 1.5);
    item.f_buffLabelPositionTimestamps = V::null();
    run(30, 0);
    std::cout << "Label slot selection, callback order, RNG bounds, captured size, future writes, replacement and dynamic fallback passed\n";
}
