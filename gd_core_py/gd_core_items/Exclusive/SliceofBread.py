# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SliceofBread(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core_items/Exclusive/SliceofBread.gd"

	def _init_fields(self):
		super()._init_fields()
		self.staminaThreshold = None
		self.stamina = None


	def doCooldownEffect(self):
		if self.character().getCurrentStamina() < self.staminaThreshold:
			self.giveStamina(self.stamina)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.staminaThreshold = self.getP("staminat")
		self.stamina = self.getP("stamina")


_R.reg("res://gd_core_items/Exclusive/SliceofBread.gd", Exclusive__SliceofBread)
_R.reg("SliceofBread", Exclusive__SliceofBread)
