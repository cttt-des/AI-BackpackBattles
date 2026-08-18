"""Generate AES-256-ECB decrypt validation cases using pycryptodome (authoritative).

Writes tools/_aes_kat.bin:
  uint32 LE  count N
  then N records of 64 bytes: key[32] || ct[16] || pt[16]
where ct = AES-256-ECB-encrypt(key, pt) computed by pycryptodome.

The C implementation must recover pt = decrypt(key, ct).
"""
import os, struct, random
from Crypto.Cipher import AES

OUT = os.path.join(os.path.dirname(__file__), "_aes_kat.bin")
random.seed(0xC0FFEE)
N = 300

cases = bytearray()
for _ in range(N):
    key = random.randbytes(32)
    pt = random.randbytes(16)
    ct = AES.new(key, AES.MODE_ECB).encrypt(pt)
    cases += key + ct + pt

with open(OUT, "wb") as f:
    f.write(struct.pack("<I", N))
    f.write(cases)
print(f"wrote {N} AES-256 cases to {OUT}")

# AES-128 cases
OUT128 = os.path.join(os.path.dirname(__file__), "_aes_kat128.bin")
cases = bytearray()
for _ in range(N):
    key = random.randbytes(16)
    pt = random.randbytes(16)
    ct = AES.new(key, AES.MODE_ECB).encrypt(pt)
    cases += key + ct + pt

with open(OUT128, "wb") as f:
    f.write(struct.pack("<I", N))
    f.write(cases)
print(f"wrote {N} AES-128 cases to {OUT128}")
