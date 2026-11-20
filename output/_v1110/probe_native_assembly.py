"""Measure disjoint item and gem assembly phases in an isolated wrapper."""
import argparse
import ctypes
import hashlib
import json
from pathlib import Path

from bench_native_corpus import STAGE, load_simulator, measure, prepare, select_cases
from probe_native_serial import insert

COUNTERS = ('construction_ns', 'setup_ns', 'ready_ns', 'geometry_ns', 'placement_ns',
            'effects_ns', 'gem_attachment_ns', 'assembly_ns', 'objects', 'items', 'gems', 'effects')
CODE = '''#include <chrono>
namespace {
using AssemblyClock = std::chrono::steady_clock;
thread_local unsigned long long assembly_counts[12]{};
struct AssemblyTimer {
    unsigned slot;
    AssemblyClock::time_point begin = AssemblyClock::now();
    ~AssemblyTimer() { assembly_counts[slot] += std::chrono::duration_cast<std::chrono::nanoseconds>(AssemblyClock::now()-begin).count(); }
};
}
extern "C" unsigned long long gd_sim_assembly_counter(unsigned i) { return assembly_counts[i]; }
'''


def instrument(native):
    path = native / 'engine_wrapper.cpp'
    source = path.read_text('utf8')
    source = insert(source, '    gd::GdVal iv = gd::construct_class(battle, proto.cls, nullptr, 0);',
                    before='    const auto construct_begin = AssemblyClock::now();\n',
                    after='\n    assembly_counts[0] += std::chrono::duration_cast<std::chrono::nanoseconds>(AssemblyClock::now()-construct_begin).count();\n    ++assembly_counts[8];')
    source = insert(source, '    if (crafted >= 0) {', before='    const auto setup_begin = AssemblyClock::now();\n')
    source = insert(source, '    gd::call_method(battle, iv, g_syms._readyInit, nullptr, 0);',
                    before='    assembly_counts[1] += std::chrono::duration_cast<std::chrono::nanoseconds>(AssemblyClock::now()-setup_begin).count();\n    AssemblyTimer ready_timer{2};\n')
    source = insert(source, '    const int16_t* ptr = xy + static_cast<size_t>(off) * 2;',
                    before='    AssemblyTimer geometry_timer{3};\n')
    source = insert(source, '    auto* entries = gd::GdArr::create(battle.arena, count);',
                    before='    AssemblyTimer effects_timer{5};\n    assembly_counts[11] += count;\n')
    source = insert(source, '    std::vector<Gd__gd_core__CoreItem*>* record_items\n) {\n',
                    after='    AssemblyTimer assembly_timer{7};\n')
    source = insert(source, '        if (iv.is_null()) continue;', after='\n        ++assembly_counts[9];')
    for anchor, slot, count in (
        ('        gd::call_method(battle, chr->f_inventory, g_syms.addItem, add_args, 2);', 4, ''),
        ('            gd::call_method(battle, iv, g_syms.setGem, sg_args, 2);', 6, ' ++assembly_counts[10];'),
    ):
        source = insert(source, anchor, before='        { AssemblyTimer phase_timer{' + str(slot) + '};\n',
                        after=count+'\n        }')
    path.write_text(CODE + source, encoding='utf8', newline='\n')


def inspect(dll, out):
    sim = load_simulator(dll)
    get = sim.lib.gd_sim_assembly_counter
    get.argtypes, get.restype = [ctypes.c_uint], ctypes.c_ulonglong
    digest = hashlib.sha256()
    jobs = list(prepare(sim, select_cases(200), digest))
    sample = measure(sim, jobs, 1, 0, continuous=True)
    reference = json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert sample['results_sha256'] == reference['results_sha256']
    assert digest.hexdigest() == reference['inputs_sha256']
    counts = dict(zip(COUNTERS, (get(i) for i in range(len(COUNTERS)))))
    report = dict(dll_sha256=hashlib.sha256(dll.read_bytes()).hexdigest(),
                  inputs_sha256=digest.hexdigest(), results_sha256=sample['results_sha256'],
                  wall_s=sample['wall_s'], **counts)
    out.write_text(json.dumps(report, indent=2)+'\n', encoding='utf8')
    print(json.dumps(report, indent=2), flush=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument('--instrument', type=Path)
    mode.add_argument('--dll', type=Path)
    parser.add_argument('--out', type=Path)
    args = parser.parse_args()
    if args.instrument:
        instrument(args.instrument)
    elif args.out:
        inspect(args.dll, args.out)
    else:
        parser.error('--dll requires --out')
