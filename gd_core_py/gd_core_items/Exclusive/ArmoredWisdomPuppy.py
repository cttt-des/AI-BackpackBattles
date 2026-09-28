# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ArmoredWisdomPuppy(_R.C("res://gd_core_items/Exclusive/WisdomPuppy.gd")):

	resource_path = "res://gd_core_items/Exclusive/ArmoredWisdomPuppy.gd"

	def _init_fields(self):
		super()._init_fields()
		self.bonusBlock = 0
		self.cold = 0


	def onPrepare(self):
		super().onPrepare()
		self.bonusBlock = 0


	def doCooldownEffect(self):
		self.giveBlock(self.getBlock() + self.bonusBlock)
		self.cleanseCold(self.cold)
		self.activate()
		self.bonusBlock += self.getP3()

	def _readyInit(self):
		super()._readyInit()
		self.cold = self.getP1()


_R.reg("res://gd_core_items/Exclusive/ArmoredWisdomPuppy.gd", Exclusive__ArmoredWisdomPuppy)
_R.reg("ArmoredWisdomPuppy", Exclusive__ArmoredWisdomPuppy)
