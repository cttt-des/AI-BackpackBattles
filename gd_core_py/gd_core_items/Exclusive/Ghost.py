# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Ghost(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Ghost.gd"

	def _init_fields(self):
		super()._init_fields()
		self.unhealing = None
		self.activationParticles = None


	def onPrepare(self):
		self.character().giveUnhealing(self.unhealing)


	def doCooldownEffect(self):
		useEvents = self.useRandomBuffs(1)
		if useEvents != None:
			self.heal(self.getP_m("heal"), useEvents[0])
		self.activate()


	def playPickupSound(self):
		# decomp Items/Exclusive/Ghost.gd:20 Sound.playSound_process(pickupSound, - 4, Util.randPitch(0.3) - 0.1)——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

		# decomp Items/Exclusive/Ghost.gd:24 Sound.playSound(dropSound, volume - 4, Util.randPitch(0.3) - 0.1)——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
	def _readyInit(self):
		super()._readyInit()
		self.unhealing = _div(self.getP('unhealing'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Ghost.gd", Exclusive__Ghost)
_R.reg("Ghost", Exclusive__Ghost)
