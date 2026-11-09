# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BagofGiving(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/BagofGiving.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activationParticles = None
		self.maxStamina = None


	def canApplyEffect(self, toItem):
		return toItem.isClassItem()


	def onPrepare(self):
		for item in _iter(self.getAffectedItemsInside()):
			self.connectForCombat(item, "activated", "onItemInsideActivated")


	def onItemInsideActivated(self, event):
		self.giveMaxStaminaTemporary(self.maxStamina, event)
		self.miniActivate()


	def onAddToInventory(self):
		pass

	def onRemoveFromInventory(self):
		super().onRemoveFromInventory()

	def onShopEntered(self):
		pass

	def getShopPriority(self):
		return _H_1


	def getRelatedItems(self):
		pass

	def getRelatedItemColumns(self):
		return 6


	def getRelatedItemHeight(self):
		return 110

	def _readyInit(self):
		super()._readyInit()
		self.maxStamina = self.getP("stamina")


_R.reg("res://gd_core_items/Exclusive/BagofGiving.gd", Exclusive__BagofGiving)
_R.reg("BagofGiving", Exclusive__BagofGiving)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Priority.Low
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
