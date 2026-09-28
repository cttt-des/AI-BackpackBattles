# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Gems__CorruptedCrystal(_R.C("res://gd_core_items/Gems/Gem.gd")):

	resource_path = "res://gd_core_items/Gems/CorruptedCrystal.gd"

	def _init_fields(self):
		super()._init_fields()
		self.damageBonusApplied = False
		self.debuffsInflicted = 0
		self.weaponParticles = None
		self.healthThreshold = None
		self.damageFactor = None
		self.debuffsNeeded = None
		self.blockGain = None

	gemColor = Color(0.938676, 0.24128, 0.988281)

	def prepareWeapon(self):
		self.damageBonusApplied = False
		self.connectForCombat(self.opponent(), "character_damaged", "onOpponentDamaged")


	def onOpponentDamaged(self, _healthChange, _event):
		if self.opponent().getRelativeHealth() < self.healthThreshold:
			if not self.damageBonusApplied:
				self.damageBonusApplied = True
				self.getItem().addBonusDamageFactor(self.damageFactor)
		elif self.damageBonusApplied:
			self.damageBonusApplied = False
			self.getItem().reduceBonusDamageFactor(self.damageFactor)


	def combatEndWeapon(self):
		pass


	def prepareArmor(self):
		self.debuffsInflicted = 0
		self.connectToOpponentDebuffs("onOpponentDebuffsChanged")


	def onOpponentDebuffsChanged(self, amount, event):
		if amount > 0:
			if isinstance(event.getOrigin(), _R.C("Item")) and event.getOrigin().character() == self.character():
				self.debuffsInflicted += amount
				activations = int(_div(self.debuffsInflicted, self.debuffsNeeded))
				self.debuffsInflicted %= int(self.debuffsNeeded)
				if activations > 0:
					self.giveBlock(self.getGemPower() * self.blockGain * activations, True, event)
					self.miniActivate()









	def doCooldownEffect(self):
		self.opponent().addFatigueDamage(1)
		self.opponent().takeFatigueDamage(self)
		self.activate()


	def onHotSwapHoverWithGemEnd(self):
		pass


	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP1(), 100.0) - 0.0001
		self.damageFactor = _div(self.getP2(), 100.0)
		self.debuffsNeeded = self.getP3()
		self.blockGain = self.getP4()


_R.reg("res://gd_core_items/Gems/CorruptedCrystal.gd", Gems__CorruptedCrystal)
_R.reg("CorruptedCrystal", Gems__CorruptedCrystal)
