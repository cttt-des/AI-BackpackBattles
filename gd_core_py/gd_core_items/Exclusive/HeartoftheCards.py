# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__HeartoftheCards(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/HeartoftheCards.gd"

	def _init_fields(self):
		super()._init_fields()
		self.regen = None
		self.mana = None
		self.chainPosition = None


	def onPrepare(self):
		for item in _iter(self.inventory.getItems()):
			if item.hasType(_R.C("CoreConst").Type.Card):
				self.connectForCombat(item, "activated", "onCardRevealed")


	def onCardRevealed(self, event):
		card = event.getOrigin()
		self.giveRegeneration(self.regen, event)
		if card.chainPosition + 1 >= self.chainPosition:
			self.giveMana(self.mana, event)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.regen = int(self.getP("regen"))
		self.mana = int(self.getP("mana"))
		self.chainPosition = int(self.getP("pos"))


_R.reg("res://gd_core_items/Exclusive/HeartoftheCards.gd", Exclusive__HeartoftheCards)
_R.reg("HeartoftheCards", Exclusive__HeartoftheCards)
