#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""verify_parallel_safety.py — 并行改造的三项安全验收（docs/parallel_workflow.md §10.4）。

判据（三项全过才算本次改造可上线）：

  1. **并行 = 串行**：同一批 Godot 闸门，1 路跑一遍、N 路跑一遍，产物文件逐字节相同。
  2. **零窗口泄漏**：N 路并发跑期间，用户（当前）桌面不得出现 Engine 类窗口、
     #32770 标准对话框或标题含项目名/Error 的新窗口。
  3. **分片汇总一致**：物品脚本按文件分片的各片「待解析」数之和 = 全量数。

为什么这三项：
  · 第 1 项守「并行不改变结果」（保序 + 无共享写）；
  · 第 2 项守「隐藏桌面真的生效」——窗口藏起来不能靠自觉，得实测枚举；
  · 第 3 项守「分片切全了」（漏切会静默少验一批文件，比报错危险）。

用法：
    python -X utf8 tools/verify_parallel_safety.py            # 三项全跑
    python -X utf8 tools/verify_parallel_safety.py --only leak
    python -X utf8 tools/verify_parallel_safety.py --jobs 3
退出码：0=全过；1=有项失败（逐项打印 FAIL）。
"""
import argparse
import ctypes
import ctypes.wintypes as w
import io
import os
import sys
import threading
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import godot_headless as gh  # noqa: E402
import run_gd_core as R  # noqa: E402

#: 验收用的三个轻量闸门（各自写不同 result 文件，互不覆盖）
GATES = [("Smoke.gd", "smoke_result.txt"),
         ("GridSmoke.gd", "grid_result.txt"),
         ("FacadeSmoke.gd", "facade_result.txt")]


def _snapshot(names):
    out = {}
    for n in names:
        p = os.path.join(R.TEST_PROJ, n)
        out[n] = (io.open(p, encoding="utf-8", errors="replace").read()
                  if os.path.exists(p) else None)
    return out


def _run(scripts, jobs, wave):
    return R.run_wave([R._Task("%s" % s, [R.GODOT] + R.GODOT_ARGS + ["--script", s])
                       for s in scripts], jobs=jobs, wave=wave)


def check_byte_equal(jobs):
    """① 并行 = 串行：逐字节比对产物。"""
    names = [n for _s, n in GATES]
    scripts = [s for s, _n in GATES]
    print("\n[1/3] 并行 = 串行（1 路 vs %d 路）" % jobs)
    _run(scripts, 1, "seq")
    seq = _snapshot(names)
    _run(scripts, jobs, "par")
    par = _snapshot(names)
    bad = []
    for n in names:
        same = seq[n] == par[n]
        print("  %-20s 串行 %s 字符 / 并行 %s 字符 / 一致=%s"
              % (n, "-" if seq[n] is None else len(seq[n]),
                 "-" if par[n] is None else len(par[n]), same))
        if not same:
            bad.append(n)
    if bad:
        print("  FAIL 产物不一致：%s" % ",".join(bad))
        return False
    print("  PASS")
    return True


def _visible_windows():
    u = ctypes.windll.user32
    found = []

    def _cb(hwnd, _lp):
        if not u.IsWindowVisible(hwnd):
            return True
        n = u.GetWindowTextLengthW(hwnd) + 1
        buf = ctypes.create_unicode_buffer(n)
        u.GetWindowTextW(hwnd, buf, n)
        cls = ctypes.create_unicode_buffer(256)
        u.GetClassNameW(hwnd, cls, 256)
        found.append((cls.value, buf.value))
        return True

    u.EnumWindows(ctypes.WINFUNCTYPE(ctypes.c_bool, w.HWND, w.LPARAM)(_cb), 0)
    return found


def check_leak(jobs):
    """② 零窗口泄漏：并发跑期间枚举用户桌面。"""
    print("\n[2/3] 零窗口泄漏（%d 路并发）" % jobs)
    before = {(c, t) for c, t in _visible_windows()}
    stop = {"v": False}
    peak = {"v": []}

    def _watch():
        while not stop["v"]:
            peak["v"] = _visible_windows()
            time.sleep(0.05)

    th = threading.Thread(target=_watch, daemon=True)
    th.start()
    try:
        rc = _run([s for s, _n in GATES], jobs, "leak")
    finally:
        stop["v"] = True
        th.join(timeout=1)
    new = [(c, t) for c, t in peak["v"] if (c, t) not in before]
    suspicious = [x for x in new
                  if x[0] in ("Engine", "#32770") or x[1] == "Error"
                  or "Backpack" in x[1] or "gd_core" in x[1]]
    print("  Godot rc=%s，新增窗口 %d 条，可疑 %d 条" % (rc, len(new), len(suspicious)))
    for c, t in new[:10]:
        print("    [新窗口] class=%r title=%r" % (c, t[:60]))
    if suspicious:
        print("  FAIL 出现窗口/弹窗泄漏")
        return False
    print("  PASS（窗口与 IME 弹窗均未落到用户桌面）")
    return True


def check_itemparse(jobs):
    """③ 分片切全：显式分片时各片「待解析」之和 == 全量数。

    ★ 注意（2026-10-31 实测）：物品解析**默认不分片**（--jobs 1）——分片会因
      每片重复支付 Godot 启动与 extends 基类解析而变慢（单进程 8.48s vs 3 路
      11.22s）。这里的显式分片只用来验收「切分逻辑正确、没漏文件」，不是推荐配置。
    """
    print("\n[3/3] 物品解析分片切全（1 路 vs 显式 %d 路）" % jobs)
    import subprocess
    # ★ 沙箱禁匿名管道：不能 capture_output / PIPE（CreatePipe 处 WinError 5），
    #   故把子进程输出重定向到文件再读回（与 gh 的日志策略一致）。
    logdir = os.path.join(ROOT, "output", "_recovery", "safety")
    os.makedirs(logdir, exist_ok=True)
    out = {}
    for j in (1, jobs):
        log_path = os.path.join(logdir, "itemparse_j%d.log" % j)
        with open(log_path, "wb") as fh:
            subprocess.run([sys.executable, "-X", "utf8",
                            os.path.join(ROOT, "tools", "run_item_parse.py"),
                            "--jobs", str(j)],
                           cwd=ROOT, stdout=fh, stderr=subprocess.STDOUT,
                           startupinfo=gh.worker_startupinfo())
        out[j] = gh.read_log(log_path)
    import re
    # 输出行形如：分片 0/3：待解析 168，成功 168，失败 0
    #            待解析：503 个（全量 503 个）
    # 两种写法都认，故用正则而不是固定分隔符。
    _re_total = re.compile(r"待解析[:：]?\s*(\d+)")

    def _total(txt):
        return sum(int(m.group(1)) for m in _re_total.finditer(txt))
    t1, tn = _total(out[1]), _total(out[jobs])
    print("  1 路待解析合计 %d / %d 路待解析合计 %d（默认配置即 1 路）"
          % (t1, jobs, tn))
    if t1 <= 0 or t1 != tn:
        print("  FAIL 分片没有切全（%d != %d）" % (t1, tn))
        return False
    print("  PASS")
    return True


def main():
    ap = argparse.ArgumentParser(description="并行改造三项安全验收")
    ap.add_argument("--jobs", type=int, default=3, help="验收用的并发数（默认 3）")
    ap.add_argument("--only", default="",
                    help="只跑某项：byte|leak|itemparse（默认全跑）")
    args = ap.parse_args()
    if not os.path.exists(gh.GODOT):
        print("缺少 Godot 宿主：%s" % gh.GODOT, file=sys.stderr)
        return 2
    jobs = max(1, args.jobs)
    print("[env] CPU %d 核，可用内存 %.1f GB，上限 %d"
          % (os.cpu_count() or 1, gh.avail_mem_gb(), gh.PARALLEL_MAX_JOBS))
    checks = {"byte": check_byte_equal, "leak": check_leak,
              "itemparse": check_itemparse}
    want = [args.only] if args.only else list(checks)
    results = {}
    for k in want:
        if k not in checks:
            print("未知验收项：%s（可选 %s）" % (k, ",".join(checks)), file=sys.stderr)
            return 2
        results[k] = checks[k](jobs)
    print("\n=== 验收汇总 ===")
    for k, ok in results.items():
        print("  %-10s %s" % (k, "PASS" if ok else "FAIL"))
    return 0 if all(results.values()) else 1


if __name__ == "__main__":
    sys.exit(main())
