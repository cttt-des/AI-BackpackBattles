# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__HyperHedgehog(_R.C("res://gd_core_items/Exclusive/Hedgehog.gd")):

	resource_path = "res://gd_core_items/Exclusive/HyperHedgehog.gd"

	def _init_fields(self):
		super()._init_fields()
		self.damagePerEmpower = None
		self.empower = None


	def onHPLow(self, event):
		super().onHPLow(event)
		self.giveEmpower(self.empower, event)


	def doCooldownEffect(self):
		dam = self.descriptor.minDam
		dam += self.character().getSpikes() * self.damagePerSpike
		dam += self.character().getEmpower() * self.damagePerEmpower
		res = self.dealEffectDamage(dam)
		self.activate(res)


	def playPickupSound(self):
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume
		# ★ kernel_r2c 移植补抽：原版此行含 Util.randPitch(0.1)（=randf_range(0.9, 1.1)，
		#   Util.gd:685-686），转译期随音效行被剥——链消耗丢失（activate() 虚分发
		#   后此覆写生效，抽面必须与原版一致）。
		self.ctx.rng.randf_range(0.9, 1.1)


	def spawnSpikeParticles(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.damagePerEmpower = self.getP("dam_empower")
		self.empower = int(self.getP("empower"))


_R.reg("res://gd_core_items/Exclusive/HyperHedgehog.gd", Exclusive__HyperHedgehog)
_R.reg("HyperHedgehog", Exclusive__HyperHedgehog)
