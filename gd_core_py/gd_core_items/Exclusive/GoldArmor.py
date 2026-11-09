# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__GoldArmor(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/GoldArmor.gd"

	def _init_fields(self):
		super()._init_fields()
		self.gold = None
		self.regen = None
		self.cleanse = None
		self.block = None
		self.speedMalus = None


	def onShopEntered(self):
		self.giveGold(self.gold)


	def canAffect(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		for item in _iter(self.inventory.getItems()):
			if item.hasType(_H_2):
				item.reduceSpeed(self.speedMalus)


	def onCombatStart(self):
		self.giveRegeneration(self.getNumAffectedItems() * self.regen)
		self.giveBlock()
		self.activate()


	def doCooldownEffect(self):
		self.cleanseRandomDebuffs(self.cleanse)
		if self.character().getDebuffStacks() == 0:
			self.giveBlock(self.block)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.gold = int(self.getP("gold"))
		self.regen = int(self.getP("regen"))
		self.cleanse = int(self.getP("cleanse"))
		self.block = self.getP("block")
		self.speedMalus = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/GoldArmor.gd", Exclusive__GoldArmor)
_R.reg("GoldArmor", Exclusive__GoldArmor)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Type.Holy
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").Type.Weapon
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
