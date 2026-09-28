# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Markswoman(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Markswoman.gd"

	def _init_fields(self):
		super()._init_fields()
		self.rangedBonusDam = None
		self.rangedBonusSpeed = None
		self.rangedBonusAcc = None


	def canAffect(self, item):
		return item.descriptor.isRangedWeapon()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.addSpeed(self.rangedBonusSpeed)
			if item.canBeEmpowered():
				item.addBonusDamageFactor(self.rangedBonusDam)
				item.addAccuracy(self.rangedBonusAcc)

	def _readyInit(self):
		super()._readyInit()
		self.rangedBonusDam = _div(self.getP('dam'), 100.0)
		self.rangedBonusSpeed = _div(self.getP('speed'), 100.0)
		self.rangedBonusAcc = self.getP("acc")


_R.reg("res://gd_core_items/Exclusive/Markswoman.gd", Exclusive__Markswoman)
_R.reg("Markswoman", Exclusive__Markswoman)
