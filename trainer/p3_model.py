# -*- coding: utf-8 -*-
"""p3_model.py — P3 学习加速·差分偏好模型（规划 §7 P3）

模型：Ridge 回归（numpy 闭式解），y = Δ̂ 实测（候选 vs 基准的 CRN 配对胜差），
X = 完整布局的差分特征（cand − base，规划 §7 P3-2「输入必须是完整布局」）。

诚实评估：
  * 留一基准（leave-one-base-out）交叉验证——报告「同基准内候选排序」的
    Spearman 相关（用途是 top-K 初筛，排序力比 R² 更贴决策）。
  * 覆盖边权校准：只用 ΔB_edges 拟合，对照 layout_rules.WEIGHTS 推断初值。
"""
from __future__ import annotations

import json
import math
import os
import sys

import numpy as np

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

DROP_KEYS = {"A", "B"}  # 绝对总量已含在差分里；A/B 差分与 B_edges 共线，留边权即可


def load_dataset(path: str):
    rows = []
    with open(path, encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if line:
                rows.append(json.loads(line))
    return rows


def build_matrix(rows):
    keys = []
    seen = set()
    for r in rows:
        for k in r["diff"]:
            if k not in seen and k not in DROP_KEYS:
                seen.add(k)
                keys.append(k)
    keys.sort()
    X = np.array([[r["diff"].get(k, 0.0) for k in keys] for r in rows], dtype=float)
    y = np.array([r["delta"] for r in rows], dtype=float)
    bi = np.array([r["bi"] for r in rows], dtype=int)
    return X, y, bi, keys


def ridge_fit(X, y, alpha=1.0, standardize=True):
    mu = X.mean(axis=0)
    sd = X.std(axis=0)
    sd[sd < 1e-9] = 1.0
    Z = (X - mu) / sd if standardize else X.copy()
    d = Z.shape[1]
    A = Z.T @ Z + alpha * np.eye(d)
    w = np.linalg.solve(A, Z.T @ y)
    b = y.mean() - (Z.mean(axis=0) @ w) if standardize else 0.0
    return {"w": w, "b": b, "mu": mu, "sd": sd, "standardize": standardize}


def ridge_predict(model, X):
    Z = (X - model["mu"]) / model["sd"] if model["standardize"] else X
    return Z @ model["w"] + model["b"]


def spearman(a, b):
    """无并列秩的 Spearman（并列极少，直接秩相关）。"""
    n = len(a)
    if n < 3:
        return float("nan")
    ra = np.argsort(np.argsort(a)).astype(float)
    rb = np.argsort(np.argsort(b)).astype(float)
    ra -= ra.mean()
    rb -= rb.mean()
    den = math.sqrt((ra @ ra) * (rb @ rb))
    return float((ra @ rb) / den) if den > 0 else float("nan")


def main():
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("--data", default="trainer/p3_dataset.jsonl")
    ap.add_argument("--alpha", type=float, default=1.0)
    ap.add_argument("--out", default="trainer/p3_model.json")
    args = ap.parse_args()

    rows = load_dataset(os.path.join(ROOT, args.data))
    print(f"dataset: {len(rows)} samples from {len(set(r['bi'] for r in rows))} bases")
    X, y, bi, keys = build_matrix(rows)

    # ── 留一基准 CV ──
    bases = sorted(set(bi.tolist()))
    cors, all_pred, all_true = [], [], []
    for b in bases:
        te = bi == b
        tr = ~te
        if tr.sum() < 20 or te.sum() < 5:
            continue
        m = ridge_fit(X[tr], y[tr], alpha=args.alpha)
        pred = ridge_predict(m, X[te])
        c = spearman(pred, y[te])
        cors.append(c)
        all_pred.extend(pred.tolist())
        all_true.extend(y[te].tolist())
        print(f"  base {b}: n={int(te.sum())} spearman={c:+.3f} "
              f"(y mean={y[te].mean():+.4f})")
    print(f"LOBO spearman: mean={np.nanmean(cors):+.3f} "
          f"per-base={['%+.3f' % c for c in cors]}")
    print(f"global pred-true spearman: {spearman(all_pred, all_true):+.3f}")

    # ── 全量拟合 + 边权校准 ──
    m = ridge_fit(X, y, alpha=args.alpha)
    wmap = {k: round(float(w), 4) for k, w in zip(keys, m["w"]) if abs(w) > 1e-6}
    top = sorted(wmap.items(), key=lambda kv: -abs(kv[1]))[:20]
    print("top-20 |weights|:")
    for k, w in top:
        print(f"  {k:28s} {w:+.4f}")
    # 覆盖边权校准（只用 e_* 特征）
    ekeys = [k for k in keys if k.startswith("e_")]
    if ekeys:
        Xe = X[:, [keys.index(k) for k in ekeys]]
        me = ridge_fit(Xe, y, alpha=args.alpha)
        cal = {k: round(float(w), 3) for k, w in zip(ekeys, me["w"]) if abs(w) > 1e-4}
        print("edge-weight calibration (ΔB_edges → Δwr):")
        for k, w in sorted(cal.items(), key=lambda kv: -abs(kv[1])):
            print(f"  {k:28s} {w:+.3f}")
    else:
        cal = {}
    out = {
        "keys": keys, "w": m["w"].tolist(), "b": float(m["b"]),
        "mu": m["mu"].tolist(), "sd": m["sd"].tolist(),
        "alpha": args.alpha, "n": len(rows),
        "lobo_spearman_mean": float(np.nanmean(cors)),
        "lobo_spearman_per_base": cors,
        "edge_weights": cal,
        "top_weights": dict(top),
    }
    with open(os.path.join(ROOT, args.out), "w", encoding="utf-8") as f:
        json.dump(out, f, ensure_ascii=False, indent=1)
    print("saved ->", args.out)


if __name__ == "__main__":
    main()
