# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PuzzlebagJ(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/PuzzlebagJ.gd"

	def _init_fields(self):
		super()._init_fields()
		self.bonusdur = None


	def canApplyEffect(self, toItem):
		return toItem.hasInventoryDuration()


	def onPrepare(self):
		for item in _iter(self.getAffectedItemsInside()):
			item.modifyParam("dur", self.bonusdur)


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High + 100


	def getBagEffect(self, number):
		descr = self.ctx.util.tra(self.getName() + "_BAGEFFECT")
		descr = self.insertParameter(descr, "p_bonusdur", self.getP("bonusdur") * number)
		return descr

	def _readyInit(self):
		super()._readyInit()
		self.bonusdur = _div(self.getP('bonusdur'), 100.0)


_R.reg("res://gd_core_items/Exclusive/PuzzlebagJ.gd", Exclusive__PuzzlebagJ)
_R.reg("PuzzlebagJ", Exclusive__PuzzlebagJ)
