# -*- coding: utf-8 -*-
"""oracle_fight.gd 全链重建（Write 锚→逐事件，cutoff=桩前）。"""
import json
import os
import glob
import collections

ROOT = r"C:/Users/Windows/.zcode/cli/artifacts"
REPO = r"D:\文件资料\学习\自动背包AI"
CUTOFF = "2026-10-20T00:00"

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
            p = (fe.get("path") or "").replace("\\", "/").lower()
            if p.endswith("oracle/oracle_fight.gd") and t < CUTOFF:
                evs.append((t, j.get("toolName"), fe))
evs.sort(key=lambda e: e[0])
print("桩前事件数:", len(evs), "| 首:", evs[0][0][:19], "| 末:", evs[-1][0][:19])

anchor = None
for i in range(len(evs) - 1, -1, -1):
    if evs[i][1] == "Write":
        anchor = i
        break
print("Write 锚:", anchor is not None, "第%d/%d笔" % (anchor, len(evs)) if anchor is not None else "")


def apply_hunks(content, hunks):
    lines = (content or "").splitlines(keepends=True)
    for h in hunks:
        old_start = h["oldStart"] - 1
        old_lines = h["oldLines"]
        new = []
        for ln in h["lines"]:
            if ln.startswith("+"):
                new.append(ln[1:])
            elif ln.startswith("-"):
                continue
            elif ln.startswith(" "):
                new.append(ln[1:])
            else:
                new.append(ln)
        joined = "".join(x if x.endswith(("\n", "\r")) else x + "\n" for x in new)
        lines = lines[:old_start] + [joined] + lines[old_start + old_lines:]
    return "".join(lines)


if anchor is not None:
    content = evs[anchor][2].get("afterContent") or ""
    chain = evs[anchor + 1:]
else:
    raise SystemExit("无 Write 锚")
fail_at = None
for i, (t, tool, fe) in enumerate(chain):
    if tool != "Edit":
        continue
    try:
        content = apply_hunks(content, fe.get("structuredPatch") or [])
    except Exception as exc:
        fail_at = (i, t, str(exc))
        break
print("链式应用:", "完成" if fail_at is None else fail_at)
with open(os.path.join(REPO, "oracle", "oracle_fight.gd"), "w", encoding="utf-8", newline="") as fh:
    fh.write(content)
print("写出长度:", len(content), "行数:", content.count(chr(10)))
