# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__FlameWhip(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/FlameWhip.gd"

	def _init_fields(self):
		super()._init_fields()
		self._spikesNeeded = 0
		self._heatGain = 0
		self.bonusDamage = 0.0

	@property
	def spikesNeeded(self):
		return self._spikesNeeded
	@spikesNeeded.setter
	def spikesNeeded(self, v):
		self._spikesNeeded = int(v)
	@property
	def heatGain(self):
		return self._heatGain
	@heatGain.setter
	def heatGain(self, v):
		self._heatGain = int(v)

	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			if self.character().getSpikes() >= self.spikesNeeded:
				self.useSpikes(self.spikesNeeded)
				damageRes.damage += self.bonusDamage
				self.giveHeat(self.heatGain)

	def _readyInit(self):
		super()._readyInit()
		self.spikesNeeded = self.getP("spikes")
		self.heatGain = self.getP("heat")
		self.bonusDamage = self.getP("bonusdam")


_R.reg("res://gd_core_items/Exclusive/FlameWhip.gd", Exclusive__FlameWhip)
_R.reg("FlameWhip", Exclusive__FlameWhip)
