# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ShinyShell(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ShinyShell.gd"


	def canAffect(self, item):
		return item.hasType(_H_1)


	def doCooldownEffect(self):
		healAmount = self.getP_m("heal") + self.getNumAffectedItems() * self.getP_m("heal_bonus")
		self.heal(healAmount)
		self.onAfterEffectFinished()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/ShinyShell.gd", Exclusive__ShinyShell)
_R.reg("ShinyShell", Exclusive__ShinyShell)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Holy
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
