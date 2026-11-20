#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreTimer.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include <cassert>
#include <functional>
#include <iostream>

using Value = gd::GdVal;
using Timer = Gd__gd_core__CoreTimer;
using Item = Gd__gd_core__CoreItem;
using Context = Gd__gd_core__CoreContext;

const gd::GdClassMeta fake_meta{65000, "NativeTimerTestReceiver"};
struct Receiver : gd::GdObj {
    std::function<void()> on_tick;
    int ticks = 0;
    int callbacks = 0;
    mutable int epoch_reads = 0;
    gd::SymId callback;
    explicit Receiver(gd::BattleCtx* ctx) : GdObj(ctx), callback(gd::intern_sym("native_timer_test_callback")) {}
    const gd::GdClassMeta* meta() const override { return &fake_meta; }
    bool get_prop(gd::SymId property, Value& out) const override {
        if (property != SYM_GEN_timer_pass_epoch_1445) return false;
        ++epoch_reads;
        out = Value::from_int(7);
        return true;
    }
    bool call_method(gd::BattleCtx&, gd::SymId method, const Value*, int, Value& out) override {
        if (method == SYM_GEN_tick_1516) {
            ++ticks;
            if (on_tick) on_tick();
        } else if (method == callback) {
            ++callbacks;
        } else return false;
        out = Value::null();
        return true;
    }
};

void setup(Timer& timer, gd::BattleCtx& battle, Context& context, bool stopped = false) {
    timer.init_fields(battle);
    timer.f__ctx = Value::from_obj(&context);
    timer.f__stopped = Value::from_bool(stopped);
    timer.f_wait_time = Value::from_float(0.5);
    timer.f__left = Value::from_float(stopped ? -1.0 : 0.5);
    timer.f__first_pass = Value::from_int(7);
    timer.f__member_epoch = Value::from_int(-1);
    timer.f_one_shot = Value::from_bool(true);
    timer.f_multi = Value::from_bool(false);
}

int main() {
    register_gen_syms();
    gd::BattleCtx battle;
    Context context(&battle);
    context.init_fields(battle);
    context.f_timer_pass_epoch = Value::from_int(7);
    context.f_in_physics_timer_pass = Value::from_bool(true);
    Item item(&battle);
    item.init_fields(battle);
    Receiver before(&battle), owner(&battle);
    Timer timer(&battle), added(&battle);
    const auto delta = Value::from_float(0.25);
    const auto start = Value::from_float(0.5);
    auto timers = [&](std::initializer_list<Value> entries) {
        item.f_timers = Value::from_arr(gd::GdArr::from_init(battle.arena, entries));
    };
    auto tick = [&] { item.fn__tickTimers(&delta, 1); };

    // An earlier callback can make a stopped, previously enrolled timer eligible now.
    setup(timer, battle, context, true);
    timer.f__member_epoch = Value::from_int(7);
    timers({Value::from_obj(&before), Value::from_obj(&timer)});
    before.on_tick = [&] { timer.fn_start(&start, 1); };
    tick();
    assert(timer.f__left.as_float() == 0.25 && !gd::gd_truth(timer.f__stopped));

    // A newly started timer without current membership waits for the next epoch.
    setup(timer, battle, context, true);
    tick();
    assert(timer.f__left.as_float() == 0.5 && timer.f__first_pass.as_int() == 8);
    before.on_tick = {};
    context.f_timer_pass_epoch = Value::from_int(8);
    tick();
    assert(timer.f__left.as_float() == 0.25);
    context.f_timer_pass_epoch = Value::from_int(7);

    setup(timer, battle, context);
    before.on_tick = [&] { timer.fn_stop(nullptr, 0); };
    tick();
    assert(gd::gd_truth(timer.f__stopped) && timer.f__left.as_float() == -1.0);

    setup(timer, battle, context);
    before.on_tick = [&] { timer.fn_stop(nullptr, 0); timer.fn_start(&start, 1); };
    tick();
    assert(!gd::gd_truth(timer.f__stopped) && timer.f__left.as_float() == 0.25);

    // Array growth preserves the captured length; replacing a future slot is visible.
    setup(added, battle, context);
    timers({Value::from_obj(&before)});
    before.on_tick = [&] { item.f_timers.arr->push_back(battle.arena, Value::from_obj(&added)); };
    tick();
    assert(added.f__left.as_float() == 0.5 && item.f_timers.arr->len == 2);
    before.on_tick = {};
    tick();
    assert(added.f__left.as_float() == 0.25);

    setup(timer, battle, context);
    setup(added, battle, context);
    timers({Value::from_obj(&before), Value::from_obj(&timer)});
    before.on_tick = [&] { item.f_timers.arr->set_idx(1, Value::from_obj(&added)); };
    tick();
    assert(timer.f__left.as_float() == 0.5 && added.f__left.as_float() == 0.25);
    before.on_tick = {};

    setup(timer, battle, context);
    timer.f__left = Value::from_float(0.125);
    timer.f__owner = Value::from_obj(&owner);
    timer.f_callback_method = Value::from_cstr(battle.arena, "native_timer_test_callback");
    timers({Value::from_obj(&timer), Value::null()});
    tick();
    assert(owner.callbacks == 1 && timer.f_fire_count.as_int() == 1);
    assert(gd::gd_truth(timer.f__stopped) && timer.f__left.as_float() == -1.0);

    // The generic truth and context-property paths remain observable.
    for (const auto& state : {Value::from_int(0), Value::from_float(0.0), Value::from_int(1),
                             Value::from_cstr(battle.arena, ""), Value::from_vec2(0.0, 1.0)}) {
        setup(timer, battle, context);
        timer.f__stopped = state;
        timer.f__ctx = Value::null();
        timer.f__left = Value::from_float(1.0);
        timers({Value::from_obj(&timer)});
        tick();
        assert(timer.f__left.as_float() == (gd::gd_truth(state) ? 1.0 : 0.75));
    }
    setup(timer, battle, context);
    timer.f__ctx = Value::from_obj(&owner);
    timers({Value::from_obj(&timer)});
    tick();
    assert(owner.epoch_reads == 1 && timer.f__left.as_float() == 0.25);
    timer.f__stopped = Value::from_bool(true);
    tick();
    assert(owner.epoch_reads == 1);
    std::cout << "Timer start, stop, restart, first epoch, append, replacement, timeout, truth and generic context cases passed\n";
}
