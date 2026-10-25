# -*- coding: utf-8 -*-
"""harness 事件二分：state(k)=git基线+前k笔事件（内容寻址链式），二分首个挂起态。"""
import json
import os
import glob
import subprocess
import shutil
import time

ROOT = r"C:/Users/Windows/.zcode/cli/artifacts"
REPO = r"D:\文件资料\学习\自动背包AI"
CUTOFF = "2026-10-24T07:30:00"
TARGET = os.path.join(REPO, "gd_core_test", "OracleAlignBattle.gd")
OUT = os.path.join(REPO, "output", "_recovery", "t_bh")

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
print("事件总数:", len(evs))


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
        for delta in (0, -1, 1, -2, 2, -3, 3, 5, -5, 10, -10, 20, -20):
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
            raise ValueError("miss")
        lines = lines[:hit] + [x + eol for x in new_norm] + lines[hit + len(old_norm):]
    return "".join(lines)


def base_content():
    r = subprocess.run(["git", "show", "HEAD:gd_core_test/OracleAlignBattle.gd"],
                       capture_output=True, cwd=REPO)
    return r.stdout.decode("utf-8", errors="replace")


def build_state(k):
    """基线 + 前 k 笔（遇 Write 用其 afterContent 重锚）。"""
    content = base_content()
    for i in range(k):
        t, tool, fe = evs[i]
        if tool == "Write":
            content = fe.get("afterContent") or content
        else:
            try:
                content = apply_addr(content, fe.get("structuredPatch") or [])
            except Exception:
                return None, i  # 此处链断（bash 段）——标记
    return content, None


def test(content, timeout=90):
    open(TARGET, "w", encoding="utf-8", newline="").write(content)
    shutil.rmtree(OUT, ignore_errors=True)
    env = dict(os.environ)
    env["APPDATA"] = r"D:\文件资料\学习\自动背包AI\output\_recovery\appdata"
    env["ORACLE_ALIGN_OUT"] = OUT
    env["ORACLE_ALIGN_CASES"] = "run569_r11"
    env["ORACLE_ALIGN_CHUNK"] = "0"
    env["ORACLE_ALIGN_SELFCHECK"] = "0"
    t0 = time.time()
    try:
        subprocess.run([os.path.join(REPO, "output/godot36/Godot_v3.6-stable_win64.exe"),
                        "--headless", "--audio-driver", "Dummy", "--path", "gd_core_test",
                        "--script", "OracleAlignBattle.gd"],
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                       env=env, cwd=REPO, timeout=timeout)
        wall = time.time() - t0
    except subprocess.TimeoutExpired:
        wall = -1
    return wall


# 先验证两端
c0, _ = build_state(0)
w0 = test(c0, 30)
print("state(0) 基线:", w0)
full = None
lo, hi = 0, len(evs)
while lo < hi:
    mid = (lo + hi) // 2
    c, broke_at = build_state(mid)
    if c is None:
        hi = mid  # mid 处链断——向左缩
        continue
    w = test(c, 60)
    print("state(%d) %s wall=%s" % (mid, evs[mid - 1][0][:19] if mid else "-", w))
    if w < 0:
        hi = mid
    else:
        lo = mid + 1
print("首个挂起事件区间: [%d, %d]" % (lo - 1, lo))
if 0 < lo <= len(evs):
    t, tool, fe = evs[lo - 1]
    print("嫌疑笔:", t[:19], tool, "hunks:", len(fe.get("structuredPatch") or []))
    for h in (fe.get("structuredPatch") or [])[:3]:
        print("  首行:", (h["lines"][0] if h.get("lines") else "")[:100])
