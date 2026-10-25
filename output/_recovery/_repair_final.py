# -*- coding: utf-8 -*-
"""终修：v6 回退基线的受害者用「内容寻址单事件法」重建。"""
import json
import os
import glob
import collections
import py_compile
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
                if rel.lower().startswith(("oracle/", ".zcode/", "dist/", "build/",
                                           "gd_core_probe/", "output/")):
                    continue
                events[rel].append((t, j.get("toolName"), fe))
for rel in events:
    events[rel].sort(key=lambda e: e[0])


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


def git_base(rel):
    r = subprocess.run(["git", "show", "HEAD:" + rel.replace("\\", "/")],
                       capture_output=True, cwd=REPO)
    return r.stdout.decode("utf-8", errors="replace") if r.returncode == 0 else None


fixed = kept = same = 0
for rel in sorted(events):
    p = os.path.join(REPO, rel.replace("/", os.sep))
    if not os.path.exists(p):
        continue
    cur = open(p, encoding="utf-8", errors="replace").read()
    base = git_base(rel)
    t, tool, fe = events[rel][-1]
    try:
        content = (fe.get("afterContent") if tool == "Write"
                   else apply_addr(fe.get("beforeContent"), fe.get("structuredPatch") or []))
        if not content.strip():
            raise ValueError("空")
    except Exception:
        continue
    if content == cur:
        same += 1
        continue
    if content == base and cur == base:
        same += 1
        continue
    # 当前=基线 且 事件版不同 → 修复
    try:
        if rel.endswith(".py"):
            py_compile.compile(p, doraise=True)  # 先验当前可编译（基线版必过）
        tmp = p + ".rec.tmp"
        with open(tmp, "w", encoding="utf-8", newline="") as fh:
            fh.write(content)
        if rel.endswith(".py"):
            py_compile.compile(tmp, doraise=True)
        os.replace(tmp, p)
        fixed += 1
        print("FIXED", rel, "<-", t[:16], tool)
    except Exception as exc:
        try:
            os.remove(tmp)
        except Exception:
            pass
        kept += 1
        print("KEEP ", rel, str(exc)[:50])

print("\n修复:", fixed, "| 保持:", kept, "| 本已同:", same)
