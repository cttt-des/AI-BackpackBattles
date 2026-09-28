# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class BagofStones(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/BagofStones.gd"


	def canAffect(self, item):
		return item.hasTag(_R.C("CoreConst").Tag.Stone)


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.setBagOfStones()


	def getAffectedCellsAfterRotate_primary(self, rotatedCells):
		return self.ctx.player.INVENTORY.getCellsInLine(rotatedCells, Vector2.UP, 1)


	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/BagofStones.gd", BagofStones)
_R.reg("BagofStones", BagofStones)
