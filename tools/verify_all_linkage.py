# -*- coding: utf-8 -*-
"""verify_all_linkage.py — 全量逐物品联动运行时探针

对 battle_items.json 中每一个具备联动机制的物品逐一验证：
  1. 影响格非空（tscn Affected tile 或脚本 getAffectedCellsAfterRotate）；
  2. 自动配对一个能通过其 canAffect* 判定的邻居，摆进影响格，
     断言 getAffectedItems 真实选中它（不是恒空）；
  3. 袋内联动（canApplyEffect）：袋占格放入合规物品，
     断言 getAffectedItemsInside 选中它；
  4. 全背包联动（canAffect_global / 无影响格脚本联动）：
     prepare 生命周期 STRICT 模式下零失败；
  5. onPrepare / onAffectedItemAdded 生命周期零异常（STRICT failures 检查）。

探针完全数据驱动：邻居配对 = 对全库物品逐一调用被测物品的 can_affect 谓词，
找到第一个匹配者。找不到匹配邻居的物品显式 SKIP 并注明谓词特征，
不允许静默漏检。

用法：
  python tools/verify_all_linkage.py             # 全量跑
  python tools/verify_all_linkage.py -v          # 逐物品打印
  python tools/verify_all_linkage.py --item Twine
"""
from __future__ import annotations

import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from simulator.item import Item                      # noqa: E402
from simulator.character import Character            # noqa: E402
from simulator.grid import GridInventory             # noqa: E402
from simulator.data import load_items                # noqa: E402
from simulator import behavior as beh_mod            # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")

COLORS = {"primary": 0, "secondary": 2, "tertiary": 4, "lightning": 7}
GRID_KEY = {"primary": "affected_cells", "secondary": "affected_secondary",
            "tertiary": "affected_tertiary", "lightning": "affected_lightning"}
SCRIPT_KEY = {"primary": "getAffectedCellsAfterRotate_primary",
              "secondary": "getAffectedCellsAfterRotate_secondary"}
CAN_METHOD = {"primary": "canAffect", "secondary": "canAffect_secondary",
              "tertiary": "canAffect_tertiary", "lightning": "canAffect_lightning"}


def _mk_item(key: str, db) -> Item:
    it = Item(key, dict(db[key]))
    ch = Character(0, "P", 9999, 99.0, 9.0)
    opp = Character(1, "O", 9999, 99.0, 9.0)
    ch.set_opponent(opp)
    opp.set_opponent(ch)
    it.character = ch
    ch.set_items([it])
    return it


def _strict_failures(it: Item) -> dict:
    ex = getattr(it, "_behavior_executor", None)
    if ex is None:
        return {}
    return {(":".join(str(x) for x in k) if not isinstance(k, str) else k): v
            for k, v in (ex.failures or {}).items()}


def _light_ready(key: str, data: dict, it: Item) -> None:
    """候选物品的轻量初始化：引擎在真实背包中邻居都是就绪物品，
    其判定所需状态（棋子颜色/卡牌牌座/冷却基值）须先就位。
    只补字段不做全量 _run_item_ready（后者会重编译行为，太慢）。"""
    chain = ((data.get("behavior") or {}).get("extends_chain") or [])
    if "ChessPiece" in chain:
        # ChessPiece.gd _ready：节点名含 "White" → White，否则 Black
        it.pieceColor = 1 if "White" in key else 0
    if "Card" in chain:
        # Card.gd：牌座内的卡牌 deck 恒真值，chainPosition 未编号为 -1
        it.deck = True
        it.chainPosition = -1
    if getattr(it, "cd", None) is None:
        it.cd = float(data.get("cd", 0) or 0)


def find_neighbor(it: Item, color: int, db, errors: dict | None = None) -> str | None:
    """对全库物品逐一调用被测物品的 can_affect 谓词，返回第一个匹配者。

    errors: 可选 {键: 计数}，收集谓词抛出的异常类型（区分「真无匹配」与「谓词崩溃」）
    """
    from collections import Counter
    errs = Counter() if errors is not None else None
    for key in db:
        if key == it.key:
            continue
        if (db[key].get('category') == 'bag' or 'bag' in (db[key].get('types') or [])):
            continue   # 引擎真值：袋子占 bagCells，getAffectedItems 只查 filled 层，
                       # 袋子永远不会成为受影响者（Item.gd isItemAffected 排除 isBag）
        try:
            cand = _mk_item(key, db)
            _light_ready(key, db[key], cand)
        except Exception:  # noqa: BLE001
            continue
        try:
            if it.can_affect(cand, color):
                return key
        except Exception as e:  # noqa: BLE001
            if errs is not None:
                errs[f"{type(e).__name__}: {e}"] += 1
            continue
    if errors is not None and errs:
        errors.update(errs)
    return None


def find_inside_neighbor(bag: Item, db, errors: dict | None = None) -> str | None:
    from collections import Counter
    errs = Counter() if errors is not None else None
    for key in db:
        if key == bag.key:
            continue
        if (db[key].get('category') == 'bag' or 'bag' in (db[key].get('types') or [])):
            continue   # 袋中袋在背包格内不可摆放（canAddBag 查 bagCells）
        try:
            cand = _mk_item(key, db)
            _light_ready(key, db[key], cand)
        except Exception:  # noqa: BLE001
            continue
        try:
            if bag.can_apply_effect(cand):
                return key
        except Exception as e:  # noqa: BLE001
            if errs is not None:
                errs[f"{type(e).__name__}: {e}"] += 1
            continue
    if errors is not None and errs:
        errors.update(errs)
    return None


def _own_can(item_data: dict, m: str) -> bool:
    """物品是否真正覆写了判定谓词（自身 methods 或非 Item 祖先类）。

    Item.gd 基类的 canAffect* 恒 False 且已入 class_methods 池，
    has_behavior() 对所有物品都为真，不能作为「有联动谓词」的依据。
    """
    beh = item_data.get("behavior") or {}
    if m in (beh.get("methods") or {}):
        return True
    for inh in (item_data.get("linkage") or {}).get("inherited") or []:
        parts = str(inh).split("<-")
        if parts and parts[0] == m and len(parts) > 1 and parts[1] not in ("Item.gd",):
            return True
    return False


def _trivial_false_can(item_data: dict, m: str) -> bool:
    """自身覆写的判定谓词是否引擎真值恒 False（如 Spear.gd `canAffect → return False`，
    矛类只按 affectsEmpty 计空格，不选中任何物品）"""
    src = ((item_data.get("behavior") or {}).get("methods") or {}).get(m)
    if not src:
        return False
    import re as _re
    return _re.fullmatch(r'def\s+\w+\s*\([^)]*\)\s*:\s*(return\s+False\s*)+\n?', src) is not None


def probe_item(key: str, db, verbose=False) -> dict:
    """返回 {status: PASS/FAIL/SKIP, details: [..]}"""
    data = db[key]
    it = _mk_item(key, db)
    kinds = []
    for cname in COLORS:
        color = COLORS[cname]
        if it._affected_cells_abs(color) or _own_can(data, CAN_METHOD[cname]):
            kinds.append(cname)
    methods = ((data.get("behavior") or {}).get("methods") or {})
    lk = data.get("linkage") or {}
    if "canApplyEffect" in methods:
        kinds.append("inside")
    if "canAffect_global" in methods or "canAffect_global" in (lk.get("overrides") or []):
        kinds.append("global")
    if not kinds and "onPrepare" in methods:
        kinds.append("lifecycle")
    if not kinds:
        return {"status": "SKIP", "details": ["无联动机制"]}

    details, fails, skips = [], [], []
    rows = cols = 9
    # 物品摆在场中央（影响格/脚本影响格随 grid_row/col 平移）
    it.set_grid_position(4, 4, 0, inventory=None)
    it._run_item_ready()

    for cname in [k for k in kinds if k in COLORS]:
        color = COLORS[cname]
        cells = it._affected_cells_abs(color)
        can_m = CAN_METHOD[cname]
        has_can = _own_can(data, can_m)
        errors = {}
        if not cells and not has_can:
            fails.append(f"{cname}: 无影响格且无 {can_m}，联动不可能发生")
            continue
        # 判定谓词引擎真值恒 False（如 Spear/Long Spear 只做空格联动 affectsEmpty）
        if has_can and _trivial_false_can(data, can_m):
            if it.has_behavior("affectsEmpty") and it.affects_empty(color):
                details.append(f"{cname}: canAffect 恒 False（引擎真值），affectsEmpty=True 仅计空格")
            else:
                details.append(f"{cname}: canAffect 恒 False（引擎真值），无物品配对")
            continue
        if not cells and it.has_behavior("affectsEmpty") and it.affects_empty(color):
            # 棋子等：tscn 无 Affected tile，仅按空格/棋盘规则联动（ChessPiece.affectsEmpty）
            details.append(f"{cname}: 影响格为空 + affectsEmpty=True（仅空格联动，无物品配对）")
            continue
        # 物品本体入网（不占格——occupied_cells 不登记），placed=True 供
        # Card.canAffect 等按 placed 分支的谓词走战斗路径
        inv = GridInventory(rows, cols)
        it.grid_inventory = inv
        nb_key = find_neighbor(it, color, db, errors)
        if nb_key is None:
            if has_can:
                src = methods.get(can_m, "")
                gaps = [t for t in ("is_crafted", "is_class_item") if t in src]
                if gaps:
                    skips.append(f"{cname}: 全库无匹配 —— 数据缺口 {','.join(gaps)} 未入库（恒 False）")
                    continue
                msg = f"{cname}: 全库无物品通过 {can_m}（检查谓词是否过严/数据缺失）"
                if errors:
                    top = sorted(errors.items(), key=lambda kv: -kv[1])[:3]
                    msg += " 谓词异常: " + "; ".join(f"{k} x{n}" for k, n in top)
                fails.append(msg)
            else:
                details.append(f"{cname}: 影响格 {len(cells)} 格（无覆写谓词，无邻居可配）")
            continue
        nb = _mk_item(nb_key, db)
        nb._run_item_ready()
        shape = list(nb.occupied_cells) or [(0, 0)]   # 无 grid 数据的物品按 1x1 兜底
        placed = False
        for (r0, c0) in cells:
            for (lr, lc) in shape:
                top = (r0 - lr, c0 - lc)
                abs_cells = {(top[0] + a, top[1] + b) for (a, b) in shape}
                if all(0 <= r < rows and 0 <= c < cols for r, c in abs_cells) \
                        and not (abs_cells & (set(inv.filled) | set(inv.bags))):
                    nb.set_grid_position(top[0], top[1], 0, inventory=inv)
                    placed = True
                    break
            if placed:
                break
        if not placed:
            fails.append(f"{cname}: 邻居 {nb_key} 在 9x9 内摆不进影响格（格子越界/形状异常）")
            continue
        try:
            it.prepare()
        except Exception as e:  # noqa: BLE001
            fails.append(f"{cname}: prepare 异常 {type(e).__name__}: {e}")
            continue
        if has_can:
            affected = it.get_affected_items(color)
            if nb not in affected:
                fails.append(f"{cname}: 邻居 {nb_key} 未被选中（影响格={len(cells)}格, "
                             f"getAffectedItems={[a.key for a in affected]}）")
            else:
                details.append(f"{cname}: 邻居 {nb_key} 被选中（影响格 {len(cells)} 格）")
        else:
            details.append(f"{cname}: 影响格 {len(cells)} 格（判定谓词在基类，跳过选中断言）")
        sf = _strict_failures(it)
        if sf:
            fails.append(f"{cname}: STRICT 失败 {json.dumps(sf, ensure_ascii=False)[:200]}")

    if "inside" in kinds:
        # canApplyEffect 引擎真值恒 False（如 Leather Bag：普通包无袋内特效，
        # 场景直接挂 Bag.gd，回调也是基类空实现）→ 无需配对
        if _trivial_false_can(data, "canApplyEffect"):
            details.append("inside: canApplyEffect 恒 False（引擎真值），无袋内特效联动")
        else:
            bag = _mk_item(key, db)
            bag.set_grid_position(3, 3, 0, inventory=GridInventory(9, 9), is_bag=True)
            errors_in = {}
            nb_key = find_inside_neighbor(bag, db, errors_in)
            if nb_key is None:
                src_in = methods.get("canApplyEffect", "")
                gaps = [t for t in ("is_crafted", "is_class_item") if t in src_in]
                if gaps:
                    skips.append(f"inside: 全库无匹配 —— 数据缺口 {','.join(gaps)} 未入库（恒 False）")
                else:
                    msg = "inside: 全库无物品通过 canApplyEffect"
                    if errors_in:
                        top = sorted(errors_in.items(), key=lambda kv: -kv[1])[:3]
                        msg += " 谓词异常: " + "; ".join(f"{k} x{n}" for k, n in top)
                    fails.append(msg)
            else:
                nb = _mk_item(nb_key, db)
                nb.set_grid_position(bag.occupied_cells[0][0], bag.occupied_cells[0][1],
                                     0, inventory=bag.grid_inventory)
                try:
                    bag.prepare()
                except Exception as e:  # noqa: BLE001
                    fails.append(f"inside: prepare 异常 {type(e).__name__}: {e}")
                else:
                    inside_aff = bag.get_affected_items_inside()
                    if nb not in inside_aff:
                        fails.append(f"inside: 邻居 {nb_key} 未被选中（"
                                     f"袋内={[i.key for i in bag.get_items_inside()]}）")
                    else:
                        details.append(f"inside: 邻居 {nb_key} 被选中（袋内联动生效）")
                    sf = _strict_failures(bag)
                    if sf:
                        fails.append(f"inside: STRICT 失败 {json.dumps(sf, ensure_ascii=False)[:200]}")

    if "global" in kinds or "lifecycle" in kinds:
        it2 = _mk_item(key, db)
        it2.set_grid_position(4, 4, 0, inventory=GridInventory(9, 9))
        try:
            it2.prepare()
        except Exception as e:  # noqa: BLE001
            fails.append(f"lifecycle: prepare 异常 {type(e).__name__}: {e}")
        else:
            details.append("lifecycle: prepare 完成")
        sf = _strict_failures(it2)
        if sf:
            fails.append(f"lifecycle: STRICT 失败 {json.dumps(sf, ensure_ascii=False)[:200]}")

    status = "FAIL" if fails else ("SKIP" if skips else "PASS")
    return {"status": status, "details": details + fails + skips}


def main():
    args = [a for a in sys.argv[1:]]
    verbose = "-v" in args
    only = None
    if "--item" in args:
        only = args[args.index("--item") + 1]
    beh_mod.STRICT = True

    with open(DB_PATH, encoding="utf-8") as f:
        db = json.load(f)
    items = db["items"] if isinstance(db, dict) and "items" in db else db
    item_db = load_items()

    targets = [only] if only else sorted(items.keys())
    results = {}
    for key in targets:
        if key not in item_db:
            continue
        try:
            results[key] = probe_item(key, item_db, verbose)
        except Exception as e:  # noqa: BLE001
            results[key] = {"status": "FAIL",
                            "details": [f"probe 崩溃: {type(e).__name__}: {e}"]}
        if verbose or results[key]["status"] != "PASS":
            mark = {"PASS": "+", "FAIL": "x", "SKIP": "-"}[results[key]["status"]]
            print(f"[{mark}] {key}: {results[key]['status']}")
            for d in results[key]["details"]:
                print(f"      {d}")

    n_pass = sum(1 for r in results.values() if r["status"] == "PASS")
    n_fail = sum(1 for r in results.values() if r["status"] == "FAIL")
    n_skip = sum(1 for r in results.values() if r["status"] == "SKIP")
    print("=" * 60)
    print(f"联动探针：通过 {n_pass} / 失败 {n_fail} / 跳过 {n_skip}（共 {len(results)}）")
    if n_fail:
        print("失败清单：", ", ".join(k for k, r in results.items() if r["status"] == "FAIL"))
        sys.exit(1)
    # 跳过物品必须列出原因（不允许静默）
    for k, r in results.items():
        if r["status"] == "SKIP":
            print(f"[SKIP] {k}: {r['details']}")


if __name__ == "__main__":
    main()
