# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Rat(_R.C("res://gd_core_items/Exclusive/ForestFriend.gd")):

	resource_path = "res://gd_core_items/Exclusive/Rat.gd"

	def _init_fields(self):
		super()._init_fields()
		self.poison = 0
		self.blind = 0


	def initRat(self):
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)
		self.poison = int(self.getP("poison"))
		self.blind = int(self.getP("blind"))


	def doCooldownEffect(self):
		dam = self.descriptor.minDam
		res = self.dealEffectDamage(dam)
		if self.rollChance():
			self.inflictPoison(self.poison, res.event)
		if self.rollChance2():
			self.inflictBlind(self.blind, res.event)

		self.activate(res)


	def playPickupSound(self):
		pitch = self.ctx.rng.randf_range(0.9, 1.1)


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume
		pitch = self.ctx.rng.randf_range(0.9, 1.1)

	def _readyInit(self):
		super()._readyInit()
		self.initRat()



_R.reg("res://gd_core_items/Exclusive/Rat.gd", Exclusive__Rat)
_R.reg("Rat", Exclusive__Rat)
