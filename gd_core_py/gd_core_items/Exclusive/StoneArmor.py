# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__StoneArmor(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/StoneArmor.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.staminaReduction = None
		self.spikeRemoval = None
		self.empowerRemoval = None
		self.healthThreshold = None
		self.blockPerHealth = None


	def onPrepare(self):
		self.activated = False

		self.connectForCombat(self.character(), "character_damaged", "onDamaged")

		for item in _iter(self.inventory.getItems()):
			item.changeStaminaFactor(self.staminaReduction)


	def onCombatStart(self):
		self.giveBlock()
		self.activate()


	def doCooldownEffect(self):
		self.opponent().loseSpikes(self.spikeRemoval, self)
		self.opponent().loseEmpower(self.empowerRemoval, self)
		self.activate()


	def onDamaged(self, _healthChange, event):
		if self.activated:
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.activated = True
			bl = self.character().getMissingHealth() * self.blockPerHealth
			self.giveBlock(bl, True, event)
			self.activate()


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High + 3

	def _readyInit(self):
		super()._readyInit()
		self.staminaReduction = self.getP("staminacost")
		self.spikeRemoval = self.getP("spikes")
		self.empowerRemoval = self.getP("empower")
		self.healthThreshold = _div(self.getP('healtht'), 100.0)
		self.blockPerHealth = _div(self.getP('blockperhealth'), 100.0)


_R.reg("res://gd_core_items/Exclusive/StoneArmor.gd", Exclusive__StoneArmor)
_R.reg("StoneArmor", Exclusive__StoneArmor)
