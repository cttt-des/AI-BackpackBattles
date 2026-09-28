# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class FannyPack(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/FannyPack.gd"

	def _init_fields(self):
		super()._init_fields()
		self.speedBonus = None


	def onCombatStart(self):
		active = False
		totalSpeed = self.speedBonus
		if self.isTypeInInventory(self.ctx.item_book.getDescriptor("Bagtacular")):
			totalSpeed += _div(self.ctx.item_book.getDescriptor('Bagtacular').getP('speed'), 100.0)

		for item in _iter(self.getItemsInside()):
			if self.canApplyEffect(item):
				item.addSpeed(totalSpeed)
				active = True

		if active:
			self.activate()


	def canApplyEffect(self, toItem):
		return toItem.hasCooldown() and not toItem.isBag()

	def _readyInit(self):
		super()._readyInit()
		self.speedBonus = _div(self.getP1(), 100)


_R.reg("res://gd_core_items/FannyPack.gd", FannyPack)
_R.reg("FannyPack", FannyPack)
