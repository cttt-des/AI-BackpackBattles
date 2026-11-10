# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ShepherdsCrook(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ShepherdsCrook.gd"


	def canAffect(self, item):
		return item.canBeEmpowered()


	def onPrepare(self):
		self.character().changeBuffProtectionChance(self.getChance())
		self.character().changeResistChance(_H_1, self.getChance2())
		self.character().changeResistChance(_H_2, self.getChance2())


	def onCombatStart(self):
		for item in _iter(self.getAffectedItems()):
			item.addBonusDamage(self.getP1())
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/ShepherdsCrook.gd", Exclusive__ShepherdsCrook)
_R.reg("ShepherdsCrook", Exclusive__ShepherdsCrook)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").EventType.Blind
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").EventType.Cold
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
