# -*- coding: utf-8 -*-
"""check_gd_py_items.py — Python 侧「517 件物品逐一上场」（与 GDScript 侧闸门 9 对等）

================ 为什么需要它 ================
闸门 9（`gd_core_test/ItemBattle.gd`）把 517 件物品逐一带上 GDScript 侧内核的场，
闸门 13/14 只跑 8 套阵容的 56 局。于是 **Python 侧（模拟器真正跑的那一份）
从未把全部物品过一遍** —— 后果是实测到的：19 件物品在模拟器里**一用就崩**，
而整条流水线全绿。

| 缺口 | 件数 | 表现 |
|---|---|---|
| `call_deferred` 未映射 | 10 处 / 8 件 | `NameError`（其中 2 件在入包当帧就抛） |
| `typeof` + `TYPE_VECTOR2` 未提供 | 12 件（棋类） | `NameError` |
| 变量名遮蔽基类方法 | 4 件 | `TypeError: 'float' object is not callable` |
| `tr` 未提供 | 3 件（描述文本） | `NameError` |
| `PCG32.randi` 缺失 | 1 件 | `AttributeError` |
| 装配期空值 | 1 件 | `AttributeError: 'NoneType'` |

★ 这 19 件**不是**「冷门物品」：其中就有 ChessMaster / Sloth / Wand of Dissonance。
  用户随手一用就撞上。

================ 判据 ================
  1. 装配面  每件都能实例化并装进背包（不得 `_MissingItem`）
  2. 运行面  整场跑完**零异常**（这是本闸门的主判据）
  3. 终止面  每场都在 tick 上限内自然收场，不靠 `timed_out` 兜底
  4. 观测面  至少存在非零时长的对局 —— 「0 场跑完」不得冒充「全部通过」

用法：
    python tools/check_gd_py_items.py              # 全量（517 件）
    python tools/check_gd_py_items.py --limit 50   # 快速迭代
    python tools/check_gd_py_items.py --only Sloth
"""
from __future__ import annotations

import io
import json
import os
import sys
import traceback

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

FIXTURE = os.path.join(ROOT, "gd_core_test", "item_battle_fixture.json")
SEED = 20260927
CHARACTER = "Adventurer"

from simulator.gd_core_engine import GDCoreEngine, _MissingItem  # noqa: E402


def make_lineup(entries):
    return {
        "version": 3,
        "meta": {"name": "item-probe"},
        "character": CHARACTER,
        "round": 1,
        "class_modifiers": {},
        "health_override": None,
        "backpack": {"grid": {"rows": 7, "cols": 10}, "items": entries},
        "storage": {"items": []},
    }


def main() -> int:
    limit = None
    only = None
    argv = sys.argv[1:]
    for i, a in enumerate(argv):
        if a == "--limit" and i + 1 < len(argv):
            limit = int(argv[i + 1])
        if a == "--only" and i + 1 < len(argv):
            only = argv[i + 1]

    if not os.path.exists(FIXTURE):
        print("缺少夹具 %s —— 先跑 tools/gen_lineup_fixture.py" % FIXTURE)
        return 2
    with io.open(FIXTURE, encoding="utf-8") as fh:
        fx = json.load(fh)
    keys = sorted(fx["items"])
    if only:
        keys = [k for k in keys if only.lower() in k.lower()]
    if limit:
        keys = keys[:limit]
    if not keys:
        print("被测清单为空 —— 无观测即无断言，判 FAIL")
        return 1

    empty = make_lineup([])
    crashes = []
    missing = []
    timed_out = []
    ended = 0
    total_time = 0.0

    for n, key in enumerate(keys, 1):
        lineup = make_lineup([{
            "id": key, "row": 0, "col": 0, "rotation": 0, "quantity": 1,
            "container": False, "contents": [], "gems": [],
        }])
        try:
            eng = GDCoreEngine(lineup, empty, {}, {}, seed=SEED)
            eng.run()
        except _MissingItem as e:
            missing.append((key, str(e)))
            continue
        except Exception as e:  # noqa: BLE001
            crashes.append((key, type(e).__name__, str(e), traceback.format_exc()))
            print("[CRASH] %s -> %s: %s" % (key, type(e).__name__, e))
            sys.stdout.flush()
            continue
        if getattr(eng, "timed_out", False):
            timed_out.append(key)
        else:
            ended += 1
        total_time += float(getattr(eng, "combat_time", 0.0) or 0.0)
        if n % 100 == 0:
            print("   ... %d/%d（CRASH %d）" % (n, len(keys), len(crashes)))
            sys.stdout.flush()

    print()
    print("被测 %d 件：自然收场 %d / 超时 %d / 装配失败 %d / 异常 %d"
          % (len(keys), ended, len(timed_out), len(missing), len(crashes)))
    if ended:
        print("平均对局时长 %.2fs（合计 %.1fs）" % (total_time / ended, total_time))

    fail = []
    if crashes:
        for key, tn, msg, _tb in crashes:
            print()
            print("[CRASH] %s" % key)
            print(_tb.rstrip())
        fail.append("运行期异常 %d 件：%s" % (len(crashes),
                                        ", ".join(k for k, *_ in crashes[:10])))
    if missing:
        for key, msg in missing[:10]:
            print("[MISSING] %s：%s" % (key, msg))
        fail.append("装配失败 %d 件" % len(missing))
    if timed_out:
        fail.append("超时未收场 %d 件：%s" % (len(timed_out), ", ".join(timed_out[:10])))
    if not ended:
        fail.append("一件都没有自然收场 —— 表笔没接上（无观测即无断言）")

    print()
    for r in fail:
        print("   ✗ " + r)
    print()
    print("GDRUN_ITEMS: %s（%d 件，异常 %d / 未转译 %d / 超时 %d）"
          % ("PASS" if not fail else "FAIL", len(keys), len(crashes),
             len(missing), len(timed_out)))
    return 0 if not fail else 1


if __name__ == "__main__":
    sys.exit(main())
