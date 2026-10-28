# -*- coding: utf-8 -*-
"""test_recover.py — 中断对局补收尾（seal_run / seal_orphan_runs）单测

覆盖实机事故（2026-10-28）后的恢复路径：
* 进程被强杀 → meta.end_reason 为 null、最后一回合还是明文
* seal_run 归档明文、写 end_reason=crash、incomplete=true
* 幂等：已收尾的局再调一次不动
* 收尾后的局仍可折叠出样本
"""
from __future__ import annotations

import json
import os
import shutil
import sys
import unittest
from pathlib import Path

_HERE = os.path.dirname(os.path.abspath(__file__))
_ROOT = _HERE
while not os.path.exists(os.path.join(_ROOT, "core", "lineup.py")):
    parent = os.path.dirname(_ROOT)
    if parent == _ROOT:
        raise RuntimeError("未找到仓库根目录（core/lineup.py）")
    _ROOT = parent
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

from core.store import load_meta, seal_orphan_runs, seal_run  # noqa: E402
from tools.corpus_fold import fold_run  # noqa: E402

_TMP_ROOT = Path(_ROOT) / ".recorder_test_tmp"


def _mkdtemp(prefix: str) -> Path:
    _TMP_ROOT.mkdir(parents=True, exist_ok=True)
    for i in range(1000):
        p = _TMP_ROOT / f"{prefix}{os.getpid()}_{i}"
        if not p.exists():
            p.mkdir()
            return p
    raise RuntimeError("无法创建测试临时目录")


def _make_crashed_run(root: Path, name: str = "20260101_000000_r01") -> Path:
    """造一个"被强杀"的局：meta 无 end_reason + 最后一回合是明文。"""
    run = root / name
    (run / "raw").mkdir(parents=True)
    (run / "snapshots").mkdir(parents=True)
    (run / "meta.json").write_text(json.dumps({
        "schema": 4, "run_id": name, "character": "Ranger",
        "started_at": "2026-01-01T00:00:00", "ended_at": None,
        "end_reason": None, "incomplete": False,
        "recorder": {"version": "4.0.0",
                     "config": {"compress": "lzma"}},
    }, ensure_ascii=False), encoding="utf-8")
    snap = {"round": 1, "gold": 10, "hp": 5, "character": "Ranger",
            "backpack": {"version": 4, "grid": [7, 9], "items": []},
            "storage": [], "shop": [
                {"slot": 0, "id": "Dagger", "price": 3, "normal_price": 3,
                 "on_sale": False, "free": False, "bought": False,
                 "reserved": False}]}
    (run / "snapshots" / "R01_shop_open.json").write_text(
        json.dumps(snap, ensure_ascii=False), encoding="utf-8")
    events = [
        {"seq": 1, "t": 0.0, "type": "run_start", "round": 1, "phase": "shop",
         "source": "recorder", "confidence": 1.0, "action": {},
         "anchor": "snapshots/R01_shop_open.json"},
        {"seq": 2, "t": 1.0, "type": "buy", "round": 1, "phase": "shop",
         "source": "diff", "confidence": 0.95,
         "action": {"slot": 0, "id": "Dagger", "price": 3,
                    "price_source": "decoded"},
         "delta": {"gold": -3}, "anchor": "snapshots/R01_shop_open.json"},
    ]
    with open(run / "raw" / "R01.jsonl", "w", encoding="utf-8", newline="\n") as f:
        for ev in events:
            f.write(json.dumps(ev, ensure_ascii=False) + "\n")
    return run


class TestSealRun(unittest.TestCase):
    def setUp(self):
        self.tmp = _mkdtemp("recover_")

    def tearDown(self):
        shutil.rmtree(self.tmp, ignore_errors=True)

    def test_seal_archives_and_marks_crash(self):
        run = _make_crashed_run(self.tmp)
        self.assertEqual(load_meta(run).get("end_reason"), None)
        self.assertTrue((run / "raw" / "R01.jsonl").exists())

        meta = seal_run(run, reason="crash")
        self.assertIsNotNone(meta)
        self.assertEqual(meta["end_reason"], "crash")
        self.assertTrue(meta["incomplete"])
        self.assertTrue(meta["sealed_after_crash"])
        self.assertTrue(meta["ended_at"])
        # 明文已归档
        self.assertFalse((run / "raw" / "R01.jsonl").exists())
        self.assertTrue((run / "raw" / "R01.jsonl.xz").exists())

    def test_seal_is_idempotent(self):
        run = _make_crashed_run(self.tmp)
        first = seal_run(run, reason="crash")
        self.assertIsNotNone(first)
        second = seal_run(run, reason="crash")
        self.assertIsNone(second)          # 已收尾 → 不再改

    def test_sealed_run_is_still_foldable(self):
        run = _make_crashed_run(self.tmp)
        seal_run(run, reason="crash")
        decisions, lineups, stats, _t = fold_run(run)
        self.assertGreaterEqual(stats.decisions, 1)
        self.assertEqual(decisions[0]["actions"][0]["kind"], "buy")

    def test_seal_orphan_runs_scans_directory(self):
        _make_crashed_run(self.tmp, "20260101_000000_r01")
        _make_crashed_run(self.tmp, "20260102_000000_r01")
        done = seal_orphan_runs(self.tmp)
        self.assertEqual(len(done), 2)
        # 再扫一次没有新东西
        self.assertEqual(seal_orphan_runs(self.tmp), [])

    def test_missing_meta_returns_none(self):
        empty = self.tmp / "empty"
        (empty / "raw").mkdir(parents=True)
        self.assertIsNone(seal_run(empty))


if __name__ == "__main__":
    unittest.main(verbosity=2)
