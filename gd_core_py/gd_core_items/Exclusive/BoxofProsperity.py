# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BoxofProsperity(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/BoxofProsperity.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activeParticles = None
		self.activationParticles = None
		self.requiredItems = None


	def canApplyEffect(self, toItem):
		return toItem.getRarity() >= _R.C("CoreConst").Rarity.Godly


	def onShopEntered(self):
		pass

	def onAffectedItemInsideAdded(self, _item):
		if self.getNumAffectedInside() == self.requiredItems:
			pass



	def onItemRemoved(self, item):
		super().onItemRemoved(item)
		if not self.conditionFulfilled():
			pass


	def conditionFulfilled(self):
		return self.getNumAffectedInside() >= self.requiredItems





	def onRemoveFromInventory(self):
		pass


	def onAddToInventory(self):
		if self.conditionFulfilled():
			pass


	def discard(self, withGems=True):
		super().discard(withGems)


	def _readyInit(self):
		super()._readyInit()
		self.requiredItems = self.getP("insideitems")


_R.reg("res://gd_core_items/Exclusive/BoxofProsperity.gd", Exclusive__BoxofProsperity)
_R.reg("BoxofProsperity", Exclusive__BoxofProsperity)
