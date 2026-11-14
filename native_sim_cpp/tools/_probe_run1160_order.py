# -*- coding: utf-8 -*-
"""run1160_r18 分叉定位探针：py 内核 + 现算终序（fresh）vs gd 腿留档终序（recorded）。

结论判读：
  fresh_order == recorded_order 且 ticks==1093 → 终序复刻无差，native 内核 bug；
  fresh_order != recorded_order 且 ticks==991（=native）→ 终序复刻在该场与真 Godot
  不一致（bundle 级问题，py 与 native 同样中招）。
"""
import contextlib
import io
import json
import os
import sys

ROOT = r"D:\文件资料\学习\自动背包AI"
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

from gd_core_py._rt import Vector2, _bind_battle, _shuffle  # noqa: E402
from simulator.gd_core_engine import kernel, runtime_data  # noqa: E402
from simulator.godot_order import sort_custom  # noqa: E402

_K = kernel()
_rt = runtime_data()
_case = next(c for c in json.load(open(os.path.join(ROOT, "gd_core_test", "oracle_align_cases.json"), encoding="utf-8"))["cases"]
             if c["case_id"] == "run1160_r18")

_DESCR_CACHE = {}


def _py_descr(ctx, key):
    if key not in _DESCR_CACHE:
        ds = _rt["items"][key]["descr"]
        _DESCR_CACHE[key] = _K["CoreItemData"]().fromDict(dict(ds))
    return ctx.item_book.register(_DESCR_CACHE[key])


def mk_chr(ctx, pid, lu):
    ch = _K["CoreCharacter"](ctx, pid)
    ch.characterClass = int(lu["class"])
    ch.setMaxHealth(float(lu["health"]))
    ch.setCurrentHealth(float(lu["health"]))
    ch.maxStamina = float(lu["stamina"])
    ch.baseMaxStamina = float(lu.get("base_max_stamina", lu["stamina"]))
    ch.baseStaminaRegen = float(lu["regen"])
    ch.staminaRegen = float(lu["regen"])
    ch.fillUpStamina()
    return ch


def mk_side(ctx, ch, lu, otype):
    out = []
    R = _K["_R"]
    CoreConst = _K["CoreConst"]
    for e in lu["items"]:
        if e.get("storage"):
            continue
        d = _py_descr(ctx, e["key"])
        it = R.C(e["script"])()
        if e.get("crafted") is not None:
            it.crafted_instance = bool(e["crafted"])
        it.setup(ctx, d, ch)
        n = int(_rt["items"][e["key"]].get("sockets", 0))
        for _ in range(n):
            it.gems.append(None)
        it.collisionCells = [Vector2(x, y) for x, y in e["collision"]]
        it.affectedTileCells = {int(k): [Vector2(x, y) for x, y in v]
                                for k, v in (e.get("affected") or {}).items()}
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
                gd = _py_descr(ctx, gk)
                git = R.C(_rt["items"][gk]["script"])()
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


def main():
    case = _case
    seed = int(case["seed"])
    with contextlib.redirect_stdout(io.StringIO()):
        ctx = _K["CoreContext"](seed, _K["CoreHooks"]())
        ctx.cur_round = int(case.get("round_id", 1))
        ctx.custom_health_multiplier = float(case.get("custom_health_multiplier", 100.0))
        ctx.label_rng_enabled = bool(case.get("label_rng", True))
        ctx.below_master = True          # 旧语料 np24 终谳约定
        ctx.deferred_flush_enabled = False
        ctx.eb_relay_mirrored = False
        ctx.class_resources = {int(_rt["classes"][ck]): dict(info)
                               for ck, info in _rt["characters"].items() if ck in _rt["classes"]}
        _bind_battle(seed)
        p = mk_chr(ctx, _K["CoreCharacter"].ID.PLAYER, case["player"])
        ctx.rng.rng.seed = seed
        ctx.player = p
        combat = _K["CoreCombat"](ctx)
        ctx.combat = combat
        p_it = mk_side(ctx, p, case["player"], _K["CoreConst"].Owner.PlayerInventory)
        o = mk_chr(ctx, _K["CoreCharacter"].ID.OPPONENT, case["opponent"])
        ctx.opponent = o
        combat.setup(p, o)
        o_it = mk_side(ctx, o, case["opponent"], _K["CoreConst"].Owner.Opponent)
        _bind_battle(seed)
        p_ord, o_ord = list(p_it), list(o_it)
        _shuffle(p_ord)
        sort_custom(p_ord, key=lambda item: -item.getTriggerPriority())
        _shuffle(o_ord)
        sort_custom(o_ord, key=lambda item: -item.getTriggerPriority())

        # 终序对拍（recorded = gd 腿 events.json 的 activation_order，真 Godot 复刻）
        gd = json.load(open(os.path.join(ROOT, "output", "oracle", "align", "gdcore",
                                         "run1160_r18", "events.json"), encoding="utf-8"))
        rec_p, rec_o = gd["activation_order"]["player"], gd["activation_order"]["opponent"]
        ip = {id(x): i for i, x in enumerate(p_it)}
        io_ = {id(x): i for i, x in enumerate(o_it)}
        fresh_p = [ip[x] for x in p_ord]
        fresh_o = [io_[x] for x in o_ord]
        same_p = fresh_p == rec_p
        same_o = fresh_o == rec_o
        diff_p = [i for i, (a, b) in enumerate(zip(fresh_p, rec_p)) if a != b]
        diff_o = [i for i, (a, b) in enumerate(zip(fresh_o, rec_o)) if a != b]

        combat.startBattle(p_ord, o_ord, True)
        ticks = 0
        while not combat.fight_ended and ticks < 20000:
            combat.physicsTick(_K["CoreContext"].PHYSICS_DELTA)
            ticks += 1
    w = combat.winner()
    print("fresh==recorded: player", same_p, "opponent", same_o)
    print("first diffs: p@", diff_p[:8], " o@", diff_o[:8])
    print("py-fresh ticks=", ticks, "winner=", "player" if (w is not None and w.playerId == 0) else "opponent",
          "php=", p.curHealth, "ohp=", o.curHealth)
    print("native was:      ticks=991 winner=opponent php=0.0 ohp=194.0")
    print("recorded was:    ticks=1093 winner=opponent php=0.0 ohp=111.0")
    if not (same_p and same_o):
        print("recorded player[:20]:", rec_p[:20])
        print("fresh    player[:20]:", fresh_p[:20])
        print("recorded opponent[:20]:", rec_o[:20])
        print("fresh    opponent[:20]:", fresh_o[:20])


if __name__ == "__main__":
    main()
