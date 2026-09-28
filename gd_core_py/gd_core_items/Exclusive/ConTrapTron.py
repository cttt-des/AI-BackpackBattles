# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ConTrapTron(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ConTrapTron.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False
		self.speedMalus = None
		self.cdAdvanceBase = None
		self.cdAdvanceBonus = None
		self.healthThreshold = None

	chargeCells1 = [Vector2( - 1, - 1), Vector2(0, - 2), Vector2(1, - 3), Vector2(2, - 2), Vector2(2, - 1)]
	chargeCells2 = [Vector2( - 1, 0), Vector2( - 1, 1), Vector2(0, 2), Vector2(1, 1), Vector2(2, 1)]

	def canAffect(self, item):
		return item.hasCooldown()


	def canAffect_lightning(self, item):
		return item.gainsBuffs() or item.reactsToCharges()


	def onPrepare(self):
		self.hasActivated = False
		item = self.getFirstAffectedItem()
		if item != None:
			item.reduceSpeed(self.speedMalus)

		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDamaged(self, _damage, event):
		if self.hasActivated:
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.hasActivated = True

			self.emitCharge()
			self.ctx.bus.emitSignal(self, "charge_emitted", [self])

			item = self.getFirstAffectedItem()
			if item != None:
				cdAdvance = self.cdAdvanceBase
				if not item.isWeapon():
					cdAdvance += self.cdAdvanceBonus

				item.advanceCooldownSeconds(cdAdvance)


	def emitCharge(self, speedFactor=1.0):
		event = self.activate()
		self.sendCharge(self.getP_m("dur"), self.chargeCells1, speedFactor, event)
		self.sendCharge(self.getP_m("dur"), self.chargeCells2, speedFactor, event)



	def onChargeEnteredCell(self, charge, cellIndex):
		self.changeChargedItemStat(charge, cellIndex, self.getChance(), self.getChance2())


	def chargedItemStatChange(self, item, value):
		item.changeAmplificiationChancePercent_allBuffs(value)


	def getTextureSize(self):
		return Vector2.ZERO

	def getSpriteOffset(self):
		return Vector2.ZERO

	def _readyInit(self):
		super()._readyInit()
		self.speedMalus = _div(self.getP('speed'), 100.0)
		self.cdAdvanceBase = self.getP("cdadvance_base")
		self.cdAdvanceBonus = self.getP("cdadvance_bonus")
		self.healthThreshold = _div(self.getP('healtht'), 100.0) - 0.0001


_R.reg("res://gd_core_items/Exclusive/ConTrapTron.gd", Exclusive__ConTrapTron)
_R.reg("ConTrapTron", Exclusive__ConTrapTron)
