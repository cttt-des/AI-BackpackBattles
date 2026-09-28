# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__LuckyCat(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/LuckyCat.gd"

	def _init_fields(self):
		super()._init_fields()
		self.sales = None
		self.goldThreshold1 = None
		self.goldThreshold2 = None


	def canAffect(self, item):
		return True


	def getCounterValue(self):
		return self.getAffectedGoldValue()


	def condition1Fulfilled(self, gold):
		return gold > self.goldThreshold1


	def condition2Fulfilled(self, gold):
		return gold > self.goldThreshold2


	def onPrepare(self):
		gold = self.getCounterValue()
		if self.condition1Fulfilled(gold):


			self.character().changeCritResistance(self.getChance())

			if self.condition2Fulfilled(gold):
				bonusSpeed = _div(self.getP('speed'), 100.0)
				for item in _iter(self.inventory.getItems()):
					if self.canAffect_global(item):
						item.addSpeed(bonusSpeed)




	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		colors = [self.ctx.util.inactiveColor, self.ctx.util.inactiveColor]
		gold = None

		if self.placed:
			gold = self.getCounterValue()
			if self.condition1Fulfilled(gold):
				colors[0] = self.ctx.util.modifiedColor
				if self.condition2Fulfilled(gold):
					colors[1] = self.ctx.util.modifiedColor

		descr = self.getModeDescription(descr, colors, True, wrapInColor)






		return descr



	def updatePaws(self):
		gold = self.getCounterValue()
		if self.condition1Fulfilled(gold):
			if self.condition2Fulfilled(gold):
				pass
			else:
				pass
		else:
			pass

		self.updateShadowTexture()



	def onAffectedItemAdded(self, item, color):
		self.updatePaws()


	def onAffectedItemRemoved(self, item, color):
		self.updatePaws()


	def onAddToInventory(self):
		self.updatePaws()


	def onRemoveFromInventory(self):
		self.updateShadowTexture()


	def canAffect_global(self, item):
		return item.getRarity() >= _R.C("CoreConst").Rarity.Godly and item.hasCooldown()


	def onSaleRoll(self, _item):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.sales = _div(self.getP('sales'), 100.0)
		self.goldThreshold1 = self.getP("gold1")
		self.goldThreshold2 = self.getP("gold2")


_R.reg("res://gd_core_items/Exclusive/LuckyCat.gd", Exclusive__LuckyCat)
_R.reg("LuckyCat", Exclusive__LuckyCat)
