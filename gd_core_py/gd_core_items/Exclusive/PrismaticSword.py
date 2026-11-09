# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PrismaticSword(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/PrismaticSword.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedTypes = {}
		self.holyDam = None
		self.debuffs = None


	def onPrepare(self):
		self.affectedTypes = self.countTypes(self.getAffectedItems())

		if self.affectedTypes[_H_1] > 0:
			self.addSpeed(_div(self.affectedTypes[_H_6] * self.getP('speed'), 100.0))


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.addBonusDamage(self.holyDam * self.affectedTypes[_H_3])
			if self.rollChance(self.getBaseChance2() * self.affectedTypes[_H_4]):
				self.inflictRandomDebuffs(self.debuffs)


	def onPreDealDamage_late(self, damageRes):
		self.heal(ceil(_div(damageRes.damage * self.getP_m('lifesteal'), 100.0) * self.affectedTypes[_H_5]))


	def canAffect(self, item):
		return (item.hasType(_H_2) or 
				item.hasType(_H_1) or 
				item.hasType(_H_3) or 
				item.hasType(_H_4))


	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		if not self.placed:
			descr = descr.replace("$n_magic", "")
			descr = descr.replace("$n_vampiric", "")
			descr = descr.replace("$n_holy", "")
			descr = descr.replace("$n_dark", "")
			return descr

		typesDict = self.countTypes(self.getAffectedItems())
		descr = self.insertCounter(descr, "n_magic", typesDict[_H_1])
		descr = self.insertCounter(descr, "n_vampiric", typesDict[_H_2])
		descr = self.insertCounter(descr, "n_holy", typesDict[_H_3])
		descr = self.insertCounter(descr, "n_dark", typesDict[_H_4])

		return descr


	def _readyInit(self):
		super()._readyInit()
		self.holyDam = self.getP("dam")
		self.debuffs = self.getP("debuffs")


_R.reg("res://gd_core_items/Exclusive/PrismaticSword.gd", Exclusive__PrismaticSword)
_R.reg("PrismaticSword", Exclusive__PrismaticSword)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Type.Magic
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").Type.Vampiric
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
try:
    _H_3 = _R.C("CoreConst").Type.Holy
except AttributeError as _he:
    _H_3 = _HoistPending(_he)
try:
    _H_4 = _R.C("CoreConst").Type.Dark
except AttributeError as _he:
    _H_4 = _HoistPending(_he)
try:
    _H_5 = _R.C('CoreConst').Type.Vampiric
except AttributeError as _he:
    _H_5 = _HoistPending(_he)
try:
    _H_6 = _R.C('CoreConst').Type.Magic
except AttributeError as _he:
    _H_6 = _HoistPending(_he)
