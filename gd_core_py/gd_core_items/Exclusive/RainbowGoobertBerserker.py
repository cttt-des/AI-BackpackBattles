# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__RainbowGoobertBerserker(_R.C("res://gd_core_items/Goobert.gd")):

	resource_path = "res://gd_core_items/Exclusive/RainbowGoobertBerserker.gd"


	def doCooldownEffect(self):
		self.giveBlock()
		self.giveMaxHealth()
		self.giveVampirism(self.getP3())
		self.giveRandomBuffs(self.getP4())
		self.inflictBlind(self.getP("blind"))

		for item in _iter(self.getAffectedItems()):
			if item.canBeEmpowered():
				item.addBonusDamage(self.getP5())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/RainbowGoobertBerserker.gd", Exclusive__RainbowGoobertBerserker)
_R.reg("RainbowGoobertBerserker", Exclusive__RainbowGoobertBerserker)
