# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SliceofToast(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core_items/Exclusive/SliceofToast.gd"

	def _init_fields(self):
		super()._init_fields()
		self.staminaThreshold = None
		self.stamina = None
		self.regen = None


	def doCooldownEffect(self):
		if self.character().getCurrentStamina() < self.staminaThreshold:
			self.giveStamina(self.stamina)
		else:
			self.giveRegeneration(self.regen)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.staminaThreshold = self.getP("staminat")
		self.stamina = self.getP("stamina")
		self.regen = int(self.getP("regen"))


_R.reg("res://gd_core_items/Exclusive/SliceofToast.gd", Exclusive__SliceofToast)
_R.reg("SliceofToast", Exclusive__SliceofToast)
