# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Broccoli(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core_items/Exclusive/Broccoli.gd"

	def _init_fields(self):
		super()._init_fields()
		self.luck = None
		self.luckNeeded = None
		self.regen = None


	def doCooldownEffect(self):
		if self.character().getLucky() >= self.luckNeeded:
			self.giveRegeneration(self.regen)
		else:
			self.giveLucky(self.luck)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.luck = int(self.getP("luck"))
		self.luckNeeded = int(self.getP("luckt"))
		self.regen = int(self.getP("regen"))


_R.reg("res://gd_core_items/Exclusive/Broccoli.gd", Exclusive__Broccoli)
_R.reg("Broccoli", Exclusive__Broccoli)
