# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class StaminaSack(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/StaminaSack.gd"


	def addToInventory(self, _inventory, _occupiedCells, _placedByPlayer):
		super().addToInventory(_inventory, _occupiedCells, _placedByPlayer)
		if self.ownerType == _R.C("CoreConst").Owner.PlayerInventory:
			self.character().changeBaseMaxStamina()


	def onRemoveFromInventory(self):
		super().onRemoveFromInventory()
		if self.ownerType != _R.C("CoreConst").Owner.BuildViewer:
			self.character().changeBaseMaxStamina()


	def onPrepare(self):
		if self.isTypeInInventory(self.ctx.item_book.getDescriptor("Bagtacular")):
			stamina = _div(self.ctx.item_book.getDescriptor('Bagtacular').getP('stamina'), 100.0)
			self.character().giveStaminaRegeneration(stamina)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/StaminaSack.gd", StaminaSack)
_R.reg("StaminaSack", StaminaSack)
