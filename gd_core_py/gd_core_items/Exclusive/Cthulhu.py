# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Cthulhu(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Cthulhu.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedFood = []
		self.foodSpeed = None
		self.dam = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Food) or item.hasType(_R.C("CoreConst").Type.Dark)










	def onAffectedItemAdded(self, item, color):
		if item.hasType(_R.C("CoreConst").Type.Food):
			item.addDynamicType(_R.C("CoreConst").Type.Dark, self)


	def onAffectedItemRemoved(self, item, color):
		item.removeDynamicType(_R.C("CoreConst").Type.Dark, self)


	def onPrepare(self):
		self.affectedFood.clear()
		for item in _iter(self.getAffectedItems()):
			if item.hasType(_R.C("CoreConst").Type.Food):
				self.affectedFood.append(item)

		self.addSpeed(self.foodSpeed * self.getNumAffectedItems())


	def doCooldownEffect(self):
		self.stealLife(self.dam, _div(self.getP_m('lifesteal'), 100.0))
		self.activate()
		if not (not self.affectedFood):
			self.ctx.util.pickRandomElement(self.affectedFood).doCooldownEffect()

	def _readyInit(self):
		super()._readyInit()
		self.foodSpeed = _div(self.getP('speed'), 100.0)
		self.dam = self.getP("dam")


_R.reg("res://gd_core_items/Exclusive/Cthulhu.gd", Exclusive__Cthulhu)
_R.reg("Cthulhu", Exclusive__Cthulhu)
