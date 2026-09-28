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
		return item.hasType(_R.C("CoreConst").Type.Dark)


	def onPrepare(self):
		self.addSpeed(_div(self.getNumAffectedItems() * self.getP1(), 100.0))


	def doCooldownEffect(self):
		for buff in _iter(_R.C("CoreConst").getBuffs()):
			self.opponent().loseStacks(buff, 1, self)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/MrsStruggles.gd", Exclusive__MrsStruggles)
_R.reg("MrsStruggles", Exclusive__MrsStruggles)
