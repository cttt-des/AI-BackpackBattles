"""
match_blobs.py -- match in-process dumped GDSC blobs to known scripts.

Each blob starts with a decrypted "GDSC" buffer but may be a larger allocation.
For each blob we try every known (plain_len, md5) from the .gde headers: if
md5(blob[:plain_len]) matches, that is the script and we save blob[:plain_len]
as <script>.gdc.
"""
import argparse
import glob
import hashlib
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import dump_decrypted as dd


def main():
    ap = argparse.ArgumentParser()
    here = os.path.dirname(os.path.abspath(__file__))
    proj = os.path.dirname(here)
    ap.add_argument("--blobs", default="C:/tmp/bb/dump")
    ap.add_argument("--extracted", default=os.path.join(proj, "extracted"))
    ap.add_argument("--out", default=os.path.join(proj, "extracted_gdc"))
    args = ap.parse_args()

    lookup, by_len, stats = dd.build_index(args.extracted)
    print(f"[*] index={stats['count']} scripts")

    os.makedirs(args.out, exist_ok=True)
    matched = {}
    seen_blobs = set()
    for path in glob.glob(os.path.join(args.blobs, "blob_*.bin")):
        b = open(path, "rb").read()
        found = None
        for L, entries in by_len.items():
            if L > len(b):
                continue
            h = hashlib.md5(b[:L]).digest()
            for (m, rel) in entries:
                if h == m:
                    found = (rel, L)
                    break
            if found:
                break
        if found:
            rel, L = found
            outp = os.path.join(args.out, rel + ".gdc")
            os.makedirs(os.path.dirname(outp), exist_ok=True)
            open(outp, "wb").write(b[:L])
            matched[rel] = L
            print(f"  [+] {rel}  ({L} bytes)  <- {os.path.basename(path)}")
        else:
            print(f"  [?] {os.path.basename(path)} ({len(b)} bytes) no match")

    print(f"\n[*] matched {len(matched)} / {stats['count']} scripts")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
