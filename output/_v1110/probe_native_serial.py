"""Instrument isolated C++ sources or measure phase counters from a probe DLL."""
import argparse
import ctypes
import hashlib
import json
from pathlib import Path
import time

from bench_native_corpus import STAGE, load_simulator, measure, prepare, select_cases
from optimize_native_serial_paths import method_body, optimize


COUNTERS = (
    "assembly_ns", "battle_ns", "export_ns", "battles",
    "idle_calls", "idle_empty", "delay_calls", "delay_empty", "motion_calls", "motion_empty",
    "timer_candidates", "timer_nonempty",
    "descriptor_build_ns", "side_item_build_ns", "timer_creations", "timer_start_requests",
    "timer_restart_requests", "timer_stop_requests", "timer_creations_in_pass",
    "timer_start_requests_in_pass", "timer_restart_requests_in_pass", "timer_stop_requests_in_pass",
)
PROBE_CODE = """#include <chrono>
#include <cstdint>
namespace {
using SerialClock = std::chrono::steady_clock;
thread_local uint64_t serial_probe[22]{};
uint64_t serial_elapsed(SerialClock::time_point begin, SerialClock::time_point end) {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
}
}
void gd_serial_probe_queue(unsigned queue, bool empty) {
    ++serial_probe[4 + queue * 2];
    serial_probe[5 + queue * 2] += empty;
}
void gd_serial_probe_timer(bool nonempty) {
    ++serial_probe[10];
    serial_probe[11] += nonempty;
}
void gd_serial_probe_timer_change(unsigned operation, bool in_pass) {
    ++serial_probe[14 + operation];
    serial_probe[18 + operation] += in_pass;
}
extern "C" uint64_t gd_sim_serial_probe_get(unsigned counter) { return serial_probe[counter]; }
"""


def insert(source, anchor, *, before="", after=""):
    if source.count(anchor) != 1:
        raise ValueError(f"Expected one instrumentation anchor: {anchor!r}")
    return source.replace(anchor, before + anchor + after)


def instrument(native):
    optimize(native, "probe")
    wrapper = native / "engine_wrapper.cpp"
    source = wrapper.read_text("utf8")
    source = insert(source, "    std::memset(&out, 0, sizeof(BattleResult));",
                    before="    const auto serial_assembly_start = SerialClock::now();\n")
    source = insert(source, "    while (!gd::gd_truth(combat_obj->f_fight_ended) && ticks < max_ticks) {",
                    before="    const auto serial_battle_start = SerialClock::now();\n")
    source = insert(source, "    std::vector<Gd__gd_core__CoreItemData*> descr_cache(g_items.size(), nullptr);",
                    before="    const auto serial_descr_start = SerialClock::now();\n")
    anchor = "    register_side_descriptors(battle, book, opponent_side, descr_cache);\n"
    source = insert(source, anchor,
                    after="    serial_probe[12] += serial_elapsed(serial_descr_start, SerialClock::now());\n")
    source = insert(source, "    build_side_items(\n        battle, ctx_val.obj, p_chr,",
                    before="    const auto serial_player_items_start = SerialClock::now();\n")
    anchor = "        opts.record_per_item ? &p_item_ptrs : nullptr);\n"
    source = insert(source, anchor,
                    after="    serial_probe[13] += serial_elapsed(serial_player_items_start, SerialClock::now());\n")
    anchor = ("    build_side_items(battle, ctx_val.obj, o_chr, 3 /* Opponent */, "
              "opponent_side, descr_cache, o_items, nullptr);\n")
    source = insert(source, anchor,
                    before="    const auto serial_opponent_items_start = SerialClock::now();\n",
                    after="    serial_probe[13] += serial_elapsed(serial_opponent_items_start, SerialClock::now());\n")
    source = insert(source, "\n    if (g_dbg_item_origins && g_dbg_enabled.load(std::memory_order_relaxed))",
                    before="\n    const auto serial_export_start = SerialClock::now();\n")
    source = insert(source, "\n}\n\nstatic thread_local gd::BattleCtx tl_battle_ctx",
                    before="\n    serial_probe[0] += serial_elapsed(serial_assembly_start, serial_battle_start);"
                    "\n    serial_probe[1] += serial_elapsed(serial_battle_start, serial_export_start);"
                    "\n    serial_probe[2] += serial_elapsed(serial_export_start, SerialClock::now());"
                    "\n    ++serial_probe[3];")
    wrapper.write_text(PROBE_CODE + source, encoding="utf8", newline="\n")
    timers = native / "gen/shards/shard_03.cpp"
    source = timers.read_text("utf8")
    for name, indent in (("item", 8), ("gem", 16)):
        spaces = " " * indent
        anchor = f"{spaces}if ({name}->f_timers.arr->len) {name}->fn__tickTimers(&delta, 1);"
        source = insert(source, anchor, before=f"{spaces}gd_serial_probe_timer({name}->f_timers.arr->len != 0);\n")
    timers.write_text("void gd_serial_probe_timer(bool);\n" + source, encoding="utf8", newline="\n")
    for shard, owner, methods in (
        ("00", "CoreItem", (("newItemTimer", "ctx", "0"),)),
        ("06", "CoreTimer", (("start", "_ctx", "gd::gd_truth(this->f__stopped) ? 1 : 2"),
                             ("stopCountdownForTimeout", "_ctx", "3"))),
    ):
        path = native / f"gen/shards/shard_{shard}.cpp"
        source = path.read_text("utf8")
        for method, field, operation in methods:
            match = method_body(source, owner, method)
            anchor = "    gd::BattleCtx& gd_ctx = *this->rt_ctx_;\n"
            call = (f"    gd_serial_probe_timer_change({operation},\n"
                    f"        !this->f_{field}.is_null() && gd::gd_truth(\n"
                    f"            gd::get_prop(gd_ctx, this->f_{field}, SYM_GEN_in_physics_timer_pass_1446)));\n")
            body = insert(match[1], anchor, after=call)
            source = source[:match.start(1)] + body + source[match.end(1):]
        path.write_text("void gd_serial_probe_timer_change(unsigned, bool);\n" + source,
                        encoding="utf8", newline="\n")


def inspect(dll):
    sim = load_simulator(dll)
    get = sim.lib.gd_sim_serial_probe_get
    get.argtypes, get.restype = [ctypes.c_uint], ctypes.c_uint64
    digest = hashlib.sha256()
    jobs = list(prepare(sim, select_cases(200), digest))
    native_ns = 0

    def timed(entry):
        def call(*args):
            nonlocal native_ns
            start = time.perf_counter_ns()
            try:
                return entry(*args)
            finally:
                native_ns += time.perf_counter_ns() - start
        return call

    for name in ("gd_sim_run_one", "gd_sim_run_one_replay_v2", "gd_sim_run_one_replay_buff_state",
                 "gd_sim_run_one_replay_engine_rng", "gd_sim_run_one_replay_scene_delays",
                 "gd_sim_run_one_replay_native_clock", "gd_sim_run_one_replay_host_phases"):
        setattr(sim.lib, name, timed(getattr(sim.lib, name)))
    sample = measure(sim, jobs, 1, 0, continuous=True)
    result = dict(zip(COUNTERS, (get(i) for i in range(len(COUNTERS))), strict=True))
    reference = json.loads((STAGE / "native_perf50_event_bus_serial.json").read_bytes())
    if (result["battles"] != len(jobs) or sample["results_sha256"] != reference["results_sha256"]
            or digest.hexdigest() != reference["inputs_sha256"]):
        raise ValueError("Probe no longer reproduces the benchmark")
    wall_ns = round(sample["wall_s"] * 1e9)
    measured_native = result["assembly_ns"] + result["battle_ns"] + result["export_ns"]
    return {"dll_sha256": hashlib.sha256(dll.read_bytes()).hexdigest(), "inputs_sha256": digest.hexdigest(),
            "results_sha256": sample["results_sha256"], "wall_ns": wall_ns, "native_call_ns": native_ns,
            "python_outside_native_call_ns": wall_ns - native_ns,
            "python_ffi_and_native_entry_ns": wall_ns - measured_native, **result}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--instrument", type=Path)
    mode.add_argument("--dll", type=Path)
    parser.add_argument("--out", type=Path)
    args = parser.parse_args()
    if args.instrument:
        instrument(args.instrument)
    elif args.out:
        result = inspect(args.dll)
        args.out.write_text(json.dumps(result, indent=2) + "\n", encoding="utf8")
        print(json.dumps(result, indent=2))
    else:
        parser.error("--dll requires --out")
