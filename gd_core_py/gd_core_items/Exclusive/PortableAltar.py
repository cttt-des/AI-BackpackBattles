# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PortableAltar(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/PortableAltar.gd"

	valueFactor = 1.0

	def canLockBag(self):
		return True


	def showBagBorderForItem(self, item):
		return not item.isBag()


	def onCombatStart(self):
		self.giveEmpower(self.getP("empower"))
		self.activate()




	def onRecipesUpdated(self):
		if self.ownerType != _R.C("CoreConst").Owner.PlayerInventory:
			return
		if self.fusing:
			return

		if self.locked or not self.placed:
			for bonded in _iter(self.bondedIngredients):
				bonded.removeBondedBaseItem()
			self.removeAllIngredients()
			return

		for item in _iter(self.getItemsInside()):
			if item.canStartNewRecipe():
				self.createBondVisual(item)
				self.updateBondVisuals()
				item.addToBaseItem(self)


	def readyToFuse(self):
		return not (not self.bondedIngredients)


	def onFusingFinished(self, validBonds):
		super().onFusingFinished(validBonds)

	def getCounterValue(self):
		gold = 0
		for item in _iter(self.bondedIngredients):
			gold += item.getPrice()
		return gold

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/PortableAltar.gd", Exclusive__PortableAltar)
_R.reg("PortableAltar", Exclusive__PortableAltar)
