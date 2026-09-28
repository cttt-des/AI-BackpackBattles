# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__RainbowOrb(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/RainbowOrb.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffs = None


	def canAffect(self, item):

		return (item.hasType(_R.C("CoreConst").Type.Vampiric) or 
				item.hasType(_R.C("CoreConst").Type.Magic) or 
				item.hasType(_R.C("CoreConst").Type.Holy) or 
				item.hasType(_R.C("CoreConst").Type.Dark))


	def onCombatStart(self):
		typesDict = self.countTypes(self.getAffectedItems())

		if typesDict[_R.C("CoreConst").Type.Vampiric] > 0:
			self.giveVampirism(typesDict[_R.C("CoreConst").Type.Vampiric] * self.getP("vampirism"))

		if typesDict[_R.C("CoreConst").Type.Magic] > 0:
			self.giveMana(typesDict[_R.C("CoreConst").Type.Magic] * self.getP("mana"))

		if typesDict[_R.C("CoreConst").Type.Holy] > 0:
			self.character().addHealingEfficiency(_div(typesDict[_R.C('CoreConst').Type.Holy] * self.getP('healamp'), 100.0))

		if typesDict[_R.C("CoreConst").Type.Dark] > 0:
			self.inflictRandomDebuffs(typesDict[_R.C("CoreConst").Type.Dark] * self.getP("debuffs"))

		self.activate()


	def doCooldownEffect(self):
		self.giveAllBuffs()
		self.activate()


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
		self.buffs = self.getP("buffs")


_R.reg("res://gd_core_items/Exclusive/RainbowOrb.gd", Exclusive__RainbowOrb)
_R.reg("RainbowOrb", Exclusive__RainbowOrb)
