# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PoisonFrog(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/PoisonFrog.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedItemsDict = {}
		self._gainedBuffs = 0
		self._usedBuffs = 0
		self._gainedThreshold = 0
		self._usedThreshold = 0
		self.poison = None
		self.mana = None

	@property
	def gainedBuffs(self):
		return self._gainedBuffs
	@gainedBuffs.setter
	def gainedBuffs(self, v):
		self._gainedBuffs = int(v)
	@property
	def usedBuffs(self):
		return self._usedBuffs
	@usedBuffs.setter
	def usedBuffs(self, v):
		self._usedBuffs = int(v)
	@property
	def gainedThreshold(self):
		return self._gainedThreshold
	@gainedThreshold.setter
	def gainedThreshold(self, v):
		self._gainedThreshold = int(v)
	@property
	def usedThreshold(self):
		return self._usedThreshold
	@usedThreshold.setter
	def usedThreshold(self, v):
		self._usedThreshold = int(v)

	def canAffect(self, item):
		return item.gainsBuffs() or item.usesBuffs()


	def onPrepare(self):
		self.affectedItemsDict.clear()
		for item in _iter(self.getAffectedItems()):
			self.affectedItemsDict[item] = True
		self.connectToCharacterBuffs("onBuffsChanged")
		self.gainedBuffs = 0
		self.usedBuffs = 0


	def onBuffsChanged(self, amount, event):
		if event.getOrigin() in self.affectedItemsDict:
			if amount > 0:
				self.gainedBuffs += amount
				ticks = _div(self.gainedBuffs, self.gainedThreshold)
				if ticks > 0:
					self.heal()


					self.gainedBuffs %= self.gainedThreshold
					self.miniActivate()

			else:

				self.usedBuffs += int(abs(amount))
				ticks = _div(self.usedBuffs, self.usedThreshold)
				if ticks > 0:
					self.inflictPoison(ticks * self.poison, event)
					self.giveMana(ticks * self.mana, event)
					self.usedBuffs %= self.usedThreshold
					self.miniActivate()


	def doCooldownEffect(self):
		self.inflictPoison(self.getP("poison2"))
		self.giveMana(self.getP("mana2"))
		self.activate()


	def playPickupSound(self):
		pitch = self.ctx.rng.randf_range(0.9, 1.1)


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume
		pitch = self.ctx.rng.randf_range(0.9, 1.1)

	def _readyInit(self):
		super()._readyInit()
		self.gainedThreshold = self.getP("gained")
		self.usedThreshold = self.getP("used")
		self.poison = int(self.getP("poison"))
		self.mana = int(self.getP("mana"))


_R.reg("res://gd_core_items/Exclusive/PoisonFrog.gd", Exclusive__PoisonFrog)
_R.reg("PoisonFrog", Exclusive__PoisonFrog)
