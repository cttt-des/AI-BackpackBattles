# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Solaris(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Solaris.gd"

	def _init_fields(self):
		super()._init_fields()
		self.boosted = 0
		self.sunShieldDescriptor = None
		self.sunArmorDescriptor = None
		self.holyArmorDescriptor = None
		self.shieldOfValorDescriptor = None
		self.heatPerShieldBlock = None


	def canAffect(self, item):
		return item.isA(self.sunShieldDescriptor) or item.isA(self.sunArmorDescriptor)


	def onBought(self):
		self.boosted = 1


	def getData(self):
		return self.boosted


	def setData(self, data):
		if data != None:
			self.boosted = data


	def onPrepare(self):
		self.inventory.changeBuffAmplification_allItems(_R.C("CoreConst").EventType.Heat, self.getChance2())

		for item in _iter(self.getAffectedItems()):
			if item.isA(self.sunShieldDescriptor):
				self.connectForCombat(item, "blocked", "onShieldBlocked")
			else:
				self.connectForCombat(item, "used_heat", "onArmorUsedHeat")


	def onArmorUsedHeat(self, event):
		self.giveBlock(self.getBlock(), True, event)
		self.miniActivate()


	def onShieldBlocked(self, blockedDamageRes):
		if self.rollChance():
			self.giveHeat(self.heatPerShieldBlock)
			self.activate()








	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if (descr == self.shieldOfValorDescriptor or 
			descr == self.holyArmorDescriptor):
			self.boosted -= 1

	def _readyInit(self):
		super()._readyInit()
		self.sunShieldDescriptor = self.ctx.item_book.getDescriptor("Sun Shield")
		self.sunArmorDescriptor = self.ctx.item_book.getDescriptor("Sun Armor")
		self.holyArmorDescriptor = self.ctx.item_book.getDescriptor("Holy Armor")
		self.shieldOfValorDescriptor = self.ctx.item_book.getDescriptor("Shield of Valor")
		self.heatPerShieldBlock = int(self.getP("heat"))


_R.reg("res://gd_core_items/Exclusive/Solaris.gd", Exclusive__Solaris)
_R.reg("Solaris", Exclusive__Solaris)
