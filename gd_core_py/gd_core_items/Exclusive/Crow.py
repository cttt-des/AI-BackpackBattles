# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Crow(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Crow.gd"

	def _init_fields(self):
		super()._init_fields()
		self.numActivations = 0
		self.speedBonus = None
		self.maxActivations = None
		self.luck = None


	def canAffect(self, item):
		return item.hasCooldown() or item.inflictsDebuffs()


	def onPrepare(self):
		self.numActivations = 0


	def doCooldownEffect(self):
		if self.numActivations < self.maxActivations:
			for item in _iter(self.getAffectedItems()):

				item.addSpeed(self.speedBonus)
				item.changeAmplificiationChancePercent_allDebuffs(self.getChance())

			self.numActivations += 1

		luckToRemove = min(self.luck, self.opponent().getLucky())
		if luckToRemove > 0:
			self.stealStack(_R.C("CoreConst").EventType.Lucky, luckToRemove)

		self.activate()


	def playPickupSound(self):
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

	def _readyInit(self):
		super()._readyInit()
		self.speedBonus = _div(self.getP('speed'), 100.0)
		self.maxActivations = int(self.getP("max"))
		self.luck = int(self.getP("luck"))


_R.reg("res://gd_core_items/Exclusive/Crow.gd", Exclusive__Crow)
_R.reg("Crow", Exclusive__Crow)
