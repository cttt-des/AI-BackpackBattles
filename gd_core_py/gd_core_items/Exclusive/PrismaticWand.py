# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PrismaticWand(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/PrismaticWand.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffs = None
		self.manaNeeded = None
		self.luckNeeded = None
		self.regenNeeded = None
		self.empower = None
		self.buffsToUse = None


	def doCooldownEffect(self):
		self.giveAllBuffs()

		mana = self.character().getMana()
		luck = self.character().getLucky()
		regen = self.character().getRegeneration()

		if (mana >= self.manaNeeded or 
			luck >= self.luckNeeded or 
			regen >= self.regenNeeded):

				event = self.removeMostBuffs(self.buffsToUse, None, True, self.buffs)
				self.giveEmpower(self.empower, event)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.buffs = [_R.C("CoreConst").EventType.Mana, _R.C("CoreConst").EventType.Lucky, _R.C("CoreConst").EventType.Regeneration]
		self.manaNeeded = int(self.getP("manat"))
		self.luckNeeded = int(self.getP("luckt"))
		self.regenNeeded = int(self.getP("regent"))
		self.empower = int(self.getP("empower"))
		self.buffsToUse = int(self.getP("use"))


_R.reg("res://gd_core_items/Exclusive/PrismaticWand.gd", Exclusive__PrismaticWand)
_R.reg("PrismaticWand", Exclusive__PrismaticWand)
