# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class PiercingArrow(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core/PiercingArrow.gd"

	def _init_fields(self):
		super()._init_fields()
		self.critDam = None
		self.blockRemoval = None


	def canAffect(self, item):
		return item.canBeEmpowered()


	def canAffect_secondary(self, item):
		return item.canActivate()


	def onPrepare(self):
		_iter__loc = _iter
		for item in _iter__loc(self.getAffectedItems()):
			item.addCritSeverity(self.critDam)

			self.connectForCombat(item, "pre_deal_damage_late", "onItemAttacks")

		for item in _iter__loc(self.getAffectedItems(_H_1)):
			self.connectForCombat(item, "activated", "onItemActivated")


	def onItemAttacks(self, damageRes):
		if damageRes.wasCriticalHit():
			damageRes.damageSource.origin.removeBlock(self.blockRemoval)


	def onItemActivated(self, event):
		if self.rollChance():
			self.giveLucky(1)
			self.miniActivate()

	def _readyInit(self):
		super()._readyInit()
		self.critDam = _div(self.getP1(), 100.0)
		self.blockRemoval = int(self.getP2())


_R.reg("res://gd_core/PiercingArrow.gd", PiercingArrow)
_R.reg("PiercingArrow", PiercingArrow)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
