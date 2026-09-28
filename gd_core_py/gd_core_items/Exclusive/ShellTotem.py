# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ShellTotem(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ShellTotem.gd"

	def _init_fields(self):
		super()._init_fields()
		self.healthThreshold = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Holy)


	def onPrepare(self):
		self.changeStaminaFactor( - self.getP("stamina") * self.getNumAffectedItems())


	def doCooldownEffect(self):
		if self.useStamina() == _R.C("CoreConst").StaminaResult.Sufficient:
			if self.character().getRelativeHealth() > self.healthThreshold:
				self.giveEmpower(1)
			else:
				self.heal()
			self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP('healtht'), 100.0)


_R.reg("res://gd_core_items/Exclusive/ShellTotem.gd", Exclusive__ShellTotem)
_R.reg("ShellTotem", Exclusive__ShellTotem)
