# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class RangerBag(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/RangerBag.gd"

	def _init_fields(self):
		super()._init_fields()
		self.itemsInside = None


	def onPrepare(self):
		self.itemsInside = self.getItemsInside()
		if not (not self.getItemsInside()):
			self.connectForCombat(self.character(), "character_lucky_changed", "onLuckyChanged")
		for item in _iter(self.itemsInside):
			item.changeCritChancePercent(self.getChance())


	def onLuckyChanged(self, amount, event):
		change = amount * self.getChance2()
		for item in _iter(self.itemsInside):
			item.changeCritChancePercent(change)


	def canApplyEffect(self, toItem):
		return toItem.canDamage()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/RangerBag.gd", RangerBag)
_R.reg("RangerBag", RangerBag)
