# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class ClawsofAttack(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/ClawsofAttack.gd"

	def _init_fields(self):
		super()._init_fields()
		self.attackCounter = 0
		self.lastSpeedBonus = 0.0
		self.speedPerSpike = None
		self.numHits = None


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_spikes_changed", "onSpikesChanged")


	def onSpikesChanged(self, _amount, _event):
		clawsBonus = min(self.speedPerSpike * self.character().getSpikes(), self.getP2())
		clawsBonus /= 100.0
		self.addSpeed(clawsBonus - self.lastSpeedBonus)
		self.lastSpeedBonus = clawsBonus


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.attackCounter += 1
			if self.attackCounter == self.numHits:
				self.giveEmpower(1)
				self.attackCounter = 0


	def onShopEntered(self):
		self.lastSpeedBonus = 0.0
		self.attackCounter = 0

	def _readyInit(self):
		super()._readyInit()
		self.speedPerSpike = self.getP1()
		self.numHits = int(self.getP3())


_R.reg("res://gd_core_items/ClawsofAttack.gd", ClawsofAttack)
_R.reg("ClawsofAttack", ClawsofAttack)
