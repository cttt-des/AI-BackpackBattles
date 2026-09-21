"""
AES-256 key-schedule memory scanner for the running Backpack Battles process.

Finds AES-256 key schedules (60-word round-key arrays, FIPS-197 expansion) in
the process address space via the Rcon recurrence relation, vectorized with
numpy. Candidates are validated by decrypting a real GDEC file and checking
the GDSC magic + MD5 (ground truth), so only keys that actually decrypt the
game's encrypted files are reported.

Usage: python tools/mem_key_scan.py [pid]
"""
import ctypes, ctypes.wintypes as wt, sys, os, hashlib
import numpy as np

# ---------- AES S-box ----------
SBOX = np.array([
0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16,
], dtype=np.uint8).reshape(256, 1)

def subword(x):  # x: uint32 array -> mbedtls T for i%8==0, i.e. SubWord(RotWord(x)) in LE words
    b0 = (x & 0xFF).astype(np.uint8); b1 = ((x >> 8) & 0xFF).astype(np.uint8)
    b2 = ((x >> 16) & 0xFF).astype(np.uint8); b3 = ((x >> 24) & 0xFF).astype(np.uint8)
    s = SBOX[b1, 0].astype(np.uint32) | (SBOX[b2, 0].astype(np.uint32) << 8) | \
        (SBOX[b3, 0].astype(np.uint32) << 16) | (SBOX[b0, 0].astype(np.uint32) << 24)
    return s

def expand_key(key_words):
    """Full AES-256 expansion from 8 key words (list of int, little-endian words)."""
    RCON = [0x00000000]*8 + [0x01000000, 0x02000000, 0x04000000,
                             0x08000000, 0x10000000, 0x20000000, 0x40000000]
    w = list(key_words)
    for i in range(8, 60):
        t = w[i-1]
        if i % 8 == 0:
            t = ((t >> 8) | (t << 24)) & 0xFFFFFFFF
            t = (int(SBOX[(t & 0xFF), 0]) | (int(SBOX[((t >> 8) & 0xFF), 0]) << 8) |
                 (int(SBOX[((t >> 16) & 0xFF), 0]) << 16) | (int(SBOX[((t >> 24) & 0xFF), 0]) << 24))
            t ^= RCON[i // 8]
        elif i % 8 == 4:
            t = (int(SBOX[(t & 0xFF), 0]) | (int(SBOX[((t >> 8) & 0xFF), 0]) << 8) |
                 (int(SBOX[((t >> 16) & 0xFF), 0]) << 16) | (int(SBOX[((t >> 24) & 0xFF), 0]) << 24))
        w.append((w[i-8] ^ t) & 0xFFFFFFFF)
    return w

# ---------- GDEC validation ----------
def try_gdec(gdec_path, key_bytes):
    from Crypto.Cipher import AES
    d = open(gdec_path, 'rb').read()
    if d[:4] != b'GDEC':
        return None
    md5_expect = d[8:24]; plain_len = int.from_bytes(d[24:32], 'little')
    pt = AES.new(key_bytes, AES.MODE_ECB).decrypt(d[32:])
    pt = pt[:plain_len] if plain_len <= len(pt) else pt
    ok = hashlib.md5(pt).digest() == md5_expect
    return pt if ok else None

# ---------- Windows process memory ----------
k32 = ctypes.windll.kernel32
PROCESS_VM_READ = 0x10; PROCESS_QUERY_INFORMATION = 0x400
class MBI(ctypes.Structure):
    _fields_ = [("BaseAddress", ctypes.c_void_p), ("AllocationBase", ctypes.c_void_p),
                ("AllocationProtect", wt.DWORD), ("RegionSize", ctypes.c_size_t),
                ("State", wt.DWORD), ("Protect", wt.DWORD), ("Type", wt.DWORD)]

def regions(h):
    addr = 0; mbi = MBI(); size = ctypes.sizeof(mbi)
    MEM_COMMIT = 0x1000
    readable = {0x02, 0x04, 0x20, 0x40, 0x08}  # RO, RW, ER, ERW, WC
    while addr < 0x7FFFFFFF0000:
        if not k32.VirtualQueryEx(ctypes.c_void_p(h), ctypes.c_void_p(addr),
                                  ctypes.byref(mbi), size):
            break
        if mbi.State == MEM_COMMIT and (mbi.Protect & 0xFF) in readable \
           and not (mbi.Protect & 0x100):  # skip PAGE_GUARD
            yield mbi.BaseAddress, mbi.RegionSize
        addr = (mbi.BaseAddress or addr) + mbi.RegionSize
        if mbi.RegionSize == 0: break

def read_mem(h, base, size):
    buf = ctypes.create_string_buffer(size)
    got = ctypes.c_size_t(0)
    ok = k32.ReadProcessMemory(ctypes.c_void_p(h), ctypes.c_void_p(base),
                               buf, size, ctypes.byref(got))
    return buf.raw[:got.value] if ok else b''

def scan_schedule_candidates(W):
    """W: uint32 array of a region. Returns offsets p where the Rcon recurrence
    holds for i=16 and i=24 (vectorized pre-filter)."""
    n = len(W)
    if n < 64: return []
    hits = []
    # i=16: W[16]^W[8] == subword(rotword(W[15])) ^ rcon(2)
    # i=24: W[24]^W[16] == subword(rotword(W[23])) ^ rcon(4)
    # mbedtls stores LE words -> rcon is the plain byte value, not top-byte
    P = max(0, n - 60)  # keep every candidate fully in-bounds for full_check
    a1 = W[16:16+P] ^ W[8:8+P]
    b1 = subword(W[15:15+P]) ^ np.uint32(0x02)  # subword() already applies RotWord
    c1 = np.nonzero(a1 == b1)[0]
    for p in c1:
        p = int(p)
        a2 = int(W[p+24]) ^ int(W[p+16])
        x = int(W[p+23]); x = ((x >> 8) | (x << 24)) & 0xFFFFFFFF  # RotWord first
        b2 = (int(SBOX[(x & 0xFF), 0]) | (int(SBOX[((x >> 8) & 0xFF), 0]) << 8) |
              (int(SBOX[((x >> 16) & 0xFF), 0]) << 16) | (int(SBOX[((x >> 24) & 0xFF), 0]) << 24))
        b2 ^= 0x04
        if a2 == b2:
            hits.append(p)
    return hits

def full_check(W, p):
    """Verify all 52 recurrence steps; return key words or None."""
    if p + 60 > len(W):
        return None
    RCON = {16:0x02, 24:0x04, 32:0x08, 40:0x10, 48:0x20, 56:0x40, 8:0x01}
    w = [int(W[p+i]) for i in range(60)]
    for i in range(8, 60):
        t = w[i-1]
        if i % 8 == 0:
            t = ((t >> 8) | (t << 24)) & 0xFFFFFFFF
            t = (int(SBOX[(t & 0xFF), 0]) | (int(SBOX[((t >> 8) & 0xFF), 0]) << 8) |
                 (int(SBOX[((t >> 16) & 0xFF), 0]) << 16) | (int(SBOX[((t >> 24) & 0xFF), 0]) << 24))
            t ^= RCON[i]
        elif i % 8 == 4:
            t = (int(SBOX[(t & 0xFF), 0]) | (int(SBOX[((t >> 8) & 0xFF), 0]) << 8) |
                 (int(SBOX[((t >> 16) & 0xFF), 0]) << 16) | (int(SBOX[((t >> 24) & 0xFF), 0]) << 24))
        if (w[i-8] ^ t) & 0xFFFFFFFF != w[i]:
            return None
    return w[:8]

def main():
    pid = int(sys.argv[1]) if len(sys.argv) > 1 else 7308
    gdec_sample = os.path.join(r'D:\文件资料\学习\自动背包AI\unpacked_new',
                               'CharacterClasses', 'CharacterClass.gde')
    h = k32.OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, False, pid)
    if not h:
        print(f"OpenProcess({pid}) failed err={ctypes.GetLastError()}"); return 1
    print(f"opened pid={pid}")

    found = {}   # key_hex -> [locations]
    total = 0
    CHUNK = 8 << 20
    for base, rsize in regions(h):
        total += rsize
        off = 0
        while off < rsize:
            take = min(CHUNK + 512, rsize - off)  # overlap for boundary spans
            blob = read_mem(h, base + off, take)
            if len(blob) >= 256:
                W = np.frombuffer(blob[:len(blob) & ~3], dtype='<u4')
                for p in scan_schedule_candidates(W):
                    kw = full_check(W, p)
                    if kw:
                        key = b''.join(x.to_bytes(4, 'little') for x in kw)
                        kh = key.hex()
                        found.setdefault(kh, []).append(hex(base + off + p * 4))
            off += CHUNK
    print(f"scanned {total/1e6:.0f} MB, {len(found)} distinct schedule key(s)")
    for kh, locs in found.items():
        # validate against real game file
        pt = try_gdec(gdec_sample, bytes.fromhex(kh))
        tag = "VALID (decrypts GDEC, MD5 OK)" if pt is not None else "not the script key"
        print(f"  key {kh}  [{tag}]  x{len(locs)} @ {locs[:3]}")
        if pt is not None:
            open(os.path.join(r'D:\文件资料\学习\自动背包AI\tools', 'memory_keys.txt'), 'a'
                 ).write(f"{kh}  script-key  sample-ok\n")
    k32.CloseHandle(ctypes.c_void_p(h))
    return 0

if __name__ == '__main__':
    sys.exit(main())
