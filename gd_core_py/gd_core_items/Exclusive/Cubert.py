# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Cubert(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Cubert.gd"

	def _init_fields(self):
		super()._init_fields()
		self.goobertAnimation = None
		self.regen = None
		self.regenNeeded = None
		self.empower = None


	def canAffect(self, item):
		return item.canActivate()


	def canAffect_secondary(self, item):
		return item.canActivate()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "activated", "onItemActivated1")

		for item in _iter(self.getAffectedItems(_R.C("CoreConst").Affected.Secondary)):
			self.connectForCombat(item, "activated", "onItemActivated2")


	def onItemActivated1(self, event):
		if self.rollChance():
			self.giveRegeneration(self.regen, event)
			self.miniActivate()


	def onItemActivated2(self, event):
		if self.character().getRegeneration() >= self.regenNeeded:
			if self.rollChance2():
				event2 = self.useRegeneration(self.regenNeeded, event)
				self.giveEmpower(self.empower, event2)
				self.miniActivate()



	def doCooldownEffect(self):
		self.giveRegeneration(self.regen)
		if self.character().getRegeneration() >= self.regenNeeded:
			event2 = self.useRegeneration(self.regenNeeded)
			self.giveEmpower(self.empower, event2)
		self.activate()










	def _readyInit(self):
		super()._readyInit()
		self.regen = int(self.getP("regen"))
		self.regenNeeded = int(self.getP("regent"))
		self.empower = int(self.getP("empower"))


_R.reg("res://gd_core_items/Exclusive/Cubert.gd", Exclusive__Cubert)
_R.reg("Cubert", Exclusive__Cubert)
