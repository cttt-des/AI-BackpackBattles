# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__WaterElemental(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/WaterElemental.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaUsed = 0
		self.activeEffects = 0
		self.coldParticles = None
		self.distortion = None
		self.manaOnHit = None
		self.bonusManaOnHit = None
		self.iceSpeed = None
		self.bonusDam = None
		self.coldOnHit = None
		self.manaNeeded1 = None
		self.manaNeeded2 = None
		self.manaNeeded3 = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Nature)


	def canAffect_secondary(self, item):
		return item.hasType(_R.C("CoreConst").Type.Ice)


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_mana_changed", "onManaChanged")
		self.manaUsed = 0
		self.addSpeed(self.iceSpeed * self.getNumAffectedItems(_R.C("CoreConst").Affected.Secondary))
		self.activeEffects = 0
		self.setState(self.activeEffects)


	def onManaChanged(self, amount, event):
		if (amount < 0 and 
			event.type == _R.C("CoreConst").EventType.Mana and 
			event.getParam("used", False)):

			self.manaUsed += abs(amount)

			before = self.activeEffects

			if self.activeEffects == 0 and self.manaUsed >= self.manaNeeded1:
				self.activeEffects = 1

			if self.activeEffects == 1 and self.manaUsed >= self.manaNeeded2:
				self.activeEffects = 2
				self.addBonusDamage(self.bonusDam)

			if self.activeEffects == 2 and self.manaUsed >= self.manaNeeded3:
				self.activeEffects = 3

			if before != self.activeEffects:
				self.setState(self.activeEffects)


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			mana = self.manaOnHit
			chance = self.getChance() * self.getNumAffectedItems()
			if self.rollChance(chance):
				mana += self.bonusManaOnHit
			self.giveMana(mana, damageRes.event)

			if self.activeEffects >= 1:
				self.heal(self.getP_m("heal"), damageRes.event)
			if self.activeEffects == 3:
				self.inflictCold(self.coldOnHit, damageRes.event)


	def onShopEntered(self):
		self.onStateChanged(0)


	def onStateChanged(self, _activeEffects):
		self.activeEffects = _activeEffects
		if self.activeEffects == 3:
			pass
		else:
			pass



	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		colors = [self.ctx.util.triggerColor, self.ctx.util.triggerColor, self.ctx.util.triggerColor]

		if self.placed:
			for i in _iter(self.activeEffects):
				colors[i] = self.ctx.util.modifiedColor

		descr = self.getModeDescription(descr, colors, False, wrapInColor)
		return descr


	def playPickupSound(self):
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

	def _readyInit(self):
		super()._readyInit()
		self.manaOnHit = int(self.getP("mana"))
		self.bonusManaOnHit = int(self.getP("mana2"))
		self.iceSpeed = _div(self.getP('speed'), 100.0)
		self.bonusDam = self.getP("dam")
		self.coldOnHit = int(self.getP("cold"))
		self.manaNeeded1 = int(self.getP("manat1"))
		self.manaNeeded2 = int(self.getP("manat2"))
		self.manaNeeded3 = int(self.getP("manat3"))
		if self.ownerType == _R.C("CoreConst").Owner.GridStorage:
			pass
		else:
			pass



_R.reg("res://gd_core_items/Exclusive/WaterElemental.gd", Exclusive__WaterElemental)
_R.reg("WaterElemental", Exclusive__WaterElemental)
