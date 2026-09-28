# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ChiliPepper(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core_items/Exclusive/ChiliPepper.gd"


	def doCooldownEffect(self):
		self.giveHeat(self.getP1())
		self.heal()
		if self.character().getHeat() >= self.getP3():
			self.cleanseRandomDebuffs(1)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/ChiliPepper.gd", Exclusive__ChiliPepper)
_R.reg("ChiliPepper", Exclusive__ChiliPepper)
