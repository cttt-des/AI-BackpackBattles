# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Generator(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Generator.gd"

	def _init_fields(self):
		super()._init_fields()
		self.flatSpeed = None
		self.speedPerTile = None

	chargeCells = [Vector2( - 1, - 1), Vector2( - 1, - 2),
		Vector2( - 2, - 3), Vector2( - 2, - 4), Vector2( - 1, - 5), Vector2(0, - 5)]

	def canAffect_lightning(self, item):
		return item.hasCooldown() or item.reactsToCharges()


	def onCombatStart(self):
		self.emitCharge()
		self.ctx.bus.emitSignal(self, "charge_emitted", [self])


	def doCooldownEffect(self):
		if self.useStamina() == _H_1:
			self.emitCharge()
			self.ctx.bus.emitSignal(self, "charge_emitted", [self])


	def emitCharge(self, speedFactor=1.0):
		event = self.activate()
		self.sendCharge(self.getP_m("dur"), self.chargeCells, speedFactor, event)


	def onChargeEnteredCell(self, charge, cellIndex):
		self.changeChargedItemStat(charge, cellIndex, self.flatSpeed, self.speedPerTile)


	def chargedItemStatChange(self, item, value):
		item.addSpeed(value)


	def getTriggerPriority(self):
		return _H_2 + 5

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.flatSpeed = _div__loc(self.getP('speed'), 100)
		self.speedPerTile = _div__loc(self.getP('speed2'), 100)


_R.reg("res://gd_core_items/Exclusive/Generator.gd", Exclusive__Generator)
_R.reg("Generator", Exclusive__Generator)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").StaminaResult.Sufficient
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").Priority.High
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
