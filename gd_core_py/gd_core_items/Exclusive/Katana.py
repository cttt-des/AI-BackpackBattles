# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Katana(_R.C("res://gd_core_items/RibSawBlade.gd")):

	resource_path = "res://gd_core_items/Exclusive/Katana.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffsNeeded = None
		self.removeBuffs = None


	def onPreDealDamage_early(self, damageRes):
		super().onPreDealDamage_early(damageRes)
		if damageRes.hasHit():
			buffs = self.opponent().getBuffStacks()
			if buffs >= self.buffsNeeded:
				self.removeMostBuffs(self.removeBuffs)

	def _readyInit(self):
		super()._readyInit()
		self.buffsNeeded = int(self.getP("buffst"))
		self.removeBuffs = int(self.getP("buffs"))


_R.reg("res://gd_core_items/Exclusive/Katana.gd", Exclusive__Katana)
_R.reg("Katana", Exclusive__Katana)
