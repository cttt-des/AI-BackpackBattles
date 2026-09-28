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
		if self.useStamina() == _R.C("CoreConst").StaminaResult.Sufficient:
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
		return _R.C("CoreConst").Priority.High + 5

	def _readyInit(self):
		super()._readyInit()
		self.flatSpeed = _div(self.getP('speed'), 100)
		self.speedPerTile = _div(self.getP('speed2'), 100)


_R.reg("res://gd_core_items/Exclusive/Generator.gd", Exclusive__Generator)
_R.reg("Generator", Exclusive__Generator)
