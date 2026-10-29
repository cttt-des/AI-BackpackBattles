# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Pop(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/Pop.gd"

	def _init_fields(self):
		super()._init_fields()
		self.previousSpeedBonus = 0.0
		self.speedPerMana = None
		self.maxSpeedBonus = None


	def onPrepare(self):
		self.previousSpeedBonus = 0
		self.connectForCombat(self.character(), "character_mana_changed", "onManaChanged")


	def onManaChanged(self, _amount, _event):
		speed = min(self.maxSpeedBonus, self.speedPerMana * self.character().getMana())
		if speed - self.previousSpeedBonus != 0:
			self.addSpeed(speed - self.previousSpeedBonus)
			self.previousSpeedBonus = speed


	def playPickupSound(self):
		# decomp Items/Exclusive/Pop.gd:21 Sound.playSound_process(popSound, 4, Util.randPitch(0.15))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

		# decomp Items/Exclusive/Pop.gd:25 Sound.playSound(popSound, volume - 0, Util.randPitch(0.15))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
	def _readyInit(self):
		super()._readyInit()
		self.speedPerMana = _div(self.getP('speed'), 100.0)
		self.maxSpeedBonus = _div(self.getP('max'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Pop.gd", Exclusive__Pop)
_R.reg("Pop", Exclusive__Pop)
