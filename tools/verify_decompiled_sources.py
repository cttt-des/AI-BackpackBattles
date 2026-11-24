"""Verify the versioned source snapshots; --full also checks local game assets."""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import re


ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / "docs/decompiled_sources_20261124.json"
TEXT_SUFFIXES = {
    ".gd", ".tscn", ".material", ".tres", ".gdshader", ".csv", ".shader",
    ".cfg", ".txt", ".godot", ".gdnlib", ".gdns",
}
LOCAL_DIRS = {".import", ".autoconverted", ".godot", "__pycache__"}


def inventory(root: Path, *, full: bool = False) -> dict:
    """Hash sorted relative paths and each file's raw SHA-256, including file sizes."""
    digest = hashlib.sha256()
    count = size = 0
    for path in sorted(root.rglob("*"), key=lambda p: p.relative_to(root).as_posix()):
        if not path.is_file():
            continue
        relative = path.relative_to(root)
        if not full and (path.suffix not in TEXT_SUFFIXES
                         or any(part in LOCAL_DIRS for part in relative.parts[:-1])):
            continue
        data = path.read_bytes()
        entry = [relative.as_posix(), len(data), hashlib.sha256(data).hexdigest()]
        digest.update((json.dumps(entry, ensure_ascii=False, separators=(",", ":"))
                       + "\n").encode("utf-8"))
        count += 1
        size += len(data)
    return {"files": count, "bytes": size, "sha256": digest.hexdigest()}


def verify(*, full: bool = False) -> None:
    manifest = json.loads(MANIFEST.read_text("utf-8"))
    for snapshot in manifest["snapshots"]:
        root = ROOT / snapshot["path"]
        game = (root / "Core/Game.gd").read_text("utf-8-sig")
        match = re.search(r'^var VERSION = "([^"]+)"', game, re.MULTILINE)
        if not match or match[1] != snapshot["version"]:
            raise ValueError(f"Version mismatch: {root}")
        for mode in ("text", "full") if full else ("text",):
            actual = inventory(root, full=mode == "full")
            if actual != snapshot[mode]:
                raise ValueError(f"Snapshot changed: {snapshot['path']} ({mode}): {actual}")
        print(f"OK {snapshot['version']}: {snapshot['path']} ({'full' if full else 'text'})")
    alias = ROOT / manifest["compatibility_alias"]
    if alias.exists():
        if not alias.samefile(ROOT / manifest["snapshots"][0]["path"]):
            raise ValueError(f"Compatibility path is a separate copy: {alias}")
        print(f"OK compatibility alias: {manifest['compatibility_alias']}")
    else:
        print("Compatibility alias absent; only historical local tools need it.")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--full", action="store_true", help="also verify all local binary assets")
    verify(full=parser.parse_args().full)
