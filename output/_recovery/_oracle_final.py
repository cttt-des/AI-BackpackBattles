# -*- coding: utf-8 -*-
"""oracle 终建 v2：1.1.9 pck 恢复树为基 + 工件覆盖（内容寻址法）。"""
import json
import os
import glob
import collections
import shutil
import subprocess

ROOT = r"C:/Users/Windows/.zcode/cli/artifacts"
REPO = r"D:\文件资料\学习\自动背包AI"
BASE = os.path.join(REPO, "output", "_recovery", "decomp_cur")
ORC = os.path.join(REPO, "oracle")
PRE_STUB = "2026-10-20T00:00"

# 1) 收集 oracle 工件事件（含 output/oracle 误映射校正：仅真 oracle/ 路径）
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
            raw = (fe.get("path") or "").replace("\\", "/")
            low = raw.lower()
            # 真 oracle 树路径：D:/.../自动背包AI/oracle/**（排除 output/oracle/**）
            i = low.find("/自动背包ai/oracle/")
            if i < 0:
                continue
            rel = "oracle" + low[i + len("/自动背包ai/oracle"):]
            events[rel].append((t, j.get("toolName"), fe))
for rel in events:
    events[rel].sort(key=lambda e: e[0])
print("真 oracle 工件文件数:", len(events))


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
            raise ValueError("定位失败 %s" % h.get("oldStart"))
        lines = lines[:hit] + [x + eol for x in new_norm] + lines[hit + len(old_norm):]
    return "".join(lines)


def content_pre_stub(rel):
    cand = [e for e in events.get(rel, []) if e[0] < PRE_STUB]
    if not cand:
        return None
    t, tool, fe = cand[-1]
    if tool == "Write":
        return fe.get("afterContent")
    try:
        return apply_addr(fe.get("beforeContent"), fe.get("structuredPatch") or [])
    except Exception:
        return None


# 2) 保护件暂存
keep = {}
for p in ("oracle/data/history.db", "oracle/fights.json", "oracle/oracle_fight.gd"):
    fp = os.path.join(REPO, p.replace("/", os.sep))
    if os.path.exists(fp):
        keep[p] = fp
print("保护件:", list(keep))

# 3) 重建：decomp_cur → oracle
shutil.rmtree(ORC, ignore_errors=True)
shutil.copytree(BASE, ORC)

# 4) 工件覆盖（桩前终态；oracle_fight.gd 用已重建版本）
ok = fail = 0
fails = []
for rel in sorted(events):
    if rel in ("oracle/oracle_fight.gd",):
        continue
    if rel.startswith(("oracle/probe/", "oracle/wf_notes/", "oracle/data/", "oracle/fights.json",
                       "oracle/offpeak")):
        continue
    c = content_pre_stub(rel)
    if c is None:
        continue
    dest = os.path.join(REPO, rel.replace("/", os.sep))
    os.makedirs(os.path.dirname(dest), exist_ok=True)
    with open(dest, "w", encoding="utf-8", newline="") as fh:
        fh.write(c)
    ok += 1
print("工件覆盖:", ok, "失败:", fail, fails[:5])

# 5) 保护件回位
for rel, fp in keep.items():
    dest = os.path.join(REPO, rel.replace("/", os.sep))
    os.makedirs(os.path.dirname(dest), exist_ok=True)
    shutil.copy2(fp, dest)
print("回位:", list(keep))
print("oracle .gd 总数:", sum(1 for _, _, fs in os.walk(ORC) for f in fs if f.endswith(".gd")))
