# -*- coding: utf-8 -*-
"""收尾修复：①enrich_classes.py np9 版单事件重建；②flicker 工具扫描源检查；
③WEBD/The Lovers connector=True 手补。"""
import json
import os
import glob
import py_compile

ROOT = r"C:/Users/Windows/.zcode/cli/artifacts"
REPO = r"D:\文件资料\学习\自动背包AI"
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
            p = (fe.get("path") or "").replace("\\", "/").lower()
            if p.endswith("tools/enrich_classes.py") and t < CUTOFF:
                evs.append((t, j.get("toolName"), fe))
evs.sort(key=lambda e: e[0])
print("enrich_classes 事件数:", len(evs))
for t, tool, fe in evs[-3:]:
    print(" ", t[:19], tool, "patch:", len(fe.get("structuredPatch") or []),
          "before:", len(fe.get("beforeContent") or ""))


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


if evs:
    t, tool, fe = evs[-1]
    if tool == "Write":
        content = fe.get("afterContent") or ""
    else:
        content = apply_hunks(fe.get("beforeContent"), fe.get("structuredPatch") or [])
    dest = os.path.join(REPO, "tools", "enrich_classes.py")
    with open(dest, "w", encoding="utf-8", newline="") as fh:
        fh.write(content)
    try:
        py_compile.compile(dest, doraise=True)
        print("enrich_classes 重建+编译 OK, 长度:", len(content))
    except Exception as exc:
        print("重建后编译失败:", exc)

# WEBD / The Lovers connector=True
bj = os.path.join(REPO, "assets", "battle_items.json")
d = json.load(open(bj, encoding="utf-8"))
it = d["items"]
flips = []
for k, v in it.items():
    if v.get("connector_ready_roll") is False and ("Lovers" in k or "WEBD" in k.upper()):
        v["connector_ready_roll"] = True
        flips.append(k)
json.dump(d, open(bj, "w", encoding="utf-8"), ensure_ascii=False, indent=1)
print("connector 手补翻转:", flips)
