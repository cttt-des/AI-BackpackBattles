# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class MagicTorch_2(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/MagicTorch.gd"

	def _init_fields(self):
		super()._init_fields()
		self._manaNeeded = 0
		self._damBonus = 0

	@property
	def manaNeeded(self):
		return self._manaNeeded
	@manaNeeded.setter
	def manaNeeded(self, v):
		self._manaNeeded = int(v)
	@property
	def damBonus(self):
		return self._damBonus
	@damBonus.setter
	def damBonus(self, v):
		self._damBonus = int(v)

	def canAffect(self, item):
		return item.canBeEmpowered()


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			event = self.tryUseMana(self.manaNeeded)
			if event != None:
				self.addBonusDamage(self.damBonus)
				for item in _iter(self.getAffectedItems()):
					item.addBonusDamage(self.damBonus)


	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = self.getP1()
		self.damBonus = self.getP2()


_R.reg("res://gd_core_items/MagicTorch.gd", MagicTorch_2)
_R.reg("MagicTorch", MagicTorch_2)
