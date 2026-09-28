# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__LightningStaff(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/LightningStaff.gd"

	def _init_fields(self):
		super()._init_fields()
		self.attackCounter = 0
		self.manaCost = None
		self.permDamBonus = None
		self.chargeDamBase = None
		self.chargeDamPerTile = None
		self.numAttacks = None

	chargeCells = [Vector2(0, - 2), Vector2(1, - 2), Vector2(2, - 1), Vector2(3, - 2), Vector2(4, - 1), Vector2(5, 0), Vector2(4, 1)]

	def onPrepare(self):
		self.attackCounter = 0


	def onPreDealDamage_early(self, damageRes):
		event = self.tryUseMana(self.manaCost)
		if event != None:
			self.addBonusDamage(self.permDamBonus)

		self.attackCounter += 1

		if self.attackCounter == self.numAttacks:
			self.emitCharge()
			self.ctx.bus.emitSignal(self, "charge_emitted", [self])
			self.attackCounter = 0


	def canAffect_lightning(self, item):
		return item.canBeEmpowered() or item.reactsToCharges()


	def emitCharge(self, speedFactor=1.0):
		event = self.activate(None, False)
		self.sendCharge(self.getP_m("dur"), self.chargeCells, speedFactor, event)


	def onChargeEnteredCell(self, charge, cellIndex):
		self.changeChargedItemStat(charge, cellIndex, self.chargeDamBase, self.chargeDamPerTile)


	def chargedItemStatChange(self, item, value):
		item.addBonusDamage(value, False)

	def _readyInit(self):
		super()._readyInit()
		self.manaCost = int(self.getP("manat"))
		self.permDamBonus = self.getP("dam")
		self.chargeDamBase = self.getP("dam_flat")
		self.chargeDamPerTile = self.getP("dam_tile")
		self.numAttacks = self.getP("num")


_R.reg("res://gd_core_items/Exclusive/LightningStaff.gd", Exclusive__LightningStaff)
_R.reg("LightningStaff", Exclusive__LightningStaff)
