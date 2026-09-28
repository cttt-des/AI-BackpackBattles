# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Cube(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Cube.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedItem = None
		self.cdAdvance = None
		self.penaltyFactor = None


	def getDescription(self, wrapInColor=True):
		descr = self.descriptor.getDescription()
		descr += "\n\n" + self.ctx.util.tra("Cube_HINT")
		return self.insertParameters(descr, wrapInColor)


	def advanceAffectedItem(self):
		if not self.affectedItem in self.ctx.cube_advanced:
			self.ctx.cube_advanced[self.affectedItem] = self
			self.affectedItem.advanceCooldownSeconds(self.cdAdvance)
		else:
			self.affectedItem.advanceCooldownSeconds(self.cdAdvance * self.penaltyFactor)


	def _readyInit(self):
		super()._readyInit()
		self.cdAdvance = self.getP("cdadvance")
		self.penaltyFactor = 1.0 - _div(self.getP('penalty'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Cube.gd", Cube)
_R.reg("Cube", Cube)
_R.reg("Cube", Cube)
