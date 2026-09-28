# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MoltenSpear2(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/MoltenSpear2.gd"

	def _init_fields(self):
		super()._init_fields()
		self.totalBlockRemoval = 0
		self.blockRemoval = None
		self.heatNeeded = None
		self.missDamage = None
		self.blind = None
		self.selfblind = None
		self.fireMultiplicity = None


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
				self.addBonusDamage(self.missDamage)
				damageRes.hit = True
				self.useHeat(self.heatNeeded)

		if damageRes.hasHit():
			self.inflictBlind(self.blind)
			self.selfInflictBlind(self.selfblind)


	def onPreDealDamage_late(self, damageRes):
		self.removeBlock(self.totalBlockRemoval)


	def getTypeMultiplicity(self, type):
		if type == _R.C("CoreConst").Type.Fire:
			return self.fireMultiplicity
		else:
			return super().getTypeMultiplicity(type)

	def _readyInit(self):
		super()._readyInit()
		self.blockRemoval = self.getP("blockremoval")
		self.heatNeeded = int(self.getP("heatt"))
		self.missDamage = int(self.getP("missdam"))
		self.blind = int(self.getP("blind"))
		self.selfblind = int(self.getP("blind_self"))
		self.fireMultiplicity = int(self.getP("fire"))


_R.reg("res://gd_core_items/Exclusive/MoltenSpear2.gd", Exclusive__MoltenSpear2)
_R.reg("MoltenSpear2", Exclusive__MoltenSpear2)
