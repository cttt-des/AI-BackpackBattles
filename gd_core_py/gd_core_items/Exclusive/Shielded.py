# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Shielded(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Shielded.gd"

	def _init_fields(self):
		super()._init_fields()
		self.boostedShields = 0
		self.shieldOfValorDescriptor = None
		self.shieldChance = None
		self.armorSpeed = None


	def getData(self):
		return self.boostedShields


	def setData(self, data):
		if data != None:
			self.boostedShields = data


	def onBought(self):
		self.boostedShields = 1


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Shield) or (item.hasType(_R.C("CoreConst").Type.Armor) and item.hasCooldown())


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):

			if item.hasType(_R.C("CoreConst").Type.Shield):
				item.addBonusChance_additive(self.shieldChance, 0)

			else:
				item.addSpeed(self.armorSpeed)


	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.shieldOfValorDescriptor:
			self.boostedShields -= 1

	def _readyInit(self):
		super()._readyInit()
		self.shieldOfValorDescriptor = self.ctx.item_book.getDescriptor("Shield of Valor")
		self.shieldChance = self.getP("chance")
		self.armorSpeed = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Shielded.gd", Exclusive__Shielded)
_R.reg("Shielded", Exclusive__Shielded)
