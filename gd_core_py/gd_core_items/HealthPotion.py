# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class HealthPotion(_R.C("res://gd_core_items/Potion.gd")):

	resource_path = "res://gd_core_items/HealthPotion.gd"

	def _init_fields(self):
		super()._init_fields()
		self.healthThreshold = None


	def onTriggerPotion(self, triggerEvent=None):
		self.heal(self.getP_m("heal"), triggerEvent)
		self.cleansePoison(self.getP3(), triggerEvent)


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDamaged(self, _healthChange, event):
		if self.isEmpty():
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.consumePotion(event)


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High

	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP1(), 100.0)


_R.reg("res://gd_core_items/HealthPotion.gd", HealthPotion)
_R.reg("HealthPotion", HealthPotion)
