# Native C++20 Backpack Battles Simulator (`native_sim`)

Standalone bundle extracted from `AI-BackpackBattles-0.5.0`.
Includes C++20 runtime (`native_sim/gd_rt.*`, `engine_wrapper.cpp`), 663 transpiled GDScript 3.6 scripts (`native_sim/gen/`),
precompiled macOS arm64 shared library (`native_sim/libgdcore.dylib`), full GDScript->C++ transpiler (`tools/gd_to_cpp.py`),
`assets/gd_core_runtime.json`, and sample lineups (`lineups/`).

## Quick Smoke Test (Python 3 stdlib only!)
```bash
python3 - <<'PY'
import json
from pathlib import Path
from native_sim import get_simulator

sim = get_simulator()
p = json.loads(Path("lineups/truth_20261001_220653_R19_player.json").read_text())
o = json.loads(Path("lineups/truth_20261001_220653_R19_opponent.json").read_text())
res = sim.run_one(p, o, seed=1001, round_id=int(p.get("round", 1)),
                  native_activation_order=False, reseed_after_player_character=False,
                  label_rng_enabled=True, max_time=600.0)
print(f"win={res.player_wins} t={res.combat_time:.3f} php={res.player_hp:.1f} ohp={res.opponent_hp:.1f} ticks={res.ticks}")
PY
```

## Rebuild Shared Library (macOS / Linux clang++)
```bash
python3 native_sim/build.py --clean
# Re-transpile from gd_core/ & gd_core_items/:
python3 tools/gd_to_cpp.py && python3 native_sim/build.py --clean
```
