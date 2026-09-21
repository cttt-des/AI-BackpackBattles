"""
Focused raw-key scanner: locates the running game's main module (BackpackBattles.exe)
image in the target process via EnumProcessModules, brute-forces every 32-byte
window in the image against the first GDEC ciphertext block (plaintext must
start with "GDSC"), then validates full-file MD5. Also byte-searches known
keys across ALL committed memory as a cross-reference.

Usage: python tools/mem_key_scan_focused.py [pid]
"""
import ctypes, ctypes.wintypes as wt, sys, os, hashlib, time
import numpy as np

psapi = ctypes.windll.psapi
k32 = ctypes.windll.kernel32
PROCESS_VM_READ = 0x10; PROCESS_QUERY_INFORMATION = 0x400
LIST_MODULES_ALL = 0x03

class MBI(ctypes.Structure):
    _fields_ = [("BaseAddress", ctypes.c_void_p), ("AllocationBase", ctypes.c_void_p),
                ("AllocationProtect", wt.DWORD), ("RegionSize", ctypes.c_size_t),
                ("State", wt.DWORD), ("Protect", wt.DWORD), ("Type", wt.DWORD)]

def read_mem(h, base, size):
    buf = ctypes.create_string_buffer(size)
    got = ctypes.c_size_t(0)
    if k32.ReadProcessMemory(ctypes.c_void_p(h), ctypes.c_void_p(base), buf, size, ctypes.byref(got)):
        return buf.raw[:got.value]
    return b''

def main_module(h, pid):
    """Return (base, size, name) of the exe module in the process."""
    Need = ctypes.c_size_t(0)
    psapi.EnumProcessModulesEx(ctypes.c_void_p(h), None, 0, ctypes.byref(Need), LIST_MODULES_ALL)
    if not Need.value:
        return None
    count = Need.value // ctypes.sizeof(ctypes.c_void_p)
    arr = (ctypes.c_void_p * count)()
    got = ctypes.c_size_t(0)
    if not psapi.EnumProcessModulesEx(ctypes.c_void_p(h), arr, Need.value, ctypes.byref(got), LIST_MODULES_ALL):
        return None
    n = got.value // ctypes.sizeof(ctypes.c_void_p)
    name = ctypes.create_unicode_buffer(512)
    for i in range(n):
        psapi.GetModuleFileNameExW(ctypes.c_void_p(h), ctypes.c_void_p(arr[i]), name, 512)
        if name.value.lower().endswith('backpackbattles.exe'):
            # size = distance to next module base (modules are sorted ascending)
            base = arr[i]
            nxt = None
            for j in range(n):
                if arr[j] > base and (nxt is None or arr[j] < nxt):
                    nxt = arr[j]
            size = (nxt - base) if nxt else (64 << 20)
            return base, size, name.value
    return None

def image_size(h, base):
    """Read SizeOfImage from the PE header at the module base in the target."""
    hdr = read_mem(h, base, 0x1000)
    if len(hdr) < 0x400 or hdr[:2] != b'MZ':
        return None
    e_lfanew = int.from_bytes(hdr[0x3C:0x40], 'little')
    if hdr[e_lfanew:e_lfanew+4] != b'PE\x00\x00':
        return None
    opt = e_lfanew + 0x18
    size = int.from_bytes(hdr[opt+0x38:opt+0x3C], 'little')  # PE32+ SizeOfImage
    return size if 0 < size < (1 << 28) else None

def gdec_parts(path):
    d = open(path, 'rb').read()
    assert d[:4] == b'GDEC'
    return d[32:48], d[8:24], int.from_bytes(d[24:32], 'little'), d[32:]

def full_validate(key, md5e, ct, ln):
    from Crypto.Cipher import AES
    pt = AES.new(key, AES.MODE_ECB).decrypt(ct)
    return hashlib.md5(pt[:ln]).digest() == md5e

def main():
    pid = int(sys.argv[1]) if len(sys.argv) > 1 else 7308
    sample = os.path.join(r'D:\文件资料\学习\自动背包AI\unpacked_new',
                          'CharacterClasses', 'CharacterClass.gde')
    first_blk, md5e, ln, ct = gdec_parts(sample)

    h = k32.OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, False, pid)
    if not h:
        print(f"OpenProcess failed err={ctypes.GetLastError()}"); return 1

    mod = main_module(h, pid)
    if not mod:
        print("main module not found"); return 1
    base, size0, name = mod
    size = image_size(h, base) or min(size0, 128 << 20)
    print(f"module: {name}\n  base={hex(base)} image_size={size/1e6:.1f} MB", flush=True)

    from Crypto.Cipher import AES
    blob = read_mem(h, base, size)
    print(f"read {len(blob)/1e6:.1f} MB", flush=True)

    # brute force every 32-byte window in the image
    t0 = time.time(); cands = []
    mv = memoryview(blob)
    new = AES.new
    n = len(blob)
    for i in range(n - 31):
        pt = new(mv[i:i+32], AES.MODE_ECB).decrypt(first_blk)
        if pt[:4] == b'GDSC':
            kh = blob[i:i+32].hex()
            if kh not in cands:
                cands.append(kh)
                print(f"  [{i}] CANDIDATE {kh}", flush=True)
    print(f"brute-force: {n-31} windows in {time.time()-t0:.0f}s, {len(set(cands))} candidate(s)", flush=True)

    for kh in sorted(set(cands)):
        ok = full_validate(bytes.fromhex(kh), md5e, ct, ln)
        print(f"KEY {kh}  full-gde-md5={'OK' if ok else 'FAIL'}", flush=True)
        if ok:
            with open(r'D:\文件资料\学习\自动背包AI\tools\memory_keys.txt', 'a', encoding='utf-8') as f:
                f.write(f"{kh}  script-key  via-image-bruteforce  gde-md5-ok\n")

    # cross-reference: byte-search known keys everywhere in memory
    known = [bytes.fromhex(x) for x in (
        '8671424952511006d39f4c9e918f821391e2b06a80d946d693fb8757154ce849',
        '0001020304c6060708090a0bc30d0e0f101112131415161718191a1b1c1d1e1f')]
    addr = 0x10000; mbi = MBI(); sz = ctypes.sizeof(mbi); total = 0
    while addr < 0x7FFFFFFF0000:
        if not k32.VirtualQueryEx(ctypes.c_void_p(h), ctypes.c_void_p(addr), ctypes.byref(mbi), sz):
            break
        if mbi.State == 0x1000 and (mbi.Protect & 0xFF) in {0x02, 0x04, 0x08, 0x20, 0x40} \
           and not (mbi.Protect & 0x100) and mbi.RegionSize < (1 << 26):
            b = read_mem(h, mbi.BaseAddress, mbi.RegionSize)
            if len(b) >= 32:
                u64 = np.frombuffer(b[:len(b) & ~7], dtype='<u8')
                for k in known:
                    k8 = int.from_bytes(k[:8], 'little')
                    for c in np.nonzero(u64 == np.uint64(k8))[0]:
                        c = int(c)
                        if b[c:c+32] == k:
                            total += 1
                            print(f"known-key {k.hex()[:16]}.. @ {hex(mbi.BaseAddress+c)}", flush=True)
        nxt = (mbi.BaseAddress or addr) + mbi.RegionSize
        if nxt <= addr: break
        addr = nxt
    print(f"cross-ref byte-search hits: {total}", flush=True)
    k32.CloseHandle(ctypes.c_void_p(h))
    return 0

if __name__ == '__main__':
    sys.exit(main())
