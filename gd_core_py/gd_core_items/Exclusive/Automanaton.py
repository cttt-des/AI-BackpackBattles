# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Automanaton(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/Automanaton.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False
		self.manaNeeded = None
		self.blind = None
		self.numDebuffs = None
		self.dmgReductionTimer = None
		self.healthThreshold = None
		self.bonusSpeed = None
		self.damReduction = None


	def canAffect(self, item):
		return item.hasCooldown() or item.gainsStack(_R.C("CoreConst").Stack.Mana)


	def onPrepare(self):
		self.updateShaderRotation()
		self.hasActivated = False
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDealtDamage(self, damageRes):
		if (damageRes.hasHit() and 
			self.character().getMana() >= self.manaNeeded):

			event = self.useMana(self.manaNeeded, damageRes.event)
			duration = self.getP_m("dur_blind")
			self.giveStacksTemporary(self.opponent(), _R.C("CoreConst").EventType.Blind, 
				self.blind, duration, event)

			if self.rollChance():
				self.stun(self.getP_m("dur_stun"), event)

			self.cleanseRandomDebuffs(self.numDebuffs, event)


	def onDamaged(self, _damage, event):
		if self.hasActivated:
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.hasActivated = True

			for item in _iter(self.getAffectedItems()):
				item.addSpeed(self.bonusSpeed)
				item.changeAmplificiationChancePercent(_R.C("CoreConst").EventType.Mana, self.getChance2())

			self.dmgReductionTimer.start(self.getP_m("dur_dmgreduction"))
			self.character().changeDamageResistance(self.damReduction)

			self.giveBlock(self.getBlock(), True, event)



	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High + 2


	def onDmgReductionTimerTimeout(self):
		self.character().changeDamageResistance( - self.damReduction)


	def onCombatEnd(self):
		self.dmgReductionTimer.stop()


	def showCooldown(self, progress):

		progress = self.rotateProgress(progress * 1.0 + 0.05)


	def clearSpriteMaterial(self):
		pass


	def giveProgressMaterial(self):
		pass


	def updateShaderRotation(self):
		super().updateShaderRotation()

	def getTextureSize(self):
		return Vector2.ZERO

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP("manat"))
		self.blind = int(self.getP("blind"))
		self.numDebuffs = int(self.getP("cleanse"))
		self.dmgReductionTimer = self.newItemTimer("DmgReductionTimer", "onDmgReductionTimerTimeout", False)
		self.healthThreshold = _div(self.getP('healtht'), 100.0) - 0.0001
		self.bonusSpeed = _div(self.getP('speed'), 100.0)
		self.damReduction = self.getP("dmgreduction")
		pass



_R.reg("res://gd_core_items/Exclusive/Automanaton.gd", Exclusive__Automanaton)
_R.reg("Automanaton", Exclusive__Automanaton)
