# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__IceArmor(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/IceArmor.gd"


	def onCombatStart(self):
		self.giveBlock()
		self.inflictCold(self.getP1())
		self.activate()


	def doCooldownEffect(self):
		if self.character().getHeat() >= self.getP2():
			self.useHeat(self.getP2())
			self.inflictCold(self.getP3())
			self.giveBlock(self.getP4())
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/IceArmor.gd", Exclusive__IceArmor)
_R.reg("IceArmor", Exclusive__IceArmor)
