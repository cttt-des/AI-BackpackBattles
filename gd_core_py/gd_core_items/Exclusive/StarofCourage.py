# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__StarofCourage(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/StarofCourage.gd"

	def _init_fields(self):
		super()._init_fields()
		self.staminaReduction = None


	def onPrepare(self):
		for item in _iter(self.inventory.getItems()):
			if item.isWeapon():
				item.changeStaminaFactor(self.staminaReduction)

	def _readyInit(self):
		super()._readyInit()
		self.staminaReduction = - self.getP("stamina")


_R.reg("res://gd_core_items/Exclusive/StarofCourage.gd", Exclusive__StarofCourage)
_R.reg("StarofCourage", Exclusive__StarofCourage)
