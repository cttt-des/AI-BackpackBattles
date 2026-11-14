"""Gate 1 bit-exact parity & performance benchmark: native_sim (C++20) vs GDCoreEngine."""

from __future__ import annotations

import argparse
import contextlib
import io
import json
import os
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
if str(ROOT) not in sys.path:
    sys.path.insert(0, str(ROOT))

from concurrent.futures import ProcessPoolExecutor

from backpack_ai.board import to_engine_lineup
from gd_core_py._rt import Vector2, _bind_battle, _shuffle
from native_sim.sim import get_simulator
from simulator.gd_core_engine import GDCoreEngine, kernel, runtime_data
from simulator.godot_order import sort_custom

_PY_DESCR_CACHE: dict = {}
_KERNEL: dict | None = None


def _K() -> dict:
    global _KERNEL
    if _KERNEL is None:
        _KERNEL = kernel()
    return _KERNEL


def _py_descr(ctx, rt: dict, key: str):
    if key not in _PY_DESCR_CACHE:
        ds = rt["items"][key]["descr"]
        _PY_DESCR_CACHE[key] = _K()["CoreItemData"]().fromDict(dict(ds))
    return ctx.item_book.register(_PY_DESCR_CACHE[key])


def run_gd_case(case: dict) -> dict:
    K = _K()
    rt = runtime_data()
    ctx = K["CoreContext"](int(case["seed"]), K["CoreHooks"]())
    ctx.cur_round = int(case.get("round_id", 1))
    ctx.custom_health_multiplier = float(case.get("custom_health_multiplier", 100.0))
    ctx.label_rng_enabled = bool(case.get("label_rng", True))
    ctx.deferred_flush_enabled = False
    ctx.eb_relay_mirrored = False
    ctx.class_resources = {
        int(rt["classes"][ck]): dict(info)
        for ck, info in rt["characters"].items()
        if ck in rt["classes"]
    }

    def mk_chr(pid: int, lu: dict):
        ch = K["CoreCharacter"](ctx, pid)
        ch.characterClass = int(lu["class"])
        ch.setMaxHealth(float(lu["health"]))
        ch.setCurrentHealth(float(lu["health"]))
        ch.maxStamina = float(lu["stamina"])
        ch.baseMaxStamina = float(lu.get("base_max_stamina", lu["stamina"]))
        ch.baseStaminaRegen = float(lu["regen"])
        ch.staminaRegen = float(lu["regen"])
        ch.fillUpStamina()
        return ch

    def reg_side(lu: dict) -> None:
        for e in lu["items"]:
            if e.get("storage"):
                continue
            _py_descr(ctx, rt, e["key"])
            for g in e.get("gems") or []:
                if g:
                    gk = g if isinstance(g, str) else (g.get("key") or g.get("id") or "")
                    if gk:
                        _py_descr(ctx, rt, gk)

    def mk_side(ch, lu: dict, otype: int) -> list:
        out = []
        R = K["_R"]
        CoreConst = K["CoreConst"]
        for e in lu["items"]:
            if e.get("storage"):
                continue
            d = _py_descr(ctx, rt, e["key"])
            it = R.C(e["script"])()
            if e.get("crafted") is not None:
                it.crafted_instance = bool(e["crafted"])
            it.setup(ctx, d, ch)
            n = int(rt["items"][e["key"]].get("sockets", 0))
            for _ in range(n):
                it.gems.append(None)
            it.collisionCells = [Vector2(x, y) for x, y in e["collision"]]
            it.affectedTileCells = {
                int(k): [Vector2(x, y) for x, y in v]
                for k, v in (e.get("affected") or {}).items()
            }
            it.occupiedCells = [Vector2(x, y) for x, y in e["occupied"]]
            it.ownerType = otype
            fd = ((int(e.get("rotation") or 0) // 90) % 4)
            it.faceDirection = fd
            cf = e.get("charge_frame") or (0, 0)
            it.chargeFrame = [Vector2(cf[0], cf[1])] * 4
            it._readyInit()
            ch.inventory.addItem(it, it.occupiedCells)
            if e.get("effects") and hasattr(it, "setCraftedEffects"):
                it.setCraftedEffects(list(e["effects"]))
            for gi, g in enumerate(e.get("gems") or []):
                if g:
                    gk = g if isinstance(g, str) else (g.get("key") or g.get("id") or "")
                    if not gk:
                        continue
                    gd = _py_descr(ctx, rt, gk)
                    git = R.C(rt["items"][gk]["script"])()
                    git.setup(ctx, gd, ch)
                    git.collisionCells = [Vector2(0, 0)]
                    git.occupiedCells = [Vector2(0, 0)]
                    git.ownerType = CoreConst.Owner.Socket
                    git.faceDirection = 0
                    git.chargeFrame = [Vector2(0, 0)] * 4
                    git._readyInit()
                    it.setGem(gi, git)
            out.append(it)
        return out

    with contextlib.redirect_stdout(io.StringIO()):
        _bind_battle(int(case["seed"]))
        p = mk_chr(K["CoreCharacter"].ID.PLAYER, case["player"])
        ctx.rng.rng.seed = int(case["seed"])
        ctx.player = p
        combat = K["CoreCombat"](ctx)
        ctx.combat = combat
        reg_side(case["player"])
        reg_side(case["opponent"])
        p_it = mk_side(p, case["player"], K["CoreConst"].Owner.PlayerInventory)
        o = mk_chr(K["CoreCharacter"].ID.OPPONENT, case["opponent"])
        ctx.opponent = o
        combat.setup(p, o)
        o_it = mk_side(o, case["opponent"], K["CoreConst"].Owner.Opponent)
        _bind_battle(int(case["seed"]))
        p_ord, o_ord = list(p_it), list(o_it)
        for items in (p_ord, o_ord):
            _shuffle(items)
            sort_custom(items, key=lambda item: -item.getTriggerPriority())
        combat.startBattle(p_ord, o_ord, True)
        ticks = 0
        while not combat.fight_ended and ticks < 20000:
            combat.physicsTick(K["CoreContext"].PHYSICS_DELTA)
            ticks += 1
    w = combat.winner()
    return {
        "player_wins": 1 if (w is not None and w.playerId == K["CoreCharacter"].ID.PLAYER) else 0,
        "timed_out": 1 if combat.timed_out else 0,
        "combat_time": float(combat.combat_time),
        "ticks": int(ticks),
        "fatigue_counter": int(combat.fatigue_counter),
        "player_hp": float(p.curHealth),
        "opponent_hp": float(o.curHealth),
        "out_of_stamina_count": int(ctx.out_of_stamina_count),
    }


def _check_batch_py(cases: list[dict]) -> list[dict]:
    return [run_gd_case(c) for c in cases]


def check_dataset(path: Path, limit: int, n_threads: int) -> tuple[int, int, float, float]:
    sim = get_simulator()
    cases = json.loads(path.read_text())["cases"]
    if limit > 0:
        cases = cases[:limit]

    t0 = time.perf_counter()
    pairs = []
    for c in cases:
        opt = sim.make_options(
            seed=int(c["seed"]),
            round_id=int(c.get("round_id", 1)),
            label_rng_enabled=bool(c.get("label_rng", True)),
            native_activation_order=True,
            reseed_after_player_character=True,
            custom_health_multiplier=float(c.get("custom_health_multiplier", 100.0)),
            formal_ev_gate=500000,
        )
        pairs.append((c["player"], c["opponent"], opt))

    t_pack = time.perf_counter()
    cpp_results = sim.run_batch(pairs, n_threads=n_threads)
    t_cpp = time.perf_counter() - t_pack

    t_py0 = time.perf_counter()
    if len(cases) >= 40 and n_threads > 1:
        chunk = max(1, (len(cases) + n_threads - 1) // n_threads)
        chunks = [cases[i : i + chunk] for i in range(0, len(cases), chunk)]
        with ProcessPoolExecutor(max_workers=n_threads) as pool:
            py_results = [r for sub in pool.map(_check_batch_py, chunks) for r in sub]
    else:
        py_results = [run_gd_case(c) for c in cases]
    t_py = time.perf_counter() - t_py0

    mismatches = 0
    for c, cr, pr in zip(cases, cpp_results, py_results):
        diffs = []
        if cr.player_wins != pr["player_wins"]:
            diffs.append(f"win {cr.player_wins}!={pr['player_wins']}")
        if cr.timed_out != pr["timed_out"]:
            diffs.append(f"timeout {cr.timed_out}!={pr['timed_out']}")
        if abs(cr.combat_time - pr["combat_time"]) > 1e-9:
            diffs.append(f"t {cr.combat_time:.6f}!={pr['combat_time']:.6f}")
        if cr.ticks != pr["ticks"]:
            diffs.append(f"ticks {cr.ticks}!={pr['ticks']}")
        if abs(cr.player_hp - pr["player_hp"]) > 1e-6:
            diffs.append(f"php {cr.player_hp}!={pr['player_hp']}")
        if abs(cr.opponent_hp - pr["opponent_hp"]) > 1e-6:
            diffs.append(f"ohp {cr.opponent_hp}!={pr['opponent_hp']}")
        if cr.out_of_stamina_count != pr["out_of_stamina_count"]:
            diffs.append(f"oos {cr.out_of_stamina_count}!={pr['out_of_stamina_count']}")
        if diffs:
            mismatches += 1
            if mismatches <= 10:
                print(f"  MISMATCH {c.get('case_id')}: {', '.join(diffs)}")

    n = len(cases)
    print(
        f"[{path.name}] n={n} mismatches={mismatches} | "
        f"C++ ({n_threads}T)={t_cpp:.3f}s ({t_cpp*1000/n:.3f} ms/fight) | "
        f"Py={t_py:.3f}s ({t_py*1000/n:.2f} ms/fight) | speedup={t_py/max(t_cpp,1e-9):.1f}x"
    )
    return n, mismatches, t_cpp, t_py


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--threads", type=int, default=min(10, os.cpu_count() or 8))
    ap.add_argument("--truth", action="store_true")
    args = ap.parse_args()

    sim = get_simulator()
    if args.truth or args.limit <= 20:
        p_lu = json.loads((ROOT / "lineups/truth_20261001_220653_R19_player.json").read_text())
        o_lu = json.loads((ROOT / "lineups/truth_20261001_220653_R19_opponent.json").read_text())
        for a, b, s, tag in [(p_lu, o_lu, 1001, "P_vs_O"), (o_lu, p_lu, 1002, "O_vs_P")]:
            eng = GDCoreEngine(a, b, seed=s, max_time=600.0)
            eng.run()
            cr = sim.run_one(
                a,
                b,
                seed=s,
                round_id=int(a.get("round", 1)),
                native_activation_order=False,
                reseed_after_player_character=False,
                label_rng_enabled=True,
                max_time=600.0,
            )
            print(
                f"[truth {tag}] C++ win={cr.player_wins} t={cr.combat_time:.3f} "
                f"php={cr.player_hp:.1f} ohp={cr.opponent_hp:.1f} ticks={cr.ticks} | "
                f"Py win={1 if eng.player_wins() else 0} t={eng.combat_time:.3f} "
                f"php={eng._p.curHealth:.1f} ohp={eng._o.curHealth:.1f} ticks={eng._ticks}"
            )

    tot_n, tot_mis = 0, 0
    for fn in ["gd_core_test/oracle_align_cases.json", "gd_core_test/expand_align_cases.json"]:
        n, m, _, _ = check_dataset(ROOT / fn, args.limit, args.threads)
        tot_n += n
        tot_mis += m

    print(f"TOTAL: checked={tot_n}, mismatches={tot_mis}")
    return 1 if tot_mis else 0


if __name__ == "__main__":
    raise SystemExit(main())
