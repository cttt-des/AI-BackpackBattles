# -*- coding: utf-8 -*-
"""Python 侧「517 件物品逐一上场」冒烟 —— 复现用户报的 TypeError。

背景：闸门 13/14 只跑 8 套阵容的 56 局；Python 侧从未把全部物品跑过一遍。
      闸门 9 有 GDScript 侧的对等物（ItemBattle.gd），Python 侧没有。

用法：
  python output/repro_allitems.py            # 全量
  python output/repro_allitems.py --limit 50
  python output/repro_allitems.py --only "Ace of Spades"
"""
import io
import json
import os
import sys
import traceback

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

FIXTURE = os.path.join(ROOT, "gd_core_test", "item_battle_fixture.json")

from simulator.gd_core_engine import GDCoreEngine, _MissingItem  # noqa: E402

CHAR = "Adventurer"


def make_lineup(items):
    return {
        "version": 3,
        "meta": {"name": "probe"},
        "character": CHAR,
        "round": 1,
        "class_modifiers": {},
        "health_override": None,
        "backpack": {"grid": {"rows": 7, "cols": 10}, "items": items},
        "storage": {"items": []},
    }


def main():
    limit = None
    only = None
    argv = sys.argv[1:]
    for i, a in enumerate(argv):
        if a == "--limit":
            limit = int(argv[i + 1])
        if a == "--only":
            only = argv[i + 1]

    with io.open(FIXTURE, encoding="utf-8") as fh:
        fx = json.load(fh)
    items = fx["items"]
    keys = sorted(items)
    if only:
        keys = [k for k in keys if only.lower() in k.lower()]
    if limit:
        keys = keys[:limit]

    empty = make_lineup([])
    bad = []
    crash = []
    n = 0
    for k in keys:
        n += 1
        lineup = make_lineup([
            {"id": k, "row": 0, "col": 0, "rotation": 0,
             "quantity": 1, "container": False, "contents": [], "gems": []}])
        try:
            eng = GDCoreEngine(lineup, empty, {}, {}, seed=20260927)
            eng.run()
        except _MissingItem as e:
            bad.append((k, "MISSING", str(e)))
        except Exception as e:  # noqa: BLE001
            tb = traceback.format_exc()
            crash.append((k, type(e).__name__, str(e), tb))
            print("[CRASH] %s -> %s: %s" % (k, type(e).__name__, e))
            print(tb)
        if n % 50 == 0:
            print("  ... %d/%d（CRASH %d）" % (n, len(keys), len(crash)))
            sys.stdout.flush()

    print()
    print("跑完 %d 件：CRASH %d 件 / 未转译 %d 件" % (len(keys), len(crash), len(bad)))
    if crash:
        print("崩溃清单：")
        for k, tn, msg, _tb in crash:
            print("  %-28s %s: %s" % (k, tn, msg))
    if bad:
        print("未转译清单（前 20）：")
        for k, _t, msg in bad[:20]:
            print("  %-28s %s" % (k, msg))
    return 1 if crash else 0


if __name__ == "__main__":
    sys.exit(main())
