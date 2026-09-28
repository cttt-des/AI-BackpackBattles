# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__JynxStaff(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/JynxStaff.gd"

	def _init_fields(self):
		super()._init_fields()
		self.numActivations = 0
		self.manaCost = None
		self.permDamBonus = None
		self.speedBonus = None
		self.maxActivations = None
		self.luckRemoval = None


	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.numActivations = 0


	def onPreDealDamage_early(self, damageRes):
		event = self.tryUseMana(self.manaCost)
		if event != None:
			self.addBonusDamage(self.permDamBonus)
			if self.numActivations < self.maxActivations:
				for item in _iter(self.getAffectedItems()):

					item.addSpeed(self.speedBonus)

				self.numActivations += 1

			if self.opponent().getLucky() > 0:
				self.removeLucky(self.luckRemoval)


	def _readyInit(self):
		super()._readyInit()
		self.manaCost = int(self.getP("manat"))
		self.permDamBonus = self.getP("dam")
		self.speedBonus = _div(self.getP('speed'), 100.0)
		self.maxActivations = int(self.getP("max"))
		self.luckRemoval = int(self.getP("luck"))


_R.reg("res://gd_core_items/Exclusive/JynxStaff.gd", Exclusive__JynxStaff)
_R.reg("JynxStaff", Exclusive__JynxStaff)
