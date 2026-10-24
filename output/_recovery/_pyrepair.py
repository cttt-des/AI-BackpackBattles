# -*- coding: utf-8 -*-
"""重放文件语法校验+自动修复：py_compile 全部重放 .py；失败者回 git 基线后重链工件；
再失败则留基线版并列入清单。gd_core_py 已删除待 gd_to_py 再生，跳过。"""
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
                orig = fe.get("path")
                rel = orig.replace("\\", "/").split("自动背包AI/", 1)[-1]
                events[rel].append((t, j.get("toolName"), fe))
for rel in events:
    events[rel].sort(key=lambda e: e[0])


def read_base(rel):
    r = subprocess.run(["git", "show", "HEAD:" + rel.replace("\\", "/")],
                       capture_output=True, cwd=REPO)
    return r.stdout.decode("utf-8", errors="replace") if r.returncode == 0 else None


def split_lines(s):
    return s.splitlines(keepends=True)


def apply_hunks(content, hunks, strict_ctx=False):
    lines = split_lines(content)
    out, pos = [], 0
    for h in hunks:
        old_start, old_lines = h["oldStart"] - 1, h["oldLines"]
        if old_start < pos:
            raise ValueError("重叠")
        out.extend(lines[pos:old_start])
        if strict_ctx:
            dels = [ln[1:].rstrip("\r\n") for ln in h["lines"] if ln.startswith("-")]
            seg = [l.rstrip("\r\n") for l in lines[old_start:old_start + len(dels)]]
            if dels != seg:
                raise ValueError("ctx失配@%d" % h["oldStart"])
        adds = "".join((ln[1:] if ln[:1] in "+ " else ln) for ln in h["lines"]
                       if not ln.startswith("-"))
        if adds and not adds.endswith("\n"):
            adds += "\n"
        out.append(adds)
        pos = old_start + old_lines
    out.extend(lines[pos:])
    return "".join(out)


def chain_content(rel, anchor_content):
    """从锚点（最近 Write afterContent 或基线）依序应用 Edit。"""
    evs = events[rel]
    idx = None
    for i in range(len(evs) - 1, -1, -1):
        if evs[i][1] == "Write":
            idx = i
            break
    if idx is not None:
        content = evs[idx][2].get("afterContent") or ""
        rest = evs[idx + 1:]
    else:
        content = anchor_content
        rest = evs
    for t, tool, fe in rest:
        if tool == "Edit":
            if content is None:
                raise ValueError("None链")
            content = apply_hunks(content, fe.get("structuredPatch") or [])
    return content


checked = fixed = kept_base = hard = 0
hard_list = []
for rel in sorted(events):
    if not rel.endswith(".py") or rel.startswith(("gd_core_py/", "output/")):
        continue
    p = os.path.join(REPO, rel.replace("/", os.sep))
    if not os.path.exists(p):
        continue
    checked += 1
    ok = True
    try:
        py_compile.compile(p, doraise=True)
    except Exception:
        ok = False
    if ok:
        continue
    # 损坏：回基线重链
    base = read_base(rel)
    if base is None:
        hard_list.append((rel, "无基线且损坏"))
        hard += 1
        continue
    try:
        content = chain_content(rel, base)
        with open(p, "w", encoding="utf-8", newline="") as fh:
            fh.write(content)
        py_compile.compile(p, doraise=True)
        fixed += 1
    except Exception:
        with open(p, "w", encoding="utf-8", newline="") as fh:
            fh.write(base)
        try:
            py_compile.compile(p, doraise=True)
            kept_base += 1
            hard_list.append((rel, "回退基线版"))
        except Exception:
            hard_list.append((rel, "基线也坏(?!?)"))
            hard += 1

print("py 校验:", checked, "| 修复重链:", fixed, "| 回退基线:", kept_base, "| 硬伤:", hard)
for rel, why in hard_list:
    print("HARD", rel, why)
