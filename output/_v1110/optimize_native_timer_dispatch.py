"""Specialize the item-to-CoreTimer tick chain with exact-type fallbacks."""
import argparse
from pathlib import Path

from optimize_native_frames import checked_method


ITEM = "Gd__gd_core__CoreItem"
TIMER = "Gd__gd_core__CoreTimer"
CONTEXT = "Gd__gd_core__CoreContext"

TICK = '''gd::GdVal Gd__gd_core__CoreTimer::fn_tick(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth(this->f__stopped)) return gd::GdVal::null();
    if (!this->f__ctx.is_null()) {
        const auto& context = this->f__ctx;
        const gd::GdVal epoch = context.kind == gd::GdVal::Kind::Obj && context.obj &&
                context.obj->meta() == &META_Gd__gd_core__CoreContext
            ? static_cast<Gd__gd_core__CoreContext*>(context.obj)->f_timer_pass_epoch
            : gd::get_prop(gd_ctx, context, SYM_GEN_timer_pass_epoch_1445);
        if (gd::gd_lt(epoch, this->f__first_pass)) return gd::GdVal::null();
    }
    this->f__left = gd::gd_sub(this->f__left, lv_delta);
    if (gd::gd_lt(this->f__left, gd::GdVal::from_float(0.0)))
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__onTimeout_1783, nullptr, 0);
    return gd::GdVal::null();
}
'''


def include(source, owner):
    header = f'#include "../hdrs/{owner}.hpp"\n'
    return source if header in source else header + source


def optimize(native, part="all"):
    shards = native / "gen/shards"
    timer_source = (shards / "shard_06.cpp").read_text("utf8")
    forwarding = "case SYM_GEN_tick_1516: out = fn_tick(args, argc); return true;"
    if timer_source.count(forwarding) != 1:
        raise ValueError("The CoreTimer tick dispatcher changed")
    updates = {}
    if part in ("dispatch", "all"):
        path = shards / "shard_00.cpp"
        source = path.read_text("utf8")
        method = checked_method(source, ITEM, "_tickTimers",
                                "29a65a2ede44d1d5111ba3e2ed0266e1f98294a91bc999e2f0767e515112a723")
        original = "            (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::call_method(gd_ctx, lv_t, SYM_GEN_tick_1516, _ca, 1); })();"
        if method[0].count(original) != 1:
            raise ValueError("The item timer loop changed")
        fast = '''            if (lv_t.kind == gd::GdVal::Kind::Obj && lv_t.obj &&
                    lv_t.obj->meta() == &META_Gd__gd_core__CoreTimer) {
                auto* timer = static_cast<Gd__gd_core__CoreTimer*>(lv_t.obj);
                if (!gd::gd_truth(timer->f__stopped)) timer->fn_tick(&lv_delta, 1);
            } else {
''' + original + '''
            }'''
        body = method[0].replace(original, fast)
        updates[path] = include(source[:method.start()] + body + source[method.end():], TIMER)
    if part in ("tick", "all"):
        context_source = (shards / "shard_07.cpp").read_text("utf8")
        if "case SYM_GEN_timer_pass_epoch_1445: out = this->f_timer_pass_epoch; return true;" not in context_source:
            raise ValueError("The context epoch getter changed")
        method = checked_method(timer_source, TIMER, "tick",
                                "07e1677e4a8e373db0a506dca6767cedcf1226fd52f2213ec93f8dbf786ba211")
        updates[shards / "shard_06.cpp"] = include(
            timer_source[:method.start()] + TICK + timer_source[method.end():], CONTEXT)
    for path, source in updates.items():
        path.write_text(source, encoding="utf8", newline="\n")
    print(f"Specialized timer chain ({part}); loop order, snapshots and non-CoreTimer receivers retain their paths", flush=True)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("native", type=Path)
    parser.add_argument("--part", choices=("dispatch", "tick", "all"), default="all")
    args = parser.parse_args()
    optimize(args.native, args.part)
