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
		return item.hasType(_H_1) or item.hasType(_H_2)










	def onAffectedItemAdded(self, item, color):
		color = int(color)
		if item.hasType(_H_1):
			item.addDynamicType(_H_2, self)


	def onAffectedItemRemoved(self, item, color):
		color = int(color)
		item.removeDynamicType(_H_2, self)


	def onPrepare(self):
		self.affectedFood.clear()
		for item in _iter(self.getAffectedItems()):
			if item.hasType(_H_1):
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


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Food
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Type.Dark
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
