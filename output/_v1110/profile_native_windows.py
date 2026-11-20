"""Sample the thread running the fixed native benchmark, with x64 unwind data."""
import argparse
from bisect import bisect_right
from collections import Counter
import ctypes as ct
from ctypes import wintypes as wt
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import sys
import threading
import time


ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from trainer.evaluator import OpponentPool
from trainer.native_backend import load_native


def func(dll, name, result, *args):
    api = getattr(dll, name)
    api.restype = result
    api.argtypes = args
    return api


def sample_native(handle, module, size, done, stacks):
    # Keep the GIL during suspension, including when the target returns to Python.
    kernel = ct.PyDLL("kernel32", use_last_error=True)
    native = ct.PyDLL("ntdll")
    suspend = func(kernel, "SuspendThread", wt.DWORD, wt.HANDLE)
    resume = func(kernel, "ResumeThread", wt.DWORD, wt.HANDLE)
    context = func(kernel, "GetThreadContext", wt.BOOL, wt.HANDLE, ct.c_void_p)
    lookup = func(native, "RtlLookupFunctionEntry", ct.c_void_p, ct.c_uint64, ct.POINTER(ct.c_uint64), ct.c_void_p)
    unwind = func(native, "RtlVirtualUnwind", ct.c_void_p, wt.DWORD, ct.c_uint64, ct.c_uint64, ct.c_void_p,
                  ct.c_void_p, ct.POINTER(ct.c_void_p), ct.POINTER(ct.c_uint64), ct.c_void_p)
    # Offsets from the Windows x64 CONTEXT layout, with 16-byte alignment.
    buffer = ct.create_string_buffer(1248)
    address = (ct.addressof(buffer) + 15) & ~15
    flags = wt.DWORD.from_address(address + 48)
    rsp = ct.c_uint64.from_address(address + 152)
    rip = ct.c_uint64.from_address(address + 248)
    base, handler, frame = ct.c_uint64(), ct.c_void_p(), ct.c_uint64()
    while not done.wait(0.003):
        stack = []
        if suspend(handle) == 0xFFFFFFFF:
            raise ct.WinError(ct.get_last_error())
        try:
            flags.value = 0x00100003  # CONTEXT_AMD64 | CONTROL | INTEGER
            if not context(handle, address):
                raise ct.WinError(ct.get_last_error())
            for _ in range(12):
                pc, sp = rip.value, rsp.value
                if not module <= pc < module + size:
                    break
                stack.append(pc - module)
                entry = lookup(pc, ct.byref(base), None)
                if entry:
                    unwind(0, base.value, pc, entry, address, ct.byref(handler), ct.byref(frame), None)
                else:
                    rip.value = ct.c_uint64.from_address(sp).value
                    rsp.value = sp + 8
                if rsp.value <= sp:
                    break
        finally:
            resume(handle)
        if stack:
            stacks[tuple(stack)] += 1


def symbols(path, nm):
    image = path.read_bytes()
    optional = struct.unpack_from("<I", image, 0x3c)[0] + 24
    base = struct.unpack_from("<Q", image, optional + 24)[0]
    size = struct.unpack_from("<I", image, optional + 56)[0]
    result = subprocess.run([nm, "-n", "-C", "--defined-only", path.name], cwd=path.parent,
                            capture_output=True, check=True)
    by_offset = {}
    for line in result.stdout.decode("utf8", "replace").splitlines():
        fields = line.split(None, 2)
        if len(fields) == 3 and fields[1] in ("T", "t") and not fields[2].startswith("."):
            by_offset[int(fields[0], 16) - base] = fields[2]
    return size, by_offset


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    source = parser.add_mutually_exclusive_group(required=True)
    source.add_argument("--runtime", type=Path)
    source.add_argument("--dll", type=Path, help="Sample an unpackaged candidate with the local runtime table")
    parser.add_argument("--nm", default="D:/mingw64/bin/nm.exe")
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--corpus", action="store_true", help="Sample the 200 duration-stratified original replays")
    parser.add_argument("--min-samples", type=int, default=0, help="Repeat the workload until this many native stacks are collected")
    args = parser.parse_args()
    if args.min_samples < 0:
        parser.error("--min-samples must be nonnegative")
    if args.dll:
        from bench_native_corpus import load_simulator

        dll = args.dll.resolve()
        sim = load_simulator(dll)
    else:
        runtime = args.runtime.resolve()
        dll = runtime / "libgdcore.dll"
        sim = load_native(runtime)
    size, by_offset = symbols(dll, args.nm)
    offsets = sorted(by_offset)
    inputs_digest = None
    if args.corpus:
        from bench_native_corpus import prepare, select_cases

        inputs_digest = hashlib.sha256()
        jobs = list(prepare(sim, select_cases(200), inputs_digest))

        def run(selected):
            return [sim.run_one(*sides, **options) for _, sides, options, _, _ in selected]
    else:
        pool = OpponentPool().sample((450, 650), 50, seed=42)[:25]
        assert len(pool) == 25
        sides = [sim.pack_side(lineup, strict=True) for lineup in pool]
        player = sides[0]
        jobs = [(player, opp, sim.make_options(round_id=player.round_id, seed=2026_11_11 + i * 10000 + k,
                                              formal_ev_gate=500000, max_time=90.0))
                for i, opp in enumerate(sides) for k in range(8)]

        def run(selected):
            return sim.run_batch(selected, n_threads=1, training=True)

    run(jobs[:8])
    kernel = ct.WinDLL("kernel32", use_last_error=True)
    current_thread = func(kernel, "GetCurrentThreadId", wt.DWORD)
    open_thread = func(kernel, "OpenThread", wt.HANDLE, wt.DWORD, wt.BOOL, wt.DWORD)
    close = func(kernel, "CloseHandle", wt.BOOL, wt.HANDLE)
    handle = open_thread(0x000A, False, current_thread())
    if not handle:
        raise ct.WinError(ct.get_last_error())
    done = threading.Event()
    stacks = Counter()
    errors = []

    def sample():
        try:
            sample_native(handle, sim.lib._handle, size, done, stacks)
        except Exception as error:
            errors.append(error)

    thread = threading.Thread(target=sample)
    thread.start()
    try:
        start = time.perf_counter()
        batches = 0
        while True:
            results = run(jobs)
            batches += 1
            if errors:
                raise errors[0]
            if stacks.total() >= args.min_samples:
                break
            if not stacks:
                raise RuntimeError("The sampler collected no native stacks")
        wall = time.perf_counter() - start
    finally:
        done.set()
        thread.join()
        close(handle)
    assert stacks and len(results) == 200

    def resolve(offset):
        index = bisect_right(offsets, offset) - 1
        return by_offset[offsets[index]] if index >= 0 else "?"

    leaf, inclusive, callers = Counter(), Counter(), Counter()
    for stack, count in stacks.items():
        names = tuple(map(resolve, stack))
        leaf[names[0]] += count
        for name in set(names):
            inclusive[name] += count
        for pair in set(zip(names[1:], names)):
            callers[" -> ".join(pair)] += count
    report = {"workload": "original_replays" if args.corpus else "training", "samples": stacks.total(),
              "batches": batches, "dll_sha256": hashlib.sha256(dll.read_bytes()).hexdigest(),
              "inputs_sha256": inputs_digest.hexdigest() if inputs_digest else None,
              "sampled_wall_s": wall, "leaf": leaf.most_common(45),
              "inclusive": inclusive.most_common(45), "callers": callers.most_common(45)}
    args.out.write_text(json.dumps(report, indent=2) + "\n", encoding="utf8")
    for key in ("leaf", "inclusive", "callers"):
        print(key, *report[key][:12], sep="\n")


if __name__ == "__main__":
    main()
