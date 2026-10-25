# -*- coding: utf-8 -*-
"""harness 前移器：从 state(20) 逐事件应用到 68，每个状态实测：
wall（挂起=超时）+ gd 事件数 vs 语料。输出每个事件的效果与首个挂起笔。"""
import json
import os
import glob
import subprocess
import shutil
import time
import sys

ROOT = r"C:/Users/Windows/.zcode/cli/artifacts"
REPO = r"D:\文件资料\学习\自动背包AI"
CUTOFF = "2026-10-24T07:30:00"
TARGET = os.path.join(REPO, "gd_core_test", "OracleAlignBattle.gd")
OUT = os.path.join(REPO, "output", "_recovery", "t_fw")
CASE = "run569_r11"

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
        for delta in (0, -1, 1, -2, 2, -3, 3, 5, -5, 10, -10, 20, -20, 40, -40):
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
            raise ValueError("miss oldStart=%d" % h.get("oldStart"))
        lines = lines[:hit] + [x + eol for x in new_norm] + lines[hit + len(old_norm):]
    return "".join(lines)


def base_content():
    r = subprocess.run(["git", "show", "HEAD:gd_core_test/OracleAlignBattle.gd"],
                       capture_output=True, cwd=REPO)
    return r.stdout.decode("utf-8", errors="replace")


def build(k):
    """state(k) = 第 k 笔事件自身的 beforeContent+patch（零链漂移）。"""
    t, tool, fe = evs[k - 1]
    if tool == "Write":
        return fe.get("afterContent")
    return apply_addr(fe.get("beforeContent"), fe.get("structuredPatch") or [])


def corpus_events(case):
    o = json.load(open(os.path.join(REPO, "output/oracle/fights", case, "events.json"),
                       encoding="utf-8"))
    return o["event_count"]


def test(content):
    open(TARGET, "w", encoding="utf-8", newline="").write(content)
    shutil.rmtree(OUT, ignore_errors=True)
    env = dict(os.environ)
    env["APPDATA"] = r"D:\文件资料\学习\自动背包AI\output\_recovery\appdata"
    env["ORACLE_ALIGN_OUT"] = OUT
    env["ORACLE_ALIGN_CASES"] = CASE
    env["ORACLE_ALIGN_CHUNK"] = "0"
    env["ORACLE_ALIGN_SELFCHECK"] = "0"
    t0 = time.time()
    try:
        subprocess.run([os.path.join(REPO, "output/godot36/Godot_v3.6-stable_win64.exe"),
                        "--headless", "--audio-driver", "Dummy", "--path", "gd_core_test",
                        "--script", "OracleAlignBattle.gd"],
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                       env=env, cwd=REPO, timeout=90)
        wall = time.time() - t0
    except subprocess.TimeoutExpired:
        return -1, None
    ev = None
    p = os.path.join(OUT, CASE, "events.json")
    if os.path.exists(p):
        try:
            ev = json.load(open(p, encoding="utf-8"))["event_count"]
        except Exception:
            ev = None
    return wall, ev


if __name__ == "__main__":
    lo = int(sys.argv[1]) if len(sys.argv) > 1 else 20
    hi = int(sys.argv[2]) if len(sys.argv) > 2 else len(evs)
    corp = corpus_events(CASE)
    print("语料 %s = %d 事件" % (CASE, corp))
    last_good = None
    for k in range(lo, hi + 1):
        pass
    for k in [int(x) for x in os.environ.get("WALK_LIST", "").split(",") if x] or range(lo, hi + 1):
        try:
            content = build(k)
        except Exception as exc:
            print("state(%d) 构建失败: %s" % (k, str(exc)[:60]))
            break
        wall, ev = test(content)
        t, tool, fe = evs[k - 1]
        hang = wall < 0
        print("state(%d) %s %s hunks=%d -> %s ev=%s (距语料 %+d)" % (
            k, t[:16], tool, len(fe.get("structuredPatch") or []),
            "HANG" if hang else round(wall, 1), ev,
            (ev - corp) if ev else 999))
        sys.stdout.flush()
        if hang:
            print(">>> 首个挂起笔 = 事件 #%d" % k)
            break
        last_good = k
        if ev == corp:
            print(">>> state(%d) 事件数与语料一致！" % k)
    print("last_good =", last_good)
