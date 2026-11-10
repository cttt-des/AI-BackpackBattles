# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class StaminaSack_2(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/StaminaSack.gd"


	def addToInventory(self, _inventory, _occupiedCells, _placedByPlayer):
		super().addToInventory(_inventory, _occupiedCells, _placedByPlayer)
		if self.ownerType == _H_1:
			self.character().changeBaseMaxStamina()


	def onRemoveFromInventory(self):
		super().onRemoveFromInventory()
		if self.ownerType != _H_2:
			self.character().changeBaseMaxStamina()


	def onPrepare(self):
		if self.isTypeInInventory(self.ctx.item_book.getDescriptor("Bagtacular")):
			stamina = _div(self.ctx.item_book.getDescriptor('Bagtacular').getP('stamina'), 100.0)
			self.character().giveStaminaRegeneration(stamina)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/StaminaSack.gd", StaminaSack_2)
_R.reg("StaminaSack", StaminaSack_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Owner.PlayerInventory
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Owner.BuildViewer
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
