# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ArmoredPowerPuppy(_R.C("res://gd_core_items/Exclusive/PowerPuppy.gd")):

	resource_path = "res://gd_core_items/Exclusive/ArmoredPowerPuppy.gd"


	def canAffect(self, item):
		return item.hasType(_H_1) or item.hasType(_H_2)


	def onPrepare(self):
		numFood = 0
		numPets = 0
		for item in _iter(self.getAffectedItems()):
			if item.hasType(_H_1):
				numFood += 1
			elif item.hasType(_H_2):
				numPets += 1

		self.addSpeed(_div(numPets * self.getP4() + numFood * self.getP5(), 100.0))
		self.options = [0, 1, 2]

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/ArmoredPowerPuppy.gd", Exclusive__ArmoredPowerPuppy)
_R.reg("ArmoredPowerPuppy", Exclusive__ArmoredPowerPuppy)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Type.Food
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").Type.Pet
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
