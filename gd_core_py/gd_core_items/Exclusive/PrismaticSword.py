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

		if self.affectedTypes[_R.C("CoreConst").Type.Magic] > 0:
			self.addSpeed(_div(self.affectedTypes[_R.C('CoreConst').Type.Magic] * self.getP('speed'), 100.0))


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.addBonusDamage(self.holyDam * self.affectedTypes[_R.C("CoreConst").Type.Holy])
			if self.rollChance(self.getBaseChance2() * self.affectedTypes[_R.C("CoreConst").Type.Dark]):
				self.inflictRandomDebuffs(self.debuffs)


	def onPreDealDamage_late(self, damageRes):
		self.heal(ceil(_div(damageRes.damage * self.getP_m('lifesteal'), 100.0) * self.affectedTypes[_R.C('CoreConst').Type.Vampiric]))


	def canAffect(self, item):
		return (item.hasType(_R.C("CoreConst").Type.Vampiric) or 
				item.hasType(_R.C("CoreConst").Type.Magic) or 
				item.hasType(_R.C("CoreConst").Type.Holy) or 
				item.hasType(_R.C("CoreConst").Type.Dark))


	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		if not self.placed:
			descr = descr.replace("$n_magic", "")
			descr = descr.replace("$n_vampiric", "")
			descr = descr.replace("$n_holy", "")
			descr = descr.replace("$n_dark", "")
			return descr

		typesDict = self.countTypes(self.getAffectedItems())
		descr = self.insertCounter(descr, "n_magic", typesDict[_R.C("CoreConst").Type.Magic])
		descr = self.insertCounter(descr, "n_vampiric", typesDict[_R.C("CoreConst").Type.Vampiric])
		descr = self.insertCounter(descr, "n_holy", typesDict[_R.C("CoreConst").Type.Holy])
		descr = self.insertCounter(descr, "n_dark", typesDict[_R.C("CoreConst").Type.Dark])

		return descr


	def _readyInit(self):
		super()._readyInit()
		self.holyDam = self.getP("dam")
		self.debuffs = self.getP("debuffs")


_R.reg("res://gd_core_items/Exclusive/PrismaticSword.gd", Exclusive__PrismaticSword)
_R.reg("PrismaticSword", Exclusive__PrismaticSword)
