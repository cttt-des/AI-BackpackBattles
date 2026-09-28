# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class BloodGoobert(_R.C("res://gd_core_items/Goobert.gd")):

	resource_path = "res://gd_core_items/BloodGoobert.gd"

	def _init_fields(self):
		super()._init_fields()
		self.dam = None
		self.vampirism = None


	def onCombatStart(self):
		self.giveVampirism(self.vampirism)
		self.activate()


	def doCooldownEffect(self):
		self.stealLife(self.dam + self.character().getVampirism(), _div(self.getP_m('lifesteal'), 100.0))

	def _readyInit(self):
		super()._readyInit()
		self.dam = self.getP("dam")
		self.vampirism = int(self.getP("vampirism"))


_R.reg("res://gd_core_items/BloodGoobert.gd", BloodGoobert)
_R.reg("BloodGoobert", BloodGoobert)
