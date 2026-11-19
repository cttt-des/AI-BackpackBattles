"""Package a corpus-verified native DLL and its matching 1.1.10 runtime."""
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import tempfile


STAGE = Path(__file__).resolve().parent
REPO = STAGE.parents[1]


def digest(path):
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dll", type=Path, required=True)
    parser.add_argument("--gate", type=Path, required=True)
    parser.add_argument("--out", type=Path, default=REPO / "dist/native_1_1_10")
    args = parser.parse_args()
    dll = args.dll.resolve()
    gate = json.loads(args.gate.read_bytes())
    for cohort, count in (("base", 914), ("expand", 1690)):
        result = gate["cohorts"][cohort]
        if result["passed"] != count or result["winner_mismatch"] or result["pending"]:
            parser.error(f"The {cohort} corpus has no complete result")
    if not gate["complete"] or digest(dll) != gate["dll_sha256"]:
        parser.error("The DLL differs from the completed corpus gate")

    runtime = STAGE / "sim_native/assets/gd_core_runtime.json"
    encoded = json.dumps(json.loads(runtime.read_bytes()), ensure_ascii=False, sort_keys=True, separators=(",", ":"))
    if hashlib.sha256(encoded.encode("utf8")).hexdigest() != gate["runtime_data_sha256"]:
        parser.error("The runtime table differs from the completed corpus gate")
    binding = STAGE / "sim_native/native_sim_cpp/native_sim/sim.py"
    inputs = {"sim.py": binding, "gd_core_runtime.json": runtime, "libgdcore.dll": dll}
    manifest = {"game_version": "1.1.10", "library": "libgdcore.dll", "verified_fights": 2604,
                "gate_sha256": digest(args.gate), "sha256": {name: digest(file) for name, file in inputs.items()}}

    destination = args.out.resolve()
    if destination.exists():
        if (json.loads((destination / "manifest.json").read_bytes()) == manifest
                and all(digest(destination / name) == value for name, value in manifest["sha256"].items())):
            print(destination)
            return
        parser.error(f"A different runtime already exists at {destination}")
    destination.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=destination.parent) as root:
        payload = Path(root) / "runtime"
        payload.mkdir()
        for name, source in inputs.items():
            shutil.copyfile(source, payload / name)
        (payload / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf8")
        payload.rename(destination)
    print(destination)


if __name__ == "__main__":
    main()
