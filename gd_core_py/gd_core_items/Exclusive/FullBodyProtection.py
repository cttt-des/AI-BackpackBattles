# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__FullBodyProtection(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/FullBodyProtection.gd"

	def _init_fields(self):
		super()._init_fields()
		self.active = None
		self.blockAmp = None
		self.damReduction = None


	def onItemAdded(self, item):
		super().onItemAdded(item)
		self.checkItems()


	def onItemRemoved(self, item):
		super().onItemRemoved(item)
		self.checkItems()


	def onRemoveFromInventory(self):
		self.active = False


	def checkItems(self):
		numArmor = 0
		numHelmets = 0
		numShoes = 0
		for item in _iter(self.inventory.getItems()):
			if item.hasType(_R.C("CoreConst").Type.Armor):
				numArmor += 1
			elif item.hasType(_R.C("CoreConst").Type.Helmet):
				numHelmets += 1
			elif item.hasType(_R.C("CoreConst").Type.Shoes):
				numShoes += 1

		if numArmor == 1 and numHelmets == 1 and numShoes == 1:
			self.active = True
		else:
			self.active = False


	def canAffect(self, item):
		return item.canBlock()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.giveBuffPower(_R.C("CoreConst").EventType.Block, self.blockAmp)

		if self.active:
			self.connectForCombat(self.character(), "pre_take_damage", "preTakeDamage")


	def preTakeDamage(self, damageRes):
		if damageRes.damageSource.isAttackOrEffect():
			damageRes.applyDamageReduction(self.damReduction, self)


	def doCooldownEffect(self):
		self.giveBlock()
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.blockAmp = _div(self.getP('block'), 100.0)
		self.damReduction = self.getP("damreduction")


_R.reg("res://gd_core_items/Exclusive/FullBodyProtection.gd", Exclusive__FullBodyProtection)
_R.reg("FullBodyProtection", Exclusive__FullBodyProtection)
