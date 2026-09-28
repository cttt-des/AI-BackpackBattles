# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class RibSawBlade(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/RibSawBlade.gd"

	def _init_fields(self):
		super()._init_fields()
		self.opponentWeapons = []
		self.removeDam = None
		self.bonusDam = None


	def onPrepare(self):
		self.opponentWeapons.clear()
		for item in _iter(self.opponent().INVENTORY.getItems()):
			if item.canBeEmpowered():
				self.opponentWeapons.append(item)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			for weapon in _iter(self.opponentWeapons):
				weapon.purgeDamage(self.removeDam)
			self.addBonusDamage(self.bonusDam)

	def _readyInit(self):
		super()._readyInit()
		self.removeDam = self.getP("dam")
		self.bonusDam = self.getP("bonusdam")


_R.reg("res://gd_core_items/RibSawBlade.gd", RibSawBlade)
_R.reg("RibSawBlade", RibSawBlade)
