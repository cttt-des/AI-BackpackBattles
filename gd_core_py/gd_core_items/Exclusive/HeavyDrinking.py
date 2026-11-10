# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__HeavyDrinking(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/HeavyDrinking.gd"

	def _init_fields(self):
		super()._init_fields()
		self.allPotions = []
		self.boostedPotions = 0
		self.potionSpeed = None


	def getData(self):
		return self.boostedPotions


	def setData(self, data):
		if data != None:
			self.boostedPotions = data


	def onBought(self):
		self.boostedPotions = 3


	def isAffectingDistinct(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_1
		return color == _H_1


	def canAffect(self, item):
		return item.hasType(_H_2)


	def canAffect_global(self, item):
		return item.hasType(_H_2)


	def onPrepare(self):
		self.addSpeed(self.getNumDistinctAffectedItems() * self.potionSpeed)

		self.allPotions.clear()
		for item in _iter(self.inventory.getItems()):
			if item.hasType(_H_2) and item != self:
				self.allPotions.append(item)


	def doCooldownEffect(self):
		if not (not self.allPotions):
			potionToTrigger = self.ctx.util.pickRandomElement(self.allPotions)
			potionToTrigger.triggerPotion()
			potionToTrigger.miniActivate()

		self.activate()


	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr.hasType(_H_2):
			self.boostedPotions -= 1

	def _readyInit(self):
		super()._readyInit()
		self.potionSpeed = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/HeavyDrinking.gd", Exclusive__HeavyDrinking)
_R.reg("HeavyDrinking", Exclusive__HeavyDrinking)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Affected.Primary
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Type.Potion
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
