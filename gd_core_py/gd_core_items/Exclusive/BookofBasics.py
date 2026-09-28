# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BookofBasics(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/BookofBasics.gd"

	def _init_fields(self):
		super()._init_fields()
		self.bonusHealthFactor = 0
		self.salesChance = None
		self.manaNeeded = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Spell)


	def onPrepare(self):
		self.bonusHealthFactor = 0
		for item in _iter(self.getAffectedItems()):
			if item.isCrafted():
				self.bonusHealthFactor += 2
			else:
				self.bonusHealthFactor += 1


	def doCooldownEffect(self):
		if self.character().getMana() >= self.manaNeeded:
			event = self.useMana(self.manaNeeded)
			self.giveMaxHealth(self.getP_m("maxhealth") + self.getP_m("maxhealth_spell") * self.bonusHealthFactor, 
			event)
		self.activate()


	def onSaleRoll(self, item):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.salesChance = _div(self.getShopChance(), 100.0)
		self.manaNeeded = int(self.getP("manat"))


_R.reg("res://gd_core_items/Exclusive/BookofBasics.gd", Exclusive__BookofBasics)
_R.reg("BookofBasics", Exclusive__BookofBasics)
