"""
extract_script_key_live.py
Launch Backpack Battles (headless), suspend it, then scan process memory for the
runtime-deobfuscated 32-byte GDEC script-encryption key.

The game obfuscates the script key at build time, so it is NOT a plain 32-byte
blob in the static EXE (verified by exhaustive static scan). At runtime Godot
deobfuscates it into a Vector<uint8_t> buffer that lives in process memory as
plain 32 bytes. We freeze the process (NtSuspendProcess) so it stays alive and
scan every readable region: for each 32-byte window we AES-256-ECB decrypt the
first ciphertext block and keep candidates whose plaintext starts with "GDSC",
then fully verify with the GDEC MD5.

Usage:
    python tools/extract_script_key_live.py [path/to/Combat.gde] [path/to/BackpackBattles.exe]
"""
import sys
import os
import time
import ctypes
import struct
import subprocess
from ctypes import wintypes

from Crypto.Cipher import AES

KERNEL = ctypes.windll.kernel32
NTDLL = ctypes.windll.ntdll

PROCESS_VM_READ = 0x10
PROCESS_QUERY_INFORMATION = 0x400
PROCESS_SUSPEND_RESUME = 0x800

PAGE_READABLE = 0x04 | 0x02 | 0x40  # READWRITE | READONLY | EXECUTE_READ
MEM_COMMIT = 0x1000


class MEMORY_BASIC_INFORMATION(ctypes.Structure):
    _fields_ = [
        ("BaseAddress", ctypes.c_void_p),
        ("AllocationBase", ctypes.c_void_p),
        ("AllocationProtect", wintypes.DWORD),
        ("PartitionId", wintypes.WORD),
        ("RegionSize", ctypes.c_size_t),
        ("State", wintypes.DWORD),
        ("Protect", wintypes.DWORD),
        ("Type", wintypes.DWORD),
    ]


def suspend(pid):
    h = KERNEL.OpenProcess(PROCESS_SUSPEND_RESUME, False, pid)
    if not h:
        return False
    NTDLL.NtSuspendProcess.argtypes = [ctypes.c_void_p]
    NTDLL.NtSuspendProcess.restype = ctypes.c_long
    rc = NTDLL.NtSuspendProcess(h)
    KERNEL.CloseHandle(h)
    return rc == 0


def resume(pid):
    h = KERNEL.OpenProcess(PROCESS_SUSPEND_RESUME, False, pid)
    if not h:
        return
    NTDLL.NtResumeProcess.argtypes = [ctypes.c_void_p]
    NTDLL.NtResumeProcess.restype = ctypes.c_long
    NTDLL.NtResumeProcess(h)
    KERNEL.CloseHandle(h)


def main():
    here = os.path.dirname(os.path.abspath(__file__))
    gde = sys.argv[1] if len(sys.argv) > 1 else os.path.join(here, "..", "extracted", "Core", "Combat.gde")
    exe = sys.argv[2] if len(sys.argv) > 2 else r"D:\steam\steamapps\common\Backpack Battles\BackpackBattles.exe"
    gde = os.path.abspath(gde)

    raw = open(gde, "rb").read()
    if raw[:4] != b"GDEC":
        print("ERROR: not a GDEC file:", gde, file=sys.stderr)
        return 2
    md5_expected = raw[8:24]
    plain_len = int.from_bytes(raw[24:32], "little")
    ct = raw[32:]
    first_block = ct[:16]
    print(f"[*] GDEC plain_len={plain_len} ct_blocks={len(ct)//16}")

    # Launch headless game
    print(f"[*] launching {exe} --headless")
    proc = subprocess.Popen([exe, "--headless"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    pid = proc.pid
    print(f"[*] pid={pid}, waiting 3s for init...")
    time.sleep(3)
    if proc.poll() is not None:
        print("ERROR: game process exited before we could suspend it", file=sys.stderr)
        return 3
    if not suspend(pid):
        print("ERROR: failed to suspend process (try running as admin)", file=sys.stderr)
        return 4
    print(f"[+] process {pid} suspended; scanning memory...")

    h = KERNEL.OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, False, pid)
    if not h:
        print("ERROR: OpenProcess failed", file=sys.stderr)
        resume(pid)
        return 5

    KERNEL.VirtualQueryEx.argtypes = [wintypes.HANDLE, ctypes.c_void_p, ctypes.POINTER(MEMORY_BASIC_INFORMATION), ctypes.c_size_t]
    KERNEL.VirtualQueryEx.restype = ctypes.c_size_t
    KERNEL.ReadProcessMemory.argtypes = [wintypes.HANDLE, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t, ctypes.POINTER(ctypes.c_size_t)]
    KERNEL.ReadProcessMemory.restype = ctypes.c_int

    addr = 0x10000
    max_addr = 0x7FFFFFFFFFFF
    candidates = []
    regions = 0
    scanned_bytes = 0
    t0 = time.time()

    mbi = MEMORY_BASIC_INFORMATION()
    while addr < max_addr:
        ret = KERNEL.VirtualQueryEx(h, ctypes.c_void_p(addr), ctypes.byref(mbi), ctypes.sizeof(mbi))
        if not ret:
            addr = (addr + 0x1000) & ~0xFFF
            if addr <= 0:
                break
            continue
        base = ctypes.cast(mbi.BaseAddress, ctypes.c_void_p).value
        size = mbi.RegionSize
        if mbi.State == MEM_COMMIT and (mbi.Protect & PAGE_READABLE) and size > 0 and size < 0x8000000:
            regions += 1
            buf = ctypes.create_string_buffer(min(size, 0x8000000))
            read = ctypes.c_size_t(0)
            if KERNEL.ReadProcessMemory(h, ctypes.c_void_p(base), buf, min(size, 0x8000000), ctypes.byref(read)):
                data = buf.raw[:read.value]
                scanned_bytes += len(data)
                # scan 32-byte windows; filter by first-block GDSC
                lim = len(data) - 32
                for i in range(0, lim):
                    k = data[i:i + 32]
                    try:
                        blk = AES.new(k, AES.MODE_ECB).decrypt(first_block)
                    except Exception:
                        continue
                    if blk[:4] == b"GDSC":
                        # full verify
                        full = AES.new(k, AES.MODE_ECB).decrypt(ct)
                        if full[:4] == b"GDSC" and hashlib_md5(full[:plain_len]) == md5_expected:
                            candidates.append((base + i, k.hex()))
                            print(f"[+] CANDIDATE key @ {hex(base+i)}: {k.hex()}")
        addr = base + size
        if addr <= 0:
            break

    elapsed = time.time() - t0
    print(f"[*] scanned {regions} regions, {scanned_bytes:,} bytes in {elapsed:.1f}s")
    KERNEL.CloseHandle(h)
    resume(pid)
    try:
        proc.terminate()
    except Exception:
        pass

    if candidates:
        best = candidates[0]
        out = os.path.join(here, "script_key.txt")
        with open(out, "w") as f:
            f.write(best[1])
        print(f"[+] SCRIPT KEY FOUND @ {hex(best[0])}")
        print(f"[+] KEY (64 hex): {best[1]}")
        print(f"[+] saved to {out}")
        return 0
    else:
        print("[-] no script key found in memory")
        return 1


def hashlib_md5(b):
    import hashlib
    return hashlib.md5(b).digest()


if __name__ == "__main__":
    raise SystemExit(main())
