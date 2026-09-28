# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__NullBlade(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/NullBlade.gd"

	def _init_fields(self):
		super()._init_fields()
		self.luckNeeded = None
		self.regenNeeded = None
		self.dam = None
		self.buffs = None
		self.speedBonus = None
		self.distortion = None


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			if self.character().getLucky() >= self.luckNeeded:
				self.useLucky(self.luckNeeded)
				damageRes.damage += self.dam
				self.addBonusDamage(self.dam)

			if self.character().getRegeneration() >= self.regenNeeded:
				self.useRegeneration(self.regenNeeded)
				self.removeRandomBuffs(self.buffs)
				if self.opponent().getBuffStacks() == 0:
					self.addSpeed(self.speedBonus)



	def pickup(self, pickupType=GD_DEFAULT):
		if pickupType is GD_DEFAULT:
			pickupType = self.PickupType.Grabbed
		super().pickup(pickupType)


	def drop(self):
		res = super().drop()
		return res

	def _readyInit(self):
		super()._readyInit()
		self.luckNeeded = int(self.getP("luckt"))
		self.regenNeeded = int(self.getP("regent"))
		self.dam = int(self.getP("dam"))
		self.buffs = int(self.getP("buffs"))
		self.speedBonus = _div(self.getP('speed'), 100.0)
		pass



_R.reg("res://gd_core_items/Exclusive/NullBlade.gd", Exclusive__NullBlade)
_R.reg("NullBlade", Exclusive__NullBlade)
