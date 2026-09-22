#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""run_gd_core.py — gd_core 无头内核一键校验流水线

依次执行四道闸门，任一失败即中止：

  1. 静态审计  tools/audit_gd_core.py      —— ctx.* 与 Core*. 引用是否都有定义
  2. 依赖环检测 tools/check_class_cycles.py —— class_name 之间无循环引用
  3. 全量解析  gd_core_test/ParseAll.gd     —— 14 个脚本在 Godot 3.6 下零解析错误
  4. 契约冒烟  gd_core_test/Smoke.gd        —— 基础对拼 / 疲劳时序 / 确定性

可选：

  --bench   追加吞吐基准 gd_core_test/Bench.gd

用法：
    python tools/run_gd_core.py [--bench]

依赖：output/godot36/Godot_v3.6-stable_win64.exe（无头宿主）
"""
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GODOT = os.path.join(ROOT, "output", "godot36", "Godot_v3.6-stable_win64.exe")
TEST_PROJ = os.path.join(ROOT, "gd_core_test")
PY = sys.executable

GODOT_ARGS = ["--no-window", "--audio-driver", "Dummy", "--path", TEST_PROJ]


def _decode(raw: bytes) -> str:
    """Godot 3 在 Windows 控制台按本地代码页（CP936）输出中文，
    而写文件走 UTF-8。故先试 UTF-8，失败回退 CP936。"""
    for enc in ("utf-8", "cp936"):
        try:
            return raw.decode(enc)
        except UnicodeDecodeError:
            continue
    return raw.decode("utf-8", errors="replace")


# 退出期噪声：Godot 的对象/资源清理告警，与测试结论无关
# （Godot 会加 "ERROR: "/"WARNING: " 前缀，故用子串匹配而非前缀匹配）
_NOISE_KEYS = (
    "Godot Engine v", "OpenGL ES", "Async. shader",
    "ObjectDB instances leaked", "Resources still in use",
    '_first != nullptr',
    "at: ~List", "at: cleanup", "at: clear",
)


def run(cmd, label, cwd=None):
    print("\n" + "=" * 68)
    print(f"[{label}]")
    print("=" * 68)
    p = subprocess.run(cmd, cwd=cwd or ROOT, capture_output=True)
    out = _decode((p.stdout or b"") + (p.stderr or b""))
    for line in out.splitlines():
        s = line.strip()
        if not s:
            continue
        if any(k in s for k in _NOISE_KEYS):
            continue
        print(line)
    return p.returncode


def say_file(path, title):
    if os.path.exists(path):
        print(f"\n--- {title} ---")
        with open(path, encoding="utf-8") as fh:
            print(fh.read().rstrip())


def main():
    if not os.path.exists(GODOT):
        print(f"缺少 Godot 无头宿主：{GODOT}")
        return 2

    with_bench = "--bench" in sys.argv

    if run([PY, os.path.join(ROOT, "tools", "audit_gd_core.py")], "1/4 静态审计") != 0:
        return 1
    if run([PY, os.path.join(ROOT, "tools", "check_class_cycles.py")], "2/4 依赖环检测") != 0:
        return 1
    if run([GODOT] + GODOT_ARGS + ["--script", "ParseAll.gd"], "3/4 全量解析") != 0:
        return 1

    smoke_out = os.path.join(TEST_PROJ, "smoke_result.txt")
    if os.path.exists(smoke_out):
        os.remove(smoke_out)
    if run([GODOT] + GODOT_ARGS + ["--script", "Smoke.gd"], "4/4 契约冒烟") != 0:
        say_file(smoke_out, "Smoke 报告")
        return 1
    say_file(smoke_out, "Smoke 报告")

    if with_bench:
        bench_out = os.path.join(TEST_PROJ, "bench_result.txt")
        if os.path.exists(bench_out):
            os.remove(bench_out)
        run([GODOT] + GODOT_ARGS + ["--script", "Bench.gd"], "附加 吞吐基准")
        say_file(bench_out, "Bench 报告")

    print("\n全部闸门通过。")
    return 0


if __name__ == "__main__":
    sys.exit(main())
