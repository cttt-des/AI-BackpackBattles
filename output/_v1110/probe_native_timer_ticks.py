"""Count stopped and not-yet-eligible CoreTimer ticks on the fixed replay corpus."""
import argparse
import ctypes
import hashlib
import json
from pathlib import Path

from bench_native_corpus import STAGE, load_simulator, measure, prepare, select_cases
from probe_native_serial import insert


COUNTERS = '''
namespace {
thread_local uint64_t native_timer_ticks[6]{};
}
extern "C" uint64_t gd_sim_timer_tick_stat(unsigned index) {
    return index < 6 ? native_timer_ticks[index] : 0;
}
extern "C" void gd_sim_timer_tick_reset() {
    for (auto& counter : native_timer_ticks) counter = 0;
}
'''
ENTRY = '''
    ++native_timer_ticks[0];
    native_timer_ticks[1] += gd::gd_truth(this->f__stopped);
    native_timer_ticks[2] += this->f__stopped.kind == gd::GdVal::Kind::Bool;
    if (!gd::gd_truth(this->f__stopped)) {
        const auto& context = this->f__ctx;
        if (context.kind == gd::GdVal::Kind::Obj && context.obj &&
                context.obj->meta() == &META_Gd__gd_core__CoreContext) {
            ++native_timer_ticks[3];
            auto* typed = static_cast<Gd__gd_core__CoreContext*>(context.obj);
            native_timer_ticks[4] += gd::gd_lt(typed->f_timer_pass_epoch, this->f__first_pass);
        } else {
            ++native_timer_ticks[5];
        }
    }
'''


def instrument(native):
    path = native / "gen/shards/shard_06.cpp"
    source = path.read_text("utf8")
    header = '#include "../hdrs/Gd__gd_core__CoreContext.hpp"\n'
    if header not in source:
        source = header + source
    anchor = "gd::GdVal Gd__gd_core__CoreTimer::fn_tick(const gd::GdVal* _args, int _argc) {"
    source = insert(source, anchor, before=COUNTERS, after=ENTRY)
    path.write_text(source, encoding="utf8", newline="\n")


def inspect(dll, out):
    sim = load_simulator(dll)
    signature = hashlib.sha256()
    jobs = list(prepare(sim, select_cases(200), signature))
    reset = sim.lib.gd_sim_timer_tick_reset
    reset.argtypes, reset.restype = [], None
    read = sim.lib.gd_sim_timer_tick_stat
    read.argtypes, read.restype = [ctypes.c_uint], ctypes.c_uint64
    reset()
    result = measure(sim, jobs, 1, 0, continuous=True)
    reference = json.loads((STAGE / "native_perf50_event_bus_serial.json").read_bytes())
    assert signature.hexdigest() == reference["inputs_sha256"]
    assert result["results_sha256"] == reference["results_sha256"]
    values = dict(zip(("ticks", "stopped", "boolean_stopped_state", "active_exact_context",
                       "active_waiting_for_first_pass", "active_other_context"),
                      (read(i) for i in range(6)), strict=True))
    report = dict(dll_sha256=hashlib.sha256(dll.read_bytes()).hexdigest(),
                  inputs_sha256=signature.hexdigest(), results_sha256=result["results_sha256"],
                  counts=values, diagnostic_only=True)
    out.write_text(json.dumps(report, indent=2) + "\n", encoding="utf8")
    print(json.dumps(report, indent=2))


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
        inspect(args.dll, args.out)
    else:
        parser.error("--dll requires --out")
