# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SpikedStaff(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/SpikedStaff.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaCost = None
		self.empower = None
		self.spikes = None


	def onPreDealDamage_early(self, damageRes):
		event = self.tryUseMana(self.manaCost)
		if event != None:
			self.giveEmpower(self.empower, event)
			if self.character().isBattleRaging():
				self.giveSpikes(self.spikes, event)

	def _readyInit(self):
		super()._readyInit()
		self.manaCost = self.getP("mana")
		self.empower = self.getP("empower")
		self.spikes = self.getP("spikes")


_R.reg("res://gd_core_items/Exclusive/SpikedStaff.gd", Exclusive__SpikedStaff)
_R.reg("SpikedStaff", Exclusive__SpikedStaff)
