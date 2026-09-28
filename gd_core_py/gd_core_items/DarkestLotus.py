# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class DarkestLotus(_R.C("res://gd_core_items/Card.gd")):

	resource_path = "res://gd_core_items/DarkestLotus.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaParticles = None


	def doRevealEffect(self):
		mana = self.getP1() * self.chainPosition
		self.giveMana(mana)
		self.removeRandomBuffs(self.getP2() * self.chainPosition)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/DarkestLotus.gd", DarkestLotus)
_R.reg("DarkestLotus", DarkestLotus)
