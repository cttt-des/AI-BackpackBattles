# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__OnionCutter(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/OnionCutter.gd"

	def _init_fields(self):
		super()._init_fields()
		self.foodSpeed = None
		self.damFactor = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Food)


	def onPrepare(self):
		self.addSpeed(self.foodSpeed * self.getNumAffectedItems())


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.opponent().changeDamageResistance( - self.damFactor)

	def _readyInit(self):
		super()._readyInit()
		self.foodSpeed = _div(self.getP('speed'), 100.0)
		self.damFactor = self.getP("dam")


_R.reg("res://gd_core_items/Exclusive/OnionCutter.gd", Exclusive__OnionCutter)
_R.reg("OnionCutter", Exclusive__OnionCutter)
