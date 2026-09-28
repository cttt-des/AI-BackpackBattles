# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MoltenSpear(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/MoltenSpear.gd"

	def _init_fields(self):
		super()._init_fields()
		self.totalBlockRemoval = 0
		self.blockRemoval = None
		self.missDamage = None
		self.heatNeeded = None


	def affectsEmpty(self, color):
		return True


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Fire)


	def onPrepare(self):
		self.totalBlockRemoval = self.blockRemoval * (self.getNumAffected_type(_R.C("CoreConst").Type.Fire)
			+ self.getNumEmptyAffectedCells())


	def onPreDealDamage_early(self, damageRes):
		if not damageRes.hasHit():
			if self.character().getHeat() >= self.heatNeeded:
				damageRes.damage += self.missDamage
				damageRes.hit = True
				self.useHeat(self.heatNeeded)


	def onPreDealDamage_late(self, damageRes):
		self.removeBlock(self.totalBlockRemoval)

	def _readyInit(self):
		super()._readyInit()
		self.blockRemoval = self.getP("blockremoval")
		self.missDamage = int(self.getP("missdam"))
		self.heatNeeded = int(self.getP("heatt"))


_R.reg("res://gd_core_items/Exclusive/MoltenSpear.gd", Exclusive__MoltenSpear)
_R.reg("MoltenSpear", Exclusive__MoltenSpear)
