# -*- coding: utf-8 -*-
"""test_kernel_reset.py — ai/kernel_reset.py 的确定性回归测试

直接运行：  python ai/tests/test_kernel_reset.py
（或 python -m unittest ai.tests.test_kernel_reset）

背景：gd_core_py 有进程级全局态（裸 arr.shuffle() 的全局 Math RNG 与
get_instance_id() 单调计数器，见 ai/kernel_reset.py 文件头），逐局不重置时
『(输入, seed) → 胜负』在同进程内不成立——修复前实测
CombatLog_20261001_221121_R19_Loss、seed=101 同进程连跑 6 次 → [1,1,0,1,1,1]。

覆盖（对应缺陷复盘的三条实测证据）：
  * 证据②（同进程同 seed 漂移）：重置后同 seed 连跑多次逐局一致；
  * 证据①（三种历史三个结果）：『异阵容热身 10 局后再跑』与净进程跑
    逐 seed 结果完全一致；
  * 证据③（跨进程/哈希序）：PYTHONHASHSEED 不同的全新子进程结果一致，
    且与进程内一致。

子进程 worker 模式：`python ai/tests/test_kernel_reset.py --worker
<player.json> <opponent.json> <seed> <n>` —— 重置态跑 n 局、stdout 末行打
JSON 结果数组（供跨 PYTHONHASHSEED 对照用）。

注意：全程每局前 reset_kernel_state()；单局 ~0.25s，整套 <1min。
"""
from __future__ import annotations

import json
import os
import subprocess
import sys
import unittest

_HERE = os.path.dirname(os.path.abspath(__file__))
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

from ai.kernel_reset import reset_kernel_state                 # noqa: E402
from simulator.gd_core_engine import GDCoreEngine              # noqa: E402
from simulator.lineup import load_lineup                       # noqa: E402

_LOG_DIR = os.path.join(_ROOT, "dist", "output", "combat_logs")

# 组2 = 本轮漂移最大的局（原 6/10 档）；组1/组3/组4 = 对照实录（另几档胜率）
G2 = os.path.join(_LOG_DIR, "CombatLog_20261001_221121_R19_Loss")
G1 = os.path.join(_LOG_DIR, "CombatLog_20261001_221048_R19_Loss")
G3 = os.path.join(_LOG_DIR, "CombatLog_20261002_002502_R19_Loss")
G4 = os.path.join(_LOG_DIR, "CombatLog_20261002_002548_R19_Loss")


def _sides(group_dir: str):
    """组目录 → (player_v3, opponent_v3)；实录缺失时返回 None（测试跳过）。"""
    p = os.path.join(group_dir, os.path.basename(group_dir) + ".Player.json")
    o = os.path.join(group_dir, os.path.basename(group_dir) + ".Opponent.json")
    if not (os.path.isfile(p) and os.path.isfile(o)):
        return None
    return load_lineup(p), load_lineup(o)


def _run_one(player_v3, opp_v3, seed: int) -> int:
    """重置内核全局态后跑一局（与修复后 eval.py 的 run_match 同口径）。"""
    reset_kernel_state()
    eng = GDCoreEngine(player_v3, opp_v3, {}, {}, seed=seed)
    eng.run()
    return int(eng.player_wins())


def _run_seq(player_v3, opp_v3, seed0: int, n: int) -> list:
    return [_run_one(player_v3, opp_v3, seed0 + i) for i in range(n)]


def _worker(player_path: str, opp_path: str, seed: int, n: int) -> list:
    """worker 模式：全新子进程里重置态跑 n 局，stdout 末行 = JSON 数组。"""
    cmd = [sys.executable, os.path.abspath(__file__), "--worker",
           player_path, opp_path, str(seed), str(n)]
    env = dict(os.environ)
    proc = subprocess.run(cmd, cwd=_ROOT, capture_output=True, text=True,
                          encoding="utf-8", env=env, timeout=600)
    if proc.returncode != 0:
        raise AssertionError("worker 退出码 %d: %s" % (proc.returncode, proc.stderr[-500:]))
    lines = [ln for ln in proc.stdout.splitlines() if ln.strip()]
    return json.loads(lines[-1])


class TestKernelResetDeterminism(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.g2 = _sides(G2)
        cls.g1 = _sides(G1)
        cls.g3 = _sides(G3)
        cls.g4 = _sides(G4)

    def _need(self, sides, group):
        if sides is None:
            self.skipTest("实录缺失: %s" % group)

    # ── 证据②：同进程同 seed 连跑 → 逐局一致（修复前 [1,1,0,1,1,1]）──
    def test_same_seed_repeated_runs_identical(self):
        self._need(self.g2, G2)
        p, o = self.g2
        seq = [_run_one(p, o, 101) for _ in range(8)]
        self.assertEqual(len(set(seq)), 1,
                         "同 seed 同阵容连跑出现不同结局: %s" % seq)

    # ── 证据①：先跑 3 组其他对局热身再跑 → 与净进程逐 seed 一致 ──
    def test_warm_three_groups_matches_fresh_process(self):
        self._need(self.g2, G2)
        self._need(self.g1, G1)
        self._need(self.g3, G3)
        self._need(self.g4, G4)
        p, o = self.g2
        cold = _run_seq(p, o, 101, 10)
        # 先各跑 3 组异阵容实录的 10 局（同样逐局重置）再跑组2 的 10 局
        _run_seq(*self.g1, seed0=201, n=10)
        _run_seq(*self.g3, seed0=301, n=10)
        _run_seq(*self.g4, seed0=401, n=10)
        warm = _run_seq(p, o, 101, 10)
        self.assertEqual(cold, warm,
                         "进程历史改变了逐 seed 结果:\n cold=%s\n warm=%s"
                         % (cold, warm))
        # warm 序列还必须与**全新子进程**（净进程跑同阵容同 seeds）一致
        p_path = os.path.join(G2, os.path.basename(G2) + ".Player.json")
        o_path = os.path.join(G2, os.path.basename(G2) + ".Opponent.json")
        fresh = _worker(p_path, o_path, 101, 10)
        self.assertEqual(warm, fresh,
                         "热身后与全新进程不一致:\n warm=%s\n fresh=%s"
                         % (warm, fresh))

    # ── 证据①：异阵容热身 10 局后再跑 → 与净进程逐 seed 一致 ──
    def test_history_independence(self):
        self._need(self.g2, G2)
        self._need(self.g1, G1)
        p, o = self.g2
        cold = _run_seq(p, o, 101, 10)
        # 先跑组1 的 10 局（同样逐局重置）再跑组2 的 10 局
        _run_seq(*self.g1, seed0=201, n=10)
        warm = _run_seq(p, o, 101, 10)
        self.assertEqual(cold, warm,
                         "进程历史改变了逐 seed 结果:\n cold=%s\n warm=%s"
                         % (cold, warm))

    # ── 证据③：不同 PYTHONHASHSEED 的全新子进程彼此一致，且与进程内一致 ──
    def test_cross_process_and_hashseed(self):
        self._need(self.g2, G2)
        p_path = os.path.join(G2, os.path.basename(G2) + ".Player.json")
        o_path = os.path.join(G2, os.path.basename(G2) + ".Opponent.json")
        in_proc = _run_seq(*self.g2, seed0=101, n=10)
        for hs in ("1", "2"):
            env_p, env_o = p_path, o_path
            cmd = [sys.executable, os.path.abspath(__file__), "--worker",
                   env_p, env_o, "101", "10"]
            env = dict(os.environ, PYTHONHASHSEED=hs)
            proc = subprocess.run(cmd, cwd=_ROOT, capture_output=True,
                                  text=True, encoding="utf-8", env=env,
                                  timeout=600)
            self.assertEqual(proc.returncode, 0, proc.stderr[-500:])
            lines = [ln for ln in proc.stdout.splitlines() if ln.strip()]
            got = json.loads(lines[-1])
            self.assertEqual(got, in_proc,
                             "PYTHONHASHSEED=%s 的子进程与进程内不一致: %s vs %s"
                             % (hs, got, in_proc))

    # ── 抽查另一档胜率的实录（对照，防『恰好不敏感』）──
    def test_other_group_history_independence(self):
        self._need(self.g3, G3)
        self._need(self.g1, G1)
        p, o = self.g3
        cold = _run_seq(p, o, 101, 5)
        _run_seq(*self.g1, seed0=301, n=5)
        warm = _run_seq(p, o, 101, 5)
        self.assertEqual(cold, warm,
                         "组3 也受进程历史影响:\n cold=%s\n warm=%s" % (cold, warm))

    # ── 根治验证：完全不走 reset_kernel_state() 的裸路径也必须确定 ──
    # （每局 reset 会掩盖内核回归，这条直接守 gd_core_py 内的根治本身。
    #   修复前实测：净进程同 seed 连跑 6 次 → [1,1,0,1,1,1]；
    #   异阵容热身后再跑 → [1,0,0,1,0,0]。）
    def test_no_reset_raw_determinism(self):
        self._need(self.g2, G2)
        self._need(self.g1, G1)
        p, o = self.g2

        def raw_same_seed():
            seq = []
            for _ in range(8):
                eng = GDCoreEngine(p, o, {}, {}, seed=101)
                eng.run()
                seq.append(int(eng.player_wins()))
            return seq

        def raw_seq(seed0, n):
            seq = []
            for i in range(n):
                eng = GDCoreEngine(p, o, {}, {}, seed=seed0 + i)
                eng.run()
                seq.append(int(eng.player_wins()))
            return seq

        rep = raw_same_seed()
        self.assertEqual(len(set(rep)), 1,
                         "不 reset 时同 seed 连跑漂移: %s" % rep)
        cold = raw_seq(101, 10)
        _run_seq(*self.g1, seed0=201, n=5)      # 异阵容热身（正常 reset 口径）
        warm = raw_seq(101, 10)
        self.assertEqual(cold, warm,
                         "不 reset 时进程历史改变逐 seed 结果:\n cold=%s\n warm=%s"
                         % (cold, warm))


def _worker_main(argv):
    """--worker 模式：净进程 + 重置态跑 n 局，stdout 末行打 JSON。"""
    player_path, opp_path, seed, n = argv[0], argv[1], int(argv[2]), int(argv[3])
    player_v3 = load_lineup(player_path)
    opp_v3 = load_lineup(opp_path)
    res = [_run_one(player_v3, opp_v3, seed + i) for i in range(n)]
    print(json.dumps(res))
    return 0


if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "--worker":
        raise SystemExit(_worker_main(sys.argv[2:]))
    unittest.main(verbosity=2)
