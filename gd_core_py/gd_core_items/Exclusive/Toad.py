# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Toad(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Toad.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedItemsDict = {}
		self.gainedBuffs = 0
		self.usedBuffs = 0
		self.gainedThreshold = None
		self.usedThreshold = None
		self.luck = None
		self.mana = None
		self.luck2 = None
		self.mana2 = None


	def canAffect(self, item):
		return item.gainsBuffs() or item.usesBuffs()


	def onPrepare(self):
		self.affectedItemsDict = self.ctx.util.arrayAsIndexDict(self.getAffectedItems())
		self.connectToCharacterBuffs("onBuffsChanged")
		self.gainedBuffs = 0
		self.usedBuffs = 0


	def onGainThresholdReached(self, ticks, event):
		self.heal(ticks * self.getP_m("heal"), event)
		self.miniActivate()


	def onUseThresholdReached(self, ticks, event):
		self.giveLucky(ticks * self.luck, event)
		self.giveMana(ticks * self.mana, event)
		self.miniActivate()


	def onBuffsChanged(self, amount, event):
		if event.getOrigin() in self.affectedItemsDict:
			if amount > 0:
				self.gainedBuffs += amount
				ticks = _div(self.gainedBuffs, self.gainedThreshold)
				if ticks > 0:
					self.onGainThresholdReached(ticks, event)
					self.gainedBuffs %= self.gainedThreshold
			else:

				self.usedBuffs += int(abs(amount))
				ticks = _div(self.usedBuffs, self.usedThreshold)
				if ticks > 0:
					self.onUseThresholdReached(ticks, event)
					self.usedBuffs %= self.usedThreshold


	def doCooldownEffect(self):
		self.giveLucky(self.luck2)
		self.giveMana(self.mana2)
		self.activate()


	def playPickupSound(self):
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

	def _readyInit(self):
		super()._readyInit()
		self.gainedThreshold = int(self.getP("gained"))
		self.usedThreshold = int(self.getP("used"))
		self.luck = int(self.getP("luck"))
		self.mana = int(self.getP("mana"))
		self.luck2 = int(self.getP("luck2"))
		self.mana2 = int(self.getP("mana2"))


_R.reg("res://gd_core_items/Exclusive/Toad.gd", Exclusive__Toad)
_R.reg("Toad", Exclusive__Toad)
