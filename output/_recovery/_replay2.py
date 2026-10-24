# -*- coding: utf-8 -*-
"""恢复重放器 v2：按位应用 hunk，锚点链式（最近 Write 或 git 基线），失配仅告警。"""
import json
import os
import glob
import collections
import subprocess

ROOT = r"C:/Users/Windows/.zcode/cli/artifacts"
REPO = r"D:\文件资料\学习\自动背包AI"
CUTOFF = "2026-10-24T07:30:00"


def norm(p: str) -> str:
    return p.replace("\\", "/").lower()


REPO_N = norm(REPO) + "/"

events = []
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
            if not p.startswith(REPO_N):
                continue
            orig = fe.get("path")
            rel = orig.replace("\\", "/").split("自动背包AI/", 1)[-1]
            events.append((t, rel, j.get("toolName"), fe))

events.sort(key=lambda e: e[0])
by_path = collections.defaultdict(list)
for t, rel, tool, fe in events:
    if t < CUTOFF:
        by_path[rel].append((t, tool, fe))


def read_base(rel: str):
    """git 基线（0ec8faf）内容；无则 None。"""
    p = os.path.join(REPO, rel.replace("/", os.sep))
    r = subprocess.run(["git", "show", "HEAD:" + rel.replace("\\", "/")],
                       capture_output=True, cwd=REPO)
    if r.returncode == 0:
        return r.stdout.decode("utf-8", errors="replace")
    return None


def split_lines(s: str):
    return s.splitlines(keepends=True)


def apply_hunks_positional(content: str, hunks):
    lines = split_lines(content)
    out = []
    pos = 0
    warns = []
    for h in hunks:
        old_start = h["oldStart"] - 1
        old_lines = h["oldLines"]
        if old_start < pos:
            raise ValueError("hunk重叠 oldStart=%d pos=%d" % (old_start, pos))
        out.extend(lines[pos:old_start])
        # 上下文校验（宽松：去 \r\n 与空白行尾比较）
        dels = [ln[1:].rstrip("\r\n").rstrip() for ln in h["lines"] if ln.startswith("-")]
        seg = [l.rstrip("\r\n").rstrip() for l in lines[old_start:old_start + len(dels)]]
        if dels != seg:
            warns.append("ctx失配@%d dels=%r seg=%r" % (h["oldStart"], dels[:2], seg[:2]))
        adds = []
        for ln in h["lines"]:
            if ln.startswith("+"):
                adds.append(ln[1:])
            elif ln.startswith(" "):
                adds.append(ln[1:])
            elif ln == "" or ln == "\n":
                adds.append(ln)
        joined = "".join(a if a.endswith(("\n", "\r\n")) else a + "\n" for a in adds)
        out.append(joined)
        pos = old_start + old_lines
    out.extend(lines[pos:])
    return "".join(out), warns


written = []
warn_files = []
fail_files = []
for rel, evs in sorted(by_path.items()):
    # 锚点：最近的 Write 事件；否则 git 基线
    anchor_idx = -1
    for i in range(len(evs) - 1, -1, -1):
        if evs[i][1] == "Write":
            anchor_idx = i
            break
    if anchor_idx >= 0:
        content = evs[anchor_idx][2].get("afterContent", "")
        chain = evs[anchor_idx + 1:]
    else:
        content = read_base(rel)
        chain = evs
    try:
        warns_all = []
        for t, tool, fe in chain:
            if tool == "Edit":
                content, ws = apply_hunks_positional(content, fe.get("structuredPatch") or [])
                warns_all.extend(ws)
        dest = os.path.join(REPO, rel.replace("/", os.sep))
        os.makedirs(os.path.dirname(dest), exist_ok=True)
        with open(dest, "w", encoding="utf-8", newline="") as fh:
            fh.write(content)
        written.append(rel)
        if warns_all:
            warn_files.append((rel, len(warns_all)))
    except Exception as exc:
        fail_files.append((rel, str(exc)[:80]))

print("重放文件:", len(written), "| 带告警:", len(warn_files), "| 失败:", len(fail_files))
for rel, w in warn_files[:12]:
    print("WARN", w, rel)
for rel, e in fail_files[:12]:
    print("FAIL", rel, e)
keys = ["gd_core_test/OracleAlignBattle.gd", "gd_core/CoreBuff.gd", "gd_core/CoreItem.gd",
        "gd_core_items/Exclusive/AmuletofAgility.gd", "tools/verify_oracle.py",
        "simulator/gd_core_engine.py", "output/alignment_fix_log.md",
        "output/oracle/wf_notes/np21_fix.md", "output/oracle/wf_notes/np22_fix.md",
        "output/oracle/wf_notes/np14_fix.md"]
wl = [w.lower() for w in written]
for k in keys:
    print("KEY", ("OK " if k.lower() in wl else "MISS"), k)
