# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class StrongDemonicFlask(_R.C("res://gd_core_items/Potion.gd")):

	resource_path = "res://gd_core_items/StrongDemonicFlask.gd"

	def _init_fields(self):
		super()._init_fields()
		self.healingReductionTimer = None
		self.healingDebuff = None
		self.damPerDebuff = None
		self.playerHealthThreshold = None
		self.opponentHealthThreshold = None


	def canDamage(self):
		return True


	def onTriggerPotion(self, triggerEvent=None):
		self.opponent().reduceHealingEfficiency(self.healingDebuff)
		dam = self.opponent().getDebuffStacks() * self.damPerDebuff
		dam = ceil(dam)
		self.stealLife(dam, _div(self.getP_m('lifesteal'), 100.0), triggerEvent)
		self.healingReductionTimer.start(self.getP_m("dur"))


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_damaged", "onPlayerDamaged")
		self.connectForCombat(self.opponent(), "character_damaged", "onOpponentDamaged")


	def onPlayerDamaged(self, healthChange, event):
		if self.isEmpty():
			return
		if self.character().getRelativeHealth() < self.playerHealthThreshold:
			self.drinkStrongDemonicFlask(event)


	def onOpponentDamaged(self, healthChange, event):
		if self.isEmpty():
			return
		if self.opponent().getRelativeHealth() < self.opponentHealthThreshold:
			self.drinkStrongDemonicFlask(event)


	def drinkStrongDemonicFlask(self, event):

		self.drink()

		self.triggerPotion(event)

		affected = self.getAffectedItems()
		if not (not affected):
			affected[0].triggerPotion(event)
			affected[0].miniActivate()

		self.activate()


	def healingReductionTimeout(self):
		self.opponent().addHealingEfficiency(self.healingDebuff)


	def onCombatEnd(self):
		self.healingReductionTimer.stop()

	def _readyInit(self):
		super()._readyInit()
		self.healingReductionTimer = self.newItemTimer("HealingReductionTimer", "healingReductionTimeout", True)
		self.healingDebuff = _div(self.getP3(), 100.0)
		self.damPerDebuff = self.getP("dam")
		self.playerHealthThreshold = _div(self.getP('ownhpt'), 100.0) - 0.0001
		self.opponentHealthThreshold = _div(self.getP('opphpt'), 100.0) - 0.0001


_R.reg("res://gd_core_items/StrongDemonicFlask.gd", StrongDemonicFlask)
_R.reg("StrongDemonicFlask", StrongDemonicFlask)
