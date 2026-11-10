# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__TimeMelting(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/TimeMelting.gd"

	def _init_fields(self):
		super()._init_fields()
		self.heat = None
		self.bonusdur = None


	def canAffect(self, item):
		return item.hasInventoryDuration()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.modifyParam("dur", self.bonusdur)


	def onCombatStart(self):
		self.giveHeat(self.heat)
		self.activate()


	def getTriggerPriority(self):
		return _H_1 + 100

	def _readyInit(self):
		super()._readyInit()
		self.heat = int(self.getP("heat"))
		self.bonusdur = _div(self.getP('bonusdur'), 100.0)


_R.reg("res://gd_core_items/Exclusive/TimeMelting.gd", Exclusive__TimeMelting)
_R.reg("TimeMelting", Exclusive__TimeMelting)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Priority.High
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
