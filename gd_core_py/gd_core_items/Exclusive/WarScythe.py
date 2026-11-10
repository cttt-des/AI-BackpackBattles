# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__WarScythe(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/WarScythe.gd"

	def _init_fields(self):
		super()._init_fields()
		self.poisonNeeded = None
		self.critDamage = None


	def canAffect(self, item):
		return item.gainsStack(_H_1)


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.giveBuffPower(_H_2, 1)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			if self.opponent().getPoison() >= self.poisonNeeded:
				self.opponent().losePoison(self.poisonNeeded, self)
				self.addCritChancePercent(self.getChance())
				self.addCritSeverity(self.critDamage)

	def _readyInit(self):
		super()._readyInit()
		self.poisonNeeded = int(self.getP("poisont"))
		self.critDamage = _div(self.getP('critdam'), 100.0)


_R.reg("res://gd_core_items/Exclusive/WarScythe.gd", Exclusive__WarScythe)
_R.reg("WarScythe", Exclusive__WarScythe)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Stack.Poison
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").EventType.Poison
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
