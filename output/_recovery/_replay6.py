# -*- coding: utf-8 -*-
"""重放 v6（单事件终态法）：每文件取 cutoff 前最晚一笔事件直接推导终态。
Edit: apply(beforeContent, patch)；Write: afterContent。失败者再试链式/基线回退。"""
import json
import os
import glob
import collections
import py_compile
import subprocess

ROOT = r"C:/Users/Windows/.zcode/cli/artifacts"
REPO = r"D:\文件资料\学习\自动背包AI"
CUTOFF = "2026-10-24T07:30:00"
EXCLUDE_PREFIX_CI = ("oracle/", ".zcode/", "dist/", "build/", "gd_core_probe/",
                     "output/oracle/probe/", "output/oracle/align/", "output/oracle/fights/",
                     "output/_recovery/", "output/godot36/", "backpack battles/")


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


def read_base(rel):
    r = subprocess.run(["git", "show", "HEAD:" + rel.replace("\\", "/")],
                       capture_output=True, cwd=REPO)
    return r.stdout.decode("utf-8", errors="replace") if r.returncode == 0 else None


ok = fallback_base = fail = 0
fail_list = []
for rel in sorted(events):
    t, tool, fe = events[rel][-1]
    dest = os.path.join(REPO, rel.replace("/", os.sep))
    try:
        if tool == "Write":
            content = fe.get("afterContent") or ""
        else:
            content = apply_hunks(fe.get("beforeContent"), fe.get("structuredPatch") or [])
        if not content.strip():
            raise ValueError("空内容")
        os.makedirs(os.path.dirname(dest), exist_ok=True)
        with open(dest, "w", encoding="utf-8", newline="") as fh:
            fh.write(content)
        if rel.endswith(".py"):
            py_compile.compile(dest, doraise=True)
        ok += 1
    except Exception:
        # 回退：git 基线（若有）
        base = read_base(rel)
        if base is not None:
            with open(dest, "w", encoding="utf-8", newline="") as fh:
                fh.write(base)
            try:
                if rel.endswith(".py"):
                    py_compile.compile(dest, doraise=True)
                fallback_base += 1
                fail_list.append((rel, "→基线"))
            except Exception:
                fail += 1
                fail_list.append((rel, "基线也失败"))
        else:
            fail += 1
            fail_list.append((rel, "无基线"))

print("单事件终态:", ok, "| 回退基线:", fallback_base, "| 硬失败:", fail)
for rel, why in fail_list:
    print("FB", rel, why)

# 关键终检
import io
def has(path, needle):
    try:
        return needle in io.open(os.path.join(REPO, path), encoding="utf-8", errors="replace").read()
    except Exception:
        return False
for path, needle in [
    ("gd_core_test/OracleAlignBattle.gd", "R5_DUAL_EXEC"),
    ("tools/verify_oracle.py", "PY_PERM_STACK_OVERRIDE"),
    ("simulator/gd_core_engine.py", "warm_latch"),
    ("combatlog_exporter.py", "def "),
    ("core/godot_reader.py", "class "),
    ("output/alignment_fix_log.md", "np22 层收口"),
]:
    print("CHECK", ("OK " if has(path, needle) else "MISS"), path)
