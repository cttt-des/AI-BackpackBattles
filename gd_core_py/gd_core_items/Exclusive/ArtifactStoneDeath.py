# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ArtifactStoneDeath(_R.C("res://gd_core_items/Stone.gd")):

	resource_path = "res://gd_core_items/Exclusive/ArtifactStoneDeath.gd"

	def _init_fields(self):
		super()._init_fields()
		self.lastFatigueDam = 0
		self.activationParticles = None


	def onPrepare(self):
		self.lastFatigueDam = 0
		self.connectForCombat(self.opponent(), "fatigue_damage_changed", "onFatigueDamageChanged")
		self.connectForCombat(self.ctx.combat, "fatigue_damage_changed", "onFatigueDamageChanged")


	def canAffect(self, item):
		return item.canDamage()


	def onFatigueDamageChanged(self):
		fatigueDam = self.ctx.fatigueDamageSource.minDamage + self.opponent().getBonusFatigueDamage()
		fatigueDiff = fatigueDam - self.lastFatigueDam
		self.lastFatigueDam = fatigueDam

		for item in _iter(self.getAffectedItems()):
			item.changeCritChancePercent(self.getChance() * fatigueDiff)


	def preHit(self):
		self.inflictFatigueDamage()


	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/ArtifactStoneDeath.gd", Exclusive__ArtifactStoneDeath)
_R.reg("ArtifactStoneDeath", Exclusive__ArtifactStoneDeath)
