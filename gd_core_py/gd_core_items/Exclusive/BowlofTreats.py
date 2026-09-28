# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BowlofTreats(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core_items/Exclusive/BowlofTreats.gd"

	def _init_fields(self):
		super()._init_fields()
		self.speedBonusGiven = 0.0
		self.speedBonus = None
		self.maxSpeedBonus = None


	def canAffect_global(self, item):
		return item.hasType(_R.C("CoreConst").Type.Pet)


	def onPrepare(self):
		self.speedBonusGiven = 0.0

		for item in _iter(self.inventory.getItems()):
			if self.canAffect_global(item):
				item.giveDoubleActivationChance(self.getChance())


	def doCooldownEffect(self):
		self.giveRandomBuffs(self.getP1())
		if self.speedBonusGiven < self.maxSpeedBonus:
			for item in _iter(self.getAffectedItems()):
				curBonus = min(self.speedBonus, self.maxSpeedBonus - self.speedBonusGiven)
				item.addSpeed(_div(curBonus, 100))

			self.speedBonusGiven += self.speedBonus
		self.activate()


	def getGatedDescriptor(self, rarity):
		itemName = None

		if rarity >= _R.C("CoreConst").Rarity.Legendary:
			rarity = self.ctx.util.pickRandomElement([_R.C("CoreConst").Rarity.Common, _R.C("CoreConst").Rarity.Rare, _R.C("CoreConst").Rarity.Epic])

		if rarity == _R.C("CoreConst").Rarity.Common:
				itemName = "Rat"
		elif rarity == _R.C("CoreConst").Rarity.Rare:
				itemName = "Squirrel"
		elif rarity == _R.C("CoreConst").Rarity.Epic:
				itemName = "Hedgehog"

		return self.ctx.item_book.getDescriptor(itemName)

	def _readyInit(self):
		super()._readyInit()
		self.speedBonus = self.getP2()
		self.maxSpeedBonus = self.getP3()


_R.reg("res://gd_core_items/Exclusive/BowlofTreats.gd", Exclusive__BowlofTreats)
_R.reg("BowlofTreats", Exclusive__BowlofTreats)
