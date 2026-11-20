"""Count dynamic methods and property symbols on the fixed replay corpus."""
import ctypes
import argparse
import hashlib
import json
from pathlib import Path

from bench_native_corpus import STAGE, load_simulator, measure, prepare, select_cases
from probe_native_serial import insert


def instrument(native):
    path = native / 'gd_rt.cpp'
    source = path.read_text('utf8')
    source = insert(source, 'namespace gd {', after='''
namespace {
thread_local uint64_t dispatch_counts[2][8192]{};
}
extern "C" uint64_t gd_sim_dispatch_count(unsigned category, unsigned symbol) {
    return category < 2 && symbol < 8192 ? dispatch_counts[category][symbol] : 0;
}
extern "C" const char* gd_sim_dispatch_symbol(unsigned symbol) { return sym_name(symbol); }
extern "C" void gd_sim_dispatch_reset() { std::memset(dispatch_counts, 0, sizeof(dispatch_counts)); }
''')
    source = insert(source, 'GdVal call_method(BattleCtx& ctx, const GdVal& recv, SymId m, const GdVal* args, int argc) {',
                    after='\n    if (m < 8192) ++dispatch_counts[0][m];')
    # Match the normal property read entry point, including calls made by generated wrappers.
    import re
    anchor = re.search(r'^GdVal get_prop\(BattleCtx& ctx, const GdVal& \w+, SymId \w+\) \{', source, re.M)
    if not anchor:
        raise ValueError('Property entry point is missing')
    prop = re.search(r'SymId (\w+)', anchor[0])[1]
    source = insert(source, anchor[0], after=f'\n    if ({prop} < 8192) ++dispatch_counts[1][{prop}];')
    path.write_text(source, encoding='utf8', newline='\n')


def inspect(dll, out):
    sim = load_simulator(dll)
    count = sim.lib.gd_sim_dispatch_count
    count.argtypes, count.restype = [ctypes.c_uint, ctypes.c_uint], ctypes.c_uint64
    symbol = sim.lib.gd_sim_dispatch_symbol
    symbol.argtypes, symbol.restype = [ctypes.c_uint], ctypes.c_char_p
    digest = hashlib.sha256()
    jobs = list(prepare(sim, select_cases(200), digest))
    reset = sim.lib.gd_sim_dispatch_reset
    reset.argtypes, reset.restype = [], None
    reset()
    sample = measure(sim, jobs, 1, 0, continuous=True)
    reference = json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert digest.hexdigest() == reference['inputs_sha256']
    assert sample['results_sha256'] == reference['results_sha256']
    report = dict(dll_sha256=hashlib.sha256(dll.read_bytes()).hexdigest(), inputs_sha256=digest.hexdigest(),
                  results_sha256=sample['results_sha256'])
    for category, name in enumerate(('methods', 'properties')):
        rows = [(i, count(category, i)) for i in range(8192)]
        rows.sort(key=lambda row: row[1], reverse=True)
        report[name] = [{'symbol': symbol(i).decode('utf8'), 'id': i, 'calls': n} for i, n in rows if n][:100]
        report[name+'_total'] = sum(n for _, n in rows)
    out.write_text(json.dumps(report, indent=2)+'\n', encoding='utf8')
    for name in ('methods','properties'):
        print(name,report[name][:20],flush=True)


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
