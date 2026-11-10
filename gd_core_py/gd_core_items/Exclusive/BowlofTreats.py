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
		return item.hasType(_H_1)


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

		if rarity >= _H_2:
			rarity = self.ctx.util.pickRandomElement([_H_3, _H_4, _H_5])

		if rarity == _H_3:
				itemName = "Rat"
		elif rarity == _H_4:
				itemName = "Squirrel"
		elif rarity == _H_5:
				itemName = "Hedgehog"

		return self.ctx.item_book.getDescriptor(itemName)

	def _readyInit(self):
		super()._readyInit()
		self.speedBonus = self.getP2()
		self.maxSpeedBonus = self.getP3()


_R.reg("res://gd_core_items/Exclusive/BowlofTreats.gd", Exclusive__BowlofTreats)
_R.reg("BowlofTreats", Exclusive__BowlofTreats)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Pet
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Rarity.Legendary
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").Rarity.Common
except AttributeError as _he:
	_H_3 = _HoistPending(_he)
try:
	_H_4 = _R.C("CoreConst").Rarity.Rare
except AttributeError as _he:
	_H_4 = _HoistPending(_he)
try:
	_H_5 = _R.C("CoreConst").Rarity.Epic
except AttributeError as _he:
	_H_5 = _HoistPending(_he)
