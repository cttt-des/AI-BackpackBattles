# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Ultima(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Ultima.gd"

	def _init_fields(self):
		super()._init_fields()
		self.typesDict = None
		self.speedPerSpell = None


	def canAffect(self, item):
		return (item.hasType(_R.C("CoreConst").Type.Nature) or 
				item.hasType(_R.C("CoreConst").Type.Ice) or 
				item.hasType(_R.C("CoreConst").Type.Holy) or 
				item.hasType(_R.C("CoreConst").Type.Dark) or 
				item.hasType(_R.C("CoreConst").Type.Spell))


	def onPrepare(self):
		self.typesDict = self.countTypes(self.getAffectedItems())

		if self.typesDict[_R.C("CoreConst").Type.Spell] > 0:
			self.addSpeed(self.speedPerSpell * self.typesDict[_R.C("CoreConst").Type.Spell])


	def doCooldownEffect(self):

		if self.typesDict[_R.C("CoreConst").Type.Nature] > 0:
			self.giveLucky(self.typesDict[_R.C("CoreConst").Type.Nature] * self.getP("luck"))
			self.giveSpikes(self.typesDict[_R.C("CoreConst").Type.Nature] * self.getP("spikes"))

		if self.typesDict[_R.C("CoreConst").Type.Ice] > 0:
			self.giveBlock(self.typesDict[_R.C("CoreConst").Type.Ice] * self.getBlock())
			self.inflictCold(self.typesDict[_R.C("CoreConst").Type.Ice] * self.getP("cold"))

		if self.typesDict[_R.C("CoreConst").Type.Holy] > 0:
			self.giveRegeneration(self.typesDict[_R.C("CoreConst").Type.Holy] * self.getP("regen"))

		if self.typesDict[_R.C("CoreConst").Type.Dark] > 0:
			self.stealRandomBuff(self.typesDict[_R.C("CoreConst").Type.Dark])

		self.onAfterEffectFinished()


	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		if not self.placed:
			descr = descr.replace("$n_nature", "")
			descr = descr.replace("$n_ice", "")
			descr = descr.replace("$n_holy", "")
			descr = descr.replace("$n_dark", "")

			return descr

		self.typesDict = self.countTypes(self.getAffectedItems())

		descr = self.insertCounter(descr, "n_nature", self.typesDict[_R.C("CoreConst").Type.Nature])
		descr = self.insertCounter(descr, "n_ice", self.typesDict[_R.C("CoreConst").Type.Ice])
		descr = self.insertCounter(descr, "n_holy", self.typesDict[_R.C("CoreConst").Type.Holy])
		descr = self.insertCounter(descr, "n_dark", self.typesDict[_R.C("CoreConst").Type.Dark])


		return descr

	def _readyInit(self):
		super()._readyInit()
		self.speedPerSpell = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Ultima.gd", Exclusive__Ultima)
_R.reg("Ultima", Exclusive__Ultima)
