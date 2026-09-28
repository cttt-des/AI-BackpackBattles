# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__AmuletofFeasting(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/AmuletofFeasting.gd"

	def _init_fields(self):
		super()._init_fields()
		self.foodSpeed = None

	amuletColor = Color(0.929412, 0.498039, 0.180392)

	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Food)


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.addSpeed(self.foodSpeed)


	def getReplaceDescriptor(self, rarity):
		return None

	def getRelatedItems(self):
		pass

	def getRelatedItemColumns(self):
		return 4

	def _readyInit(self):
		super()._readyInit()
		self.foodSpeed = _div(self.getP('foodspeed'), 100.0)
		pass



_R.reg("res://gd_core_items/Exclusive/AmuletofFeasting.gd", Exclusive__AmuletofFeasting)
_R.reg("AmuletofFeasting", Exclusive__AmuletofFeasting)
