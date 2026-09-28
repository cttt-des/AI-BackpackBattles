# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MoltenGreatsword(_R.C("res://gd_core_items/Greatsword.gd")):

	resource_path = "res://gd_core_items/Exclusive/MoltenGreatsword.gd"

	def _init_fields(self):
		super()._init_fields()
		self.fireMultiplicity = None
		self.heatNeeded = None
		self.empower = None


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			if self.character().getHeat() >= self.heatNeeded:
				event = self.useHeat(self.heatNeeded)
				self.giveEmpower(self.empower, event)





	def getTypeMultiplicity(self, type):
		if type == _R.C("CoreConst").Type.Fire:
			return self.fireMultiplicity
		else:
			return super().getTypeMultiplicity(type)

	def _readyInit(self):
		super()._readyInit()
		self.fireMultiplicity = int(self.getP("fire"))
		self.heatNeeded = int(self.getP("heat"))
		self.empower = int(self.getP("empower"))


_R.reg("res://gd_core_items/Exclusive/MoltenGreatsword.gd", Exclusive__MoltenGreatsword)
_R.reg("MoltenGreatsword", Exclusive__MoltenGreatsword)
