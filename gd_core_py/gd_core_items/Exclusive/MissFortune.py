# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MissFortune(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/MissFortune.gd"

	def _init_fields(self):
		super()._init_fields()
		self.luckNeeded = None
		self.numBuffs = None
		self.activationParticles = None


	def doCooldownEffect(self):
		if self.character().getLucky() >= self.luckNeeded:
			event = self.useLucky(self.luckNeeded)
			self.giveMostBuffs(self.numBuffs, event)

		self.activate()


	def _readyInit(self):
		super()._readyInit()
		self.luckNeeded = self.getP("luck")
		self.numBuffs = self.getP("buffs")


_R.reg("res://gd_core_items/Exclusive/MissFortune.gd", Exclusive__MissFortune)
_R.reg("MissFortune", Exclusive__MissFortune)
