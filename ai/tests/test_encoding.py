# -*- coding: utf-8 -*-
"""test_encoding.py — ai/encoding.py 的单元测试

直接运行：  python ai/tests/test_encoding.py
（或 python -m unittest ai.tests.test_encoding）

覆盖：
  * 旋转坐标变换与引擎逐物品一致（对照 simulator/grid.py 的
    rotate_and_normalize / rotate_cell、simulator/gd_core_engine.py 的
    _place_of、simulator/combat.py 的 GridInventory 装配）；
  * 真值实录（dist/output/combat_logs）阵容的逐物品占格/影响格断言；
  * 四个旋转角、宝石多热、袋内物品（bag contents）不崩、空背包、
    未知物品（GoldCounter 等）跳过、v3 内部形状、非法旋转角。
"""
from __future__ import annotations

import glob
import json
import os
import sys
import unittest

import numpy as np

_HERE = os.path.dirname(os.path.abspath(__file__))
_ROOT = os.path.dirname(os.path.dirname(_HERE))
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

from ai.encoding import (AFFECTED_COLORS, COLS, ROWS, encode_lineup,
                         item_geometry, rot_index, rotate_and_normalize,
                         rotate_cell, to_abs)

from simulator.grid import (rotate_and_normalize as engine_rotate_and_normalize,
                            rotate_cell as engine_rotate_cell)
from simulator.lineup import load_lineup


def _load_json(path):
    with open(path, encoding="utf-8") as f:
        return json.load(f)


RUNTIME_DB = _load_json(os.path.join(_ROOT, "assets", "gd_core_runtime.json"))
BATTLE_DB = _load_json(os.path.join(_ROOT, "assets", "battle_items.json"))["items"]
ITEMS = RUNTIME_DB["items"]
CLASSES = RUNTIME_DB.get("classes") or {}

_LOG_DIR = os.path.join(_ROOT, "dist", "output", "combat_logs")
GT_PLAYERS = sorted(glob.glob(os.path.join(_LOG_DIR, "*", "CombatLog_*.Player.json")))


def _pair_of(player_path):
    return player_path.replace(".Player.json", ".Opponent.json")


def _lineup_fully_known(player_path):
    """阵容双方的所有物品与宝石都在运行时库里（引擎对照测试用）。"""
    for path in (player_path, _pair_of(player_path)):
        d = _load_json(path)
        for it in d["items"]:
            if it["id"] not in ITEMS:
                return False
            for g in it.get("gems") or []:
                if g not in ITEMS:
                    return False
    return True


CLEAN_PLAYERS = [p for p in GT_PLAYERS if _lineup_fully_known(p)]


def _abs_cells(rel_cells, row, col):
    """引擎风格的锚点系→绝对格换算（(x,y)→(row+y, col+x)），供断言书写。"""
    return sorted({(row + y, col + x) for (x, y) in rel_cells})


# ═══════════════════════ 旋转变换 × 全物品库逐物品断言 ═══════════════════════

class TestRotationParity(unittest.TestCase):
    """旋转 90/180/270 的坐标变换必须和引擎一致（全库 517 件 × 4 角）。"""

    def test_asset_matches_engine_rotate_and_normalize(self):
        """资产自洽：simulator/grid.py 的 rotate_and_normalize 作用在 0°
        collision 上必须复现 rot 表的各角度 collision（引擎旋转实现的镜像）。"""
        bad = []
        for key, ent in ITEMS.items():
            rot0 = ent["rot"]["0"]["collision"]
            for ang in (0, 90, 180, 270):
                expect = sorted(tuple(c) for c in ent["rot"][str(ang)]["collision"])
                got = engine_rotate_and_normalize([tuple(c) for c in rot0], ang)
                if got != expect:
                    bad.append((key, ang, expect, got))
        self.assertEqual(bad, [],
                         "rot 表与 grid.py 旋转不一致（前 5 处）：%s" % (bad[:5],))

    def test_my_rotate_cell_matches_engine(self):
        """本模块 rotate_cell / rotate_and_normalize 与 simulator/grid.py 逐字一致。"""
        probe = {(x, y) for x in range(-3, 4) for y in range(-3, 4)}
        for cell in probe:
            for ang in (0, 90, 180, 270):
                self.assertEqual(rotate_cell(cell, ang), engine_rotate_cell(cell, ang),
                                 "rotate_cell%s@%d" % (cell, ang))
        sample = ["Ace of Spades", "Falcon Blade", "Anvil", "Leather Bag",
                  "Berserker Bag", "Chipped Ruby"]
        for key in sample:
            cells = ITEMS[key]["rot"]["0"]["collision"]
            for ang in (0, 90, 180, 270):
                self.assertEqual(rotate_and_normalize(cells, ang),
                                 engine_rotate_and_normalize([tuple(c) for c in cells], ang),
                                 "rotate_and_normalize(%s)@%d" % (key, ang))

    def test_my_grid_fallback_matches_rot_tables(self):
        """本模块的旋转实现（grid 原生字段路径，走 rotate+归一化）必须复现
        rot 表的四个角度——对照 simulator/grid.py 与 gen_lineup_fixture 的
        placement_of 同一套变换。"""
        bad = []
        for key, ent in ITEMS.items():
            raw = BATTLE_DB.get(key, {}).get("grid")
            if not raw:
                continue
            fake = {"grid": raw}      # 走 encoding 的 grid 原生字段路径
            for ang in (0, 90, 180, 270):
                idx = rot_index(ang)
                col_mine, aff_mine = _geometry_of(fake, idx)
                pl = ent["rot"][str(ang)]
                if col_mine != sorted(tuple(c) for c in pl["collision"]):
                    bad.append((key, ang, "collision"))
                for color, cells in pl["affected"].items():
                    if aff_mine.get(int(color)) != sorted(tuple(c) for c in cells):
                        bad.append((key, ang, "affected[%s]" % color))
        self.assertEqual(bad, [], "grid 路径与 rot 表不一致（前 5 处）：%s" % (bad[:5],))

    def test_matches_gd_core_engine_place_of(self):
        """对照 simulator/gd_core_engine.py::_place_of（gd_core_py 内核的实际
        装配几何）：占格与四色影响格在摆位 (2,3) 处逐物品一致。"""
        from simulator.gd_core_engine import _place_of
        bad = []
        for key in ITEMS:
            for ang in (0, 90, 180, 270):
                pl = _place_of(RUNTIME_DB, key, 2, 3, ang)
                mine = item_geometry(key, ang, RUNTIME_DB, row=2, col=3)
                # _place_of 返回的 occupied/affected 已平移到绝对位（(x=col, y=row)
                # 序，x 已 +col、y 已 +row）→ (row,col) = (y, x)
                eng_occ = sorted({(c[1], c[0]) for c in pl["occupied"]})
                if mine["collision"] != eng_occ:
                    bad.append((key, ang, "collision", mine["collision"], eng_occ))
                eng_aff = {}
                for color, cells in pl["affected"].items():
                    eng_aff[int(color)] = sorted({(c[1], c[0]) for c in cells})
                if {c: s for c, s in mine["affected"].items() if s} != \
                   {c: s for c, s in eng_aff.items() if s}:
                    bad.append((key, ang, "affected", mine["affected"], eng_aff))
        self.assertEqual(bad, [], "与 gd_core _place_of 不一致（前 3 处）：%s" % (bad[:3],))


def _geometry_of(entry_like, idx):
    """走 encoding 内部的 grid 原生字段路径（测试辅助）。"""
    from ai.encoding import _entry_geometry
    return _entry_geometry(entry_like, idx)


# ═══════════════════════ 真值实录逐物品断言 ═══════════════════════

class TestGroundTruthLineups(unittest.TestCase):
    """用 dist/output/combat_logs 的真值实录阵容做逐物品断言。"""

    def test_per_item_collision_matches_old_engine_assembly(self):
        """与 simulator/combat.py 的 GridInventory 装配结果一致：旧引擎逐物品
        occupied_cells == 本编码器逐物品绝对占格；整包 collision_mask ==
        filled|bags 的指示矩阵。"""
        from simulator.combat import CombatEngine
        self.assertTrue(CLEAN_PLAYERS, "至少要有一套全已知物品的真值实录")
        for player_path in CLEAN_PLAYERS:
            with self.subTest(lineup=os.path.basename(player_path)):
                lu_p = load_lineup(player_path)
                lu_o = load_lineup(_pair_of(player_path))
                eng = CombatEngine(lu_p, lu_o, BATTLE_DB, {})
                inv = eng.player_inventory
                enc = encode_lineup(_load_json(player_path), RUNTIME_DB)

                engine_cells = set(inv.filled) | set(inv.bags)
                mask_cells = {(int(r), int(c)) for r, c in zip(*np.nonzero(enc["collision_mask"]))}
                self.assertEqual(mask_cells, engine_cells)

                engine_items = {(it.key, it.grid_row, it.grid_col, it.grid_rotation):
                                set(it.occupied_cells) for it in eng.player_items}
                for e in _flatten_of(player_path):
                    geo = item_geometry(e["id"], e["rotation"], RUNTIME_DB,
                                        row=e["row"], col=e["col"])
                    self.assertIsNotNone(geo, e["id"])
                    self.assertEqual(set(geo["collision"]),
                                     engine_items[(e["id"], e["row"], e["col"], e["rotation"] % 360)],
                                     "%s@(%d,%d,r%d)" % (e["id"], e["row"], e["col"], e["rotation"]))

    def test_per_item_affected_matches_gd_core_all_lineups(self):
        """全部真值实录（含带未知物品的）里、每个库内物品的四色影响格，
        与 gd_core 引擎 _place_of 的 affected 逐物品一致。"""
        from simulator.gd_core_engine import _place_of
        self.assertGreater(len(GT_PLAYERS), 0)
        checked = 0
        bad = []
        for player_path in GT_PLAYERS:
            for path in (player_path, _pair_of(player_path)):
                d = _load_json(path)
                for it in d["items"]:
                    if it["id"] not in ITEMS:
                        continue          # GoldCounter 等不可装配物品：跳过
                    row, col = it["at"]
                    ang = int(it.get("r", 0) or 0)
                    pl = _place_of(RUNTIME_DB, it["id"], int(row), int(col), ang)
                    eng_aff = {int(color): sorted({(c[1], c[0]) for c in cells})
                               for color, cells in pl["affected"].items()}
                    eng_aff = {c: s for c, s in eng_aff.items() if s}
                    mine = item_geometry(it["id"], ang, RUNTIME_DB, row=int(row), col=int(col))
                    mine_aff = {c: s for c, s in mine["affected"].items() if s}
                    checked += 1
                    if eng_aff != mine_aff:
                        bad.append((os.path.basename(path), it["id"], ang, mine_aff, eng_aff))
        self.assertGreater(checked, 500)
        self.assertEqual(bad, [], "影响格不一致（前 3 处）：%s" % (bad[:3],))

    def test_all_ground_truth_lineups_encode(self):
        """全部真值实录阵容可编码、形状正确、未知物品如实上报。"""
        self.assertGreater(len(GT_PLAYERS), 0)
        for player_path in GT_PLAYERS:
            with self.subTest(lineup=os.path.basename(player_path)):
                enc = encode_lineup(_load_json(player_path), RUNTIME_DB)
                self.assertEqual(enc["item_grid"].shape, (ROWS, COLS))
                self.assertEqual(enc["rotation_grid"].shape, (ROWS, COLS))
                self.assertEqual(enc["collision_mask"].shape, (ROWS, COLS))
                self.assertEqual(enc["affected_masks"].shape, (4, ROWS, COLS))
                # ids/root_ids = 根物品（引擎装配口径）；袋内物品不进编码
                flat = _flatten_of(player_path)
                roots = [e for e in flat if e["parent"] is None]
                bags = [e for e in flat if e["parent"] is not None]
                self.assertEqual(enc["ids"], [e["id"] for e in roots])
                self.assertEqual(enc["root_ids"], enc["ids"])
                self.assertEqual(len(enc["ids"]), int(enc["scalars"]["num_items"]))
                self.assertEqual(int(enc["scalars"]["bag_item_count"]), len(bags))
                self.assertEqual(len(enc["ids"]), int(enc["gem_onehot"].shape[0]))
                self.assertEqual(enc["gem_onehot"].shape,
                                 (len(enc["ids"]), len(enc["gem_ids"])))
                # 网格里画出的只有库内根物品（未知物品不画）；item_grid 置位格
                # 与 collision_mask 置位格严格同集（同一循环同一越界口径）
                unknown = set(enc["unknown_ids"])
                self.assertTrue(unknown <= set(enc["ids"]))
                drawn = set(np.unique(enc["item_grid"]).tolist()) - {-1}
                self.assertTrue(drawn <= set(range(len(enc["ids"]))))
                for k in drawn:
                    self.assertNotIn(enc["ids"][k], unknown)
                grid_cells = {(int(r), int(c))
                              for r, c in zip(*np.nonzero(enc["item_grid"] >= 0))}
                mask_cells = {(int(r), int(c))
                              for r, c in zip(*np.nonzero(enc["collision_mask"]))}
                self.assertEqual(grid_cells, mask_cells)


# ═══════════════════════ 基础行为 ═══════════════════════

class TestEncodingBasics(unittest.TestCase):
    def test_empty_backpack(self):
        enc = encode_lineup({"version": 4, "character": "Ranger", "items": []},
                            RUNTIME_DB)
        self.assertTrue((enc["item_grid"] == -1).all())
        self.assertTrue((enc["rotation_grid"] == -1).all())
        self.assertEqual(int(enc["collision_mask"].sum()), 0)
        self.assertEqual(int(enc["affected_masks"].sum()), 0)
        self.assertEqual(enc["ids"], [])
        self.assertEqual(int(enc["scalars"]["num_items"]), 0)
        self.assertEqual(int(enc["scalars"]["rarity_sum"]), 0)
        self.assertEqual(enc["scalars"]["class_onehot"][CLASSES["Ranger"]], 1.0)

    def test_four_rotations(self):
        """Falcon Blade（1×3）四个角：占格随角度转、旋转通道记 0..3。"""
        items = [{"id": "Falcon Blade", "at": [0, 0], "r": 0},
                 {"id": "Falcon Blade", "at": [0, 4], "r": 90},
                 {"id": "Falcon Blade", "at": [3, 0], "r": 180},
                 {"id": "Falcon Blade", "at": [4, 5], "r": 270}]
        enc = encode_lineup({"version": 4, "character": "Mage", "items": items},
                            RUNTIME_DB)
        for i, it in enumerate(items):
            expect = engine_rotate_and_normalize(
                [tuple(c) for c in ITEMS["Falcon Blade"]["rot"]["0"]["collision"]],
                it["r"])
            expect_abs = _abs_cells(expect, it["at"][0], it["at"][1])
            for (r, c) in expect_abs:
                self.assertEqual(int(enc["item_grid"][r, c]), i)
                self.assertEqual(int(enc["rotation_grid"][r, c]), it["r"] // 90)
            self.assertEqual(sorted((int(r), int(c)) for r, c in
                                    zip(*np.nonzero(enc["item_grid"] == i))),
                             expect_abs)
        self.assertEqual(sorted(np.unique(enc["rotation_grid"]).tolist()),
                         [-1, 0, 1, 2, 3])          # -1 = 空格
        # 四个角互不重叠 → 占格总数 = 4×3
        self.assertEqual(int(enc["collision_mask"].sum()), 12)

    def test_gems_onehot(self):
        items = [{"id": "Falcon Blade", "at": [0, 0], "r": 0,
                  "gems": ["Badger Rune", "Hawk Rune"]},
                 {"id": "Corrupted Armor", "at": [0, 2], "r": 0,
                  "gems": ["Chipped Emerald", "Chipped Emerald", "Chipped Emerald"]}]
        enc = encode_lineup({"version": 4, "character": "Berserker", "items": items},
                            RUNTIME_DB)
        self.assertEqual(enc["gem_ids"], ["Badger Rune", "Hawk Rune", "Chipped Emerald"])
        self.assertEqual(enc["gem_onehot"][0].tolist(), [1, 1, 0])
        # 同名三颗仍是一条 one-hot（多热语义）
        self.assertEqual(enc["gem_onehot"][1].tolist(), [0, 0, 1])
        self.assertEqual(int(enc["gem_onehot"].sum()), 3)

    def test_bag_contents_not_drawn(self):
        """袋内物品（in=…）不崩、但**不画进网格**、其宝石也不进宝石通道：
        引擎只装配根物品（simulator/lineup.py:98 的 roots、
        simulator/gd_core_engine.py::_build_side 只遍历顶层，宝石只对根物品
        setGem），编码层与引擎的可见物品集必须逐件一致。"""
        items = [{"id": "Leather Bag", "at": [2, 2], "r": 0},      # 2×2 袋
                 {"id": "Falcon Blade", "at": [2, 3], "r": 0, "in": 0,
                  "gems": ["Hawk Rune"]}]
        enc = encode_lineup({"version": 4, "character": "Adventurer", "items": items},
                            RUNTIME_DB)
        # 袋内物品不进编码：ids/root_ids 只含根物品
        self.assertEqual(enc["ids"], ["Leather Bag"])
        self.assertEqual(enc["root_ids"], ["Leather Bag"])
        # 袋内物品的宝石也不进词表/通道（引擎不装配袋内物品 → 不 setGem）
        self.assertEqual(enc["gem_ids"], [])
        self.assertEqual(enc["gem_onehot"].shape, (1, 0))
        # 袋内物品不画格：格子上是袋子本身
        self.assertEqual(int(enc["item_grid"][2, 3]), 0)
        self.assertEqual(int(enc["item_grid"][2, 2]), 0)
        # 2×2 占格全部置位（袋子的占格）
        for r, c in ((2, 2), (2, 3), (3, 2), (3, 3)):
            self.assertEqual(int(enc["collision_mask"][r, c]), 1)
        # 标量按引擎装配口径：num_items = 根物品数；袋内件数仅作信息参考
        self.assertEqual(int(enc["scalars"]["num_items"]), 1)
        self.assertEqual(int(enc["scalars"]["bag_item_count"]), 1)
        self.assertEqual(int(enc["scalars"]["rarity_sum"]),
                         int(ITEMS["Leather Bag"]["descr"]["rarity"]))

    def test_v3_internal_shape(self):
        lineup = {
            "version": 3, "meta": {"name": "t"}, "character": "Mage",
            "backpack": {"grid": {"rows": 7, "cols": 9}, "items": [
                {"id": "Leather Bag", "row": 1, "col": 1, "rotation": 0,
                 "container": True,
                 "contents": [{"id": "Chipped Ruby", "row": 1, "col": 1,
                               "rotation": 0,
                               "gems": [{"id": "Badger Rune"}]}]},
            ]},
        }
        enc = encode_lineup(lineup, RUNTIME_DB)
        self.assertEqual(enc["ids"], ["Leather Bag"])
        self.assertEqual(enc["root_ids"], ["Leather Bag"])
        self.assertEqual(int(enc["item_grid"][1, 1]), 0)   # 袋内物品不画：袋子占格
        self.assertEqual(int(enc["scalars"]["num_items"]), 1)
        self.assertEqual(int(enc["scalars"]["bag_item_count"]), 1)
        # 袋内物品的宝石也不进词表/通道（引擎不装配袋内物品 → 不 setGem）
        self.assertEqual(enc["gem_ids"], [])
        self.assertEqual(enc["gem_onehot"].shape, (1, 0))

    def test_unknown_item_skipped(self):
        """真值实录里的不可装配物品（GoldCounter 等）跳过不崩、如实上报。"""
        items = [{"id": "Falcon Blade", "at": [0, 0], "r": 0},
                 {"id": "GoldCounter", "at": [3, 3], "r": 0},
                 {"id": "Chipped Ruby", "at": [0, 4], "r": 0, "in": 1}]
        enc = encode_lineup({"version": 4, "character": "Ranger", "items": items},
                            RUNTIME_DB)
        self.assertEqual(enc["unknown_ids"], ["GoldCounter"])
        # ids 只含根物品（袋内宝石物品不进编码）
        self.assertEqual(enc["ids"], ["Falcon Blade", "GoldCounter"])
        # 未知物品不画格（下标 1 不出现在任何格里）→ 网格里只有鹰爪刃 3 格
        self.assertEqual(int((enc["item_grid"] >= 0).sum()), 3)
        self.assertNotIn(1, np.unique(enc["item_grid"]).tolist())
        # num_items = 根物品数（含未知根物品）；袋内件数仅作信息参考
        self.assertEqual(int(enc["scalars"]["num_items"]), 2)
        self.assertEqual(int(enc["scalars"]["bag_item_count"]), 1)

    def test_engine_visible_alignment(self):
        """编码可见物品集 == gd_core 引擎实际装配集合：v4 平铺阵容里带 in=
        的物品引擎不装配，编码层同样不画；根物品则逐件占格一致。"""
        items = [{"id": "Falcon Blade", "at": [0, 0], "r": 0},
                 {"id": "Chipped Ruby", "at": [0, 4], "r": 0, "in": 0},
                 {"id": "Anvil", "at": [3, 3], "r": 0}]
        enc = encode_lineup({"version": 4, "character": "Ranger", "items": items},
                            RUNTIME_DB)
        drawn = set(enc["ids"][int(i)] for i in np.unique(enc["item_grid"]) if i >= 0)
        self.assertEqual(drawn, {"Falcon Blade", "Anvil"})
        self.assertEqual(enc["root_ids"], ["Falcon Blade", "Anvil"])
        self.assertEqual(int(enc["scalars"]["num_items"]), 2)

    def test_affected_mask_matches_item_geometry(self):
        """Anvil（多色影响格、含负偏移）的掩码 = 逐物品几何的并集，越界裁剪。"""
        items = [{"id": "Anvil", "at": [0, 0], "r": 0},
                 {"id": "Anvil", "at": [3, 3], "r": 90}]
        enc = encode_lineup({"version": 4, "character": "Engineer", "items": items},
                            RUNTIME_DB)
        for ch in range(4):
            mask_cells = {(int(r), int(c)) for r, c in
                          zip(*np.nonzero(enc["affected_masks"][ch]))}
            union = set()
            for it in items:
                geo = item_geometry(it["id"], it["r"], RUNTIME_DB,
                                    row=it["at"][0], col=it["at"][1])
                union |= set(geo["affected"].get(ch, []))
            in_bounds = {(r, c) for (r, c) in union if 0 <= r < ROWS and 0 <= c < COLS}
            self.assertEqual(mask_cells, in_bounds, "颜色 %d" % ch)

    def test_invalid_rotation_raises(self):
        with self.assertRaises(ValueError):
            rot_index(45)
        with self.assertRaises(ValueError):
            encode_lineup({"version": 4, "character": "Mage",
                           "items": [{"id": "Anvil", "at": [0, 0], "r": 45}]},
                          RUNTIME_DB)

    def test_scalars(self):
        items = [{"id": "Ace of Spades", "at": [0, 0], "r": 0},   # rarity 1
                 {"id": "Chipped Ruby", "at": [0, 2], "r": 0}]    # rarity 0
        enc = encode_lineup({"version": 4, "character": "Pyromancer",
                             "class_modifiers": {"health": 40}, "items": items},
                            RUNTIME_DB)
        self.assertEqual(int(enc["scalars"]["num_items"]), 2)
        self.assertEqual(int(enc["scalars"]["rarity_sum"]), 1)
        self.assertEqual(int(enc["scalars"]["class_id"]), CLASSES["Pyromancer"])
        self.assertEqual(int(enc["scalars"]["class_onehot"].argmax()),
                         CLASSES["Pyromancer"])


def _flatten_of(player_path):
    """真值 v4 平铺条目（测试辅助）。"""
    from ai.encoding import _flatten
    return _flatten(_load_json(player_path))


if __name__ == "__main__":
    unittest.main(verbosity=2)
