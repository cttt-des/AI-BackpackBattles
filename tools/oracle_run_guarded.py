# -*- coding: utf-8 -*-
"""受控神谕批量运行包装器： Godot 的 stdout/stderr 里 SCRIPT ERROR 刷屏会以
GB 计（个别超时场每 tick 报错）。本包装器只保留进度/结论行，其余计数丢弃，
防止磁盘被诊断噪声写爆。真正要排查某场时再用 ORACLE_DEBUG 单场复跑。"""
import subprocess, sys, re, os, time

KEEP = re.compile(r"ORACLE-BATCH|/\s*917\]|确定性|漂移|\[FAIL\]|\[PASS\]|暖场|预检\]|watchdog|resume|tick-diverge|批量结束|用例|共 \d+ 条 run|裁剪")
LOG = "oracle_batch_full_progress.log"

cmd = sys.argv[1:]
env = dict(os.environ)
env["ORACLE_RESUME"] = "1"
p = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                     text=True, encoding="utf-8", errors="replace", env=env, bufsize=1)
kept = 0
dropped = 0
t0 = time.time()
with open(LOG, "w", encoding="utf-8") as out:
    for line in p.stdout:
        if KEEP.search(line):
            out.write(line)
            out.flush()
            kept += 1
        else:
            dropped += 1
        if dropped % 200000 == 0 and dropped > 0:
            out.write("[wrapper] 已丢弃 %d 行噪声，elapsed %.0fs\n" % (dropped, time.time() - t0))
            out.flush()
p.wait()
out.write("[wrapper] exit=%s kept=%d dropped=%d elapsed=%.0fs\n" % (p.returncode, kept, dropped, time.time() - t0))
print("exit=", p.returncode, "kept=", kept, "dropped=", dropped)
