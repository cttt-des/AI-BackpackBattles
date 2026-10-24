# -*- coding: utf-8 -*-
"""定点调试：verify_oracle.py 最新工件事件的单补丁应用，找应用器 bug。"""
import json
import os
import glob

ROOT = r"C:/Users/Windows/.zcode/cli/artifacts"
REPO_N = "d:/文件资料/学习/自动背包ai/"
TARGET = "tools/verify_oracle.py"
CUTOFF = "2026-10-24T07:30:00"

evs = []
for d in sorted(os.listdir(ROOT)):
    dp = os.path.join(ROOT, d)
    if not os.path.isdir(dp):
        continue
    for f in glob.glob(os.path.join(dp, "*.json")):
        try:
            j = json.load(open(f, encoding="utf-8"))
        except Exception:
            continue
        t = j.get("createdAt") or ""
        for fe in j.get("files", []) or []:
            if (fe.get("path") or "").replace("\\", "/").lower().endswith(TARGET) and t < CUTOFF:
                evs.append((t, j.get("toolName"), fe, d))
evs.sort(key=lambda e: e[0])
print("事件数:", len(evs))
for t, tool, fe, d in evs[-4:]:
    print(" ", t[:19], tool, "patch hunks:", len(fe.get("structuredPatch") or []))

t, tool, fe, d = evs[-1]
before = fe.get("beforeContent") or ""
hunks = fe.get("structuredPatch") or []
print("\n最新事件:", t[:19], tool, "| before 长度:", len(before), "| hunks:", len(hunks))

# 逐 hunk 检验：oldStart/oldLines 与删除行上下文是否吻合
lines = before.splitlines(keepends=True)
print("before 行数:", len(lines))
for i, h in enumerate(hunks):
    old_start, old_lines = h["oldStart"], h["oldLines"]
    dels = [ln for ln in h["lines"] if ln.startswith("-")]
    seg = lines[old_start - 1:old_start - 1 + old_lines]
    ok = len(dels) == old_lines and all(
        (dels[k][1:].rstrip("\r\n") == seg[k].rstrip("\r\n")) if k < len(seg) else False
        for k in range(max(len(dels), len(seg))))
    print("hunk%d oldStart=%d oldLines=%d dels=%d seg=%d %s"
          % (i, old_start, old_lines, len(dels), len(seg), "OK" if ok else "MISMATCH"))
    if not ok and i < 3:
        print("   dels前2:", [x[:60] for x in dels[:2]])
        print("   seg 前2:", [x[:60] for x in seg[:2]])
