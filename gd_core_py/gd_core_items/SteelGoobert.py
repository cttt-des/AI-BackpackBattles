# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class SteelGoobert_2(_R.C("res://gd_core_items/Goobert.gd")):

	resource_path = "res://gd_core_items/SteelGoobert.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedWeapons = []


	def canAffect_secondary(self, item):
		return item.canBeEmpowered()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems(_H_1)):
			self.affectedWeapons.append(item)


	def doCooldownEffect(self):
		for item in _iter(self.affectedWeapons):
			item.addBonusDamage(self.getP2())
		self.giveBlock()


	def onCombatEnd(self):
		self.affectedWeapons.clear()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/SteelGoobert.gd", SteelGoobert_2)
_R.reg("SteelGoobert", SteelGoobert_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
