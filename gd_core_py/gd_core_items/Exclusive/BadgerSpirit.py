# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BadgerSpirit(_R.C("res://gd_core_items/Exclusive/SpiritCompanion.gd")):

	resource_path = "res://gd_core_items/Exclusive/BadgerSpirit.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.healthThreshold = None
		self.manaNeeded = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Nature)


	def onPrepare(self):
		self.activated = False
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDamaged(self, _healthChange, event):
		if not self.activated and self.character().getRelativeHealth() < self.healthThreshold:
			self.activated = True
			self.heal(_div(self.character().getMaxHealth() * self.getP_m('heal'), 100.0), event)


	def doCooldownEffect(self):
		if self.character().getMana() >= self.manaNeeded:
			event = self.useMana(self.manaNeeded)
			self.giveMaxHealth(self.getP_m("maxhealth") + self.getNumAffectedItems() * 
				self.getP_m("maxhealth_bonus"), event)
		self.activate()


	def playPickupSound(self):
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP('healtht'), 100.0)
		self.manaNeeded = int(self.getP("manat"))


_R.reg("res://gd_core_items/Exclusive/BadgerSpirit.gd", Exclusive__BadgerSpirit)
_R.reg("BadgerSpirit", Exclusive__BadgerSpirit)
