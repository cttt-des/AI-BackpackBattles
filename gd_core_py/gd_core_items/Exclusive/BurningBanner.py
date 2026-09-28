# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BurningBanner(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/BurningBanner.gd"

	def _init_fields(self):
		super()._init_fields()
		self.regeneration = None
		self.buffsToRemove = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Holy) and item.canActivate()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "activated", "onItemActivated")

		self.opponent().changeDebuffProtectionChance(self.getChance2())
		self.character().changeBuffProtectionChance(self.getChance2())


	def onItemActivated(self, event):
		if self.rollChance():
			self.giveStacksTemporary(self.opponent(), _R.C("CoreConst").EventType.Blind, 
				1, self.getP_m("dur_blind"))


	def doCooldownEffect(self):
		self.removeRandomBuffs(self.buffsToRemove)
		self.giveRegeneration(self.regeneration)
		self.activate()





























	def _readyInit(self):
		super()._readyInit()
		self.regeneration = int(self.getP("regen"))
		self.buffsToRemove = int(self.getP("buffs"))


_R.reg("res://gd_core_items/Exclusive/BurningBanner.gd", Exclusive__BurningBanner)
_R.reg("BurningBanner", Exclusive__BurningBanner)
