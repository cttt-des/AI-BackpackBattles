# -*- coding: utf-8 -*-
"""临时超参扫描驱动：只看 val 指标选型，AI_TRAIN_SKIP_TEST=1 保证 test 零触碰。"""
import os, re, subprocess, sys, time

os.environ["AI_TRAIN_SKIP_TEST"] = "1"
CONFIGS = [
    ("base",            []),
    ("ib2",             ["--inter-blocks", "2"]),
    ("ib3",             ["--inter-blocks", "3"]),
    ("ls08",            ["--label-shrink", "0.8"]),
    ("ls08_ib2",        ["--label-shrink", "0.8", "--inter-blocks", "2"]),
    ("ls06",            ["--label-shrink", "0.6"]),
    ("ls08_ib2_wd",     ["--label-shrink", "0.8", "--inter-blocks", "2", "--weight-decay", "1e-4"]),
    ("ls08_ib2_do",     ["--label-shrink", "0.8", "--inter-blocks", "2", "--dropout", "0.25"]),
    ("ls08_ib2_cos",    ["--label-shrink", "0.8", "--inter-blocks", "2", "--scheduler", "cosine", "--lr", "2e-3"]),
    ("ls08_ib2_te60",   ["--label-shrink", "0.8", "--inter-blocks", "2", "--te-smoothing", "60"]),
    ("ls08_ib2_lr5_e15",["--label-shrink", "0.8", "--inter-blocks", "2", "--lr", "5e-4", "--epochs", "15"]),
]

def run(name, extra):
    t0 = time.time()
    r = subprocess.run(
        [sys.executable, "ai/train.py", "--data", "data/dataset_v1.jsonl",
         "--distill", "1", "--out", f"ai/_sweep_{name}.pt"] + extra,
        capture_output=True, text=True, timeout=900)
    out = r.stdout
    best = 0.0
    for m in re.finditer(r"val loss=([\d.]+) rho=([\d.]+)", out):
        best = max(best, float(m.group(2)))
    mt = re.search(r"topk-average:.*val rho=([\d.]+) \(single best ([\d.]+) @ep(-?\d+)\)", out)
    topk = float(mt.group(1)) if mt else float("nan")
    single = float(mt.group(2)) if mt else best
    print(f"{name:18s} best-epoch-val-rho={best:.4f}  single={single:.4f}  topk3={topk:.4f}  ({time.time()-t0:.0f}s)", flush=True)
    if r.returncode != 0:
        print(f"  !! {name} failed:\n{r.stderr[-800:]}", flush=True)

for name, extra in CONFIGS:
    run(name, extra)
print("SWEEP DONE")
