# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MoonArmor(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/MoonArmor.gd"

	def _init_fields(self):
		super()._init_fields()
		self._mana = 0
		self._reflect = 0

	@property
	def mana(self):
		return self._mana
	@mana.setter
	def mana(self, v):
		self._mana = int(v)
	@property
	def reflect(self):
		return self._reflect
	@reflect.setter
	def reflect(self, v):
		self._reflect = int(v)

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
