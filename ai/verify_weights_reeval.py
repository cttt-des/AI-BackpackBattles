# -*- coding: utf-8 -*-
"""verify_weights_reeval.py — 只读复核脚本（评审复核用，不写任何仓库文件）。

用 ai/weights.pt 内存储的 val/test 下标 + data/dataset_v1.jsonl + canonical
compute_item_te（TE_VAL_FRAC=TE_TEST_FRAC=0.1, smoothing=20, seed=42），按
ai/train.py main() 的同一口径重建缓存张量，实测当前交付权重的 val/test
Spearman；并逐位核对：
  1) group_split3(dataset_v1.jsonl, seed=42, 0.1/0.1) 是否逐位复现存储下标；
  2) TE 统计的 train 侧是否 == 主切分 train（TE 未掺 val/test）。
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import torch                                    # noqa: E402
from torch.utils.data import DataLoader         # noqa: E402
from ai import model as M                       # noqa: E402
from ai.encoding import encode_lineup           # noqa: E402
from ai import train as T                       # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

ck = torch.load(os.path.join(REPO, "ai", "weights.pt"),
                map_location="cpu", weights_only=False)
cfg = ck["config"]
stored_val, stored_test = list(cfg["val_idx"]), list(cfg["test_idx"])
print("config.best_epoch =", repr(cfg["best_epoch"]), " config.seed =", cfg["seed"],
      " stored val/test n =", len(stored_val), len(stored_test))

pairs = T.load_pairs(os.path.join(REPO, "data", "dataset_v1.jsonl"))
item_db = M.load_item_db()
vocab = M.build_item_vocab(item_db)
vocab_index = {n: i for i, n in enumerate(vocab)}
print("pairs:", len(pairs), " vocab:", len(vocab))

# ── 与 main() 完全一致的编码循环（train.py:404-426）──
cache, lineup_ids, lineup_roots, hashes, base_edges = {}, {}, {}, [], []
for p in pairs:
    for side in ("player", "opponent"):
        h = M.lineup_content_hash(p[side])
        if h not in cache:
            enc = encode_lineup(p[side], item_db)
            cache[h] = T._to_tensor_group(
                M.lineup_tensors(enc, vocab_index, p[side], item_db))
            lineup_ids[h] = set(enc["root_ids"])
            lineup_roots[h] = list(enc["root_ids"])
    hp, ho = M.lineup_content_hash(p["player"]), M.lineup_content_hash(p["opponent"])
    hashes.append((hp, ho))
    base_edges.append((hp, M.lineup_base_hash(p["player"])))
    base_edges.append((ho, M.lineup_base_hash(p["opponent"])))
print("unique lineups:", len(cache))

# ── 核对 1：切分可复现性（train.py:431-433 同参调用）──
fresh_train, fresh_val, fresh_test = T.group_split3(
    len(pairs), hashes, 0.1, 0.1, 42, extra_edges=base_edges)
print("fresh split sizes (train/val/test):",
      len(fresh_train), len(fresh_val), len(fresh_test))
print("fresh val  == stored val :", fresh_val == stored_val)
print("fresh test == stored test:", fresh_test == stored_test)
sv, st, sf = set(stored_val), set(stored_test), set(fresh_train)
print("stored val/test/train 两两不相交:",
      not (sv & st) and not (sv & sf) and not (st & sf))

# ── 核对 2：TE 统计 train 侧口径（train.py:188-189 同参调用）──
s_tilde, te_by_name = T.compute_item_te(
    pairs, item_db, vocab_index, 42, 0.1, 0.1, 20.0,
    precomputed=(hashes, base_edges, lineup_ids))
te_train, _, _ = T.group_split3(len(pairs), hashes, 0.1, 0.1, 42,
                                extra_edges=base_edges)
print("TE train side == main train split:", te_train == fresh_train)
print("TE train 与 val/test 无交集:",
      not (set(te_train) & (set(fresh_val) | set(fresh_test))))
n_cov = sum(1 for v in s_tilde[M.PAD_VOCAB:] if v != 0.0)
print("TE coverage:", n_cov, "/", len(vocab) - M.PAD_VOCAB)

# ── 强度通道注入（train.py:466-472 同口径）──
for h, t in cache.items():
    t["strength"] = torch.from_numpy(s_tilde[t["items"].numpy()])[None]
    t["scalars"][M.SCALAR_DIM - 1] = float(
        sum(te_by_name.get(n, 0.0) for n in lineup_roots[h]))

model = M.WinRateModel(n_items=len(vocab), n_blocks=cfg["res_blocks"],
                       inter_blocks=cfg["inter_blocks"],
                       emb_dim=cfg["emb_dim"], tower_ch=cfg["tower_ch"])
model.load_state_dict(ck["state_dict"])
device = torch.device("cpu")


# 与 main() 相同的 collate（train.py:481-485；y 强制 float32）
collate = lambda b: {                           # noqa: E731
    "p": {k: torch.stack([s["p"][k] for s in b]) for k in b[0]["p"]},
    "o": {k: torch.stack([s["o"][k] for s in b]) for k in b[0]["o"]},
    "y": torch.tensor([s["y"] for s in b], dtype=torch.float32),
}


def make_dl(idx):
    ds = T.PairDataset([(cache[hashes[i][0]], cache[hashes[i][1]],
                         pairs[i]["y"]) for i in idx])
    return DataLoader(ds, batch_size=128, shuffle=False, collate_fn=collate)


vl, vp, vy = T.evaluate(model, make_dl(stored_val), device)
tl, tp, ty = T.evaluate(model, make_dl(stored_test), device)
print("VAL  n=%d bce=%.4f spearman=%.6f" % (len(vy), vl, T.spearman(vy, vp)))
print("TEST n=%d bce=%.4f spearman=%.6f" % (len(ty), tl, T.spearman(ty, tp)))
