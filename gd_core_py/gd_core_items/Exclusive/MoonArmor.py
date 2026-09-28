# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MoonArmor(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/MoonArmor.gd"

	def _init_fields(self):
		super()._init_fields()
		self.mana = 0
		self.reflect = 0


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Magic)


	def onCombatStart(self):
		self.giveBlock(self.getBlock() + self.getP1() * self.getNumAffectedItems())
		self.activate()


	def doCooldownEffect(self):
		self.giveMana(self.mana)
		self.giveReflectStacks(self.reflect)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.mana = self.getP("mana")
		self.reflect = self.getP("reflect")


_R.reg("res://gd_core_items/Exclusive/MoonArmor.gd", Exclusive__MoonArmor)
_R.reg("MoonArmor", Exclusive__MoonArmor)
