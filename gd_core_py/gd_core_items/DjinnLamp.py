# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class DjinnLamp(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/DjinnLamp.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.affectedWeapon = None
		self.stacksNeeded = None
		self.healthNeeded = None
		self.activationParticles = None

	numIngredients = 5.0

	def canAffect(self, item):
		return item.canBeEmpowered()


	def onPrepare(self):
		self.activated = False
		self.affectedWeapon = None
		affectedItems = self.getAffectedItems()
		if not (not affectedItems):
			self.affectedWeapon = affectedItems[0]
			self.connectForCombat(self.character(), "character_block_changed", "checkStacks")
			self.connectForCombat(self.character(), "character_spikes_changed", "checkStacks")
			self.connectForCombat(self.character(), "character_mana_changed", "checkStacks")
			self.connectForCombat(self.character(), "character_lucky_changed", "checkStacks")
			self.connectForCombat(self.character(), "character_damaged", "checkStacks")
			self.connectForCombat(self.character(), "character_healed", "checkStacks")


	def checkStacks(self, changeAmount, event):
		if self.activated:
			return

		progress = 0.0
		progress += _div(min(self.character().getBlock(), self.stacksNeeded), float(self.stacksNeeded))
		progress += _div(min(self.character().getSpikes(), self.stacksNeeded), float(self.stacksNeeded))
		progress += _div(min(self.character().getMana(), self.stacksNeeded), float(self.stacksNeeded))
		progress += _div(min(self.character().getLucky(), self.stacksNeeded), float(self.stacksNeeded))
		progress += _div(min(self.character().getCurrentHealth() - 1, self.healthNeeded), float(self.healthNeeded))
		progress /= self.numIngredients

		if changeAmount > 0:

			if progress >= 0.9999:
				self.activated = True
				self.ctx.bus.setLoggingMode(self.ctx.bus.LoggingMode.Delayed)
				self.useBlock(self.stacksNeeded, event)
				self.useSpikes(self.stacksNeeded, event)
				self.useMana(self.stacksNeeded, event)
				self.useLucky(self.stacksNeeded, event)
				self.character().loseHealth(self.healthNeeded, self, event)
				bonusDamage = self.getP3()
				self.affectedWeapon.addBonusDamage(bonusDamage)
				dmgBuffEvent = self.ctx.combat_log.createEvent_DamageBuff(self, self.affectedWeapon, bonusDamage, self.character().playerId, event)
				self.ctx.bus.logEvent(dmgBuffEvent)
				self.ctx.bus.flushLoggingQueue()
				self.activate()


	def doCooldownEffect(self):
		numLucky = self.character().getLucky()
		numSpikes = self.character().getSpikes()
		numMana = self.character().getMana()

		if numLucky < numSpikes:
			if numLucky < numMana:

				self.giveLucky(1)
			else:

				self.giveMana(1)
		else:

			if numSpikes < numMana:

				self.giveSpikes(1)
			else:

				self.giveMana(1)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.stacksNeeded = self.getP1()
		self.healthNeeded = self.getP2()


_R.reg("res://gd_core_items/DjinnLamp.gd", DjinnLamp)
_R.reg("DjinnLamp", DjinnLamp)
