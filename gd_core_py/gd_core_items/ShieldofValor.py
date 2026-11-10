# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class ShieldofValor_2(_R.C("res://gd_core_items/Shield.gd")):

	resource_path = "res://gd_core_items/ShieldofValor.gd"

	def _init_fields(self):
		super()._init_fields()
		self.blockFactor = None


	def canAffect(self, item):
		return item.canBlock()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.giveBuffPower(_H_1, self.blockFactor)


	def afterBlock(self):
		self.drainStamina(self.getP2(), self.blockedDamageRes.event)
		self.activate()


	def _readyInit(self):
		super()._readyInit()
		self.blockFactor = _div(self.getP3(), 100.0)


_R.reg("res://gd_core_items/ShieldofValor.gd", ShieldofValor_2)
_R.reg("ShieldofValor", ShieldofValor_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").EventType.Block
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
