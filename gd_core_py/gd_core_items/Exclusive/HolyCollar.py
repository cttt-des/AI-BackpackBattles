# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__HolyCollar(_R.C("res://gd_core_items/RangerCollar.gd")):

	resource_path = "res://gd_core_items/Exclusive/HolyCollar.gd"

	def _init_fields(self):
		super()._init_fields()
		self.luck = None
		self.regen = None


	def canAffect(self, item):
		return item.canActivate()


	def onPrepare(self):
		for item in _iter(self.affectedItems):
			self.connectForCombat(item, "activated", "onItemActivated")

		if not (not self.affectedItems):
			self.connectForCombat(self.character(), "character_lucky_changed", "onLuckyOrRegenChanged")
			self.connectForCombat(self.character(), "character_regeneration_changed", "onLuckyOrRegenChanged")


	def onLuckyOrRegenChanged(self, amount, _event):
		for item in _iter(self.affectedItems):
			item.changeCritChancePercent(amount * self.getChance2())


	def onItemActivated(self, event):
		if self.rollChance():
			self.giveLucky(self.luck, event)
			self.giveRegeneration(self.regen, event)
			self.miniActivate()

	def _readyInit(self):
		super()._readyInit()
		self.luck = int(self.getP("luck"))
		self.regen = int(self.getP("regen"))


_R.reg("res://gd_core_items/Exclusive/HolyCollar.gd", Exclusive__HolyCollar)
_R.reg("HolyCollar", Exclusive__HolyCollar)
