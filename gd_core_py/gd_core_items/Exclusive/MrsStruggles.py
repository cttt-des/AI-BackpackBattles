# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MrsStruggles(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/MrsStruggles.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activationParticles = None


	def canAffect(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		self.addSpeed(_div(self.getNumAffectedItems() * self.getP1(), 100.0))


	def doCooldownEffect(self):
		for buff in _iter(_H_2.getBuffs()):
			self.opponent().loseStacks(buff, 1, self)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/MrsStruggles.gd", Exclusive__MrsStruggles)
_R.reg("MrsStruggles", Exclusive__MrsStruggles)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Dark
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
_H_2 = _R.C("CoreConst")
