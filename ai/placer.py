# -*- coding: utf-8 -*-
"""placer.py — 代理模型引导的摆盘搜索（占位保持式重排）

语义基线（第二轮复核的结论，逐条遵守）
====================================
* 实录阵容是**扁平化导出**：原始布局本身允许重叠，引擎（GDCoreEngine）对
  输入阵容**全量装配**、对重叠容忍——装配结果与游戏真值对齐
  （simulator/gd_core_engine.py:_build_side 逐一装配 backpack.items 顶层；
  simulator/lineup.py:98 roots = 无显式 `in` 的全部条目；引擎侧重叠格在
  CoreGrid.addItem 里按键覆盖、不报错）。重叠是引擎容忍的合法输入，
  不是需要修复的错误。
* 因此 placer **不做任何成员关系推断、不做任何降级**：输入阵容的每件物品
  都必须出现在输出里（含每件的 id 与宝石）；显式 `in` 承载关系原样保留。
  旧版「非重叠装包 / 根物品降级进袋 / 占格超 63 报错退出」的口径整体作废。

动作空间（结构保持式重排）
========================
① 初始解 = 原布局（启动时先实测引擎装配基线，见「探针落点」）。
② 主动作 = 物品在『占位』之间的形状匹配置换：原布局每个物品的占格轮廓
  （该物品当前旋转角的 collision 绝对格，引擎逐字口径）视为一个占位；候选
  动作在同一**形状类**（占位形状的旋转封闭等价类，如 1×1 / 1×2 / 2×2 / L 形）
  内挑 2–3 件物品做循环置换，每件物品落到另一件物品的占位上，且必须取
  「collision 与目标占位**逐格完全一致**」的旋转角——可用旋转匹配形状（同类
  1×2 的横/竖占位经 90° 互换）。置换是双射 ⇒ 占位多重集逐格不变 ⇒ 总占格
  集合与重叠结构（每格被几件物品占、被哪些形状的占位覆盖）严格不变。
③ 副动作 = 宝石重挂：全局宝石多重集守恒；**只限根物品**之间——引擎不装配
  袋内物品（`in` 条目），其宝石在引擎侧不存在，若允许把参战根物品的宝石挂
  到袋内件上，等于静默抽掉参战宝石且装配探针无法发现（宝石不计入装配数）。
  宝石只能落到 descr.sockets 尚有空位的根物品上（含两件之间互换）。
  另有原位换向动作：collision 逐格不变的旋转（1×1 任意角、2×2 转 90°/180°
  等）——占格不变、影响格变，代理分可感知。

硬性规则（逐条可测）
==================
* 候选的物品多重集（含每件的 id）与输入严格一致——不丢弃、不新增、不降级；
* 总占格集合不变：候选的占位多重集与输入逐格一致（等价于每格被占次数一致）；
* 宝石全局多重集守恒，且只落在带空 socket 的根物品上；
* 候选必须通过引擎装配探针：用 GDCoreEngine 实际装配候选与原阵容，
  len(player_items) 必须相等，不等（或装配抛错）即拒绝该候选。

探针落点（设计取舍，如实说明）
============================
探针 = GDCoreEngine 全量构造（装配 + startBattle，实测 ~40ms/次）。模拟退火
每步生成一批候选（--batch，默认 48）做代理批量打分；**探针落在两道闸**：
(a) 接受闸——每步按代理分选出的最优候选必须过探针，才可能被接受为当前
    状态或进入候选池；
(b) 输出闸——top-k 候选输出前逐一重过探针，失败即报错退出（绝不输出）。
批内落选候选既不进入状态轨迹也不进入输出，不做探针——对每步全部 48 个
候选逐个探针会把运行时间放大约 50 倍，而动作空间在结构上已保证装配数
不变，探针是对引擎侧意外行为（如某摆位触发 startBattle 异常）的兜底闸，
不是对动作空间的重复校验。
启动时先实测**原阵容**的装配基线；原阵容装配失败（实测 25 组实录中 17 组
至少一侧含 GoldCounter/Icon/Time Pendant 等不可装配物品，装配抛 _MissingItem）
则 placer 报错退出——按本语义 placer 不跳过、不降级任何物品，无法建立基线
即无法工作，绝不静默绕过。

搜索
====
模拟退火（温度几何衰减 T0=0.03 → T1=0.0015，胜率尺度）：每步生成 --batch 个
邻域候选 → 代理模型 batch 推理打分（对称推理 π(p,o)=½(π(p,o)+1−π(o,p))，
与 ai/train.py evaluate 同口径，对手阵容固定）→ 取最优过探针 → 退火准则
接受。候选池按编码级内容哈希去重，先取代理胜率 top-k 的互异摆盘。

引擎在环（第四轮的教训：代理分在真值阵容上会饱和到 0.94+ 而引擎实测只有
0.0–0.6，只按代理分交付等于在盲区爬坡）
==================================================================
最终交付前，对代理分 top-k 候选与原阵容各用 --verify-seeds（默认 10）个
seed 实测引擎胜率（seed 列表 = 101, 102, …，与 ai/eval.py 默认同基，候选与
原阵容同 seed 配对；每局模拟前调 ai/kernel_reset.reset_kernel_state()，内核
修复后此调用幂等安全），**按引擎实测胜率对候选重排为最终 top-k 顺序**
（同分按代理分；实测报错的候选排最后、engine_winrate=null）。stdout 每个候选
一行 `CAND <rank> <proxyWinRate> <engineWinRate>`，另有一行
`BASE <engineWinRate>` 报告原阵容同 seed 实测胜率（配对对照基线）。
随后输出 top-k 摆盘 JSON 到 stdout 与 ai/placer_out.json，含每个候选的
代理胜率与引擎实测胜率。

用法
====
    python ai/placer.py --lineup <Player.json> --opponent <Opponent.json>
                        [--weights ai/weights.pt] [--topk 5] [--iters 500]
                        [--verify-seeds 10]
    stdout = 每候选一行 CAND … + BASE 行 + 一份 JSON（meta + candidates），
    同时写 ai/placer_out.json。进度/告警走 stderr；探针/实测期间引擎的
    零星 print 被重定向，不会污染 stdout。
"""
from __future__ import annotations

import argparse
import contextlib
import io
import json
import math
import os
import random
import sys
import time
from collections import Counter
from typing import Dict, List, Optional, Tuple

import numpy as np

_REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _REPO not in sys.path:
    sys.path.insert(0, _REPO)

from ai import model as M                                        # noqa: E402
from ai.encoding import (ROWS, COLS, ROTATIONS, _entry_geometry,                 # noqa: E402
                         _flatten as enc_flatten, _items_map, encode_lineup,
                         normalize_cells, rotate_cell)

DEFAULT_WEIGHTS = os.path.join(_REPO, "ai", "weights.pt")
DEFAULT_OUT = os.path.join(_REPO, "ai", "placer_out.json")
DEFAULT_TE_DATASET = os.path.join(_REPO, "data", "dataset_v1.jsonl")

# 退火温度（胜率尺度，几何衰减）
T0, T1 = 0.03, 0.0015
# 动作混合：形状置换 / 原位换向 / 宝石重挂（有宝石可动时）
P_SHAPE, P_REROT, P_GEM = 0.66, 0.09, 0.25
# 引擎在环实测的 seed 基值（列表 = BASE+i；与 ai/eval.py --seed 默认同基）
VERIFY_SEED_BASE = 101


# ─────────────────────────── 物品几何（引擎逐字口径） ───────────────────────────

class Geo:
    """(id, 旋转角) → collision 原始偏移（锚点系 (x,y)，与引擎 _place_of 逐字
    一致：绝对占格 = (row + y, col + x)），外加形状类键与旋转匹配索引。

    * raw_shape 用物品库 rot 表的原始数据（引擎不归一化，这里也不归一化）；
    * shape_class 是占位形状的旋转封闭等价类键（占位分组用）——**可行性判定
      仍以 raw 逐格相等为准**（rots_matching），类键只是快速分组索引；
    * 库外 id 兜底 1×1（对齐 ai/encoding._entry_geometry 的兜底；这类阵容在
      装配基线探针就会失败退出，实际到不了搜索）。
    """

    def __init__(self, item_db: dict):
        im = _items_map(item_db)
        self._raw: Dict[Tuple[str, int], Tuple[Tuple[int, int], ...]] = {}
        self.sockets: Dict[str, int] = {}
        self._canon: Dict[Tuple[Tuple[int, int], ...], tuple] = {}
        for key, entry in im.items():
            for idx in range(4):
                coll, _aff = _entry_geometry(entry, idx)
                self._raw[(key, idx)] = tuple(sorted((int(x), int(y)) for x, y in coll)) \
                    or ((0, 0),)
            descr = entry.get("descr") or {}
            try:
                self.sockets[key] = int(descr.get("sockets", 0) or 0)
            except (TypeError, ValueError):
                self.sockets[key] = 0

    def raw_shape(self, key: str, rot: int) -> Tuple[Tuple[int, int], ...]:
        return self._raw.get((key, int(rot) % 360 // 90), ((0, 0),))

    def cells(self, key: str, rot: int, row: int, col: int) -> frozenset:
        """绝对占格（引擎逐字口径：(row + y, col + x)，见 gd_core_engine._place_of）。"""
        return frozenset((int(row) + y, int(col) + x)
                         for (x, y) in self.raw_shape(key, rot))

    def shape_class(self, raw: Tuple[Tuple[int, int], ...]) -> tuple:
        """占位形状的旋转封闭等价类键（旋转 4 角归一化后取字典序最小）。"""
        hit = self._canon.get(raw)
        if hit is None:
            hit = min(tuple(normalize_cells([rotate_cell(c, rho * 90) for c in raw]))
                      for rho in range(4))
            self._canon[raw] = hit
        return hit

    def rots_matching(self, key: str, raw: Tuple[Tuple[int, int], ...]) -> List[int]:
        """该物品 collision 与 raw 逐格完全一致的旋转角列表（占位分配的可行域）。"""
        return [r for r in ROTATIONS if self.raw_shape(key, r) == raw]


# ─────────────────────────── 搜索状态 ───────────────────────────
# entries = enc_flatten(输入阵容)（顺序 = 输出顺序；parent 只来自显式 `in`）。
# State 按同一顺序描述每件物品：
#   pos:  [[row, col, rot], ...]
#   gems: [tuple(gem_id, ...), ...]
# 成员关系（parent）不在 State 里——原样保留，不可搜索改动。

State = dict


def copy_state(st: State) -> State:
    return {"pos": [list(p) for p in st["pos"]],
            "gems": [tuple(g) for g in st["gems"]]}


def snapshot_state(st: State) -> State:
    return {"pos": [tuple(p) for p in st["pos"]],
            "gems": [tuple(g) for g in st["gems"]]}


def occupancy_multiset(entries: List[dict], st: State, geo: Geo) -> Counter:
    """占位多重集：每件物品的绝对占格集 → Counter（总占格集合不变式的口径）。"""
    return Counter(geo.cells(e["id"], st["pos"][i][2], st["pos"][i][0], st["pos"][i][1])
                   for i, e in enumerate(entries))


def invariant_violation(entries: List[dict], st: State, geo: Geo,
                        base_occ: Counter, base_gems: Counter) -> Optional[str]:
    """硬性规则逐条自检（候选闸 + 输出闸共用）。返回 None = 全部通过。"""
    got = occupancy_multiset(entries, st, geo)
    if got != base_occ:
        miss = base_occ - got
        extra = got - base_occ
        return "占位多重集漂移：缺 %s 多 %s" % (dict(list(miss.items())[:2]),
                                              dict(list(extra.items())[:2]))
    got_gems = Counter(g for gs in st["gems"] for g in gs)
    if got_gems != base_gems:
        return "宝石全局多重集漂移：缺 %s 多 %s" % (
            dict(base_gems - got_gems), dict(got_gems - base_gems))
    for i, e in enumerate(entries):
        cap = geo.sockets.get(e["id"], 0)
        if len(st["gems"][i]) > cap:
            return "宝石容量溢出：%s 镶 %d 颗 > socket %d" % (e["id"], len(st["gems"][i]), cap)
    return None


# ─────────────────────────── 邻域动作（全部结构保持） ───────────────────────────

def _move_shape(s2: State, entries: List[dict], geo: Geo, rng: random.Random) -> bool:
    """主动作：同形状类内 2–3 件物品循环置换（占位多重集逐格保持）。

    每件移动物品必须存在 collision 与目标占位逐格一致的旋转角（可用旋转匹配
    形状）；先行全量可行性检查再落子，保证原子性（不可行整步放弃）。
    """
    groups: Dict[tuple, List[int]] = {}
    for i, e in enumerate(entries):
        r, c, rot = s2["pos"][i]
        groups.setdefault(geo.shape_class(geo.raw_shape(e["id"], rot)), []).append(i)
    multi = [g for g in groups.values() if len(g) >= 2]
    if not multi:
        return False
    g = rng.choice(multi)
    k = 3 if len(g) >= 3 and rng.random() < 0.3 else 2
    pick = rng.sample(g, k)
    snap = {i: tuple(s2["pos"][i]) for i in pick}
    perm = list(pick)
    rng.shuffle(perm)
    if all(perm[i] == pick[i] for i in range(k)):      # 恒等置换 → 强制交换前两件
        perm[0], perm[1] = perm[1], perm[0]
    plan = []
    for i in range(k):
        mover, target = perm[i], pick[i]
        if mover == target:
            continue
        tr, tc, trot = snap[target]
        raw_t = geo.raw_shape(entries[target]["id"], trot)
        rots = geo.rots_matching(entries[mover]["id"], raw_t)
        if not rots:
            return False
        plan.append((mover, tr, tc, rng.choice(rots)))
    for mover, tr, tc, rot in plan:
        s2["pos"][mover] = [tr, tc, rot]
    return True


def _move_rerot(s2: State, entries: List[dict], geo: Geo, rng: random.Random) -> bool:
    """原位换向：collision 逐格不变的旋转（占格不变、影响格变）。"""
    i = rng.randrange(len(entries))
    rot = s2["pos"][i][2]
    raw = geo.raw_shape(entries[i]["id"], rot)
    alts = [r for r in ROTATIONS if r != rot and geo.raw_shape(entries[i]["id"], r) == raw]
    if not alts:
        return False
    s2["pos"][i][2] = rng.choice(alts)
    return True


def _move_gems(s2: State, entries: List[dict], geo: Geo, rng: random.Random,
               root_idx: List[int]) -> bool:
    """副动作：宝石在根物品之间重挂（全局多重集守恒、只落有空 socket 的根物品）。

    移挂 = 从持有者卸下一颗装到有空位的另一根物品；互换 = 两持有者交换一颗
    （各自数量不变，容量自动守恒）。宝石多重集在两种动作下都严格守恒。
    """
    holders = [i for i in root_idx if s2["gems"][i]]
    if not holders:
        return False
    free = [i for i in root_idx if len(s2["gems"][i]) < geo.sockets.get(entries[i]["id"], 0)]
    moveable = [i for i in free]                        # 移挂目标 = 有空位的根物品
    src = rng.choice(holders)
    moveable = [i for i in moveable if i != src]
    if moveable and (len(holders) < 2 or rng.random() < 0.6):
        dst = rng.choice(moveable)                      # 移挂
        gi = rng.randrange(len(s2["gems"][src]))
        gem = s2["gems"][src][gi]
        s2["gems"][src] = s2["gems"][src][:gi] + s2["gems"][src][gi + 1:]
        s2["gems"][dst] = s2["gems"][dst] + (gem,)
        return True
    if len(holders) < 2:
        return False
    a, b = rng.sample(holders, 2)                       # 互换（各自数量不变，容量守恒）
    ga, gb = s2["gems"][a], s2["gems"][b]
    ia, ib = rng.randrange(len(ga)), rng.randrange(len(gb))
    s2["gems"][a] = ga[:ia] + (gb[ib],) + ga[ia + 1:]
    s2["gems"][b] = gb[:ib] + (ga[ia],) + gb[ib + 1:]
    return True


def mutate_state(entries: List[dict], st: State, geo: Geo, rng: random.Random,
                 root_idx: List[int]) -> Optional[State]:
    """随机产生一个邻域候选。动作空间结构性守恒（多重集/占位/宝石不变），
    不可行动作按主选→兜底链尝试，全不可行返回 None。"""
    s2 = copy_state(st)
    holders = [i for i in root_idx if s2["gems"][i]]
    free = [i for i in root_idx
            if len(s2["gems"][i]) < geo.sockets.get(entries[i]["id"], 0)]
    gem_ok = bool(holders) and (len(holders) >= 2 or
                                any(i not in holders for i in free))
    # 主选动作按权重抽签；不可行时沿兜底链再试其余动作
    p_gem = P_GEM if gem_ok else 0.0
    p_rerot = P_REROT + (P_GEM * 0.4 if not gem_ok else 0.0)
    r = rng.random()
    if r < p_gem:
        order = ("gem", "shape", "rerot")
    elif r < p_gem + p_rerot:
        order = ("rerot", "shape", "gem")
    else:
        order = ("shape", "rerot", "gem")
    for kind in order:
        if kind == "gem" and not gem_ok:
            continue
        if kind == "gem":
            ok = _move_gems(s2, entries, geo, rng, root_idx)
        elif kind == "rerot":
            ok = _move_rerot(s2, entries, geo, rng)
        else:
            ok = _move_shape(s2, entries, geo, rng)
        if ok:
            return s2
    return None


# ─────────────────────────── 状态 → v4 阵容 ───────────────────────────

def state_to_lineup(st: State, entries: List[dict], base: dict, name: str) -> dict:
    """状态 → v4 阵容 dict。物品按输入平铺序输出（每件都在：不丢弃、不降级）；
    显式 `in` 承载关系原样保留（顺序不变 ⇒ 下标仍有效）；成员关系永不改写。"""
    items: List[dict] = []
    for i, e in enumerate(entries):
        r, c, rot = st["pos"][i]
        item = {"id": e["id"], "at": [int(r), int(c)], "r": int(rot) % 360}
        if e["parent"] is not None:
            item["in"] = int(e["parent"])
        if st["gems"][i]:
            item["gems"] = list(st["gems"][i])
        items.append(item)
    out = {"version": 4, "name": name, "character": base.get("character"),
           "round": base.get("round", 1),
           "grid": list(base.get("grid") or [ROWS, COLS]),
           "items": items}
    for k in ("class_modifiers", "health_override", "storage"):
        if base.get(k) is not None:
            out[k] = base[k]
    return out


# ─────────────────────────── 引擎装配探针 ───────────────────────────

def to_v3(player_v4: dict) -> dict:
    """v4 阵容 dict → 引擎内部 v3 形状（与 load_lineup 同一条规范化路径；
    v3 内部形状原样透传）。"""
    from simulator import lineup as L
    if int(player_v4.get("version") or 0) >= 4:
        p3 = L._normalize_v4(player_v4, "<placer>")
        L._validate(p3, "<placer>")
        return p3
    return player_v4


def engine_probe(player_v4: dict, opp_v3: dict) -> Tuple[Optional[int], str]:
    """GDCoreEngine 全量构造探针：返回 (len(player_items), 错误串)。

    装配数 = 引擎实际装配的玩家侧物品数（宝石不计件）。构造走与真值对照
    同一条代码路径（_normalize_v4 → _validate → GDCoreEngine）；构造前调
    ai/kernel_reset.reset_kernel_state() 清内核进程级全局态（与 ai/eval.py
    的 engine_assembly 同口径），引擎内部的零星 print（如 setGem 超容量的
    "ohnonononononno"）被重定向，不污染 stdout。"""
    from simulator.gd_core_engine import GDCoreEngine
    from ai.kernel_reset import reset_kernel_state
    buf = io.StringIO()
    try:
        with contextlib.redirect_stdout(buf):
            reset_kernel_state()
            eng = GDCoreEngine(to_v3(player_v4), opp_v3, {}, {}, seed=0)
            return len(eng.player_items), ""
    except Exception as exc:                             # noqa: BLE001
        return None, "%s: %s" % (type(exc).__name__, exc)


def engine_winrate(player_v3: dict, opp_v3: dict, seeds: List[int]
                   ) -> Tuple[Optional[float], int, str]:
    """引擎在环：逐 seed 实跑一局，返回 (胜率或 None, 实跑局数, 错误串)。

    * 每局模拟前调 ai/kernel_reset.reset_kernel_state()（内核修复后幂等安全）；
    * seed 列表对候选与原阵容相同 → 同 seed 配对，可直接对照；
    * 任一 seed 实跑报错 → 胜率记 None + 错误串（部分 seed 的胜率不可信，
      不拿残缺测量参与排序）；引擎零星 print 重定向，不污染 stdout。"""
    from simulator.gd_core_engine import GDCoreEngine
    from ai.kernel_reset import reset_kernel_state
    wins = ran = 0
    for seed in seeds:
        buf = io.StringIO()
        try:
            with contextlib.redirect_stdout(buf):
                reset_kernel_state()
                eng = GDCoreEngine(player_v3, opp_v3, {}, {}, seed=int(seed))
                eng.run()
                win = bool(eng.player_wins())
            wins += 1 if win else 0
            ran += 1
        except Exception as exc:                         # noqa: BLE001
            return None, ran, "%s: %s（seed=%d）" % (type(exc).__name__, exc, seed)
    return ((wins / ran) if ran else None), ran, ""


# ─────────────────────────── 代理模型打分 ───────────────────────────

def compute_te(dataset_path: str, item_db: dict, vocab_index: Dict[str, int],
               seed: int, val_frac: float, smoothing: float
               ) -> Tuple[Optional[np.ndarray], Dict[str, float], Optional[str]]:
    """复刻 ai/train.py 的物品强度目标编码（s̃ = 平滑 P(胜|物品在玩家阵容) − prior）。

    返回 (s_tilde[len(vocab)] 或 None, te_by_name, 备注)。只在玩家侧阵容统计。
    s̃ 必须与训练期逐位一致（模型对强度通道取值敏感）——直接委托 train 的
    canonical 实现 compute_item_te。"""
    try:
        from ai.train import load_pairs, compute_item_te, TE_TEST_FRAC
        pairs = load_pairs(dataset_path)
        if len(pairs) < 10:
            return None, {}, "TE 数据太少（%d 行），强度通道置零" % len(pairs)
        s_tilde, te_by_name = compute_item_te(
            pairs, item_db, vocab_index, seed, val_frac, TE_TEST_FRAC, smoothing)
        return s_tilde, te_by_name, None
    except FileNotFoundError:
        return None, {}, "TE 数据集缺失（%s），强度通道置零" % dataset_path
    except Exception as exc:                             # noqa: BLE001
        return None, {}, "TE 计算失败（%s: %s），强度通道置零" % (type(exc).__name__, exc)


class Scorer:
    """候选阵容 → 代理胜率（batch 推理，对手固定，对称推理）。"""

    def __init__(self, model, device, item_db: dict, vocab_index: Dict[str, int],
                 opp_lineup: dict, s_tilde: Optional[np.ndarray],
                 te_by_name: Dict[str, float]):
        import torch
        self.torch = torch
        self.model = model
        self.device = device
        self.db = item_db
        self.vi = vocab_index
        self.s_tilde = s_tilde
        self.te_by_name = te_by_name
        t, _key = self.tensors(opp_lineup)
        self.opp_t = {k: torch.from_numpy(np.ascontiguousarray(v)).to(device)
                      for k, v in t.items()}

    def tensors(self, lineup: dict) -> Tuple[Dict[str, np.ndarray], str]:
        """阵容 → (张量组, 编码级键)。编码级键 = 模型全部输入的摘要——不同摆法
        若编码逐位相同（对模型不可见）据此去重。"""
        import hashlib
        enc = encode_lineup(lineup, self.db)
        t = M.lineup_tensors(enc, self.vi, lineup, self.db)
        if self.s_tilde is not None:
            t["strength"] = self.s_tilde[t["items"]][None]
        else:
            t["strength"] = np.zeros((1, ROWS, COLS), dtype=np.float32)
        t["scalars"][M.SCALAR_DIM - 1] = float(
            sum(self.te_by_name.get(n, 0.0) for n in enc["root_ids"]))
        h = hashlib.sha1()
        for k in sorted(t):
            h.update(k.encode())
            h.update(np.ascontiguousarray(t[k]).tobytes())
        return t, h.hexdigest()

    def score(self, lineups: List[dict]) -> Tuple[np.ndarray, List[str]]:
        torch = self.torch
        ts, keys = [], []
        for lu in lineups:
            t, key = self.tensors(lu)
            ts.append(t)
            keys.append(key)
        B = len(ts)
        p = {k: torch.stack([torch.from_numpy(np.ascontiguousarray(t[k])) for t in ts]
                            ).to(self.device) for k in ts[0]}
        o = {k: v.unsqueeze(0).expand(B, *v.shape) for k, v in self.opp_t.items()}
        with torch.no_grad():
            pr = 0.5 * (self.model(p, o) + (1.0 - self.model(o, p)))
        return pr.float().cpu().numpy(), keys


# ─────────────────────────── 主流程 ───────────────────────────

def parse_args(argv=None):
    ap = argparse.ArgumentParser(description="代理模型引导的摆盘搜索（占位保持式重排）")
    ap.add_argument("--lineup", required=True, help="待重摆的 v4 玩家阵容 JSON")
    ap.add_argument("--opponent", required=True, help="对手阵容 JSON（打分时固定）")
    ap.add_argument("--weights", default=DEFAULT_WEIGHTS, help="代理模型权重（默认 ai/weights.pt）")
    ap.add_argument("--topk", type=int, default=5, help="输出候选数（默认 5）")
    ap.add_argument("--iters", type=int, default=500, help="模拟退火迭代数（默认 500）")
    ap.add_argument("--batch", type=int, default=48, help="每步批量候选数（默认 48）")
    ap.add_argument("--verify-seeds", type=int, default=10,
                    help="引擎在环：top-k 候选与原阵容各实测的 seed 数（默认 10；0=关闭，"
                         "此时按代理分排序、engine_winrate=null）")
    ap.add_argument("--seed", type=int, default=42, help="随机种子（默认 42）")
    ap.add_argument("--device", choices=("auto", "cuda", "cpu"), default="auto")
    ap.add_argument("--out", default=DEFAULT_OUT, help="结果 JSON 路径（默认 ai/placer_out.json）")
    ap.add_argument("--te-dataset", default=DEFAULT_TE_DATASET,
                    help="物品强度目标编码用的数据集（默认 data/dataset_v1.jsonl）")
    ap.add_argument("--te-smoothing", type=float, default=20.0,
                    help="目标编码平滑伪计数（与 ai/train.py 默认一致）")
    ap.add_argument("--no-te", action="store_true", help="关闭物品强度通道（置零）")
    return ap.parse_args(argv)


def main(argv=None) -> int:
    import torch
    args = parse_args(argv)
    t0 = time.time()

    def log(msg: str):
        print(msg, file=sys.stderr)

    rng = random.Random(args.seed)

    # ── 数据 ──
    with open(args.lineup, encoding="utf-8") as f:
        base_lineup = json.load(f)
    with open(args.opponent, encoding="utf-8") as f:
        opp_lineup = json.load(f)
    item_db = M.load_item_db()
    vocab = M.build_item_vocab(item_db)
    vocab_index = {n: i for i, n in enumerate(vocab)}
    geo = Geo(item_db)

    if tuple(base_lineup.get("grid") or (ROWS, COLS)) != (ROWS, COLS):
        log("⚠ 输入 grid=%s ≠ %dx%d：占格口径按引擎实测（重叠容忍、无边界裁剪）"
            % (base_lineup.get("grid"), ROWS, COLS))

    # ── 物品清单（不做成员关系推断：parent 只来自显式 in；每件物品都保留） ──
    entries = enc_flatten(base_lineup)
    if not entries:
        raise SystemExit("阵容没有物品")
    root_idx = [i for i, e in enumerate(entries) if e["parent"] is None]
    n_bag = len(entries) - len(root_idx)

    # ── 引擎装配基线（先于模型加载；失败即退出——不跳过、不降级） ──
    from simulator.lineup import load_lineup
    opp_v3 = load_lineup(args.opponent)
    base_n, base_err = engine_probe(base_lineup, opp_v3)
    if base_n is None:
        raise SystemExit(
            "原阵容引擎装配失败（%s）——按本语义 placer 不跳过、不降级任何物品"
            "（输入每件物品都必须出现在输出里），无法建立装配基线即无法工作。" % base_err)
    if n_bag:
        log("引擎装配基线：原阵容装配 %d 件（玩家侧；另 %d 件显式 in 袋内件引擎不装配）"
            % (base_n, n_bag))
    else:
        log("引擎装配基线：原阵容装配 %d 件（玩家侧）" % base_n)

    # ── 初始解 = 原布局 ──
    st = {"pos": [[e["row"], e["col"], e["rotation"]] for e in entries],
          "gems": [tuple(e["gems"]) for e in entries]}
    base_occ = occupancy_multiset(entries, st, geo)
    base_gems = Counter(g for e in entries for g in e["gems"])
    inv = invariant_violation(entries, st, geo, base_occ, base_gems)
    assert inv is None, "初始解不变式破坏（BUG）：%s" % inv
    log("初始解 = 原布局（物品 %d 件全部保留，占位多重集 %d 种 / 每格最多被 %d 件覆盖）"
        % (len(entries), len(base_occ), max(base_occ.values())))

    # ── 代理模型 ──
    device = torch.device("cuda" if (args.device == "auto" and torch.cuda.is_available())
                          else (args.device if args.device != "auto" else "cpu"))
    ck = torch.load(args.weights, map_location="cpu", weights_only=False)
    cfg = ck.get("config") or {}
    if cfg.get("n_items") not in (None, len(vocab)):
        raise SystemExit("权重词表不匹配：weights n_items=%s，物品库 vocab=%d"
                         % (cfg.get("n_items"), len(vocab)))
    model = M.WinRateModel(n_items=len(vocab), n_blocks=int(cfg.get("res_blocks", 2)),
                           inter_blocks=int(cfg.get("inter_blocks", 0)),
                           emb_dim=int(cfg.get("emb_dim", M.EMB_DIM)),
                           tower_ch=int(cfg.get("tower_ch", M.TOWER_CH)))
    model.load_state_dict(ck["state_dict"])
    model.eval().to(device)
    log("device=%s  weights=%s" % (device, args.weights))

    if args.no_te:
        s_tilde, te_by_name, te_note = None, {}, "TE 已关闭（--no-te），强度通道置零"
    else:
        s_tilde, te_by_name, te_note = compute_te(
            args.te_dataset, item_db, vocab_index, int(cfg.get("seed", 42)),
            0.1, args.te_smoothing)
    if te_note:
        log("⚠ " + te_note)
    scorer = Scorer(model, device, item_db, vocab_index, opp_lineup, s_tilde, te_by_name)

    # ── 模拟退火（结构保持动作 + 批量代理打分 + 接受闸探针） ──
    cur = copy_state(st)
    cur_lu = state_to_lineup(cur, entries, base_lineup, "cur")
    cur_score = float(scorer.score([cur_lu])[0][0])
    log("初始解 代理胜率=%.4f" % cur_score)

    pool: Dict[str, Tuple[float, State]] = {
        scorer.tensors(cur_lu)[1]: (cur_score, snapshot_state(cur))}
    n_eval = 1
    n_probe_reject = 0
    n_inv_skip = 0
    for it in range(args.iters):
        cands, lineups = [], []
        for _ in range(args.batch * 2):
            if len(cands) >= args.batch:
                break
            s2 = mutate_state(entries, cur, geo, rng, root_idx)
            if s2 is None:
                continue
            viol = invariant_violation(entries, s2, geo, base_occ, base_gems)
            if viol is not None:                        # 结构性 BUG 才会到这；跳过并计数
                n_inv_skip += 1
                continue
            cands.append(s2)
            lineups.append(state_to_lineup(s2, entries, base_lineup, "cand"))
        if not cands:
            continue
        scores, enc_keys = scorer.score(lineups)
        n_eval += len(cands)
        bi = int(np.argmax(scores))
        best_v, best_s = float(scores[bi]), cands[bi]
        best_lu = lineups[bi]
        # 接受闸：探针不过的候选绝不接受、绝不入池
        n, err = engine_probe(best_lu, opp_v3)
        if n != base_n:
            n_probe_reject += 1
            if n_probe_reject <= 3:
                log("⚠ 候选被装配探针拒绝（装配 %s ≠ 基线 %d）%s"
                    % (n, base_n, ("——%s" % err) if err else ""))
            continue
        k = enc_keys[bi]
        if k not in pool or best_v > pool[k][0]:
            pool[k] = (best_v, snapshot_state(best_s))
        T = T0 * (T1 / T0) ** (it / max(args.iters - 1, 1))
        if best_v >= cur_score or rng.random() < math.exp((best_v - cur_score) / max(T, 1e-9)):
            cur, cur_score = copy_state(best_s), best_v
        if (it + 1) % max(args.iters // 10, 1) == 0:
            log("iter %4d/%d  cur=%.4f  T=%.4f  池=%d  探针拒绝=%d"
                % (it + 1, args.iters, cur_score, T, len(pool), n_probe_reject))

    # ── top-k 初选（输出闸：不变式 + 探针双闸，失败即报错退出，绝不输出违规候选） ──
    topk = sorted(pool.items(), key=lambda kv: -kv[1][0])[:max(args.topk, 1)]
    base_name = base_lineup.get("name") or os.path.splitext(os.path.basename(args.lineup))[0]
    proxy_cands: List[dict] = []
    for pi, (_key, (v, snap)) in enumerate(topk, 1):
        s2 = {"pos": [list(p) for p in snap["pos"]],
              "gems": [tuple(g) for g in snap["gems"]]}
        inv = invariant_violation(entries, s2, geo, base_occ, base_gems)
        if inv:
            raise SystemExit("候选 #%d %s（BUG，拒绝输出）" % (pi, inv))
        lu = state_to_lineup(s2, entries, base_lineup, "%s · 重摆 #%d" % (base_name, pi))
        n, err = engine_probe(lu, opp_v3)
        if n != base_n:
            raise SystemExit("候选 #%d 装配探针失败（装配 %s ≠ 基线 %d）%s——拒绝输出"
                             % (pi, n, base_n, ("——%s" % err) if err else ""))
        proxy_cands.append({"proxy_winrate": float(v), "lineup": lu, "probe_n": n})

    # ── 引擎在环：代理 top-k 候选与原阵容各 --verify-seeds 个 seed 实测引擎胜率 ──
    #    （每局模拟前 reset_kernel_state；同 seed 配对；基线跑不起来即拒绝输出）
    seeds = [VERIFY_SEED_BASE + i for i in range(max(args.verify_seeds, 0))]
    base_wr: Optional[float] = None
    if seeds:
        log("引擎在环：%d 个候选 + 原阵容各实测 %d seeds（%d..%d，同 seed 配对）…"
            % (len(proxy_cands), len(seeds), seeds[0], seeds[-1]))
        base_wr, base_ran, base_err = engine_winrate(to_v3(base_lineup), opp_v3, seeds)
        if base_wr is None:
            raise SystemExit("原阵容引擎实测失败（%s）——无法建立引擎在环基线，拒绝输出。"
                             % base_err)
        log("原阵容引擎实测胜率 %.4f（%d seeds）" % (base_wr, base_ran))
        for ci, c in enumerate(proxy_cands, 1):
            wr, ran, err = engine_winrate(to_v3(c["lineup"]), opp_v3, seeds)
            c["engine_winrate"], c["engine_error"] = wr, err
            log("代理序 #%d 候选 引擎实测胜率 %s（%d seeds）%s"
                % (ci, "n/a" if wr is None else "%.4f" % wr, ran,
                   ("⚠ %s" % err) if err else ""))
    else:
        for c in proxy_cands:
            c["engine_winrate"], c["engine_error"] = None, ""

    # 按引擎实测胜率重排为最终 top-k 顺序（None 最后；同分按代理分，稳定序）
    order = sorted(range(len(proxy_cands)),
                   key=lambda i: (proxy_cands[i]["engine_winrate"] is None,
                                  -(proxy_cands[i]["engine_winrate"] or 0.0),
                                  -proxy_cands[i]["proxy_winrate"]))
    candidates = []
    for rank, i in enumerate(order, 1):
        c = proxy_cands[i]
        c["lineup"]["name"] = "%s · 重摆 #%d" % (base_name, rank)
        candidates.append({"rank": rank,
                           "proxy_winrate": round(c["proxy_winrate"], 6),
                           "engine_winrate": (None if c["engine_winrate"] is None
                                              else round(c["engine_winrate"], 6)),
                           "n_items": len(entries), "n_gems": int(base_gems.total()),
                           "assembled_items": c["probe_n"], "lineup": c["lineup"]})

    # stdout：每候选一行 CAND <rank> <proxyWinRate> <engineWinRate> + BASE 行（基线对照）
    for c in candidates:
        print("CAND %d %.4f %s" % (c["rank"], c["proxy_winrate"],
                                   "n/a" if c["engine_winrate"] is None
                                   else "%.4f" % c["engine_winrate"]))
    if base_wr is not None:
        print("BASE %.4f" % base_wr)

    result = {
        "meta": {
            "lineup": os.path.abspath(args.lineup),
            "opponent": os.path.abspath(args.opponent),
            "weights": os.path.abspath(args.weights),
            "iters": args.iters, "batch": args.batch, "seed": args.seed,
            "device": str(device), "scored_states": n_eval,
            "elapsed_s": round(time.time() - t0, 1),
            "items": len(entries), "root_items": len(root_idx),
            "bag_items_explicit_in": n_bag,
            "baseline_assembled": base_n,
            "verify_seeds": args.verify_seeds,
            "verify_seed_list": seeds,
            "baseline_engine_winrate": (None if base_wr is None
                                        else round(base_wr, 6)),
            "final_order": "候选按引擎实测胜率降序（实测报错者最后、engine_winrate="
                           "null；同分按代理分，稳定序）",
            "probe_rejects": n_probe_reject, "invariant_skips": n_inv_skip,
            "te": "on" if s_tilde is not None else "off",
            "hard_rules": "候选物品多重集（含每件 id）与输入严格一致（不丢弃、不降级、"
                          "不做成员关系推断，显式 in 原样保留）；总占格集合不变（占位"
                          "多重集逐格一致）；宝石全局多重集守恒且只落在带空 socket 的"
                          "根物品上；候选过引擎装配探针（GDCoreEngine 实测装配数 == "
                          "原阵容基线）",
            "probe_policy": "探针 = GDCoreEngine 全量构造（~40ms/次，构造前 "
                            "reset_kernel_state）；落在接受闸（每步最优候选）与输出闸"
                            "（top-k 逐一重过）两道闸；批内落选候选不进入轨迹/输出故"
                            "不探针",
            "verify_policy": "引擎在环：代理 top-k 候选与原阵容各 --verify-seeds 个 "
                             "seed 实跑 GDCoreEngine（每局前 reset_kernel_state，同 "
                             "seed 配对），按引擎实测胜率重排为最终 top-k；CAND 行="
                             "最终序，BASE 行=原阵容基线",
            "action_space": "① 初始解=原布局；② 主动作=同形状类占位间的循环置换"
                            "（collision 与目标占位逐格一致的旋转匹配，占位多重集保持）；"
                            "③ 副动作=根物品间宝石重挂（全局守恒）+ 原位换向"
                            "（collision 不变的旋转）",
        },
        "candidates": candidates,
    }
    text = json.dumps(result, ensure_ascii=False, indent=2)
    with open(args.out, "w", encoding="utf-8") as f:
        f.write(text + "\n")
    print(text)                     # stdout：CAND/BASE 行之后的 JSON（top-k 摆盘 + 双胜率）
    log("完成：%d 个候选 → %s（%.1fs，评分 %d 状态，探针拒绝 %d，引擎实测 %d seeds×%d 阵容）"
        % (len(candidates), args.out, time.time() - t0, n_eval, n_probe_reject,
           args.verify_seeds, len(candidates) + (1 if base_wr is not None else 0)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
