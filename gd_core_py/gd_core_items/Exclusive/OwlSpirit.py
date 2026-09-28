# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__OwlSpirit(_R.C("res://gd_core_items/Exclusive/SpiritCompanion.gd")):

	resource_path = "res://gd_core_items/Exclusive/OwlSpirit.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaNeeded = None
		self.mana = None
		self.fatigueMana = None


	def canAffect(self, item):
		return item.gainsBuffs()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.changeAmplificiationChancePercent_allBuffs(self.getChance())


	def doCooldownEffect(self):
		if self.character().getMana() >= self.manaNeeded:
			event = self.useMana(self.manaNeeded)
			if self.ctx.combat.hasFatigueStarted():
				self.giveMana(self.fatigueMana, event)
			else:
				self.giveMana(self.mana, event)
		self.activate()


	def playPickupSound(self):
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP("manat"))
		self.mana = int(self.getP("mana"))
		self.fatigueMana = int(self.getP("fatiguemana"))


_R.reg("res://gd_core_items/Exclusive/OwlSpirit.gd", Exclusive__OwlSpirit)
_R.reg("OwlSpirit", Exclusive__OwlSpirit)
