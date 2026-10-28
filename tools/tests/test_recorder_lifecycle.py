# -*- coding: utf-8 -*-
"""test_recorder_lifecycle.py — 记录器端到端（假 bot，无游戏进程）

用假 bot 依次吐出几帧状态，验证：
* 开局目录/meta 生成、raw 分片写入、回合切换分片
* combat_start 快照生成、combat_end 事件
* 停止时归档为 .xz 且明文消失
* 归档后的记录仍可被 corpus_fold 折叠
"""
from __future__ import annotations

import json
import os
import shutil
import sys
import time
import unittest
from pathlib import Path

_HERE = os.path.dirname(os.path.abspath(__file__))
# 向上找到仓库根（含 core/lineup.py 的目录），不依赖测试文件所在的层级
_ROOT = _HERE
while not os.path.exists(os.path.join(_ROOT, "core", "lineup.py")):
    parent = os.path.dirname(_ROOT)
    if parent == _ROOT:
        raise RuntimeError("未找到仓库根目录（core/lineup.py）")
    _ROOT = parent
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

from core.recorder import Recorder, RecorderConfig  # noqa: E402
from core.store import iter_run_events, load_meta  # noqa: E402
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


class FakeItemReader:
    def __init__(self, lineups=None):
        self.lineups = lineups or {"player": [], "opponent": []}

    def read_fight_lineups(self):
        return self.lineups


class FakeBot:
    """按脚本吐状态：每调用一次 get_state() 前进一帧。"""

    def __init__(self, frames):
        self.frames = list(frames)
        self.i = 0
        self.memory_reader = None
        self.godot_reader = None
        self.item_reader = FakeItemReader()

    def get_state(self):
        if not self.frames:
            return None
        idx = min(self.i, len(self.frames) - 1)
        self.i += 1
        return self.frames[idx]

    def read_character(self):
        return "Ranger"


def _state(round_=1, gold=10, hp=5, backpack=(), storage=(), shop=(), combat=False):
    live = {
        "backpack": [{"name": n, "row": r, "col": c, "rotation": 0.0, "cells": [(r, c)]}
                     for (n, r, c) in backpack],
        "storage": [{"name": n, "row": 0, "col": 0, "rotation": 0.0, "cells": []}
                    for n in storage],
        "shop": [{"slot": s, "name": n, "price": p, "normal_price": p,
                  "on_sale": False, "free": False, "bought": b, "reserved": rv}
                 for (s, n, p, b, rv) in shop],
    }
    return {"gold": gold, "hp": hp, "round": round_, "wins": 0, "losses": 0,
            "character": "Ranger", "live_items": live, "game_state": None}


class TestRecorderLifecycle(unittest.TestCase):
    def setUp(self):
        self.tmp = _mkdtemp("lifecycle_")

    def tearDown(self):
        shutil.rmtree(self.tmp, ignore_errors=True)

    def _run(self, frames, compress="lzma", stop_reason="user_stop"):
        cfg = RecorderConfig(enabled=True, out_dir=str(self.tmp), interval_ms=20,
                             adaptive_interval=False, combat_interval_ms=20,
                             confirm_frames=2, compress=compress,
                             auto_stop_on_title=False, gap_threshold_ms=50)
        bot = FakeBot(frames)
        rec = Recorder(bot, cfg)
        self.assertTrue(rec.start())
        # 等采样跑完脚本帧数
        deadline = time.time() + 5.0
        while bot.i < len(frames) and time.time() < deadline:
            time.sleep(0.01)
        time.sleep(0.1)
        rec.stop(stop_reason)
        return rec

    def test_full_run_directory_and_archive(self):
        frames = [
            _state(1, 10, 5, shop=[(0, "Dagger", 3, False, False)]),
            _state(1, 10, 5, shop=[(0, "Dagger", 3, False, False)]),   # 重复帧 → 丢弃
            _state(1, 7, 5, shop=[(0, "Dagger", 3, True, False)],
                   storage=["Dagger"]),
            _state(1, 7, 5, backpack=[("Dagger", 2, 3)],
                   shop=[(0, "Dagger", 3, True, False)]),
            _state(2, 7, 5, backpack=[("Dagger", 2, 3)],
                   shop=[(0, "Sword", 5, False, False)]),
        ]
        rec = self._run(frames)
        run_dir = Path(rec.cfg.out_dir) / rec.run_id
        self.assertTrue((run_dir / "meta.json").exists())
        meta = load_meta(run_dir)
        self.assertEqual(meta.get("schema"), 4)
        self.assertEqual(meta.get("end_reason"), "user_stop")

        events = list(iter_run_events(run_dir))
        types = [ev.get("type") for _r, ev in events]
        self.assertIn("run_start", types)
        self.assertIn("buy", types)
        self.assertGreaterEqual(len(events), 3)

        # 归档：明文消失，出现 .xz
        raw_files = list((run_dir / "raw").iterdir())
        self.assertTrue(any(p.suffix == ".xz" for p in raw_files
                            if p.name.endswith(".jsonl.xz")),
                        f"未归档: {[p.name for p in raw_files]}")
        self.assertFalse(any(p.name.endswith(".jsonl") for p in raw_files),
                         "归档后不应残留明文分片")

        # 快照存在且可折叠
        snaps = list((run_dir / "snapshots").glob("*_shop_open.json"))
        self.assertTrue(snaps, "缺少回合商店快照")
        decisions, lineups, stats, _traces = fold_run(run_dir)
        self.assertGreaterEqual(stats.decisions, 0)

    def test_combat_snapshot_written(self):
        frames = [
            _state(1, 10, 5, shop=[(0, "Dagger", 3, False, False)]),
            # 战斗帧：背包有物品、无商店 → phase=combat
            # （去抖要求变化稳定两帧，故战斗帧连给两次）
            _state(1, 10, 5, backpack=[("Dagger", 2, 3)]),
            _state(1, 10, 5, backpack=[("Dagger", 2, 3)]),
            _state(1, 10, 5, backpack=[("Dagger", 2, 3)]),
            # 回到商店
            _state(1, 8, 4, backpack=[("Dagger", 2, 3)],
                   shop=[(0, "Sword", 5, False, False)]),
            _state(1, 8, 4, backpack=[("Dagger", 2, 3)],
                   shop=[(0, "Sword", 5, False, False)]),
        ]
        bot = FakeBot(frames)
        bot.item_reader = FakeItemReader({
            "player": [{"name": "Dagger", "row": 2, "col": 3, "rotation": 0.0,
                        "cells": [(2, 3)], "gems": [], "contents": []}],
            "opponent": [{"name": "Sword", "row": 1, "col": 1, "rotation": 0.0,
                          "cells": [(1, 1)], "gems": [], "contents": []}],
        })
        cfg = RecorderConfig(enabled=True, out_dir=str(self.tmp), interval_ms=20,
                             adaptive_interval=False, combat_interval_ms=20,
                             confirm_frames=2, auto_stop_on_title=False)
        rec = Recorder(bot, cfg)
        self.assertTrue(rec.start())
        deadline = time.time() + 5.0
        while bot.i < len(frames) and time.time() < deadline:
            time.sleep(0.01)
        time.sleep(0.1)
        rec.stop("test_done")
        run_dir = Path(cfg.out_dir) / rec.run_id
        snaps = list((run_dir / "snapshots").glob("*_combat_start.json"))
        self.assertTrue(snaps, "缺少开战快照")
        data = json.loads(snaps[0].read_text(encoding="utf-8"))
        self.assertIn("backpack", data)
        self.assertEqual(data["backpack"]["items"][0]["id"], "Dagger")
        self.assertEqual(data.get("opponent", {}).get("items", [{}])[0].get("id"),
                         "Sword")

    def test_compress_none_keeps_plaintext(self):
        frames = [_state(1, 10, 5, shop=[(0, "Dagger", 3, False, False)]),
                  _state(1, 7, 5, shop=[(0, "Dagger", 3, True, False)],
                         storage=["Dagger"])]
        rec = self._run(frames, compress="none")
        run_dir = Path(rec.cfg.out_dir) / rec.run_id
        plains = [p for p in (run_dir / "raw").iterdir()
                  if p.name.endswith(".jsonl")]
        self.assertTrue(plains, "compress=none 时应保留明文")


if __name__ == "__main__":
    unittest.main(verbosity=2)