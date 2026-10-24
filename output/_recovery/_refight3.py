# -*- coding: utf-8 -*-
"""oracle_fight.gd v3：内容寻址 hunk 应用（旧跨度串匹配定位）+ 桩前末笔单事件。"""
import json
import os
import glob

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
t, tool, fe = evs[-1]
print("桩前末笔:", t[:19], tool)


def strip_eol(s):
    return s.rstrip("\r\n")


def apply_addr(content, hunks):
    lines = (content or "").splitlines(keepends=True)
    eol = "\r\n" if content.find("\r\n") >= 0 else "\n"
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
        guess = h["oldStart"] - 1
        hit = None
        for delta in (0, -1, 1, -2, 2, -3, 3):
            s = guess + delta
            if 0 <= s and s + len(old_norm) <= len(lines):
                if [strip_eol(l) for l in lines[s:s + len(old_norm)]] == old_norm:
                    hit = s
                    break
        if hit is None:
            # 全局搜索
            flat = [strip_eol(l) for l in lines]
            for s in range(len(flat) - len(old_norm) + 1):
                if flat[s:s + len(old_norm)] == old_norm:
                    hit = s
                    break
        if hit is None:
            raise ValueError("旧跨度串定位失败 oldStart=%d" % h["oldStart"])
        lines = lines[:hit] + [x + eol for x in new_norm] + lines[hit + len(old_norm):]
    return "".join(lines)


if tool == "Write":
    content = fe.get("afterContent")
else:
    content = apply_addr(fe.get("beforeContent"), fe.get("structuredPatch") or [])
with open(os.path.join(REPO, "oracle", "oracle_fight.gd"), "w", encoding="utf-8", newline="") as fh:
    fh.write(content)
print("写出:", len(content), "字节 /", content.count("\n"), "行")
