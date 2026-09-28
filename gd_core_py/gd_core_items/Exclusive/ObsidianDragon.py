# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ObsidianDragon(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/ObsidianDragon.gd"

	def _init_fields(self):
		super()._init_fields()
		self.heatCounter = 0
		self.affectedWeapon = None
		self.heatNeeded = None
		self.bonusDam = None


	def canAffect(self, item):
		return item.canBeEmpowered()


	def onPrepare(self):
		self.affectedWeapon = self.getFirstAffectedItem()
		self.heatCounter = 0
		self.connectForCombat(self.character(), "character_heat_changed", "onHeatChanged")


	def onHeatChanged(self, amount, event):
		if amount > 0:
			self.heatCounter += amount
			proccs = _div(self.heatCounter, self.heatNeeded)
			if proccs > 0:
				self.heatCounter %= self.heatNeeded

				self.addBonusDamage(self.bonusDam * proccs)
				if self.affectedWeapon != None:
					self.affectedWeapon.addCritTokens(proccs)

	def _readyInit(self):
		super()._readyInit()
		self.heatNeeded = int(self.getP1())
		self.bonusDam = int(self.getP2())


_R.reg("res://gd_core_items/Exclusive/ObsidianDragon.gd", Exclusive__ObsidianDragon)
_R.reg("ObsidianDragon", Exclusive__ObsidianDragon)
