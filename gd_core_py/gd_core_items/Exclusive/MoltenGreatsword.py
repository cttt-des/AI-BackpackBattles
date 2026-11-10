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
		type = int(type)
		if type == _H_1:
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


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Fire
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
