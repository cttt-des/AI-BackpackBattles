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
		return item.hasType(_R.C("CoreConst").Type.Shield)


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
		super()._readyInit()
		self.extraDamBlock = _div(self.getP('bonus_damblock'), 100.0)
		self.maxHealthBlock = _div(self.getP('block2'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Turtle.gd", Exclusive__Turtle)
_R.reg("Turtle", Exclusive__Turtle)
