# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ManaCrystal(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ManaCrystal.gd"

	def _init_fields(self):
		super()._init_fields()
		self.mana1 = None
		self.mana2 = None

	chargeCells = [
		[Vector2(0, 0), Vector2( - 1, 0), Vector2( - 2, 0), Vector2( - 3, 0)], 
		[Vector2(0, 0), Vector2(0, - 1), Vector2(0, - 2)], 
		[Vector2(0, 0), Vector2(1, 0), Vector2(2, 0), Vector2(3, 0)], 
		[Vector2(0, 0), Vector2(0, 1), Vector2(0, 2)]
		]

	def canAffect_lightning(self, item):
		return True


	def doCooldownEffect(self):
		self.emitCharge()
		self.ctx.bus.emitSignal(self, "charge_emitted", [self])


	def emitCharge(self, speedFactor=1.0):
		event = self.activate()
		for i in _iter(len(self.chargeCells)):
			self.sendCharge(self.getP_m("dur"), self.chargeCells[i], speedFactor, event)


	def onChargeEnteredCell(self, charge, cellIndex):
		if (charge.curChargedItem != None and 
			charge.curChargedItem != charge.lastChargedItem):

			if charge.curChargedItem.hasType(_R.C("CoreConst").Type.Magic):
				self.giveMana(self.mana2)
			else:
				self.giveMana(self.mana1)


	def _readyInit(self):
		super()._readyInit()
		self.mana1 = int(self.getP("mana1"))
		self.mana2 = int(self.getP("mana2"))


_R.reg("res://gd_core_items/Exclusive/ManaCrystal.gd", Exclusive__ManaCrystal)
_R.reg("ManaCrystal", Exclusive__ManaCrystal)
