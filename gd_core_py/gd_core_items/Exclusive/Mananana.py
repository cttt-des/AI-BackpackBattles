# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Mananana(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core_items/Exclusive/Mananana.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaNeeded = None
		self.stamina = None


	def doCooldownEffect(self):
		if self.character().getMana() >= self.manaNeeded:
			event2 = self.useMana(self.manaNeeded)
			self.heal(self.getP_m("heal"), event2)
			self.giveStamina(self.stamina, event2)
		self.activate()


	def getTranslatedName(self, removeLinebreaks=False):
		return ""

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP("manat"))
		self.stamina = self.getP("stamina")


_R.reg("res://gd_core_items/Exclusive/Mananana.gd", Exclusive__Mananana)
_R.reg("Mananana", Exclusive__Mananana)
