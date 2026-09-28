# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SmithingForDummies(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SmithingForDummies.gd"

	def _init_fields(self):
		super()._init_fields()
		self.boostedWhetstones = 0
		self.whetstoneDescriptor = None
		self.staminaReduction = None
		self.bonusDamage = None


	def getData(self):
		return self.boostedWhetstones


	def setData(self, data):
		if data != None:
			self.boostedWhetstones = data


	def canAffect(self, item):
		return item.isWeapon() and item.isCrafted()


	def onCombatStart(self):
		for item in _iter(self.getAffectedItems()):
			item.changeStaminaFactor(self.staminaReduction)
			if item.canDamage():
				item.addBonusDamage(self.bonusDamage)
		self.activate()


	def onBought(self):
		pass

	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.whetstoneDescriptor:
			self.boostedWhetstones -= 1


	def _readyInit(self):
		super()._readyInit()
		self.whetstoneDescriptor = self.ctx.item_book.getDescriptor("Whetstone")
		self.staminaReduction = - self.getP("stamina")
		self.bonusDamage = self.getP("dam")


_R.reg("res://gd_core_items/Exclusive/SmithingForDummies.gd", Exclusive__SmithingForDummies)
_R.reg("SmithingForDummies", Exclusive__SmithingForDummies)
