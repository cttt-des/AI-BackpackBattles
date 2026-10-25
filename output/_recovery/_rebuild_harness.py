# -*- coding: utf-8 -*-
"""OracleAlignBattle.gd 内容寻址全链重建：Write 锚 → 逐事件内容匹配应用。"""
import json
import os
import glob

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
            if (fe.get("path") or "").replace("\\", "/").lower().endswith(
                    "gd_core_test/oraclealignbattle.gd") and t < CUTOFF:
                evs.append((t, j.get("toolName"), fe))
evs.sort(key=lambda e: e[0])
print("事件数:", len(evs))

anchor = None
for i in range(len(evs) - 1, -1, -1):
    if evs[i][1] == "Write":
        anchor = i
        break
print("Write 锚:", anchor is not None and ("第%d笔 %s" % (anchor + 1, evs[anchor][0][:19])))


def strip_eol(s):
    return s.rstrip("\r\n")


def apply_addr(content, hunks, strict=False):
    lines = (content or "").splitlines(keepends=True)
    eol = "\r\n" if (content or "").find("\r\n") >= 0 else "\n"
    for h in hunks:
        old_part, new_part = [], []
        for ln in h["lines"]:
            if ln.startswith("-"):
                old_part.append(ln[1:])
            elif ln.startswith("+"):
                new_part.append(ln[1:])
            elif ln.startswith(" "):
                old_part.append(ln[1:])
                new_part.append(ln[1:])
            else:
                old_part.append(ln)
                new_part.append(ln)
        old_norm = [strip_eol(x) for x in old_part]
        new_norm = [strip_eol(x) for x in new_part]
        hit = None
        guess = h["oldStart"] - 1
        for delta in (0, -1, 1, -2, 2, -3, 3, 5, -5, 10, -10):
            s = guess + delta
            if 0 <= s and s + len(old_norm) <= len(lines):
                if [strip_eol(l) for l in lines[s:s + len(old_norm)]] == old_norm:
                    hit = s
                    break
        if hit is None:
            flat = [strip_eol(l) for l in lines]
            for s in range(len(flat) - len(old_norm) + 1):
                if flat[s:s + len(old_norm)] == old_norm:
                    hit = s
                    break
        if hit is None:
            raise ValueError("hunk 内容定位失败 oldStart=%d 首行=%r" % (
                h["oldStart"], (h["lines"][0] if h["lines"] else "")[:60]))
        lines = lines[:hit] + [x + eol for x in new_norm] + lines[hit + len(old_norm):]
    return "".join(lines)


content = evs[anchor][2].get("afterContent")
misses = []
for i, (t, tool, fe) in enumerate(evs[anchor + 1:]):
    if tool != "Edit":
        continue
    try:
        content = apply_addr(content, fe.get("structuredPatch") or [])
    except Exception as exc:
        misses.append((t, str(exc)[:90]))
print("链式应用完成 | 失败 hunk:", len(misses))
for t, m in misses[:10]:
    print("MISS", t[:19], m)

out = os.path.join(REPO, "gd_core_test", "OracleAlignBattle.gd")
open(out, "w", encoding="utf-8", newline="").write(content)
print("写出:", len(content), "字节 /", content.count("\n"), "行")
