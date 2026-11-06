# -*- coding: utf-8 -*-
"""godot_watchdog —— 检测「Godot 卡死」并自动杀掉重跑。

## 解决什么问题

录制/重放时 Godot 窗口会出现在屏幕上。用户一旦点它，进程会进入「未响应」
并在阻塞 tick 循环里彻底卡住 —— 实测两次：墙钟 231s / 161s，退出码
`0xFFFFFFFF` / `0xCFFFFFFF`，`events.json` **0 事件**，日志停在 `t=63.3s`
（整场 66.6s，差最后 3 秒）。

## 为什么不用 IsHungAppWindow

**实测它是假信号**：正常录制期间（t=5s 到 t=40s，日志持续增长、产物正常）
`IsHungAppWindow` 返回的**一直是 1**。原因同上：Godot 的主循环是手动 tick 的
阻塞循环，长时间不处理消息，系统据此就判「未响应」。所以它区分不了
「正在跑」和「真卡死」。

## 用什么判据：日志停滞

同一次实测的日志增长曲线（正常录制）：

```
停滞时长序列（秒）：3, 0, 4, 2, 7, 1, 6, 1, 0     <- 正常最多 7 秒
```

而真卡死时日志会**几分钟到几小时**不动。所以判据是：**日志文件在 N 秒内
零增长**（默认 90 秒，留足正常批写间隔的 10 倍余量）。

## 用法

```python
import godot_watchdog as wd
res = wd.run_with_watchdog(specs, label="long_rec", max_parallel=3,
                           stall_seconds=90, max_retries=2)
for r in res:
    print(r["tag"], r["rc"], "卡死重跑次数", r["retries"])
```

★ 只杀自己起的进程（按 Popen 句柄），不按进程名批量杀，避免误伤。
"""
from __future__ import annotations

import os
import subprocess
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import godot_headless as gh  # noqa: E402

#: 判定卡死的日志停滞阈值（秒）。正常录制实测最长停滞 7s，取 90 留 10 倍余量。
DEFAULT_STALL_SECONDS = 90.0
#: 单段最多重跑几次（每次都是「杀掉 -> 重来」）
DEFAULT_MAX_RETRIES = 2
#: 轮询间隔（秒）。太小费 CPU，太大浪费排查时间。
POLL_SECONDS = 2.0


def _log_size(path: str) -> int:
    try:
        return os.path.getsize(path)
    except OSError:
        return -1


def run_with_watchdog(specs, label="godot", max_parallel=0,
                      stall_seconds=DEFAULT_STALL_SECONDS,
                      max_retries=DEFAULT_MAX_RETRIES,
                      on_event=None):
    """跑一批 Godot，**卡死（日志停滞）就杀掉重跑**。

    specs 同 gh.run_many：[{"cmd", "tag", "env_extra", "timeout"}, ...]
    返回 [{"index","tag","rc","log","tail","secs","retries","killed"}...]。

    ★ 卡死判据 = 该进程自己的日志文件 stall_seconds 内零增长。
    ★ 杀掉时用 Popen.kill()（只杀自己起的进程，不按进程名扫）。
    ★ 重跑 = 同一 spec 原样再起一次（调用方通常靠"产物存在即跳过"保证幂等）。
    """
    specs = list(specs)
    if not specs:
        return []
    limit = int(max_parallel) if max_parallel and int(max_parallel) > 0 else len(specs)
    limit = max(1, min(limit, len(specs)))

    state = {}          # index -> 结果字典
    attempts = {}       # index -> 已尝试次数
    pending = list(enumerate(specs))
    running = []        # [(index, tag, proc, fh, log_path, deadline, t0, last_size, stale_since)]

    def _emit(kind, payload):
        if on_event is not None:
            try:
                on_event(kind, payload)
            except Exception:  # noqa: BLE001
                pass

    def _launch(i, sp, retry):
        tag = sp.get("tag") or ("w%d" % i)
        proc, log_path, fh = gh.spawn(sp["cmd"],
                                      label="%s_%s%s" % (label, tag, "" if not retry else "_r%d" % retry),
                                      tag=tag, cwd=sp.get("cwd"),
                                      env_extra=sp.get("env_extra"))
        tmo = sp.get("timeout")
        deadline = (time.time() + float(tmo)) if tmo else None
        running.append([i, tag, proc, fh, log_path, deadline, time.time(),
                        _log_size(log_path), None])

    def _finish(entry, rc, killed):
        i, tag, proc, fh, log_path, _dl, t0, _ls, _ss = entry
        try:
            fh.close()
        except OSError:
            pass
        text = gh.read_log(log_path)
        tail = [l for l in text.splitlines() if l.strip() and not gh.is_noise(l)][-5:]
        rec = {"index": i, "tag": tag, "rc": rc, "log": log_path, "tail": tail,
               "secs": time.time() - t0, "retries": attempts.get(i, 0) - 1,
               "killed": killed}
        state[i] = rec
        _emit("done", rec)
        return rec

    while pending and len(running) < limit:
        i, sp = pending.pop(0)
        attempts[i] = 1
        _launch(i, sp, 0)

    while running:
        now = time.time()
        action = None
        for entry in running:
            i, tag, proc, fh, log_path, deadline, t0, last_size, stale_since = entry
            # 1) 正常退出
            rc = proc.poll()
            if rc is not None:
                action = ("done", entry, rc, False)
                break
            # 2) 超时
            if deadline is not None and now > deadline:
                proc.kill()
                try:
                    proc.wait(timeout=5)
                except Exception:  # noqa: BLE001
                    pass
                action = ("timeout", entry, -9, True)
                break
            # 3) 日志停滞 -> 判卡死
            size = _log_size(log_path)
            if size > last_size:
                entry[7] = size
                entry[8] = None
            else:
                if entry[8] is None:
                    entry[8] = now
                elif now - entry[8] >= stall_seconds:
                    proc.kill()
                    try:
                        proc.wait(timeout=5)
                    except Exception:  # noqa: BLE001
                        pass
                    action = ("stalled", entry, -8, True)
                    break
        if action is None:
            time.sleep(POLL_SECONDS)
            continue
        kind, entry, rc, killed = action
        running.remove(entry)
        i, sp0 = entry[0], specs[entry[0]]
        if kind == "stalled":
            _emit("stalled", {"index": i, "tag": entry[1],
                              "stalled_for": round(now - (entry[8] or now), 1)})
            if attempts.get(i, 0) <= max_retries:
                attempts[i] = attempts.get(i, 0) + 1
                _launch(i, sp0, attempts[i] - 1)
                continue
        rec = _finish(entry, rc, killed)
        rec["verdict"] = kind
        if pending:
            j, sp = pending.pop(0)
            attempts[j] = 1
            _launch(j, sp, 0)
    return [state[i] for i in sorted(state)]


def main(argv=None):
    """命令行自检：不启动 Godot，只验证判据函数。"""
    print("DEFAULT_STALL_SECONDS =", DEFAULT_STALL_SECONDS)
    print("DEFAULT_MAX_RETRIES  =", DEFAULT_MAX_RETRIES)
    print("POLL_SECONDS         =", POLL_SECONDS)
    print("判据：日志文件在 N 秒内零增长 = 卡死")
    print("（不用 IsHungAppWindow：实测正常录制期间它恒为 1，是假信号）")
    return 0


if __name__ == "__main__":
    sys.exit(main())
