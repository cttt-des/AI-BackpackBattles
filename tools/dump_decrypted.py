"""
dump_decrypted.py  --  Reconstruct decrypted Godot .gdc scripts from a LIVE game process.

WHY THIS WORKS (no key needed):
  Each encrypted .gde (GDEC container) stores in its header:
      [0:4]   "GDEC"
      [4:8]   version (4 bytes)
      [8:24]  MD5(plaintext)         <- MD5 of the original .gdc content
      [24:32] plain_len (uint64 LE)  <- exact size of the original .gdc content
      [32:]   AES ciphertext
  When the GAME loads a script, its custom FileAccessEncrypted::open_and_parse
  decrypts the ciphertext into a contiguous in-memory buffer that is EXACTLY the
  original .gdc (starts with magic "GDSC"). Because the engine keeps compiled
  bytecode cached, that buffer stays resident.

  So we do NOT need the AES key. We:
    1. Precompute, for every extracted .gde: (path, plain_len, md5(plaintext)).
    2. Launch the game, wait for scripts to load, suspend the process.
    3. Scan all committed + readable memory regions for the 4-byte pattern "GDSC".
    4. For each hit, read exactly `plain_len` bytes and compute MD5; if it matches
       a known .gde header, we have reconstructed that script's .gdc exactly.
    5. Save the .gdc; later feed to gdre_tools to decompile to .gd.

Usage:
    python tools/dump_decrypted.py                 # launch game, dump, save .gdc
    python tools/dump_decrypted.py --pid 1234      # attach to running game
    python tools/dump_decrypted.py --wait 45       # wait longer for load
    python tools/dump_decrypted.py --no-launch     # assume game already running
"""
import argparse
import ctypes
import ctypes.wintypes as wt
import glob
import hashlib
import os
import subprocess
import sys
import time

# --------------------------------------------------------------------------
# Win32 bindings
# --------------------------------------------------------------------------
kernel32 = ctypes.windll.kernel32
ntdll = ctypes.windll.ntdll

PROCESS_VM_READ = 0x10
PROCESS_QUERY_INFORMATION = 0x400
PROCESS_SUSPEND_RESUME = 0x0800
PROCESS_TERMINATE = 0x0001

MEM_COMMIT = 0x1000
PAGE_READONLY = 0x02
PAGE_READWRITE = 0x04
PAGE_WRITECOPY = 0x08
PAGE_EXECUTE_READ = 0x20
PAGE_EXECUTE_READWRITE = 0x40
PAGE_EXECUTE_WRITECOPY = 0x80
READABLE = {
    PAGE_READONLY, PAGE_READWRITE, PAGE_WRITECOPY,
    PAGE_EXECUTE_READ, PAGE_EXECUTE_READWRITE, PAGE_EXECUTE_WRITECOPY,
}


class MEMORY_BASIC_INFORMATION(ctypes.Structure):
    _fields_ = [
        ("BaseAddress", ctypes.c_void_p),
        ("AllocationBase", ctypes.c_void_p),
        ("AllocationProtect", ctypes.c_ulong),
        ("RegionSize", ctypes.c_size_t),
        ("State", ctypes.c_ulong),
        ("Protect", ctypes.c_ulong),
        ("Type", ctypes.c_ulong),
    ]


def suspend(pid):
    h = kernel32.OpenProcess(PROCESS_SUSPEND_RESUME, False, pid)
    if not h:
        return False, ctypes.GetLastError()
    status = ntdll.NtSuspendProcess(h)
    kernel32.CloseHandle(h)
    return (status == 0), status


def resume(pid):
    h = kernel32.OpenProcess(PROCESS_SUSPEND_RESUME, False, pid)
    if not h:
        return False, ctypes.GetLastError()
    status = ntdll.NtResumeProcess(h)
    kernel32.CloseHandle(h)
    return (status == 0), status


# --------------------------------------------------------------------------
# Index: from each extracted .gde, get (relpath, plain_len, md5)
# --------------------------------------------------------------------------
GDSC = b"GDSC"


def build_index(extracted_dir):
    """Return (lookup, by_len, stats)."""
    lookup = {}      # (plain_len, md5_bytes) -> relpath
    by_len = {}      # plain_len -> list of (md5_bytes, relpath)
    max_len = 0
    n = 0
    for path in glob.glob(os.path.join(extracted_dir, "**", "*.gde"), recursive=True):
        try:
            with open(path, "rb") as f:
                hdr = f.read(32)
        except OSError:
            continue
        if len(hdr) < 32 or hdr[:4] != b"GDEC":
            continue
        md5e = hdr[8:24]
        plain_len = int.from_bytes(hdr[24:32], "little")
        if plain_len <= 0 or plain_len > 50_000_000:
            continue
        rel = os.path.relpath(path, extracted_dir)
        key = (plain_len, md5e)
        if key in lookup:
            continue
        lookup[key] = rel
        by_len.setdefault(plain_len, []).append((md5e, rel))
        max_len = max(max_len, plain_len)
        n += 1
    return lookup, by_len, {"count": n, "max_len": max_len}


# --------------------------------------------------------------------------
# Memory scan
# --------------------------------------------------------------------------
def scan_process(hproc, lookup, by_len, max_len, saved, out_dir, chunk_cap):
    mbi = MEMORY_BASIC_INFORMATION()
    addr = 0
    cap = min(max_len, chunk_cap)
    regions = 0
    hits = 0
    # precompute candidate lengths once
    candidate_lengths = sorted(by_len.keys())
    while True:
        ret = kernel32.VirtualQueryEx(
            hproc, ctypes.c_void_p(addr), ctypes.byref(mbi), ctypes.sizeof(mbi)
        )
        if ret == 0:
            break
        base = addr
        size = mbi.RegionSize
        if mbi.State == MEM_COMMIT and (mbi.Protect & 0xFF) in READABLE and size > 0:
            regions += 1
            buf = ctypes.create_string_buffer(size)
            nread = ctypes.c_size_t()
            ok = kernel32.ReadProcessMemory(
                hproc, ctypes.c_void_p(base), buf, size, ctypes.byref(nread)
            )
            if ok:
                data = buf.raw[: nread.value]
                off = 0
                while True:
                    off = data.find(GDSC, off)
                    if off < 0:
                        break
                    hits += 1
                    chunk = data[off: off + cap]
                    # try candidate lengths <= len(chunk)
                    for L in candidate_lengths:
                        if L > len(chunk):
                            break
                        h = hashlib.md5(chunk[:L]).digest()
                        key = (L, h)
                        if key in lookup and key not in saved:
                            rel = lookup[key]
                            outp = os.path.join(out_dir, rel + ".gdc")
                            os.makedirs(os.path.dirname(outp), exist_ok=True)
                            with open(outp, "wb") as fo:
                                fo.write(chunk[:L])
                            saved.add(key)
                            print(f"  [+] {rel}  ({L} bytes)")
                    off += 1
        addr = base + size
        if addr >= 0x7FFFFFFFFFFF:
            break
    return regions, hits


# --------------------------------------------------------------------------
# Main
# --------------------------------------------------------------------------
def main():
    ap = argparse.ArgumentParser()
    here = os.path.dirname(os.path.abspath(__file__))
    proj = os.path.dirname(here)
    ap.add_argument("--game", default=os.path.join(proj, "Backpack Battles", "BackpackBattles.exe"))
    ap.add_argument("--extracted", default=os.path.join(proj, "extracted"))
    ap.add_argument("--out", default=os.path.join(proj, "extracted_gdc"))
    ap.add_argument("--wait", type=float, default=30.0)
    ap.add_argument("--pid", type=int, default=None, help="attach to running pid")
    ap.add_argument("--no-launch", action="store_true")
    ap.add_argument("--chunk-cap", type=int, default=400_000)
    ap.add_argument("--keep-alive", action="store_true", help="do not kill game after scan")
    ap.add_argument("--continuous", action="store_true",
                    help="scan repeatedly across the whole process lifetime (union hits)")
    ap.add_argument("--interval", type=float, default=2.0, help="seconds between scans (continuous)")
    ap.add_argument("--max-time", type=float, default=32.0, help="max seconds to keep scanning")
    args = ap.parse_args()

    os.makedirs(args.out, exist_ok=True)

    print(f"[*] Building index from {args.extracted} ...")
    lookup, by_len, stats = build_index(args.extracted)
    print(f"[*] Indexed {stats['count']} scripts; max plain_len={stats['max_len']}")

    proc = None
    pid = args.pid
    if pid is None and not args.no_launch:
        gdir = os.path.dirname(args.game)
        print(f"[*] Launching {args.game} --headless (cwd={gdir})")
        proc = subprocess.Popen([args.game, "--headless"], cwd=gdir)
        pid = proc.pid
        print(f"[*] Launched pid={pid}")

    saved = set()

    if args.continuous:
        # Scan repeatedly across the whole process lifetime. Decrypted .gdc
        # buffers are transient (freed after compile), so we union every pass.
        hproc = kernel32.OpenProcess(
            PROCESS_VM_READ | PROCESS_QUERY_INFORMATION | PROCESS_TERMINATE, False, pid)
        if not hproc:
            print(f"[!] OpenProcess({pid}) failed, err={ctypes.GetLastError()}")
            return 2
        t0 = time.time()
        passes = 0
        try:
            while time.time() - t0 < args.max_time:
                if proc is not None and proc.poll() is not None:
                    print(f"[*] Game exited (code {proc.returncode}) after {time.time()-t0:.1f}s")
                    break
                passes += 1
                regions, hits = scan_process(
                    hproc, lookup, by_len, stats["max_len"], saved, args.out, args.chunk_cap)
                print(f"[*] pass {passes}: {regions} regions, {hits} GDSC hits, total {len(saved)} scripts")
                time.sleep(args.interval)
        finally:
            kernel32.CloseHandle(hproc)
            h = kernel32.OpenProcess(PROCESS_TERMINATE, False, pid)
            if h:
                kernel32.TerminateProcess(h, 0)
                kernel32.CloseHandle(h)
            if proc is not None:
                try:
                    proc.wait(timeout=5)
                except Exception:
                    pass
            print("[*] Game terminated.")
        print(f"[*] Saved {len(saved)} .gdc files to {args.out}")
        return 0

    # ---- single-pass mode: wait, suspend, scan ----
    print(f"[*] Waiting {args.wait}s for scripts to load ...")
    time.sleep(args.wait)

    if proc is not None:
        if proc.poll() is not None:
            print("[!] Game process exited early (code %s). Headless may need a display or Steam." % proc.returncode)
            return 1

    hproc = kernel32.OpenProcess(
        PROCESS_VM_READ | PROCESS_QUERY_INFORMATION | PROCESS_SUSPEND_RESUME | PROCESS_TERMINATE,
        False, pid,
    )
    if not hproc:
        print(f"[!] OpenProcess({pid}) failed, err={ctypes.GetLastError()}")
        return 2

    ok, st = suspend(pid)
    print(f"[*] Suspended pid={pid}: {ok} (status={st})")

    try:
        regions, hits = scan_process(hproc, lookup, by_len, stats["max_len"], saved, args.out, args.chunk_cap)
        print(f"[*] Scanned {regions} regions, {hits} GDSC hits, reconstructed {len(saved)} scripts.")
    finally:
        kernel32.CloseHandle(hproc)
        ok2, st2 = resume(pid)
        h = kernel32.OpenProcess(PROCESS_TERMINATE, False, pid)
        if h:
            kernel32.TerminateProcess(h, 0)
            kernel32.CloseHandle(h)
        if proc is not None:
            try:
                proc.wait(timeout=5)
            except Exception:
                pass
        print("[*] Game terminated.")

    print(f"[*] Saved {len(saved)} .gdc files to {args.out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
