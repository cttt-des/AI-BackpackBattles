# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Snake(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Snake.gd"

	def _init_fields(self):
		super()._init_fields()
		self.poison = None
		self.luckPerPet = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Pet)


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_lucky_changed", "onLuckyChanged")


	def onCombatStart(self):
		numPets = self.getNumAffectedItems()
		self.giveLucky(numPets * self.luckPerPet)
		self.giveMaxHealth(numPets * self.getP_m("maxhealth"))
		self.activate()


	def onLuckyChanged(self, amount, event):
		protectChance = amount * self.getChance()
		self.opponent().changeProtectionChance(_R.C("CoreConst").EventType.Poison, protectChance)


	def doCooldownEffect(self):
		self.inflictPoison(self.poison)
		self.activate()


	def playPickupSound(self):
		pitch = self.ctx.rng.randf_range(0.9, 1.1)


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume
		pitch = self.ctx.rng.randf_range(0.9, 1.1)






































	def _readyInit(self):
		super()._readyInit()
		self.poison = self.getP("poison")
		self.luckPerPet = self.getP("luck")


_R.reg("res://gd_core_items/Exclusive/Snake.gd", Exclusive__Snake)
_R.reg("Snake", Exclusive__Snake)
