# -*- coding: utf-8 -*-
"""actions.py — 有效动作空间（规划 §7.2，取代旧 placer 的"形状类内置换"）

动作表（§7.2）：
  move_item    物品挪位   —— 改跨包数 + 拓扑邻接（中等连锁）
  move_bag     包挪位     —— 改形状匹配（强连锁）
  swap_items   两物品换位 —— 同 move_item 组合
  drop_item    减物品     —— 腾空间换拓扑（用户明确允许的可能性）
  add_item     加物品     —— 从闲置池捡回
  swap_bag     换包       —— 容器层+加成域+自身属性全变（极强连锁）
  add_bag / drop_bag —— 改容量（强连锁）

每个动作都产出 **完整布局候选**，由 layout_rules.check_layout 复核合法性——
两层强耦合（§2.4/§2.5），任何动作都可能连锁失效，所以一律"提议→复核"。
"""
from __future__ import annotations

import copy
import random
from typing import Dict, List, Optional, Sequence, Tuple

from trainer.layout_rules import ItemIndex, check_layout, COLS, ROWS, occ_of


def _entries_of(lineup: dict) -> List[dict]:
    """lineup v4 → 布局条目。`_idx` = 原 items 下标，供写回对位。"""
    out = []
    for i, it in enumerate(lineup["items"]):
        out.append({"id": it["id"], "rot": int(it.get("r", 0) or 0) % 360,
                    "row": it["at"][0], "col": it["at"][1], "_idx": i})
    return out


def _write_back(lineup: dict, entries: Sequence[dict]) -> dict:
    """布局条目 → lineup v4 items（按 _idx 对位，gems 等原字段保留；_idx=-1 = 新增）。

    ★ id 取自**条目**（e["id"]）而非原槽位——act_swap_bag_H 的 placed_in
    挂在被换出包的 _idx 上，验证时板上是新包，写回必须也写新包 id，
    否则形状与验证板不一致 → 非法板（BAG_OVERLAP/NO_CONTAINER，已实测）。"""
    by_idx = {}
    added = []
    for e in entries:
        if e["_idx"] < 0:
            added.append(e)
        else:
            by_idx[e["_idx"]] = e
    new_items = []
    for i, it in enumerate(lineup["items"]):
        e = by_idx.get(i)
        if e is None:
            continue  # 该物品被动作移除
        nit = {"id": e.get("id") or it["id"],
               "at": [e["row"], e["col"]], "r": e.get("rot", 0)}
        if it.get("gems"):
            nit["gems"] = it["gems"]
        new_items.append(nit)
    for e in added:
        new_items.append({"id": e["id"], "at": [e["row"], e["col"]], "r": e.get("rot", 0)})
    out = dict(lineup)
    out["items"] = new_items
    out.pop("_legal", None)
    return out


def legal(index: ItemIndex, entries: Sequence[dict]) -> bool:
    ok, _ = check_layout(index, entries)
    return ok


# ── 原子动作实现（全部返回新 lineup 或 None）──

def _find_spot(index: ItemIndex, entries, e: dict, rng,
               max_tries: int = 40) -> Optional[Tuple[int, int, int]]:
    """为条目 e 找一个合法的 (rot, row, col) 新位置（小位移优先）。"""
    others = [x for x in entries if x is not e]
    base_rot = e.get("rot", 0)
    for _ in range(max_tries):
        rot = base_rot if rng.random() < 0.7 else rng.choice([0, 90, 180, 270])
        dx = rng.randint(-3, 3)
        dy = rng.randint(-3, 3)
        if dx == 0 and dy == 0:
            continue
        cand = dict(e, rot=rot, row=e["row"] + dy, col=e["col"] + dx)
        if check_layout(index, others + [cand])[0]:
            return (rot, cand["row"], cand["col"])
    return None


def act_move_item(index, lineup, rng) -> Optional[dict]:
    ents = _entries_of(lineup)
    nonbags = [e for e in ents if not index.is_bag(e["id"])]
    if not nonbags:
        return None
    e = rng.choice(nonbags)
    spot = _find_spot(index, ents, e, rng)
    if spot is None:
        return None
    e2 = dict(e, rot=spot[0], row=spot[1], col=spot[2])
    return _write_back(lineup, [e2 if x is e else x for x in ents])


def act_move_bag(index, lineup, rng) -> Optional[dict]:
    ents = _entries_of(lineup)
    bags = [e for e in ents if index.is_bag(e["id"])]
    if not bags:
        return None
    e = rng.choice(bags)
    spot = _find_spot(index, ents, e, rng)
    if spot is None:
        return None
    e2 = dict(e, rot=spot[0], row=spot[1], col=spot[2])
    return _write_back(lineup, [e2 if x is e else x for x in ents])


def act_swap_items(index, lineup, rng) -> Optional[dict]:
    """两物品互换（尝试「换位带换向」与「换位保向」两种变体）。

    密铺棋盘（终盘常态）上单物品挪位基本无解，互换是主要的有效动作。
    """
    ents = _entries_of(lineup)
    nonbags = [e for e in ents if not index.is_bag(e["id"])]
    if len(nonbags) < 2:
        return None
    a, b = rng.sample(nonbags, 2)
    variants = [
        (b["row"], b["col"], b["rot"], a["row"], a["col"], a["rot"]),  # 带换向
        (b["row"], b["col"], a["rot"], a["row"], a["col"], b["rot"]),  # 保向
    ]
    for ar, ac, arot, br, bc, brot in variants:
        a2 = dict(a, row=ar, col=ac, rot=arot)
        b2 = dict(b, row=br, col=bc, rot=brot)
        new = [a2 if x is a else b2 if x is b else x for x in ents]
        if check_layout(index, new)[0]:
            return _write_back(lineup, new)
    return None


def act_rotate_item(index, lineup, rng) -> Optional[dict]:
    """原位旋转一件物品（若合法）。"""
    ents = _entries_of(lineup)
    cands = [e for e in ents if not index.is_bag(e["id"])] or ents
    rng.shuffle(cands)
    for e in cands[:10]:
        for rot in rng.sample([0, 90, 180, 270], 4):
            if rot == e["rot"]:
                continue
            cand = dict(e, rot=rot)
            new = [cand if x is e else x for x in ents]
            if check_layout(index, new)[0]:
                return _write_back(lineup, new)
    return None


def act_drop_item(index, lineup, rng) -> Optional[dict]:
    ents = _entries_of(lineup)
    nonbags = [e for e in ents if not index.is_bag(e["id"])]
    if not nonbags:
        return None
    victim = rng.choice(nonbags)
    new = [x for x in ents if x is not victim]
    return _write_back(lineup, new) if check_layout(index, new)[0] else None


def act_add_item(index, lineup, rng, bench: Sequence[str]) -> Optional[dict]:
    """从闲置池 bench 捡一件物品塞进空位。"""
    ents = _entries_of(lineup)
    names = list(bench)
    rng.shuffle(names)
    for name in names:
        if not index.has(name):
            continue
        for rot in rng.sample([0, 90, 180, 270], 4):
            for _ in range(30):
                row = rng.randrange(ROWS)
                col = rng.randrange(COLS)
                cand = {"id": name, "rot": rot, "row": row, "col": col, "_idx": -1}
                if check_layout(index, ents + [cand])[0]:
                    return _write_back(lineup, ents + [cand])
    return None


def act_swap_bag(index, lineup, rng, bench_bags: Sequence[str]) -> Optional[dict]:
    """换包：把一个包换成 bench 里的另一个包（同位放不进则试微移）。"""
    ents = _entries_of(lineup)
    bags = [e for e in ents if index.is_bag(e["id"])]
    if not bags:
        return None
    names = [n for n in bench_bags if index.has(n)]
    rng.shuffle(names)
    target = rng.choice(bags)
    for name in names[:6]:
        for rot in (0, 90, 180, 270):
            cand = dict(target, id=name, rot=rot)
            others = [x for x in ents if x is not target]
            if check_layout(index, others + [cand])[0]:
                return _write_back(lineup, others + [cand])
        # 微移兜底：±2 格
        for _ in range(20):
            cand = dict(target, id=name,
                        rot=rng.choice([0, 90, 180, 270]),
                        row=target["row"] + rng.randint(-2, 2),
                        col=target["col"] + rng.randint(-2, 2))
            others = [x for x in ents if x is not target]
            if check_layout(index, others + [cand])[0]:
                return _write_back(lineup, others + [cand])
    return None


def act_drop_bag(index, lineup, rng) -> Optional[dict]:
    ents = _entries_of(lineup)
    bags = [e for e in ents if index.is_bag(e["id"])]
    if not bags:
        return None
    victim = rng.choice(bags)
    keep = [x for x in ents if x is not victim]
    # 包没了，物品会浮空——只保留仍合法的物品（浮空者剔除）
    ok_items = []
    from trainer.layout_rules import occ_of as _occ
    bag_union = set()
    for x in keep:
        if index.is_bag(x["id"]):
            bag_union |= set(_occ(index, x))
    for x in keep:
        if index.is_bag(x["id"]):
            ok_items.append(x)
        elif all(c in bag_union for c in _occ(index, x)):
            ok_items.append(x)
    return _write_back(lineup, ok_items) if check_layout(index, ok_items)[0] else None


def act_cross_bag_swap(index, lineup, rng) -> Optional[dict]:
    """跨包交换：两个分属不同包的非包物品互换位置。

    密铺板上同名包内互换通常不改覆盖关系（战斗等价），跨包交换才改变
    加成指派（assign_bonuses）——这是搜索里「物品挪位」动作的有效形态。
    """
    ents = _entries_of(lineup)
    from trainer.layout_rules import occ_of as _occ
    bag_owner = {}
    for e in ents:
        if index.is_bag(e["id"]):
            for c in _occ(index, e):
                bag_owner[c] = e["_idx"]
    nonbags = [e for e in ents if not index.is_bag(e["id"])]
    if len(nonbags) < 2:
        return None
    # 按所属包分组
    from collections import defaultdict
    by_owner = defaultdict(list)
    for e in nonbags:
        o = bag_owner.get((_occ(index, e)[0]))
        if o is None:
            cells = _occ(index, e)
            o = bag_owner.get(cells[0], "none")
        by_owner[o].append(e)
    groups = [g for g in by_owner.values() if g]
    for _try in range(10):
        if len(groups) < 2:
            break
        ga, gb = rng.sample(groups, 2)
        if not ga or not gb:
            continue
        a, b = rng.choice(ga), rng.choice(gb)
        for keep_rot in (False, True):
            a2 = dict(a, row=b["row"], col=b["col"],
                      rot=b["rot"] if not keep_rot else a["rot"])
            b2 = dict(b, row=a["row"], col=a["col"],
                      rot=a["rot"] if not keep_rot else b["rot"])
            new = [a2 if x is a else b2 if x is b else x for x in ents]
            if check_layout(index, new)[0]:
                return _write_back(lineup, new)
        # 失败后把这对从候选里摘掉再试
        ga = [x for x in ga if x is not a]
        gb = [x for x in gb if x is not b]
        groups = [g for g in groups if len(g) > 0 and g is not ga and g is not gb]
        if ga:
            groups.append(ga)
        if gb:
            groups.append(gb)
    return None


def coverage_perturb(index: ItemIndex, lineup: dict, i: int) -> Optional[dict]:
    """CRN 探针专用扰动：保证改变解析指派（A/B 变化）的等强度扰动。"""
    from trainer.layout_rules import analytic_score
    rng = random.Random(888_000 + i)
    ents0 = _entries_of(lineup)
    s0 = analytic_score(index, [dict(e) for e in ents0])
    menu = [act_cross_bag_swap, act_swap_items, act_move_item, act_move_bag]
    for act in menu:
        for _ in range(10):
            out = act(index, lineup, rng)
            if out is None:
                continue
            s1 = analytic_score(index, [dict(e) for e in _entries_of(out)])
            if (s1["B"] != s0["B"]) or (s1["B_edges"] != s0["B_edges"]) or (s1["A"] != s0["A"]):
                return out
    return None


def act_composite(index, lineup, rng, n_moves: int = 3) -> Optional[dict]:
    """LNS-lite 复合动作：连续施加 n_moves 个成功的小动作（每步过合法性闸）。

    单步邻域效应（±0.02）与评估噪声同量级（P2 实测），复合动作把多处覆盖
    关系一起改，效应量更大、更可分辨——这是规划 §7.2「外层 LNS 大邻域」的
    轻量形态。
    """
    cur = lineup
    applied = 0
    for _ in range(n_moves * 3):
        if applied >= n_moves:
            break
        act = rng.choice([act_cross_bag_swap, act_swap_items, act_move_bag,
                          act_rotate_item, act_move_item])
        out = act(index, cur, rng)
        if out is not None:
            cur = out
            applied += 1
    return cur if applied > 0 and cur is not lineup else None


# ═══════════ H 注入与换包（规划 v3 §1.1/§7.3：子集选择 + 包集合动作消融） ═══════════

TAG_SINGULAR = 128   # ItemDescriptor.canOnlyExistOnce() = tags & Tag.Singular


def inject_extra_bags(index: ItemIndex, lineup: dict, rng, k: int = 3) -> dict:
    """向持有池 H 注入 k 个额外包（规划 §1.4 的压力放大器，量级见 §9.7 开放问题）。

    注入规则（文档化选择）：27 包里均匀抽，排除 Singular（tags&128，唯一件）
    与已在板上的 id；注入件进 ``lineup["_extra"]``（持有未上场，无位置）。
    """
    fielded_ids = {it["id"] for it in lineup["items"]}
    # ★ sorted：frozenset 迭代序随 PYTHONHASHSEED 变化，不排序则注入集合
    #   跨进程不可复现（实验配对性被破坏）
    pool = sorted(name for name in index.bag_set()
                  if not (index.descr(name)["tags"] & TAG_SINGULAR)
                  and name not in fielded_ids)
    rng.shuffle(pool)
    extras = [{"id": name} for name in pool[:k]]
    out = dict(lineup)
    out["_extra"] = extras
    return out


def act_swap_bag_H(index, lineup, rng) -> Optional[dict]:
    """换包（子集选择动作）：下场一个已摆包 B_out，上场一个持有包 B_in。

    连锁处理（贪婪修复）：B_out 移除后其容器格消失，物品占格失去包垫的
    自动下场，随后按占格数从大到小贪婪重摆（first-fit）；摆不回的物品
    留在"持有未上场"（从板上消失——这正是「少上几件换拓扑」的取舍形态）。
    ``lineup["_extra"]`` 同步换入换出。效应量应远大于单步（§7.3：容器层 +
    加成域 + 自身属性三样全变）。
    """
    extras = lineup.get("_extra") or []
    if not extras:
        return None
    ents = _entries_of(lineup)
    bags = [e for e in ents if index.is_bag(e["id"])]
    if not bags:
        return None
    e_out = rng.choice(bags)
    e_in_spec = rng.choice(extras)
    name_in = e_in_spec["id"]

    keep = [e for e in ents if e is not e_out]
    # B_out 下场后失去包垫的物品先下场
    from trainer.layout_rules import occ_of as _occ
    bag_union = set()
    for e in keep:
        if index.is_bag(e["id"]):
            bag_union |= set(_occ(index, e))
    survivors, dropped = [], []
    for e in keep:
        if index.is_bag(e["id"]) or all(c in bag_union for c in _occ(index, e)):
            survivors.append(e)
        else:
            dropped.append(e)

    # 放 B_in：优先 B_out 原锚位（4 朝向），再随机锚位
    placed_in = None
    anchors = [(e_out["row"], e_out["col"])] + [
        (rng.randrange(ROWS), rng.randrange(COLS)) for _ in range(24)]
    rots = rng.sample([0, 90, 180, 270], 4)
    for (r0, c0) in anchors:
        for rot in rots:
            cand = {"id": name_in, "rot": rot, "row": r0, "col": c0,
                    "_idx": e_out["_idx"]}
            if check_layout(index, survivors + [cand])[0]:
                placed_in = cand
                break
        if placed_in is not None:
            break
    if placed_in is None:
        return None
    board = survivors + [placed_in]

    # 贪婪重摆被挤掉的物品（占格数从大到小 first-fit）
    dropped.sort(key=lambda e: -len(_occ(index, e)))
    for e in dropped:
        fitted = None
        for _ in range(40):
            rot = rng.choice([0, 90, 180, 270])
            cand = dict(e, rot=rot, row=rng.randrange(ROWS), col=rng.randrange(COLS))
            if check_layout(index, board + [cand])[0]:
                fitted = cand
                break
        if fitted is not None:
            board.append(fitted)
        # 摆不回 → 留在持有未上场（从板上消失）

    out = _write_back(lineup, board)
    new_extras = [x for x in extras if x is not e_in_spec] + [{"id": e_out["id"]}]
    out["_extra"] = new_extras
    return out


# ── 扰动器（CRN 探针用：等强度小扰动，菜单式尝试保证密铺板上也能落地）──

PERTURB_MENU = [act_move_item, act_swap_items, act_rotate_item, act_move_bag]


def random_perturb(index: ItemIndex, lineup: dict, i: int) -> Optional[dict]:
    rng = random.Random(777_000 + i)
    order = PERTURB_MENU[i % len(PERTURB_MENU):] + PERTURB_MENU[:i % len(PERTURB_MENU)]
    for act in order:
        for _ in range(6):
            out = act(index, lineup, rng)
            if out is not None:
                return out
    return None


ACTIONS = {
    "move_item": act_move_item,
    "move_bag": act_move_bag,
    "swap_items": act_swap_items,
    "rotate_item": act_rotate_item,
    "drop_item": act_drop_item,
    "drop_bag": act_drop_bag,
}
