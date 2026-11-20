"""Count the three Buff integer loops without changing their iteration or RNG calls."""
import argparse
import ctypes
import hashlib
import json
from pathlib import Path

from bench_native_corpus import STAGE, load_simulator, measure, prepare, select_cases
from optimize_native_integer_ranges import SITES, blocks, original


COUNTERS = '''
namespace {
thread_local uint64_t native_buff_range_counts[12]{};
void native_buff_range_probe(unsigned site, const gd::GdVal& value) {
    auto* counts = native_buff_range_counts + 4 * site;
    ++counts[0];
    if (value.kind != gd::GdVal::Kind::Int) ++counts[3];
    else if (value.i <= 0) ++counts[2];
    else counts[1] += static_cast<uint64_t>(value.i);
}
}
extern "C" uint64_t gd_sim_buff_range_stat(unsigned index) {
    return index < 12 ? native_buff_range_counts[index] : 0;
}
extern "C" void gd_sim_buff_range_reset() {
    for (auto& value : native_buff_range_counts) value = 0;
}
'''


def instrument(native):
    path, source, method, body = original(native)
    assert "native_buff_range_probe" not in source
    for index, site in enumerate(SITES):
        old, _ = blocks(site)
        body = body.replace(old, " " * site[3] + f"native_buff_range_probe({index}, lv_amount);\n" + old, 1)
    source = source[:method.start()] + body + source[method.end():]
    path.write_text('#include "../../gd_rt.hpp"\n' + COUNTERS + source, encoding="utf8", newline="\n")


def inspect(dll, out):
    sim = load_simulator(dll)
    signature = hashlib.sha256()
    jobs = list(prepare(sim, select_cases(200), signature))
    reset = sim.lib.gd_sim_buff_range_reset
    reset.argtypes, reset.restype = [], None
    read = sim.lib.gd_sim_buff_range_stat
    read.argtypes, read.restype = [ctypes.c_uint], ctypes.c_uint64
    reset()
    result = measure(sim, jobs, 1, 0, continuous=True)
    reference = json.loads((STAGE / "native_perf50_event_bus_serial.json").read_bytes())
    assert signature.hexdigest() == reference["inputs_sha256"]
    assert result["results_sha256"] == reference["results_sha256"]
    names = [f"{site}_{field}" for site in ("resistance", "amplification", "reflection")
             for field in ("calls", "iterations", "nonpositive", "noninteger")]
    report = {"diagnostic_only": True, "dll_sha256": hashlib.sha256(dll.read_bytes()).hexdigest(),
              "inputs_sha256": signature.hexdigest(), "results_sha256": result["results_sha256"],
              "counts": dict(zip(names, (read(i) for i in range(12)), strict=True))}
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
