# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DualWielding(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/DualWielding.gd"

	def _init_fields(self):
		super()._init_fields()
		self.active = False
		self.weaponSpeed = None
		self.weaponStamina = None


	def onItemAdded(self, item):
		super().onItemAdded(item)
		self.checkItems()


	def onItemRemoved(self, item):
		super().onItemRemoved(item)
		self.checkItems()


	def onRemoveFromInventory(self):
		self.active = False


	def canAffect_global(self, item):
		return item.isWeapon() and item.getBaseStaminaCost() > 0


	def checkItems(self):
		numWeapons = 0
		for item in _iter(self.inventory.getItems()):
			if self.canAffect_global(item):
				numWeapons += 1

		if numWeapons == 2:
			self.active = True
		else:
			self.active = False


	def onPrepare(self):
		if self.active:
			for item in _iter(self.inventory.getItems()):
				if item.hasType(_R.C("CoreConst").Type.Weapon) and item.getBaseStaminaCost() > 0:
					item.addSpeed(self.weaponSpeed)
					item.changeStaminaFactor( - self.weaponStamina)

	def _readyInit(self):
		super()._readyInit()
		self.weaponSpeed = _div(self.getP('speed'), 100.0)
		self.weaponStamina = self.getP("stamina")


_R.reg("res://gd_core_items/Exclusive/DualWielding.gd", Exclusive__DualWielding)
_R.reg("DualWielding", Exclusive__DualWielding)
