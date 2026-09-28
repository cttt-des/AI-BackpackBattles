# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class RainbowGoobert(_R.C("res://gd_core_items/Goobert.gd")):

	resource_path = "res://gd_core_items/RainbowGoobert.gd"


	def doCooldownEffect(self):
		self.giveBlock()
		self.heal()
		self.giveVampirism(self.getP3())
		self.inflictBlind(self.getP4())
		self.inflictPoison(self.getP4())

		for item in _iter(self.getAffectedItems()):
			if item.canBeEmpowered():
				item.addBonusDamage(self.getP5())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/RainbowGoobert.gd", RainbowGoobert)
_R.reg("RainbowGoobert", RainbowGoobert)
