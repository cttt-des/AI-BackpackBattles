# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class MrStruggles(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/MrStruggles.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False
		self.speedbuffTimer = None
		self.activationParticles = None
		self.healthThreshold = None
		self.bonusSpeed = None
		self.fatigueDam = None
		self.speedBuffParticles1 = None
		self.speedBuffParticles2 = None

	plushies = ["Mrs Struggles", "Miss Fortune"]

	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		for debuff in _iter(_R.C("CoreConst").getDebuffs()):
			self.connectForCombat(self.character(), self.character().buffs[debuff].signalName, 
			"onDebuffed")


		self.hasActivated = False
		self.setState(False)
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDamaged(self, _damage, event):
		if self.hasActivated:
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.hasActivated = True
			self.setState(True)
			for item in _iter(self.getAffectedItems()):
				item.addSpeed(self.bonusSpeed)
			self.speedbuffTimer.start(self.getP_m("dur_speed"))


	def onSpeedbuffTimeout(self):
		self.setState(False)
		for item in _iter(self.getAffectedItems()):
			item.reduceSpeed(self.bonusSpeed)


	def onDebuffed(self, amount, event):
		if self.checkTriggerCount(10):
			if self.rollChance():
				debuffType = event.type
				dur = event.getParam("duration", - 1)
				self.giveStacksTemporary(self.opponent(), debuffType, amount, dur, event)



	def doCooldownEffect(self):
		self.inflictFatigueDamage(self.fatigueDam)
		self.activate()






	def onCombatEnd(self):
		self.speedbuffTimer.stop()


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High + 3


	def getDescription(self, wrapInColor=True):
		return ""

	def rollShopChance(self, shopChance=GD_DEFAULT):
		if shopChance is GD_DEFAULT:
			shopChance = self.descriptor.shopChance
		return False

	def getGatedDescriptor(self, rarity):
		return self.ctx.item_book.getDescriptor(self.ctx.util.pickRandomElement(self.plushies))


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, speedBuffActive):
		if speedBuffActive:
			pass
		else:
			pass


	def _readyInit(self):
		super()._readyInit()
		self.speedbuffTimer = self.newItemTimer("SpeedbuffTimer", "onSpeedbuffTimeout", False)
		self.healthThreshold = _div(self.getP2(), 100.0) - 0.0001
		self.bonusSpeed = _div(self.getP3(), 100.0)
		self.fatigueDam = int(self.getP1())


_R.reg("res://gd_core_items/MrStruggles.gd", MrStruggles)
_R.reg("MrStruggles", MrStruggles)
