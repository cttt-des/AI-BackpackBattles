# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class VampiricArmor(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/VampiricArmor.gd"


	def onCombatStart(self):
		self.healthToBlock(self.getP1(), self.getBlock())
		self.giveVampirism(self.getP2())
		self.activate()


	def doCooldownEffect(self):
		self.healthToBlock(self.getP3(), self.getP4())
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/VampiricArmor.gd", VampiricArmor)
_R.reg("VampiricArmor", VampiricArmor)
