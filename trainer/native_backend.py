"""Use the versioned native simulator for trainer win-rate batches."""
from __future__ import annotations

from functools import lru_cache
import hashlib
import importlib.util
import json
import os
from pathlib import Path

from simulator.gd_core_engine import _MissingItem


DEFAULT_RUNTIME = Path(__file__).resolve().parents[1] / "dist/native_1_1_10"


def runtime_directory():
    selection = os.environ.get("BACKPACK_TRAINER_BACKEND", "auto")
    if selection == "python":
        return None
    directory = DEFAULT_RUNTIME if selection in ("auto", "native") else Path(selection)
    if selection == "auto" and not (directory / "manifest.json").is_file():
        return None
    return directory.resolve()


@lru_cache(maxsize=1)
def load_native(directory):
    manifest = json.loads((directory / "manifest.json").read_bytes())
    if manifest["game_version"] != "1.1.10":
        raise ValueError("The trainer requires a 1.1.10 native runtime")
    binding = directory / "sim.py"
    dll = directory / manifest["library"]
    runtime = directory / "gd_core_runtime.json"
    for path in (binding, dll, runtime):
        with path.open("rb") as stream:
            actual = hashlib.file_digest(stream, "sha256").hexdigest()
        if actual != manifest["sha256"][path.name]:
            raise ValueError(f"Unexpected contents in {path}")
    spec = importlib.util.spec_from_file_location("_backpack_trainer_native", binding)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    simulator = module.NativeSimulator(lib_path=dll, runtime_path=runtime)
    if not hasattr(simulator.lib, "gd_sim_run_batch_training"):
        raise ValueError("The native runtime lacks the seeded training entry point")
    return simulator


def run_jobs(directory, jobs, workers):
    sim = load_native(directory)
    packed = {}

    def pack(lineup):
        key = id(lineup)
        if key not in packed:
            try:
                packed[key] = sim.pack_side(lineup, strict=True)
            except (_MissingItem, TypeError, ValueError, KeyError):
                packed[key] = None
        return packed[key]

    outcomes = [-1] * len(jobs)
    batches = []
    indices = []
    for index, (player, opponent, seed) in enumerate(jobs):
        player_side, opponent_side = pack(player), pack(opponent)
        if player_side is None or opponent_side is None:
            continue
        opts = sim.make_options(seed=seed, round_id=player_side.round_id,
                                below_master=bool(player.get("below_master", False)),
                                custom_health_multiplier=player.get("custom_health_multiplier", 100.0),
                                formal_ev_gate=500000, max_time=90.0)
        batches.append((player_side, opponent_side, opts))
        indices.append(index)
    for index, result in zip(indices, sim.run_batch(batches, n_threads=workers, training=True), strict=True):
        if not result.formal_ev_capped:
            outcomes[index] = int(result.player_wins)
    return outcomes
