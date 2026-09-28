# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class PotionBelt(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/PotionBelt.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedPotions = []
		self.numConsumed = 0


	def onPrepare(self):
		self.numConsumed = 0
		self.affectedPotions.clear()
		affectedItems = self.getItemsInside()
		for item in _iter(affectedItems):
			if self.canApplyEffect(item):
				self.affectedPotions.append(item)
				self.connectForCombat(item, "potion_emptied", "onPotionEmptied")


	def onPotionEmptied(self, _potion):
		numBuffs = 0
		active = False
		self.numConsumed += 1

		if self.numConsumed == 1:
			numBuffs = 1
			active = True

		elif self.numConsumed == 4:
			self.cleanseRandomDebuffs(self.getP1())
			active = True

		if self.isTypeInInventory(self.ctx.item_book.getDescriptor("Bagtacular")):
			numBuffs += int(self.ctx.item_book.getDescriptor("Bagtacular").getP("buffs"))
			active = True

		if numBuffs > 0:
			self.giveRandomBuffs(numBuffs)

		if active:
			self.activate()










	def canApplyEffect(self, toItem):
		return toItem.hasType(_R.C("CoreConst").Type.Potion)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/PotionBelt.gd", PotionBelt)
_R.reg("PotionBelt", PotionBelt)
