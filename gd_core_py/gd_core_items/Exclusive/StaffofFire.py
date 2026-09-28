# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__StaffofFire(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/StaffofFire.gd"

	def _init_fields(self):
		super()._init_fields()
		self.numActivations = 0
		self.activationParticles = None
		self.manaCost = 0
		self.heatCost = 0
		self.damBonus = 0


	def onPrepare(self):
		self.numActivations = 0


	def onPreDealDamage_early(self, damageRes):
		if self.character().getHeat() >= self.heatCost:
			event = self.tryUseMana(self.manaCost)
			if event != None:
				self.useHeat(self.heatCost, event)
				self.addBonusDamage(self.damBonus)
				self.numActivations += 1


	def onShopEntered(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.manaCost = self.getP1()
		self.heatCost = self.getP2()
		self.damBonus = self.getP3()
		pass



_R.reg("res://gd_core_items/Exclusive/StaffofFire.gd", Exclusive__StaffofFire)
_R.reg("StaffofFire", Exclusive__StaffofFire)
