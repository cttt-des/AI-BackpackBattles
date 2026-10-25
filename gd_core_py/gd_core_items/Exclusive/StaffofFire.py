# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__StaffofFire(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/StaffofFire.gd"

	def _init_fields(self):
		super()._init_fields()
		self._numActivations = 0
		self.activationParticles = None
		self._manaCost = 0
		self._heatCost = 0
		self._damBonus = 0

	@property
	def numActivations(self):
		return self._numActivations
	@numActivations.setter
	def numActivations(self, v):
		self._numActivations = int(v)
	@property
	def manaCost(self):
		return self._manaCost
	@manaCost.setter
	def manaCost(self, v):
		self._manaCost = int(v)
	@property
	def heatCost(self):
		return self._heatCost
	@heatCost.setter
	def heatCost(self, v):
		self._heatCost = int(v)
	@property
	def damBonus(self):
		return self._damBonus
	@damBonus.setter
	def damBonus(self, v):
		self._damBonus = int(v)

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
