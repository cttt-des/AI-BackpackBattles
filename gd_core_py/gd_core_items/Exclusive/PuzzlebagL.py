# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PuzzlebagL(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/PuzzlebagL.gd"

	def _init_fields(self):
		super()._init_fields()
		self.healamp = None


	def canApplyEffect(self, toItem):
		return toItem.canHealOrLifesteal()


	def onPrepare(self):
		for item in _iter(self.getAffectedItemsInside()):
			item.changeHealAmp(self.healamp)


	def onCombatStart(self):
		self.giveMaxHealth()
		self.activate()


	def getBagEffect(self, number):
		descr = self.ctx.util.tra(self.getName() + "_BAGEFFECT")
		descr = self.insertParameter(descr, "p_healamp", self.getP("healamp") * number)
		return descr

	def _readyInit(self):
		super()._readyInit()
		self.healamp = _div(self.getP('healamp'), 100.0)


_R.reg("res://gd_core_items/Exclusive/PuzzlebagL.gd", Exclusive__PuzzlebagL)
_R.reg("PuzzlebagL", Exclusive__PuzzlebagL)
