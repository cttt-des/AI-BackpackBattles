#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""run_godot_script.py — 跑一个 gd_core_test 脚本（统一入口：无窗口、无弹窗、文件重定向）。

存在的理由：docs/parallel_workflow.md §7.1 要求「Godot 一律走 tools/godot_headless.py」，
但过去各处都手敲完整命令行（--no-window --audio-driver Dummy --path gd_core_test
--script Xxx.gd），一不留神就写成 --headless（3.6 不认，仍出窗口）或漏了隐藏桌面，
屏幕上就冒出窗口和搜狗 IME 的 "OpenMem failed" 弹窗。这个脚本把那条命令固化下来。

用法：
    python -X utf8 tools/run_godot_script.py RngProbe.gd
    python -X utf8 tools/run_godot_script.py RngStateProbe.gd --project gd_core_test
    python -X utf8 tools/run_godot_script.py oracle_fight.gd --project oracle \
        --env ORACLE_ONLY_CASES=run570_r18
    python -X utf8 tools/run_godot_script.py TruthBattle.gd --timeout 3600 --quiet

参数：
    script            脚本名（相对 --project，或 res:// 形式）
    --project NAME    项目目录（默认 gd_core_test）
    --env K=V         额外环境变量（可重复；纯开关可只给 K）
    --timeout 秒       墙钟上限（超时 rc=-9，日志仍可读）
    --quiet           只打印过滤后的尾部（噪声行不刷屏）

退出码 = Godot 进程退出码（与直接调引擎一致）。
"""
import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import godot_headless as gh  # noqa: E402


def main() -> int:
    ap = argparse.ArgumentParser(description="跑一个 Godot 3.6 脚本（隐藏桌面 + 静音）")
    ap.add_argument("script", help="脚本名（如 RngProbe.gd）")
    ap.add_argument("--project", default="gd_core_test", help="项目目录（默认 gd_core_test）")
    ap.add_argument("--env", action="append", default=[], metavar="K=V",
                    help="额外环境变量（可重复）")
    ap.add_argument("--timeout", type=float, default=0.0, help="墙钟上限（秒，0=不限）")
    ap.add_argument("--quiet", action="store_true", help="只打印过滤后的尾部")
    args = ap.parse_args()

    if not os.path.exists(gh.GODOT):
        print("缺少 Godot 宿主：%s" % gh.GODOT, file=sys.stderr)
        return 2

    env_extra = {}
    for kv in args.env:
        if "=" in kv:
            k, v = kv.split("=", 1)
            env_extra[k] = v
        else:
            env_extra[kv] = "1"

    cmd = gh.cmd(project=args.project, script=args.script)
    print("[run] %s" % " ".join(cmd))
    rc, out, log_path = gh.run(cmd, label="script_%s" % os.path.basename(args.script),
                               timeout=args.timeout or None, env_extra=env_extra)
    if args.quiet:
        tail = [l for l in out.splitlines() if l.strip() and not gh.is_noise(l)][-40:]
        sys.stdout.write("\n".join(tail) + ("\n" if tail else ""))
    else:
        sys.stdout.write(out)
    print("[run] rc=%s 日志：%s" % (rc, os.path.relpath(log_path, gh.ROOT)
                                   .replace("\\", "/")))
    return rc


if __name__ == "__main__":
    sys.exit(main())
