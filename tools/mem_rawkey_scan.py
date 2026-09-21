"""
Raw script-key memory scanner: slides a 32-byte window over committed memory,
AES-256-ECB decrypts the first GDEC ciphertext block, keeps keys whose
plaintext starts with "GDSC". Validated by full-file MD5 at the end.

Phase 1: byte-search known historical keys (cross-reference only).
Phase 2: independent brute-force over image + data regions (multiprocess).
"""
import ctypes, ctypes.wintypes as wt, sys, os, hashlib, time
import numpy as np
from multiprocessing import Pool

k32 = ctypes.windll.kernel32
PROCESS_VM_READ = 0x10; PROCESS_QUERY_INFORMATION = 0x400
class MBI(ctypes.Structure):
    _fields_ = [("BaseAddress", ctypes.c_void_p), ("AllocationBase", ctypes.c_void_p),
                ("AllocationProtect", wt.DWORD), ("RegionSize", ctypes.c_size_t),
                ("State", wt.DWORD), ("Protect", wt.DWORD), ("Type", wt.DWORD)]

def regions(h):
    addr = 0x10000; mbi = MBI(); size = ctypes.sizeof(mbi)
    while addr < 0x7FFFFFFF0000:
        if not k32.VirtualQueryEx(ctypes.c_void_p(h), ctypes.c_void_p(addr),
                                  ctypes.byref(mbi), size):
            addr = (addr + 0x1000) & ~0xFFF; continue
        if mbi.State == 0x1000 and (mbi.Protect & 0xFF) in {0x02, 0x04, 0x08, 0x20, 0x40} \
           and not (mbi.Protect & 0x100):
            yield mbi.BaseAddress, mbi.RegionSize, mbi.Type
        nxt = (mbi.BaseAddress or addr) + mbi.RegionSize
        if nxt <= addr: break
        addr = nxt

def read_mem(h, base, size):
    buf = ctypes.create_string_buffer(size)
    got = ctypes.c_size_t(0)
    if k32.ReadProcessMemory(ctypes.c_void_p(h), ctypes.c_void_p(base), buf, size, ctypes.byref(got)):
        return buf.raw[:got.value]
    return b''

def gdec_first_block(path):
    d = open(path, 'rb').read()
    assert d[:4] == b'GDEC'
    return d[32:48], d[8:24], d[32:]   # first ct block, expected md5, full ct

def full_validate(key):
    """Full decrypt + MD5 on several game files."""
    from Crypto.Cipher import AES
    base = r'D:\文件资料\学习\自动背包AI\unpacked_new'
    samples = [os.path.join(base, 'CharacterClasses', 'CharacterClass.gde'),
               os.path.join(base, 'Sheets', 'CSV', 'ItemData_e.csv')]
    for s in samples:
        d = open(s, 'rb').read()
        if d[:4] != b'GDEC':
            continue
        pt = AES.new(key, AES.MODE_ECB).decrypt(d[32:])
        ln = int.from_bytes(d[24:32], 'little')
        pt = pt[:ln]
        if hashlib.md5(pt).digest() != d[8:24]:
            return False
    return True

def worker(args):
    blob, first_blk = args
    from Crypto.Cipher import AES
    out = []
    n = len(blob)
    if n < 32:
        return out
    mv = memoryview(blob)
    new = AES.new
    for i in range(n - 31):
        pt = new(mv[i:i+32], AES.MODE_ECB).decrypt(first_blk)
        if pt[0] == 0x47 and pt[1] == 0x44 and pt[2] == 0x53 and pt[3] == 0x43:
            out.append((i, blob[i:i+32].hex()))
    return out

def main():
    pid = int(sys.argv[1]) if len(sys.argv) > 1 else 7308
    sample = os.path.join(r'D:\文件资料\学习\自动背包AI\unpacked_new',
                          'CharacterClasses', 'CharacterClass.gde')
    first_blk, _, _ = gdec_first_block(sample)
    h = k32.OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, False, pid)
    if not h:
        print(f"OpenProcess failed err={ctypes.GetLastError()}"); return 1

    known = [bytes.fromhex('8671424952511006d39f4c9e918f821391e2b06a80d946d693fb8757154ce849'),
             bytes.fromhex('0001020304c6060708090a0bc30d0e0f101112131415161718191a1b1c1d1e1f')]

    img_regions, all_count, total = [], 0, 0
    regdata = []
    for base, rsize, rtype in regions(h):
        total += rsize
        if rtype == 0x1000000:  # MEM_IMAGE
            img_regions.append((base, rsize))
        regdata.append((base, rsize, rtype))
    print(f"{len(regdata)} committed regions, {total/1e6:.0f} MB; image regions: {len(img_regions)}, "
          f"{sum(s for _, s in img_regions)/1e6:.0f} MB")

    # ---- phase 1: known-key byte search (cross-check) ----
    hits_known = {k.hex(): 0 for k in known}
    for base, rsize, rtype in regdata:
        blob = read_mem(h, base, rsize)
        if not blob or len(blob) < 32:
            continue
        arr = np.frombuffer(blob, dtype=np.uint8)
        for k in known:
            # first 8 bytes as one u64 compare (memory-light), then verify tail
            u64 = np.frombuffer(blob[:len(blob) & ~7], dtype='<u8')
            k8 = int.from_bytes(k[:8], 'little')
            cand = np.nonzero(u64 == np.uint64(k8))[0]
            n = 0
            for c in cand:
                c = int(c)
                if blob[c:c+32] == k:
                    n += 1
                    if n == 1:
                        print(f"  known-key {k.hex()[:16]}.. found @ {hex(base+c)} "
                              f"(type {'image' if rtype==0x1000000 else rtype})")
            hits_known[k.hex()] += n
    print("phase1 done:", hits_known)

    # ---- phase 2: independent brute-force over image regions ----
    t0 = time.time()
    cands = []
    for base, rsize in img_regions:
        blob = read_mem(h, base, rsize)
        if not blob:
            continue
        NW = 8
        chunk = (len(blob) - 31) // NW + 1
        tasks = []
        for w in range(NW):
            lo = w * chunk
            hi = min(len(blob), lo + chunk + 31)   # overlap 31 bytes
            if hi - lo >= 32:
                tasks.append((blob[lo:hi], first_blk))
        with Pool(NW) as p:
            for res in p.imap_unordered(worker, tasks):
                for i, kh in res:
                    cands.append(kh)
        print(f"  image region {hex(base)} ({rsize/1e6:.0f} MB) scanned, cands so far: {len(cands)}")
    print(f"phase2 brute-force done in {time.time()-t0:.0f}s, {len(cands)} candidate(s)")
    for kh in sorted(set(cands)):
        ok = full_validate(bytes.fromhex(kh))
        print(f"  KEY {kh}  full-MD5-valid={ok}")
        if ok:
            with open(r'D:\文件资料\学习\自动背包AI\tools\memory_keys.txt', 'a') as f:
                f.write(f"{kh}  raw-scan  gde+csv-md5-ok\n")
    k32.CloseHandle(ctypes.c_void_p(h))
    return 0

if __name__ == '__main__':
    sys.exit(main())
