"""Versioned 1.1.10 C++ combat simulation for Windows x64."""
from pathlib import Path
from functools import lru_cache
import hashlib
import json

__version__ = '0.6.0'


@lru_cache(maxsize=1)
def get_simulator():
    from .sim import NativeSimulator
    root = Path(__file__).parent
    manifest = json.loads((root / 'manifest.json').read_bytes())
    for name, expected in manifest['sha256'].items():
        if hashlib.sha256((root / name).read_bytes()).hexdigest() != expected:
            raise RuntimeError(f'Native runtime checksum failed for {name}')
    return NativeSimulator(root / 'libgdcore.dll', runtime_path=root / 'gd_core_runtime.json')


def run_mc(player, opponent, *, seed=42, runs=200, workers=1):
    """Run consecutive seeds on v3/v4 lineup dictionaries, returning JSON-compatible results."""
    if runs < 1 or workers < 1:
        raise ValueError('runs and workers must be positive')
    sim = get_simulator()
    p, o = sim.pack_side(player, strict=True), sim.pack_side(opponent, strict=True)
    pairs = [(p, o, sim.make_options(seed=seed+i, round_id=p.round_id,
                                   formal_ev_gate=500000, max_time=90.0)) for i in range(runs)]
    results = sim.run_batch(pairs, n_threads=workers, training=True)
    if any(r.formal_ev_capped for r in results):
        raise RuntimeError('Combat event safety limit reached')
    return {'version': __version__, 'game_version': '1.1.10', 'runs': runs,
            'wins': sum(r.player_wins for r in results),
            'win_rate': sum(r.player_wins for r in results) / runs,
            'results': [{'seed': seed+i, 'player_wins': bool(r.player_wins),
                         'combat_time': r.combat_time, 'events': r.event_count,
                         'timed_out': bool(r.timed_out)} for i, r in enumerate(results)]}
