# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__FriendlyFire(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/FriendlyFire.gd"

	def _init_fields(self):
		super()._init_fields()
		self.maxHeatReached = 0
		self.manaNeeded = 0
		self.threshold1 = 0
		self.threshold2 = 0
		self.threshold3 = 0


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Fire)


	def onPrepare(self):
		self.addSpeed(_div(self.getNumAffected_type(_R.C('CoreConst').Type.Fire) * self.getP3(), 100.0))
		self.maxHeatReached = 0
		self.connectForCombat(self.character(), "character_heat_changed", "onHeatChanged")


	def onHeatChanged(self, _amount, event):
		newMaxHeat = max(self.maxHeatReached, self.character().getHeat())
		if newMaxHeat >= self.threshold3 and self.maxHeatReached < self.threshold3:
			self.maxHeatReached = newMaxHeat
			dam = self.descriptor.minDam
			damageRes = self.dealEffectDamage(dam, event)
			self.activate()
		elif newMaxHeat >= self.threshold2 and self.maxHeatReached < self.threshold2:
			self.maxHeatReached = newMaxHeat
			self.giveRegeneration(self.getP7(), event)
			self.activate()
		elif newMaxHeat >= self.threshold1 and self.maxHeatReached < self.threshold1:
			self.maxHeatReached = newMaxHeat
			self.giveLucky(self.getP5(), event)
			self.activate()



	def doCooldownEffect(self):
		if self.character().getMana() >= self.manaNeeded:
			self.useMana(self.manaNeeded)
			self.giveHeat(self.getP2())
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = self.getP1()
		self.threshold1 = self.getP4()
		self.threshold2 = self.getP6()
		self.threshold3 = self.getP8()
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)



_R.reg("res://gd_core_items/Exclusive/FriendlyFire.gd", Exclusive__FriendlyFire)
_R.reg("FriendlyFire", Exclusive__FriendlyFire)
