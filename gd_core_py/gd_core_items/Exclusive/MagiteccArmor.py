# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MagiteccArmor(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/MagiteccArmor.gd"

	def _init_fields(self):
		super()._init_fields()
		self.speedPerAffected = None
		self.manaNeeded = None
		self.numDebuffs = None
		self.block2 = None


	def canAffect(self, item):
		return item.hasType(_H_1) or item.hasType(_H_2)


	def onPrepare(self):
		self.addSpeed(self.getNumAffectedItems() * self.speedPerAffected)


	def onCombatStart(self):
		self.giveBlock()
		self.activate()


	def doCooldownEffect(self):
		if self.character().getMana() >= self.manaNeeded:
			event = self.useMana(self.manaNeeded)
			self.cleanseRandomDebuffs(self.numDebuffs, event)
			self.giveBlock(self.block2, True, event)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.speedPerAffected = _div(self.getP('speed'), 100.0)
		self.manaNeeded = int(self.getP("manat"))
		self.numDebuffs = int(self.getP("cleanse"))
		self.block2 = int(self.getP("block"))


_R.reg("res://gd_core_items/Exclusive/MagiteccArmor.gd", Exclusive__MagiteccArmor)
_R.reg("MagiteccArmor", Exclusive__MagiteccArmor)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Type.Holy
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").Type.Magic
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
