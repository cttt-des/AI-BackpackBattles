# -*- coding: utf-8 -*-
"""model.py — 胜率代理模型（双塔 ResNet 式小 CNN）

结构（参数量约 25 万，< 500K 上限，本地 CPU/单卡可训）
======================================================
每座塔（玩家背包 / 对手背包，权重共享）：

  输入 (B, 44, 7, 9)：
    * 物品 embedding 图 (32 通道)：ai/encoding.py 的 item_grid（占格上的
      物品序号）查可学习 embedding 表，按占格散布到网格——每个被物品占据
      的格子取该物品的 embedding 向量，空格为 0；
    * 旋转 one-hot (4 通道)：rotation_grid → 0/90/180/270；
    * collision_mask (1 通道) + affected_masks (4 色通道)：encoding 直出；
    * has_gem (1 通道)：该格所属物品镶了宝石（gem_onehot 行和 > 0）；
    * 稀有度 (1 通道)：该格所属物品 descr.rarity /5（泛化特征）；
    * 物品强度 (1 通道)：train 侧目标编码 s̃_i（平滑平均胜率，中心化），
      forward 里对手塔取负号——物品对玩家越有利，出现在对手背包越不利。
  → Conv3x3 + BN + ReLU → 3 × 残差块（3x3 卷积对 + 跳连）→ 塔特征 (64,7,9)。

交互层：
    逐格积 p⊙o、逐格差 p−o、逐格和 p+o 拼成 (192,7,9) → 1x1 卷积降到 48
    通道；全局 avg+max 池化交互图与两塔特征，连同双方标量（职业 one-hot、
    物品数、稀有度和、回合数、TE 强度和）及其差值拼接过 MLP；再加一条
    冻结的线性先验 logit（train 侧 numpy LR，ai/train.py 拟合）→ sigmoid 胜率。

模型加载/推理只用本文件 + ai/encoding.py（不依赖 simulator/）。权重由
ai/train.py 产出（ai/weights.pt，dict: state_dict + config）。
"""
from __future__ import annotations

import json
import sys
from pathlib import Path
from typing import Dict, List

import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F

# 同目录导入（`python ai/train.py` 与包导入两种姿势都容）
try:
    from . import encoding as _enc  # 包导入
except ImportError:  # pragma: no cover
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    import encoding as _enc  # 脚本直跑

ROWS, COLS = _enc.ROWS, _enc.COLS  # 7, 9

# ── 词表约定：0 = 空格占位，1 = 未知物品，2.. = 物品库物品 ──
EMPTY_IDX = 0
UNK_IDX = 1
PAD_VOCAB = 2

# ── 结构超参 ──
EMB_DIM = 32          # 物品 embedding 维度（散布到网格后的通道数）
ROT_CH = 4            # 旋转 one-hot
MASK_CH = 1 + 4 + 1 + 1 + 1  # collision + 4 色影响格 + has_gem + 稀有度 + 物品强度
IN_CH = EMB_DIM + ROT_CH + MASK_CH          # 43
TOWER_CH = 64         # 塔特征通道
INTER_CH = 48         # 交互 1x1 卷积输出通道
SCALAR_DIM = 11       # 单塔标量：class_onehot(7) + num_items + rarity_sum + round + TE强度和
# num_items 的归一化基准：真值实录平铺物品数实测 37–64（引擎装配口径 = 根物品数，
# 见 ai/encoding.py），归一化必须覆盖该值域——此前 /16 使真值阵容的标量达 ~4，
# 远超训练值域（外推 → 代理分失真）。
ITEM_NORM = 64
N_RES_BLOCKS = 2
INTER_BLOCKS = 0                      # 交互图 3x3 残差块数（训练侧可调）
MLP_DROPOUT = 0.2

ITEM_DB_DEFAULT = Path(__file__).resolve().parent.parent / "assets" / "gd_core_runtime.json"


# ─────────────────────────── 词表 ───────────────────────────

def build_item_vocab(item_db: dict) -> List[str]:
    """物品库 → embedding 词表（前 PAD_VOCAB 个是特殊 token）。"""
    items = item_db.get("items") if isinstance(item_db.get("items"), dict) else item_db
    ids = sorted(k for k in items.keys() if isinstance(k, str))
    return ["<empty>", "<unk>"] + ids


def _hash_payload(lineup: dict, with_gems: bool) -> str:
    """阵容内容哈希的规范化载荷（lineup_content_hash / lineup_base_hash 共用）。"""
    import json as _json
    bp_items = lineup.get("items")
    entries: List[tuple] = []
    if isinstance(bp_items, list):
        for e in bp_items:
            if not isinstance(e, dict) or not e.get("id"):
                continue
            at = e.get("at") or [0, 0]
            if with_gems:
                gem_key = tuple(sorted(str(g.get("id") if isinstance(g, dict) else g)
                                       for g in (e.get("gems") or [])))
            else:
                gem_key = ()
            entries.append((str(e["id"]), int(at[0]), int(at[1]),
                            int(e.get("r", 0) or 0), gem_key))
    return _json.dumps({
        "c": str(lineup.get("character") or ""),
        "r": int(lineup.get("round", 0) or 0),
        "i": sorted(entries),
    }, sort_keys=True, ensure_ascii=False)


def lineup_content_hash(lineup: dict) -> str:
    """阵容内容哈希（分组切分用）：职业+回合数+物品(id,行,列,旋转,宝石)规范化
    序列化的 sha1——与 ai/gen_dataset.py 的去重口径一致（摆位不同即不同阵容）。"""
    import hashlib
    return hashlib.sha1(
        _hash_payload(lineup, with_gems=True).encode("utf-8")).hexdigest()


def lineup_base_hash(lineup: dict) -> str:
    """宝石无关的内容哈希（同一阵容的宝石变体同哈希）——train.py 切分时把
    内容哈希与其宝石无关哈希并查集连边，保证宝石变体不跨 train/val/test 侧。"""
    import hashlib
    return hashlib.sha1(
        _hash_payload(lineup, with_gems=False).encode("utf-8")).hexdigest()


# ─────────────────────────── 编码结果 → 张量 ───────────────────────────

def lineup_tensors(enc: dict, vocab_index: Dict[str, int],
                   lineup: dict, item_db: dict = None) -> Dict[str, np.ndarray]:
    """encode_lineup 的输出（+原阵容 dict 取回合数）→ 固定形状 numpy 张量组。

    返回 dict：
      items    int64 (7,9)  占格物品的词表下标（0=空格，1=未知）
      rot      int64 (7,9)  旋转角序号 0..3（空格 0，靠 items==0 掩掉）
      collision float32 (1,7,9)
      affected float32 (4,7,9)
      gem      float32 (1,7,9)  该格所属物品含宝石
      rarity   float32 (1,7,9)  该格所属物品的稀有度 /5（库外/未知记 0）
      scalars  float32 (10,)
    """
    rows, cols = enc["grid_shape"].tolist()
    item_grid = enc["item_grid"]
    rot_grid = enc["rotation_grid"]

    ids: List[str] = enc["ids"]
    cell_items = np.zeros((rows, cols), dtype=np.int64)   # 0 = 空格
    for r in range(rows):
        for c in range(cols):
            i = int(item_grid[r, c])
            if i < 0:
                continue
            cell_items[r, c] = vocab_index.get(ids[i], UNK_IDX)

    rot = np.clip(rot_grid, 0, 3).astype(np.int64)
    rot[item_grid < 0] = 0

    # 宝石格：物品 i 的 gem_onehot 行和 > 0 → 其占格置 1
    gem_per_item = (enc["gem_onehot"].sum(axis=1) > 0) if enc["gem_onehot"].size else np.zeros(len(ids), bool)
    gem_cell = np.zeros((rows, cols), dtype=np.float32)
    hit = item_grid >= 0
    gem_cell[hit] = gem_per_item[item_grid[hit]].astype(np.float32)

    # 稀有度格：物品 i 的 descr.rarity /5（查不到的物品记 0）
    rarity_cell = np.zeros((rows, cols), dtype=np.float32)
    if item_db is not None:
        items_map = item_db.get("items") if isinstance(item_db.get("items"), dict) else item_db
        rar = np.zeros(len(ids), dtype=np.float32)
        for i, name in enumerate(ids):
            entry = items_map.get(name)
            if entry is not None:
                try:
                    rar[i] = float((entry.get("descr") or {}).get("rarity", 0) or 0)
                except (TypeError, ValueError):
                    pass
        rar = np.clip(rar, 0.0, 5.0) / 5.0
        rarity_cell[hit] = rar[item_grid[hit]]

    sc = enc["scalars"]
    round_n = float(lineup.get("round", 0) or 0)
    scalars = np.concatenate([
        sc["class_onehot"].astype(np.float32),                       # 7
        np.array([float(sc["num_items"]) / float(ITEM_NORM),
                  float(sc["rarity_sum"]) / 100.0,
                  min(round_n, 19.0) / 19.0,
                  0.0], dtype=np.float32),   # 4（末位 = TE 强度和，train.py 回填）
    ])
    assert scalars.shape == (SCALAR_DIM,), scalars.shape

    return {
        "items": cell_items,
        "rot": rot,
        "collision": enc["collision_mask"].astype(np.float32)[None],
        "affected": enc["affected_masks"].astype(np.float32),
        "gem": gem_cell[None],
        "rarity": rarity_cell[None],
        "scalars": scalars,
    }


def encode_lineup_tensors(lineup: dict, item_db: dict,
                          vocab_index: Dict[str, int]) -> Dict[str, np.ndarray]:
    """一步到位：阵容 v4 dict → 固定形状张量组（encode_lineup + lineup_tensors）。"""
    enc = _enc.encode_lineup(lineup, item_db)
    return lineup_tensors(enc, vocab_index, lineup, item_db)


# ─────────────────────────── 网络 ───────────────────────────

class ResBlock(nn.Module):
    """3x3 卷积对 + 跳连的残差块（通道数不变）。"""

    def __init__(self, ch: int):
        super().__init__()
        self.conv1 = nn.Conv2d(ch, ch, 3, padding=1, bias=False)
        self.bn1 = nn.BatchNorm2d(ch)
        self.conv2 = nn.Conv2d(ch, ch, 3, padding=1, bias=False)
        self.bn2 = nn.BatchNorm2d(ch)

    def forward(self, x):
        y = F.relu(self.bn1(self.conv1(x)))
        y = self.bn2(self.conv2(y))
        return F.relu(x + y)


class Tower(nn.Module):
    """单背包塔：embedding 散布图 + 几何/状态通道 → ResNet 式小 CNN。"""

    def __init__(self, n_items: int, emb_dim: int = EMB_DIM,
                 out_ch: int = TOWER_CH, n_blocks: int = N_RES_BLOCKS):
        super().__init__()
        self.emb = nn.Embedding(n_items, emb_dim, padding_idx=EMPTY_IDX)
        nn.init.normal_(self.emb.weight, std=0.02)
        with torch.no_grad():                       # 空格 embedding 恒 0
            self.emb.weight[EMPTY_IDX].zero_()

        in_ch = emb_dim + ROT_CH + MASK_CH
        self.stem = nn.Sequential(
            nn.Conv2d(in_ch, out_ch, 3, padding=1, bias=False),
            nn.BatchNorm2d(out_ch),
            nn.ReLU(inplace=True),
        )
        self.blocks = nn.Sequential(*[ResBlock(out_ch) for _ in range(n_blocks)])

    def forward(self, items: torch.Tensor, rot: torch.Tensor,
                collision: torch.Tensor, affected: torch.Tensor,
                gem: torch.Tensor, rarity: torch.Tensor,
                strength: torch.Tensor) -> torch.Tensor:
        # items: (B,7,9) long → embedding 图 (B,EMB,7,9)，空格(padding_idx)为 0
        x = self.emb(items).permute(0, 3, 1, 2)
        rot1h = F.one_hot(rot.clamp(0, 3), ROT_CH).permute(0, 3, 1, 2).float()
        rot1h = rot1h * (items != EMPTY_IDX).unsqueeze(1).float()  # 空格旋转通道清零
        x = torch.cat([x, rot1h, collision, affected, gem, rarity, strength], dim=1)
        return self.blocks(self.stem(x))


class WinRateModel(nn.Module):
    """双塔 + 逐格积/差/和交互 + MLP → 胜率 sigmoid。

    inter_blocks > 0 时在 1x1 交互卷积后追加同宽 3x3 残差块，让交互图在
    池化前看到邻域结构（相邻物品的局部配合/抵消）；参数量每块约 41K。
    """

    def __init__(self, n_items: int, n_blocks: int = N_RES_BLOCKS,
                 inter_blocks: int = INTER_BLOCKS, emb_dim: int = EMB_DIM,
                 tower_ch: int = TOWER_CH):
        super().__init__()
        self.tower = Tower(n_items, emb_dim=emb_dim, out_ch=tower_ch,
                           n_blocks=n_blocks)
        # 线性先验分支（train 侧 numpy LR 拟合后冻结；[w(3*SCALAR_DIM), b]）
        self.register_buffer("prior_w", torch.zeros(3 * SCALAR_DIM + 1))
        # 逐格积/差/和 → 1x1 卷积交互
        self.inter = nn.Sequential(
            nn.Conv2d(3 * tower_ch, INTER_CH, 1, bias=False),
            nn.BatchNorm2d(INTER_CH),
            nn.ReLU(inplace=True),
        )
        self.inter_res = (nn.Sequential(*[ResBlock(INTER_CH)
                                          for _ in range(inter_blocks)])
                          if inter_blocks else nn.Identity())
        pooled = 2 * INTER_CH + 4 * tower_ch   # 交互图与两塔特征各 avg+max
        self.mlp = nn.Sequential(
            nn.Linear(pooled + 3 * SCALAR_DIM, 128),   # [p_aux, o_aux, p_aux−o_aux]
            nn.ReLU(inplace=True),
            nn.Dropout(MLP_DROPOUT),
            nn.Linear(128, 64),
            nn.ReLU(inplace=True),
            nn.Linear(64, 1),
        )

    def _pool2(self, x: torch.Tensor) -> torch.Tensor:
        return torch.cat([F.adaptive_avg_pool2d(x, 1).flatten(1),
                          F.adaptive_max_pool2d(x, 1).flatten(1)], dim=1)

    def forward(self, p: Dict[str, torch.Tensor], o: Dict[str, torch.Tensor]) -> torch.Tensor:
        # 物品强度通道按塔翻转符号：玩家塔 +s̃（对该阵容有利），对手塔 −s̃
        fp = self.tower(p["items"], p["rot"], p["collision"], p["affected"],
                        p["gem"], p["rarity"], p["strength"])
        fo = self.tower(o["items"], o["rot"], o["collision"], o["affected"],
                        o["gem"], o["rarity"], -o["strength"])
        inter = torch.cat([fp * fo, fp - fo, fp + fo], dim=1)
        z = self._pool2(self.inter_res(self.inter(inter)))
        aux = torch.cat([p["scalars"], o["scalars"],
                         p["scalars"] - o["scalars"]], dim=1)
        vec = torch.cat([z, self._pool2(fp), self._pool2(fo), aux], dim=1)
        logit = self.mlp(vec).squeeze(-1)
        if self.prior_w.abs().sum() > 0:            # 冻结的线性先验（LR 残差学习）
            logit = logit + aux @ self.prior_w[:-1] + self.prior_w[-1]
        return torch.sigmoid(logit)


def count_parameters(model: nn.Module) -> int:
    return sum(p.numel() for p in model.parameters() if p.requires_grad)


def load_item_db(path=None) -> dict:
    with open(path or ITEM_DB_DEFAULT, encoding="utf-8") as f:
        return json.load(f)
