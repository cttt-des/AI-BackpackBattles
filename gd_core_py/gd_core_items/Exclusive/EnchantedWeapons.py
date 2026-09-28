# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__EnchantedWeapons(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/EnchantedWeapons.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffs = None


	def canAffect(self, item):
		return item.hasAttackEffect()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.giveDoubleAttackEffectChance(self.getChance())


	def doCooldownEffect(self):
		self.giveLeastBuffs(self.buffs)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.buffs = int(self.getP("buffs"))


_R.reg("res://gd_core_items/Exclusive/EnchantedWeapons.gd", Exclusive__EnchantedWeapons)
_R.reg("EnchantedWeapons", Exclusive__EnchantedWeapons)
