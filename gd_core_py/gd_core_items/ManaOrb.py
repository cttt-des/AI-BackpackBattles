# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class ManaOrb(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/ManaOrb.gd"

	def _init_fields(self):
		super()._init_fields()
		self.stackTypes = []
		self.activated = False
		self.bonusBuffs = 0
		self.mana = None
		self.manaNeeded = 0
		self.buffs = None
		self.light = None


	def canAffect(self, item):
		return item.canActivate()


	def onPrepare(self):
		self.bonusBuffs = 0
		self.setState(False)
		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "activated", "onItemActivated")
		self.connectForCombat(self.character(), "character_mana_changed", "onManaChanged")


	def onItemActivated(self, event):
		if self.rollChance():
			self.miniActivate()
			self.giveMana(self.mana)


	def onManaChanged(self, amount, triggerEvent):
		if not self.activated and amount > 0 and self.character().getMana() >= self.manaNeeded:
			self.setState(True)
			event = self.useMana(self.manaNeeded, triggerEvent)
			self.giveRandomBuffs(self.buffs + self.bonusBuffs, event, self.stackTypes)
			self.activate()



	def onShopEntered(self):
		self.onStateChanged(False)


	def addBonusRandomBuffs(self, amount):
		self.bonusBuffs += amount


	def onStateChanged(self, _activated):
		self.activated = _activated

	def _readyInit(self):
		super()._readyInit()
		self.mana = int(self.getP1())
		self.manaNeeded = self.getP2()
		self.buffs = int(self.getP3())
		self.stackTypes = _R.C("CoreConst").getBuffs()
		_erase(self.stackTypes, _R.C("CoreConst").EventType.Mana)



_R.reg("res://gd_core_items/ManaOrb.gd", ManaOrb)
_R.reg("ManaOrb", ManaOrb)
