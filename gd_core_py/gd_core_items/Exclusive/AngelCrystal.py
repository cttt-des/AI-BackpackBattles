# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__AngelCrystal(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/AngelCrystal.gd"

	def _init_fields(self):
		super()._init_fields()
		self.regen = None
		self.regenPerHoly = None
		self.empower = None
		self.empowerPerHoly = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Holy)


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_regeneration_changed", "onRegenChanged")


	def onCombatStart(self):
		self.giveRegeneration(self.regen + self.regenPerHoly * self.getNumAffectedItems())
		self.activate()


	def doCooldownEffect(self):
		self.giveEmpower(self.empower + self.empowerPerHoly * self.getNumAffectedItems())
		self.onAfterEffectFinished()


	def onRegenChanged(self, amount, event):
		if amount > 0:
			self.giveMaxHealth(self.getP_m("maxhealth") * amount, event)
			self.miniActivate()

	def _readyInit(self):
		super()._readyInit()
		self.regen = int(self.getP("regen"))
		self.regenPerHoly = int(self.getP("regen_holy"))
		self.empower = int(self.getP("empower"))
		self.empowerPerHoly = int(self.getP("empower_holy"))


_R.reg("res://gd_core_items/Exclusive/AngelCrystal.gd", Exclusive__AngelCrystal)
_R.reg("AngelCrystal", Exclusive__AngelCrystal)
