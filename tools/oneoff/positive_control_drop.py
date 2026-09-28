# -*- coding: utf-8 -*-
"""C 段（整行丢失）的正对照：人为删掉 Python 产物里的一行，扫描必须报出来。

★ 为什么必须做：`0 命中` 有两种解释 —— 「真的没有」或「表笔没接上」。
  项目里已经吃过一次亏：`scan_shadow` 的继承链解析写错，GDScript 侧**恒返回「无」**，
  看起来是「全库干净」，实际是扫描器坏了。
  故对「0 命中」的判据一律配一次**可证伪**的正对照。
"""
import io
import os
import subprocess
import sys

ROOT = r"D:\文件资料\学习\自动背包AI"
PY = r"C:\Users\Windows\.workbuddy\binaries\python\versions\3.13.12\python.exe"
TARGET = os.path.join(ROOT, "gd_core_py", "gd_core_items", "Exclusive",
                      "WandofDissonance.py")
NEEDLE = '\t\tself.damageSource = _R.C("CoreDamageSource")().setItem(self)\n'

with io.open(TARGET, encoding="utf-8") as fh:
    orig = fh.read()
assert NEEDLE in orig, "待删的那行不在文件里，正对照的构造前提不成立"

try:
    io.open(TARGET, "w", encoding="utf-8", newline="\n").write(
        orig.replace(NEEDLE, "", 1))
    r = subprocess.run([PY, os.path.join(ROOT, "tools", "scan_translit_gaps.py"),
                        "--drop"], capture_output=True, text=True,
                       encoding="utf-8", errors="replace", cwd=ROOT)
    body = r.stdout or ""
    hit = "WandofDissonance" in body and "damageSource" in body
    print("删掉一行后扫描是否报出：%s" % ("是 ✓" if hit else "否 ✗（表笔没接上）"))
    for ln in body.splitlines():
        if "WandofDissonance" in ln or "TRANSLIT_GAPS" in ln:
            print("   " + ln.strip())
    print("退出码：%d（预期 1 = FAIL，说明确实判成了失败）" % r.returncode)
    ok = hit and r.returncode == 1
finally:
    io.open(TARGET, "w", encoding="utf-8", newline="\n").write(orig)
    # 复核还原
    with io.open(TARGET, encoding="utf-8") as fh:
        assert fh.read() == orig, "还原失败！"
    print("已还原并复核一致。")

# 还原后必须回到 PASS
r2 = subprocess.run([PY, os.path.join(ROOT, "tools", "scan_translit_gaps.py")],
                    capture_output=True, text=True, encoding="utf-8",
                    errors="replace", cwd=ROOT)
tail = [l for l in (r2.stdout or "").splitlines() if l.startswith("TRANSLIT_GAPS")]
print("还原后：" + (tail[0] if tail else "(无输出)"))
sys.exit(0 if ok and r2.returncode == 0 else 1)
