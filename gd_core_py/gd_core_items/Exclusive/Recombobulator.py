# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Recombobulator(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Recombobulator.gd"

	def _init_fields(self):
		super()._init_fields()
		self.stable = True
		self.idleAnimation = None


	def canAffect(self, item):
		return not item.isBag() and (item.canStartNewRecipe() or item.bondedBaseItem == self)


	def cacheAffectedItemsForCombat(self):
		super().cacheAffectedItemsForCombat()
		arr = self.getItemsInAffectedCells_cached()
		self.cachedAffectedItems[_R.C("CoreConst").Affected.Primary] = arr




	def readyToFuse(self):
		if self.stable:
			return not (not self.bondedIngredients)
		else:
			return self.bondedBaseItem == None


	def onFusingFinished(self, validBonds):
		super().onFusingFinished(validBonds)

	def reactToDropResult(self, dropResult):
		super().reactToDropResult(dropResult)
		if self.wasAddedToInventory(dropResult):
			pass


	def doCooldownEffect(self):
		self.giveRandomBuffs(1)
		self.cleanseRandomDebuffs(1)
		self.activate()


	def getCounterValue(self):
		return self.getAffectedGoldValue()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/Recombobulator.gd", Exclusive__Recombobulator)
_R.reg("Recombobulator", Exclusive__Recombobulator)
