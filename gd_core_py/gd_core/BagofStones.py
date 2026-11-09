# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class BagofStones(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core/BagofStones.gd"


	def canAffect(self, item):
		return item.hasTag(_H_1)


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.setBagOfStones()


	def getAffectedCellsAfterRotate_primary(self, rotatedCells):
		return self.ctx.player.INVENTORY.getCellsInLine(rotatedCells, Vector2.UP, 1)


	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core/BagofStones.gd", BagofStones)
_R.reg("BagofStones", BagofStones)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Tag.Stone
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
