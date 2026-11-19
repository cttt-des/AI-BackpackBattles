"""Record provenance and recover a separate installed game copy for battle recording."""

import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import struct
import subprocess

from pck_full_extract import extract


REPO = Path(__file__).resolve().parent.parent
GAME_FILES = ("BackpackBattles.exe", "BackpackBattles.pck", "libgdsqlite.dll", "steam_api64.dll")


def read_varint(data, offset):
    value = 0
    for shift in range(0, 70, 7):
        byte = data[offset]
        offset += 1
        value |= (byte & 127) << shift
        if byte < 128:
            return value, offset
    raise ValueError("Invalid manifest varint")


def fields(data):
    offset = 0
    while offset < len(data):
        tag, offset = read_varint(data, offset)
        wire = tag & 7
        if wire == 0:
            value, offset = read_varint(data, offset)
        elif wire == 2:
            length, offset = read_varint(data, offset)
            end = offset + length
            if end > len(data):
                raise ValueError("Truncated manifest field")
            value = data[offset:end]
            offset = end
        else:
            raise ValueError(f"Unexpected manifest wire type {wire}")
        yield tag >> 3, value


def depot_hashes(path):
    data = path.read_bytes()
    magic, length = struct.unpack_from("<II", data)
    if magic != 0x71F617D0 or 8 + length > len(data):
        raise ValueError("Invalid Steam depot manifest payload")
    mappings = [dict(fields(value)) for number, value in fields(data[8:8 + length]) if number == 1]
    # Steam may encrypt file names. Matching the size and whole-file SHA-1
    # identifies these four distinct payload files without using account data.
    return {(entry[2], entry[5].hex()) for entry in mappings if 2 in entry and 5 in entry}


def file_hash(path, algorithm):
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, algorithm).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, required=True)
    parser.add_argument("--manifest", type=Path, required=True)
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--version", required=True)
    parser.add_argument("--verify-only", action="store_true")
    parser.add_argument("--require-depot-match", action="store_true",
                        help="Require exact depot files when explicitly checking an unmodified release")
    args = parser.parse_args()

    expected = depot_hashes(args.manifest)
    provenance = {"manifest": str(args.manifest.resolve()), "files": {}}
    rejected = []
    for name in GAME_FILES:
        path = args.source / name
        size, sha1 = path.stat().st_size, file_hash(path, "sha1")
        match = (size, sha1) in expected
        print(f"{name}: {size} {sha1} {'OK' if match else 'DIFFERENT'}", flush=True)
        if not match:
            rejected.append(name)
        provenance["files"][name] = {"size": size, "sha1": sha1}
    if rejected and args.require_depot_match:
        raise SystemExit("Source files differ from Steam depot: " + ", ".join(rejected))
    if args.verify_only:
        return

    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=False)
    source = out / "source"
    source.mkdir()
    for name in GAME_FILES:
        copied = source / name
        shutil.copy2(args.source / name, copied)
        info = provenance["files"][name]
        if file_hash(copied, "sha1") != info["sha1"]:
            raise ValueError(f"Source changed while copying {name}")
        info["sha256"] = file_hash(copied, "sha256")

    pack = source / "BackpackBattles.pck"
    raw = out / "raw"
    if not extract(pack, raw):
        raise ValueError("Extracted PCK entries failed their MD5 checks")
    notes = (REPO / "docs/reverse_engineering_2026-09.md").read_text("utf8")
    key = re.search(r"--key=([0-9a-fA-F]{64})", notes).group(1)
    decompiled = out / "decompiled"
    cmd = [str(REPO / "tools/gdre/gdre_tools.exe"), "--headless", f"--recover={pack}",
           f"--key={key}", f"--output={decompiled}"]
    with (out / "gdre.log").open("wb") as log:
        result = subprocess.run(cmd, cwd=out, stdout=log, stderr=subprocess.STDOUT,
                                creationflags=subprocess.CREATE_NO_WINDOW)
    if result.returncode:
        raise SystemExit(f"GDRE failed with code {result.returncode}. See {out / 'gdre.log'}")
    game = (decompiled / "Core/Game.gd").read_text("utf8")
    version = re.search(r'^var VERSION\s*=\s*"([^"]+)"', game, re.M).group(1)
    if version != args.version:
        raise ValueError(f"Expected {args.version}, recovered {version}")
    scripts = [p.relative_to(raw).with_suffix(".gd") for p in raw.rglob("*.gde")]
    missing = [p for p in scripts if not (decompiled / p).is_file()]
    if missing:
        raise ValueError(f"Missing {len(missing)} decoded scripts: {missing[:8]}")
    provenance["version"] = version
    provenance["steam_depot_match"] = not rejected
    provenance["decrypted_scripts"] = len(scripts)
    provenance["pack_entries"] = sum(p.is_file() for p in raw.rglob("*"))
    (out / "source_manifest.json").write_text(json.dumps(provenance, indent=2), encoding="utf8")
    print(f"Recovered installed release {version} with {len(scripts)} scripts into {out}")


if __name__ == "__main__":
    main()
