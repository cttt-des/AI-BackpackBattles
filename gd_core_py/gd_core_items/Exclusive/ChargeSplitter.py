# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ChargeSplitter(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ChargeSplitter.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False
		self.heatNeeded = None
		self.luck = None

	chargeCells1 = [Vector2( - 1, - 1), Vector2( - 2, - 1), Vector2( - 2, 0), Vector2( - 2, 1), Vector2( - 3, 1), Vector2( - 4, 1), Vector2( - 4, 0)]
	chargeCells2 = [Vector2( - 1, - 1), Vector2(0, - 1), Vector2(0, - 2), Vector2(0, - 3), Vector2(1, - 3), Vector2(2, - 3), Vector2(2, - 2)]

	def onPrepare(self):
		self.hasActivated = False


	def doCooldownEffect(self):
		if self.character().getHeat() >= self.heatNeeded:
			event = self.useHeat(self.heatNeeded)
			self.giveLucky(self.luck, event)
			self.giveBlock(self.getBlock(), True, event)

		self.onAfterEffectFinished()


	def canAffect_lightning(self, item):
		return item.gainsBuffs() or item.reactsToCharges()


	def onChargeReceived(self, _charge):
		if not self.hasActivated:
			self.hasActivated = True
			self.emitCharge()
			self.ctx.bus.emitSignal(self, "charge_emitted", [self])


	def emitCharge(self, speedFactor=1.0):
		event = self.activate()
		self.sendCharge(self.getP_m("dur"), self.chargeCells1, speedFactor, event)
		self.sendCharge(self.getP_m("dur"), self.chargeCells2, speedFactor, event)



	def onChargeEnteredCell(self, charge, cellIndex):
		self.changeChargedItemStat(charge, cellIndex, self.getChance(), self.getChance2())


	def chargedItemStatChange(self, item, value):
		item.changeAmplificiationChancePercent_allBuffs(value)

	def _readyInit(self):
		super()._readyInit()
		self.heatNeeded = int(self.getP("heatt"))
		self.luck = int(self.getP("luck"))


_R.reg("res://gd_core_items/Exclusive/ChargeSplitter.gd", Exclusive__ChargeSplitter)
_R.reg("ChargeSplitter", Exclusive__ChargeSplitter)
