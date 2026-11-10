# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Snowmaster(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Snowmaster.gd"

	def _init_fields(self):
		super()._init_fields()
		self.iceSpeed = None
		self.cold = None
		self.empower = None
		self.coldNeeded = None


	def canAffect(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		self.addSpeed(self.getNumAffectedItems() * self.iceSpeed)


	def doCooldownEffect(self):
		if self.opponent().getCold() >= self.coldNeeded:
			self.giveEmpower(self.empower)
		else:
			self.inflictCold(self.cold)

		self.cleanseRandomDebuffs(1)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.iceSpeed = _div(self.getP('speed'), 100.0)
		self.cold = int(self.getP("cold"))
		self.empower = int(self.getP("empower"))
		self.coldNeeded = int(self.getP("coldt"))


_R.reg("res://gd_core_items/Exclusive/Snowmaster.gd", Exclusive__Snowmaster)
_R.reg("Snowmaster", Exclusive__Snowmaster)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Ice
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
