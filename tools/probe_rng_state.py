# -*- coding: utf-8 -*-
"""probe_rng_state.py — Util.rng 内存读取的活体标定与差分验证（只读）

按 docs/rng_truth.md §6.1 执行三段验证：
  1. 定位：Util autoload → members[3]（Variant OBJECT）→ RandomNumberGenerator 对象；
  2. 偏移标定：配置偏移 (+0xE0/+0xE8/+0xF0) 经 LCG 不变式校验，失败自动扫描标定；
  3. 差分：间隔采样 N 次，相邻两次沿 PCG 前进式找步数 k ——
     找得到 ⇒ 读到的是同一条 Util.rng 链的真 pcg.state 字段；
     全程读数不变且游戏不在战斗 ⇒ 字段稳定性成立（战斗外应不变）。

用法（游戏运行后）：
    python tools/probe_rng_state.py [--diff-seconds 4] [--interval 0.2]

只读进程内存；不进入任何游戏模式。退出码：0=验证通过，1=连接失败，
2=rng 读取失败，3=差分校验失败。
"""
from __future__ import annotations

import argparse
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))

from core.combatlog_reader import CombatLogReader  # noqa: E402
from core.godot_reader import PCG_INC, pcg_match_forward  # noqa: E402


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--diff-seconds", type=float, default=4.0,
                    help="差分采样总时长（秒）")
    ap.add_argument("--interval", type=float, default=0.2,
                    help="差分采样间隔（秒）")
    args = ap.parse_args()

    r = CombatLogReader()
    if not r.ensure_connected():
        print("[FAIL] 未连接到游戏进程（请先启动 Backpack Battles）")
        return 1
    gr = r.gr
    print(f"[OK] 已连接 PID={r.pid} "
          f"os_singleton_rva={hex(gr.off.get('os_singleton_rva', 0))}")

    util = gr.find_util_node()
    if not util:
        print("[FAIL] 未找到 Util autoload 节点")
        return 2
    print(f"[OK] Util 节点 {hex(util)} name={gr.node_name(util)!r} "
          f"script={gr.node_script_path(util)!r}")

    ma = gr._members_addr(util)
    slot = gr.off.get("rng_member_slot", 3)
    vtype = gr._read_int(ma + slot * gr.off["variant_size"], 4)
    print(f"[..] members[{slot}] Variant type={vtype}（预期 17 OBJECT）")
    if vtype != 17:
        print("[FAIL] members[3] 不是 OBJECT——槽位推导失效，禁止继续")
        return 2

    d = gr.read_rng_state_detail()
    if not d:
        print("[FAIL] rng 对象读取/标定失败（LCG 不变式无命中）")
        return 2
    print(f"[OK] rng 对象 {hex(d['obj'])} "
          f"state=+0x{d['state_off']:X} inc=+0x{gr.off['rng_inc_off']:X} "
          f"seed=+0x{d['seed_off']:X} 校验模式={d['mode']}")
    print(f"[OK] state={d['state']}  seed={d['seed']}  inc={d['inc']}"
          f"（inc 应恒为 {PCG_INC}）")

    # ---------------- 差分采样 ----------------
    st0 = r.poll()
    t0 = time.time()
    samples: list = []
    while time.time() - t0 < args.diff_seconds:
        dd = gr.read_rng_state_detail()
        samples.append((round(time.time() - t0, 3),
                        dd["state"] if dd else None))
        time.sleep(args.interval)
    st1 = r.poll()
    cnt0 = st0.get("event_count") or 0
    cnt1 = st1.get("event_count") or 0
    in_battle = cnt1 > cnt0 or bool(st1.get("last_type") in (0,) )
    print(f"[..] 差分窗口内 CombatLog 事件 {cnt0} → {cnt1} "
          f"⇒ 判定{'战斗内' if in_battle else '战斗外'}")

    n_fail = n_same = n_adv = 0
    for (t0_, s0), (t1_, s1) in zip(samples, samples[1:]):
        if s0 is None or s1 is None:
            n_fail += 1
            print(f"[WARN] t={t1_} 读取失败")
            continue
        if s0 == s1:
            n_same += 1
            print(f"[..] t={t1_} state 不变（稳定）")
            continue
        k = pcg_match_forward(s0, s1)
        if k is None:
            n_fail += 1
            print(f"[FAIL] t={t1_} state 变化但 {1 << 20} 步内无 LCG 命中"
                  f"（读到的不是真 pcg.state！）")
        else:
            n_adv += 1
            print(f"[OK] t={t1_} state 前进 k={k} 步（LCG 命中）")

    ok = n_fail == 0 and n_fail + n_same + n_adv > 0
    if in_battle and n_adv == 0 and n_fail == 0:
        print("[WARN] 判定战斗内但 state 未前进——采样可能落在消费间隙，"
              "请重跑或延长窗口")
    if not ok:
        print(f"[FAIL] 差分校验未通过：稳定={n_same} 前进={n_adv} 失败={n_fail}")
        return 3
    verdict = ("战斗内链持续前进" if n_adv and in_battle else
               "战斗外读数稳定" if n_same and not n_adv else
               "存在链前进（历史界面动画等亦消费 Util.rng，docs/rng_truth.md §1.4-4）")
    print(f"[PASS] 差分校验通过：稳定={n_same} 前进={n_adv} 失败={n_fail}"
          f" —— {verdict}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
