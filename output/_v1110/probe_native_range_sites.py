"""Locate native integer-iteration materialization by caller, without changing its behavior."""
import argparse
from bisect import bisect_right
import ctypes
import hashlib
import json
from pathlib import Path
import shutil
import struct
import subprocess
import tempfile

from bench_native_corpus import STAGE, load_simulator, measure, prepare, select_cases
from optimize_native_integer_ranges import ITERATOR_HASH

COUNTERS = '''
namespace {
struct NativeRangeSite { uint64_t site=0, calls=0, elements=0, nonpositive=0, maximum=0; };
thread_local NativeRangeSite native_range_sites[256];
thread_local uint64_t native_range_overflow=0;
void native_range_site_probe(uintptr_t caller, int64_t count) {
    for (auto& row : native_range_sites) {
        if (!row.site || row.site == caller) {
            row.site = caller;
            ++row.calls;
            if (count <= 0) ++row.nonpositive;
            else {
                row.elements += static_cast<uint64_t>(count);
                if (static_cast<uint64_t>(count) > row.maximum) row.maximum = static_cast<uint64_t>(count);
            }
            return;
        }
    }
    ++native_range_overflow;
}
}
extern "C" uint64_t gd_sim_range_site_stat(unsigned index, unsigned field) {
    if (index == 256) return native_range_overflow;
    if (index > 256) return 0;
    const auto& row=native_range_sites[index];
    switch(field) {
        case 0: return row.site;
        case 1: return row.calls;
        case 2: return row.elements;
        case 3: return row.nonpositive;
        case 4: return row.maximum;
        default: return 0;
    }
}
extern "C" void gd_sim_range_site_reset() {
    for (auto& row : native_range_sites) row = NativeRangeSite{};
    native_range_overflow = 0;
}
'''


def instrument(native):
    path = native / "gd_rt.cpp"
    source = path.read_text("utf8")
    begin = source.index("GdVal gd_iter_seq(")
    end = source.index("// ─", begin)
    if hashlib.sha256(source[begin:end].encode()).hexdigest() != ITERATOR_HASH:
        raise ValueError("The range materialization implementation changed")
    anchor = "GdVal gd_iter_seq(BattleArena& arena, const GdVal& x) {\n"
    entry = ("    if (x.kind == GdVal::Kind::Int || x.kind == GdVal::Kind::Bool)\n"
             "        native_range_site_probe(reinterpret_cast<uintptr_t>(__builtin_return_address(0)), x.as_int());\n")
    source = source.replace(anchor, COUNTERS + "\n" + anchor + entry, 1)
    path.write_text(source, encoding="utf8", newline="\n")


def inspect(dll, out):
    sim = load_simulator(dll)
    signature = hashlib.sha256()
    jobs = list(prepare(sim, select_cases(200), signature))
    reset = sim.lib.gd_sim_range_site_reset
    reset.argtypes, reset.restype = [], None
    read = sim.lib.gd_sim_range_site_stat
    read.argtypes, read.restype = [ctypes.c_uint, ctypes.c_uint], ctypes.c_uint64
    reset()
    result = measure(sim, jobs, 1, 0, continuous=True)
    reference = json.loads((STAGE / "native_perf50_event_bus_serial.json").read_bytes())
    assert signature.hexdigest() == reference["inputs_sha256"]
    assert result["results_sha256"] == reference["results_sha256"]
    with tempfile.TemporaryDirectory(prefix="native-range-symbols-") as directory:
        copied = Path(directory) / "probe.dll"
        shutil.copyfile(dll, copied)
        assert copied.read_bytes() == dll.read_bytes()
        listing = subprocess.check_output(["D:/mingw64/bin/nm.exe", "-n", "-C", "--defined-only", str(copied)], text=True)
    symbols = []
    for line in listing.splitlines():
        parts = line.split(maxsplit=2)
        if len(parts) == 3 and parts[1].lower() == "t":
            symbols.append((int(parts[0], 16), parts[2]))
    symbols.sort()
    starts = [address for address, _ in symbols]
    # PE symbol addresses use the preferred image base; loader addresses may be relocated.
    # Windows rewrites the loaded PE header's ImageBase after relocation.
    # nm reports the preferred addresses stored in the file, so read that copy.
    binary = dll.read_bytes()
    pe_offset = struct.unpack_from("<I", binary, 0x3c)[0]
    assert binary[:2] == b"MZ" and binary[pe_offset:pe_offset + 4] == b"PE\0\0"
    assert struct.unpack_from("<H", binary, pe_offset + 24)[0] == 0x20b
    image_base = struct.unpack_from("<Q", binary, pe_offset + 48)[0]
    rows = []
    for index in range(256):
        caller = read(index, 0)
        if not caller:
            break
        rva = caller - sim.lib._handle
        address = image_base + rva
        found = bisect_right(starts, address) - 1
        rows.append({"caller_rva": hex(rva), "caller": symbols[found][1] if found >= 0 else "unknown",
                     "calls": read(index, 1), "elements": read(index, 2), "nonpositive": read(index, 3),
                     "maximum": read(index, 4)})
    assert read(256, 0) == 0, "The caller counter table overflowed"
    rows.sort(key=lambda row: row["elements"], reverse=True)
    report = {"diagnostic_only": True, "symbol_resolution": "preferred PE image base from file",
              "dll_sha256": hashlib.sha256(dll.read_bytes()).hexdigest(),
              "inputs_sha256": signature.hexdigest(), "results_sha256": result["results_sha256"],
              "calls": sum(row["calls"] for row in rows), "elements": sum(row["elements"] for row in rows),
              "sites": rows}
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
