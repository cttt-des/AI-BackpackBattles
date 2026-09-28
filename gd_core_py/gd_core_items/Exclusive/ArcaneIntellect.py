# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ArcaneIntellect(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ArcaneIntellect.gd"

	def _init_fields(self):
		super()._init_fields()
		self.magicSpeed = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Magic) and item.hasCooldown()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.addSpeed(self.magicSpeed)



	def getRandomScroll(self):
		pass

	def getRandomBook(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.magicSpeed = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/ArcaneIntellect.gd", Exclusive__ArcaneIntellect)
_R.reg("ArcaneIntellect", Exclusive__ArcaneIntellect)
