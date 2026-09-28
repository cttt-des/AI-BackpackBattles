# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__IceFlower(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/IceFlower.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaNeeded = None
		self.cold = None
		self.mana = None


	def canAffect(self, item):
		return item.isWeapon()


	def canAffect_secondary(self, item):
		return item.hasType(_R.C("CoreConst").Type.Shield) or (item.hasType(_R.C("CoreConst").Type.Armor) and item.canActivate())


	def onPrepare(self):
		for item in _iter(self.getAffectedItems(_R.C("CoreConst").Affected.Primary)):
			self.connectForCombat(item, "attacked", "onWeaponAttacked")

		for item in _iter(self.getAffectedItems(_R.C("CoreConst").Affected.Secondary)):
			self.connectForCombat(item, "activated", "onShieldOrArmorActivated")


	def onWeaponAttacked(self, damageRes):
		if self.character().getMana() >= self.manaNeeded and self.rollChance():
			event = self.useMana(self.manaNeeded)
			self.inflictCold(self.cold, event)
			self.miniActivate()


	def onShieldOrArmorActivated(self, event):
		if self.rollChance2():
			self.giveMana(self.mana)
			self.giveBlock()
			self.miniActivate()

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP("manat"))
		self.cold = int(self.getP("cold"))
		self.mana = int(self.getP("mana"))


_R.reg("res://gd_core_items/Exclusive/IceFlower.gd", Exclusive__IceFlower)
_R.reg("IceFlower", Exclusive__IceFlower)
