# -*- coding: utf-8 -*-
"""gen_dataset.py — 随机阵容采样（终盘规模） + 多进程对战数据集生成

做什么
======
1. 采样阵容（对齐真值分布）：真值终盘阵容根物品约占满 7×9 网格大半
   （2026-10-03 实测全部 50 个真值侧：根物品 36–64、中位 48；占格 49–63 格、
   占格率 78%–100%、中位 60/63；回合 50/50 全为 R19）、回合集中在 R19。
   随机侧按『占格预算』装填：从 assets/gd_core_runtime.json 的可装配物品池
   （可装配口径 = 引擎装配不抛 _MissingItem，即物品在 items 表且脚本已注册，
   见 simulator/gd_core_engine.py::_place_of/_make_item；实测 517 件全部注册，
   unplayable 清单 Coins 不在 items 表）按稀有度加权（有放回）抽物品，
   贪心合法摆放（占格不重叠、不越界、允许 4 向旋转），直到占格数达到预算
   （每套阵容随机抽 54–63 格，对齐"占满大半"）或连续放置失败（网格对剩余
   候选已满）。只采样根物品，不生成袋内物品；回合 15–19 加权偏向 19
   （ctx.cur_round 影响血量成长，见 gd_core_engine.py:600-604）。
   约 20% 的对手阵容直接取自 dist/output/combat_logs 真值实录池
   （剔除含不可装配物品的实录，如 GoldCounter）。
1b. 宝石采样（补上一轮缺口——真值实录双方共 187 颗宝石而数据集 gems 恒为
   空表）：约 50% 的随机阵容（GEM_PROB）从可装配宝石池（items 表中
   descr.types 含类型 13 的 34 件，职业位掩码过滤后按稀有度加权）随机抽
   宝石注入，使宝石通道与内容哈希的宝石变体切分真正生效。宝石数量按真值
   规模校准（TRUTH_GEM_COUNTS：75 个真值侧中 43 个带宝石侧的经验分布，
   1–12 颗/侧），在宿主物品 socket 容量内（runtime 资产顶层 sockets，引擎
   _make_item 建等长 gems 数组，gd_core_engine.py:680-681）随机落位——
   不装满全部 socket，否则终盘阵容会灌进 27–47 颗、比真值（0–12）高一个
   数量级，宝石通道照样外推。真值对手保留其自带宝石。
   ★ 例外：type-13 的宿主（宝石本身带 socket，如 Flawless Ruby）不装——
   内核对『格上宝石再嵌宝石』的装配链会崩（宿主 Gem.getItem() 返回 None，
   gd_core_py/gd_core_items/Gems/Gem.py:65-70 → getGemMode:88 抛
   AttributeError，2026-10-02 实测），且 25 组真值实录 143 件带宝石物品中
   宝石嵌宝石为 0 例，采样口径与之对齐。
2. 模拟：进程内直接构造 GDCoreEngine——引擎 __init__ 内部按原版次序完成
   setup → _readyInit → addItem → setGem → startBattle
   （simulator/gd_core_engine.py:606-616 与 _build_side:701-723），随后
   eng.run() 跑完一局。每对阵容跑 --seeds 局（每局独立随机 seed，注意
   seed 语义为内核 CoreRng 种子，None 会折成 0，见 gd_core_engine.py:562-569），
   记录玩家胜场数；multiprocessing.Pool 并行。每局构造前逐局重置内核进程级
   全局态（ai/kernel_reset.py——全局 Math RNG/实例 id 台账不清会让 wins 标签
   随 worker 进程历史漂移，同 (对, seed) 不复现）。
3. 输出 JSONL：每行 {"player": v4阵容, "opponent": v4阵容, "wins": n, "seeds": n}；
   阵容对按双方（物品 id + 行 + 列 + 旋转 + 宝石配置）的规范化序列化去重
   （宝石必须参与——真值对手阵容带 gems，随机侧为空表也写入签名）；
   启动时读取已有输出做断点续跑（去重键同口径，已存在的对不再重跑）。

旧数据隔离
==========
data/ 下各批产物分层归档（2026-10-03 本轮逐一实测核对行数/根物品数/宝石数）：
  * *.v0.jsonl —— 任务所指的旧分布（8–16 件）：dataset_v1.v0.jsonl 2500 对
    （根物品 8–56、均值 15.7）、pilot.v0.jsonl 100 对（8–55、均值 14.5）、
    gen_dataset.v0.jsonl —— 已在更早一轮改名让位。
  * *.v0b.jsonl —— 中间批（终盘规模但无随机侧宝石，宝石仅来自 20% 真值对手）：
    dataset_v1.v0b.jsonl 4000 对 / 宝石 2731 颗、pilot.v0b.jsonl、
    dataset_v3.v0b.jsonl 25 对。
  * *.v0c.jsonl —— 本轮（2026-10-03）改名让位的前几次尝试产物（终盘规模、已带
    随机侧宝石，但无法追溯其生成代码与本版是否同口径，一律不续用）：
    dataset_v1.v0c.jsonl 4944 对（根物品 32–61、宝石 22448 颗、52% 侧带宝石）、
    pilot.v0c.jsonl 100 对、dataset_v3.v0c.jsonl 24 对。
★ 后缀 *.v0 / *.v0b 已被上述更早批次占用，本轮改用 *.v0c（直接覆盖会毁掉
  更早的归档）。本版从零生成、默认输出 data/dataset_v3.jsonl，不与旧批混用。

用法
====
    python ai/gen_dataset.py --pairs 20 --out data/dataset_v3.jsonl --workers 6 --seeds 2
    python ai/gen_dataset.py --sample-check 20   # 只统计随机阵容规模 vs 真值，不模拟

耗时：终盘规模阵容单局耗时显著大于 0.24s/局的空背包基线，实测值见本文件
运行输出；总耗时 ≈ pairs × seeds × 单局耗时 / workers。
"""
from __future__ import annotations

import argparse
import glob
import hashlib
import json
import os
import random
import sys
import time
from typing import Any, Dict, List, Optional, Tuple

from multiprocessing import Pool

# 仓库根入 sys.path（脚本既可 `python ai/gen_dataset.py` 也可 -m 方式跑）
_REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _REPO not in sys.path:
    sys.path.insert(0, _REPO)

from simulator.gd_core_engine import GDCoreEngine  # noqa: E402  # _MissingItem 由池口径前置排除
from simulator.lineup import load_lineup, to_v4  # noqa: E402
from ai.kernel_reset import reset_kernel_state  # noqa: E402  # 逐局清内核进程级全局态

RUNTIME_PATH = os.path.join(_REPO, "assets", "gd_core_runtime.json")
COMBAT_LOGS_DIR = os.path.join(_REPO, "dist", "output", "combat_logs")

ROWS, COLS = 7, 9                    # 背包网格 7 行 × 9 列 = 63 格
TRUTH_RATIO = 0.2                    # 对手取自真值实录池的比例（约 20%）
# 占格预算域：真值 50 个侧实测占格 49–63 格（78%–100%、中位 60），
# "约占满大半" → 预算 54–63 格（86%–100% 占格率）。装填到预算即停
# （大件可轻微越预算，保证不摆到一半留大洞）。
MIN_BUDGET, MAX_BUDGET = 54, 63
# 稀有度 → 抽样权重（rarity 0..5，越稀有越难抽到；缺档回落 10）
RARITY_WEIGHTS = {0: 100, 1: 70, 2: 50, 3: 34, 4: 20, 5: 12}
# 占格数 → 追加尺寸因子（与稀有度权重相乘）。真值终盘 ~50 件根物品占满 63 格
# → 平均每件仅占 ~1.2 格（大量 1×1 填充件）；纯稀有度加权的期望占格 ~2.6 格/件，
# 根物品数只有真值一半（实测 25 vs 50–54），故对 1×1/1×2 小件加权、大件减权，
# 把期望占格拉到 ~1.2 格/件（系数由 assets/gd_core_runtime.json 全量分布数值调出）。
SIZE_FACTORS = {1: 12.0, 2: 2.5, 3: 1.0, 4: 0.7, 5: 0.4, 6: 0.3,
                7: 0.25, 8: 0.25, 9: 0.25}
SIZE_FACTOR_DEFAULT = 0.25         # 超大件（>9 格，池内无）回落值
# 连续放置失败上限：超过即认为网格对剩余候选已满（剩余洞格放不进任何候选）
MAX_MISS = 200
# 回合 15–19，加权偏向 19（真值实录全部为 R19；回合经 ctx.cur_round 影响血量）
ROUND_CHOICES = (15, 16, 17, 18, 19)
ROUND_WEIGHTS = (1, 1, 2, 3, 10)
# 宝石：descr.types 中的类型 id（Chipped Ruby/Flawless Ruby/Badger Rune…，
# assets/gd_core_runtime.json 实测 34 件）；GEM_PROB = 注入宝石的随机阵容占比
GEM_TYPE = 13
GEM_PROB = 0.5
# 带宝石阵容的宝石数预算：真值 50 个侧中 43 个带宝石侧的逐侧经验分布
# （2026-10-03 全量实测核对本表逐值一致：{1:6,2:9,3:7,4:3,5:6,6:3,7:2,8:2,
# 9:1,10:2,11:1,12:1}）。宝石注入量按此抽样并在
# 可用 socket 容量内随机落位——若把全部 socket 装满，终盘 ~50 件会灌进
# 27–47 颗，比真值高一个数量级，宝石通道反而外推（2026-10-02 --sample-check 实测）。
TRUTH_GEM_COUNTS = (1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3,
                    3, 3, 3, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 7, 7, 8, 8,
                    9, 10, 10, 11, 12)


# ═══════════════════════════ 物品池 ═══════════════════════════

def load_runtime() -> dict:
    with open(RUNTIME_PATH, encoding="utf-8") as f:
        return json.load(f)


def playable_pool(data: dict) -> Dict[str, dict]:
    """可装配物品池：items 表剔除 unplayable 清单。

    引擎装配抛 _MissingItem 的两种情况（gd_core_engine.py:527-529 与 674-675）：
    物品不在 items 表，或脚本未转译（R.is_registered 为假）。本仓库实测
    items 表 517 件脚本全部已注册、unplayable（Coins）本就不在 items 表，
    故 items − unplayable 即为精确池（2026-10-02 用 kernel()["_R"].is_registered
    全量核验）。
    """
    unplayable = set(data.get("unplayable") or [])
    return {k: e for k, e in (data.get("items") or {}).items()
            if k not in unplayable}


def lineup_ids(lineup: dict) -> List[str]:
    """阵容内全部物品 id（含袋内嵌套与宝石）——用于真值实录的可装配性过滤。"""
    ids: List[str] = []

    def walk(entries):
        for e in entries or []:
            ids.append(e.get("id"))
            for g in (e.get("gems") or []):
                ids.append(g.get("id") if isinstance(g, dict) else g)
            walk(e.get("contents") or [])

    walk((lineup.get("backpack") or {}).get("items") or [])
    return [i for i in ids if i]


def occupied_cells(data: dict, lineup: dict) -> set:
    """根物品占格集合（与引擎 _place_of 同一几何口径，gd_core_engine.py:530-540）。

    只算根物品（backpack.items 顶层）——袋内嵌套物品不参与战斗
    （gd_core_engine.py:_build_side 只装配 backpack/storage 顶层的 items）。
    """
    occ: set = set()
    for e in (lineup.get("backpack") or {}).get("items") or []:
        ent = (data.get("items") or {}).get(e.get("id"))
        if ent is None:
            continue
        rot = ent["rot"].get(str(int(e.get("rotation") or 0) % 360))
        if not rot or not rot.get("collision"):
            continue
        row, col = int(e.get("row") or 0), int(e.get("col") or 0)
        occ |= {(c[0] + col, c[1] + row) for c in rot["collision"]}
    return occ


# ═══════════════════════════ 随机采样与摆放 ═══════════════════════════

def is_gem(ent: dict) -> bool:
    """物品是否为宝石（descr.types 含类型 GEM_TYPE）。"""
    return GEM_TYPE in (ent["descr"].get("types") or [])


def class_gem_pool(pool: Dict[str, dict], class_id: int) -> Tuple[List[str], List[float]]:
    """某职业的可装配宝石池 + 稀有度权重（职业位掩码过滤，与物品同口径）。"""
    keys: List[str] = []
    weights: List[float] = []
    for key, ent in pool.items():
        if not is_gem(ent):
            continue
        mask = int(ent["descr"].get("classes") or 0)
        if mask != 0 and not (mask >> class_id) & 1:
            continue
        keys.append(key)
        weights.append(RARITY_WEIGHTS.get(int(ent["descr"].get("rarity") or 0), 10))
    return keys, weights


def _weighted_draw(rng: random.Random, keys: List[str], weights: List[float]) -> str:
    return keys[rng.choices(range(len(keys)), weights=weights, k=1)[0]]


def _legal_placements(ent: dict, occupied: set) -> List[Tuple[int, int, int, set]]:
    """枚举一件物品的全部合法摆位（占格不重叠、不越界、允许 4 向旋转）。

    几何口径与引擎一致（gd_core_engine.py:_place_of）：rot 表的 collision 为
    锚点系相对偏移（min 已归一化 (0,0)，c[0]=列偏移、c[1]=行偏移），摆位
    (row,col) 为旋转后占格左上角。返回 [(rot, row, col, cells), ...]。
    """
    out: List[Tuple[int, int, int, set]] = []
    for rot_key in ent["rot"].keys():
        anchor = ent["rot"][rot_key]["collision"]
        if not anchor:
            continue
        h = max(c[1] for c in anchor) + 1
        w = max(c[0] for c in anchor) + 1
        if h > ROWS or w > COLS:
            continue
        for row in range(ROWS - h + 1):
            for col in range(COLS - w + 1):
                cells = {(c[0] + col, c[1] + row) for c in anchor}
                if cells.isdisjoint(occupied):
                    out.append((int(rot_key), row, col, cells))
    return out


def make_lineup_v3(rng: random.Random, data: dict, pool: Dict[str, dict],
                   classes: dict, tag: str, *, with_gems: bool = True) -> dict:
    """按『占格预算』随机生成一套阵容（内部 v3 形状，引擎直接可装配）。

    装填：按稀有度加权（有放回）抽物品，每个候选枚举全部合法摆位随机取一；
    放不下（无合法摆位）记一次 miss，连续 MAX_MISS 次 miss 即认为网格对剩余
    候选已满。只生成根物品（不生成袋内物品），占格不重叠、不越界、允许旋转。
    with_gems=True 时以 GEM_PROB 概率为本套阵容按 socket 数注入随机宝石
    （见文件头 1b；type-13 宿主不装，内核不支持格上宝石嵌宝石）。
    """
    char = rng.choice(sorted(classes))
    class_id = int(classes[char])

    # 类兼容 + 稀有度权重的候选表（有放回抽——终盘阵容本就允许同名多件）
    keys: List[str] = []
    weights: List[float] = []
    for key, ent in pool.items():
        mask = int(ent["descr"].get("classes") or 0)
        # 位掩码语义（CoreItemData.classes）：0 = 无职业限制；否则第 class_id 位
        # 置 1 的职业可用（Ranger=0..Engineer=6，见运行时资产 classes 表）
        if mask != 0 and not (mask >> class_id) & 1:
            continue
        r0 = ent["rot"].get("0") or next(iter(ent["rot"].values()))
        cells_n = len(r0["collision"]) if r0["collision"] else 1
        keys.append(key)
        weights.append(
            RARITY_WEIGHTS.get(int(ent["descr"].get("rarity") or 0), 10)
            * SIZE_FACTORS.get(cells_n, SIZE_FACTOR_DEFAULT))
    if not keys:
        raise RuntimeError(f"职业 {char} 无可用物品")

    budget = rng.randint(MIN_BUDGET, MAX_BUDGET)
    occupied: set = set()
    items: List[dict] = []
    misses = 0
    while len(occupied) < budget and misses < MAX_MISS:
        key = _weighted_draw(rng, keys, weights)
        placed = _legal_placements(pool[key], occupied)
        if not placed:
            misses += 1
            continue
        rot, row, col, cells = rng.choice(placed)
        occupied |= cells
        misses = 0
        items.append({"id": key, "row": row, "col": col, "rotation": rot,
                      "quantity": 1, "container": False, "contents": [],
                      "gems": []})

    # ── 宝石注入：约 50% 的阵容按真值规模在 socket 容量内装入随机宝石（文件头 1b） ──
    if with_gems and rng.random() < GEM_PROB:
        gk, gw = class_gem_pool(pool, class_id)
        # 可落位的 (物品, socket 下标) 槽位；type-13 宿主不装（内核装配会崩，真值 0 例）
        slots = []
        for ii, it in enumerate(items):
            host = pool[it["id"]]
            if is_gem(host):
                continue
            for si in range(int(host.get("sockets") or 0)):
                slots.append((ii, si))
        rng.shuffle(slots)
        for ii, si in slots[:rng.choice(TRUTH_GEM_COUNTS)]:
            if gk:
                items[ii]["gems"].append({"id": _weighted_draw(rng, gk, gw)})

    return {
        "version": 3,
        "meta": {"name": tag, "source": "gen_dataset"},
        "character": char,
        "round": rng.choices(ROUND_CHOICES, weights=ROUND_WEIGHTS, k=1)[0],
        "class_modifiers": {},
        "health_override": None,
        "backpack": {"grid": {"rows": ROWS, "cols": COLS}, "items": items},
        "storage": [],
    }


# ═══════════════════════════ 真值实录池 ═══════════════════════════

def load_truth_pool(pool: Dict[str, dict]) -> List[dict]:
    """加载 dist/output/combat_logs 的双方阵容（v4 → 内部 v3）。

    剔除含任何不可装配物品（不在可装配池，如 GoldCounter）的实录——引擎
    装配会对它们抛 _MissingItem。袋内嵌套物品（v4 的 in）保留原样：引擎
    只装配背包根物品（gd_core_engine.py:_build_side:701-714）。
    """
    out: List[dict] = []
    skipped = 0
    paths = sorted(glob.glob(os.path.join(COMBAT_LOGS_DIR, "*", "*.Player.json"))) \
        + sorted(glob.glob(os.path.join(COMBAT_LOGS_DIR, "*", "*.Opponent.json")))
    for path in paths:
        try:
            lu = load_lineup(path)
        except Exception as exc:  # noqa: BLE001 —— 坏文件跳过
            print(f"⚠ 实录加载失败 {os.path.basename(path)}: {exc}", file=sys.stderr)
            skipped += 1
            continue
        if any(i not in pool for i in lineup_ids(lu)):
            skipped += 1
            continue
        out.append(lu)
    print(f"真值实录池：{len(out)} 套可用（剔除 {skipped} 套）", file=sys.stderr)
    return out


# ═══════════════════════════ 去重键（含宝石配置） ═══════════════════════════

def _side_sig(v4: dict) -> str:
    """单侧规范化签名：职业 + 回合 + 每件物品的 (id, 行, 列, 旋转, 宝石)。"""
    items = sorted(
        (it["id"], int(it["at"][0]), int(it["at"][1]), int(it.get("r", 0) or 0),
         tuple(sorted(str(g) for g in (it.get("gems") or []))))
        for it in v4.get("items") or [])
    return json.dumps([v4.get("character"), v4.get("round"), items],
                      ensure_ascii=False, separators=(",", ":"), default=list)


def pair_key(player_v4: dict, opponent_v4: dict) -> str:
    h = hashlib.sha1()
    h.update(_side_sig(player_v4).encode("utf-8"))
    h.update(b"||")
    h.update(_side_sig(opponent_v4).encode("utf-8"))
    return h.hexdigest()


# ═══════════════════════════ 对战（worker 侧） ═══════════════════════════

def run_pair(task: Tuple[int, dict, dict, int, int]) -> dict:
    """跑一对阵容的 seeds 局，返回 {player, opponent, wins, seeds}（v4 序列化）。

    每局在进程内直接构造 GDCoreEngine（其 __init__ 按原版次序完成
    setup → _readyInit → addItem → setGem → startBattle，见文件头注释），
    随后 eng.run() 跑完一局；每局独立 seed（内核 CoreRng 种子）。
    ★ 每局构造前 reset_kernel_state()：gd_core_py 的全局 Math RNG（裸
      arr.shuffle() 走它）与实例 id 台账是进程级、局间不重置的，不清的话
      同一局在 worker 进程里的结局随该进程此前跑过什么而漂移——
      wins 标签就不再是 (阵容, seed) 的确定函数（2026-10-03 修复）。
    任何装配/模拟异常（含 _MissingItem）都折成 {"error": ...} 回传——不让
    单对坏数据炸掉整个 imap_unordered 迭代。
    """
    idx, player_v3, opponent_v3, pair_seed, seeds = task
    try:
        rng = random.Random(pair_seed)
        wins = 0
        for _ in range(seeds):
            reset_kernel_state()
            eng = GDCoreEngine(player_v3, opponent_v3, {}, {},
                               seed=rng.randrange(1, 2 ** 31))
            eng.run()
            if eng.player_wins():
                wins += 1
    except Exception as exc:  # noqa: BLE001 —— 单对失败只记错，不拖垮整批
        return {"error": f"{type(exc).__name__}: {exc}"}
    return {"player": to_v4(player_v3), "opponent": to_v4(opponent_v3),
            "wins": wins, "seeds": seeds}


# ═══════════════════════════ 断点续跑 ═══════════════════════════

def existing_keys(out_path: str) -> set:
    """读取已有 jsonl，收集已完成阵容对的去重键（与采样去重同口径）。"""
    done: set = set()
    if not os.path.exists(out_path):
        return done
    with open(out_path, encoding="utf-8") as f:
        for ln, line in enumerate(f, 1):
            line = line.strip()
            if not line:
                continue
            try:
                rec = json.loads(line)
                done.add(pair_key(rec["player"], rec["opponent"]))
            except Exception as exc:  # noqa: BLE001
                print(f"⚠ {out_path}:{ln} 解析失败，忽略：{exc}", file=sys.stderr)
    return done


# ═══════════════════════════ 规模自检（--sample-check） ═══════════════════════════

def sample_check(n: int, seed: Optional[int]) -> int:
    """采样 n 套随机阵容，统计根物品数/占格率/宝石数并与真值实录对照（不模拟）。"""
    data = load_runtime()
    pool = playable_pool(data)
    classes = data.get("classes") or {}
    rng = random.Random(seed)
    truth_paths = sorted(glob.glob(os.path.join(
        COMBAT_LOGS_DIR, "*", "*.Player.json")))[:3]
    print(f"{'阵容':<28} {'根物品':>6} {'占格':>6} {'占格率':>7} {'宝石':>4} {'回合':>4}")
    rows = []
    for p in truth_paths:
        lu = load_lineup(p)
        occ = occupied_cells(data, lu)
        n_roots = len((lu.get("backpack") or {}).get("items") or [])
        n_gems = sum(len(e.get("gems") or []) for e in
                     (lu.get("backpack") or {}).get("items") or [])
        rows.append(("真值:" + os.path.basename(p)[:22], n_roots, len(occ),
                     n_gems, lu.get("round")))
    for i in range(n):
        lu = make_lineup_v3(rng, data, pool, classes, f"check_{i:03d}")
        occ = occupied_cells(data, lu)
        n_gems = sum(len(e["gems"]) for e in lu["backpack"]["items"])
        rows.append((f"随机:check_{i:03d}",
                     len(lu["backpack"]["items"]), len(occ), n_gems, lu["round"]))
    def _grp(prefix):
        return [r for r in rows if r[0].startswith(prefix)]
    t_rows, g_rows = _grp("真值"), _grp("随机")
    t_root = [r[1] for r in t_rows]; g_root = [r[1] for r in g_rows]
    t_occ = [r[2] for r in t_rows];  g_occ = [r[2] for r in g_rows]
    t_gem = [r[3] for r in t_rows];  g_gem = [r[3] for r in g_rows]
    for name, nr, oc, ng, rd in rows:
        print(f"{name:<28} {nr:>6} {oc:>6} {oc / (ROWS * COLS) * 100:>6.1f}% "
              f"{ng:>4} {rd:>4}")
    print(f"\n真值 {len(t_rows)} 份：根物品 {min(t_root)}–{max(t_root)}，"
          f"占格率 {min(t_occ) / 63 * 100:.0f}%–{max(t_occ) / 63 * 100:.0f}%，"
          f"宝石 {min(t_gem)}–{max(t_gem)}")
    n_with = sum(1 for g in g_gem if g)
    print(f"随机 {n} 份：根物品 {min(g_root)}–{max(g_root)}（均值 "
          f"{sum(g_root) / n:.1f}），占格率 {min(g_occ) / 63 * 100:.0f}%–"
          f"{max(g_occ) / 63 * 100:.0f}%（均值 {sum(g_occ) / n / 63 * 100:.1f}%），"
          f"带宝石阵容 {n_with}/{n}（宝石 {min(g_gem)}–{max(g_gem)}，合计 {sum(g_gem)}）")
    return 0


# ═══════════════════════════ 主流程 ═══════════════════════════

def main(argv: Optional[List[str]] = None) -> int:
    ap = argparse.ArgumentParser(
        description="随机阵容采样（终盘规模）+ 多进程对战数据集生成（gd_core 内核）")
    ap.add_argument("--pairs", type=int, help="阵容对数")
    ap.add_argument("--out", default=os.path.join(_REPO, "data", "dataset_v3.jsonl"),
                    help="输出 JSONL 路径（默认 data/dataset_v3.jsonl）")
    ap.add_argument("--workers", type=int, default=os.cpu_count() or 1,
                    help="并行进程数（默认 CPU 核数）")
    ap.add_argument("--seeds", type=int, default=2,
                    help="每对阵容的模拟局数 / 随机 seed 数（默认 2）")
    ap.add_argument("--truth-ratio", type=float, default=TRUTH_RATIO,
                    help="对手取自真值实录池的比例（默认 0.2）")
    ap.add_argument("--sample-check", type=int, default=None, metavar="N",
                    help="只采样 N 套随机阵容统计规模并与真值对照，不模拟")
    ap.add_argument("--check-seed", type=int, default=20261002,
                    help="--sample-check 的随机种子（默认 20261002）")
    args = ap.parse_args(argv)

    if args.sample_check is not None:
        return sample_check(args.sample_check, args.check_seed)

    if not args.pairs or args.pairs < 1 or args.seeds < 1 or args.workers < 1:
        print("❌ --pairs/--seeds/--workers 均须 ≥ 1", file=sys.stderr)
        return 2

    t0 = time.time()
    data = load_runtime()
    pool = playable_pool(data)
    classes = data.get("classes") or {}
    if not classes or not pool:
        print("❌ 运行时资产缺少 items/classes", file=sys.stderr)
        return 2

    truth = load_truth_pool(pool)
    done = existing_keys(args.out)
    if done:
        print(f"断点续跑：{args.out} 已有 {len(done)} 对，本次新增 {args.pairs} 对"
              f"（已存在的对自动去重跳过）", file=sys.stderr)

    os.makedirs(os.path.dirname(os.path.abspath(args.out)) or ".", exist_ok=True)

    # ── 采样去重后的阵容对 ──
    master = random.Random()
    seen = set(done)
    tasks: List[Tuple[int, dict, dict, int, int]] = []
    n_truth_opp = 0
    attempts = 0
    max_attempts = args.pairs * 200 + 1000
    while len(tasks) < args.pairs and attempts < max_attempts:
        attempts += 1
        player = make_lineup_v3(master, data, pool, classes,
                                f"gen_p{attempts:06d}")
        if truth and master.random() < args.truth_ratio:
            opponent = master.choice(truth)
            n_truth_opp += 1
        else:
            opponent = make_lineup_v3(master, data, pool, classes,
                                      f"gen_o{attempts:06d}")
        key = pair_key(to_v4(player), to_v4(opponent))
        if key in seen:
            if opponent in truth:
                n_truth_opp -= 1
            continue
        seen.add(key)
        tasks.append((len(tasks), player, opponent,
                      master.randrange(1, 2 ** 31), args.seeds))
    if len(tasks) < args.pairs:
        print(f"❌ 采样去重后仅得 {len(tasks)}/{args.pairs} 对（尝试 {attempts} 次）",
              file=sys.stderr)
        return 2
    gen_t = time.time() - t0
    print(f"采样完成：{len(tasks)} 对"
          f"（真值对手 {n_truth_opp} 对 / 随机对手 {len(tasks) - n_truth_opp} 对）"
          f"，耗时 {gen_t:.1f}s", file=sys.stderr)

    # ── 多进程对战，逐条落盘（断点可续） ──
    print(f"开始模拟：{len(tasks)} 对 × {args.seeds} 局，workers={args.workers}",
          file=sys.stderr)
    wins_total = 0
    n_ok = 0
    n_fail = 0
    t1 = time.time()
    with open(args.out, "a", encoding="utf-8") as fout, \
            Pool(processes=args.workers) as pool_mp:
        for res in pool_mp.imap_unordered(run_pair, tasks, chunksize=1):
            if "error" in res:
                n_fail += 1
                print(f"⚠ 对局失败，跳过：{res['error']}", file=sys.stderr)
            else:
                fout.write(json.dumps(res, ensure_ascii=False) + "\n")
                fout.flush()
                wins_total += int(res["wins"])
                n_ok += 1
            done_n = n_ok + n_fail
            if done_n % max(1, len(tasks) // 10 or 1) == 0 or done_n == len(tasks):
                print(f"  进度 {done_n}/{len(tasks)}  "
                      f"胜率 {wins_total / max(1, n_ok * args.seeds) * 100:.1f}%  "
                      f"耗时 {time.time() - t1:.1f}s", file=sys.stderr)

    dt = time.time() - t1
    per_battle = dt / max(1, n_ok * args.seeds)
    print(f"✅ 完成：写入 {n_ok} 对 → {args.out}（失败 {n_fail}）  "
          f"玩家总胜率 {wins_total / max(1, n_ok * args.seeds) * 100:.1f}%  "
          f"模拟耗时 {dt:.1f}s（单局均值 {per_battle:.2f}s，"
          f"{n_ok * args.seeds / dt:.2f} 局/s）  "
          f"总计 {time.time() - t0:.1f}s", file=sys.stderr)
    return 0 if n_fail == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
