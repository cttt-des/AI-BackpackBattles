"""Measure array mutations while evaluating reuse of a timer-owner index."""
import argparse
import ctypes
import hashlib
import json
from pathlib import Path
import re

from bench_native_corpus import STAGE, load_simulator, measure, prepare, select_cases
from probe_native_serial import insert


CODE = '''
namespace {
thread_local uint64_t timer_array_epoch = 1;
thread_local uint64_t timer_index_counts[3]{};
struct TimerIndexCheckpoint { const void* character = nullptr; uint64_t epoch = 0; };
thread_local TimerIndexCheckpoint timer_index_checkpoints[2];
}
void gd_timer_index_probe_mutate() { ++timer_array_epoch; ++timer_index_counts[2]; }
void gd_timer_index_probe_new_combat() {
    for (auto& checkpoint : timer_index_checkpoints) checkpoint = {};
}
void gd_timer_index_probe_visit(const void* character) {
    auto* checkpoint = &timer_index_checkpoints[0];
    for (auto& possible : timer_index_checkpoints) {
        if (!possible.character || possible.character == character) { checkpoint = &possible; break; }
    }
    ++timer_index_counts[0];
    if (checkpoint->character == character && checkpoint->epoch == timer_array_epoch) ++timer_index_counts[1];
    *checkpoint = {character, timer_array_epoch};
}
extern "C" uint64_t gd_sim_timer_index_stat(unsigned index) {
    return index < 3 ? timer_index_counts[index] : 0;
}
extern "C" void gd_sim_timer_index_reset() {
    for (auto& count : timer_index_counts) count = 0;
    gd_timer_index_probe_new_combat();
}
'''


def instrument(native):
    path = native / "gd_rt.cpp"
    source = path.read_text("utf8")
    source = insert(source, "namespace gd {\n", before=CODE)
    methods = ("push_back", "insert_at", "pop_at", "append_array", "pop_front", "pop_back",
               "remove_at", "erase_val", "resize", "fill", "invert", "set_idx")
    for method in methods:
        source, count = re.subn(rf"^((?:void|GdVal) GdArr::{method}\([^\n]*\{{)\n",
                                r"\1\n    gd_timer_index_probe_mutate();\n", source, flags=re.M)
        if count != 1:
            raise ValueError(f"Expected one array mutator {method}")
    source = insert(source, "case SYM_clear: a->len = 0;", after=" gd_timer_index_probe_mutate();")
    for method in ("shuffle", "sort_custom"):
        source = insert(source, f"case SYM_{method}:\n", after="                    gd_timer_index_probe_mutate();\n")
    symbols = (native / "gen/sym_ids.hpp").read_text("utf8")
    relevant = []
    for name in ("inventory", "items", "timers", "gems"):
        matches = set(re.findall(rf"\bSYM_GEN_{name}_\d+\b", symbols))
        if len(matches) != 1:
            raise ValueError(f"Unexpected symbol IDs for {name}")
        relevant.extend(matches)
    source = insert(source, "void set_prop(BattleCtx& ctx, GdVal& recv, SymId prop, const GdVal& val) {\n",
                    after="    if (" + " || ".join("prop == " + name for name in relevant) + ") gd_timer_index_probe_mutate();\n")
    source = '#include "gen/sym_ids.hpp"\n' + source
    path.write_text(source, encoding="utf8", newline="\n")
    path = native / "gen/shards/shard_03.cpp"
    source = path.read_text("utf8")
    source = ("extern void gd_timer_index_probe_new_combat();\n"
              "extern void gd_timer_index_probe_visit(const void* character);\n") + source
    source = insert(source, "void Gd__gd_core__CoreCombat::init_fields(gd::BattleCtx& gd_ctx) {\n",
                    after="    gd_timer_index_probe_new_combat();\n")
    source = insert(source, "    character->fn_tickBuffs(&delta, 1);\n",
                    after="    gd_timer_index_probe_visit(character);\n")
    path.write_text(source, encoding="utf8", newline="\n")


def inspect(dll, out):
    sim = load_simulator(dll)
    signature = hashlib.sha256()
    jobs = list(prepare(sim, select_cases(200), signature))
    reset = sim.lib.gd_sim_timer_index_reset
    reset.argtypes, reset.restype = [], None
    read = sim.lib.gd_sim_timer_index_stat
    read.argtypes, read.restype = [ctypes.c_uint], ctypes.c_uint64
    reset()
    result = measure(sim, jobs, 1, 0, continuous=True)
    reference = json.loads((STAGE / "native_perf50_event_bus_serial.json").read_bytes())
    assert signature.hexdigest() == reference["inputs_sha256"]
    assert result["results_sha256"] == reference["results_sha256"]
    values = dict(zip(("character_timer_passes", "unchanged_epoch_passes", "array_mutations"),
                      (read(i) for i in range(3)), strict=True))
    report = dict(dll_sha256=hashlib.sha256(dll.read_bytes()).hexdigest(),
                  inputs_sha256=signature.hexdigest(), results_sha256=result["results_sha256"],
                  counts=values, unchanged_epoch_fraction=values["unchanged_epoch_passes"] / values["character_timer_passes"],
                  diagnostic_only=True,
                  mutation_scope="Array mutators, clear/shuffle/sort_custom and generic inventory/items/timers/gems setters; direct generated field assignments are not covered")
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
