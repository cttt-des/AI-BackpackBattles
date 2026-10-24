# -*- coding: utf-8 -*-
"""oracle/ 全树重建：decompiled_full 基座 + 工件覆盖（桩前版本）+ 工程件。"""
import json
import os
import glob
import shutil
import collections

ROOT = r"C:/Users/Windows/.zcode/cli/artifacts"
REPO = r"D:\文件资料\学习\自动背包AI"
PRE_STUB = "2026-10-20"  # np19 TSNAP 桩首日；此前事件视为 pristine

events = collections.defaultdict(list)
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
            if "/oracle/" in p.replace("\\", "/"):
                rel = "oracle/" + p.split("/oracle/", 1)[1]
                events[rel].append((t, j.get("toolName"), fe))
for rel in events:
    events[rel].sort(key=lambda e: e[0])

print("oracle 工件事件文件数:", len(events))
for rel in sorted(events):
    ts = [t[:10] for t, _, _ in events[rel]]
    print(" ", rel, "事件:", ",".join(ts))


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


def content_at(rel, before):
    """rel 在 before 日期前的最新事件内容；无则 None。"""
    cand = [e for e in events.get(rel, []) if e[0] < before]
    if not cand:
        return None
    t, tool, fe = cand[-1]
    if tool == "Write":
        return fe.get("afterContent")
    return apply_hunks(fe.get("beforeContent"), fe.get("structuredPatch") or [])


# ── 执行重建 ──
DEC = os.path.join(REPO, "decompiled_full")
ORC = os.path.join(REPO, "oracle")
JUNK = ("oracle/offpeak_handoff.md", "oracle/offpeak_np2_report.md",
        "oracle/offpeak_np3_report.md", "oracle/rage_dump_tmp.gd")

# 1) decomp 基座（不覆盖已有事件文件的最终内容，先把整个 decomp 拷进去）
copied = 0
for dirpath, _, files in os.walk(DEC):
    rel_dir = os.path.relpath(dirpath, DEC)
    for fn in files:
        src = os.path.join(dirpath, fn)
        dst = os.path.join(ORC, rel_dir, fn)
        if os.path.normcase(dst) not in {os.path.normcase(os.path.join(REPO, r.replace("/", os.sep))) for r in events}:
            os.makedirs(os.path.dirname(dst), exist_ok=True)
            shutil.copy2(src, dst)
            copied += 1

# 2) 事件文件覆盖（桩前版本）
overlay = []
no_event_pre = []
for rel in sorted(events):
    if rel in JUNK:
        continue
    content = content_at(rel, "2026-10-20T00:00")
    if content is None:
        no_event_pre.append(rel)
        continue
    # 原大小写路径：工件 path 字段
    orig_rel = None
    for d2 in events[rel]:
        pass
    # 直接用小写匹配盘上文件
    dst = os.path.join(REPO, rel.replace("/", os.sep))
    hit = None
    if os.path.exists(dst):
        hit = dst
    else:
        for cand in glob.glob(os.path.join(REPO, "*")):
            pass
    os.makedirs(os.path.dirname(dst), exist_ok=True)
    with open(dst, "w", encoding="utf-8", newline="") as fh:
        fh.write(content)
    overlay.append(rel)

print("\n基座拷贝:", copied, "| 事件覆盖:", len(overlay), "| 无桩前事件(留基座/工程件另查):", no_event_pre)
print("oracle/ .gd 总数:", sum(1 for _, _, fs in os.walk(ORC) for f in fs if f.endswith(".gd")))
