# -*- coding: utf-8 -*-
"""重放 v5（终版）：git 基线归零 → 全事件文件强制重建（v4 unified-diff 应用器）。
排除 oracle/ .zcode/ dist/ build/ gd_core_probe/ extracted*/ 与 output/oracle/probe|align|fights。"""
import json
import os
import glob
import collections
import py_compile
import subprocess

ROOT = r"C:/Users/Windows/.zcode/cli/artifacts"
REPO = r"D:\文件资料\学习\自动背包AI"
CUTOFF = "2026-10-24T07:30:00"
EXCLUDE_PREFIX = ("oracle/", ".zcode/", "dist/", "build/", "gd_core_probe/",
                  "output/oracle/probe/", "output/oracle/align/", "output/oracle/fights/",
                  "output/_recovery/", "output/godot36/", "Backpack Battles/")
EXCLUDE_PREFIX_CI = tuple(x.lower() for x in EXCLUDE_PREFIX)


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
            if not p.startswith(REPO_N) or t >= CUTOFF:
                continue
            rel = fe.get("path").replace("\\", "/").split("自动背包AI/", 1)[-1]
            if rel.lower().startswith(EXCLUDE_PREFIX_CI):
                continue
            events[rel].append((t, j.get("toolName"), fe))
for rel in events:
    events[rel].sort(key=lambda e: e[0])
print("事件文件数:", len(events))


def read_base(rel):
    r = subprocess.run(["git", "show", "HEAD:" + rel.replace("\\", "/")],
                       capture_output=True, cwd=REPO)
    if r.returncode == 0:
        return r.stdout.decode("utf-8", errors="replace")
    return None


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
            new.append(ln)
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
        lines = (content or "").splitlines(keepends=True)
        for h in fe.get("structuredPatch") or []:
            lines = apply_hunk(lines, h)
        content = "".join(lines)
    return content


ok = fail = 0
fail_list = []
py_checked = 0
for rel in sorted(events):
    try:
        content = rebuild(rel)
        dest = os.path.join(REPO, rel.replace("/", os.sep))
        os.makedirs(os.path.dirname(dest), exist_ok=True)
        with open(dest, "w", encoding="utf-8", newline="") as fh:
            fh.write(content)
        if rel.endswith(".py"):
            py_compile.compile(dest, doraise=True)
            py_checked += 1
        ok += 1
    except Exception as exc:
        fail += 1
        fail_list.append((rel, str(exc)[:70]))

print("重建:", ok, "| 其中 .py 编译过:", py_checked, "| 失败:", fail)
for rel, e in fail_list[:15]:
    print("FAIL", rel, e)

# 关键抽查
import io
def has(path, needle):
    p = os.path.join(REPO, path)
    try:
        return needle in io.open(p, encoding="utf-8", errors="replace").read()
    except Exception:
        return False
for path, needle in [
    ("gd_core_test/OracleAlignBattle.gd", "R5_DUAL_EXEC"),
    ("tools/verify_oracle.py", "PY_PERM_STACK_OVERRIDE"),
    ("simulator/gd_core_engine.py", "warm_latch"),
    ("tools/_np21_gate.py", "ALL PASS"),
    ("output/alignment_fix_log.md", "np22 层收口"),
    ("output/oracle/wf_notes/np21_fix.md", "R5"),
    ("output/oracle/wf_notes/np8_bl.md", "盲"),
    ("docs/consistency_expansion_playbook.md", "实战手册"),
]:
    print("CHECK", ("OK " if has(path, needle) else "MISS"), path)
