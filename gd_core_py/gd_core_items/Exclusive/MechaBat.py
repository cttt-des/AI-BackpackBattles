# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MechaBat(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/MechaBat.gd"

	def _init_fields(self):
		super()._init_fields()
		self.lifestealActive = False
		self.lifestealParticles = None
		self.lifestealLight = None
		self.vampirism1 = None
		self.luckNeeded = None
		self.luckUsed = None
		self.vampirism2 = None


	def canAffect(self, item):
		return item.canDamage()


	def doCooldownEffect(self):
		numVamp = 0
		if self.character().getLucky() >= self.luckNeeded:
			self.useLucky(self.luckUsed)
			numVamp += self.vampirism2

		if self.useStamina() == _R.C("CoreConst").StaminaResult.Sufficient:
			numVamp += self.vampirism1

		if numVamp > 0:
			self.giveVampirism(numVamp)
			self.activate()


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.opponent(), "character_attacked", "onOpponentDamaged")


	def onOpponentDamaged(self, damageRes):
		if self.lifestealActive:
			if damageRes.hasHit() and damageRes.damageSource.canApplyLifesteal():
				if damageRes.damageSource.origin in self.getAffectedItems():
					self.heal(ceil(_div(damageRes.damage * self.getP_m('lifesteal'), 100.0)), damageRes.event)


	def onChargeReceived(self, _charge):
		if self.numCharges == 1:
			self.setState(True)


	def onChargeLeft(self, _charge):
		if self.numCharges == 0:
			self.setState(False)


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, _lifestealActive):
		self.lifestealActive = _lifestealActive
		if self.lifestealActive:
			pass
		else:
			pass

	def _readyInit(self):
		super()._readyInit()
		self.vampirism1 = int(self.getP("vampirism"))
		self.luckNeeded = int(self.getP("luckt"))
		self.luckUsed = int(self.getP("luck"))
		self.vampirism2 = int(self.getP("vampirism2"))


_R.reg("res://gd_core_items/Exclusive/MechaBat.gd", Exclusive__MechaBat)
_R.reg("MechaBat", Exclusive__MechaBat)
