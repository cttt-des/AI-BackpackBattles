# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BurningSword(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/BurningSword.gd"

	def _init_fields(self):
		super()._init_fields()
		self.heatCounter = 0
		self.particleReadyTime = 0.0
		self.heatOnHit = 0
		self.heatNeeded = 0


	def canAffect(self, item):
		return item.canBeEmpowered()


	def onPrepare(self):
		self.heatCounter = 0
		self.connectForCombat(self.character(), "character_heat_changed", "onHeatChanged")


	def onHeatChanged(self, amount, _event):
		if amount > 0:
			self.heatCounter += amount
			bonus = _div(self.heatCounter, self.heatNeeded)
			if bonus > 0:
				bonusDamage = self.getP3() * bonus
				for item in _iter(self.getAffectedItems()):
					item.addBonusDamage(bonusDamage)
				self.addBonusDamage(bonusDamage)

				if self.ctx.time >= self.particleReadyTime:
					self.particleReadyTime = self.ctx.time + 0.1

			self.heatCounter %= self.heatNeeded


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			self.giveHeat(self.heatOnHit)

	def _readyInit(self):
		super()._readyInit()
		self.heatOnHit = self.getP1()
		self.heatNeeded = self.getP2()


_R.reg("res://gd_core_items/Exclusive/BurningSword.gd", Exclusive__BurningSword)
_R.reg("BurningSword", Exclusive__BurningSword)
