# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ParadiseBirb(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ParadiseBirb.gd"

	def _init_fields(self):
		super()._init_fields()
		self.numActivations = 0
		self.speedBonus = None
		self.maxActivations = None
		self.bonusHeal = None


	def canAffect(self, item):
		return (item.hasCooldown() or item.gainsBuffs() or item.canHealOrLifesteal())


	def onPrepare(self):
		self.numActivations = 0


	def doCooldownEffect(self):
		if self.numActivations < self.maxActivations:

			for item in _iter(self.getAffectedItems()):
				item.addSpeed(self.speedBonus)
				item.changeAmplificiationChancePercent_allBuffs(self.getChance())
				item.changeHealAmp(self.bonusHeal)

			self.numActivations += 1

			if self.numActivations == self.maxActivations:
				self.onAfterEffectFinished()
			else:
				self.activate()


	def playPickupSound(self):
		pitch = self.ctx.rng.randf_range(0.8, 1.0)


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume
		pitch = self.ctx.rng.randf_range(0.8, 1.0)

	def _readyInit(self):
		super()._readyInit()
		self.speedBonus = _div(self.getP('speed'), 100.0)
		self.maxActivations = int(self.getP("max"))
		self.bonusHeal = _div(self.getP('healamp'), 100.0)


_R.reg("res://gd_core_items/Exclusive/ParadiseBirb.gd", Exclusive__ParadiseBirb)
_R.reg("ParadiseBirb", Exclusive__ParadiseBirb)
