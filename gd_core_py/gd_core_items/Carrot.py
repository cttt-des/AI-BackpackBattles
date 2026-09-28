# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Carrot(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core_items/Carrot.gd"


	def doCooldownEffect(self):
		self.cleanseRandomDebuffs(1)

		if self.character().getLucky() >= self.getP2():
			if self.rollChance():
				self.giveEmpower(1)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Carrot.gd", Carrot)
_R.reg("Carrot", Carrot)
