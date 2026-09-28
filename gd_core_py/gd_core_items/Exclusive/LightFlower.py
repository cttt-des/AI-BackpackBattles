# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__LightFlower(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core_items/Exclusive/LightFlower.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaNeeded = None
		self.debuffs = None
		self.regen = None
		self.luck = None


	def canAffect_secondary(self, item):
		return item.hasType(_R.C("CoreConst").Type.Holy)


	def onPrepare(self):
		self.character().changeBuffProtectionChance(self.getChance() + 
			self.getChance2() * self.getNumAffectedItems(_R.C("CoreConst").Affected.Secondary))


	def doCooldownEffect(self):
		if self.character().getMana() >= self.manaNeeded:
			event = self.useMana(self.manaNeeded)
			self.cleanseRandomDebuffs(self.debuffs, event)
			if self.character().getDebuffStacks() == 0:
				self.giveRegeneration(self.regen)
				self.giveLucky(self.luck)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP("manat"))
		self.debuffs = int(self.getP("debuffs"))
		self.regen = int(self.getP("regen"))
		self.luck = int(self.getP("luck"))


_R.reg("res://gd_core_items/Exclusive/LightFlower.gd", Exclusive__LightFlower)
_R.reg("LightFlower", Exclusive__LightFlower)
