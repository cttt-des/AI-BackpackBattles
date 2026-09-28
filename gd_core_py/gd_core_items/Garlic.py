# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Garlic(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core_items/Garlic.gd"

	def _init_fields(self):
		super()._init_fields()
		self.extraBlock = 0


	def doCooldownEffect(self):
		self.giveBlock(self.getBlock() + self.extraBlock)
		if self.rollChance():
			self.removeVampirism(self.getP1())
		self.activate()


	def onShopEntered(self):
		self.extraBlock = 0


	def addBonusBlock(self, _extraBlock):
		self.extraBlock += _extraBlock

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Garlic.gd", Garlic)
_R.reg("Garlic", Garlic)
