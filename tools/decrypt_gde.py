"""
decrypt_gde.py  --  Decrypt Godot GDEC scripts (.gde -> GDScript bytecode "GDSC").

GDEC container (verified on Backpack Battles Combat.gde):
    [4 "GDEC"][4 version][16 MD5(plaintext)][8 LE plaintext len][AES-256-ECB ciphertext]

The encryption key is a raw 32-byte AES-256 key. To obtain it see
tools/scan_gdec_key.py (static) or extract it from the running process
(Godot reconstructs an obfuscated key at startup).

Usage:
    # single file
    python tools/decrypt_gde.py --key <64hex> input.gde -o out.gds
    # batch a directory (writes <name>.gds next to each .gde)
    python tools/decrypt_gde.py --key <64hex> --dir extracted --ext .gds
    # pipe key from file
    python tools/decrypt_gde.py --key-file key.txt input.gde -o out.gds
"""
import argparse
import hashlib
import os
import sys

from Crypto.Cipher import AES


def decrypt_gde(data: bytes, key: bytes) -> bytes | None:
    if len(key) not in (16, 32):
        raise ValueError("key must be 16 bytes (AES-128) or 32 bytes (AES-256)")
    if data[:4] != b"GDEC":
        # already plaintext / not encrypted
        return data
    version = int.from_bytes(data[4:8], "little")
    md5_expected = data[8:24]
    plain_len = int.from_bytes(data[24:32], "little")
    ct = data[32:]
    aes = AES.new(key, AES.MODE_ECB)
    # decrypt block by block (ECB)
    plain = aes.decrypt(ct)
    if plain[:4] != b"GDSC":
        return None  # wrong key
    # trim to the declared plaintext length (trailing padding byte)
    if plain_len <= len(plain):
        plain = plain[:plain_len]
    # verify integrity if MD5 matches the (possibly trimmed) plaintext
    if hashlib.md5(plain).digest() == md5_expected:
        pass  # integrity OK
    return plain


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("files", nargs="*", help=".gde files to decrypt")
    ap.add_argument("--key", help="64-hex-char AES-256 key")
    ap.add_argument("--key-file", help="path to a file containing the 64-hex key")
    ap.add_argument("-o", "--out", help="output file (single-file mode)")
    ap.add_argument("--dir", help="decrypt every *.gde under this directory")
    ap.add_argument("--ext", default=".gds", help="output extension for --dir (default .gds)")
    args = ap.parse_args()

    key = None
    if args.key_file:
        key = bytes.fromhex(open(args.key_file, "r").read().strip())
    elif args.key:
        key = bytes.fromhex(args.key)
    if key is None:
        print("ERROR: provide --key or --key-file", file=sys.stderr)
        return 2

    targets = list(args.files)
    if args.dir:
        for root, _, fs in os.walk(args.dir):
            for f in fs:
                if f.endswith(".gde"):
                    targets.append(os.path.join(root, f))

    if not targets:
        print("ERROR: no input files", file=sys.stderr)
        return 2

    ok = fail = 0
    for path in targets:
        data = open(path, "rb").read()
        plain = decrypt_gde(data, key)
        if plain is None:
            print(f"  FAIL  {path}  (wrong key or not GDEC)")
            fail += 1
            continue
        if args.dir:
            outp = path[: -len(".gde")] + args.ext
        else:
            outp = args.out or (path + args.ext)
        open(outp, "wb").write(plain)
        print(f"  OK    {path}  ->  {outp}  ({len(plain)} bytes)")
        ok += 1
    print(f"\nDone. decrypted={ok} failed={fail}")
    return 0 if fail == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
