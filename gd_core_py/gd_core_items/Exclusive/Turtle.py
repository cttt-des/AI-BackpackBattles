# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Turtle(_R.C("res://gd_core_items/LeatherHelm.gd")):

	resource_path = "res://gd_core_items/Exclusive/Turtle.gd"

	def _init_fields(self):
		super()._init_fields()
		self.extraDamBlock = None
		self.maxHealthBlock = None


	def canAffect(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.modifyParam("damblock", self.extraDamBlock)


	def onPreCombatStart(self):
		super().onPreCombatStart()
		self.opponent().changeDamageResistance(self.damReduction)


	def buffEnded(self):
		super().buffEnded()
		self.opponent().changeDamageResistance( - self.damReduction)


	def doCooldownEffect(self):
		blockAmount = self.getBlock() + self.character().getMaxHealth() * self.maxHealthBlock
		self.giveBlock(blockAmount)
		self.activate()

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.extraDamBlock = _div__loc(self.getP('bonus_damblock'), 100.0)
		self.maxHealthBlock = _div__loc(self.getP('block2'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Turtle.gd", Exclusive__Turtle)
_R.reg("Turtle", Exclusive__Turtle)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Shield
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
