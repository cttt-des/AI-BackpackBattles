# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ForestFriend(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ForestFriend.gd"


	def canAffect(self, item):
		return item.hasType(_H_1) or item.hasType(_H_2)


	def combatStart(self):
		super().combatStart()
		numAffected = self.getNumAffectedItems()
		if numAffected > 0:
			self.addSpeed(_div(numAffected * self.getP1(), 100.0))

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/ForestFriend.gd", Exclusive__ForestFriend)
_R.reg("ForestFriend", Exclusive__ForestFriend)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Type.Pet
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").Type.Food
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
