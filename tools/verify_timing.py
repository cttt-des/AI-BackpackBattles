# -*- coding: utf-8 -*-
"""verify_timing.py — 冷却/时序回归验证（对齐 Item.gd 时间语义）

背景：onready 的 typed_defaults（`_item.baseCooldownOverride = 0.0` 等）曾通过
__setattr__ 重定向清零引擎冷却状态，导致所有物品每物理帧触发（"冷却0.01s"）。
本文件固化时序不变量，防止回归。

源码真值（decompiled_full/Items/Item.gd）：
  _physics_process: triggerTime -= delta * getSpeed(); <=0 时 trigger()
  trigger():        iterationCooldown = adjustCooldown(); triggerTime += iterationCooldown
  preCombatStart:   iterationCooldown = adjustCooldown(); triggerTime = iterationCooldown
  getBaseCooldown() = baseCooldownOverride（初始 = descriptor.cd）

用法: python tools/verify_timing.py
"""
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

for _stream in (sys.stdout, sys.stderr):
    try:
        if hasattr(_stream, "reconfigure"):
            _stream.reconfigure(encoding="utf-8", errors="replace")
    except Exception:  # noqa: BLE001
        pass

from simulator.grid import GridInventory          # noqa: E402
from simulator.item import Item, engine_managed_attrs  # noqa: E402
from simulator.character import Character         # noqa: E402
from simulator.data import load_items             # noqa: E402
from collections import defaultdict as _defaultdict_t  # noqa: E402

DB = {}
DELTA = 1.0 / 60.0
FAILED = []


def check(name, ok, detail=""):
    print(f"  [{'PASS' if ok else 'FAIL'}] {name}  {detail}")
    if not ok:
        FAILED.append(name)


def make(key):
    inv = GridInventory(7, 10)
    ch = Character(0, "P", 9999, 99, 9.0)
    opp = Character(1, "O", 9999, 99, 9.0)
    ch.set_opponent(opp)
    opp.set_opponent(ch)
    it = Item(key, dict(DB[key]))
    it.character = ch
    it.set_grid_position(3, 3, 0, inventory=inv)
    return it, ch


def case_engine_state_not_clobbered():
    """构造 → prepare：引擎管理属性不得被 onready/默认值循环覆盖（防回归断言）。

    （pre_combat_start 合法定义 trigger_time/iteration_cooldown = cd，单独在
    weapon_cooldown_seconds 用例中验证。）
    """
    managed = engine_managed_attrs()
    allowed_diff = {
        "_behavior_executor", "_behavior_ready", "_affected_cache",
        "has_pre_deal_damage_early_effect", "has_pre_deal_damage_late_effect",
        "has_dealt_damage_effect", "damage_source",
    }
    probe_keys = [k for k in DB if DB[k].get("cd")][:120]
    bad = []
    for key in probe_keys:
        it, _ = make(key)
        before = {a: v for a, v in vars(it).items() if a in managed}
        it.prepare()
        after = {a: v for a, v in vars(it).items() if a in managed}
        for attr in before:
            if attr in allowed_diff:
                continue
            b = before[attr]
            a_ = after.get(attr)
            if b is None:
                continue                      # 惰性初始化字段（如 _behavior_executor）
            if isinstance(b, (dict, list, _defaultdict_t)) and not a_:
                continue                      # 空容器等价
            if isinstance(b, float) and isinstance(a_, float):
                same = (b == a_) or (b != b and a_ != a_)
            else:
                same = type(b) is type(a_) and b == a_
            if not same:
                bad.append((key, attr, b, a_))
    check("engine_state_not_clobbered", not bad,
          f"覆盖 {len(bad)} 处 {bad[:4]}" if bad else f"抽查 {len(probe_keys)} 物品无覆盖")


def case_weapon_cooldown_seconds():
    """cd=5 的物品：首帧不触发，t≈5.0 才触发第一次。"""
    key = next((k for k, v in DB.items()
                if abs((v.get("cd") or 0) - 5.0) < 1e-9
                and (v.get("grid") or {}).get("collision_cells")), None)
    if key is None:
        check("weapon_cooldown_seconds", True, "SKIP 无 cd=5 样本")
        return
    it, _ = make(key)
    it.prepare()
    it.pre_combat_start()
    ok_init = abs(it.base_cooldown_override - 5.0) < 1e-9 \
        and abs(it.trigger_time - 5.0) < 1e-9
    triggers = 0
    t_first = None
    t = 0.0
    for _ in range(int(6.0 / DELTA)):
        t += DELTA
        prev = it.trigger_time
        it.physics_tick(DELTA, t)
        if it.trigger_time > prev:      # trigger() 里 trigger_time += iteration_cooldown
            triggers += 1
            if t_first is None:
                t_first = t
            break
    ok = ok_init and triggers >= 1 and abs((t_first or 0) - 5.0) < 0.05
    check("weapon_cooldown_seconds", ok,
          f"base={it.base_cooldown_override} 首帧未触发={ok_init} "
          f"首次触发 t={t_first}（期望≈5.0）")


def case_crit_severity_preserved():
    """prepare 后 crit_severity 必须仍是 2.0（曾被 onready 写成 _Noop）。"""
    bad = []
    for key in list(DB)[:80]:
        if not DB[key].get("cd"):
            continue
        it, _ = make(key)
        it.prepare()
        if type(it.crit_severity).__name__ != "float" \
                or abs(it.crit_severity - 2.0) > 1e-9:
            bad.append((key, repr(it.crit_severity)))
    check("crit_severity_preserved", not bad, f"异常 {bad[:3]}" if bad else "抽查 80 物品")


def case_stamina_regen_per_frame():
    """体力恢复 = regen × delta 每物理帧（Character.gd _physics_process）。"""
    ch = Character(0, "P", 100, 99, 5.0)   # max_stamina=99, regen=5/s
    ch.prepare()
    ch.cur_stamina = 10.0                   # 先清空，避免满仓 clamp 掩盖恢复量
    ch.character_tick(DELTA)
    gained = ch.get_current_stamina() - 10.0
    ok = abs(gained - 5.0 * DELTA) < 1e-9
    check("stamina_regen_per_frame", ok, f"1帧恢复 {gained:.6f}（期望 {5.0*DELTA:.6f}）")


def case_battle_rage_frame_precise():
    """战怒 2.5s：每帧递减，t≈2.5 结束（等价 battleRageTimer）。"""
    ch = Character(0, "P", 100, 99, 9.0)
    opp = Character(1, "O", 100, 99, 9.0)
    ch.set_opponent(opp)
    opp.set_opponent(ch)
    ch.prepare()
    ended_at = None
    ended = []
    ch.connect_signal("battle_rage_ended", lambda ev: ended.append(True))
    ch.start_battle_rage(None, 2.5)
    t = 0.0
    for _ in range(int(4.0 / DELTA)):
        t += DELTA
        ch.character_tick(DELTA)
        if ended and ended_at is None:
            ended_at = t
        if ended_at is not None:
            break
    ok = ended_at is not None and abs(ended_at - 2.5) < 0.05
    check("battle_rage_frame_precise", ok, f"结束于 t={ended_at}（期望≈2.5）")


def main():
    global DB
    DB = load_items()
    print(f"物品库: {len(DB)}")
    print("=" * 70)
    case_engine_state_not_clobbered()
    case_weapon_cooldown_seconds()
    case_crit_severity_preserved()
    case_stamina_regen_per_frame()
    case_battle_rage_frame_precise()
    print("=" * 70)
    if FAILED:
        print(f"失败 {len(FAILED)}: {FAILED}")
        return 1
    print("全部通过")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
