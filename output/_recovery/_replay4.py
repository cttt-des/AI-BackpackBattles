# -*- coding: utf-8 -*-
"""重放 v4：标准 unified-diff hunk 语义，全链（基线/Write 锚→逐事件），编译校验。
用于修复此前回退基线的文件与其余 .py。"""
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
                events[rel].append((t, j.get("toolName"), fe))
for rel in events:
    events[rel].sort(key=lambda e: e[0])


def read_base(rel):
    r = subprocess.run(["git", "show", "HEAD:" + rel.replace("\\", "/")],
                       capture_output=True, cwd=REPO)
    return r.stdout.decode("utf-8", errors="replace") if r.returncode == 0 else None


def nl(s):
    """统一行尾视图：splitlines(keepends) 但空串安全。"""
    return s.splitlines(keepends=True) if s else []


def apply_hunk(lines, h):
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
            new.append(ln)  # 序列化器剥掉空上下文行前缀的情形
    joined = "".join(x if x.endswith(("\n", "\r")) else x + "\n" for x in new)
    return lines[:old_start] + [joined] + lines[old_start + old_lines:]


def rebuild(rel):
    evs = events[rel]
    anchor = None
    for i in range(len(evs) - 1, -1, -1):
        if evs[i][1] == "Write":
            anchor = i
            break
    if anchor is not None:
        content = evs[anchor][2].get("afterContent") or ""
        chain = evs[anchor + 1:]
    else:
        content = read_base(rel)
        chain = evs
        if content is None:
            raise ValueError("无锚点无基线")
    for t, tool, fe in chain:
        if tool != "Edit":
            continue
        lines = nl(content)
        for h in fe.get("structuredPatch") or []:
            lines = apply_hunk(lines, h)
        content = "".join(lines)
    return content


targets = [rel for rel in sorted(events)
           if rel.endswith(".py") and not rel.startswith(("gd_core_py/", "output/", ".zcode/", "ai/"))]
ok = fixed = fail = 0
fail_list = []
for rel in targets:
    p = os.path.join(REPO, rel.replace("/", os.sep))
    if not os.path.exists(p):
        continue
    try:
        py_compile.compile(p, doraise=True)
        ok += 1
        continue
    except Exception:
        pass
    try:
        content = rebuild(rel)
        with open(p, "w", encoding="utf-8", newline="") as fh:
            fh.write(content)
        py_compile.compile(p, doraise=True)
        fixed += 1
        print("FIXED", rel)
    except Exception as exc:
        fail += 1
        fail_list.append((rel, str(exc)[:70]))

print("\n原本健康:", ok, "| 修复:", fixed, "| 失败:", fail)
for rel, e in fail_list:
    print("FAIL", rel, e)
