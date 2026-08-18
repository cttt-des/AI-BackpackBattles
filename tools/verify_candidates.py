"""Verify candidate AES-256 keys produced by scan_key.exe.

Reads <candidates_file> (lines: "<loc> <keyhex>"), and for each candidate key:
  1. decrypts extracted/Core/Combat.gde fully and checks the GDSC magic + MD5.
  2. if OK, also confirms on 2 more scripts for robustness.
Prints any working key(s) and writes the best one to <out_key_file>.
"""
import sys, os, hashlib
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from decrypt_gde import decrypt_gde

BASE = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "extracted")
TEST_FILES = [
    "Core/Combat.gde",
    "Core/CombatEvent.gde",
    "Core/Player.gde",
    "Core/Game.gde",
]

def main():
    if len(sys.argv) < 3:
        print("usage: verify_candidates.py <candidates_file> <out_key_file> [gde_dir]")
        return 2
    cands = sys.argv[1]
    out_key = sys.argv[2]
    gde_dir = sys.argv[3] if len(sys.argv) > 3 else BASE

    working = []
    with open(cands, "r") as f:
        lines = [l.strip() for l in f if l.strip()]
    print(f"loaded {len(lines)} candidates")
    for line in lines:
        parts = line.split()
        if len(parts) < 2:
            continue
        loc = parts[0]
        # format: "<loc> <type>:<keyhex>"  (type 1=AES256,2=AES128a,3=AES128b)
        spec = parts[1]
        if ":" in spec:
            keyhex = spec.split(":", 1)[1]
        else:
            keyhex = spec
        try:
            key = bytes.fromhex(keyhex)
        except Exception:
            continue
        if len(key) not in (16, 32):
            continue
        # test primary
        p = os.path.join(gde_dir, TEST_FILES[0])
        if not os.path.exists(p):
            print("missing test file", p); continue
        plain = decrypt_gde(open(p, "rb").read(), key)
        if plain is None:
            continue
        # confirm md5 is consistent
        ok_files = [TEST_FILES[0]]
        for tf in TEST_FILES[1:]:
            pp = os.path.join(gde_dir, tf)
            if not os.path.exists(pp):
                continue
            pl = decrypt_gde(open(pp, "rb").read(), key)
            if pl is not None:
                ok_files.append(tf)
        print(f"WORKING KEY from {loc}: {keyhex}")
        print(f"   verified on: {ok_files}")
        working.append((loc, keyhex, ok_files))
        break  # first working key is enough; stop

    if working:
        best = working[0]
        with open(out_key, "w") as f:
            f.write(best[1])
        print(f"\nWROTE working key to {out_key}: {best[1]}")
        print(f"verified files: {best[2]}")
        return 0
    else:
        print("\nNO WORKING KEY FOUND among candidates")
        return 1

if __name__ == "__main__":
    raise SystemExit(main())
