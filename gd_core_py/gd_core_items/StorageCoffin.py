# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class StorageCoffin(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/StorageCoffin.gd"


	def onPrepare(self):
		for item in _iter(self.getItemsInside()):
			self.connectForCombat(item, "activated", "onItemActivated")


	def onItemActivated(self, event):
		if self.rollChance():
			self.inflictPoison(1)
			self.activate()


	def canApplyEffect(self, toItem):
		return toItem.canActivate() and not toItem.isBag()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/StorageCoffin.gd", StorageCoffin)
_R.reg("StorageCoffin", StorageCoffin)
