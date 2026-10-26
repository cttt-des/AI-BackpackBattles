# -*- coding: utf-8 -*-
"""受控神谕批量分块驱动（临时工具，批量完成后删除）。

为什么分块：oracle_fight.gd 的批量在 SceneTree 脚本里以阻塞循环手动 tick，
MessageQueue 只能在帧末 flush，call_deferred/queue_free/request_ready 消息跨场
累积（实测 ~116 场后队列溢出内刷，陈旧目标逐条报错，单场 532s/831MB）。
[M11] ORACLE_FIGHT_CHUNK=N 让每个进程跑满 N 场即优雅退出（帧末一次干净 flush），
本驱动反复重入直到用例全部完成（resume 幂等：events.json 非空即跳过）。

用法：python oracle_chunk_driver.py [chunk_size] [max_rounds]
"""
import json, os, subprocess, sys, time

REPO = os.path.dirname(os.path.abspath(__file__))
GODOT = os.path.join(REPO, "output", "godot36", "Godot_v3.6-stable_win64.exe")
ROOT = os.path.join(REPO, "output", "oracle", "fights")

CHUNK = int(sys.argv[1]) if len(sys.argv) > 1 else 60
MAX_ROUNDS = int(sys.argv[2]) if len(sys.argv) > 2 else 12
PER_CHUNK_TIMEOUT = 100 * 60  # 单块墙钟上限（秒）


def pending_cases():
    d = json.load(open(os.path.join(REPO, "oracle", "fights.json"), encoding="utf-8"))
    dropped = set()
    pdrop = os.path.join(ROOT, "_preflight_dropped.txt")
    if os.path.exists(pdrop):
        dropped = set(open(pdrop, encoding="utf-8").read().split())
    out = []
    for c in d["cases"]:
        cid = c["case_id"]
        if cid in dropped:
            continue
        ev = os.path.join(ROOT, cid, "events.json")
        if not os.path.exists(ev):
            out.append(cid)
            continue
        try:
            if json.load(open(ev, encoding="utf-8")).get("event_count", 0) <= 0:
                out.append(cid)
        except Exception:
            out.append(cid)
    return out


def main():
    no_progress_rounds = 0
    for rnd in range(1, MAX_ROUNDS + 1):
        pend = pending_cases()
        print("[%s] round %d: pending=%d chunk=%d" % (
            time.strftime("%H:%M:%S"), rnd, len(pend), CHUNK), flush=True)
        if not pend:
            print("DRIVER: all cases done")
            return 0
        before = len(pend)
        outp = os.path.join(REPO, "oracle_chunk_%02d.out.log" % rnd)
        errp = os.path.join(REPO, "oracle_chunk_%02d.err.log" % rnd)
        env = dict(os.environ, ORACLE_FIGHT_CHUNK=str(CHUNK))
        t0 = time.time()
        with open(outp, "wb") as fo, open(errp, "wb") as fe:
            try:
                rc = subprocess.run(
                    [GODOT, "--headless", "--path", "oracle",
                     "--script", "oracle_fight.gd"],
                    stdout=fo, stderr=fe, env=env, cwd=REPO,
                    timeout=PER_CHUNK_TIMEOUT).returncode
                killed = False
            except subprocess.TimeoutExpired:
                rc = -9
                killed = True
        after = len(pending_cases())
        print("[%s] round %d done: rc=%s killed=%s wall=%.0fs pending %d -> %d" % (
            time.strftime("%H:%M:%S"), rnd, rc, killed, time.time() - t0,
            before, after), flush=True)
        if after == 0:
            print("DRIVER: all cases done")
            return 0
        if after >= before:
            no_progress_rounds += 1
            print("DRIVER: no progress this round (%d)" % no_progress_rounds, flush=True)
            if no_progress_rounds >= 2:
                print("DRIVER: two rounds without progress — stop for manual triage")
                return 2
        else:
            no_progress_rounds = 0
    print("DRIVER: max rounds reached, pending=%d" % len(pending_cases()))
    return 1


if __name__ == "__main__":
    sys.exit(main())
