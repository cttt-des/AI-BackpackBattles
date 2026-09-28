# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Piggybank(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Piggybank.gd"

	def _init_fields(self):
		super()._init_fields()
		self.piggyPinataDescriptor = None
		self.hammerDescriptor = None
		self.thorsHammerDescriptor = None


	def onShopEntered(self):
		self.giveGold(self.getP1())
		self.explodeRandomly()


	def explodeRandomly(self):
		if not self.isBaseItem() and not self.isBoundAsIngredient() and self.hasPinata():
			if self.ctx.util.flipPercent(self.piggyPinataDescriptor.shopChance):
				self.explode()
				self.inventory.removeItem(self)
				self.discard()


	def canAffect(self, item):
		return item.hasStartofBattle()


	def onCombatStart(self):
		self.giveMaxHealth(self.getP_m("maxhealth") * self.getNumAffectedItems())
		self.consume()


	def hasPinata(self):
		return self.ctx.item_book.isItemInInventory(self.piggyPinataDescriptor)


	def isSmashRecipe(self):
		return (self.curRecipe.ingredients[0] == self.hammerDescriptor or 
				self.curRecipe.ingredients[0] == self.thorsHammerDescriptor)


	def getFusionItemName(self):
		if self.isSmashRecipe() and self.hasPinata():
			return self.ctx.util.tr("Piggy Pinata_CRAFT")
		return super().getFusionItemName()


	def allowGeneratingFusionItem(self):
		if self.isSmashRecipe() and self.hasPinata():
			return False
		return True


	def explode(self):
		pass

	def finishFusing(self):

		if self.isSmashRecipe():
			self.explode()

		super().finishFusing()


	def getShopPriority(self):
		return _R.C("CoreConst").Priority.Lowest

	def _readyInit(self):
		super()._readyInit()
		self.piggyPinataDescriptor = self.ctx.item_book.getDescriptor("Piggy Pinata")
		self.hammerDescriptor = self.ctx.item_book.getDescriptor("Hammer")
		self.thorsHammerDescriptor = self.ctx.item_book.getDescriptor("Thors Hammer")


_R.reg("res://gd_core_items/Piggybank.gd", Piggybank)
_R.reg("Piggybank", Piggybank)
