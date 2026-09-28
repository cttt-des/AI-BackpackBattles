# -*- coding: utf-8 -*-
"""check_scan_gaps.py — 给 `scan_translit_gaps.py` 的「0 命中」配正对照

================ 为什么需要 ================
`scan_translit_gaps.py` 输出 `0 命中` 有两种解释：

  1. 真的没有缺口          —— 我们想要的
  2. **扫描器坏了**，恒返回 0 —— 看起来一模一样

本项目已经栽过两次（都是同一个坑的变体）：

  · `scan_shadow` 的继承链解析只认 `"res://Items/…"`，不认 `"res://gd_core/…"`
    → GDScript 侧恒返回「无」，看着像全库干净；
  · `scan_dropped_assigns` 的 `^\\t+名字 =` 少了 `re.M`，`^` 只匹配文件首行
    → 同样恒返回「无」。**是被这个正对照当场抓出来的。**

故凡是「0 命中即通过」的判据，都必须配一次**可证伪**的对照。

================ 做法 ================
人为删掉 Python 产物里的一行赋值（默认取 WandofDissonance 的 `damageSource`），
要求扫描器**必须报出来**；随后还原并复核字节一致，再要求扫描回到 PASS。

★ 用 try/finally + 还原后复核：正对照会真的改文件，中途失败必须能恢复。

用法：
    python tools/check_scan_gaps.py
"""
from __future__ import annotations

import io
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = sys.executable

TARGET = os.path.join(ROOT, "gd_core_py", "gd_core_items", "Exclusive",
                      "WandofDissonance.py")
NEEDLE = '\t\tself.damageSource = _R.C("CoreDamageSource")().setItem(self)\n'


def _scan(*args) -> subprocess.CompletedProcess:
    return subprocess.run([PY, os.path.join(ROOT, "tools", "scan_translit_gaps.py")] + list(args),
                          capture_output=True, text=True, encoding="utf-8",
                          errors="replace", cwd=ROOT)


def main() -> int:
    if not os.path.exists(TARGET):
        print("正对照的目标文件不存在：%s" % TARGET)
        return 2
    with io.open(TARGET, encoding="utf-8") as fh:
        orig = fh.read()
    if NEEDLE not in orig:
        print("目标行不在文件里，正对照构造不出前提：%s" % NEEDLE.strip())
        return 2

    ok = False
    try:
        with io.open(TARGET, "w", encoding="utf-8", newline="\n") as fh:
            fh.write(orig.replace(NEEDLE, "", 1))
        r = _scan("--drop")
        body = r.stdout or ""
        hit = ("WandofDissonance" in body) and ("damageSource" in body)
        print("删掉 1 行后：扫描报出 = %s；退出码 = %d（预期 1）"
              % ("是" if hit else "否", r.returncode))
        for ln in body.splitlines():
            if "WandofDissonance" in ln:
                print("   " + ln.strip())
        ok = hit and r.returncode == 1
    finally:
        with io.open(TARGET, "w", encoding="utf-8", newline="\n") as fh:
            fh.write(orig)
        with io.open(TARGET, encoding="utf-8") as fh:
            assert fh.read() == orig, "还原失败，文件已被改坏！"

    r2 = _scan()
    back = r2.returncode == 0
    tail = [l for l in (r2.stdout or "").splitlines() if l.startswith("TRANSLIT_GAPS")]
    print("还原后：%s（退出码 %d，预期 0）" % (tail[0].strip() if tail else "(无输出)",
                                          r2.returncode))
    ok = ok and back
    print()
    print("SCAN_GAPS_CONTROL: %s" % ("PASS" if ok else "FAIL"))
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
