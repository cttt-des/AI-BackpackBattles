# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class DemonicFlask(_R.C("res://gd_core_items/Potion.gd")):

	resource_path = "res://gd_core_items/DemonicFlask.gd"

	def _init_fields(self):
		super()._init_fields()
		self.healthThreshold = None


	def canDamage(self):
		return True


	def onTriggerPotion(self, triggerEvent=None):
		dam = self.opponent().getDebuffStacks()
		dam *= self.getP2()
		dam = ceil(dam)
		self.dealEffectDamage(dam, triggerEvent)


	def onPrepare(self):
		self.connectForCombat(self.opponent(), "character_damaged", "onDamaged")


	def onDamaged(self, healthChange, event):
		if self.isEmpty():
			return

		if self.opponent().getRelativeHealth() < self.healthThreshold:

			self.drink()

			self.triggerPotion(event)

			affected = self.getAffectedItems()
			if not (not affected):
				affected[0].triggerPotion(event)
				affected[0].miniActivate()

			self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP1(), 100.0) - 0.0001
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)




_R.reg("res://gd_core_items/DemonicFlask.gd", DemonicFlask)
_R.reg("DemonicFlask", DemonicFlask)
