# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__FalseLife(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/FalseLife.gd"

	def _init_fields(self):
		super()._init_fields()
		self.maxHealthAmp = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Dark)


	def canAffect_global(self, item):
		return item.descriptor.hasParam("maxhealth")


	def onPrepare(self):
		self.character().changeMaxHealthGain(self.maxHealthAmp)
		self.connectForCombat(self.character(), "character_overhealed", "onOverheal")


	def doCooldownEffect(self):
		healAmount = self.getP_m("heal") + self.getP_m("heal_dark") * self.getNumAffectedItems()
		self.heal(healAmount)
		self.activate()


	def onOverheal(self, overheal, healEvent):
		self.giveMaxHealth(overheal, healEvent)

	def _readyInit(self):
		super()._readyInit()
		self.maxHealthAmp = _div(self.getP('healthamp'), 100.0)


_R.reg("res://gd_core_items/Exclusive/FalseLife.gd", Exclusive__FalseLife)
_R.reg("FalseLife", Exclusive__FalseLife)
