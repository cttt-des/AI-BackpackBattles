# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Squirrel(_R.C("res://gd_core_items/Exclusive/ForestFriend.gd")):

	resource_path = "res://gd_core_items/Exclusive/Squirrel.gd"


	def doCooldownEffect(self):
		self.stealRandomBuff(1)
		self.activate()


	def playPickupSound(self):
		pitch = self.ctx.rng.randf_range(0.9, 1.1)


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume
		pitch = self.ctx.rng.randf_range(0.9, 1.1)


	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/Squirrel.gd", Exclusive__Squirrel)
_R.reg("Squirrel", Exclusive__Squirrel)
