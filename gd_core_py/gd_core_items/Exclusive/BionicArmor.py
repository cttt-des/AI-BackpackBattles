# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BionicArmor(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/BionicArmor.gd"

	def _init_fields(self):
		super()._init_fields()
		self.blockHealthAcc = 0
		self.staminaRegenMalus = None
		self.healthThreshold = None
		self.maxStamina = None
		self.staminaThreshold = None
		self.staminaUsed = None
		self.empower = None
		self.block2 = None


	def onPrepare(self):
		self.blockHealthAcc = 0
		baseStaminaRegen = self.character().baseStaminaRegen
		self.character().giveStaminaRegeneration(self.staminaRegenMalus * baseStaminaRegen)

		self.connectForCombat(self.character(), "character_healed", "onHealOrBlockChanged")
		self.connectForCombat(self.character(), "character_block_changed", "onHealOrBlockChanged")


	def onCombatStart(self):
		self.giveBlock()
		self.activate()


	def onHealOrBlockChanged(self, amount, event):
		if amount > 0:
			self.blockHealthAcc += amount
			numProccs = int(_div(self.blockHealthAcc, self.healthThreshold))
			if numProccs > 0:
				self.blockHealthAcc -= numProccs * self.healthThreshold
				self.giveMaxStaminaTemporary(self.maxStamina * numProccs)
				self.miniActivate()


	def doCooldownEffect(self):
		if self.character().getCurrentStamina() < self.staminaThreshold:
			self.giveBlock(self.block2)
		else:
			self.useStamina(self.staminaUsed)
			self.giveEmpower(self.empower)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.staminaRegenMalus = _div(-self.getP('staminaregen'), 100.0)
		self.healthThreshold = self.getP("healtht")
		self.maxStamina = self.getP("maxstamina")
		self.staminaThreshold = self.getP("staminat1")
		self.staminaUsed = self.getP("staminat2")
		self.empower = int(self.getP("empower"))
		self.block2 = int(self.getP("block"))


_R.reg("res://gd_core_items/Exclusive/BionicArmor.gd", Exclusive__BionicArmor)
_R.reg("BionicArmor", Exclusive__BionicArmor)
