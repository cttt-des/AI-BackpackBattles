"""Trace Util RNG deltas on a native fixture without a GD replay dependency."""
from functools import wraps
import json
from pathlib import Path
import sys


stage = Path(__file__).resolve().parent
sim = stage / "sim_native"
sys.path[:0] = [str(sim), str(sim / "tools")]
from _cpp_verify_events import canonical_parent_indices, event_rows, first_tuple_difference
from _cmp_events import py_row_canonical
from gd_core_py._rt import RandomNumberGenerator
from gd_core_py.gd_core.CoreCombat import CoreCombat
from simulator.data import load_characters, load_items
from simulator.gd_core_engine import GDCoreEngine, kernel
from simulator.lineup import load_lineup
from verify_oracle import _FightEndGate, _py_payload


def prepare(root, cid):
    case = next(row for row in json.loads((root / "fixtures.json").read_bytes())["cases"] if row["case_id"] == cid)
    sides = ("player", "opponent")
    lineups = [load_lineup(str(root / "align/lineups" / f"oracle_{cid}_{side}.json")) for side in sides]
    stats = [{key: case[side].get(key) for key in ("stamina", "health", "regen")} for side in sides]
    lens = [[len(item.get("gems") or []) for item in case[side]["items"]] for side in sides]
    state = int(next(line[6:] for line in (root / "fights" / cid / "rng_state.txt").read_text().splitlines()
                     if line.startswith("state=")))
    order = case["native_activation_order"]
    engine = GDCoreEngine(*lineups, load_items(), load_characters(), seed=case["seed"], max_time=90.0,
                          probe_bases=(_FightEndGate,), below_master=case["below_master"],
                          p_gem_lens=lens[0], o_gem_lens=lens[1], p_activation_order=order["player"],
                          o_activation_order=order["opponent"], reseed_after_player_character=True,
                          post_seed_draws=0, rng_state=state, label_rng_enabled=bool(case.get("label_rng", True)),
                          p_stats=stats[0], o_stats=stats[1], custom_health_multiplier=case["custom_health_multiplier"])
    data = case["replay_initial"]
    engine.ctx.setReplayInitial(data["activation_rng_state"], data["idle_left"], data["flickers"], data.get("buff_state"),
                                data.get("engine_rng"), data.get("native_scene_delays", False), float(data.get("util_time", 0.0)))
    return engine, case


def main():
    source, inputs, cid = sys.argv[1:4]
    engine, case = prepare(stage / inputs, cid)
    draws = []
    active = inside = False
    activate = CoreCombat.activateItems

    def begin(self, *args):
        nonlocal active
        active = True
        return activate(self, *args)

    def wrap(name, limits):
        method = getattr(RandomNumberGenerator, name)

        @wraps(method)
        def observed(self, *args):
            nonlocal inside
            if not active or inside or self is not engine.ctx.rng.rng:
                return method(self, *args)
            before = self.get_state()
            inside = True
            try:
                result = method(self, *args)
            finally:
                inside = False
            stack = []
            frame = sys._getframe(1)
            for _index in range(8):
                if frame is None:
                    break
                stack.append([Path(frame.f_code.co_filename).name, frame.f_code.co_name])
                frame = frame.f_back
            draws.append({"kind": name, "bounds": limits or args, "before": str(before), "state": str(self.get_state()),
                          "value": result, "time": engine.ctx.combat_time, "stack": stack})
            return result

        return observed

    CoreCombat.activateItems = begin
    for name, limits in (("randf", (0, 1)), ("randi", (0, 2**32 - 1)), ("randi_range", None), ("randf_range", None)):
        setattr(RandomNumberGenerator, name, wrap(name, limits))
    engine.run()
    names = {int(value): key for key, value in kernel()["CoreConst"].EventType.items()}
    replayed = _py_payload(cid, case["seed"], engine, names, True)
    expected = json.loads((stage / source / cid / "events.json").read_bytes())
    streams = [canonical_parent_indices([py_row_canonical(row) for row in event_rows(doc)[0]])
               for doc in (expected, replayed)]
    first = first_tuple_difference(*streams)
    output = stage / (inputs + "_rng_py")
    output.mkdir(exist_ok=True)
    (output / f"{cid}.json").write_text(json.dumps(draws, ensure_ascii=False), encoding="utf8")
    print(cid, "events", [len(rows) for rows in streams], "first", first, "draws", len(draws))
    if first is not None:
        print([rows[first] for rows in streams if first < len(rows)])


if __name__ == "__main__":
    main()
