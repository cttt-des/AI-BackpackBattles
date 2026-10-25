# -*- coding: utf-8 -*-
"""临时验证：部署口径（placer.Scorer.tensors 同构）重载权重的 val 复现。"""
import sys

sys.path.insert(0, '.')
import numpy as np
import torch

from ai import model as M
from ai.train import load_pairs, spearman, evaluate
from ai.encoding import encode_lineup
from ai.placer import compute_te
from torch.utils.data import DataLoader

item_db = M.load_item_db()
vocab = M.build_item_vocab(item_db)
vi = {n: i for i, n in enumerate(vocab)}
ck = torch.load('ai/weights.pt', map_location='cpu', weights_only=False)
cfg = ck['config']
pairs = load_pairs('data/dataset_v1.jsonl')
s_tilde, te_by_name, note = compute_te('data/dataset_v1.jsonl', item_db, vi,
                                       cfg['seed'], 0.1, 20.0)
m = M.WinRateModel(n_items=cfg['n_items'], n_blocks=cfg['res_blocks'],
                   inter_blocks=cfg.get('inter_blocks', 0),
                   emb_dim=cfg.get('emb_dim', M.EMB_DIM),
                   tower_ch=cfg.get('tower_ch', M.TOWER_CH))
m.load_state_dict(ck['state_dict'])
m.eval()

samples = []
for i in cfg['val_idx']:
    def T(lu):
        # 与 placer.Scorer.tensors 同构：encode_lineup + lineup_tensors(…, db)
        t = dict(M.lineup_tensors(encode_lineup(lu, item_db), vi, lu, item_db))
        t['strength'] = (s_tilde[t['items']] if s_tilde is not None
                         else np.zeros((7, 9), np.float32))[None]
        t['scalars'][M.SCALAR_DIM - 1] = float(
            sum(te_by_name.get(n, 0.0) for n in encode_lineup(lu, item_db)['root_ids']))
        return t
    samples.append((T(pairs[i]['player']), T(pairs[i]['opponent']), pairs[i]['y']))

collate = lambda b: {
    'p': {k: torch.stack([torch.as_tensor(s[0][k]) for s in b]) for k in b[0][0]},
    'o': {k: torch.stack([torch.as_tensor(s[1][k]) for s in b]) for k in b[0][1]},
    'y': torch.tensor([s[2] for s in b], dtype=torch.float32)}
dl = DataLoader(samples, batch_size=128, shuffle=False, collate_fn=collate)
loss, ps, ys = evaluate(m, dl, torch.device('cpu'))
print('部署口径重载 val Spearman =', round(spearman(ys, ps), 6),
      '（训练期选中 val = 0.6322）')
