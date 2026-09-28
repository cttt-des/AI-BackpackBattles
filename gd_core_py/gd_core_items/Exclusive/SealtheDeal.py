# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SealtheDeal(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SealtheDeal.gd"

	def _init_fields(self):
		super()._init_fields()
		self.regenNeeded = None
		self.vampirism = None
		self.luckNeeded = None
		self.spikes = None
		self.manaNeeded = None
		self.empower = None
		self.tradeBonusValue = None


	def onCalcTradeChance(self):
		pass

	def doCooldownEffect(self):

		if self.character().getRegeneration() >= self.regenNeeded:
			event = self.useRegeneration(self.regenNeeded)
			self.giveVampirism(self.vampirism, event)

		if self.character().getLucky() >= self.luckNeeded:
			event = self.useLucky(self.luckNeeded)
			self.giveSpikes(self.spikes, event)

		if self.character().getMana() >= self.manaNeeded:
			event = self.useMana(self.manaNeeded)
			self.giveEmpower(self.empower, event)


		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.regenNeeded = int(self.getP("regent"))
		self.vampirism = int(self.getP("vamp"))
		self.luckNeeded = int(self.getP("luckt"))
		self.spikes = int(self.getP("spikes"))
		self.manaNeeded = int(self.getP("manat"))
		self.empower = int(self.getP("empower"))
		self.tradeBonusValue = int(self.getP("gold"))


_R.reg("res://gd_core_items/Exclusive/SealtheDeal.gd", Exclusive__SealtheDeal)
_R.reg("SealtheDeal", Exclusive__SealtheDeal)
