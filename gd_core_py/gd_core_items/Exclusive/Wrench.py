# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Wrench(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/Wrench.gd"


	def canAffect(self, item):
		return item.gainsBuffs()


	def canAffect_secondary(self, item):
		return item.canDamage()


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			item1 = self.getFirstAffectedItem(_H_1)
			if item1 != None:
				item1.changeAmplificiationChancePercent_allBuffs(self.getChance())

			item2 = self.getFirstAffectedItem(_H_2)
			if item2 != None:
				item2.changeCritChancePercent(self.getChance2())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/Wrench.gd", Exclusive__Wrench)
_R.reg("Wrench", Exclusive__Wrench)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Affected.Primary
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
