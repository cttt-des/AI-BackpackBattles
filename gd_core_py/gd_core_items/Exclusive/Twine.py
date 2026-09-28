# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Twine(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Twine.gd"

	def _init_fields(self):
		super()._init_fields()
		self.maxHealth = None


	def canAffect(self, item):
		return item.canActivate()


	def canAffect_secondary(self, item):
		return item.isNeutral()


	def onPrepare(self):
		for triggerItem in _iter(self.getAffectedItems()):
			self.connectForCombat(triggerItem, "activated", "onTriggerItemActivated")


	def onTriggerItemActivated(self, event):
		totalChance = self.getBaseChance()
		totalChance += self.getNumAffectedItems(_R.C("CoreConst").Affected.Secondary) * self.getBaseChance2()
		if self.rollChance(totalChance):
			self.giveMaxHealth(self.maxHealth, event)
			self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.maxHealth = int(self.getP("health"))


_R.reg("res://gd_core_items/Exclusive/Twine.gd", Exclusive__Twine)
_R.reg("Twine", Exclusive__Twine)
