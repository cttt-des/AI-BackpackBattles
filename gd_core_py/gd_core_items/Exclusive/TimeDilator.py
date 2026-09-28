# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__TimeDilator(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/TimeDilator.gd"

	def _init_fields(self):
		super()._init_fields()
		self.tickI = 0
		self.slow = None
		self.speedUp = None


	def onPrepare(self):
		self.tickI = 0
		allItems = self.ctx.player.INVENTORY.getItems() + self.ctx.opponent.INVENTORY.getItems()
		for item in _iter(allItems):
			if item.isWeapon():
				item.reduceSpeed(self.slow)


	def doCooldownEffect(self):
		slowestCd = 0.0
		slowestItem = None

		for item in _iter(self.inventory.getItems()):
			if item.hasCooldown() and item.isCooldownActive():
				cd = item.getModifiedCooldown()
				if cd > slowestCd:
					slowestCd = cd
					slowestItem = item


		slowestItem.addSpeed(self.speedUp)
		self.activate()
		self.tickI += 1


	def playActivationSound(self):
		pitch = 1.0 if _mod(self.tickI, 2) == 0 else 0.7


	def _readyInit(self):
		super()._readyInit()
		self.slow = _div(self.getP('slow'), 100.0)
		self.speedUp = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/TimeDilator.gd", Exclusive__TimeDilator)
_R.reg("TimeDilator", Exclusive__TimeDilator)
