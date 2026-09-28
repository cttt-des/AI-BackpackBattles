# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__StrongVampiricPotion(_R.C("res://gd_core_items/Exclusive/VampiricPotion.gd")):

	resource_path = "res://gd_core_items/Exclusive/StrongVampiricPotion.gd"

	def _init_fields(self):
		super()._init_fields()
		self.curLifesteal = 0.0
		self.lifestealGiven = []
		self.lifestealTimer = None
		self.lifestealPerTrigger = None


	def onPrepare(self):
		super().onPrepare()
		self.curLifesteal = 0.0
		self.lifestealGiven.clear()
		self.connectForCombat(self.opponent(), "character_attacked", "onOpponentDamaged")


	def onTriggerPotion(self, triggerEvent=None):

		amount = _div(self.getP_m('lifesteal'), 100.0)
		self.curLifesteal += amount
		self.lifestealGiven.append(amount)
		self.lifestealTimer.start(self.getP_m("dur"))
		self.giveVampirism(self.getP2(), triggerEvent)


	def onOpponentDamaged(self, damageRes):
		if self.curLifesteal > 0:
			if damageRes.hasHit() and damageRes.damageSource.canApplyLifesteal():
				self.heal(ceil(damageRes.damage * self.curLifesteal), damageRes.event)


	def onLifestealTimeout(self):
		self.curLifesteal -= self.lifestealGiven.pop(0)


	def onCombatEnd(self):
		self.lifestealTimer.stop()

	def _readyInit(self):
		super()._readyInit()
		self.lifestealTimer = self.newItemTimer("LifestealTimer", "onLifestealTimeout", True)
		self.lifestealPerTrigger = _div(self.getP3(), 100.0)


_R.reg("res://gd_core_items/Exclusive/StrongVampiricPotion.gd", Exclusive__StrongVampiricPotion)
_R.reg("StrongVampiricPotion", Exclusive__StrongVampiricPotion)
