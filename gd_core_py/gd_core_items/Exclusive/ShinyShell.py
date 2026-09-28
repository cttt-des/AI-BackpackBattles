# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ShinyShell(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ShinyShell.gd"


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Holy)


	def doCooldownEffect(self):
		healAmount = self.getP_m("heal") + self.getNumAffectedItems() * self.getP_m("heal_bonus")
		self.heal(healAmount)
		self.onAfterEffectFinished()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/ShinyShell.gd", Exclusive__ShinyShell)
_R.reg("ShinyShell", Exclusive__ShinyShell)
