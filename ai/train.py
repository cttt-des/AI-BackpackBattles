# -*- coding: utf-8 -*-
"""train.py — 胜率代理模型训练（ai/model.py 的 WinRateModel）

做什么
======
1. 读 data/dataset_v1.jsonl（每行 {"player": v4阵容, "opponent": v4阵容,
   "wins": n, "seeds": n}），标签 = wins / seeds ∈ [0,1]（软标签，BCE 直接吃）。
2. 阵容张量化：ai/encoding.py encode_lineup + ai/model.py lineup_tensors，
   每个唯一阵容只编码一次（内容哈希缓存）。
3. 防泄漏切分：按阵容内容哈希做并查集——同一样本的玩家/对手阵容连边、
   内容哈希与其宝石无关哈希（ai/model.py lineup_base_hash）连边（同一阵容
   的宝石变体并成同组）、出现在多个样本对里的同一阵容自动并入同组；
   组（连通分量）整体按约 8:1:1 随机分到 train/val/test，保证同一阵容
   （含宝石变体）绝不同时出现在两侧。
4. 训练：BCE + Adam，CUDA 可用则用 GPU，否则 CPU 也能跑完；val 用于一切
   选型（逐 epoch 选优、蒸馏教师取舍、top-K 权重均值），test 只在最终
   评估一次、绝不参与任何选型。
5. test 集自实现 Spearman 排序相关（不依赖 scipy）；保存最优权重到
   ai/weights.pt；stdout 最后一行打印 `SPEARMAN <浮点>`（来自 test 集）。

用法
====
    python ai/train.py --data data/dataset_v1.jsonl --epochs 10
"""
from __future__ import annotations

import argparse
import json
import os
import random
import sys
import time
from collections import defaultdict
from typing import Dict, List, Optional, Tuple

import numpy as np
import torch
import torch.nn.functional as F
from torch.utils.data import DataLoader, Dataset

# 仓库根入 sys.path（既可 `python ai/train.py` 也可 -m 方式跑）
_REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _REPO not in sys.path:
    sys.path.insert(0, _REPO)

from ai import model as M  # noqa: E402
from ai.encoding import encode_lineup  # noqa: E402

DEFAULT_OUT = os.path.join(_REPO, "ai", "weights.pt")

# TE 统计切分常数（train 与 placer 部署口径共用；不随 CLI 覆盖变化）
TE_VAL_FRAC = 0.1
TE_TEST_FRAC = 0.1


# ─────────────────────────── 数据 ───────────────────────────

def load_pairs(path: str) -> List[dict]:
    pairs = []
    with open(path, encoding="utf-8") as f:
        for ln, line in enumerate(f, 1):
            line = line.strip()
            if not line:
                continue
            d = json.loads(line)
            seeds = int(d.get("seeds", 1) or 1)
            if seeds <= 0 or "player" not in d or "opponent" not in d:
                continue
            pairs.append({"player": d["player"], "opponent": d["opponent"],
                          "y": float(d.get("wins", 0)) / seeds, "line": ln})
    return pairs


class PairDataset(Dataset):
    """每样本 = 玩家/对手张量组 + 软标签。张量预先算好（编码缓存）。"""

    def __init__(self, samples: List[Tuple[dict, dict, float]]):
        self.samples = samples

    def __len__(self):
        return len(self.samples)

    def __getitem__(self, i):
        p, o, y = self.samples[i]
        return {"p": p, "o": o, "y": y}


def _to_tensor_group(t: Dict[str, np.ndarray]) -> Dict[str, torch.Tensor]:
    return {k: torch.from_numpy(np.ascontiguousarray(v)) for k, v in t.items()}


# ─────────────────────────── 防泄漏分组切分 ───────────────────────────

class _UnionFind:
    def __init__(self):
        self.parent: Dict[str, str] = {}

    def find(self, x: str) -> str:
        self.parent.setdefault(x, x)
        root = x
        while self.parent[root] != root:
            root = self.parent[root]
        while self.parent[x] != root:            # 路径压缩
            self.parent[x], x = root, self.parent[x]
        return root

    def union(self, a: str, b: str) -> None:
        ra, rb = self.find(a), self.find(b)
        if ra != rb:
            self.parent[rb] = ra


def group_split3(n_pairs: int, lineup_hashes: List[Tuple[str, str]],
                 val_frac: float, test_frac: float, seed: int,
                 extra_edges: Optional[List[Tuple[str, str]]] = None
                 ) -> Tuple[List[int], List[int], List[int]]:
    """按阵容哈希并查集分组 → 组级约 (1−val_frac−test_frac):val_frac:test_frac 切分。

    并查集连边：同一样本的玩家/对手阵容（同一对必须同侧）、extra_edges
    （train.py 传入：内容哈希 ↔ 宝石无关哈希，把同一阵容的宝石变体并成同组）。
    组（连通分量）整体随机分配，同一阵容（含宝石变体）绝不跨侧。
    返回 (train 下标, val 下标, test 下标)；test_frac=0 时不留 test 组。
    """
    uf = _UnionFind()
    for h_p, h_o in lineup_hashes:
        uf.union(h_p, h_o)                       # 同一对两侧连边
    for a, b in (extra_edges or []):
        uf.union(a, b)                           # 内容哈希 ↔ 宝石无关哈希
    groups: Dict[str, List[int]] = defaultdict(list)
    for i, (h_p, h_o) in enumerate(lineup_hashes):
        groups[uf.find(h_p)].append(i)

    keys = sorted(groups)                        # 组键定序 → 洗牌可复现
    rng = random.Random(seed)
    rng.shuffle(keys)
    n_val = max(1, int(round(len(keys) * val_frac))) if keys else 0
    n_test = (max(1, int(round(len(keys) * test_frac)))
              if keys and test_frac > 0 else 0)
    train_idx, val_idx, test_idx = [], [], []
    for gi, key in enumerate(keys):
        if gi < n_val:
            val_idx.extend(groups[key])
        elif gi < n_val + n_test:
            test_idx.extend(groups[key])
        else:
            train_idx.extend(groups[key])
    return sorted(train_idx), sorted(val_idx), sorted(test_idx)


def group_split(n_pairs: int, lineup_hashes: List[Tuple[str, str]],
                val_frac: float, seed: int) -> Tuple[List[int], List[int]]:
    """按阵容哈希并查集分组 → 组级二分切分（ placer.compute_te 兼容接口）。
    返回 (train 下标, val 下标)。"""
    train_idx, val_idx, _test_idx = group_split3(
        n_pairs, lineup_hashes, val_frac, 0.0, seed)
    return train_idx, val_idx


def compute_item_te(pairs: List[dict], item_db: dict, vocab_index: Dict[str, int],
                    seed: int, val_frac: float, test_frac: float, smoothing: float,
                    precomputed: Optional[Tuple] = None
                    ) -> Tuple[np.ndarray, Dict[str, float]]:
    """Canonical 物品强度目标编码（train 训练期与 placer 部署期共用，逐位一致）。

    s_i = (Σy_i + k·prior)/(n_i + k) − prior，只统计 3-way 切分（group_split3，
    含内容哈希↔宝石无关哈希连边）train 侧样本、玩家侧阵容的根物品。
    precomputed=(hashes, base_edges, lineup_ids) 供 main 传入已编码结果避免重复
    encode；placer 侧不传、自行构建——两侧必须产出逐位相同的 s_tilde，否则模型
    对强度通道的记忆化键失配、代理分崩塌（实测 val ρ 0.63 → 0.51）。
    """
    if precomputed is None:
        hashes: List[Tuple[str, str]] = []
        base_edges: List[Tuple[str, str]] = []
        lineup_ids: Dict[str, set] = {}
        for p in pairs:
            for side in ("player", "opponent"):
                h = M.lineup_content_hash(p[side])
                if h not in lineup_ids:
                    # 只统计引擎装配的根物品（与编码层网格同口径）
                    lineup_ids[h] = set(encode_lineup(p[side], item_db)["root_ids"])
            hp = M.lineup_content_hash(p["player"])
            ho = M.lineup_content_hash(p["opponent"])
            hashes.append((hp, ho))
            base_edges.append((hp, M.lineup_base_hash(p["player"])))
            base_edges.append((ho, M.lineup_base_hash(p["opponent"])))
    else:
        hashes, base_edges, lineup_ids = precomputed
    te_train_idx, _, _ = group_split3(len(pairs), hashes, val_frac, test_frac,
                                      seed, extra_edges=base_edges)
    prior = float(np.mean([pairs[i]["y"] for i in te_train_idx]))
    k = smoothing
    cnt: Dict[str, float] = defaultdict(float)
    hit: Dict[str, float] = defaultdict(float)
    for i in te_train_idx:
        for name in lineup_ids[hashes[i][0]]:      # 玩家侧阵容里的物品
            cnt[name] += 1.0
            hit[name] += pairs[i]["y"]
    s_tilde = np.zeros(len(vocab_index), dtype=np.float32)
    te_by_name: Dict[str, float] = {}
    for name, c in cnt.items():
        s = (hit[name] + k * prior) / (c + k)
        s_tilde[vocab_index.get(name, M.UNK_IDX)] = s - prior
        te_by_name[name] = s - prior
    return s_tilde, te_by_name


# ─────────────────────────── Spearman（自实现） ───────────────────────────

def _rankdata(x: np.ndarray) -> np.ndarray:
    """平均秩（ties 取平均），对齐 scipy.stats.rankdata 默认行为。"""
    x = np.asarray(x, dtype=np.float64)
    n = x.shape[0]
    order = np.argsort(x, kind="mergesort")
    ranks = np.empty(n, dtype=np.float64)
    sx = x[order]
    i = 0
    while i < n:
        j = i
        while j + 1 < n and sx[j + 1] == sx[i]:
            j += 1
        ranks[order[i:j + 1]] = 0.5 * (i + j) + 1.0
        i = j + 1
    return ranks


def spearman(a, b) -> float:
    """Spearman ρ = 秩的 Pearson 相关。常向量（秩零方差）返回 0.0。"""
    ra, rb = _rankdata(a), _rankdata(b)
    ra = ra - ra.mean()
    rb = rb - rb.mean()
    denom = float(np.sqrt((ra * ra).sum() * (rb * rb).sum()))
    if denom == 0.0:
        return 0.0
    return float((ra * rb).sum() / denom)


# ─────────────────────────── 训练/评估原语 ───────────────────────────

def evaluate(model, dl, device) -> Tuple[float, List[float], List[float]]:
    """评估：返回 (BCE loss, 对称推理概率, 标签)。
    对称推理——胜率满足 π(p,o) = 1 − π(o,p)，两方向取平均（免参的测试时增强）。"""
    model.eval()
    tot, ys, ps = 0.0, [], []
    with torch.no_grad():
        for batch in dl:
            p = {k: v.to(device) for k, v in batch["p"].items()}
            o = {k: v.to(device) for k, v in batch["o"].items()}
            y = batch["y"].to(device)
            prob = 0.5 * (model(p, o) + (1.0 - model(o, p)))
            tot += float(F.binary_cross_entropy(prob, y)) * len(y)
            ys.extend(y.tolist())
            ps.extend(prob.tolist())
    return tot / max(len(ys), 1), ps, ys


def fit_model(model, train_dl, val_dl, device, *, epochs: int, lr: float,
              weight_decay: float, scheduler: str, verbose: bool = True,
              tag: str = "", evals_per_epoch: int = 1
              ) -> List[Tuple[float, int, dict]]:
    """训练一个模型，返回按 val ρ 排序的 [(val rho, epoch, CPU state_dict)]。

    evals_per_epoch > 1 时每个 epoch 在中途（等分步数处）追加 val 评估与
    checkpoint（epoch 记为 1.5 这类小数）——学生/教师的 val 峰值常出现在
    第 1 个 epoch 内部，密集采样让「峰值区候选池」更稳，且 top-K 均值只
    会平均同一条轨迹相邻的权重（同一盆地，加权平均有效）。
    """
    opt = torch.optim.Adam(model.parameters(), lr=lr, weight_decay=weight_decay)
    sched = (torch.optim.lr_scheduler.CosineAnnealingLR(opt, T_max=epochs)
             if scheduler == "cosine" else None)
    steps = len(train_dl)
    interval = max(1, steps // max(1, evals_per_epoch))
    history: List[Tuple[float, int, dict]] = []
    for epoch in range(1, epochs + 1):
        # 训练轮（不对称：就着给定方向学，对称性交给镜像增强/对称推理）
        model.train()
        tot, n, ys, ps = 0.0, 0, [], []
        for step, batch in enumerate(train_dl, 1):
            p = {k: v.to(device) for k, v in batch["p"].items()}
            o = {k: v.to(device) for k, v in batch["o"].items()}
            y = batch["y"].to(device)
            prob = model(p, o)
            loss = F.binary_cross_entropy(prob, y)
            opt.zero_grad()
            loss.backward()
            opt.step()
            tot += float(loss.detach()) * len(y)
            n += len(y)
            ys.extend(y.tolist())
            ps.extend(prob.detach().tolist())
            if (evals_per_epoch > 1 and step % interval == 0
                    and step != steps):
                va_m, va_rho_m = spearman_loss(model, val_dl, device)
                state = {k: v.detach().cpu().clone()
                         for k, v in model.state_dict().items()}
                history.append((va_rho_m, epoch - 1 + step / steps, state))
        tr_loss, tr_rho = tot / max(n, 1), spearman(ys, ps)
        va_loss, va_rho = spearman_loss(model, val_dl, device)
        state = {k: v.detach().cpu().clone() for k, v in model.state_dict().items()}
        history.append((va_rho, epoch, state))
        if verbose:
            star = "  *best" if va_rho >= max(h[0] for h in history) else ""
            print(f"{tag}epoch {epoch:3d}/{epochs}  train loss={tr_loss:.4f} rho={tr_rho:.4f}  "
                  f"val loss={va_loss:.4f} rho={va_rho:.4f}{star}")
        if sched is not None:
            sched.step()
    history.sort(key=lambda t: -t[0])
    return history


def spearman_loss(model, dl, device) -> Tuple[float, float]:
    loss, ps, ys = evaluate(model, dl, device)
    return loss, spearman(ys, ps)


def topk_average_state(history, k: int):
    """val ρ 最高 K 个 epoch 的 state_dict 逐参数均值（SWA 式；非浮点 buffer 取最优）。"""
    k = min(k, len(history))
    avg = {}
    for key, v0 in history[0][2].items():
        if v0.dtype.is_floating_point:
            avg[key] = torch.stack([s[key].float()
                                    for _, _, s in history[:k]]).mean(0).to(v0.dtype)
        else:
            avg[key] = v0
    return avg, [h[1] for h in history[:k]]


# ─────────────────────────── 训练主流程 ───────────────────────────

def parse_args(argv=None):
    ap = argparse.ArgumentParser(description="胜率代理模型训练")
    ap.add_argument("--data", required=True, help="dataset JSONL 路径")
    ap.add_argument("--epochs", type=int, default=10)
    ap.add_argument("--batch-size", type=int, default=128)
    ap.add_argument("--lr", type=float, default=1e-3)
    ap.add_argument("--val-frac", type=float, default=0.1, help="验证组占比（约 0.1）")
    ap.add_argument("--test-frac", type=float, default=0.1,
                    help="测试组占比（约 0.1；test 只在最终评估一次）")
    ap.add_argument("--seed", type=int, default=42)
    ap.add_argument("--model-seed", type=int, default=None,
                    help="模型初始化/洗牌种子（默认跟 --seed；切分恒用 --seed）")
    ap.add_argument("--out", default=DEFAULT_OUT, help="权重保存路径")
    ap.add_argument("--num-workers", type=int, default=0)
    ap.add_argument("--device", choices=("auto", "cuda", "cpu"), default="auto",
                    help="auto=有 CUDA 用 CUDA，否则 CPU")
    ap.add_argument("--weight-decay", type=float, default=0.0)
    ap.add_argument("--dropout", type=float, default=0.0, help="MLP Dropout 概率")
    ap.add_argument("--scheduler", choices=("cosine", "none"), default="none")
    ap.add_argument("--no-swap-aug", action="store_true",
                    help="关闭训练集对称增强（玩家/对手互换、标签取 1-y）")
    ap.add_argument("--res-blocks", type=int, default=2, help="塔内残差块数")
    ap.add_argument("--inter-blocks", type=int, default=0,
                    help="交互图 3x3 残差块数（0=仅 1x1 交互卷积）")
    ap.add_argument("--label-shrink", type=float, default=1.0,
                    help="训练标签向 0.5 收缩系数（1=不收缩；对抗 2-seeds 标签噪声）")
    ap.add_argument("--topk-average", type=int, default=3,
                    help="末了用 val ρ 最高的 K 个 epoch 权重均值出结果（0=只用单点最优）")
    ap.add_argument("--distill", type=int, default=4,
                    help="自蒸馏教师数 K：先训 K 个不同种子的教师，用其集成概率做软标签再训学生（1/0=关）")
    ap.add_argument("--distill-beta", type=float, default=0.7,
                    help="软标签混合系数：目标 = β·教师集成 + (1-β)·真值（val 扫描 0.7 最优）")
    ap.add_argument("--student-restarts", type=int, default=2,
                    help="学生重启次数（各自独立初始化训练，与教师候选一起只按 val 选优）")
    ap.add_argument("--student-lr", type=float, default=None,
                    help="学生学习率（默认跟随 --lr；软标签下可调低抑制记忆化）")
    ap.add_argument("--evals-per-epoch", type=int, default=2,
                    help="每 epoch 额外 checkpoint/val 评估次数（峰值区密集采样，1=仅 epoch 末）")
    ap.add_argument("--oof-folds", type=int, default=4,
                    help="OOF 分折蒸馏折数（教师在 1−1/fold 子集训练、对留出折出预测；"
                         "1=退回同数据蒸馏）")
    ap.add_argument("--emb-dim", type=int, default=32, help="物品 embedding 维度")
    ap.add_argument("--tower-ch", type=int, default=64, help="塔特征通道数")
    ap.add_argument("--te-smoothing", type=float, default=20.0,
                    help="物品强度目标编码的平滑伪计数（0=关目标编码通道）")
    ap.add_argument("--no-prior", action="store_true",
                    help="关闭线性先验分支（aux 特征 numpy LR 冻结进模型，CNN 学残差）")
    return ap.parse_args(argv)


def main(argv=None) -> int:
    args = parse_args(argv)
    t0 = time.time()
    torch.manual_seed(args.model_seed if args.model_seed is not None else args.seed)
    np.random.seed(args.seed)
    random.seed(args.seed)
    if args.device == "auto":
        device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    else:
        device = torch.device(args.device)
    print(f"device: {device} (torch {torch.__version__})")

    # ── 数据 ──
    pairs = load_pairs(args.data)
    if len(pairs) < 10:
        print(f"数据太少：{len(pairs)} 行（{args.data}）", file=sys.stderr)
        return 1
    print(f"pairs: {len(pairs)}  label mean={np.mean([p['y'] for p in pairs]):.3f}")

    item_db = M.load_item_db()
    vocab = M.build_item_vocab(item_db)
    vocab_index = {name: i for i, name in enumerate(vocab)}
    print(f"item vocab: {len(vocab)} (含 2 个特殊 token)")

    # 编码（唯一阵容缓存）+ 内容哈希 + 逐阵容物品 id 集（目标编码用）
    cache: Dict[str, Dict[str, torch.Tensor]] = {}
    lineup_ids: Dict[str, set] = {}
    lineup_roots: Dict[str, list] = {}           # 根物品列表（含同名多件，标量 TE 和用）
    hashes: List[Tuple[str, str]] = []
    base_edges: List[Tuple[str, str]] = []       # 内容哈希 ↔ 宝石无关哈希
    for p in pairs:
        for side in ("player", "opponent"):
            h = M.lineup_content_hash(p[side])
            if h not in cache:
                enc = encode_lineup(p[side], item_db)
                # item_db 必须传：稀有度通道在部署侧（placer.Scorer.tensors）
                # 是填充的——训练期若缺省 None 则该通道全零，训练/部署输入分布
                # 失配，保存权重在部署口径下的 val ρ 从 0.63 崩到 0.51。
                cache[h] = _to_tensor_group(
                    M.lineup_tensors(enc, vocab_index, p[side], item_db))
                # 与编码层网格同口径：只统计引擎装配的根物品
                lineup_ids[h] = set(enc["root_ids"])
                lineup_roots[h] = list(enc["root_ids"])
        hp, ho = M.lineup_content_hash(p["player"]), M.lineup_content_hash(p["opponent"])
        hashes.append((hp, ho))
        base_edges.append((hp, M.lineup_base_hash(p["player"])))
        base_edges.append((ho, M.lineup_base_hash(p["opponent"])))
    print(f"unique lineups: {len(cache)}  (encode {time.time()-t0:.1f}s)")

    # 组级 8:1:1 切分：同一对两侧连边 + 内容哈希↔宝石无关哈希连边
    # （同一阵容的宝石变体并成同组，绝不跨侧）
    train_idx, val_idx, test_idx = group_split3(
        len(pairs), hashes, args.val_frac, args.test_frac, args.seed,
        extra_edges=base_edges)
    # 防泄漏硬校验：任一阵容哈希（含宝石无关变体口径）不得同时出现在两侧
    def _side_hashes(idxs):
        return ({h for i in idxs for h in hashes[i]},
                {b for i in idxs for b in (base_edges[2 * i][1],
                                           base_edges[2 * i + 1][1])})
    train_hashes, train_bases = _side_hashes(train_idx)
    val_hashes, val_bases = _side_hashes(val_idx)
    test_hashes, test_bases = _side_hashes(test_idx)
    leaked = ((train_hashes & val_hashes) | (train_hashes & test_hashes)
              | (val_hashes & test_hashes)
              | (train_bases & val_bases) | (train_bases & test_bases)
              | (val_bases & test_bases))
    assert not leaked, f"切分泄漏：{len(leaked)} 个阵容同时出现在两侧"
    print(f"split: train={len(train_idx)} val={len(val_idx)} test={len(test_idx)} "
          f"(groups by lineup-hash union-find + 宝石变体连边, "
          f"lineup leak=0, 阵容数 train {len(train_hashes)} / "
          f"val {len(val_hashes)} / test {len(test_hashes)})")

    # ── 物品强度目标编码（canonical compute_item_te：train/placer 逐位一致）──
    # s_i = 平滑后的 P(玩家胜 | 物品 i 在玩家阵容)，中心化得 s̃_i ∈ [-0.5,0.5]；
    # 注入两塔输入（forward 内对手塔取负）。统计只用 3-way 切分的 train 侧标签，
    # 部署侧（placer.compute_te）必须能重建出逐位相同的 s̃——此前两口径有微差
    # （placer 用 2-way 切分），模型对强度通道的记忆化键失配，保存权重的 val
    # 代理分从 0.63 崩到 0.51。val/test 阵容照常套用（目标编码惯例）。
    if args.te_smoothing > 0:
        s_tilde, te_by_name = compute_item_te(
            pairs, item_db, vocab_index, args.seed, TE_VAL_FRAC,
            TE_TEST_FRAC, args.te_smoothing,
            precomputed=(hashes, base_edges, lineup_ids))
        n_cov = sum(1 for v in s_tilde[M.PAD_VOCAB:] if v != 0.0)
        print(f"item-strength TE: smoothing=k={args.te_smoothing} "
              f"items covered={n_cov}/{len(vocab) - M.PAD_VOCAB}")
        for h, t in cache.items():
            t["strength"] = torch.from_numpy(s_tilde[t["items"].numpy()])[None]
            # 标量第 11 维 = 阵容物品 TE 强度和（LR 诊断里最强特征之一的来源）。
            # 必须按根物品列表（含同名多件）求和——部署侧 placer.Scorer.tensors
            # 就是这个口径；用去重集合会和部署差 ~0.05（终盘阵容同名多件极多）。
            t["scalars"][M.SCALAR_DIM - 1] = float(
                sum(te_by_name.get(n, 0.0) for n in lineup_roots[h]))
    for h, t in cache.items():
        t.setdefault("strength", torch.zeros_like(t["items"], dtype=torch.float32))

    def make_ds(idx: List[int]) -> PairDataset:
        return PairDataset([(cache[hashes[i][0]], cache[hashes[i][1]],
                             pairs[i]["y"]) for i in idx])

    train_ds, val_ds = make_ds(train_idx), make_ds(val_idx)
    collate = lambda b: {  # noqa: E731
        "p": {k: torch.stack([s["p"][k] for s in b]) for k in b[0]["p"]},
        "o": {k: torch.stack([s["o"][k] for s in b]) for k in b[0]["o"]},
        "y": torch.tensor([s["y"] for s in b], dtype=torch.float32),
    }
    train_dl = DataLoader(train_ds, batch_size=args.batch_size, shuffle=True,
                          collate_fn=collate, num_workers=args.num_workers)
    train_base_dl = DataLoader(train_ds, batch_size=args.batch_size, shuffle=False,
                               collate_fn=collate, num_workers=args.num_workers)
    val_dl = DataLoader(val_ds, batch_size=args.batch_size, shuffle=False,
                        collate_fn=collate, num_workers=args.num_workers)
    test_ds = make_ds(test_idx)
    test_dl = DataLoader(test_ds, batch_size=args.batch_size, shuffle=False,
                         collate_fn=collate, num_workers=args.num_workers)

    # ── 线性先验：aux 特征 [p_scalars, o_scalars, p−o] 上的 numpy LR，冻结进模型 ──
    # 诊断依据：10 维标量 LR 的 val ρ 就有 0.668，超过深层 CNN——把这条强信号
    # 固化成先验 logit，让 CNN 只学残差。fit_prior_lr 抽成函数，OOF 教师按折
    # 各自拟合（只用本折训练子集的标签，保证折内预测的 OOF 诚实性）。
    def fit_prior_lr(samples) -> Optional[np.ndarray]:
        if args.no_prior:
            return None
        X = np.stack([np.concatenate([ps["scalars"].numpy(), os_["scalars"].numpy(),
                                      ps["scalars"].numpy() - os_["scalars"].numpy()])
                      for (ps, os_, _) in samples])
        yv = np.array([yy for (_, _, yy) in samples], dtype=np.float64)
        w = np.zeros(X.shape[1] + 1)
        for _ in range(4000):
            pr = 1.0 / (1.0 + np.exp(-(X @ w[:-1] + w[-1])))
            w[:-1] -= 0.5 * (X.T @ (pr - yv) / len(yv) + 1e-2 * w[:-1] / len(yv))
            w[-1] -= 0.5 * float(np.mean(pr - yv))
        return w.astype(np.float32)

    prior_w = fit_prior_lr(train_ds.samples)   # 初始版（原始硬标签，swap 前）

    def set_prior(m, w=None):
        w = prior_w if w is None else w
        if w is not None:
            m.prior_w.copy_(torch.from_numpy(w))

    fit_kw = dict(epochs=args.epochs, lr=args.lr, weight_decay=args.weight_decay,
                  scheduler=args.scheduler, evals_per_epoch=args.evals_per_epoch)

    # ── 自蒸馏：教师集成概率做软标签。默认 OOF 分折——教师在训练集的 3/4 子集
    # 上训练、对留出的 1/4 折出预测，学生拿到的目标不含「教师对自己见过样本的
    # 记忆化输出」（同数据蒸馏会把教师的记忆误差当知识传给学生，恶化泛化）。
    # 折按阵容哈希并查集分组（同一阵容/宝石变体恒同折），折间零泄漏。
    teacher_histories: List[List[Tuple[float, int, dict]]] = []
    if args.distill > 1:
        M.MLP_DROPOUT = args.dropout
        y_train = [s[2] for s in train_ds.samples]
        val_prob_sum = None
        if args.oof_folds > 1:
            # 折划分：并查集（对内哈希 + 宝石变体连边）→ 组整体轮转分折
            uf_f = _UnionFind()
            for i in train_idx:
                uf_f.union(hashes[i][0], hashes[i][1])
                uf_f.union(base_edges[2 * i][1], hashes[i][0])
                uf_f.union(base_edges[2 * i + 1][1], hashes[i][1])
            groups_f: Dict[str, List[int]] = defaultdict(list)
            for i in train_idx:
                groups_f[uf_f.find(hashes[i][0])].append(i)
            keys_f = sorted(groups_f)
            random.Random(args.seed + 7).shuffle(keys_f)
            folds: List[List[int]] = [[] for _ in range(args.oof_folds)]
            for gi, kk in enumerate(keys_f):
                folds[gi % args.oof_folds].extend(groups_f[kk])
            folds = [sorted(f) for f in folds]
            pos = {i: j for j, i in enumerate(train_idx)}
            probs_oof = np.zeros(len(train_idx), dtype=np.float64)
            for fi, fold in enumerate(folds):
                fold_set = set(fold)
                sub_idx = [i for i in train_idx if i not in fold_set]
                sub_samples = list(make_ds(sub_idx).samples)
                if not args.no_swap_aug:
                    sub_samples = sub_samples + [(o, p, 1.0 - y)
                                                 for (p, o, y) in sub_samples]
                sub_dl = DataLoader(PairDataset(sub_samples), batch_size=args.batch_size,
                                    shuffle=True, collate_fn=collate,
                                    num_workers=args.num_workers)
                fold_dl = DataLoader(
                    make_ds(fold), batch_size=args.batch_size, shuffle=False,
                    collate_fn=collate, num_workers=args.num_workers)
                torch.manual_seed((args.model_seed or args.seed) + 1001 + fi)
                tm = M.WinRateModel(n_items=len(vocab), n_blocks=args.res_blocks,
                                    inter_blocks=args.inter_blocks,
                                    emb_dim=args.emb_dim, tower_ch=args.tower_ch
                                    ).to(device)
                set_prior(tm, fit_prior_lr(sub_samples))
                th = fit_model(tm, sub_dl, val_dl, device, verbose=False, **fit_kw)
                teacher_histories.append(th)
                if args.topk_average > 1:
                    avg, eps = topk_average_state(th, args.topk_average)
                    tm.load_state_dict(avg)
                else:
                    avg, eps = th[0][2], [th[0][1]]
                th_rho = spearman_loss(tm, val_dl, device)[1]
                _, fps, _ = evaluate(tm, fold_dl, device)
                for i, pr in zip(fold, fps):
                    probs_oof[pos[i]] = pr
                _, _ps_val, ys_val = evaluate(tm, val_dl, device)
                val_prob_sum = (np.asarray(_ps_val, dtype=np.float64)
                                if val_prob_sum is None
                                else val_prob_sum + np.asarray(_ps_val, dtype=np.float64))
                print(f"OOF teacher {fi+1}/{args.oof_folds}: val rho={th_rho:.4f} "
                      f"(avg epochs={eps}, fold n={len(fold)})")
            soft = probs_oof
            print(f"OOF ensemble: train rho(vs真值)={spearman(y_train, soft):.4f}  "
                  f"val rho(教师等权集成)={spearman(ys_val, (val_prob_sum / args.oof_folds).tolist()):.4f}")
        else:
            teacher_probs = np.zeros(len(train_ds.samples), dtype=np.float64)
            for ti in range(args.distill):
                torch.manual_seed((args.model_seed or args.seed) + 1001 + ti)
                tm = M.WinRateModel(n_items=len(vocab), n_blocks=args.res_blocks,
                                    inter_blocks=args.inter_blocks,
                                    emb_dim=args.emb_dim, tower_ch=args.tower_ch
                                    ).to(device)
                set_prior(tm)
                th = fit_model(tm, train_dl, val_dl, device, verbose=False, **fit_kw)
                teacher_histories.append(th)
                if args.topk_average > 1:
                    avg, eps = topk_average_state(th, args.topk_average)
                    tm.load_state_dict(avg)
                else:
                    avg, eps = th[0][2], [th[0][1]]
                th_rho = spearman_loss(tm, val_dl, device)[1]
                _, ps, _ = evaluate(tm, train_base_dl, device)
                teacher_probs += np.asarray(ps)
                print(f"distill teacher {ti+1}/{args.distill}: val rho={th_rho:.4f} "
                      f"(avg epochs={eps})")
            soft = teacher_probs / args.distill
            print(f"distill ensemble: train rho(vs真值)={spearman(y_train, soft):.4f}")
        beta = args.distill_beta
        train_ds.samples = [(p, o, float(beta * t + (1.0 - beta) * y))
                            for (p, o, y), t in zip(train_ds.samples, soft)]

    # ── 对称增强（软标签之后做：镜像目标 = 1−t 自动成立）与标签收缩 ──
    if not args.no_swap_aug:
        before = len(train_ds.samples)
        train_ds.samples = train_ds.samples + [(o, p, 1.0 - y)
                                               for (p, o, y) in train_ds.samples]
        print(f"swap-aug: train {before} -> {len(train_ds.samples)}")
    if args.label_shrink != 1.0:
        a = args.label_shrink
        train_ds.samples = [(p, o, 0.5 + (y - 0.5) * a) for (p, o, y) in train_ds.samples]
        print(f"label-shrink: alpha={a}")
    prior_w = fit_prior_lr(train_ds.samples)   # 最终版（软标签 + 镜像增强）
    if prior_w is not None:
        yv_f = np.array([yy for (_, _, yy) in train_ds.samples], dtype=np.float64)
        Xf = np.stack([np.concatenate([ps["scalars"].numpy(), os_["scalars"].numpy(),
                                       ps["scalars"].numpy() - os_["scalars"].numpy()])
                       for (ps, os_, _) in train_ds.samples])
        ptr = 1.0 / (1.0 + np.exp(-(Xf @ prior_w[:-1] + prior_w[-1])))
        print(f"prior-LR: train rho={spearman(yv_f, ptr):.4f}")

    # ── 学生模型（最终保存的 ≤500K 单模型；可多重启，全部只按 val 选优）──
    M.MLP_DROPOUT = args.dropout
    model = M.WinRateModel(n_items=len(vocab), n_blocks=args.res_blocks,
                           inter_blocks=args.inter_blocks,
                           emb_dim=args.emb_dim, tower_ch=args.tower_ch).to(device)
    set_prior(model)
    n_params = M.count_parameters(model)
    print(f"params: {n_params:,} ({'OK <500K' if n_params < 500_000 else '超出 500K 上限!'})")

    def _select(histories, labels):
        """跨历史选优：候选 = 每个 epoch 单点 + K=2..topk_average 的权重均值，
        一律按 val ρ 取最优（val 用于一切选型；K=1 即单点最优）。
        返回 (rho, 来源标签, epoch(均值候选记 -K), state)。"""
        best = (-1.0, "", 0, None)
        for hist, lab in zip(histories, labels):
            cands = list(hist)                                 # (rho, epoch, state)
            for k in range(2, max(1, args.topk_average) + 1):
                if k > len(hist):
                    break
                avg, _eps = topk_average_state(hist, k)
                model.load_state_dict(avg)
                rho = spearman_loss(model, val_dl, device)[1]
                cands.append((rho, -k, avg))
            rho, ep, state = max(cands, key=lambda t: t[0])
            print(f"  candidate {lab}: val rho={rho:.4f} (@ep{ep})")
            if rho > best[0]:
                best = (rho, f"{lab}@ep{ep}" if ep > 0 else f"{lab}@avgK{-ep}",
                        ep, state)
        return best

    student_histories: List[List[Tuple[float, int, dict]]] = []
    for r in range(max(1, args.student_restarts)):
        torch.manual_seed((args.model_seed if args.model_seed is not None
                           else args.seed) + 977 * r)
        sm = M.WinRateModel(n_items=len(vocab), n_blocks=args.res_blocks,
                            inter_blocks=args.inter_blocks,
                            emb_dim=args.emb_dim, tower_ch=args.tower_ch).to(device)
        set_prior(sm)
        sh = fit_model(sm, train_dl, val_dl, device,
                       tag=f"[restart {r+1}/{args.student_restarts}] "
                           if args.student_restarts > 1 else "",
                       **({**fit_kw, "lr": args.student_lr}
                          if args.student_lr else fit_kw))
        student_histories.append(sh)

    # ── 全局选优：教师/学生的全部 epoch 与 top-K 均值候选一起按 val ρ 排座次 ──
    labels = ([f"teacher{i+1}" for i in range(len(teacher_histories))]
              + [f"student{r+1}" for r in range(len(student_histories))])
    best_rho, best_from, best_epoch, best_state = _select(
        teacher_histories + student_histories, labels)
    print(f"selected: val rho={best_rho:.4f} from {best_from}")
    model.load_state_dict(best_state)

    # ── 保存权重（选型全部只用了 val；test 到此为止一次未碰）──
    os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)
    torch.save({
        "state_dict": best_state,
        "config": {"n_items": len(vocab), "emb_dim": args.emb_dim,
                   "tower_ch": args.tower_ch, "inter_ch": M.INTER_CH,
                   "res_blocks": args.res_blocks,
                   "inter_blocks": args.inter_blocks,
                   "rows": M.ROWS, "cols": M.COLS,
                   "val_idx": val_idx, "test_idx": test_idx, "seed": args.seed,
                   "best_epoch": best_epoch},
    }, args.out)
    print(f"saved: {args.out} (best epoch {best_epoch}, "
          f"{time.time()-t0:.1f}s total)")

    if os.environ.get("AI_TRAIN_SKIP_TEST") == "1":
        # 超参扫描/选型阶段用：不触碰 test（test 只许在最终评估一次）
        print("(AI_TRAIN_SKIP_TEST=1：跳过 test 评估，SPEARMAN 行不输出)")
        return 0

    # ── 最终评估：test 集只在这里碰这一次，SPEARMAN 来自 test 而非 val ──
    model.load_state_dict(best_state)
    test_loss, test_ps, test_ys = evaluate(model, test_dl, device)
    print(f"test: n={len(test_idx)} bce={test_loss:.4f}")
    print(f"SPEARMAN {spearman(test_ys, test_ps):.6f}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
