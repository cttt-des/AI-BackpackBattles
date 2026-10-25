# -*- coding: utf-8 -*-
"""重放 v7：全部 .gd 事件文件用内容寻址法重建（针对 git stash pop 部分还原的伤）。"""
import json
import os
import glob
import collections
import subprocess

ROOT = r"C:/Users/Windows/.zcode/cli/artifacts"
REPO = r"D:\文件资料\学习\自动背包AI"
CUTOFF = "2026-10-24T07:30:00"


def norm(p):
    return p.replace("\\", "/").lower()


REPO_N = norm(REPO) + "/"
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
            p = norm(fe.get("path") or "")
            if p.startswith(REPO_N) and t < CUTOFF:
                rel = fe.get("path").replace("\\", "/").split("自动背包AI/", 1)[-1]
                if rel.lower().endswith(".gd") and not rel.lower().startswith(
                        ("oracle/", ".zcode/", "gd_core_probe/")):
                    events[rel].append((t, j.get("toolName"), fe))
for rel in events:
    events[rel].sort(key=lambda e: e[0])
print(".gd 事件文件数:", len(events))


def strip_eol(s):
    return s.rstrip("\r\n")


def apply_addr(content, hunks):
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
        for delta in (0, -1, 1, -2, 2, -3, 3):
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
            raise ValueError("定位失败")
        lines = lines[:hit] + [x + eol for x in new_norm] + lines[hit + len(old_norm):]
    return "".join(lines)


fixed = same = fail = 0
fail_list = []
for rel in sorted(events):
    t, tool, fe = events[rel][-1]
    try:
        content = (fe.get("afterContent") if tool == "Write"
                   else apply_addr(fe.get("beforeContent"), fe.get("structuredPatch") or []))
        if not content.strip():
            raise ValueError("空")
    except Exception as exc:
        fail += 1
        fail_list.append((rel, str(exc)[:40]))
        continue
    p = os.path.join(REPO, rel.replace("/", os.sep))
    os.makedirs(os.path.dirname(p), exist_ok=True)
    cur = open(p, encoding="utf-8", errors="replace").read() if os.path.exists(p) else ""
    if content == cur:
        same += 1
        continue
    open(p, "w", encoding="utf-8", newline="").write(content)
    fixed += 1

print("重写:", fixed, "| 本已同:", same, "| 失败:", fail)
for r, e in fail_list[:8]:
    print("FAIL", r, e)

# label_rng 声明检查（era 内核必有）
for f in ("gd_core/CoreContext.gd", "gd_core_test/gd_core/CoreContext.gd"):
    fp = os.path.join(REPO, f)
    src = open(fp, encoding="utf-8", errors="replace").read()
    if "var label_rng_enabled" not in src:
        src = src.replace(
            "var below_master := false",
            "var below_master := false\nvar label_rng_enabled := true", 1)
        if "var label_rng_enabled" not in src:
            # 兜底：插在 class 体首行 var 区（_init 前）
            src = src.replace("func _init", "var label_rng_enabled := true\n\nfunc _init", 1)
        open(fp, "w", encoding="utf-8", newline="").write(src)
        print("补声明:", f)
    else:
        print("已有声明:", f)
