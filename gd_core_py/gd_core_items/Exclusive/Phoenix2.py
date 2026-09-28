# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Phoenix2(_R.C("res://gd_core_items/Exclusive/Phoenix.gd")):

	resource_path = "res://gd_core_items/Exclusive/Phoenix2.gd"

	def _init_fields(self):
		super()._init_fields()
		self.fireMultiplicity = None


	def getTypeMultiplicity(self, type):
		if type == _R.C("CoreConst").Type.Fire:
			return self.fireMultiplicity
		else:
			return super().getTypeMultiplicity(type)


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Fire)


	def onPrepare(self):
		super().onPrepare()
		self.addCritChancePercent(self.getChance() * self.getNumAffected_type(_R.C("CoreConst").Type.Fire))

	def _readyInit(self):
		super()._readyInit()
		self.fireMultiplicity = int(self.getP("fire"))


_R.reg("res://gd_core_items/Exclusive/Phoenix2.gd", Exclusive__Phoenix2)
_R.reg("Phoenix2", Exclusive__Phoenix2)
