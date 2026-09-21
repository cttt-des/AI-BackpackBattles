"""
Launch a fresh headless game instance, suspend it right after engine/script
init, then find the script key in its still-hot memory:
  1) numpy AES-256 key-schedule scan (Rcon recurrence, mbedtls LE form)
  2) multiprocess raw-key brute force (every 32-byte window -> ECB -> "GDSC")
Candidates are validated by full GDEC MD5. The temp process is killed at the end.
The user's own game session is never touched.

Usage: python tools/launch_fresh_and_scan.py
"""
import subprocess, sys, time, os, ctypes, hashlib
import numpy as np
from multiprocessing import Pool

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

k32 = ctypes.windll.kernel32
ntdll = ctypes.windll.ntdll

EXE = r"D:\steam\steamapps\common\Backpack Battles\BackpackBattles.exe"
GDE_SAMPLE = os.path.join(r'D:\文件资料\学习\自动背包AI\extracted',
                          'CharacterClasses', 'CharacterClass.gde')
OUT_KEYS = os.path.join(r'D:\文件资料\学习\自动背包AI\tools', 'memory_keys.txt')

PROCESS_VM_READ = 0x10; PROCESS_QUERY_INFORMATION = 0x400
PROCESS_SUSPEND_RESUME = 0x0800; PROCESS_TERMINATE = 0x0001

class MBI(ctypes.Structure):
    _fields_ = [("BaseAddress", ctypes.c_void_p), ("AllocationBase", ctypes.c_void_p),
                ("AllocationProtect", ctypes.c_uint32), ("RegionSize", ctypes.c_size_t),
                ("State", ctypes.c_uint32), ("Protect", ctypes.c_uint32), ("Type", ctypes.c_uint32)]

def read_mem(h, base, size):
    buf = ctypes.create_string_buffer(size)
    got = ctypes.c_size_t(0)
    if k32.ReadProcessMemory(ctypes.c_void_p(h), ctypes.c_void_p(base), buf, size, ctypes.byref(got)):
        return buf.raw[:got.value]
    return b''

def regions(h, skip_image=False):
    addr = 0x10000; mbi = MBI()
    while addr < 0x7FFFFFFF0000:
        if not k32.VirtualQueryEx(ctypes.c_void_p(h), ctypes.c_void_p(addr), ctypes.byref(mbi), ctypes.sizeof(mbi)):
            addr = (addr + 0x1000) & ~0xFFF; continue
        if mbi.State == 0x1000 and (mbi.Protect & 0xFF) in {0x02, 0x04, 0x08, 0x20, 0x40} \
           and not (mbi.Protect & 0x100) and not (skip_image and mbi.Type == 0x1000000):
            yield mbi.BaseAddress, mbi.RegionSize
        nxt = (mbi.BaseAddress or addr) + mbi.RegionSize
        if nxt <= addr: break
        addr = nxt

def gdec_first_block(path):
    d = open(path, 'rb').read()
    assert d[:4] == b'GDEC'
    return d[32:48]

def validate_key(key_hex, sample_path=GDE_SAMPLE):
    from Crypto.Cipher import AES
    d = open(sample_path, 'rb').read()
    pt = AES.new(bytes.fromhex(key_hex), AES.MODE_ECB).decrypt(d[32:])
    ln = int.from_bytes(d[24:32], 'little')
    return hashlib.md5(pt[:ln]).digest() == d[8:24]

def raw_worker(args):
    from Crypto.Cipher import AES
    blob, blk = args
    out = []; mv = memoryview(blob); new = AES.new
    for i in range(len(blob) - 31):
        pt = new(mv[i:i+32], AES.MODE_ECB).decrypt(blk)
        if pt[:4] == b'GDSC':
            out.append(blob[i:i+32].hex())
    return out

def scan_all(h):
    import mem_key_scan as ms
    found = {}
    total = 0
    CHUNK = 8 << 20
    blobs = []
    for base, rsize in regions(h, skip_image=True):  # image regions already brute-forced clean
        total += rsize
        off = 0
        while off < rsize:
            take = min(CHUNK + 512, rsize - off)
            blob = read_mem(h, base + off, take)
            if len(blob) >= 256:
                W = np.frombuffer(blob[:len(blob) & ~3], dtype='<u4')
                for p in ms.scan_schedule_candidates(W):
                    kw = ms.full_check(W, p)
                    if kw:
                        key = b''.join(x.to_bytes(4, 'little') for x in kw).hex()
                        found.setdefault(key, []).append(hex(base + off + p * 4))
                blobs.append(blob)
            off += CHUNK
    print(f"[scan] memory: {total/1e6:.0f} MB; schedule hits: {len(found)}", flush=True)
    for kh, locs in found.items():
        print(f"[sched] {kh} x{len(locs)} @ {locs[:2]} valid={validate_key(kh)}", flush=True)
        if validate_key(kh):
            return kh
    # raw brute force over all collected memory
    blk = gdec_first_block(GDE_SAMPLE)
    NW = 8
    tasks = []
    for b in blobs:
        step = max(1 << 22, (len(b) - 31) // NW + 1)
        for lo in range(0, max(1, len(b) - 31), step):
            hi = min(len(b), lo + step + 31)
            if hi - lo >= 32:
                tasks.append((b[lo:hi], blk))
    print(f"[scan] raw brute force: {len(tasks)} chunks over {sum(len(b) for b in blobs)/1e6:.0f} MB", flush=True)
    cands = set()
    t0 = time.time()
    with Pool(NW) as pool:
        for res in pool.imap_unordered(raw_worker, tasks):
            cands.update(res)
            if cands:
                for kh in list(cands):
                    print(f"[raw] candidate {kh} valid={validate_key(kh)} ({time.time()-t0:.0f}s)", flush=True)
                    if validate_key(kh):
                        return kh
    return None

def suspend(pid):
    hh = k32.OpenProcess(PROCESS_SUSPEND_RESUME, False, pid)
    if not hh: return False
    ok = ntdll.NtSuspendProcess(hh) == 0
    k32.CloseHandle(hh); return ok

def kill(pid):
    hh = k32.OpenProcess(PROCESS_TERMINATE, False, pid)
    if hh:
        k32.TerminateProcess(hh, 0); k32.CloseHandle(hh)

def main():
    for attempt in range(1, 4):
        wait = 15 + 5 * (attempt - 1)
        print(f"[attempt {attempt}] launching headless game, init wait {wait}s ...", flush=True)
        proc = subprocess.Popen([EXE, "--headless"],
                                stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                                cwd=os.path.dirname(EXE))
        t0 = time.time()
        while time.time() - t0 < wait:
            if proc.poll() is not None:
                break
            time.sleep(0.3)
        if proc.poll() is not None:
            print(f"  exited early code={proc.returncode}; retry", flush=True)
            continue
        pid = proc.pid
        h = k32.OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, False, pid)
        if not h:
            print(f"  OpenProcess failed err={ctypes.GetLastError()}", flush=True)
            kill(pid); continue
        if not suspend(pid):
            print("  suspend failed", flush=True); kill(pid); continue
        print(f"  suspended pid={pid}, scanning ...", flush=True)
        try:
            key = scan_all(h)
        finally:
            k32.CloseHandle(ctypes.c_void_p(h))
            kill(pid)
        if key:
            print(f"\nSCRIPT KEY FOUND: {key}", flush=True)
            with open(OUT_KEYS, 'a', encoding='utf-8') as f:
                f.write(f"{key}  script-key  fresh-instance-scan  gde-md5-ok\n")
            return 0
        print("  no key this attempt", flush=True)
    print("ALL ATTEMPTS FAILED", flush=True)
    return 1

if __name__ == '__main__':
    sys.exit(main())
