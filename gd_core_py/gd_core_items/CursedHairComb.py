# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CursedHairComb_2(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/CursedHairComb.gd"


	def canAffect(self, item):
		return item.canBeEmpowered()


	def canAffect_secondary(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		self.character().addHealingEfficiency(_div(self.getP3(), 100.0))


		for weapon in _iter(self.getAffectedItems()):
			self.connectForCombat(weapon, "attacked", "onAffectedAttacked")


	def onCombatStart(self):
		self.giveVampirism(self.getP1())
		self.activate()


	def onAffectedAttacked(self, damageRes):
		if damageRes.hasHit():
			bonusLifesteal = self.getNumAffectedItems(_H_2) * self.getP_m("lifesteal_scaling")
			self.heal(ceil(damageRes.damage * (self.getP_m("lifesteal") + bonusLifesteal) / 100.0), 
				damageRes.event)










	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/CursedHairComb.gd", CursedHairComb_2)
_R.reg("CursedHairComb", CursedHairComb_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Vampiric
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
